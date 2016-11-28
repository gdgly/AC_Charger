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
 * \brief lpc17xx 系列 MRT(Multi-Rate Timer)定时器驱动
 *
 * 本驱动实现了 lpc17xx 32bit standard Timers  定时器的定时器功能,不提供计数、匹配、
 * 捕获和PWM功能。
 *
 * \par 1.驱动信息
 *
 *  - 驱动名:  "lpc17xx_timer_std"
 *  - 总线类型: AWBL_BUSID_PLB
 *  - 设备信息: struct awbl_lpc17xx_timer_param
 *
 * \par 2.兼容设备
 *
 *  - NXP LPC17XX 系列MCU
 *
 * \par 3.设备定义/配置
 *
 *  - \ref grp_awbl_drv_lpc11xx_16_32timer_hwconf
 *
 * \par 4.用户接口
 *
 *  - \ref grp_aw_serv_hwtimer
 *
 * \internal
 * \par modification history
 * - 1.00 14-08-20  tee, first implementation
 * \endinternal
 */

#ifndef __AWBL_AMETAL_TIMER_H
#define __AWBL_AMETAL_TIMER_H

#include "awbl_timer.h"
#include "am_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AWBL_AMETAL_TIMER_NAME      "ametal_timer"

/**< \brief The Pointer to the hardware initialize function */
typedef am_timer_handle_t (*pfunc_timer_init_t)(void *,const void *); 

/** \brief ametal timer channel structure  */
struct awbl_ametal_timer_chan {
    struct awbl_ametal_timer_dev *p_timer_dev; /**< \brief Pointer to the timer dev */
    struct awbl_timer             timer;       /**< \brief The awbl timer           */
    uint8_t                       timer_no;    /**< \brief The timer number         */
};

/** \brief ametal timer initialization structure for plb based AWBus devices */
struct awbl_ametal_timer_param {
    
    /** \breif Pointer to the hardware dev    */
    void                           *p_hw_dev;   
    
    /** \breif Pointer to the hardware device information  */
    const void                     *p_hw_devinfo;
    
    /** 
     * \brief Pointer to the struct awbl_ametal_timer_chan array,
     *  The array size is the channel num.according to the 
     *  Actual device.
     */
    struct awbl_ametal_timer_chan  *p_chan_array;
    
    /** 
     * \brief 按照名字指定分配
     *
     *  相应位为1，表示该定时器的该通道只能按照名字指定的方式分配
     *  位0对应通道0，位1对应通道1，以此类推
     */
    uint32_t                        alloc_byname;  
    
    /**< \brief Pointer to the hardware initialize function */
    pfunc_timer_init_t              pfn_timer_init; 
    
    /** \brief BSP function to pre initialize the device    */
    void (*pfn_plfm_init)(void);
};

/** \brief ametal timer dev   */
struct awbl_ametal_timer_dev {
    struct awbl_dev                  dev;          /**< \brief awbl device data         */
    am_timer_handle_t                handle;       /**< \brief The handle from hardware */
    struct awbl_ametal_timer_chan   *p_chan_array; /**< \brief Pointer to the awbl timer*/ 
    struct awbl_timer_param          param;        /**< \brief timer common parameters  */
};

void awbl_ametal_uart_drv_register (void);

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_LPC11XX_TIMER_H */

/* end of file */
