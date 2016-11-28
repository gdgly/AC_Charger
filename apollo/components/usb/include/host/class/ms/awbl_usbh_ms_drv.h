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
 * \brief USB host mass storage class
 *
 * \internal
 * \par modification history:
 * - 1.00 15-05-23  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USBH_MS_DRV_H
#define __AWBL_USBH_MS_DRV_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "fs/aw_block_dev.h"
#include "aw_delayed_work.h"

#define AWBL_USBH_MS_DRV_NAME "awbl_usbh_mass_storage_driver"

#define __USBH_MS_MAX_SUBCLASS      3
#define __USBH_MS_FUNS_INVAL        0
#define __USBH_MS_FUNS_SCSI_INDEX   1



/** \brief MS logic unit */
struct awbl_usbh_ms_lun {
    struct awbl_usbh_mass_storage *p_ms;
    struct aw_block_dev           bd_dev;
    char                          name[32];
    uint8_t                       lun;
    uint32_t                      nblks;
    uint32_t                      blk_size;
    uint8_t                       subcalss_index;
    struct aw_delayed_work        delay_work;
};

/** \brief USB host MS device */
struct awbl_usbh_mass_storage {
    struct awbl_usbh_device     *p_udev;
    struct awbl_usbh_interface  *p_itf;

    AW_MUTEX_DECL(mutex);
    struct aw_list_head         node;

    struct awbl_usbh_endpoint *p_bulk_in_ep;
    struct awbl_usbh_endpoint *p_bulk_out_ep;
    struct awbl_usbh_endpoint *p_intr_ep;

    uint8_t max_lun;
    uint32_t tag;

    struct awbl_usbh_ms_lun *luns;
};

/** \brief USB host MS subclass function */
struct awbl_usbh_ms_subclass_funs {

    aw_err_t (*inquiry) (struct awbl_usbh_ms_lun *p_lun,
                         void                    *p_buf,
                         uint8_t                 len);

    aw_err_t (*unit_ready) (struct awbl_usbh_ms_lun *p_lun);

    aw_err_t (*read_capacity) (struct awbl_usbh_ms_lun *p_lun,
                               uint32_t                *p_nblks,
                               uint32_t                *p_blk_size);

    aw_err_t (*request_sense) (struct awbl_usbh_ms_lun *p_lun,
                               void                    *p_buf,
                               uint8_t                 len);

    aw_err_t (*mode_sense) (struct awbl_usbh_ms_lun *p_lun,
                            void                    *p_data,
                            uint8_t                 len);

    aw_err_t (*read) (struct awbl_usbh_ms_lun *p_lun,
                      uint32_t                block_addr,
                      uint32_t                nblock,
                      void                    *p_buf,
                      uint32_t                len);

    aw_err_t (*write) (struct awbl_usbh_ms_lun *p_lun,
                       uint32_t                block_addr,
                       uint32_t                nblock,
                       void                    *p_buf,
                       uint32_t                len);
};

/****************************************************************************/
void awbl_usbh_ms_drv_register (void);

/****************************************************************************/
aw_err_t awbl_usbh_ms_drv_lock (uint32_t timeout);

/****************************************************************************/
aw_err_t awbl_usbh_ms_drv_unlock (void);

/****************************************************************************/
uint32_t awbl_usbh_ms_get_tag (struct awbl_usbh_mass_storage *p_ms);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_MS_DRV_H */
