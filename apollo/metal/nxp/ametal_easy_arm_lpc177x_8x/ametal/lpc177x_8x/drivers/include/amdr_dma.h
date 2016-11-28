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
 * \brief DMA����������ӿ�
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
 * \name ͨ�������жϱ�־ 
 * \anchor amdr_dma_chan_cfg_flags
 * @{
 */
	
#define AMDR_DMA_INTTC         0     /**< \brief �ն˼����жϱ�־   */
#define AMDR_DMA_INTERR        1     /**< \brief �����жϱ�־       */

/** @} */	

/**
 * \name DMA ͨ������������
 * \anchor grp_dma_chan_conn_req_num
 * @{
 */
#define AMDR_DMA_CONN_NONE             ((0UL))         /** ������        */
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


/** \brief DMA�жϻص��������� */
typedef void (*amdr_pfn_dma_isr_t)(void *p_arg, void *p_flg);	
	
/** \brief DMA�жϻص�������Ϣ */
struct amdr_dma_int_info {
    
    /** \brief DMA�����ص����� */
    amdr_pfn_dma_isr_t  pfn_isr;

    /** \brief �ص������ĵ�һ����ڲ��� */
    void               *p_arg;
};
	
/** \brief DMA�豸��Ϣ */
typedef struct amdr_dma_devinfo {
    
    /** \brief ָ��DMA�Ĵ������ָ�� */
    amhw_dma_t 			   *p_hw_dma;
	
    /** \brief ָ��ϵͳ���ƼĴ������ָ�� */
    amhw_syscon_t 	       *p_hw_syscon;
	
	/** \brief AHB�����ֽ�˳�򣬴�С��ģʽ */
    amhw_dma_endian_mode_t  endian_mode;
	
    /** \brief DMA�жϺ� */
    uint8_t                 inum;
    
} amdr_dma_devinfo_t;

/**
 * \brief DMA�豸ʵ��
 */
typedef struct amdr_dma_dev {
    
    /** \brief ָ��DMA�豸��Ϣ��ָ�� */
    const amdr_dma_devinfo_t *p_devinfo;
    
} amdr_dma_dev_t;


/**
 * \brief ͨ����������
 *
 * \param[in] chan  : DMA ͨ����, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] flags : ���ò������μ�
 *                    \ref grp_amhw_dma_chan_config_flags "Channel Configuration Flags".
 * \param[in] src   : Դ������������ѡ�񣬲μ�
 *                    \ref grp_dma_chan_conn_req_num "Channel Connect Request Num"
 * \param[in] des   : Ŀ��������������ѡ�񣬲μ�
 *                    \ref grp_dma_chan_conn_req_num "Channel Connect Request Num"
 * 
 * \retval AM_OK    : ���óɹ� 
 */
int amdr_dma_chan_setup(int chan, uint8_t src, uint8_t des, uint32_t flags);

/**
 * \brief ����������
 *
 * \param[in] chan    : DMA ͨ����, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] p_lli   : ָ��DMA�������ָ��
 *
 * \retval  AM_OK     : �����ɹ� 
 * \retval -AM_EINVAL : ������Ч 
 */
int amdr_dma_chan_lli_startup(int chan, amhw_dma_lli_t *p_lli);

/**
 * \brief ����������
 *
 * \param[in] p_lli    : ������������
 * \param[in] src_addr : Դ���׵�ַ 
 * \param[in] dst_addr : Ŀ����׵�ַ 
 * \param[in] nbytes   : �����ֽ�����ע��Ҫ�롰flags���Ŀ�ȶ�Ӧ 
 * \param[in] flags    : ���ò������μ�
 *                       \ref grp_amhw_dma_chan_control_flags 
 * 
 * \retval  AM_OK      : �����ɹ� 
 * \retval -AM_EINVAL  : ��Ч���� 
 */
int amdr_dma_chan_lli_build(amhw_dma_lli_t *p_lli,
                            uint32_t        src_addr,
                            uint32_t        dst_addr,	
                            uint16_t        nbytes,
                            uint32_t        flags);

/**
 * \brief ��������������
 *
 * \attention �����ַ����4�ֽڶ���
 *
 * \param[in] p_desc : ָ��ǰ�������ָ��
 * \param[in] p_next : ָ����һ���������ָ��
 *
 * \retval  AM_OK    : ���ӳɹ� 
 */
int amdr_dma_lli_link(amhw_dma_lli_t  *p_desc, 
                      amhw_dma_lli_t  *p_next);

/**
 * \brief ��ʼͨ������ 
 * \param[in] chan : DMA ͨ����, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \retval AM_OK   : �����ɹ� 
 */
int amdr_dma_chan_start(int chan);

/**
 * \brief ֹͣͨ������ 
 * \param[in] chan : DMA ͨ����, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \retval AM_OK   : �����ɹ� 
 */
int amdr_dma_chan_stop(int chan);
	
/**
 * \brief ����DMA�ص����� 
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AMDR_DMA_INT* 
 *            (#AMDR_DMA_INTTC)��(#AMDR_DMA_INTERR)
 *
 * \param[in] chan    : DMA ͨ����, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] pfn_isr : �ص�����ָ�� 
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ��� 
 *
 * \retval  AM_OK     : ���ӳɹ� 
 * \retval -AM_EPERM  : �������� 
 */
int amdr_dma_isr_connect(int                 chan,
                         amdr_pfn_dma_isr_t  pfn_isr, 
                         void               *p_arg);

/**
 * \brief ɾ��DMA�ص����������� 
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AMDR_DMA_INT* 
 *            (#AMDR_DMA_INTTC)��(#AMDR_DMA_INTERR)
 *
 * \param[in] chan    : DMA ͨ����, ֵΪ��DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \retval  AM_OK     : ɾ���ɹ� 
 * \retval -AM_EINVAL : �������� 
 */
int amdr_dma_isr_disconnect(int chan);

/**
 * \brief DMA��ʼ��
 *
 * \param[in] p_dev     : ָ��DMA�豸��ָ�� 
 * \param[in] p_devinfo : ָ��DMA�豸��Ϣ��ָ�� 
 *
 * \retval  AM_OK       : ��ʼ���ɹ� 
 */
int amdr_dma_init(amdr_dma_dev_t *p_dev, const amdr_dma_devinfo_t *p_devinfo);


/**
 * \brief DMAȥ��ʼ�� 
 *
 * \param[in] p_dev : ָ��DMA�豸��ָ�� 
 *
 * \return  ��
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
