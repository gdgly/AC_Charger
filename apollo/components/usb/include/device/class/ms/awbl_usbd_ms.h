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
 * \brief USB device mass storage class head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-07-13  deo, first implementation
 * \endinternal
 */
#ifndef __AWBL_USBD_MS_H
#define __AWBL_USBD_MS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "device/awbl_usbd.h"
#include "aw_task.h"
#include "aw_msgq.h"

#define AWBL_USBD_MS_TASK_STACK_SIZE    4096
#define AWBL_USBD_MS_TASK_PRIORITY      10
#define AWBL_USBD_MS_NUM_BUFFERS        2
#define AWBL_USBD_MS_BUFFER_SIZE        (16*1024)
#define AWBL_USBD_MS_MAX_LUNS           8

/* bulk only CBW */
struct awbl_usbd_ms_cbw {
    uint32_t    signature;
    uint32_t    tag;
    uint32_t    data_trf_len;
    uint8_t     flags;
    uint8_t     lun;
    uint8_t     cb_length;
    uint8_t     cb[16];
};

/* bulk only CSW */
struct awbl_usbd_ms_csw {
    uint32_t    signature;
    uint32_t    tag;
    uint32_t    data_residue;
    uint8_t     status;
};

/* MS buffer */
struct awbl_usbd_ms_buf {
    void                *buf;
    struct aw_list_head node;
};

/* MS logic unit */
struct awbl_usbd_ms_lun {
    /* number */
    int                  num;
    struct aw_list_head  node;
    uint32_t             sense_data;
    uint32_t             sense_data_info;
    bool_t               info_valid;

    bool_t               read_only;
    bool_t               removable;
    int                  blk_size;
    int                  nblks;

    int (*read) (   struct awbl_usbd_ms_lun *lun,
                    void                    *buf,
                    int                     blk_no,
                    int                     nblks);

    int (*write) (  struct awbl_usbd_ms_lun *lun,
                    void                    *buf,
                    int                     blk_no,
                    int                     nblks);
};

struct awbl_usbd_ms_info {
    uint16_t                vid;
    uint16_t                pid;
    uint16_t                bcd;
    const char              *manufacturer;
    const char              *product;
    const char              *serial_num;
    const char              *configuraton;
    const char              *interface;
};

/* usbd MS */
struct awbl_usbd_ms {
    struct awbl_usbd_class          class;
    const struct awbl_usbd_ms_info  *info;

    struct awbl_usbd_cfg            cfg;
    struct awbl_usbd_itf            itf;
    struct awbl_usbd_ep             *p_in_ep;
    struct awbl_usbd_ep             *p_out_ep;

    struct awbl_usb_device_desc     dev_desc;
    struct awbl_usb_config_desc     cfg_desc;
    struct awbl_usb_interface_desc  itf_desc;
    struct awbl_usb_endpoint_desc   ep_in_desc;
    struct awbl_usb_endpoint_desc   ep_out_desc;
    struct awbl_usb_desc_header     *alt_desc[4];
    struct awbl_usbd_string         string[5];

    aw_task_id_t                    task_id;
    AW_TASK_DECL(task, AWBL_USBD_MS_TASK_STACK_SIZE);
    AW_SEMB_DECL(semb_run);

//  struct awbl_usbd_transfer       bulk_out;
//  struct awbl_usbd_transfer       bulk_in;

    uint8_t                         nluns;
    struct aw_list_head             lun_list;
    struct awbl_usbd_ms_lun         *curlun;

    struct awbl_usbd_ms_buf         buffers[AWBL_USBD_MS_NUM_BUFFERS];
    struct aw_list_head             buf_list;
    struct awbl_usbd_ms_cbw         cbw;
    uint32_t                        residue;
    uint8_t                         status;
};

void awbl_usbd_ms_init (struct awbl_usbd_ms             *p_ms,
                        const struct awbl_usbd_ms_info  *p_info);

void awbl_usbd_ms_add_lun (struct awbl_usbd_ms     *p_ms,
                           struct awbl_usbd_ms_lun *p_lun);
#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBD_MS_H */
