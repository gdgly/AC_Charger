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
 * \brief 计费单元实例
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
#include "billing.h"
#include "aw_time.h"
#include "aw_rtc.h"
#include "ammeter.h"
#include "pile.h"
#include "aw_nvram.h"

#include "mb/aw_mb_dgus_regmap.h"
#include "ac_charge_prj_cfg.h"
#define IDLE_TO_BILLING(p_this, pp_role) \
    struct billing *p_this = AW_CONTAINER_OF(pp_role, struct billing, p_billing_idle)

#define START_TO_BILLING(p_this, pp_role) \
    struct billing *p_this = AW_CONTAINER_OF(pp_role, struct billing, p_billing_start)

#define ING_TO_BILLING(p_this, pp_role) \
    struct billing *p_this = AW_CONTAINER_OF(pp_role, struct billing, p_billing_ing)

#define END_TO_BILLING(p_this, pp_role) \
    struct billing *p_this = AW_CONTAINER_OF(pp_role, struct billing, p_billing_end)


#define EVT_TO_BILLING(p_this, p_evt) \
    struct billing *p_this = AW_CONTAINER_OF(p_evt, struct billing, evt_node)

static role_ret play(role_t **pp_role, void *p_arg);  /* 扮演 */
static void  event_driver(struct event_node *p_evt, event_t event, void *p_arg);
static role_ret billing_idle_do (struct role **pp_role, void *p_arg);

/**
 *  \brief 充电模块实例初始化
 *  param [in]   p_this        : 充电模块实例
 *  */
void billing_inst_init(billing_t  *p_this,
                       uint8_t     rtc_id,
                       pile_sem_t *p_pile_sem,
                       pile_t     *p_pile)
{
    p_this->player.pfn_play      = play;
    p_this->evt_node.pfunc_event = event_driver;
    p_this->p_billing_idle       = NULL;
    p_this->p_billing_start      = NULL;
    p_this->p_billing_ing        = NULL;
    p_this->p_billing_end        = NULL;
    p_this->rtc_id               = rtc_id;
    p_this->p_pile_sem           = p_pile_sem;
    p_this->p_pile               = p_pile;
    p_this->enough               = TRUE;
    AW_MUTEX_INIT(p_this->dev_lock, AW_SEM_Q_PRIORITY);
    AW_MUTEX_INIT(p_this->role_lock, AW_SEM_Q_PRIORITY);

}


/**
 * 计费模式监控
 */
static void billing_mode_monitor (billing_t *p_this)
{
    uint32_t price;  /* 电价 单位0.0001元 */
    billing_dat_t *p_dat = &p_this->dat;

    billing_dev_lock(p_this);
    switch (p_this->mode.mode) {

    case AW_MB_DGUS_CHARGE_WAY_AUTO :
        break;

    case AW_MB_DGUS_CHARGE_WAY_AMOUNT :
        if (p_dat->used_amount >= (p_this->mode.charge_amount)) {
            p_dat->used_amount = p_this->mode.charge_amount;
            p_dat->stop_reason = AW_MB_DGUS_CHARGE_AMOUNT_RUNOUT;
        }
        break;

    case AW_MB_DGUS_CHARGE_WAY_ENERGY :
        if (p_dat->used_energy >= (p_this->mode.charge_energy)) {
            p_dat->used_energy = p_this->mode.charge_energy;
            price = p_dat->now_price;
            p_dat->used_amount =  (p_dat->used_energy * price) / 10000;
            p_dat->stop_reason = AW_MB_DGUS_CHARGE_ENERGY_RUNOUT;
        }
        break;

    case AW_MB_DGUS_CHARGE_WAY_TIME :
        if (p_dat->used_time >= p_this->mode.charge_time) {
            p_dat->used_time   = p_this->mode.charge_time;
            p_dat->stop_reason = AW_MB_DGUS_CHARGE_TIME_RUNOUT;
        }
        break;

    default:
        break;
    }

    /* 实时结算 */
    if (p_dat->used_amount >= p_dat->usr_balance ) {

        p_dat->used_amount  = p_dat->usr_balance;
        if (p_dat->stop_reason == AW_MB_DGUS_CHARGE_NONE) {
            /* todo 发起余额不足事件*/
            p_dat->stop_reason = AW_MB_DGUS_CHARGE_BALANCE_UNDER;
        }
    }
    billing_dev_unlock(p_this);
}

/**
 * 将当前消费细节保存在EEPROM里
 */
//static
aw_err_t billing_info_eeprom_save (billing_dat_t  *p_billing_dat,
                                   billing_mode_t *p_billing_mode)
{

#if ACP1000_EEPROM_CHARGE_DAT_SET
    /* 获取到上次的记录位置 */
    uint8_t total = 0;  /* eeprom目前有效的记录数 */
    int16_t last  = 0;  /* 上一次记录的偏移位置 */
    uint8_t buf[ACP1000_EEPROM_CHARGE_SIZE];
    uint8_t offset = 0; /* 偏移地址 */

    if(AW_OK != aw_nvram_get(ACP1000_EEPROM_NAME, 4, buf, 0, 2)) {
        return AW_ERROR;
    }
    total = buf[0];
    if ((total > ACP1000_EEPROM_CHARGE_MAX_NUMS) ||
        (total == 0)) {
        /* 错误的数据，任务无效，一般EEPROM 出厂即使0xFF */
        last  = -1;
        total = 0;
    } else {
        last  = buf[1];
    }
    /* 保存记录 */
    memcpy(&buf[0], p_billing_mode->usr_id, 16);
    memcpy(&buf[16], &p_billing_mode->usr_balance, 4);
    memcpy(&buf[20], &p_billing_dat->start_time, sizeof(time_t));
    memcpy(&buf[28], &p_billing_dat->start_energy, 4);
    memcpy(&buf[32], &p_billing_dat->used_time, 2);
    memcpy(&buf[34], &p_billing_dat->used_amount, 4);
    memcpy(&buf[38], &p_billing_dat->used_energy, 2);
    memcpy(&buf[40], &p_billing_dat->stop_reason, 2);
    memcpy(&buf[42], &p_billing_dat->now_price, 2);

    last++;
    if (last >= ACP1000_EEPROM_CHARGE_MAX_NUMS) {
        last = 0;
    }
    total++;
    if (total >= ACP1000_EEPROM_CHARGE_MAX_NUMS) {
        total = ACP1000_EEPROM_CHARGE_MAX_NUMS;
    }
    offset =   last * sizeof(buf);
    if(AW_OK != aw_nvram_set(ACP1000_EEPROM_NAME, 5, buf, offset, sizeof(buf))) {
        return AW_ERROR;
    }

    buf[0] = total;
    buf[1] = last;
    if(AW_OK != aw_nvram_set(ACP1000_EEPROM_NAME, 4, buf, 0, 2)) {
        return AW_ERROR;
    }
#endif

    return AW_OK;
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
 * 计费空闲，鉴权成功后，检测余额是否充足，对应设置的金额模式
 */
static role_ret billing_idle_do (struct role **pp_role, void *p_arg)
{
    IDLE_TO_BILLING(p_this, pp_role);
    event_node_tell_all(&p_this->evt_node, BILLING_MODE_GET, &p_this->mode);

    billing_dev_lock(p_this);
    if (p_this->mode.usr_balance == 0){
        if (TRUE == p_this->enough) {
            /* 发送余额不足 */
            p_this->enough = FALSE;
            billing_dev_unlock(p_this);
//            event_node_tell_all(&p_this->evt_node, BILLING_BALANCE, FALSE);
        } else {
            billing_dev_unlock(p_this);
        }
    } else {
        billing_dev_unlock(p_this);
    }

    return AW_OK;
}

/**
 * 计费开始
 */
static role_ret billing_start_do (struct role **pp_role, void *p_arg)
{
    START_TO_BILLING(p_this, pp_role);
    aw_tm_t  tm;
    time_t   now_time;
    /* 获取起始时间 */
    aw_rtc_time_get(p_this->rtc_id, &tm);
    aw_tm_to_time(&tm, &now_time);

    /* 获取充电模式 */
    event_node_tell_all(&p_this->evt_node, BILLING_MODE_GET, &p_this->mode);

    billing_dev_lock(p_this);
    p_this->dat.used_time   = 0;
    p_this->dat.used_amount = 0;
    p_this->dat.used_energy = 0;
    p_this->dat.start_energy= p_this->dat.now_energy;
    p_this->dat.usr_balance = p_this->mode.usr_balance; /* 获取用户余额 */
    p_this->dat.start_time  = now_time;
    p_this->dat.stop_reason = AW_MB_DGUS_CHARGE_NONE;
    billing_dev_unlock(p_this);

    /* 计费开始 */
    event_node_tell(&p_this->evt_node, BILLING_START, TRUE);
    AW_SEMB_INIT(p_this->p_pile_sem->charge_gun_sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
    return AW_OK;
}

/**
 * 计费中
 */
static role_ret billing_ing_do (struct role **pp_role, void *p_arg)
{
    ING_TO_BILLING(p_this, pp_role);
    time_t  now_time;
    aw_tm_t tm;
    uint16_t price /* 单位0.0001元 每度 */;

    aw_rtc_time_get (p_this->rtc_id, &tm);
    aw_tm_to_time(&tm, &now_time);

    pile_dev_lock(p_this->p_pile);
    price = p_this->p_pile->pile_time.now_price;
    pile_dev_unlock(p_this->p_pile);

    billing_dev_lock(p_this);
#if ACP1000_ENERGY_AUTO_ADD
    p_this->dat.used_energy += 10;
    p_this->dat.now_price   = 10000;
#else
    p_this->dat.used_energy = (p_this->dat.now_energy - p_this->dat.start_energy);
    p_this->dat.now_price   = price;
#endif
    p_this->dat.used_time   = (now_time - p_this->dat.start_time) / 60;
    p_this->dat.used_amount =  (p_this->dat.used_energy * p_this->dat.now_price) / 10000;
    billing_dev_unlock(p_this);

#if ACP1000_BILING_MONITOR
    billing_mode_monitor(p_this);
#endif

    event_node_tell_all(&p_this->evt_node, BILLING_ING, &p_this->dat);
    if (p_this->dat.stop_reason != AW_MB_DGUS_CHARGE_NONE) {
        /* 计费单元终止充电， 发起计费单元终止计费事件  */
        event_node_tell_all(&p_this->evt_node, BILLING_STOP, p_this->dat.stop_reason);
    }
    return AW_OK;
}

/**
 * 计费结束
 */
static role_ret billing_end_do (struct role **pp_role, void *p_arg)
{
    END_TO_BILLING(p_this, pp_role);
    aw_err_t ret;

    /*  此处保存充电信息   */
    billing_info_eeprom_save(&p_this->dat, &p_this->mode);

#if ACP1000_HUB4G_BILLING
    event_node_tell_all(&p_this->evt_node, BILLING_ENDING, TRUE);
    // todo 等待结算结果下发
    ret = AW_SEMB_TAKE(p_this->p_pile_sem->hub4g_billing_sem,
                       aw_ms_to_ticks(ACP1000_BILLING_TIMEOUT));
    AW_SEMB_TAKE(p_this->p_pile_sem->charge_gun_sem, AW_SEM_WAIT_FOREVER);
    if (ret == -ETIME) {

        event_node_tell_all(&p_this->evt_node, BILLING_END, FALSE);
        return AW_ERROR;
    }
#endif
    /* 发起结算结果，TRUE为结算成功，FALSE为结算异常  */
    event_node_tell_all(&p_this->evt_node, BILLING_END, TRUE);

    return AW_OK;
}

/* ========================================================================= */
static void event_driver(struct event_node *p_evt, event_t event, void *p_arg)
{
    EVT_TO_BILLING(p_this, p_evt);
    static role_t billing_idle  = {billing_idle_do};
    static role_t billing_start = {billing_start_do};
    static role_t billing_ing   = {billing_ing_do};
    static role_t billing_end   = {billing_end_do};

    uint32_t arg  = (uint32_t)p_arg;
    ammeter_dat_t *p_ammeter_dat = NULL;

    switch (event) {

    case CARD_AUTH_SUS:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_billing_idle  = &billing_idle;
        p_this->p_billing_start = NULL;
        p_this->p_billing_ing   = NULL;
        p_this->p_billing_end   = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        billing_dev_lock(p_this);
        p_this->enough = TRUE;
        billing_dev_unlock(p_this);
        break;

    case CHARGE_PIEL_START:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_billing_idle  = NULL;
        p_this->p_billing_start = &billing_start;
        p_this->p_billing_ing   = NULL;
        p_this->p_billing_end   = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case BILLING_START:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_billing_idle  = NULL;
        p_this->p_billing_start = NULL;
        p_this->p_billing_ing   = &billing_ing;
        p_this->p_billing_end   = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CHARGE_PILE_STOP:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_billing_idle  = NULL;
        p_this->p_billing_start = NULL;
        p_this->p_billing_ing   = NULL;
        p_this->p_billing_end   = &billing_end;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    /* 接收电表的数据  */
    case AMETER_MEASURE:
        p_ammeter_dat = (ammeter_dat_t *)p_arg;
        billing_dev_lock(p_this);
        p_this->dat.now_energy = p_ammeter_dat->now_energy;
        billing_dev_unlock(p_this);
        break;

    case ERR_CHAGER:
        billing_dev_lock(p_this);
        p_this->dat.stop_reason = arg;
        billing_dev_unlock(p_this);
        break;

    case BILLING_END:
    case CARD_AUTH_FAIL:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_billing_idle  = NULL;
        p_this->p_billing_start = NULL;
        p_this->p_billing_ing   = NULL;
        p_this->p_billing_end   = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
       break;

    default:break;
    }

}



/* ========================================================================= */
#define BILLING_TASK_PRIO       4
#define BILLING_TACK_SIZE       2048
#define BILLING_DETECT_PERIOD   100
AW_TASK_DECL_STATIC(billing_task, BILLING_TACK_SIZE);

/**
 * 卡探测任务
 */
static void billing_task_entry (void *p_arg)
{
    billing_t *p_this = (billing_t *)p_arg;
    role_t     *p_role[4];

    while (1) {

        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        memcpy(&p_role[0], &p_this->p_billing_idle, sizeof(role_t*) * 4);
        AW_MUTEX_UNLOCK(p_this->role_lock);

        if (NULL != p_role[0]) {
            p_this->player.pfn_play(&p_this->p_billing_idle, NULL);

        } else if (NULL != p_role[1]) {
            p_this->player.pfn_play(&p_this->p_billing_start, NULL);

        } else if (NULL != p_role[2]) {
            p_this->player.pfn_play(&p_this->p_billing_ing, NULL);

        } else if (NULL != p_role[3]) {
            p_this->player.pfn_play(&p_this->p_billing_end, NULL);
        }
        aw_mdelay(BILLING_DETECT_PERIOD);
    }
}

void billing_task_startup (billing_t *p_this)
{
    AW_TASK_INIT(billing_task,           /* 任务实体 */
                 "billing_task",            /* 任务名字 */
                 BILLING_TASK_PRIO,      /* 任务优先级 */
                 BILLING_TACK_SIZE,      /* 任务堆栈大小 */
                 billing_task_entry,     /* 任务入口函数 */
                 (void *)p_this);        /* 任务入口参数 */
    /* 启动任务 */
    AW_TASK_STARTUP(billing_task);
}

