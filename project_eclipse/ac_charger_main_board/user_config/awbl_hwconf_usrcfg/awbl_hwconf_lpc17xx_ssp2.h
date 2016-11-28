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
  lpc17xx SSP2 配置信息
*******************************************************************************/
#include "aw_int.h"
#include "aw_spi.h"
#include "aw_gpio.h"

#ifdef AW_DEV_LPC17XX_SSP_2

#include "driver/spi/awbl_ametal_spi.h"

const amdr_ssp_devinfo_t  g_ssp2_devinfo = {
    AMHW_SSP2,                  /**< \brief SSP base addr   */
    INUM_SSP2,                  /**< \brief interrupt num   */
    8 ,                         /**< \brief bits per byte   */
    0,                          /**< \brief flags           */
    1000000                     /**< \brief speed           */
};

/** \brief SSP2 设备实例 */
amdr_ssp_dev_t            g_ssp2_dev;

/** \brief SSP2 平台初始化 */
void amhw_plfm_ssp2_init (void)
{
    amhw_power_periph_up(AMHW_POWER_SSP2);

    am_gpio_pin_cfg(PIO1_4, PIO1_4_MISO2 | PIO1_4_PULLUP);
	am_gpio_pin_cfg(PIO1_1, PIO1_1_MOSI2 | PIO1_1_PULLUP);
	am_gpio_pin_cfg(PIO1_0, PIO1_0_SCK2  | PIO1_0_PULLUP);
}

/** \brief 解除SSP2 平台初始化 */
void amhw_plfm_ssp2_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_SSP2);
}

/* 设备信息 */
aw_local aw_const struct awbl_ametal_spi_devinfo __g_ametal_ssp2_devinfo = {
    {
		LPC17XX_SSP2_BUSID,                                   /* SPI BUS ID   */
    },
    &g_ssp2_dev,
    &g_ssp2_devinfo,
    (pfn_spi_init_t)amdr_ssp_init,
    amhw_plfm_ssp2_init
};


/* 设备实例内存静态分配 */
aw_local struct awbl_ametal_spi_dev __g_ametal_ssp2_dev;


#define AWBL_HWCONF_LPC17XX_SSP_2           \
    {                                       \
        AWBL_AMETAL_SPI_NAME,               \
        1,                                  \
        AWBL_BUSID_PLB,                     \
        1,                                  \
        (struct awbl_dev *)&__g_ametal_ssp2_dev,  \
        &__g_ametal_ssp2_devinfo                  \
    },
#else 
    
#define AWBL_HWCONF_LPC17XX_SSP_2

#endif  /* AW_DEV_LPC17XX_SSP_2 */
    
