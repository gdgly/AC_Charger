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
    UART 4 ������Ϣ
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_UART4

aw_local void __lpc17xx_uart4_rs485_dir (uint8_t dir)
{
    aw_gpio_set(PIO3_23, dir);
}

/** \brief The USART4 device information */
const amdr_usart_devinfo_t g_usart4_devinfo = {

	AMHW_USART4,                    /**< \brief ָ��USART4�Ĵ������ָ��         */
	INUM_UART4,                     /**< \brief USART4�жϺ�                     */

	AMHW_USART_LCR_8BIT      |      /**< \brief 8-bit����λ                      */
	AMHW_USART_LCR_PARITY_NO |      /**< \brief ��У��                           */
	AMHW_USART_LCR_STOP_1,          /**< \brief 1-bitֹͣλ                      */

	0,                              /**< \brief �޿��Ʊ�־                       */

	115200,                         /**< \brief ������                           */

	AMHW_USART_RX_TRILEVEL0,        /**< \brief FIFO��������Ϊ3��14���ֽڴ�����  */

	15,                             /**< \brief FIFO��СΪ16Byte  */

	AMHW_USART_RS485_OINV0,         /* �����߼�Ϊ1 */

	20,                             /**< \brief RS485���������ʱʱ��  */

	__lpc17xx_uart4_rs485_dir,      /**< \brief GPIOģ��RS485���ƹܽŷ���ӿ� */

	0,                              /**< \brief ��Ӳ��������  */

	0,                              /**< \brief �������ж�                       */
};

amdr_usart_dev_t  g_usart4_dev;     /**< \brief define space for USART4          */

/** \brief USART4 Platform Initialize */
void amhw_plfm_usart4_init (void)
{
	  /* Power up the peripheral UART4 */
    amhw_power_periph_up(AMHW_POWER_UART4);

    /* ���� UART4_TXD�ܽ� */
    am_gpio_pin_cfg(PIO1_29, PIO1_29_TXD4 | AM_GPIO_PULLUP);

    /* ���� UART4_RXD�ܽ� */
    am_gpio_pin_cfg(PIO5_3, PIO5_3_RXD4 | AM_GPIO_PULLUP);
#if 0
    /* ���� UART4 OE�ܽ� */
    am_gpio_pin_cfg(PIO0_21, PIO0_21_OE4);
#else
    /* GPIO ģ��RS485�����ʱ���������¹ܽ� */
    /* ���� UART4 OE�ܽ� */
    am_gpio_pin_cfg(PIO3_23, AM_GPIO_OUTPUT_INIT_HIGH);
//    aw_gpio_set(PIO3_23, 1);
#endif
}

/** \brief USART 4 Platform De-initialize */
void amhw_plfm_usart4_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_UART4);
}

/* UART 4 �豸��Ϣ */
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

