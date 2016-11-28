/*******************************************************************************
*                                 Apollo
*                       ---------------------------
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
 * \brief LPC17xx DMA driver
 *
 * \internal
 * \par modification history:
 * - 1.00 15-08-31  anu, first implementation
 * \endinternal
 */

#ifndef __AWBL_LPC17XX_DMA_H
#define __AWBL_LPC17XX_DMA_H

#include "awbus_lite.h"

#include "amdr_dma.h"

#ifdef __cplusplus
extern "C" {
#endif  


#define AWBL_LPC17XX_DMA_NAME   "lpc17xx_dma"

/** \brief LPC17x DMA 初始化函数类型 */
typedef int (*pfunc_dma_init_t) (void *, void *);


/**
 * \brief LPC17xx DMA 设备信息
 */
typedef struct awbl_lpc17xx_dma_param {

    /** \brief LPC17xx DMA 设备 */
    struct amdr_dma_dev     *p_dev;
    
    /** \brief LPC17xx DMA 设备信息 */
    struct amdr_dma_devinfo *p_devinfo;
    
    /** \brief DMA 初始化函数 */
    pfunc_dma_init_t pfunc_dma_init;
    
    /** \brief DMA 平台初始化函数 */
    void (*pfunc_plfm_init)(void);
} awbl_lpc17xx_dma_param_t;

/**
 * \brief lpc17xx DMA设备实例
 */
typedef struct awbl_lpc17xx_dma_dev {

    /** \brief 继承自 AWBus 设备 */
    struct awbl_dev dma_dev;
    
} awbl_lpc17xx_dma_dev_t;

/*****************************************************************************/

void awbl_lpc17xx_dma_drv_register(void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_LPC5410X_DMA_H */

/* end of file */


