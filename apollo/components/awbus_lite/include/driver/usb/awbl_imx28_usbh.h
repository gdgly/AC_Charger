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
 * \brief imx28 USB host controller driver head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-04-23  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX28_USB_HC_H
#define __AWBL_IMX28_USB_HC_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_clk.h"
#include "host/awbl_usbhbus.h"
#include "host/controller/awbl_usbh_ehci.h"


#define AWBL_IMX28_USBH_DRV_NAME	"awbl_imx28_usbh"


/** \brief imx28 USB host controller struct */
struct awbl_imx28_usbh {
	struct awbl_usbh_ehci ehci;
};

/** \brief imx28 USB host controller information */
struct awbl_imx28_usbh_info {
	struct awbl_usbh_ehci_info ehci_info;

	/** \brief controller register base */
    uint32_t	usb_regbase;

    /** \brief phy register base */
    uint32_t	phy_regbase;

    /** \brief IRQ number */
    int			inum;

    /** \brief clock ID */
    aw_clk_id_t	clk_id;

    void (*pfunc_plfm_init)(void);
};


void awbl_imx28_usbh_drv_register (void);



#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_IMX28_USB_HC_H */
