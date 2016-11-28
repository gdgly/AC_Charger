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
 * \brief STREAMS interface.
 *
 * \internal
 * \par modification history:
 * - 140822 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_STROPTS_H /* { */
#define __IO_STROPTS_H

/**
 * \addtogroup grp_ios_stropts
 * @{
 */
#include "apollo.h"
#include "aw_ioctl.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
#define I_FLUSH     AW_FIOFLUSH
#define I_NREAD     AW_FIONREAD

/******************************************************************************/
int aw_ioctl (int filedes, int request, void *argument);


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* } __IO_STROPTS_H */

/* end of file */
