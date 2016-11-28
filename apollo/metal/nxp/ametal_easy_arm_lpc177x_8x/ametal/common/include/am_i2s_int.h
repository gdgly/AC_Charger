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
 * \brief I2S interrupt mode implementation
 * 
 * \internal
 * - 1.01 15-07-14  sam.
 * \endinternal
 */

#ifndef __AM_I2S_INT_H
#define __AM_I2S_INT_H



#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2s.h"

/**
 * \addtogroup am_if_i2s_int
 * \copydoc am_i2s_int.h
 * @{
 */
    
/**
 * \brief I2S（中断模式）设备结构体
 */
typedef struct am_i2s_int_dev {
    
    /** \brief I2S标准服务操作句柄     */
    am_i2s_handle_t    handle;

    /** \brief 指向I2S发送缓冲区的指针 */
    uint32_t          *p_txbuf;
    
    /** \brief 发送数据个数             */
    volatile uint32_t  tx_nbytes;
    
    /** \brief 指向I2S接收缓冲区的指针 */
    volatile uint32_t *p_rxbuf;
    
    /** \brief 结束数据个数             */
    volatile uint32_t  rx_nbytes;
		  
} am_i2s_int_dev_t;

/** \brief I2S（中断模式）标准服务操作句柄类型定义 */
typedef struct am_i2s_int_dev *am_i2s_int_handle_t;


/**
 * \brief 初始化I2S为中断模式
 *
 * \param[in] p_dev   : I2S（中断模式）设备结构体指针
 * \param[in] handle  : I2S标准服务操作句柄
 *
 * \return I2S（中断模式）标准服务操作句柄，如果值为NULL，表明初始化失败
 */
am_i2s_int_handle_t am_i2s_int_init(am_i2s_int_dev_t *p_dev,
                                    am_i2s_handle_t   handle);

/**
 * \brief I2S数据发送（中断模式）
 *
 * \param[in] handle  : I2S（中断模式）标准服务操作句柄
 * \param[in] p_txbuf : 发送数据缓冲区
 * \param[in] nbytes  : 待发送数据的个数
 * 
 * \return 成功发送数据的个数
 */
int am_i2s_int_send(am_i2s_int_handle_t  handle,
                    const uint32_t      *p_txbuf,
                    uint32_t             nbytes);
                            

/**
 * \brief I2S数据接收（中断模式）
 *
 * \param[in] handle  : I2S（中断模式）标准服务操作句柄
 * \param[in] p_rxbuf : 接收数据缓冲区
 * \param[in] nbytes  : 待接收数据的个数
 * 
 * \return 成功接收数据的个数
 */
int am_i2s_int_receive(am_i2s_int_handle_t  handle,
                       uint32_t            *p_rxbuf,
                       uint32_t             nbytes);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2S_INT_H */

/* end of file */
