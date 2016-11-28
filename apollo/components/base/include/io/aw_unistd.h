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
 * \brief standard symbolic constants and types.
 *
 * \internal
 * \par modification history:
 * - 150430 deo, 增加aw_ftruncate,aw_fsync
 * - 150417 deo, 增加aw_truncate
 * - 140822 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_UNISTD_H /* { */
#define __IO_UNISTD_H

/**
 * \addtogroup grp_iosys_unistd
 * @{
 */
#include "apollo.h"
#include "aw_types.h"
#include "stdio.h"      /* for SEEK_SET, SEEK_CUR and SEEK_END */

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
#ifndef SEEK_SET
#define	SEEK_SET	0	/* set file offset to offset */
#endif
#ifndef SEEK_CUR
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#endif
#ifndef SEEK_END
#define	SEEK_END	2	/* set file offset to EOF plus offset */
#endif

/******************************************************************************/
struct aw_seek_struct {
    int   whence;
    off_t offset;
};

/******************************************************************************/
int aw_close (int filedes);

ssize_t aw_read  (int filedes, void       *buf, size_t nbyte);
ssize_t aw_write (int filedes, const void *buf, size_t nbyte);

off_t aw_lseek (int fildes, off_t offset, int whence);

int aw_rmdir  (const char *path);
int aw_unlink (const char *path);

int aw_rename (const char *oldpath, const char *newpath);

int aw_truncate (const char *path, off_t length);
int aw_ftruncate(int fildes, off_t length);

char *aw_getcwd (char *buf, size_t size);
int aw_chdir (const char *path);

int aw_fsync(int fildes);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __IO_UNISTD_H */

/* end of file */
