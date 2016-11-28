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
 * \brief I2S��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-14  sam.
 * \endinternal
 */

#ifndef __AM_I2S_H
#define __AM_I2S_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_if_i2s
 * \copydoc am_i2s.h
 * @{
 */

/**
 * \name Ӳ����������ѡ�����Ӳ������ʱ�������Ƕ��ѡ��Ļ�ֵ
 * @{
 */
#define AM_I2S_TX_BIT8         0x0          /**< \brief �����ֿ��Ϊ8λ                  */
#define AM_I2S_TX_BIT16        0x1          /**< \brief �����ֿ��Ϊ16λ                 */
#define AM_I2S_TX_BIT32        0x2          /**< \brief �����ֿ��Ϊ32λ                 */

#define AM_I2S_TX_BIT8         0x0          /**< \brief �����ֿ��Ϊ8λ                  */
#define AM_I2S_TX_BIT16        0x1          /**< \brief �����ֿ��Ϊ16λ                 */
#define AM_I2S_TX_BIT32        0x2          /**< \brief �����ֿ��Ϊ32λ                 */
	
#define AM_I2S_RX_BIT8         0x3          /**< \brief �����ֿ��Ϊ8λ                  */
#define AM_I2S_RX_BIT16        0x4          /**< \brief �����ֿ��Ϊ16λ                 */
#define AM_I2S_RX_BIT32        0x5          /**< \brief �����ֿ��Ϊ32λ                 */	

#define AM_I2S_WIDTH8         8             /**< \brief �ֿ��Ϊ8λ                      */
#define AM_I2S_WIDTH16        16            /**< \brief �ֿ��Ϊ16λ                     */
#define AM_I2S_WIDTH32        32   	        /**< \brief �ֿ��Ϊ32λ                     */
	
#define AM_I2S_TXSOUND_STEREO 0             /**< \brief ��������Ϊ������                 */
#define AM_I2S_TXSOUND_MONO   1             /**< \brief ��������Ϊ������                 */
#define AM_I2S_RXSOUND_STEREO 2             /**< \brief ��������Ϊ������                 */
#define AM_I2S_RXSOUND_MONO   3             /**< \brief ��������Ϊ������                 */


#define AM_I2S_RXFIFO_EMPTY   0             /**< \brief ����FIFOΪ�ձ�־                 */
#define AM_I2S_TXFIFO_FULL    8             /**< \brief ����FIFOΪ����־                 */

#define AM_I2S_RXFIFO_LEVEL   1             /**< \brief ����FIFO���ֵ                   */
#define AM_I2S_TXFIFO_LEVEL   2             /**< \brief ����FIFO���ֵ                   */

#define AM_I2S_OPT_TXMASTER   0             /**< \brief ��������                         */
#define AM_I2S_OPT_TXSLAVE    1             /**< \brief �ӻ�����                         */
#define AM_I2S_OPT_RXMASTER   2             /**< \brief ��������                         */
#define AM_I2S_OPT_RXSLAVE    3             /**< \brief �ӻ�����                         */

#define AM_I2S_TXCLKSLECT_FRAC   0          /**< \brief ����ʱ��ԴΪС�����ʷ�Ƶ��       */
#define AM_I2S_TXCLKSLECT_RXREF  1          /**< \brief ����ʱ��ԴΪRX_REF               */
#define AM_I2S_TXCLKSLECT_WIRE4  2          /**< \brief ����ʱ��ԴΪRX��λʱ��           */ 
#define AM_I2S_TXCLKSLECT_TXMCLK 3          /**< \brief ����ʱ��ԴΪ������ʱ��           */

#define AM_I2S_RXCLKSLECT_FRAC   4          /**< \brief ����ʱ��ԴΪС�����ʷ�Ƶ��       */
#define AM_I2S_RXCLKSLECT_RXREF  5          /**< \brief ����ʱ��ԴΪRX_REF               */
#define AM_I2S_RXCLKSLECT_WIRE4  6          /**< \brief ����ʱ��ԴΪTX��λʱ��           */ 
#define AM_I2S_RXCLKSLECT_RXMCLK 7          /**< \brief ����ʱ��ԴΪ������ʱ��           */
		
/** @} */	
	

/**
 * \name I2S�豸�ص��������ͱ��룬����ָ��ע����ֻص�����
 * @{
 */

#define AM_I2S_CALLBACK_GET_TX_DATA   0 /**< \brief ��ȡһ��������       */
#define AM_I2S_CALLBACK_PUT_RCV_DATA  1 /**< \brief �ύһ�����յ�����   */
#define AM_I2S_CALLBACK_ERROR         2 /**< \brief ����ص�����         */

/** @} */

/**
 * \name �ص��������Ͷ���
 * @{
 */

/** \brief ��ȡһ�������ֻص��������� */
typedef int  (*pfn_i2s_txdata_get_t)(void *p_arg, uint32_t *p_data);

/** \brief �ύһ�����յ�����        */
typedef int  (*pfn_i2s_rxdata_put_t)(void *p_arg, uint32_t ch);

/** \brief ����ص�����                 */
typedef int  (*pfn_i2s_err_t)(void *p_arg, int code, void *p_data, int size);

/** @} */


/**
 * \brief I2S���������ṹ��
 */
struct am_i2s_drv_funcs {

    /**\brief ����I2S���Ϳ�ʼ���� */
    int (*pfn_i2s_transmit_startup)(void *p_drv);
	
	/**\brief  I2S���ͽ������� */
	int (*pfn_i2s_tx_stop)(void *p_drv);
	
	/**\brief  I2S���ս������� */
	int (*pfn_i2s_rx_stop)(void *p_drv);
  
    /**\brief ����I2S�ص����� */
    int (*pfn_i2s_callback_set)(void  *p_drv,
                                int    callback_type,
                                int  (*pfn_callback)(void *),
                                void  *p_callback_arg);

    /**\brief I2S���ӣ�������I2S�жϺ���   */
    int (*pfn_i2s_connect)(void *p_drv);
};

/**
 * \brief I2S����
 */
typedef struct am_i2s_serv {

    /** \brief I2S���������ṹ��ָ��    */
    struct am_i2s_drv_funcs *p_funcs;

    /** \brief �������������ĵ�һ������  */
    void                     *p_drv;
} am_i2s_serv_t;

/** \brief I2S��׼�������������Ͷ���  */
typedef am_i2s_serv_t *am_i2s_handle_t;


/**
 * \brief ����I2S����
 * \param[in] handle : I2S��׼����������
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_i2s_transmit_startup (am_i2s_handle_t handle)
{
    return handle->p_funcs->pfn_i2s_transmit_startup(handle->p_drv);
}

/**
 * \brief I2S���ͽ���
 * \param[in] handle : I2S��׼����������
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_i2s_tx_stop (am_i2s_handle_t handle)
{
    return handle->p_funcs->pfn_i2s_tx_stop(handle->p_drv);
}

/**
 * \brief I2S���ս���
 * \param[in] handle : I2S��׼����������
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_i2s_rx_stop (am_i2s_handle_t handle)
{
    return handle->p_funcs->pfn_i2s_rx_stop(handle->p_drv);
}

/**
 * \brief ����I2S�ص�����
 *
 * \param[in] handle         : I2S��׼����������
 * \param[in] callback_type  : ָ�����õĺ��ֻص�����
 *            - AM_I2S_CALLBACK_GET_TX_DATA  : ��ȡһ�������ֺ���
 *            - AM_I2S_CALLBACK_PUT_RCV_DATA : �ύһ�����յ����ָ�Ӧ�ó���
 *            - AM_I2S_CALLBACK_ERROR        : ����ص�����
 * \param[in] pfn_callback   : ָ��ص�������ָ��
 * \param[in] p_callback_arg : �ص��������û�����
 *
 * \retval  AM_OK      : �ص��������óɹ�
 * \retval -AM_EINVAL  : ����ʧ�ܣ���������
 */
am_static_inline
int am_i2s_callback_set (am_i2s_handle_t  handle,
                         int              callback_type,
                         int             (*pfn_callback)(void *),
                         void             *p_callback_arg)
{
    return handle->p_funcs->pfn_i2s_callback_set(handle->p_drv,
                                                 callback_type,
                                                 pfn_callback,
                                                 p_callback_arg);
}


/**
 * \brief I2S�жϺ������ӣ���ʹ���ж�ģʽʱ��Ҫ���ô˺���
 * \param[in] handle  : I2S��׼����������
 * \retval  AM_OK     : ���ӳɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 */
am_static_inline
int am_i2s_connect (am_i2s_handle_t handle)
{
    return handle->p_funcs->pfn_i2s_connect(handle->p_drv);
}


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2S_H */

/* end of file */
