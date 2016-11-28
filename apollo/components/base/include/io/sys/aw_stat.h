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
 * \brief stat function.
 *
 * \internal
 * \par modification history:
 * - 150417 deo, Ôö¼Ó aw_chmod
 * - 140811 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_SYS_STAT_H /* { */
#define __IO_SYS_STAT_H

/**
 * \addtogroup grp_ios_stat
 * @{
 */

#include <aw_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/

/* File mode (st_mode) bit masks */
#define S_IFMT   0xf000 /* file type field */
#define S_IFIFO  0x1000 /* fifo */
#define S_IFCHR  0x2000 /* character special */
#define S_IFDIR  0x4000 /* directory */
#define S_IFBLK  0x6000 /* block special */
#define S_IFREG  0x8000 /* regular */
#define S_IFLNK  0xa000 /* symbolic link */
#define S_IFSHM  0xb000 /* shared memory object */
#define S_IFSOCK 0xc000 /* socket */

/******************************************************************************/
#define S_ISUID  04000  /* set user id on execution */
#define S_ISGID  02000  /* set group id on execution */

#define S_IRWXU  00700  /* read/write/execute permission, owner */
#define S_IRUSR  00400  /* read permission, owner */
#define S_IWUSR  00200  /* write permission, owner */
#define S_IXUSR  00100  /* execute/search permission, owner */

#define S_IRWXG  00070  /* read/write/execute permission, group */
#define S_IRGRP  00040  /* read permission, group */
#define S_IWGRP  00020  /* write permission, group */
#define S_IXGRP  00010  /* execute/search permission, group */

#define S_IRWXO  00007  /* read/write/execute permission, other */
#define S_IROTH  00004  /* read permission, other */
#define S_IWOTH  00002  /* write permission, other */
#define S_IXOTH  00001  /* execute/search permission, other */

/******************************************************************************/
/* File type test macros */
#define S_ISBLK(m)  ((m & S_IFMT) == S_IFBLK)   /* block special */
#define S_ISCHR(m)  ((m & S_IFMT) == S_IFCHR)   /* character special */
#define S_ISDIR(m)  ((m & S_IFMT) == S_IFDIR)   /* directory */
#define S_ISFIFO(m) ((m & S_IFMT) == S_IFIFO)   /* fifo special */
#define S_ISREG(m)  ((m & S_IFMT) == S_IFREG)   /* regular file */
#define S_ISLNK(m)  ((m & S_IFMT) == S_IFLNK)   /* symbolic link special */
#define S_ISSOCK(m) ((m & S_IFMT) == S_IFSOCK)  /* symbolic link special */

/*
 * POSIX.1b objects.  The macros that evaluate to zero (false) are
 * defined so that they provide syntax checking for the parameter.
 */
#define S_TYPEISMQ(buf)     ((buf)->st_mode - (buf)->st_mode)
#define S_TYPEISSEM(buf)    ((buf)->st_mode - (buf)->st_mode)
#define S_TYPEISSHM(buf)    (((buf)->st_mode & S_IFMT) == S_IFSHM)

/******************************************************************************/
typedef unsigned int blksize_t;
typedef unsigned int blkcnt_t;

/******************************************************************************/

/** \brief stat struct */
struct aw_stat {
    dev_t   st_dev;     /**< \brief device ID of device containing file */
    ino_t   st_ino;     /**< \brief File serial number */
    mode_t  st_mode;    /**< \brief mode of file */
    nlink_t st_nlink;   /**< \brief number of hard links to the file */
    uid_t   st_uid;     /**< \brief user ID of file */
    gid_t   st_gid;     /**< \brief group ID of file */
    dev_t   st_rdev;    /**< \brief device ID (if file is character or block) */
    /**
     * \brief length in bytes
     *
     * - for regular files, the file size in bytes
     * - for symbolic links, the length in bytes of the pathname contained in
     *   the symbolic link
     * - for a shared memory object, the length in bytes
     * - for a typed memory object, the length in bytes
     * - for other file types, the use of this field is unspecified
     */
    off_t st_size;

    struct timespec st_atim; /**< \brief last data access time stamp */
    struct timespec st_mtim; /**< \brief last data modification time stamp */
    struct timespec st_ctim; /**< \brief last file status change time stamp */

    /** \brief a file system specific preferred I/O block size for this object*/
    blksize_t st_blksize;
    /** \brief number of blocks allocated for this object */
    blkcnt_t  st_blocks;
};

/******************************************************************************/
/** \brief get file status */
int aw_fstat (int         fildes, struct aw_stat *buf);
int aw_stat  (const char *path,   struct aw_stat *buf);

/** \brief make a directory relative to directory file descriptor */
int aw_mkdir (const char *path, mode_t mode);

/** \brief change mode of a file */
int aw_chmod(const char *path, mode_t mode);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __IO_SYS_STAT_H */

/* end of file */
