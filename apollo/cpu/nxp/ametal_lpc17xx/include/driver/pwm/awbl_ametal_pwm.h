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
 * \brief LPC17XX PWM外设驱动 公共头文件
 *
 *  描述了本驱动支持的通道范围
 *
 * \internal
 * \par modification history:
 * - 1.00 14-09-02  tee, first implemetation
 * \endinternal
 */
#ifndef __AWBL_LPC17XX_PWM_H
#define __AWBL_LPC17XX_PWM_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbus_lite.h"
#include "awbl_pwm.h"
#include "am_pwm.h"

#define  AWBL_AMETAL_PWM_NAME     "ametal_pwm"

/**< \brief The Pointer to the hardware initialize function */
typedef am_pwm_handle_t (*pfn_pwm_init_t)(void *,const void *); 

/**
 * \brief Ametal PWM 设备信息
 */
struct awbl_ametal_pwm_param {

    /** \breif Pointer to the hardware dev    */
    void                           *p_hw_dev;   
    
    /** \breif Pointer to the hardware device information  */
    const void                     *p_hw_devinfo;
 
    struct awbl_pwm_servinfo        pwm_servinfo;      /* PWM服务相关信息     */
    
    /** \brief Pointer to the hardware initialize function */
    pfn_pwm_init_t                  pfn_pwm_init; 
    
    void (*pfunc_plfm_init) (void);                /**< \brief platform initializing   */
};

struct awbl_ametal_pwm_dev {
/** \brief Ametal PWM dev   */
    struct awbl_dev                  dev;          /**< \brief awbl device data         */
    am_pwm_handle_t                  handle;       /**< \brief The handle from hardware */
    
    /** \brief PWM 服务  */
    struct awbl_pwm_service          pwm_serv;     /** 每个设备提供一个PWM服务给上层 */
};

void awbl_ametal_pwm_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */


#endif /* __AWBL_LPC17XX_PWM_H */
