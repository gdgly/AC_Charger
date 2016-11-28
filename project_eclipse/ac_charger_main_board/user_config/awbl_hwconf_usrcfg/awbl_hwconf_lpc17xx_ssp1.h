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
  lpc54xxx SSP1 配置信息
*******************************************************************************/
#include "aw_int.h"
#include "aw_spi.h"
//#include "clkpwr.h"
#include "aw_gpio.h"

#ifdef AW_DEV_LPC17XX_SSP_1

#include "driver/spi/awbl_ametal_spi.h"

const amdr_ssp_devinfo_t  g_ssp1_devinfo = {
    AMHW_SSP1,                  /**< \brief SSP base addr   */
    INUM_SSP1,                  /**< \brief interrupt num   */
    8 ,                         /**< \brief bits per byte   */
    0,                          /**< \brief flags           */
    1000000                     /**< \brief speed           */
};

/** \brief SSP1 设备实例 */
amdr_ssp_dev_t            g_ssp1_dev;

/** \brief SSP1 平台初始化 */
void amhw_plfm_ssp1_init (void)
{
    amhw_power_periph_up(AMHW_POWER_SSP1);

    am_gpio_pin_cfg(PIO0_8, PIO0_8_MISO1 | PIO0_8_PULLUP);
    am_gpio_pin_cfg(PIO0_9, PIO0_9_MOSI1 | PIO0_9_PULLUP);
    am_gpio_pin_cfg(PIO0_7, PIO0_7_SCK1  | PIO0_7_PULLUP);
}

/** \brief 解除SSP1 平台初始化 */
void amhw_plfm_ssp1_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_SSP1);
}

/* 设备信息 */
aw_local aw_const struct awbl_ametal_spi_devinfo __g_ametal_ssp1_devinfo = {
    {
		LPC17XX_SSP1_BUSID,                                   /* SPI BUS ID   */
    },
    &g_ssp1_dev,
    &g_ssp1_devinfo,
    (pfn_spi_init_t)amdr_ssp_init,
    amhw_plfm_ssp1_init
};


/* 设备实例内存静态分配 */
aw_local struct awbl_ametal_spi_dev __g_ametal_ssp1_dev;


#define AWBL_HWCONF_LPC17XX_SSP_1           \
    {                                       \
        AWBL_AMETAL_SPI_NAME,               \
        1,                                  \
        AWBL_BUSID_PLB,                     \
        1,                                  \
        (struct awbl_dev *)&__g_ametal_ssp1_dev,  \
        &__g_ametal_ssp1_devinfo                  \
    },
#else 
    
#define AWBL_HWCONF_LPC17XX_SSP_1

#endif  /* AW_DEV_LPC17XX_SSP_1 */
    
