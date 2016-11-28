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

#ifndef __DUGS_H
#define __DUGS_H

#include "player.h"
#include "aw_sem.h"
#include "event_node.h"
#include "mb/aw_mb_dgus_regmap.h"

/**
 * modbusЭ��ͨ����Ϣ
 */
typedef struct modbus_info {
    uint32_t  addr;  /* modbus��ַ */
    uint32_t  com;   /* modbusʹ�ô��ں� */
    uint32_t  baud;  /* ʹ�ò����� */
    uint32_t  par;   /* ʹ��У�鷽ʽ*/
}modbus_info_t;


/**
 * ������ʵ������
 */
typedef struct dugs {
    struct aw_mb_dgus_reg_map  super;      /* ���������� */
    player_t          player;              /* ������ */
    event_node_t      evt_node;            /* �¼��ӿ� */

    role_t           *p_dugs_display;      /* �ɰ��ݵĽ�ɫ - ��ʾ�� */
    role_t           *p_dugs_billing_ctrl; /* �ɰ��ݵĽ�ɫ  - �Ʒѿ����� */
    role_t           *p_dugs_charge_ctrl;  /* �ɰ��ݵĽ�ɫ  - �������� */
    role_t           *p_dugs_settings;     /* �ɰ��ݵĽ�ɫ  - ���������� */
    AW_MUTEX_DECL(role_lock);              /**< \brief ��ɫ��  */

    uint16_t          stop_reason;         /* ֹͣ���ԭ�� */
}dugs_t;
/**
 *  \brief ��������ʼ��
 *  param [in]   p_this        : ������ʵ��
 *  param [in]   p_dgus_info   : dugs������������Ϣ
 *  */
void dugs_inst_init(dugs_t *p_this, modbus_info_t *p_dugs_info);

/** \brief ��������д��������  */
aw_static_inline void dugs_lock(dugs_t *p_this)
{
    aw_mb_dugs_reg_map_lock(&(p_this->super));
}

/** \brief ��������д��������  */
aw_static_inline void dugs_unlock(dugs_t *p_this)
{
    aw_mb_dugs_reg_map_unlock(&(p_this->super));
}


#if 1
/** \brief ���ô�����  */
#define dugs_super_set(p_this, state_name, state) \
                    do {                                    \
                           dugs_lock(p_this); \
                           (p_this)->super.state_name = state;  \
                           dugs_unlock(p_this);\
                       }while (0)

/** \brief ���ô�����  */
#define dugs_super_unsafe_set(p_this, state_name, state) \
                    do {                                    \
                           (p_this)->super.state_name = state; \
                       }while (0)

/** \brief ��ȡ������  */
#define dugs_super_get(p_this, state_name, state)  \
                    do {                                    \
                            dugs_lock(p_this); \
                            state = (p_this)->super.state_name;  \
                            dugs_unlock(p_this);\
                        }while (0)

/** \brief ��ȡ������  */
#define dugs_super_unsafe_get(p_this, state_name, state)  \
                    do {                                    \
                            state = (p_this)->super.state_name;  \
                        }while (0)

#endif



#endif
