/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

#include "apollo.h"
#include "aw_spinlock.h"
#include "awbus_lite.h"

/*******************************************************************************
  ADC 配置信息
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_ADC

#include "driver/adc/awbl_ametal_adc.h"
#include "ametal.h"

/** \brief ADC device information */
const amdr_adc_devinfo_t g_adc_devinfo =
{
    AMHW_ADC,                      /**< \brief ADC register address      */
	ADC_IRQn,				       /**  \brief ADC interrupt number      */
    12,                            /**< \brief ADC sample bits           */
    3270,                          /**< \brief ADC reference voltage(mV) */
    4                              /**< \brief ADC sample clock divice   */
};

/** \brief ADC device instance */
amdr_adc_dev_t g_adc_dev;

/** 
 * \brief ADC platform initialization
 */
void amdr_plfm_adc_init (void)
{
    /*  
     * Initialize the ADC
     */
	amhw_power_periph_up(AMHW_POWER_ADC);
}

/** 
 * \brief ADC platform de-initialization
 */
void amdr_plfm_adc_deinit (void)
{
	amhw_power_periph_down(AMHW_POWER_ADC);

}

/* ADC0 设备信息 */
aw_local aw_const struct awbl_ametal_adc_param __g_awbl_adc_param = {
    &g_adc_devinfo,

    {
       AMHW_ADC_CHAN_0,        /*  the minimum channel  */
       AMHW_ADC_CHAN_7         /*  the maximum channel  */
    },

    amdr_plfm_adc_init
};

/* ADC 设备实例内存静态分配*/
aw_local struct awbl_ametal_adc_dev __g_awbl_adc_dev;

#define AWBL_HWCONF_LPC17XX_ADC      \
    {                                \
        "ametal_adc",                \
        0,                           \
        AWBL_BUSID_PLB,              \
        0,                           \
        (struct awbl_dev *)&__g_awbl_adc_dev,  \
        &__g_awbl_adc_param                    \
    },

#else

#define AWBL_HWCONF_LPC17XX_ADC

#endif  /* AW_DEV_LPC17XX_ADC */

/* end of file */
