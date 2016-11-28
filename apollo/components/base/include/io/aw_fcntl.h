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
 * \brief file control options.
 *
 * \internal
 * \par modification history:
 * - 140703 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_FCNTL_H /* { */
#define __IO_FCNTL_H

/**
 * \addtogroup grp_iosys_fcntl
 * @{
 */
#include "apollo.h"
#include "aw_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
#define O_ACCMODE   (O_RDONLY | O_WRONLY | O_RDWR)

#define O_RDONLY    0x0000  /**< \brief */
#define O_WRONLY    0x0001  /**< \brief */
#define O_RDWR      0x0002  /**< \brief */
#define O_APPEND    0x0008  /**< \brief */

#define O_EXCL      0x0100  /**< \brief */
#define O_CREAT     0x0200  /**< \brief */
#define O_TRUNC     0x0400  /**< \brief */
#define O_DIRECTORY 0x0800  /**< \brief */

/******************************************************************************/
int aw_create (const char *path, mode_t mode);

int aw_open (const char *path, int oflag, mode_t mode);

int aw_fcntl  (int fildes, int cmd, void *arg);


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __IO_FCNTL_H */

/* end of file */
