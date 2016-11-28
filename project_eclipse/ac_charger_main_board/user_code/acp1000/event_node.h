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
 * \brief 事件实例声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */
#ifndef EVENT_NODE_H
#define EVENT_NODE_H

#include "apollo.h"
#include "aw_sem.h"

/* 事件 */
typedef enum event
{
   CARD_AUTH_SUS,  /* 鉴权成功事件 */
   CARD_AUTH_ING,  /* 鉴权中事件 */
   CARD_AUTH_FAIL, /* 鉴权中失败 */
   CARD_WAIT_KEY,  /* 等待密钥信号 */
   CARD_SWING_OK,  /* 读卡数据成功 */
   CARD_AUTH_ID,   /* 卡ID */
   CARD_AUTH_SUS_ORDER,  /* 鉴权成功但已被预约事件 */
   CARD_ADMIN_MODE,     /* 管理员模式  1：进入管理员模式 0: 退出管理员模式*/
   SCREEN_UNLOCK,  /* 命名解锁事件 */

   CHARGE_MAN_START,  /* 人为启动充电事件 */
   CHARGE_MAN_STOP,   /* 人为停止充电事件 */
   CHARGE_BG_STOP,    /* 后台停止充电事件 */

   CHARGE_PIEL_WAIT,   /* 等待汽车充电就绪事件 */
   CHARGE_PIEL_START,  /* 机身启动充电事件 */
   CHARGE_PILE_STOP,   /* 机身启动充电事件 */
   CHARGE_FULL,        /* 汽车充电充满 */
   CHARGE_AC_STATE,    /* 接触器状态 */

   GUN_INSERT,          /* 枪插上 */
   GUN_EXTRACT,         /* 枪拔出 */

   BILLING_START,       /* 计费开始 */
   BILLING_ING,         /* 计费中 */
   BILLING_STOP,        /* 计费停止事件 */
   BILLING_END,         /* 计费结束 */
   BILLING_ENDING,      /* 计费结束中 */

   BILLING_MODE_GET,    /* 后期充电的模式和数据 */
   BILLING_BALANCE,     /* 余额情况 */

   AMETER_MEASURE,      /* 电表测量完成 */

   PILE_ALARM,          /* 桩警报数据 */
   PILE_TIME,           /* 时间数据 */
   PILE_TEMP,           /* 温度数据 */
   PILE_DUGS_INFO,      /* 桩信息数据(管理员界面) */

   HUB4G_AUTH_KEY,      /* 集中器下发密钥 */
   HUB4G_AUTH_USR,      /* 集中器鉴权中下发余额 */
   HUB4G_ALLOW_CHARGE,  /* 允许充电事件 */
   HUB4G_BILLING,       /* 结算事件 */
   HUB4G_PILE_ORDER,    /* 桩预约情况 */
   HUB4G_USR_INFO,      /* 集中器下发用户ID余额数据  */
   HUB4G_PILE_ID,       /* 桩ID */
   HUB4G_PRICE,         /* 桩ID */
   HUB4G_UPGRADE,       /* 桩升级 */

   DUGS_HUB4G_ADDR,     /* 集中器地址 */
   DUGS_PRICE_GET,      /* 获取电价 */
   /*---------------------------------------------------*/
   ERR_CARD_READER,     /* 读卡器通讯异常 */
   ERR_AMMETER,         /* 电表通讯异常 */
   ERR_CAR_READY,       /* 汽车就绪异常 */
   ERR_CHAGER,          /* 一般异常退出 */
   ERR_AMMETER_VOL,     /* 电压情况 */
   ERR_AMMETER_CURR,    /* 电流情况  */
   ERR_SCRAM,           /* 紧急开关情况  */
   ERR_LIGHT,           /* 防雷器异常情况 */
   ERR_AC,              /* AC母排开关异常情况 */
   ERR_TEMP,            /* 温度异常情况， 0： 正常； 1： 过高； 2： 过低 */
   ERR_PILE_GUN_CONN,   /* 枪接触异常情况  */
   ERR_PILE_GUN_LOCK,   /* 枪锁异常情况 */
   ERR_HUB4G,           /* 4G通信情况， 0： 正常； 1：异常 */
   ERR_DUGS,            /* 串口屏异常情况， 0： 正常； 1：异常 */
   ERR_HUB4G_COMM,      /* 集中器通信异常 */
}event_t;

struct event_manager;

typedef struct event_node
{
    AW_MUTEX_DECL(lock);
    struct event_node *next;
    struct event_manager *parent;
    void (*pfunc_event)(struct event_node *p_this, event_t event, void *p_arg);
}event_node_t;

void event_node_init( struct event_node *p_this );
void event_node_lock( struct event_node *p_this );
void event_node_unlock( struct event_node *p_this );
void event_node_tell( struct event_node *p_this, event_t event, void *p_arg);
void event_node_tell_all( struct event_node *p_this, event_t event, void *p_arg);
void event_node_destroy( struct event_node *p_this );

/*  */
typedef struct event_manager
{
    struct event_node *p_event_nodes;
    AW_MUTEX_DECL(lock);
}event_manager_t;

void event_manager_init( struct event_manager *p_this);
void event_manager_add( struct event_manager *p_this, struct event_node *p_newone);
void event_manager_tell_all( struct event_manager *p_this, event_t event, void *p_arg);
void event_manager_destroy( struct event_manager *p_this);


#endif /* EVENT_NODE_H */
