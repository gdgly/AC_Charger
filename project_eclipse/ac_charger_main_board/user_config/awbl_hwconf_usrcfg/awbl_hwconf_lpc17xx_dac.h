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
#ifdef AW_DEV_LPC17XX_DAC

#include "driver/dac/awbl_ametal_dac.h"
#include "ametal.h"

/** \brief DAC 设备信息 */
const amdr_dac_devinfo_t  g_dac_devinfo = {
    AMHW_DAC,                 /* 指向DAC寄存器块的指针 */
    10,                       /* DAC采样精度   10bits  */
    3300                      /* 参考电压 3.3V        */
};

/** \brief DAC设备实例  */
amdr_dac_dev_t            g_dac_dev;

/** \brief DAC平台初始化 */
void amhw_plfm_dac_init (void)
{
	/* 配置GPIO引脚功能 , 未使能DAC*/
	am_gpio_pin_cfg(PIO0_26,
					PIO0_26_AOUT  |
					PIO0_26_FLOAT |
					PIO0_26_ADMODE_ANALOG);

}

/** \brief 解除DAC 平台初始化 */
void amhw_plfm_dac_deinit (void)
{
	/* DAC管脚设置为数字模式，DAC禁能 */
	am_gpio_pin_cfg(PIO0_26,
					PIO0_26_GPIO |
					PIO0_26_ADMODE_DIGITAL |
					PIO0_26_DAC_DISABLE);
}

/* DAC0 设备信息 */
aw_local aw_const struct awbl_ametal_dac_param __g_awbl_dac_param = {
    &g_dac_dev,
    &g_dac_devinfo,

    {
       0,        /*  the minimum channel  */
       0         /*  the maximum channel  */
    },

    (pfunc_dac_init_t)amdr_dac_init,
    amhw_plfm_dac_init
};

/* ADC 设备实例内存静态分配*/
aw_local struct awbl_ametal_dac_dev __g_awbl_dac_dev;

#define AWBL_HWCONF_LPC17XX_DAC      \
    {                                \
		AWBL_AMETAL_DAC_NAME,        \
        0,                           \
        AWBL_BUSID_PLB,              \
        0,                           \
        (struct awbl_dev *)&__g_awbl_dac_dev,  \
        &__g_awbl_dac_param                    \
    },

#else

#define AWBL_HWCONF_LPC17XX_DAC

#endif  /* AW_DEV_LPC17XX_DAC */

/* end of file */
