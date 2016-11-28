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
 * ������ʵ������
 */
typedef struct hub4g {
    struct modbus_reg_map  super;      /* ���������� */
    player_t          player;              /* ������ */
    event_node_t      evt_node;            /* �¼��ӿ� */

    role_t           *p_hub4g_auth_usr;     /* �ɰ��ݵĽ�ɫ  - ��Ȩ�û��������� */
    role_t           *p_hub4g_charge_ctrl;  /* �ɰ��ݵĽ�ɫ  - �������� */
    role_t           *p_hub4g_billing;      /* �ɰ��ݵĽ�ɫ  - ��������� */
    role_t           *p_hub4g_settings;     /* �ɰ��ݵĽ�ɫ  - ���������� */
    role_t           *p_hub4g_auth_key;     /* �ɰ��ݵĽ�ɫ  - ��Կ�·������� */
    role_t           *p_hub4g_allow_charge; /* �ɰ��ݵĽ�ɫ  - ��Կ�·������� */
    role_t           *p_hub4g_unlock;       /* �ɰ��ݵĽ�ɫ  - ��Ļ������ */

    AW_MUTEX_DECL(role_lock);               /**< \brief ��ɫ��  */

    pile_sem_t       *p_pile_sem;           /* �ź���ͬ�� */
    uint32_t          pile_alarm;
}hub4g_t;

/** \brief ��������д��������  */
aw_static_inline void hub4g_dev_lock(hub4g_t *p_this)
{
    modbus_reg_map_lock(&(p_this->super));
}

/** \brief ��������д��������  */
aw_static_inline void hub4g_dev_unlock(hub4g_t *p_this)
{
    modbus_reg_map_unlock(&(p_this->super));
}



/**
 * ������ʵ����ʼ��
 */
void hub4g_inst_init(hub4g_t      *p_hub4g,
                    modbus_info_t *p_mb_info,
                    pile_sem_t    *p_pile_sem,
                    bool_t         key_vaild);

#endif
