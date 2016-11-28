/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief MCPWM驱动，服务MCPWM标准接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  snk, first implementation.
 * \endinternal
 */

#ifndef __AMDR_MCPWM_H
#define __AMDR_MCPWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "amhw_mcpwm.h"
#include "am_bitops.h"
    

/**
 * \addtogroup amdr_if_mcpwm
 * \copydoc amdr_mcpwm.h
 * @{
 */


/**
 * \brief mcpwm功能相关的GPIO信息
 */
typedef struct amdr_mcpwm_ioinfo {
    uint32_t gpio;                          /**< \brief 对应的GPIO管脚  */
    uint32_t func;                          /**< \brief 为PWM功能时的GPIO功能设置  */
    uint32_t dfunc;                         /**< \brief 禁能管脚PWM功能时的默认GPIO功能设置 */
} amdr_mcpwm_ioinfo_t;

/**
 * \brief mcpwm功能相关的设备信息
 */
typedef struct amdr_mcpwm_devinfo {
    amhw_mcpwm_t            *p_hw_mcpwm;    /**< \brief 指向mcpwm寄存器块的指针 */
    uint8_t                  inum;          /**< \brief mcpwm对应的中断号 */
    amdr_mcpwm_ioinfo_t     *p_ioinfo;      /**< \brief 指向PWM管脚信息结构体   */
    uint8_t                  channels_num;  /**< \brief 使用的通道数，最大为4 */
} amdr_mcpwm_devinfo_t;
 
/**
 * \brief mcpwm功能设备结构体
 */
typedef struct amdr_mcpwm_dev {
   
    /** \brief 标准PWM服务                         */
    am_pwm_serv_t                    pwm_serv; 
    
    /** \brief 指向定时器PWM功能设备信息常量的指针 */
    const amdr_mcpwm_devinfo_t      *p_devinfo;

} amdr_mcpwm_dev_t;

/**
 * \brief 初始化mcpwm输出功能
 *
 * \param[in] p_dev     : 指向定时器PWM输出功能设备的指针
 * \param[in] p_devinfo : 指向定时器PWM输出功能设备信息常量的指针
 *
 * \return PWM标准服务操作句柄，值为NULL时表明初始化失败
 */
am_pwm_handle_t amdr_mcpwm_init(amdr_mcpwm_dev_t           *p_dev,
                                const amdr_mcpwm_devinfo_t *p_devinfo);

/**
 * \brief 不使用mcpwm输出功能时，解初始化定时器的PWM输出功能，释放相关资源
 * \param[in] p_dev : 指向定时器PWM输出功能设备的指针
 * \return 无
 */
void amdr_mcpwm_deinit(amdr_mcpwm_dev_t *p_dev);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_MCPWM_H */

/* end of file */



