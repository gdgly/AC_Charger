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
 * \brief DMA硬件操作接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-06-04  cod, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_DMA_H
#define __AMHW_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 
#include "am_common.h"
#include "amhw_syscon.h"	

/**
 * \addtogroup amhw_if_dma
 * \copydoc amhw_dma.h
 * @{
 */

/** \brief DMA 通道数量 */
#define AMHW_DMA_CHAN_CNT           8
	
/**
 * \name DMA 通道编号
 * @{
 */
#define DMA_CHAN_0                0               /**< \brief DMA通道0  */
#define DMA_CHAN_1                1               /**< \brief DMA通道1  */
#define DMA_CHAN_2                2               /**< \brief DMA通道2  */
#define DMA_CHAN_3                3               /**< \brief DMA通道3  */
#define DMA_CHAN_4                4               /**< \brief DMA通道4  */
#define DMA_CHAN_5                5               /**< \brief DMA通道5  */
#define DMA_CHAN_6                6               /**< \brief DMA通道6  */
#define DMA_CHAN_7                7               /**< \brief DMA通道7  */

/** @} */

/**
 * \brief DMA 通道寄存器结构体
 */
typedef struct amhw_dma_chan {
    __IO uint32_t srcaddr;          /**< \brief DMA 源地址寄存器   */
    __IO uint32_t destaddr;         /**< \brief DMA 目标地址寄存器 */
    __IO uint32_t lli;              /**< \brief DMA 链表项寄存器   */
    __IO uint32_t control;          /**< \brief 控制寄存器         */
    __IO uint32_t config;           /**< \brief 配置寄存器         */
    __IO uint32_t reserved[3];      /**< \brief 保留               */
} amhw_dma_chan_t;

/**
 * \brief DMA 控制器寄存器块结构体 
 */
typedef struct amhw_dma {
    __I  uint32_t intstat;          /**< \brief DMA中断状态寄存器              */
    __I  uint32_t inttcstat;        /**< \brief DMA中断终端计数请求状态寄存器  */
    __O  uint32_t inttcclear;       /**< \brief DMA中断终端计数请求清除寄存器  */
    __I  uint32_t interrstat;       /**< \brief DMA中断错误状态寄存器          */
    __O  uint32_t interrclear;      /**< \brief DMA中断错误清除寄存器          */
    __I  uint32_t rawinttcstat;     /**< \brief DMA原始中断终端计数状态寄存器  */
    __I  uint32_t rawinterrstat;    /**< \brief DMA原始错误中断状态寄存器      */
    __I  uint32_t enbldchns;        /**< \brief DMA使能通道寄存器                    */
    __IO uint32_t softbreq;         /**< \brief DMA软件突发请求寄存器          */
    __IO uint32_t softsreq;         /**< \brief DMA软件单个请求寄存器          */
    __IO uint32_t softlbreq;        /**< \brief DMA软件最后一个突发请求寄存器  */
    __IO uint32_t softlsreq;        /**< \brief DMA软件最后一个单个请求寄存器  */
    __IO uint32_t config;           /**< \brief DMA配置寄存器                  */
    __IO uint32_t sync;             /**< \brief DMA同步寄存器                  */
    __IO uint32_t reserved[50];     /**< \brief 保留                           */
    amhw_dma_chan_t chan[AMHW_DMA_CHAN_CNT];   /**< \brief DMA通道寄存器       */
} amhw_dma_t;

/**
 * \brief DMA 链表项
 * \attention 链表项地址必须是16字节对齐
 */
typedef struct amhw_dma_lli {
    volatile uint32_t srcaddr;      /**< \brief 源地址       */
    volatile uint32_t dstaddr;      /**< \brief 目标地址     */
    volatile uint32_t next;         /**< \brief 下一个链表项 */
    volatile uint32_t control;      /**< \brief 控制寄存器	 */
} amhw_dma_lli_t;

/**
 * \brief AHB主机字节顺序配置模式定义
 */
typedef enum amhw_dma_endian_mode {
    AMHW_DMA_LITTLE_ENDIAN ,       /**< \brief 小端模式      */
    AMHW_DMA_BIG_ENDIAN	           /**< \brief 大端模式      */
} amhw_dma_endian_mode_t;

/**
 * \brief 软件请求传输信号
 */
typedef enum amhw_dma_req_sem {
    AMHW_DMA_SOFT_BREQ,	         /**< \brief DMA软件突发请求          */
    AMHW_DMA_SOFT_SREQ,	         /**< \brief DMA软件单次请求          */
    AMHW_DMA_SOFT_LBREQ,         /**< \brief DMA软件最后一次突发请求  */
    AMHW_DMA_SOFT_LSREQ	         /**< \brief DMA软件最后一次单次请求  */
} amhw_dma_req_sem_t;

/**
 * \name 外设传输请求编号
 * \anchor grp_amhw_dma_chan_req_line
 * @{
 */
#define AMHW_DMA_CHAN_REQ_NONE_MAT00       (0UL)    /**< \brief 无外设或T0 匹配0 */
#define AMHW_DMA_CHAN_REQ_SDCARD_MAT01     (1UL)    /**< \brief SD_CARD或T0匹配1 */
#define AMHW_DMA_CHAN_REQ_SSP0TX_MAT10     (2UL)    /**< \brief SSP0 TX或T1匹配0 */
#define AMHW_DMA_CHAN_REQ_SSP0RX_MAT11     (3UL)    /**< \brief SSP0 RX或T1匹配1 */
#define AMHW_DMA_CHAN_REQ_SSP1TX_MAT20     (4UL)    /**< \brief SSP1 TX或T2匹配0 */
#define AMHW_DMA_CHAN_REQ_SSP1RX_MAT21     (5UL)    /**< \brief SSP1 RX或T2匹配1 */
#define AMHW_DMA_CHAN_REQ_SSP2TX_I2SCH0    (6UL)    /**< \brief SSP2 TX或I2S CH0 */
#define AMHW_DMA_CHAN_REQ_SSP2RX_I2SCH1    (7UL)    /**< \brief SSP2 RX或I2S CH1 */
#define AMHW_DMA_CHAN_REQ_ADC              (8UL)    /**< \brief ADC      */
#define AMHW_DMA_CHAN_REQ_DAC              (9UL)    /**< \brief DAC      */
#define AMHW_DMA_CHAN_REQ_UART0TX_UART3TX  (10UL)   /**< \brief UART0 TX或UART3 TX */
#define AMHW_DMA_CHAN_REQ_UART0RX_UART3RX  (11UL)   /**< \brief UART0 RX或UART3 RX */
#define AMHW_DMA_CHAN_REQ_UART1TX_UART4TX  (12UL)   /**< \brief UART1 TX或UART4 TX */
#define AMHW_DMA_CHAN_REQ_UART1RX_UART4RX  (13UL)   /**< \brief UART1 RX或UART4 RX */
#define AMHW_DMA_CHAN_REQ_UART2TX_MAT30    (14UL)   /**< \brief UART2 TX或T3匹配0*/
#define AMHW_DMA_CHAN_REQ_UART2RX_MAT31    (15UL)   /**< \brief UART2 TX或T3匹配1*/

/** @} */

/**
 * \brief DMA外设请求选择，设置为0
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \param[in] line        : DMA外设连接请求编号,参见
 *                          \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \return    无
 */
am_static_inline
void amhw_dma_req_select0 (amhw_syscon_t *p_hw_syscon,
                           uint8_t        line)
{
    p_hw_syscon->dmareqsel &= ~AM_BIT(line);
}

/**
 * \brief DMA外设请求选择，设置为1
 * \param[in] p_hw_syscon : 指向系统控制寄存器块的指针
 * \param[in] line        : DMA外设连接请求编号,参见
 *                          \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \return    无
 */
am_static_inline
void amhw_dma_req_select1 (amhw_syscon_t *p_hw_syscon,
                           uint8_t        line)
{
    p_hw_syscon->dmareqsel |= AM_BIT(line);
}

/**
 * \brief 使能DMA控制器
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_dma_enable (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->config |= AM_BIT(0);
}

/**
 * \brief 禁能DMA控制器
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_dma_disable (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->config &= ~AM_BIT(0);
}

/**
 * \brief AHB主机字节顺序大端模式
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_dma_big_endian (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->config |= AM_BIT(1);
}

/**
 * \brief AHB主机字节顺序小端模式
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_dma_little_endian (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->config &= ~AM_BIT(1);
}

/**
 * \brief 获取DMA中断状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    中断状态。
 */
am_static_inline
uint32_t amhw_dma_int_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intstat;
}

/**
 * \brief 获取DMA中断终端计数请求状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    DMA中断终端计数请求状态
 */
am_static_inline
uint32_t amhw_dma_inttc_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->inttcstat;
}

/**
 * \brief 通过掩码清除终端计数中断标志
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] mask     : bit[7:0] 对应DMA通道 n, 该被清除为必须与 NTA 相对应
 * \return    无
 */
am_static_inline
void amhw_dma_inttc_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->inttcclear = mask ;
}

/**
 * \brief 清除DMA指定通道中断终端计数请求状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道号, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 */
am_static_inline
void amhw_dma_chan_inttc_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->inttcclear |= AM_BIT(chan) ;
}

/**
 * \brief 获取DMA中断错误状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    DMA中断错误状态
 */
am_static_inline
uint32_t amhw_dma_interr_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->interrstat;
}

/**
 * \brief 通过掩码清除中断错误标志
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] mask     : bit[7:0] 对应DMA通道 n, 该被清除为必须与 NTA 相对应
 * \return    无
 */
am_static_inline
void amhw_dma_interr_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->interrclear = mask ;
}

/**
 * \brief 清除DMA中断错误状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道号, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 */
am_static_inline
void amhw_dma_chan_interr_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->interrclear |= AM_BIT(chan) ;
}

/**
 * \brief 获取DMA原始中断终端计数状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    DMA原始中断终端计数状态
 */
am_static_inline
uint32_t amhw_dma_rawinttc_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->rawinttcstat;
}

/**
 * \brief 获取DMA原始错误中断状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    DMA原始错误中断状态
 */
am_static_inline
uint32_t amhw_dma_rawinterr_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->rawinterrstat;
}

/**
 * \brief 获取DMA使能通道状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    DMA使能通道状态
 */
am_static_inline
uint32_t amhw_dma_enabled_channels_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->enbldchns;
}

/**
 * \brief 使能软件产生指定源的DMA突发请求
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line     : DMA请求线或外设功能
 * \return    无
 */
am_static_inline
void amhw_dma_softb_req_enable (amhw_dma_t   *p_hw_dma, 
                                unsigned int line)
{
    p_hw_dma->softbreq |= AM_BIT(line);
}

/**
 * \brief 指定源是否在正在请求DMA突发传输
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line     : DMA外设请求编号，参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \retval  非0        : 指定源line正在请求DMA突发传输
 * \retval  0          : 不在请求
 */
am_static_inline
uint32_t amhw_dma_softb_req_active (amhw_dma_t  *p_hw_dma, 
                                    unsigned int line)
{
    return p_hw_dma->softbreq & AM_BIT(line);
}

/**
 * \brief 使能软件产生指定源的DMA单次请求
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line 	   : DMA外设请求编号,参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \return    无
 */
am_static_inline
void amhw_dma_softs_req_enable (amhw_dma_t   *p_hw_dma, 
                                unsigned int line)
{
    p_hw_dma->softsreq |= AM_BIT(line);
}

/**
 * \brief 指定源是否在正在请求DMA单次传输
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line     : DMA外设请求编号，参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \retval    非0      : 指定源line正在请求DMA单次传输
 * \retval    0        : 不在请求
 */
am_static_inline
uint32_t amhw_dma_softs_req_active (amhw_dma_t  *p_hw_dma, 
	                                unsigned int line)
{
    return p_hw_dma->softsreq & AM_BIT(line);
}

/**
 * \brief 使能软件产生指定源的DMA最后一个突发请求
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line     : DMA外设请求编号，参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \return    无
 */
am_static_inline
void amhw_dma_softlb_req_enable (amhw_dma_t  *p_hw_dma, 
                                 unsigned int line)
{
    p_hw_dma->softlbreq |= AM_BIT(line);
}

/**
 * \brief 指定源是否在正在请求DMA突发传输
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line     : DMA外设请求编号，参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \retval    非0      : 指定源line正在请求最后一个DMA突发传输
 * \retval    0        : 不在请求
 */
am_static_inline
uint32_t amhw_dma_softlb_req_active (amhw_dma_t  *p_hw_dma, 
                                     unsigned int line)
{
    return p_hw_dma->softlbreq & AM_BIT(line);
}

/**
 * \brief 使能软件产生指定源的DMA最后一个单次请求
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line     : DMA外设请求编号，参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 *
 * \return    无
 */
am_static_inline
void amhw_dma_softls_req_enable (amhw_dma_t  *p_hw_dma, 
                                 unsigned int line)
{
    p_hw_dma->softlsreq |= AM_BIT(line);
}

/**
 * \brief 指定源是否在正在请求最后一个DMA单次传输
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line     : DMA外设请求编号，参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \retval  非0        : 指定源line正在请求最后一个DMA单次传输
 * \retval  0          : 不在请求
 */
am_static_inline
uint32_t amhw_dma_softls_req_active (amhw_dma_t  *p_hw_dma, 
                                     unsigned int line)
{
    return p_hw_dma->softlsreq & AM_BIT(line);
}

/**
 * \brief 禁能DMA请求信号的同步逻辑
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line 	   : DMA外设请求编号，参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 */
am_static_inline
void amhw_dma_sync_disable (amhw_dma_t  *p_hw_dma,
                            unsigned int line)
{
    p_hw_dma->sync |= AM_BIT(line);
}

/**
 * \brief 使能DMA请求信号的同步逻辑
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] line 	   : DMA外设请求编号，参见
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 */
am_static_inline
void amhw_dma_sync_enable (amhw_dma_t  *p_hw_dma,
                           unsigned int line)
{
    p_hw_dma->sync &= ~AM_BIT(line);
}


/**
 * \brief 配置当前要传输的源地址
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] addr     : 源地址                    
 * \return    无
 */
am_static_inline
void amhw_dma_chan_srcaddr_set (amhw_dma_t  *p_hw_dma, 
                                unsigned int chan, 
                                uint32_t     addr)
{
    p_hw_dma->chan[chan].srcaddr = addr;
}

/**
 * \brief 配置当前要传输的目标地址
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] addr     : 源地址                    
 * \return    无
 */
am_static_inline
void amhw_dma_chan_destaddr_set (amhw_dma_t  *p_hw_dma, 
                                 unsigned int chan, 
                                 uint32_t     addr)
{
    p_hw_dma->chan[chan].destaddr = addr;
}

/**
 * \brief 配置链表项
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] lli      : 下个链表项地址        
 * \return    无
 */
am_static_inline
void amhw_dma_chan_lli_set (amhw_dma_t  *p_hw_dma, 
                            unsigned int chan, 
                            uint32_t     lli)
{
    p_hw_dma->chan[chan].lli = lli;
}

/**
 * \name 定义通道控制信息
 * \anchor grp_amhw_dma_chan_control_flags
 * @{
 */

#define AMHW_DMA_CCONTROL_SBSIZE_1    AM_SBF(0, 12)    /**< \brief  源突发传输数据量 SIZE = 1   */
#define AMHW_DMA_CCONTROL_SBSIZE_4    AM_SBF(1, 12)    /**< \brief  源突发传输数据量 SIZE = 4   */
#define AMHW_DMA_CCONTROL_SBSIZE_8 	  AM_SBF(2, 12)    /**< \brief  源突发传输数据量 SIZE = 8   */
#define AMHW_DMA_CCONTROL_SBSIZE_16   AM_SBF(3, 12)    /**< \brief  源突发传输数据量 SIZE = 16  */
#define AMHW_DMA_CCONTROL_SBSIZE_32   AM_SBF(4, 12)    /**< \brief  源突发传输数据量 SIZE = 32  */
#define AMHW_DMA_CCONTROL_SBSIZE_64   AM_SBF(5, 12)    /**< \brief  源突发传输数据量 SIZE = 64  */
#define AMHW_DMA_CCONTROL_SBSIZE_128  AM_SBF(6, 12)    /**< \brief  源突发传输数据量 SIZE = 128 */
#define AMHW_DMA_CCONTROL_SBSIZE_256  AM_SBF(7, 12)    /**< \brief  源突发传输数据量 SIZE = 256 */

#define AMHW_DMA_CCONTROL_DBSIZE_1     AM_SBF(0, 15)   /**< \brief  目标突发传输数据量 SIZE = 1   */
#define AMHW_DMA_CCONTROL_DBSIZE_4 	   AM_SBF(1, 15)   /**< \brief  目标突发传输数据量 SIZE = 4   */
#define AMHW_DMA_CCONTROL_DBSIZE_8 	   AM_SBF(2, 15)   /**< \brief  目标突发传输数据量 SIZE = 8   */
#define AMHW_DMA_CCONTROL_DBSIZE_16    AM_SBF(3, 15)   /**< \brief  目标突发传输数据量 SIZE = 16  */
#define AMHW_DMA_CCONTROL_DBSIZE_32    AM_SBF(4, 15)   /**< \brief  目标突发传输数据量 SIZE = 32  */
#define AMHW_DMA_CCONTROL_DBSIZE_64    AM_SBF(5, 15)   /**< \brief  目标突发传输数据量 SIZE = 64  */
#define AMHW_DMA_CCONTROL_DBSIZE_128   AM_SBF(6, 15)   /**< \brief  目标突发传输数据量 SIZE = 128 */
#define AMHW_DMA_CCONTROL_DBSIZE_256   AM_SBF(7, 15)   /**< \brief  目标突发传输数据量 SIZE = 256 */

#define AMHW_DMA_CCONTROL_SWIDTH_8BIT      AM_SBF(0, 18)   	/**< \brief  8-bit 数据宽度  */
#define AMHW_DMA_CCONTROL_SWIDTH_16BIT     AM_SBF(1, 18)   	/**< \brief 16-bit 数据宽度  */
#define AMHW_DMA_CCONTROL_SWIDTH_32BIT     AM_SBF(2, 18)   	/**< \brief 32-bit 数据宽度  */

#define AMHW_DMA_CCONTROL_DWIDTH_8BIT      AM_SBF(0, 21)   	/**< \brief  8-bit 数据宽度 */
#define AMHW_DMA_CCONTROL_DWIDTH_16BIT     AM_SBF(1, 21)   	/**< \brief 16-bit 数据宽度  */
#define AMHW_DMA_CCONTROL_DWIDTH_32BIT     AM_SBF(2, 21)  	/**< \brief 32-bit 数据宽度  */

#define AMHW_DMA_CCONTROL_SI_DISABLE    0                 /**< \brief 源地址不增加    */
#define AMHW_DMA_CCONTROL_SI_ENABLE     AM_SBF(1, 26) 	  /**< \brief 源地址增加      */

#define AMHW_DMA_CCONTROL_DI_DISABLE    0                 /**< \brief 目标地址不增加  */
#define AMHW_DMA_CCONTROL_DI_ENABLE     AM_SBF(1, 27)     /**< \brief 目标地址增加    */

#define AMHW_DMA_CCONTROL_PROT1_DISABLE   0                /**< \brief 用户模式下    */
#define AMHW_DMA_CCONTROL_PROT1_ENABLE    AM_SBF(1, 28)    /**< \brief 特权模式下    */

#define AMHW_DMA_CCONTROL_PROT2_DISABLE   0                /**< \brief 不可缓冲  */
#define AMHW_DMA_CCONTROL_PROT2_ENABLE    AM_SBF(1, 29)    /**< \brief 可缓冲    */

#define AMHW_DMA_CCONTROL_PROT3_DISABLE   0                 /**< \brief 不可缓存  */
#define AMHW_DMA_CCONTROL_PROT3_ENABLE    AM_SBF(1, 30)   	/**< \brief 可缓存    */

#define AMHW_DMA_CCONTROL_ITC_DISABLE   0                   /**< \brief 终端计数中断失能  */
#define AMHW_DMA_CCONTROL_ITC_ENABLE    AM_SBF(1ul, 31)     /**< \brief 终端计数中断使能  */

/** @} */

#define AMHW_DMA_CCONTROL_TRANS_SIZE(size) (0x0fff & (size)) /**< \brief  传输数据大小   */

/**
 * \brief DMA 通道控制信息配置
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] flags    : 配置参数，参见
 *                       \ref grp_amhw_dma_chan_control_flags 
 * \return    无
 */
am_static_inline
void amhw_dma_chan_control_set (amhw_dma_t  *p_hw_dma, 
                                unsigned int chan, 
                                uint32_t     flags)
{
    p_hw_dma->chan[chan].control = flags;
}

/**
 * \brief 使能DMA指定通道终端计数中断
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan 	   : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 */
am_static_inline
void amhw_dma_chan_inttc_enable (amhw_dma_t  *p_hw_dma,
                                 unsigned int chan)
{
    p_hw_dma->chan[chan].control |= AM_BIT(31);
}

/**
 * \brief 失能DMA指定通道终端计数中断
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 */
am_static_inline
void amhw_dma_chan_inttc_disable (amhw_dma_t  *p_hw_dma,
                                  unsigned int chan)
{
    p_hw_dma->chan[chan].control &= ~AM_BIT(31);
}


/**
 * \name 定义通道配置参数
 * \anchor grp_amhw_dma_chan_config_flags
 * @{
 */

#define AMHW_DMA_CCONFIG_CHAN_ENABLE   AM_SBF(1, 0)  /**< \brief DMA通道使能     */
/**
 * \brief DMA传输源外设,val值为参见
 *         \ref grp_amhw_dma_chan_req_line "Channel Connect Request"
 */
#define AMHW_DMA_CCONFIG_SRCPER(val)    AM_SBF(((val) & 0x1F), 1)

/**
 * \brief DMA传输源外设,val值为参见
 *         \ref grp_amhw_dma_chan_req_line "Channel Connect Request"
 */
#define AMHW_DMA_CCONFIG_DESPER(val)   AM_SBF(((val) & 0x1F), 6)

/** \brief 存储器到存储器  */
#define AMHW_DMA_CCONFIG_TRANTYPE_M2M	    AM_SBF(0, 11)
/** \brief 存储器到外设     */
#define AMHW_DMA_CCONFIG_TRANTYPE_M2P       AM_SBF(1, 11)
/** \brief 外设到存储器     */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2M       AM_SBF(2, 11)
/** \brief 源外设到目标外设 */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2P       AM_SBF(3, 11)
/** \brief 存储器到存储器(目标外设控制) */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2P_DEST  AM_SBF(4, 11)
/** \brief 存储器到外设 (目标外设控制) */
#define AMHW_DMA_CCONFIG_TRANTYPE_M2P_DEST  AM_SBF(5, 11)
/** \brief 外设到存储器(源外设控制)   */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2M_SRC   AM_SBF(6, 11)
/** \brief 源外设到目标外设 (源外设控制) */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2P_SRC   AM_SBF(7, 11)

#define AMHW_DMA_CCONFIG_IE_VALID      AM_SBF(1, 14)   /**< \brief 中断错误不屏蔽 	*/
#define AMHW_DMA_CCONFIG_IE_INVALID    0	           /**< \brief 中断错误屏蔽    */

#define AMHW_DMA_CCONFIG_ITC_VALID	   AM_SBF(1, 15)   /**< \brief 中断错误不屏蔽  */
#define AMHW_DMA_CCONFIG_ITC_INVALID   0               /**< \brief 中断错误屏蔽    */

#define AMHW_DMA_CCONFIG_TRANS_LOCK    AM_SBF(1, 16)   /**< \brief 锁定传输     */
#define AMHW_DMA_CCONFIG_TRANS_UNLOCK  0               /**< \brief 传输不锁定   */

#define AMHW_DMA_CCONFIG_HALT          AM_SBF(1, 18)   /**< \brief 忽略后面源请求     */

#define AMHW_DMA_CCONFIG_REQ_ENABLE    0               /**< \brief  DMA传输请求使能   */
/** @} */

/**
 * \brief DMA 通道配置
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] flags    : 配置参数，参见
 *                       \ref grp_amhw_dma_chan_config_flags "Channel Configuration Flags"
 * \return    无
 */
am_static_inline
void amhw_dma_chan_config_set (amhw_dma_t  *p_hw_dma, 
                               unsigned int chan, 
                               uint32_t     flags)
{
    p_hw_dma->chan[chan].config = flags;
}

/**
 * \brief 使能DMA指定通道
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 */
am_static_inline
void amhw_dma_chan_enable (amhw_dma_t  *p_hw_dma,
                           unsigned int chan)
{
    p_hw_dma->chan[chan].config |= AM_BIT(0);
}

/**
 * \brief 失能DMA指定通道
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 *
 *
 */
am_static_inline
void amhw_dma_chan_disable (amhw_dma_t  *p_hw_dma,
                            unsigned int chan)
{
    p_hw_dma->chan[chan].config &= ~AM_BIT(0);
}

/**
 * \brief 屏蔽指定通道中断错误
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 */
am_static_inline
void amhw_dma_chan_interr_mask (amhw_dma_t  *p_hw_dma,
                                unsigned int chan)
{
    p_hw_dma->chan[chan].config &= ~AM_BIT(14);
}

/**
 * \brief 屏蔽指定通道终端计数中断
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 */
am_static_inline
void amhw_dma_chan_inttc_mask (amhw_dma_t  *p_hw_dma,
                               unsigned int chan)
{
    p_hw_dma->chan[chan].config &= ~AM_BIT(15);
}

/**
 * \brief 锁定指定通道传输
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 */
am_static_inline
void amhw_dma_chan_lock_trans (amhw_dma_t  *p_hw_dma,
                               unsigned int chan)
{
    p_hw_dma->chan[chan].config |= AM_BIT(16);
}

/**
 * \brief 指定通道的FIFO是否有数据
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \retval    非0      : 通道的FIFO中有数据
 * \retval    0        : 通道的FIFO没有数据
 */
am_static_inline
uint32_t amhw_dma_chan_fifo_active (amhw_dma_t  *p_hw_dma, 
                                    unsigned int chan)
{
    return p_hw_dma->chan[chan].config & AM_BIT(17);
}

/**
 * \brief 忽略指定通道DMA请求
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan 	   : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 */
am_static_inline
void amhw_dma_chan_req_ignore (amhw_dma_t  *p_hw_dma, 
                               unsigned int chan)
{
    p_hw_dma->chan[chan].config |= AM_BIT(18);
}

/**
 * \brief 使能指定通道DMA请求
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \return    无
 */
am_static_inline
void amhw_dma_chan_req_enable (amhw_dma_t  *p_hw_dma, 
                               unsigned int chan)
{
    p_hw_dma->chan[chan].config &= ~AM_BIT(18);
}

/**
 * @} amhw_if_dma
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_DMA_H */

/* end of file */

