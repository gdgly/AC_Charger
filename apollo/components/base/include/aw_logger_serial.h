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
 * \brief serial logger
 * \note 
 *       
 * \internal
 * \par modification history:
 * - 1.00 14-11-25  zen, first implementation
 * \endinternal
 */

#ifndef __AW_LOGGER_SERIAL_H
#define __AW_LOGGER_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_loglib.h"

typedef struct aw_logger_serial {
    aw_logger_t base;
    int         com_id;
} aw_logger_serial_t;

aw_err_t aw_logger_serial_register(aw_logger_serial_t *p_logger,
                                   int                 com_id,
                                   int                 baud_rate);

#ifdef __cplusplus
}
#endif

#endif /* __AW_LOGGER_SERIAL_H */

/* end of file */
