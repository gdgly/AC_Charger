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
 * \brief 电源控制接口
 *
 * 1. 低功耗控制
 * 2. 外设电源控制
 *
 * \internal
 * \par History
 * - 1.00 15-04-22  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_POWER_H
#define __AMHW_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"

/**
 * \addtogroup amhw_if_power
 * \copydoc amhw_power.h
 * @{
 */

/**
 * \name 外设电源控制定义
 * @{
 */
#define AMHW_POWER_LCD       (1 << 0)    /**< \brief LCD         */
#define AMHW_POWER_TIMER0    (1 << 1)    /**< \brief 定时器0     */
#define AMHW_POWER_TIMER1    (1 << 2)    /**< \brief 定时器1     */
#define AMHW_POWER_UART0     (1 << 3)    /**< \brief UART0       */
#define AMHW_POWER_UART1     (1 << 4)    /**< \brief UART1       */
#define AMHW_POWER_PWM0      (1 << 5)    /**< \brief PWM0        */
#define AMHW_POWER_PWM1      (1 << 6)    /**< \brief PWM1        */
#define AMHW_POWER_I2C0      (1 << 7)    /**< \brief ADC0        */
#define AMHW_POWER_UART4     (1 << 8)    /**< \brief UART4       */
#define AMHW_POWER_RTC       (1 << 9)    /**< \brief RTC         */
#define AMHW_POWER_SSP1      (1 << 10)   /**< \brief SSP1        */
#define AMHW_POWER_EMC       (1 << 11)   /**< \brief EMC         */
#define AMHW_POWER_ADC       (1 << 12)   /**< \brief ADC         */
#define AMHW_POWER_CAN1      (1 << 13)   /**< \brief CAN1        */
#define AMHW_POWER_CAN2      (1 << 14)   /**< \brief CAN2        */
#define AMHW_POWER_GPIO      (1 << 15)   /**< \brief GPIO        */
#define AMHW_POWER_SPIFI     (1 << 16)   /**< \brief SPIFI       */
#define AMHW_POWER_MCPWM     (1 << 17)   /**< \brief MCPWM       */
#define AMHW_POWER_QEI       (1 << 18)   /**< \brief QEI         */
#define AMHW_POWER_I2C1      (1 << 19)   /**< \brief I2C1        */
#define AMHW_POWER_SSP2      (1 << 20)   /**< \brief SSP2        */
#define AMHW_POWER_SSP0      (1 << 21)   /**< \brief SSP0        */
#define AMHW_POWER_TIMER2    (1 << 22)   /**< \brief 定时器2     */
#define AMHW_POWER_TIMER3    (1 << 23)   /**< \brief 定时器3     */
#define AMHW_POWER_UART2     (1 << 24)   /**< \brief UART2       */
#define AMHW_POWER_UART3     (1 << 25)   /**< \brief UART3       */
#define AMHW_POWER_I2C2      (1 << 26)   /**< \brief I2C2        */
#define AMHW_POWER_I2S       (1 << 27)   /**< \brief I2S         */
#define AMHW_POWER_SDC       (1 << 28)   /**< \brief SD卡                      */
#define AMHW_POWER_GPDMA     (1 << 29)   /**< \brief GPDMA       */
#define AMHW_POWER_ENET      (1 << 30)   /**< \brief ENET        */
#define AMHW_POWER_USB       (1 << 31)   /**< \brief USB         */

/** @} */

/**
 * \brief 关闭外设电源
 * \param[in] powerdownmask ：AMHW_POWER_* 宏值或多个 AMHW_POWER_*宏的
                              或（OR）值(#AMHW_POWER_I2C2)
 * \return 无
 */
am_static_inline
void amhw_power_periph_down (uint32_t powerdownmask)
{
    AMHW_SYSCON->pconp &= ~powerdownmask;
}

/**
 * \brief 打开外设电源
 * \param[in] powerupmask ：AMHW_POWER_* 宏值或多个 AMHW_POWER_*宏的
                            或（OR）值(#AMHW_POWER_I2C2)
 * \return 无
 */
am_static_inline
void amhw_power_periph_up (uint32_t powerupmask)
{
    AMHW_SYSCON->pconp |= powerupmask;
}

/**
 * \name 低功耗模式定义
 * @{
 */

#define AMHW_POWER_MODE_SLEEP           (1 << 0)    /**< \brief 睡眠模式      */
#define AMHW_POWER_MODE_DEEP_SLEEP      (1 << 1)    /**< \brief 深度睡眠模式  */
#define AMHW_POWER_MODE_POWERDOWN       (1 << 2)    /**< \brief 掉电模式      */
#define AMHW_POWER_MODE_DEEP_POWERDOWN  (1 << 3)    /**< \brief 深度掉电模式  */

/** @} */

/**
 * \brief 设置低功耗模式
 * \param[in] mode : 低功耗模式，宏值 AMHW_SYSCON_POWER_MODE_*,
 *                   如#AMHW_SYSCON_POWER_MODE_SLEEP
 * \return 无
 */
void amhw_power_mode_enter (uint32_t mode);

/**
 * \brief 获取当前的低功耗模式
 * \return 低功耗模式，宏值 AMHW_SYSCON_POWER_MODE_*,如#AMHW_SYSCON_POWER_MODE_SLEEP
 */
am_static_inline
uint32_t amhw_power_mode_get(void)
{
    return (AMHW_SYSCON->pcon >> 8) & 0x0F;
}

/**
 * \brief 清除低功耗模式标志
 * \param[in] mode : 低功耗模式，宏值 AMHW_SYSCON_POWER_MODE_*,
 *                   如#AMHW_SYSCON_POWER_MODE_SLEEP
 * \return 无
 */
am_static_inline
void amhw_power_mode_clr (uint32_t mode)
{
    AMHW_SYSCON->pcon |= (mode & 0x0F) << 8;
}

/**
 * \brief 使能低功耗模式下BOD工作
 * \return 无
 */
am_static_inline
void amhw_power_bod_powermode_enable(void)
{
    AMHW_SYSCON->pcon &= ~(1 << 2);
}
   
/**
 * \brief 禁能低功耗模式下BOD工作
 * \return 无
 */
am_static_inline
void amhw_power_bod_powermode_disable(void)
{
    AMHW_SYSCON->pcon |=  (1 << 2);
}

/**
 * \brief 禁能全局的BOD检测
 * \return 无
 */
am_static_inline
void amhw_power_bod_global_disable(void)
{
    AMHW_SYSCON->pcon |= (1 << 3);
}

/**
 * \brief 使能全局的BOD检测
 * \return 无
 */
am_static_inline
void amhw_power_bod_global_enable(void)
{
    AMHW_SYSCON->pcon &= ~(1 << 3);
}

/**
 * \brief 使能BOD复位
 * \return 无
 */
am_static_inline
void amhw_power_bod_reset_enable(void)
{
    AMHW_SYSCON->pcon &= ~(1 << 4);
}
   
/**
 * \brief 禁能BOD复位
 * \return 无
 */
am_static_inline
void amhw_power_bod_reset_disable(void)
{
    AMHW_SYSCON->pcon |=  (1 << 4);
}

/**
 * \brief 功率提升开启
 * \return 无
 * \note  操作功耗允许高达120MHz
 */
am_static_inline
void amhw_power_boost_enable(void)
{
    AMHW_SYSCON->pboost |= 0x03;
}

/**
 * \brief 功率提升关闭
 * \return 无
 * \note 操作功耗必须在100MHz以下
 */
am_static_inline
void amhw_power_boost_disable(void)
{
    AMHW_SYSCON->pboost &= ~0x03;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_POWER_H */

/* end of file */
