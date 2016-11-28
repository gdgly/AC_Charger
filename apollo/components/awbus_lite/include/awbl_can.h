/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \internal
 * \par modification history:
 * - 1.02 15-11-16  cae, first implementation
 * \endinternal
 */
#ifndef __AWBL_CAN_H
#define __AWBL_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_can.h"
#include "aw_msgq.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "aw_list.h"

/** \brief can Interrupt status */
#define AWBL_CAN_INT_NONE                 0x00  /** \brief �޴���                 */
#define AWBL_CAN_INT_TX                   0x01  /** \brief ���ͳɹ� �ж�*/
#define AWBL_CAN_INT_RX                   0x02  /** \brief ���� �ж�          */
#define AWBL_CAN_INT_WAKE_UP              0x04  /** \brief �����ж�           */
#define AWBL_CAN_INT_ERROR                0x08  /** \brief �����ж�           */
#define AWBL_CAN_INT_DATAOVER             0x10  /** \brief ���߳��� �ж�*/
#define AWBL_CAN_INT_WARN                 0x20  /** \brief ���󱨾� �ж�*/
#define AWBL_CAN_INT_ERROR_PASSIVE        0x40  /** \brief ���󱻶��ж� */
#define AWBL_CAN_INT_BUS_OFF              0x80  /** \brief ���߹ر��ж� */
#define AWBL_CAN_INT_STATUS               0xf8
#define AWBL_CAN_INT_ALL                  0xffffffff
typedef uint32_t awbl_can_int_type_t;

#define AWBL_CAN_CHN_INIT                 0x00  /** \brief �޴���                 */
#define AWBL_CAN_CHN_START                0x01  /** \brief �����ж�           */
#define AWBL_CAN_CHN_STOP                 0x02  /** \brief ���߹ر��ж� */

typedef struct awbl_can_drv_funcs {
    /** \brief ��ʼ����غ��� */
    aw_can_err_t (*pfn_can_init)  (void *, uint8_t);

    /** \brief CAN���� */
    aw_can_err_t (*pfn_can_start) (void *);
    
    /** \brief CAN��λ��ֹͣ�� */
    aw_can_err_t (*pfn_can_reset) (void *);
    
    /** \brief CAN���� */
    aw_can_err_t (*pfn_can_sleep) (void *);

    /** \brief CAN���� */
    aw_can_err_t (*pfn_can_wakeup)(void *);

    /** \brief �ж�ʹ�� ������ */
    aw_can_err_t (*pfn_can_int_enable)  (void *, awbl_can_int_type_t);
    aw_can_err_t (*pfn_can_int_disable) (void *, awbl_can_int_type_t);

    /** \brief ���������� */
    aw_can_err_t (*pfn_can_baud_set) (void *, aw_can_baud_param_t*);

    /** \brief ���������� */
    aw_can_err_t (*pfn_can_baud_get) (void *, aw_can_baud_param_t*);

    /** \brief ��ȡ������� */
    aw_can_err_t (*pfn_can_err_cnt_get) (void *, aw_can_err_cnt_t*);
    
    /** \brief ���������� */
    aw_can_err_t (*pfn_can_err_cnt_clr) (void *);

    /** \brief CAN�շ���غ��� */
    aw_can_err_t (*pfn_can_reg_msg_read)  (void *, aw_can_msg_t*);
    aw_can_err_t (*pfn_can_reg_msg_write) (void *, aw_can_msg_t*);
    aw_can_err_t (*pfn_can_msg_snd_stop)  (void *);

    /** \brief �����˲���غ��� */
    aw_can_err_t (*pfn_can_filter_table_set) (void *, uint8_t*, size_t);
    aw_can_err_t (*pfn_can_filter_table_get) (void *, uint8_t*, size_t*);

    /** \brief CAN bus���״̬��ȡ */
    aw_can_err_t (*pfn_can_int_status_get) (void *, awbl_can_int_type_t*,
                                                    aw_can_bus_err_t*);

    /** \brief �����Ĵ��������ӿڣ������CAN�������õ� */
    aw_can_err_t (*pfn_can_reg_write) (void *, uint32_t,uint8_t*, size_t);
    aw_can_err_t (*pfn_can_reg_read ) (void *, uint32_t,uint8_t*, size_t);

} awbl_can_drv_funcs_t;

/** \brief ���������� */
#define AWBL_CAN_CONTROLLER_LOCK(p_serv) \
    aw_spinlock_isr_take(&((struct awbl_can_service *)p_serv)->lock_dev)

/** \brief ������������� */
#define AWBL_CAN_CONTROLLER_UNLOCK(p_serv) \
    aw_spinlock_isr_give(&((struct awbl_can_service *)p_serv)->lock_dev)

typedef struct awbl_can_servinfo {
    int                chn;              /** \brief ��ǰͨ����     */
    uint8_t            ctr_type;         /** \brief ��ǰ���������� */
    uint8_t            sizeof_msg;       /** \brief ��ǰ���ĳ���   */
    uint32_t           rxd_buf_size;     /** \brief ���ձ��Ļ�������С*/
    void              *p_rxd_buf;        /** \brief ���ձ��Ļ�����ָ��*/
    struct aw_rngbuf  *p_rxd_buf_ctr;    /** \brief ���ձ��Ļ�����������*/

}awbl_can_servinfo_t;

/**
 * \brief AWBus CAN ����ʵ��
 */
typedef struct awbl_can_service {

    /** \brief ָ����һ�� CAN ���� */
    struct awbl_can_service *p_next;

    /** \brief CAN ����������Ϣ */
    awbl_can_servinfo_t     *p_info;

    /** \brief ͨ��״̬    */
    uint8_t  chn_status;

    /** \brief ���ͷ�æ��־   */
    uint8_t  txd_busy;

    /** \brief �豸�� */
    aw_spinlock_isr_t lock_dev;

    /** \brief �豸������ */
    AW_MUTEX_DECL(dev_mux);

    /**< \brief �����ź��� */
    AW_SEMB_DECL(rcv_start_sem);

    /** \brief CAN ��������Ϣ���� */
    struct aw_list_head transfer_list;

    /** \brief ��ǰ���͵���Ϣ*/
    aw_can_transfer_t *p_curr_trans;

    /** \brief CAN�������غ��� */
    awbl_can_drv_funcs_t *p_servfuncs;

    /** \brief �û�APP�ص����� */
    aw_can_app_callbacks_t *p_app_cb_funcs;

    void *p_cookie;

} awbl_can_service_t;

/** \brief �����ʼ������ */
aw_err_t awbl_can_service_init (awbl_can_service_t    *p_serv,
                                awbl_can_servinfo_t   *p_servinfo,
                                awbl_can_drv_funcs_t  *p_servfuncs);
/** \brief CAN����ע�� */
aw_err_t awbl_can_service_register (awbl_can_service_t *p_serv);

/** \brief �жϷ����� */
void awbl_can_isr_handler (awbl_can_service_t *p_serv);

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_CAN_H */

