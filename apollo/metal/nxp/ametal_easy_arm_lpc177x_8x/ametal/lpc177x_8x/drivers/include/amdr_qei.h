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
 * \brief  QEI驱动层实现
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  anu, first implementation.
 * \endinternal
 */
 

#ifndef __AMDR_QEI_H
#define __AMDR_QEI_H

#ifdef __cplusplus
extern "C" {
#endif
	
	
#include "am_types.h"
#include "amhw_qei.h"
#include "am_int.h"
    
    
/** 
 * \addtogroup amdr_if_qei
 * \copydoc amdr_qei.h
 * @{
 */
    

/**
 * \name QEI捕获的模式定义
 * \anchor grp_amdr_qei_capmode
 * @{
 */
    
typedef uint32_t amdr_qei_capmode_t; /**< \brief QEI捕获的模式类型 */
#define AMDR_QEI_CAPMODE_PHA    0    /**< \brief 对相A的沿边进行捕获计数 */
#define AMDR_QEI_CAPMODE_PHAB   1    /**< \brief 对相A和B的沿边进行捕获计数 */

/** @} */

/**
 * \name QEI信号的模式定义
 * \anchor grp_amdr_qei_sigmode
 * @{
 */
    
typedef uint32_t amdr_qei_sigmode_t;       /**< \brief QEI信号的模式类型 */
#define AMDR_QEI_SIGMODE_QUADRATURE    0   /**< \brief 相A和相B作为编码器的正交相位信号 */
#define AMDR_QEI_SIGMODE_DIR_A_CLK_B   1   /**< \brief 相A为方向信号，相B为时钟信号 */

/** @} */

/**
 * \brief QEI配置信息
 */
typedef struct amdr_qei_cfg_info {
    uint32_t           maxpos;            /**< \brief 位置最大值  */
    uint32_t           cmpos0;            /**< \brief 位置0比较值  */
    uint32_t           cmpos1;            /**< \brief 比较位置1值  */
    uint32_t           cmpos2;            /**< \brief 比较位置2值  */
    uint32_t           cmpindex;          /**< \brief 索引比较值  */
    uint32_t           timeload;          /**< \brief 定时器装载时间值  */
    uint32_t           cmpvel;            /**< \brief 速度比较值  */
    uint32_t           filter;            /**< \brief 采样时钟  */
    amdr_qei_capmode_t capmode;           /**< \brief 捕获的模式  */
    amdr_qei_sigmode_t sigmode;           /**< \brief 信号的模式  */
} amdr_qei_cfg_info_t;

/**
 * \brief 中断回调信息 
 */
typedef struct amdr_qei_intcb_info {

    /** \brief 触发回调函数   */
    am_pfnvoid_t  pfn_callback;

    /** \brief 回调函数的参数 */
    void         *p_arg;
	
} amdr_qei_intcb_info_t;

/**
 * \brief QEI 设备信息 
 */
typedef struct amdr_qei_devinfo {
    amhw_qei_t              *p_hw_qei;       /**< \brief QEI寄存器首地址  */
    amdr_qei_cfg_info_t     *p_cfg_info;     /**< \brief QEI 配置信息 */
    amdr_qei_intcb_info_t   *p_intcb_info;   /**< \brief QEI 回调信息 */
    uint16_t                 inum;           /**< \brief QEI 中断号  */
} amdr_qei_devinfo_t;

/**
 * \brief QEI 设备结构体
 */
typedef struct amdr_qei_dev {
    const amdr_qei_devinfo_t  *p_devinfo;   /**< \brief 指向QEI设备信息 */
} amdr_qei_dev_t;

/**
 * \brief 设置捕获的模式 
 *
 * \param[in] p_dev : QEI设备
 * \param[in] mode  : 捕获模式 配置参数，参见
 *                    \ref grp_amdr_qei_capmode "capture mode"
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 *
 * \note AMDR_QEI_CAPMODE_PHA:edges为2，AMDR_QEI_CAPMODE_PHAB:edges为4
 */
int amdr_qei_capmode_set (amdr_qei_dev_t *p_dev, amdr_qei_capmode_t mode);

/**
 * \brief 设置信号的模式
 *
 * \param[in] p_dev : QEI设备
 * \param[in] mode  : 信号模式 配置参数，参见
 *                    \ref grp_amdr_qei_sigmode "signal mode"
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 */
int amdr_qei_sigmode_set (amdr_qei_dev_t *p_dev, amdr_qei_sigmode_t mode);
    
/**
 * \brief 开启QEI总中断
 *
 * \param[in] p_dev : QEI设备
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 * \retval -AM_EPERM    没有空的内存映射
 */
int amdr_qei_int_connect (amdr_qei_dev_t *p_dev);

/**
 * \brief 注册中断回调函数
 *
 * \param[in] p_dev        : QEI设备
 * \param[in] inttype      : 中断类型 中断类型 配置参数，参见
 *                           \ref grp_amhw_qei_int "interrupt type"
 * \param[in] pfn_callback : 要注册的回调函数
 * \param[in] p_arg        : 传进回调函数的参数
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 */
int amdr_qei_intcb_connect (amdr_qei_dev_t      *p_dev,
                            amhw_qei_int_type_t  inttype,
                            am_pfnvoid_t         pfn_callback,
                            void                *p_arg);

/**
 * \brief 删除某个类型的中断回调函数
 *
 * \param[in] p_dev        : QEI设备
 * \param[in] inttype      : 中断类型 配置参数，参见
 *                           \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 */
int amdr_qei_intcb_disconnect (amdr_qei_dev_t        *p_dev,
                               amhw_qei_int_type_t    inttype);
    
/**
 * \brief 初始化QEI
 *
 * \param[in] p_dev     : QEI设备
 * \param[in] p_devinfo : QEI设备信息
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 */
int amdr_qei_init (amdr_qei_dev_t           *p_dev,
                   const amdr_qei_devinfo_t *p_devinfo);

/**
 * \brief 解初始化QEI
 * \param[in] p_dev   : QEI设备
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 */
int amdr_qei_deinit (amdr_qei_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_QEI_H */

/*end of file */



