/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief RAW FS configure file.
 *
 * \internal
 * \par modification history:
 * - 1.00 14-12-12 orz, first implementation.
 * \endinternal
 */

/******************************************************************************/
#include "aw_vdebug.h"
#include "fs/aw_raw_fs.h"

/******************************************************************************/
#ifndef AW_CFG_RAWFS_VOLUMES
#define AW_CFG_RAWFS_VOLUMES    1
#endif

#ifndef AW_CFG_RAWFS_FILES
#define AW_CFG_RAWFS_FILES      1
#endif

#ifndef AW_CFG_RAWFS_BLOCK_SIZE
#define AW_CFG_RAWFS_BLOCK_SIZE 512
#endif

/******************************************************************************/
void aw_rawfs_lib_init (void)
{
    static struct aw_raw_fs_volume volumes[AW_CFG_RAWFS_VOLUMES];
    static struct aw_raw_fs_file   files[AW_CFG_RAWFS_FILES];
    static uint8_t                 bio_buf[AW_CFG_RAWFS_VOLUMES] \
                                          [AW_CFG_RAWFS_BLOCK_SIZE];
    struct aw_raw_fs_init_struct   init;

    init.vol_pool      = volumes;
    init.vol_pool_size = sizeof(volumes);
    init.fil_pool      = files;
    init.fil_pool_size = sizeof(files);
    init.bio_pool      = bio_buf;
    init.bio_pool_size = sizeof(bio_buf);
    init.bio_buf_size  = AW_CFG_RAWFS_BLOCK_SIZE;

    if (aw_raw_fs_init(&init) != 0) {
        AW_ERRF(("%s(): failed\n", __func__));
    }
}

/* end of file */

