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
 * \brief 桩实例声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#ifndef __PILE_H
#define __PILE_H

#include "aw_sem.h"
#include "event_node.h"
#include "aw_time.h"

/**
 * 时间与电价
 */
typedef struct pile_time_price {
    aw_tm_t  tm;        /* 桩目前RTC时间 */
    uint16_t now_price; /* 桩目前时间下的电价 ， 单位0.0001元每度 */
}pile_time_price_t;


/**
 * 整桩告警情况
 */
typedef struct pile_alarm {
    uint32_t alarm_mask;   /* 告警掩码 0：整桩无告警 \ref grp_pile_alarm */
}pile_alarm_t;

/**
 * 整桩数据情况
 */
typedef struct pile_dat{
    bool_t   charge_state; /* 是否充电 */
    bool_t   gun_state;    /* 枪是否与汽车连上*/
    bool_t   scram_state;  /* 是否紧急开关动作 */
    bool_t   light_state;  /* 是否防雷器异常  */
    bool_t   auth_state;   /* 鉴权有效是否 TRUE: 鉴权有效， FALSE： 鉴权无效 */
    bool_t   gun_lock;     /* 装上的枪的锁状态 */

    uint8_t  bg_state;     /* 后台通信状态（bit1: 4G通信状态； bit2: 集中器通信情况）*/
    uint8_t  hub4g_addr;   /* 集中器通信地址 */
    uint32_t input_vol;    /* 桩输入电压， 单位0.1V */
    uint32_t input_curr;   /* 桩输入电流   单位0.001A*/
    time_t   start_time;   /* 启动时间 */
    uint32_t run_time;     /* 运行时间，单位分钟 */
    uint16_t err_cnt;      /* 异常计数 */
    uint16_t charge_cnt;   /* 充电次数 */
    int16_t  temp;         /* 桩内温度 ，单位度*/
    bool_t   charge_ac_state;

    uint32_t mcu_uid[4];   /* 芯片ID号 */

}pile_dat_t;

/**
 * 桩内置信号量
 */
typedef struct pile_sem {
    AW_SEMB_DECL(hub4g_key_sem);     /**< key接收等待锁  */
    AW_SEMB_DECL(hub4g_auth_sem);    /**< 鉴权等待锁  */
    AW_SEMB_DECL(hub4g_cctrl_sem);   /**< 允许充电等待锁  */
    AW_SEMB_DECL(hub4g_billing_sem); /**< 结算等待锁  （用户结算）*/
    AW_SEMB_DECL(charge_gun_sem);    /**< 拔枪等待锁(用户结算)  */
}pile_sem_t;

/**
 * 整桩数据
 */
typedef struct pile{
    event_node_t  evt_node;            /* 事件接口 */
    AW_MUTEX_DECL(dev_lock);          /**< \brief 设备锁  */

    pile_dat_t        pile_dat;
    pile_alarm_t      pile_alarm;
    pile_time_price_t pile_time;

    pile_sem_t        pile_sem;
}pile_t;


/**
 * \brief 充电停止原因
 * \anchor grp_pile_alarm
 * @{
 */
#define PILE_ALARM_NONE            0x00   /**< \brief 无异常    */
#define PILE_ALARM_CARDREADER      0x01   /**< \brief 读卡通信异常    */
#define PILE_ALARM_AMMETER         0x02   /**< \brief 电表通信异常    */
#define PILE_ALARM_LCD             0x04   /**< \brief 串口屏通信异常    */
#define PILE_ALARM_HUG4G           0x08   /**< \brief 集中器通信异常    */
#define PILE_ALARM_VTP1            0x10   /**< \brief 检测VTP1异常    */
#define PILE_ALARM_ELOCK           0x20   /**< \brief 电子锁异常    */
#define PILE_ALARM_ACLOCK          0x40   /**< \brief AC母排锁异常    */
#define PILE_ALARM_SCRAM           0x80   /**< \brief 检测到紧急开关动作    */
#define PILE_ALARM_CURR            0x100  /**< \brief 检测到电流异常    */
#define PILE_ALARM_OVERVOL         0x200  /**< \brief 过压异常    */
#define PILE_ALARM_UNDERVOL        0x400  /**< \brief 欠压异常    */
#define PILE_ALARM_LIGHT           0x1000  /**< \brief 防雷器异常    */
#define PILE_ALARM_TEMP            0x2000  /**< \brief 温度异常    */
#define PILE_ALARM_EEPROM          0x4000  /**< \brief 内部EEPROM异常    */
#define PILE_ALARM_HUB4G_COM       0x8000  /**< \brief 集中器通信异常    */

static inline void pile_dev_lock(pile_t *p_this)
{
    AW_MUTEX_LOCK(p_this->dev_lock, AW_SEM_WAIT_FOREVER);
}

static inline void pile_dev_unlock(pile_t *p_this)
{
    AW_MUTEX_UNLOCK(p_this->dev_lock);
}

/**
 *  \brief 充电模块实例初始化
 *  param [in]   p_this        : 整机实例
 *  */
void pile_inst_init(pile_t *p_this);
void pile_task_startup (pile_t *p_this);


#endif
