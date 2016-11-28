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
 * \brief c674x SDIO driver
 *
 * \internal
 * \par modification history:
 * - 1.00 15-11-5  sss, first implementation
 * \endinternal
 */

#ifndef __AWBL_C674x_SDIO_H
#define __AWBL_C674x_SDIO_H


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#include "awbl_sdiobus.h"

#include "aw_ti_edma3.h"

#define AWBL_C674X_SDIO_NAME               "c674x_sdio"

#define __SDIO_SPI_TRANS_TASK_STACK_SIZE   2048

/**
 * \brief c674x sdio 设备实例
 */
typedef struct awbl_c674x_sdio_dev {
    /** \brief 继承自 AWBus SDIO 主机控制器 */
    awbl_sdio_host_t        host;
    AW_MUTEX_DECL(dev_mux);

    uint32_t                speed;

    AW_TASK_DECL(c674x_sdio_trans_task,
            __SDIO_SPI_TRANS_TASK_STACK_SIZE);
    AW_SEMB_DECL(sem_sync);

}awbl_c674x_sdio_dev_t;

/* sdio host 设备信息  */
typedef struct awbl_c674x_sdio_dev_info {
    awbl_sdio_host_info_t host_info;
    uint32_t              regbase;
    uint32_t              clkfreq;         /**< 输入时钟的频率 */
    uint32_t              sdmmc_peripheral_num;

    uint32_t              task_trans_prio;  /**< 传输任务优先级 */

    /** 平台相关初始化：开启时钟、初始化引脚等操作 */
    void (*pfunc_plfm_init)(void);
    int                    inum;             /**< SDMMC中断号      */
    uint32_t               sd_status;        /**< SDMMC传输状态*/
    int                    dma_en;           /**< 使能DMA传输      */
    int                    dma_rx_chan;      /**< DMA接收通道号 */
    int                    dma_tx_chan;      /**< DMA发送通道号 */
    int                    dma_status;       /**< DMA传输状态      */
    AW_SEMB_DECL(dma_sem);                   /**< DMA信号量实体         */
    aw_semb_id_t           dma_sem_id;       /**< DMA信号量ID     */
    AW_SEMB_DECL(mmc_sem);                   /**< MMC信号量实体         */
    aw_semb_id_t           mmc_sem_id;       /**< MMC信号量ID     */
    aw_ti_edma3_chan_res_t tx_chan_res;      /**< 发送通道资源   */
    aw_ti_edma3_chan_res_t rx_chan_res;      /**< 接收通道资源   */

    aw_ti_edma3_param_regs_t tx_param;       /**< 发送通道参数集合*/
    aw_ti_edma3_param_regs_t rx_param;       /**< 接收通道参数集合*/
}awbl_c674x_sdio_dev_info_t;

void awbl_c674x_sdio_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_c674x_SDIO_H */
