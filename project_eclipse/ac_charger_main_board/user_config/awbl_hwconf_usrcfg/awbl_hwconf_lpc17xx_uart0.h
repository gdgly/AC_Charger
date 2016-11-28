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
#include "aw_delayed_work.h"


/*******************************************************************************
    UART 0 配置信息
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_UART0

static struct aw_delayed_work g_dir_clr_work;
#define       UART_RS485_DIR_DLY   20         /* 方向控制延时 */
/**
 * 鉴权后无操作超时检测任务
 */
static void dir_clr_work (void *p_arg)
{
    amdr_usart_devinfo_t *p_info = (amdr_usart_devinfo_t *)p_arg;
    aw_gpio_set(PIO4_3, p_info->rs485_ctrl & AMHW_USART_RS485_OINV1 ? 0 : 1);
}
/**
  * \brief 重新启动超时检测
  */
//static
void dir_clr_work_restart()
{
    aw_gpio_set(PIO4_3, 0);
    aw_delayed_work_stop(&g_dir_clr_work);
    aw_delayed_work_start(&g_dir_clr_work, UART_RS485_DIR_DLY);
}


aw_local void __lpc17xx_uart0_rs485_dir (uint8_t dir)
{
    if (dir != 2) {
        aw_gpio_set(PIO4_3, dir);
    } else {
        dir_clr_work_restart();
    }
}

/** \brief The USART0 device information */
const amdr_usart_devinfo_t g_usart0_devinfo = {

	AMHW_USART0,                    /**< \brief 指向USART0寄存器块的指针         */
	INUM_UART0,                     /**< \brief USART0中断号                      */

	AMHW_USART_LCR_8BIT      |      /**< \brief 8-bit数据位                      */
	AMHW_USART_LCR_PARITY_NO |      /**< \brief 无校验                                   */
	AMHW_USART_LCR_STOP_1,          /**< \brief 1-bit停止位                      */

	0,                              /**< \brief 无控制标志                       */

	115200,                         /**< \brief 波特率                           */

	AMHW_USART_RX_TRILEVEL3,        /**< \brief FIFO触发级别为3（14个字节触发）  */

	15,                             /**< \brief FIFO大小为15Byte， 使用RS485时，
                                                MCU上485互发则需要将FIFO设置为15  */
    AMHW_USART_RS485_OINV0,         /* 驱动逻辑为1 */

    UART_RS485_DIR_DLY,             /**< \brief RS485方向控制延时时间  */

	__lpc17xx_uart0_rs485_dir,      /**< \brief GPIO模拟RS485控制管脚方向接口 */

	0,                              /**< \brief 无硬件流控制功能  */

	0,                              /**< \brief 无其他中断                       */
};

amdr_usart_dev_t  g_usart0_dev;     /**< \brief define space for USART0          */

/** \brief USART0 Platform Initialize */
void amhw_plfm_usart0_init (void)
{
     /* Power up the peripheral UART0 */
    amhw_power_periph_up(AMHW_POWER_UART0);

	/* Configure the PIO0_2 operate as UART0_TXD */
    am_gpio_pin_cfg(PIO0_0, PIO0_0_TXD0);

    /* Configure the PIO0_3 operate as UART0_RXD */
    am_gpio_pin_cfg(PIO0_1, PIO0_1_RXD0 | AM_GPIO_PULLUP);

#if 0  /* 硬件RS485z控制时，配置以下管脚 */
    /* Configure the PIO5_4 operate as RS485 UART0 OE */
    am_gpio_pin_cfg(PIO5_4, PIO5_4_OE0);
#else
    /* GPIO 模拟RS485方向脚时，配置以下管脚 */
    am_gpio_pin_cfg(PIO4_3, AM_GPIO_OUTPUT_INIT_HIGH | AM_GPIO_PULLUP);
    aw_gpio_set(PIO4_3, 1);
    aw_delayed_work_init(&g_dir_clr_work,
                          dir_clr_work,
                         &g_usart0_devinfo);
    aw_delayed_work_start(&g_dir_clr_work, g_usart0_devinfo.rs485_dly);
#endif

}

/** \brief USART0 Platform De-initialize */
void amhw_plfm_usart0_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_UART0);
}

/* UART 0 设备信息 */
aw_local aw_const struct awbl_ametal_uart_param __g_ametal_uart0_info = {
    &g_usart0_dev,
    &g_usart0_devinfo,                  /* The hardware device information  */
    (pfunc_uart_init_t)amdr_usart_init, /* The hardware init function       */
    amhw_plfm_usart0_init               /* pfunc_plfm_init                  */
};

aw_local struct awbl_ametal_uart_dev __g_ametal_uart0_dev;

#define AWBL_HWCONF_LPC17XX_UART0   \
    {                               \
        AWBL_AMETAL_UART_NAME,      \
        LPC17XX_UART0_COMID,        \
        AWBL_BUSID_PLB,             \
        0,                          \
        &__g_ametal_uart0_dev.dev,  \
        &__g_ametal_uart0_info      \
    },
#else
    
#define AWBL_HWCONF_LPC17XX_UART0
    
#endif  /* AW_DEV_LPC17XX_UART0 */

/* end of file */

