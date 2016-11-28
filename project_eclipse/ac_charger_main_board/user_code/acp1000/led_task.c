/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief ACP1000 低优先级监控任务
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-27  xjc, first implementation
 * \endinternal
 */

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "acp1000_din.h"
#include "acp1000_dout.h"
#include "aw_time.h"
#include "aw_rtc.h"
#include "pile.h"
#include "string.h"
#include "aw_delayed_work.h"

#define PILE_TASK_PERIOD  1000 /* 任务执行周期 */
#define PILE_TASK_PRIO    5
#define PILE_TACK_SIZE    (2048)
AW_TASK_DECL_STATIC(pile_task, PILE_TACK_SIZE);

bool_t g_ac_check_en = 1;
bool_t g_need_ac_check  = TRUE;
/**
 * 桩任务任务入口
 */
static void pile_task_entry(void *p_arg)
{

#define __LED_STATE_MONITOR  0 /* 监控中    */
#define __LED_STATE_FORSURE  1 /* 异常确认 */

    pile_t *p_pile = (pile_t *)p_arg;
    uint32_t alarm;
    bool_t   charge_state;
    bool_t   auth_state;
    bool_t   ac_state;
    int      cnt_lock = 0, cnt_unlock = 0;
    pile_time_price_t  tm_price;
    uint16_t price;
    uint8_t  ac_pin_state     = 0;
    uint8_t  ac_err_cnt       = 0;    /* 充电中接触器异常计数，用于防掉电自动恢复 */
    uint8_t  gun_lock_err_cnt = 0;    /* 枪内置锁异常检测计数，若异常计数过多，则锁要重新操作锁  */
    bool_t   splash_yled      = FALSE; /* 充电指示灯闪烁标志 */

    if (p_pile == NULL) {
        return;
    }

    while (1) {

        pile_dev_lock(p_pile);
        alarm        = p_pile->pile_alarm.alarm_mask;
        charge_state = p_pile->pile_dat.charge_state;
        auth_state   = p_pile->pile_dat.auth_state;
        ac_state      = p_pile->pile_dat.charge_ac_state;
        pile_dev_unlock(p_pile);


        ac_pin_state =  aw_gpio_get(ACP1000_DIN_AC1);
        /* ---------------设置LED -------------*/
        if (alarm == PILE_ALARM_NONE) {
            if ((0 == ac_pin_state) || charge_state) {
                splash_yled = !splash_yled;
                acp1000_state_led_set(ACP1000_LED_STATE_YELLOW, splash_yled);
            } else {
                acp1000_state_led_set(ACP1000_LED_STATE_GREEN, FALSE);
            }
        } else {
            acp1000_state_led_set(ACP1000_LED_STATE_RED,
                          ((0 == ac_pin_state) || charge_state) ? TRUE : FALSE);
        }
        if ((0 == ac_pin_state) || charge_state) {
            aw_gpio_set(ACP1000_DOUT_LEDS, 1);
        } else {
            aw_gpio_set(ACP1000_DOUT_LEDS, 0);
        }

#if ACP1000_AC1_ERR_DETECT
        /* ---------------接触器异常检测 -------------*/
        if (g_ac_check_en && g_need_ac_check) {
            if (1 == ac_pin_state) {
                if (ac_state == TRUE) {
                    ac_err_cnt++;
                    if (ac_err_cnt >= 2) {
                        ac_err_cnt = 0;
                        /* todo 发送AC接触器异常警报 */
                        event_node_tell_all(&p_pile->evt_node, ERR_AC, TRUE);
                    }
                } else {
                    ac_err_cnt = 0;
                    event_node_tell_all(&p_pile->evt_node, ERR_AC, FALSE);
                }
            } else {
                ac_err_cnt = 0;
                if (ac_state == FALSE) {
                    /* todo 发送AC接触器异常警报 */
                    event_node_tell_all(&p_pile->evt_node, ERR_AC, TRUE);
                } else {
                    event_node_tell_all(&p_pile->evt_node, ERR_AC, FALSE);
                }
            }
        }
#endif

#if ACP1000_INLOCK_TASK
        /* ---------------内置的桩枪套锁操作 -------------*/
        if (auth_state == TRUE) {
            /* 用户已将鉴权成功，解锁*/
            if (p_pile->pile_dat.gun_lock) {
                p_pile->pile_dat.gun_lock = FALSE;
                acp1000_gun_unlock();
            } else {
                if (1 == aw_gpio_get(ACP1000_DIN_INLOCK)) {
                    gun_lock_err_cnt++;
                    if (gun_lock_err_cnt >= 3) {
                        /* 解锁不成功， 重试解锁 */
                        gun_lock_err_cnt = 0;
                        acp1000_gun_unlock();
                        event_node_tell_all(&p_pile->evt_node, ERR_PILE_GUN_LOCK, TRUE);
                    }
                } else {
                    gun_lock_err_cnt = 0;
                    event_node_tell_all(&p_pile->evt_node, ERR_PILE_GUN_LOCK, FALSE);
                }
            }

        } else {
            if (1 == aw_gpio_get(ACP1000_DIN_INGUN)) {
                event_node_tell_all(&p_pile->evt_node, ERR_PILE_GUN_CONN, FALSE);
               /* 枪在 ，锁上 */
                cnt_unlock = 0;
                cnt_lock++;
                if (cnt_lock >= 2) {
                    cnt_lock = 0;
                    if (!(p_pile->pile_dat.gun_lock)) {
                        p_pile->pile_dat.gun_lock = TRUE;
                        acp1000_gun_lock();
                    } else {
                        if (0 == aw_gpio_get(ACP1000_DIN_INLOCK)) {
                            acp1000_gun_lock();
                            event_node_tell_all(&p_pile->evt_node, ERR_PILE_GUN_LOCK, TRUE);
                        } else {
                            event_node_tell_all(&p_pile->evt_node, ERR_PILE_GUN_LOCK, FALSE);
                        }
                    }

                }
            } else {
                event_node_tell_all(&p_pile->evt_node, ERR_PILE_GUN_CONN, TRUE);
               /* 枪不在 ，解锁 */
                cnt_lock = 0;
                cnt_unlock++;
                if (cnt_unlock >= 2) {
                    cnt_unlock = 0;
                    if ((p_pile->pile_dat.gun_lock)) {
                        p_pile->pile_dat.gun_lock = FALSE;
                        acp1000_gun_unlock();
                    } else {
                        if (1 == aw_gpio_get(ACP1000_DIN_INLOCK)) {
                            acp1000_gun_unlock();
                            event_node_tell_all(&p_pile->evt_node, ERR_PILE_GUN_LOCK, TRUE);
                        } else {
                            event_node_tell_all(&p_pile->evt_node, ERR_PILE_GUN_LOCK, FALSE);
                        }
                    }
                }
            }
        }
#endif
        /* ---------------设置时间 -------------*/
        if (aw_rtc_time_get(ACP1000_RTC_NUM, &tm_price.tm) == AW_OK) {

        } else {
            /* 若RTC无法获取则，电价为默认电价 */
            tm_price.tm.tm_hour = 0;
        }
        /* 实时设置时间 */
        event_node_tell_all(&p_pile->evt_node, PILE_TIME, &tm_price);
        pile_dev_lock(p_pile);
        memcpy(&p_pile->pile_time, &tm_price, sizeof(pile_time_price_t));
        pile_dev_unlock(p_pile);

        event_node_tell_all(&p_pile->evt_node, PILE_ALARM, p_pile->pile_alarm.alarm_mask);

        event_node_tell_all(&p_pile->evt_node, PILE_DUGS_INFO, &(p_pile->pile_dat));

        aw_mdelay(PILE_TASK_PERIOD);
    }
}

static struct aw_delayed_work g_time_work; /* 运行时间工作  */
/**
 * 鉴权后无操作超时检测任务
 */
static void time_run_work (void *p_arg)
{
    aw_tm_t tm;
    time_t  now_time;
    pile_t *p_pile = (pile_t *)p_arg;
    static  uint32_t last_time = 0;

    if (NULL == p_pile) {
        return;
    }

    aw_rtc_time_get (ACP1000_RTC_NUM, &tm);
    aw_tm_to_time(&tm, &now_time);

    pile_dev_lock(p_pile);
    if (0 == p_pile->pile_dat.start_time) {
        p_pile->pile_dat.start_time = now_time;
    } else {
        p_pile->pile_dat.run_time  = (now_time - p_pile->pile_dat.start_time) / 60;
        if (((uint32_t)(p_pile->pile_dat.run_time - last_time)) > 2) {
            /* 前后时间相差过大，可能由于重新设置时间所导致，故重新设定时间计数 */
            p_pile->pile_dat.run_time   = 0;
            p_pile->pile_dat.start_time = 0;
        }
        last_time = p_pile->pile_dat.run_time;
    }
    pile_dev_unlock(p_pile);
    aw_delayed_work_start(&g_time_work, 30000); /* 每30秒执行一次  */
}

void led_task_startup (pile_t *p_pile)
{
    AW_TASK_INIT(pile_task,        /* 任务实体 */
                "pile_task",       /* 任务名字 */
                PILE_TASK_PRIO,    /* 任务优先级 */
                PILE_TACK_SIZE,    /* 任务堆栈大小 */
                pile_task_entry,   /* 任务入口函数 */
                (void *)p_pile);   /* 任务入口参数 */
    /* 启动任务 */
    AW_TASK_STARTUP(pile_task);

    /* 运行时间任务 */
    aw_delayed_work_init(&g_time_work,
                          time_run_work,
                          p_pile);
    aw_delayed_work_start(&g_time_work, 30000); /* 上电后30秒后执行 */
}


