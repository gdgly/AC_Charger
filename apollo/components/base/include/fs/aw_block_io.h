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
 * \brief block device I/O interface.
 *
 * \internal
 * \par modification history:
 * - 140611 orz, first implementation.
 * \endinternal
 */

#ifndef __BLOCK_IO_H /* { */
#define __BLOCK_IO_H

/**
 * \addtogroup grp_awbl_block_io
 * \copydoc awbl_block_io.h
 * @{
 */

#include "aw_compiler.h"
#include "aw_common.h"
#include "fs/aw_block_dev.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/** \brief block I/O direction. */
enum aw_block_io_direction {
    AW_BLOCK_IO_READ  = 0x01, /**< \brief read blocks */
    AW_BLOCK_IO_WRITE = 0x02  /**< \brief write to blocks */
};

/******************************************************************************/
/** \brief a block(sector) index type. */
typedef long sector_t;

/******************************************************************************/

/** \brief block device I/O data */
struct aw_block_io {
    struct aw_block_dev *dev;  /**< \brief the owner of this block_io */

    sector_t    blk_no;     /**< \brief the block number of this block_io */
    unsigned    nbytes;     /**< \brief total number of bytes in this segment */
    void       *data;       /**< \brief data pointer */
    unsigned    residual;   /**< \brief residual bytes for this segment */
    int         error;      /**< \brief error code for this segment */
    unsigned    flags;      /**< \brief flags. BLOCK_IO_READ / BLOCK_IO_WRITE */

    void       *priv_data;  /**< \brief caller supplied data */

    /** \brief completion function for this segment */
    void      (*complete) (struct aw_block_io *bio);

    struct aw_block_io *next;  /**< \brief the next segment or NULL */
};

/******************************************************************************/
static aw_inline void aw_block_io_complete (struct aw_block_io *bio, int err)
{
    bio->error = err;
    if (NULL != bio->complete) {
        bio->complete(bio);
    }
}

#ifdef __cplusplus
}
#endif

/** @} grp_awbl_block_io */

#endif /* } __BLOCK_IO_H */

/* end of file */
