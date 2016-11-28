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
 * \brief 充电机实例
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#include "player.h"
#include "aw_sem.h"
#include "aw_task.h"
#include "event_node.h"
#include "charger.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_pwm.h"
#include "role.h"
#include "string.h"
#include "acp1000_din.h"
#include "acp1000_dout.h"
#include "ac_charge_prj_cfg.h"
#include "aw_delayed_work.h"
#include "mb/aw_mb_dgus_regmap.h"

#define IDLE_TO_CHARGER(p_this, pp_role) \
    struct charge *p_this = AW_CONTAINER_OF(pp_role, struct charge, p_charge_idle)

#define ALLOW_TO_CHARGER(p_this, pp_role) \
    struct charge *p_this = AW_CONTAINER_OF(pp_role, struct charge, p_charge_allow)

#define START_TO_CHARGER(p_this, pp_role) \
    struct charge *p_this = AW_CONTAINER_OF(pp_role, struct charge, p_charge_start)

#define ING_TO_CHARGER(p_this, pp_role) \
    struct charge *p_this = AW_CONTAINER_OF(pp_role, struct charge, p_charge_ing)

#define STOP_TO_CHARGER(p_this, pp_role) \
    struct charge *p_this = AW_CONTAINER_OF(pp_role, struct charge, p_charge_stop)

#define ERR_TO_CHARGER(p_this, pp_role) \
    struct charge *p_this = AW_CONTAINER_OF(pp_role, struct charge, p_charge_err)

#define EVT_TO_CHARGER(p_this, p_evt) \
    struct charge *p_this = AW_CONTAINER_OF(p_evt, struct charge, evt_node)

static role_ret play(role_t **pp_role, void *p_arg);  /* 扮演 */
static void event_driver(struct event_node *p_evt, event_t event, void *p_arg);
static role_ret charger_idle_do (struct role **pp_role, void *p_arg);

#define CHARGER_9V_TIMEOUT_MS      10000 /* 汽车未就绪超时异常检测（开始充电后一直在9V的最大持续时间 ） */
#define CHARGER_UNLOCK_TIMEOUT_MS  200   /* 断开交流输出后到解锁的时间（ms）*/
#define CHARGER_ERR_TIMEOUT_MS     3000  /* 自异常发生到切断交流输出的最大容忍时间（ms）*/

/**
 * \brief 充电机电子锁设定
 * \param[in] p_this :  充电桩实例
 * \param[in] islock :  是否锁住电子锁，TRUE：锁定电子锁；FALSE： 解开电子锁
 * \return AW_OK    : 操作成功
 * \return AW_ERROR : 操作失败
 * \note 若充电机没有电子锁，请返回AW_OK，而不做任何事情
 */
static inline aw_err_t charger_elock_lock (charger_t *p_this, bool_t islock)
{
#ifdef ACP1000_DOUT_GUNLOCK
    aw_gpio_set(ACP1000_DOUT_GUNLOCK, islock ? 1 : 0);
#endif
    return AW_OK;
}

extern bool_t g_need_ac_check;
/**
  * \brief 设置AC电压输出
  * \param[in] p_this : 充电桩实例
  * \param[in] enable :  TRUE : 输出AC电压  ， FALSE：禁止AC电压输出
  */
//static
inline void charger_ac_output_enable(charger_t *p_this, bool_t enable)
{
    aw_gpio_set(ACP1000_DOUT_AC, enable ? 1 : 0);

    g_need_ac_check = FALSE;

    charger_dev_lock(p_this);
    p_this->dat.ac_enable = enable;
    charger_dev_unlock(p_this);



#if ACP1000_AC1_ERR_DETECT
    aw_delayed_work_stop(&(p_this->ac_detect_dk));
    aw_delayed_work_start(&(p_this->ac_detect_dk), 1000); /* 母排电磁继电器一般为0.3-0.5s */
#endif
}

#define ACP1000_CURR_PWM_PERIOD    (1000000UL) /* 电流指示PWM周期 1ms 即1KHz */

/**
 * \brief 设置可输出的最大电流
 * \param[in] p_this   :  交流充电机实例
 * \param[in] current  :  充电机可输出的最大电流，单位0.01A
 * \note 电流值被调制成一定的占空比，当为current为0时，占空比占100%(测试点1接12V)
 */
static void charger_current_limit(charger_t *p_this, uint32_t current)
{
    uint32_t duty = 0; /* 占空比 */
    uint32_t curr_pwm_id = p_this->dat.curr_pwm;

    if (current < 600) {
        /* 其他电流输出100%占空比 */
        duty =  ACP1000_CURR_PWM_PERIOD;
    } else if (current == 600) {
        duty = (ACP1000_CURR_PWM_PERIOD / 100) * 9;
    } else if (current <= 5100) {
        duty = ((4 * ACP1000_CURR_PWM_PERIOD) / 6000) * (current / 4) ;
    } else if (current <= 6300){
        duty = (current * 40) + 640000;
    } else {
        duty =  ACP1000_CURR_PWM_PERIOD;
    }
    aw_pwm_config(curr_pwm_id, duty, ACP1000_CURR_PWM_PERIOD);
    aw_pwm_enable(curr_pwm_id);
}

/**
 * 交流母排检测任务
 */
static void ac_detect_work_entry (void *p_arg)
{
    charger_t *p_this = (charger_t *)p_arg;
    uint8_t    ac_enable;

    charger_dev_lock(p_this);
    ac_enable = p_this->dat.ac_enable;
    charger_dev_unlock(p_this);

//    if (aw_gpio_get(ACP1000_DIN_AC1)) {
//        if (ac_enable == TRUE) {
//            event_node_tell_all(&p_this->evt_node, ERR_AC, TRUE);
//            /* todo 发送AC接触器异常警报 */
//        } else {
//            event_node_tell_all(&p_this->evt_node, ERR_AC, FALSE);
//        }
//    } else {
//        if (ac_enable == FALSE) {
//            /* todo 发送AC接触器异常警报 */
//            event_node_tell_all(&p_this->evt_node, ERR_AC, TRUE);
//        } else {
//            event_node_tell_all(&p_this->evt_node, ERR_AC, FALSE);
//        }
//    }

    event_node_tell_all(&p_this->evt_node, CHARGE_AC_STATE, ac_enable);
    g_need_ac_check = TRUE;

}

/**
 *  \brief 充电模块实例初始化
 *  param [in]   p_this        : 充电模块实例
 *  */
void charger_inst_init(charger_t *p_this, pile_sem_t *p_pile_sem)
{
    static role_t charger_idle  = {charger_idle_do};  /* 可扮演的角色 - 充电空闲期 */
    p_this->player.pfn_play      = play;
    p_this->evt_node.pfunc_event = event_driver;
    p_this->p_charge_idle        = &charger_idle;
    p_this->p_charge_allow       = NULL;
    p_this->p_charge_start       = NULL;
    p_this->p_charge_ing         = NULL;
    p_this->p_charge_stop        = NULL;
    p_this->p_pile_sem           = p_pile_sem;

    AW_MUTEX_INIT(p_this->dev_lock, AW_SEM_Q_PRIORITY);
    AW_MUTEX_INIT(p_this->role_lock, AW_SEM_Q_PRIORITY);
    p_this->dat.ac_enable   = FALSE;
    p_this->dat.curr_pwm    = 7;
    p_this->dat.max_curr    = (ACP1000_PILE_MAX_CURR /  10);
    p_this->dat.tp1_vol     = 0;
    p_this->dat.start_ticks = 0;
#if ACP1000_AC1_ERR_DETECT
    aw_delayed_work_init(&(p_this->ac_detect_dk), ac_detect_work_entry, p_this);
#endif
}
/* ===============================扮演者与角色===================================  */
static role_ret play(role_t **pp_role, void *p_arg)  /* 扮演 */
{
    if ((*pp_role)->pfn_role_do) {
        return (*pp_role)->pfn_role_do(pp_role, p_arg);
    }
    return -AW_EINVAL;
}

/**
 * 充电空闲
 * p_arg : 传入的卡片ID
 */
static role_ret charger_idle_do (struct role **pp_role, void *p_arg)
{
    IDLE_TO_CHARGER(p_this, pp_role);
    uint8_t vol = (uint8_t)p_arg;
    static int cnt = 0; /* 插枪防抖计数 */

    /* 该状态肯定是不充电的 */
//    charger_ac_output_enable(p_this, FALSE);
    aw_gpio_set(ACP1000_DOUT_AC, 0);

    if ((6 == vol) || (9 == vol)) {
        cnt++;
        if (cnt > 20) {
            cnt = 0;
            /* 锁住电子锁 */
            charger_elock_lock(p_this, TRUE);

            /* 发起枪插上事件 */
            event_node_tell_all(&p_this->evt_node, GUN_INSERT, NULL);

            charger_dev_lock(p_this);

            if (p_this->dat.pile_alarm == 0) {
                p_this->dat.allow_charge = TRUE;
            } else {
                p_this->dat.allow_charge = FALSE;
            }
            charger_dev_unlock(p_this);

#if ACP1000_SKIP_AUTH
            event_node_tell_all(&p_this->evt_node, CHARGE_MAN_START, NULL);
#endif
        }
    } else {
       cnt = 0;
       /* 锁住电子锁 */
       charger_elock_lock(p_this, FALSE);
       /* 发起枪插上事件 */
       event_node_tell_all(&p_this->evt_node, GUN_EXTRACT, NULL);

       charger_dev_lock(p_this);
       p_this->dat.allow_charge = FALSE;
       charger_dev_unlock(p_this);
    }

    return AW_OK;
}

/**
 * 充电允许
 * 检测插枪，插枪完成发起插枪完成事件
 * p_arg : 传入的卡片ID
 */
static role_ret charger_allow_do (struct role **pp_role, void *p_arg)
{
    ALLOW_TO_CHARGER(p_this, pp_role);
    uint8_t vol = (uint8_t)p_arg;

    /* 该状态肯定是不充电的 */
//    charger_ac_output_enable(p_this, FALSE);
    aw_gpio_set(ACP1000_DOUT_AC, 0);

    /* 通知车辆充电机的最大输出电流 */
    if ((6 == vol) || (9 == vol)) {
        /* 锁住电子锁 */
        charger_elock_lock(p_this, TRUE);

        /* 发起枪插上事件 */
        event_node_tell_all(&p_this->evt_node, CHARGE_PIEL_WAIT, NULL);

        /* 通知车辆充电机的最大输出电流 */
        charger_current_limit(p_this, p_this->dat.max_curr);

        p_this->dat.start_ticks = aw_sys_tick_get();
    }
    return AW_OK;
}


/**
 * 充电启动
 * p_arg : 传入的卡片ID
 */
static role_ret charger_start_do (struct role **pp_role, void *p_arg)
{
    START_TO_CHARGER(p_this, pp_role);
    uint8_t vol = (uint8_t)p_arg;
    aw_tick_t   end_ticks;
    uint32_t    timeout_ms;

    if (vol != 6) {
//      charger_ac_output_enable(p_this, FALSE);
        aw_gpio_set(ACP1000_DOUT_AC, 0);
    }

    switch (vol) {

    case 6:
        /* 启动 */
        charger_ac_output_enable(p_this, TRUE);
        /* 充电准备就绪，发起机身开始充电事件 */
        event_node_tell_all(&p_this->evt_node, CHARGE_PIEL_START, NULL);
        p_this->dat.start_ticks  = 0;
        break;

    case 9:
        end_ticks = aw_sys_tick_get();
        timeout_ms = aw_ticks_to_ms(end_ticks - p_this->dat.start_ticks);
        if (timeout_ms > CHARGER_9V_TIMEOUT_MS) {
            charger_current_limit(p_this, 0); // todo add by anu
            /* 锁住电子锁 */
            charger_elock_lock(p_this, FALSE);
            /* 汽车充电就绪异常 */
            event_node_tell_all(&p_this->evt_node, ERR_CAR_READY, NULL);
            p_this->dat.start_ticks = aw_sys_tick_get();
        }
        break;

    case 12:
        /* 枪拔出，解锁 */
        charger_elock_lock(p_this, FALSE);
        event_node_tell_all(&p_this->evt_node, GUN_EXTRACT, NULL);
        event_node_tell_all(&p_this->evt_node, CHARGE_FULL, NULL);
        event_node_tell_all(&p_this->evt_node, CHARGE_PILE_STOP, NULL);

#if ACP1000_HUB4G_BILLING
        AW_SEMB_GIVE(p_this->p_pile_sem->charge_gun_sem);
#endif
        break;

    default:
        break;
    }

    return AW_OK;
}

/**
 * 充电中
 * p_arg : 传入的卡片ID
 */
static role_ret charger_ing_do (struct role **pp_role, void *p_arg)
{
    ING_TO_CHARGER(p_this, pp_role);
    uint8_t vol = (uint8_t)p_arg;
    aw_tick_t   end_ticks;
    uint32_t    timeout_ms;
    bool_t      exit_now;

    charger_dev_lock(p_this);
    exit_now = p_this->dat.exit_now;
    charger_dev_unlock(p_this);
    if (exit_now) {
        /* 紧急停止充电 */
        charger_ac_output_enable(p_this, FALSE);
        /* 充电准备就绪，发起机身开始充电事件 */
        event_node_tell_all(&p_this->evt_node, CHARGE_PILE_STOP, NULL);
        event_node_tell_all(&p_this->evt_node, ERR_CHAGER, p_this->dat.exit_code);
        charger_current_limit(p_this, 0);

        charger_dev_lock(p_this);
        p_this->dat.exit_now = FALSE;
        p_this->dat.start_ticks = aw_sys_tick_get();
        charger_dev_unlock(p_this);
        return AW_OK;
    }

    switch (vol) {

    case 6:
        /* 充电中 */
        if (!(p_this->dat.ac_enable)) {
            charger_ac_output_enable(p_this, TRUE);
        }
        break;

    case 9:
        /* 关闭AC输出，但仍输出脉冲 */
        charger_ac_output_enable(p_this, FALSE);

        /* 异常一时关闭充电 ，检测超时 */
        if ( 0 == p_this->dat.start_ticks) {
            p_this->dat.start_ticks = aw_sys_tick_get();
        }

        /* 超时认为汽车充满 */
        end_ticks = aw_sys_tick_get();
        timeout_ms = aw_ticks_to_ms(end_ticks - p_this->dat.start_ticks);
        if (timeout_ms > CHARGER_UNLOCK_TIMEOUT_MS) {
            /* 锁住电子锁 */
            charger_elock_lock(p_this, FALSE);
            event_node_tell_all(&p_this->evt_node, CHARGE_PILE_STOP, NULL);
            /* 汽车充电就绪异常 */
            event_node_tell_all(&p_this->evt_node, CHARGE_FULL, NULL);
            charger_current_limit(p_this, 0);
            p_this->dat.start_ticks = aw_sys_tick_get();
        }
        break;

    case 12:
    default:
        /* 汽车已经充满 */
        charger_ac_output_enable(p_this, FALSE);
        /* 充电准备就绪，发起机身开始充电事件 */
        event_node_tell_all(&p_this->evt_node, CHARGE_FULL, NULL);
        event_node_tell_all(&p_this->evt_node, CHARGE_PILE_STOP, NULL);
        charger_current_limit(p_this, 0);
        p_this->dat.start_ticks = aw_sys_tick_get();
        break;
    }

    return AW_OK;
}

/**
 * 异常充电停止
 * p_arg : 传入的卡片ID
 */
static role_ret charger_err_do (struct role **pp_role, void *p_arg)
{

    ERR_TO_CHARGER(p_this, pp_role);
    uint8_t vol = (uint8_t)p_arg;
    aw_tick_t   end_ticks;
    uint32_t    timeout_ms;
    static  uint32_t state = 0;

    switch (state) {

    case 0:
        state = 1;
        p_this->dat.start_ticks = aw_sys_tick_get();
        charger_current_limit(p_this, 0);
        break;

    case 1:
        if (vol == 6) {
           /* 异常时汽车未作出反应 ，强制关闭 */
           end_ticks = aw_sys_tick_get();
           timeout_ms = aw_ticks_to_ms(end_ticks - p_this->dat.start_ticks);
           if (timeout_ms > CHARGER_ERR_TIMEOUT_MS) {
               /* 关闭电源  */
               charger_ac_output_enable(p_this, FALSE);
               /* 发起枪拔出事件 */
               event_node_tell_all(&p_this->evt_node, CHARGE_PILE_STOP, NULL);
               event_node_tell_all(&p_this->evt_node, ERR_CHAGER, p_this->dat.exit_code);
               p_this->dat.start_ticks = aw_sys_tick_get();
               state = 0;
               return AW_OK;
           }
        }
        break;
    }

    if (vol != 6) {
        /* 关闭电源  */
        charger_ac_output_enable(p_this, FALSE);
        event_node_tell_all(&p_this->evt_node, CHARGE_PILE_STOP, NULL);
        event_node_tell_all(&p_this->evt_node, ERR_CHAGER, p_this->dat.exit_code);
        p_this->dat.start_ticks = aw_sys_tick_get();
        state = 0;
    }
    return AW_OK;
}

/**
 * 停止充电
 */
static role_ret charger_stop_do (struct role **pp_role, void *p_arg)
{

    STOP_TO_CHARGER(p_this, pp_role);
    uint8_t vol = (uint8_t)p_arg;
    aw_tick_t   end_ticks;
    uint32_t    timeout_ms;

    /* 该状态肯定是不充电的 */
//    charger_ac_output_enable(p_this, FALSE);
    aw_gpio_set(ACP1000_DOUT_AC, 0);

    switch (vol) {

    case 6:
        /* 充电中 */
        break;

    case 9:
        break;

    case 12:
        charger_current_limit(p_this, 0); // todo add by anu
        /* 超时认为汽车充满 */
       end_ticks = aw_sys_tick_get();
       timeout_ms = aw_ticks_to_ms(end_ticks - p_this->dat.start_ticks);
       if (timeout_ms > CHARGER_UNLOCK_TIMEOUT_MS) {
           /* 解除电子锁 */
           charger_elock_lock(p_this, FALSE);
           /* 发起枪拔出事件 */
           event_node_tell_all(&p_this->evt_node, GUN_EXTRACT, NULL);
#if ACP1000_HUB4G_BILLING
           AW_SEMB_GIVE(p_this->p_pile_sem->charge_gun_sem);
#endif
       }
       break;

    default:
        break;
    }

    return AW_OK;
}



/*=============================事件驱动==========================================*/
void static event_driver(struct event_node *p_evt, event_t event, void *p_arg)
{
    EVT_TO_CHARGER(p_this, p_evt);
    static role_t charger_idle  = {charger_idle_do};  /* 可扮演的角色 - 充电空闲期 */
    static role_t charger_allow = {charger_allow_do}; /* 可扮演的角色  - 允许充电裁定器 */
    static role_t charger_start = {charger_start_do}; /* 可扮演的角色  - 启动充电裁定器 */
    static role_t charger_ing   = {charger_ing_do};   /* 可扮演的角色  - 启动中控制器 */
    static role_t charger_stop  = {charger_stop_do};  /* 可扮演的角色  - 充电停止控制器 */
    static role_t charger_err   = {charger_err_do};   /* 可扮演的角色  - 充电异常控制器 */

    uint32_t arg = (uint32_t)p_arg;
    bool_t   allow_charge;
    uint32_t stop_reason = AW_MB_DGUS_CHARGE_NONE;

    switch (event) {
//    case CARD_AUTH_SUS:
    case CHARGE_MAN_START:
        charger_dev_lock(p_this);
        allow_charge = p_this->dat.allow_charge;
        charger_dev_unlock(p_this);

        /* 人为开始充电 */
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        if ((p_this->p_charge_idle == NULL) ||
             (allow_charge != TRUE)) {
            /* 不在空闲中，不允许人为启动充电 */
            AW_MUTEX_UNLOCK(p_this->role_lock);
            return;
        }
        p_this->p_charge_idle  = NULL;
        p_this->p_charge_allow = &charger_allow;
        p_this->p_charge_start = NULL;
        p_this->p_charge_ing   = NULL;
        p_this->p_charge_stop  = NULL;
        p_this->p_charge_err   = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CHARGE_PIEL_START:
        /* 充电开始 */
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_charge_idle  = NULL;
        p_this->p_charge_allow = NULL;
        p_this->p_charge_start = NULL;
        p_this->p_charge_ing   = &charger_ing;
        p_this->p_charge_stop  = NULL;
        p_this->p_charge_err   = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CARD_AUTH_FAIL:
    case CHARGE_PILE_STOP:
    case ERR_CAR_READY:
    case ERR_CHAGER:
        /* 充电结束 */
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_charge_idle  = NULL;
        p_this->p_charge_allow = NULL;
        p_this->p_charge_start = NULL;
        p_this->p_charge_ing   = NULL;
        p_this->p_charge_err   = NULL;
        p_this->p_charge_stop  = &charger_stop;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        charger_dev_lock(p_this);
        p_this->dat.allow_charge = FALSE;
        charger_dev_unlock(p_this);
        break;

    case CHARGE_PIEL_WAIT:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_charge_idle  = NULL;
        p_this->p_charge_allow = NULL;
        p_this->p_charge_start = &charger_start;
        p_this->p_charge_ing   = NULL;
        p_this->p_charge_stop  = NULL;
        p_this->p_charge_err   = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case GUN_EXTRACT:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_charge_idle  = &charger_idle;
        p_this->p_charge_allow = NULL;
        p_this->p_charge_start = NULL;
        p_this->p_charge_ing   = NULL;
        p_this->p_charge_stop  = NULL;
        p_this->p_charge_err   = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CHARGE_BG_STOP:  /* 后台终止充电 */
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        if (p_this->p_charge_ing == NULL) {
            /* 不在充电中，无作用 */
            AW_MUTEX_UNLOCK(p_this->role_lock);
            return;
        }
        p_this->p_charge_idle  = NULL;
        p_this->p_charge_allow = NULL;
        p_this->p_charge_start = NULL;
        p_this->p_charge_ing   = NULL;
        p_this->p_charge_stop  = NULL;
        p_this->p_charge_err   = &charger_err;
        p_this->dat.exit_code  = AW_MB_DGUS_CHARGE_BG_EXIT;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CHARGE_MAN_STOP:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        if (p_this->p_charge_ing == NULL) {
            /* 不在充电中，无作用 */
            AW_MUTEX_UNLOCK(p_this->role_lock);
            return;
        }
        p_this->p_charge_idle  = NULL;
        p_this->p_charge_allow = NULL;
        p_this->p_charge_start = NULL;
        p_this->p_charge_ing   = NULL;
        p_this->p_charge_stop  = NULL;
        p_this->p_charge_err   = &charger_err;
        p_this->dat.exit_code  = AW_MB_DGUS_CHARGE_MAN_EXIT;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case ERR_AMMETER:
    case ERR_CARD_READER:
    case ERR_LIGHT:
    case ERR_AC:
    case ERR_TEMP:
    case ERR_DUGS:
    case ERR_HUB4G_COMM:
        if (arg == 0) {
            /* 读卡器或者电表正常，退出，否则进入异常处理角色  */
            return;
        }
        if (ERR_AMMETER == event) {
            stop_reason = AW_MB_DGUS_CHARGE_AMETETER;
        } else if (ERR_CARD_READER == event) {
            stop_reason = AW_MB_DGUS_CHARGE_CARDREADER;
        } else if (ERR_LIGHT == event) {
            stop_reason = AW_MB_DGUS_CHARGE_LIGHT;
        } else if (ERR_AC == event) {
            stop_reason = AW_MB_DGUS_CHARGE_AC;
        } else if (ERR_TEMP == event) {
            stop_reason = AW_MB_DGUS_CHARGE_TEMP;
        }
        p_arg = (void *)stop_reason;
//        p_arg = (void *)AW_MB_DGUS_CHARGE_ERR_EXIT;

    case BILLING_STOP:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        if (p_this->p_charge_ing == NULL) {
            /* 不在充电中，无作用 */
            AW_MUTEX_UNLOCK(p_this->role_lock);
            return;
        }
        p_this->p_charge_idle  = NULL;
        p_this->p_charge_allow = NULL;
        p_this->p_charge_start = NULL;
        p_this->p_charge_ing   = NULL;
        p_this->p_charge_stop  = NULL;
        p_this->p_charge_err   = &charger_err;
        p_this->dat.exit_code  = (uint32_t)p_arg;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case ERR_AMMETER_CURR:
    case ERR_AMMETER_VOL:
    case ERR_SCRAM:
        if (arg != 0) {
            if (ERR_AMMETER_CURR == event) {
                stop_reason = AW_MB_DGUS_CHARGE_CURR;
            } else if (ERR_AMMETER_VOL == event) {
                if (arg == 1) {
                    stop_reason = AW_MB_DGUS_CHARGE_UNDERVOL;
                } else {
                    stop_reason = AW_MB_DGUS_CHARGE_OVERVOL;
                }
            } else if (ERR_SCRAM == event) {
                stop_reason = AW_MB_DGUS_CHARGE_SCRAM;
            }
            /* 异常 ，同步断开电源 */
//            p_this->dat.exit_code = AW_MB_DGUS_CHARGE_ERR_EXIT;
            p_this->dat.exit_code = stop_reason;
            charger_dev_lock(p_this);
            p_this->dat.exit_now  = TRUE;
            charger_dev_unlock(p_this);
        }
        break;

    case PILE_ALARM: /* 保存告警情况 */
         charger_dev_lock(p_this);
         p_this->dat.pile_alarm  = arg;
         charger_dev_unlock(p_this);
         break;

    default: break;
    }
}
/* ========================================================================= */
#define CHARGER_TASK_PRIO       2
#define CHARGER_TACK_SIZE       4096
#define CHARGER_DETECT_PERIOD   30
AW_TASK_DECL_STATIC(charger_task, CHARGER_TACK_SIZE);

/**
 * 卡探测任务
 */
static void charger_task_entry (void *p_arg)
{
    charger_t *p_this = (charger_t *)p_arg;
    uint8_t    vol    = 0;
    role_t     *p_role[6];

    while (1) {
        charger_dev_lock(p_this);
        vol = p_this->dat.tp1_vol;
        charger_dev_unlock(p_this);

        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        memcpy(&p_role[0], &p_this->p_charge_idle, sizeof(role_t*) * 6);
        AW_MUTEX_UNLOCK(p_this->role_lock);

        if (NULL != p_role[0]) {
            p_this->player.pfn_play(&p_this->p_charge_idle, (void *)vol);

        } else if (NULL != p_role[1]) {
            p_this->player.pfn_play(&p_this->p_charge_allow, (void *)vol);

        } else if (NULL != p_role[2]) {
            p_this->player.pfn_play(&p_this->p_charge_start, (void *)vol);

        } else if (NULL != p_role[3]) {
            p_this->player.pfn_play(&p_this->p_charge_ing, (void *)vol);

        } else if (NULL != p_role[4]) {
            p_this->player.pfn_play(&p_this->p_charge_stop, (void *)vol);

        }  else if (NULL != p_role[5]) {
            p_this->player.pfn_play(&p_this->p_charge_err, (void *)vol);
        }


        aw_mdelay(CHARGER_DETECT_PERIOD);
    }
}

void charger_task_startup (charger_t *p_this)
{
    AW_TASK_INIT(charger_task,           /* 任务实体 */
                 "charger_task",            /* 任务名字 */
                 CHARGER_TASK_PRIO,      /* 任务优先级 */
                 CHARGER_TACK_SIZE,      /* 任务堆栈大小 */
                 charger_task_entry,     /* 任务入口函数 */
                 (void *)p_this);        /* 任务入口参数 */
    /* 启动任务 */
    AW_TASK_STARTUP(charger_task);
}
