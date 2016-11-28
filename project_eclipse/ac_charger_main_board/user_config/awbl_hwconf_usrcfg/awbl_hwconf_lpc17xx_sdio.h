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
  lpc17xx SDIO 配置信息
*******************************************************************************/

#ifndef __AWBL_HWCONF_LPC17XX_SDIO_H
#define __AWBL_HWCONF_LPC17XX_SDIO_H

#ifdef  AW_DEV_LPC17XX_SDIO

#include "aw_gpio.h"
#include "aw_clk.h"
#include "awbl_sdiobus.h"
#include "driver/sdiocard/aw_sdcard.h"
//#include "driver/gpio/awbl_imx28x_gpio_private.h"
#include "driver/dma/awbl_lpc17xx_dma.h"
#include "driver/sdio/awbl_lpc17xx_sdio.h"

/* 设备实例内存静态分配 */
aw_local awbl_lpc17xx_sdio_dev_t __g_lpc17xx_sdio_dev;

aw_local awbl_sdio_slot_t __g_lpc17xx_slot0;

/* 提供一个静态内存存放具体的卡设备实体 */
static uint8_t card_buf[sizeof(awbl_sdcard_dev_t)];

/** \brief 引脚触发信息内存 */
static struct amdr_mci_intcb_info __g_mci_intcb_infos[AMHW_MCI_INT_TYPE_COUNT];

#define __SDIO_DMA_MCIFIFO     0x400C0080      /* SDIO 接口FIFO入口             */
#define __SDIO_DMA_CHN         0               /* 写数据的DMA 通道 */
#define __SDIO_TASK_PRIO       6               /* SDIO任务优先级 */

/** \brief MCI设备信息 */
const amdr_mci_devinfo_t g_mci_devinfo = {

    AMHW_SDC,               /**< \brief MCI的基地址  */

    AMHW_SYSCON,            /**< \brief SYSCON的基地址  */

    __g_mci_intcb_infos,    /**< \brief MCI的中断回调  */

    INUM_SDC,               /**< \brief MCI中断号  */

    PIO2_19,                /**< \brief MCI SD_INSERT引脚  */

    PIO2_21                 /**< \brief MCI SD_WP引脚  */
};

/** \brief MCI设备实例 */
amdr_mci_dev_t g_mci_dev;

static bool_t __sdio_detect (awbl_sdio_slot_t *p_slot)
{
	uint8_t cd_state, ro_state;

	cd_state = aw_gpio_get(PIO2_19) ? SDIO_CD_STUBBS : SDIO_CD_PLUG;
	ro_state = aw_gpio_get(PIO2_21) ? SDIO_READ_ONLY : SDIO_WRITE_EN;

	if (p_slot->cd_state == cd_state) {
		return FALSE;
	}

	p_slot->cd_state = cd_state;
	p_slot->ro_state = ro_state;
	return TRUE;
}

/** \brief MCI平台初始化 */
void amhw_plfm_mci_init (void)
{
    /* MCI上电 */
    amhw_power_periph_up(AMHW_POWER_SDC);

    /* 配置MCI接口各功能引脚 */
    aw_gpio_pin_cfg(PIO1_5, PIO1_5_SD_PWR);
    aw_gpio_pin_cfg(PIO1_2, PIO1_2_SD_CLK);
    aw_gpio_pin_cfg(PIO1_3, PIO1_3_SD_CMD);
    aw_gpio_pin_cfg(PIO1_6, PIO1_6_SD_DAT0);
    aw_gpio_pin_cfg(PIO1_7, PIO1_7_SD_DAT1);
    aw_gpio_pin_cfg(PIO1_11, PIO1_11_SD_DAT2);
    aw_gpio_pin_cfg(PIO1_12, PIO1_12_SD_DAT3);

    /* 配置卡插入检测引脚 */
    aw_gpio_pin_cfg(PIO2_19, PIO2_19_INPUT);

    /* 配置卡写保护检测引脚 */
    aw_gpio_pin_cfg(PIO2_21, PIO2_21_INPUT);


    awbl_sdio_link_slot(
		&(__g_lpc17xx_sdio_dev.host),
		&__g_lpc17xx_slot0,
		__sdio_detect,
		card_buf,
		sizeof(card_buf),
		0);

}

/** \brief MCI平台去初始化 */
void amhw_plfm_mci_deinit (void)
{
    /* MCI关闭电源 */
    amhw_power_periph_down(AMHW_POWER_SDC);
}


/* 设备信息 */
aw_local aw_const awbl_lpc17xx_sdio_dev_info_t __g_lpc17xx_sdio_devinfo = {
	{
		LPC17XX_SDIO_BUSID,
		SDIO_SD_4B_M,
		(OCR_VDD_27_28 | OCR_VDD_28_29 | OCR_VDD_29_30 |
		 OCR_VDD_30_31 | OCR_VDD_31_32 | OCR_VDD_32_33 |
		 OCR_VDD_33_34 | OCR_VDD_34_35 | OCR_VDD_35_36),
		 SDIO_SPI_CRC_DISABLE
	},

    TRUE,							/* 使能DMA传输 */
    __SDIO_DMA_CHN,				    /* DMA通道号 */
    __SDIO_DMA_MCIFIFO,				/* SDIO FIFO地址 */
    __SDIO_TASK_PRIO,               /* 传输任务优先级 */

    &g_mci_dev,						/* 设备实例 */
    &g_mci_devinfo,					/* 设备信息 */
    (pfunc_mci_init_t)amdr_mci_init,/* 设备初始化 */
    amhw_plfm_mci_init,   	        /* 平台相关初始化 */
};

#define AWBL_HWCONF_LPC17XX_SDIO    \
    {                               \
		AWBL_LPC17XX_SDIO_NAME,     \
        0,                          \
        AWBL_BUSID_PLB,             \
        0,										   \
        &(__g_lpc17xx_sdio_dev.host.super.super),  \
        &__g_lpc17xx_sdio_devinfo                  \
    },

#else

#define AWBL_HWCONF_LPC17XX_SDIO

#endif /* AWBL_HWCONF_LPC17XX_SDIO */

/* end of file */

#endif /* __AWBL_HWCONF_LPC17XX_SDIO_H */
