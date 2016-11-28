/**
 * \file
 * \brief raw block device file system.
 *
 * \internal
 * \par modification history:
 * - 140702 orz, first implementation.
 * \endinternal
 */

#ifndef __FS_RAW_FS_H /* { */
#define __FS_RAW_FS_H

/**
 * \addtogroup grp_raw_fs
 * \copydoc raw_fs.h
 * @{
 */

#include "io/core/aw_io_dev.h"
#include "fs/aw_block_dev.h"
#include "fs/aw_block_io.h"
#include "aw_sem.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/

/** \brief raw file system volume descriptor */
struct aw_raw_fs_volume {
    struct aw_io_dev     ios_dev;  /**< \brief I/O system device instance */
    struct aw_block_dev *blk_dev;  /**< \brief backing block device */
    struct aw_block_io   bio;      /**< \brief block I/O transaction */
    uint_t               blk_size; /**< \brief number of blocks of this volume*/
    AW_MUTEX_DECL(       lock);    /**< \brief mutex lock of the volume */
    AW_SEMC_DECL(        bio_sem); /**< \brief block I/O semaphore */
    aw_semc_id_t		 semc_id;
};

/** \brief raw device file descriptor */
struct aw_raw_fs_file {
    struct aw_raw_fs_volume *volume; /**< \brief pointer to volume descriptor */
    int                      oflags; /**< \brief flags */
    aw_block_dev_size_t      offset; /**< \brief file offset for read/write */
    aw_block_dev_size_t      size;   /**< \brief file size */
    AW_MUTEX_DECL(           lock);  /**< \brief mutex lock of the file */
};

/**
 * \brief raw FS initializing data
 * \note (bio_pool_size / bio_buf_size) should be equal to
 *       (vol_pool_size / sizeof(struct raw_fs_volume))
 */
struct aw_raw_fs_init_struct {
    struct aw_raw_fs_volume *vol_pool;      /**< \brief volume pool memory */
    unsigned int             vol_pool_size; /**< \brief volume pool size */
    struct aw_raw_fs_file   *fil_pool;      /**< \brief file descriptor pool */
    unsigned int             fil_pool_size; /**< \brief file desc pool size */
    void                    *bio_pool;      /**< \brief bio pool */
    unsigned int             bio_pool_size; /**< \brief bio pool size */
    unsigned int             bio_buf_size;  /**< \brief bio buffer size */
};

/******************************************************************************/
int aw_raw_fs_init (const struct aw_raw_fs_init_struct *init);

struct aw_raw_fs_volume *aw_raw_fs_dev_attach (const char          *vol_name,
                                               struct aw_block_dev *blk_dev);
int aw_raw_fs_dev_detach (void *volume);


#ifdef __cplusplus
}
#endif

/** @} grp_raw_fs */

#endif /* } __FS_RAW_FS_H */

/* end of file */
