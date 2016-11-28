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
 * \brief ROMFS configure file.
 *
 * \internal
 * \par modification history:
 * - 1.00 15-06-26 cod, first implementation.
 * \endinternal
 */

/******************************************************************************/
#include "aw_vdebug.h"
#include "fs/aw_romfs.h"

/******************************************************************************/
#ifndef AW_CFG_ROMFS_VOLUMES
#define AW_CFG_ROMFS_VOLUMES    1
#endif

#ifndef AW_CFG_ROMFS_FILES
#define AW_CFG_ROMFS_FILES      1
#endif

/******************************************************************************/
void aw_romfs_lib_init (void)
{
    static struct aw_romfs_volume  volumes[AW_CFG_ROMFS_VOLUMES];
    static struct aw_romfs_file    files[AW_CFG_ROMFS_FILES];
    static struct aw_romfs_dev     devs[AW_CFG_ROMFS_VOLUMES];
    struct aw_romfs_init_struct    init;

    init.vol_pool      = volumes;
    init.vol_pool_size = sizeof(volumes);
    init.fil_pool      = files;
    init.fil_pool_size = sizeof(files);
    init.dev_pool      = devs;
    init.dev_pool_size = sizeof(devs);

    if (aw_romfs_init(&init) != 0) {
        AW_ERRF(("%s(): failed\n", __func__));
    }
}

/* end of file */

