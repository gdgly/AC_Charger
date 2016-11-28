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

/**
 * \file
 * \brief EasyARM-54000M4 AWBus-lite 硬件配置文件
 *
 * \internal
 * \par modification history
 * - 1.01 14-08-19  tee, add digitron and SPI1
 * - 1.00 12-10-23  liuweiyun, first implementation
 * \endinternal
 */
/*******************************************************************************
  headers
*******************************************************************************/

#undef  AW_IMG_PRJ_BUILD
#define AW_IMG_PRJ_BUILD

#include "apollo.h"
#include "awbus_lite.h"

#include "aw_gpio.h"

#include "aw_bsp_config.h"

#include "awbl_hwconf_led.h"
#include "awbl_hwconf_lpc17xx_nvic.h"
#include "awbl_hwconf_lpc17xx_gpio.h"
#include "awbl_hwconf_lpc17xx_uart0.h"
#include "awbl_hwconf_lpc17xx_uart1.h"
#include "awbl_hwconf_lpc17xx_uart2.h"
#include "awbl_hwconf_lpc17xx_uart3.h"
#include "awbl_hwconf_lpc17xx_uart4.h"
#include "awbl_hwconf_lpc17xx_timer0_timing.h"
#include "awbl_hwconf_lpc17xx_timer1_timing.h"
#include "awbl_hwconf_lpc17xx_timer2_timing.h"
#include "awbl_hwconf_lpc17xx_timer3_timing.h"
#include "awbl_hwconf_lpc17xx_timer0_cap.h"
#include "awbl_hwconf_lpc17xx_timer1_cap.h"
#include "awbl_hwconf_lpc17xx_timer2_cap.h"
#include "awbl_hwconf_lpc17xx_timer3_cap.h"
#include "awbl_hwconf_lpc17xx_pwm0.h"
#include "awbl_hwconf_lpc17xx_pwm1.h"
#include "awbl_hwconf_lpc17xx_pwm0_cap.h"
#include "awbl_hwconf_lpc17xx_pwm1_cap.h"
#include "awbl_hwconf_lpc17xx_mcpwm.h"
#include "awbl_hwconf_lpc17xx_mcpwm_cap.h"
#include "awbl_hwconf_lpc17xx_i2c0.h"
#include "awbl_hwconf_lpc17xx_i2c1.h"
#include "awbl_hwconf_lpc17xx_i2c2.h"
#include "awbl_hwconf_lpc17xx_ssp0.h"
#include "awbl_hwconf_lpc17xx_ssp1.h"
#include "awbl_hwconf_lpc17xx_ssp2.h"
#include "awbl_hwconf_lpc17xx_rtc.h"
#include "awbl_hwconf_lpc17xx_crc.h"
#include "awbl_hwconf_lpc17xx_wwdt.h"
#include "awbl_hwconf_lpc17xx_adc.h"
#include "awbl_hwconf_lpc17xx_dac.h"
#include "awbl_hwconf_lpc17xx_dma.h"
#include "awbl_hwconf_lpc17xx_can_comm.h"
#include "awbl_hwconf_lpc17xx_can1.h"
#include "awbl_hwconf_lpc17xx_can2.h"
#include "awbl_hwconf_lpc17xx_usbd.h"
#include "awbl_hwconf_lpc17xx_sdio.h"
#include "awbl_hwconf_lpc17xx_emac.h"
#include "awbl_hwconf_generic_phy0.h"
#include "awbl_hwconf_lpc17xx_eeprom.h"

#include "awbl_hwconf_spi_flash.h"
#include "awbl_hwconf_pcf8563_0.h"
#include "awbl_hwconf_pcf85063_000.h"
#include "awbl_hwconf_pwm_buzzer.h"
#include "awbl_hwconf_gpio_wdt.h"
#include "awbl_hwconf_gpio_spi0.h"

/*******************************************************************************
  globals
*******************************************************************************/

/*
 * lpc17xx 硬件设备列表 {
 *     p_name,
 *     unit,
 *     bus_type,
 *     bus_index,
 *     p_dev,
 *     p_devinfo
 * }
 */
aw_const struct awbl_devhcf g_awbl_devhcf_list[] = {

    /* nvic */
    AWBL_HWCONF_LPC17XX_NVIC

	/* gpio */
	AWBL_HWCONF_LPC17XX_GPIO

	/* LED */
	AWBL_HWCONF_LED

    /* UART0 */
    AWBL_HWCONF_LPC17XX_UART0

	/* UART1 */
	AWBL_HWCONF_LPC17XX_UART1

	/* UART2 */
	AWBL_HWCONF_LPC17XX_UART2

	/* UART3 */
	AWBL_HWCONF_LPC17XX_UART3

	/* UART4 */
	AWBL_HWCONF_LPC17XX_UART4

	/* DAC */
	AWBL_HWCONF_LPC17XX_DAC

	/* DMA */
	AWBL_HWCONF_LPC17XX_DMA

	/* ADC */
	AWBL_HWCONF_LPC17XX_ADC

	/* standard timer 0 for timing */
	AWBL_HWCONF_LPC17XX_TIMER0_TIMING

	/* standard timer 1 for timing */
	AWBL_HWCONF_LPC17XX_TIMER1_TIMING

	/* standard timer 2 for timing */
	AWBL_HWCONF_LPC17XX_TIMER2_TIMING

	/* standard timer 3 for timing */
	AWBL_HWCONF_LPC17XX_TIMER3_TIMING

	/* standard timer 0 for CAP */
	AWBL_HWCONF_LPC17XX_TIMER0_CAP

	/* standard timer 1 for CAP */
	AWBL_HWCONF_LPC17XX_TIMER1_CAP

	/* standard timer 2 for CAP */
	AWBL_HWCONF_LPC17XX_TIMER2_CAP

	/* standard timer 3 for CAP */
	AWBL_HWCONF_LPC17XX_TIMER3_CAP

	/* PWM0 */
	AWBL_HWCONF_LPC17XX_PWM0

	/* PWM1 */
	AWBL_HWCONF_LPC17XX_PWM1

	/* PWM for CAP */
	AWBL_HWCONF_LPC17XX_PWM0_CAP

	/* PWM for CAP */
	AWBL_HWCONF_LPC17XX_PWM1_CAP

	/* MCPWM */
	AWBL_HWCONF_LPC17XX_MCPWM

	/* MCPWM for CAP */
	AWBL_HWCONF_LPC17XX_MCPWM_CAP

	/* I2C0 */
	AWBL_HWCONF_LPC17XX_I2C_0

	/* I2C1 */
	AWBL_HWCONF_LPC17XX_I2C_1

	/* I2C2 */
	AWBL_HWCONF_LPC17XX_I2C_2

	/* SSP0 */
	AWBL_HWCONF_LPC17XX_SSP_0

	/* SSP1 */
	AWBL_HWCONF_LPC17XX_SSP_1

	/* SSP2 */
	AWBL_HWCONF_LPC17XX_SSP_2

    AWBL_HWCONF_GPIO_SPI0

	/* WDT */
	AWBL_HWCONF_LPC17XX_WDT

    /* PCF8563 RTC */
    AWBL_HWCONF_PCF8563_0

    /* PCF85063 RTC */
    AWBL_HWCONF_PCF85063_0

	/* RTC  */
	AWBL_HWCONF_LPC17XX_RTC

	/* CRC  */
	AWBL_HWCONF_LPC17XX_CRC

	/* CAN1  */
	AWBL_HWCONF_LPC17XX_CAN1

	/* CAN2  */
	AWBL_HWCONF_LPC17XX_CAN2

	/* EMAC  */
	AWBL_HWCONF_LPC17XX_EMAC

	/* EMAC PHY */
    AWBL_HWCONF_GENERIC_PHY0

    /* USBD */
    AWBL_HWCONF_LPC17XX_USBD

    /* SDIO */
    AWBL_HWCONF_LPC17XX_SDIO

    /* EEPROM */
    AWBL_HWCONF_LPC17XX_EEPROM

    /* SPI FLASH */
    AWBL_HWCONF_SPI_FLASH0

    /* PWM BUZZER */
    AWBL_HWCONF_PWM_BUZZER

    /* GPIO WDT */
    AWBL_HWCONF_GPIO_WDT
};

/******************************************************************************/
aw_const struct awbl_devhcf *awbl_devhcf_list_get(void)
{
    return &g_awbl_devhcf_list[0];
}

/******************************************************************************/
size_t awbl_devhcf_list_count_get(void)
{
    return AW_NELEMENTS(g_awbl_devhcf_list);
}

/* end of file */
