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
 * \brief  DACӲ�������ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-05-26  snk, first implementation.
 * \endinternal
 */

#ifndef __AMHW_DAC_H
#define __AMHW_DAC_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "amhw_clock.h"
#include "am_types.h"  
#include "amhw_pincon.h"
#include "lpc177x_8x_pin.h"
    
/** 
 * \addtogroup amhw_if_dac
 * \copydoc amhw_dac.h
 * @{
 */

/**
 * \brief DAC�Ĵ�����Ľṹ��
 */
typedef struct amhw_dac {
    __IO uint32_t  cr;            /**< \brief ��ģת����ת���Ĵ���   */
    __IO uint32_t  ctrl;          /**< \brief ��ģת�������ƼĴ���   */
    __IO uint32_t  cntval;        /**< \brief ��ģת��������ֵ�Ĵ��� */
} amhw_dac_t;

/**
 * \brief dac_cntval�Ĵ����Ľṹ��
 */
typedef struct amhw_dac_cntval {
	uint8_t  dblbuf_ena;    /**< \brief ˫����ʹ��λ      */	
	uint8_t  cnt_ena;	    /**< \brief ��ʱ������ʹ��λ  */
	uint8_t  dma_ena;	    /**< \brief dma����ʹ��λ     */
	uint8_t  reserved;      /**< \brief ����              */
} amhw_dac_cntval_t;


/**
 * \name DAC �Ĵ����궨��
 * @{
 */

/** \brief �ú��е�n�����������Ĵ���Ϊ��λ�������趨ֵ &0x3FF */
#define AMHW_DAC_VALUE(n) 		 ((uint32_t)((n)<<6))

/** \brief DAC������趨ʱ��������� */
#define AMHW_DAC_BIAS_EN  ((uint32_t)(1<<16))

/** \brief DMA�ж϶�ʱ������ֵ */
#define AMHW_DAC_CCNT_VALUE(n)   ((uint32_t)(n&0xffff))

/** \brief ˫����ʹ�� */
#define AMHW_DAC_DBLBUF_ENA		 ((uint32_t)(1<<1))

/** \brief ��ʱ������ʹ�� */
#define AMHW_DAC_CNT_ENA         ((uint32_t)(1<<2))

/** \brief DMA����ʹ�� */
#define AMHW_DAC_DMA_ENA		 ((uint32_t)(1<<3))

/** \brief ת�����ƼĴ�������λ */
#define AMHW_DAC_DACCTRL_MASK	 ((uint32_t)(0x0F))

/** @} */
 
/**
 * \brief ��ʼ��DAC
 * \param[in] p_amhw_dac : ָ��DAC�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_dac_init (amhw_dac_t *p_amhw_dac)
{
    p_amhw_dac->cr &= ~AMHW_DAC_BIAS_EN;         /* DAC������趨ʱ��Ϊ1us��������Ϊ700uA */
}

/**
 * \brief ��������ֵ��DAC
 * \param[in] p_amhw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] dac_value  ����Ҫת������ֵ
 * \return    ��
 */
am_static_inline
void amhw_dac_value_update (amhw_dac_t *p_amhw_dac,uint32_t dac_value)
{
    uint32_t tmp;                        /* ���ݻ������            */
    tmp = p_amhw_dac->cr & AMHW_DAC_BIAS_EN;  /* ������Ϊ700uA         */
    tmp |= AMHW_DAC_VALUE(dac_value);  		 /* VALUE�ֶκ�BIAS�ֶκϲ� */
    p_amhw_dac->cr = tmp;				 /* ����ת���Ĵ�������ֵ    */
}

/**
 * \brief ����D/Aת�������Ĵ�����ֵ
 * \param[in] p_amhw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] time_value  ����Ҫת������ֵ
 * \return    ��
 */
am_static_inline
void amhw_dac_time_set (amhw_dac_t *p_amhw_dac,uint32_t time_value)
{
    p_amhw_dac->cntval = AMHW_DAC_CCNT_VALUE(time_value); /* ����ת���Ĵ�������ֵ */
}

/**
 * \brief ʹ��DMA���ܺ�����DMA��ʱ��
 * \param[in] p_amhw_dac         : ָ��DAC�Ĵ������ָ��
 * \param[in] p_amhw_dac_cntval  ��ָ��cntval�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_dac_convert_control_config (amhw_dac_t *p_amhw_dac,amhw_dac_cntval_t *p_amhw_dac_cntval)
{
    p_amhw_dac->cntval &= ~AMHW_DAC_DACCTRL_MASK; /* �û������Ӧ����λд��1 */
	if (p_amhw_dac_cntval->dblbuf_ena)       /* ˫����ʹ��                */
		p_amhw_dac->cntval |= AMHW_DAC_DBLBUF_ENA;
	if (p_amhw_dac_cntval->cnt_ena)          /* ��ʱ������ʹ�� 			  */
		p_amhw_dac->cntval |= AMHW_DAC_CNT_ENA;
	if (p_amhw_dac_cntval->dma_ena)          /* DMA����ʹ�� 			  */
		p_amhw_dac->cntval |= AMHW_DAC_DMA_ENA;	
}

/** 
 * @} amhw_if_dac 
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_DAC_H */

/* end of file */
