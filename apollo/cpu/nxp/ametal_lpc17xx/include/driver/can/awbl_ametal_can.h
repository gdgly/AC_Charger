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
 * \brief The ametal can driver directly from Ametal
 *
 * \internal
 * \par modification history:
 * - 1.00 15-11-21  anu, modified.
 * - 1.00 15-09-01  anu, first implementation.
 * \endinternal
 */

#ifndef __AWBL_AMETAL_CAN_H
#define __AWBL_AMETAL_CAN_H

#define AWBL_AMETAL_CAN_NAME       "ametal_can"

#include "aw_hwtimer.h"
#include "awbl_can.h"
#include "am_can.h"

/*******************************************************************************
    types
*******************************************************************************/

/**< \brief The Pointer to the hardware initialize function */
typedef am_can_handle_t (*pfn_can_init_t)(void *,const void *);

/** \brief can device channel structure for awbus lite */
typedef struct awbl_ametal_can_dev {

	/**< \brief device */
	struct awbl_dev  dev;

	 /** \brief driver functions, always goes first */
    struct awbl_can_service can_serv;

    /** \brief handle */
	am_can_handle_t handle;

} awbl_ametal_can_dev_t;

/** \brief can initialization structure for plb based AWBus devices */
typedef struct awbl_ametal_can_param {

    awbl_can_servinfo_t  servinfo;

    /** \brief Pointer to the hardware dev    */
    void        *p_hw_dev;

    /**< \breif Pointer to the hardware device information */
    const void  *p_hw_devinfo;

    /**< \brief Pointer to the hardware initialize function */
    pfn_can_init_t  pfn_can_init;

    /** \brief BSP function to pre initialize the device */
    void (*pfn_plfm_init)(void);

} awbl_ametal_can_param_t;


void awbl_ametal_can_drv_register(void);


#endif /* __AWBL_AMETAL_CAN_H */
