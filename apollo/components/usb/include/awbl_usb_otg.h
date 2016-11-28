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
 * \brief USB OTG support head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-07-07  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USB_OTG_H
#define __AWBL_USB_OTG_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbus_lite.h"


struct awbl_usb_otg {
    struct awbl_dev awdev;

    uint8_t         state;
#define OTG_STATE_UNDEFINED         0
        /* single-role peripheral, and dual-role default-b */
#define OTG_STATE_B_IDLE            1
#define OTG_STATE_B_SRP_INIT        2
#define OTG_STATE_B_PERIPHERAL      3
        /* extra dual-role default-b states */
#define OTG_STATE_B_WAIT_ACON       4
#define OTG_STATE_B_HOST            5
        /* dual-role default-a */
#define OTG_STATE_A_IDLE            6
#define OTG_STATE_A_WAIT_VRISE      7
#define OTG_STATE_A_WAIT_BCON       8
#define OTG_STATE_A_HOST            9
#define OTG_STATE_A_SUSPEND         10
#define OTG_STATE_A_PERIPHERAL      11
#define OTG_STATE_A_WAIT_VFALL      12
#define OTG_STATE_A_VBUS_ERR        13

    struct awbl_usbh    *p_usbh;
    struct awbl_usbd    *p_usbd;

};


struct awbl_usb_otg_drv {
    struct awbl_drvinfo awdrv;

    void (*shutdown)(struct awbl_usb_otg *p_otg);

    int (*set_host)(struct awbl_usb_otg *p_otg,
                    struct awbl_usbh    *p_usbh);

    int (*set_peripheral)(struct awbl_usb_otg *p_otg,
                          struct awbl_usbd    *p_usbd);

    /* effective for B devices, ignored for A-peripheral */
    int (*set_power)(struct awbl_usb_otg  *p_otg,
                     unsigned int         mA);

    /* effective for A-peripheral, ignored for B devices */
    int (*set_vbus)(struct awbl_usb_otg *p_otg,
                    bool_t              enabled);

    /* for non-OTG B devices: set transceiver into suspend mode */
    int (*set_suspend)(struct awbl_usb_otg  *p_otg,
                       int                  suspend);

    /* for B devices only:  start session with A-Host */
    int (*start_srp)(struct awbl_usb_otg *p_otg);

    /* start or continue HNP role switch */
    int (*start_hnp)(struct awbl_usb_otg *p_otg);
};

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_USB_OTG_H_ */
