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
 * \brief IMX28 系列定时器驱动
 *
 * 本驱动只实现了定时器的周期中断功能，不提供计数、匹配、捕获、旋转编码和PWM功能。
 *
 * \par 1.驱动信息
 *
 *  - 驱动名:  "lpc11xx_timer32"(32-bit timer) ; "lpc11xx_timer16"(16-bit timer)
 *  - 总线类型: AWBL_BUSID_PLB
 *  - 设备信息: struct awbl_lpc11xx_timer_param
 *
 * \par 2.兼容设备
 *
 *  - NXP LPC11XX 系列MCU
 *  - NXP LPC13XX 系列MCU
 *  - 其它与LPC11XX TIMER 兼容的设备
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
 * - 1.00 12-11-15  orz, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX28_TIMER_H
#define __AWBL_IMX28_TIMER_H /* { */

#include "awbl_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_awbl_drv_imx28_timer
 * \copydetails awbl_imx28_timer.h
 * @{
 */

/**
 * \defgroup  grp_awbl_drv_lpc11xx_16_32timer_hwconf 设备定义/配置
 *
 * LPC11XX TIMER 硬件设备的定义如下面的代码所示，用户在定义目标系统的硬件资源时,
 * 可以直接将这段代码嵌入到 awbus_lite_hwconf_usrcfg.c 中对应的位置，然后对设备
 * 信息进行必要的配置(可配置的项目用【x】标识)。
 *
 * \note 有多少个TIMER，就将下面的代码嵌入多少次，注意将变量修改为不同的名字。
 *
 * \include  hwconf_usrcfg_hwtimer_lpc11xx.c
 * \note 以下配置项中带【用户配置】标识的，表示用户在开发应用时可以配置此参数。
 *
 * - 【1】平台相关初始化函数 \n
 * 在平台初始化函数中完成使能时钟等与平台相关的操作。
 *
 * - 【2】定时器可达到的最小频率 \n
 * 请查阅手册中定时器的可用分频设置来确定该参数
 *
 * - 【3】定时器可达到的最大频率 \n
 * 请查阅手册中定时器的可用分频设置来确定该参数
 *
 * - 【4】定时器的输入时钟频率 \n
 * 请查阅手册及系统时钟设置来确定该参数
 *
 * - 【5】定时器的溢出翻转周期 \n
 *
 * - 【6】定时器寄存器起始地址 \n
 * 请查阅手册确定该参数
 *
 * - 【8】设备名称 \n
 * 16位定时器请填“lpc11xx_timer16”，32位定时器请填写“lpc11xx_timer32”
 *
 * - 【9】定时器设备的单元号 \n
 * 用于区分同类设备，如16位定时器0和16位定时器1
 */

/** @} */

/******************************************************************************/
struct imx28_reg {
    uint32_t dat; /**< \brief data value (both read and write) register */
    uint32_t set; /**< \brief data bits field set register */
    uint32_t clr; /**< \brief data bits field clear register */
    uint32_t tog; /**< \brief data bits field toggle register */
};

/** \brief IMX28 timer registers */
struct imx28_timer_reg {
    struct imx28_reg tim_ctrl;      /**< \brief [00] Control and status */
    struct imx28_reg running_count; /**< \brief [10] Running Count */
    struct imx28_reg fixed_count;   /**< \brief [20] Fixed Count */
    struct imx28_reg match_count;   /**< \brief [30] Match Count */
};

/******************************************************************************/

/** \brief timer fixed parameter */
struct awbl_imx28_timer_param {
    uint32_t	clk_frequency;	        /**< \brief clock frequency              */
    uint32_t     alloc_byname;          /**< \brief the bit with 1 means the chan the timer can any be alloc by name   */
    uint32_t         reg_addr;          /**< \brief register base address   */
    int                  inum;          /**< \brief interrupt number        */
    void (*pfunc_plfm_init) (void);     /**< \brief platform initializing   */ 
};

/** \brief convert AWBus timer device info to imx28 timer parameter */
#define awbldev_get_imx28_timer_param(p_dev) \
    ((struct awbl_imx28_timer_param *)AWBL_DEVINFO_GET(p_dev))
 
/******************************************************************************/

/** \brief imx28 Timer type for AWBus */
struct awbl_imx28_timer {
    /* always go first */   
    awbl_dev_t  dev;                 /** \brief AWBus device data */
    
    struct awbl_timer        tmr;    /**< \brief AWBL timer instance */
    struct imx28_timer_reg  *reg;    /**< \brief register base */
    
    uint32_t                 count;  /**< \brief current max counts */
    uint32_t          rollover_period;  /**< \brief rollover_period */
    
    struct awbl_timer_param  param;     /**< \brief the timer's param */
    
    void (*pfunc_isr) (void *p_arg);    /**< \brief ISR */
    void  *p_arg;                       /**< \brief ISR argument */
};

/** \brief Convert a awbl_timer pointer to a awbl_imx28_timer pointer */
#define awbl_timer_to_imx28_timer(p_timer) \
    ((struct awbl_imx28_timer *)(p_timer))

/** \brief convert a awbl_dev pointer to awbl_imx28_timer pointer */
#define awbldev_to_imx28_timer(p_dev) \
          ((struct awbl_imx28_timer *)(p_dev))

/** \brief get IMX28 timer parameter */
#define imx28_timer_get_param(p_imxtimer)  ((struct awbl_imx28_timer_param *) \
    AWBL_DEVINFO_GET(&((p_imxtimer)->tmr.dev)))

/******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* } __AWBL_IMX28_TIMER_H */

/* end of file */
