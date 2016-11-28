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
 * \brief ADC drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.01 15-08-17  cod, add "p_dev->p_val != NULL"
 * - 1.00 15-05-28  ben, first implementation.
 * \endinternal
 */

#include "amdr_adc.h"
#include "am_int.h"

/*******************************************************************************
* Private declaration
*******************************************************************************/

#define __ADC_HW_DECL(p_hw_adc, p_drv)    \
        amhw_adc_t *p_hw_adc =               \
            ((amdr_adc_dev_t *)p_drv)->p_devinfo->p_hw_adc

#define __ADC_BITS_GET(p_drv)             \
        (((amdr_adc_dev_t *)p_drv)->p_devinfo->bits)

#define __ADC_VREF_GET(p_drv)             \
        (((amdr_adc_dev_t *)p_drv)->p_devinfo->vref)

/*******************************************************************************
* Functions declaration
*******************************************************************************/

static int __adc_start (void               *p_drv,
						int                 channel,
						uint32_t           *p_val,
						uint32_t            desired_cnt,
						void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt),
						void               *p_arg);

static uint32_t __adc_get_bits(void *p_drv);

static uint32_t __adc_get_vref(void *p_drv);

/**
* \brief ADC service functions 
*/
static const struct am_adc_drv_funcs __g_adc_drvfuncs = {
	__adc_start,
	__adc_get_bits, 
	__adc_get_vref
};

/******************************************************************************/

static void __adc_int(void *p_arg)
{
	amdr_adc_dev_t *p_dev = (amdr_adc_dev_t *)p_arg;

	__ADC_HW_DECL(p_hw_adc, p_arg);

	uint32_t data;

	data = amhw_adc_glo_data_get(p_hw_adc);

	if (p_dev->p_val != NULL) {
        *(p_dev->p_val) = (data & 0xFFFF) >> (16 - __ADC_BITS_GET(p_arg));

        if (p_dev->pfn_convert_cb) {
            p_dev->pfn_convert_cb(p_dev->p_arg, 1); /* 每次启动转换仅转换一次 */
		}
	}
}

/******************************************************************************/

/**
* \brief The ADC initialization
*/
am_adc_handle_t amdr_adc_init (amdr_adc_dev_t           *p_dev, 
                               const amdr_adc_devinfo_t *p_devinfo)
{
	amhw_adc_t *p_hw_adc = NULL;

	uint32_t cfg_ctrl;

	if ((p_devinfo == NULL) || (p_dev == NULL)) {
		return NULL;
	}

	p_dev->p_devinfo         = p_devinfo;
	p_dev->adc_serve.p_funcs = &__g_adc_drvfuncs;
	p_dev->adc_serve.p_drv   = p_dev; 
	p_hw_adc                 = p_devinfo->p_hw_adc;

	amhw_adc_startup(p_hw_adc);

	cfg_ctrl = AMHW_ADC_CTRL_CLK_DIV(p_devinfo->clk_div) |\
	           AMHW_ADC_CTRL_BURST_SOFT                  |\
	           AMHW_ADC_CTRL_PDN_SET;

	/* ADC CTRL configure */
	amhw_adc_config(p_hw_adc, cfg_ctrl);

	/* enable  channel interrupt */
	amhw_adc_int_config(p_hw_adc, AMHW_ADC_ADGINTEN,AMHW_ADC_FUN_ENABLE); 

	/* Connect ADC interrupt */
	am_int_connect(p_devinfo->intnum, __adc_int, p_dev);

	/* Enable ADC interrupt  */
	am_int_enable(p_devinfo->intnum);

	/* start conversion now */
	amhw_adc_start_cmd(p_hw_adc,AMHW_ADC_CTRL_START_NOW);

	return (am_adc_handle_t)(&(p_dev->adc_serve));
}

/**
* \brief The ADC de-initialization
*/
void amdr_adc_deinit (amdr_adc_dev_t *p_dev)
{
	/* Disconnect ADC interrupt   */
	am_int_disconnect(p_dev->p_devinfo->intnum, __adc_int, p_dev);
	/* Disable channel interrupt  */
	am_int_disable(p_dev->p_devinfo->intnum);
	/* Disable  channel interrupt */
	amhw_adc_int_config(p_dev->p_devinfo->p_hw_adc,AMHW_ADC_ADGINTEN,AMHW_ADC_FUN_DISABLE); 
	/* Power down ADC             */
	amhw_adc_powerdown_cmd(p_dev->p_devinfo->p_hw_adc,AMHW_ADC_FUN_DISABLE);
}

/**
* \brief 启动一次AD转换
*
* \param[in] p_drv            作为驱动函数的第一个参数
* \param[in] channel          待转换的通道
* \param[in] p_val            转换结果存放的缓冲区
* \param[in] desired_cnt      期望的转换次数，实际转换次数通过回调函数返回
* \param[in] pfn_convert_cb   一次转换完成的回调函数
* \param[in] p_arg            回调函数的第一个参数，用户设置
*
* \retval   AM_OK     启动转换成功
* \retval -AM_ENXIO   通道不存在
* \retval -AM_EINVAL  无效参数
*/

/**
* \brief The ADC start conversion
*/
static int __adc_start (void               *p_drv,
						int                 channel,
						uint32_t           *p_val,
						uint32_t            desired_cnt,
						void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt),
						void               *p_arg)
{		
	__ADC_HW_DECL(p_hw_adc, p_drv);

	amdr_adc_dev_t *p_dev = (amdr_adc_dev_t *)p_drv;

	if (p_val == NULL || desired_cnt == 0) {
		return -AM_EINVAL;
	}

	if (channel >= AMHW_ADC_CHAN_CNT) {
		return -AM_ENXIO;   /* 无效的通道值 */
	}

	p_dev->pfn_convert_cb = pfn_convert_cb;
	p_dev->p_arg          = p_arg;      /*addr of adc_cb_arg*/
	p_dev->p_val          = p_val;
	p_dev->chan           = channel;
	/* set & enable channel */
	amhw_adc_channel_sel(p_hw_adc,channel,AMHW_ADC_FUN_ENABLE);
	/* start conversion now */
	amhw_adc_start_cmd(p_hw_adc,AMHW_ADC_CTRL_START_NOW);

	return AM_OK;
}

/**
* \brief 获取ADC转换精度。
*/
static uint32_t __adc_get_bits (void *p_drv)
{
	return (uint32_t)__ADC_BITS_GET(p_drv);
}

/**
* \brief 获取ADC参考电压。
*/
static uint32_t __adc_get_vref (void *p_drv)
{
	return (uint32_t)__ADC_VREF_GET(p_drv);
}

/* end of file */
