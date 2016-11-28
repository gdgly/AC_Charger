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
 * \brief  SSP硬件操作接口
 * 
 * \internal
 * \par Modification history
 * - 1.01 15-08-19  cod, fix code style and comments.
 * - 1.00 15-07-20  ben, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_SSP_H
#define __AMHW_SSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_ssp
 * \copydoc amhw_ssp.h
 * @{
 */
    
/**
 * \brief ssp寄存器块的结构体
 */
typedef struct amhw_ssp {
    __IO  uint32_t  cr0;    /**< \brief 串行速率，总线类型，数据长度      */
    __IO  uint32_t  cr1;    /**< \brief 选择主机/从机和其他模式           */
    __IO  uint32_t  dr;     /**< \brief 数据寄存器                       */
    __I   uint32_t  sr;     /**< \brief 状态寄存器                       */
    __IO  uint32_t  cpsr;   /**< \brief 时钟预分频寄存器                  */ 
    __IO  uint32_t  imsr;   /**< \brief 中断屏蔽设置清零寄存器            */
    __IO  uint32_t  ris;    /**< \brief 原始中断状态寄存器                */
    __IO  uint32_t  mis;    /**< \brief 屏蔽后的中断状态寄存器            */
    __O   uint32_t  icr;    /**< \brief 中断清零寄存器                    */
    __IO  uint32_t  dmacr;  /**< \brief DMA控制寄存器                     */ 
    
} amhw_ssp_t;


/**
 * \brief 选择ssp数据大小
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] dss      : 数据大小
 * \return    无
 * \note   位数介于 4到16位
 */

am_static_inline 
void amhw_ssp_data_size_select (amhw_ssp_t *p_hw_ssp, uint8_t dss)
{
    p_hw_ssp->cr0 = ((p_hw_ssp->cr0 << 4) | (dss & 0xf));
}

/**
 * \name SSP帧格式
 * @{
 */

/** \brief 通讯帧格式位SPI */
#define AMHW_SSP_FRF_SPI        0

/** \brief 通讯帧格式位SSI */
#define AMHW_SSP_FRF_SSI        1

/** \brief 通讯帧格式位MICWIRE */
#define AMHW_SSP_FRF_MICWIRE    2

/** @} */

/**
 * \brief 数据帧格式设置
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] frf      : 帧格式，值为AMHW_SSP_FRF_*如(#AMHW_SSP_FRF_SPI)
 * \return    无
 * \note      位数介于 4到16位
 */
am_static_inline 
void amhw_ssp_frame_format_set (amhw_ssp_t *p_hw_ssp, uint8_t frf)
{
    p_hw_ssp->cr0 &= ~((uint32_t) 3 << 4);
    p_hw_ssp->cr0 |= ((uint32_t)(frf & 0x3) << 4);
}

/**
 * \brief 极性控制
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] cpol     : 极性控制，值为1或0
 * \return 无
 */
am_static_inline
void amhw_ssp_cpol_set(amhw_ssp_t *p_hw_ssp, uint8_t cpol)
{
    if (cpol) {
        p_hw_ssp->cr0 |= (1 << 6);
    } else {
        p_hw_ssp->cr0 &= ~(1 << 6);
    }    
}

/**
 * \brief 相位控制
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] cpha     : 相位,值为1或0
 * \return 无
 */
am_static_inline
void amhw_ssp_cpha_set (amhw_ssp_t *p_hw_ssp, uint8_t cpha)
{
    if (cpha) {
        p_hw_ssp->cr0 |= (1 << 7);
    } else {
        p_hw_ssp->cr0 &= ~(1 << 7);
    }    
}

/**
 * \brief 位速率
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] scr      : 串行时钟速率
 * \return 无
 */
am_static_inline
void amhw_ssp_scr_set (amhw_ssp_t *p_hw_ssp, uint8_t scr)
{
    p_hw_ssp->cr0 &= ~((uint32_t) 0xff << 8);
    p_hw_ssp->cr0 |= ((uint32_t)(scr & 0xff) << 8);
}

/**
 * \brief 回环模式选择
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] mode     : 启用或禁用，非0为启用
 * \return    无
 */
am_static_inline
void amhw_ssp_mode (amhw_ssp_t *p_hw_ssp, uint8_t mode)
{
    if (mode) {
        p_hw_ssp->cr1 |= 1 << 0;
    }
    else {
        p_hw_ssp->cr1 &=~(1 << 0);
    }
}

/**
 * \brief SSP使能
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_ssp_enable (amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->cr1 |= 1 << 1; 
}

/**
 * \brief SSP失能
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_disable (amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->cr1 &= ~(1 << 1);
}

/**
 * \brief 设置主机模式
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_master_mode (amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->cr1 &= ~(1 << 2); 
}

/**
 * \brief 设置从机模式
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_slave_mode(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->cr1 |= 1 << 2;
}
/**
 * \brief 从机输出设置
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] value    : 1为启用，0为禁用
 * \return    无
 */
am_static_inline
void amhw_ssp_slave_out_set(amhw_ssp_t *p_hw_ssp, uint8_t value)
{
    if (value) p_hw_ssp->cr1 |= 1 << 3;
    else       p_hw_ssp->cr1 &= ~(1 << 3);
}

/**
 * \brief 发送数据
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] data     : 数据
 * \return    无
 */
am_static_inline
void amhw_ssp_send_data(amhw_ssp_t *p_hw_ssp,uint16_t data)
{
    p_hw_ssp->dr = data;
}
/**
 * \brief 读一个字节
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    读到的字节
 */
am_static_inline
uint8_t amhw_ssp_read_8bit_data(amhw_ssp_t *p_hw_ssp)
{
    return (uint8_t)(p_hw_ssp->dr);
}

/**
 * \brief 读一个字
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    读到的字
 */
am_static_inline
uint16_t amhw_ssp_read_16bit_data(amhw_ssp_t *p_hw_ssp)
{
    return (uint16_t)(p_hw_ssp->dr);
}

/** \brief 发送缓存为空  */
#define AMHW_SSP_ST_TF_EMPTY       AM_BIT(0)

/** \brief 发送缓存未满   */
#define AMHW_SSP_ST_TF_NOT_FULL    AM_BIT(1)

/** \brief 接收缓存不为空  */
#define AMHW_SSP_ST_RF_NOT_EMPTY   AM_BIT(2)

/** \brief 接收缓存已满   */
#define AMHW_SSP_ST_RF_FULL        AM_BIT(3)

/** \brief 总线忙标志   */
#define AMHW_SSP_ST_LINE_BUSY      AM_BIT(4)

/**
 * \brief 读状态寄存器
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return 读到的状态
 */
am_static_inline
uint8_t amhw_ssp_read_status(amhw_ssp_t *p_hw_ssp)
{
    return (uint8_t)(p_hw_ssp->sr);
}

/**
 * \brief 设置时钟分频
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] prescale : 分频
 * \return    无
 */
am_static_inline
void amhw_ssp_set_clock_prescale(amhw_ssp_t *p_hw_ssp, uint8_t prescale)
{
    p_hw_ssp->cpsr = prescale; /* prescale > 2 && prescale < 254 && even */
}

/**
 * \name SSP中断类型
 * @{
 */

/** \brief 接收溢出中断   */
#define AMHW_SSP_IM_ROR  AM_BIT(0)

/** \brief 接收超时中断   */
#define AMHW_SSP_IM_RT   AM_BIT(1)

/** \brief Rx FIFO至少有一半为满时触发中断   */
#define AMHW_SSP_IM_RX   AM_BIT(2)

/** \brief Tx FIFO至少有一半为满时触发中断    */
#define AMHW_SSP_IM_TX   AM_BIT(3)

/** @} */

/**
 * \brief 设置中断
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] flags    : 中断标志，值为AMHW_SSP_IM_* 如(#AMHW_SSP_IM_ROR)
 * \return none
 */
am_static_inline
void amhw_ssp_int_set(amhw_ssp_t *p_hw_ssp, uint8_t flags)
{
    p_hw_ssp->imsr = (flags & 0xf);
}

/**
 * \brief 中断清零
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] flags    : 中断标志，值为AMHW_SSP_IM_* 如(#AMHW_SSP_IM_ROR)
 * \return    无
 */
am_static_inline
void amhw_ssp_int_clear(amhw_ssp_t *p_hw_ssp, uint8_t flags)
{
    p_hw_ssp->imsr &= ~(flags);
}

/**
 * \name SSP MIS中断
 * @{
 */

/** \brief 接收溢出中断   */
#define AMHW_SSP_MIS_ROR  AM_BIT(0)

/** \brief 接收超时中断   */
#define AMHW_SSP_MIS_RT   AM_BIT(1)

/** \brief Rx FIFO至少有一半为满时触发中断 */
#define AMHW_SSP_MIS_RX   AM_BIT(2)

/** \brief Tx FIFO至少有一半为满时触发中断   */
#define AMHW_SSP_MIS_TX   AM_BIT(3)

/** @} */

/**
 * \brief 读中断状态寄存器
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    读到的状态字,值为AMHW_SSP_MIS_* 如(#AMHW_SSP_MIS_ROR)
 */
am_static_inline
uint8_t amhw_ssp_int_status_read(amhw_ssp_t *p_hw_ssp)
{
    return (uint8_t)p_hw_ssp->mis;
}

/**
 * \brief 清除溢出中断
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_clear_roric(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->icr |= 1 << 0; /**< \brief 清除接收溢出中断标志  */
}

/**
 * \brief 清除接收超时中断
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_clear_rtic(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->icr |= 1 << 1; /**< \brief  清除接收超时中断标志 */
}

/**
 * \brief dma接收使能
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_dma_rx_enable(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->dmacr |= 1 << 0; 
}

/**
 * \brief dma接收禁用
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_dma_rx_disable(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->dmacr &= ~(1 << 0); 
}

/**
 * \brief dma发送使能
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_dma_tx_enable(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->dmacr |= 1 << 1;
}

/**
 * \brief dma发送禁用
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_ssp_dma_tx_disable(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->dmacr &= ~(1 << 1);
}

/**
 * \brief 设置SSP时钟频率
 * \param[in] p_hw_ssp : 指向SSP寄存器块的指针
 * \param[in] target_clock : SSP时钟频率
 * \param[in] ssp_pclk : SSP外设时钟频率
 * \return    设置后SSP时钟频率
 */
uint32_t amhw_ssp_set_clock(amhw_ssp_t *p_hw_ssp,uint32_t target_clock,uint32_t ssp_pclk);

/**
 * @} amhw_if_ssp
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_SSP_H */

/* end of file */ 

