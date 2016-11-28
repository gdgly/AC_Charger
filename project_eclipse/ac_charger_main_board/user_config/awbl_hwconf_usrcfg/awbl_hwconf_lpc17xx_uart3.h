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
    UART 3 配置信息
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_UART3

aw_local void __lpc17xx_uart3_rs485_dir (uint8_t dir)
{
//    aw_gpio_set(PIO1_30, dir);
}

/** \brief The USART3 device information */
const amdr_usart_devinfo_t g_usart3_devinfo = {

	AMHW_USART3,                    /**< \brief 指向USART2寄存器块的指针         */
	INUM_UART3,                     /**< \brief USART3中断号                     */

	AMHW_USART_LCR_8BIT      |      /**< \brief 8-bit数据位                      */
	AMHW_USART_LCR_PARITY_NO |      /**< \brief 无校验                           */
	AMHW_USART_LCR_STOP_1,          /**< \brief 1-bit停止位                      */

	0,                              /**< \brief 无控制标志                       */

	115200,                         /**< \brief 波特率                           */

	AMHW_USART_RX_TRILEVEL0,        /**< \brief FIFO触发级别为3（14个字节触发）  */

	15,                             /**< \brief FIFO大小为15Byte， 使用RS485时，
                                                MCU上485互发则需要将FIFO设置为15  */

	AMHW_USART_RS485_OINV0,         /* 驱动逻辑为0，该参数配置为硬件RS485控制，
                                                                                                  若使用GPIO模拟485控制管脚，亦可在此处配置驱动逻辑*/

	20,                             /**< \brief RS485方向控制延时时间  */

	__lpc17xx_uart3_rs485_dir,      /**< \brief GPIO模拟RS485控制管脚方向接口 */

	0,                              /**< \brief 无硬件流控制  */

	0,                              /**< \brief 无其他中断                       */
};

amdr_usart_dev_t  g_usart3_dev;     /**< \brief define space for USART3          */

/** \brief USART3 Platform Initialize */
void amhw_plfm_usart3_init (void)
{
	  /* Power up the peripheral UART3 */
    amhw_power_periph_up(AMHW_POWER_UART3);

	  /* Configure the PIO4_28 operate as UART3_TXD */
    am_gpio_pin_cfg(PIO4_28,PIO4_28_TXD3 | AM_GPIO_PULLUP);
    
	/* Configure the PIO4_29 operate as UART3_RXD */
	am_gpio_pin_cfg(PIO4_29,PIO4_29_RXD3 | AM_GPIO_PULLUP);

#if 0  /* 硬件RS485z控制时，配置以下管脚 */
    /* Configure the PIO1_30 operate as UART3 RS485 OE */
	am_gpio_pin_cfg(PIO1_30,PIO1_30_OE3);
#else  /* GPIO 模拟RS485方向脚时，配置以下管脚 */
//	am_gpio_pin_cfg(PIO4_8, AM_GPIO_OUTPUT_INIT_HIGH);
#endif
}

/** \brief USART 3 Platform De-initialize */
void amhw_plfm_usart3_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_UART3);
}

/* UART 3 设备信息 */
aw_local aw_const struct awbl_ametal_uart_param __g_ametal_uart3_info = {
    &g_usart3_dev,
    &g_usart3_devinfo,                  /* The hardware device information  */
    (pfunc_uart_init_t)amdr_usart_init, /* The hardware init function       */
    amhw_plfm_usart3_init               /* pfunc_plfm_init                  */
};



aw_local struct awbl_ametal_uart_dev __g_ametal_uart3_dev;

#define AWBL_HWCONF_LPC17XX_UART3   \
    {                               \
        AWBL_AMETAL_UART_NAME,      \
        LPC17XX_UART3_COMID,        \
        AWBL_BUSID_PLB,             \
        0,                          \
        &__g_ametal_uart3_dev.dev,  \
        &__g_ametal_uart3_info      \
    },
#else
    
#define AWBL_HWCONF_LPC17XX_UART3
    
#endif  /* AW_DEV_LPC17XX_UART3 */

/* end of file */

