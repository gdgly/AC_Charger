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
 * \brief USB host hub
 *
 * \internal
 * \par modification history:
 * - 1.00 15-04-09  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USBH_HUB_H
#define __AWBL_USBH_HUB_H


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "apollo.h"
#include "aw_list.h"
#include "host/awbl_usbhbus.h"

#define AWBL_USBH_HUB_DRV_NAME  "awbl_usbh_hub_driver"

/** \brief USB hub status */
struct awbl_usbh_hub_status {
    uint16_t status;
    uint16_t change;
};

/** \brief USB hub */
struct awbl_usbh_hub {
    /* USB device */
    struct awbl_usbh_device     *p_udev;
    /* USB interface */
    struct awbl_usbh_interface  *p_itf;

    /* hub descriptor */
    struct awbl_usbh_hub_desc   *desc;

    struct aw_list_head node;

    struct awbl_usbh_hub_status *p_status;

    /* interrupt TRP */
    struct awbl_usbh_trp        int_trp;
    uint8_t                     err_cnt;
#ifdef __USBH_HUB_PORT_STATUS_MASK__
    uint16_t                    status_mask;
#endif

    /* children device on this hub */
    struct awbl_usbh_device     **ports;

    uint16_t                    mA_per_port;
    bool_t                      has_indicators;
    uint8_t                     indicator[AWBL_USBH_MAX_CHILDREN];

    bool_t                      remove_en;

};


#define usbh_hub_get_hub_status(p_hub, p_status)    \
        __hub_get_status(p_hub, p_status, FALSE, 0)
#define usbh_hub_get_port_status(p_hub, p_status, port_num) \
        __hub_get_status(p_hub, p_status, TRUE, port_num)

#define usbh_hub_set_hub_feature(p_hub, feature)    \
        __hub_feature_req(p_hub, feature, FALSE, 0, TRUE)
#define usbh_hub_clr_hub_feature(p_hub, feature) \
        __hub_feature_req(p_hub, feature, FALSE, 0, FALSE)
#define usbh_hub_set_port_feature(p_hub, feature, port_num) \
        __hub_feature_req(p_hub, feature, TRUE, port_num, TRUE)
#define usbh_hub_clr_port_feature(p_hub, feature, port_num) \
        __hub_feature_req(p_hub, feature, TRUE, port_num, FALSE)

aw_err_t awbl_usbh_hub_create_root_hub (struct awbl_usbh *p_hc);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_HUB_H */
