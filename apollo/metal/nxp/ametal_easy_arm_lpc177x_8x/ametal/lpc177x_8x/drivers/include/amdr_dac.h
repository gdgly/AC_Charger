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
 * \brief  DAC驱动，服务DAC标准接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-05-29  snk, first implementation.
 * \endinternal
 */

#ifndef __AMDR_DAC_H
#define __AMDR_DAC_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_dac.h"
#include "amhw_dac.h"
    
/** 
 * \addtogroup amdr_if_dac
 * \copydoc amdr_dac.h
 * @{
 */
    
/**
 * \brief DAC设备信息结构体
 */
typedef struct amdr_dac_devinfo {
    
    /** \brief 指向DAC寄存器块的结构体指针    */
    amhw_dac_t  *p_hw_dac;

    /** \brief DAC采样精度 */
    uint8_t     bits;

    /** \brief  DAC参考电压    */
    uint32_t    vref;
   
} amdr_dac_devinfo_t;

/**
 * \brief DAC设备结构体
 */
typedef struct amdr_dac_dev {

    am_dac_serv_t              dac_serv;   /**< \brief DAC标准服务           */
    const amdr_dac_devinfo_t  *p_devinfo;  /**< \brief 指向DAC设备信息的指针 */
} amdr_dac_dev_t;

/**
 * \brief 初始化DAC 
 *
 * \param[in] p_dev     : 指向DAC设备
 * \param[in] p_devinfo : 指向DAC设备信息
 *
 * \return  DAC 标准服务操作句柄。如果为 NULL，表明初始化失败。
 */
am_dac_handle_t amdr_dac_init(amdr_dac_dev_t           *p_dev,
                              const amdr_dac_devinfo_t *p_devinfo);

/**
 * \brief 解初始化DAC
 * \param[in] p_dev : 指向DAC设备
 * \return  无
 */
void amdr_dac_deinit(amdr_dac_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_DAC_H */

/* end of file */
