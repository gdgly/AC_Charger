/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief LPC17xx DMA 接口
 *
 * 使用本服务需要包含以下头文件：
 * \code
 * #include "aw_lpc17xx_dma.h"
 * \endcode
 *
 * \par 简单示例
 * \code
 * \endcode
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history:
 * - 1.01 15-10-15  cod, modify DMA marco defintion.
 * - 1.00 15-08-31  anu, first implementation
 * \endinternal
 */

#ifndef __AW_LPC17XX_DMA_H
#define __AW_LPC17XX_DMA_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/


/**
 * \addtogroup grp_aw_if_lpc17xx_dma
 * \copydetails aw_lpc17xx_dma.h
 * @{
 */

#include "aw_types.h"
#include "aw_sem.h"   
#include "amdr_dma.h"

/**
 * \name DMA 通道编号
 * \anchor grp_dma_channel
 * @{
 */
#define AW_DMA_CHAN_0  DMA_CHAN_0      /**< \brief DMA通道0  */
#define AW_DMA_CHAN_1  DMA_CHAN_1      /**< \brief DMA通道1  */
#define AW_DMA_CHAN_2  DMA_CHAN_2      /**< \brief DMA通道2  */
#define AW_DMA_CHAN_3  DMA_CHAN_3      /**< \brief DMA通道3  */
#define AW_DMA_CHAN_4  DMA_CHAN_4      /**< \brief DMA通道4  */
#define AW_DMA_CHAN_5  DMA_CHAN_5      /**< \brief DMA通道5  */
#define AW_DMA_CHAN_6  DMA_CHAN_6      /**< \brief DMA通道6  */
#define AW_DMA_CHAN_7  DMA_CHAN_7      /**< \brief DMA通道7  */
/** @} */

/**
 * \name DMA 通道连接请求编号
 * \anchor grp_dma_chan_conn_req_num
 * @{
 */
#ifdef AW_LPC177X_8X
#define AW_DMA_CONN_NONE      AMDR_DMA_CONN_NONE      /** 无外设        */
#define AW_DMA_CONN_MCI       AMDR_DMA_CONN_MCI       /** SD card  */
#define AW_DMA_CONN_SSP0_TX   AMDR_DMA_CONN_SSP0_TX   /**< SSP0 Tx */
#define AW_DMA_CONN_SSP0_RX   AMDR_DMA_CONN_SSP0_RX   /**< SSP0 Rx */
#define AW_DMA_CONN_SSP1_TX   AMDR_DMA_CONN_SSP1_TX   /**< SSP1 Tx */
#define AW_DMA_CONN_SSP1_RX   AMDR_DMA_CONN_SSP1_RX   /**< SSP1 Rx */
#define AW_DMA_CONN_SSP2_TX   AMDR_DMA_CONN_SSP2_TX   /**< SSP2 Tx */
#define AW_DMA_CONN_SSP2_RX   AMDR_DMA_CONN_SSP2_RX   /**< SSP2 Rx */
#define AW_DMA_CONN_ADC       AMDR_DMA_CONN_ADC       /**< ADC */
#define AW_DMA_CONN_DAC       AMDR_DMA_CONN_DAC       /**< DAC */
#define AW_DMA_CONN_UART0_TX  AMDR_DMA_CONN_UART0_TX  /**< UART0 Tx */
#define AW_DMA_CONN_UART0_RX  AMDR_DMA_CONN_UART0_RX  /**< UART0 Rx */
#define AW_DMA_CONN_UART1_TX  AMDR_DMA_CONN_UART1_TX  /**< UART1 Tx */
#define AW_DMA_CONN_UART1_RX  AMDR_DMA_CONN_UART1_RX  /**< UART1 Rx */
#define AW_DMA_CONN_UART2_TX  AMDR_DMA_CONN_UART2_TX  /**< UART2 Tx */
#define AW_DMA_CONN_UART2_RX  AMDR_DMA_CONN_UART2_RX  /**< UART2 Rx */
#define AW_DMA_CONN_MAT0_0    AMDR_DMA_CONN_MAT0_0    /**< MAT0.0 */
#define AW_DMA_CONN_MAT0_1    AMDR_DMA_CONN_MAT0_1    /**< MAT0.1 */
#define AW_DMA_CONN_MAT1_0    AMDR_DMA_CONN_MAT1_0    /**< MAT1.0 */
#define AW_DMA_CONN_MAT1_1    AMDR_DMA_CONN_MAT1_1    /**< MAT1.1 */
#define AW_DMA_CONN_MAT2_0    AMDR_DMA_CONN_MAT2_0    /**< MAT2.0 */
#define AW_DMA_CONN_MAT2_1    AMDR_DMA_CONN_MAT2_1    /**< MAT2.1 */
#define AW_DMA_CONN_I2S_CH0   AMDR_DMA_CONN_I2S_CH0   /**< I2S channel 0 */
#define AW_DMA_CONN_I2S_CH1   AMDR_DMA_CONN_I2S_CH1   /**< I2S channel 1 */
#define AW_DMA_CONN_UART3_TX  AMDR_DMA_CONN_UART3_TX  /**< UART3 Tx */
#define AW_DMA_CONN_UART3_RX  AMDR_DMA_CONN_UART3_RX  /**< UART3 Rx */
#define AW_DMA_CONN_UART4_TX  AMDR_DMA_CONN_UART4_TX  /**< UART3 Tx */
#define AW_DMA_CONN_UART4_RX  AMDR_DMA_CONN_UART4_RX  /**< UART3 Rx */
#define AW_DMA_CONN_MAT3_0    AMDR_DMA_CONN_MAT3_0    /**< MAT3.0 */
#define AW_DMA_CONN_MAT3_1    AMDR_DMA_CONN_MAT3_1    /**< MAT3.1 */
#else
#define AW_DMA_CONN_NONE      AMDR_DMA_CONN_NONE      /**< \brief 无外设         */
#define AW_DMA_CONN_SSP0_TX   AMDR_DMA_CONN_SSP0_TX   /**< \brief SSP0 Tx  */
#define AW_DMA_CONN_SSP0_RX   AMDR_DMA_CONN_SSP0_RX   /**< \brief SSP0 Rx  */
#define AW_DMA_CONN_SSP1_TX   AMDR_DMA_CONN_SSP1_TX   /**< \brief SSP1 Tx  */
#define AW_DMA_CONN_SSP1_RX   AMDR_DMA_CONN_SSP1_RX   /**< \brief SSP1 Rx  */
#define AW_DMA_CONN_ADC       AMDR_DMA_CONN_ADC       /**< \brief ADC      */
#define AW_DMA_CONN_I2S0      AMDR_DMA_CONN_I2S0      /**< \brief I2S通道0 */
#define AW_DMA_CONN_I2S1      AMDR_DMA_CONN_I2S1      /**< \brief I2S通道1 */
#define AW_DMA_CONN_DAC       AMDR_DMA_CONN_DAC       /**< \brief DAC      */
#define AW_DMA_CONN_UART0_TX  AMDR_DMA_CONN_UART0_TX  /**< \brief UART0 TX */
#define AW_DMA_CONN_UART0_RX  AMDR_DMA_CONN_UART0_RX  /**< \brief UART0 RX */
#define AW_DMA_CONN_UART1_TX  AMDR_DMA_CONN_UART1_TX  /**< \brief UART1 TX */
#define AW_DMA_CONN_UART1_RX  AMDR_DMA_CONN_UART1_RX  /**< \brief UART1 RX */
#define AW_DMA_CONN_UART2_TX  AMDR_DMA_CONN_UART2_TX  /**< \brief UART2 TX */
#define AW_DMA_CONN_UART2_RX  AMDR_DMA_CONN_UART2_RX  /**< \brief UART2 RX */
#define AW_DMA_CONN_UART3_TX  AMDR_DMA_CONN_UART3_TX  /**< \brief UART3 TX */
#define AW_DMA_CONN_UART3_RX  AMDR_DMA_CONN_UART3_RX  /**< \brief UART3 RX */
#define AW_DMA_CONN_MAT0_0    AMDR_DMA_CONN_MAT0_0    /**< \brief 定时器0 匹配0   */
#define AW_DMA_CONN_MAT0_1    AMDR_DMA_CONN_MAT0_1    /**< \brief 定时器0 匹配1   */
#define AW_DMA_CONN_MAT1_0    AMDR_DMA_CONN_MAT1_0    /**< \brief 定时器1 匹配0   */
#define AW_DMA_CONN_MAT1_1    AMDR_DMA_CONN_MAT1_1    /**< \brief 定时器1 匹配1   */
#define AW_DMA_CONN_MAT2_0    AMDR_DMA_CONN_MAT2_0    /**< \brief 定时器2 匹配0   */
#define AW_DMA_CONN_MAT2_1    AMDR_DMA_CONN_MAT2_1    /**< \brief 定时器2 匹配1   */
#define AW_DMA_CONN_MAT3_0    AMDR_DMA_CONN_MAT3_0    /**< \brief 定时器3 匹配0   */
#define AW_DMA_CONN_MAT3_1    AMDR_DMA_CONN_MAT3_1    /**< \brief 定时器3 匹配1   */
#endif
/** @} */

/**
 * \name 定义通道配置参数
 * \anchor grp_amh_dma_chan_setup_flags
 * @{
 */
#ifndef AW_LPC177X_8X
/**
 * \brief 源外设请求通道请求类型
 */
#define AW_DMA_CCONFIG_SREQ_NONE	        AMHW_DMA_CCONFIG_SREQ_NONE	          /**< \brief 传输源存储器，忽略该字段  */
#define AW_DMA_CCONFIG_SREQ_SSP0TX          AMHW_DMA_CCONFIG_SREQ_SSP0TX         /**< \brief SSP0 TX	 */
#define AW_DMA_CCONFIG_SREQ_SSP0RX          AMHW_DMA_CCONFIG_SREQ_SSP0RX         /**< \brief SSP0 RX	 */
#define AW_DMA_CCONFIG_SREQ_SSP1TX          AMHW_DMA_CCONFIG_SREQ_SSP1TX         /**< \brief SSP1 TX	 */
#define AW_DMA_CCONFIG_SREQ_SSP1RX	        AMHW_DMA_CCONFIG_SREQ_SSP1RX	      /**< \brief SSP1 RX	 */
#define AW_DMA_CCONFIG_SREQ_ADC	            AMHW_DMA_CCONFIG_SREQ_ADC	          /**< \brief ADC 		 */
#define AW_DMA_CCONFIG_SREQ_I2S0	        AMHW_DMA_CCONFIG_SREQ_I2S0	          /**< \brief I2S通道0 */
#define AW_DMA_CCONFIG_SREQ_I2S1	        AMHW_DMA_CCONFIG_SREQ_I2S1	          /**< \brief I2S通道1 */
#define AW_DMA_CCONFIG_SREQ_DAC             AMHW_DMA_CCONFIG_SREQ_DAC            /**< \brief DAC			 */
#define AW_DMA_CCONFIG_SREQ_UART0TX_MAT00   AMHW_DMA_CCONFIG_SREQ_UART0TX_MAT00  /**< \brief UART0 TX 或 定时器0 匹配0	*/
#define AW_DMA_CCONFIG_SREQ_UART0RX_MAT01   AMHW_DMA_CCONFIG_SREQ_UART0RX_MAT01  /**< \brief UART0 RX 或 定时器0 匹配1	*/
#define AW_DMA_CCONFIG_SREQ_UART1TX_MAT10   AMHW_DMA_CCONFIG_SREQ_UART1TX_MAT10  /**< \brief UART1 TX 或 定时器1 匹配0	*/
#define AW_DMA_CCONFIG_SREQ_UART1RX_MAT11   AMHW_DMA_CCONFIG_SREQ_UART1RX_MAT11  /**< \brief UART1 RX 或 定时器1 匹配1	*/
#define AW_DMA_CCONFIG_SREQ_UART2TX_MAT20   AMHW_DMA_CCONFIG_SREQ_UART2TX_MAT20  /**< \brief UART2 TX 或 定时器2 匹配0	*/
#define AW_DMA_CCONFIG_SREQ_UART2RX_MAT21   AMHW_DMA_CCONFIG_SREQ_UART2RX_MAT21  /**< \brief UART2 RX 或 定时器2 匹配1	*/
#define AW_DMA_CCONFIG_SREQ_UART3TX_MAT30   AMHW_DMA_CCONFIG_SREQ_UART3TX_MAT30  /**< \brief UART3 TX 或 定时器3 匹配0	*/
#define AW_DMA_CCONFIG_SREQ_UART3RX_MAT31   AMHW_DMA_CCONFIG_SREQ_UART3RX_MAT31  /**< \brief UART3 RX 或 定时器3 匹配1	*/

/**
 * \brief 目标外设请求通道请求类型
 */
#define AW_DMA_CCONFIG_DREQ_NONE	       AMHW_DMA_CCONFIG_DREQ_NONE	            /**< \brief 传输目标存储器，忽略该字段*/
#define AW_DMA_CCONFIG_DREQ_SSP0TX         AMHW_DMA_CCONFIG_DREQ_SSP0TX              /**< \brief SSP0 TX	 */
#define AW_DMA_CCONFIG_DREQ_SSP0RX         AMHW_DMA_CCONFIG_DREQ_SSP0RX              /**< \brief SSP0 RX	 */
#define AW_DMA_CCONFIG_DREQ_SSP1TX         AMHW_DMA_CCONFIG_DREQ_SSP1TX              /**< \brief SSP1 TX	 */
#define AW_DMA_CCONFIG_DREQ_SSP1RX         AMHW_DMA_CCONFIG_DREQ_SSP1RX              /**< \brief SSP1 RX	 */
#define AW_DMA_CCONFIG_DREQ_ADC            AMHW_DMA_CCONFIG_DREQ_ADC                 /**< \brief ADC      */
#define AW_DMA_CCONFIG_DREQ_I2S0	       AMHW_DMA_CCONFIG_DREQ_I2S0	            /**< \brief I2S通道0 */
#define AW_DMA_CCONFIG_DREQ_I2S1           AMHW_DMA_CCONFIG_DREQ_I2S1                /**< \brief I2S通道1 */
#define AW_DMA_CCONFIG_DREQ_DAC            AMHW_DMA_CCONFIG_DREQ_DAC                 /**< \brief DAC      */
#define AW_DMA_CCONFIG_DREQ_UART0TX_MAT00  AMHW_DMA_CCONFIG_DREQ_UART0TX_MAT00       /**< \brief UART0 TX 或 定时器0 匹配0	*/
#define AW_DMA_CCONFIG_DREQ_UART0RX_MAT01  AMHW_DMA_CCONFIG_DREQ_UART0RX_MAT01       /**< \brief UART0 RX 或 定时器0 匹配1	*/
#define AW_DMA_CCONFIG_DREQ_UART1TX_MAT10  AMHW_DMA_CCONFIG_DREQ_UART1TX_MAT10       /**< \brief UART1 TX 或 定时器1 匹配0	*/
#define AW_DMA_CCONFIG_DREQ_UART1RX_MAT11  AMHW_DMA_CCONFIG_DREQ_UART1RX_MAT11       /**< \brief UART1 RX 或 定时器1 匹配1	*/
#define AW_DMA_CCONFIG_DREQ_UART2TX_MAT20  AMHW_DMA_CCONFIG_DREQ_UART2TX_MAT20       /**< \brief UART2 TX 或 定时器2 匹配0	*/
#define AW_DMA_CCONFIG_DREQ_UART2RX_MAT21  AMHW_DMA_CCONFIG_DREQ_UART2RX_MAT21       /**< \brief UART2 RX 或 定时器2 匹配1	*/
#define AW_DMA_CCONFIG_DREQ_UART3TX_MAT30  AMHW_DMA_CCONFIG_DREQ_UART3TX_MAT30       /**< \brief UART3 TX 或 定时器3 匹配0	*/
#define AW_DMA_CCONFIG_DREQ_UART3RX_MAT31  AMHW_DMA_CCONFIG_DREQ_UART3RX_MAT31       /**< \brief UART3 RX 或 定时器3 匹配1	*/
#endif
/**
 * \brief 通道传输类型
 */
/**< \brief 存储器到存储器	 */
#define AW_DMA_CCONFIG_TRANTYPE_M2M       AMHW_DMA_CCONFIG_TRANTYPE_M2M
/**< \brief 存储器到外设     */
#define AW_DMA_CCONFIG_TRANTYPE_M2P       AMHW_DMA_CCONFIG_TRANTYPE_M2P
/**< \brief 外设到存储器     */
#define AW_DMA_CCONFIG_TRANTYPE_P2M       AMHW_DMA_CCONFIG_TRANTYPE_P2M
/**< \brief 源外设到目标外设 */
#define AW_DMA_CCONFIG_TRANTYPE_P2P       AMHW_DMA_CCONFIG_TRANTYPE_P2P
/** \brief 存储器到存储器(目标外设控制) */
#define AW_DMA_CCONFIG_TRANTYPE_P2P_DEST  AMHW_DMA_CCONFIG_TRANTYPE_P2P_DEST
/** \brief 存储器到外设 (目标外设控制) */
#define AW_DMA_CCONFIG_TRANTYPE_M2P_DEST  AMHW_DMA_CCONFIG_TRANTYPE_M2P_DEST
/** \brief 外设到存储器(源外设控制)   */
#define AW_DMA_CCONFIG_TRANTYPE_P2M_SRC   AMHW_DMA_CCONFIG_TRANTYPE_P2M_SRC
/** \brief 源外设到目标外设 (源外设控制) */
#define AW_DMA_CCONFIG_TRANTYPE_P2P_SRC   AMHW_DMA_CCONFIG_TRANTYPE_P2P_SRC

/**
 * \brief 通道中断错误屏蔽
 */
#define AW_DMA_CCONFIG_IE_VALID    AMHW_DMA_CCONFIG_IE_VALID    /**< \brief 中断错误不屏蔽 	*/
#define AW_DMA_CCONFIG_IE_INVALID  AMHW_DMA_CCONFIG_IE_INVALID  /**< \brief 中断错误屏蔽    */

/**
 * \brief 通道终端计数中断屏蔽
 */
#define AW_DMA_CCONFIG_ITC_VALID	AMHW_DMA_CCONFIG_ITC_VALID	   /**< \brief 中断错误不屏蔽  */
#define AW_DMA_CCONFIG_ITC_INVALID  AMHW_DMA_CCONFIG_ITC_INVALID   /**< \brief 中断错误屏蔽    */

/**
 * \brief 锁定传输
 */
#define AW_DMA_CCONFIG_TRANS_LOCK    AMHW_DMA_CCONFIG_TRANS_LOCK     /**< \brief 锁定传输     */
#define AW_DMA_CCONFIG_TRANS_UNLOCK  AMHW_DMA_CCONFIG_TRANS_UNLOCK	 /**< \brief 传输不锁定   */
 
/**
 * \brief DMA传输请求使能
 */
#define AW_DMA_CCONFIG_REQ_ENABLE  AMHW_DMA_CCONFIG_REQ_ENABLE

/** @} */

/**
 * \name 定义通道控制信息
 * \anchor grp_amh_dma_chan_xfercfg_flags
 * @{
 */

/**
 * \brief 源突发传输大小
 */
#define AW_DMA_CCONTROL_SBSIZE_1    AMHW_DMA_CCONTROL_SBSIZE_1        /**< \brief  源突发传输数据量 SIZE = 1   */
#define AW_DMA_CCONTROL_SBSIZE_4    AMHW_DMA_CCONTROL_SBSIZE_4        /**< \brief  源突发传输数据量 SIZE = 4   */
#define AW_DMA_CCONTROL_SBSIZE_8 	AMHW_DMA_CCONTROL_SBSIZE_8 	      /**< \brief  源突发传输数据量 SIZE = 8   */
#define AW_DMA_CCONTROL_SBSIZE_16   AMHW_DMA_CCONTROL_SBSIZE_16       /**< \brief  源突发传输数据量 SIZE = 16  */
#define AW_DMA_CCONTROL_SBSIZE_32   AMHW_DMA_CCONTROL_SBSIZE_32       /**< \brief  源突发传输数据量 SIZE = 32  */
#define AW_DMA_CCONTROL_SBSIZE_64   AMHW_DMA_CCONTROL_SBSIZE_64       /**< \brief  源突发传输数据量 SIZE = 64  */
#define AW_DMA_CCONTROL_SBSIZE_128  AMHW_DMA_CCONTROL_SBSIZE_128      /**< \brief  源突发传输数据量 SIZE = 128 */
#define AW_DMA_CCONTROL_SBSIZE_256  AMHW_DMA_CCONTROL_SBSIZE_256      /**< \brief  源突发传输数据量 SIZE = 256 */

/**
 * \brief 目标突发传输大小
 */
#define AW_DMA_CCONTROL_DBSIZE_1    AMHW_DMA_CCONTROL_DBSIZE_1     /**< \brief  目标突发传输数据量 SIZE = 1   */
#define AW_DMA_CCONTROL_DBSIZE_4 	AMHW_DMA_CCONTROL_DBSIZE_4 	   /**< \brief  目标突发传输数据量 SIZE = 4   */
#define AW_DMA_CCONTROL_DBSIZE_8    AMHW_DMA_CCONTROL_DBSIZE_8 	   /**< \brief  目标突发传输数据量 SIZE = 8   */
#define AW_DMA_CCONTROL_DBSIZE_16   AMHW_DMA_CCONTROL_DBSIZE_16    /**< \brief  目标突发传输数据量 SIZE = 16  */
#define AW_DMA_CCONTROL_DBSIZE_32   AMHW_DMA_CCONTROL_DBSIZE_32    /**< \brief  目标突发传输数据量 SIZE = 32  */
#define AW_DMA_CCONTROL_DBSIZE_64   AMHW_DMA_CCONTROL_DBSIZE_64    /**< \brief  目标突发传输数据量 SIZE = 64  */
#define AW_DMA_CCONTROL_DBSIZE_128  AMHW_DMA_CCONTROL_DBSIZE_128   /**< \brief  目标突发传输数据量 SIZE = 128 */
#define AW_DMA_CCONTROL_DBSIZE_256  AMHW_DMA_CCONTROL_DBSIZE_256   /**< \brief  目标突发传输数据量 SIZE = 256 */

/**
 * \brief 源传输数据宽度
 */
#define AW_DMA_CCONTROL_SWIDTH_8BIT   AMHW_DMA_CCONTROL_SWIDTH_8BIT   /**< \brief  8-bit 数据宽度  */
#define AW_DMA_CCONTROL_SWIDTH_16BIT  AMHW_DMA_CCONTROL_SWIDTH_16BIT  /**< \brief 16-bit 数据宽度  */
#define AW_DMA_CCONTROL_SWIDTH_32BIT  AMHW_DMA_CCONTROL_SWIDTH_32BIT  /**< \brief 32-bit 数据宽度  */

/**
 * \brief 目标传输数据宽度
 */
#define AW_DMA_CCONTROL_DWIDTH_8BIT   AMHW_DMA_CCONTROL_DWIDTH_8BIT    /**< \brief  8-bit 数据宽度  */
#define AW_DMA_CCONTROL_DWIDTH_16BIT  AMHW_DMA_CCONTROL_DWIDTH_16BIT   /**< \brief 16-bit 数据宽度  */
#define AW_DMA_CCONTROL_DWIDTH_32BIT  AMHW_DMA_CCONTROL_DWIDTH_32BIT   /**< \brief 32-bit 数据宽度  */

/**
 * \brief 传输后源地址增加
 */
#define AW_DMA_CCONTROL_SI_DISABLE  AMHW_DMA_CCONTROL_SI_DISABLE        /**< \brief 源地址不增加    */
#define AW_DMA_CCONTROL_SI_ENABLE   AMHW_DMA_CCONTROL_SI_ENABLE         /**< \brief 源地址增加      */
                                      
/**                                  
 * \brief 传输后目标地址增加         
 */                                  
#define AW_DMA_CCONTROL_DI_DISABLE  AMHW_DMA_CCONTROL_DI_DISABLE        /**< \brief 目标地址不增加  */
#define AW_DMA_CCONTROL_DI_ENABLE   AMHW_DMA_CCONTROL_DI_ENABLE         /**< \brief 目标地址增加    */
                                     
/**                                  
 * \brief 指定模式下访问AHB总线      
 */                                  
#define AW_DMA_CCONTROL_PROT1_DISABLE  AMHW_DMA_CCONTROL_PROT1_DISABLE      /**< \brief 用户模式下    */
#define AW_DMA_CCONTROL_PROT1_ENABLE   AMHW_DMA_CCONTROL_PROT1_ENABLE       /**< \brief 特权模式下    */
                                     
/**                                  
 * \brief AHB主机是否可缓冲          
 */                                  
#define AW_DMA_CCONTROL_PROT2_DISABLE  AMHW_DMA_CCONTROL_PROT2_DISABLE      /**< \brief 不可缓冲  */
#define AW_DMA_CCONTROL_PROT2_ENABLE   AMHW_DMA_CCONTROL_PROT2_ENABLE       /**< \brief 可缓冲    */

/**
 * \brief AHB从机访问AHB主机时，主机是否有Cache功能
 */
#define AW_DMA_CCONTROL_PROT3_DISABLE  AMHW_DMA_CCONTROL_PROT3_DISABLE      /**< \brief 不可缓存  */
#define AW_DMA_CCONTROL_PROT3_ENABLE   AMHW_DMA_CCONTROL_PROT3_ENABLE       /**< \brief 可缓存    */

/**
 * \brief 通道终端计数中断使能
 */
#define AW_DMA_CCONTROL_ITC_DISABLE  AMHW_DMA_CCONTROL_ITC_DISABLE       /**< \brief 终端计数中断失能  */
#define AW_DMA_CCONTROL_ITC_ENABLE   AMHW_DMA_CCONTROL_ITC_ENABLE        /**< \brief 终端计数中断使能  */

/** @} */

/**
 * \name Channel transfer interrupt flags
 * @{
 */

#define AW_DMA_INT_FLG          AMDR_DMA_INTTC                   /** \brief Interrupt flag     */
#define AW_DMA_INT_FLG_ERR      AMDR_DMA_INTERR                  /** \brief Error interrupt flag */

/** @} */

/** \brief DMA 通道描述符类型 */
typedef amhw_dma_lli_t  aw_lpc17xx_dma_desc_t;

/** \brief DMA 异步回调函数类型 */
typedef amdr_pfn_dma_isr_t   aw_pfunc_dma_isr_t;


/**
 * \brief DMA 通道设置
 *
 * 设置DMA的传输通道。
 *
 * \param[in] chan  : DMA 通道号，见： \ref grp_dma_channel
 * \param[in] src   : 源外设连接请求选择，参见
 *                    \ref grp_dma_chan_conn_req_num
 * \param[in] des   : 目标外设连接请求选择，参见
 *                    \ref grp_dma_chan_conn_req_num
 * \param[in] flags : 配置信息，由配置参数进行或操作得，配置参数见：
 *                    \ref grp_amh_dma_chan_setup_flags
 *
 * \retval  AW_OK   : DMA 通道设置成功 
 */
aw_err_t aw_lpc17xx_dma_chan_setup(int      chan,
		                           uint8_t  src,
		                           uint8_t  des,
		                           uint32_t flags);

/**
 * \brief 建立 DMA 通道描述符。
 *
 * \param[in] p_desc   : 通道描述符
 * \param[in] src_addr : 源数据首地址
 * \param[in] dst_addr : 目标数据首地址
 * \param[in] nbytes   : 传输字节数
 * \param[in] flags    : 传输配置信息，由配置参数进行或操作得，配置参数见：
 *                       \ref grp_amh_dma_chan_xfercfg_flags 
 *
 * \retval  AW_OK      : 描述符建立成功
 * \retval -AM_EINVAL  : 无效参数
 * 
 */
aw_err_t aw_lpc17xx_dma_desc_build(aw_lpc17xx_dma_desc_t *p_desc,
                                   uint32_t               src_addr,
                                   uint32_t               dst_addr,
                                   uint32_t               nbytes,
                                   uint32_t               flags);

/**
 * \brief DMA 异步传输
 * 
 * 当传输完成时，调用用户自定义的回调函数。 *
 * \param[in] chan           : DMA 通道号，参见 \ref grp_dma_channel
 * \param[in] p_desc         : 通道描述符
 * \param[in] pfunc_callback : 传输完成回调函数
 * \param[in] p_arg          : 回调函数第一个参数
 * 
 * \retval  AW_OK            : 传输启动成功
 * 
 * \note 回调函数的类型为：void (*)(void *p_arg, void *p_flg), 其第一个参数p_arg
 *       由用户传入，即对应该函数的第4个参数P_arg；第2个参数p_flg由底层驱动传递
 *       给用户使用.
 *
 * \par 范例
 * \code 
 * void dma_isr (void *p_arg, void *p_flg)  //DMA 中断处理函数
 * {
 *     int flag = (int)p_flg;
 *
 *     if (flag == AW_DMA_INT_FLG) {
 *         // do something
 *     } else if (flag == AW_DMA_INT_FLG) {
 *         // do something
 *     }
 * }
 * \endcode
 */
aw_err_t aw_lpc17xx_dma_tran_async(int                     chan,
								   aw_lpc17xx_dma_desc_t  *p_desc,
                                   aw_pfunc_dma_isr_t      pfunc_callback,
                                   void                   *p_arg);

/**
 * \brief DMA 同步传输
 *
 * \param[in] chan   : DMA 通道号,参见\ref grp_dma_channel
 * \param[in] p_desc : 通道描述符
 *
 * \retval AW_OK     : 传输成功
 *
 *
 */
aw_err_t aw_lpc17xx_dma_tran_sync(int chan, aw_lpc17xx_dma_desc_t *p_desc);

/**
 * \brief 连接重载描述符
 *
 * \param[in] p_desc : 重载描述符
 * \param[in] p_next : 被指向的重载描述符
 *
 * \retval AW_OK     : 连接成功
 *
 * \par 范例1
 * \code 
 * __align(16) aw_lpc17xx_dma_desc_t reload_desc[2];
 *
 * aw_lpc17xx_dma_desc_link(&reload_desc[0], &reload_desc[1]);
 * aw_lpc17xx_dma_desc_link(&reload_desc[1], &reload_desc[0]);
 * \endcode
 *
 * \par 范例2
 * \code 
 * __align(16) aw_lpc17xx_dma_desc_t reload_desc[3];
 *
 * aw_lpc17xx_dma_desc_link(&reload_desc[0], &reload_desc[1]);
 * aw_lpc17xx_dma_desc_link(&reload_desc[1], &reload_desc[2]);
 * aw_lpc17xx_dma_desc_link(&reload_desc[2], &reload_desc[0]);
 * \endcode
 */
aw_err_t aw_lpc17xx_dma_desc_link(aw_lpc17xx_dma_desc_t *p_desc,
							      aw_lpc17xx_dma_desc_t *p_next);

/**
 * \brief 停止 DMA 通道传输
 *
 * 只有在该通道no-busy时才能停止。
 *
 * \param[in] chan : DMA 通道号, 参见 \ref grp_dma_channel
 *
 * \retval AW_OK   : 操作成功。
 */
aw_err_t aw_lpc17xx_dma_tran_stop(int chan);


/** @} grp_aw_if_lpc17xx_dma */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_LPC17XX_DMA_H */

/* end of file */
