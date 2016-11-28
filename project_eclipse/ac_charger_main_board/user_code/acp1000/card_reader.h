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
 * \brief 读卡器实例声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */


#ifndef __CARD_READER_H
#define __CARD_READER_H

#include "player.h"
#include "aw_sem.h"
#include "event_node.h"
#include "pile.h"
#include "cardreader/aw_iccreader.h"
/**
 * 读卡器实例数据
 */
typedef struct card_dat {
    aw_iccreader_t     *p_card_driver;
    uint8_t id[4];                   /* 上一次卡的ID （超时或结算后清除）*/
    uint8_t key[6];                  /* 上一次卡的密钥  （超时或结算后清除）*/
    uint8_t blk_dat[3 * 16];         /* 上一次卡的扇区数据 （超时或结算后清除）*/

    bool_t  allow_charge;            /* 鉴权结果  TRUE: 允许充电，FALSE: 不允许充电*/
    bool_t  key_vaild;               /* 卡密钥是否从非易失性设备中读取成成功 */
    uint8_t *p_des_key;              /* DES密钥 */
}card_dat_t;

/**
 * 读卡器实例声明
 */
typedef struct card_reader {
    player_t          player;    /* 扮演者 */
    event_node_t      evt_node;  /* 事件接口 */

    role_t           *p_card_auth; /* 可扮演的角色 - 鉴权器 */
    role_t           *p_card_lock; /* 可扮演的角色  - 解锁器 */
    role_t           *p_card_reco; /* 可扮演的角色  - 卡片识别器 */
    AW_MUTEX_DECL(role_lock);      /**< \brief 角色锁  */

    card_dat_t        dat;         /* 卡片数据 */
    pile_sem_t       *p_pile_sem;  /* 信号量同步 */

    bool_t            pile_order;  /* 桩预约状态 （必须在无预约情况下发送鉴权成功事件，但仍进行鉴权）*/
    AW_MUTEX_DECL(dev_lock);      /**< \brief 角色锁  */

}card_reader_t;

static inline void card_reader_dev_lock(card_reader_t *p_this)
{
    AW_MUTEX_LOCK(p_this->dev_lock, AW_SEM_WAIT_FOREVER);
}

static inline void card_reader_dev_unlock(card_reader_t *p_this)
{
    AW_MUTEX_UNLOCK(p_this->dev_lock);
}

/**
 * 读卡器实例初始化
 */
void card_reader_inst_init (card_reader_t                 *p_this,
                            aw_iccreader_t                *p_card_driver,
                            const aw_iccreader_transfer_t *p_card_transfer,
                            pile_t                        *p_pile);

void card_reader_task_startup (card_reader_t *p_this);

#define CARD_RECO_DIFF   0  /* 不相同的卡片 */
#define CARD_RECO_SAME   1  /* 相同的卡片 */
#define CARD_RECO_INVAID 2  /* 无效卡片 */

#endif
