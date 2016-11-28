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
 * \brief 计费单元实例声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */


#ifndef __BILLING_H
#define __BILLING_H


#include "player.h"
#include "aw_sem.h"
#include "event_node.h"
#include "aw_time.h"
#include "pile.h"

/**
 * 计费数据
 */
typedef struct billing_dat {
    uint32_t now_energy;    /* 当前电量 */

    time_t   start_time;   /* 起始时间 */
    uint32_t start_energy; /* 开始充电电量 */

    uint16_t used_time;    /* 使用时间 单位： 分钟*/
    uint32_t used_amount;  /* 使用金额  单位： 0.01元*/
    uint16_t used_energy;  /* 使用电量 单位： 0.01 KW-h */
    uint16_t now_price;    /* 当前电价 0.0001元 /KW-h */
    uint32_t usr_balance;  /* 用户初始余额  单位： 0.01元 */
    uint16_t stop_reason;  /* 计费监控结果 */
}billing_dat_t;

typedef struct billing_mode {
    uint8_t   mode;           /* 计费模式 */
    uint16_t  charge_amount ; /* 充电金额  0.01元 */
    uint16_t  charge_energy ; /* 充电电量 0.01 KW-h */
    uint16_t  charge_time;    /* 充电时间 0. 分钟 */
    uint32_t  usr_balance;    /* 用户初始余额  单位： 0.01元 */
    uint8_t   usr_id[16];     /* 当前充电用户ID */
}billing_mode_t;

/**
 * 计费单元实例声明
 */
typedef struct billing {
    player_t          player;              /* 扮演者 */
    event_node_t      evt_node;            /* 事件接口 */

    role_t           *p_billing_idle;      /* 可扮演的角色  - 空闲器 */
    role_t           *p_billing_start;     /* 可扮演的角色  - 计费启动器 */
    role_t           *p_billing_ing;       /* 可扮演的角色  - 计费中器 */
    role_t           *p_billing_end;       /* 可扮演的角色  - 计费结算器 */
    AW_MUTEX_DECL(role_lock);              /**< \brief 角色锁  */

    billing_dat_t     dat;                /* 计费数据 */
    billing_mode_t    mode;               /* 计费模式 */

    uint8_t           rtc_id;             /* 时间RTCID */
    pile_sem_t       *p_pile_sem;          /* 信号量同步 */
    pile_t           *p_pile;              /* 桩的数据 */

    bool_t            enough;              /* 余额充足情况 */
    AW_MUTEX_DECL(dev_lock);               /**< \brief 设备锁  */
}billing_t;


static inline void billing_dev_lock(billing_t *p_this)
{
    AW_MUTEX_LOCK(p_this->dev_lock, AW_SEM_WAIT_FOREVER);
}

static inline void billing_dev_unlock(billing_t *p_this)
{
    AW_MUTEX_UNLOCK(p_this->dev_lock);
}


void billing_inst_init(billing_t  *p_this,
                       uint8_t     rtc_id,
                       pile_sem_t *p_pile_sem,
                       pile_t     *p_pile);
void billing_task_startup (billing_t *p_this);

#endif
