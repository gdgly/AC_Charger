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
 * \brief USB descriptor define head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-04-04  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USB_DESCRIPTOR_H
#define __AWBL_USB_DESCRIPTOR_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbl_usb_cfg.h"

/******************************************************************************/
/* bRequestType */
    /* direction */
#define AWBL_USB_DIR_OUT                    0               /* to device */
#define AWBL_USB_DIR_IN                     0x80            /* to host */
    /* type */
#define AWBL_USB_TYPE_MASK                  (0x03 << 5)
#define AWBL_USB_TYPE_STANDARD              (0x00 << 5)
#define AWBL_USB_TYPE_CLASS                 (0x01 << 5)
#define AWBL_USB_TYPE_VENDOR                (0x02 << 5)
#define AWBL_USB_TYPE_RESERVED              (0x03 << 5)
    /* target */
#define AWBL_USB_RECIP_MASK                 0x1f
#define AWBL_USB_RECIP_DEVICE               0x00
#define AWBL_USB_RECIP_INTERFACE            0x01
#define AWBL_USB_RECIP_ENDPOINT             0x02
#define AWBL_USB_RECIP_OTHER                0x03
#define AWBL_USB_RECIP_PORT                 0x04
#define AWBL_USB_RECIP_RPIPE                0x05

/* bRequest */
#define AWBL_USB_REQ_GET_STATUS             0x00
#define AWBL_USB_REQ_CLEAR_FEATURE          0x01
#define AWBL_USB_REQ_SET_FEATURE            0x03
#define AWBL_USB_REQ_SET_ADDRESS            0x05
#define AWBL_USB_REQ_GET_DESCRIPTOR         0x06
#define AWBL_USB_REQ_SET_DESCRIPTOR         0x07
#define AWBL_USB_REQ_GET_CONFIGURATION      0x08
#define AWBL_USB_REQ_SET_CONFIGURATION      0x09
#define AWBL_USB_REQ_GET_INTERFACE          0x0A
#define AWBL_USB_REQ_SET_INTERFACE          0x0B
#define AWBL_USB_REQ_SYNCH_FRAME            0x0C
#define AWBL_USB_REQ_SET_ENCRYPTION         0x0D    /* Wireless USB */
#define AWBL_USB_REQ_GET_ENCRYPTION         0x0E
#define AWBL_USB_REQ_RPIPE_ABORT            0x0E
#define AWBL_USB_REQ_SET_HANDSHAKE          0x0F
#define AWBL_USB_REQ_RPIPE_RESET            0x0F
#define AWBL_USB_REQ_GET_HANDSHAKE          0x10
#define AWBL_USB_REQ_SET_CONNECTION         0x11
#define AWBL_USB_REQ_SET_SECURITY_DATA      0x12
#define AWBL_USB_REQ_GET_SECURITY_DATA      0x13
#define AWBL_USB_REQ_SET_WUSB_DATA          0x14
#define AWBL_USB_REQ_LOOPBACK_DATA_WRITE    0x15
#define AWBL_USB_REQ_LOOPBACK_DATA_READ     0x16
#define AWBL_USB_REQ_SET_INTERFACE_DS       0x17
#define AWBL_USB_REQ_SET_SEL                0x30
#define AWBL_USB_REQ_SET_ISOCH_DELAY        0x31

/* HUB class request */
#define AWBL_USB_HUB_CLEAR_TT_BUFFER        8
#define AWBL_USB_HUB_RESET_TT               9
#define AWBL_USB_HUB_GET_TT_STATE           10
#define AWBL_USB_HUB_STOP_TT                11
#define AWBL_USB_HUB_SET_DEPTH              12
#define AWBL_USB_HUB_GET_PORT_ERR_COUNT     13

/* HUB class feature */
#define AWBL_USB_HUB_C_LOCAL_POWER      0
#define AWBL_USB_HUB_C_OVER_CURRENT     1
#define AWBL_USB_PORT_CONNECTION        0
#define AWBL_USB_PORT_ENABLE            1
#define AWBL_USB_PORT_SUSPEND           2
#define AWBL_USB_PORT_OVER_CURRENT      3
#define AWBL_USB_PORT_RESET             4
#define AWBL_USB_PORT_POWER             8
#define AWBL_USB_PORT_LOW_SPEED         9
#define AWBL_USB_PORT_C_CONNECTION      16
#define AWBL_USB_PORT_C_ENABLE          17
#define AWBL_USB_PORT_C_SUSPEND         18
#define AWBL_USB_PORT_C_OVER_CURRENT    19
#define AWBL_USB_PORT_C_RESET           20
#define AWBL_USB_PORT_C_TEST            21
#define AWBL_USB_PORT_C_INDICATOR       22

/* USB descriptor type */
#define AWBL_USB_DT_DEVICE                  0x01
#define AWBL_USB_DT_CONFIG                  0x02
#define AWBL_USB_DT_STRING                  0x03
#define AWBL_USB_DT_INTERFACE               0x04
#define AWBL_USB_DT_ENDPOINT                0x05
#define AWBL_USB_DT_DEVICE_QUALIFIER        0x06
#define AWBL_USB_DT_OTHER_SPEED_CONFIG      0x07
#define AWBL_USB_DT_INTERFACE_POWER         0x08
#define AWBL_USB_DT_OTG                     0x09
#define AWBL_USB_DT_DEBUG                   0x0a
#define AWBL_USB_DT_INTERFACE_ASSOCIATION   0x0b
#define AWBL_USB_DT_SECURITY                0x0c
#define AWBL_USB_DT_KEY                     0x0d
#define AWBL_USB_DT_ENCRYPTION_TYPE         0x0e
#define AWBL_USB_DT_BOS                     0x0f
#define AWBL_USB_DT_DEVICE_CAPABILITY       0x10
#define AWBL_USB_DT_WIRELESS_ENDPOINT_COMP  0x11
#define AWBL_USB_DT_WIRE_ADAPTER            0x21
#define AWBL_USB_DT_RPIPE                   0x22
#define AWBL_USB_DT_CS_RADIO_CONTROL        0x23
#define AWBL_USB_DT_PIPE_USAGE              0x24
#define AWBL_USB_DT_SS_ENDPOINT_COMP        0x30

#define AWBL_USB_DT_HUB             (AWBL_USB_TYPE_CLASS | 0x09)
#define AWBL_USB_DT_SS_HUB          (AWBL_USB_TYPE_CLASS | 0x0a)

/* Class ID */
#define AWBL_USB_CLASS_PER_INTERFACE        0x00    /* for DeviceClass */
#define AWBL_USB_CLASS_AUDIO                0x01
#define AWBL_USB_CLASS_COMM                 0x02
#define AWBL_USB_CLASS_HID                  0x03
#define AWBL_USB_CLASS_PHYSICAL             0x05
#define AWBL_USB_CLASS_STILL_IMAGE          0x06
#define AWBL_USB_CLASS_PRINTER              0x07
#define AWBL_USB_CLASS_MASS_STORAGE         0x08
#define AWBL_USB_CLASS_HUB                  0x09
#define AWBL_USB_CLASS_CDC_DATA             0x0a
#define AWBL_USB_CLASS_CSCID                0x0b    /* chip+ smart card */
#define AWBL_USB_CLASS_CONTENT_SEC          0x0d    /* content security */
#define AWBL_USB_CLASS_VIDEO                0x0e
#define AWBL_USB_CLASS_WIRELESS_CONTROLLER  0xe0
#define AWBL_USB_CLASS_MISC                 0xef
#define AWBL_USB_CLASS_APP_SPEC             0xfe
#define AWBL_USB_CLASS_VENDOR_SPEC          0xff

/* EndPoint direction */
#define AWBL_USB_EP_DIR_OUT                 0
#define AWBL_USB_EP_DIR_IN                  0x80
/* EndPoint type */
#define AWBL_USB_EP_TR_TYPE_CTRL            0x00
#define AWBL_USB_EP_TR_TYPE_ISO             0x01
#define AWBL_USB_EP_TR_TYPE_BULK            0x02
#define AWBL_USB_EP_TR_TYPE_INT             0x03

/* 3.0 status type */
#define AWBL_USB_STATUS_TYPE_STANDARD       0x00
#define AWBL_USB_STATUS_TYPE_PTM            0x01

/* standard status and feature */
#define AWBL_USB_DEVICE_SELF_POWERED        0   /* (read only) */
#define AWBL_USB_DEVICE_REMOTE_WAKEUP       1   /* dev may initiate wakeup */
#define AWBL_USB_DEVICE_TEST_MODE           2   /* (wired high speed only) */
#define AWBL_USB_DEVICE_BATTERY             2   /* (wireless) */
#define AWBL_USB_DEVICE_B_HNP_ENABLE        3   /* (otg) dev may initiate HNP */
#define AWBL_USB_DEVICE_WUSB_DEVICE         3   /* (wireless)*/
#define AWBL_USB_DEVICE_A_HNP_SUPPORT       4   /* (otg) RH port supports HNP */
#define AWBL_USB_DEVICE_A_ALT_HNP_SUPPORT   5   /* (otg) other RH port does */
#define AWBL_USB_DEVICE_DEBUG_MODE          6   /* (special devices only) */

/* setup packet */
struct awbl_usb_ctrlreq {
    uint8_t bRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} __attribute__ ((packed));

/* descriptor header */
struct awbl_usb_desc_header {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
} __attribute__ ((packed));

/* device descriptor */
struct awbl_usb_device_desc {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t  iManufacturer;
    uint8_t  iProduct;
    uint8_t  iSerialNumber;
    uint8_t  bNumConfigurations;
} __attribute__ ((packed));

/* qualifier descriptor */
struct awbl_usb_qualifier_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint8_t  bNumConfigurations;
    uint8_t  bRESERVED;
} __attribute__ ((packed));

/* configure descriptor */
struct awbl_usb_config_desc {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint16_t wTotalLength;
    uint8_t  bNumInterfaces;
    uint8_t  bConfigurationValue;
    uint8_t  iConfiguration;
    uint8_t  bmAttributes;
    uint8_t  bMaxPower;
} __attribute__ ((packed));

/* interface descriptor */
struct awbl_usb_interface_desc {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint8_t  bInterfaceNumber;
    uint8_t  bAlternateSetting;
    uint8_t  bNumEndpoints;
    uint8_t  bInterfaceClass;
    uint8_t  bInterfaceSubClass;
    uint8_t  bInterfaceProtocol;
    uint8_t  iInterface;
} __attribute__ ((packed));

/* EndPoint descriptor */
struct awbl_usb_endpoint_desc {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t  bInterval;

    /* NOTE:  these two are _only_ in audio endpoints. */
    /* use AWBL_USB_DT_ENDPOINT*_SIZE in bLength, not sizeof. */
    uint8_t  bRefresh;
    uint8_t  bSynchAddress;
} __attribute__ ((packed));

/* string descriptor */
struct awbl_usb_string_desc {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t wData[0];              /* UTF-16LE encoded */
} __attribute__ ((packed));

/* OTG descriptor */
struct awbl_usb_otg_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint8_t  bmAttributes;          /* support for HNP, SRP, etc */
} __attribute__ ((packed));

/* from usb_otg_descriptor.bmAttributes */
#define USB_OTG_SRP     (1 << 0)
#define USB_OTG_HNP     (1 << 1)    /* swap host/device roles */

/* interface association descriptor */
struct awbl_usb_interface_assoc_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint8_t  bFirstInterface;
    uint8_t  bInterfaceCount;
    uint8_t  bFunctionClass;
    uint8_t  bFunctionSubClass;
    uint8_t  bFunctionProtocol;
    uint8_t  iFunction;
} __attribute__ ((packed));

/* BOS descriptor */
struct awbl_usb_bos_desc {
    uint8_t  bLength;
    uint8_t  bDescriptorType;

    uint16_t wTotalLength;
    uint8_t  bNumDeviceCaps;
} __attribute__((packed));

/* EXT CAP descriptor */
struct awbl_usb_ext_cap_desc {      /* Link Power Management */
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDevCapabilityType;
    uint32_t bmAttributes;
#define USB_LPM_SUPPORT             (1 << 1)    /* supports LPM */
#define USB_BESL_SUPPORT            (1 << 2)    /* supports BESL */
#define USB_BESL_BASELINE_VALID     (1 << 3)    /* Baseline BESL valid*/
#define USB_BESL_DEEP_VALID         (1 << 4)    /* Deep BESL valid */
#define USB_GET_BESL_BASELINE(p)    (((p) & (0xf << 8)) >> 8)
#define USB_GET_BESL_DEEP(p)        (((p) & (0xf << 12)) >> 12)
} __attribute__((packed));


struct awbl_usb_ss_cap_desc {       /* Link Power Management */
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDevCapabilityType;
    uint8_t  bmAttributes;
#define USB_LTM_SUPPORT             (1 << 1)    /* supports LTM */
    uint16_t wSpeedSupported;
#define USB_LOW_SPEED_OPERATION     (1)         /* Low speed operation */
#define USB_FULL_SPEED_OPERATION    (1 << 1)    /* Full speed operation */
#define USB_HIGH_SPEED_OPERATION    (1 << 2)    /* High speed operation */
#define USB_5GBPS_OPERATION         (1 << 3)    /* Operation at 5Gbps */
    uint8_t  bFunctionalitySupport;
    uint8_t  bU1devExitLat;
    uint16_t bU2DevExitLat;
} __attribute__((packed));


#define USB_HUB_PR_FS               0       /* Full speed hub */
#define USB_HUB_PR_HS_NO_TT         0       /* Hi-speed hub without TT */
#define USB_HUB_PR_HS_SINGLE_TT     1       /* Hi-speed hub with single TT */
#define USB_HUB_PR_HS_MULTI_TT      2       /* Hi-speed hub with multiple TT */
#define USB_HUB_PR_SS               3       /* Super speed hub */

struct awbl_usbh_hub_desc {
    uint8_t  bDescLength;
    uint8_t  bDescriptorType;
    uint8_t  bNbrPorts;
    uint16_t wHubCharacteristics;
    uint8_t  bPwrOn2PwrGood;
    uint8_t  bHubContrCurrent;

    /* 2.0 and 3.0 hubs differ here */
    union {
        struct {
            /* add 1 bit for hub status change; round to bytes */
            uint8_t  DeviceRemovable[(AWBL_USBH_MAX_CHILDREN + 1 + 7) / 8];
            uint8_t  PortPwrCtrlMask[(AWBL_USBH_MAX_CHILDREN + 1 + 7) / 8];
        }  __attribute__ ((packed)) hs;

        struct {
            uint8_t     bHubHdrDecLat;
            uint16_t    wHubDelay;
            uint16_t    DeviceRemovable;
        }  __attribute__ ((packed)) ss;
    } u;
} __attribute__ ((packed));


/* return direction in EP descriptor */
aw_local aw_inline uint8_t awbl_usb_ep_dir (
        const struct awbl_usb_endpoint_desc *p_desc)
{
    return p_desc->bEndpointAddress & 0x80;
}

/* return EP number in EP descriptor */
aw_local aw_inline uint8_t awbl_usb_ep_num (
        const struct awbl_usb_endpoint_desc *p_desc)
{
    return p_desc->bEndpointAddress & 0x0f;
}

/* return EP type in EP descriptor */
aw_local aw_inline uint8_t awbl_usb_ep_tr_type (
        const struct awbl_usb_endpoint_desc *p_desc)
{
    return p_desc->bmAttributes & 0x03;
}

/* return EP MAX packet size in EP descriptor */
aw_local aw_inline uint16_t awbl_usb_ep_max_pkt_size (
        const struct awbl_usb_endpoint_desc *p_desc)
{
    return AWBL_USB_CPU_TO_LE16(p_desc->wMaxPacketSize);
}

/* return EP interval in EP descriptor */
aw_local aw_inline uint8_t awbl_usb_ep_interval (
        const struct awbl_usb_endpoint_desc *p_desc)
{
    return p_desc->bInterval;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USB_DESCRIPTOR_H */
