/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB host device base driver
 *
 * \internal
 * \par modification history:
 * - 1.00 15-05-15  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USBH_DEVDRV_H
#define __AWBL_USBH_DEVDRV_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#define AWBL_USBH_DEVDRV_NAME "awbl_usbh_devdrv_name"

void awbl_usbh_device_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_DEVDRV_H */
