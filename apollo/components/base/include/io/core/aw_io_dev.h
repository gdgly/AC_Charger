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
 * \brief I/O devices management.
 *
 * \internal
 * \par modification history:
 * - 140701 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_CORE_DEV_H /* { */
#define __IO_CORE_DEV_H

/**
 * \addtogroup grp_aw_io_dev
 * @{
 */

#include "aw_types.h"
#include "aw_list.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
struct aw_io_dev;

/******************************************************************************/
/**
 * \brief I/O device driver
 * interface pfn_create and pfn_remove are optional.
 */
struct aw_io_driver {
    void   *(*pfn_create)(struct aw_io_dev *dev, const char *path, mode_t mode);
    int     (*pfn_delete)(struct aw_io_dev *dev, const char *path);
    void   *(*pfn_open)  (struct aw_io_dev *dev, const char *path, int    oflag,
                          mode_t            mode);
    int     (*pfn_close) (void             *pfd);
    ssize_t (*pfn_read)  (void             *pfd, void       *buf, size_t nbyte);
    ssize_t (*pfn_write) (void             *pfd, const void *buf, size_t nbyte);
    int     (*pfn_ioctl) (void             *pfd, int         cmd, void  *arg);
};

/** \brief I/O device. Devices in I/O system should inherit this struct */
struct aw_io_dev {
    struct aw_list_head        node;      /**< \brief list node in device list*/
    const struct aw_io_driver *drv;       /**< \brief driver of this device */
    const char                *name;      /**< \brief device name */
    unsigned short             ref_count; /**< \brief reference counter */
    unsigned short             flag;      /**< \brief reference flags */
};

/******************************************************************************/
void aw_io_dev_init (void);

void aw_io_dev_lock (void);
void aw_io_dev_unlock (void);

int aw_io_dev_foreach(int (*func)(struct aw_io_dev *dev, void *arg), void *arg);

struct aw_io_dev *aw_io_dev_match (const char *name);
struct aw_io_dev *aw_io_dev_find  (const char *name, const char **name_tail);

int aw_io_dev_add (struct aw_io_dev          *dev,
                   const char                *name,
                   const struct aw_io_driver *drv);

int aw_io_dev_delete (struct aw_io_dev *dev);


#ifdef __cplusplus
}
#endif

/** @} grp_aw_io_dev */

#endif /* } __IO_CORE_DEV_H */

/* end of file */
