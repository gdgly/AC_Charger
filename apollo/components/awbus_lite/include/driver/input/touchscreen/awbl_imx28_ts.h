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
 * \brief Freescale i.MX283 touch screen controller
 *
 * \internal
 * \par modification history:
 * - 1.00 14-07-17  ops, first implemetation
 * \endinternal
 */
#ifndef AWBL_IMX28_TS_H_
#define AWBL_IMX28_TS_H_

#include "awbl_input.h"
#include "awbl_touch_screen.h"
#include "awbus_lite.h"
#include "aw_delayed_work.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#define AWBL_IMX28_TOUCHSCREEN_NAME            "imx28_touchscreen"

typedef struct awbl_imx28_ts_devinfo {

	uint32_t regbase;       /* 寄存器基地址 */
	uint8_t x_plus_ch;
	uint8_t x_minus_ch;
	uint8_t y_plus_ch;
	uint8_t y_minus_ch;

    uint8_t detect_interval;

}awbl_imx28_ts_devinfo_t;


typedef struct awbl_imx28_ts_dev {

	/** \bried 继承自Touch SCreen设备 */
	struct awbl_ts_dev tdev;

	/** \brief 继承自 AWBus 设备 */
	struct awbl_dev adev;

	struct aw_delayed_work dwork;

	awbl_imx28_ts_devinfo_t info;

}awbl_imx28_ts_dev_t;

#define AWBL_DEV_TO_IMX28_TS_DEV(pdev)   AW_CONTAINER_OF(pdev, awbl_imx28_ts_dev_t, adev)
#define TS_DEV_TO_IMX28_TS_DEV(pdev)     AW_CONTAINER_OF(pdev, awbl_imx28_ts_dev_t, tdev)
#define TO_IMX28_TS_DEVINFO(pdev)        (awbl_imx28_ts_devinfo_t *)AWBL_DEVINFO_GET(pdev)

/**
 * \brief imx283 pwm driver register
 */
void awbl_imx28_touch_screen_drv_register (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_IMX28_TS_H_ */
