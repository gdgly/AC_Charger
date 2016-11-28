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
 * \brief USB device support head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-07-13  deo, first implementation
 * \endinternal
 */


#ifndef __AWBL_USBD_H
#define __AWBL_USBD_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbus_lite.h"
#include "aw_list.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "awbl_usb_descriptor.h"
#include "awbl_usb_unicode.h"


#define AWBL_USBD_EVT_CONNECT           1
#define AWBL_USBD_EVT_DISCONNECT        2
#define AWBL_USBD_EVT_BUS_RST           3
#define AWBL_USBD_EVT_SUSPENDED         4
#define AWBL_USBD_EVT_RESUME            5
#define AWBL_USBD_EVT_SETUP_PKT         6
#define AWBL_USBD_EVT_UPDATE_SPEED      7
#define AWBL_USBD_EVT_ERROR             8

#define AWBL_USBD_EP_MATCH_NUM          0x01
#define AWBL_USBD_EP_MATCH_DIR          0x02
#define AWBL_USBD_EP_MATCH_TYPE         0x04
#define AWBL_USBD_EP_MATCH_SIZE         0x08
#define AWBL_USBD_EP_MATCH_USED         0x10

#define AWBL_USBD_DESC_END              NULL


/** \brief USB device transfer packet */
struct awbl_usbd_transfer {
    struct awbl_usbd_ep             *p_ep;
    void                            *buf;               /* data */
    size_t                          len;                /* length of data */
    void                            (*complete) (void *arg);
    void                            *arg;
    size_t                          act_len;            /* length of data that actually transfer */
    int                             status;             /* result */
    int                             flag;
#define _SHORT_NOT_OK  0x00000001                       /* Short packets are errors */
#define _ZERO_PACKET   0x00000002                       /* End OUT transfer with short packet */
#define _NO_INTERRUPT  0x00000004                       /* no interrupt needed,except for error */
};

/** \brief USB device string */
struct awbl_usbd_string {
    uint8_t             id;
    const char          *s;
    struct aw_list_head node;
};

/** \brief USB device EndPoint */
struct awbl_usbd_ep {
    const struct awbl_usb_endpoint_desc *p_desc;
    uint8_t                             ep_addr;
    uint8_t                             type_support;
#define AWBL_USBD_EP_TS_CTRL    0x01
#define AWBL_USBD_EP_TS_ISO     0x02
#define AWBL_USBD_EP_TS_BULK    0x04
#define AWBL_USBD_EP_TS_INT     0x08
#define AWBL_USBD_EP_TS_ALL     0x0F
    uint16_t                            mps_limt;
#define AWBL_USBD_EP_MPS_NO_LIMT 0x00
    struct aw_list_head                 node;
    bool_t                              enable;
    bool_t                              used;
};

/** \brief USB device EndPoint0 */
struct awbl_usbd_ep0 {
    struct awbl_usbd_ep         *p_ep;
    struct awbl_usbd_transfer   req;
    struct awbl_usbd            *p_usbd;
};

/** \brief USB device configuration */
struct awbl_usbd_cfg {
    struct awbl_usbd_class              *p_class;
    struct aw_list_head                 itf_list;
    struct aw_list_head                 node;
    struct awbl_usb_config_desc         *desc;
    const struct awbl_usb_desc_header   **descs;
};

/** \brief USB alt setting */
struct awbl_usbd_itf {
    struct awbl_usbd_cfg                *p_cfg;
    const struct awbl_usb_desc_header   **descs;
    uint8_t                             itf_num;
    int                                 cur_alt;
    struct aw_list_head                 node;
};

/** \brief USB device */
struct awbl_usbd {
    struct awbl_dev             awdev;
    uint8_t                     state;
#define USB_STATE_NOTATTACHED       0           /* disconnect */
#define USB_STATE_ATTACHED          1           /* connected but not be enumerated */
#define USB_STATE_POWERED           2           /* power up */
#define USB_STATE_DEFAULT           3           /*   */
#define USB_STATE_ADDRESS           4           /* set address */
#define USB_STATE_CONFIGURED        5           /* configure */
#define USB_STATE_SUSPENDED         6           /* suspended */
    uint8_t                     resume_state;
    uint8_t                     speed;
#define USB_SPEED_UNKNOWN           0
#define USB_SPEED_LOW               1           /* usb 1.1 */
#define USB_SPEED_FULL              2           /* usb 1.1 */
#define USB_SPEED_HIGH              3           /* usb 2.0 */
#define USB_SPEED_WIRELESS          4           /* wireless (usb 2.5) */
#define USB_SPEED_SUPER             5           /* usb 3.0 */

    uint8_t                     addr;
    bool_t                      remote_wakeup;
    bool_t                      self_powered;
    AW_MUTEX_DECL(mutex);
    aw_spinlock_isr_t           lock;
    struct awbl_usbd_class      *class;

    struct aw_list_head         ep_list;

    struct awbl_usbd_ep0        ep0_in;
    struct awbl_usbd_ep0        ep0_out;
    bool_t                      need_sta;

    struct aw_list_head         node;
};

/** \brief USB device information */
struct awbl_usbd_info {
    const char  *name;
    uint8_t cfg_flag;
#define AWBL_USBD_CFG_SELF_POWERED  0x01
};

/** \brief USB device driver */
struct awbl_usbd_drv {
    struct awbl_drvinfo awdrv;

    /* reset controller */
    void (*reset) (struct awbl_usbd *p_usbd);

    /* start controller */
    aw_err_t (*run) (struct awbl_usbd *p_usbd);

    /* stop controller */
    aw_err_t (*stop) (struct awbl_usbd *p_usbd);

    /* request transfer */
    aw_err_t (*transfer_req) (struct awbl_usbd          *p_usbd,
                              struct awbl_usbd_transfer *p_transfer);

    /* cancel transfer */
    aw_err_t (*transfer_cancel) (struct awbl_usbd          *p_usbd,
                                 struct awbl_usbd_transfer *p_transfer);

    /* enable EndPoint */
    aw_err_t (*ep_enable) (struct awbl_usbd    *p_usbd,
                           struct awbl_usbd_ep *p_ep);

    /* disable EndPoint */
    aw_err_t (*ep_disable) (struct awbl_usbd    *p_usbd,
                            struct awbl_usbd_ep *p_ep);

    /* reset EndPoint, but keep the EP config information */
    aw_err_t (*ep_reset) (struct awbl_usbd    *p_usbd,
                          struct awbl_usbd_ep *p_ep);

    /* update address */
    aw_err_t (*set_address) (struct awbl_usbd  *p_usbd,
                             uint8_t           addr);

    aw_err_t (*set_config) (struct awbl_usbd  *p_usbd,
                            bool_t            set);

    /* get or set EndPoint's status */
    aw_err_t (*ep_status) ( struct awbl_usbd    *p_usbd,
                            uint8_t             ep_addr,
                            bool_t              is_set,
                            uint16_t            *status);

    /* set or clear EndPoint's feature */
    aw_err_t (*ep_feature) (struct awbl_usbd    *p_usbd,
                            uint8_t             ep_addr,
                            bool_t              is_set);

    /* wake up controller */
    aw_err_t (*wakeup)(struct awbl_usbd *p_usbd);

    /* pull up or disconnect resistance on D+/D- */
    aw_err_t (*pullup)(struct awbl_usbd *p_usbd, bool_t on);
};

/** \brief USB device class function */
struct awbl_usbd_class {
    struct awbl_usbd                    *p_usbd;
    struct awbl_usb_device_desc         *desc;
    struct awbl_usbd_cfg                *cur_cfg;
    struct aw_list_head                 cfg_list;
    const struct awbl_usbd_class_opt    *opt;
    struct aw_list_head                 string_list;
};

/** \brief USB device class function driver */
struct awbl_usbd_class_opt {
    /* notice class a controller had been bind */
    aw_err_t (*bind) (struct awbl_usbd_class *class);

    /* notice class a controller had been unbind */
    aw_err_t (*unbind) (struct awbl_usbd_class *class);

    /* received a setup packet */
    int (*ctrl_setup) (struct awbl_usbd_class  *class,
                       struct awbl_usb_ctrlreq *p_setup,
                       void                    *p_buf,
                       int                     buf_len);

    /* set or clear configuration */
    aw_err_t (*config_set) (struct awbl_usbd_class  *class,
                            struct awbl_usbd_cfg    *cfg,
                            bool_t                  set);

    /* set or clear alt */
    aw_err_t (*itf_set) (struct awbl_usbd_class  *class,
                         struct awbl_usbd_itf    *itf,
                         uint8_t                 alt,
                         bool_t                  set);

    /* bus suspend */
    void (*suspend) (struct awbl_usbd_class *class);

    /* bus resume */
    void (*resume) (struct awbl_usbd_class  *class);

    /* bus disconnect */
    void (*disconnect) (struct awbl_usbd_class *class);
};







/*
 * common
 */
/****************************************************************************/
void awbl_usbd_fill_transfer (
            struct awbl_usbd_transfer *p_tsf,
            struct awbl_usbd_ep       *p_ep,
            void                      *buf,
            size_t                    len,
            int                       flag,
            void                      (*complete) (void *arg),
            void                      *arg);

/****************************************************************************/
aw_err_t awbl_usbd_transfer_req (struct awbl_usbd           *p_usbd,
                                 struct awbl_usbd_transfer  *p_transfer);

/****************************************************************************/
aw_err_t awbl_usbd_cancel_transfer (struct awbl_usbd           *p_usbd,
                                    struct awbl_usbd_transfer  *p_transfer);

/****************************************************************************/
aw_err_t awbl_usbd_sync_transfer_req (struct awbl_usbd    *p_usbd,
                                      struct awbl_usbd_ep *p_ep,
                                      void                *buf,
                                      size_t              len,
                                      int                 flag,
                                      int                 timeout);

/****************************************************************************/
aw_err_t awbl_usbd_ep_enable (struct awbl_usbd    *p_usbd,
                              struct awbl_usbd_ep *p_ep);

/****************************************************************************/
aw_err_t awbl_usbd_ep_disable (struct awbl_usbd    *p_usbd,
                               struct awbl_usbd_ep *p_ep);

/****************************************************************************/
aw_err_t awbl_usbd_ep_reset (struct awbl_usbd    *p_usbd,
                             struct awbl_usbd_ep *p_ep);

/*******************************controller***********************************/
aw_err_t awbl_usbd_create (struct awbl_usbd *p_usbd);

/****************************************************************************/
aw_err_t awbl_usbd_ep_register (struct awbl_usbd    *p_usbd,
                                struct awbl_usbd_ep *p_ep,
                                uint8_t             ep_addr,
                                uint8_t             type_support,
                                uint16_t            mps_limt);

/****************************************************************************/
aw_err_t awbl_usbd_event_handle (struct awbl_usbd  *p_usbd,
                                 uint8_t           event,
                                 void              *arg);






/*
 * application
 */
/****************************************************************************/
aw_err_t awbl_usbd_class_bind (struct awbl_usbd        *p_usbd,
                               struct awbl_usbd_class  *class);

/****************************************************************************/
void awbl_usbd_class_unbind (struct awbl_usbd *p_usbd);

/****************************************************************************/
struct awbl_usbd *awbl_usbd_find_dev (const char *name);







/*
 * calss
 */
/****************************************************************************/
struct awbl_usbd_ep *
awbl_usbd_alloc_ep (struct awbl_usbd               *p_usbd,
                    struct awbl_usb_endpoint_desc  *p_desc,
                    uint8_t                        flag);

/****************************************************************************/
aw_err_t awbl_usbd_free_ep (struct awbl_usbd    *p_usbd,
                            struct awbl_usbd_ep *p_ep);

/****************************************************************************/
void awbl_usbd_init_class (struct awbl_usbd_class           *p_class,
                           const struct awbl_usbd_class_opt *opt,
                           struct awbl_usb_device_desc      *desc);

/****************************************************************************/
aw_err_t awbl_usbd_add_string (struct awbl_usbd_class  *class,
                               struct awbl_usbd_string *string);

/****************************************************************************/
void awbl_usbd_init_config (
                struct awbl_usbd_cfg              *config,
                struct awbl_usb_config_desc       *desc,
                const struct awbl_usb_desc_header **descs);

/****************************************************************************/
aw_err_t awbl_usbd_add_config (struct awbl_usbd_class  *class,
                               struct awbl_usbd_cfg    *config);

/****************************************************************************/
aw_err_t awbl_usbd_init_itf (
                        struct awbl_usbd_itf              *itf,
                        uint8_t                           itf_num,
                        const struct awbl_usb_desc_header **descs);

/****************************************************************************/
aw_err_t awbl_usbd_add_itf (struct awbl_usbd_cfg  *config,
                            struct awbl_usbd_itf  *itf);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBD_H */
