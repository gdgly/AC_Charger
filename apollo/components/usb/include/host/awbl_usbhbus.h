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
 * \brief USB host bus
 *
 * \internal
 * \par modification history:
 * - 1.00 15-04-04  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USBHBUS_H
#define __AWBL_USBHBUS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "apollo.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "awbus_lite.h"
#include "aw_list.h"
#include "awbl_usb_cfg.h"
#include "awbl_usb_mem.h"

/****************************************************************************/
#define __AWBL_USBH_DECL(p_hc, p_awdev) \
    struct awbl_usbh *p_hc = \
        (struct awbl_usbh *)AW_CONTAINER_OF( \
            p_awdev, struct awbl_usbh, super)

#define __AWBL_USBH_INFO_DECL(p_info, p_awdev) \
    struct awbl_usbh_info *p_info = \
        (struct awbl_usbh_info *)AWBL_DEVINFO_GET(p_awdev)

#define __AWBL_USBH_DEV_DECL(p_udev, p_awdev) \
    struct awbl_usbh_device *p_udev = \
        (struct awbl_usbh_device *)AW_CONTAINER_OF( \
            p_awdev, struct awbl_usbh_device, udev)

#define __AWBL_USBH_ITF_DECL(p_itf, p_awdev) \
    struct awbl_usbh_interface *p_itf = \
        (struct awbl_usbh_interface *)AW_CONTAINER_OF( \
            p_awdev, struct awbl_usbh_interface, udev)

#define __AWBL_USBH_DRV(p_drv, p_awdrv) \
    struct awbl_usbh_drv *p_drv = \
        (struct awbl_usbh_drv *)AW_CONTAINER_OF( \
            p_awdrv, struct awbl_usbh_drv, drv)

#define __AWBL_USBH_DEVBASE_DRV(p_drv, p_awdrv) \
    struct awbl_usbh_devbase_drv *p_drv = \
        (struct awbl_usbh_devbase_drv *)AW_CONTAINER_OF( \
            p_awdrv, struct awbl_usbh_devbase_drv, drv)

#define __AWBL_USBH_ITF_DRV(p_drv, p_awdrv) \
    struct awbl_usbh_itfdev_drv *p_drv = \
        (struct awbl_usbh_itfdev_drv *)AW_CONTAINER_OF( \
            p_awdrv, struct awbl_usbh_itfdev_drv, devdrv)

#define AWBL_USBH_EP_TYPE(p_ep) \
            awbl_usb_ep_tr_type((p_ep)->desc)
#define AWBL_USBH_EP_NUM(p_ep) \
            awbl_usb_ep_num((p_ep)->desc)
#define AWBL_USBH_EP_MPS(p_ep) \
            awbl_usb_ep_max_pkt_size((p_ep)->desc)
#define AWBL_USBH_EP_DIR(p_ep) \
            awbl_usb_ep_dir((p_ep)->desc)
#define AWBL_USBH_EP_ITV(p_ep) \
            awbl_usb_ep_interval((p_ep)->desc)





#define AWBL_USBH_MISC_DEVICE_CLASS               0xEF
#define AWBL_USBH_MULTI_INTERFACE_FUNC_CLASS      AWBL_USBH_MISC_DEVICE_CLASS

#define AWBL_USBH_COMMON_CLASS                    0x02
#define AWBL_USBH_MULTI_INTERFACE_FUNC_SUBCLASS   AWBL_USBH_COMMON_CLASS

#define AWBL_USBH_INTERFACE_ASSOC_DESC            0x01
#define AWBL_USBH_MULTI_INTERFACE_FUNC_PROTOCOL   AWBL_USBH_INTERFACE_ASSOC_DESC


AWBL_METHOD_IMPORT(awbl_remove_dev);


#include "awbl_usb_descriptor.h"

struct awbl_usbh_drv;
struct awbl_usbh_devbase_drv;
struct awbl_usbh_devdrv_info;
struct awbl_usbh_device_drv;
struct awbl_usbh_itfdev_drv;
struct awbl_usbh;
struct awbl_usbh_info;
struct awbl_usbh_device;
struct awbl_usbh_config;
struct awbl_usbh_interface;
struct awbl_usbh_endpoint;
struct awbl_usbh_trp;


/** \brief USB host driver */
struct awbl_usbh_drv {
    struct awbl_drvinfo drv;

    /* reset controller */
    aw_err_t (*reset) (struct awbl_usbh *p_hc);

    /* request transfer */
    aw_err_t (*request)(struct awbl_usbh *p_hc, struct awbl_usbh_trp *p_trp);

    /* cancel transfers */
    aw_err_t (*cancel)(struct awbl_usbh *p_hc, struct awbl_usbh_trp *p_trp);

    /* enable EP */
    aw_err_t (*ep_en)(struct awbl_usbh *p_hc, struct awbl_usbh_endpoint *p_ep);

    /* disable EP */
    aw_err_t (*ep_dis)(struct awbl_usbh *p_hc, struct awbl_usbh_endpoint *p_ep);

    /* reset EP */
    aw_err_t (*ep_rst)(struct awbl_usbh *p_hc, struct awbl_usbh_endpoint *p_ep);

    /* request root hub transfer */
    aw_err_t (*rh_req)(struct awbl_usbh *p_hc, struct awbl_usbh_trp *p_trp);

    /* cancel root hub transfer */
    aw_err_t (*rh_cancel)(struct awbl_usbh *p_hc, struct awbl_usbh_trp *p_trp);
};

/** \brief USB host driver base */
struct awbl_usbh_devbase_drv {
    struct awbl_drvinfo drv;
    bool_t is_interface;
};

/** \brief USB host driver information */
struct awbl_usbh_devdrv_info {
    uint16_t    match_flags;
#define USBH_DRV_INFO_MATCH_VENDOR          0x0001
#define USBH_DRV_INFO_MATCH_PRODUCT         0x0002
#define USBH_DRV_INFO_MATCH_DEV_LO          0x0004
#define USBH_DRV_INFO_MATCH_DEV_HI          0x0008
#define USBH_DRV_INFO_MATCH_DEV_CLASS       0x0010
#define USBH_DRV_INFO_MATCH_DEV_SUBCLASS    0x0020
#define USBH_DRV_INFO_MATCH_DEV_PROTOCOL    0x0040
#define USBH_DRV_INFO_MATCH_INT_CLASS       0x0080
#define USBH_DRV_INFO_MATCH_INT_SUBCLASS    0x0100
#define USBH_DRV_INFO_MATCH_INT_PROTOCOL    0x0200
#define USBH_DRV_INFO_MATCH_INT_NUMBER      0x0400

    uint16_t    idVendor;
    uint16_t    idProduct;
    uint16_t    bcdDevice_lo;
    uint16_t    bcdDevice_hi;

    uint8_t     bDeviceClass;
    uint8_t     bDeviceSubClass;
    uint8_t     bDeviceProtocol;

    uint8_t     bInterfaceClass;
    uint8_t     bInterfaceSubClass;
    uint8_t     bInterfaceProtocol;

    uint8_t     bInterfaceNumber;
};

/** \brief USB host device driver */
struct awbl_usbh_device_drv {
    struct awbl_usbh_devbase_drv devdrv;

    void (*disconnect) (struct awbl_usbh_device *p_udev);
    int (*suspend) (struct awbl_usbh_device *p_udev);
    int (*resume) (struct awbl_usbh_device *p_udev);
};

/** \brief USB host interface driver */
struct awbl_usbh_itfdev_drv {
    struct awbl_usbh_devbase_drv devdrv;

    void (*disconnect) (struct awbl_usbh_interface *p_itf);
    int (*suspend) (struct awbl_usbh_interface *p_itf);
    int (*resume) (struct awbl_usbh_interface *p_itf);
    int (*reset_resume)(struct awbl_usbh_interface *p_itf);
    const struct awbl_usbh_devdrv_info *info_tab;
};




/** \brief USB host */
struct awbl_usbh {
    struct awbl_busctlr     super;
    AW_MUTEX_DECL(mutex);
    uint32_t                addr_map[4];
    uint8_t                 root_hub_addr;
    uint16_t                max_mA;

    /* host controller state */
    uint8_t                 state;
#define __ACTIVE        0x01
#define __SUSPEND       0x04
#define __TRANSIENT     0x80

#define HC_STATE_HALT       0
#define HC_STATE_RUNNING    (__ACTIVE)
#define HC_STATE_QUIESCING  (__SUSPEND|__TRANSIENT|__ACTIVE)
#define HC_STATE_RESUMING   (__SUSPEND|__TRANSIENT)
#define HC_STATE_SUSPENDED  (__SUSPEND)

#define HC_IS_RUNNING(state) ((state) & __ACTIVE)
#define HC_IS_SUSPENDED(state) ((state) & __SUSPEND)

    struct awbl_usbh_device *root_hub;
    struct awbl_usbh        *p_next;
};

/** \brief USB host information */
struct awbl_usbh_info {
    uint8_t     bus_index;
    uint8_t     root_hub_speed;
};

/** \brief USB device base */
struct awbl_usbh_devbase {
    struct awbl_dev             awdev;
    struct awbl_devhcf          devhcf;
    bool_t                      is_interface;
    aw_spinlock_isr_t           lock;
    AW_MUTEX_DECL(mutex);
    int                         ref_cnt;
    bool_t                      remove;
    struct aw_list_head         node;
};

/** \brief USB host configure */
struct awbl_usbh_config {
    uint8_t                         *raw_cfg_desc;
    struct awbl_usb_config_desc     *desc;
#define _CONFIG_DESC_SIZE sizeof(struct awbl_usb_config_desc)

    char                            *string;

    struct awbl_usb_otg_descriptor  *otg_desc;

    uint8_t                         niads;
    struct awbl_usb_interface_assoc_descriptor
                                    *itf_assoc[AWBL_USBH_MAX_IADS];

    struct awbl_usbh_interface      *itf;
};


/** \brief USB interface device */
struct awbl_usbh_interface {
    struct awbl_usbh_devbase                    udev;
    struct awbl_usbh_device                     *p_udev;

    uint8_t                                     num_alt_setting;

    struct awbl_usbh_alternate_setting          *altsetting;

    struct awbl_usbh_alternate_setting          *cur_altsetting;

    struct awbl_usb_interface_assoc_descriptor  *itf_assoc;
};

/** \brief USB interface alternate */
struct awbl_usbh_alternate_setting {
    struct awbl_usb_interface_desc  *desc;
#define _INTERFACE_DESC_SIZE sizeof(struct awbl_usb_interface_desc)
    char                            *string;
    struct awbl_usbh_endpoint       *eps;
};

/** \brief USB host EndPoint */
struct awbl_usbh_endpoint {
    struct awbl_usbh_device         *p_udev;
    struct awbl_usb_endpoint_desc   *desc;
#define _ENDPOINT_DESC_SIZE         7
#define _ENDPOINT_DESC_AUDIO_SIZE   9
    bool_t                          enabled;
    AW_MUTEX_DECL(mutex);
    /* need bandwidth, us */
    int                             bandwidth;
    /* for host controller */
    void                            *private;
};

/** \brief USB device */
struct awbl_usbh_device {
    struct awbl_usbh_devbase        udev;
    struct awbl_usbh                *p_hc;

    /* device address */
    uint8_t                         addr;
    uint16_t                        mA;

    /* device state */
    uint8_t                         state;
#define USB_STATE_NOTATTACHED       0           /* disconnect */
#define USB_STATE_ATTACHED          1           /* connected but not be enumerated */
#define USB_STATE_POWERED           2           /* power up */
#define USB_STATE_DEFAULT           3           /*   */
#define USB_STATE_ADDRESS           4           /* set address */
#define USB_STATE_CONFIGURED        5           /* configure */
#define USB_STATE_SUSPENDED         6           /* suspended */

    /* device speed */
    uint8_t                         speed;
#define USB_SPEED_UNKNOWN           0
#define USB_SPEED_LOW               1           /* usb 1.1 */
#define USB_SPEED_FULL              2           /* usb 1.1 */
#define USB_SPEED_HIGH              3           /* usb 2.0 */
#define USB_SPEED_WIRELESS          4           /* wireless (usb 2.5) */
#define USB_SPEED_SUPER             5           /* usb 3.0 */

    /* parents hub,root hub must be NULL */
    struct awbl_usbh_device         *parent;
    /* post number on parents hub */
    uint8_t                         port_num;

    /* device descriptor */
    struct awbl_usb_device_desc     desc;
    /* all configuration */
    struct awbl_usbh_config         *config;
    /* current configuration */
    struct awbl_usbh_config         *actconfig;
    /* IN EPs */
    struct awbl_usbh_endpoint       *ep_in[16];
    /* OUT EPs */
    struct awbl_usbh_endpoint       *ep_out[16];

    struct awbl_usbh_endpoint       ep0;
    struct awbl_usb_endpoint_desc   ep0_desc;
//  struct awbl_usb_bos_desc        *bos_desc;
//  struct awbl_usb_ext_cap_desc    *ext_cap_desc;
//  struct awbl_usb_ss_cap_desc     *ss_cap_desc;

    char                            *product;
    char                            *manufacturer;
    char                            *serial;

    /* OTG support status */
    /* This contains the following information in the 8 bits:
     *
     *   Bit b0 indicates SRP support by the device.
     *   Bit b1 indicates HNP support by the device.
     *   Bits b2, b3 are reserved.
     *   Bit b4 indicates if SRP is enabled on the device.
     *   Bit b5 indicates if HNP is enabled on the device.
     *   Bit b6 indicates if HNP is supported on the host(a_hnp_support).
     *   Bit b7 indicates if HNP is supported on some other port on the
     *   host (a_alt_hnp_support).
     *   bit 6 & 7 only makes sense for Function stack. Bit 5 takes
     *   precedence over bit 6 & 7.
     */
    uint8_t                         otg_status;
};


/** \brief USB host transfer request packet */
struct awbl_usbh_trp {
    struct awbl_usbh_device         *p_dev;
    struct awbl_usbh_endpoint       *p_ep;

    /* 8 bytes setup packet */
    void                            *setup_pkt;
    /* data */
    void                            *buf;
    /* data lenght */
    uint32_t                        len;
    void                            (*complete) (void *arg);
    void                            *arg;

    /* length of data that actually transfer */
    uint32_t                        act_len;
    /* result of transfer */
    int                             status;
    int                             flag;
#define USB_SHORT_NOT_OK  0x00000001    /* Short packets are errors */
#define USB_ISO_ASAP      0x00000002    /* Start ISO transfer at the earliest */
#define USB_ZERO_PACKET   0x00000004    /* End OUT transfer with short packet */
#define USB_NO_INTERRUPT  0x00000008    /* no interrupt needed,except for error */
};



/** \brief USB host bus function */
/****************************************************************************/
void awbl_usbhbus_init (void);

/****************************************************************************/
aw_err_t awbl_usbhbus_create (struct awbl_usbh *p_hc);

/****************************************************************************/
struct awbl_usbh_device *
awbl_usbhbus_alloc_dev (struct awbl_usbh        *p_hc,
                        struct awbl_usbh_device *p_parent,
                        uint8_t                 port_num);

/****************************************************************************/
void awbl_usbhbus_free_dev (struct awbl_usbh_device *p_udev);

/****************************************************************************/
aw_err_t awbl_usbhbus_remove_dev (struct awbl_usbh_device *p_udev);

/****************************************************************************/
aw_err_t awbl_usbhbus_itf_init (struct awbl_usbh_device     *p_udev,
                                struct awbl_usbh_interface  *p_itf,
                                uint8_t                     itf_num);

/****************************************************************************/
aw_err_t awbl_usbhbus_remove_itf (struct awbl_usbh_interface *p_itf);

/****************************************************************************/
aw_err_t awbl_usbhbus_register_dev (struct awbl_usbh_devbase *p_udev);

/****************************************************************************/
aw_err_t awbl_usbhbus_get_dev (struct awbl_usbh_devbase *p_udev);

/****************************************************************************/
aw_err_t awbl_usbhbus_put_dev (struct awbl_usbh_devbase *p_udev);




/** \brief USB host EndPoint function */
/****************************************************************************/
aw_err_t awbl_usbh_ep_init (struct awbl_usbh_device       *p_udev,
                            struct awbl_usbh_endpoint     *p_ep,
                            struct awbl_usb_endpoint_desc *p_desc);

/****************************************************************************/
aw_err_t awbl_usbh_ep_enable (struct awbl_usbh_endpoint *p_ep);

/****************************************************************************/
aw_err_t awbl_usbh_ep_disable (struct awbl_usbh_endpoint *p_ep);

/****************************************************************************/
aw_err_t awbl_usbh_ep_reset (struct awbl_usbh_endpoint *p_ep);

/****************************************************************************/
aw_err_t awbl_usbh_clr_ep_halt (struct awbl_usbh_endpoint *p_ep);




/** \brief USB host standard request */
/****************************************************************************/
aw_err_t awbl_usbh_get_descriptor(struct awbl_usbh_device *p_udev,
                                  uint16_t                type,
                                  uint16_t                value,
                                  uint16_t                index,
                                  void                    *buf,
                                  size_t                  size);

/****************************************************************************/
aw_err_t awbl_usbh_set_addr (struct awbl_usbh_device *p_udev,
                             uint8_t                 addr);

/****************************************************************************/
char *awbl_usbh_get_string(struct awbl_usbh_device  *p_udev,
                           uint8_t                  index);

/****************************************************************************/
aw_err_t awbl_usbh_get_configuration(struct awbl_usbh_device *p_udev);

/****************************************************************************/
aw_err_t awbl_usbh_set_configuration (struct awbl_usbh_device *p_udev,
                                      uint8_t                 conf);

/****************************************************************************/
aw_err_t awbl_usbh_get_status (struct awbl_usbh_device *p_udev,
                               int                     target,
                               uint8_t                 stype,
                               uint8_t                 ep_num,
                               void                    *p_buf);

/****************************************************************************/
aw_err_t awbl_usbh_clear_feature (struct awbl_usbh_device *p_udev,
                                  int                     target,
                                  uint8_t                 feature,
                                  uint8_t                 ep_num);




/** \brief USB host transfer */
/****************************************************************************/
void awbl_usbh_fill_setup_pkt (struct awbl_usb_ctrlreq  *p_setup,
                               uint8_t                  bRequestType,
                               uint8_t                  bRequest,
                               uint16_t                 wValue,
                               uint16_t                 wIndex,
                               uint16_t                 wLength);

/****************************************************************************/
void awbl_usbh_fill_trp (struct awbl_usbh_trp    *p_trp,
                         struct awbl_usbh_device *p_udev,
                         uint8_t                 ep_addr,
                         void                    *setup_pkt,
                         void                    *buf,
                         size_t                  len,
                         void                    (*complete_fn)(void *arg),
                         void                    *arg);

/****************************************************************************/
aw_err_t awbl_usbh_submit_trp (struct awbl_usbh_trp *p_trp);

/****************************************************************************/
aw_err_t awbl_usbh_cancel_trp (struct awbl_usbh_trp *p_trp);

/****************************************************************************/
aw_err_t awbl_usbh_transfer_sync (struct awbl_usbh_device   *p_udev,
                                  struct awbl_usb_ctrlreq   *p_setup,
                                  uint8_t                   ep_addr,
                                  void                      *data,
                                  int                       len,
                                  int                       timeout,
                                  int                       flag);

/****************************************************************************/
aw_err_t awbl_usbh_ctrl_transfer_sync (struct awbl_usbh_device *p_udev,
                                       uint8_t                 bRequestType,
                                       uint8_t                 bRequest,
                                       uint16_t                wValue,
                                       uint16_t                wIndex,
                                       void                    *data,
                                       int                     len,
                                       int                     timeout,
                                       int                     flag);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBHBUS_H */
