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
 * \brief 桩实例
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "event_node.h"
#include "aw_task.h"
#include "string.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_time.h"
#include "aw_rtc.h"
#include "ac_charge_prj_cfg.h"
#include "pile.h"
#include "ammeter.h"
#include "acp1000_din.h"
#include "acp1000_dout.h"
#include "mb/aw_mb_dgus_regmap.h"
#include "aw_nvram.h"

#define EVT_TO_PILE(p_this, p_evt) \
    struct pile *p_this = AW_CONTAINER_OF(p_evt, struct pile, evt_node)

static void  event_driver(struct event_node *p_evt, event_t event, void *p_arg);

/**
 *  \brief 充电模块实例初始化
 *  param [in]   p_this        : 整机实例
 *  */
void pile_inst_init(pile_t *p_this)
{
    uint8_t addr;

    memset(p_this, 0, sizeof(pile_t));
    p_this->evt_node.pfunc_event = event_driver;
    AW_MUTEX_INIT(p_this->dev_lock, AW_SEM_Q_PRIORITY);
    AW_SEMB_INIT(p_this->pile_sem.hub4g_key_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
    AW_SEMB_INIT(p_this->pile_sem.hub4g_auth_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
    AW_SEMB_INIT(p_this->pile_sem.hub4g_billing_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
    AW_SEMB_INIT(p_this->pile_sem.hub4g_cctrl_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
    AW_SEMB_INIT(p_this->pile_sem.charge_gun_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);

    p_this->pile_dat.gun_lock = TRUE; /* 默认上电枪已经被锁住 */

#if ACP1000_EEPROM_HUB4G_ADDR_GET
    if(AW_OK == aw_nvram_get(ACP1000_EEPROM_NAME, 2, &addr, 0, 1)) {
        p_this->pile_dat.hub4g_addr = addr;
    }
#endif
}

/* ========================================================================= */
static void event_driver(struct event_node *p_evt, event_t event, void *p_arg)
{
    EVT_TO_PILE(p_this, p_evt);
    uint32_t arg = (uint32_t)p_arg;
    ammeter_dat_t *p_ammeter_dat = NULL;

    switch (event) {

    case CARD_AUTH_SUS:
    case SCREEN_UNLOCK:
        pile_dev_lock(p_this);
        p_this->pile_dat.auth_state = TRUE;
        pile_dev_unlock(p_this);
        break;

    case CARD_AUTH_FAIL:
        pile_dev_lock(p_this);
        p_this->pile_dat.auth_state = FALSE;
        pile_dev_unlock(p_this);
        break;

    case CHARGE_PIEL_START:
        pile_dev_lock(p_this);
        p_this->pile_dat.charge_cnt++;
        p_this->pile_dat.charge_state = TRUE;
        pile_dev_unlock(p_this);
        break;

    case CHARGE_PILE_STOP:
        pile_dev_lock(p_this);
        p_this->pile_dat.charge_state = FALSE;
        p_this->pile_dat.auth_state = FALSE;
        pile_dev_unlock(p_this);
        break;

    case GUN_INSERT:
        pile_dev_lock(p_this);
        p_this->pile_dat.gun_state = TRUE;
        pile_dev_unlock(p_this);
        break;

    case GUN_EXTRACT:
        pile_dev_lock(p_this);
        p_this->pile_dat.gun_state    = FALSE;
        p_this->pile_dat.charge_state = FALSE;
        pile_dev_unlock(p_this);
        break;

    case ERR_AMMETER_VOL:
        if (arg == AMMETER_VOL_STATE_UNDER) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_UNDERVOL;
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_OVERVOL;
            pile_dev_unlock(p_this);
        } else if (arg == AMMETER_VOL_STATE_OVER) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_UNDERVOL;
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_OVERVOL;
            pile_dev_unlock(p_this);
        } else {
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_UNDERVOL;
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_OVERVOL;
        }
        break;

    case ERR_AMMETER_CURR:
        if (arg != AMMETER_CURR_STATE_NORMAL) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_CURR;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_CURR;
            pile_dev_unlock(p_this);
        }
        break;

    case ERR_CARD_READER:
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_CARDREADER;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_CARDREADER;
            pile_dev_unlock(p_this);
        }
        break;

    case ERR_AMMETER:
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_AMMETER;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_AMMETER;
            pile_dev_unlock(p_this);
        }
        break;

    case ERR_SCRAM:
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_SCRAM;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_SCRAM;
            pile_dev_unlock(p_this);
        }
        break;

    case ERR_LIGHT:
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_LIGHT;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_LIGHT;
            pile_dev_unlock(p_this);
        }
        break;

    case ERR_AC:
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_ACLOCK;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_ACLOCK;
            pile_dev_unlock(p_this);
        }
        break;

    /* 接收电表的数据  */
    case AMETER_MEASURE:
        p_ammeter_dat = (ammeter_dat_t *)p_arg;
        pile_dev_lock(p_this);
        p_this->pile_dat.input_vol  = p_ammeter_dat->now_vol;
        p_this->pile_dat.input_curr = p_ammeter_dat->now_curr;
        pile_dev_unlock(p_this);
        break;

    case PILE_TEMP:
        pile_dev_lock(p_this);
        p_this->pile_dat.temp = (int16_t)p_arg;
        pile_dev_unlock(p_this);
        break;

    case ERR_TEMP:
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_TEMP;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_TEMP;
            pile_dev_unlock(p_this);
        }
        break;

    case ERR_CHAGER:
        if (arg >= AW_MB_DGUS_CHARGE_CARDREADER) {
            pile_dev_lock(p_this);
            p_this->pile_dat.err_cnt++;
            pile_dev_unlock(p_this);
        }
        break;

    case CHARGE_AC_STATE:
        pile_dev_lock(p_this);
        p_this->pile_dat.charge_ac_state = arg ? TRUE : FALSE;
        pile_dev_unlock(p_this);
        break;

    case ERR_DUGS:
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_LCD;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_LCD;
            pile_dev_unlock(p_this);
        }
        break;

    case ERR_HUB4G_COMM: /* 集中器通信故障*/
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask |= PILE_ALARM_HUB4G_COM;
            p_this->pile_dat.bg_state     |= 0x2;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_alarm.alarm_mask &= ~PILE_ALARM_HUB4G_COM;
            p_this->pile_dat.bg_state     &= ~0x2;
            pile_dev_unlock(p_this);
        }
        break;
    case ERR_HUB4G:   /* 4G通信故障*/
        if (arg) {
            pile_dev_lock(p_this);
            p_this->pile_dat.bg_state |= 0x1;
            pile_dev_unlock(p_this);
        }  else {
            pile_dev_lock(p_this);
            p_this->pile_dat.bg_state &= ~0x1;
            pile_dev_unlock(p_this);
        }
        break;

    case DUGS_HUB4G_ADDR:
        pile_dev_lock(p_this);
        p_this->pile_dat.hub4g_addr = (uint8_t)p_arg;
        pile_dev_unlock(p_this);
        break;

    default:break;
    }
}

/* ========================================================================= */
#define PILE_TASK_PRIO       2
#define PILE_TACK_SIZE       1024
#define PILE_DETECT_PERIOD   15
AW_TASK_DECL_STATIC(pile_task, PILE_TACK_SIZE);

/**
 * 桩异常检测任务
 */
static void pile_task_entry (void *p_arg)
{
    pile_t *p_this = (pile_t *)p_arg;
    static  int cnt = 0;
    uint32_t level;

    if (NULL == p_this) {
        return ;
    }

    while (1) {

        cnt--;
        if (cnt <= 0) {
            cnt = 0;
        }

#if ACP1000_SCRAM_DETECT
        /* 紧急开关检测 */
        level = aw_gpio_get(ACP1000_DIN_SCREEM);
        if (0 == level) {
           /* 延时一段时间，再做紧急开关检测  */
           cnt = 30000 / PILE_DETECT_PERIOD;
           aw_gpio_set(ACP1000_DOUT_AC, FALSE);
           if (!p_this->pile_dat.scram_state) {
               p_this->pile_dat.scram_state = TRUE;
               event_node_tell_all(&p_this->evt_node, ERR_SCRAM, TRUE);
           }
        } else {
           if (cnt == 0) {
               if (p_this->pile_dat.scram_state) {
                   p_this->pile_dat.scram_state = FALSE;
                   //event_node_tell_all(&p_this->evt_node, ERR_SCRAM, FALSE);
                   //2016.6.21屏蔽，以便人为硬件复位才能重新开始充电
               }
           }
        }
#endif

#if ACP1000_LIGHT_ERR_DETECT
        /* 防雷器开关检测 */
        level = aw_gpio_get(ACP1000_DIN_LIGHT);
        if (0 == level) {
            if (!p_this->pile_dat.light_state) {
               p_this->pile_dat.light_state = TRUE;
               event_node_tell_all(&p_this->evt_node, ERR_LIGHT, TRUE);
            }
        } else {
            if (p_this->pile_dat.light_state) {
               p_this->pile_dat.light_state = FALSE;
               event_node_tell_all(&p_this->evt_node, ERR_LIGHT, FALSE);
            }
        }
#endif
    aw_mdelay(PILE_DETECT_PERIOD);
    }
}

void pile_task_startup (pile_t *p_this)
{
    AW_TASK_INIT(pile_task,           /* 任务实体 */
                 "pile_task",         /* 任务名字 */
                 PILE_DETECT_PERIOD,  /* 任务优先级 */
                 PILE_TACK_SIZE,      /* 任务堆栈大小 */
                 pile_task_entry,     /* 任务入口函数 */
                 (void *)p_this);     /* 任务入口参数 */
    /* 启动任务 */
    AW_TASK_STARTUP(pile_task);
}


