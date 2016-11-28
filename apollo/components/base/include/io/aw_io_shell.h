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
 * \brief I/O system shell commands.
 *
 * \internal
 * \par modification history:
 * - 140825 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_SHELL_H /* { */
#define __IO_SHELL_H

/**
 * \addtogroup grp_iosys_shell
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "apollo.h"
/******************************************************************************/
void aw_io_shell_init (void);
void aw_io_shell_ramdisk_init (void);


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __IO_SHELL_H */

/* end of file */
