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
 * \brief ���ʵ������
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
 * �������
 */
typedef struct ammeter_dat {
    uint32_t now_energy;  /* ��ǰ���� ����λ0.01 �� */
    int32_t now_vol;      /* ��ǰ��ѹ����λ0.1V   */
    uint32_t now_curr;    /* ��ǰ����. ��λ0.001A */
}ammeter_dat_t;


/**
 * �Ʒѵ�Ԫʵ������
 */
typedef struct ammeter {
    player_t          player;              /* ������ */
    event_node_t      evt_node;            /* �¼��ӿ� */
    ammeter_dat_t     dat;                 /* ��Ƭ���� */
    aw_ammeter_t      *p_ammeter_driver;   /* ��������豸 */

    role_t           *p_ammeter_vol;       /* �ɰ��ݵĽ�ɫ  - ��ѹ����� */
    role_t           *p_ammeter_curr;      /* �ɰ��ݵĽ�ɫ  - ��������� */
    AW_MUTEX_DECL(role_lock);              /**< \brief ��ɫ��  */
    AW_MUTEX_DECL(dev_lock);               /**< \brief �豸��  */

    uint32_t          max_curr;           /* �������������� ����λ0.01A�� */
    uint8_t           vol_state;          /* ��ѹ״̬��0���� , 1; Ƿѹ�� 2�� ��ѹ��  */
    uint8_t           curr_state;         /* �����Ƿ��쳣�� 0�������� 1�� ������С �� 2�� ����  */
    uint32_t          vol_step;           /* �ڲ�״̬�� */
    aw_tick_t         start_ticks;        /* �ڲ����� */
    bool_t            abnormal_state;     /* ���������� , FALSE: ������TRUE: �쳣*/
    bool_t            enable_curr_check;  /* �Ƿ�ʹ�ܵ������� */
}ammeter_t;

#define AMMETER_VOL_STATE_NORMAL    0     /* ��ѹ���� */
#define AMMETER_VOL_STATE_UNDER     1     /* Ƿѹ */
#define AMMETER_VOL_STATE_OVER      2     /* ��ѹ */

#define AMMETER_CURR_STATE_NORMAL    0     /* �������� */
#define AMMETER_CURR_STATE_UNDER     1     /* ������С */
#define AMMETER_CURR_STATE_OVER      2     /* ���� */


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
