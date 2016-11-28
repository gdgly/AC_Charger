/*******************************************************************************
*                                  Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief RAM disk implementation with block device interface.
 *
 * \internal
 * \par modification history:
 * - 140616 orz, first implementation.
 * \endinternal
 */

#ifndef __FS_RAM_DISK_H /* { */
#define __FS_RAM_DISK_H

/**
 * \addtogroup grp_awbl_ram_disk
 * \copydoc awbl_ram_disk.h
 * @{
 */

#include "fs/aw_block_dev.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/

/** \brief RAM disk data */
struct aw_ram_disk {
    struct aw_block_dev  bd_dev;    /**< \brief block device instance */
    uint8_t             *mem;       /**< \brief memory for ram disk */
};

/******************************************************************************/
int aw_ram_disk_attach (struct aw_ram_disk *disk,
                        uint_t              block_size,
                        uint_t              disk_size,
                        void               *mem,
                        const char         *name);

int aw_ram_disk_detach (struct aw_ram_disk *disk);


#ifdef __cplusplus
}
#endif

/** @} grp_awbl_ram_disk */

#endif /* } __FS_RAM_DISK_H */

/* end of file */
