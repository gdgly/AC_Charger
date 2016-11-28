
/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USART����������USART��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 15-06-13  sam, first implementation.
 * \endinternal
 */

#ifndef __AMDR_USART_H
#define __AMDR_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"	
#include "amhw_usart.h"		

/**
 * \addtogroup amdr_if_usart
 * \copydoc amdr_usart.h
 * @{
 */	
	
/**
 *  ������ش�����Ĵ���ص�����
 *  ����ص�����ģ�� :
    
 *  int uart_err (void *p_arg, int code, void *p_data, int size);
    
 *  �ܹ����� am_uart_callback_set() ��װ����ص�����
 * @{
 */
 
/** 
 * \brief ���������ж�, p_data ������������ "uint32_t",
 *        ֵΪ USART �ж�״̬,��СΪ 1.
 */ 
#define AMDR_UART_ERRCODE_USART_OTHER_INT 2

/** @} */

/**
 * \brief LPC17XX UART�豸��Ϣ
 */	
typedef struct amdr_usart_devinfo {
  
    amhw_usart_t *p_hw_usart;       /**< \brief ָ��UART�Ĵ������ָ�� */
    
    uint8_t      inum;              /**< \brief USART ���������жϺ�     */
    uint32_t     cfg_flags;         /**< \brief ���ñ�־                                    */
    uint32_t     ctl_flags;         /**< \brief ���Ʊ�־                                    */
    uint32_t     baud_rate;         /**< \brief ����������                                */
    uint32_t     fifo_level;        /**< \brief ����FIFO����                           */
    uint8_t      fifo_size;         /**< \brief ����FIFO��С                          */

    uint8_t      rs485_ctrl;        /**< \brief RS485������Ϣ���μ�
                                        \ref grp_amhw_usart_rs485_ctrl_flags */
    uint8_t      rs485_dly;         /**< \brief RS485��ʱֵ��ֵΪ0~255  */

    void (*pfunc_rs485_gpio_dir_set) (uint8_t dir);

    /** \brief Ӳ������������Ϣ��������1��Ч���� Ϊ0��ʾ��֧�� */
    uint8_t      flowctrl_flags;

    /**
     * \brief  USART �����ж�ʹ��,����ֵΪ AMHW_USART_INT_*         
     */
    uint32_t other_int_enable;
	
} amdr_usart_devinfo_t;

/**
 * \brief LPC17XX USART �豸
 */
typedef struct amdr_usart_dev {

    am_uart_serv_t  uart_serv;                  /**< \brief USART��׼���� */
 
    int (*pfn_txchar_get)(void *, char *);      /**< \brief ���ͺ���ָ��      */
    int (*pfn_rxchar_put)(void *, char);        /**< \brief ���պ���ָ��       */
    int (*pfn_err)(void *, int, void *, int);   /**< \brief ������ָ��        */

    void     *txget_arg;                        /**< \brief ���ͺ�������ָ��    */
    void     *rxput_arg;                        /**< \brief ���պ�������ָ��     */
    void     *err_arg;                          /**< \brief ����������ָ��    */
    
    uint8_t   channel_mode;                     /**< \brief �����жϣ���ѯģʽ    */
    uint32_t  baud_rate;                        /**< \brief ������                  */
    uint16_t  options;                          /**< \brief Ӳ������ѡ��    */
    
    uint32_t  other_int_enable;                 /**< \brief ���������ж�ʹ�� */

	uint8_t   rs485_enable;                     /**< \brief RS485ʹ��           */

	uint8_t   rs485_txing;                      /**< \brief RS485���ڷ��ͱ�־       */

	uint8_t   flowctrl_mode;                    /**< \brief ������ģʽ ����UART1��Ч  */

    /** \brief ָ���豸��Ϣָ�� */
    const amdr_usart_devinfo_t *p_devinfo;
	
} amdr_usart_dev_t;

/**
 * \brief USART��ʼ��
 *
 * \param[in] p_dev     : ָ��USART�豸��ָ��
 * \param[in] p_devinfo : ָ��USART�豸��Ϣ��ָ�� 
 *
 * \return ��׼USART�ӿڷ���.��ΪNULL�����ʼ��ʧ��
 */
am_uart_handle_t amdr_usart_init(amdr_usart_dev_t           *p_dev,
                                 const amdr_usart_devinfo_t *p_devinfo);

/**
 * \brief USART ���ʼ��
 * \param[in] p_dev : ָ��USART�豸��ָ��
 * \return None
 */
void amdr_usart_deinit(amdr_usart_dev_t *p_dev);

/** 
 * @} 
 */
#ifdef __cplusplus
}
#endif

#endif    /* __AMDR_USART_H */

/* end of file */

