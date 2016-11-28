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
  lpc17xx SDIO ������Ϣ
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

/* �豸ʵ���ڴ澲̬���� */
aw_local awbl_lpc17xx_sdio_dev_t __g_lpc17xx_sdio_dev;

aw_local awbl_sdio_slot_t __g_lpc17xx_slot0;

/* �ṩһ����̬�ڴ��ž���Ŀ��豸ʵ�� */
static uint8_t card_buf[sizeof(awbl_sdcard_dev_t)];

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct amdr_mci_intcb_info __g_mci_intcb_infos[AMHW_MCI_INT_TYPE_COUNT];

#define __SDIO_DMA_MCIFIFO     0x400C0080      /* SDIO �ӿ�FIFO���             */
#define __SDIO_DMA_CHN         0               /* д���ݵ�DMA ͨ�� */
#define __SDIO_TASK_PRIO       6               /* SDIO�������ȼ� */

/** \brief MCI�豸��Ϣ */
const amdr_mci_devinfo_t g_mci_devinfo = {

    AMHW_SDC,               /**< \brief MCI�Ļ���ַ  */

    AMHW_SYSCON,            /**< \brief SYSCON�Ļ���ַ  */

    __g_mci_intcb_infos,    /**< \brief MCI���жϻص�  */

    INUM_SDC,               /**< \brief MCI�жϺ�  */

    PIO2_19,                /**< \brief MCI SD_INSERT����  */

    PIO2_21                 /**< \brief MCI SD_WP����  */
};

/** \brief MCI�豸ʵ�� */
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

/** \brief MCIƽ̨��ʼ�� */
void amhw_plfm_mci_init (void)
{
    /* MCI�ϵ� */
    amhw_power_periph_up(AMHW_POWER_SDC);

    /* ����MCI�ӿڸ��������� */
    aw_gpio_pin_cfg(PIO1_5, PIO1_5_SD_PWR);
    aw_gpio_pin_cfg(PIO1_2, PIO1_2_SD_CLK);
    aw_gpio_pin_cfg(PIO1_3, PIO1_3_SD_CMD);
    aw_gpio_pin_cfg(PIO1_6, PIO1_6_SD_DAT0);
    aw_gpio_pin_cfg(PIO1_7, PIO1_7_SD_DAT1);
    aw_gpio_pin_cfg(PIO1_11, PIO1_11_SD_DAT2);
    aw_gpio_pin_cfg(PIO1_12, PIO1_12_SD_DAT3);

    /* ���ÿ����������� */
    aw_gpio_pin_cfg(PIO2_19, PIO2_19_INPUT);

    /* ���ÿ�д����������� */
    aw_gpio_pin_cfg(PIO2_21, PIO2_21_INPUT);


    awbl_sdio_link_slot(
		&(__g_lpc17xx_sdio_dev.host),
		&__g_lpc17xx_slot0,
		__sdio_detect,
		card_buf,
		sizeof(card_buf),
		0);

}

/** \brief MCIƽ̨ȥ��ʼ�� */
void amhw_plfm_mci_deinit (void)
{
    /* MCI�رյ�Դ */
    amhw_power_periph_down(AMHW_POWER_SDC);
}


/* �豸��Ϣ */
aw_local aw_const awbl_lpc17xx_sdio_dev_info_t __g_lpc17xx_sdio_devinfo = {
	{
		LPC17XX_SDIO_BUSID,
		SDIO_SD_4B_M,
		(OCR_VDD_27_28 | OCR_VDD_28_29 | OCR_VDD_29_30 |
		 OCR_VDD_30_31 | OCR_VDD_31_32 | OCR_VDD_32_33 |
		 OCR_VDD_33_34 | OCR_VDD_34_35 | OCR_VDD_35_36),
		 SDIO_SPI_CRC_DISABLE
	},

    TRUE,							/* ʹ��DMA���� */
    __SDIO_DMA_CHN,				    /* DMAͨ���� */
    __SDIO_DMA_MCIFIFO,				/* SDIO FIFO��ַ */
    __SDIO_TASK_PRIO,               /* �����������ȼ� */

    &g_mci_dev,						/* �豸ʵ�� */
    &g_mci_devinfo,					/* �豸��Ϣ */
    (pfunc_mci_init_t)amdr_mci_init,/* �豸��ʼ�� */
    amhw_plfm_mci_init,   	        /* ƽ̨��س�ʼ�� */
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
