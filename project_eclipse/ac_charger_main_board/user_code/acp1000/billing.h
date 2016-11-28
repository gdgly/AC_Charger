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
 * \brief �Ʒѵ�Ԫʵ������
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
 * �Ʒ�����
 */
typedef struct billing_dat {
    uint32_t now_energy;    /* ��ǰ���� */

    time_t   start_time;   /* ��ʼʱ�� */
    uint32_t start_energy; /* ��ʼ������ */

    uint16_t used_time;    /* ʹ��ʱ�� ��λ�� ����*/
    uint32_t used_amount;  /* ʹ�ý��  ��λ�� 0.01Ԫ*/
    uint16_t used_energy;  /* ʹ�õ��� ��λ�� 0.01 KW-h */
    uint16_t now_price;    /* ��ǰ��� 0.0001Ԫ /KW-h */
    uint32_t usr_balance;  /* �û���ʼ���  ��λ�� 0.01Ԫ */
    uint16_t stop_reason;  /* �ƷѼ�ؽ�� */
}billing_dat_t;

typedef struct billing_mode {
    uint8_t   mode;           /* �Ʒ�ģʽ */
    uint16_t  charge_amount ; /* �����  0.01Ԫ */
    uint16_t  charge_energy ; /* ������ 0.01 KW-h */
    uint16_t  charge_time;    /* ���ʱ�� 0. ���� */
    uint32_t  usr_balance;    /* �û���ʼ���  ��λ�� 0.01Ԫ */
    uint8_t   usr_id[16];     /* ��ǰ����û�ID */
}billing_mode_t;

/**
 * �Ʒѵ�Ԫʵ������
 */
typedef struct billing {
    player_t          player;              /* ������ */
    event_node_t      evt_node;            /* �¼��ӿ� */

    role_t           *p_billing_idle;      /* �ɰ��ݵĽ�ɫ  - ������ */
    role_t           *p_billing_start;     /* �ɰ��ݵĽ�ɫ  - �Ʒ������� */
    role_t           *p_billing_ing;       /* �ɰ��ݵĽ�ɫ  - �Ʒ����� */
    role_t           *p_billing_end;       /* �ɰ��ݵĽ�ɫ  - �Ʒѽ����� */
    AW_MUTEX_DECL(role_lock);              /**< \brief ��ɫ��  */

    billing_dat_t     dat;                /* �Ʒ����� */
    billing_mode_t    mode;               /* �Ʒ�ģʽ */

    uint8_t           rtc_id;             /* ʱ��RTCID */
    pile_sem_t       *p_pile_sem;          /* �ź���ͬ�� */
    pile_t           *p_pile;              /* ׮������ */

    bool_t            enough;              /* ��������� */
    AW_MUTEX_DECL(dev_lock);               /**< \brief �豸��  */
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
