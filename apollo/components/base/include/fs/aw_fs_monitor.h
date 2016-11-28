/**
 * \file
 * \brief File system monitor.
 *
 * \internal
 * \par modification history:
 * - 140805 orz, first implementation.
 * \endinternal
 */

#ifndef __FS_MONITOR_H /* { */
#define __FS_MONITOR_H

/**
 * \addtogroup grp_fs_monitor
 * @{
 */

#include "io/core/aw_io_dev.h"
#include "fs/aw_block_dev.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/

/** @brief file system */
struct fs_monitor {
    const char *name;
};

/******************************************************************************/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __FS_MONITOR_H */

/* end of file */
