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
 * \brief DMA驱动及服务接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-06-04  cod, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_DMA_H
#define __AMDR_DMA_H
 
 
#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_dma.h"
	
/**
 * \addtogroup amdr_if_dma
 * \copydoc amdr_dma.h
 * @{
 */

	
/**
 * \name 通道传输中断标志 
 * \anchor amdr_dma_chan_cfg_flags
 * @{
 */
	
#define AMDR_DMA_INTTC         0     /**< \brief 终端计数中断标志   */
#define AMDR_DMA_INTERR        1     /**< \brief 错误中断标志       */

/** @} */	

/**
 * \name DMA 通道连接请求编号
 * \anchor grp_dma_chan_conn_req_num
 * @{
 */
#define AMDR_DMA_CONN_NONE             ((0UL))         /** 无外设        */
#define AMDR_DMA_CONN_MCI              ((1UL))         /** SD card  */
#define AMDR_DMA_CONN_SSP0_TX          ((2UL))         /**< SSP0 Tx */
#define AMDR_DMA_CONN_SSP0_RX          ((3UL))         /**< SSP0 Rx */
#define AMDR_DMA_CONN_SSP1_TX          ((4UL))         /**< SSP1 Tx */
#define AMDR_DMA_CONN_SSP1_RX          ((5UL))         /**< SSP1 Rx */
#define AMDR_DMA_CONN_SSP2_TX          ((6UL))         /**< SSP2 Tx */
#define AMDR_DMA_CONN_SSP2_RX          ((7UL))         /**< SSP2 Rx */
#define AMDR_DMA_CONN_ADC              ((8UL))         /**< ADC */
#define AMDR_DMA_CONN_DAC              ((9UL))         /**< DAC */
#define AMDR_DMA_CONN_UART0_TX         ((10UL))        /**< UART0 Tx */
#define AMDR_DMA_CONN_UART0_RX         ((11UL))        /**< UART0 Rx */
#define AMDR_DMA_CONN_UART1_TX         ((12UL))        /**< UART1 Tx */
#define AMDR_DMA_CONN_UART1_RX         ((13UL))        /**< UART1 Rx */
#define AMDR_DMA_CONN_UART2_TX         ((14UL))        /**< UART2 Tx */
#define AMDR_DMA_CONN_UART2_RX         ((15UL))        /**< UART2 Rx */
#define AMDR_DMA_CONN_MAT0_0           ((16UL))        /**< MAT0.0 */
#define AMDR_DMA_CONN_MAT0_1           ((17UL))        /**< MAT0.1 */
#define AMDR_DMA_CONN_MAT1_0           ((18UL))        /**< MAT1.0 */
#define AMDR_DMA_CONN_MAT1_1           ((19UL))        /**< MAT1.1 */
#define AMDR_DMA_CONN_MAT2_0           ((20UL))        /**< MAT2.0 */
#define AMDR_DMA_CONN_MAT2_1           ((21UL))        /**< MAT2.1 */
#define AMDR_DMA_CONN_I2S_CH0          ((22UL))        /**< I2S channel 0 */
#define AMDR_DMA_CONN_I2S_CH1          ((23UL))        /**< I2S channel 1 */
#define AMDR_DMA_CONN_UART3_TX         ((26UL))        /**< UART3 Tx */
#define AMDR_DMA_CONN_UART3_RX         ((27UL))        /**< UART3 Rx */
#define AMDR_DMA_CONN_UART4_TX         ((28UL))        /**< UART3 Tx */
#define AMDR_DMA_CONN_UART4_RX         ((29UL))        /**< UART3 Rx */
#define AMDR_DMA_CONN_MAT3_0           ((30UL))        /**< MAT3.0 */
#define AMDR_DMA_CONN_MAT3_1           ((31UL))        /**< MAT3.1 */

/** @} */


/** \brief DMA中断回调函数类型 */
typedef void (*amdr_pfn_dma_isr_t)(void *p_arg, void *p_flg);	
	
/** \brief DMA中断回调函数信息 */
struct amdr_dma_int_info {
    
    /** \brief DMA触发回调函数 */
    amdr_pfn_dma_isr_t  pfn_isr;

    /** \brief 回调函数的第一个入口参数 */
    void               *p_arg;
};
	
/** \brief DMA设备信息 */
typedef struct amdr_dma_devinfo {
    
    /** \brief 指向DMA寄存器块的指针 */
    amhw_dma_t 			   *p_hw_dma;
	
    /** \brief 指向系统控制寄存器块的指针 */
    amhw_syscon_t 	       *p_hw_syscon;
	
	/** \brief AHB主机字节顺序，大小端模式 */
    amhw_dma_endian_mode_t  endian_mode;
	
    /** \brief DMA中断号 */
    uint8_t                 inum;
    
} amdr_dma_devinfo_t;

/**
 * \brief DMA设备实例
 */
typedef struct amdr_dma_dev {
    
    /** \brief 指向DMA设备信息的指针 */
    const amdr_dma_devinfo_t *p_devinfo;
    
} amdr_dma_dev_t;


/**
 * \brief 通道传输配置
 *
 * \param[in] chan  : DMA 通道号, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] flags : 配置参数，参见
 *                    \ref grp_amhw_dma_chan_config_flags "Channel Configuration Flags".
 * \param[in] src   : 源外设连接请求选择，参见
 *                    \ref grp_dma_chan_conn_req_num "Channel Connect Request Num"
 * \param[in] des   : 目标外设连接请求选择，参见
 *                    \ref grp_dma_chan_conn_req_num "Channel Connect Request Num"
 * 
 * \retval AM_OK    : 设置成功 
 */
int amdr_dma_chan_setup(int chan, uint8_t src, uint8_t des, uint32_t flags);

/**
 * \brief 启动链表项
 *
 * \param[in] chan    : DMA 通道号, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] p_lli   : 指向DMA链表项的指针
 *
 * \retval  AM_OK     : 操作成功 
 * \retval -AM_EINVAL : 参数无效 
 */
int amdr_dma_chan_lli_startup(int chan, amhw_dma_lli_t *p_lli);

/**
 * \brief 建立链表项
 *
 * \param[in] p_lli    : 建立的链表项
 * \param[in] src_addr : 源端首地址 
 * \param[in] dst_addr : 目标端首地址 
 * \param[in] nbytes   : 传输字节数，注意要与“flags”的宽度对应 
 * \param[in] flags    : 配置参数，参见
 *                       \ref grp_amhw_dma_chan_control_flags 
 * 
 * \retval  AM_OK      : 建立成功 
 * \retval -AM_EINVAL  : 无效参数 
 */
int amdr_dma_chan_lli_build(amhw_dma_lli_t *p_lli,
                            uint32_t        src_addr,
                            uint32_t        dst_addr,	
                            uint16_t        nbytes,
                            uint32_t        flags);

/**
 * \brief 连接两个链表项
 *
 * \attention 传输地址必须4字节对齐
 *
 * \param[in] p_desc : 指向当前链表项的指针
 * \param[in] p_next : 指向下一个链表项的指针
 *
 * \retval  AM_OK    : 连接成功 
 */
int amdr_dma_lli_link(amhw_dma_lli_t  *p_desc, 
                      amhw_dma_lli_t  *p_next);

/**
 * \brief 开始通道传输 
 * \param[in] chan : DMA 通道号, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \retval AM_OK   : 操作成功 
 */
int amdr_dma_chan_start(int chan);

/**
 * \brief 停止通道传输 
 * \param[in] chan : DMA 通道号, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \retval AM_OK   : 操作成功 
 */
int amdr_dma_chan_stop(int chan);
	
/**
 * \brief 连接DMA回调函数 
 *
 * \attention 该回调函数的第二个参数可从驱动获得，该参数的取值范围是 AMDR_DMA_INT* 
 *            (#AMDR_DMA_INTTC)或(#AMDR_DMA_INTERR)
 *
 * \param[in] chan    : DMA 通道号, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] pfn_isr : 回调函数指针 
 * \param[in] p_arg   : 回调函数的第一个入口参数 
 *
 * \retval  AM_OK     : 连接成功 
 * \retval -AM_EPERM  : 参数错误 
 */
int amdr_dma_isr_connect(int                 chan,
                         amdr_pfn_dma_isr_t  pfn_isr, 
                         void               *p_arg);

/**
 * \brief 删除DMA回调函数的连接 
 *
 * \attention 该回调函数的第二个参数可从驱动获得，该参数的取值范围是 AMDR_DMA_INT* 
 *            (#AMDR_DMA_INTTC)或(#AMDR_DMA_INTERR)
 *
 * \param[in] chan    : DMA 通道号, 值为：DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \retval  AM_OK     : 删除成功 
 * \retval -AM_EINVAL : 参数错误 
 */
int amdr_dma_isr_disconnect(int chan);

/**
 * \brief DMA初始化
 *
 * \param[in] p_dev     : 指向DMA设备的指针 
 * \param[in] p_devinfo : 指向DMA设备信息的指针 
 *
 * \retval  AM_OK       : 初始化成功 
 */
int amdr_dma_init(amdr_dma_dev_t *p_dev, const amdr_dma_devinfo_t *p_devinfo);


/**
 * \brief DMA去初始化 
 *
 * \param[in] p_dev : 指向DMA设备的指针 
 *
 * \return  无
 */
void amdr_dma_deinit (amdr_dma_dev_t *p_dev);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_DMA_H */

/* end of file */
