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
 * \brief USB device aworks class head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-06-07  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USBD_AWORKS_H
#define __AWBL_USBD_AWORKS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "device/awbl_usbd.h"
#include "aw_list.h"

/* usbd aworks transfer */
struct awbl_usbd_aworks_transfer {
    struct awbl_usbd_transfer trf;
};

/* usbd aworks */
struct awbl_usbd_aworks {
    /* class struct */
    struct awbl_usbd_class              uclass;

    /* controller */
    struct awbl_usbd                    *p_usbd;

    /* information */
    const struct awbl_usbd_aworks_info  *info;

    /* configuration */
    struct awbl_usbd_cfg                cfg;

    /* interface */
    struct awbl_usbd_itf                itf;

    /* EPs */
    struct aw_list_head                 ep_list;

    /* device descriptor */
    struct awbl_usb_device_desc         dev_desc;

    /* configure descriptor */
    struct awbl_usb_config_desc         cfg_desc;

    /* interface descriptor */
    struct awbl_usb_interface_desc      itf_desc;

    /* alt and EPs descriptor pointer */
    struct awbl_usb_desc_header         **alt_desc;

    /* string */
    struct awbl_usbd_string             string[5];

    /* count of EPs */
    uint8_t                             neps;

    bool_t                              config;
    bool_t                              connected;

    /* wait for connect list */
    struct aw_list_head                 wfc_list;
    aw_spinlock_isr_t                   wfc_lock;
};

/* usbd aworks information */
struct awbl_usbd_aworks_info {
    uint16_t                vid;
    uint16_t                pid;
    uint16_t                bcd;
    const char              *manufacturer;
    const char              *product;
    const char              *serial_num;
    const char              *configuraton;
    const char              *interface;

    /* handle setup packet */
    int (*ctrl_setup) ( struct awbl_usbd_aworks *aworks,
                        struct awbl_usb_ctrlreq *p_setup,
                        void                    *p_buf,
                        int                     buf_len);

    /* device connect */
    void (*connect) (struct awbl_usbd_aworks    *aworks);

    /* device disconnect */
    void (*disconnect) (struct awbl_usbd_aworks *aworks);
};

/******************************************************************************/
aw_err_t awbl_usbd_aworks_init (
        struct awbl_usbd_aworks             *p_aworks,
        const struct awbl_usbd_aworks_info  *info,
        const char                          *controller);

/******************************************************************************/
void awbl_usbd_aworks_uninit (struct awbl_usbd_aworks *p_aworks);

/******************************************************************************/
aw_err_t awbl_usbd_aworks_start (struct awbl_usbd_aworks *p_aworks);

/******************************************************************************/
aw_err_t awbl_usbd_aworks_stop (struct awbl_usbd_aworks *p_aworks);

/******************************************************************************/
aw_err_t awbl_usbd_aworks_create_ep (struct awbl_usbd_aworks *p_aworks,
                                     uint8_t                 ep_addr,
                                     uint8_t                 type,
                                     uint32_t                max_pkt_size);

/******************************************************************************/
aw_err_t awbl_usbd_aworks_reset_ep (struct awbl_usbd_aworks *p_aworks,
                                    uint8_t                 ep_addr);

/******************************************************************************/
aw_err_t awbl_usbd_aworks_init_transfer (
        struct awbl_usbd_aworks           *p_aworks,
        struct awbl_usbd_aworks_transfer  *p_trf,
        uint8_t                           ep_addr,
        void                              *p_buf,
        int                               len,
        int                               flag,
        void                              (*complete) (void *arg),
        void                              *arg);

/******************************************************************************/
aw_err_t awbl_usbd_aworks_sync_transfer (
                                    struct awbl_usbd_aworks *p_aworks,
                                    uint8_t                 ep_addr,
                                    void                    *p_buf,
                                    int                     len,
                                    int                     timeout);

/******************************************************************************/
aw_err_t awbl_usbd_aworks_async_transfer (
        struct awbl_usbd_aworks           *p_aworks,
        struct awbl_usbd_aworks_transfer  *p_trf);

/******************************************************************************/
aw_err_t awbl_usbd_aworks_cacel_transfer (
            struct awbl_usbd_aworks           *p_aworks,
            struct awbl_usbd_aworks_transfer  *p_trf);

/******************************************************************************/
bool_t awbl_aworks_is_connected (struct awbl_usbd_aworks *p_aworks);

/******************************************************************************/
aw_err_t awbl_aworks_wait_for_connect (struct awbl_usbd_aworks *p_aworks,
                                       int                     timeout);
#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBD_AWORKS_H */
