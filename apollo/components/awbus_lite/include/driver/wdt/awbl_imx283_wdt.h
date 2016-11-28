/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AWBus IMX283芯片内部看门狗接口头文件
 *
 * 使用本模块需要包含以下头文件：
 * \code
 * #include "awbl_imx283_wdt.h"
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 14-08-27  may, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX283_WDT_H
#define __AWBL_IMX283_WDT_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


/*******************************************************************************
  includes
*******************************************************************************/
#include "apollo.h"
#include "awbus_lite.h"
#include "awbl_wdt.h"


/*******************************************************************************
  define
*******************************************************************************/

/** \brief  定义IMX283看门狗的名称 */
#define  IMX283_WDT_NAME  "imx283-wdt"

/** \brief 定义IMX283看门狗时间信息 */
struct  imx283_wdt_param {
    uint32_t    reg_base;       /**< RTC register base address*/
    uint32_t    wdt_time;       /**< \brief watchdog time (ms)*/
};

/** \brief 定义IMX283看门狗设备 */
struct  imx283_wdt_device {
    struct awbl_dev          dev;    /**< the AWBus device */
    struct awbl_hwwdt_info   info;   /**< hwwdt info */
    uint32_t                 reg_base;
};

/**
 * \brief IMX283 wdt driver register
 */
void  awbl_imx283_wdt_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_IMX283_WDT_H */
