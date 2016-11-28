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
 * \brief AWBus ����ʹ��GPIOι����Ӳ���豸
 *
 * ʹ�ñ�ģ����Ҫ��������ͷ�ļ���
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

/* GPIOι���豸��Ϣ */
aw_local aw_const struct gpio_wdt_param __g_gpio_wdt_param = {
    PIO5_0, 600
};

/* ֱ���������豸ʵ���ڴ澲̬���� */
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
