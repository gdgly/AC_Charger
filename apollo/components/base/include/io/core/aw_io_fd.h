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
 * \brief I/O device file descriptor management.
 *
 * \internal
 * \par modification history:
 * - 150429 deo, 增加aw_io_fd_entry结构体path元素
 * - 140701 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_CORE_FD_H /* { */
#define __IO_CORE_FD_H

/**
 * \addtogroup grp_aw_io_fd
 * @{
 */

#include "io/core/aw_io_dev.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/

/** \brief I/O file descriptor entry */
struct aw_io_fd_entry {
    struct aw_io_dev *dev; /**< \brief I/O device struct pointer */
    void             *pfd; /**< \brief device file descriptor pointer */
};

/******************************************************************************/
/** \brief initializing file descriptor lib */
void aw_io_fd_init (struct aw_io_fd_entry *fd_array, unsigned int fd_num);

/**
 * \brief reserve a file descriptor
 * \retval 0            file descriptor reserved success.
 * \retval -EBADF       fd is invalid.
 * \retval -EINPROGRESS fd is already in use.
 */
int aw_io_fd_reserve (int fd);

/**
 * \brief allocate (get) a file descriptor
 * \return a negative value for out of file descriptors, else a valid descriptor
 */
int aw_io_fd_alloc (void);

/** \brief free (put back) a file descriptor */
int aw_io_fd_free (int fd);

/**
 * \brief get file descriptor entry via a file descriptor entry.
 * \return file descriptor entry pointer for valid fd or NULL for invalid fd.
 */
struct aw_io_fd_entry *aw_io_fd_to_entry (int fd);

/**
 * \brief map a file descriptor to a file descriptor entry.
 * \return file descriptor entry pointer for valid fd or NULL for invalid fd.
 */
struct aw_io_fd_entry *aw_io_fd_map (int fd);


#ifdef __cplusplus
}
#endif

/** @} grp_aw_io_fd */

#endif /* } __IO_CORE_FD_H */

/* end of file */
