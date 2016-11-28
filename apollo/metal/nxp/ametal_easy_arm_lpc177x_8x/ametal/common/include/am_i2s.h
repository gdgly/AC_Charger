/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief I2S标准接口
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-14  sam.
 * \endinternal
 */

#ifndef __AM_I2S_H
#define __AM_I2S_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_if_i2s
 * \copydoc am_i2s.h
 * @{
 */

/**
 * \name 硬件参数设置选项，设置硬件参数时，可以是多个选项的或值
 * @{
 */
#define AM_I2S_TX_BIT8         0x0          /**< \brief 发送字宽度为8位                  */
#define AM_I2S_TX_BIT16        0x1          /**< \brief 发送字宽度为16位                 */
#define AM_I2S_TX_BIT32        0x2          /**< \brief 发送字宽度为32位                 */

#define AM_I2S_TX_BIT8         0x0          /**< \brief 发送字宽度为8位                  */
#define AM_I2S_TX_BIT16        0x1          /**< \brief 发送字宽度为16位                 */
#define AM_I2S_TX_BIT32        0x2          /**< \brief 发送字宽度为32位                 */
	
#define AM_I2S_RX_BIT8         0x3          /**< \brief 接收字宽度为8位                  */
#define AM_I2S_RX_BIT16        0x4          /**< \brief 接收字宽度为16位                 */
#define AM_I2S_RX_BIT32        0x5          /**< \brief 接收字宽度为32位                 */	

#define AM_I2S_WIDTH8         8             /**< \brief 字宽度为8位                      */
#define AM_I2S_WIDTH16        16            /**< \brief 字宽度为16位                     */
#define AM_I2S_WIDTH32        32   	        /**< \brief 字宽度为32位                     */
	
#define AM_I2S_TXSOUND_STEREO 0             /**< \brief 发送声道为立体声                 */
#define AM_I2S_TXSOUND_MONO   1             /**< \brief 发送声道为单声道                 */
#define AM_I2S_RXSOUND_STEREO 2             /**< \brief 接收声道为立体声                 */
#define AM_I2S_RXSOUND_MONO   3             /**< \brief 接收声道为立体声                 */


#define AM_I2S_RXFIFO_EMPTY   0             /**< \brief 接收FIFO为空标志                 */
#define AM_I2S_TXFIFO_FULL    8             /**< \brief 发送FIFO为满标志                 */

#define AM_I2S_RXFIFO_LEVEL   1             /**< \brief 接收FIFO深度值                   */
#define AM_I2S_TXFIFO_LEVEL   2             /**< \brief 发送FIFO深度值                   */

#define AM_I2S_OPT_TXMASTER   0             /**< \brief 主机发送                         */
#define AM_I2S_OPT_TXSLAVE    1             /**< \brief 从机发送                         */
#define AM_I2S_OPT_RXMASTER   2             /**< \brief 主机接收                         */
#define AM_I2S_OPT_RXSLAVE    3             /**< \brief 从机接收                         */

#define AM_I2S_TXCLKSLECT_FRAC   0          /**< \brief 发送时钟源为小数速率分频器       */
#define AM_I2S_TXCLKSLECT_RXREF  1          /**< \brief 发送时钟源为RX_REF               */
#define AM_I2S_TXCLKSLECT_WIRE4  2          /**< \brief 发送时钟源为RX的位时钟           */ 
#define AM_I2S_TXCLKSLECT_TXMCLK 3          /**< \brief 发送时钟源为发送主时钟           */

#define AM_I2S_RXCLKSLECT_FRAC   4          /**< \brief 接收时钟源为小数速率分频器       */
#define AM_I2S_RXCLKSLECT_RXREF  5          /**< \brief 接收时钟源为RX_REF               */
#define AM_I2S_RXCLKSLECT_WIRE4  6          /**< \brief 接收时钟源为TX的位时钟           */ 
#define AM_I2S_RXCLKSLECT_RXMCLK 7          /**< \brief 接收时钟源为接收主时钟           */
		
/** @} */	
	

/**
 * \name I2S设备回调函数类型编码，用于指定注册何种回调函数
 * @{
 */

#define AM_I2S_CALLBACK_GET_TX_DATA   0 /**< \brief 获取一个发送字       */
#define AM_I2S_CALLBACK_PUT_RCV_DATA  1 /**< \brief 提交一个接收到的字   */
#define AM_I2S_CALLBACK_ERROR         2 /**< \brief 错误回调函数         */

/** @} */

/**
 * \name 回调函数类型定义
 * @{
 */

/** \brief 获取一个发送字回调函数类型 */
typedef int  (*pfn_i2s_txdata_get_t)(void *p_arg, uint32_t *p_data);

/** \brief 提交一个接收到的字        */
typedef int  (*pfn_i2s_rxdata_put_t)(void *p_arg, uint32_t ch);

/** \brief 错误回调函数                 */
typedef int  (*pfn_i2s_err_t)(void *p_arg, int code, void *p_data, int size);

/** @} */


/**
 * \brief I2S驱动函数结构体
 */
struct am_i2s_drv_funcs {

    /**\brief 启动I2S发送开始函数 */
    int (*pfn_i2s_transmit_startup)(void *p_drv);
	
	/**\brief  I2S发送结束函数 */
	int (*pfn_i2s_tx_stop)(void *p_drv);
	
	/**\brief  I2S接收结束函数 */
	int (*pfn_i2s_rx_stop)(void *p_drv);
  
    /**\brief 设置I2S回调函数 */
    int (*pfn_i2s_callback_set)(void  *p_drv,
                                int    callback_type,
                                int  (*pfn_callback)(void *),
                                void  *p_callback_arg);

    /**\brief I2S连接，以连接I2S中断函数   */
    int (*pfn_i2s_connect)(void *p_drv);
};

/**
 * \brief I2S服务
 */
typedef struct am_i2s_serv {

    /** \brief I2S驱动函数结构体指针    */
    struct am_i2s_drv_funcs *p_funcs;

    /** \brief 用于驱动函数的第一个参数  */
    void                     *p_drv;
} am_i2s_serv_t;

/** \brief I2S标准服务操作句柄类型定义  */
typedef am_i2s_serv_t *am_i2s_handle_t;


/**
 * \brief 启动I2S传输
 * \param[in] handle : I2S标准服务操作句柄
 * \retval AM_OK : 启动成功
 */
am_static_inline
int am_i2s_transmit_startup (am_i2s_handle_t handle)
{
    return handle->p_funcs->pfn_i2s_transmit_startup(handle->p_drv);
}

/**
 * \brief I2S发送结束
 * \param[in] handle : I2S标准服务操作句柄
 * \retval AM_OK : 启动成功
 */
am_static_inline
int am_i2s_tx_stop (am_i2s_handle_t handle)
{
    return handle->p_funcs->pfn_i2s_tx_stop(handle->p_drv);
}

/**
 * \brief I2S接收结束
 * \param[in] handle : I2S标准服务操作句柄
 * \retval AM_OK : 启动成功
 */
am_static_inline
int am_i2s_rx_stop (am_i2s_handle_t handle)
{
    return handle->p_funcs->pfn_i2s_rx_stop(handle->p_drv);
}

/**
 * \brief 设置I2S回调函数
 *
 * \param[in] handle         : I2S标准服务操作句柄
 * \param[in] callback_type  : 指明设置的何种回调函数
 *            - AM_I2S_CALLBACK_GET_TX_DATA  : 获取一个发送字函数
 *            - AM_I2S_CALLBACK_PUT_RCV_DATA : 提交一个接收到的字给应用程序
 *            - AM_I2S_CALLBACK_ERROR        : 错误回调函数
 * \param[in] pfn_callback   : 指向回调函数的指针
 * \param[in] p_callback_arg : 回调函数的用户参数
 *
 * \retval  AM_OK      : 回调函数设置成功
 * \retval -AM_EINVAL  : 设置失败，参数错误
 */
am_static_inline
int am_i2s_callback_set (am_i2s_handle_t  handle,
                         int              callback_type,
                         int             (*pfn_callback)(void *),
                         void             *p_callback_arg)
{
    return handle->p_funcs->pfn_i2s_callback_set(handle->p_drv,
                                                 callback_type,
                                                 pfn_callback,
                                                 p_callback_arg);
}


/**
 * \brief I2S中断函数连接，仅使用中断模式时需要调用此函数
 * \param[in] handle  : I2S标准服务操作句柄
 * \retval  AM_OK     : 连接成功
 * \retval -AM_EINVAL : 失败，参数错误
 */
am_static_inline
int am_i2s_connect (am_i2s_handle_t handle)
{
    return handle->p_funcs->pfn_i2s_connect(handle->p_drv);
}


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2S_H */

/* end of file */
