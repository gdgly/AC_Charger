/*******************************************************************************
*                                 Apollo
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
 * \brief access and modification times structure
 *
 * \internal
 * \par modification history:
 * - 150420 deo, first implementation.
 * \endinternal
 */

#ifndef AW_UTIME_H_
#define AW_UTIME_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "apollo.h"
#include <aw_types.h>


struct aw_utimbuf {
    time_t    actime;    /* Access time. */
    time_t    modtime;   /* Modification time. */
};
/* set file access and modification times */
int aw_utime(const char *path, struct aw_utimbuf *times);

#ifdef __cplusplus
}
#endif

#endif /* AW_UTIME_H_ */
