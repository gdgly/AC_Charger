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
 * \brief GPIO �ж�Ӳ�������ӿ�
 *
 * 1����GPIO PORT0 �� GPIO PORT2 ֧���жϣ�
 * 2��GPIO PORT0 �� GPIO PORT2 zai NVIC���� EXINT3�����жϺš�
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 15-04-23  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_GPIOINT_H
#define __AMHW_GPIOINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_gpioint
 * \copydoc amhw_gpioint.h
 * @{
 */
 
/**
 * \brief GPIO �жϼĴ�����ṹ��
 */
typedef struct amhw_gpioint
{
  __I  uint32_t intstatus;    /**< \brief �ж�״̬�Ĵ���                                              */
  __I  uint32_t io0intstatr;  /**< \brief GPIO�˿�0�������ж�״̬�Ĵ���        */
  __I  uint32_t io0intstatf;  /**< \brief GPIO�˿�0�½����ж�״̬�Ĵ���        */
  __O  uint32_t io0intclr;    /**< \brief GPIO�˿�0�ж�����Ĵ���                        */
  __IO uint32_t io0intenr;    /**< \brief GPIO�˿�0�������ж�ʹ�ܼĴ���         */
  __IO uint32_t io0intenf;    /**< \brief GPIO�˿�0�½����ж�ʹ�ܼĴ���         */
  __IO uint32_t reserved0[3]; /**< \brief ����                                                                        */
  __I  uint32_t io2intstatr;  /**< \brief GPIO�˿�2�������ж�״̬�Ĵ���         */
  __I  uint32_t io2intstatf;  /**< \brief GPIO�˿�2�������ж�״̬�Ĵ���         */
  __O  uint32_t io2intclr;    /**< \brief GPIO�˿�2�ж�����Ĵ���                        */
  __IO uint32_t io2intenr;    /**< \brief GPIO�˿�2�������ж�ʹ�ܼĴ���         */
  __IO uint32_t io2intenf;    /**< \brief GPIO�˿�2�������ж�ʹ�ܼĴ���         */
} amhw_gpioint_t;

#define AWBL_GPIOPIN_COUNT_MAX   64    /**< \brief ��֧��PORT0��PORT2���ж���Ŀ64 */

/**
 * \brief GPIO�ж�PORT���ö��
 * ��LPC17xx�ϣ���PORT0��PORT2֧���ж�
 */
typedef enum amhw_gpioint_port {
    
    AMHW_GPIOINT_PORT0 = 0,            /**< \brief GPIO PORT0 */
    AMHW_GPIOINT_PORT2 = 2,            /**< \brief GPIO PORT2 */

} amhw_gpioint_port_t;

/**
 * \brief ���PORT�Ƿ��жϴ���pending״̬
 *
 * \param[in] p_hw_gpioint : ָ��GPIO�жϼĴ������ָ��
 * \param[in] port         : #AMHW_GPIOINT_PORT0 ��  #AMHW_GPIOINT_PORT2
 *
 * \retval TRUE  : PORT����pending״̬����ʶPORT��������һ���жϲ�����
 * \retval FALSE : PORTδ����pending״̬����ʶ����PORT��û��һ���жϲ���
 */
am_static_inline
bool_t amhw_gpioint_port_pending_chk (amhw_gpioint_t      *p_hw_gpioint, 
                                      amhw_gpioint_port_t  port)
{
    return (bool_t)((p_hw_gpioint->intstatus & (1 << port)) != 0);
}

/**
 * \brief ʹ��ָ��port�Ĺܽ������ش����ж�
 *
 * \param[in] p_hw_gpioint : ָ��GPIO�жϼĴ������ָ��
 * \param[in] port         : #AMHW_GPIOINT_PORT0 ��  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : �ܽźţ�0 ~ 31
 *
 * \return ��
 */
am_static_inline
void amhw_gpioint_pin_rising_enable (amhw_gpioint_t       *p_hw_gpioint, 
                                     amhw_gpioint_port_t   port,  
                                     int                   pin_num)
{
    if (port == AMHW_GPIOINT_PORT0) {
        p_hw_gpioint->io0intenr |= (1 << (pin_num & 0x1F));
    } else {
        p_hw_gpioint->io2intenr |= (1 << (pin_num & 0x1F));
    }
}

/**
 * \brief ����ָ��port�Ĺܽ������ش����ж�
 *
 * \param[in] p_hw_gpioint : ָ��GPIO�жϼĴ������ָ��
 * \param[in] port         : #AMHW_GPIOINT_PORT0 ��  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : �ܽźţ�0 ~ 31
 *
 * \return ��
 */
am_static_inline
void amhw_gpioint_pin_rising_disable (amhw_gpioint_t       *p_hw_gpioint, 
                                     amhw_gpioint_port_t   port,  
                                     int                   pin_num)
{
    if (port == AMHW_GPIOINT_PORT0) {
        p_hw_gpioint->io0intenr &= ~(1 << (pin_num & 0x1F));
    } else {
        p_hw_gpioint->io2intenr &= ~(1 << (pin_num & 0x1F));
    }
}

/**
 * \brief ���ָ��port�Ĺܽ��Ƿ�����������ж�
 *
 * \param[in] p_hw_gpioint : ָ��GPIO�жϼĴ������ָ��
 * \param[in] port         : #AMHW_GPIOINT_PORT0 ��  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : �ܽźţ�0 ~ 31
 *
 * \retval TRUE  : ��⵽������,�������ش������ж�
 * \retval FALSE : δ��⵽�����أ�δ�����ж�
 */
am_static_inline
bool_t amhw_gpioint_pin_rising_chk (amhw_gpioint_t       *p_hw_gpioint, 
                                    amhw_gpioint_port_t   port,  
                                    int                   pin_num)
{
    if (port == AMHW_GPIOINT_PORT0) {
        return (bool_t)((p_hw_gpioint->io0intstatr & (1 << (pin_num & 0x1F)) ) != 0);
    } else {
        return (bool_t)((p_hw_gpioint->io2intstatr & (1 << (pin_num & 0x1F)) ) != 0);
    }
}




/**
 * \brief ʹ��ָ��port�Ĺܽ��½��ش����ж�
 *
 * \param[in] p_hw_gpioint : ָ��GPIO�жϼĴ������ָ��
 * \param[in] port         : #AMHW_GPIOINT_PORT0 ��  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : �ܽźţ�0 ~ 31
 *
 * \return ��
 */
am_static_inline
void amhw_gpioint_pin_falling_enable (amhw_gpioint_t       *p_hw_gpioint, 
                                      amhw_gpioint_port_t   port,  
                                      int                   pin_num)
{
    if (port == AMHW_GPIOINT_PORT0) {
        p_hw_gpioint->io0intenf |= (1 << (pin_num & 0x1F));
    } else {
        p_hw_gpioint->io2intenf |= (1 << (pin_num & 0x1F));
    }
}

/**
 * \brief ����ָ��port�Ĺܽ��½��ش����ж�
 *
 * \param[in] p_hw_gpioint : ָ��GPIO�жϼĴ������ָ��
 * \param[in] port         : #AMHW_GPIOINT_PORT0 ��  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : �ܽźţ�0 ~ 31
 *
 * \return ��
 */
am_static_inline
void amhw_gpioint_pin_falling_disable (amhw_gpioint_t       *p_hw_gpioint, 
                                       amhw_gpioint_port_t   port,  
                                       int                   pin_num)
{
    if (port == AMHW_GPIOINT_PORT0) {
        p_hw_gpioint->io0intenf &= ~(1 << (pin_num & 0x1F));
    } else {
        p_hw_gpioint->io2intenf &= ~(1 << (pin_num & 0x1F));
    }
}

/**
 * \brief ���ָ��port�Ĺܽ��Ƿ�����½����ж�
 *
 * \param[in] p_hw_gpioint : ָ��GPIO�жϼĴ������ָ��
 * \param[in] port         : #AMHW_GPIOINT_PORT0 ��  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : �ܽźţ�0 ~ 31
 *
 * \retval TRUE  : ��⵽�½���,���½��ش������ж�
 * \retval FALSE : δ��⵽�½��أ�δ�����ж�
 */
am_static_inline
bool_t amhw_gpioint_pin_falling_chk (amhw_gpioint_t       *p_hw_gpioint, 
                                     amhw_gpioint_port_t   port,  
                                     int                   pin_num)
{
    if (port == AMHW_GPIOINT_PORT0) {
        return (bool_t)((p_hw_gpioint->io0intstatf & (1 << (pin_num & 0x1F)) ) != 0);
    } else {
        return (bool_t)((p_hw_gpioint->io2intstatf & (1 << (pin_num & 0x1F)) ) != 0);
    }
}

/**
 * \brief ���ָ���ܽŵ��ж�״̬
 *
 * \param[in] p_hw_gpioint : ָ��GPIO�жϼĴ������ָ��
 * \param[in] port         : #AMHW_GPIOINT_PORT0 ��  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : �ܽźţ�0 ~ 31
 *
 * \return ��
 */
am_static_inline
void amhw_gpioint_pin_intstat_clr (amhw_gpioint_t       *p_hw_gpioint, 
                                     amhw_gpioint_port_t   port,  
                                     int                   pin_num)
{
    if (port == AMHW_GPIOINT_PORT0) {
         p_hw_gpioint->io0intclr |= (1 << (pin_num & 0x1F)) ;
    } else {
         p_hw_gpioint->io2intclr |= (1 << (pin_num & 0x1F)) ;
    }
}

/** @} amhw_if_gpioint */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_GINT_H */

/* end of file */
