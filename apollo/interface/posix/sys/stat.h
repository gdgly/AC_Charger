/**
 * \file
 * \brief stat function.
 *
 * \internal
 * \par modification history:
 * - 150417 deo, Ôö¼Ó chmod
 * - 140822 orz, first implementation.
 * \endinternal
 */

#ifndef __SYS_STAT_H /* { */
#define __SYS_STAT_H

#include "io/sys/aw_stat.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
#define fstat(fildes, buf)  aw_fstat(fildes, buf)
#define stat(path, buf)     aw_stat(path, buf)
#define lstat(path, buf)    aw_stat(path, buf)
#define mkdir(path, mode)   aw_mkdir(path, mode)
#define chmod(path, mode)	aw_chmod(path, mode)

#ifdef __cplusplus
}
#endif

#endif /* } __SYS_STAT_H */

/* end of file */
