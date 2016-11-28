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
 * \brief block device interface.
 *
 * \internal
 * \par modification history:
 * - 141110 orz, add prefix "aw_" to everything.
 * - 140611 orz, first implementation.
 * \endinternal
 */

#ifndef __BLOCK_DEV_H /* { */
#define __BLOCK_DEV_H

/**
 * \addtogroup grp_awbl_block_dev
 * \copydoc awbl_block_dev.h
 * @{
 */

#include "aw_types.h"
#include "aw_event.h"
#include "aw_sem.h"
#include "aw_ioctl_generic.h"

#include "fs/aw_block_io.h"


#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
#define __AW_BDIO(nr)          __AW_IO(0xbd, nr)
#define __AW_BDIOR(nr, size)   __AW_IOR(0xbd, nr, size)
#define __AW_BDIOW(nr, size)   __AW_IOW(0xbd, nr, size)
#define __AW_BDIOWR(nr, size)  __AW_IOWR(0xbd, nr, size)

/******************************************************************************/

/**
 * \name block device ioctl commands
 * @{
 */
/** \brief extract disk geometry */
#define AW_BDIO_GET_GEOMETRY    __AW_BDIOR(1, int)
/** \brief flush block device*/
#define AW_BDIO_SYNC            __AW_BDIO(2)
/** \brief eject and raise soft insert event */
#define AW_BDIO_SOFT_EJECT      __AW_BDIO(3)
/** \brief eject and raise insert event */
#define AW_BDIO_HARD_EJECT      __AW_BDIO(4)
/** \brief retrieve name of base block device */
#define AW_BDIO_GET_BASE_NAME   __AW_BDIO(5)
/** \brief request block device test its validity */
#define AW_BDIO_TEST            __AW_BDIO(6)
/** \brief block device stack is initialized */
#define AW_BDIO_STACK_COMPLETE  __AW_BDIO(7)
/** \brief obtain block device information */
#define AW_BDIO_GET_INFO        __AW_BDIO(8)
/** @} */

/******************************************************************************/
/** \brief block device properies */
enum aw_block_dev_property {
    AW_BLOCK_DEV_PROPERTY_READ_ONLY = 0x01, /**< device is read-only */
    AW_BLOCK_DEV_PROPERTY_DISCARD   = 0x02  /**< supports discard interface */
};

/******************************************************************************/
typedef char     aw_block_dev_name_t[32];
typedef uint64_t aw_block_dev_size_t;

/******************************************************************************/
struct aw_block_dev;

/******************************************************************************/

/** \brief block device functions */
struct aw_block_dev_funcs {
    int (*ioctl) (struct aw_block_dev *dev, int cmd, void *arg);
    int (*xfr)   (struct aw_block_dev *dev, struct aw_block_io *bio);
    int (*dump)  (struct aw_block_dev *dev, sector_t pos, void *data, size_t n);
};

/** \brief block device */
struct aw_block_dev {
    aw_block_dev_name_t              name;       /**< \brief device name */
    const struct aw_block_dev_funcs *funcs;      /**< \brief block functions */
    uint_t                           block_size; /**< \brief block size */
    sector_t                         nblocks;    /**< \brief number of blocks */
    AW_MUTEX_DECL(                   mutex);     /**< \brief device mutex lock*/
    struct aw_block_dev             *next;       /**< \brief next device */
};

/** \brief block device geometry */
struct aw_block_dev_geometry {
    uint_t   heads;         /**< \brief number of magnetic heads */
    uint64_t cylinders;     /**< \brief number of cylinders */
    sector_t total_blocks;  /**< \brief total number of blocks */
    uint_t   secs_per_track;/**< \brief number of sectors per track */
    uint_t   block_size;    /**< \brief block size */
};

/******************************************************************************/
extern struct event_category   g_block_dev_event_category;
extern struct event_type       g_block_dev_event_insert;
extern struct event_type       g_block_dev_event_soft_insert;
extern struct event_type       g_block_dev_event_remove;
extern struct event_type       g_block_dev_event_media_changed;

/******************************************************************************/
/** \brief initialize the block device lib */
void aw_block_dev_lib_init (void);

/** \brief find a block device by name */
struct aw_block_dev *aw_block_dev_find (const char *name);

/** \brief attach a block device */
int aw_block_dev_attach (struct aw_block_dev             *dev,
                         const struct aw_block_dev_funcs *funcs,
                         const char                      *name,
                         uint_t                           block_size,
                         sector_t                         nblocks);

/** \brief detach a block device */
int aw_block_dev_detach (struct aw_block_dev *dev);

/** \brief block device ioctl routine */
int aw_block_dev_ioctl (struct aw_block_dev *dev, int cmd, void *arg);

/** \brief block device transfer routine */
int aw_block_dev_xfr (struct aw_block_dev *dev, struct aw_block_io *bio);

/** \brief block device dump routine */
int aw_block_dev_dump (struct aw_block_dev *dev,
                       sector_t             pos,
                       void                *data,
                       size_t               n);

/** \brief retrieve the total number of bytes of a block device */
int aw_block_dev_size (struct aw_block_dev *dev, aw_block_dev_size_t *size);

/** \brief retrieve the total blocks of a block device */
int aw_block_dev_nblocks (struct aw_block_dev *dev, sector_t *nblocks);

/** \brief retrieve the block size of a block device */
int aw_block_dev_block_size (struct aw_block_dev *dev, uint_t *block_size);

/** \brief retrieve the block device name */
int aw_block_dev_name (struct aw_block_dev *dev, aw_block_dev_name_t name);

/** \brief get mutex lock of the block device */
int aw_block_dev_lock (struct aw_block_dev *dev);

/** \brief release mutex lock of the block device */
int aw_block_dev_unlock (struct aw_block_dev *dev);


#ifdef __cplusplus
}
#endif

/** @} grp_awbl_block_dev */

#endif /* } __BLOCK_DEV_H */

/* end of file */
