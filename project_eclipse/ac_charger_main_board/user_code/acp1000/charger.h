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
 * \brief 充电机声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */


#ifndef __CHARGER_H
#define __CHARGER_H

#include "player.h"
#include "aw_sem.h"
#include "event_node.h"
#include "ac_charge_prj_cfg.h"
#include "aw_delayed_work.h"
#include "pile.h"
/**
 * 充电数据
 */
typedef struct charge_dat {
    uint32_t  max_curr;    /* 最大电流 */
    uint32_t  curr_pwm;    /* CP PWM编号 */
    uint8_t   tp1_vol;      /* CP电压 */
    uint8_t   ac_enable;   /* AC输出情况，TRUE: 输出，FALSE: 没有输出 */
    aw_tick_t start_ticks; /* 超时检测ticks */
    uint32_t  exit_code;   /* 充电退出代码 \ref grp_charge_stop_reason */
    bool_t    exit_now;    /* 是否需要马上退出（ 由外部紧急异常触发） */
    bool_t    allow_charge; /* 充电机判断是否可以充电 */
    uint32_t  pile_alarm;   /* 桩告警情况 */
}charge_dat_t;


/**
 * 充电控制器
 */
typedef struct charge {
    player_t          player;    /* 扮演者 */
    event_node_t      evt_node;  /* 事件接口 */

    role_t           *p_charge_idle;  /* 可扮演的角色 - 充电空闲期 */
    role_t           *p_charge_allow; /* 可扮演的角色  - 允许充电裁定器 */
    role_t           *p_charge_start; /* 可扮演的角色  - 启动充电裁定器 */
    role_t           *p_charge_ing;   /* 可扮演的角色  - 启动中控制器 */
    role_t           *p_charge_stop;  /* 可扮演的角色  - 充电停止控制器 */
    role_t           *p_charge_err;   /* 可扮演的角色  - 充电异常控制器 */
    AW_MUTEX_DECL(role_lock);         /**< \brief 角色锁  */

    charge_dat_t      dat;            /* 卡片数据 */
    AW_MUTEX_DECL(dev_lock);          /**< \brief 设备锁  */

    pile_sem_t       *p_pile_sem;     /* 信号量同步 */

#if ACP1000_AC1_ERR_DETECT
    struct aw_delayed_work  ac_detect_dk;
#endif

}charger_t;

void charger_inst_init(charger_t *p_this, pile_sem_t *p_pile_sem);
void charger_task_startup (charger_t *p_this);

static inline void charger_dev_lock(charger_t *p_this)
{
    AW_MUTEX_LOCK(p_this->dev_lock, AW_SEM_WAIT_FOREVER);
}

static inline void charger_dev_unlock(charger_t *p_this)
{
    AW_MUTEX_UNLOCK(p_this->dev_lock);
}

#endif
