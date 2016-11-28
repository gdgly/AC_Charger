/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AnyData driver head file
 *
 * define AnyData driver data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 15-07-02  deo, first implementation
 * \endinternal
 */


#ifndef AWBL_ANYDATA_DRV_H_
#define AWBL_ANYDATA_DRV_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_list.h"

#define AWBL_ANYDATA_DRV_NAME "awbl_anydata_driver"

struct awbl_anydata_usbh {
    int                 ref_cnt;
    struct aw_list_head node;

#define __ANYDATA_MAX_SERS 8
    /** \brief all serials */
    struct awbl_usbh_serial *serials[__ANYDATA_MAX_SERS];
    /** \brief count of serials */
    int                     nser;
};

struct awbl_anydata_port {
    int rts_state;
    int dtr_state;
    int cts_state;
    int dsr_state;
    int dcd_state;
    int ri_state;
};


/** \brief register AnyData driver */
void awbl_anydata_drv_register (void);

/** \brief return a AnyData */
struct awbl_anydata_usbh *
awbl_anydata_get_anydata (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_ANYDATA_DRV_H_ */
