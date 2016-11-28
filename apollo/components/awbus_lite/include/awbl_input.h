/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Input device model.
 *
 * \internal
 * \par modification history
 * - 1.01 15-01-07  ops, encapsulate aw_input_handler and redefine how to register/unregister.
 * - 1.00 14-08-29  ops, first implementation.
 * \endinternal
 */

#ifndef __AWBL_INPUT_H
#define __AWBL_INPUT_H

#include "aw_types.h"
#include "aw_input.h"
#include "aw_msgq.h"

#ifdef __cplusplus
extern "C" {
#endif

void awbl_input_event_init(void);
void awbl_input_event_key_init(void);
void awbl_input_event_abs_init(void);
void awbl_input_event_rel_init(void);

int  awbl_input_report_key (int ev_type, int code, int is_pressed);
int  awbl_input_report_coord (int ev_type, int code, int coord_x, int coord_y, int coord_z);

aw_err_t awbl_input_handler_register (struct aw_input_handler *p_input_handler,
                                      input_cb_func_t         *p_cb_func,
                                      void                    *p_usr_data);

aw_err_t awbl_input_handler_unregister (struct aw_input_handler *p_input_handler);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_INPUT_H */

/* end of file */
