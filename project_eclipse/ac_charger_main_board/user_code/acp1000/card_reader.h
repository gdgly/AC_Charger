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
 * \brief ������ʵ������
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
 * ������ʵ������
 */
typedef struct card_dat {
    aw_iccreader_t     *p_card_driver;
    uint8_t id[4];                   /* ��һ�ο���ID ����ʱ�����������*/
    uint8_t key[6];                  /* ��һ�ο�����Կ  ����ʱ�����������*/
    uint8_t blk_dat[3 * 16];         /* ��һ�ο����������� ����ʱ�����������*/

    bool_t  allow_charge;            /* ��Ȩ���  TRUE: �����磬FALSE: ��������*/
    bool_t  key_vaild;               /* ����Կ�Ƿ�ӷ���ʧ���豸�ж�ȡ�ɳɹ� */
    uint8_t *p_des_key;              /* DES��Կ */
}card_dat_t;

/**
 * ������ʵ������
 */
typedef struct card_reader {
    player_t          player;    /* ������ */
    event_node_t      evt_node;  /* �¼��ӿ� */

    role_t           *p_card_auth; /* �ɰ��ݵĽ�ɫ - ��Ȩ�� */
    role_t           *p_card_lock; /* �ɰ��ݵĽ�ɫ  - ������ */
    role_t           *p_card_reco; /* �ɰ��ݵĽ�ɫ  - ��Ƭʶ���� */
    AW_MUTEX_DECL(role_lock);      /**< \brief ��ɫ��  */

    card_dat_t        dat;         /* ��Ƭ���� */
    pile_sem_t       *p_pile_sem;  /* �ź���ͬ�� */

    bool_t            pile_order;  /* ׮ԤԼ״̬ ����������ԤԼ����·��ͼ�Ȩ�ɹ��¼������Խ��м�Ȩ��*/
    AW_MUTEX_DECL(dev_lock);      /**< \brief ��ɫ��  */

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
 * ������ʵ����ʼ��
 */
void card_reader_inst_init (card_reader_t                 *p_this,
                            aw_iccreader_t                *p_card_driver,
                            const aw_iccreader_transfer_t *p_card_transfer,
                            pile_t                        *p_pile);

void card_reader_task_startup (card_reader_t *p_this);

#define CARD_RECO_DIFF   0  /* ����ͬ�Ŀ�Ƭ */
#define CARD_RECO_SAME   1  /* ��ͬ�Ŀ�Ƭ */
#define CARD_RECO_INVAID 2  /* ��Ч��Ƭ */

#endif
