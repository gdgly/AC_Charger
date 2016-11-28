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
 * \brief  �������������淶������ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 16-06-22  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"

#ifndef __AW_ICCREADER_H
#define __AW_ICCREADER_H

#define AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYA   (0x60u) /**< \brief ��ԿA */
#define AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYB   (0x61u) /**< \brief ��ԿB */

typedef struct aw_iccreader_info {
    uint8_t cpu_interface[8];  /**< ����������Ķ������淶�汾��Ϣ*/
    uint8_t acq_interface[8];  /**< ����������İ汾��Ϣ */
    uint8_t manu_len;          /**< �����Զ���������Ϣ���� */
    uint8_t manu_info[50];     /**< �����Զ�����Ϣ */
    uint8_t reserv[2];         /**< ���� */
}aw_iccreader_info_t;


typedef struct aw_iccreader_s50s70_ci {
    uint8_t key_type;    /**< ������ */
    uint8_t uid_len;     /**< ��UID���� */
    uint8_t uid[4];      /**< ��UID */
}aw_iccreader_s50s70_ci_t;


/** 
 *  \brief ͨ�Ŵ�����Ϣ����
 */
typedef struct aw_iccreader_transfer {
    uint32_t              uart_num;    /**< \brief ͨ��ʱʹ�õĴ��ں� */
    uint32_t              uart_buad;   /**< \brief ͨ������ */
    uint32_t              uart_format; /**< \brief ����ͨ�Ÿ�ʽ */
    bool_t                rs485_en;    /**< \brief RS485ʹ�� */
}aw_iccreader_transfer_t;

/**
 *  \brief ������
 */
typedef struct aw_iccreader {
    const aw_iccreader_transfer_t *p_transfer;    /**< \brief ������Ϣ���� */
    /** 
     * \brief ��������
     * \param [in] handle  : ��������ʵ��
     * \param [in] p_txbuf : �������ݻ�����
     * \param [in] nbytes  : �����ֽ���
     * \return �����룺 ����AW_OKʱ����ʾͨ�ųɹ���
     */
    aw_err_t (*pfn_send)(struct aw_iccreader* handle,
                         const uint8_t       *p_txbuf,
                         uint32_t             nbytes);
    /** 
     * \brief ��������
     * \param [in] handle  : ��������ʵ��
     * \param [in] p_rxbuf : �������ݻ�����
     * \param [in] nbytes  : �����ֽ���
     * \return �����룺 ����AW_OKʱ����ʾͨ�ųɹ���
     */
    int (*pfn_receive)(struct aw_iccreader* handle,
                       uint8_t             *p_rxbuf,
                       uint32_t              nbytes);
}aw_iccreader_t;

/**
 * CPU��Ƭ�ϵ縴λ��Ӧ��Ϣ
 */
typedef struct aw_iccreader_samc_info {
    uint8_t   ptl;         /**< PTL */
    uint8_t  atr[50];      /**< ATR������ */
    uint16_t status;       /**<  ״̬��Ϣ */
}aw_iccreader_samc_info_t;

/**
 * \brief IC��������ʵ����ʼ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_iccreader_inst_init (struct aw_iccreader           *handle,
                                 const aw_iccreader_transfer_t *p_transfer);


/**
 * \brief ��������
 * \param[in]  handle   : ָ���������ʵ��
 * \param[in]  cmd      : ��������
 * \param[in]  p_txbuf  : ���ͻ�����
 * \param[in]  tlen     : ���ͻ���������
 * \param[out] p_rxbuf  : ���ջ�����
 * \param[in]  rlen     : ���ջ���������
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_iccreader_transfer(struct aw_iccreader* handle,
                               uint32_t  cmd,
                               void     *p_txbuf,
                               uint16_t  tlen,
                               void     *p_rxbuf,
                               uint16_t  rlen);


aw_err_t aw_iccreader_block_read (struct aw_iccreader *handle,
                                  uint8_t          *p_buf,
                                  uint8_t           block);

aw_err_t aw_iccreader_block_write (struct aw_iccreader *handle,
                                   uint8_t          *p_buf,
                                   uint8_t           block);

aw_err_t aw_iccreader_key_auth (struct aw_iccreader* handle,
                                uint8_t              key_type,
                                uint8_t             *p_uid,
                                uint8_t              uid_len,
                                uint8_t             *p_key,
                                uint8_t              key_len,
                                uint8_t              block);

aw_err_t aw_iccreader_rf_close (struct aw_iccreader* handle);

aw_err_t aw_iccreader_rf_open (struct aw_iccreader* handle);

aw_err_t aw_iccreader_led_set (struct aw_iccreader* handle, bool_t led1_en, bool_t led2_en);
aw_err_t aw_iccreader_buzzer_set (struct aw_iccreader* handle, uint16_t dlytime, uint8_t times);
aw_err_t aw_iccreader_baud_set (struct aw_iccreader* handle, uint8_t baud_code);
aw_err_t aw_iccreader_info_get (struct aw_iccreader* handle, void *p_rxbuf, uint32_t rlen);

aw_err_t aw_iccreader_s50s70_active (struct aw_iccreader      *handle,
                                     aw_iccreader_s50s70_ci_t *p_card);

aw_err_t aw_iccreader_halt(struct aw_iccreader *handle);

aw_err_t aw_iccreader_samc_power_on(struct aw_iccreader *handle,
                                    uint8_t card_no,
                                    uint16_t dly_time,
                                    aw_iccreader_samc_info_t *p_info);

aw_err_t aw_iccreader_samc_power_off(struct aw_iccreader *handle,
                                    uint8_t               card_no);
#endif
