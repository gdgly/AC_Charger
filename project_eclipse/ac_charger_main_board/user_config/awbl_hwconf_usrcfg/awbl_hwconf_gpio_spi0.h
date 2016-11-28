/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      aworks.support@zlg.cn
*******************************************************************************/

#ifndef __AWBL_HWCONF_GPIO_SPI0_H
#define __AWBL_HWCONF_GPIO_SPI0_H

#ifdef AW_DEV_GPIO_SPI_0

#include "aw_gpio.h"
#include "driver/busctlr/awbl_gpio_spi.h"

/* �豸��Ϣ */
aw_local aw_const awbl_gpio_spi_devinfo_t __g_gpio_spi0_devinfo = {
    {
        GPIO_SPI0_BUSID,        /* ���߱�� */
    },
    PIO1_19,                     /* sck���ź� */
    PIO0_13,                     /* mosi���ź� */
    PIO0_12,                     /* miso���ź� */
    0xFF,                       /* ��������ʱ��MOSI���ֵ */
    NULL,                       /* �ṩGPIO������������ṩ(NULL)��ʹ��ϵͳĬ�Ͻӿ� */
    10,                         /* ���������������ȼ� */
    NULL,                       /* ƽ̨��س�ʼ�� */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local awbl_gpio_spi_dev_t __g_gpio_spi0_dev;

#define AWBL_HWCONF_GPIO_SPI0                   \
    {                                           \
        AWBL_GPIO_SPI_NAME,                     \
        0,                                      \
        AWBL_BUSID_PLB,                         \
        0,                                      \
        &__g_gpio_spi0_dev.super.super.super,   \
        &__g_gpio_spi0_devinfo                  \
    },

#else
#define AWBL_HWCONF_GPIO_SPI0

#endif  /* AW_DEV_GPIO_SPI_0 */

#endif  /* __AWBL_HWCONF_GPIO_SPI0_H */

/* end of file */
