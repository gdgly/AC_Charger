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
 * \brief LPC17xx DMA �ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ���
 * \code
 * #include "aw_lpc17xx_dma.h"
 * \endcode
 *
 * \par ��ʾ��
 * \code
 * \endcode
 *
 * // �������ݴ���ӡ�����
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
 * \name DMA ͨ�����
 * \anchor grp_dma_channel
 * @{
 */
#define AW_DMA_CHAN_0  DMA_CHAN_0      /**< \brief DMAͨ��0  */
#define AW_DMA_CHAN_1  DMA_CHAN_1      /**< \brief DMAͨ��1  */
#define AW_DMA_CHAN_2  DMA_CHAN_2      /**< \brief DMAͨ��2  */
#define AW_DMA_CHAN_3  DMA_CHAN_3      /**< \brief DMAͨ��3  */
#define AW_DMA_CHAN_4  DMA_CHAN_4      /**< \brief DMAͨ��4  */
#define AW_DMA_CHAN_5  DMA_CHAN_5      /**< \brief DMAͨ��5  */
#define AW_DMA_CHAN_6  DMA_CHAN_6      /**< \brief DMAͨ��6  */
#define AW_DMA_CHAN_7  DMA_CHAN_7      /**< \brief DMAͨ��7  */
/** @} */

/**
 * \name DMA ͨ������������
 * \anchor grp_dma_chan_conn_req_num
 * @{
 */
#ifdef AW_LPC177X_8X
#define AW_DMA_CONN_NONE      AMDR_DMA_CONN_NONE      /** ������        */
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
#define AW_DMA_CONN_NONE      AMDR_DMA_CONN_NONE      /**< \brief ������         */
#define AW_DMA_CONN_SSP0_TX   AMDR_DMA_CONN_SSP0_TX   /**< \brief SSP0 Tx  */
#define AW_DMA_CONN_SSP0_RX   AMDR_DMA_CONN_SSP0_RX   /**< \brief SSP0 Rx  */
#define AW_DMA_CONN_SSP1_TX   AMDR_DMA_CONN_SSP1_TX   /**< \brief SSP1 Tx  */
#define AW_DMA_CONN_SSP1_RX   AMDR_DMA_CONN_SSP1_RX   /**< \brief SSP1 Rx  */
#define AW_DMA_CONN_ADC       AMDR_DMA_CONN_ADC       /**< \brief ADC      */
#define AW_DMA_CONN_I2S0      AMDR_DMA_CONN_I2S0      /**< \brief I2Sͨ��0 */
#define AW_DMA_CONN_I2S1      AMDR_DMA_CONN_I2S1      /**< \brief I2Sͨ��1 */
#define AW_DMA_CONN_DAC       AMDR_DMA_CONN_DAC       /**< \brief DAC      */
#define AW_DMA_CONN_UART0_TX  AMDR_DMA_CONN_UART0_TX  /**< \brief UART0 TX */
#define AW_DMA_CONN_UART0_RX  AMDR_DMA_CONN_UART0_RX  /**< \brief UART0 RX */
#define AW_DMA_CONN_UART1_TX  AMDR_DMA_CONN_UART1_TX  /**< \brief UART1 TX */
#define AW_DMA_CONN_UART1_RX  AMDR_DMA_CONN_UART1_RX  /**< \brief UART1 RX */
#define AW_DMA_CONN_UART2_TX  AMDR_DMA_CONN_UART2_TX  /**< \brief UART2 TX */
#define AW_DMA_CONN_UART2_RX  AMDR_DMA_CONN_UART2_RX  /**< \brief UART2 RX */
#define AW_DMA_CONN_UART3_TX  AMDR_DMA_CONN_UART3_TX  /**< \brief UART3 TX */
#define AW_DMA_CONN_UART3_RX  AMDR_DMA_CONN_UART3_RX  /**< \brief UART3 RX */
#define AW_DMA_CONN_MAT0_0    AMDR_DMA_CONN_MAT0_0    /**< \brief ��ʱ��0 ƥ��0   */
#define AW_DMA_CONN_MAT0_1    AMDR_DMA_CONN_MAT0_1    /**< \brief ��ʱ��0 ƥ��1   */
#define AW_DMA_CONN_MAT1_0    AMDR_DMA_CONN_MAT1_0    /**< \brief ��ʱ��1 ƥ��0   */
#define AW_DMA_CONN_MAT1_1    AMDR_DMA_CONN_MAT1_1    /**< \brief ��ʱ��1 ƥ��1   */
#define AW_DMA_CONN_MAT2_0    AMDR_DMA_CONN_MAT2_0    /**< \brief ��ʱ��2 ƥ��0   */
#define AW_DMA_CONN_MAT2_1    AMDR_DMA_CONN_MAT2_1    /**< \brief ��ʱ��2 ƥ��1   */
#define AW_DMA_CONN_MAT3_0    AMDR_DMA_CONN_MAT3_0    /**< \brief ��ʱ��3 ƥ��0   */
#define AW_DMA_CONN_MAT3_1    AMDR_DMA_CONN_MAT3_1    /**< \brief ��ʱ��3 ƥ��1   */
#endif
/** @} */

/**
 * \name ����ͨ�����ò���
 * \anchor grp_amh_dma_chan_setup_flags
 * @{
 */
#ifndef AW_LPC177X_8X
/**
 * \brief Դ��������ͨ����������
 */
#define AW_DMA_CCONFIG_SREQ_NONE	        AMHW_DMA_CCONFIG_SREQ_NONE	          /**< \brief ����Դ�洢�������Ը��ֶ�  */
#define AW_DMA_CCONFIG_SREQ_SSP0TX          AMHW_DMA_CCONFIG_SREQ_SSP0TX         /**< \brief SSP0 TX	 */
#define AW_DMA_CCONFIG_SREQ_SSP0RX          AMHW_DMA_CCONFIG_SREQ_SSP0RX         /**< \brief SSP0 RX	 */
#define AW_DMA_CCONFIG_SREQ_SSP1TX          AMHW_DMA_CCONFIG_SREQ_SSP1TX         /**< \brief SSP1 TX	 */
#define AW_DMA_CCONFIG_SREQ_SSP1RX	        AMHW_DMA_CCONFIG_SREQ_SSP1RX	      /**< \brief SSP1 RX	 */
#define AW_DMA_CCONFIG_SREQ_ADC	            AMHW_DMA_CCONFIG_SREQ_ADC	          /**< \brief ADC 		 */
#define AW_DMA_CCONFIG_SREQ_I2S0	        AMHW_DMA_CCONFIG_SREQ_I2S0	          /**< \brief I2Sͨ��0 */
#define AW_DMA_CCONFIG_SREQ_I2S1	        AMHW_DMA_CCONFIG_SREQ_I2S1	          /**< \brief I2Sͨ��1 */
#define AW_DMA_CCONFIG_SREQ_DAC             AMHW_DMA_CCONFIG_SREQ_DAC            /**< \brief DAC			 */
#define AW_DMA_CCONFIG_SREQ_UART0TX_MAT00   AMHW_DMA_CCONFIG_SREQ_UART0TX_MAT00  /**< \brief UART0 TX �� ��ʱ��0 ƥ��0	*/
#define AW_DMA_CCONFIG_SREQ_UART0RX_MAT01   AMHW_DMA_CCONFIG_SREQ_UART0RX_MAT01  /**< \brief UART0 RX �� ��ʱ��0 ƥ��1	*/
#define AW_DMA_CCONFIG_SREQ_UART1TX_MAT10   AMHW_DMA_CCONFIG_SREQ_UART1TX_MAT10  /**< \brief UART1 TX �� ��ʱ��1 ƥ��0	*/
#define AW_DMA_CCONFIG_SREQ_UART1RX_MAT11   AMHW_DMA_CCONFIG_SREQ_UART1RX_MAT11  /**< \brief UART1 RX �� ��ʱ��1 ƥ��1	*/
#define AW_DMA_CCONFIG_SREQ_UART2TX_MAT20   AMHW_DMA_CCONFIG_SREQ_UART2TX_MAT20  /**< \brief UART2 TX �� ��ʱ��2 ƥ��0	*/
#define AW_DMA_CCONFIG_SREQ_UART2RX_MAT21   AMHW_DMA_CCONFIG_SREQ_UART2RX_MAT21  /**< \brief UART2 RX �� ��ʱ��2 ƥ��1	*/
#define AW_DMA_CCONFIG_SREQ_UART3TX_MAT30   AMHW_DMA_CCONFIG_SREQ_UART3TX_MAT30  /**< \brief UART3 TX �� ��ʱ��3 ƥ��0	*/
#define AW_DMA_CCONFIG_SREQ_UART3RX_MAT31   AMHW_DMA_CCONFIG_SREQ_UART3RX_MAT31  /**< \brief UART3 RX �� ��ʱ��3 ƥ��1	*/

/**
 * \brief Ŀ����������ͨ����������
 */
#define AW_DMA_CCONFIG_DREQ_NONE	       AMHW_DMA_CCONFIG_DREQ_NONE	            /**< \brief ����Ŀ��洢�������Ը��ֶ�*/
#define AW_DMA_CCONFIG_DREQ_SSP0TX         AMHW_DMA_CCONFIG_DREQ_SSP0TX              /**< \brief SSP0 TX	 */
#define AW_DMA_CCONFIG_DREQ_SSP0RX         AMHW_DMA_CCONFIG_DREQ_SSP0RX              /**< \brief SSP0 RX	 */
#define AW_DMA_CCONFIG_DREQ_SSP1TX         AMHW_DMA_CCONFIG_DREQ_SSP1TX              /**< \brief SSP1 TX	 */
#define AW_DMA_CCONFIG_DREQ_SSP1RX         AMHW_DMA_CCONFIG_DREQ_SSP1RX              /**< \brief SSP1 RX	 */
#define AW_DMA_CCONFIG_DREQ_ADC            AMHW_DMA_CCONFIG_DREQ_ADC                 /**< \brief ADC      */
#define AW_DMA_CCONFIG_DREQ_I2S0	       AMHW_DMA_CCONFIG_DREQ_I2S0	            /**< \brief I2Sͨ��0 */
#define AW_DMA_CCONFIG_DREQ_I2S1           AMHW_DMA_CCONFIG_DREQ_I2S1                /**< \brief I2Sͨ��1 */
#define AW_DMA_CCONFIG_DREQ_DAC            AMHW_DMA_CCONFIG_DREQ_DAC                 /**< \brief DAC      */
#define AW_DMA_CCONFIG_DREQ_UART0TX_MAT00  AMHW_DMA_CCONFIG_DREQ_UART0TX_MAT00       /**< \brief UART0 TX �� ��ʱ��0 ƥ��0	*/
#define AW_DMA_CCONFIG_DREQ_UART0RX_MAT01  AMHW_DMA_CCONFIG_DREQ_UART0RX_MAT01       /**< \brief UART0 RX �� ��ʱ��0 ƥ��1	*/
#define AW_DMA_CCONFIG_DREQ_UART1TX_MAT10  AMHW_DMA_CCONFIG_DREQ_UART1TX_MAT10       /**< \brief UART1 TX �� ��ʱ��1 ƥ��0	*/
#define AW_DMA_CCONFIG_DREQ_UART1RX_MAT11  AMHW_DMA_CCONFIG_DREQ_UART1RX_MAT11       /**< \brief UART1 RX �� ��ʱ��1 ƥ��1	*/
#define AW_DMA_CCONFIG_DREQ_UART2TX_MAT20  AMHW_DMA_CCONFIG_DREQ_UART2TX_MAT20       /**< \brief UART2 TX �� ��ʱ��2 ƥ��0	*/
#define AW_DMA_CCONFIG_DREQ_UART2RX_MAT21  AMHW_DMA_CCONFIG_DREQ_UART2RX_MAT21       /**< \brief UART2 RX �� ��ʱ��2 ƥ��1	*/
#define AW_DMA_CCONFIG_DREQ_UART3TX_MAT30  AMHW_DMA_CCONFIG_DREQ_UART3TX_MAT30       /**< \brief UART3 TX �� ��ʱ��3 ƥ��0	*/
#define AW_DMA_CCONFIG_DREQ_UART3RX_MAT31  AMHW_DMA_CCONFIG_DREQ_UART3RX_MAT31       /**< \brief UART3 RX �� ��ʱ��3 ƥ��1	*/
#endif
/**
 * \brief ͨ����������
 */
/**< \brief �洢�����洢��	 */
#define AW_DMA_CCONFIG_TRANTYPE_M2M       AMHW_DMA_CCONFIG_TRANTYPE_M2M
/**< \brief �洢��������     */
#define AW_DMA_CCONFIG_TRANTYPE_M2P       AMHW_DMA_CCONFIG_TRANTYPE_M2P
/**< \brief ���赽�洢��     */
#define AW_DMA_CCONFIG_TRANTYPE_P2M       AMHW_DMA_CCONFIG_TRANTYPE_P2M
/**< \brief Դ���赽Ŀ������ */
#define AW_DMA_CCONFIG_TRANTYPE_P2P       AMHW_DMA_CCONFIG_TRANTYPE_P2P
/** \brief �洢�����洢��(Ŀ���������) */
#define AW_DMA_CCONFIG_TRANTYPE_P2P_DEST  AMHW_DMA_CCONFIG_TRANTYPE_P2P_DEST
/** \brief �洢�������� (Ŀ���������) */
#define AW_DMA_CCONFIG_TRANTYPE_M2P_DEST  AMHW_DMA_CCONFIG_TRANTYPE_M2P_DEST
/** \brief ���赽�洢��(Դ�������)   */
#define AW_DMA_CCONFIG_TRANTYPE_P2M_SRC   AMHW_DMA_CCONFIG_TRANTYPE_P2M_SRC
/** \brief Դ���赽Ŀ������ (Դ�������) */
#define AW_DMA_CCONFIG_TRANTYPE_P2P_SRC   AMHW_DMA_CCONFIG_TRANTYPE_P2P_SRC

/**
 * \brief ͨ���жϴ�������
 */
#define AW_DMA_CCONFIG_IE_VALID    AMHW_DMA_CCONFIG_IE_VALID    /**< \brief �жϴ������� 	*/
#define AW_DMA_CCONFIG_IE_INVALID  AMHW_DMA_CCONFIG_IE_INVALID  /**< \brief �жϴ�������    */

/**
 * \brief ͨ���ն˼����ж�����
 */
#define AW_DMA_CCONFIG_ITC_VALID	AMHW_DMA_CCONFIG_ITC_VALID	   /**< \brief �жϴ�������  */
#define AW_DMA_CCONFIG_ITC_INVALID  AMHW_DMA_CCONFIG_ITC_INVALID   /**< \brief �жϴ�������    */

/**
 * \brief ��������
 */
#define AW_DMA_CCONFIG_TRANS_LOCK    AMHW_DMA_CCONFIG_TRANS_LOCK     /**< \brief ��������     */
#define AW_DMA_CCONFIG_TRANS_UNLOCK  AMHW_DMA_CCONFIG_TRANS_UNLOCK	 /**< \brief ���䲻����   */
 
/**
 * \brief DMA��������ʹ��
 */
#define AW_DMA_CCONFIG_REQ_ENABLE  AMHW_DMA_CCONFIG_REQ_ENABLE

/** @} */

/**
 * \name ����ͨ��������Ϣ
 * \anchor grp_amh_dma_chan_xfercfg_flags
 * @{
 */

/**
 * \brief Դͻ�������С
 */
#define AW_DMA_CCONTROL_SBSIZE_1    AMHW_DMA_CCONTROL_SBSIZE_1        /**< \brief  Դͻ������������ SIZE = 1   */
#define AW_DMA_CCONTROL_SBSIZE_4    AMHW_DMA_CCONTROL_SBSIZE_4        /**< \brief  Դͻ������������ SIZE = 4   */
#define AW_DMA_CCONTROL_SBSIZE_8 	AMHW_DMA_CCONTROL_SBSIZE_8 	      /**< \brief  Դͻ������������ SIZE = 8   */
#define AW_DMA_CCONTROL_SBSIZE_16   AMHW_DMA_CCONTROL_SBSIZE_16       /**< \brief  Դͻ������������ SIZE = 16  */
#define AW_DMA_CCONTROL_SBSIZE_32   AMHW_DMA_CCONTROL_SBSIZE_32       /**< \brief  Դͻ������������ SIZE = 32  */
#define AW_DMA_CCONTROL_SBSIZE_64   AMHW_DMA_CCONTROL_SBSIZE_64       /**< \brief  Դͻ������������ SIZE = 64  */
#define AW_DMA_CCONTROL_SBSIZE_128  AMHW_DMA_CCONTROL_SBSIZE_128      /**< \brief  Դͻ������������ SIZE = 128 */
#define AW_DMA_CCONTROL_SBSIZE_256  AMHW_DMA_CCONTROL_SBSIZE_256      /**< \brief  Դͻ������������ SIZE = 256 */

/**
 * \brief Ŀ��ͻ�������С
 */
#define AW_DMA_CCONTROL_DBSIZE_1    AMHW_DMA_CCONTROL_DBSIZE_1     /**< \brief  Ŀ��ͻ������������ SIZE = 1   */
#define AW_DMA_CCONTROL_DBSIZE_4 	AMHW_DMA_CCONTROL_DBSIZE_4 	   /**< \brief  Ŀ��ͻ������������ SIZE = 4   */
#define AW_DMA_CCONTROL_DBSIZE_8    AMHW_DMA_CCONTROL_DBSIZE_8 	   /**< \brief  Ŀ��ͻ������������ SIZE = 8   */
#define AW_DMA_CCONTROL_DBSIZE_16   AMHW_DMA_CCONTROL_DBSIZE_16    /**< \brief  Ŀ��ͻ������������ SIZE = 16  */
#define AW_DMA_CCONTROL_DBSIZE_32   AMHW_DMA_CCONTROL_DBSIZE_32    /**< \brief  Ŀ��ͻ������������ SIZE = 32  */
#define AW_DMA_CCONTROL_DBSIZE_64   AMHW_DMA_CCONTROL_DBSIZE_64    /**< \brief  Ŀ��ͻ������������ SIZE = 64  */
#define AW_DMA_CCONTROL_DBSIZE_128  AMHW_DMA_CCONTROL_DBSIZE_128   /**< \brief  Ŀ��ͻ������������ SIZE = 128 */
#define AW_DMA_CCONTROL_DBSIZE_256  AMHW_DMA_CCONTROL_DBSIZE_256   /**< \brief  Ŀ��ͻ������������ SIZE = 256 */

/**
 * \brief Դ�������ݿ��
 */
#define AW_DMA_CCONTROL_SWIDTH_8BIT   AMHW_DMA_CCONTROL_SWIDTH_8BIT   /**< \brief  8-bit ���ݿ��  */
#define AW_DMA_CCONTROL_SWIDTH_16BIT  AMHW_DMA_CCONTROL_SWIDTH_16BIT  /**< \brief 16-bit ���ݿ��  */
#define AW_DMA_CCONTROL_SWIDTH_32BIT  AMHW_DMA_CCONTROL_SWIDTH_32BIT  /**< \brief 32-bit ���ݿ��  */

/**
 * \brief Ŀ�괫�����ݿ��
 */
#define AW_DMA_CCONTROL_DWIDTH_8BIT   AMHW_DMA_CCONTROL_DWIDTH_8BIT    /**< \brief  8-bit ���ݿ��  */
#define AW_DMA_CCONTROL_DWIDTH_16BIT  AMHW_DMA_CCONTROL_DWIDTH_16BIT   /**< \brief 16-bit ���ݿ��  */
#define AW_DMA_CCONTROL_DWIDTH_32BIT  AMHW_DMA_CCONTROL_DWIDTH_32BIT   /**< \brief 32-bit ���ݿ��  */

/**
 * \brief �����Դ��ַ����
 */
#define AW_DMA_CCONTROL_SI_DISABLE  AMHW_DMA_CCONTROL_SI_DISABLE        /**< \brief Դ��ַ������    */
#define AW_DMA_CCONTROL_SI_ENABLE   AMHW_DMA_CCONTROL_SI_ENABLE         /**< \brief Դ��ַ����      */
                                      
/**                                  
 * \brief �����Ŀ���ַ����         
 */                                  
#define AW_DMA_CCONTROL_DI_DISABLE  AMHW_DMA_CCONTROL_DI_DISABLE        /**< \brief Ŀ���ַ������  */
#define AW_DMA_CCONTROL_DI_ENABLE   AMHW_DMA_CCONTROL_DI_ENABLE         /**< \brief Ŀ���ַ����    */
                                     
/**                                  
 * \brief ָ��ģʽ�·���AHB����      
 */                                  
#define AW_DMA_CCONTROL_PROT1_DISABLE  AMHW_DMA_CCONTROL_PROT1_DISABLE      /**< \brief �û�ģʽ��    */
#define AW_DMA_CCONTROL_PROT1_ENABLE   AMHW_DMA_CCONTROL_PROT1_ENABLE       /**< \brief ��Ȩģʽ��    */
                                     
/**                                  
 * \brief AHB�����Ƿ�ɻ���          
 */                                  
#define AW_DMA_CCONTROL_PROT2_DISABLE  AMHW_DMA_CCONTROL_PROT2_DISABLE      /**< \brief ���ɻ���  */
#define AW_DMA_CCONTROL_PROT2_ENABLE   AMHW_DMA_CCONTROL_PROT2_ENABLE       /**< \brief �ɻ���    */

/**
 * \brief AHB�ӻ�����AHB����ʱ�������Ƿ���Cache����
 */
#define AW_DMA_CCONTROL_PROT3_DISABLE  AMHW_DMA_CCONTROL_PROT3_DISABLE      /**< \brief ���ɻ���  */
#define AW_DMA_CCONTROL_PROT3_ENABLE   AMHW_DMA_CCONTROL_PROT3_ENABLE       /**< \brief �ɻ���    */

/**
 * \brief ͨ���ն˼����ж�ʹ��
 */
#define AW_DMA_CCONTROL_ITC_DISABLE  AMHW_DMA_CCONTROL_ITC_DISABLE       /**< \brief �ն˼����ж�ʧ��  */
#define AW_DMA_CCONTROL_ITC_ENABLE   AMHW_DMA_CCONTROL_ITC_ENABLE        /**< \brief �ն˼����ж�ʹ��  */

/** @} */

/**
 * \name Channel transfer interrupt flags
 * @{
 */

#define AW_DMA_INT_FLG          AMDR_DMA_INTTC                   /** \brief Interrupt flag     */
#define AW_DMA_INT_FLG_ERR      AMDR_DMA_INTERR                  /** \brief Error interrupt flag */

/** @} */

/** \brief DMA ͨ������������ */
typedef amhw_dma_lli_t  aw_lpc17xx_dma_desc_t;

/** \brief DMA �첽�ص��������� */
typedef amdr_pfn_dma_isr_t   aw_pfunc_dma_isr_t;


/**
 * \brief DMA ͨ������
 *
 * ����DMA�Ĵ���ͨ����
 *
 * \param[in] chan  : DMA ͨ���ţ����� \ref grp_dma_channel
 * \param[in] src   : Դ������������ѡ�񣬲μ�
 *                    \ref grp_dma_chan_conn_req_num
 * \param[in] des   : Ŀ��������������ѡ�񣬲μ�
 *                    \ref grp_dma_chan_conn_req_num
 * \param[in] flags : ������Ϣ�������ò������л�����ã����ò�������
 *                    \ref grp_amh_dma_chan_setup_flags
 *
 * \retval  AW_OK   : DMA ͨ�����óɹ� 
 */
aw_err_t aw_lpc17xx_dma_chan_setup(int      chan,
		                           uint8_t  src,
		                           uint8_t  des,
		                           uint32_t flags);

/**
 * \brief ���� DMA ͨ����������
 *
 * \param[in] p_desc   : ͨ��������
 * \param[in] src_addr : Դ�����׵�ַ
 * \param[in] dst_addr : Ŀ�������׵�ַ
 * \param[in] nbytes   : �����ֽ���
 * \param[in] flags    : ����������Ϣ�������ò������л�����ã����ò�������
 *                       \ref grp_amh_dma_chan_xfercfg_flags 
 *
 * \retval  AW_OK      : �����������ɹ�
 * \retval -AM_EINVAL  : ��Ч����
 * 
 */
aw_err_t aw_lpc17xx_dma_desc_build(aw_lpc17xx_dma_desc_t *p_desc,
                                   uint32_t               src_addr,
                                   uint32_t               dst_addr,
                                   uint32_t               nbytes,
                                   uint32_t               flags);

/**
 * \brief DMA �첽����
 * 
 * ���������ʱ�������û��Զ���Ļص������� *
 * \param[in] chan           : DMA ͨ���ţ��μ� \ref grp_dma_channel
 * \param[in] p_desc         : ͨ��������
 * \param[in] pfunc_callback : ������ɻص�����
 * \param[in] p_arg          : �ص�������һ������
 * 
 * \retval  AW_OK            : ���������ɹ�
 * 
 * \note �ص�����������Ϊ��void (*)(void *p_arg, void *p_flg), ���һ������p_arg
 *       ���û����룬����Ӧ�ú����ĵ�4������P_arg����2������p_flg�ɵײ���������
 *       ���û�ʹ��.
 *
 * \par ����
 * \code 
 * void dma_isr (void *p_arg, void *p_flg)  //DMA �жϴ�����
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
 * \brief DMA ͬ������
 *
 * \param[in] chan   : DMA ͨ����,�μ�\ref grp_dma_channel
 * \param[in] p_desc : ͨ��������
 *
 * \retval AW_OK     : ����ɹ�
 *
 *
 */
aw_err_t aw_lpc17xx_dma_tran_sync(int chan, aw_lpc17xx_dma_desc_t *p_desc);

/**
 * \brief ��������������
 *
 * \param[in] p_desc : ����������
 * \param[in] p_next : ��ָ�������������
 *
 * \retval AW_OK     : ���ӳɹ�
 *
 * \par ����1
 * \code 
 * __align(16) aw_lpc17xx_dma_desc_t reload_desc[2];
 *
 * aw_lpc17xx_dma_desc_link(&reload_desc[0], &reload_desc[1]);
 * aw_lpc17xx_dma_desc_link(&reload_desc[1], &reload_desc[0]);
 * \endcode
 *
 * \par ����2
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
 * \brief ֹͣ DMA ͨ������
 *
 * ֻ���ڸ�ͨ��no-busyʱ����ֹͣ��
 *
 * \param[in] chan : DMA ͨ����, �μ� \ref grp_dma_channel
 *
 * \retval AW_OK   : �����ɹ���
 */
aw_err_t aw_lpc17xx_dma_tran_stop(int chan);


/** @} grp_aw_if_lpc17xx_dma */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_LPC17XX_DMA_H */

/* end of file */
