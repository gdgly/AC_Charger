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

/**
 * \file
 * \brief AWBus 定义使用GPIO喂狗的硬件设备
 *
 * 使用本模块需要包含以下头文件：
 * \code
 * #include "awbl_hwconf_gpio_wdt.h"
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 14-08-27  may, first implementation
 * \endinternal
 */

#ifndef  __AWBL_HWCONF_GPIO_WDT_H
#define  __AWBL_HWCONF_GPIO_WDT_H


/*******************************************************************************
  includes
*******************************************************************************/
#include "driver/wdt/awbl_gpio_wdt.h"
#include "ametal.h"

#ifdef  AW_DEV_GPIO_WDT

/* GPIO喂狗设备信息 */
aw_local aw_const struct gpio_wdt_param __g_gpio_wdt_param = {
    PIO5_0, 600
};

/* 直流蜂鸣器设备实例内存静态分配 */
aw_local struct gpio_wdt_device __g_gpio_wdt_dev;

#define  AWBL_HWCONF_GPIO_WDT   \
    {                           \
        GPIO_WDT_NAME,          \
        0,                      \
        AWBL_BUSID_PLB,         \
        0,                      \
        &(__g_gpio_wdt_dev.dev),\
        &(__g_gpio_wdt_param)  \
    },
#else   /* AW_DEV_IMX283_RTC */

#define AWBL_HWCONF_GPIO_WDT

#endif

#endif  /* __AWBL_HWCONF_GPIO_WDT_H */
