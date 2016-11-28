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
 * \brief USART interfaces for operating hardware.
 *
 * \internal
 * \par Modification History
 * - 1.01 15-09-30  cod, add uart4, rewrite "amhw_usart_t".
 * - 1.00 15-06-15  sam, first implementation.
 * \endinternal
 */

#ifndef __AMHW_USART_H
#define __AMHW_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup amhw_if_usart
 * \copydoc amhw_usart.h
 * @{
 */

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \brief LPC177X_8X UART �Ĵ����ṹ��
 */
typedef struct  {
    union {
        __I  uint32_t  rbr;        /**< \brief ���ջ���Ĵ���     */
        __O  uint32_t  thr;        /**< \brief ���ͱ��ּĴ���     */
        __IO uint32_t  dll;        /**< \brief ����������               */
    };
    union {
        __IO uint32_t  dlm;        /**< \brief ���ջ���Ĵ���     */
        __IO uint32_t  ier;        /**< \brief �ж�ʹ�ܼĴ���     */
    };
    union {
        __I  uint32_t  iir;        /**< \brief �жϱ�־�Ĵ���     */
        __O  uint32_t  fcr;        /**< \brief FIFO���ƼĴ���     */
    };
    __IO uint32_t  lcr;            /**< \brief �����߿��ƼĴ���                                                         */
    __IO uint32_t  mcr;            /**< \brief ���ƽ�������ƼĴ���,��UART1/4��ʹ��     */
    __I  uint32_t  lsr;            /**< \brief ��״̬�Ĵ���                                                                   */
    __IO uint32_t  msr;            /**< \brief ���ƽ����״̬�Ĵ���,��UART1/4��ʹ��     */
    __IO uint32_t  scr;            /**< \brief ���ٻ���Ĵ���                                                              */
    __IO uint32_t  acr;            /**< \brief �Զ������ʣ�auto-baud�����ƼĴ���             */
    __IO uint32_t  icr;            /**< \brief IrDA���ƼĴ���,UART4����                                   */
    __IO uint32_t  fdr;            /**< \brief С����Ƶ�Ĵ���                                                              */
    __IO uint32_t  osr;            /**< \brief �������Ĵ���,UART4����                                         */
    __IO uint32_t  ter;            /**< \brief ����ʹ�ܼĴ���,UART0/1/2/3����                    */
         uint32_t  reserved0[3];   /**< \brief ����λ                                                                                  */
    __IO uint32_t  hden;           /**< \brief Half-duplexʹ�ܼĴ���                                           */
         uint32_t  reserved1[1];   /**< \brief ����λ                                                                                  */
    __IO uint32_t  sci_ctrl;       /**< \brief ���ܿ��ӿڿ��ƼĴ���,UART4����                      */
    __IO uint32_t  rs485ctrl;      /**< \brief RS485 ���ƼĴ���                                                         */
    __IO uint32_t  adrmatch;       /**< \brief RS485 ��ַƥ��Ĵ���                                                */
    __IO uint32_t  rs485dly;       /**< \brief RS485 ���������ʱ�Ĵ���                                      */

    union {
    	__IO uint32_t  syncctrl;   /**< \brief ͬ��ģʽ���ƼĴ���        */
    	__I  uint32_t  fifolvl;    /**< \brief FIFOˮƽ�Ĵ���       */
    };

    __IO uint32_t  u4ter;          /**< \brief UART4����ʹ�ܼĴ���,UART4����                         */
} amhw_usart_t;

/**
 * \name ����USART�ж�����
 * \anchor grp_amhw_usart_irq_cfg_flags
 * @{
 */
#define AMHW_USART_IER_RBRINT   (1 << 0)  /**< \brief ʹ�ܽ����ж�   */

#define AMHW_USART_IER_THREINT  (1 << 1)  /**< \brief ʹ�ܷ����ж�   */
 
#define AMHW_USART_IER_RXLSINT  (1 << 2)  /**< \brief ʹ�ܽ�������״̬�ж�   */

#define AMHW_USART_IER_MODEMINT (1 << 3)  /**< \brief ʹ�ܴ���1ģʽ�ж�   */
#define AMHW_USART_IER_CTIINT   (1 << 7)  /**< \brief ʹ�ܴ���1��ʱ�ж�   */

#define AMHW_USART_IER_ABEOINT  (1 << 8)  /**< \brief ʹ���Զ����������ý����ж�   */

#define AMHW_USART_IER_ABTOINT  (1 << 9)  /**< \brief ʹ���Զ����������ó�ʱ�ж�   */

#define AMHW_USART_IER_INTALL   (0x038F)  /**< \brief �����ж�  */

/** @} */

/**
 * \name USART�ж�״̬��־λ
 * @{ 
 */
 
/** \brief ��Ϊ0ʱ��������һ���жϹ��𣻵�Ϊ1ʱ��û��һ���жϹ���     */
#define AMHW_USART_IIR_INTSTATUS    (1 << 0)

#define AMHW_USART_RLS_INTID      (3 << 1)     /**< \brief ���������ж�״̬ID   */
#define AMHW_USART_RDA_INTID      (2 << 1)     /**< \brief ���������ж�ID   */
#define AMHW_USART_CTI_INTID      (6 << 1)     /**< \brief ��ʱ�ж�ID   */
#define AMHW_USART_THRE_INTID     (1 << 1)     /**< \brief ���������ж�ID   */
#define AMHW_USART_MODEM_INTID    (0 << 1)     /**< \brief ģʽ�ж�ID   */
#define AMHW_USART_IIR_FIFOENABLE (3 << 6)     /**< \brief ��Ч��UnFCR[0]   */
#define AMHW_USART_IIR_ABEOINT    (1 << 8)     /**< \brief �Զ����������ý����ж�״̬  */
#define AMHW_USART_IIR_ABTOINT    (1 << 9)     /**< \brief �Զ����������ó�ʱ�ж�״̬ */

#define AMHW_USART_INTID_MASK     (0x07 << 1)  /**< \brief �жϱ�ʶ����  */

#define AMHW_USART_IIR_ALL        (0x030F)     /**< \brief �����ж�״̬  */


/** @} */

/**
 * \name  USART��FIFO���ƼĴ����궨��
 * @{      
 */
#define AMHW_USART_FCR_FIFO        (1 << 0) /**< \brief ʹ�ܷ��ͽ���FIFO  */
      
#define AMHW_USART_RXFIFO_RESET    (1 << 1) /**< \brief ��ս���FIFO  */

#define AMHW_USART_TXFIFO_RESET    (1 << 2) /**< \brief ��շ���FIFO  */

#define AMHW_USART_FCR_DMA         (1 << 3) /**< \brief DMAģʽ��FIFO  */

/** @} */

/**
 * \name  USART�Ľ��մ����ж���ֵ
 * @{      
 */
#define AMHW_USART_RX_TRILEVEL0       (0 << 6)  /**< \brief 1���ֽ�  */
#define AMHW_USART_RX_TRILEVEL1       (1 << 6)  /**< \brief 4���ֽ�  */
#define AMHW_USART_RX_TRILEVEL2       (2 << 6)  /**< \brief 8���ֽ�  */
#define AMHW_USART_RX_TRILEVEL3       (3 << 6)  /**< \brief 14���ֽ�  */

/** @} */

/**
 * \name USART ֡��ʽ����
 * @{       
 */
 
#define AMHW_USART_LCR_5BIT      0     /**< \brief 5λ�ֽڳ���  */
#define AMHW_USART_LCR_6BIT      1     /**< \brief 6λ�ֽڳ���  */
#define AMHW_USART_LCR_7BIT      2     /**< \brief 7λ�ֽڳ���  */
#define AMHW_USART_LCR_8BIT      3     /**< \brief 8λ�ֽڳ���  */

#define AMHW_USART_LCR_STOP_1      (0 << 2)  /**< \brief  1������λ   */

#define AMHW_USART_LCR_STOP_2      (1 << 2)  /**< \brief  2������λ   */

#define AMHW_USART_LCR_PARITY      (1 << 3)  /**< \brief  ʹ��У��    */

#define AMHW_USART_LCR_PARITY_NO   (0 << 3)  /**< \brief  �ر�У��    */

#define AMHW_USART_PARITY_ODD      (0 << 4)  /**< \brief  ��У��    */
#define AMHW_USART_PARITY_EVEN     (1 << 4)  /**< \brief  żУ��    */
#define AMHW_USART_PARITY_1STICK   (2 << 4)  /**< \brief  ǿ��Ϊ��1��stickУ��    */
#define AMHW_USART_PARITY_0STICK   (3 << 4)  /**< \brief  ǿ��Ϊ��0��stickУ��    */

#define AMHW_USART_LCR_BREAK       (1 << 6)  /**< \brief  ʹ�ܴ�����ֹ   */
  
#define AMHW_USART_DLAB_ENABLE     (1 << 7)  /**< \brief  �����Ƶ��     */
 
/** @} */

/**
 * \name ����USART1ģʽ����
 * \anchor grp_amhw_usart_mcr_cfg_flags
 * @{
 */
#define AMHW_USART_MCR_DTR        (1 << 0)  /**< \brief  DTR     */

#define AMHW_USART_MCR_RTS        (1 << 1)  /**< \brief  RTS     */

#define AMHW_USART_MCR_LOOPBACK   (1 << 4)  /**< \brief  ʹ�ܻ���ģʽ     */

#define AMHW_USART_MCR_RTSEN      (1 << 6)  /**< \brief  ʹ��auto-rts ������ */

#define AMHW_USART_MCR_CTSEN      (1 << 7)  /**< \brief  ʹ��auto-cts ������ */

/** @} */

/**
 * \name ����USART����״̬
 * \anchor grp_amhw_usart_lsr_cfg_flags
 * @{
 */
#define AMHW_USART_LSR_RDR    (1 << 0)  /**< \brief  ����FIFO��������  */

#define AMHW_USART_LSR_OE     (1 << 1)  /**< \brief  �������    */

#define AMHW_USART_LSR_PE     (1 << 2)  /**< \brief  �������   */

#define AMHW_USART_LSR_FE     (1 << 3)  /**< \brief  ֡����    */

#define AMHW_USART_LSR_BI     (1 << 4)  /**< \brief  ��ֹ����   */

#define AMHW_USART_LSR_THRE   (1 << 5)  /**< \brief UTHR Ϊ��   */

#define AMHW_USART_LSR_TEMT   (1 << 6)  /**< \brief UTHR and the U1TSR Ϊ��*/

/** \brief UART RBR ��������һ�� UART1 ���մ��� */
#define AMHW_USART_LSR_RXFE   (1 << 7)

/** @} */

/**
 * \name ����USARTģʽ״̬
 * \anchor grp_amhw_usart_msr_cfg_flags
 * @{
 */
#define AMHW_USART_MSR_DELTACTS   (1 << 0)  /**< \brief  ��������CTS��״̬ת��   */

#define AMHW_USART_MSR_DELTADSR   (1 << 1)  /**< \brief  ��������DSR��״̬ת��   */

#define AMHW_USART_MSR_DELTARI    (1 << 2)  /**< \brief  ��������RI�ɸߵ��͵�״̬ת�� */
 
#define AMHW_USART_MSR_DELTADCD   (1 << 3)  /**< \brief  ��������DCD��״̬ת��   */
 
#define AMHW_USART_MSR_CTS        (1 << 4)  /**< \brief  ��������CTS��״̬   */

#define AMHW_USART_MSR_DSR        (1 << 5)  /**< \brief  ��������DSR��״̬   */

#define AMHW_USART_MSR_RI         (1 << 6)  /**< \brief  ��������RI��״̬    */

#define AMHW_USART_MSR_DCD        (1 << 7)  /**< \brief  ��������DCD��״̬   */

/** @} */

/**
 * \name ����USART�Զ�����������
 * \anchor grp_amhw_usart_autobaud_cfg_flags
 * @{
 */                                                           
#define AMHW_USART_AUTOBAUD_START     (1 << 0) /**< \brief  �Զ�ƥ�䲨���ʿ�ʼ   */
#define AMHW_USART_AUTOBAUD_STOP      (0 << 0) /**< \brief  �Զ�ƥ�䲨���ʽ���   */

#define AMHW_USART_AUTOBAUD_MODE0     (0 << 1) /**< \brief  ģʽ0   */

#define AMHW_USART_AUTOBAUD_MODE1     (1 << 1) /**< \brief  ģʽ1   */

#define AMHW_USART_AUTOBAUD_RESTART   (1 << 2) /**< \brief  �Զ�����������  */

/** \brief  �Զ�ƥ�䲨���ʽ����ж����(����д)  */
#define AMHW_USART_ACR_ABEOINTCLR     (1 << 8)

/** \brief  �Զ�ƥ�䲨���ʳ�ʱ�ж����(����д)  */
#define AMHW_USART_ACR_ABTOINTCLR     (1 << 9)

/** @} */     

/**
 * \name ����USART  IrDA����
 * \anchor grp_amhw_usart_icr_cfg_flags
 * @{
 */
#define AMHW_USART_ICR_IrDAEN      (1 << 0) /**< \brief ����IrDAģʽʹ��         */

#define AMHW_USART_ICR_IrDAInv     (1 << 1) /**< \brief ʹ�� IrDA �̶�����ģʽ   */

#define AMHW_USART_ICR_FixPulseEn  (1 << 2) /**< \brief ����IrDAģʽ����ʹ��     */


/* ���� IrDA ����(����������) */
#define AMHW_USART_ICR_PD2     (0 << 3)   /**< \brief  2��   */
#define AMHW_USART_ICR_PD4     (1 << 3)   /**< \brief  4��   */
#define AMHW_USART_ICR_PD8     (2 << 3)   /**< \brief  8��   */
#define AMHW_USART_ICR_PD16    (3 << 3)   /**< \brief  16��   */
#define AMHW_USART_ICR_PD32    (4 << 3)   /**< \brief  32��   */
#define AMHW_USART_ICR_PD64    (5 << 3)   /**< \brief  64��   */
#define AMHW_USART_ICR_PD128   (6 << 3)   /**< \brief  128��  */
#define AMHW_USART_ICR_PD256   (7 << 3)   /**< \brief  256��  */

/** @} */

/**
 * \name  USART����ʹ�ܼĴ����궨��    
 * @{   
 */
#define AMHW_USART_TER_TXEN      (1 << 7)          /**< \brief ���ڷ���ʹ��  */

/** @} */

/**
 * \brief ʹ�ܴ����ж�
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] int_flags  : �ж�ʹ��λ�� �μ�
 *                        \ref grp_amhw_usart_irq_cfg_flags "Irq Configuration Flags"
 *
 * \return    ��
 */
am_static_inline
void amhw_usart_int_enable (amhw_usart_t *p_hw_usart, uint32_t int_flags)
{
     p_hw_usart->ier |= int_flags;
}

/**
 * \brief �رմ����ж�
 *
 * \param[in] p_hw_usart  : ָ��USART�Ĵ������ָ��
 * \param[in] int_flags : �ж�λ�� �μ�
 *                        \ref grp_amhw_usart_irq_cfg_flags "Irq Configuration Flags"
 *
 * \return ��
 */
am_static_inline
void amhw_usart_int_disable (amhw_usart_t *p_hw_usart, uint32_t int_flags)
{
     p_hw_usart->ier &= ~int_flags;
}

/**
 * \brief ����USART�ж�״̬
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] int_flag   : �ж�λ��ֵΪAMHW_USART_*(#AMHW_USART_IIR_INTSTATUS)
 *
 * \return ��
 */
am_static_inline
uint32_t amhw_usart_intstat_get (amhw_usart_t *p_hw_usart, uint32_t int_flag)
{
    return p_hw_usart->iir & int_flag;
}

/**
 * \brief ����USART��FIFO
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] fifo_flags : FIFO��־λ��ֵΪAMHW_USART_*(#AMHW_USART_RX_TRILEVEL0)
 *
 * \return ��
 */
am_static_inline
void amhw_usart_fifo_set (amhw_usart_t *p_hw_usart, uint32_t fifo_flags)
{
    p_hw_usart->fcr = fifo_flags;
}

/**
 * \brief USART ����
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] cfg_flags  : ����ֵ��ֵΪAMHW_USART_*(#AMHW_USART_LCR_5BIT)
 *
 * \return ��
 */
am_static_inline
void amhw_usart_config (amhw_usart_t *p_hw_usart, uint32_t cfg_flags)
{
    p_hw_usart->lcr |= cfg_flags;
}

/**
 * \brief ʹ�� DLAB
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_usart_dlab_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->lcr |= AMHW_USART_DLAB_ENABLE;
}

/**
 * \brief �ر� DLAB
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_usart_dlab_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->lcr &= ~AMHW_USART_DLAB_ENABLE;
}


/**
 * \brief ��ȡUART ���ƽ��������ģʽ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return USART����ģʽ
 * \note   ֻ�ɻ�ȡUART1
 */
am_static_inline
uint32_t amhw_usart_mcr_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->mcr;
}

/**
 * \brief ����UART ���ƽ��������ģʽ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] mcr_flags  : ����ֵ���μ�
 *                          \ref grp_amhw_usart_mcr_cfg_flags "Control Mode Configuration"
 *
 * \return ��
 * \note   ֻ������UART1
 */
am_static_inline
uint32_t amhw_usart_mcr_set (amhw_usart_t *p_hw_usart, uint32_t mcr_flags)
{
    return p_hw_usart->mcr = mcr_flags;
}

/**
 * \brief ��ȡUSART��״̬�Ĵ���
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return USART״̬
 */
am_static_inline
uint32_t amhw_usart_stat_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->lsr;
}

/**
 * \brief ��ȡUSART���ƽ����״̬
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return UART���ƽ����״̬�Ĵ���ֵ
 * \note   �ýӿ�������UART1
 */
am_static_inline
uint32_t amhw_usart_msr_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->msr;
}

/**
 * \brief ����USART�Զ�������
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] autobaud_flags : ����ֵ���μ�
 *                             \ref grp_amhw_usart_autobaud_cfg_flags "Autobaud Configuration "
 *
 * \return ��
 */
am_static_inline
uint32_t amhw_usart_autobaud_set (amhw_usart_t *p_hw_usart, uint32_t autobaud_flags)
{
    return p_hw_usart->acr = autobaud_flags;
}

/**
 * \brief ����USART4 irdaģʽ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] irda_flags : ����ֵ���μ�
 *                         \ref grp_amhw_usart_icr_cfg_flags "IrDA Configuration"
 *
 * \return ��
 */
am_static_inline
uint32_t amhw_usart_irda_set (amhw_usart_t *p_hw_usart, uint32_t irda_flags)
{
    return p_hw_usart->icr = irda_flags;
}

/**
 * \brief ʹ��USART ����
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return ��
 * \note   Ĭ��ʹ��
 */
am_static_inline
void amhw_usart_tx_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->ter |= AMHW_USART_TER_TXEN;
}
  
/**
 * \brief �ر�USART ����
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_usart_tx_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->ter &= ~AMHW_USART_TER_TXEN;
}

/**
 * \brief ʹ��USART4 ����
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_usart4_tx_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->u4ter |= AMHW_USART_TER_TXEN;
}

/**
 * \brief �ر�USART4 ����
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_usart4_tx_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->u4ter &= ~AMHW_USART_TER_TXEN;
}

/**
 * \brief USART4 �������Ĵ�������
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] value      : ���õ��������Ĵ�����ֵ
 * \return ��
 */
am_static_inline
void amhw_usart_osr_set (amhw_usart_t *p_hw_usart, uint32_t value)
{
    p_hw_usart->osr = value;
}

/**
 * \brief USART4 �������Ĵ���ֵ��ȡ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \return �������Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_usart_osr_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->osr & 0x7FFF;
}


/**
 * \name ���ܿ��ӿڿ���λ����
 * \anchor grp_amhw_usart_sci_cfg_flags
 * @{
 */
#define AMHW_USART_SCI_ENABLE          (0 << 0)   /**< \brief  ���ܿ��ӿڽ���   */
#define AMHW_USART_SCI_DISABLE         (1 << 0)   /**< \brief  ʹ���첽��˫�����ܿ��ӿ�   */

#define AMHW_USART_SCI_NACKDIS_ENABLE  (0 << 1)   /**< \brief  ʹ��NACK��Ӧ   */
#define AMHW_USART_SCI_NACKDIS_DISABLE (1 << 1)   /**< \brief  ��ֹNACK��Ӧ   */

#define AMHW_USART_SCI_PROTESEL_0      (0 << 1)    /**< \brief  T=0   */
#define AMHW_USART_SCI_PROTESEL_1      (1 << 1)    /**< \brief  T=1   */

/** \brief UART4�������·��͵�������� val  */
#define AMHW_USART_SCI_TXRETRY_VALUE(val)   ((val) << 5)

/** \brief λʱ����   */
#define AMHW_USART_SCI_XTRAGUARD_VALUE(val) ((val) << 8)

/** @} */

/**
 * \brief USART4 ���ܿ��ӿ�����
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] flag       : ���ò������μ� \ref grp_amhw_usart_sci_cfg_flags "SCI Configuration Flags"
 *
 * \return ��
 */
am_static_inline
void amhw_usart_sci_set (amhw_usart_t *p_hw_usart, uint32_t flag)
{
    p_hw_usart->sci_ctrl = flag;
}

/**
 * \name ͬ��ģʽ����λ����
 * \anchor grp_amhw_usart_sync_ctrl_flags
 * @{
 */
#define AMHW_USART_SYNC_ENABLE          (1 << 0)    /**< \brief  ͬ��ģʽʹ��   */
#define AMHW_USART_SYNC_DISABLE         (0 << 0)    /**< \brief  ͬ��ģʽ����  */

#define AMHW_USART_SYNC_CSRC_SLAVE      (0 << 1)    /**< \brief  ͬ���ӻ�ģʽ   */
#define AMHW_USART_SYNC_CSRC_MASTER     (1 << 1)    /**< \brief  ͬ������ģʽ   */

#define AMHW_USART_SYNC_FES_ENABLE      (1 << 2)    /**< \brief  �½��ز���   */
#define AMHW_USART_SYNC_FES_DISABLE     (0 << 2)    /**< \brief  �����ز���   */

#define AMHW_USART_SYNC_TSBYPASS_ENABLE  (1 << 3)   /**< \brief ���Է���ͬ��   */
#define AMHW_USART_SYNC_TSBYPASS_DISABLE (0 << 3)   /**< \brief �����Է���ͬ��  */

#define AMHW_USART_SYNC_CSC_ENABLE  (1 << 4) /**< \brief ��������ʱ��ʹ��   */
#define AMHW_USART_SYNC_CSC_DISABLE (0 << 4) /**< \brief ��������ʱ�ӽ���   */

#define AMHW_USART_SYNC_SSS_DISABLE (1 << 5) /**< \brief ��������ʼ/ֹͣλ  */
#define AMHW_USART_SYNC_SSS_EANBLE  (0 << 5) /**< \brief ������ģʽ������ʼ/ֹͣλ  */

/** \brief CSCENλ������Ŀ���֮��  */
#define AMHW_USART_SYNC_CCLR_DISABLE (0 << 6)

/** \brief Ӳ���ڽ��յ�ÿ���ַ�������CECEN     */
#define AMHW_USART_SYNC_CCLR_EANBLE  (1 << 6)
/** @} */

/**
 * \brief USART4 ͬ��ģʽ���ƼĴ�������
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] flag       : ���ò������μ�
 *                         \ref grp_amhw_usart_sync_ctrl_flags "Sync Configuration Flags"
 *
 * \return ��
 */
am_static_inline
void amhw_usart_sync_set (amhw_usart_t *p_hw_usart, uint32_t flag)
{
    p_hw_usart->syncctrl = flag;
}

/**
 * \brief USART4 ͬ��ģʽʹ��
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_usart_sync_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->syncctrl |= AMHW_USART_SYNC_ENABLE;
}

/**
 * \brief USART4 ͬ��ģʽ����
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_usart_sync_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->syncctrl &= ~AMHW_USART_SYNC_ENABLE;
}

/**
 * \name RS485����λ����
 * \anchor grp_amhw_usart_rs485_ctrl_flags
 * @{
 */
#define AMHW_USART_RS485_NMM_ENABLE    (1 << 0)   /**< \brief ��ͨ���ģʽʹ��   */
#define AMHW_USART_RS485_NMM_DISABLE   (0 << 0)   /**< \brief ��ͨ���ģʽ����  */

#define AMHW_USART_RS485_RX_DISABLE    (1 << 1)   /**< \brief ���ܽ�����  */
#define AMHW_USART_RS485_RX_ENABLE     (0 << 1)   /**< \brief ʹ�ܽ�����   */

#define AMHW_USART_RS485_AAD_ENABLE    (1 << 2)   /**< \brief �Զ���ַ���ʹ��   */
#define AMHW_USART_RS485_AAD_DISABLE   (0 << 2)   /**< \brief �Զ���ַ������   */

#define AMHW_USART_RS485_SEL_RTS   (0 << 3)       /**< \brief �ܽ�RTS���ڷ������   */
#define AMHW_USART_RS485_SEL_DTR   (1 << 3)       /**< \brief �ܽ�DTR���ڷ������   */

#define AMHW_USART_RS485_DCTRL_ENABLE    (1 << 4)  /**< \brief �Զ��������ʹ��   */
#define AMHW_USART_RS485_DCTRL_DISABLE   (0 << 4)  /**< \brief �Զ�������ƽ���   */

/** \brief ����ʱ��������ƹܽű�����Ϊ�߼�1 */
#define AMHW_USART_RS485_OINV1    (1 << 5)
/** \brief ����ʱ��������ƹܽű�����Ϊ�߼�1 */
#define AMHW_USART_RS485_OINV0   (0 << 5)

/** @} */

/**
 * \brief RS485���ƼĴ�������
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] flag       : ���ò������μ�
 *                         \ref grp_amhw_usart_rs485_ctrl_flags
 *                              "RS485 Configuration Flags"
 *
 * \return ��
 */
am_static_inline
void amhw_usart_rs485_ctrl_set (amhw_usart_t *p_hw_usart, uint32_t flag)
{
    p_hw_usart->rs485ctrl = flag;
}

/**
 * \brief ����RS485��ַƥ��ֵ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] val        : ��ַƥ��ֵ��0~255
 *
 * \return ��
 */
am_static_inline
void amhw_usart_rs485_adrmatch_set (amhw_usart_t *p_hw_usart, uint32_t val)
{
    p_hw_usart->adrmatch = val;
}

/**
 * \brief ��ȡRS485��ַƥ��ֵ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return    RS485��ַƥ��ֵ
 */
am_static_inline
uint32_t amhw_usart_rs485_adrmatch_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->adrmatch & 0xFF;
}

/**
 * \brief ����RS485���������ʱֵ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] dly        : ���������ʱֵ��0~255
 *
 * \return ��
 */
am_static_inline
void amhw_usart_rs485_dly_set (amhw_usart_t *p_hw_usart, uint32_t dly)
{
    p_hw_usart->rs485dly = dly;
}

/**
 * \brief ��ȡRS485��ַƥ��ֵ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return    ���������ʱֵ
 */
am_static_inline
uint32_t amhw_usart_rs485_dly_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->rs485dly & 0xFF;
}

/**
 * \name UART FIFO��ǰˮƽ����
 * @{
 */
#define AMHW_UART_RXFIFOLVL_MASK    0xF         /**< \brief ����FIFO�ĵ�ǰˮƽ����  */
#define AMHW_UART_TXFIFOLVL_MASK   (0xF << 8)   /**< \brief ����FIFO�ĵ�ǰˮƽ����  */

/** @} */

/**
 * \brief ��ȡUART����FIFO�ĵ�ǰˮƽ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return  ����FIFO�ĵ�ǰˮƽ,ֵΪ0~0xF,0ΪFIFO�գ�0xFΪFIFO��
 *
 * \note   : UART4����ʹ��
 */
am_static_inline
uint8_t amhw_usart_rxfifo_level_get (amhw_usart_t *p_hw_usart)
{
    return (uint8_t)(p_hw_usart->fifolvl & AMHW_UART_RXFIFOLVL_MASK);
}

/**
 * \brief ��ȡUART����FIFO�ĵ�ǰˮƽ
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 *
 * \return  ����FIFO�ĵ�ǰˮƽ,ֵΪ0~0xF,0ΪFIFO�գ�0xFΪFIFO��
 *
 * \note   : UART4����ʹ��
 */
am_static_inline
uint8_t amhw_usart_txfifo_level_get (amhw_usart_t *p_hw_usart)
{
    return (uint8_t)((p_hw_usart->fifolvl & AMHW_UART_TXFIFOLVL_MASK) >> 8);
}

/**
 * \brief  USART ����������
 *
 * \param[in] p_hw_usart : ָ��USART�Ĵ������ָ��
 * \param[in] u_clk      : USART ����ʱ��
 * \param[in] baudrate   : ����������ֵ
 *
 * \return  >0           : ��ʵ������ֵ
 *          -AM_EINVAL   : ����ʧ�ܣ�������Ч
 */
int amhw_usart_baudrate_set (amhw_usart_t *p_hw_usart,
                             uint32_t      u_clk,
                             uint32_t      baudrate);

/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/**
 * @} amhw_if_usart
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_USART_H */

/* end of file */
