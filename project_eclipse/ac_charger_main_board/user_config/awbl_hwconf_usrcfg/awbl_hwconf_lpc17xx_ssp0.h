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
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/
/*******************************************************************************
  lpc54xxx SSP0 配置信息
*******************************************************************************/
#include "aw_int.h"
#include "aw_spi.h"
//#include "clkpwr.h"
#include "aw_gpio.h"

#ifdef AW_DEV_LPC17XX_SSP_0

#include "driver/spi/awbl_ametal_spi.h"

/** \brief SSP0 设备信息 */
const amdr_ssp_devinfo_t  g_ssp0_devinfo = {
    AMHW_SSP0,                  /**< \brief SSP base addr   */
    INUM_SSP0,                  /**< \brief interrupt num   */
    8,                          /**< \brief bits per byte   */
    0,                          /**< \brief flags           */
    30000000                    /**< \brief speed           */
};

/** \brief SSP0 设备实例 */
amdr_ssp_dev_t            g_ssp0_dev;

/** \brief SSP0 平台初始化 */
void amhw_plfm_ssp0_init (void)
{
    amhw_power_periph_up(AMHW_POWER_SSP0);

    am_gpio_pin_cfg(PIO0_17, PIO0_17_MISO0 | PIO0_17_PULLUP);
    am_gpio_pin_cfg(PIO0_18, PIO0_18_MOSI0 | PIO0_18_PULLUP);
    am_gpio_pin_cfg(PIO0_15, PIO0_15_SCK0  | PIO0_15_PULLUP);
    am_gpio_pin_cfg(PIO0_16, PIO0_16_GPIO | PIO0_16_PULLUP);
}

/** \brief 解除SSP0 平台初始化 */
void amhw_plfm_ssp0_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_SSP0);
}

/* 设备信息 */
aw_local aw_const struct awbl_ametal_spi_devinfo __g_ametal_ssp0_devinfo = {
    {
    	LPC17XX_SSP0_BUSID,                                   /* SPI BUS ID   */
    },
    &g_ssp0_dev,
    &g_ssp0_devinfo,
    (pfn_spi_init_t)amdr_ssp_init,
    amhw_plfm_ssp0_init
};


/* 设备实例内存静态分配 */
aw_local struct awbl_ametal_spi_dev __g_ametal_ssp0_dev;


#define AWBL_HWCONF_LPC17XX_SSP_0           \
    {                                       \
        AWBL_AMETAL_SPI_NAME,               \
        0,                                  \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        (struct awbl_dev *)&__g_ametal_ssp0_dev,  \
        &__g_ametal_ssp0_devinfo                  \
    },
#else

#define AWBL_HWCONF_LPC17XX_SSP_0

#endif  /* AW_DEV_LPC17XX_SSP_0 */

