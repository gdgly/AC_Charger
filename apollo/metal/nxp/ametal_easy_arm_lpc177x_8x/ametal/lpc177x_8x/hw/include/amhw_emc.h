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
 * \brief EMC硬件操作接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-12  cod, first implementation.
 * \endinternal
 */

#ifndef __AMHW_EMC_H
#define __AMHW_EMC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"

/**
 * \addtogroup amhw_if_emc
 * \copydoc amhw_emc.h
 * @{
 */

/**
 * \name EMC片外存储器地址
 * @{
 */

/** \brief 静态存储器片选0地址，范围0x80000000—0x83FFFFFF,使能存储转换模式，容量可达256MB */
#define AMHW_EMC_STATICMEM_ADDR0  0x80000000UL

/** \brief 静态存储器片选1地址，范围0x90000000—0x93FFFFFF,使能存储转换模式，容量可达128MB */
#define AMHW_EMC_STATICMEM_ADDR1  0x90000000UL

/** \brief 静态存储器片选2地址，范围0x9800 0000—0x9BFF FFFF    */
#define AMHW_EMC_STATICMEM_ADDR2  0x98000000UL

/** \brief 静态存储器片选3地址，范围0x9C00 0000—0x9FFF FFFF    */
#define AMHW_EMC_STATICMEM_ADDR3  0x9C000000UL

/** \brief 动态存储器片选0地址，范围0xA000 0000—0xAFFF FFFF    */
#define AMHW_EMC_DYNAMICMEM_ADDR0  0xA0000000UL

/** \brief 动态存储器片选1地址，范围0xB000 0000—0xBFFF FFFF    */
#define AMHW_EMC_DYNAMICMEM_ADDR1  0xB0000000UL

/** \brief 动态存储器片选2地址，范围0xC000 0000—0xBFFF FFFF    */
#define AMHW_EMC_DYNAMICMEM_ADDR2  0xC0000000UL

/** \brief 动态存储器片选3地址，范围0xD000 0000—0xDFFF FFFF    */
#define AMHW_EMC_DYNAMICMEM_ADDR3  0xD0000000UL
/** @} */

/**
 * \name EMC 大小端模式
 * @{
 */
#define AMHW_EMC_LITTLE_ENDIAN   0    /**< \brief EMC小端模式                         */
#define AMHW_EMC_BIG_ENDIAN      1    /**< \brief EMC大端模式                          */
/** @} */

/**
 * \brief EMC动态存储器配置寄存器及RAS & CAS延时寄存器块
 */
typedef struct amhw_emc_dynamics {
    __IO uint32_t config;          /**< \brief 动态存储器配置寄存器                           */
    __IO uint32_t rascas;          /**< \brief 动态存储器RAS & CAS延时寄存器   */
         uint32_t reserved[6];     /**< \brief 保留                                                                   */
} amhw_emc_dynamics_t;

/**
 * \brief EMC静态存储器寄存器块
 */
typedef struct amhw_emc_statics {
    __IO uint32_t config;       /**< \brief 静态存储器配置寄存器                                */
    __IO uint32_t waitwen;      /**< \brief 静态存储器写使能延迟寄存器                 */
    __IO uint32_t waitoen;      /**< \brief 静态存储器输出使能延迟寄存器             */
    __IO uint32_t waitrd;       /**< \brief 静态存储器读取延迟寄存器                       */
    __IO uint32_t waitpage;     /**< \brief 静态存储器页读模式读取延迟寄存器  */
    __IO uint32_t waitwr;       /**< \brief 静态存储器写入延迟寄存器                        */
    __IO uint32_t waitturn;     /**< \brief 静态存储器周转延迟寄存器                        */
         uint32_t reserved;     /**< \brief 保留                                                                           */
} amhw_emc_statics_t;

/**
 * \brief EMC控制器寄存器块结构体
 */
typedef struct amhw_emc {
    __IO uint32_t control;             /**< \brief 控制寄存器              */
    __I  uint32_t status;              /**< \brief 状态寄存器              */
    __IO uint32_t config;              /**< \brief 配置寄存器              */
         uint32_t reserved0[5];        /**< \brief 保留                             */
    __IO uint32_t dynamiccontrol;      /**< \brief 动态存储器控制寄存器                                              */
    __IO uint32_t dynamicrefresh;      /**< \brief 动态存储器刷新定时器寄存器                               */
    __IO uint32_t dynamicreadconfig;   /**< \brief 动态存储器读取配置寄存器                                    */
         uint32_t reserved1;           /**< \brief 保留                                                                                      */
    __IO uint32_t dynamictrp;          /**< \brief 动态存储器预充电命令周期寄存器                     */
    __IO uint32_t dynamictras;         /**< \brief 动态存储器有效至预充电命令周期寄存器      */
    __IO uint32_t dynamictsrex;        /**< \brief 动态存储器自刷新退出时间寄存器                     */
    __IO uint32_t dynamictapr;         /**< \brief 动态存储器最后数据输出至有效时间寄存器                  */
    __IO uint32_t dynamictdal;         /**< \brief 动态存储器数据输入至有效命令时间寄存器                  */
    __IO uint32_t dynamictwr;          /**< \brief 动态存储器写入恢复时间寄存器                                           */
    __IO uint32_t dynamictrc;          /**< \brief 动态存储器有效至有效命令周期寄存器                            */
    __IO uint32_t dynamictrfc;         /**< \brief 动态存储器自动刷新周期寄存器                                           */
    __IO uint32_t dynamictxsr;         /**< \brief 动态存储器退出自刷新寄存器                                                */
    __IO uint32_t dynamictrrd;         /**< \brief 动态存储器有效组A至有效组B的时间寄存器                  */
    __IO uint32_t dynamictmrd;         /**< \brief 动态存储器装载模式寄存器至有效命令时间寄存器    */
         uint32_t reserved2[9];        /**< \brief 保留                                                                        */
    __IO uint32_t staticextendedwait;  /**< \brief 静态存储器延长等待寄存器                      */
         uint32_t reserved3[31];       /**< \brief 保留                                                                        */

    amhw_emc_dynamics_t dynamic_mem[4]; /**< \brief EMC动态存储器配置寄存器及RAS & CAS延时寄存器0~3 */

    uint32_t reserved7[32];             /**< \brief 保留                                                                        */

    amhw_emc_statics_t  static_mem[4];  /**< \brief 静态存储器寄存器块0~3                 */

} amhw_emc_t;

/**
 * \brief 使能EMC控制器
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \return    无
 * \note      复位自动使能
 */
am_static_inline
void amhw_emc_enable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control |= (1 << 0);
}

/**
 * \brief 禁能EMC控制器
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_emc_disable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control &= ~(1 << 0);
}

/**
 * \name EMC复位存储器映射
 * @{
 */
#define AMHW_EMC_MIRROR_ENABLE  (1 << 1)  /**< \brief 复位存储器映射使能   */
#define AMHW_EMC_MIRROR_DISABLE (0)       /**< \brief 复位存储器映射失能   */
/** @} */

/**
 * \brief 使能EMC复位存储器映射(复位默认状态)
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \return    无
 * \note      复位自动使能
 */
am_static_inline
void amhw_emc_mirror_enable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control |= (1 << 1);
}

/**
 * \brief 禁能EMC复位存储器映射
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_emc_mirror_disable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control &= ~(1 << 1);
}

/**
 * \brief 使能低功耗模式
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_emc_lowpower_mode_enable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control |= (1 << 2);
}

/**
 * \brief 禁能低功耗模式(正常模式)
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \return    无
 * \note      复位进入该模式
 */
am_static_inline
void amhw_emc_lowpower_mode_disable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control |= (1 << 2);
}

/**
 * \name EMC状态寄存器状态位定义
 * @{
 */
#define AMHW_EMC_STAT_BUSY   AM_BIT(0)  /**< \brief EMC BUSY位        */
#define AMHW_EMC_STAT_S      AM_BIT(1)  /**< \brief 写缓存位               */
#define AMHW_EMC_STAT_SA     AM_BIT(2)  /**< \brief EMC工作模式位   */
#define AMHW_EMC_STAT_MASK   (0x07)     /**< \brief EMC状态位掩码   */
/** @} */

/**
 * \brief 指定状态位是否置位
 *
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] flag     : 指定状态位, 值为AMHW_EMC_STAT_*(如#AMHW_EMC_STAT_BUSY)
 * \retval    TURE     : 指定位置位
 * \retval    FALSE    : 指定位为0
 */
am_static_inline
bool_t amhw_emc_status_get (amhw_emc_t *p_hw_emc, uint8_t flag)
{
    return (bool_t)(p_hw_emc->status & (flag & 0x7));
}

/**
 * \brief EMC配置为小端模式
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \return    无
 * \note 建议对该寄存器的修改应在系统初始化期间，或在不存在电流和未完成事务时进行
 */
am_static_inline
void amhw_emc_endian_little (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->config &= ~(1 << 0);
}

/**
 * \brief EMC配置为大端模式
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \return    无
 * \note 建议对该寄存器的修改应在系统初始化期间，或在不存在电流和未完成事务时进行
 */
am_static_inline
void amhw_emc_endian_big (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->config = (1 << 0);
}

/**
 * \name EMC 动态存储器控制信息
 * \anchor grp_amhw_emc_dynamic_ctrl_flag
 * @{
 */
/** \brief 空闲设备的时钟使能被禁止(上电复位值)  */
#define AMHW_EMC_DYNCTRL_CE_SAVEPWR     (0UL)
/** \brief 所有时钟使能持续受到高电平的驱动        */
#define AMHW_EMC_DYNCTRL_CE_ALLCLK_HI   (1 << 0)

/** \brief CLKOUT停止                                               */
#define AMHW_EMC_DYNCTRL_CS_CLKOUT_STOP (0UL)
/** \brief CLKOUT持续运行（上电复位值）  */
#define AMHW_EMC_DYNCTRL_CS_CLKOUT_CONN (1 << 1)

#define AMHW_EMC_DYNCTRL_SR_NORMALMODE  (0UL)     /**< \brief 正常模式       */
#define AMHW_EMC_DYNCTRL_SR_SELFREFRESH (1 << 2)  /**< \brief 自刷新模式（上电复位值） */

#define AMHW_EMC_DYNCTRL_MMC_CLKOUT_ENABLE   (0UL)     /**< \brief CLKOUT使能    */
#define AMHW_EMC_DYNCTRL_MMC_CLKOUT_DISABLE  (1 << 5)  /**< \brief CLKOUT禁能    */

#define AMHW_EMC_DYNCTRL_SDRAM_NORMAL (0 << 7) /**< \brief SDRAM NORMAL操作命令（上电复位值）*/
#define AMHW_EMC_DYNCTRL_SDRAM_MODE   (1 << 7) /**< \brief SDRAM MODE操作命令   */
#define AMHW_EMC_DYNCTRL_SDRAM_PALL   (2 << 7) /**< \brief SDRAM PALL操作命令   */
#define AMHW_EMC_DYNCTRL_SDRAM_NOP    (3 << 7) /**< \brief SDRAM NOP操作命令   */

#define AMHW_EMC_DYNCTRL_DP_NORMAL      (0UL)      /**< \brief 正常操作（上电复位值） */
#define AMHW_EMC_DYNCTRL_DP_DEEPSLEEP   (1 << 13)  /**< \brief 进入深度睡眠模式                 */

/** @} */

/**
 * \brief  EMC动态存储器时钟控制
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟控制值，值为
 *                       #AMHW_EMC_DYNCTRL_CE_SAVEPWR  ：空闲设备的时钟使能被禁止, 或
 *                       #AMHW_EMC_DYNCTRL_CE_ALLCLK_HI:所有时钟使能持续受到高电平的驱动
 *
 * \return    无
 */
am_static_inline
void amhw_emc_dynctrl_ce_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 0);
    p_hw_emc->dynamiccontrol |= val & 0x01;
}

/**
 * \brief  EMC动态存储器时钟CLKOUT设置
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 设置值，值为
 *                       #AMHW_EMC_DYNCTRL_CS_CLKOUT_STOP: CLKOUT停止, 或
 *                       #AMHW_EMC_DYNCTRL_CS_CLKOUT_CONN: CLKOUT持续运行
 *
 * \return    无
 */
am_static_inline
void amhw_emc_dynctrl_cs_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 1);
    p_hw_emc->dynamiccontrol |= val & (0x01 << 1);
}

/**
 * \brief  EMC动态存储器自刷新模式设置
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 自刷新设置值，值为
 *                       #AMHW_EMC_DYNCTRL_SR_NORMALMODE: 正常模式, 或
 *                       #AMHW_EMC_DYNCTRL_SR_SELFREFRESH: 自刷新模式
 *
 * \return    无
 */
am_static_inline
void amhw_emc_dynctrl_sr_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 2);
    p_hw_emc->dynamiccontrol |= val & (0x01 << 2);
}

/**
 * \brief  设置EMC动态存储器CLKOUT 使能或失能
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 使能/失能，值为：
 *                       (#AMHW_EMC_DYNCTRL_MMC_CLKOUT_ENABLE)使能或
 *                       (#AMHW_EMC_DYNCTRL_MMC_CLKOUT_DISABLE)失能
 *
 * \return    无
 */
am_static_inline
void amhw_emc_dynctrl_mmc_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 5);
    p_hw_emc->dynamiccontrol |= val & (0x01 << 5);
}

/**
 * \brief 发布EMC SDRAM命令
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] cmd      : SDRAM命令，值为AMHW_EMC_DYNCTRL_SDRAM_*
 *                       如(#AMHW_EMC_DYNCTRL_SDRAM_NORMAL)
 * \return    无
 */
am_static_inline
void amhw_emc_dynctrl_sdram_init (amhw_emc_t *p_hw_emc, uint32_t cmd)
{
    p_hw_emc->dynamiccontrol &= ~(0x03 << 7);
    p_hw_emc->dynamiccontrol |= (cmd & (0x03 << 7));
}

/**
 * \brief 动态存储器深度睡眠模式设置
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 正常模式或深度睡眠模式，值为
 *                       #AMHW_EMC_DYNCTRL_DP_NORMAL:正常模式
 *                       #AMHW_EMC_DYNCTRL_DP_DEEPSLEEP:深度睡眠
 * \return    无
 */
am_static_inline
void amhw_emc_dynctrl_dp_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 13);
    p_hw_emc->dynamiccontrol |= (val & (0x01 << 13));
}

/**
 * \brief 设置EMC SDRAM刷新周期之间16个CCLK的倍数
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 16个CCLK的倍数值，值为0~0x3FF.值为0时刷新禁能
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_refresh_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamicrefresh = val & 0x3FF;
}

/**
 * \name EMC 动态存储器延时策略
 * @{
 */
/** \brief 时钟输出延时策略，使用CLKOUT（命令未延时，时钟输出延时）,上电复位值       */
#define AMHW_EMC_DYNAMIC_RD_0  (0UL)
/** \brief 命令延时策略，使用EMCCLKDELAY（命令延时，时钟输出未延时  */
#define AMHW_EMC_DYNAMIC_RD_1  (1UL)
/** \brief 命令延时策略与一个时钟周期，使用EMCCLKDELAY（命令延时，时钟输出未延时）  */
#define AMHW_EMC_DYNAMIC_RD_2  (2UL)
/** \brief 命令延时策略与二个时钟周期，使用EMCCLKDELAY（命令延时，时钟输出未延时）  */
#define AMHW_EMC_DYNAMIC_RD_3  (3UL)
/** @} */

/**
 * \brief  配置EMC动态存储器的读取策略
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 读取策略，值为0~3,可用调用宏如(#AMHW_EMC_DYNAMIC_RD_0)
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_rd_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamicreadconfig = val & 0x03;
}

/**
 * \brief 设置EMC动态存储器预充电命令周期
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~15. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_trp_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictrp = val & 0x0F;
}

/**
 * \brief 设置EMC动态存储器有效至预充电命令周期
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~15. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_tras_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictras = val & 0x0F;
}

/**
 * \brief 设置EMC动态存储器自刷新退出时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~15. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_tsrex_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictsrex = val & 0x0F;
}

/**
 * \brief 设置EMC动态存储器最后数据输出至有效时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~15. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_tapr_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictapr = val & 0x0F;
}

/**
 * \brief 设置EMC动态存储器数据输入至有效命令时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~15. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_tdal_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictdal = val & 0x0F;
}

/**
 * \brief 设置EMC动态存储器写入恢复时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~15. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_twr_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictwr = val & 0x0F;
}

/**
 * \brief 设置EMC动态存储器有效至有效命令周期
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~31. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_trc_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictrc = val & 0x1F;
}

/**
 * \brief 设置EMC动态存储器自刷新周期
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~31. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_trfc_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictrfc = val & 0x1F;
}

/**
 * \brief 设置EMC动态存储器退出自刷新至有效命令时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~31. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_txsr_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictxsr = val & 0x1F;
}

/**
 * \brief 设置EMC动态存储器有效组A至有效组B的时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~15. 实际时钟周期为val+1
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_trrd_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictrrd = val & 0x0F;
}

/**
 * \brief 设置EMC动态存储器装载模式寄存器至有效命令时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~15. val+1个时钟周期
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_tmrd_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictmrd = val & 0x0F;
}

/**
 * \brief 设置EMC静态存储器延长等待时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] val      : 时钟周期数，值为0~0x3FF. 实际时钟周期为(val+1)*16个
 * \return    无
 */
am_static_inline
void amhw_emc_externdedwait_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->staticextendedwait = val & 0x3FF;
}

/**
 * \name EMC 动态存储器配置信息
 * \anchor grp_amhw_emc_dynamic_cfg_flag
 * @{
 */

#define AMHW_EMC_DYNCFG_MD_SDRAM          (0 << 3)  /**< \brief SDRAM（上电复位值）  */
#define AMHW_EMC_DYNCFG_MD_LOWPWR_SDRAM   (1 << 3)  /**< \brief 低功耗SDRAM        */

/** \brief 地址映射设置,设置位数[11:7]  */
#define AMHW_EMC_DYNCFG_ADDRMAP_P1(val)   (((val) & 0x1F) << 7)
/** \brief 地址映射设置,设置位数[12],地址映射方式 (行组列)或(组行列) */
#define AMHW_EMC_DYNCFG_ADDRMAP_P2(val)   (((val) & 0x01) << 12)
/** \brief 地址映射设置,设置位数[14],16bits外部总线val为0,32bits时val为1  */
#define AMHW_EMC_DYNCFG_ADDRMAP_P3(val)   (((val) & 0x01) << 14)

#define AMHW_EMC_DYNCFG_BUFFER_ENABLE     (1 << 19) /**< \brief 缓存使能    */
#define AMHW_EMC_DYNCFG_BUFFER_DISABLE    (0 << 19) /**< \brief 缓存禁能    */

#define AMHW_EMC_DYNCFG_WR_PROTECTED      (1 << 20) /**< \brief 写保护         */
#define AMHW_EMC_DYNCFG_WR_UNPROTECTED    (0 << 20) /**< \brief 写未保护    */

/** @} */

/**
 * \brief 设置EMC动态存储器内存设备设置
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] num      : 配置寄存器编号,值为0~3
 * \param[in] val      : 内存设备,值为(#AMHW_EMC_DYNCFG_MD_SDRAM)或
 *                                   (#AMHW_EMC_DYNCFG_MD_LOWPWR_SDRAM)
 *
 * \return    无
 */
am_static_inline
void amhw_emc_dynconfig_md_set (amhw_emc_t *p_hw_emc,
                                uint8_t     num,
                                uint32_t    val)
{
    p_hw_emc->dynamic_mem[num].config &= ~(1 << 3);
    p_hw_emc->dynamic_mem[num].config |= val;
}

/**
 * \name EMC 动态存储器地址映射设置信息
 * @{
 */
#define AMHW_EMC_ADDRWIDTH_16   (16)    /**< \brief 地址总线宽度16bits    */
#define AMHW_EMC_ADDRWIDTH_32   (32)    /**< \brief 地址总线宽度32bits    */

#define AMHW_EMC_DATAWIDTH_8    (8)     /**< \brief 数据总线宽度8bits     */
#define AMHW_EMC_DATAWIDTH_16   (16)    /**< \brief 数据总线宽度16bits    */
#define AMHW_EMC_DATAWIDTH_32   (32)    /**< \brief 数据总线宽度32bits    */

#define AMHW_EMC_AM_ROW_BANK_COL   (0)  /**< \brief 地址映射：行-组-列   */
#define AMHW_EMC_AM_BANK_ROW_COL   (1)  /**< \brief 地址映射：组-行-列   */

#define AMHW_EMC_DYNCHIP_SIZE_16MB   (16)  /**< \brief 动态存储器大小16MB    */
#define AMHW_EMC_DYNCHIP_SIZE_64MB   (64)  /**< \brief 动态存储器大小64MB    */
#define AMHW_EMC_DYNCHIP_SIZE_128MB  (128) /**< \brief 动态存储器大小128MB   */
#define AMHW_EMC_DYNCHIP_SIZE_256MB  (256) /**< \brief 动态存储器大小256MB   */
#define AMHW_EMC_DYNCHIP_SIZE_512MB  (512) /**< \brief 动态存储器大小512MB   */

/** @} */

/**
 * \brief 设置EMC动态存储器地址映射设置
 * \param[in] p_hw_emc   : 指向EMC控制器寄存器块的指针
 * \param[in] index      : 片选号,值为0~3
 * \param[in] addr_width : 外部总线地址宽度,值为16/32,
 *                         或设置为(#AMHW_EMC_ADDRWIDTH_16)或
 *                                 (#AMHW_EMC_ADDRWIDTH_32)
 * \param[in] data_width : 外部数据总线宽度,值为8/16/32,
 *                         或设置为(#AMHW_EMC_DATAWIDTH_8)或
 *                                 (#AMHW_EMC_DATAWIDTH_16)或
 *                                 (#AMHW_EMC_DATAWIDTH_32)
 * \param[in] addrmap    : 地址映射方式,值为(#AMHW_EMC_AM_ROW_BANK_COL)或
 *                                         (#AMHW_EMC_AM_BANK_ROW_COL)
 * \param[in] chipsize   : 动态存储器存储大小(MB),值为 16/64/128/256/512,
 *                         或设置值为AMHW_EMC_DYNCHIP_SIZE_*(如#AMHW_EMC_DYNCHIP_SIZE_16MB)
 *
 * \return    无
 */
void amhw_emc_dynconfig_am_set(amhw_emc_t *p_hw_emc,
                               uint8_t     index,
                               uint8_t     addr_width,
                               uint8_t     data_width,
                               uint8_t     addrmap,
                               uint8_t     chipsize);

/**
 * \brief 设置EMC动态存储器 缓冲使/禁能
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] index    : 片选号,值为0~3
 * \param[in] val      : 使能#AMHW_EMC_DYNCFG_BUFFER_ENABLE 或
 *                       禁能#AMHW_EMC_DYNCFG_BUFFER_DISABLE
 * \return    无
 */
am_static_inline
void amhw_emc_dynconfig_buffer_set (amhw_emc_t *p_hw_emc,
                                    uint8_t     index,
                                    uint32_t    val)
{
    p_hw_emc->dynamic_mem[index].config &= ~AMHW_EMC_DYNCFG_BUFFER_ENABLE;
    p_hw_emc->dynamic_mem[index].config |= val;
}

/**
 * \brief 设置EMC动态存储器 写保护使/禁能
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] index    : 片选号,值为0~3
 * \param[in] val      : 写保护,值为#AMHW_EMC_DYNCFG_WR_PROTECTED 或
 *                       未写保护, 值为#AMHW_EMC_DYNCFG_WR_UNPROTECTED
 * \return    无
 */
am_static_inline
void amhw_emc_dynconfig_protect_set (amhw_emc_t *p_hw_emc,
                                     uint8_t     index,
                                     uint32_t    val)
{
    p_hw_emc->dynamic_mem[index].config &= ~AMHW_EMC_DYNCFG_WR_UNPROTECTED;
    p_hw_emc->dynamic_mem[index].config |= val;
}

/**
 * \brief 设置EMC动态存储器RAS和CAS延时
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] num      : 配置寄存器编号,值为0~3
 * \param[in] ras      : RAS的CCLK周期数，值为1~3.（上电复位为3个CCLK周期）
 * \param[in] cas      : CAS的CCLK周期数，值为1~3.（上电复位为3个CCLK周期）
 * \return    无
 */
am_static_inline
void amhw_emc_dynamic_rascas_set (amhw_emc_t *p_hw_emc,
                                  uint8_t     num,
                                  uint32_t    ras,
                                  uint32_t    cas)
{
    p_hw_emc->dynamic_mem[num].rascas = (ras & 0x03) | ((cas & 0x03) << 8);
}

/**
 * \name EMC 静态存储器配置信息
 * \anchor grp_amhw_emc_static_cfg_flag
 * @{
 */
#define AMHW_EMC_STATICCFG_MW_8BITS   AM_SBF(0, 0)  /**< \brief 存储器宽度8位  */
#define AMHW_EMC_STATICCFG_MW_16BITS  AM_SBF(1, 0)  /**< \brief 存储器宽度16位  */
#define AMHW_EMC_STATICCFG_MW_32BITS  AM_SBF(2, 0)  /**< \brief 存储器宽度32位  */

#define AMHW_EMC_STATICCFG_PM_ENABLE  AM_SBF(1, 3)  /**< \brief 异步页读模式使能  */
#define AMHW_EMC_STATICCFG_PM_DISABLE AM_SBF(0, 3)  /**< \brief 禁能（上电复位值） */

#define AMHW_EMC_STATICCFG_PC_ACTIVE_LO  AM_SBF(0, 6) /**< \brief 低电平片选有效  */
#define AMHW_EMC_STATICCFG_PC_ACTIVE_HI  AM_SBF(1, 6) /**< \brief 高电平片选有效  */

#define AMHW_EMC_STATICCFG_PB_RDHI  AM_SBF(0, 7) /**< \brief 读取BLS[3:0]中的所有位为高电平  */
#define AMHW_EMC_STATICCFG_PB_RDLO  AM_SBF(1, 7) /**< \brief 读取BLS[3:0]中的所有位为低电平  */

#define AMHW_EMC_STATICCFG_EW_DISABLE  AM_SBF(0, 8)  /**< \brief 延长等待禁能  */
#define AMHW_EMC_STATICCFG_EW_ENABLE   AM_SBF(1, 8)  /**< \brief 延长等待使能  */

#define AMHW_EMC_STATICCFG_BUFFER_DISABLE  AM_SBF(0, 19)  /**< \brief 写缓冲禁能  */
#define AMHW_EMC_STATICCFG_BUFFER_ENABLE   AM_SBF(1, 19)  /**< \brief 写缓冲待使能  */

#define AMHW_EMC_STATICCFG_WR_UNPROTECTED  AM_SBF(0, 20)  /**< \brief 未写保护  */
#define AMHW_EMC_STATICCFG_WR_PROTECTED    AM_SBF(1, 20)  /**< \brief 写保护       */

/** @} */

/**
 * \brief 设置EMC静态存储器配置信息
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] index    : 片选号,值为0~3
 * \param[in] flag     : 配置信息,参见
 *                       \ref grp_amhw_emc_static_cfg_flag "Static Configuration Flag"
 * \return    无
 */
am_static_inline
void amhw_emc_static_config_set (amhw_emc_t *p_hw_emc,
                                 uint8_t     index,
                                 uint32_t    flag)
{
    p_hw_emc->static_mem[index].config = flag;
}

/**
 * \brief 设置EMC静态存储器写使能延时时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] num      : 配置寄存器编号,值为0~3
 * \param[in] val      : 延时周期数，值为0~15.延时周期为(val+1)个CCLK
 * \return    无
 */
am_static_inline
void amhw_emc_static_waitwen_set (amhw_emc_t *p_hw_emc,
                                  uint8_t     num,
                                  uint32_t    val)
{
    p_hw_emc->static_mem[num].waitwen = val & 0xF;
}

/**
 * \brief 设置EMC静态存储器输出使能延迟
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] num      : 配置寄存器编号,值为0~3
 * \param[in] val      : 延时周期数，值为0~15,为0无延迟,大于0,延迟为val*cclk.
 * \return    无
 */
am_static_inline
void amhw_emc_static_waitoen_set (amhw_emc_t *p_hw_emc,
                                  uint8_t     num,
                                  uint32_t    val)
{
    p_hw_emc->static_mem[num].waitoen = val & 0xF;
}

/**
 * \brief 设置EMC静态存储器从片选到读取的延迟
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] num      : 配置寄存器编号,值为0~3
 * \param[in] val      : 延时周期数，值为0~0x1F
 * \return    无
 * \note      val值为0x1F时，32个读取CCLK周期（上电复位值）
 *            val值为0~0x1E时，等待状态时间为(val+1)*cclk.
 */
am_static_inline
void amhw_emc_static_waitrd_set (amhw_emc_t *p_hw_emc,
                                 uint8_t     num,
                                 uint32_t    val)
{
    p_hw_emc->static_mem[num].waitrd = val & 0x1F;
}

/**
 * \brief 设置EMC静态存储器页读模式读取延迟
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] num      : 配置寄存器编号,值为0~3
 * \param[in] val      : 延时周期数，值为0~0x1F
 * \return    无
 * \note      val值为0x1F时，32个读取CCLK周期（上电复位值）
 *            val值为0~0x1E时，等待状态时间为(val+1)*cclk.
 */
am_static_inline
void amhw_emc_static_waitpage_set (amhw_emc_t *p_hw_emc,
                                   uint8_t     num,
                                   uint32_t    val)
{
    p_hw_emc->static_mem[num].waitpage = val & 0x1F;
}

/**
 * \brief 设置EMC静态存储器写入延迟
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] num      : 配置寄存器编号,值为0~3
 * \param[in] val      : 延时周期数，值为0~0x1F
 * \return    无
 * \note      val值为0x1F时，33个读取CCLK周期（上电复位值）
 *            val值为0~0x1E时，等待状态时间为(val+2)*cclk.
 */
am_static_inline
void amhw_emc_static_waitwr_set (amhw_emc_t *p_hw_emc,
                                 uint8_t     num,
                                 uint32_t    val)
{
    p_hw_emc->static_mem[num].waitwr = val & 0x1F;
}

/**
 * \brief 设置EMC静态存储器周转延迟时间
 * \param[in] p_hw_emc : 指向EMC控制器寄存器块的指针
 * \param[in] num      : 配置寄存器编号,值为0~3
 * \param[in] val      : 延时周期数，值为1~15.周转延迟为(val+1)*cclk.
 * \return    无
 */
am_static_inline
void amhw_emc_static_waitturn_set (amhw_emc_t *p_hw_emc,
                                   uint8_t     num,
                                   uint32_t    val)
{
    p_hw_emc->static_mem[num].waitturn = val & 0xF;
}

/**
 * \brief 动态存储器时间信息
 */
typedef struct amdr_emc_dynamic_timeinfo {
    uint16_t refreshtime;   /**< \brief SDRAM刷新周期之间16个CCLK的倍数  */
    uint8_t  trp;           /**< \brief 动态存储器预充电命令周期   */
    uint8_t  tras;          /**< \brief 动态存储器有效至预充电命令周期   */
    uint8_t  tsrex;         /**< \brief 动态存储器自刷新退出时间  */
    uint8_t  tapr;          /**< \brief 动态存储器最后数据输出至有效时间   */
    uint8_t  tdal;          /**< \brief 动态存储器数据输入至有效命令时间 */
    uint8_t  twr;           /**< \brief 动态存储器写入恢复时间   */
    uint8_t  trc;           /**< \brief 动态存储器有效至有效命令周期   */
    uint8_t  trfc;          /**< \brief 动态存储器自动刷新周期   */
    uint8_t  txsr;          /**< \brief 动态存储器退出自刷新至有效命令时间   */
    uint8_t  trrd;          /**< \brief 动态存储器有效组A至有效组B的延时   */
    uint8_t  tmrd;          /**< \brief 动态存储器装载模式寄存器至有效命令时间   */
} amhw_emc_dynamic_timeinfo_t;

/**
 * \brief 设置EMC动态存储器时间信息
 * \param[in] p_hw_emc   : 指向EMC寄存器块的指针
 * \param[in] p_info     : 时间信息，
 *                         参见结构体amhw_emc_dynamic_timeinfo_t
 *
 * \return    无
 */
void amhw_emc_dynamic_time_set (amhw_emc_t                  *p_hw_emc,
                                amhw_emc_dynamic_timeinfo_t *p_info);

/**
 * \brief 静态存储器延迟时间信息
 */
typedef struct amdr_emc_static_timeinfo {
    uint8_t waitwen;       /**< \brief 静态存储器写使能延时时间  */
    uint8_t waitoen;       /**< \brief 静态存储器输出使能延迟时间  */
    uint8_t waitrd;        /**< \brief 静态存储器从片选到读取的延迟时间  */
    uint8_t waitpage;      /**< \brief 静态存储器页读模式读取延迟时间  */
    uint8_t waitwr;        /**< \brief 静态存储器写入延迟时间  */
    uint8_t waitturn;      /**< \brief 静态存储器周转延迟时间  */
} amhw_emc_static_timeinfo_t;

/**
 * \brief EMC静态存储器延迟时间设置
 * \param[in] p_hw_emc   : 指向EMC寄存器块的指针
 * \param[in] index      : 片选号，值为0/1/2/3
 * \param[in] p_info     : 延迟时间信息，
 *                         参见结构体amhw_emc_static_timeinfo_t
 *
 * \return    无
 */
void amhw_emc_static_time_set (amhw_emc_t                 *p_hw_emc,
                               uint8_t                     index,
                               amhw_emc_static_timeinfo_t *p_info);
/**
 * \name EMC延迟控制信息
 * \anchor grp_amhw_emc_dlyctl_flag
 * @{
 */

/** \brief 命令延迟模式下EMC 输出的可编程延迟值,延迟时间约为(n+1)*250ps  */
#define AMHW_EMC_DLYCTL_CMDDLY(n)        ((uint32_t)(n&0x1F))
/** \brief 控制输入数据采样的反馈时钟的可编程延迟值,延迟时间约为(n+1)*250ps  */
#define AMHW_EMC_DLYCTL_FBCLKDLY(n)      ((uint32_t)((n&0x1F)<<8))
/** \brief CLKOUT0 输出的可编程延迟值,延迟时间约为(n+1)*250ps  */
#define AMHW_EMC_DLYCTL_CLKOUT0DLY(n)    ((uint32_t)((n&0x1F)<<16))
/** \brief CLKOUT1 输出的可编程延迟值,延迟时间约为(n+1)*250ps  */
#define AMHW_EMC_DLYCTL_CLKOUT1DLY(n)    ((uint32_t)((n&0x1F)<<24))
/** @} */

/**
 * \brief 设置EMC静态存储器输出使能延迟
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \param[in] flag        : 延迟控制信息，参见
 *                          \ref grp_amhw_emc_dlyctl_flag "EMC Dlyctl Flag"
 * \return    无
 */
am_static_inline
void amhw_emc_dlyctl_set (amhw_syscon_t *p_hw_syscon,
                          uint32_t       flag)
{
    p_hw_syscon->emcdlyctl = flag;
}

/**
 * \name EMC校准位定义
 * @{
 */
/** \brief 返回约50MHz 环形振荡器的计数  */
#define AMHW_EMC_CAL_CALVALUE(n) ((uint32_t)(n&0xFF))
/** \brief EMC 校准计数器的开始控制位数  */
#define AMHW_EMC_CAL_START       ((uint32_t)(1<<14))
/** \brief 测量完成标志  */
#define AMHW_EMC_CAL_DONE        ((uint32_t)(1<<15))
/** @} */


/**
 * \brief 获取EMC环形振荡器计数的校准值
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \return   约50MHz 环形振荡器的计数
 */
uint8_t amhw_emc_calvalue_get(amhw_syscon_t *p_hw_syscon);

/**
 * \brief 静态存储器地址通过转换以匹配数据总线宽度
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \return    无
 * \note 调用该接口，可使存储容量多达256MB
 */
am_static_inline
void amhw_emc_sc_enable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs &= ~(1 << 0);
}

/**
 * \brief 静态存储器地址转换失能
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \return    无
 * \note  上电默认值
 */
am_static_inline
void amhw_emc_sc_disable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs |= (1 << 0);
}

/**
 * \brief EMC复位去使能
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \return    无
 * \note 调用该接口，可使存储容量多达256MB
 */
am_static_inline
void amhw_emc_reset_disable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs |= (1 << 1);
}

/**
 * \brief 两个EMC复位均生效
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_emc_reset_assert (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs &= ~(1 << 1);
}

/**
 * \brief EMC突发使能(上电默认值)
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_emc_burst_enable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs &= ~(1 << 2);
}

/**
 * \brief EMC突发禁能
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_emc_burst_disable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs |= (1 << 2);
}

/**
 * @} amhw_if_emc
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_EMC_H */

/* end of file */
