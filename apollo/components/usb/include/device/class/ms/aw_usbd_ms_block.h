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
 * \brief block device for USB device mass storage class head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-08-08  deo, first implementation
 * \endinternal
 */

#ifndef __AW_USBD_MS_BLOCK_H
#define __AW_USBD_MS_BLOCK_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbl_usbd_ms.h"

struct aw_usbd_ms_block_lun {
    struct awbl_usbd_ms_lun lun;
    struct aw_block_dev     *blk_dev;
    struct aw_block_io      bio;
    AW_SEMC_DECL(bio_sem);
};

aw_err_t aw_usbd_ms_block_init (struct aw_usbd_ms_block_lun *blun,
                                const char                  *name,
                                bool_t                      read_only,
                                bool_t                      removable);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AW_USBD_MS_BLOCK_H */
