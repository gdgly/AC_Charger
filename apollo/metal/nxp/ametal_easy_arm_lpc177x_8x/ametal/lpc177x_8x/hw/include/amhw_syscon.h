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
 * \brief 系统控制接口
 *
 * 1. 复位控制；
 * 2. BOD（掉电检测）配置；
 * 3. 外部中断输入(External Interrupt Inputs)
 * 4. 其它系统控制和状态
 *
 * \internal
 * \par History
 * - 1.00 15-09-02  cod, first implementation.
 * \endinternal
 */

#ifndef __AMHW_SYSCON_H
#define __AMHW_SYSCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc177x_8x.h"

/**
 * \addtogroup amhw_if_syscon
 * \copydoc amhw_syscon.h
 * @{
 */

/**
  * \brief 系统控制寄存器块结构体
  */
typedef struct amhw_syscon {
    __IO uint32_t flashcfg;          /**< \brief Flash加速器配置    */
         uint32_t reserved0[31];     /**< \brief 保留，不应使用     */
    __IO uint32_t pll0con;           /**< \brief PLL0控制寄存器     */
    __IO uint32_t pll0cfg;           /**< \brief PLL0配置寄存器     */
    __I  uint32_t pll0stat;          /**< \brief PLL0状态寄存器     */
    __O  uint32_t pll0feed;          /**< \brief PLL0 FEED寄存器    */
         uint32_t reserved1[4];      /**< \brief 保留，不应使用     */
    __IO uint32_t pll1con;           /**< \brief PLL1控制寄存器     */
    __IO uint32_t pll1cfg;           /**< \brief PLL1配置寄存器     */
    __I  uint32_t pll1stat;          /**< \brief PLL1状态寄存器     */
    __O  uint32_t pll1feed;          /**< \brief PLL1 FEED寄存器    */
         uint32_t reserved2[4];      /**< \brief 保留，不应使用      */
    __IO uint32_t pcon;              /**< \brief 电源控制寄存器      */
    __IO uint32_t pconp;             /**< \brief 外设电源控制寄存器  */
         uint32_t reserved3[14];     /**< \brief 保留，不应使用      */
    __IO uint32_t emcclksel;         /**< \brief 外部存储控制器时钟选择寄存器    */
    __IO uint32_t cclksel;           /**< \brief CPU时钟选择寄存器   */
    __IO uint32_t usbclksel;         /**< \brief USB时钟选择寄存器   */
    __IO uint32_t clksrcsel;         /**< \brief 时钟源选择寄存器    */
    __IO uint32_t cansleepclr;       /**< \brief CAN 通道睡眠状态    */
    __IO uint32_t canwakeflags;      /**< \brief CAN 通道唤醒标志    */
         uint32_t reserved4[10];     /**< \brief 保留，不应使用      */
    __IO uint32_t extint;            /**< \brief 外部中断寄存器      */
         uint32_t reserved5;         /**< \brief 保留，不应使用      */
    __IO uint32_t extmode;           /**< \brief 外部中断模式寄存器  */
    __IO uint32_t extpolar;          /**< \brief 外部中断极性寄存器  */
         uint32_t reserved6[12];     /**< \brief 保留，不应使用      */
    __IO uint32_t rsid;              /**< \brief 时钟源寄存器        */
         uint32_t reserved7;         /**< \brief 保留，不应使用      */
    __IO uint32_t matrixarb;         /**< \brief 矩阵仲裁寄存器    */
         uint32_t reserved8[5];      /**< \brief 保留，不应使用      */
    __IO uint32_t scs;               /**< \brief 系统控制/状态寄存器  */
    __IO uint32_t irctrim;           /**< \brief IRC调整寄存器                 */
    __IO uint32_t pclksel;           /**< \brief 外设时钟选择寄存器     */
         uint32_t reserved9;         /**< \brief 保留，不应使用               */
    __IO uint32_t pboost;            /**< \brief 功率提升控制寄存器     */
    __IO uint32_t spificlksel;       /**< \brief SPIFI时钟选择寄存器  */
    __IO uint32_t lcd_cfg;           /**< \brief LCD时钟配制寄存器        */
         uint32_t reserved10;        /**< \brief 保留，不应使用               */
    __IO uint32_t usbintst;          /**< \brief USB中断状态寄存器    */
    __IO uint32_t dmareqsel;         /**< \brief DMA请求源选择寄存器  */
    __IO uint32_t clkoutcfg;         /**< \brief 时钟输出配置寄存器   */
    __IO uint32_t rstcon0;           /**< \brief 复位控制寄存器0   */
    __IO uint32_t rstcon1;           /**< \brief 复位控制寄存器1   */
         uint32_t reserved11[2];     /**< \brief 保留，不应使用           */
    __IO uint32_t emcdlyctl;         /**< \brief EMC延迟控制寄存器    */
    __IO uint32_t emccal;            /**< \brief EMC校准寄存器             */
} amhw_syscon_t;


/**
 * \name 复位源定义
 * @{
 */

#define AMHW_SYSCON_RSID_POR       (1 << 0)      /**< \brief 上电复位             */
#define AMHW_SYSCON_RSID_EXTR      (1 << 1)      /**< \brief 外部管脚（RESET）复位 */
#define AMHW_SYSCON_RSID_WDTR      (1 << 2)      /**< \brief 看门狗复位          */
#define AMHW_SYSCON_RSID_BODR      (1 << 3)      /**< \brief 掉电检测复位          */
#define AMHW_SYSCON_RSID_SYSRESET  (1 << 4)      /**< \brief 系统请求复位          */
#define AMHW_SYSCON_RSID_LOCKUP    (1 << 5)      /**< \brief 处理器锁定复位      */


/** @} */

/**
 * \brief 得到复位源
 * \return 复位源,值为AMHW_SYSCON_RSID_*(如：#AMHW_SYSCON_RSID_WDTR)
 */
am_static_inline
uint32_t amhw_syscon_rsid_get (void)
{
    return (AMHW_SYSCON->rsid & 0x0F);
}

/**
 * \brief 检测复位源是否是某个指定的复位源
 * \param[in] rsid : 待检测的复位源，AMHW_SYSCON_RSID_*如(#AMHW_SYSCON_RSID_WDTR)
 * \retval TRUE    : 复位源是指定的待检测的复位源
 * \retval FALSE   : 复位源不是指定的待检测的复位源
 */
am_static_inline
bool_t amhw_syscon_rsid_chk (uint32_t rsid)
{
    return (bool_t)((AMHW_SYSCON->rsid & rsid) != 0);
}

/**
 * \brief 清除指定的复位源
 * \param[in] rsid : 待检测的复位源，AMHW_SYSCON_RSID_*如(#AMHW_SYSCON_RSID_WDTR)
 * \return    无
 */
am_static_inline
void amhw_syscon_rsid_clr (uint32_t rsid)
{
    AMHW_SYSCON->rsid |= rsid;
}

/**
 * \name EINT中断源定义
 * @{
 */

#define AMHW_SYSCON_EINT0  (1 << 0)    /**< \brief 外部中断0        */
#define AMHW_SYSCON_EINT1  (1 << 1)    /**< \brief 外部中断1        */
#define AMHW_SYSCON_EINT2  (1 << 2)    /**< \brief 外部中断2        */
#define AMHW_SYSCON_EINT3  (1 << 3)    /**< \brief 外部中断3        */

/** @} */

/**
 * \brief 得到外部中断的状态
 * \return 相应位为1，表明外部中断处于激活状态
 */
am_static_inline
uint32_t amhw_syscon_eint_get (void)
{
    return (AMHW_SYSCON->extint & 0x0F);
}

/**
 * \brief 检测指定外部中断是否处于激活态
 * \param[in] eint_id : 待检测的外部中断，AMHW_SYSCON_EINT*如(#AMHW_SYSCON_EINT0)
 * \retval TRUE       : 外部中断处于激活状态
 * \retval FALSE      : 外部中断未处于激活状态
 */
am_static_inline
bool_t amhw_syscon_eint_chk (uint32_t eint_id)
{
    return (bool_t)((AMHW_SYSCON->extint & eint_id) != 0);
}

/**
 * \brief 清除指定外部中断的状态
 * \param[in] eint_id : AMHW_SYSCON_EINT*值或多个宏的值，如：(#AMHW_SYSCON_EINT3)
 * \return    无
 */
am_static_inline
void amhw_syscon_eint_clr (uint32_t eint_id)
{
    AMHW_SYSCON->extint = eint_id & 0x0F;
}

/**
 * \name EINT模式
 * @{
 */

#define AMHW_SYSCON_EINTMODE_LEVEL  0    /**< \brief 电平有效     */
#define AMHW_SYSCON_EINTMODE_EDGE   1    /**< \brief 边沿有效     */
 
/** @} */

/**
 * \brief 设置EXTINT的模式
 * \param[in] eint_id : AMHW_SYSCON_EINT*值或多个宏的值，如：(#AMHW_SYSCON_EINT3)
 * \param[in] mode    : AMHW_SYSCON_EINTMODE_LEVEL 或者 AMHW_SYSCON_EINTMODE_EDGE
 * \return None
 */
am_static_inline
void amhw_syscon_eintmode_set (uint32_t eint_id, uint32_t mode)
{
    if (mode == AMHW_SYSCON_EINTMODE_EDGE) {
        AMHW_SYSCON->extmode |= eint_id;
    } else {
        AMHW_SYSCON->extmode &= ~eint_id;
    }
}

/**
 * \name EINT模式
 * @{
 */

#define AMHW_SYSCON_EINTPOLAR_1   1    /**< \brief 高电平或上升沿（依赖模式）     */
#define AMHW_SYSCON_EINTPOLAR_0   0    /**< \brief 低电平或下降沿（依赖模式）     */
 
/** @} */

/**
 * \brief 设置EXTINT的极性
 * \param[in] eint_id : AMHW_SYSCON_EINT*值或多个宏的值，如：(#AMHW_SYSCON_EINT3)
 * \param[in] polar   : AMHW_SYSCON_EINTPOLAR_0 或者 AMHW_SYSCON_EINTPOLAR_1
 * \return None
 */
am_static_inline
void amhw_syscon_eintpolar_set (uint32_t eint_id, uint32_t polar)
{
    if (polar == AMHW_SYSCON_EINTPOLAR_1) {
        AMHW_SYSCON->extpolar |= eint_id;
    } else {
        AMHW_SYSCON->extpolar &= ~eint_id;
    }
}

/**
 * \name 主晶振(main oscillator)的范围
 * @{
 */

#define AMHW_SYSCON_OSCRANGE_1_20MHz    0    /**< \brief 范围是1  ~ 20MHz     */
#define AMHW_SYSCON_OSCRANGE_15_25MHz   1    /**< \brief 范围是15 ~ 25MHz     */
 
/** @} */

/**
 * \brief 设置主振荡器(main oscillator)的范围
 * \param[in] range : AMHW_SYSCON_OSCRANGE_1_20MHz 或者 AMHW_SYSCON_OSCRANGE_15_25MHz
 * \return 无
 */
am_static_inline
void amhw_syscon_oscrange_set (uint32_t range)
{
    if (range == AMHW_SYSCON_OSCRANGE_15_25MHz) {
        AMHW_SYSCON->scs |= (1 << 4);
    } else {
        AMHW_SYSCON->scs &= ~(1 << 4);
    }
}


/**
 * \brief 使能主振荡器(main oscillator)
 * \return 无
 */
am_static_inline
void amhw_syscon_osc_enable (void)
{
    AMHW_SYSCON->scs |= (1 << 5);
}

/**
 * \brief 禁能主振荡器(main oscillator)
 * \return 无
 */
am_static_inline
void amhw_syscon_osc_disable (void)
{
    AMHW_SYSCON->scs &= ~(1 << 5);
}


/**
 * \brief 检测主振荡器是否准备就绪
 * \retval TRUE  : 准备就绪，可以被用作其它时钟的时钟源
 * \retval FALSE : 未准备就绪，不能用作其它时钟的时钟源
 */
am_static_inline
bool_t amhw_syscon_osc_ready_chk (void)
{
    return (bool_t)((AMHW_SYSCON->scs & (1 << 6)) != 0);
}


/**
 * \name 复位控制寄存器0--复位控制位定义
 * @{
 */
#define AMWH_RSTCON0_LCD     (1 << 0)       /**< \brief LCD控制器复位 */
#define AMWH_RSTCON0_TIM0    (1 << 1)       /**< \brief 定时器/计数器0复位 */
#define AMWH_RSTCON0_TIM1    (1 << 2)       /**< \brief 定时器/计数器1复位 */
#define AMWH_RSTCON0_UART0   (1 << 3)       /**< \brief UART0复位 */
#define AMWH_RSTCON0_UART1   (1 << 4)       /**< \brief UART1复位 */
#define AMWH_RSTCON0_PWM0    (1 << 5)       /**< \brief PWM0复位 */
#define AMWH_RSTCON0_PWM1    (1 << 6)       /**< \brief PWM1复位 */
#define AMWH_RSTCON0_I2C0    (1 << 7)       /**< \brief I2C0复位 */
#define AMWH_RSTCON0_UART4   (1 << 8)       /**< \brief UART4复位 */
#define AMWH_RSTCON0_RTC     (1 << 9)       /**< \brief RTC和事件监视器复位 */
#define AMWH_RSTCON0_SSP1    (1 << 10)      /**< \brief SSP1复位 */
#define AMWH_RSTCON0_EMC     (1 << 11)      /**< \brief EMC复位 */
#define AMWH_RSTCON0_ADC     (1 << 12)      /**< \brief ADC复位 */
#define AMWH_RSTCON0_CAN1    (1 << 13)      /**< \brief CAN1复位 */
#define AMWH_RSTCON0_CAN2    (1 << 14)      /**< \brief CAN2复位 */
#define AMWH_RSTCON0_GPIO    (1 << 15)      /**< \brief GPIO复位 */

#define AMWH_RSTCON0_MCPWM   (1 << 17)      /**< \brief MCPWM复位 */
#define AMWH_RSTCON0_QEI     (1 << 18)      /**< \brief QEI复位 */
#define AMWH_RSTCON0_I2C1    (1 << 19)      /**< \brief I2C1复位 */
#define AMWH_RSTCON0_SSP2    (1 << 20)      /**< \brief SSP2复位 */
#define AMWH_RSTCON0_SSP0    (1 << 21)      /**< \brief SSP0复位 */
#define AMWH_RSTCON0_TIM2    (1 << 22)      /**< \brief TIM2复位 */
#define AMWH_RSTCON0_TIM3    (1 << 23)      /**< \brief TIM3复位 */
#define AMWH_RSTCON0_UART2   (1 << 24)      /**< \brief UART2复位 */
#define AMWH_RSTCON0_UART3   (1 << 25)      /**< \brief UART3复位 */
#define AMWH_RSTCON0_I2C2    (1 << 26)      /**< \brief I2C2复位 */
#define AMWH_RSTCON0_I2S     (1 << 27)      /**< \brief I2S复位 */
#define AMWH_RSTCON0_SDC     (1 << 28)      /**< \brief SD卡复位 */
#define AMWH_RSTCON0_GPDMA   (1 << 29)      /**< \brief GPDMA复位 */
#define AMWH_RSTCON0_ENET    (1 << 30)      /**< \brief 以太网复位 */
#define AMWH_RSTCON0_USB     (1 << 31)      /**< \brief USB复位 */

/** @} */

/**
 * \brief  外设复位寄存器0--指定外设复位
 * \param[in] per : 外设编号，值为AMHW_SYSCON_RST*(如#AMHW_RSTCON0_LCD)
 *
 * \return 无
 */
am_static_inline
void amhw_syscon_periph_reset0 (uint32_t per)
{
   AMHW_SYSCON->rstcon0 |= per;
   AMHW_SYSCON->rstcon0 &= ~per;
}


/**
 * \name 复位控制寄存器1--复位控制位定义
 * @{
 */
#define AMWH_RSTCON1_IOCON     (1 << 0)     /**< \brief IOCON寄存器复位 */
#define AMWH_RSTCON1_DAC       (1 << 1)     /**< \brief DAC转换器复位 */
#define AMWH_RSTCON1_CANACC    (1 << 2)     /**< \brief CAN接收滤波器复位 */
/** @} */
/**
 * \brief  外设复位寄存器1--指定外设复位
 * \param[in] per : 外设编号，值为AMHW_SYSCON_RST*(如#AMHW_RSTCON1_IOCON)
 *
 * \return 无
 */
am_static_inline
void amhw_syscon_periph_reset1 (uint32_t per)
{
   AMHW_SYSCON->rstcon1 |= per;
   AMHW_SYSCON->rstcon1 &= ~per;
}

/**
 * \brief 设置FLASH加速器
 * \param[in] cpu_freq : 系统时钟频率，单位Hz
 * \return 无
 */
am_static_inline
void amhw_syscon_flash_cfg (uint32_t cpu_freq)
{
    if (cpu_freq <= 20000000) {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (0 << 12);
    } else if (cpu_freq <= 40000000) {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (1 << 12);
    } else if (cpu_freq <= 60000000) {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (2 << 12);
    } else if (cpu_freq <= 80000000) {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (3 << 12);
    } else {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (4 << 12);
    }
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_SYSCON_H */

/* end of file */
