
/*
 *  此文件由配置工具生产，请勿修改。
 *  现在作为一个例子。
 */
#undef  AW_IMG_PRJ_BUILD
#define AW_IMG_PRJ_BUILD

#include "apollo.h"
#include "rtk.h"
#include "aw_task.h"
#include "aw_exc.h"
#include "aw_serial.h"
#include "aw_isr_defer.h"
#include "aw_vdebug.h"

#include "aw_prj_params.h"
#include "awbl_driver_if.h"

/* including c source files */
#include "all/aworks_startup.c"
#include "all/aw_psp_startup.c"
#include "all/aw_psp_usr_app_init.c"
#include "core/awbus_lite_cfg.c"
#include "core/awbus_input_cfg.c"

#include "os/aw_isr_defer_cfg.c"

#ifdef AW_COM_EVENT
#include "util/aw_event_cfg.c"
#endif

#ifdef AW_SHELL_SERIAL
#include "aw_shell_cfg.c"
#endif

#ifdef AW_COM_AWBL_SERIAL
#include "driver/serial/awbl_serial_cfg.c"
#endif  /* AW_COM_AWBL_SERIAL */

#ifdef AW_COM_NETWORK
#include "aw_net.h"
#include "ppp/sio_mgn.h"
#endif  /* AW_COM_NETWORK */

#ifdef AW_USING_CPLUSPLUS
extern void aw_cplusplus_runtime_init(void);
#endif

#ifdef AW_DRV_MTD_DEV
#include "mtd/aw_mtd.h"
#endif

#ifdef AW_DRV_BLOCK_DEV
#include "fs/aw_block_dev.h"
#endif

#include "awbl_digitron_if.h"


static void awbl_group_init( void )
{
    #include "awbl_led.h"
    awbus_lite_init();
    awbl_plb_register();

#ifdef AW_COM_AWBL_INTCTLR
    awbl_armcm_nvic_drv_register();
#endif  /* AW_COM_AWBL_INTCTLR */

    awbl_ametal_gpio_drv_register();

#ifdef AW_DEV_LPC17XX_DMA
    awbl_lpc17xx_dma_drv_register();
#endif  /* AW_DRV_AWBL_LPC17XX_DMA*/

#ifdef AW_DRV_AWBL_LPC17XX_PWM
    awbl_ametal_pwm_drv_register();
#endif  /* AW_DRV_AWBL_LPC17XX_PWM*/

#ifdef AW_COM_AWBL_PWM_BUZZER
    awbl_pwm_buzzer_drv_register();
#endif

#ifdef AW_DRV_AWBL_LPC17XX_CAP
    awbl_ametal_cap_drv_register();
#endif  /* AW_DRV_AWBL_LPC17XX_CAP*/

#ifdef AW_DRV_AWBL_LPC17XX_I2C
    awbl_ametal_i2c_drv_register();
#endif /* AW_DRV_AWBL_LPC17XX_I2C */

#ifdef AW_DRV_AWBL_LPC17XX_UART
    awbl_ametal_uart_drv_register();
#endif /* AW_DRV_AWBL_LPC17XX_UART */

#ifdef AW_DEV_LPC17XX_DAC
	awbl_ametal_dac_drv_register();
#endif /* AW_DEV_LPC17XX_DAC */

#ifdef AW_DEV_LPC17XX_ADC
    awbl_ametal_adc_drv_register();
#endif /* AW_DRV_AWBL_LPC17XX_ADC */

#ifdef AW_DEV_LPC17XX_CRC
	awbl_ametal_crc_drv_register();
#endif /* AW_DRV_AWBL_LPC17XX_CRC */

#ifdef AW_DRV_AWBL_LPC17XX_SPI
	awbl_ametal_spi_drv_register();
#endif /* AW_DRV_AWBL_LPC17XX_SPI */

#ifdef AW_DRV_AWBL_LPC17XX_TIMER
    awbl_ametal_timer_drv_register();
#endif /* AW_DRV_AWBL_LPC17XX_TIMER */

#ifdef AW_DEV_LPC17XX_USBD
	awbl_lpc17xx_usbd_drv_register();
#endif /* AW_DEV_LPC17XX_USBD */

#ifdef AW_DEV_LPC17XX_WDT
    awbl_ametal_wdt_drv_register();
#endif /* AW_DEV_LPC17XX_WDT */

#if defined(AW_COM_AWBL_LED) || defined(AW_DEV_LED_GPIO)
#ifdef AW_DRV_AWBL_GPIO_LED
    awbl_led_gpio_drv_register();
#endif  /* AW_DRV_AWBL_GPIO_LED */
#endif  /* AW_COM_AWBL_LED */

#ifdef AW_COM_AWBL_I2CBUS
    awbl_i2cbus_init();
#endif /* AW_COM_AWBL_I2CBUS */

#ifdef AW_COM_AWBL_SPIBUS
    awbl_spibus_init();
#endif /* AW_COM_AWBL_SPIBUS */

#ifdef AW_DEV_LPC17XX_RTC
    awbl_ametal_rtc_drv_register();
#endif /* AW_DEV_LPC17XX_RTC */

#ifdef AW_DRV_AWBL_LPC17XX_EMAC
    awbl_miibus_init();
    awbl_generic_phy_drv_register();
    awbl_17xx_emac_drv_register();
#endif /* AW_DRV_AWBL_LPC17XX_EMAC */

#ifdef AW_COM_AWBL_SDIOBUS
    awbl_sdiobus_init();
#endif /* AW_COM_AWBL_SDIOBUS */

#ifdef AW_DEV_AWBL_SDCARD
    awbl_sdcard_drv_register();
#endif /* AW_DEV_AWBL_SDCARD */

#ifdef AW_DEV_LPC17XX_SDIO
    awbl_ametal_sdio_drv_register();
#endif /* AW_DEV_LPC17XX_SDIO */

#ifdef AW_DRV_AWBL_LPC17XX_CAN
    awbl_ametal_can_drv_register();
#endif /* AW_DRV_AWBL_LPC17XX_CAN */

#ifdef AW_DRV_AWBL_LPC17XX_EEPROM
    awbl_lpc17xx_eeprom_drv_register();
#endif

#ifdef AW_DRV_AWBL_GPIO_SPI
    awbl_gpio_spi_drv_register();
#endif

#ifdef AW_DRV_AWBL_NOR_FLASH
    awbl_spi_flash_drv_register();
#endif

#ifdef AW_DEV_EXTEND_PCF8563_0
    awbl_pcf8563_drv_register();
#endif /* AW_DEV_EXTEND_PCF8563_0 */

#ifdef AW_DRV_AWBL_PCF85063
    awbl_pcf85063_drv_register();
#endif /* AW_DEV_EXTEND_PCF8563_0 */

#ifdef AW_DRV_AWBL_GPIO_WDT
    awbl_gpio_wdt_drv_register();
#endif
}

void aw_prj_early_init( void )
{
    awbl_group_init();

    /* AWBus init phase 1 */
    awbl_dev_init1();
    awbl_intctlr_init();    /* AWBus IntCtlr service up */
    awbl_gpio_init();       /* AWBus GPIO service up */

#ifdef AW_COM_AWBL_LED
    awbl_led_init();        /* AWBus LED service up */
#endif

    awbl_pwm_init();        /* AWBus PWM service up */

    /*
     * Initialize serial I/O for kernel output. after this call, kprintf()
     * is ready for use
     */
#ifdef AW_COM_CONSOLE
    aw_koutput_sio_init(AW_CFG_CONSOLE_COMID, AW_CFG_CONSOLE_BAUD_RATE);
    aw_serial_ioctl(AW_CFG_CONSOLE_COMID, SIO_MODE_SET, (void *)SIO_MODE_INT);
#endif  /* AW_COM_CONSOLE */

#ifdef AW_COM_AWBL_ADC
    awbl_adc_init();
#endif  /* AW_COM_AWBL_ADC */

#ifdef AW_COM_AWBL_DAC
    awbl_dac_init();
#endif  /* AW_COM_AWBL_DAC */

#if defined(AW_COM_AWBL_CAP)
    awbl_cap_init();
#endif  /* AW_COM_AWBL_CAP */

}

void aw_prj_task_level_init( void )
{
	/* isr deferral library initialization */
    aw_isr_defer_lib_init();

    /* event lib initialization */
#ifdef AW_COM_EVENT
    aw_event_lib_init();
#endif

#ifdef AW_DRV_BLOCK_DEV
    aw_block_dev_lib_init();    /* block device lib initialization */
#endif

#ifdef AW_DRV_MTD_DEV
    aw_mtd_lib_init();
#endif

    /* AWBus init phase 2 */
    awbl_dev_init2();

    /* system tick initialization */
    systick_init(AW_CFG_TICKS_PER_SECOND);

#ifdef AW_COM_AWBL_RTC
    awbl_rtc_init();
#endif /* AW_COM_AWBL_RTC */

	/* system time initialization */
	aw_time_lib_init(aw_sys_clkrate_get(),0);

#ifdef AW_COM_NETWORK
	net_init();
	sio_list_init();
#endif

    /* AWBus init phase 3 */
    awbl_dev_connect();

#ifdef AW_COM_AWBL_SERIAL
    aw_serial_init();
#endif  /* AW_COM_AWBL_SERIAL */

#ifdef AW_SHELL_SERIAL
    aw_serial_shell_cfg();
#endif

#ifdef AW_COM_AWBL_WDT
    awbl_wdt_init();
#endif  /* AW_COM_AWBL_WDT */

#ifdef AW_USING_CPLUSPLUS
    aw_cplusplus_runtime_init();
#endif
}

