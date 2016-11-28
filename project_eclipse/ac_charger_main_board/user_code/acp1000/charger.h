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
 * \brief ��������
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
 * �������
 */
typedef struct charge_dat {
    uint32_t  max_curr;    /* ������ */
    uint32_t  curr_pwm;    /* CP PWM��� */
    uint8_t   tp1_vol;      /* CP��ѹ */
    uint8_t   ac_enable;   /* AC��������TRUE: �����FALSE: û����� */
    aw_tick_t start_ticks; /* ��ʱ���ticks */
    uint32_t  exit_code;   /* ����˳����� \ref grp_charge_stop_reason */
    bool_t    exit_now;    /* �Ƿ���Ҫ�����˳��� ���ⲿ�����쳣������ */
    bool_t    allow_charge; /* �����ж��Ƿ���Գ�� */
    uint32_t  pile_alarm;   /* ׮�澯��� */
}charge_dat_t;


/**
 * ��������
 */
typedef struct charge {
    player_t          player;    /* ������ */
    event_node_t      evt_node;  /* �¼��ӿ� */

    role_t           *p_charge_idle;  /* �ɰ��ݵĽ�ɫ - �������� */
    role_t           *p_charge_allow; /* �ɰ��ݵĽ�ɫ  - ������ö��� */
    role_t           *p_charge_start; /* �ɰ��ݵĽ�ɫ  - �������ö��� */
    role_t           *p_charge_ing;   /* �ɰ��ݵĽ�ɫ  - �����п����� */
    role_t           *p_charge_stop;  /* �ɰ��ݵĽ�ɫ  - ���ֹͣ������ */
    role_t           *p_charge_err;   /* �ɰ��ݵĽ�ɫ  - ����쳣������ */
    AW_MUTEX_DECL(role_lock);         /**< \brief ��ɫ��  */

    charge_dat_t      dat;            /* ��Ƭ���� */
    AW_MUTEX_DECL(dev_lock);          /**< \brief �豸��  */

    pile_sem_t       *p_pile_sem;     /* �ź���ͬ�� */

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
