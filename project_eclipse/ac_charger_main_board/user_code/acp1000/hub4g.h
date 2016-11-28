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
 * \brief 集中器实例声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#ifndef __HUB4G_H
#define __HUB4G_H
#include "apollo.h"
#include "aw_time.h"
#include "player.h"
#include "aw_sem.h"
#include "event_node.h"
#include "pile.h"
#include "dugs.h"
#include "mb/ac_modbus_reg_map.h"
/**
 * 集中器实例声明
 */
typedef struct hub4g {
    struct modbus_reg_map  super;      /* 串口屏数据 */
    player_t          player;              /* 扮演者 */
    event_node_t      evt_node;            /* 事件接口 */

    role_t           *p_hub4g_auth_usr;     /* 可扮演的角色  - 鉴权用户余额控制器 */
    role_t           *p_hub4g_charge_ctrl;  /* 可扮演的角色  - 充电控制器 */
    role_t           *p_hub4g_billing;      /* 可扮演的角色  - 结算控制器 */
    role_t           *p_hub4g_settings;     /* 可扮演的角色  - 参数设置器 */
    role_t           *p_hub4g_auth_key;     /* 可扮演的角色  - 密钥下发控制器 */
    role_t           *p_hub4g_allow_charge; /* 可扮演的角色  - 密钥下发控制器 */
    role_t           *p_hub4g_unlock;       /* 可扮演的角色  - 屏幕解锁器 */

    AW_MUTEX_DECL(role_lock);               /**< \brief 角色锁  */

    pile_sem_t       *p_pile_sem;           /* 信号量同步 */
    uint32_t          pile_alarm;
}hub4g_t;

/** \brief 串口屏读写操作上锁  */
aw_static_inline void hub4g_dev_lock(hub4g_t *p_this)
{
    modbus_reg_map_lock(&(p_this->super));
}

/** \brief 串口屏读写操作解锁  */
aw_static_inline void hub4g_dev_unlock(hub4g_t *p_this)
{
    modbus_reg_map_unlock(&(p_this->super));
}



/**
 * 集中器实例初始化
 */
void hub4g_inst_init(hub4g_t      *p_hub4g,
                    modbus_info_t *p_mb_info,
                    pile_sem_t    *p_pile_sem,
                    bool_t         key_vaild);

#endif
