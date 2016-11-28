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
    UART 4 配置信息
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_UART4

aw_local void __lpc17xx_uart4_rs485_dir (uint8_t dir)
{
    aw_gpio_set(PIO3_23, dir);
}

/** \brief The USART4 device information */
const amdr_usart_devinfo_t g_usart4_devinfo = {

	AMHW_USART4,                    /**< \brief 指向USART4寄存器块的指针         */
	INUM_UART4,                     /**< \brief USART4中断号                     */

	AMHW_USART_LCR_8BIT      |      /**< \brief 8-bit数据位                      */
	AMHW_USART_LCR_PARITY_NO |      /**< \brief 无校验                           */
	AMHW_USART_LCR_STOP_1,          /**< \brief 1-bit停止位                      */

	0,                              /**< \brief 无控制标志                       */

	115200,                         /**< \brief 波特率                           */

	AMHW_USART_RX_TRILEVEL0,        /**< \brief FIFO触发级别为3（14个字节触发）  */

	15,                             /**< \brief FIFO大小为16Byte  */

	AMHW_USART_RS485_OINV0,         /* 驱动逻辑为1 */

	20,                             /**< \brief RS485方向控制延时时间  */

	__lpc17xx_uart4_rs485_dir,      /**< \brief GPIO模拟RS485控制管脚方向接口 */

	0,                              /**< \brief 无硬件流控制  */

	0,                              /**< \brief 无其他中断                       */
};

amdr_usart_dev_t  g_usart4_dev;     /**< \brief define space for USART4          */

/** \brief USART4 Platform Initialize */
void amhw_plfm_usart4_init (void)
{
	  /* Power up the peripheral UART4 */
    amhw_power_periph_up(AMHW_POWER_UART4);

    /* 配置 UART4_TXD管脚 */
    am_gpio_pin_cfg(PIO1_29, PIO1_29_TXD4 | AM_GPIO_PULLUP);

    /* 配置 UART4_RXD管脚 */
    am_gpio_pin_cfg(PIO5_3, PIO5_3_RXD4 | AM_GPIO_PULLUP);
#if 0
    /* 配置 UART4 OE管脚 */
    am_gpio_pin_cfg(PIO0_21, PIO0_21_OE4);
#else
    /* GPIO 模拟RS485方向脚时，配置以下管脚 */
    /* 配置 UART4 OE管脚 */
    am_gpio_pin_cfg(PIO3_23, AM_GPIO_OUTPUT_INIT_HIGH);
//    aw_gpio_set(PIO3_23, 1);
#endif
}

/** \brief USART 4 Platform De-initialize */
void amhw_plfm_usart4_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_UART4);
}

/* UART 4 设备信息 */
aw_local aw_const struct awbl_ametal_uart_param __g_ametal_uart4_info = {
    &g_usart4_dev,
    &g_usart4_devinfo,                  /* The hardware device information  */
    (pfunc_uart_init_t)amdr_usart_init, /* The hardware init function       */
    amhw_plfm_usart4_init               /* pfunc_plfm_init                  */
};



aw_local struct awbl_ametal_uart_dev __g_ametal_uart4_dev;

#define AWBL_HWCONF_LPC17XX_UART4   \
    {                               \
        AWBL_AMETAL_UART_NAME,      \
        LPC17XX_UART4_COMID,        \
        AWBL_BUSID_PLB,             \
        0,                          \
        &__g_ametal_uart4_dev.dev,  \
        &__g_ametal_uart4_info      \
    },
#else
    
#define AWBL_HWCONF_LPC17XX_UART4
    
#endif  /* AW_DEV_LPC17XX_UART4 */

/* end of file */

