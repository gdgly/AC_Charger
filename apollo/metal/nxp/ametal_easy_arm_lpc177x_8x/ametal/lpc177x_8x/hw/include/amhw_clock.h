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
 * \brief 时钟选择和控制接口
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_CLOCK_H
#define __AMHW_CLOCK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"

/**
 * \addtogroup amhw_if_clock
 * \copydoc amhw_clock.h
 * @{
 */

extern uint32_t g_system_clkfreq;      /**< \brief 主时钟的频率（单位:Hz）  */
extern uint32_t g_pclk_freq;           /**< \brief 外设时钟频率（单位:Hz）    */
/**
 * \name 频率值定义
 * @{
 */
 
#define AMHW_CLOCK_FREQ_OSC      12000000UL   /**< \brief 主振荡器频率(默认设置) */
#define AMHW_CLOCK_FREQ_RTC      32768UL      /**< \brief RTC振荡器频率    */
#define AMHW_CLOCK_FREQ_IRC      12000000UL   /**< \brief 内部IRC频率      */
#define AMHW_CLOCK_FREQ_WWDT     500000UL     /**< \brief WWDT时钟频率      */
/** @} */


/**
 * \brief 获取IRC时钟频率
 * \return IRC时钟频率
 */
am_static_inline
uint32_t amhw_clock_freq_irc_get (void)
{
    return AMHW_CLOCK_FREQ_IRC;
}

/**
 * \brief 获取主振荡器的时钟频率
 * \return 主振荡器的时钟频率
 */
uint32_t amhw_clock_freq_osc_get (void);

/**
 * \brief 设置主振荡器的时钟频率
 * \param[in] 主振荡器的时钟频率
 */
void amhw_clock_freq_osc_set (uint32_t osc_freq);

/**
 * \brief 获取RTC振荡器的时钟频率
 * \return RTC振荡器的时钟频率
 */
am_static_inline
uint32_t amhw_clock_freq_rtc_get (void)
{
    return AMHW_CLOCK_FREQ_RTC;
}

/**
 * \brief 获取窗口看门狗（WWDT）的时钟频率
 * \return WWDT的时钟频率
 */
am_static_inline
uint32_t amhw_clock_freq_wwdt_get (void)
{
    return AMHW_CLOCK_FREQ_WWDT;
}

/**
 * \brief 更新系统时钟全局变量的值 g_system_clkfreq
 * \return 无
 */
void amhw_clock_freq_update(void);
    

/**
 * \brief 获取PLL0的输入时钟频率
 * \return PLL0的输入时钟频率
 */
uint32_t amhw_clock_freq_pll0in_get(void);

/**
 * \brief 获取PLL0的输出时钟频率
 * \return PLL0的输出时钟频率
 */
uint32_t amhw_clock_freq_pll0out_get(void);

/**
 * \brief 获取PLL1的输入时钟频率
 * \return PLL0的输入时钟频率
 */
am_static_inline
uint32_t amhw_clock_freq_pll1in_get (void)
{
    return amhw_clock_freq_osc_get();
}

/**
 * \brief 获取PLL1的输出时钟频率
 * \return PLL1的输出时钟频率
 */
uint32_t amhw_clock_freq_pll1out_get(void);

/**
 * \name PLL0输入时钟源定义
 * PLL0输入时钟源，在时钟树中，标志为sysclk，当使用USB时钟使用PLL0输出路径时，
 * PLL0的输入时钟必须为OSC，当CAN时钟频率超过100kbit/s时，不应使用IRC作为
 * PLL0时钟源
 * @{
 */

#define AMHW_CLOCK_PLL0_INSRC_IRC   0   /**< \brief 选择内部IRC作为PLL0输入    */ 
#define AMHW_CLOCK_PLL0_INSRC_OSC   1   /**< \brief 选择主振荡器作为PLL0输入   */

/** @} */

/**
 * \brief 设置PLL0的输入时钟源
 * \param[in] insrc ： 值AMHW_CLOCK_PLL0_INSRC_* 如(#AMHW_CLOCK_PLL0_INSRC_OSC)
 * \return 无
 */
am_static_inline
void amhw_clock_pll0_insrc_set (uint32_t insrc)
{
    AMHW_SYSCON->clksrcsel = insrc & 0x01;
}

/**
 * \brief 使能PLL0
 * \return 无
 */
am_static_inline
void amhw_clock_pll0_enable (void)
{
    AMHW_SYSCON->pll0con |= 0x01;
}

/**
 * \brief 禁能PLL0
 * \return 无
 */
am_static_inline
void amhw_clock_pll0_disable (void)
{
    AMHW_SYSCON->pll0con &= ~0x01;
}

/**
 * \brief 配置PLL0，设置分频值和倍频值,PLL的输出频率应该固定为48MHz
 *
 * PLL0的输入时钟固定为OSC,m_sel * Fosc = 48MHz
 * 同时： FCCO / 2P = 48MHz -> FCCO = 2 * p_sel * 48MHz = 2 * p_sel * m_sel * Fosc
 *
 * \param[in] m_sel : PLL0倍频值
 * \param[in] p_sel ：PLL0分频值,只能是1、2、4、8
 * \return 无
 */
am_static_inline
void amhw_clock_pll0_cfg (uint32_t m_sel, uint32_t p_sel)
{
    if (p_sel == 8) {
        AMHW_SYSCON->pll0cfg = ((m_sel - 1) & 0x1F) | (3 << 5);
    } else {  /* pse = 1,2,4 */
        AMHW_SYSCON->pll0cfg = ((m_sel - 1) & 0x1F) | (((p_sel >> 1) & 0x03) << 5);
    }
}

/**
 * \brief 获取PLL0当前使用的MSEL值
 * \return PLL0当前使用的MSEL值
 */
am_static_inline
uint32_t amhw_clock_pll0_msel_get (void)
{
    return (AMHW_SYSCON->pll0stat & 0x1F) + 1;
}

/**
 * \brief 获取PLL0当前使用的pSEL值
 * \return PLL0当前使用的PSEL值
 */
am_static_inline
uint32_t amhw_clock_pll0_psel_get (void)
{
    return (1 << ((AMHW_SYSCON->pll0stat >> 5) & 0x3));
}

/**
 * \brief 检测PLL0当前的使能状态
 * \return TRUE   ： PLL0已经使能
 * \retval FALSE  : PLL0未使能
 */
am_static_inline
bool_t amhw_clock_pll0_enable_chk (void)
{
    return (bool_t)((AMHW_SYSCON->pll0stat & (1 << 8)) != 0);
}

/**
 * \brief 检测当前PLL0是否锁定
 * \return TRUE   ： PLL0已锁定
 * \retval FALSE  :  PLL0未锁定
 */
am_static_inline
bool_t amhw_clock_pll0_lock_chk (void)
{
    return (bool_t)((AMHW_SYSCON->pll0stat & (1 << 10)) != 0);
}

/**
 * \brief FEED PLL0
 *
 * 只有FEED PLL0后，配置的值才会真正起作用，建议FEED操作时关闭中断。
 *
 * \return TRUE   ： PLL0已锁定
 * \retval FALSE  :  PLL0未锁定
 */
am_static_inline
void amhw_clock_pll0_feed (void)
{
    AMHW_SYSCON->pll0feed = 0xAA;
    AMHW_SYSCON->pll0feed = 0x55;
}

/******************************************************************************/

/**
 * \brief 使能PLL1
 * \return 无
 * \note 使能和连接PLL1后，PLL1输出时钟将自动作为USB的输入时钟
 */
am_static_inline
void amhw_clock_pll1_enable (void)
{
    AMHW_SYSCON->pll1con |= 0x01;
}

/**
 * \brief 禁能PLL1
 * \return 无
 */
am_static_inline
void amhw_clock_pll1_disable (void)
{
    AMHW_SYSCON->pll1con &= ~0x01;
}

/**
 * \brief 检测PLL1当前的使能状态
 * \return TRUE   ： PLL1已经使能
 * \retval FALSE  :  PLL1未使能
 */
am_static_inline
bool_t amhw_clock_pll1_enable_chk (void)
{
    return (bool_t)((AMHW_SYSCON->pll1stat & (1 << 8)) != 0);
}

/**
 * \brief 检测当前PLL1是否锁定
 * \return TRUE   ： PLL1已锁定
 * \retval FALSE  :  PLL1未锁定
 */
am_static_inline
bool_t amhw_clock_pll1_lock_chk (void)
{
    return (bool_t)((AMHW_SYSCON->pll1stat & (1 << 10)) != 0);
}

/**
 * \brief 配置PLL1，设置分频值和倍频值,PLL的输出频率应该固定为48MHz
 *
 * PLL1的输入时钟固定为OSC,m_sel * Fosc = 48MHz
 * 同时： FCCO / 2P = 48MHz -> FCCO = 2 * p_sel * 48MHz = 2 * p_sel * m_sel * Fosc
 *
 * \param[in] m_sel : PLL0倍频值
 * \param[in] p_sel ：PLL0分频值,只能是1、2、4、8
 * \return 无
 */
am_static_inline
void amhw_clock_pll1_cfg (uint32_t m_sel, uint32_t p_sel)
{
    if (p_sel == 8) {
        AMHW_SYSCON->pll1cfg = ((m_sel - 1) & 0x1F) | (3 << 5);
    } else {  /* pse = 1,2,4 */
        AMHW_SYSCON->pll1cfg = ((m_sel - 1) & 0x1F) | (((p_sel >> 1) & 0x03) << 5);
    }
}

/**
 * \brief 获取PLL1当前使用的MSEL值
 * \return PLL1当前使用的MSEL值
 */
am_static_inline
uint32_t amhw_clock_pll1_msel_get (void)
{
    return (AMHW_SYSCON->pll1stat & 0x1F) + 1;
}

/**
 * \brief 获取PLL1当前使用的P值
 * \return PLL1当前使用的P值
 */
am_static_inline
uint32_t amhw_clock_pll1_psel_get (void)
{
    return (1 << ((AMHW_SYSCON->pll1stat >> 5) & 0x3));
}

/**
 * \brief FEED PLL1
 *
 * 只有FEED PLL1后，配置的值才会真正起作用，建议FEED操作时关闭中断。
 *
 * \return 无
 */
am_static_inline
void amhw_clock_pll1_feed (void)
{
    AMHW_SYSCON->pll1feed = 0xAA;
    AMHW_SYSCON->pll1feed = 0x55;
}

/******************************************************************************/
/**
 * \name CCLK时钟源
 * @{
 */
#define AMHW_CLOCK_CCLK_SRC_SYSCLK    0   /**< \brief 选择系统时钟作为CCLK输入    */
#define AMHW_CLOCK_CCLK_SRC_MAINPLL   1   /**< \brief 选择主PLL作为CCLK输入    */
/** @} */

/**
 * \brief CPU CLK的时钟源选择
 *
 * \param[in] src : CCLK时钟源，值为(#AMHW_CLOCK_CCLK_SRC_SYSCLK)或
 *                                 (#AMHW_CLOCK_CCLK_SRC_MAINPLL)
 * \return 无
 */
am_static_inline
void amhw_clock_cclk_src_set (uint8_t src)
{
    if (src == AMHW_CLOCK_CCLK_SRC_SYSCLK) {
        AMHW_SYSCON->cclksel &= ~(1 << 8);
    } else {
        AMHW_SYSCON->cclksel |= (1 << 8);
    }
}

/**
 * \brief 设置PLL0到CPU CLK的时钟分频
 *
 * PLL0时钟经过该分频值分频后作为CPU时钟,当使用USB时，分频后时钟至少为18MHZ
 *
 * \param[in] div : 若MCU为LPC175X_6X,则分频值： 1 ~ 256
 *                  若MCU为LPC177X_8X,则分频值： 0 ~ 31，为0时，分频器关闭，不提供时钟
 * \return 无
 */
am_static_inline
void amhw_clock_cclk_div_set (uint16_t div)
{
    uint32_t temp;
    temp = AMHW_SYSCON->cclksel & (1 << 8);

    AMHW_SYSCON->cclksel = temp | (div & 0x1F);

}

/**
 * \brief CPU CLK的时钟分频
 * 
 * \return 时钟分频值
 */
am_static_inline
uint32_t amhw_clock_cclk_div_get (void)
{
    return (AMHW_SYSCON->cclksel & 0x1F);
}

/******************************************************************************/
/**
 * \name USB时钟源
 * @{
 */
#define AMHW_CLOCK_USBSRC_SYSCLK  0  /**< \brief 系统时钟被用作USB时钟分频器的输入  */
#define AMHW_CLOCK_USBSRC_PLL0    1  /**< \brief 主PLL被用作USB时钟分频器的输入         */
#define AMHW_CLOCK_USBSRC_PLL1    2  /**< \brief 副PLL被用作USB时钟分频器的输入         */
/** @} */

/**
 * \brief 设置USB时钟源
 * \param[in] src : USB CLK时钟源，值为(#AMHW_CLOCK_USBSRC_SYSCLK)或(#AMHW_CLOCK_USBSRC_PLL0)
 *                  或(#AMHW_CLOCK_USBSRC_PLL1)
 * \param[in] div : 时钟分频，值为 0,1,2,3
 * \return 无
 */
am_static_inline
void amhw_clock_usbclk_set (uint8_t src, uint8_t div)
{
    AMHW_SYSCON->usbclksel = ((src & 0x03) << 8) | (div & 0x03);
}

/**
 * \brief 获取USB时钟选择寄存器值
 * \return USB时钟选择寄存器值
 */
am_static_inline
uint32_t amhw_clock_usbclk_get (void)
{
    return AMHW_SYSCON->usbclksel;
}

/******************************************************************************/
/**
 * \name EMC时钟分频
 * @{
 */
#define AMHW_CLOCK_EMC_DIV0 0  /**< \brief EMC和CPU使用同个时钟      */
#define AMHW_CLOCK_EMC_DIV2 1  /**< \brief EMC时钟为CPU时钟的一半 */
/** @} */

/**
 * \brief 设置EMC的时钟
 * \param[in] clk : EMC的时钟，值为(#AMHW_CLOCK_EMC_DIV0)或(#AMHW_CLOCK_EMC_DIV2)
 * \return 无
 */
am_static_inline
void amhw_clock_emcclk_set (uint16_t clk)
{
    AMHW_SYSCON->emcclksel =  clk & 0xF;
}

/**
 * \brief 获取EMC的时钟
 * \retval AMHW_CLOCK_EMC_DIV0: EMC和CPU使用同个时钟
 * \retval AMHW_CLOCK_EMC_DIV2: EMC时钟为CPU时钟的一半
 */
am_static_inline
uint32_t amhw_clock_emcclk_get (void)
{
    return AMHW_SYSCON->emcclksel & 0x01;
}

/**
 * \brief 设置LCD时钟分频
 * \param[in] div : LCD时钟分频值，最小为1
 * \return 无
 */
am_static_inline
void amhw_clock_lcdclk_div_set (uint8_t div)
{
    AMHW_SYSCON->lcd_cfg = (div - 1);
}

/**
 * \brief 获取LCD时钟分频
 * \return LCD时钟分频值
 */
am_static_inline
uint32_t amhw_clock_lcdclk_div_get (void)
{
    return (AMHW_SYSCON->lcd_cfg & 0x1F) + 1;
}

/******************************************************************************/
/**
 * \brief 设置外设的输入频率
 * \param[in] div  : 时钟分频，值为0~31.为0时，不提供外设时钟
 * \return 无
 */
am_static_inline
void amhw_clock_pclk_div_set (uint32_t div)
{
    AMHW_SYSCON->pclksel = div;
}

/**
 * \brief 获取外设时钟的分频
 * \return 外设时钟分频值
 */
am_static_inline
uint32_t amhw_clock_pclk_div_get (void)
{
    return AMHW_SYSCON->pclksel & 0x1F;
}

/**
 * \brief 获取外设时钟频率
 * \return 外设时钟频率
 */
uint32_t amhw_clock_freq_pclk_get (void);

/******************************************************************************/
/**
 * \name CLKOUT时钟源定义
 * @{
 */

#define AMHW_CLOCK_CLKOUT_CCLK    0        /**< \brief CPU时钟         */
#define AMHW_CLOCK_CLKOUT_OSCCLK  1        /**< \brief OSC时钟         */
#define AMHW_CLOCK_CLKOUT_IRC     2        /**< \brief IRC时钟         */
#define AMHW_CLOCK_CLKOUT_USB     3        /**< \brief USB时钟         */
#define AMHW_CLOCK_CLKOUT_RTC     4        /**< \brief RTC时钟         */
#define AMHW_CLOCK_CLKOUT_SPIFI   5        /**< \brief SPIFI时钟    */
#define AMHW_CLOCK_CLKOUT_WDT     6        /**< \brief WDT时钟         */

/** @} */

/**
 * \brief 配置CLKOUT的时钟源和输出时钟分频
 * \param[in] clksrc : 时钟源，宏AMHW_CLOCK_CLKOUT_*值，如#AMHW_CLOCK_CLKOUT_OSCCLK
 * \param[in] clkdiv : 时钟分频，有效值1 ~ 16
 * \return    无
 */
void amhw_clock_clkout_cfg(uint32_t clksrc,uint8_t clkdiv);

/**
 * \brief 检测CLKOUT管脚是否有输出时钟
 * \retval TRUE  : 正在输出中
 * \retval FALSE : 未输出时钟
 */
am_static_inline
bool_t amhw_clock_clkout_chk (void)
{
    return (bool_t)((AMHW_SYSCON->clkoutcfg & (1 << 9)) != 0);
}

/**
 * \brief 使能CLKOUT输出
 * \return 无
 */
am_static_inline
void amhw_clock_clkout_enable(void)
{
    AMHW_SYSCON->clkoutcfg |= (1 << 8);
}
   
/**
 * \brief 禁能BOD复位
 * \return 无
 */
am_static_inline
void amhw_clock_clkout_disable(void)
{
    AMHW_SYSCON->clkoutcfg &= ~(1 << 8);
}


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_CLOCK_H */

/* end of file */
