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
 * \brief 匿名结构体段的开始
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
 * \brief LPC177X_8X UART 寄存器结构体
 */
typedef struct  {
    union {
        __I  uint32_t  rbr;        /**< \brief 接收缓冲寄存器     */
        __O  uint32_t  thr;        /**< \brief 发送保持寄存器     */
        __IO uint32_t  dll;        /**< \brief 除数锁存器               */
    };
    union {
        __IO uint32_t  dlm;        /**< \brief 接收缓冲寄存器     */
        __IO uint32_t  ier;        /**< \brief 中断使能寄存器     */
    };
    union {
        __I  uint32_t  iir;        /**< \brief 中断标志寄存器     */
        __O  uint32_t  fcr;        /**< \brief FIFO控制寄存器     */
    };
    __IO uint32_t  lcr;            /**< \brief 串口线控制寄存器                                                         */
    __IO uint32_t  mcr;            /**< \brief 调制解调器控制寄存器,仅UART1/4可使用     */
    __I  uint32_t  lsr;            /**< \brief 线状态寄存器                                                                   */
    __IO uint32_t  msr;            /**< \brief 调制解调器状态寄存器,仅UART1/4可使用     */
    __IO uint32_t  scr;            /**< \brief 高速缓存寄存器                                                              */
    __IO uint32_t  acr;            /**< \brief 自动波特率（auto-baud）控制寄存器             */
    __IO uint32_t  icr;            /**< \brief IrDA控制寄存器,UART4可用                                   */
    __IO uint32_t  fdr;            /**< \brief 小数分频寄存器                                                              */
    __IO uint32_t  osr;            /**< \brief 过采样寄存器,UART4可用                                         */
    __IO uint32_t  ter;            /**< \brief 发送使能寄存器,UART0/1/2/3可用                    */
         uint32_t  reserved0[3];   /**< \brief 保留位                                                                                  */
    __IO uint32_t  hden;           /**< \brief Half-duplex使能寄存器                                           */
         uint32_t  reserved1[1];   /**< \brief 保留位                                                                                  */
    __IO uint32_t  sci_ctrl;       /**< \brief 智能卡接口控制寄存器,UART4可用                      */
    __IO uint32_t  rs485ctrl;      /**< \brief RS485 控制寄存器                                                         */
    __IO uint32_t  adrmatch;       /**< \brief RS485 地址匹配寄存器                                                */
    __IO uint32_t  rs485dly;       /**< \brief RS485 方向控制延时寄存器                                      */

    union {
    	__IO uint32_t  syncctrl;   /**< \brief 同步模式控制寄存器        */
    	__I  uint32_t  fifolvl;    /**< \brief FIFO水平寄存器       */
    };

    __IO uint32_t  u4ter;          /**< \brief UART4发送使能寄存器,UART4可用                         */
} amhw_usart_t;

/**
 * \name 定义USART中断配置
 * \anchor grp_amhw_usart_irq_cfg_flags
 * @{
 */
#define AMHW_USART_IER_RBRINT   (1 << 0)  /**< \brief 使能接收中断   */

#define AMHW_USART_IER_THREINT  (1 << 1)  /**< \brief 使能发送中断   */
 
#define AMHW_USART_IER_RXLSINT  (1 << 2)  /**< \brief 使能接收线性状态中断   */

#define AMHW_USART_IER_MODEMINT (1 << 3)  /**< \brief 使能串口1模式中断   */
#define AMHW_USART_IER_CTIINT   (1 << 7)  /**< \brief 使能串口1超时中断   */

#define AMHW_USART_IER_ABEOINT  (1 << 8)  /**< \brief 使能自动波特率配置结束中断   */

#define AMHW_USART_IER_ABTOINT  (1 << 9)  /**< \brief 使能自动波特率配置超时中断   */

#define AMHW_USART_IER_INTALL   (0x038F)  /**< \brief 所有中断  */

/** @} */

/**
 * \name USART中断状态标志位
 * @{ 
 */
 
/** \brief 当为0时，至少有一个中断挂起；当为1时，没有一个中断挂起     */
#define AMHW_USART_IIR_INTSTATUS    (1 << 0)

#define AMHW_USART_RLS_INTID      (3 << 1)     /**< \brief 接收线性中断状态ID   */
#define AMHW_USART_RDA_INTID      (2 << 1)     /**< \brief 接收数据中断ID   */
#define AMHW_USART_CTI_INTID      (6 << 1)     /**< \brief 超时中断ID   */
#define AMHW_USART_THRE_INTID     (1 << 1)     /**< \brief 发送数据中断ID   */
#define AMHW_USART_MODEM_INTID    (0 << 1)     /**< \brief 模式中断ID   */
#define AMHW_USART_IIR_FIFOENABLE (3 << 6)     /**< \brief 等效于UnFCR[0]   */
#define AMHW_USART_IIR_ABEOINT    (1 << 8)     /**< \brief 自动波特率配置结束中断状态  */
#define AMHW_USART_IIR_ABTOINT    (1 << 9)     /**< \brief 自动波特率配置超时中断状态 */

#define AMHW_USART_INTID_MASK     (0x07 << 1)  /**< \brief 中断标识掩码  */

#define AMHW_USART_IIR_ALL        (0x030F)     /**< \brief 所有中断状态  */


/** @} */

/**
 * \name  USART的FIFO控制寄存器宏定义
 * @{      
 */
#define AMHW_USART_FCR_FIFO        (1 << 0) /**< \brief 使能发送接收FIFO  */
      
#define AMHW_USART_RXFIFO_RESET    (1 << 1) /**< \brief 清空接收FIFO  */

#define AMHW_USART_TXFIFO_RESET    (1 << 2) /**< \brief 清空发送FIFO  */

#define AMHW_USART_FCR_DMA         (1 << 3) /**< \brief DMA模式下FIFO  */

/** @} */

/**
 * \name  USART的接收触发中断阈值
 * @{      
 */
#define AMHW_USART_RX_TRILEVEL0       (0 << 6)  /**< \brief 1个字节  */
#define AMHW_USART_RX_TRILEVEL1       (1 << 6)  /**< \brief 4个字节  */
#define AMHW_USART_RX_TRILEVEL2       (2 << 6)  /**< \brief 8个字节  */
#define AMHW_USART_RX_TRILEVEL3       (3 << 6)  /**< \brief 14个字节  */

/** @} */

/**
 * \name USART 帧格式配置
 * @{       
 */
 
#define AMHW_USART_LCR_5BIT      0     /**< \brief 5位字节长度  */
#define AMHW_USART_LCR_6BIT      1     /**< \brief 6位字节长度  */
#define AMHW_USART_LCR_7BIT      2     /**< \brief 7位字节长度  */
#define AMHW_USART_LCR_8BIT      3     /**< \brief 8位字节长度  */

#define AMHW_USART_LCR_STOP_1      (0 << 2)  /**< \brief  1个结束位   */

#define AMHW_USART_LCR_STOP_2      (1 << 2)  /**< \brief  2个结束位   */

#define AMHW_USART_LCR_PARITY      (1 << 3)  /**< \brief  使能校验    */

#define AMHW_USART_LCR_PARITY_NO   (0 << 3)  /**< \brief  关闭校验    */

#define AMHW_USART_PARITY_ODD      (0 << 4)  /**< \brief  奇校验    */
#define AMHW_USART_PARITY_EVEN     (1 << 4)  /**< \brief  偶校验    */
#define AMHW_USART_PARITY_1STICK   (2 << 4)  /**< \brief  强制为“1”stick校验    */
#define AMHW_USART_PARITY_0STICK   (3 << 4)  /**< \brief  强制为“0”stick校验    */

#define AMHW_USART_LCR_BREAK       (1 << 6)  /**< \brief  使能传输中止   */
  
#define AMHW_USART_DLAB_ENABLE     (1 << 7)  /**< \brief  进入分频器     */
 
/** @} */

/**
 * \name 定义USART1模式设置
 * \anchor grp_amhw_usart_mcr_cfg_flags
 * @{
 */
#define AMHW_USART_MCR_DTR        (1 << 0)  /**< \brief  DTR     */

#define AMHW_USART_MCR_RTS        (1 << 1)  /**< \brief  RTS     */

#define AMHW_USART_MCR_LOOPBACK   (1 << 4)  /**< \brief  使能回馈模式     */

#define AMHW_USART_MCR_RTSEN      (1 << 6)  /**< \brief  使能auto-rts 流控制 */

#define AMHW_USART_MCR_CTSEN      (1 << 7)  /**< \brief  使能auto-cts 流控制 */

/** @} */

/**
 * \name 定义USART线性状态
 * \anchor grp_amhw_usart_lsr_cfg_flags
 * @{
 */
#define AMHW_USART_LSR_RDR    (1 << 0)  /**< \brief  接收FIFO中有数据  */

#define AMHW_USART_LSR_OE     (1 << 1)  /**< \brief  溢出错误    */

#define AMHW_USART_LSR_PE     (1 << 2)  /**< \brief  检验错误   */

#define AMHW_USART_LSR_FE     (1 << 3)  /**< \brief  帧错误    */

#define AMHW_USART_LSR_BI     (1 << 4)  /**< \brief  中止错误   */

#define AMHW_USART_LSR_THRE   (1 << 5)  /**< \brief UTHR 为空   */

#define AMHW_USART_LSR_TEMT   (1 << 6)  /**< \brief UTHR and the U1TSR 为空*/

/** \brief UART RBR 包含至少一个 UART1 接收错误 */
#define AMHW_USART_LSR_RXFE   (1 << 7)

/** @} */

/**
 * \name 定义USART模式状态
 * \anchor grp_amhw_usart_msr_cfg_flags
 * @{
 */
#define AMHW_USART_MSR_DELTACTS   (1 << 0)  /**< \brief  设置输入CTS的状态转变   */

#define AMHW_USART_MSR_DELTADSR   (1 << 1)  /**< \brief  设置输入DSR的状态转变   */

#define AMHW_USART_MSR_DELTARI    (1 << 2)  /**< \brief  设置输入RI由高到低的状态转变 */
 
#define AMHW_USART_MSR_DELTADCD   (1 << 3)  /**< \brief  设置输入DCD的状态转变   */
 
#define AMHW_USART_MSR_CTS        (1 << 4)  /**< \brief  设置输入CTS的状态   */

#define AMHW_USART_MSR_DSR        (1 << 5)  /**< \brief  设置输入DSR的状态   */

#define AMHW_USART_MSR_RI         (1 << 6)  /**< \brief  设置输入RI的状态    */

#define AMHW_USART_MSR_DCD        (1 << 7)  /**< \brief  设置输入DCD的状态   */

/** @} */

/**
 * \name 定义USART自动波特率配置
 * \anchor grp_amhw_usart_autobaud_cfg_flags
 * @{
 */                                                           
#define AMHW_USART_AUTOBAUD_START     (1 << 0) /**< \brief  自动匹配波特率开始   */
#define AMHW_USART_AUTOBAUD_STOP      (0 << 0) /**< \brief  自动匹配波特率结束   */

#define AMHW_USART_AUTOBAUD_MODE0     (0 << 1) /**< \brief  模式0   */

#define AMHW_USART_AUTOBAUD_MODE1     (1 << 1) /**< \brief  模式1   */

#define AMHW_USART_AUTOBAUD_RESTART   (1 << 2) /**< \brief  自动波特率重启  */

/** \brief  自动匹配波特率结束中断清除(仅能写)  */
#define AMHW_USART_ACR_ABEOINTCLR     (1 << 8)

/** \brief  自动匹配波特率超时中断清除(仅能写)  */
#define AMHW_USART_ACR_ABTOINTCLR     (1 << 9)

/** @} */     

/**
 * \name 定义USART  IrDA配置
 * \anchor grp_amhw_usart_icr_cfg_flags
 * @{
 */
#define AMHW_USART_ICR_IrDAEN      (1 << 0) /**< \brief 串口IrDA模式使能         */

#define AMHW_USART_ICR_IrDAInv     (1 << 1) /**< \brief 使能 IrDA 固定脉宽模式   */

#define AMHW_USART_ICR_FixPulseEn  (1 << 2) /**< \brief 配置IrDA模式脉宽使能     */


/* 设置 IrDA 脉宽(总线脉宽倍数) */
#define AMHW_USART_ICR_PD2     (0 << 3)   /**< \brief  2倍   */
#define AMHW_USART_ICR_PD4     (1 << 3)   /**< \brief  4倍   */
#define AMHW_USART_ICR_PD8     (2 << 3)   /**< \brief  8倍   */
#define AMHW_USART_ICR_PD16    (3 << 3)   /**< \brief  16倍   */
#define AMHW_USART_ICR_PD32    (4 << 3)   /**< \brief  32倍   */
#define AMHW_USART_ICR_PD64    (5 << 3)   /**< \brief  64倍   */
#define AMHW_USART_ICR_PD128   (6 << 3)   /**< \brief  128倍  */
#define AMHW_USART_ICR_PD256   (7 << 3)   /**< \brief  256倍  */

/** @} */

/**
 * \name  USART传输使能寄存器宏定义    
 * @{   
 */
#define AMHW_USART_TER_TXEN      (1 << 7)          /**< \brief 串口发送使能  */

/** @} */

/**
 * \brief 使能串口中断
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] int_flags  : 中断使能位， 参见
 *                        \ref grp_amhw_usart_irq_cfg_flags "Irq Configuration Flags"
 *
 * \return    无
 */
am_static_inline
void amhw_usart_int_enable (amhw_usart_t *p_hw_usart, uint32_t int_flags)
{
     p_hw_usart->ier |= int_flags;
}

/**
 * \brief 关闭串口中断
 *
 * \param[in] p_hw_usart  : 指向USART寄存器块的指针
 * \param[in] int_flags : 中断位， 参见
 *                        \ref grp_amhw_usart_irq_cfg_flags "Irq Configuration Flags"
 *
 * \return 无
 */
am_static_inline
void amhw_usart_int_disable (amhw_usart_t *p_hw_usart, uint32_t int_flags)
{
     p_hw_usart->ier &= ~int_flags;
}

/**
 * \brief 设置USART中断状态
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] int_flag   : 中断位，值为AMHW_USART_*(#AMHW_USART_IIR_INTSTATUS)
 *
 * \return 无
 */
am_static_inline
uint32_t amhw_usart_intstat_get (amhw_usart_t *p_hw_usart, uint32_t int_flag)
{
    return p_hw_usart->iir & int_flag;
}

/**
 * \brief 设置USART的FIFO
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] fifo_flags : FIFO标志位，值为AMHW_USART_*(#AMHW_USART_RX_TRILEVEL0)
 *
 * \return 无
 */
am_static_inline
void amhw_usart_fifo_set (amhw_usart_t *p_hw_usart, uint32_t fifo_flags)
{
    p_hw_usart->fcr = fifo_flags;
}

/**
 * \brief USART 配置
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] cfg_flags  : 配置值，值为AMHW_USART_*(#AMHW_USART_LCR_5BIT)
 *
 * \return 无
 */
am_static_inline
void amhw_usart_config (amhw_usart_t *p_hw_usart, uint32_t cfg_flags)
{
    p_hw_usart->lcr |= cfg_flags;
}

/**
 * \brief 使能 DLAB
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_usart_dlab_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->lcr |= AMHW_USART_DLAB_ENABLE;
}

/**
 * \brief 关闭 DLAB
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_usart_dlab_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->lcr &= ~AMHW_USART_DLAB_ENABLE;
}


/**
 * \brief 获取UART 调制解调器控制模式
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return USART控制模式
 * \note   只可获取UART1
 */
am_static_inline
uint32_t amhw_usart_mcr_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->mcr;
}

/**
 * \brief 设置UART 调制解调器控制模式
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] mcr_flags  : 配置值，参见
 *                          \ref grp_amhw_usart_mcr_cfg_flags "Control Mode Configuration"
 *
 * \return 无
 * \note   只可设置UART1
 */
am_static_inline
uint32_t amhw_usart_mcr_set (amhw_usart_t *p_hw_usart, uint32_t mcr_flags)
{
    return p_hw_usart->mcr = mcr_flags;
}

/**
 * \brief 获取USART线状态寄存器
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return USART状态
 */
am_static_inline
uint32_t amhw_usart_stat_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->lsr;
}

/**
 * \brief 获取USART调制解调器状态
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return UART调制解调器状态寄存器值
 * \note   该接口适用于UART1
 */
am_static_inline
uint32_t amhw_usart_msr_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->msr;
}

/**
 * \brief 设置USART自动波特率
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] autobaud_flags : 配置值，参见
 *                             \ref grp_amhw_usart_autobaud_cfg_flags "Autobaud Configuration "
 *
 * \return 无
 */
am_static_inline
uint32_t amhw_usart_autobaud_set (amhw_usart_t *p_hw_usart, uint32_t autobaud_flags)
{
    return p_hw_usart->acr = autobaud_flags;
}

/**
 * \brief 设置USART4 irda模式
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] irda_flags : 配置值，参见
 *                         \ref grp_amhw_usart_icr_cfg_flags "IrDA Configuration"
 *
 * \return 无
 */
am_static_inline
uint32_t amhw_usart_irda_set (amhw_usart_t *p_hw_usart, uint32_t irda_flags)
{
    return p_hw_usart->icr = irda_flags;
}

/**
 * \brief 使能USART 发送
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return 无
 * \note   默认使能
 */
am_static_inline
void amhw_usart_tx_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->ter |= AMHW_USART_TER_TXEN;
}
  
/**
 * \brief 关闭USART 发送
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_usart_tx_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->ter &= ~AMHW_USART_TER_TXEN;
}

/**
 * \brief 使能USART4 发送
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_usart4_tx_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->u4ter |= AMHW_USART_TER_TXEN;
}

/**
 * \brief 关闭USART4 发送
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_usart4_tx_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->u4ter &= ~AMHW_USART_TER_TXEN;
}

/**
 * \brief USART4 过采样寄存器设置
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] value      : 设置到过采样寄存器的值
 * \return 无
 */
am_static_inline
void amhw_usart_osr_set (amhw_usart_t *p_hw_usart, uint32_t value)
{
    p_hw_usart->osr = value;
}

/**
 * \brief USART4 过采样寄存器值获取
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \return 过采样寄存器值
 */
am_static_inline
uint32_t amhw_usart_osr_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->osr & 0x7FFF;
}


/**
 * \name 智能卡接口控制位定义
 * \anchor grp_amhw_usart_sci_cfg_flags
 * @{
 */
#define AMHW_USART_SCI_ENABLE          (0 << 0)   /**< \brief  智能卡接口禁能   */
#define AMHW_USART_SCI_DISABLE         (1 << 0)   /**< \brief  使能异步半双工智能卡接口   */

#define AMHW_USART_SCI_NACKDIS_ENABLE  (0 << 1)   /**< \brief  使能NACK响应   */
#define AMHW_USART_SCI_NACKDIS_DISABLE (1 << 1)   /**< \brief  禁止NACK响应   */

#define AMHW_USART_SCI_PROTESEL_0      (0 << 1)    /**< \brief  T=0   */
#define AMHW_USART_SCI_PROTESEL_1      (1 << 1)    /**< \brief  T=1   */

/** \brief UART4尝试重新发送的最大数量 val  */
#define AMHW_USART_SCI_TXRETRY_VALUE(val)   ((val) << 5)

/** \brief 位时间数   */
#define AMHW_USART_SCI_XTRAGUARD_VALUE(val) ((val) << 8)

/** @} */

/**
 * \brief USART4 智能卡接口配置
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] flag       : 配置参数，参见 \ref grp_amhw_usart_sci_cfg_flags "SCI Configuration Flags"
 *
 * \return 无
 */
am_static_inline
void amhw_usart_sci_set (amhw_usart_t *p_hw_usart, uint32_t flag)
{
    p_hw_usart->sci_ctrl = flag;
}

/**
 * \name 同步模式控制位定义
 * \anchor grp_amhw_usart_sync_ctrl_flags
 * @{
 */
#define AMHW_USART_SYNC_ENABLE          (1 << 0)    /**< \brief  同步模式使能   */
#define AMHW_USART_SYNC_DISABLE         (0 << 0)    /**< \brief  同步模式禁能  */

#define AMHW_USART_SYNC_CSRC_SLAVE      (0 << 1)    /**< \brief  同步从机模式   */
#define AMHW_USART_SYNC_CSRC_MASTER     (1 << 1)    /**< \brief  同步主机模式   */

#define AMHW_USART_SYNC_FES_ENABLE      (1 << 2)    /**< \brief  下降沿采样   */
#define AMHW_USART_SYNC_FES_DISABLE     (0 << 2)    /**< \brief  上升沿采样   */

#define AMHW_USART_SYNC_TSBYPASS_ENABLE  (1 << 3)   /**< \brief 忽略发送同步   */
#define AMHW_USART_SYNC_TSBYPASS_DISABLE (0 << 3)   /**< \brief 不忽略发送同步  */

#define AMHW_USART_SYNC_CSC_ENABLE  (1 << 4) /**< \brief 连续主机时钟使能   */
#define AMHW_USART_SYNC_CSC_DISABLE (0 << 4) /**< \brief 连续主机时钟禁能   */

#define AMHW_USART_SYNC_SSS_DISABLE (1 << 5) /**< \brief 不发送起始/停止位  */
#define AMHW_USART_SYNC_SSS_EANBLE  (0 << 5) /**< \brief 在其他模式发送起始/停止位  */

/** \brief CSCEN位在软件的控制之下  */
#define AMHW_USART_SYNC_CCLR_DISABLE (0 << 6)

/** \brief 硬件在接收到每个字符后清零CECEN     */
#define AMHW_USART_SYNC_CCLR_EANBLE  (1 << 6)
/** @} */

/**
 * \brief USART4 同步模式控制寄存器设置
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] flag       : 配置参数，参见
 *                         \ref grp_amhw_usart_sync_ctrl_flags "Sync Configuration Flags"
 *
 * \return 无
 */
am_static_inline
void amhw_usart_sync_set (amhw_usart_t *p_hw_usart, uint32_t flag)
{
    p_hw_usart->syncctrl = flag;
}

/**
 * \brief USART4 同步模式使能
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_usart_sync_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->syncctrl |= AMHW_USART_SYNC_ENABLE;
}

/**
 * \brief USART4 同步模式禁能
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_usart_sync_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->syncctrl &= ~AMHW_USART_SYNC_ENABLE;
}

/**
 * \name RS485控制位定义
 * \anchor grp_amhw_usart_rs485_ctrl_flags
 * @{
 */
#define AMHW_USART_RS485_NMM_ENABLE    (1 << 0)   /**< \brief 普通多点模式使能   */
#define AMHW_USART_RS485_NMM_DISABLE   (0 << 0)   /**< \brief 普通多点模式禁能  */

#define AMHW_USART_RS485_RX_DISABLE    (1 << 1)   /**< \brief 禁能接收器  */
#define AMHW_USART_RS485_RX_ENABLE     (0 << 1)   /**< \brief 使能接收器   */

#define AMHW_USART_RS485_AAD_ENABLE    (1 << 2)   /**< \brief 自动地址检测使能   */
#define AMHW_USART_RS485_AAD_DISABLE   (0 << 2)   /**< \brief 自动地址检测禁能   */

#define AMHW_USART_RS485_SEL_RTS   (0 << 3)       /**< \brief 管脚RTS用于方向控制   */
#define AMHW_USART_RS485_SEL_DTR   (1 << 3)       /**< \brief 管脚DTR用于方向控制   */

#define AMHW_USART_RS485_DCTRL_ENABLE    (1 << 4)  /**< \brief 自动方向控制使能   */
#define AMHW_USART_RS485_DCTRL_DISABLE   (0 << 4)  /**< \brief 自动方向控制禁能   */

/** \brief 发送时，方向控制管脚被驱动为逻辑1 */
#define AMHW_USART_RS485_OINV1    (1 << 5)
/** \brief 发送时，方向控制管脚被驱动为逻辑1 */
#define AMHW_USART_RS485_OINV0   (0 << 5)

/** @} */

/**
 * \brief RS485控制寄存器设置
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] flag       : 配置参数，参见
 *                         \ref grp_amhw_usart_rs485_ctrl_flags
 *                              "RS485 Configuration Flags"
 *
 * \return 无
 */
am_static_inline
void amhw_usart_rs485_ctrl_set (amhw_usart_t *p_hw_usart, uint32_t flag)
{
    p_hw_usart->rs485ctrl = flag;
}

/**
 * \brief 设置RS485地址匹配值
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] val        : 地址匹配值，0~255
 *
 * \return 无
 */
am_static_inline
void amhw_usart_rs485_adrmatch_set (amhw_usart_t *p_hw_usart, uint32_t val)
{
    p_hw_usart->adrmatch = val;
}

/**
 * \brief 获取RS485地址匹配值
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return    RS485地址匹配值
 */
am_static_inline
uint32_t amhw_usart_rs485_adrmatch_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->adrmatch & 0xFF;
}

/**
 * \brief 设置RS485方向控制延时值
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] dly        : 方向控制延时值，0~255
 *
 * \return 无
 */
am_static_inline
void amhw_usart_rs485_dly_set (amhw_usart_t *p_hw_usart, uint32_t dly)
{
    p_hw_usart->rs485dly = dly;
}

/**
 * \brief 获取RS485地址匹配值
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return    方向控制延时值
 */
am_static_inline
uint32_t amhw_usart_rs485_dly_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->rs485dly & 0xFF;
}

/**
 * \name UART FIFO当前水平掩码
 * @{
 */
#define AMHW_UART_RXFIFOLVL_MASK    0xF         /**< \brief 接收FIFO的当前水平掩码  */
#define AMHW_UART_TXFIFOLVL_MASK   (0xF << 8)   /**< \brief 发送FIFO的当前水平掩码  */

/** @} */

/**
 * \brief 获取UART接收FIFO的当前水平
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return  接收FIFO的当前水平,值为0~0xF,0为FIFO空，0xF为FIFO满
 *
 * \note   : UART4不可使用
 */
am_static_inline
uint8_t amhw_usart_rxfifo_level_get (amhw_usart_t *p_hw_usart)
{
    return (uint8_t)(p_hw_usart->fifolvl & AMHW_UART_RXFIFOLVL_MASK);
}

/**
 * \brief 获取UART发送FIFO的当前水平
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 *
 * \return  发送FIFO的当前水平,值为0~0xF,0为FIFO空，0xF为FIFO满
 *
 * \note   : UART4不可使用
 */
am_static_inline
uint8_t amhw_usart_txfifo_level_get (amhw_usart_t *p_hw_usart)
{
    return (uint8_t)((p_hw_usart->fifolvl & AMHW_UART_TXFIFOLVL_MASK) >> 8);
}

/**
 * \brief  USART 波特率设置
 *
 * \param[in] p_hw_usart : 指向USART寄存器块的指针
 * \param[in] u_clk      : USART 输入时钟
 * \param[in] baudrate   : 波特率设置值
 *
 * \return  >0           : 真实波特率值
 *          -AM_EINVAL   : 设置失败，参数无效
 */
int amhw_usart_baudrate_set (amhw_usart_t *p_hw_usart,
                             uint32_t      u_clk,
                             uint32_t      baudrate);

/*
 * \brief 匿名结构体段的结束
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
