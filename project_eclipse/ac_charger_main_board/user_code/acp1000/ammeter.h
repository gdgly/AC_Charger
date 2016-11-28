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
 * \brief 电表实例声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#ifndef __AMMETER_H
#define __AMMETER_H

#include "aw_sem.h"
#include "player.h"
#include "event_node.h"
#include "ammeter/aw_ammeter.h"
#include "ammeter.h"
/**
 * 电表数据
 */
typedef struct ammeter_dat {
    uint32_t now_energy;  /* 当前电量 ，单位0.01 度 */
    int32_t now_vol;      /* 当前电压，单位0.1V   */
    uint32_t now_curr;    /* 当前电流. 单位0.001A */
}ammeter_dat_t;


/**
 * 计费单元实例声明
 */
typedef struct ammeter {
    player_t          player;              /* 扮演者 */
    event_node_t      evt_node;            /* 事件接口 */
    ammeter_dat_t     dat;                 /* 卡片数据 */
    aw_ammeter_t      *p_ammeter_driver;   /* 电表驱动设备 */

    role_t           *p_ammeter_vol;       /* 可扮演的角色  - 电压监控器 */
    role_t           *p_ammeter_curr;      /* 可扮演的角色  - 电流监控器 */
    AW_MUTEX_DECL(role_lock);              /**< \brief 角色锁  */
    AW_MUTEX_DECL(dev_lock);               /**< \brief 设备锁  */

    uint32_t          max_curr;           /* 充电机最大输出电流 （单位0.01A） */
    uint8_t           vol_state;          /* 电压状态，0正常 , 1; 欠压； 2： 过压；  */
    uint8_t           curr_state;         /* 电流是否异常： 0：正常； 1： 电流过小 ； 2： 过流  */
    uint32_t          vol_step;           /* 内部状态机 */
    aw_tick_t         start_ticks;        /* 内部变量 */
    bool_t            abnormal_state;     /* 电表运行情况 , FALSE: 正常，TRUE: 异常*/
    bool_t            enable_curr_check;  /* 是否使能电流测量 */
}ammeter_t;

#define AMMETER_VOL_STATE_NORMAL    0     /* 电压正常 */
#define AMMETER_VOL_STATE_UNDER     1     /* 欠压 */
#define AMMETER_VOL_STATE_OVER      2     /* 过压 */

#define AMMETER_CURR_STATE_NORMAL    0     /* 电流正常 */
#define AMMETER_CURR_STATE_UNDER     1     /* 电流过小 */
#define AMMETER_CURR_STATE_OVER      2     /* 过流 */


static inline void ammeter_dev_lock(ammeter_t *p_this)
{
    AW_MUTEX_LOCK(p_this->dev_lock, AW_SEM_WAIT_FOREVER);
}

static inline void ammeter_dev_unlock(ammeter_t *p_this)
{
    AW_MUTEX_UNLOCK(p_this->dev_lock);
}

void ammeter_inst_init(ammeter_t *p_this, aw_ammeter_t *p_ammeter_driver, uint32_t max_curr);
void ammeter_task_startup (ammeter_t *p_this);

#endif
