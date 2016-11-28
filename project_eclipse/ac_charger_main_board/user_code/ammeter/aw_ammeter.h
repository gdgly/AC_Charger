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
 * \brief  �������ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-12  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "modbus/aw_mb_master.h"
#include "aw_task.h"                    /* ��������� */

#ifndef __AW_AMMETER_H
#define __AW_AMMETER_H

/** \brief  07��DL645Э�� */
#define AW_AMMETER_TRANSFER_PROTOCOL_DL645_07     0
/** \brief 97��DL645Э�飬��δ֧�� */
#define AW_AMMETER_TRANSFER_PROTOCOL_DL645_97     1
/** \brief  modbus-rtuЭ�� */
#define AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU   2 

/** \brief �������Ϊֱ����� */
#define AW_AMMETER_TYPE_DC    0

/** \brief �������Ϊ����� */
#define AW_AMMETER_TYPE_AC    1

#define AW_AMMETER_PHASE_A    0    /**< \brief A�� */
#define AW_AMMETER_PHASE_B    1    /**< \brief A�� */
#define AW_AMMETER_PHASE_C    2    /**< \brief A�� */

/** 
 *  \brief ���
 */
typedef struct aw_ammeter {
    uint32_t energy;                     /**< \brief ��ǰ���� */
    uint32_t type;                      /**< \brief ����ʶ */
    
    /** 
     * \brief ��ȡ��ǰ�����й����ܣ���λ0.01 KWh
     * \param[in]  handle   : ָ�����ʵ��
     * \param[out] p_energy : ָ���ŵ����ı���
     *  
     * \return AW_OK    : ��ȡ�ɹ�
     * \return AW_ERROR : ��ȡʧ��
     */
    aw_err_t (*pfn_active_energy_get)(struct aw_ammeter* handle,
                                      uint32_t          *p_energy);
}aw_ammeter_t;

/** 
 *  \brief ���ͨ�Ŵ���ṹ
 */
typedef struct aw_ammeter_transfer {
    uint8_t  *p_addr;                /**< \brief ͨ�ŵ�ַ */
    uint8_t   addr_len;              /**< \brief ͨ�ŵ�ַ���� */
    uint8_t   protocol;              /**< \brief ͨ��Э�� */

    /** 
     * \brief ��������
     * \param [in] handle  : ���ͨ�Ŵ����ʵ��
     * \param [in] p_txbuf : �������ݻ�����
     * \param [in] nbytes  : �����ֽ���
     * \return �����룺 ����AW_OKʱ����ʾͨ�ųɹ���
     */
    aw_err_t (*pfn_send)(struct aw_ammeter_transfer* handle,
                         const uint8_t              *p_txbuf,
                         uint32_t                    nbytes);
    /** 
     * \brief ��������
     * \param [in] handle  : ���ͨ�Ŵ����ʵ��
     * \param [in] p_rxbuf : �������ݻ�����
     * \param [in] nbytes  : �����ֽ���
     * \return �����룺 ����AW_OKʱ����ʾͨ�ųɹ���
     */
    int (*pfn_receive)(struct aw_ammeter_transfer* handle,
                       uint8_t                    *p_rxbuf,
                       uint32_t                    nbytes);
}aw_ammeter_transfer_t;

/** 
 *  \brief ���DL645Э��ͨ�Ŵ���ṹ
 */
typedef struct aw_ammeter_transfer_dl645 {
    aw_ammeter_transfer_t super;       /**< \brief �̳еĸ��� */
    uint32_t              uart_num;    /**< \brief ͨ��ʱʹ�õĴ��ں� */
    uint32_t              uart_buad;   /**< \brief ͨ������ */
    uint32_t              uart_format; /**< \brief ����ͨ�Ÿ�ʽ */
    bool_t                rs485_en;    /**< \brief RS485ʹ�� */
}aw_ammeter_transfer_dl645_t;      

/**
 *  \brief ���modbus-rtuЭ��ͨ�Ŵ���ṹ
 */
typedef struct aw_ammeter_transfer_mb {
    aw_ammeter_transfer_t         super;          /**< \brief �̳еĸ��� */
    aw_mb_master_serial_params_t *p_ser_params;   /**< \brief ���ڳ�ʼ������ */
    aw_mb_master_t                master;         /**< \brief ��վ */
    aw_task_id_t                  tid;            /**< \brief ��վ���ݽ�����ѯ����id */
}aw_ammeter_transfer_mb_t;


/**
  * \brief ֱ�����
  */
typedef struct aw_ammeter_dc {
    aw_ammeter_t super;                 /**< \brief �̳еĸ��� */
    aw_ammeter_transfer_t *p_transfer;  /**< \brief ������ͨ���� */
}aw_ammeter_dc_t;


/**
 * \brief ֱ�����ʵ����ʼ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_dc_inst_init (aw_ammeter_t* handle);

/**
 * \brief ֱ�����ʵ��ȥ��ʼ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_dc_inst_deinit (aw_ammeter_t* handle);

/**
 * \brief ��ȡ��ǰ��������λ0.01 KWh
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_energy : ָ���ŵ����ı���
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_active_energy_get(struct aw_ammeter* handle,
                                      uint32_t          *p_energy);

/**
 * \brief ��ȡA�����
 * \param[in]  handle  : ָ�����ʵ��
 * \param[out] p_curr  : ָ���ŵ����ı���
 *                        ����07��汾����λΪ0.001A
 *                        ����97��汾����λΪ0.01A
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_err_t aw_ammeter_current_get(struct aw_ammeter* handle,
                                uint8_t            phase,
                                uint32_t          *p_curr);

/**
 * \brief ��ȡ��ѹ����λ0.1V
 * \param[in]  handle  : ָ�����ʵ��
 * \param[out] p_vol   : ָ���ŵ����ı���
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_voltage_get(struct aw_ammeter* handle,
                                uint8_t            phase,
                                int32_t           *p_vol);

/**
 * \brief ��ȡ����
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_power    : ָ����ѹ�ı�������λkW
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_err_t aw_ammeter_power_get(struct aw_ammeter* handle, uint32_t *p_power);
#endif
