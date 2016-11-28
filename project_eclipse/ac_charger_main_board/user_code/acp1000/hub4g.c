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
 * \brief 集中器实例
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "mb/ac_modbus_reg_map.h"
#include "mb/aw_mb_dgus_regmap.h"
#include "string.h"
#include "aw_sem.h"
#include "aw_time.h"
#include "aw_rtc.h"
#include "aw_delay.h"
#include "ac_charge_prj_cfg.h"
#include "hub4g.h"
#include "dugs.h"
#include "billing.h"
#include "ammeter.h"
#include "modbus/aw_mb_utils.h"
#include "aw_nvram.h"
#include "aw_delayed_work.h"

#define UNLOCK_TO_HUB4G(p_this, pp_role) \
    struct hub4g *p_this = AW_CONTAINER_OF(pp_role, struct hub4g, p_hub4g_unlock)

#define CHARGE_CTRL_TO_HUB4G(p_this, pp_role) \
    struct hub4g *p_this = AW_CONTAINER_OF(pp_role, struct hub4g, p_hub4g_charge_ctrl)

#define BILLING_TO_HUB4G(p_this, pp_role) \
    struct hub4g *p_this = AW_CONTAINER_OF(pp_role, struct hub4g, p_hub4g_billing)

#define ALLOW_CHARGER_TO_HUB4G(p_this, pp_role) \
    struct hub4g *p_this = AW_CONTAINER_OF(pp_role, struct hub4g, p_hub4g_allow_charge)


#define AUTH_USR_TO_HUB4G(p_this, pp_role) \
    struct hub4g *p_this = AW_CONTAINER_OF(pp_role, struct hub4g, p_hub4g_auth_usr)


#define AUTH_KEY_TO_HUB4G(p_this, pp_role) \
    struct hub4g *p_this = AW_CONTAINER_OF(pp_role, struct hub4g, p_hub4g_auth_key)

#define SETTINGS_TO_HUB4G(p_this, pp_role) \
    struct hub4g *p_this = AW_CONTAINER_OF(pp_role, struct hub4g, p_hub4g_settings)

#define EVT_TO_HUG4G(p_this, p_evt) \
    struct hub4g *p_this = AW_CONTAINER_OF(p_evt, struct hub4g, evt_node)

#define PILE_SEM_TO_PILE(p_pile, p_pile_sem) \
    struct pile *p_pile = AW_CONTAINER_OF(p_pile_sem, struct pile, pile_sem)

static role_ret play(role_t **pp_role, void *p_arg);
void static event_driver(struct event_node *p_evt, event_t event, void *p_arg);

int hub4g_card_key_recevied (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t *p_this = (hub4g_t *)p_arg;
    role_t  *p_role = NULL;

    hub4g_dev_lock(p_this);
    p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.key_store_ok = 1;
    /* 置刷卡标志位为1，起始等待集中器下发key */
    p_this->super.rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit.card_swing_ok1 = 0;
    hub4g_dev_unlock(p_this);

    event_node_tell_all(&p_this->evt_node, HUB4G_AUTH_KEY, val);

    AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
    p_role = p_this->p_hub4g_auth_key;
    AW_MUTEX_UNLOCK(p_this->role_lock);

    if (NULL != p_role) {
        p_this->player.pfn_play(&p_this->p_hub4g_auth_key, val);
    }
    //todo 发起密钥下发信号量
//#if ACP1000_HUB4G_AUTH /* 是否开启集中器鉴权 */
//    AW_SEMB_GIVE(p_this->super_key_sem);
//#endif
    return AW_OK;
}

int hub4g_charge_price_recevied (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t              *p_this   = (hub4g_t *)p_arg;
    struct modbus_reg_map *p_hub4g = &(p_this->super);

    hub4g_dev_lock(p_this);
    aw_mb_regcpy(p_hub4g->rm_measure_reg.charger_data.time_invl_price, val, RM_ADJ_CHARGE_PRICE_NUM);
    hub4g_dev_unlock(p_this);

    event_node_tell(&p_this->evt_node, HUB4G_PRICE, val);

    return AW_OK;
}


int hub4g_usr_id_recevied (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t              *p_this   = (hub4g_t *)p_arg;
    struct modbus_reg_map *p_hub4g = &(p_this->super);

    hub4g_dev_lock(p_this);
    aw_mb_regcpy(p_hub4g->rm_measure_reg.usr_info.user_id, val, RM_ADJ_USR_ID_NUM);
    hub4g_dev_unlock(p_this);

    //todo 发起用户ID数据
//    acp1000_work_state_lock(p_ws);
//    aw_mb_regcpy(p_ws->super.rd_reg.usr_id, val, RM_ADJ_USR_ID_NUM);
//    acp1000_work_state_unlock(p_ws);

    return AW_OK;
}

int hub4g_pile_id_recevied (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t              *p_this   = (hub4g_t *)p_arg;
    struct modbus_reg_map *p_hub4g = &(p_this->super);

    hub4g_dev_lock(p_this);
    aw_mb_regcpy(p_hub4g->rm_measure_reg.charger_data.pile_id, val, RM_ADJ_PILE_ID_NUM);
    hub4g_dev_unlock(p_this);

    event_node_tell_all(&p_this->evt_node, HUB4G_PILE_ID, p_hub4g->rm_measure_reg.charger_data.pile_id);

    return AW_OK;
}


int hub4g_usr_balance_recevied (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t              *p_this   = (hub4g_t *)p_arg;
    struct modbus_reg_map *p_hub4g = &(p_this->super);
    uint8_t                state   = 0;
    role_t  *p_role = NULL;

#if ACP1000_CARD_AMOUNT_ADD
    /* 测试余额 100000*/
    (*(uint16_t *)val)         = (100000 & 0xFFFF0000) >> 16; /* 读取卡余额 */
    (*(((uint16_t *)val) + 1)) = (100000 & 0xFFFF);           /* 读取卡余额 */
#endif
    hub4g_dev_lock(p_this);
    aw_mb_regcpy(p_hub4g->rm_measure_reg.usr_info.user_balance, val, RM_ADJ_USR_BALANCE_NUM);
    hub4g_dev_unlock(p_this);

    AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
    p_role = p_this->p_hub4g_auth_usr;
    AW_MUTEX_UNLOCK(p_this->role_lock);

    //todo 发送用户ID和用户余额
    event_node_tell_all(&p_this->evt_node,
                         HUB4G_USR_INFO,
                        &(p_hub4g->rm_measure_reg.usr_info));

    if (NULL != p_role) {
        p_this->player.pfn_play(&p_this->p_hub4g_auth_usr, val);
    }
    return AW_OK;
}

int hub4g_charge_interface_recevied (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t              *p_this   = (hub4g_t *)p_arg;
    struct modbus_reg_map *p_hub4g = &(p_this->super);

    hub4g_dev_lock(p_this);
    aw_mb_regcpy(&p_hub4g->rm_measure_reg.charger_wdata, val, RM_ADJ_USR_CHARGE_INTERFACE_NUM);
    hub4g_dev_unlock(p_this);
    return AW_OK;
}

static
int hub4g_charge_energy_recevied (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t              *p_this   = (hub4g_t *)p_arg;
    struct modbus_reg_map *p_hub4g = &(p_this->super);
    role_t  *p_role = NULL;

    AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
    p_role = p_this->p_hub4g_billing;
    AW_MUTEX_UNLOCK(p_this->role_lock);

    if (NULL != p_role) {
        p_this->player.pfn_play(&p_this->p_hub4g_billing, val);
    }

    return AW_OK;
}

int hub4g_auth_fail_reason_recevied (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t              *p_this   = (hub4g_t *)p_arg;
    struct modbus_reg_map *p_hub4g = &(p_this->super);

    hub4g_dev_lock(p_this);
    aw_mb_regcpy(&p_hub4g->rm_measure_reg.charger_wdata.auth_fail_reason,
                  val,
                  RM_ADJ_USR_CHARGE_INTERFACE_NUM);
    hub4g_dev_unlock(p_this);
    return AW_OK;
}

/** 返回用户余额 单位0.01元 */
static uint32_t hub4g_usr_balance_get (hub4g_t *p_this)
{
    struct modbus_reg_map *p_hub4g = &(p_this->super);

    uint32_t  balance;
    uint16_t *p_usr_amout = p_hub4g->rm_adjust_reg.usr_ctrl.usr_info.user_balance;


    hub4g_dev_lock(p_this);
    balance =  (p_usr_amout[0] << 16) |
               (p_usr_amout[1] << 0)  ;
    hub4g_dev_unlock(p_this);

    return balance;
}

/**
 * 获取本次充电金额
 * 返回电量单位 0.01元
 */
static uint16_t hub4g_charge_amout_get (hub4g_t *p_this)
{
    uint16_t  balance;

    hub4g_dev_lock(p_this);
    balance = p_this->super.rm_adjust_reg.usr_ctrl.now_charge_amount;
    hub4g_dev_unlock(p_this);

    return balance;
}

/**
 * 获取本次充电电量
 * 返回电量单位 0.01度
 */
static uint16_t hub4g_charge_energy_get (hub4g_t *p_this)
{
    uint16_t  energy;

    hub4g_dev_lock(p_this);
    energy = p_this->super.rm_adjust_reg.usr_ctrl.now_charge_energy;
    hub4g_dev_unlock(p_this);

    return energy;
}

/**
 * 保存测量参数
 * enery : 32位电表读数
 * vol   : 电压 ， 单位0.1V
 * curr  : 电流 ， 单位0.1A
 */
static void hub4g_ammeter_data_set (hub4g_t  *p_this,
                                    uint32_t  energy,
                                    uint32_t  vol,
                                    uint32_t  curr)
{
    struct aw_charger_whole_data *p_dat = \
                              &p_this->super.rm_measure_reg.charger_wdata;

    hub4g_dev_lock(p_this);
    p_dat->charger_out_curr = curr;
    p_dat->charger_out_volt = vol;
    p_dat->meter_rtval_hi_word = (energy & 0xFFFF0000) >> 16;
    p_dat->meter_rtval_lo_word = (energy & 0xFFFF);
    hub4g_dev_unlock(p_this);
}

/**
 * 保存充电参数
 * enery :  充电电量 单位 0.01度
 * amout  : 充电金额  单位：0.01元
 * time  :  充电时间  单位，分
 */
static void hub4g_charge_data_set (hub4g_t *p_this,
                                   uint16_t energy,
                                   uint16_t amout,
                                   uint16_t time)
{
    struct aw_charger_whole_data *p_dat = \
                              &p_this->super.rm_measure_reg.charger_wdata;

    hub4g_dev_lock(p_this);
    p_dat->now_charge_energy = energy;
    p_dat->now_charge_time   = time;
    p_dat->now_charge_amount = amout;
    hub4g_dev_unlock(p_this);
}

/**
 * 设置卡ID
 * p_id_buf为NULL时，设置为全0
 */
static void hub4g_card_id_set (hub4g_t *p_this,
                               uint8_t *p_id_buf,
                               uint8_t  id_len)
{
    int i;

    hub4g_dev_lock(p_this);
    if (p_id_buf != NULL) {
        for (i = 0; i < id_len; i++) {
            if (0 == (i % 2)) {
                p_this->super.rm_measure_reg.s50_card.card_id[i/2] = (p_id_buf[id_len-1-i] << 8);
            } else {
                p_this->super.rm_measure_reg.s50_card.card_id[i/2]  |= (p_id_buf[id_len-1-i]);
            }
        }
    } else {
        memset(p_this->super.rm_measure_reg.s50_card.card_id, 0, 4);
    }
    hub4g_dev_unlock(p_this);
}

/**
 * 设置扇区数据
 * p_blk_dat为NULL时，设置为全0
 */
static void hub4g_card_blk_dat_set (hub4g_t *p_this,
                                    uint8_t *p_blk_dat,
                                    uint8_t  blk)
{
    int i;
    int tmp ;

    if (p_blk_dat != NULL) {
        blk = (blk - 1) * 8;

        for (i = 0; i < 16; i++) {
            tmp =  blk + (i / 2);
            if (0 == (i % 2)) {
                p_this->super.rm_measure_reg.s50_card.card_dat[tmp] = (p_blk_dat[i] << 8);
            } else {
                p_this->super.rm_measure_reg.s50_card.card_dat[tmp] |= (p_blk_dat[i]);
            }
        }
    } else {
        memset(p_this->super.rm_measure_reg.s50_card.card_dat, 0, 48);
    }
}


/**
 * 获取本次充电电量
 */


/**
 * 是否允许充电
 */
static bool_t hub4g_charge_allow_get (hub4g_t *p_this)
{
    uint16_t data;

    hub4g_dev_lock(p_this);
    data = p_this->super.rm_ctrl_reg.gun_ctrl_data[0].allow_charging;
    hub4g_dev_unlock(p_this);

    if (data == 0x00AA) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 是否开始充电
 */
static bool_t hub4g_charge_allow_ctrl (hub4g_t *p_this)
{
    uint16_t  data;
    uint16_t *p_data = \
            p_this->super.rm_ctrl_reg.gun_ctrl_data[0].charging_startup;

    hub4g_dev_lock(p_this);
    data =  p_data[0];
    hub4g_dev_unlock(p_this);

    if (data == 0x00AA) {
        return TRUE;
    } else {
        return FALSE;
    }
}


/**
 * 获取用户ID
 */
static void hub4g_usr_id_get (hub4g_t *p_this, uint16_t *p_buf)
{
    uint16_t *p_usr_id = p_this->super.rm_adjust_reg.usr_ctrl.usr_info.user_id;

    hub4g_dev_lock(p_this);
    memcpy(p_buf, p_usr_id, 8);
    hub4g_dev_unlock(p_this);
}

/**
 * \brief 获取某小时的电价
 * \param[in] p_this : 集中器实例
 * \param[in] hour : 0 - 23
 *
 * \return 电价 单位0.0001元
 */
static uint16_t hub4g_charge_price_get (hub4g_t *p_this, uint8_t hour)
{
    uint16_t *p_price = \
                p_this->super.rm_measure_reg.charger_data.time_invl_price;
    uint16_t  price   = RM_ADJ_ELECT_MIN_PRICE;

    hour  = hour > 23 ? 0 : hour;
    hub4g_dev_lock(p_this);
    price = p_price[hour];
    hub4g_dev_unlock(p_this);

    return price;
}
/**
 * 获取当前5个小时以内的充电电价平均值
 * 有助于对充电电量的估算
 */
static uint16_t hub4g_charge_price_avg (hub4g_t *p_this)
{
    uint16_t *p_price = \
                p_this->super.rm_measure_reg.charger_data.time_invl_price;
    uint16_t  price   = RM_ADJ_ELECT_MIN_PRICE;
    uint32_t  sum     = 0;
    uint8_t   i       = 0;
    uint8_t   hour    = 12;

    aw_tm_t  tm;
    /* 获取起始时间 */
    if (AW_OK != aw_rtc_time_get(ACP1000_RTC_NUM, &tm)) {
        hour = 12;
    } else {
        hour  = tm.tm_hour;
    }
    hub4g_dev_lock(p_this);
    for (i = 0; i < 5; i++) {
        sum += p_price[hour];
        hour++;
        hour = hour > 23 ? 0 : hour;
    }
    hub4g_dev_unlock(p_this);
    price = sum / 5;

    return price;
}
/**
 * 调整时间
 */
static int hub4g_time_adjust (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    aw_tm_t tm;
    /* 设置时间  */
    struct aw_charger_time *p_time = (struct aw_charger_time *)val;

    tm.tm_year = p_time->year - 1900;
    tm.tm_mon  = p_time->month  - 1;
    tm.tm_mday = p_time->day;
    tm.tm_hour = p_time->hour;
    tm.tm_min  = p_time->minute;
    tm.tm_sec  = p_time->second;

    aw_rtc_time_set (ACP1000_RTC_NUM, &tm);
    return AW_OK;
}
/**
 * 设置遥测时间
 */
static void hub4g_rm_time_set (hub4g_t *p_this, aw_tm_t *p_tm)
{
    struct aw_charger_time *p_time = (struct aw_charger_time *)\
            &p_this->super.rm_measure_reg.charger_data.local_time;

    hub4g_dev_lock(p_this);
    p_time->year   = p_tm->tm_year + 1900;
    p_time->month  = p_tm->tm_mon + 1;
    p_time->day    = p_tm->tm_mday;
    p_time->hour   = p_tm->tm_hour;
    p_time->minute = p_tm->tm_min ;
    p_time->second = p_tm->tm_sec ;
    hub4g_dev_unlock(p_this);
}


/* 遥控回调  */

/* 是否允许充电回调 */
static int hub4g_rm_ctrl_charge_allow (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t *p_this = (hub4g_t *)p_arg;
    bool_t  state = 0;
    role_t  *p_role = NULL;

#if ACP1000_HUB4G_AUTH /* 是否开启集中器鉴权 */
    hub4g_dev_lock(p_this);
    /* todo 发起允许充电事件信号量，已拥有实现鉴权 */
//    if (state == 0) {
//        AW_SEMB_GIVE(p_this->super_cctrl_sem);
//    }
    p_this->super.rm_ctrl_reg.gun_ctrl_data[0].allow_charging = (int)val;

    if ((uint8_t)val == 0xAA) {
        state = TRUE;
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.charger_allow_stat = 1;
    } else {
        state = FALSE;
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.charger_allow_stat = 0;
    }
    hub4g_dev_unlock(p_this);

    AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
    p_role = p_this->p_hub4g_allow_charge;
    AW_MUTEX_UNLOCK(p_this->role_lock);

    if (NULL != p_role) {
        p_this->player.pfn_play(&p_this->p_hub4g_allow_charge, (void *)state);
    }
#endif
    return AW_OK;
}

/* 停止或开始充电 */
static int hub4g_rm_ctrl_charge_ctl (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t *p_this = (hub4g_t *)p_arg;
    role_t  *p_role = NULL;

    AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
    p_role = p_this->p_hub4g_charge_ctrl;
    AW_MUTEX_UNLOCK(p_this->role_lock);

    if (NULL != p_role) {
        p_this->player.pfn_play(&p_this->p_hub4g_charge_ctrl,
                                (void *)(((uint32_t)val == 0xAA) ? TRUE : FALSE));
    }
    return AW_OK;
}

extern void acp1000_overtime_check_restart();

/* 锁屏  */
static int hub4g_rm_ctrl_scren_lock (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t *p_this = (hub4g_t *)p_arg;
    struct aw_charger_stat_bit *p_rm_signal = \
            &p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit;
    uint8_t state = 0; /* 0 不做任何操作； 1，紧紧解锁锁屏；2，鉴权结果 */
    role_t  *p_role = NULL;

    AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
    p_role = p_this->p_hub4g_unlock;
    AW_MUTEX_UNLOCK(p_this->role_lock);

    hub4g_dev_lock(p_this);
    if ((uint8_t)val == 0xAA) { /* 解锁屏幕 */

        if (NULL != p_role) {
            /* 充电中，仅仅是解锁屏幕  */
            state = 1;
        } else {
            /* 非充电中，可以解锁屏幕，进行“插枪”页面 */
            p_rm_signal->card_swing_ok2 = 0;
            state = 2;
        }
        p_rm_signal->screen_lock_stat = 1;
        p_rm_signal->pile_order_stat = 0;
        /* 解锁屏幕，均要取消桩预约 */


    } else {
        p_rm_signal->screen_lock_stat = 0;
        state = 0;
    }
    hub4g_dev_unlock(p_this);

    if (0 == state) {
        return AW_OK;
    }

    /* todo 发起解锁屏幕 取消预约 */
    event_node_tell_all(&p_this->evt_node, HUB4G_PILE_ORDER, FALSE);
    /* todo 发起鉴权中事件  */
    event_node_tell_all(&p_this->evt_node, CARD_AUTH_ING, p_arg);
    aw_mdelay(200);
    switch (state) {
    case 1:
        /* todo 解锁事件  */
        p_this->player.pfn_play(&p_this->p_hub4g_unlock, NULL);
        break;

    case 2:
        /* todo 发起鉴权成功  */
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_SUS, p_arg);

#if ACP1000_OVERTIME_DETECT
    acp1000_overtime_check_restart();
#endif
        break;

    default:
        break;
    }

    return AW_OK;
}

/* 4G通信状态 */
static int hub4g_rm_ctrl_comm_state (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t *p_this = (hub4g_t *)p_arg;
    struct aw_charger_stat_bit *p_rm_signal = \
            &p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit;

    hub4g_dev_lock(p_this);
    if ((uint32_t)val == 0xAA) {
        p_rm_signal->g4_comm_stat = 0;
    } else {
        p_rm_signal->g4_comm_stat = 1;
    }
    hub4g_dev_unlock(p_this);

    event_node_tell_all(&p_this->evt_node, ERR_HUB4G, (void *)(p_rm_signal->g4_comm_stat));

    return AW_OK;
}

/* 预约充电  */
static int hub4g_rm_ctrl_charge_order (void *p_arg, void *p_reg, uint8_t gun_num, void *val)
{
    hub4g_t *p_this = (hub4g_t *)p_arg;
    struct aw_charger_stat_bit *p_rm_signal = \
            &p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit;

    hub4g_dev_lock(p_this);
    if ((uint32_t)val == 0xAA) {
        p_rm_signal->pile_order_stat = 1;
    } else {
        p_rm_signal->pile_order_stat = 0;
    }
    hub4g_dev_unlock(p_this);

    /* todo 预约事件控制 */
    event_node_tell_all(&p_this->evt_node,
                        HUB4G_PILE_ORDER,
                       (((uint32_t)val == 0xAA) ? TRUE : FALSE));
    return AW_OK;
}

#define ALARM     1
#define NONALARM  0

/**
 * 报警情况汇总显示
 */
static void hub4g_alarm_status_set (hub4g_t *p_this, uint16_t err)
{
    struct modbus_reg_map *p_hub4g = &p_this->super;
    struct aw_charger_stat_bit *p_state = \
            &p_hub4g->rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit;

    if (err & PILE_ALARM_CARDREADER) {
        p_state->cardreader_alm = ALARM;
    } else {
        p_state->cardreader_alm = NONALARM;
    }

    if (err & PILE_ALARM_AMMETER) {
       p_state->ammeter_alm = ALARM;
    } else {
       p_state->ammeter_alm = NONALARM;
    }

    if (err & PILE_ALARM_ACLOCK) {
       p_state->contactor_fault_alm = ALARM;
    } else {
       p_state->contactor_fault_alm = NONALARM;
    }

    if (err & PILE_ALARM_OVERVOL) {
        p_state->ac_in_overvolt_alm = ALARM;
    } else {
        p_state->ac_in_overvolt_alm = NONALARM;
    }

    if (err & PILE_ALARM_UNDERVOL) {
        p_state->ac_in_undervolt_alm = ALARM;
    } else {
        p_state->ac_in_undervolt_alm = NONALARM;
    }

    if (err & PILE_ALARM_LIGHT) {
        p_state->light_pro_alm = ALARM;
    } else {
        p_state->light_pro_alm = NONALARM;
    }

    if (err & PILE_ALARM_TEMP) {
        p_state->charger_overtemp_alm = ALARM;
    } else {
        p_state->charger_overtemp_alm = NONALARM;
    }
}
#define ACTIVE     1
#define INACTIVE   0

static void hub4g_stop_reason_set (hub4g_t      *p_this,
                                   uint16_t      reason,
                                   uint16_t      err)
{
    struct modbus_reg_map *p_hub4g = &p_this->super;
    struct aw_charging_stop_cause_bit *p_state = \
            &p_hub4g->rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit;

    if (reason == AW_MB_DGUS_CHARGE_MAN_EXIT) {
        p_state->manual_stop = ACTIVE;
    } else {
        p_state->manual_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_BG_EXIT) {
        p_state->background_stop = ACTIVE;
    } else {
        p_state->background_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_BALANCE_UNDER) {
        p_state->banlance_notenough_stop = ACTIVE;
    } else {
        p_state->banlance_notenough_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_CARDREADER) {
        p_state->pos_charge_unusal_stop = ACTIVE;
    } else {
        p_state->pos_charge_unusal_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_AMETETER) {
       p_state->measure_per_unusal_stop = ACTIVE;
    } else {
       p_state->measure_per_unusal_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_CURR) {
      p_state->ac_in_overcurr_stop = ACTIVE;
    } else {
      p_state->ac_in_overcurr_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_OVERVOL) {
        p_state->ac_in_overvolt_stop = ACTIVE;
    } else {
        p_state->ac_in_overvolt_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_UNDERVOL) {
        p_state->ac_in_undervolt_stop = ACTIVE;
    } else {
        p_state->ac_in_undervolt_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_LIGHT) {
       p_state->light_pro_unusal_stop = ACTIVE;
    } else {
       p_state->light_pro_unusal_stop = INACTIVE;
    }

    if (reason == AW_MB_DGUS_CHARGE_AC) {
       p_state->guide_test_fail = ACTIVE;
    } else {
       p_state->guide_test_fail = INACTIVE;
    }
}


static int upgrade_callback (void *p_arg)
{
    hub4g_t *p_this = (hub4g_t *)p_arg;

    if(NULL == p_this) {
        return -AW_EINVAL;
    }

    /* 告知串口屏正在升级 */
    event_node_tell_all(&p_this->evt_node, HUB4G_UPGRADE, TRUE);

    /* 延时200以便串口屏能轮询到该标志位*/
    aw_mdelay(975);
}


static struct aw_delayed_work g_hub4g_comm_work; /* 集中器通信异常延时处理工作  */
static bool_t g_comm_err_state = FALSE;          /* 集中器异常情况 */

/**
 * 集中器通信异常处理
 */
static void hub4g_comm_dly_work (void *p_arg)
{
    hub4g_t *p_this        = (hub4g_t *)p_arg;

    event_node_tell_all(&p_this->evt_node, ERR_HUB4G_COMM, TRUE);
    g_comm_err_state = TRUE;
}

/**
 * 集中器通信正常回调
 */
aw_local int hub4g_comm_state_action (void *p_arg, uint16_t val)
{
#if ACP1000_HUB4G_ERR_DETECT
    hub4g_t *p_this        = (hub4g_t *)p_arg;

    aw_delayed_work_stop(&g_hub4g_comm_work);
    aw_delayed_work_start(&g_hub4g_comm_work, ACP1000_HUB4G_ERR_TIMEOUT);
    if (g_comm_err_state) {
        event_node_tell_all(&p_this->evt_node, ERR_HUB4G_COMM, FALSE);
        g_comm_err_state = FALSE;
    }
#endif
    return AW_OK;
}

void hub4g_inst_init(hub4g_t      *p_hub4g,
                    modbus_info_t *p_mb_info,
                    pile_sem_t    *p_pile_sem,
                    bool_t         key_vaild)
{
    PILE_SEM_TO_PILE(p_pile, p_pile_sem);
    struct modbus_reg_map *p_this = (struct modbus_reg_map *)&(p_hub4g->super);
    uint8_t pile_id[8];
    uint8_t addr;
    uint8_t price[48];

    memset(p_this, 0, sizeof(struct modbus_reg_map));

    p_hub4g->player.pfn_play      = play;
    p_hub4g->evt_node.pfunc_event = event_driver;
    p_hub4g->p_pile_sem = p_pile_sem;
    modbus_reg_map_init(p_this);

    /* 遥调 */
    modbus_func_cb_register(p_this, PILE_ID_FUNC, hub4g_pile_id_recevied, p_hub4g);
    modbus_func_cb_register(p_this, CARD_KEY_LOAD_FUNC, hub4g_card_key_recevied, p_hub4g);
    modbus_func_cb_register(p_this, USR_ID_SAVE_FUNC, hub4g_usr_id_recevied, p_hub4g);
    modbus_func_cb_register(p_this, USR_ID_BALANCE_FUNC, hub4g_usr_balance_recevied, p_hub4g);
    modbus_func_cb_register(p_this, TIME_SET_FUNC, hub4g_time_adjust, p_hub4g);
    modbus_func_cb_register(p_this, CHARGE_INTERFACE_FUNC, hub4g_charge_interface_recevied, p_hub4g);
    modbus_func_cb_register(p_this, CHARGE_PRICE_FUNC, hub4g_charge_price_recevied, p_hub4g);
    modbus_func_cb_register(p_this, CHARGE_ENERGY_FUNC, hub4g_charge_energy_recevied, p_hub4g);
    modbus_func_cb_register(p_this, AUTH_FAILE_REASON, hub4g_auth_fail_reason_recevied, p_hub4g);

    /* 遥控回调 */
    modbus_func_cb_register(p_this, ALLOW_CHARGING_FUNC, hub4g_rm_ctrl_charge_allow, p_hub4g);
    modbus_func_cb_register(p_this, CHARGING_STARTUP_FUNC, hub4g_rm_ctrl_charge_ctl, p_hub4g);
    modbus_func_cb_register(p_this, UNLOCK_SCREEN_FUNC, hub4g_rm_ctrl_scren_lock, p_hub4g);
    modbus_func_cb_register(p_this, COMM_4G_STAT_FUNC, hub4g_rm_ctrl_comm_state, p_hub4g);
    modbus_func_cb_register(p_this, ORDER_CHARGING_FUNC, hub4g_rm_ctrl_charge_order, p_hub4g);

    /* 集中器通信正常回调 */
    modbus_func_cb_register(p_this, HUB4G_COMM_STATE, hub4g_comm_state_action, p_hub4g);

#if ACP1000_EEPROM_PILE_ID_GET
    if(AW_OK == aw_nvram_get(ACP1000_EEPROM_NAME, 1, &pile_id, 0, 8)) {
        // 设置非易失性数据"桩ID"
        aw_mb_regcpy(p_this->rm_measure_reg.charger_data.pile_id, pile_id, RM_ADJ_PILE_ID_NUM);
    } else {
        p_pile->pile_alarm.alarm_mask |= PILE_ALARM_EEPROM;
    }
#endif

#if ACP1000_EEPROM_PRICE_GET
    memset(price, 0, sizeof(price));
    if (AW_OK != aw_nvram_get(ACP1000_EEPROM_NAME, 3, price, 0, 48)) {
         p_pile->pile_alarm.alarm_mask |= PILE_ALARM_EEPROM;
    }
    aw_mb_regcpy(p_this->rm_measure_reg.charger_data.time_invl_price, price, RM_ADJ_CHARGE_PRICE_NUM);
#endif

    /* 接口标志对交流桩恒为 0 */
    p_this->rm_measure_reg.charger_wdata.charger_interface = 0;

    /* 初始化dgus modbus slave*/
     ac_modbus_slave_hdl_init (p_this,
                               p_mb_info->addr,
                               p_mb_info->com,
                               p_mb_info->baud,
                               p_mb_info->par);

     ac_modbus_upgrade_callback_set(upgrade_callback, (void *)p_hub4g);

#if ACP1000_EEPROM_HUB4G_ADDR_GET
    if(AW_OK == aw_nvram_get(ACP1000_EEPROM_NAME, 2, &addr, 0, 1)) {
        ac_modbus_slave_set_addr(addr);
    }
#endif

    if (key_vaild) {
        p_this->rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.key_store_ok = 1;
    }

#if ACP1000_HUB4G_ERR_DETECT
    aw_delayed_work_init(&g_hub4g_comm_work,
                          hub4g_comm_dly_work,
                          p_hub4g);
    aw_delayed_work_start(&g_hub4g_comm_work, ACP1000_HUB4G_ERR_TIMEOUT);
#endif
}

static role_ret play(role_t **pp_role, void *p_arg)  /* 扮演 */
{
    if ((*pp_role)->pfn_role_do) {
        return (*pp_role)->pfn_role_do(pp_role, p_arg);
    }
    return -AW_EINVAL;
}

/**
 * 用户余额控制
 */
static role_ret hub4g_auth_usr_do (struct role **pp_role, void *p_arg)
{
    AUTH_USR_TO_HUB4G(p_this, pp_role);

    event_node_tell(&p_this->evt_node, HUB4G_AUTH_USR, p_arg);
    /* 发送鉴权成功 */
    AW_SEMB_GIVE(p_this->p_pile_sem->hub4g_auth_sem);
    return AW_OK;
}

/**
 * 允许充电控制
 */
static role_ret hub4g_allow_charge_do (struct role **pp_role, void *p_arg)
{
    ALLOW_CHARGER_TO_HUB4G(p_this, pp_role);

    /* 发送允许充电事件 */
    event_node_tell_all(&p_this->evt_node, HUB4G_ALLOW_CHARGE, p_arg);
    AW_SEMB_GIVE(p_this->p_pile_sem->hub4g_cctrl_sem);

    return AW_OK;
}

/**
 * 允许充电控制
 */
static role_ret hub4g_billing_do (struct role **pp_role, void *p_arg)
{
    BILLING_TO_HUB4G(p_this, pp_role);

    /* 发送允许充电事件 */
    event_node_tell_all(&p_this->evt_node, HUB4G_BILLING, &(p_this->super.rm_adjust_reg.usr_ctrl));
    AW_SEMB_GIVE(p_this->p_pile_sem->hub4g_billing_sem);

    return AW_OK;
}


/**
 * 密钥下发控制
 * p_arg： 密钥
 */
static role_ret hub4g_auth_key_do (struct role **pp_role, void *p_arg)
{
    AUTH_KEY_TO_HUB4G(p_this, pp_role);

    /* 发送密钥下发事件 */
//    event_node_tell_all(&p_this->evt_node, HUB4G_AUTH_KEY, p_arg);
    AW_SEMB_GIVE(p_this->p_pile_sem->hub4g_key_sem);
    return AW_OK;
}

/**
 * 密钥下发控制
 * p_arg： TRUE: 开始充电，FALSE: 停止充电
 */
static role_ret hub4g_charge_ctrl_do (struct role **pp_role, void *p_arg)
{
    CHARGE_CTRL_TO_HUB4G(p_this, pp_role);

    if (p_arg) {
        event_node_tell_all(&p_this->evt_node, CHARGE_MAN_START, NULL);
    } else {
        event_node_tell_all(&p_this->evt_node, CHARGE_BG_STOP, NULL);
    }

    return AW_OK;
}

/**
 * 解锁器
 */
static role_ret hub4g_unlock_do (struct role **pp_role, void *p_arg)
{
    UNLOCK_TO_HUB4G(p_this, pp_role);

    event_node_tell_all(&p_this->evt_node, SCREEN_UNLOCK, NULL);
    return AW_OK;
}

/*=============================事件驱动==========================================*/
void static event_driver(struct event_node *p_evt, event_t event, void *p_arg)
{
    EVT_TO_HUG4G(p_this, p_evt);
    static role_t hub4g_auth_usr     = {hub4g_auth_usr_do};
    static role_t hub4g_auth_key     = {hub4g_auth_key_do};
    static role_t hub4g_allow_charge = {hub4g_allow_charge_do};
    static role_t hub4g_billing      = {hub4g_billing_do};
    static role_t hub4g_charge_ctrl  = {hub4g_charge_ctrl_do};
    static role_t hub4g_unlock       = {hub4g_unlock_do};

    uint8_t           *p_blk_dat     = NULL;
    billing_mode_t    *p_billing_mod = NULL;
    pile_time_price_t *p_tm          = NULL ;
    uint16_t           temp;
    billing_dat_t     *p_billing_dat = NULL;
    ammeter_dat_t     *p_ammeter_dat = NULL;
    uint8_t            buf[48];
    uint8_t            addr;
    uint32_t           price;

    switch (event) {

    case CARD_WAIT_KEY: /* 等待密钥   p_arg 为：卡片ID  */
        hub4g_card_id_set(p_this, (uint8_t *)p_arg, 4);
        hub4g_dev_lock(p_this);
        /* 清除密钥保存标志 */
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.key_store_ok = 0;
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.charger_allow_stat = 0;
        /* 置刷卡标志位为1，起始等待集中器下发key */
        p_this->super.rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit.card_swing_ok1 = 1;
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.card_swing_ok2 = 0;
        AW_SEMB_INIT(p_this->p_pile_sem->hub4g_key_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
        hub4g_dev_unlock(p_this);

        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_auth_key  =  &hub4g_auth_key;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CARD_AUTH_ID:
        hub4g_card_id_set(p_this, (uint8_t *)p_arg, 4);
        hub4g_dev_lock(p_this);
        /* 清除密钥保存标志 */
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.charger_allow_stat = 0;
        /* 置刷卡标志位为1，起始等待集中器下发key */
        p_this->super.rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit.card_swing_ok1 = 1;
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.card_swing_ok2 = 0;
        hub4g_dev_unlock(p_this);

        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_auth_key  =  NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case HUB4G_AUTH_KEY:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_auth_key = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CARD_SWING_OK:
        p_blk_dat = (uint8_t *)p_arg; /* 卡扇区数据 */
        /* 向集中器点表填写卡扇区数据 */
        hub4g_dev_lock(p_this);
        AW_SEMB_INIT(p_this->p_pile_sem->hub4g_auth_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
        AW_SEMB_INIT(p_this->p_pile_sem->hub4g_cctrl_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
        hub4g_card_blk_dat_set(p_this, &p_blk_dat[0],  1);
        hub4g_card_blk_dat_set(p_this, &p_blk_dat[16],  2);
        hub4g_card_blk_dat_set(p_this, &p_blk_dat[32],  3);
        /* 刷卡成功标志位置1 */
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.card_swing_ok2 = 1;
//        /* 清除密钥保存标志 */
//        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.key_store_ok = 0;
        hub4g_dev_unlock(p_this);

        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_auth_usr     =  &hub4g_auth_usr;
        p_this->p_hub4g_allow_charge =  &hub4g_allow_charge;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case HUB4G_AUTH_USR:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_auth_usr = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        hub4g_dev_lock(p_this);
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.card_swing_ok2 = 0;
        hub4g_dev_unlock(p_this);
        break;

    case HUB4G_ALLOW_CHARGE:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_allow_charge = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CARD_AUTH_SUS:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_charge_ctrl = &hub4g_charge_ctrl;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        ac_modbus_upgrade_disable();
        break;

    case CARD_AUTH_FAIL:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_charge_ctrl = NULL;
        p_this->p_hub4g_unlock      =  NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        hub4g_charge_data_set(p_this, 0, 0, 0);
        hub4g_card_id_set(p_this, NULL, 0);
        hub4g_dev_lock(p_this);
        memset(&(p_this->super.rm_measure_reg.usr_info), 0, sizeof(struct aw_charging_usr_info));
        hub4g_card_blk_dat_set(p_this, NULL, 0);
        p_this->super.rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit.card_swing_ok1 = 0;
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.card_swing_ok2 = 0;
//        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.key_store_ok = 0;
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.charger_allow_stat = 0;
        hub4g_dev_unlock(p_this);

        ac_modbus_upgrade_enable();
        break;

    case CHARGE_MAN_START:
    case CHARGE_PIEL_START:
        hub4g_dev_lock(p_this);
        if (event == CHARGE_PIEL_START) {
            p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.charger_stat = 1;
        }
        AW_SEMB_INIT(p_this->p_pile_sem->hub4g_billing_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
        hub4g_stop_reason_set(p_this, 0, 0);
        hub4g_alarm_status_set(p_this, 0);
        hub4g_dev_unlock(p_this);

        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_billing = &hub4g_billing;
        p_this->p_hub4g_unlock  = &hub4g_unlock;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        ac_modbus_upgrade_disable();
        break;

    case CHARGE_PILE_STOP:
        hub4g_dev_lock(p_this);
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.charger_stat = 0;
        hub4g_dev_unlock(p_this);

        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_charge_ctrl = NULL;
        p_this->p_hub4g_unlock      =  NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case BILLING_ING: /* 计费中 */
        p_billing_dat = (billing_dat_t  *)p_arg;
        hub4g_charge_data_set(p_this,
                              p_billing_dat->used_energy,
                              p_billing_dat->used_amount,
                              p_billing_dat->used_time);
        break;

    case AMETER_MEASURE:
        p_ammeter_dat = (ammeter_dat_t *)p_arg;
        hub4g_ammeter_data_set(p_this,
                               p_ammeter_dat->now_energy,
                               p_ammeter_dat->now_vol,
                               p_ammeter_dat->now_curr / 100);
        break;

    case BILLING_END:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_hub4g_billing = NULL;
        p_this->p_hub4g_unlock  = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        hub4g_charge_data_set(p_this, 0, 0, 0);
        hub4g_card_id_set(p_this, NULL, 0);
        hub4g_dev_lock(p_this);
        hub4g_card_blk_dat_set(p_this, NULL, 0);
        memset(&(p_this->super.rm_measure_reg.usr_info), 0, sizeof(struct aw_charging_usr_info));
        p_this->super.rm_signal_reg.charger_stat[0].charger_stat1.stat1_bit.charger_allow_stat = 0;
        hub4g_dev_unlock(p_this);

        ac_modbus_upgrade_enable();
        break;

    case BILLING_MODE_GET:
        p_billing_mod = (billing_mode_t  *)p_arg;
        p_billing_mod->usr_balance = hub4g_usr_balance_get(p_this);
        break;

    case PILE_TIME:
        p_tm = (pile_time_price_t *)p_arg;
        hub4g_rm_time_set(p_this, &p_tm->tm);
        p_tm->now_price = hub4g_charge_price_get(p_this, p_tm->tm.tm_hour);
        break;

    case PILE_ALARM:
        hub4g_dev_lock(p_this);
        p_this->pile_alarm = (uint32_t)p_arg;
        hub4g_alarm_status_set(p_this, p_this->pile_alarm);
        hub4g_dev_unlock(p_this);
        break;

    case ERR_CHAGER:
        hub4g_dev_lock(p_this);
        hub4g_stop_reason_set(p_this, (uint32_t)p_arg, p_this->pile_alarm);
        hub4g_dev_unlock(p_this);
        break;

    case PILE_TEMP:
        hub4g_dev_lock(p_this);
        temp = (int16_t)p_arg;
        if (temp > -50) {
            p_this->super.rm_measure_reg.charger_wdata.charger_ambient_temp = \
                                                              500 + (temp * 10);
        } else {
            p_this->super.rm_measure_reg.charger_wdata.charger_ambient_temp =  0;
        }
        hub4g_dev_unlock(p_this);
        break;

    case HUB4G_PILE_ID:
#if ACP1000_EEPROM_PILE_ID_SET
        if (AW_OK != aw_nvram_set(ACP1000_EEPROM_NAME, 1, p_arg, 0, 8)) {
            return ;
        }
#endif
#if ACP1000_EEPROM_PILE_ID_GET
        memset(buf, 0, sizeof(buf));
        if (AW_OK != aw_nvram_get(ACP1000_EEPROM_NAME, 1, buf, 0, 8)) {
             return;
        }
        hub4g_dev_lock(p_this);
        memcpy(p_this->super.rm_measure_reg.charger_data.pile_id, buf, 8);
        hub4g_dev_unlock(p_this);
#endif
        break;

    case DUGS_HUB4G_ADDR:
#if ACP1000_EEPROM_HUB4G_ADDR_SET
        addr = (uint8_t)p_arg;
        if(AW_OK != aw_nvram_set(ACP1000_EEPROM_NAME, 2, &addr, 0, 1)) {
            return ;
        }
#endif
#if ACP1000_EEPROM_HUB4G_ADDR_GET
        if (AW_OK != aw_nvram_get(ACP1000_EEPROM_NAME, 2, &addr, 0, 1)) {
            return ;
        }
        ac_modbus_slave_set_addr(addr);
#endif
        break;

    case HUB4G_PRICE:
#if ACP1000_EEPROM_PRICE_SET
        if (AW_OK != aw_nvram_set(ACP1000_EEPROM_NAME, 3, p_arg, 0, 48)) {
            return ;
        }
#endif
#if ACP1000_EEPROM_PRICE_GET
        memset(buf, 0, sizeof(buf));
        if (AW_OK != aw_nvram_get(ACP1000_EEPROM_NAME, 3, buf, 0, 48)) {
             return;
        }
        hub4g_dev_lock(p_this);
        aw_mb_regcpy(p_this->super.rm_measure_reg.charger_data.time_invl_price, buf, RM_ADJ_CHARGE_PRICE_NUM);
        hub4g_dev_unlock(p_this);
#endif
        break;

    case DUGS_PRICE_GET:
        price = hub4g_charge_price_avg(p_this);
        (*(uint32_t *)p_arg) = price;
        break;

    case ERR_PILE_GUN_CONN:
        if (p_arg) {
            hub4g_dev_lock(p_this);
            p_this->super.rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit.gun_contact_alm = 1;
            hub4g_dev_unlock(p_this);
        }  else {
            hub4g_dev_lock(p_this);
            p_this->super.rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit.gun_contact_alm = 0;
            hub4g_dev_unlock(p_this);
        }
        break;

    case ERR_PILE_GUN_LOCK:
        if (p_arg) {
            hub4g_dev_lock(p_this);
            p_this->super.rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit.elect_lock_alm = 1;
            hub4g_dev_unlock(p_this);
        }  else {
            hub4g_dev_lock(p_this);
            p_this->super.rm_signal_reg.charger_stat[0].charging_stop_cause.cause_bit.elect_lock_alm = 0;
            hub4g_dev_unlock(p_this);
        }
        break;


    default: break;
    }

}



