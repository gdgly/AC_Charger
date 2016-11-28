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

/* 设备信息 */
aw_local aw_const awbl_gpio_spi_devinfo_t __g_gpio_spi0_devinfo = {
    {
        GPIO_SPI0_BUSID,        /* 总线编号 */
    },
    PIO1_19,                     /* sck引脚号 */
    PIO0_13,                     /* mosi引脚号 */
    PIO0_12,                     /* miso引脚号 */
    0xFF,                       /* 接收数据时，MOSI输出值 */
    NULL,                       /* 提供GPIO输出函数，不提供(NULL)则使用系统默认接口 */
    10,                         /* 驱动传输任务优先级 */
    NULL,                       /* 平台相关初始化 */
};

/* 设备实例内存静态分配 */
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
