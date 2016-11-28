/**
 * \file
 * \brief format of directory entries.
 *
 * \internal
 * \par modification history:
 * - 150417 deo, ÐÞ¸Äopendir_rÎªopendir
 * - 140822 orz, first implementation.
 * \endinternal
 */

#ifndef __DIRENT_H /* { */
#define __DIRENT_H

#include "io/aw_dirent.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
typedef struct dir DIR;

/******************************************************************************/
#define opendir   	aw_opendir
#define closedir    aw_closedir
#define readdir_r   aw_readdir_r
#define readdir     aw_readdir


#ifdef __cplusplus
}
#endif

#endif /* } __DIRENT_H */

/* end of file */
