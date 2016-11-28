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
 * \brief c674x USB device controller driver head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-09-21  deo, first implementation
 * \endinternal
 */


#ifndef __AWBL_C674X_USBH_H
#define __AWBL_C674X_USBH_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "host/awbl_usbhbus.h"
#include "host/controller/awbl_usbh_ohci.h"
#include "aw_clk.h"

#define AWBL_C674X_USBH_DRV_NAME    "awbl_c674x_usbh"


/** \brief imx28 USB host controller struct */
struct awbl_c674x_usbh {
    struct awbl_usbh_ohci ohci;
};

/** \brief imx28 USB host controller information */
struct awbl_c674x_usbh_info {
    struct awbl_usbh_ohci_info ohci_info;

    /** \brief controller register base */
    uint32_t    reg_base;

    /** \brief IRQ number */
    int         inum;

    void (*pfunc_plfm_init)(void);
};


void awbl_c674x_usbh_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */


#endif /* __AWBL_C674X_USBH_H */
