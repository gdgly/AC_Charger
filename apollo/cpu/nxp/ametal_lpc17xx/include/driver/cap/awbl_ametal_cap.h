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
 * \brief Ametal 输入捕获驱动
 * 
 * \internal
 * \par modification history:
 * - 1.00 15-01-12  tee, first implemetation
 * \endinternal
 */
#ifndef __AWBL_AMETAL_CAP_H
#define __AWBL_AMETAL_CAP_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbus_lite.h"
#include "awbl_cap.h"
#include "am_cap.h"
    
#define AWBL_AMETAL_CAP_NAME            "ametal_cap"

/**< \brief The Pointer to the hardware initialize function */
typedef am_cap_handle_t (*pfn_cap_init_t)(void *,const void *); 

/**
 * \brief LPC54xxx CAP 设备信息
 */
typedef struct awbl_ametal_cap_param {
    /** \breif Pointer to the hardware dev    */
    void                           *p_hw_dev;   
    
    /** \breif Pointer to the hardware device information  */
    const void                     *p_hw_devinfo;
    
	struct awbl_cap_servinfo        cap_servinfo; 
    
    /** \brief Pointer to the hardware initialize function */
    pfn_cap_init_t                  pfn_cap_init; 
    
    void (*pfn_plfm_init) (void);               /**< \brief platform initializing   */
} awbl_ametal_cap_param_t;

/**
 * \brief ametal capture device
 */
typedef struct awbl_ametal_cap_dev {
	struct awbl_dev            dev;       /**< \brief 继承自 AWBus 设备             */
    am_cap_handle_t            handle;    /**< \brief The handle from hardware      */
	struct awbl_cap_service    cap_serv;  /**< \brief 每个设备提供一个CAP服务给上层 */
    
} awbl_ametal_cap_dev_t;

/**
 * \brief Ametal cap driver register
 */
void awbl_ametal_cap_drv_register (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */


#endif /* __AWBL_AMETAL_CAP_H */
