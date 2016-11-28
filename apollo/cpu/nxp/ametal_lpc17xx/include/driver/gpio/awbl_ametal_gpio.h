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
 * \brief AWBus-lite GPIO 驱动
 *
 * \internal
 * \par modification history:
 * - 1.10 15-01-08  hbt, modified.
 * - 1.00 12-08-23  zen, first implementation
 * \endinternal
 */

#ifndef __AWBL_AMETAL_GPIO_H
#define __AWBL_AMETAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbl_gpio.h"
#include "awbl_intctlr.h"

#include "am_gpio.h"


/** \brief GPIO 驱动名 */
#define AWBL_AMETAL_GPIO_NAME   "ametal_gpio"

/** \brief The Pointer to the hardware initialize function */
typedef int (*pfunc_gpio_init_t)(void *, const void *); 


/**
 * \brief GPIO 设备信息
 */
typedef struct awbl_ametal_gpio_param {  
    
    /** \brief 指向 GPIO 硬件设备 */
    void        *p_hw_dev;  
         
    /**< \breif 指向 GPIO 硬件设备信息 */
    const void  *p_hw_devinfo;
    
    /** \brief GPIO 服务配置信息 */
    struct awbl_gpio_servinfo    gpio_servinfo;
    
    /** \brief IntCtlr 服务配置信息 */
    struct awbl_intctlr_servinfo intctlr_servinfo;
    
    /** \brief GPIO 初始化函数 */
    pfunc_gpio_init_t            pfunc_gpio_init;
    
    /** \brief 平台相关初始化函数 */
    void (*pfunc_plfm_init)(void);
    
} awbl_ametal_gpio_param_t;

/**
 * \brief GPIO 设备
 */
typedef struct awbl_ametal_gpio_dev {
    
    /** \brief inherit AWBus decive */
    struct awbl_dev super;

    /** \brief IntCtlr serve */
    struct awbl_intctlr_service intctlr_serv;

    /** \brief GPIO 服务 */
    struct awbl_gpio_service gpio_serv;
    
} awbl_ametal_gpio_dev_t;


/**
 * \brief ametal GPIO driver register
 */
void awbl_ametal_gpio_drv_register(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_AMETAL_GPIO_H */

/* end of file */

