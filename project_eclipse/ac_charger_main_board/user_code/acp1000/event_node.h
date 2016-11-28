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
 * \brief �¼�ʵ������
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

/* �¼� */
typedef enum event
{
   CARD_AUTH_SUS,  /* ��Ȩ�ɹ��¼� */
   CARD_AUTH_ING,  /* ��Ȩ���¼� */
   CARD_AUTH_FAIL, /* ��Ȩ��ʧ�� */
   CARD_WAIT_KEY,  /* �ȴ���Կ�ź� */
   CARD_SWING_OK,  /* �������ݳɹ� */
   CARD_AUTH_ID,   /* ��ID */
   CARD_AUTH_SUS_ORDER,  /* ��Ȩ�ɹ����ѱ�ԤԼ�¼� */
   CARD_ADMIN_MODE,     /* ����Աģʽ  1���������Աģʽ 0: �˳�����Աģʽ*/
   SCREEN_UNLOCK,  /* ���������¼� */

   CHARGE_MAN_START,  /* ��Ϊ��������¼� */
   CHARGE_MAN_STOP,   /* ��Ϊֹͣ����¼� */
   CHARGE_BG_STOP,    /* ��ֹ̨ͣ����¼� */

   CHARGE_PIEL_WAIT,   /* �ȴ������������¼� */
   CHARGE_PIEL_START,  /* ������������¼� */
   CHARGE_PILE_STOP,   /* ������������¼� */
   CHARGE_FULL,        /* ���������� */
   CHARGE_AC_STATE,    /* �Ӵ���״̬ */

   GUN_INSERT,          /* ǹ���� */
   GUN_EXTRACT,         /* ǹ�γ� */

   BILLING_START,       /* �Ʒѿ�ʼ */
   BILLING_ING,         /* �Ʒ��� */
   BILLING_STOP,        /* �Ʒ�ֹͣ�¼� */
   BILLING_END,         /* �Ʒѽ��� */
   BILLING_ENDING,      /* �Ʒѽ����� */

   BILLING_MODE_GET,    /* ���ڳ���ģʽ������ */
   BILLING_BALANCE,     /* ������ */

   AMETER_MEASURE,      /* ��������� */

   PILE_ALARM,          /* ׮�������� */
   PILE_TIME,           /* ʱ������ */
   PILE_TEMP,           /* �¶����� */
   PILE_DUGS_INFO,      /* ׮��Ϣ����(����Ա����) */

   HUB4G_AUTH_KEY,      /* �������·���Կ */
   HUB4G_AUTH_USR,      /* ��������Ȩ���·���� */
   HUB4G_ALLOW_CHARGE,  /* �������¼� */
   HUB4G_BILLING,       /* �����¼� */
   HUB4G_PILE_ORDER,    /* ׮ԤԼ��� */
   HUB4G_USR_INFO,      /* �������·��û�ID�������  */
   HUB4G_PILE_ID,       /* ׮ID */
   HUB4G_PRICE,         /* ׮ID */
   HUB4G_UPGRADE,       /* ׮���� */

   DUGS_HUB4G_ADDR,     /* ��������ַ */
   DUGS_PRICE_GET,      /* ��ȡ��� */
   /*---------------------------------------------------*/
   ERR_CARD_READER,     /* ������ͨѶ�쳣 */
   ERR_AMMETER,         /* ���ͨѶ�쳣 */
   ERR_CAR_READY,       /* ���������쳣 */
   ERR_CHAGER,          /* һ���쳣�˳� */
   ERR_AMMETER_VOL,     /* ��ѹ��� */
   ERR_AMMETER_CURR,    /* �������  */
   ERR_SCRAM,           /* �����������  */
   ERR_LIGHT,           /* �������쳣��� */
   ERR_AC,              /* ACĸ�ſ����쳣��� */
   ERR_TEMP,            /* �¶��쳣����� 0�� ������ 1�� ���ߣ� 2�� ���� */
   ERR_PILE_GUN_CONN,   /* ǹ�Ӵ��쳣���  */
   ERR_PILE_GUN_LOCK,   /* ǹ���쳣��� */
   ERR_HUB4G,           /* 4Gͨ������� 0�� ������ 1���쳣 */
   ERR_DUGS,            /* �������쳣����� 0�� ������ 1���쳣 */
   ERR_HUB4G_COMM,      /* ������ͨ���쳣 */
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
