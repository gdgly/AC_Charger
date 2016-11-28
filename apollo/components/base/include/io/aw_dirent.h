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
 * \brief format of directory entries.
 *
 * \internal
 * \par modification history:
 * - 150417 deo, ÐÞ¸Äaw_opendirº¯Êý
 * - 140811 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_DIRENT_H /* { */
#define __IO_DIRENT_H

/**
 * \addtogroup grp_iosys_dirent
 * @{
 */
#include "apollo.h"
#include <aw_types.h>
#include "aw_pool.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
#define NAME_MAX        255

/******************************************************************************/
/* typedef char ino_t; */

/******************************************************************************/

/** @brief directory entry */
struct dirent {
    ino_t d_ino; /**< @brief File serial number */

    /**
     * @brief File name string of entry
     *
     * The character array d_name is of unspecified size, but the number
     * of bytes preceding the terminating null byte shall not exceed NAME_MAX
     */
    char d_name[NAME_MAX + 1];
};

/** @brief directory stream descriptor */
struct dir {
    int           d_fildes; /**< \brief file descriptor of the directory */
    int           d_index;  /**< \brief index in directory stream */
    struct dirent d_dirent; /**< \brief directory entry instance */
};

/******************************************************************************/
/** \brief open directory with dirname */
struct dir *aw_opendir(const char *dirname);

/** \brief close a directory */
int aw_closedir(struct dir *dirp);

/** \brief read a directory entry */
int aw_readdir_r (struct dir     *dirp,
                  struct dirent  *entry,
                  struct dirent **result);

/** \brief read a directory entry */
struct dirent *aw_readdir (struct dir *dirp);


void aw_dir_init (struct dir *dirp, unsigned int dir_num);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __IO_DIRENT_H */

/* end of file */
