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
 * \brief  DAC硬件操作接口
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
 * \brief DAC寄存器块的结构体
 */
typedef struct amhw_dac {
    __IO uint32_t  cr;            /**< \brief 数模转换器转换寄存器   */
    __IO uint32_t  ctrl;          /**< \brief 数模转换器控制寄存器   */
    __IO uint32_t  cntval;        /**< \brief 数模转换器计数值寄存器 */
} amhw_dac_t;

/**
 * \brief dac_cntval寄存器的结构体
 */
typedef struct amhw_dac_cntval {
	uint8_t  dblbuf_ena;    /**< \brief 双缓冲使能位      */	
	uint8_t  cnt_ena;	    /**< \brief 超时计数器使能位  */
	uint8_t  dma_ena;	    /**< \brief dma访问使能位     */
	uint8_t  reserved;      /**< \brief 保留              */
} amhw_dac_cntval_t;


/**
 * \name DAC 寄存器宏定义
 * @{
 */

/** \brief 该宏中的n都是以整个寄存器为单位，数字设定值 &0x3FF */
#define AMHW_DAC_VALUE(n) 		 ((uint32_t)((n)<<6))

/** \brief DAC的最大设定时间和最大电流 */
#define AMHW_DAC_BIAS_EN  ((uint32_t)(1<<16))

/** \brief DMA中断定时器重载值 */
#define AMHW_DAC_CCNT_VALUE(n)   ((uint32_t)(n&0xffff))

/** \brief 双缓冲使能 */
#define AMHW_DAC_DBLBUF_ENA		 ((uint32_t)(1<<1))

/** \brief 超时计数器使能 */
#define AMHW_DAC_CNT_ENA         ((uint32_t)(1<<2))

/** \brief DMA访问使能 */
#define AMHW_DAC_DMA_ENA		 ((uint32_t)(1<<3))

/** \brief 转换控制寄存器保留位 */
#define AMHW_DAC_DACCTRL_MASK	 ((uint32_t)(0x0F))

/** @} */
 
/**
 * \brief 初始化DAC
 * \param[in] p_amhw_dac : 指向DAC寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_dac_init (amhw_dac_t *p_amhw_dac)
{
    p_amhw_dac->cr &= ~AMHW_DAC_BIAS_EN;         /* DAC的最大设定时间为1us，最大电流为700uA */
}

/**
 * \brief 更新数字值到DAC
 * \param[in] p_amhw_dac : 指向DAC寄存器块的指针
 * \param[in] dac_value  ：需要转换的数值
 * \return    无
 */
am_static_inline
void amhw_dac_value_update (amhw_dac_t *p_amhw_dac,uint32_t dac_value)
{
    uint32_t tmp;                        /* 数据缓存变量            */
    tmp = p_amhw_dac->cr & AMHW_DAC_BIAS_EN;  /* 最大电流为700uA         */
    tmp |= AMHW_DAC_VALUE(dac_value);  		 /* VALUE字段和BIAS字段合并 */
    p_amhw_dac->cr = tmp;				 /* 更新转换寄存器的数值    */
}

/**
 * \brief 设置D/A转换计数寄存器的值
 * \param[in] p_amhw_dac : 指向DAC寄存器块的指针
 * \param[in] time_value  ：需要转换的数值
 * \return    无
 */
am_static_inline
void amhw_dac_time_set (amhw_dac_t *p_amhw_dac,uint32_t time_value)
{
    p_amhw_dac->cntval = AMHW_DAC_CCNT_VALUE(time_value); /* 更新转换寄存器的数值 */
}

/**
 * \brief 使能DMA功能和设置DMA定时器
 * \param[in] p_amhw_dac         : 指向DAC寄存器块的指针
 * \param[in] p_amhw_dac_cntval  ：指向cntval寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_dac_convert_control_config (amhw_dac_t *p_amhw_dac,amhw_dac_cntval_t *p_amhw_dac_cntval)
{
    p_amhw_dac->cntval &= ~AMHW_DAC_DACCTRL_MASK; /* 用户软件不应向保留位写入1 */
	if (p_amhw_dac_cntval->dblbuf_ena)       /* 双缓冲使能                */
		p_amhw_dac->cntval |= AMHW_DAC_DBLBUF_ENA;
	if (p_amhw_dac_cntval->cnt_ena)          /* 超时计数器使能 			  */
		p_amhw_dac->cntval |= AMHW_DAC_CNT_ENA;
	if (p_amhw_dac_cntval->dma_ena)          /* DMA访问使能 			  */
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
