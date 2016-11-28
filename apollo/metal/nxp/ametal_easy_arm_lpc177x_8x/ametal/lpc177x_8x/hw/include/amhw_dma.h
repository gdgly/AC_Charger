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
 * \brief DMAӲ�������ӿ�
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

/** \brief DMA ͨ������ */
#define AMHW_DMA_CHAN_CNT           8
	
/**
 * \name DMA ͨ�����
 * @{
 */
#define DMA_CHAN_0                0               /**< \brief DMAͨ��0  */
#define DMA_CHAN_1                1               /**< \brief DMAͨ��1  */
#define DMA_CHAN_2                2               /**< \brief DMAͨ��2  */
#define DMA_CHAN_3                3               /**< \brief DMAͨ��3  */
#define DMA_CHAN_4                4               /**< \brief DMAͨ��4  */
#define DMA_CHAN_5                5               /**< \brief DMAͨ��5  */
#define DMA_CHAN_6                6               /**< \brief DMAͨ��6  */
#define DMA_CHAN_7                7               /**< \brief DMAͨ��7  */

/** @} */

/**
 * \brief DMA ͨ���Ĵ����ṹ��
 */
typedef struct amhw_dma_chan {
    __IO uint32_t srcaddr;          /**< \brief DMA Դ��ַ�Ĵ���   */
    __IO uint32_t destaddr;         /**< \brief DMA Ŀ���ַ�Ĵ��� */
    __IO uint32_t lli;              /**< \brief DMA ������Ĵ���   */
    __IO uint32_t control;          /**< \brief ���ƼĴ���         */
    __IO uint32_t config;           /**< \brief ���üĴ���         */
    __IO uint32_t reserved[3];      /**< \brief ����               */
} amhw_dma_chan_t;

/**
 * \brief DMA �������Ĵ�����ṹ�� 
 */
typedef struct amhw_dma {
    __I  uint32_t intstat;          /**< \brief DMA�ж�״̬�Ĵ���              */
    __I  uint32_t inttcstat;        /**< \brief DMA�ж��ն˼�������״̬�Ĵ���  */
    __O  uint32_t inttcclear;       /**< \brief DMA�ж��ն˼�����������Ĵ���  */
    __I  uint32_t interrstat;       /**< \brief DMA�жϴ���״̬�Ĵ���          */
    __O  uint32_t interrclear;      /**< \brief DMA�жϴ�������Ĵ���          */
    __I  uint32_t rawinttcstat;     /**< \brief DMAԭʼ�ж��ն˼���״̬�Ĵ���  */
    __I  uint32_t rawinterrstat;    /**< \brief DMAԭʼ�����ж�״̬�Ĵ���      */
    __I  uint32_t enbldchns;        /**< \brief DMAʹ��ͨ���Ĵ���                    */
    __IO uint32_t softbreq;         /**< \brief DMA���ͻ������Ĵ���          */
    __IO uint32_t softsreq;         /**< \brief DMA�����������Ĵ���          */
    __IO uint32_t softlbreq;        /**< \brief DMA������һ��ͻ������Ĵ���  */
    __IO uint32_t softlsreq;        /**< \brief DMA������һ����������Ĵ���  */
    __IO uint32_t config;           /**< \brief DMA���üĴ���                  */
    __IO uint32_t sync;             /**< \brief DMAͬ���Ĵ���                  */
    __IO uint32_t reserved[50];     /**< \brief ����                           */
    amhw_dma_chan_t chan[AMHW_DMA_CHAN_CNT];   /**< \brief DMAͨ���Ĵ���       */
} amhw_dma_t;

/**
 * \brief DMA ������
 * \attention �������ַ������16�ֽڶ���
 */
typedef struct amhw_dma_lli {
    volatile uint32_t srcaddr;      /**< \brief Դ��ַ       */
    volatile uint32_t dstaddr;      /**< \brief Ŀ���ַ     */
    volatile uint32_t next;         /**< \brief ��һ�������� */
    volatile uint32_t control;      /**< \brief ���ƼĴ���	 */
} amhw_dma_lli_t;

/**
 * \brief AHB�����ֽ�˳������ģʽ����
 */
typedef enum amhw_dma_endian_mode {
    AMHW_DMA_LITTLE_ENDIAN ,       /**< \brief С��ģʽ      */
    AMHW_DMA_BIG_ENDIAN	           /**< \brief ���ģʽ      */
} amhw_dma_endian_mode_t;

/**
 * \brief ����������ź�
 */
typedef enum amhw_dma_req_sem {
    AMHW_DMA_SOFT_BREQ,	         /**< \brief DMA���ͻ������          */
    AMHW_DMA_SOFT_SREQ,	         /**< \brief DMA�����������          */
    AMHW_DMA_SOFT_LBREQ,         /**< \brief DMA������һ��ͻ������  */
    AMHW_DMA_SOFT_LSREQ	         /**< \brief DMA������һ�ε�������  */
} amhw_dma_req_sem_t;

/**
 * \name ���贫��������
 * \anchor grp_amhw_dma_chan_req_line
 * @{
 */
#define AMHW_DMA_CHAN_REQ_NONE_MAT00       (0UL)    /**< \brief �������T0 ƥ��0 */
#define AMHW_DMA_CHAN_REQ_SDCARD_MAT01     (1UL)    /**< \brief SD_CARD��T0ƥ��1 */
#define AMHW_DMA_CHAN_REQ_SSP0TX_MAT10     (2UL)    /**< \brief SSP0 TX��T1ƥ��0 */
#define AMHW_DMA_CHAN_REQ_SSP0RX_MAT11     (3UL)    /**< \brief SSP0 RX��T1ƥ��1 */
#define AMHW_DMA_CHAN_REQ_SSP1TX_MAT20     (4UL)    /**< \brief SSP1 TX��T2ƥ��0 */
#define AMHW_DMA_CHAN_REQ_SSP1RX_MAT21     (5UL)    /**< \brief SSP1 RX��T2ƥ��1 */
#define AMHW_DMA_CHAN_REQ_SSP2TX_I2SCH0    (6UL)    /**< \brief SSP2 TX��I2S CH0 */
#define AMHW_DMA_CHAN_REQ_SSP2RX_I2SCH1    (7UL)    /**< \brief SSP2 RX��I2S CH1 */
#define AMHW_DMA_CHAN_REQ_ADC              (8UL)    /**< \brief ADC      */
#define AMHW_DMA_CHAN_REQ_DAC              (9UL)    /**< \brief DAC      */
#define AMHW_DMA_CHAN_REQ_UART0TX_UART3TX  (10UL)   /**< \brief UART0 TX��UART3 TX */
#define AMHW_DMA_CHAN_REQ_UART0RX_UART3RX  (11UL)   /**< \brief UART0 RX��UART3 RX */
#define AMHW_DMA_CHAN_REQ_UART1TX_UART4TX  (12UL)   /**< \brief UART1 TX��UART4 TX */
#define AMHW_DMA_CHAN_REQ_UART1RX_UART4RX  (13UL)   /**< \brief UART1 RX��UART4 RX */
#define AMHW_DMA_CHAN_REQ_UART2TX_MAT30    (14UL)   /**< \brief UART2 TX��T3ƥ��0*/
#define AMHW_DMA_CHAN_REQ_UART2RX_MAT31    (15UL)   /**< \brief UART2 TX��T3ƥ��1*/

/** @} */

/**
 * \brief DMA��������ѡ������Ϊ0
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \param[in] line        : DMA��������������,�μ�
 *                          \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \return    ��
 */
am_static_inline
void amhw_dma_req_select0 (amhw_syscon_t *p_hw_syscon,
                           uint8_t        line)
{
    p_hw_syscon->dmareqsel &= ~AM_BIT(line);
}

/**
 * \brief DMA��������ѡ������Ϊ1
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \param[in] line        : DMA��������������,�μ�
 *                          \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \return    ��
 */
am_static_inline
void amhw_dma_req_select1 (amhw_syscon_t *p_hw_syscon,
                           uint8_t        line)
{
    p_hw_syscon->dmareqsel |= AM_BIT(line);
}

/**
 * \brief ʹ��DMA������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_dma_enable (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->config |= AM_BIT(0);
}

/**
 * \brief ����DMA������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_dma_disable (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->config &= ~AM_BIT(0);
}

/**
 * \brief AHB�����ֽ�˳����ģʽ
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_dma_big_endian (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->config |= AM_BIT(1);
}

/**
 * \brief AHB�����ֽ�˳��С��ģʽ
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_dma_little_endian (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->config &= ~AM_BIT(1);
}

/**
 * \brief ��ȡDMA�ж�״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    �ж�״̬��
 */
am_static_inline
uint32_t amhw_dma_int_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intstat;
}

/**
 * \brief ��ȡDMA�ж��ն˼�������״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    DMA�ж��ն˼�������״̬
 */
am_static_inline
uint32_t amhw_dma_inttc_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->inttcstat;
}

/**
 * \brief ͨ����������ն˼����жϱ�־
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] mask     : bit[7:0] ��ӦDMAͨ�� n, �ñ����Ϊ������ NTA ���Ӧ
 * \return    ��
 */
am_static_inline
void amhw_dma_inttc_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->inttcclear = mask ;
}

/**
 * \brief ���DMAָ��ͨ���ж��ն˼�������״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_inttc_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->inttcclear |= AM_BIT(chan) ;
}

/**
 * \brief ��ȡDMA�жϴ���״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    DMA�жϴ���״̬
 */
am_static_inline
uint32_t amhw_dma_interr_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->interrstat;
}

/**
 * \brief ͨ����������жϴ����־
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] mask     : bit[7:0] ��ӦDMAͨ�� n, �ñ����Ϊ������ NTA ���Ӧ
 * \return    ��
 */
am_static_inline
void amhw_dma_interr_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->interrclear = mask ;
}

/**
 * \brief ���DMA�жϴ���״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_interr_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->interrclear |= AM_BIT(chan) ;
}

/**
 * \brief ��ȡDMAԭʼ�ж��ն˼���״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    DMAԭʼ�ж��ն˼���״̬
 */
am_static_inline
uint32_t amhw_dma_rawinttc_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->rawinttcstat;
}

/**
 * \brief ��ȡDMAԭʼ�����ж�״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    DMAԭʼ�����ж�״̬
 */
am_static_inline
uint32_t amhw_dma_rawinterr_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->rawinterrstat;
}

/**
 * \brief ��ȡDMAʹ��ͨ��״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    DMAʹ��ͨ��״̬
 */
am_static_inline
uint32_t amhw_dma_enabled_channels_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->enbldchns;
}

/**
 * \brief ʹ���������ָ��Դ��DMAͻ������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line     : DMA�����߻����蹦��
 * \return    ��
 */
am_static_inline
void amhw_dma_softb_req_enable (amhw_dma_t   *p_hw_dma, 
                                unsigned int line)
{
    p_hw_dma->softbreq |= AM_BIT(line);
}

/**
 * \brief ָ��Դ�Ƿ�����������DMAͻ������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line     : DMA���������ţ��μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \retval  ��0        : ָ��Դline��������DMAͻ������
 * \retval  0          : ��������
 */
am_static_inline
uint32_t amhw_dma_softb_req_active (amhw_dma_t  *p_hw_dma, 
                                    unsigned int line)
{
    return p_hw_dma->softbreq & AM_BIT(line);
}

/**
 * \brief ʹ���������ָ��Դ��DMA��������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line 	   : DMA����������,�μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \return    ��
 */
am_static_inline
void amhw_dma_softs_req_enable (amhw_dma_t   *p_hw_dma, 
                                unsigned int line)
{
    p_hw_dma->softsreq |= AM_BIT(line);
}

/**
 * \brief ָ��Դ�Ƿ�����������DMA���δ���
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line     : DMA���������ţ��μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \retval    ��0      : ָ��Դline��������DMA���δ���
 * \retval    0        : ��������
 */
am_static_inline
uint32_t amhw_dma_softs_req_active (amhw_dma_t  *p_hw_dma, 
	                                unsigned int line)
{
    return p_hw_dma->softsreq & AM_BIT(line);
}

/**
 * \brief ʹ���������ָ��Դ��DMA���һ��ͻ������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line     : DMA���������ţ��μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \return    ��
 */
am_static_inline
void amhw_dma_softlb_req_enable (amhw_dma_t  *p_hw_dma, 
                                 unsigned int line)
{
    p_hw_dma->softlbreq |= AM_BIT(line);
}

/**
 * \brief ָ��Դ�Ƿ�����������DMAͻ������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line     : DMA���������ţ��μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \retval    ��0      : ָ��Դline�����������һ��DMAͻ������
 * \retval    0        : ��������
 */
am_static_inline
uint32_t amhw_dma_softlb_req_active (amhw_dma_t  *p_hw_dma, 
                                     unsigned int line)
{
    return p_hw_dma->softlbreq & AM_BIT(line);
}

/**
 * \brief ʹ���������ָ��Դ��DMA���һ����������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line     : DMA���������ţ��μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_softls_req_enable (amhw_dma_t  *p_hw_dma, 
                                 unsigned int line)
{
    p_hw_dma->softlsreq |= AM_BIT(line);
}

/**
 * \brief ָ��Դ�Ƿ��������������һ��DMA���δ���
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line     : DMA���������ţ��μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 * \retval  ��0        : ָ��Դline�����������һ��DMA���δ���
 * \retval  0          : ��������
 */
am_static_inline
uint32_t amhw_dma_softls_req_active (amhw_dma_t  *p_hw_dma, 
                                     unsigned int line)
{
    return p_hw_dma->softlsreq & AM_BIT(line);
}

/**
 * \brief ����DMA�����źŵ�ͬ���߼�
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line 	   : DMA���������ţ��μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 */
am_static_inline
void amhw_dma_sync_disable (amhw_dma_t  *p_hw_dma,
                            unsigned int line)
{
    p_hw_dma->sync |= AM_BIT(line);
}

/**
 * \brief ʹ��DMA�����źŵ�ͬ���߼�
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] line 	   : DMA���������ţ��μ�
 *                       \ref grp_amhw_dma_chan_req_line"Channel Connect Request"
 */
am_static_inline
void amhw_dma_sync_enable (amhw_dma_t  *p_hw_dma,
                           unsigned int line)
{
    p_hw_dma->sync &= ~AM_BIT(line);
}


/**
 * \brief ���õ�ǰҪ�����Դ��ַ
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] addr     : Դ��ַ                    
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_srcaddr_set (amhw_dma_t  *p_hw_dma, 
                                unsigned int chan, 
                                uint32_t     addr)
{
    p_hw_dma->chan[chan].srcaddr = addr;
}

/**
 * \brief ���õ�ǰҪ�����Ŀ���ַ
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] addr     : Դ��ַ                    
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_destaddr_set (amhw_dma_t  *p_hw_dma, 
                                 unsigned int chan, 
                                 uint32_t     addr)
{
    p_hw_dma->chan[chan].destaddr = addr;
}

/**
 * \brief ����������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] lli      : �¸��������ַ        
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_lli_set (amhw_dma_t  *p_hw_dma, 
                            unsigned int chan, 
                            uint32_t     lli)
{
    p_hw_dma->chan[chan].lli = lli;
}

/**
 * \name ����ͨ��������Ϣ
 * \anchor grp_amhw_dma_chan_control_flags
 * @{
 */

#define AMHW_DMA_CCONTROL_SBSIZE_1    AM_SBF(0, 12)    /**< \brief  Դͻ������������ SIZE = 1   */
#define AMHW_DMA_CCONTROL_SBSIZE_4    AM_SBF(1, 12)    /**< \brief  Դͻ������������ SIZE = 4   */
#define AMHW_DMA_CCONTROL_SBSIZE_8 	  AM_SBF(2, 12)    /**< \brief  Դͻ������������ SIZE = 8   */
#define AMHW_DMA_CCONTROL_SBSIZE_16   AM_SBF(3, 12)    /**< \brief  Դͻ������������ SIZE = 16  */
#define AMHW_DMA_CCONTROL_SBSIZE_32   AM_SBF(4, 12)    /**< \brief  Դͻ������������ SIZE = 32  */
#define AMHW_DMA_CCONTROL_SBSIZE_64   AM_SBF(5, 12)    /**< \brief  Դͻ������������ SIZE = 64  */
#define AMHW_DMA_CCONTROL_SBSIZE_128  AM_SBF(6, 12)    /**< \brief  Դͻ������������ SIZE = 128 */
#define AMHW_DMA_CCONTROL_SBSIZE_256  AM_SBF(7, 12)    /**< \brief  Դͻ������������ SIZE = 256 */

#define AMHW_DMA_CCONTROL_DBSIZE_1     AM_SBF(0, 15)   /**< \brief  Ŀ��ͻ������������ SIZE = 1   */
#define AMHW_DMA_CCONTROL_DBSIZE_4 	   AM_SBF(1, 15)   /**< \brief  Ŀ��ͻ������������ SIZE = 4   */
#define AMHW_DMA_CCONTROL_DBSIZE_8 	   AM_SBF(2, 15)   /**< \brief  Ŀ��ͻ������������ SIZE = 8   */
#define AMHW_DMA_CCONTROL_DBSIZE_16    AM_SBF(3, 15)   /**< \brief  Ŀ��ͻ������������ SIZE = 16  */
#define AMHW_DMA_CCONTROL_DBSIZE_32    AM_SBF(4, 15)   /**< \brief  Ŀ��ͻ������������ SIZE = 32  */
#define AMHW_DMA_CCONTROL_DBSIZE_64    AM_SBF(5, 15)   /**< \brief  Ŀ��ͻ������������ SIZE = 64  */
#define AMHW_DMA_CCONTROL_DBSIZE_128   AM_SBF(6, 15)   /**< \brief  Ŀ��ͻ������������ SIZE = 128 */
#define AMHW_DMA_CCONTROL_DBSIZE_256   AM_SBF(7, 15)   /**< \brief  Ŀ��ͻ������������ SIZE = 256 */

#define AMHW_DMA_CCONTROL_SWIDTH_8BIT      AM_SBF(0, 18)   	/**< \brief  8-bit ���ݿ��  */
#define AMHW_DMA_CCONTROL_SWIDTH_16BIT     AM_SBF(1, 18)   	/**< \brief 16-bit ���ݿ��  */
#define AMHW_DMA_CCONTROL_SWIDTH_32BIT     AM_SBF(2, 18)   	/**< \brief 32-bit ���ݿ��  */

#define AMHW_DMA_CCONTROL_DWIDTH_8BIT      AM_SBF(0, 21)   	/**< \brief  8-bit ���ݿ�� */
#define AMHW_DMA_CCONTROL_DWIDTH_16BIT     AM_SBF(1, 21)   	/**< \brief 16-bit ���ݿ��  */
#define AMHW_DMA_CCONTROL_DWIDTH_32BIT     AM_SBF(2, 21)  	/**< \brief 32-bit ���ݿ��  */

#define AMHW_DMA_CCONTROL_SI_DISABLE    0                 /**< \brief Դ��ַ������    */
#define AMHW_DMA_CCONTROL_SI_ENABLE     AM_SBF(1, 26) 	  /**< \brief Դ��ַ����      */

#define AMHW_DMA_CCONTROL_DI_DISABLE    0                 /**< \brief Ŀ���ַ������  */
#define AMHW_DMA_CCONTROL_DI_ENABLE     AM_SBF(1, 27)     /**< \brief Ŀ���ַ����    */

#define AMHW_DMA_CCONTROL_PROT1_DISABLE   0                /**< \brief �û�ģʽ��    */
#define AMHW_DMA_CCONTROL_PROT1_ENABLE    AM_SBF(1, 28)    /**< \brief ��Ȩģʽ��    */

#define AMHW_DMA_CCONTROL_PROT2_DISABLE   0                /**< \brief ���ɻ���  */
#define AMHW_DMA_CCONTROL_PROT2_ENABLE    AM_SBF(1, 29)    /**< \brief �ɻ���    */

#define AMHW_DMA_CCONTROL_PROT3_DISABLE   0                 /**< \brief ���ɻ���  */
#define AMHW_DMA_CCONTROL_PROT3_ENABLE    AM_SBF(1, 30)   	/**< \brief �ɻ���    */

#define AMHW_DMA_CCONTROL_ITC_DISABLE   0                   /**< \brief �ն˼����ж�ʧ��  */
#define AMHW_DMA_CCONTROL_ITC_ENABLE    AM_SBF(1ul, 31)     /**< \brief �ն˼����ж�ʹ��  */

/** @} */

#define AMHW_DMA_CCONTROL_TRANS_SIZE(size) (0x0fff & (size)) /**< \brief  �������ݴ�С   */

/**
 * \brief DMA ͨ��������Ϣ����
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] flags    : ���ò������μ�
 *                       \ref grp_amhw_dma_chan_control_flags 
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_control_set (amhw_dma_t  *p_hw_dma, 
                                unsigned int chan, 
                                uint32_t     flags)
{
    p_hw_dma->chan[chan].control = flags;
}

/**
 * \brief ʹ��DMAָ��ͨ���ն˼����ж�
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan 	   : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 */
am_static_inline
void amhw_dma_chan_inttc_enable (amhw_dma_t  *p_hw_dma,
                                 unsigned int chan)
{
    p_hw_dma->chan[chan].control |= AM_BIT(31);
}

/**
 * \brief ʧ��DMAָ��ͨ���ն˼����ж�
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 */
am_static_inline
void amhw_dma_chan_inttc_disable (amhw_dma_t  *p_hw_dma,
                                  unsigned int chan)
{
    p_hw_dma->chan[chan].control &= ~AM_BIT(31);
}


/**
 * \name ����ͨ�����ò���
 * \anchor grp_amhw_dma_chan_config_flags
 * @{
 */

#define AMHW_DMA_CCONFIG_CHAN_ENABLE   AM_SBF(1, 0)  /**< \brief DMAͨ��ʹ��     */
/**
 * \brief DMA����Դ����,valֵΪ�μ�
 *         \ref grp_amhw_dma_chan_req_line "Channel Connect Request"
 */
#define AMHW_DMA_CCONFIG_SRCPER(val)    AM_SBF(((val) & 0x1F), 1)

/**
 * \brief DMA����Դ����,valֵΪ�μ�
 *         \ref grp_amhw_dma_chan_req_line "Channel Connect Request"
 */
#define AMHW_DMA_CCONFIG_DESPER(val)   AM_SBF(((val) & 0x1F), 6)

/** \brief �洢�����洢��  */
#define AMHW_DMA_CCONFIG_TRANTYPE_M2M	    AM_SBF(0, 11)
/** \brief �洢��������     */
#define AMHW_DMA_CCONFIG_TRANTYPE_M2P       AM_SBF(1, 11)
/** \brief ���赽�洢��     */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2M       AM_SBF(2, 11)
/** \brief Դ���赽Ŀ������ */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2P       AM_SBF(3, 11)
/** \brief �洢�����洢��(Ŀ���������) */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2P_DEST  AM_SBF(4, 11)
/** \brief �洢�������� (Ŀ���������) */
#define AMHW_DMA_CCONFIG_TRANTYPE_M2P_DEST  AM_SBF(5, 11)
/** \brief ���赽�洢��(Դ�������)   */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2M_SRC   AM_SBF(6, 11)
/** \brief Դ���赽Ŀ������ (Դ�������) */
#define AMHW_DMA_CCONFIG_TRANTYPE_P2P_SRC   AM_SBF(7, 11)

#define AMHW_DMA_CCONFIG_IE_VALID      AM_SBF(1, 14)   /**< \brief �жϴ������� 	*/
#define AMHW_DMA_CCONFIG_IE_INVALID    0	           /**< \brief �жϴ�������    */

#define AMHW_DMA_CCONFIG_ITC_VALID	   AM_SBF(1, 15)   /**< \brief �жϴ�������  */
#define AMHW_DMA_CCONFIG_ITC_INVALID   0               /**< \brief �жϴ�������    */

#define AMHW_DMA_CCONFIG_TRANS_LOCK    AM_SBF(1, 16)   /**< \brief ��������     */
#define AMHW_DMA_CCONFIG_TRANS_UNLOCK  0               /**< \brief ���䲻����   */

#define AMHW_DMA_CCONFIG_HALT          AM_SBF(1, 18)   /**< \brief ���Ժ���Դ����     */

#define AMHW_DMA_CCONFIG_REQ_ENABLE    0               /**< \brief  DMA��������ʹ��   */
/** @} */

/**
 * \brief DMA ͨ������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] flags    : ���ò������μ�
 *                       \ref grp_amhw_dma_chan_config_flags "Channel Configuration Flags"
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_config_set (amhw_dma_t  *p_hw_dma, 
                               unsigned int chan, 
                               uint32_t     flags)
{
    p_hw_dma->chan[chan].config = flags;
}

/**
 * \brief ʹ��DMAָ��ͨ��
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_enable (amhw_dma_t  *p_hw_dma,
                           unsigned int chan)
{
    p_hw_dma->chan[chan].config |= AM_BIT(0);
}

/**
 * \brief ʧ��DMAָ��ͨ��
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
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
 * \brief ����ָ��ͨ���жϴ���
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_interr_mask (amhw_dma_t  *p_hw_dma,
                                unsigned int chan)
{
    p_hw_dma->chan[chan].config &= ~AM_BIT(14);
}

/**
 * \brief ����ָ��ͨ���ն˼����ж�
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_inttc_mask (amhw_dma_t  *p_hw_dma,
                               unsigned int chan)
{
    p_hw_dma->chan[chan].config &= ~AM_BIT(15);
}

/**
 * \brief ����ָ��ͨ������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_lock_trans (amhw_dma_t  *p_hw_dma,
                               unsigned int chan)
{
    p_hw_dma->chan[chan].config |= AM_BIT(16);
}

/**
 * \brief ָ��ͨ����FIFO�Ƿ�������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \retval    ��0      : ͨ����FIFO��������
 * \retval    0        : ͨ����FIFOû������
 */
am_static_inline
uint32_t amhw_dma_chan_fifo_active (amhw_dma_t  *p_hw_dma, 
                                    unsigned int chan)
{
    return p_hw_dma->chan[chan].config & AM_BIT(17);
}

/**
 * \brief ����ָ��ͨ��DMA����
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan 	   : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_req_ignore (amhw_dma_t  *p_hw_dma, 
                               unsigned int chan)
{
    p_hw_dma->chan[chan].config |= AM_BIT(18);
}

/**
 * \brief ʹ��ָ��ͨ��DMA����
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ��, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \return    ��
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

