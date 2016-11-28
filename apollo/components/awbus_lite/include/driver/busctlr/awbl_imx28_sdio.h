/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief imx28x SDIO driver
 *
 * \internal
 * \par modification history:
 * - 1.00 14-09-15  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX28_SDIO_H
#define __AWBL_IMX28_SDIO_H


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#include "awbl_sdiobus.h"
#include "driver/dma/awbl_imx28_dma.h"

#define AWBL_IMX28_SDIO_NAME               "imx28_sdio"

#define __SDIO_SPI_TRANS_TASK_STACK_SIZE   2048

/**
 * \brief imx28 sdio 设备实例
 */
typedef struct awbl_imx28_sdio_dev {
    /** \brief 继承自 AWBus SDIO 主机控制器 */
    awbl_sdio_host_t        host;

    uint32_t                speed;
    uint8_t                 width;
    awbl_imx28_dma_desc_t  *dma_desc;
    uint8_t                *dma_buf;
    uint32_t                buf_size;
    awbl_imx28_dma_chan_dev dma_chan_dev;

    awbl_sdio_msg_t         *p_cur_msg;
    aw_spinlock_isr_t        lock;
    AW_TASK_DECL(            im28_sdio_trans_task,
                             __SDIO_SPI_TRANS_TASK_STACK_SIZE);
    AW_SEMC_DECL(            sem_sync);

}awbl_imx28_sdio_dev_t;

/* sdio host 设备信息  */
typedef struct awbl_imx28_sdio_dev_info {
    awbl_sdio_host_info_t host_info;

    uint32_t              regbase;
    uint32_t              clk_id;         /**< 输入时钟ID：取值CLK_SSP0~CLK_SSP3 */

    uint8_t               dma_en;
    uint32_t              dma_channel;    /**< DMA通道号 */
    uint32_t              dma_regbase;    /**< DMA寄存器基址 */
    int                   dma_inum;       /**< DMA中断号 */
    uint32_t              task_trans_prio;/**< 传输任务优先级 */

    /** 平台相关初始化：开启时钟、初始化引脚等操作 */
    void (*pfunc_plfm_init)(void);

}awbl_imx28_sdio_dev_info_t;

void awbl_imx28_sdio_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_IMX28_SDIO_H */
