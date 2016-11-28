/*******************************************************************************
*                                 AnyWhere
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

#include "aw_int.h"
#include "aw_gpio.h"

#include "aw_serial.h"
#include "driver/serial/awbl_ametal_uart.h"
#include "ametal.h"

/*******************************************************************************
    UART 2 配置信息
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_UART2

aw_local void __lpc17xx_uart2_rs485_dir (uint8_t dir)
{
    aw_gpio_set(PIO4_9, dir);
}

/** \brief The USART2 device information */
const amdr_usart_devinfo_t g_usart2_devinfo = {

    AMHW_USART2,                    /**< \brief USART2                           */
    INUM_UART2,                     /**< \brief The USART interrupt number       */
    
    AMHW_USART_LCR_8BIT      |      /**< \brief 8-bit data                       */
    AMHW_USART_LCR_PARITY_NO |      /**< \brief No parity                        */
    AMHW_USART_LCR_STOP_1,          /**< \brief 1 stop bit                       */
    
    0,                              /**< \brief No flags to control              */

    115200,                         /**< \brief The baud rate to set             */
    
    AMHW_USART_RX_TRILEVEL0,        /**< \brief FIFO触发级别为3（14个字节触发）  */

    1,                             /**< \brief FIFO大小为15Byte， 使用RS485时，
                                                MCU上485互发则需要将FIFO设置为15  */

	AMHW_USART_RS485_OINV0,         /* 驱动逻辑为0，该参数配置为硬件RS485控制，
	                                                                                        若使用GPIO模拟485控制管脚，亦可在此处配置驱动逻辑*/

	20,                             /**< \brief RS485方向控制延时时间  */

	__lpc17xx_uart2_rs485_dir,      /**< \brief GPIO模拟RS485控制管脚方向接口 */

	0,                              /**< \brief 无硬件流控制  */

    0,                              /**< \brief No other interrupt need          */
};

amdr_usart_dev_t  g_usart2_dev;     /**< \brief define space for USART2          */

/** \brief USART2 Platform Initialize */
void amhw_plfm_usart2_init (void)
{
	  /* Power up the peripheral UART2 */
    amhw_power_periph_up(AMHW_POWER_UART2);

	  /* Configure the PIO2_8 operate as UART2_TXD */
    am_gpio_pin_cfg(PIO2_8,PIO2_8_TXD2 | AM_GPIO_PULLUP);

	  /* Configure the PIO2_9 operate as UART2_RXD */
    am_gpio_pin_cfg(PIO2_9,PIO2_9_RXD2 | AM_GPIO_PULLUP);

#if 0  /* 硬件RS485z控制时，配置以下管脚 */
    /* Configure the PIO2_6 operate as UART1 RS485 RTS1(OE) */
    am_gpio_pin_cfg(PIO2_6,PIO2_6_OE2);
#else  /* GPIO 模拟RS485方向脚时，配置以下管脚 */
    am_gpio_pin_cfg(PIO4_9, AM_GPIO_OUTPUT_INIT_HIGH);
    aw_gpio_set(PIO4_9, 1);
#endif
}

/** \brief USART 2 Platform De-initialize */
void amhw_plfm_usart2_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_UART2);
}

/* UART 2 设备信息 */
aw_local aw_const struct awbl_ametal_uart_param __g_ametal_uart2_info = {
    &g_usart2_dev,
    &g_usart2_devinfo,                  /* The hardware device information  */
    (pfunc_uart_init_t)amdr_usart_init, /* The hardware init function       */
    amhw_plfm_usart2_init               /* pfunc_plfm_init                  */
};



aw_local struct awbl_ametal_uart_dev __g_ametal_uart2_dev;

#define AWBL_HWCONF_LPC17XX_UART2   \
    {                               \
        AWBL_AMETAL_UART_NAME,      \
        LPC17XX_UART2_COMID,        \
        AWBL_BUSID_PLB,             \
        0,                          \
        &__g_ametal_uart2_dev.dev,  \
        &__g_ametal_uart2_info      \
    },
#else
    
#define AWBL_HWCONF_LPC17XX_UART2
    
#endif  /* AW_DEV_LPC17XX_UART2 */

/* end of file */

