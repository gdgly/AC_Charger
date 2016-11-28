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
 * \brief VFS file system information.
 *
 * \internal
 * \par modification history:
 * - 150417 deo, ÐÞ¸Ästruct statvfsÎªstruct aw_statvfs
 * - 140812 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_SYS_STATVFS_H /* { */
#define __IO_SYS_STATVFS_H

/**
 * \addtogroup grp_ios_statvfs
 * @{
 */

#include <aw_types.h> 

#include "aw_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
#define ST_RDONLY   0x01    /**< \brief Read-only file system */

/** \brief Does not support the semantics of the ST_ISUID and ST_SSGID file
 * mode bits */
#define ST_NOSUID   0x02

/******************************************************************************/
typedef unsigned int fsblkcnt_t;
typedef unsigned int fsfilcnt_t;

/******************************************************************************/

/** \brief VFS file system information structure */
struct aw_statvfs {
    unsigned long f_bsize;  /**< \brief file system block size */
    unsigned long f_frsize; /**< \brief fundamental file system block size */

    fsblkcnt_t    f_blocks; /**< \brief number of blocks in units of f_frsize */
    fsblkcnt_t    f_bfree;  /**< \brief number of free blocks */
    fsblkcnt_t    f_bavail; /**< \brief number of blocks available */

    fsfilcnt_t    f_files;  /**< \brief number of file serial numbers */
    fsfilcnt_t    f_ffree;  /**< \brief number of free file serial numbers */
    fsfilcnt_t    f_favail; /**< \brief number of file serial numbers available*/

    unsigned long f_fsid;   /**< \brief file system ID */
    unsigned long f_flag;   /**< \brief bit mask of f_flag values */
    unsigned long f_namemax;/**< \brief maximum filename length */
};

/******************************************************************************/
int aw_fstatvfs (int fildes, struct aw_statvfs *buf);

int aw_statvfs (const char *path, struct aw_statvfs *buf);


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __IO_SYS_STATVFS_H */

/* end of file */
