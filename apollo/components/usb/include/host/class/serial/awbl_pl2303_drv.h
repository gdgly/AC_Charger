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
 * \brief pl2303 drvier head file
 *
 * define pl2303 driver data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 15-06-16  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_PL2303_DRV_H
#define __AWBL_PL2303_DRV_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#define AWBL_PL2303_DRV_NAME    "awbl_pl2303_driver"


struct awbl_pl2303_usbh {
    /** \brief father device */
    struct awbl_usbh_serial serial;
    int                     ref_cnt;
    struct aw_list_head     node;
    uint8_t                 type;
#define __PL2303_TYPE_0     0
#define __PL2303_TYPE_1     1
#define __PL2303_TYPE_HX    2
    bool_t                  init;
};

/** \brief pl2303 driver register */
void awbl_pl2303_drv_register (void);

/** \brief return a pl2303's COM */
int awbl_pl2303_get_com (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_PL2303_DRV_H */

