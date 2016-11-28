/*******************************************************************************
*                                 AWorks
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
 * \brief LCD硬件操作接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-19  cod, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LCD_H
#define __AMHW_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_common.h"

/**
 * \addtogroup amhw_if_lcd
 * \copydoc amhw_lcd.h
 * @{
 */

/**
 * \brief LCD控制器寄存器块结构体
 */
typedef struct amhw_lcd {
    __IO uint32_t timh;           /**< \brief 水平时序控制寄存器                  */
    __IO uint32_t timv;           /**< \brief 垂直时序控制寄存器                  */
    __IO uint32_t pol;            /**< \brief 时钟和信号极性控制寄存器   */
    __IO uint32_t le;             /**< \brief 行末控制寄存器                 */
    __IO uint32_t upbase;         /**< \brief 上屏帧基址寄存器            */
    __IO uint32_t lpbase;         /**< \brief 下屏帧基址寄存器            */
    __IO uint32_t ctrl;           /**< \brief LCD控制寄存器                    */
    __IO uint32_t intmsk;         /**< \brief 中断屏蔽寄存器                  */
    __I  uint32_t intraw;         /**< \brief 原始中断状态寄存器         */
    __I  uint32_t intstat;        /**< \brief 已屏蔽中断状态寄存器     */
    __O  uint32_t intclr;         /**< \brief 中断清除寄存器                    */
    __I  uint32_t upcurr;         /**< \brief 上屏当前地址值寄存器      */
    __I  uint32_t lpcurr;         /**< \brief 下屏当前地址值寄存器      */
         uint32_t reserved0[115]; /**< \brief 保留      */
    __IO uint32_t pal[128];       /**< \brief 256×16位彩色调色板寄存器   */
         uint32_t reserved1[256]; /**< \brief 保留                                   */
    __IO uint32_t crsr_img[256];  /**< \brief 光标图像寄存器           */
    __IO uint32_t crsr_ctrl;      /**< \brief 光标控制寄存器           */
    __IO uint32_t crsr_cfg;       /**< \brief 光标配置寄存器            */
    __IO uint32_t crsr_pal0;      /**< \brief 光标调色板寄存器0  */
    __IO uint32_t crsr_pal1;      /**< \brief 光标调色板寄存器1  */
    __IO uint32_t crsr_xy;        /**< \brief 光标XY位置寄存器        */
    __IO uint32_t crsr_clip;      /**< \brief 光标剪辑位置寄存器    */
         uint32_t reserved2[2];   /**< \brief 保留       */
    __IO uint32_t crsr_intmsk;    /**< \brief 光标中断屏蔽寄存器      */
    __O  uint32_t crsr_intclr;    /**< \brief 光标中断清除寄存器      */
    __I  uint32_t crsr_intraw;    /**< \brief 光标原始中断状态寄存器      */
    __I  uint32_t crsr_intstat;   /**< \brief 光标已屏蔽中断状态寄存器  */
} amhw_lcd_t;

#define AMHW_LCD_PWR_DIS_DLY  10000UL   /**< \brief LCD上电断电延时           */

/**
 * \name LCD控制位定义
 * \anchor grp_amhw_lcd_ctrl_flags
 * @{
 */
#define AMHW_LCD_DISABLE         (0)      /**< \brief LCD禁止  */
#define AMHW_LCD_ENABLE          (1 << 0) /**< \brief LCD使能  */

#define AMHW_LCD_BPP_1           (0 << 1) /**< \brief 1bpp  */
#define AMHW_LCD_BPP_2           (1 << 1) /**< \brief 2bpp  */
#define AMHW_LCD_BPP_4           (2 << 1) /**< \brief 4bpp  */
#define AMHW_LCD_BPP_8           (3 << 1) /**< \brief 8bpp  */
#define AMHW_LCD_BPP_16          (4 << 1) /**< \brief 16bpp */
#define AMHW_LCD_BPP_24          (5 << 1) /**< \brief 24bpp（仅为TFT显示屏）*/
#define AMHW_LCD_BPP_16_565Mode  (6 << 1) /**< \brief 16bpp 5:6:5模式 */
#define AMHW_LCD_BPP_12_444Mode  (7 << 1) /**< \brief 12bpp 4:4:4模式 */

#define AMHW_LCD_STN_COLOR       (0)      /**< \brief STN LCD是彩色 */
#define AMHW_LCD_STN_MONO        (1 << 4) /**< \brief STN LCD是单色 */

#define AMHW_LCD_TYPE_STN        (0)      /**< \brief LCD为STN显示屏 */
#define AMHW_LCD_TYPE_TFT        (1 << 5) /**< \brief LCD为TFT显示屏 */

#define AMHW_LCD_STN_MONO_4BIT   (0)      /**< \brief 单色STN LCD使用4位并行接口  */
#define AMHW_LCD_STN_MONO_8BIT   (1 << 6) /**< \brief 单色STN LCD使用8位并行接口  */

#define AMHW_LCD_SINGLE_PANEL    (0)      /**< \brief 单屏 */
#define AMHW_LCD_DUAL_PANEL      (1 << 7) /**< \brief 双屏 */

#define AMHW_LCD_COLOR_FORMAT_RGB (0)      /**< \brief RGB(正常输出) */
#define AMHW_LCD_COLOR_FORMAT_BGR (1 << 8) /**< \brief BGR(红蓝交换) */

#define AMHW_LCD_BYTE_LITTLE_ENDIAN (0)      /**< \brief 内存字节小端模式 */
#define AMHW_LCD_BYTE_BIG_ENDIAN    (1 << 9) /**< \brief 内存字节大端模式*/

#define AMHW_LCD_PIXEL_LITTLE_ENDIAN  (0)       /**< \brief 字节象素小端模式 */
#define AMHW_LCD_PIXEL_BIG_ENDIAN     (1 << 10) /**< \brief 字节象素大端模式 */

#define AMHW_LCD_PWR_ENABLE          (1 << 11) /**< \brief LCD电源使能 */
#define AMHW_LCD_PWR_DISABLE         (0)       /**< \brief LCD电源失能 */

#define AMHW_LCD_VCOMP_VERTICAL_SYNC (0 << 12) /**< \brief VComp中断垂直同步开始 */
#define AMHW_LCD_VCOMP_BACK_PORCH    (1 << 12) /**< \brief VComp中断后沿开始 */
#define AMHW_LCD_VCOMP_ACTIVE_VIDEO  (2 << 12) /**< \brief VComp中断有效视频开始 */
#define AMHW_LCD_VCOMP_FRONT_PORCH   (3 << 12) /**< \brief VComp中断前沿开始*/

#define AMHW_LCD_DMA_FIFO_EMPTY4   (0)       /**< \brief FIFO >=4个空单元产生DMA请求 */
#define AMHW_LCD_DMA_FIFO_EMPTY8   (1 << 16) /**< \brief FIFO >=8个空单元产生DMA请求 */
/** @} */

/**
 * \brief LCD配置
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : LCD配置信息,参见\ref grp_amhw_lcd_ctrl_flags "LCD CTRL FLAG"
 * \return 无
 */
am_static_inline
void amhw_lcd_ctrl_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl = flag;
}

/**
 * \brief LCD使能
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_lcd_enable (amhw_lcd_t *p_hw_lcd)
{
    p_hw_lcd->ctrl |= AMHW_LCD_ENABLE;
}

/**
 * \brief LCD失能
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_lcd_disable (amhw_lcd_t *p_hw_lcd)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_ENABLE;
}

/**
 * \brief LCD电源使能
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_lcd_power_on (amhw_lcd_t *p_hw_lcd)
{
    volatile int i;
    p_hw_lcd->ctrl |= AMHW_LCD_ENABLE ;
    for (i = 0; i < AMHW_LCD_PWR_DIS_DLY; i++);
    p_hw_lcd->ctrl |= AMHW_LCD_PWR_ENABLE;
}

/**
 * \brief LCD电源失能
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_lcd_power_off (amhw_lcd_t *p_hw_lcd)
{
    volatile int i;
    p_hw_lcd->ctrl &= ~AMHW_LCD_PWR_ENABLE;
    for (i = 0; i < AMHW_LCD_PWR_DIS_DLY; i++);
    p_hw_lcd->ctrl &= ~AMHW_LCD_ENABLE;
}

/**
 * \brief LCD象素位数设置
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : LCD象素需要的位数,值为AMHW_LCD_BPP_*(#AMHW_LCD_BPP_1)
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_bpp_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~(0x7 << 1);
    p_hw_lcd->ctrl |= flag & (0x7 << 1);
}

/**
 * \brief STN LCD单色/彩色选择
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 单色/彩色，值为#AMHW_LCD_STN_COLOR 或 #AMHW_LCD_STN_MONO
 *
 * \return 无
 * \note   TFT模式该操作没有意义
 */
am_static_inline
void amhw_lcd_stn_bw_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_STN_MONO;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_STN_MONO;
}

/**
 * \brief LCD显示屏TFT类型选择
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : TFT类型选择，值为#AMHW_LCD_TYPE_STN 或 #AMHW_LCD_TYPE_TFT
 *
 * \return 无
 * \note   TFT模式该操作没有意义
 */
am_static_inline
void amhw_lcd_tft_type_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_TYPE_TFT;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_TYPE_TFT;
}

/**
 * \brief 单色STN LCD接口宽度设置
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 单色LCD接口宽度，值为#AMHW_LCD_STN_MONO_8BIT
 *                       或 #AMHW_LCD_STN_MONO_4BIT
 *
 * \return 无
 * \note   该操作只对单色STN LCD有意义，其他模式无意义
 */
am_static_inline
void amhw_lcd_mono_interfacewidth_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_STN_MONO_8BIT;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_STN_MONO_8BIT;
}

/**
 * \brief STN LCD接口单屏/双屏选择
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 单屏/双屏，值为#AMHW_LCD_SINGLE_PANEL
 *                       或 #AMHW_LCD_DUAL_PANEL
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_dual_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_DUAL_PANEL;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_DUAL_PANEL;
}

/**
 * \brief LCD色彩模式选择
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : RGB或BGR模式，值为#AMHW_LCD_COLOR_FORMAT_RGB
 *                       或#AMHW_LCD_COLOR_FORMAT_BGR
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_color_mode_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_COLOR_FORMAT_BGR;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_COLOR_FORMAT_BGR;
}

/**
 * \brief 设置内存中字节排序
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 大端/小端模式，值为#AMHW_LCD_BYTE_LITTLE_ENDIAN
 *                       或#AMHW_LCD_BYTE_BIG_ENDIAN
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_byte_endian_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_BYTE_BIG_ENDIAN;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_BYTE_BIG_ENDIAN;
}

/**
 * \brief 设置字节中象素排序
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 大端/小端模式，值为#AMHW_LCD_PIXEL_LITTLE_ENDIAN
 *                       或#AMHW_LCD_PIXEL_BIG_ENDIAN
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_pixel_endian_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_PIXEL_BIG_ENDIAN;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_PIXEL_BIG_ENDIAN;
}

/**
 * \brief 纵向比较中断(VComp)类型选择
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] type     : 中断类型，值为AMHW_LCD_VCOMP_*(#AMHW_LCD_VCOMP_VERTICAL_SYNC)
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_vcomp_type_sel (amhw_lcd_t *p_hw_lcd, uint32_t type)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_VCOMP_FRONT_PORCH;
    p_hw_lcd->ctrl |= type & AMHW_LCD_VCOMP_FRONT_PORCH;
}

/**
 * \brief LCD DMA FIFO水位线设置
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : DMA FIFO水位线，值为#AMHW_LCD_DMA_FIFO_EMPTY4
 *                       或#AMHW_LCD_DMA_FIFO_EMPTY8
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_dma_watermark_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_DMA_FIFO_EMPTY8;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_DMA_FIFO_EMPTY8;
}

/*****************************************************************************/
/**
 * \name LCD时序配置信息
 * \anchor grp_amhw_lcd_pol_flags
 * @{
 */
#define AMHW_LCD_POL_PCD_LO(n)   ((n) & 0x1F)   /**< \brief 显示屏时钟分频器低5位 */

#define AMHW_LCD_POL_CLKSEL_CCLK    (0)         /**< \brief LCD时钟源CCLK*/
#define AMHW_LCD_POL_CLKSEL_CLKIN   (1 << 5)    /**< \brief LCD时钟源LCD_CLKIN */

/** \brief AC偏置管脚频率 */
#define AMHW_LCD_POL_ACB(n)    (((n) & 0x1F) << 6)

#define AMHW_LCD_POL_IVS_HI    (0)       /**< \brief LCD_FP管脚高电平有效 */
#define AMHW_LCD_POL_IVS_LO    (1 << 11) /**< \brief LCD_FP管脚低电平有效 */

#define AMHW_LCD_POL_IHS_HI    (0)       /**< \brief LCD_LP管脚高电平有效 */
#define AMHW_LCD_POL_IHS_LO    (1 << 12) /**< \brief LCD_LP管脚低电平有效 */

#define AMHW_LCD_POL_IPC_RISE  (0)       /**< \brief 数据在LCD_DCLK上升沿被驱动 */
#define AMHW_LCD_POL_IPC_FALL  (1 << 13) /**< \brief 数据在LCD_DCLK下升沿被驱动 */

#define AMHW_LCD_POL_IOE_HI    (0)       /**< \brief LCD_ENAB_M管脚TFT模式高电平有效 */
#define AMHW_LCD_POL_IOE_LO    (1 << 14) /**< \brief LCD_ENAB_M管脚TFT模式低电平有效 */

/** \brief 每行LCD_DCLK时钟数  */
#define AMHW_LCD_POL_CPL(n)    ((((n) - 1) & 0x3FF) << 16)

/** \brief 旁路象素时钟分频器 */
#define AMHW_LCD_POL_BCD_SET   (1 << 26)

/** \brief 显示屏时钟分频器高5位 */
#define AMHW_LCD_POL_PCD_HI(n) (((n) & 0x1F) << 27)

/** @} */

/**
 * \brief LCD时序配置信息设置
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : LCD时序配置信息,参见
 *                       \ref grp_amhw_lcd_pol_flags "LCD POL FLAG"
 * \return 无
 */
am_static_inline
void amhw_lcd_pol_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->pol = flag;
}

/**
 * \name LCD水平时序控制信息
 * \anchor grp_amhw_lcd_timh_flag
 * @{
 */

/** \brief 象素每行时钟数 */
#define AMHW_LCD_TIMH_PPL(n) (((((n) >> 4) - 1) & 0x3F) << 2)

/** \brief 同步脉宽时钟数 */
#define AMHW_LCD_TIMH_HSW(n) ((((n) - 1) & 0xFF) << 8)

/** \brief 水平前沿时钟数 */
#define AMHW_LCD_TIMH_HFP(n) ((((n) - 1) & 0xFF) << 16)

/** \brief 水平后沿时钟数 */
#define AMHW_LCD_TIMH_HBP(n) ((((n) - 1) & 0xFF) << 24)
/** @} */

/**
 * \brief 设置水平时序控制信息
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 水平时序信息，参见
 *                       \ref grp_amhw_lcd_timh_flag "LCD TIMH FLAG"
 * \return    无
 */
am_static_inline
void amhw_lcd_timh_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->timh = flag;
}

/**
 * \name LCD垂直时序控制信息
 * \anchor grp_amhw_lcd_timv_flag
 * @{
 */

/** \brief 每屏包含有效行数n */
#define AMHW_LCD_TIMV_LPP(n) ((((n) - 1) & 0x3FF) <<  0)

/** \brief 水平同步脉宽 */
#define AMHW_LCD_TIMV_VSW(n) ((((n) - 1) & 0x3F)  << 10)

/** \brief 垂直前沿 */
#define AMHW_LCD_TIMV_VFP(n) (((n) & 0xFF)  << 16)

/** \brief 垂直后沿 */
#define AMHW_LCD_TIMV_VBP(n) (((n) & 0xFF)  << 24)
/** @} */

/**
 * \brief 设置垂直时序控制信息
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 垂直时序信息，参见
 *                       \ref grp_amhw_lcd_timv_flag "LCD TIMV FLAG"
 * \return    无
 */
am_static_inline
void amhw_lcd_timv_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->timv = flag;
}

/**
 * \brief 设置行末延迟LCDCLK时钟周期数
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] val      : 行末延迟LCDCLK时钟周期数
 * \return    无
 */
am_static_inline
void amhw_lcd_le_dly_set (amhw_lcd_t *p_hw_lcd, uint32_t val)
{
    p_hw_lcd->le |= (val - 1) & 0x7F;
}

/**
 * \brief 行末使能设置
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] state    : 行末使能/失能，值为TRUE（使能）或FALSE（失能）
 * \return    无
 */
am_static_inline
void amhw_lcd_le_enable (amhw_lcd_t *p_hw_lcd, bool_t state)
{
    if (state == FALSE) {
        p_hw_lcd->le &= ~(1 << 16);
    } else {
        p_hw_lcd->le |= (1 << 16);
    }
}

/**
 * \brief 设置LCD上屏帧基址
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] addr     : 上屏帧基址
 * \return 无
 * \note 写入基址必须双字对齐
 */
am_static_inline
void amhw_lcd_upbase_set (amhw_lcd_t *p_hw_lcd, uint32_t addr)
{
    p_hw_lcd->upbase = addr;
}

/**
 * \brief 设置LCD下屏帧基址
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] addr     : 上屏帧基址
 * \return 无
 * \note 写入基址必须双字对齐
 */
am_static_inline
void amhw_lcd_lpbase_set (amhw_lcd_t *p_hw_lcd, uint32_t addr)
{
    p_hw_lcd->lpbase = addr;
}

/**
 * \brief 获取LCD上屏当前地址
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \return LCD上屏当前地址
 */
am_static_inline
uint32_t amhw_lcd_upcur_addr_get (amhw_lcd_t *p_hw_lcd)
{
    return p_hw_lcd->upcurr;
}

/**
 * \brief 获取LCD下屏当前地址
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \return LCD下屏当前地址
 */
am_static_inline
uint32_t amhw_lcd_lpcur_addr_get (amhw_lcd_t *p_hw_lcd)
{
    return p_hw_lcd->lpcurr;
}

/**
 * \brief LCD中断类型定义
 */
typedef enum amhw_lcd_int_type {
    AMHW_LCD_INT_FUF    = (1 << 0x1),  /**< \brief FIFO溢出中断  */
    AMHW_LCD_INT_LNBU   = (1 << 0x2),  /**< \brief LCD下基址更新中断 */
    AMHW_LCD_INT_VCOMP  = (1 << 0x3),  /**< \brief 纵向比较中断  */
    AMHW_LCD_INT_BER    = (1 << 0x4),  /**< \brief AHB主设备错误中断使能 */
    AMHW_LCD_INT_MASK   = (0xF << 1)   /**< \brief LCD中断掩码 */
} amhw_lcd_int_type_t;

/**
 * \brief 使能/失能LCD指定中断
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] type     : LCD中断类型
 * \param[in] state    : 指定中断使能/失能，值为TRUE（使能）或FALSE（失能）
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_int_enable (amhw_lcd_t         *p_hw_lcd,
                          amhw_lcd_int_type_t type,
                          bool_t              state)
{
    if (state == FALSE) {
        p_hw_lcd->intmsk &= ~(uint32_t)type;
    } else {
        p_hw_lcd->intmsk |=  (uint32_t)type;
    }
}

/**
 * \brief 指定LCD原始中断是否置位
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] type     : LCD中断类型
 *
 * \retval    TRUE     : 指定原始中断置位
 * \retval    FALSE    : 指定原始中断未置位
 */
am_static_inline
bool_t amhw_lcd_intraw_get (amhw_lcd_t         *p_hw_lcd,
                             amhw_lcd_int_type_t type)
{
    return (bool_t)((p_hw_lcd->intraw & (uint32_t)type) != 0);
}

/**
 * \brief 指定LCD（已屏蔽）中断是否置位
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] type     : LCD中断类型
 *
 * \retval    TRUE     : 指定中断置位
 * \retval    FALSE    : 指定中断未置位
 */
am_static_inline
bool_t amhw_lcd_intstat_get (amhw_lcd_t         *p_hw_lcd,
                             amhw_lcd_int_type_t type)
{
    return (bool_t)((p_hw_lcd->intstat & (uint32_t)type) != 0);
}

/**
 * \brief 清除指定LCD中断
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] type     : 指定中断类型，值为AMHW_LCD_INT_*(#AMHW_LCD_INT_FUF)
 *                       可或操作同时清除多个中断。
 * \return 无
 */
am_static_inline
void amhw_lcd_int_clr (amhw_lcd_t *p_hw_lcd,
                       uint32_t    type)
{
    p_hw_lcd->intclr = type;
}

/**
 * \brief 加载彩色调色板
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] p_pal    : 彩色调色板数据
 * \param[in] size     : 需要设置的调色板寄存器数目
 * \return    无
 */
void amhw_lcd_palette_load (amhw_lcd_t *p_hw_lcd,
                            uint32_t   *p_pal,
                            uint8_t     size);
/*****************************************************************************/
/**
 * \brief 设置光标图像
 *
 * \param[in] p_hw_lcd  : 指向LCD寄存器块的指针
 * \param[in] num       : 光标图像编号，值为0/1/2/3
 * \param[in] p_cursor  : 光标图像数据地址
 * \param[in] size      : 光标图像大小
 *
 * \return 无
 *
 * \note 若光标图像大小为64*64，则光标图像编号只能为0
 */
void amhw_lcd_crsr_img_set (amhw_lcd_t     *p_hw_lcd,
                            uint8_t         num,
                            const uint32_t *p_cursor,
                            uint16_t        size);

/**
 * \brief 使能显示指定光标
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] num      : 显示的光标，值为0~3
 * \return 无
 */
am_static_inline
void amhw_lcd_cursor_enable (amhw_lcd_t *p_hw_lcd, uint8_t num)
{
    p_hw_lcd->crsr_ctrl = 0x01 | (num << 4);
}

/**
 * \brief 关闭光标显示
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_cursor_disable (amhw_lcd_t *p_hw_lcd)
{
    p_hw_lcd->crsr_ctrl = 0;
}

/**
 * \name LCD光标配置信息设置
 * \anchor grp_amhw_lcd_crsr_cfg_flag
 * @{
 */
#define AMHW_LCD_CRSR_SIZE_32  (0)  /**< \brief 光标尺寸为32*32  */
#define AMHW_LCD_CRSR_SIZE_64  (1)  /**< \brief 光标尺寸为64*64  */

#define AMHW_LCD_CRSR_FRAME_SYNC    (1 << 1)  /**< \brief 光标坐标与帧同步脉冲同步  */
#define AMHW_LCD_CRSR_FRAME_NO_SYNC (0)       /**< \brief 光标坐标不同步  */
/** @} */

/**
 * \brief 光标配置信息设置
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 光标配置信息，参见
 *                       \ref grp_amhw_lcd_crsr_cfg_flag "CRSR CFG Flag"
 *
 * \return 无
 *
 */
am_static_inline
void amhw_lcd_cursor_cfg_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->crsr_cfg = flag & 0x03;
}

/**
 * \name LCD光标调色板设置
 * \anchor grp_amhw_lcd_crsr_palette_flag
 * @{
 */

/** \brief 光标调色板红色分量 */
#define AMHW_LCD_CRSR_PAL_RED(n)   ((n) & 0xFF)

/** \brief 光标调色板绿色分量 */
#define AMHW_LCD_CRSR_PAL_GREEN(n) (((n) & 0xFF) <<  8)

/** \brief 光标调色板蓝色分量 */
#define AMHW_LCD_CRSR_PAL_BLUE(n)  (((n) & 0xFF) << 16)
/** @} */

/**
 * \brief 设置光标调色板0信息
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 光标调色板信息，
 *                       参见\ref grp_amhw_lcd_crsr_palette_flag "CRSR Palette Flag"
 *
 * \return 无
 *
 */
am_static_inline
void amhw_lcd_crsr_palette0_load (amhw_lcd_t *p_hw_lcd,
                                  uint32_t    flag)
{
    p_hw_lcd->crsr_pal0 = flag;
}

/**
 * \brief 设置光标调色板1信息
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] flag     : 光标调色板信息，
 *                       参见\ref grp_amhw_lcd_crsr_palette_flag "CRSR Palette Flag"
 *
 * \return 无
 *
 */
am_static_inline
void amhw_lcd_crsr_palette1_load (amhw_lcd_t *p_hw_lcd,
                                  uint32_t    flag)
{
    p_hw_lcd->crsr_pal1 = flag;
}

/**
 * \brief 设置光标XY位置
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] x        : 光标起点的X坐标
 * \param[in] y        : 光标起点的Y坐标
 *
 * \return 无
 *
 */
am_static_inline
void amhw_lcd_crsr_xy_set (amhw_lcd_t *p_hw_lcd,
                           uint16_t    x,
                           uint16_t    y)
{
    p_hw_lcd->crsr_xy = (x & 0x3FF) | ((y & 0x3FF) << 16);
}

/**
 * \brief 获取光标XY位置信息
 *
 * \param[in]  p_hw_lcd : 指向LCD寄存器块的指针
 * \param[out] *x       : 光标起点的X坐标
 * \param[out] *y       : 光标起点的Y坐标
 *
 * \return 无
 *
 */
am_static_inline
void amhw_lcd_crsr_xy_get (amhw_lcd_t *p_hw_lcd,
                           uint16_t   *x,
                           uint16_t   *y)
{
    *x = p_hw_lcd->crsr_xy & 0x3FF;
    *y = (p_hw_lcd->crsr_xy >> 16) & 0x3FF;
}

/**
 * \brief 设置光标剪辑位置
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] x        : X方向的光标剪辑位置
 * \param[in] y        : Y方向的光标剪辑位置
 *
 * \return 无
 * \note 确保指定帧的剪辑和位置信息一致，需在操作XY寄存器前执行该操作。
 */
am_static_inline
void amhw_lcd_crsr_clip_set (amhw_lcd_t *p_hw_lcd,
                             uint16_t    x,
                             uint16_t    y)
{
    p_hw_lcd->crsr_clip = (x & 0x3F) | ((y & 0x3F) << 8);
}

/**
 * \brief 设置光标中断使能
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 * \param[in] state    : 光标中断使能值，值为TRUE则中断使能,
 *                       值为FALSE则中断失能
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_crsr_int_enable (amhw_lcd_t *p_hw_lcd,
                               bool_t      state)
{
    p_hw_lcd->crsr_intmsk &= ~0x1UL;
    p_hw_lcd->crsr_intmsk |= (uint8_t)state & 0x01;
}

/**
 * \brief 清除光标中断
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_lcd_crsr_int_clr (amhw_lcd_t *p_hw_lcd)
{
    p_hw_lcd->crsr_intclr = 0x01;
}

/**
 * \brief 获取光标原始中断状态
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 *
 * \retval TRUE  : 光标原始中断状态置位
 * \retval FALSE : 光标原始中断未置位
 */
am_static_inline
bool_t amhw_lcd_crsr_intraw_get (amhw_lcd_t *p_hw_lcd)
{
    return (bool_t)((p_hw_lcd->crsr_intraw & 0x01) != 0);
}

/**
 * \brief 获取光标（已屏蔽）中断状态
 *
 * \param[in] p_hw_lcd : 指向LCD寄存器块的指针
 *
 * \retval TRUE  : 光标中断状态置位
 * \retval FALSE : 光标中断未置位
 */
am_static_inline
bool_t amhw_lcd_crsr_intstat_get (amhw_lcd_t *p_hw_lcd)
{
    return (bool_t)((p_hw_lcd->crsr_intstat & 0x01) != 0);
}

/**
 * @} amhw_if_lcd
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_LCD_H */

/* end of file */

