/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief I2S interrupt mode implementation
 * 
 * \internal
 * - 1.01 15-07-14  sam.
 * \endinternal
 */

#ifndef __AM_I2S_INT_H
#define __AM_I2S_INT_H



#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2s.h"

/**
 * \addtogroup am_if_i2s_int
 * \copydoc am_i2s_int.h
 * @{
 */
    
/**
 * \brief I2S���ж�ģʽ���豸�ṹ��
 */
typedef struct am_i2s_int_dev {
    
    /** \brief I2S��׼����������     */
    am_i2s_handle_t    handle;

    /** \brief ָ��I2S���ͻ�������ָ�� */
    uint32_t          *p_txbuf;
    
    /** \brief �������ݸ���             */
    volatile uint32_t  tx_nbytes;
    
    /** \brief ָ��I2S���ջ�������ָ�� */
    volatile uint32_t *p_rxbuf;
    
    /** \brief �������ݸ���             */
    volatile uint32_t  rx_nbytes;
		  
} am_i2s_int_dev_t;

/** \brief I2S���ж�ģʽ����׼�������������Ͷ��� */
typedef struct am_i2s_int_dev *am_i2s_int_handle_t;


/**
 * \brief ��ʼ��I2SΪ�ж�ģʽ
 *
 * \param[in] p_dev   : I2S���ж�ģʽ���豸�ṹ��ָ��
 * \param[in] handle  : I2S��׼����������
 *
 * \return I2S���ж�ģʽ����׼���������������ֵΪNULL��������ʼ��ʧ��
 */
am_i2s_int_handle_t am_i2s_int_init(am_i2s_int_dev_t *p_dev,
                                    am_i2s_handle_t   handle);

/**
 * \brief I2S���ݷ��ͣ��ж�ģʽ��
 *
 * \param[in] handle  : I2S���ж�ģʽ����׼����������
 * \param[in] p_txbuf : �������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 * 
 * \return �ɹ��������ݵĸ���
 */
int am_i2s_int_send(am_i2s_int_handle_t  handle,
                    const uint32_t      *p_txbuf,
                    uint32_t             nbytes);
                            

/**
 * \brief I2S���ݽ��գ��ж�ģʽ��
 *
 * \param[in] handle  : I2S���ж�ģʽ����׼����������
 * \param[in] p_rxbuf : �������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 * 
 * \return �ɹ��������ݵĸ���
 */
int am_i2s_int_receive(am_i2s_int_handle_t  handle,
                       uint32_t            *p_rxbuf,
                       uint32_t             nbytes);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2S_INT_H */

/* end of file */
