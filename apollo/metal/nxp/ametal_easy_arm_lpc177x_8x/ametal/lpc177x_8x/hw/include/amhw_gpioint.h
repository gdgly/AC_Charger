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
 * \brief GPIO 中断硬件操作接口
 *
 * 1、仅GPIO PORT0 和 GPIO PORT2 支持中断；
 * 2、GPIO PORT0 和 GPIO PORT2 zai NVIC中与 EXINT3共享中断号。
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
 * \brief GPIO 中断寄存器块结构体
 */
typedef struct amhw_gpioint
{
  __I  uint32_t intstatus;    /**< \brief 中断状态寄存器                                              */
  __I  uint32_t io0intstatr;  /**< \brief GPIO端口0上升沿中断状态寄存器        */
  __I  uint32_t io0intstatf;  /**< \brief GPIO端口0下降沿中断状态寄存器        */
  __O  uint32_t io0intclr;    /**< \brief GPIO端口0中断清零寄存器                        */
  __IO uint32_t io0intenr;    /**< \brief GPIO端口0上升沿中断使能寄存器         */
  __IO uint32_t io0intenf;    /**< \brief GPIO端口0下降沿中断使能寄存器         */
  __IO uint32_t reserved0[3]; /**< \brief 保留                                                                        */
  __I  uint32_t io2intstatr;  /**< \brief GPIO端口2上升沿中断状态寄存器         */
  __I  uint32_t io2intstatf;  /**< \brief GPIO端口2下升沿中断状态寄存器         */
  __O  uint32_t io2intclr;    /**< \brief GPIO端口2中断清零寄存器                        */
  __IO uint32_t io2intenr;    /**< \brief GPIO端口2上升沿中断使能寄存器         */
  __IO uint32_t io2intenf;    /**< \brief GPIO端口2下升沿中断使能寄存器         */
} amhw_gpioint_t;

#define AWBL_GPIOPIN_COUNT_MAX   64    /**< \brief 仅支持PORT0和PORT2，中断数目64 */

/**
 * \brief GPIO中断PORT编号枚举
 * 在LPC17xx上，仅PORT0和PORT2支持中断
 */
typedef enum amhw_gpioint_port {
    
    AMHW_GPIOINT_PORT0 = 0,            /**< \brief GPIO PORT0 */
    AMHW_GPIOINT_PORT2 = 2,            /**< \brief GPIO PORT2 */

} amhw_gpioint_port_t;

/**
 * \brief 检测PORT是否中断处于pending状态
 *
 * \param[in] p_hw_gpioint : 指向GPIO中断寄存器块的指针
 * \param[in] port         : #AMHW_GPIOINT_PORT0 或  #AMHW_GPIOINT_PORT2
 *
 * \retval TRUE  : PORT处于pending状态，标识PORT中至少有一个中断产生了
 * \retval FALSE : PORT未处于pending状态，标识整个PORT中没有一个中断产生
 */
am_static_inline
bool_t amhw_gpioint_port_pending_chk (amhw_gpioint_t      *p_hw_gpioint, 
                                      amhw_gpioint_port_t  port)
{
    return (bool_t)((p_hw_gpioint->intstatus & (1 << port)) != 0);
}

/**
 * \brief 使能指定port的管脚上升沿触发中断
 *
 * \param[in] p_hw_gpioint : 指向GPIO中断寄存器块的指针
 * \param[in] port         : #AMHW_GPIOINT_PORT0 或  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : 管脚号，0 ~ 31
 *
 * \return 无
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
 * \brief 禁能指定port的管脚上升沿触发中断
 *
 * \param[in] p_hw_gpioint : 指向GPIO中断寄存器块的指针
 * \param[in] port         : #AMHW_GPIOINT_PORT0 或  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : 管脚号，0 ~ 31
 *
 * \return 无
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
 * \brief 检测指定port的管脚是否产生上升沿中断
 *
 * \param[in] p_hw_gpioint : 指向GPIO中断寄存器块的指针
 * \param[in] port         : #AMHW_GPIOINT_PORT0 或  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : 管脚号，0 ~ 31
 *
 * \retval TRUE  : 检测到上升沿,该上升沿触发了中断
 * \retval FALSE : 未检测到上升沿，未触发中断
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
 * \brief 使能指定port的管脚下降沿触发中断
 *
 * \param[in] p_hw_gpioint : 指向GPIO中断寄存器块的指针
 * \param[in] port         : #AMHW_GPIOINT_PORT0 或  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : 管脚号，0 ~ 31
 *
 * \return 无
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
 * \brief 禁能指定port的管脚下降沿触发中断
 *
 * \param[in] p_hw_gpioint : 指向GPIO中断寄存器块的指针
 * \param[in] port         : #AMHW_GPIOINT_PORT0 或  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : 管脚号，0 ~ 31
 *
 * \return 无
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
 * \brief 检测指定port的管脚是否产生下降沿中断
 *
 * \param[in] p_hw_gpioint : 指向GPIO中断寄存器块的指针
 * \param[in] port         : #AMHW_GPIOINT_PORT0 或  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : 管脚号，0 ~ 31
 *
 * \retval TRUE  : 检测到下降沿,该下降沿触发了中断
 * \retval FALSE : 未检测到下降沿，未触发中断
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
 * \brief 清除指定管脚的中断状态
 *
 * \param[in] p_hw_gpioint : 指向GPIO中断寄存器块的指针
 * \param[in] port         : #AMHW_GPIOINT_PORT0 或  #AMHW_GPIOINT_PORT2
 * \param[in] pin_num      : 管脚号，0 ~ 31
 *
 * \return 无
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
