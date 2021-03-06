/**
 * \file
 * \brief File system types management.
 *
 * \internal
 * \par modification history:
 * - 141223 orz, change block device pointer to a path.
 * - 140805 orz, first implementation.
 * \endinternal
 */

#ifndef __FS_TYPE_H /* { */
#define __FS_TYPE_H

/**
 * \addtogroup grp_fs_type
 * @{
 */

#include "io/core/aw_io_dev.h"
#include "fs/aw_block_dev.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
#define AW_FS_FMT_FLAG_LOW_LEVEL    0x01    /**< \brief low level format */

/******************************************************************************/
/** @brief arguments for file system type to make a volume */
struct aw_fs_format_arg {
    const char *vol_name;  /**< \brief volume name */
    size_t      unit_size; /**< \brief unit size of this volume */
    uint_t      flags;     /**< \brief flags for this volume */
};

/** @brief file system type struct */
struct aw_fs_type {
    struct aw_fs_type *fs_next;
    const char        *fs_name;
    void            *(*fs_dev_attach) (const char                    *vol_path,
                                       const char                    *dev_path);
    int              (*fs_dev_detach) (void                          *volume);
    int              (*fs_make_fs)    (const char                    *dev_path,
                                       const struct aw_fs_format_arg *fmt_arg);
};

/******************************************************************************/
struct aw_fs_type *aw_fs_type_find     (const char        *name);
int                aw_fs_type_register (struct aw_fs_type *fs);


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __FS_TYPE_H */

/* end of file */
