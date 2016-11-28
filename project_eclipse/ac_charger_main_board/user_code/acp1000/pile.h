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
 * \brief ׮ʵ������
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
 * ʱ������
 */
typedef struct pile_time_price {
    aw_tm_t  tm;        /* ׮ĿǰRTCʱ�� */
    uint16_t now_price; /* ׮Ŀǰʱ���µĵ�� �� ��λ0.0001Ԫÿ�� */
}pile_time_price_t;


/**
 * ��׮�澯���
 */
typedef struct pile_alarm {
    uint32_t alarm_mask;   /* �澯���� 0����׮�޸澯 \ref grp_pile_alarm */
}pile_alarm_t;

/**
 * ��׮�������
 */
typedef struct pile_dat{
    bool_t   charge_state; /* �Ƿ��� */
    bool_t   gun_state;    /* ǹ�Ƿ�����������*/
    bool_t   scram_state;  /* �Ƿ�������ض��� */
    bool_t   light_state;  /* �Ƿ�������쳣  */
    bool_t   auth_state;   /* ��Ȩ��Ч�Ƿ� TRUE: ��Ȩ��Ч�� FALSE�� ��Ȩ��Ч */
    bool_t   gun_lock;     /* װ�ϵ�ǹ����״̬ */

    uint8_t  bg_state;     /* ��̨ͨ��״̬��bit1: 4Gͨ��״̬�� bit2: ������ͨ�������*/
    uint8_t  hub4g_addr;   /* ������ͨ�ŵ�ַ */
    uint32_t input_vol;    /* ׮�����ѹ�� ��λ0.1V */
    uint32_t input_curr;   /* ׮�������   ��λ0.001A*/
    time_t   start_time;   /* ����ʱ�� */
    uint32_t run_time;     /* ����ʱ�䣬��λ���� */
    uint16_t err_cnt;      /* �쳣���� */
    uint16_t charge_cnt;   /* ������ */
    int16_t  temp;         /* ׮���¶� ����λ��*/
    bool_t   charge_ac_state;

    uint32_t mcu_uid[4];   /* оƬID�� */

}pile_dat_t;

/**
 * ׮�����ź���
 */
typedef struct pile_sem {
    AW_SEMB_DECL(hub4g_key_sem);     /**< key���յȴ���  */
    AW_SEMB_DECL(hub4g_auth_sem);    /**< ��Ȩ�ȴ���  */
    AW_SEMB_DECL(hub4g_cctrl_sem);   /**< ������ȴ���  */
    AW_SEMB_DECL(hub4g_billing_sem); /**< ����ȴ���  ���û����㣩*/
    AW_SEMB_DECL(charge_gun_sem);    /**< ��ǹ�ȴ���(�û�����)  */
}pile_sem_t;

/**
 * ��׮����
 */
typedef struct pile{
    event_node_t  evt_node;            /* �¼��ӿ� */
    AW_MUTEX_DECL(dev_lock);          /**< \brief �豸��  */

    pile_dat_t        pile_dat;
    pile_alarm_t      pile_alarm;
    pile_time_price_t pile_time;

    pile_sem_t        pile_sem;
}pile_t;


/**
 * \brief ���ֹͣԭ��
 * \anchor grp_pile_alarm
 * @{
 */
#define PILE_ALARM_NONE            0x00   /**< \brief ���쳣    */
#define PILE_ALARM_CARDREADER      0x01   /**< \brief ����ͨ���쳣    */
#define PILE_ALARM_AMMETER         0x02   /**< \brief ���ͨ���쳣    */
#define PILE_ALARM_LCD             0x04   /**< \brief ������ͨ���쳣    */
#define PILE_ALARM_HUG4G           0x08   /**< \brief ������ͨ���쳣    */
#define PILE_ALARM_VTP1            0x10   /**< \brief ���VTP1�쳣    */
#define PILE_ALARM_ELOCK           0x20   /**< \brief �������쳣    */
#define PILE_ALARM_ACLOCK          0x40   /**< \brief ACĸ�����쳣    */
#define PILE_ALARM_SCRAM           0x80   /**< \brief ��⵽�������ض���    */
#define PILE_ALARM_CURR            0x100  /**< \brief ��⵽�����쳣    */
#define PILE_ALARM_OVERVOL         0x200  /**< \brief ��ѹ�쳣    */
#define PILE_ALARM_UNDERVOL        0x400  /**< \brief Ƿѹ�쳣    */
#define PILE_ALARM_LIGHT           0x1000  /**< \brief �������쳣    */
#define PILE_ALARM_TEMP            0x2000  /**< \brief �¶��쳣    */
#define PILE_ALARM_EEPROM          0x4000  /**< \brief �ڲ�EEPROM�쳣    */
#define PILE_ALARM_HUB4G_COM       0x8000  /**< \brief ������ͨ���쳣    */

static inline void pile_dev_lock(pile_t *p_this)
{
    AW_MUTEX_LOCK(p_this->dev_lock, AW_SEM_WAIT_FOREVER);
}

static inline void pile_dev_unlock(pile_t *p_this)
{
    AW_MUTEX_UNLOCK(p_this->dev_lock);
}

/**
 *  \brief ���ģ��ʵ����ʼ��
 *  param [in]   p_this        : ����ʵ��
 *  */
void pile_inst_init(pile_t *p_this);
void pile_task_startup (pile_t *p_this);


#endif
