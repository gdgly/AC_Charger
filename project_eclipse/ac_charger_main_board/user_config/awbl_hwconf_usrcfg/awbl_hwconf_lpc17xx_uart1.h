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
    UART 1 ������Ϣ
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_UART1

static struct aw_delayed_work g_uart1_dir_clr_work;
#define       UART1_RS485_DIR_DLY   10              /* ���������ʱ */
#define       UART1_RS485_DIR_PIN   PIO4_8
/**
 * ��Ȩ���޲�����ʱ�������
 */
static void uart1_dir_clr_work (void *p_arg)
{
    aw_gpio_set(UART1_RS485_DIR_PIN, p_arg ? 1 : 0);
}
/**
  * \brief ����������ʱ���
  */
static void uart1_dir_clr_work_restart()
{
    aw_gpio_set(UART1_RS485_DIR_PIN, 0);
    aw_delayed_work_stop(&g_uart1_dir_clr_work);
    aw_delayed_work_start(&g_uart1_dir_clr_work, UART_RS485_DIR_DLY);
}

aw_local void __lpc17xx_uart1_rs485_dir (uint8_t dir)
{
    if (dir != 2) {
       aw_gpio_set(UART1_RS485_DIR_PIN, dir);
    } else {
        uart1_dir_clr_work_restart();
    }
}


/** \brief The USART1 device information */
const amdr_usart_devinfo_t g_usart1_devinfo = {

	AMHW_USART1,                    /**< \brief ָ��USART1�Ĵ������ָ��         */
	INUM_UART1,                     /**< \brief USART1�жϺ�                     */

	AMHW_USART_LCR_8BIT      |      /**< \brief 8-bit����λ                      */
	AMHW_USART_LCR_PARITY_NO |      /**< \brief ��У��                           */
	AMHW_USART_LCR_STOP_1,          /**< \brief 1-bitֹͣλ                      */

	0,                              /**< \brief �޿��Ʊ�־                       */

	115200,                         /**< \brief ������                           */

	AMHW_USART_RX_TRILEVEL0,        /**< \brief FIFO��������Ϊ3��14���ֽڴ�����  */

	15,                             /**< \brief FIFO��СΪ15Byte�� ʹ��RS485ʱ��
                                                MCU��485��������Ҫ��FIFO����Ϊ15  */

	AMHW_USART_RS485_OINV0,         /* �����߼�Ϊ0���ò�������ΪӲ��RS485���ƣ�
                                                                                                  ��ʹ��GPIOģ��485���ƹܽţ�����ڴ˴����������߼�*/

	UART1_RS485_DIR_DLY,             /**< \brief RS485���������ʱʱ��  */

	__lpc17xx_uart1_rs485_dir,      /**< \brief GPIOģ��RS485���ƹܽŷ���ӿ� */

	AMHW_USART_MCR_RTS   |          /**< \brief Ӳ����������Ϣ  */
	AMHW_USART_MCR_RTSEN |
	AMHW_USART_MCR_CTSEN,


	0,                              /**< \brief �������ж�                       */
};

amdr_usart_dev_t  g_usart1_dev;     /**< \brief define space for USART1          */

/** \brief USART1 Platform Initialize */
void amhw_plfm_usart1_init (void)
{
	  /* Power up the peripheral UART1 */
    amhw_power_periph_up(AMHW_POWER_UART1);

	/* Configure the PIO0_15 operate as UART1_TXD */
    am_gpio_pin_cfg(PIO0_15,PIO0_15_TXD1);

	/* Configure the PIO0_16 operate as UART1_RXD */
    am_gpio_pin_cfg(PIO0_16,PIO0_16_RXD1 | AM_GPIO_PULLUP);

#if 0  /* Ӳ��RS485z����ʱ���������¹ܽ� */
    /* RTS1(OE) */
//    am_gpio_pin_cfg(PIO0_22, PIO0_22_RTS1);
#else
    /* GPIO ģ��RS485�����ʱ���������¹ܽ� */
    am_gpio_pin_cfg(UART1_RS485_DIR_PIN, AM_GPIO_OUTPUT_INIT_LOW);
    aw_gpio_set(UART1_RS485_DIR_PIN, 0);
    aw_delayed_work_init(&g_uart1_dir_clr_work,
                          uart1_dir_clr_work,
                        (void *)(g_usart1_devinfo.rs485_ctrl & AMHW_USART_RS485_OINV1 ? 0 : 1));
    aw_delayed_work_start(&g_uart1_dir_clr_work, UART1_RS485_DIR_DLY);

#endif

//    /* CTS1 */
//    am_gpio_pin_cfg(PIO3_18, PIO3_18_CTS1);

}

/** \brief USART 1 Platform De-initialize */
void amhw_plfm_usart1_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_UART1);
}

/* UART 1 �豸��Ϣ */
aw_local aw_const struct awbl_ametal_uart_param __g_ametal_uart1_info = {
    &g_usart1_dev,
    &g_usart1_devinfo,                  /* The hardware device information  */
    (pfunc_uart_init_t)amdr_usart_init, /* The hardware init function       */
    amhw_plfm_usart1_init               /* pfunc_plfm_init                  */
};



aw_local struct awbl_ametal_uart_dev __g_ametal_uart1_dev;

#define AWBL_HWCONF_LPC17XX_UART1   \
    {                               \
        AWBL_AMETAL_UART_NAME,      \
        LPC17XX_UART1_COMID,        \
        AWBL_BUSID_PLB,             \
        0,                          \
        &__g_ametal_uart1_dev.dev,  \
        &__g_ametal_uart1_info      \
    },
#else
    
#define AWBL_HWCONF_LPC17XX_UART1
    
#endif  /* AW_DEV_LPC17XX_UART1 */

/* end of file */

