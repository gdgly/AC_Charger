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
 * \brief 电表实例
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "event_node.h"
#include "role.h"
#include "aw_task.h"
#include "string.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "ammeter.h"
#include "ammeter/aw_ammeter.h"
#include "ac_charge_prj_cfg.h"

#define VOL_TO_AMMETER(p_this, pp_role) \
    struct ammeter *p_this = AW_CONTAINER_OF(pp_role, struct ammeter, p_ammeter_vol)

#define CURR_TO_AMMETER(p_this, pp_role) \
    struct ammeter *p_this = AW_CONTAINER_OF(pp_role, struct ammeter, p_ammeter_curr)


#define EVT_TO_AMMETER(p_this, p_evt) \
    struct ammeter *p_this = AW_CONTAINER_OF(p_evt, struct ammeter, evt_node)

static void event_driver(struct event_node *p_evt, event_t event, void *p_arg);
static role_ret play(role_t **pp_role, void *p_arg);  /* 扮演 */

static role_ret ammeter_vol_do (struct role **pp_role, void *p_arg);


#define PILE_OVER_VOL_VAL    2500  /* 过压值  单位0.1V */
#define PILE_UNDER_VOL_VAL   1700  /* 欠压值  单位0.1V */

#define PILE_CURR_POINT       20000        /* 电流监控点  20A*/
#define PILE_CURR_TIMEOUT     5000         /* 电流异常最大超时时间 ，异常时间大于该时间确认为异常 */
#define PILE_CURR_MIN_TIMEOUT 60000        /* 最大允许空载的时间  */
#define PILE_CURR_MIN         3000         /* 充电过程中，允许的最小电流  3A */

/**
 *  \brief 充电模块实例初始化
 *  param [in]   p_this        : 充电模块实例
 *  */
void ammeter_inst_init(ammeter_t *p_this, aw_ammeter_t *p_ammeter_driver, uint32_t max_curr)
{
    static role_t ammeter_vol    = {ammeter_vol_do};  /* 可扮演的角色 - 电压监控器 */
    p_this->player.pfn_play      = play;
    p_this->evt_node.pfunc_event = event_driver;
    p_this->p_ammeter_driver     = p_ammeter_driver;
    p_this->p_ammeter_curr       = NULL;
    p_this->p_ammeter_vol        = &ammeter_vol;
    p_this->max_curr             = max_curr;
    p_this->start_ticks          = 0;
    p_this->abnormal_state       = FALSE;
    p_this->enable_curr_check    = TRUE;
    AW_MUTEX_INIT(p_this->dev_lock, AW_SEM_Q_PRIORITY);
    AW_MUTEX_INIT(p_this->role_lock, AW_SEM_Q_PRIORITY);
}

/* ===============================扮演者与角色===================================  */
static role_ret play(role_t **pp_role, void *p_arg)  /* 扮演 */
{
    if ((*pp_role)->pfn_role_do) {
        return (*pp_role)->pfn_role_do(pp_role, p_arg);
    }
    return -AW_EINVAL;
}
/* 电压监控角色 */
static role_ret ammeter_vol_do (struct role **pp_role, void *p_arg)
{
#define VOL_DETECT_STEP_IDLE   0  /* 电压检测空闲状态  */
#define VOL_DETECT_STEP_UNDER  1  /* 欠压确认状态  */
#define VOL_DETECT_STEP_OVER   2  /* 过压确认状态  */

    VOL_TO_AMMETER(p_this, pp_role);
    int32_t  vol = (int32_t)p_arg;

    switch (p_this->vol_step) {

    case  VOL_DETECT_STEP_IDLE:
        if (PILE_UNDER_VOL_VAL >= vol) {
            /* 欠压 */
            p_this->vol_step = VOL_DETECT_STEP_UNDER;
        } else if (PILE_OVER_VOL_VAL <= vol) {
            /* 过压 */
            p_this->vol_step = VOL_DETECT_STEP_OVER;
        } else {
           if ( p_this->vol_state != AMMETER_VOL_STATE_NORMAL) {
               p_this->vol_state = AMMETER_VOL_STATE_NORMAL;
               /* todo 发起电压正常事件 */
               event_node_tell_all(&p_this->evt_node, ERR_AMMETER_VOL, p_this->vol_state);
           }
        }

        break;

    case  VOL_DETECT_STEP_UNDER:
        if (PILE_UNDER_VOL_VAL >= vol) {
            /* 欠压 */
            if ( p_this->vol_state != AMMETER_VOL_STATE_UNDER) {
                p_this->vol_state = AMMETER_VOL_STATE_UNDER;
                /* todo 发起欠压异常事件 */
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER_VOL, p_this->vol_state);
            }
        } else {
            p_this->vol_step = VOL_DETECT_STEP_IDLE;
        }
        break;


    case VOL_DETECT_STEP_OVER:
        if (PILE_OVER_VOL_VAL <= vol) {
            /* 过压 */
            if ( p_this->vol_state != AMMETER_VOL_STATE_OVER) {
                p_this->vol_state = AMMETER_VOL_STATE_OVER;
                /* todo 发起过压异常事件 */
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER_VOL, p_this->vol_state);
            }
        } else {
            p_this->vol_step = VOL_DETECT_STEP_IDLE;
        }
        break;
    default:break;
    }
    return AW_OK;
}

/* 电流监控角色 */
static role_ret ammeter_curr_do (struct role **pp_role, void *p_arg)
{
    CURR_TO_AMMETER(p_this, pp_role);
    uint32_t curr = (uint32_t)p_arg;
    aw_tick_t  end_ticks;
    uint32_t   timeout_ms;

    if (curr <= PILE_CURR_MIN) {
        /* 电流异常*/
        if (0 == p_this->start_ticks) {
            p_this->start_ticks = aw_sys_tick_get() + 1;
        } else {
            end_ticks  = aw_sys_tick_get();
            timeout_ms = aw_ticks_to_ms(end_ticks - p_this->start_ticks);
            if (timeout_ms > PILE_CURR_MIN_TIMEOUT) {
                 /* 发送电流异常信号 （空载异常 ）*/
                if (p_this->curr_state != AMMETER_CURR_STATE_UNDER) {
                    /* todo 发送欠流事件*/
                    p_this->curr_state = AMMETER_CURR_STATE_UNDER;
                    event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
                }

            }
        }
    } else if (p_this->max_curr <= PILE_CURR_POINT) {

        if (curr > ( p_this->max_curr + 2000)) {
            /* 电流异常*/
            if (0 == p_this->start_ticks) {
                p_this->start_ticks = aw_sys_tick_get();
            } else {
                end_ticks  = aw_sys_tick_get();
                timeout_ms = aw_ticks_to_ms(end_ticks - p_this->start_ticks);
                if (timeout_ms > PILE_CURR_TIMEOUT) {
                     /* 发送电流异常信号 （过流异常 ）*/
                    if (p_this->curr_state != AMMETER_CURR_STATE_OVER) {
                        /* todo 发送过流事件*/
                        p_this->curr_state = AMMETER_CURR_STATE_OVER;
                        event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
                    }
                }
            }
        } else  {
            /* todo 电流正常 */
            p_this->start_ticks = 0;
            if (p_this->curr_state != AMMETER_CURR_STATE_NORMAL) {
                /* todo 发送电流正常事件*/
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
            }
            p_this->curr_state = AMMETER_CURR_STATE_NORMAL;
        }
    } else {
        if (curr > ((uint32_t)(p_this->max_curr * 1.1))) {
            /* 电流异常*/
            if (0 == p_this->start_ticks) {
                p_this->start_ticks = aw_sys_tick_get();
            } else {
                end_ticks  = aw_sys_tick_get();
                timeout_ms = aw_ticks_to_ms(end_ticks - p_this->start_ticks);
                if (timeout_ms > PILE_CURR_TIMEOUT) {

                    if (p_this->curr_state != AMMETER_CURR_STATE_OVER) {
                        /* todo 发送过流事件*/
                        p_this->curr_state = AMMETER_CURR_STATE_OVER;
                        event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
                    }

                }
            }
        } else {
            /* todo 电流正常 */
            p_this->start_ticks = 0;
            if (p_this->curr_state != AMMETER_CURR_STATE_NORMAL) {
                /* todo 发送电流正常事件*/
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
            }
            p_this->curr_state = AMMETER_CURR_STATE_NORMAL;

        }
    }
    return AW_OK;
}


static void event_driver(struct event_node *p_evt, event_t event, void *p_arg)
{
    EVT_TO_AMMETER(p_this, p_evt);

    static role_t ammeter_curr  = {ammeter_curr_do};

    switch (event) {

    case CHARGE_PIEL_START:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_ammeter_curr = &ammeter_curr;
        p_this->curr_state     = AMMETER_CURR_STATE_NORMAL;
        p_this->start_ticks    = 0;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CHARGE_PILE_STOP:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_ammeter_curr = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    default : break;

    }

}

/* ========================================================================= */
#define AMMETER_TASK_PRIO       4
#define AMMETER_TACK_SIZE       2048
#define AMMETER_DETECT_PERIOD   1000
AW_TASK_DECL_STATIC(ammeter_task, AMMETER_TACK_SIZE);

/**
 * 卡探测任务
 */
static void ammeter_task_entry (void *p_arg)
{
    ammeter_t *p_this = (ammeter_t *)p_arg;

    uint32_t energy = 0, scnt = 0, cnt = 0;
    int32_t  vol    = 0;
    uint32_t curr   = 0;
    role_t     *p_role[2];
    uint8_t     state = FALSE;

    if ((NULL == p_this) ||
        (NULL == p_this->p_ammeter_driver)) {
        return ;
    }
    aw_ammeter_dc_inst_init(p_this->p_ammeter_driver);

    while (1) {

        scnt++;
        /* 获取电量 */
        if ((AW_OK == aw_ammeter_active_energy_get(p_this->p_ammeter_driver, &energy))) {
            state = 0;
//            aw_kprintf("eng: %06d (0.01KWh)     Err: %d - %d\r\n", energy, scnt, cnt);
#if ACP1000_AMMETER_ERR_DETECT
            cnt = 0;
            if (TRUE == p_this->abnormal_state) {
                p_this->abnormal_state = FALSE;
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER, FALSE);
            }
#endif
        } else {
            state = 0x1;
#if ACP1000_AMMETER_ERR_DETECT
            cnt++;
            if (cnt >= 2) {
                /* 通信3次失败，认为电表有异常 */
                if (FALSE == p_this->abnormal_state) {
                    p_this->abnormal_state = TRUE;
                    event_node_tell_all(&p_this->evt_node, ERR_AMMETER, TRUE);
                }
            }
#endif
        }
        aw_mdelay(30);
        /* 获取电压 */
        if (AW_OK == aw_ammeter_voltage_get(p_this->p_ammeter_driver, 0, &vol)) {
            state &= ~0x2;
        } else {
            state |=  0x2;
        }
        aw_mdelay(30);
        /* 获取电流 */
        if (AW_OK == aw_ammeter_current_get(p_this->p_ammeter_driver, 0, &curr)) {
            state &= ~0x4;
        } else {
            state |=  0x4;
        }

        if (state == 0) {
            ammeter_dev_lock(p_this);
            p_this->dat.now_curr   = curr;
            p_this->dat.now_vol    = vol;
            p_this->dat.now_energy = energy;
            ammeter_dev_unlock(p_this);

            /* 发送电量数据 */
            event_node_tell_all(&p_this->evt_node, AMETER_MEASURE, &p_this->dat);
        }

#if ACP1000_VOL_ERR_DETECT
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_role[0] = p_this->p_ammeter_vol;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        /* 监控电压 */
        if (NULL != p_role[0]) {
            p_this->player.pfn_play(&p_this->p_ammeter_vol, vol);
        }
#endif

#if ACP1000_CURR_ERR_DETECT
        if (p_this->enable_curr_check) {
            AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
            p_role[1] = p_this->p_ammeter_curr;
            AW_MUTEX_UNLOCK(p_this->role_lock);

            /* 监控电流*/
            if (NULL != p_role[1]) {
                p_this->player.pfn_play(&p_this->p_ammeter_curr, curr);
            } else {
                /* 无需监控电流时 ，认为电流正常 */
                if (p_this->curr_state != AMMETER_CURR_STATE_NORMAL) {
                    p_this->curr_state     = AMMETER_CURR_STATE_NORMAL;
                    event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
                }
            }
        }
#endif
        aw_mdelay(AMMETER_DETECT_PERIOD);
    }
}

void ammeter_task_startup (ammeter_t *p_this)
{
    AW_TASK_INIT(ammeter_task,           /* 任务实体 */
                 "ammeter_task",            /* 任务名字 */
                 AMMETER_TASK_PRIO,      /* 任务优先级 */
                 AMMETER_TACK_SIZE,      /* 任务堆栈大小 */
                 ammeter_task_entry,     /* 任务入口函数 */
                 (void *)p_this);        /* 任务入口参数 */
    /* 启动任务 */
    AW_TASK_STARTUP(ammeter_task);
}


