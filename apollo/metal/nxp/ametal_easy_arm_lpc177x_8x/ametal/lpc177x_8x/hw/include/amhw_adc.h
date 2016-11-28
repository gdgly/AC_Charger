/*******************************************************************************
*                                Apollo
*                      ----------------------------
*                      innovating embedded platform
*
*Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
*All rights reserved.
*
*Contact information:
*web site:    http://www.zlg.cn/
*e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC 硬件层接口
 *
 * - 12位主次逼近式模数转换器；
 * - 8个引脚复用为A/D输入脚；
 * - 具有掉电模式；
 * - 测量范围：0~VREFP（通常为3V；不超过VDDA）；
 * - 12位转换时间，200KHz；
 * - 一个或多个输入的Burst转换模式；
 * - 可选择由输入跳变或定时器匹配信号触发转换。
 *
 * \internal
 * \par Modification history
 * - 1.01 15-08-19  cod, fix code style and comments.
 * - 1.00 15-05-26  ben, first implementation.
 * \endinternal
 */
#ifndef  __AMHW_ADC_H
#define  __AMHW_ADC_H

#ifdef __cplusplus
extern "C" {
#endif
#include "am_types.h"

/**
 * \addtogroup amhw_if_adc
 * \copydoc amhw_adc.h
 * @{
 */

/**
 * \brief 匿名结构体段的开始
 * @{
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

/** @} */


/**
 * \brief ADC 寄存器结构
 */
typedef struct amhw_adc {
    __IO uint32_t ctrl;               /**< \brief ADC 控制寄存器          */
    __IO uint32_t gdat;               /**< \brief ADC 全局数据寄存器      */
	     uint32_t reserved;           /**< \brief 保留          */
	__IO uint32_t inten;              /**< \brief ADC 中断使能寄存器 */
    union {
        __I uint32_t dat[8];          /**< \brief ADC 通道数据寄存器    */
        struct {
            __I uint32_t dat0;        /**< \brief ADC 通道0数据寄存器   */
            __I uint32_t dat1;        /**< \brief ADC 通道1数据寄存器   */
            __I uint32_t dat2;        /**< \brief ADC 通道2数据寄存器   */
            __I uint32_t dat3;        /**< \brief ADC 通道3数据寄存器   */
            __I uint32_t dat4;        /**< \brief ADC 通道4数据寄存器   */
            __I uint32_t dat5;        /**< \brief ADC 通道5数据寄存器   */
            __I uint32_t dat6;        /**< \brief ADC 通道6数据寄存器   */
            __I uint32_t dat7;        /**< \brief ADC 通道7数据寄存器   */
        };
    };
    __I  uint32_t status;             /**< \brief ADC 状态寄存器.   */
    __IO uint32_t trim;               /**< \brief ADC trim 寄存器.  */
} amhw_adc_t;


/**
 * \name ADC 通道号索引
 * \anchor grp_amhw_adc_chan
 * @{
 */

#define AMHW_ADC_CHAN_0          0          /**< \brief ADC  通道0  */
#define AMHW_ADC_CHAN_1          1          /**< \brief ADC  通道1  */
#define AMHW_ADC_CHAN_2          2          /**< \brief ADC  通道2  */
#define AMHW_ADC_CHAN_3          3          /**< \brief ADC  通道3  */
#define AMHW_ADC_CHAN_4          4          /**< \brief ADC  通道4  */
#define AMHW_ADC_CHAN_5          5          /**< \brief ADC  通道5  */
#define AMHW_ADC_CHAN_6          6          /**< \brief ADC  通道6  */
#define AMHW_ADC_CHAN_7          7          /**< \brief ADC  通道7  */

/** @} */

#define AMHW_ADC_CHAN_CNT        8          /**< \brief 通道总数     */

/**
 * \name ADC 功能使能/失能
 * @{
 */
#define AMHW_ADC_FUN_ENABLE     (1UL)		/**< \brief 使能               */
#define AMHW_ADC_FUN_DISABLE    (0UL)		/**< \brief 失能               */

/** @} */

/**
 * \name ADC 控制寄存器位
 * \anchor grp_amhw_adc_ctrl
 * @{
 */
#define AMHW_ADC_CTRL_PINS_SEL(pin)    (1UL << (pin))       /**< \brief 选择 AD0 7:0 作为采样管脚     */
#define AMHW_ADC_CTRL_CLK_DIV(x)       (((x) & 0xFF) << 8)  /**< \brief 设置 ADC时钟分频        */
#define AMHW_ADC_CTRL_BURST_REPEAT     (1UL << 16)          /**< \brief ADC burst 重复装换	    */
#define AMHW_ADC_CTRL_BURST_SOFT       (0UL << 16)	        /**< \brief ADC burst 软件触发		*/
#define AMHW_ADC_CTRL_PDN_SET          (1UL << 21)	    	/**< \brief 设置ADC工作在普通模式   */
#define AMHW_ADC_CTRL_PDN_RESET        (0UL << 21)	    	/**< \brief 设置ADC掉电模式         */
#define AMHW_ADC_CTRL_START_CONFIG(x)  (((x) & 0x7) << 24)  /**< \brief 设置ADC启动转换的条件   */
#define AMHW_ADC_CTRL_TRIG_EDGE        (1UL << 27)	    	/**< \brief 设置ADC边沿触发条件		*/

/** \brief 立即启动转换               */
#define AMHW_ADC_CTRL_START_NOW	   (1UL)

/** \brief 当位27选择的边沿出现在P2.10/EINT0/NMI脚时启动转换          */
#define AMHW_ADC_CTRL_START_EINT0  (2UL)

/** \brief 当位27选择的边沿出现在P1.27/CLKOUT/USB_OVRCRn/CAP0.1脚时启动转换    */
#define AMHW_ADC_CTRL_START_CAP01  (3UL)

/** \brief 当位27选择的边沿出现在MAT0.1时启动转换                  */
#define AMHW_ADC_CTRL_START_MAT01  (4UL)

/** \brief 当位27选择的边沿出现在MAT0.3时启动转换                  */
#define AMHW_ADC_CTRL_START_MAT03  (5UL)

/** \brief 当位27选择的边沿出现在MAT1.0时启动转换                  */
#define AMHW_ADC_CTRL_START_MAT10  (6UL)

/** \brief 当位27选择的边沿出现在MAT1.1时启动转换                  */
#define AMHW_ADC_CTRL_START_MAT11  (7UL)

/** @} */

#define AMHW_ADC_CTRL_START_MASK       (7UL << 24)	    	/**< \brief 设置ADC启动条件掩码  	*/

/**
 * \brief 启动ADC转换序列.
 *
 * \param[in] p_hw_adc : 指向ADC基地址.
 *
 * \retval  AM_OK      : 启动成功
 * \retval -AM_ETIME   : 启动超时.
 */
int amhw_adc_startup(amhw_adc_t *p_hw_adc);


/**
 * \brief 设置ADC转换频率
 * \param[in] p_hw_adc : 指向ADC基地址.
 * \param[in] convfreq : ADC工作频率
 */

void amhw_adc_set_freq (amhw_adc_t *p_hw_adc, uint32_t convfreq);

/**
 * \brief ADC控制寄存器
 *
 * \param[in] p_hw_adc : ADC寄存器基地址
 * \param[in] flags    : 控制字,参见
 *                       \ref grp_amhw_adc_ctrl "ADC Ctrl Flags"
 *
 * \return    None
 */
am_static_inline
void amhw_adc_config (amhw_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->ctrl = flags;
}

/**
 * \brief 获得ADC控制寄存器状态
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块
 * \return    控制寄存器状态
 */
am_static_inline
uint32_t amhw_adc_ctrl_get (amhw_adc_t *p_hw_adc)
{
    return p_hw_adc->ctrl;
}
/**
 * \brief 设置ADC转换通道
 *
 * \param[in] p_hw_adc : ADC基地址
 * \param[in] channel  : 通道号,值为: AMHW_ADC_CHAN_*(#AMHW_ADC_CHAN_0)
 * \param[in] state    : 状态,值为：(#AMHW_ADC_FUN_ENABLE)或(#AMHW_ADC_FUN_DISABLE)
 * \return    无
 */
am_static_inline
void amhw_adc_channel_sel(amhw_adc_t *p_hw_adc, uint8_t channel, uint8_t state)
{
	if(AMHW_ADC_FUN_ENABLE == state){
		p_hw_adc->ctrl |= AMHW_ADC_CTRL_PINS_SEL(channel);
	} else{
	    p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_PINS_SEL(channel);
	}
}

/**
 * \brief 设置ADC的启动模式
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块
 * \param[in] mode     : 选择启动转换的类型,
 *                       值为AMHW_ADC_CTRL_START_*(#AMHW_ADC_CTRL_START_NOW)
 * \return    无
 */
am_static_inline
void amhw_adc_start_cmd (amhw_adc_t *p_hw_adc, uint8_t mode)
{
    p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_START_MASK;
    p_hw_adc->ctrl |=  AMHW_ADC_CTRL_START_CONFIG(mode);
}

/**
 * \brief Burst 模式
 *
 * \param[in] p_hw_adc  : 指向ADC寄存器块
 * \param[in] burstmode : 是否使用Burst模式,
 *                        值为:(#AMHW_ADC_FUN_ENABLE)或(#AMHW_ADC_FUN_DISABLE)
 * \return    无
 */
am_static_inline
void amhw_adc_burst_cmd(amhw_adc_t *p_hw_adc, uint8_t burstmode)
{
	p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_BURST_REPEAT;
	if( AMHW_ADC_FUN_ENABLE == burstmode){
		p_hw_adc->ctrl |= AMHW_ADC_CTRL_BURST_REPEAT;
	}
}
/**
 * \brief 设置电源模式
 *
 * \param[in] p_hw_adc : 指向ADC基地址
 * \param[in] mode	   : 设置模式,
 *                       值为:(#AMHW_ADC_FUN_ENABLE)或(#AMHW_ADC_FUN_DISABLE)
 * \return    无
 */
am_static_inline
void amhw_adc_powerdown_cmd(amhw_adc_t *p_hw_adc,uint8_t mode)
{
	p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_PDN_SET;
	if(AMHW_ADC_FUN_ENABLE == mode){
		p_hw_adc->ctrl |= AMHW_ADC_CTRL_PDN_SET;
	}
}
/**
 * \brief 设置ADC采样触发模式
 *
 * \param[in] p_hw_adc : 指向ADC基地址
 * \param[in] mode 	   : 使能或者禁用
 *                       值为:(#AMHW_ADC_FUN_ENABLE)或(#AMHW_ADC_FUN_DISABLE)
 * \return    无
 */
am_static_inline
void amhw_adc_edgstart_cmd(amhw_adc_t *p_hw_adc,uint8_t mode)
{
	p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_TRIG_EDGE;
	if (AMHW_ADC_FUN_ENABLE == mode){
		p_hw_adc->ctrl |= AMHW_ADC_CTRL_TRIG_EDGE;
	}
}


/**
 * \name 全局寄存器位域定义
 * @{
 */
#define AMHW_ADC_DATA_OVERRUN_FLAG    (1UL << 30)            /**< \brief 最后一次转换失败标志      */
#define AMHW_ADC_DATA_DONE_FLAG       (1UL << 31)			 /**< \brief 转换完成标志                          */
#define AMHW_ADC_GDATA_RESULT(n) 	  (((n) >> 4) & 0xFFF) 	 /**< \brief 获取ADC值                                  */
#define AMHW_ADC_GDATA_GET_CHN(x)     (((x) >> 24) & 0x7 )   /**< \brief 获取指定通道当前ADC值     */

/** @} */

/**
 * \brief 获取指定通道的数据值
 *
 * \param[in] p_hw_adc : ADC基地址
 * \param[in] chan     : ADC通道序号,值为: AMHW_ADC_CHAN_*(#AMHW_ADC_CHAN_0)
 *
 * \return  转化后的ADC值
 */
am_static_inline
uint32_t amhw_adc_chan_data_get (amhw_adc_t *p_hw_adc, int chan)
{
    return (p_hw_adc->dat[chan]);
}

/**
 * \brief 从全局数据寄存器中获得ADC数据.
 *
 * \param[in] p_hw_adc :指向ADC基地址
 *
 * \return    ADC转换值
 */
am_static_inline
uint32_t amhw_adc_glo_data_get (amhw_adc_t *p_hw_adc)
{
    return (p_hw_adc->gdat );
}


/**
 * \name ADC 中断使能寄存器位定义
 * \anchor grp_amhw_adc_inten
 * @{
 */

#define AMHW_ADC_INTEN_ENABLE(ch)   (0x1UL << ch)   /**< \brief 使能指定通道中断    */
#define AMHW_ADC_INTEN_DISABLE(ch)  (0x0UL << ch)   /**< \brief 禁止指定通道中断    */
#define AMHW_ADC_INTEN_EN_SEL       (0x1UL << 8)    /**< \brief 中断触发选择              */

/** \brief ADC中断类型 */
typedef enum
{
	AMHW_ADC_ADINTEN0 = 0,		/**< \brief 中断通道 0 */
	AMHW_ADC_ADINTEN1,			/**< \brief 中断通道 1 */
	AMHW_ADC_ADINTEN2,			/**< \brief 中断通道 2 */
	AMHW_ADC_ADINTEN3,			/**< \brief 中断通道 3 */
	AMHW_ADC_ADINTEN4,			/**< \brief 中断通道 4 */
	AMHW_ADC_ADINTEN5,			/**< \brief 中断通道 5 */
	AMHW_ADC_ADINTEN6,			/**< \brief 中断通道 6 */
	AMHW_ADC_ADINTEN7,			/**< \brief 中断通道 7 */
	AMHW_ADC_ADGINTEN			/**< \brief 使能全局中断 */
}amhw_adc_type_int_opt;


/** @} */

/**
 * \brief 中断配置
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块基地址
 * \param[in] intch    : 选择通道序号,值为：AMHW_ADC_ADINTEN*(#AMHW_ADC_ADINTEN0)
 * \param[in] state    : 使能、禁用，
 *                       值为:(#AMHW_ADC_FUN_ENABLE)或(#AMHW_ADC_FUN_DISABLE)
 *
 * \return  None
 */
am_static_inline
void amhw_adc_int_config (amhw_adc_t           *p_hw_adc,
		                  amhw_adc_type_int_opt intch,
		                  uint8_t               state)
{
    p_hw_adc->inten &= ~AMHW_ADC_INTEN_ENABLE(intch);
    if(AMHW_ADC_FUN_ENABLE == state){
		p_hw_adc->inten |= AMHW_ADC_INTEN_ENABLE(intch);
    }
}


/**
 * \name ADC 状态寄存器位域
 * \anchor grp_amhw_adc_status
 * @{
 */
#define  AMHW_ADC_STATUS_DONE_FLAG(ch)    (1UL << (ch))   /**< \brief 装换完成     			*/
#define  AMHW_ADC_STATUS_OVERRUN_FLAG(ch) (1UL << (ch))   /**< \brief 转换超时   				*/
#define  AMHW_ADC_STATUS_GINT_FLAG        (1UL << 16)     /**< \brief 任何通道转换完成时置位	*/

/** @} */

#define  AMHW_ADC_STA_DONE          	    (1UL)    /**< \brief 转换完成   */
#define  AMHW_ADC_STA_OVERRUN               (0UL)    /**< \brief 转换超时   */

/**
 * \brief 获取ADC通道数据寄存器状态
 *
 * \param[in] p_hw_adc  : ADC基地址寄存器
 * \param[in] chan      : 通道号,值为: AMHW_ADC_CHAN_*(#AMHW_ADC_CHAN_0)
 * \param[in] flag      : 完成或者超时标志，
 *                        值为 (#AMHW_ADC_STA_DONE)或  (#AMHW_ADC_STA_OVERRUN)
 * \retval    AM_OK     : 置位
 * \retval    AM_EINVAL : 为零
 */
am_static_inline uint8_t amhw_adc_channel_get_status(amhw_adc_t *p_hw_adc,
		                                             uint8_t     chan,
		                                             uint8_t     flag)
{
	uint32_t temp;
	temp = p_hw_adc->dat[chan];
	if(flag == AMHW_ADC_STA_DONE){
		temp &= AMHW_ADC_DATA_DONE_FLAG;
	} else {
		temp &= AMHW_ADC_DATA_OVERRUN_FLAG;
	}
	if (temp) {
	    return AM_OK;
	} else {
		return AM_EINVAL;
	}
}

/**
 * \brief 获取ADC全局数据寄存器状态
 *
 * \param[in] p_hw_adc   : ADC基地址寄存器
 * \param[in] flag       : 完成或者超时标志,
 *                         值为 (#AMHW_ADC_STA_DONE)或  (#AMHW_ADC_STA_OVERRUN)
 * \retval    AM_OK      : 置位
 * \retval    AM_EINVAL  : 为零
 */
am_static_inline uint8_t amhw_adc_global_get_status(amhw_adc_t *p_hw_adc,
		                                            uint8_t     flag)
{
	uint32_t temp;
	temp = p_hw_adc->gdat;
	if(flag == AMHW_ADC_STA_DONE){
		temp &= AMHW_ADC_DATA_DONE_FLAG;
	} else {
		temp &= AMHW_ADC_DATA_OVERRUN_FLAG;
	}
	if (temp) {
	    return AM_OK;
	} else {
		return AM_EINVAL;
	}
}


/**
 * \name ADC TRIM 寄存器
 * \anchor grp_amhw_adc_trim
 * @{
 */
#define AMHW_ADC_TRIM_ADCOFFS(offs)   (((offs) & 0xF) << 4) 			/**< \brief 设置ADC偏移 */

/**
 * \brief  匿名结构体段的结束
 * @{
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

/** @} */


/**
 *@} amhw_if_adc
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMHW_ADC_H */

/* end of file */
