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
 * \brief I/O system core API.
 *
 * \internal
 * \par modification history:
 * - 140617 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_CORE_CORE_H /* { */
#define __IO_CORE_CORE_H

/**
 * \addtogroup grp_iosys_core
 * @{
 */

#include "aw_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/* typedef int mode_t; */

/******************************************************************************/
int aw_delete (const char *path);


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __IO_CORE_CORE_H */

/* end of file */
