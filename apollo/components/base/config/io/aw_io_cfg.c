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
 * \brief I/O library configure file.
 *
 * \internal
 * \par modification history:
 * - 15-04-17 deo, Ôö¼Óaw_dir_init
 * - 1.00 14-12-12 orz, first implementation.
 * \endinternal
 */

#include "apollo.h"
#include "io/core/aw_io_fd.h"
#include "io/core/aw_io_dev.h"
#include "io/aw_dirent.h"
#include "io/aw_io_cwd.h"

/******************************************************************************/
#ifndef AW_CFG_IO_OPEN_FILES_MAX
#define AW_CFG_IO_OPEN_FILES_MAX    4
#endif

/******************************************************************************/
void aw_io_lib_init (void)
{
    /* reserved 3 file descriptors for stdin, stdout and stderr */
    static struct aw_io_fd_entry fdent[3 + AW_CFG_IO_OPEN_FILES_MAX];
    static struct dir dirents[AW_CFG_IO_OPEN_FILES_MAX];
    static struct aw_cwd_struct share_cwd;


    aw_io_fd_init(fdent, sizeof(fdent) / sizeof(fdent[0]));
    aw_io_dev_init();

    aw_dir_init(dirents, sizeof(dirents) / sizeof(dirents[0]));

    aw_cwd_init();
    aw_cwd_register(&share_cwd, 0);
}

/* end of file */

