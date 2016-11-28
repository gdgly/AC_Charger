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
 * \brief  SSP驱动，服务SSP标准接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-28  ben, first implementation.
 * \endinternal
 */

#ifndef __AMDR_SSP_H
#define __AMDR_SSP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_spi.h"    
#include "am_types.h"
#include "amhw_int.h"
#include "amhw_power.h"
#include "amhw_ssp.h"

/**
 * \addtogroup amdr_if_ssp
 * \copydoc amdr_ssp.h
 * @{
 */


/**
 * \brief SSP 设备信息结构体
 */
typedef struct amdr_ssp_devinfo {
    
	amhw_ssp_t   *p_hw_ssp;            /**< \brief 指向SPI寄存器块的指针  */
    uint16_t      inum;                /**< \brief SSP 中断编号          */
    uint8_t       bits_per_word;       /**< \brief 数据帧的位数          */
    uint32_t      flags;               /**< \brief SPI 配置标识          */
    uint32_t      speed;               /**< \brief 初始化速率            */

} amdr_ssp_devinfo_t;

/** \brief SSP 设备信息重定义 */
typedef amdr_ssp_devinfo_t am_ssp_devinfo_hw_t;


/**
 * \brief SSP 设备
 */
typedef struct amdr_ssp_dev {
    
     /** \brief SSP标准服务操作句柄 */
    am_spi_serv_t             spi_serve;  
    
    /** \brief 指向SPI传输结构体的指针 */
    am_spi_transfer_t        *p_trans; 
    
    /** \brief 指向SSP设备信息的指针 */
    const amdr_ssp_devinfo_t *p_devinfo;
    
    uint8_t         state;          /**< \brief 当前状态   */
    
    uint32_t        cur_speed;      /**< \brief 控制器当前速度   */
    uint8_t         cur_bpw;        /**< \brief 控制器当前字大小 */
    uint8_t         cur_flags;      /**< \brief 控制器当前模式   */   
    uint32_t        nbytes_to_recv; /**< \brief 待接收的字节数   */    
    uint32_t        data_tx_ptr;    /**< \brief 数据传输记数     */
    uint32_t        data_rx_ptr;    /**< \brief 数据传输记数     */    
       
} amdr_ssp_dev_t;

/**
 * \brief SSP 初始化
 *
 * \param[in] p_dev     : 指向SSP设备结构体的指针
 * \param[in] p_devinfo : 指向SSP设备信息结构体的指针
 *
 * \return  SPI标准服务操作句柄 
 */
am_spi_handle_t amdr_ssp_init(amdr_ssp_dev_t           *p_dev,
                              const amdr_ssp_devinfo_t *p_devinfo);

/**
 * \brief 解除SPI初始化
 * \param[in] p_dev : 指向SPI设备结构体的指针
 * \return 无
 */
void amdr_ssp_deinit(amdr_ssp_dev_t *p_dev);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

/* end of file */

