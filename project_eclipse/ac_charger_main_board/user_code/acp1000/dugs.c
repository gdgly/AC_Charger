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
 * \brief 串口屏实例
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#include "apollo.h"
#include "card_reader.h"
#include "event_node.h"
#include "role.h"
#include "aw_task.h"
#include "string.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "mb/aw_mb_dgus_regmap.h"
#include "mb/ac_modbus_reg_map.h"
#include "dugs.h"
#include "billing.h"
#include "ac_charge_prj_cfg.h"
#include "aw_delayed_work.h"
#include "modbus/aw_mb_utils.h"
#include "aw_nvram.h"

#define BILLING_TO_DUGS(p_this, p_role) \
    struct dugs *p_this = AW_CONTAINER_OF(p_role, struct dugs, p_dugs_billing_ctrl)

#define CHARGER_TO_DUGS(p_this, p_role) \
    struct dugs *p_this = AW_CONTAINER_OF(p_role, struct dugs, p_dugs_charge_ctrl)

#define SETTINGS_TO_DUGS(p_this, p_role) \
    struct dugs *p_this = AW_CONTAINER_OF(p_role, struct dugs, p_dugs_settings)


#define EVT_TO_DUGS(p_this, p_evt) \
    struct dugs *p_this = AW_CONTAINER_OF(p_evt, struct dugs, evt_node)


static role_ret play(role_t **pp_role, void *p_arg);  /* 扮演 */
static void event_driver(struct event_node *p_evt, event_t event, void *p_arg);


/**
 * 鉴权失败
 */
void card_fail (dugs_t *p_this)
{
    dugs_lock(p_this);
    p_this->super.rd_reg.card_stat  = AW_MB_DGUS_CARD_STAT_INVALID;
    dugs_unlock(p_this);
}


/**
 * 鉴权成功
 */
void auth_sus (dugs_t *p_this)
{
#if ACP1000_OVERTIME_DETECT
    acp1000_overtime_check_restart();
#endif

    dugs_lock(p_this);
    p_this->super.rd_reg.card_stat    = AW_MB_DGUS_CARD_STAT_SUCCESS;
    p_this->super.rd_reg.card_cnt    += 1;
    p_this->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_ENOUGH;
    p_this->super.rd_reg.stop_reason  = AW_MB_DGUS_CHARGE_NONE;
    p_this->super.rd_reg.used_energy  = 0;
    p_this->super.rd_reg.used_time    = 0;
    p_this->super.rd_reg.used_amount  = 0;
    dugs_unlock(p_this);
//    acp1000_buzzer_on();/* 响蜂鸣器 */
}

/* 多次刷卡事件 (解锁屏幕)*/
void unlock_sus (dugs_t *p_this)
{
    dugs_lock(p_this);
    p_this->super.rd_reg.card_cnt    += 1;
    p_this->super.rd_reg.card_stat    = AW_MB_DGUS_CARD_STAT_SUCCESS;
    p_this->super.rd_reg.stop_reason  = AW_MB_DGUS_CHARGE_NONE;
    dugs_unlock(p_this);

#if ACP1000_OVERTIME_DETECT
    acp1000_overtime_check_restart();
#endif
}


/**
 * 充电控制回调函数
 */
aw_local int dugs_charge_ctrl_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this        = (dugs_t *)p_arg;
    role_t *p_role_charge = NULL;
    /* */
    AW_MUTEX_LOCK(p_this->role_lock,AW_SEM_WAIT_FOREVER);
    p_role_charge = p_this->p_dugs_charge_ctrl;
    AW_MUTEX_UNLOCK(p_this->role_lock);

    if (NULL != p_role_charge) {
        p_this->player.pfn_play(&p_this->p_dugs_charge_ctrl, val);
    }

    return AW_OK;
}

/**
 * 清除卡状态
 */
aw_local int dugs_card_state_clr_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this        = (dugs_t *)p_arg;

//    dugs_lock(p_this);
//    p_this->super.rd_reg.card_stat  = AW_MB_DGUS_CARD_STAT_IDLE;
//    dugs_unlock(p_this);

    return AW_OK;
}

/**
 * 清除余额不足状态
 */
aw_local int dugs_amount_state_clr_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this        = (dugs_t *)p_arg;

    dugs_lock(p_this);
    p_this->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_ENOUGH;
    dugs_unlock(p_this);

    return AW_OK;
}

/**
 * 设置充电金恩
 */
aw_local int dugs_charge_amount_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this  = (dugs_t *)p_arg;
    uint32_t usr_balance = 0; /* 单位0.1元 */

    /* 比较当前余额是否超过设置的金额 */
    dugs_lock(p_this);
    usr_balance = (p_this->super.rd_reg.usr_balance[0]) << 16 |
                   p_this->super.rd_reg.usr_balance[1] ;
    dugs_unlock(p_this);

    if (val > usr_balance) {
        dugs_lock(p_this);
        p_this->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_NOT_ENOUGH;
        dugs_unlock(p_this);
    } else {
        dugs_lock(p_this);
        p_this->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_ENOUGH;
        dugs_unlock(p_this);
    }

    return AW_OK;
}

/**
 * 设置充电电量
 */
aw_local int dugs_charge_energy_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this  = (dugs_t *)p_arg;
    uint32_t usr_balance   = 0; /* 单位0.1元 */
    uint32_t charge_amount = 0; /* 单位0.1元 */
    uint32_t price         = 0; /* 单位0.0001元每度 */
    /* 比较当前余额是否超过设置的金额 */
    dugs_lock(p_this);
    usr_balance = (p_this->super.rd_reg.usr_balance[0]) << 16 |
                   p_this->super.rd_reg.usr_balance[1] ;
    dugs_unlock(p_this);

    event_node_tell_all(&p_this->evt_node, DUGS_PRICE_GET, (void *)&price);

    charge_amount = (val * price) / 10000;

    if (charge_amount > usr_balance) {
        dugs_lock(p_this);
        p_this->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_NOT_ENOUGH;
        dugs_unlock(p_this);
    } else {
        dugs_lock(p_this);
        p_this->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_ENOUGH;
        dugs_unlock(p_this);
    }

    return AW_OK;
}


/**
 * 清除卡状态
 */
aw_local int dugs_charge_way_ctrl_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this        = (dugs_t *)p_arg;
    return AW_OK;
}


static struct aw_delayed_work g_dugs_comm_work; /* 串口屏通信异常延时处理工作  */
static bool_t g_comm_err_state = FALSE;         /* 串口屏异常情况 */

/**
 * 串口屏通信异常处理
 */
static void dugs_comm_dly_work (void *p_arg)
{
    dugs_t *p_this        = (dugs_t *)p_arg;

    event_node_tell_all(&p_this->evt_node, ERR_DUGS, TRUE);
    g_comm_err_state = TRUE;
}

/**
 * 串口屏通信正常回调
 */
aw_local int dugs_comm_state_action (void *p_arg, uint16_t val)
{
#if ACP1000_DUGS_ERR_DETECT
    dugs_t *p_this        = (dugs_t *)p_arg;

    aw_delayed_work_stop(&g_dugs_comm_work);
    aw_delayed_work_start(&g_dugs_comm_work, ACP1000_DUGS_ERR_TIMEOUT);
    if (g_comm_err_state) {
        event_node_tell_all(&p_this->evt_node, ERR_DUGS, FALSE);
        g_comm_err_state = FALSE;
    }
#endif
    return AW_OK;
}

/**
 * 退出账号命令
 */
aw_local int dugs_accout_exit_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this        = (dugs_t *)p_arg;

    return AW_OK;
}

/**
 * 退出管理员模式
 */
aw_local int dugs_admin_exit_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this        = (dugs_t *)p_arg;
    dugs_lock(p_this);
    p_this->super.rd_reg.admin_flag = 0xAA;
    dugs_unlock(p_this);
    return AW_OK;
}

/**
 * 设置于集中器通信地址
 */
aw_local int dugs_hub4g_addr_action (void *p_arg, uint16_t val)
{
    dugs_t *p_this        = (dugs_t *)p_arg;
    dugs_lock(p_this);
    p_this->super.rd_reg.hub4g_addr = val;
    dugs_unlock(p_this);
    event_node_tell_all(&p_this->evt_node, DUGS_HUB4G_ADDR, (void *)((uint8_t)val));
    return AW_OK;
}
/**
 * 设置桩ID
 */
aw_local void dugs_pile_id_set (dugs_t *p_this, void *p_arg)
{
    int i = 0;
    uint16_t *p_dat = (uint16_t *)p_arg;
    uint8_t  buf[18];
    uint8_t *p_pile_id = p_this->super.rd_reg.pile_id;

    if (NULL == p_arg) {
        return ;
    }

    sprintf((void *)buf, "%04X%04X%04X%04X", p_dat[0], p_dat[1], p_dat[2], p_dat[3]);
    aw_mb_regcpy(p_pile_id, buf, 8);
}
/**
 *  \brief 串口屏初始化
 *  param [in]   p_this        : 串口屏实例
 *  param [in]   p_dgus_info   : dugs串口屏配置信息
 *  */
void dugs_inst_init(dugs_t *p_this, modbus_info_t *p_dugs_info)
{
    uint16_t pile_id[4];

    p_this->player.pfn_play = play;
    p_this->evt_node.pfunc_event = event_driver;
    AW_MUTEX_INIT(p_this->role_lock, AW_SEM_Q_PRIORITY);
    p_this->p_dugs_billing_ctrl = NULL;
    p_this->p_dugs_charge_ctrl  = NULL;
    p_this->p_dugs_settings     = NULL;
    p_this->p_dugs_display      = NULL;

    aw_mb_dgus_reg_map_init(&p_this->super);

    p_this->super.rd_reg.gun_stat = AW_MB_DGUS_GUN_IDLE;
    p_this->super.rd_reg.upgrade_flag =  AW_MB_DGUS_UPGRADE_IDLE;

    /* 注册控制回调函数 */
    aw_mb_dgus_func_cb_register (&(p_this->super),
                                 FUNC_CHARGE_CTRL,
                                 dugs_charge_ctrl_action,
                                 (void *)p_this);
    /* 注册控制回调函数 */
    aw_mb_dgus_func_cb_register (&(p_this->super),
                                 FUNC_CHARGE_WAY,
                                 dugs_charge_way_ctrl_action,
                                 (void *)p_this);

    /* 注册控制回调函数 */
    aw_mb_dgus_func_cb_register (&(p_this->super),
                               FUNC_CARD_STATE_CLR,
                               dugs_card_state_clr_action,
                              (void *)p_this);

    /* 注册控制回调函数 */
    aw_mb_dgus_func_cb_register (&(p_this->super),
                                FUNC_CHARGE_AMOUNT,
                                dugs_charge_amount_action,
                               (void *)p_this);
    /* 注册控制回调函数 */
    aw_mb_dgus_func_cb_register (&(p_this->super),
                                 FUNC_CHARGE_ENERGY,
                                 dugs_charge_energy_action,
                                (void *)p_this);

    /* 注册控制回调函数 */
    aw_mb_dgus_func_cb_register (&(p_this->super),
                                  FUNC_AMOUNT_STATE_CLR,
                                  dugs_amount_state_clr_action,
                                 (void *)p_this);

    /* 注册控制回调函数 */
    aw_mb_dgus_func_cb_register (&(p_this->super),
                                 FUNC_DUGS_COMM_STATE,
                                 dugs_comm_state_action,
                                 (void *)p_this);

    aw_mb_dgus_func_cb_register (&(p_this->super),
                                 FUNC_ACCOUT_EXIT_CMD,
                                 dugs_accout_exit_action,
                                 (void *)p_this);

    aw_mb_dgus_func_cb_register (&(p_this->super),
                                 FUNC_ADMIN_EXIT_CMD,
                                 dugs_admin_exit_action,
                                 (void *)p_this);

    aw_mb_dgus_func_cb_register (&(p_this->super),
                                  FUNC_HUB4G_ADDR_CMD,
                                  dugs_hub4g_addr_action,
                                 (void *)p_this);

    /* 初始化dgus modbus slave*/
    aw_mb_dgus_slave_hdl_init (&p_this->super,
                                p_dugs_info->addr,
                                p_dugs_info->com,
                                p_dugs_info->baud,
                                p_dugs_info->par);

#if ACP1000_EEPROM_PILE_ID_GET
    if(AW_OK == aw_nvram_get(ACP1000_EEPROM_NAME, 1, (char *)pile_id, 0, 8)) {
        dugs_lock(p_this);
        dugs_pile_id_set(p_this, pile_id);
        dugs_unlock(p_this);
    }
#endif

#if ACP1000_DUGS_ERR_DETECT
    aw_delayed_work_init(&g_dugs_comm_work,
                          dugs_comm_dly_work,
                          p_this);
    aw_delayed_work_start(&g_dugs_comm_work, ACP1000_DUGS_ERR_TIMEOUT);
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
 * 计费模式设计
 * p_arg : 传入的卡片ID
 */
static role_ret dugs_billing_do (struct role **pp_role, void *p_arg)
{
    return AW_OK;
}

/**
 * 充电角色控制
 * p_arg : 传入的卡片ID
 */
static role_ret dugs_charger_do (struct role **pp_role, void *p_arg)
{
    CHARGER_TO_DUGS(p_this, pp_role);
    uint32_t ctrl = (uint32_t )p_arg;

    if (AW_MB_DGUS_CHARGE_CTRL_START == ctrl) {
        /* 人为开始充电 */
        dugs_lock(p_this);
        p_this->super.rd_reg.stop_reason = AW_MB_DGUS_CHARGE_NONE;
        dugs_unlock(p_this);
        event_node_tell_all(&p_this->evt_node, CHARGE_MAN_START, NULL);
    } else {
        /* 人为退出充电 */
        event_node_tell_all(&p_this->evt_node, CHARGE_MAN_STOP, NULL);
    }
    return AW_OK;
}


/**
 * 充电角色控制
 * p_arg : 传入的卡片ID
 */
static role_ret dugs_settings_do (struct role **pp_role, void *p_arg)
{

    return AW_OK;
}


/*=============================事件驱动==========================================*/
void static event_driver(struct event_node *p_evt, event_t event, void *p_arg)
{
    EVT_TO_DUGS(p_this, p_evt);
    static role_t dugs_billing = {dugs_billing_do};
    static role_t dugs_charger = {dugs_charger_do};
    static role_t dugs_setting = {dugs_settings_do};

    uint32_t arg  = (uint32_t)p_arg;
    uint32_t balance;
    billing_dat_t  *p_billing_dat = NULL;
    billing_mode_t *p_billing_mod = NULL;
    pile_dat_t     *p_pile_dat    = NULL;

    struct aw_charging_usr_info      *p_usr_info = NULL;
    struct aw_remote_adjust_usr_ctrl *p_usr_ctrl = NULL;

    switch (event) {

    case CARD_AUTH_SUS:
        /* 鉴权成功 */
        AW_MUTEX_LOCK(p_this->role_lock,AW_SEM_WAIT_FOREVER);
        p_this->p_dugs_billing_ctrl = &dugs_billing;
        p_this->p_dugs_settings     = &dugs_setting;
        p_this->p_dugs_charge_ctrl  = &dugs_charger;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        auth_sus(p_this);
        break;

    case CHARGE_MAN_START:
    case CHARGE_PIEL_START:
        /* 充电开始 */
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_dugs_billing_ctrl = NULL;
        p_this->p_dugs_settings     = NULL;
        p_this->p_dugs_charge_ctrl  =  &dugs_charger;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        dugs_lock(p_this);
        p_this->super.rd_reg.stop_reason = AW_MB_DGUS_CHARGE_NONE;
        p_this->stop_reason              = AW_MB_DGUS_CHARGE_NONE;
        p_this->super.rd_reg.work_stat   = AW_MB_DGUS_WORK_STAT_BUSY;
        dugs_unlock(p_this);
        break;

    case CARD_AUTH_FAIL:
    case CHARGE_PILE_STOP:
        /* 充电开始 */
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_dugs_billing_ctrl = NULL;
        p_this->p_dugs_settings     = NULL;
        p_this->p_dugs_charge_ctrl  = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        dugs_lock(p_this);
        if (event == CARD_AUTH_FAIL) {
            p_this->super.rd_reg.work_stat = AW_MB_DGUS_WORK_STAT_IDLE;
        } else {
            p_this->super.rd_reg.work_stat = AW_MB_DGUS_WORK_STAT_FINISH;
        }
        dugs_unlock(p_this);
        /* */
        card_fail(p_this);
        break;

    /* ----------------------------------------------------------  */
    case CARD_AUTH_ING:
        dugs_lock(p_this);
        p_this->super.rd_reg.card_stat = AW_MB_DGUS_CARD_STAT_AUTH;
        dugs_unlock(p_this);
        break;

    case SCREEN_UNLOCK:
        unlock_sus(p_this);
        break;

    case GUN_INSERT:
        dugs_lock(p_this);
        p_this->super.rd_reg.gun_stat = AW_MB_DGUS_GUN_VALID;
        dugs_unlock(p_this);
        break;

    case GUN_EXTRACT:
        dugs_lock(p_this);
        p_this->super.rd_reg.gun_stat  = AW_MB_DGUS_GUN_IDLE;
        dugs_unlock(p_this);

        break;

    case CHARGE_FULL:
        dugs_lock(p_this);
        p_this->stop_reason = AW_MB_DGUS_CHARGE_FULL;
        dugs_unlock(p_this);
        break;

    case ERR_CAR_READY:
        dugs_lock(p_this);
        p_this->stop_reason = AW_MB_DGUS_CHARGE_ERR_EXIT;
        dugs_unlock(p_this);
        break;

    case ERR_CHAGER:
        /* 异常退出充电 */
        dugs_lock(p_this);
        if (arg == AW_MB_DGUS_CHARGE_BG_EXIT) {
            p_this->stop_reason = AW_MB_DGUS_CHARGE_MAN_EXIT;
        } else {
            if (arg >= AW_MB_DGUS_CHARGE_CARDREADER) {
                p_this->stop_reason = AW_MB_DGUS_CHARGE_ERR_EXIT;
            } else {
                p_this->stop_reason = arg;
            }
        }
        dugs_unlock(p_this);
        break;

    case BILLING_ENDING:
        dugs_lock(p_this);
        p_this->super.rd_reg.stop_reason = p_this->stop_reason;
        dugs_unlock(p_this);
        break;


    case BILLING_END:
        dugs_lock(p_this);
        if (arg) {
            /* 结算成功 */
            p_this->super.rd_reg.stop_reason = p_this->stop_reason;
        } else {
            /* 结算失败*/
            p_this->super.rd_reg.stop_reason = AW_MB_DGUS_CHARGE_ERR_BILLING;
        }
        p_this->super.rd_reg.work_stat = AW_MB_DGUS_WORK_STAT_IDLE;
        p_this->super.rd_reg.card_stat = AW_MB_DGUS_CARD_STAT_IDLE;
        dugs_unlock(p_this);
        break;

    case BILLING_ING: /* 计费中 */
        p_billing_dat = (billing_t  *)p_arg;
        dugs_lock(p_this);
        p_this->super.rd_reg.used_energy = p_billing_dat->used_energy / 10;
        p_this->super.rd_reg.used_time   = p_billing_dat->used_time;
        p_this->super.rd_reg.used_amount = p_billing_dat->used_amount / 10;
        balance = (p_billing_dat->usr_balance - p_billing_dat->used_amount) / 10;
        p_this->super.rd_reg.usr_balance[0] = ((balance & 0xFFFF0000) >> 16 );
        p_this->super.rd_reg.usr_balance[1] = ((balance & 0xFFFF) >> 0 );
        dugs_unlock(p_this);
        break;

    case BILLING_MODE_GET:
        p_billing_mod = (billing_mode_t  *)p_arg;
        dugs_lock(p_this);
        p_billing_mod->mode          =  p_this->super.wr_reg.charge_way;
        p_billing_mod->charge_amount =  p_this->super.wr_reg.charge_amount * 10;
        p_billing_mod->charge_time   =  p_this->super.wr_reg.charge_time;
        p_billing_mod->charge_energy =  p_this->super.wr_reg.charge_energy * 10;
        memcpy(p_billing_mod->usr_id, p_this->super.rd_reg.usr_id, 16);
//        p_billing_mod->charge_time   = 1;
//        p_billing_mod->charge_energy =  10;
//        p_billing_mod->charge_amount =  10;
//        p_billing_mod->usr_balance   =  10000; /* todo 从集中器获取余额 */
        dugs_unlock(p_this);
        break;

    case PILE_ALARM:
        if (arg) {
            dugs_lock(p_this);
            p_this->super.rd_reg.pile_stat = AW_MB_DGUS_PILE_STAT_ABNORMAL;
            dugs_unlock(p_this);
        } else {
            dugs_lock(p_this);
            p_this->super.rd_reg.pile_stat = AW_MB_DGUS_PILE_STAT_NORMAL;
            dugs_unlock(p_this);
        }
        break;

    case HUB4G_PILE_ORDER:
        if (arg) {
            dugs_lock(p_this);
            p_this->super.rd_reg.pile_order = AW_MB_DGUS_PILE_IS_ORDERED;
            dugs_unlock(p_this);
        } else {
            dugs_lock(p_this);
            p_this->super.rd_reg.pile_order = AW_MB_DGUS_PILE_IS_NOT_ORDERED;
            dugs_unlock(p_this);
        }
        break;

    case HUB4G_USR_INFO:
        p_usr_info = (struct aw_charging_usr_info *)p_arg;
        dugs_lock(p_this);
        memcpy((uint8_t *)(p_this->super.rd_reg.usr_id), (uint8_t *)(p_usr_info->user_id), 16);
        balance = (p_usr_info->user_balance[0] << 16) | p_usr_info->user_balance[1];
        balance /= 10;
        p_this->super.rd_reg.usr_balance[0] = (balance & 0xFFFF0000 ) >> 16;
        p_this->super.rd_reg.usr_balance[1] = (balance & 0xFFFF )     >> 0;
        dugs_unlock(p_this);
        break;

    case BILLING_BALANCE:
        if (!arg) {
            dugs_lock(p_this);
            p_this->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_NOT_ENOUGH;
            dugs_unlock(p_this);
        } else {
            dugs_lock(p_this);
            p_this->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_ENOUGH;
            dugs_unlock(p_this);
        }
        break;

    case CARD_AUTH_SUS_ORDER:
        dugs_lock(p_this);
        p_this->super.rd_reg.card_stat    = AW_MB_DGUS_CARD_STAT_SUCCESS;
        p_this->super.rd_reg.card_cnt    += 1;
        dugs_unlock(p_this);
        break;

    case HUB4G_UPGRADE:
        dugs_lock(p_this);
        p_this->super.rd_reg.upgrade_flag = AW_MB_DGUS_UPGRADE_BUSY;
        dugs_unlock(p_this);
        break;

    case PILE_DUGS_INFO:
        p_pile_dat = (pile_dat_t *)p_arg;
        dugs_lock(p_this);
        p_this->super.rd_reg.pile_temp  = p_pile_dat->temp * 10;
        p_this->super.rd_reg.input_vol  = p_pile_dat->input_vol;
        p_this->super.rd_reg.input_curr = p_pile_dat->input_curr;
        p_this->super.rd_reg.run_time   = p_pile_dat->run_time;
        p_this->super.rd_reg.err_cnt    = p_pile_dat->err_cnt;
        p_this->super.rd_reg.charge_cnt = p_pile_dat->charge_cnt;
        p_this->super.rd_reg.hub4g_addr = p_pile_dat->hub4g_addr;
        p_this->super.rd_reg.bg_state   = p_pile_dat->bg_state;
        dugs_unlock(p_this);
        break;

    case ERR_AMMETER_VOL:
        dugs_lock(p_this);
        p_this->super.rd_reg.vol_state  = p_arg ? 1 : 0;
        dugs_unlock(p_this);
        break;

    case ERR_AMMETER:
        dugs_lock(p_this);
        p_this->super.rd_reg.ammeter_state  = p_arg ? 1 : 0;
        dugs_unlock(p_this);
        break;

    case ERR_CARD_READER:
        dugs_lock(p_this);
        p_this->super.rd_reg.cardreader_state  = p_arg ? 1 : 0;
        dugs_unlock(p_this);
        break;

    case CARD_ADMIN_MODE:
        dugs_lock(p_this);
        p_this->super.rd_reg.admin_flag = p_arg ? 0x55 : 0xAA;
        dugs_unlock(p_this);
        break;

    case HUB4G_BILLING:
        p_usr_ctrl = (struct aw_remote_adjust_usr_ctrl *)p_arg;
        dugs_lock(p_this);
        p_this->super.rd_reg.used_energy = p_usr_ctrl->now_charge_energy / 10;
        p_this->super.rd_reg.used_amount = p_usr_ctrl->now_charge_amount  / 10;
//        balance = (p_billing_dat->usr_balance - p_billing_dat->used_amount) / 10;
//        p_this->super.rd_reg.usr_balance[0] = ((balance & 0xFFFF0000) >> 16 );
//        p_this->super.rd_reg.usr_balance[1] = ((balance & 0xFFFF) >> 0 );
        dugs_unlock(p_this);
        break;

    case HUB4G_PILE_ID:
        dugs_lock(p_this);
        dugs_pile_id_set(p_this, p_arg);
        dugs_unlock(p_this);
        break;

    default: break;
    }

}

