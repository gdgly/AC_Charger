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
 * \brief 串口屏实例声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#ifndef __DUGS_H
#define __DUGS_H

#include "player.h"
#include "aw_sem.h"
#include "event_node.h"
#include "mb/aw_mb_dgus_regmap.h"

/**
 * modbus协议通信信息
 */
typedef struct modbus_info {
    uint32_t  addr;  /* modbus地址 */
    uint32_t  com;   /* modbus使用串口号 */
    uint32_t  baud;  /* 使用波特率 */
    uint32_t  par;   /* 使用校验方式*/
}modbus_info_t;


/**
 * 串口屏实例声明
 */
typedef struct dugs {
    struct aw_mb_dgus_reg_map  super;      /* 串口屏数据 */
    player_t          player;              /* 扮演者 */
    event_node_t      evt_node;            /* 事件接口 */

    role_t           *p_dugs_display;      /* 可扮演的角色 - 显示器 */
    role_t           *p_dugs_billing_ctrl; /* 可扮演的角色  - 计费控制器 */
    role_t           *p_dugs_charge_ctrl;  /* 可扮演的角色  - 充电控制器 */
    role_t           *p_dugs_settings;     /* 可扮演的角色  - 参数设置器 */
    AW_MUTEX_DECL(role_lock);              /**< \brief 角色锁  */

    uint16_t          stop_reason;         /* 停止充电原因 */
}dugs_t;
/**
 *  \brief 串口屏初始化
 *  param [in]   p_this        : 串口屏实例
 *  param [in]   p_dgus_info   : dugs串口屏配置信息
 *  */
void dugs_inst_init(dugs_t *p_this, modbus_info_t *p_dugs_info);

/** \brief 串口屏读写操作上锁  */
aw_static_inline void dugs_lock(dugs_t *p_this)
{
    aw_mb_dugs_reg_map_lock(&(p_this->super));
}

/** \brief 串口屏读写操作解锁  */
aw_static_inline void dugs_unlock(dugs_t *p_this)
{
    aw_mb_dugs_reg_map_unlock(&(p_this->super));
}


#if 1
/** \brief 设置串口屏  */
#define dugs_super_set(p_this, state_name, state) \
                    do {                                    \
                           dugs_lock(p_this); \
                           (p_this)->super.state_name = state;  \
                           dugs_unlock(p_this);\
                       }while (0)

/** \brief 设置串口屏  */
#define dugs_super_unsafe_set(p_this, state_name, state) \
                    do {                                    \
                           (p_this)->super.state_name = state; \
                       }while (0)

/** \brief 获取串口屏  */
#define dugs_super_get(p_this, state_name, state)  \
                    do {                                    \
                            dugs_lock(p_this); \
                            state = (p_this)->super.state_name;  \
                            dugs_unlock(p_this);\
                        }while (0)

/** \brief 获取串口屏  */
#define dugs_super_unsafe_get(p_this, state_name, state)  \
                    do {                                    \
                            state = (p_this)->super.state_name;  \
                        }while (0)

#endif



#endif
