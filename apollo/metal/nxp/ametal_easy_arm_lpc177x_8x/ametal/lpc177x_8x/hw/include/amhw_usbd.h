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
 * \brief  USB设备硬件操作接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-11-03  cod, first implementation.
 * - 1.00 15-08-04  sam, first implementation.
 * \endinternal
 */

#ifndef __AMHW_USBD_H
#define __AMHW_USBD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_usbd
 * \copydoc amhw_usbd.h
 * @{
 */

/**
 * \brief USBD寄存器块结构体
 */
typedef struct amhw_usbd {

    __I  uint32_t devintst;          /**< \brief 设备中断状态寄存器           */
    __IO uint32_t devinten;          /**< \brief 设备中断使能寄存器          */
    __O  uint32_t devintclr;         /**< \brief 设备中断清零寄存器           */
    __O  uint32_t devintset;         /**< \brief 设备中断状态寄存器           */

    __O  uint32_t cmdcode;           /**< \brief 命令代码寄存器           */
    __I  uint32_t cmddata;           /**< \brief 命令数据寄存器          */

    __I  uint32_t rxdata;            /**< \brief 接收数据寄存器           */
    __O  uint32_t txdata;            /**< \brief 发送数据寄存器          */
    __I  uint32_t rxplen;            /**< \brief 接收包长度寄存器           */
    __O  uint32_t txplen;            /**< \brief 发送包长度寄存器           */
    __IO uint32_t ctrl;              /**< \brief 控制寄存器           */

    __O  uint32_t devintpri;         /**< \brief 设备中断优先级寄存器           */

    __I  uint32_t epintst;           /**< \brief 端点中断状态寄存器           */
    __IO uint32_t epinten;           /**< \brief 端点中断使能寄存器          */
    __O  uint32_t epintclr;          /**< \brief 端点中断清零寄存器           */
    __O  uint32_t epintset;          /**< \brief 端点中断设置寄存器          */
    __O  uint32_t epintpri;          /**< \brief 端点中断优先级 寄存器          */

    __IO uint32_t reep;              /**< \brief 使用端点寄存器           */
    __O  uint32_t epind;             /**< \brief 端点索引寄存器           */
    __IO uint32_t maxpsize;          /**< \brief 最大包长度寄存器           */

    __I  uint32_t dmarst;            /**< \brief DMA请求状态寄存器          */
    __O  uint32_t dmarclr;           /**< \brief DMA请求清零寄存器          */
    __O  uint32_t dmarset;           /**< \brief DMA请求设置寄存器           */
         uint32_t reserved0[9];      /**< \brief 保留         */
    __IO uint32_t udcah;             /**< \brief  UDCA Head寄存器     */
    __I  uint32_t epdmast;           /**< \brief 端点DMA状态寄存器          */
    __O  uint32_t epdmaen;           /**< \brief 端点DMA使能寄存器         */
    __O  uint32_t epdmadis;          /**< \brief 端点DMA禁能寄存器          */
    __I  uint32_t dmaintst;          /**< \brief DMA中断状态寄存器          */
    __IO uint32_t dmainten;          /**< \brief DMA中断使能寄存器          */
         uint32_t reserved1[2];      /**< \brief 保留位          */
    __I  uint32_t eotintst;          /**< \brief 传输结束中断状态寄存器          */
    __O  uint32_t eotintclr;         /**< \brief 传输结束中断清除寄存器          */
    __O  uint32_t eotintset;         /**< \brief 传输结束中断设置寄存器          */
    __I  uint32_t nddrintst;         /**< \brief 新DD请求中断状态寄存器          */
    __O  uint32_t nddrintclr;        /**< \brief 新DD请求中断清除寄存器          */
    __O  uint32_t nddrintset;        /**< \brief 新DD请求中断设置寄存器          */
    __I  uint32_t syserrintst;       /**< \brief 系统错误中断状态寄存器          */
    __O  uint32_t syserrintclr;      /**< \brief 系统错误中断清除寄存器          */
    __O  uint32_t syserrintset;      /**< \brief 系统错误中断设置寄存器          */
         uint32_t reserved2[844];    /**< \brief 保留   */

    __IO uint32_t usbclkctrl;        /**< \brief  USB 时钟控制寄存器           */
    __I  uint32_t usbclkst;          /**< \brief  USB 时钟状态寄存器           */

} amhw_usbd_t;


/**
 * \name USB端点位标志
 * \anchor grp_amhw_usbd_ep_bit
 * @{
 */

#define AMHW_USBD_BIT_EP(x)     (1 << x)   /**< \brief  端点位          */

/** @} */

/**
 * \name USB时钟控制位定义
 * \anchor grp_amhw_usbd_clock_bit
 * @{
 */
#define AMHW_USBD_DEV_CLK      (1 << 1)  /**< \brief  设备时钟          */
#define AMHW_USBD_PORTSEL_CLK  (1 << 3)  /**< \brief  端口选择寄存器时钟（只适用LPC177x_8x） */
#define AMHW_USBD_AHB_CLK      (1 << 4)  /**< \brief  AHB时钟           */

/** @} */

/**
 * \name 定义  USB设备中断位定义
 * \anchor grp_amhw_usbd_interrupt_flag
 * @{
 */

#define AMHW_USBD_INT_FRAME        (1 << 0)  /**< \brief  每隔1ms产生一次帧中断           */
#define AMHW_USBD_INT_EP_FAST      (1 << 1)  /**< \brief  端点的快速中断           */
#define AMHW_USBD_INT_EP_SLOW      (1 << 2)  /**< \brief  端点的慢速中断           */
#define AMHW_USBD_INT_DEV_STAT     (1 << 3)  /**< \brief  USB总线复位、USB挂起改变或连接改变时置位           */
#define AMHW_USBD_INT_CCEMPTY      (1 << 4)  /**< \brief  命令代码寄存器（USBCmdCode）为空（可写入新的命令）          */
#define AMHW_USBD_INT_CDFULL       (1 << 5)  /**< \brief  命令数据寄存器（USBCmdData）已满（现在可以读取数据）           */
#define AMHW_USBD_INT_RXENDPKT     (1 << 6)  /**< \brief  在端点缓冲区中的当前数据包已传送给CPU           */
#define AMHW_USBD_INT_TXENDPKT     (1 << 7)  /**< \brief  传输到端点缓冲区的数据字节数与TxPacket长度寄存器（USBTxPLen）中编程设定的字节数相等           */
#define AMHW_USBD_INT_EP_RLZED     (1 << 8)  /**< \brief  端点被使用          */
#define AMHW_USBD_INT_ERR          (1 << 9)  /**< \brief  错误中断          */

/** @} */

/**
 * \name 定义  USB设备中断优先级寄存器
 * @{
 */

#define AMHW_USBD_FRAME_ENTER_HP   (1 << 0)  /**< \brief  FRAME中断将进入USB_INT_REQ_HP           */
#define AMHW_USBD_EPFAST_ENTER_HP  (1 << 1)  /**< \brief  EP_FAST中断将进入USB_INT_REQ_HP           */

/** @} */

/**
 * \name USB控制寄存器位定义
 * @{
 */

#define AMHW_USBD_RD_EN       (1 << 0)           /**< \brief  读模式使能           */
#define AMHW_USBD_WR_EN       (1 << 1)           /**< \brief  写模式使能           */

#define AMHW_USBD_LOG_EP(x)   (((x) >> 1) << 2)  /**< \brief 逻辑端点设置，x为物理端点       */

/** @} */

/**
 * \name USB接收包长度寄存器位定义
 * @{
 */

#define AMHW_USBD_RX_PKTLEN_MASK    0x3FF      /**< \brief  端点接收数据长度掩码           */
#define AMHW_USBD_RX_BIT_DV        (1 << 10)   /**< \brief  数据有效位定义          */
#define AMHW_USBD_RX_BIT_PKT_RDY   (1 << 11)   /**< \brief  数据包准备位定义          */

/** @} */

/**
 * \name USB DMA传输中断类型
 * \anchor grp_amhw_usbd_dmaint_flag
 * @{
 */

#define AMHW_USBD_DMAINT_EOT      (1 << 0)  /**< \brief  DMA传输结束中断          */
#define AMHW_USBD_DMAINT_NDDR     (1 << 1)  /**< \brief  新的DMA传输请求中断    */
#define AMHW_USBD_DMAINT_SYSERR   (1 << 2)  /**< \brief  系统错误中断           */

/** @} */

/**
 * \brief USB时钟使能
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] clk_flag    : 时钟使能位,参见\ref grp_amhw_usbd_clock_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_clk_enable (amhw_usbd_t *p_hw_usbd, uint32_t clk_flag)
{
    p_hw_usbd->usbclkctrl = clk_flag;
}

/**
 * \brief USB时钟失能
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] clk_flag  : 时钟使能位,参见\ref grp_amhw_usbd_clock_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_clk_disable (amhw_usbd_t *p_hw_usbd, uint32_t clk_flag)
{
    p_hw_usbd->usbclkctrl &= ~clk_flag;
}

/**
 * \brief USB时钟状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 时钟状态,参见\ref grp_amhw_usbd_clock_bit
 */
am_static_inline
uint32_t amhw_usbd_clkstat_get (amhw_usbd_t *p_hw_usbd)
{
    return p_hw_usbd->usbclkst;
}

/**
 * \brief USB设备中断状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 无
 */
am_static_inline
uint32_t amhw_usbd_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->devintst;
}

/**
 * \brief USB设备中断使能
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag    : 中断使能位,参见\ref grp_amhw_usbd_interrupt_flag
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_int_enable (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->devinten |= int_flag;
}

/**
 * \brief 获取使能设备中断
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 使能中断位,参见\ref grp_amhw_usbd_interrupt_flag
 */
am_static_inline
uint32_t amhw_usbd_int_enable_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->devinten;
}

/**
 * \brief USB设备中断清除
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag    : 中断清除位,参见\ref grp_amhw_usbd_interrupt_flag
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_int_clr (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->devintclr = int_flag;
}

/**
 * \brief USB设备中断设置
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag    : 中断设置位,参见\ref grp_amhw_usbd_interrupt_flag
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_int_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->devintset = int_flag;
}

/**
 * \brief USB设备中断优先级设置
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag    : 中断优先级设置位,值为#AMHW_USBD_FRAME_ENTER_HP 或
 *                          #AMHW_USBD_EPFAST_ENTER_HP,清除置位写0
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_intpri_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->devintpri |= int_flag;
}

/**
 * \brief USB端点中断状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 端点中断状态
 */
am_static_inline
uint32_t amhw_usbd_ep_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->epintst;
}

/**
 * \brief USB端点中断使能
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] flag        : 端点位标志，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_ep_int_enable (amhw_usbd_t *p_hw_usbd, uint32_t flag)
{
    p_hw_usbd->epinten |= flag;
}

/**
 * \brief 失能端点从模式中断
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] flag        : 失能标志，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_ep_int_disable (amhw_usbd_t *p_hw_usbd, uint32_t flag)
{
    p_hw_usbd->epinten &= ~flag;
}

/**
 * \brief USB端点中断清除
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag    : 端点中断清除位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_ep_int_clr (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->epintclr = int_flag;
}

/**
 * \brief USB端点中断设置
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag    : 端点中断设置位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_ep_int_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->epintset = int_flag;
}

/**
 * \brief 指定端点端点中断优先级设置位EP_FAST
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag    : 端点中断优先级设置位,，参见\ref grp_amhw_usbd_ep_bit
 * \return 无
 */
am_static_inline
void amhw_usbd_intpri_epfast_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->epintpri = int_flag;
}

/**
 * \brief 指定端点中断优先级设置为EP_SLOW
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag  : 端点中断优先级设置位,，参见\ref grp_amhw_usbd_ep_bit
 * \return 无
 */
am_static_inline
void amhw_usbd_intpri_epslow_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->epintpri &= ~int_flag;
}

/**
 * \brief USB使用端点设置
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_flag     : 使用端点设置位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_ep_use_set (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    p_hw_usbd->reep |= ep_flag;
}

/**
 * \brief 设置不再使用指定端点
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_flag     : 不使用端点设置位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_ep_no_use_set (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    p_hw_usbd->reep &= ~ep_flag;
}


/**
 * \brief 端点最大包设置
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep          : 物理端点号，值为0~31
 * \param[in] size        : 最大包大小，值为0~1024，具体根据实际端点号设置
 *
 * \return 无
 */
void amhw_usbd_ep_maxpacksize_set (amhw_usbd_t *p_hw_usbd,
                                   uint8_t      ep,
                                   uint16_t     size);

/**
 * \brief 端点DMA传输请求请求状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] dma_ep      : 端点DMA请求状态位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 请求状态
 */
am_static_inline
uint32_t amhw_usbd_dmarst_stat_get (amhw_usbd_t *p_hw_usbd, uint32_t dma_ep)
{
    return (uint32_t)(p_hw_usbd->dmarst & dma_ep);
}


/**
 * \brief USB端点DMA传输请求清除
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] dma_ep      : 端点DMA清除位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_dmarst_clr (amhw_usbd_t *p_hw_usbd, uint32_t dma_ep)
{
    p_hw_usbd->dmarclr = dma_ep;
}

/**
 * \brief USB端点DMA传输请求设置
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] int_flag    : 中断设置位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_dmarst_set (amhw_usbd_t *p_hw_usbd, uint32_t dma_ep)
{
    p_hw_usbd->dmarset = dma_ep;
}

/**
 * \brief USB UDCA Head 设置
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] udca_addr   : UDCA 地址
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_udcah_set (amhw_usbd_t *p_hw_usbd, uint32_t udca_addr)
{
    p_hw_usbd->udcah = udca_addr;
}

/**
 * \brief USB端点DMA状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_flag     : 端点DMA状态位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 端点DMA状态，参见\ref grp_amhw_usbd_ep_bit
 */
am_static_inline
uint32_t amhw_usbd_ep_dmastat_get (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    return (uint32_t)(p_hw_usbd->epdmast & ep_flag);
}

/**
 * \brief 端点DMA传输使能
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_flag     : DMA使能端点标志，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_ep_dma_enable (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    p_hw_usbd->epdmaen = ep_flag;
}

/**
 * \brief 端点DMA传输失能
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_flag     : 端点中断清除位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_ep_dma_disable (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    p_hw_usbd->epdmadis = ep_flag;
}

/**
 * \brief USB DMA  中断状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return DMA中断状态，参见\ref grp_amhw_usbd_dmaint_flag
 */
am_static_inline
uint32_t amhw_usbd_dmaint_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->dmaintst;
}

/**
 * \brief USB DMA 中断使能
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] dma_int     : DMA中断使能位，参见\ref grp_amhw_usbd_dmaint_flag
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_dma_int_enable (amhw_usbd_t *p_hw_usbd, uint32_t dma_int)
{
    p_hw_usbd->dmainten |= dma_int;
}

/**
 * \brief USB 传输结束中断状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 传输结束中断状态
 */
am_static_inline
uint32_t amhw_usbd_eot_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->eotintst;
}


/**
 * \brief USB 传输结束中断清零
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] eot_ep      : 传输结束中断清零位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_eot_intstat_clr (amhw_usbd_t *p_hw_usbd, uint32_t eot_ep)
{
    p_hw_usbd->eotintclr = eot_ep;
}

/**
 * \brief USB传输结束中断置位
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] eot_ep      : 传输结束中断置位位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_eot_intstat_set (amhw_usbd_t *p_hw_usbd, uint32_t eot_ep)
{
    p_hw_usbd->eotintset = eot_ep;
}

/**
 * \brief USB 新DD请求中断状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] dd_ep       : USB 新DD请求中断状态位
 *
 * \return USB 新DD请求中断状态
 */
am_static_inline
uint32_t amhw_usbd_nddr_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->nddrintst;
}


/**
 * \brief USB 新DD请求中断清零
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] dd_ep       : 新DD请求中断清零位,参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_nddr_intstat_clr (amhw_usbd_t *p_hw_usbd, uint32_t dd_ep)
{
    p_hw_usbd->nddrintclr = dd_ep;
}

/**
 * \brief USB新DD请求中断置位
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] dd_ep       : 新DD请求中断置位位,参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_nddr_intstat_set (amhw_usbd_t *p_hw_usbd, uint32_t dd_ep)
{
    p_hw_usbd->nddrintset = dd_ep;
}

/**
 * \brief USB 系统错误中断状态获取
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 端点DMA传输系统错误中断状态
 */
am_static_inline
uint32_t amhw_usbd_syserr_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->syserrintst;
}


/**
 * \brief USB 系统错误中断清零
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] err_ep      : 系统错误中断清零位，参见\ref grp_amhw_usbd_ep_bit
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_syserr_intstat_clr (amhw_usbd_t *p_hw_usbd, uint32_t err_ep)
{
    p_hw_usbd->syserrintclr = err_ep;
}

/**
 * \brief USB系统错误中断置位
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] err_ep      : 系统错误中断置位位
 *
 * \return 无
 */
am_static_inline
void amhw_usbd_syserr_intstat_set (amhw_usbd_t *p_hw_usbd, uint32_t err_ep)
{
    p_hw_usbd->syserrintset = err_ep;
}

/*****************************************************************************
 *   SIE命令操作
 *****************************************************************************/
/**
 * \name SIE命令
 * \anchor grp_amhw_sie_cmd
 * @{
 */

#define AMHW_CMD_SET_ADDR          0x00D00500                 /**< \brief 设置地址          */
#define AMHW_CMD_CFG_DEV           0x00D80500                 /**< \brief 配置设备          */
#define AMHW_CMD_SET_MODE          0x00F30500                 /**< \brief 设置模式          */
#define AMHW_CMD_RD_FRAME          0x00F50500                 /**< \brief 读当前帧编号（命令） */
#define AMHW_DAT_RD_FRAME          0x00F50200                 /**< \brief 读当前帧编号（数据） */
#define AMHW_CMD_RD_TEST           0x00FD0500                 /**< \brief 读测试寄存器（命令） */
#define AMHW_DAT_RD_TEST           0x00FD0200                 /**< \brief 读测试寄存器（数据）  */
#define AMHW_CMD_SET_DEV_STAT      0x00FE0500                 /**< \brief 设置设备状态（命令）  */
#define AMHW_CMD_GET_DEV_STAT      0x00FE0500                 /**< \brief 获取设备状态（命令）  */
#define AMHW_DAT_GET_DEV_STAT      0x00FE0200                 /**< \brief 设置设备状态（数据）  */
#define AMHW_CMD_GET_ERR_CODE      0x00FF0500                 /**< \brief 获取错误代码（命令）  */
#define AMHW_DAT_GET_ERR_CODE      0x00FF0200                 /**< \brief 获取错误代码（数据）  */
#define AMHW_CMD_RD_ERR_STAT       0x00FB0500                 /**< \brief 读错误状态（命令）  */
#define AMHW_DAT_RD_ERR_STAT       0x00FB0200                 /**< \brief 获错误状态（数据）  */
#define AMHW_DAT_WR_BYTE(x)       (0x00000100 | ((x) << 16))  /**< \brief 读/写数据  */
#define AMHW_CMD_SEL_EP(x)        (0x00000500 | ((x) << 16))  /**< \brief 选择端点（命令）  */
#define AMHW_DAT_SEL_EP(x)        (0x00000200 | ((x) << 16))  /**< \brief 选择端点（数据）  */
#define AMHW_CMD_SEL_EP_CLRI(x)   (0x00400500 | ((x) << 16))  /**< \brief 选择端点/清除中断（命令）  */
#define AMHW_DAT_SEL_EP_CLRI(x)   (0x00400200 | ((x) << 16))  /**< \brief 选择端点/清除中断（数据）  */
#define AMHW_CMD_SET_EP_STAT(x)   (0x00400500 | ((x) << 16))  /**< \brief 设置端点状态  */
#define AMHW_CMD_CLR_BUF           0x00F20500                 /**< \brief 清空缓冲区（命令）  */
#define AMHW_DAT_CLR_BUF           0x00F20200                 /**< \brief 清空缓冲区（数据）  */
#define AMHW_CMD_VALID_BUF         0x00FA0500                 /**< \brief 确认缓冲区  */

/** @} */

/**
 * \brief SIE获取一字节数据
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] cmd       : SIE命令，参见\ref grp_amhw_sie_cmd
 *
 * \return 无
 */
uint8_t amhw_usbd_sie_data_get (amhw_usbd_t *p_hw_usbd, uint32_t cmd);

/**
 * \brief SIE获取一字节数据
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] cmd       : SIE命令，参见\ref grp_amhw_sie_cmd
 * \param[in] data      : SIE数据，若无填入0
 *
 * \return 无
 */
void amhw_usbd_sie_cmd_send (amhw_usbd_t *p_hw_usbd, uint32_t cmd, uint32_t data);

/**
 * \brief 设置USB设备地址，使能设备
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] addr      : 设备地址
 * \param[in] enable    : 使能设备位
 *
 * \return 无
 */
void amhw_usbd_set_address_enable (amhw_usbd_t *p_hw_usbd,
                                   uint8_t      addr,
                                   bool_t       enable);

/**
 * \brief 配置设备，所有使能的配置端点可作出相应
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] cfg       : 配置设备
 *
 * \return 无
 */
void amhw_usbd_cfg_device_set (amhw_usbd_t *p_hw_usbd, bool_t cfg);

/**
 * \brief 设置设备模式
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] mode      : 设备模式值
 *
 * \return 无
 */
void amhw_usbd_mode_set (amhw_usbd_t *p_hw_usbd, uint8_t mode);

/**
 * \brief 读取当前帧编号
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 当前帧编号
 */
uint16_t amhw_usbd_curframe_num_read (amhw_usbd_t *p_hw_usbd);

/**
 * \brief 读测试寄存器
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 读取测试值，若USB时钟运行，则返回值为0xA50F
 */
uint16_t amhw_usbd_test_register_read (amhw_usbd_t *p_hw_usbd);

/**
 * \name USB设备状态位定义
 * @{
 */
#define AMHW_DEV_CON          (1 << 0)     /**< \brief 连接位表示当前设备连接状态  */
#define AMHW_DEV_CON_CH       (1 << 1)     /**< \brief 连接发生改变位  */
#define AMHW_DEV_SUS          (1 << 2)     /**< \brief 挂起状态位  */
#define AMHW_DEV_SUS_CH       (1 << 3)     /**< \brief 挂起状态改变位  */
#define AMHW_DEV_RST          (1 << 4)     /**< \brief 总线复位位  */
/** @} */

/**
 * \brief 设置设备状态
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] status    ： 设备状态，值为AMHW_DEV_*如(#AMHW_DEV_CON)
 *
 * \return 无
 */
void amhw_usbd_device_status_set (amhw_usbd_t *p_hw_usbd, uint8_t status);

/**
 * \brief 获取设备状态
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 设备状态，值为AMHW_DEV_*如(#AMHW_DEV_CON)
 */
uint8_t amhw_usbd_device_status_get (amhw_usbd_t *p_hw_usbd);

/**
 * \brief 获取错误代码
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 错误代码
 */
uint8_t amhw_usbd_err_code_get (amhw_usbd_t *p_hw_usbd);

/**
 * \name USB设备状态位定义
 * @{
 */
#define AMHW_ERR_PID_ERR     (1 << 0)     /**< \brief PID编码错误、未知的PID或未知的令牌CRC  */
#define AMHW_ERR_UEPKT       (1 << 1)     /**< \brief 意外的信息包－任何违反规范的信息包序列 */
#define AMHW_ERR_DCRC        (1 << 2)     /**< \brief 数据CRC错误  */
#define AMHW_ERR_TIMEOUT     (1 << 3)     /**< \brief 超时错误  */
#define AMHW_ERR_EOP         (1 << 4)     /**< \brief 信息包结束错误  */
#define AMHW_ERR_B_OVRN      (1 << 5)     /**< \brief 缓冲区溢出  */
#define AMHW_ERR_BTSTF       (1 << 6)     /**< \brief 位填充错误  */
#define AMHW_ERR_TGL_ERR     (1 << 7)     /**< \brief 数据PID中的错误翻转位（toggle bit），数据无效  */
/** @} */

/**
 * \brief 获取错误状态
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 错误状态,值为AMHW_ERR_*如(#AMHW_ERR_PID_ERR)
 */
uint8_t amhw_usbd_err_status_get (amhw_usbd_t *p_hw_usbd);


/**
 * \name USB选择端点位定义
 * @{
 */
#define AMHW_EP_SEL_FE         (1 << 0)    /**< \brief 端点满/空位  */
#define AMHW_EP_SEL_ST         (1 << 1)    /**< \brief 暂停端点指示位  */
#define AMHW_EP_SEL_STP        (1 << 2)    /**< \brief SETUP位 */
#define AMHW_EP_SEL_PO         (1 << 3)    /**< \brief 包覆盖位 */
#define AMHW_EP_SEL_EPN        (1 << 4)    /**< \brief EP NAK位 */
#define AMHW_EP_SEL_B_1_FULL   (1 << 5)    /**< \brief 缓冲区1状态位 */
#define AMHW_EP_SEL_B_2_FULL   (1 << 6)    /**< \brief 缓冲区2状态位 */

/** @} */

/**
 * \brief 选择端点
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_index  : 物理端点编号，值为0~31
 *
 * \return 端点状态信息，值为AMHW_EP_SEL_*如(#AMHW_EP_SEL)
 */
uint8_t amhw_usbd_endpoint_select (amhw_usbd_t *p_hw_usbd, uint8_t ep_index);

/**
 * \brief 选择端点清除中断并返回端点信息
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_index  : 物理端点编号，值为0~31
 *
 * \return 端点状态信息，值为AMHW_EP_SEL_*如(#AMHW_EP_SEL)
 */
uint8_t amhw_usbd_endpoint_select_int_clr (amhw_usbd_t *p_hw_usbd, uint8_t ep_index);


/**
 * \name USB端点状态位定义
 * @{
 */
#define AMHW_EP_STAT_ST        (1 << 0)   /**< \brief 暂停的端点位  */
#define AMHW_EP_STAT_DA        (1 << 5)   /**< \brief 禁能端点位  */
#define AMHW_EP_STAT_RF_MO     (1 << 6)   /**< \brief 速率反馈模式位  */
#define AMHW_EP_STAT_CND_ST    (1 << 7)   /**< \brief 条件暂停位  */

/** @} */

/**
 * \brief 设置端点状态
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_index  : 物理端点编号，值为0~31
 * \param[in] status    : 端点状态,值为AMHW_EP_STAT_*如(#AMHW_EP_STAT_ST)
 *
 * \return 无
 */
void amhw_usbd_endpoint_status_set (amhw_usbd_t *p_hw_usbd,
                                    uint8_t      ep_index,
                                    uint8_t      status);

/**
 * \brief 清除OUT端点缓冲区
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \retval           1  : 之前接收到的信息包被后面的SETUP包覆盖
 * \retval           0  : 之前接收到的信息包保持完好
 */
uint8_t amhw_usbd_buffer_clr (amhw_usbd_t *p_hw_usbd);

/**
 * \brief 确认缓冲区
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 *
 * \return 无
 */
void amhw_usbd_vaild_buffer (amhw_usbd_t *p_hw_usbd);

/*****************************************************************************
 * 读写端点操作
 *****************************************************************************/
/**
 * \brief 向指定物理端点写入数据
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_index  : 物理端点编号
 * \param[in] p_buf     : 发送缓冲区指针
 * \param[in] len       : 发送数据长度
 *
 * \return 实际发送数据长度
 */
uint16_t amhw_usbd_endpoint_write (amhw_usbd_t    *p_hw_usbd,
                                   uint8_t         ep_index,
                                   const uint8_t  *p_buf,
                                   uint16_t        len);

/**
 * \brief 向指定物理端点读取数据
 *
 * \param[in] p_hw_usbd : 指向USB寄存器块的指针
 * \param[in] ep_index  : 物理端点编号
 * \param[in] p_buf     : 接收缓冲区指针
 * \param[in] len       : 接收数据长度
 *
 * \return 实际接收数据长度
 */
uint16_t amhw_usbd_endpoint_read (amhw_usbd_t *p_hw_usbd,
                                  uint8_t      ep_index,
                                  uint8_t     *p_buf,
                                  uint16_t     len);

/*****************************************************************************
 * DMA传输相关操作
 *****************************************************************************/
/**
 * \brief DMA描述符（DD）结构体定义
 */
typedef struct amhw_usbd_dd {

    uint32_t    next;           /**< \brief 下个DMA描述符起始地址  */

    uint32_t    control;        /**< \brief DD(DMA描述符)控制信息 */

    uint32_t    buf;            /**< \brief DMA缓冲区起始地址  */

    uint32_t    status;         /**< \brief 状态信息 */

    uint32_t    iso_buf;        /**< \brief 同步端点帧编号的缓冲区地址（同步端点使用）  */

} amhw_usbd_dd_t;


/**
 * \name DD控制信息相关定义
 * @{
 */

#define AMHW_DD_MODE_NORMAL     (0 << 0)   /**< \brief  正常模式            */
#define AMHW_DD_MODE_ATLE       (1 << 0)   /**< \brief  ATLE模式            */

#define AMHW_DD_NEXT_DD_VALID   (1 << 2)   /**< \brief 下个DD有效            */

#define AMHW_DD_ISO_EP          (1 << 4)   /**< \brief 同步端点位            */

/** \brief 最大信息包大小（设置）            */
#define AMHW_DD_MAXPKT_SIZE(x)  (((x) & 0x7FF) << 5)

/** \brief DMA传输字节数/包数（设置）  */
#define AMHW_DD_BUF_LEN(x)      (((x) & 0xFFFF) << 16)

/** @} */

/**
 * \name DD状态信息位定义
 * @{
 */

#define AMHW_DD_RETIRED              0x01  /**< \brief DD使用完标志            */

#define AMHW_DD_STATUS_MASK          0x1F  /**< \brief 状态掩码(含Retired位) */

#define AMHW_DD_STATUS_NOT_SERV      0x00  /**< \brief 指示没有包没传输            */
#define AMHW_DD_STATUS_BEING_SERV    0x01  /**< \brief 指示至少有一个包被传输      */
#define AMHW_DD_STATUS_UNDER_RUN     0x03  /**< \brief 指示收到短包而中止          */
#define AMHW_DD_STATUS_SYS_ERR       0x09  /**< \brief 指示系统总线错误            */
#define AMHW_DD_STATUS_OVER_RUN      0x11  /**< \brief 指示缓冲区到达末尾错误      */
#define AMHW_DD_STATUS_NORMAL_COMP   0x05  /**< \brief 指示DMA传输正常结束         */

#define AMHW_DD_PACKET_VALID      (1 << 5) /**< \brief 包有效（适用同步端点）        */

/** \brief LS_byte_extracted,ATLE模式   */
#define AMHW_DD_LS_BYTE_EXTRACTED (1 << 6)

/** \brief MS_byte_extracted,ATLE模式   */
#define AMHW_DD_MS_BYTE_EXTRACTED (1 << 7)

/**< \brief 嵌入到输入数据包中的消息长度位置的偏移量   */
#define AMHW_DD_MESS_LEN_POS(x)   (((x) & 0x3F) << 8)

/** \brief 当前DMA传输长度        */
#define AMHW_DD_PRESENT_CNT(x)  (((x) >> 16) & 0x7FF)

/** @} */


/**
 *@}
 */

#ifdef __cplusplus
}
#endif

#endif /* AMHW_USBD_H_ */
