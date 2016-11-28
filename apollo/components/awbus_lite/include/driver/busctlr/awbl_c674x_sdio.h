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
 * \brief c674x sdio �豸ʵ��
 */
typedef struct awbl_c674x_sdio_dev {
    /** \brief �̳��� AWBus SDIO ���������� */
    awbl_sdio_host_t        host;
    AW_MUTEX_DECL(dev_mux);

    uint32_t                speed;

    AW_TASK_DECL(c674x_sdio_trans_task,
            __SDIO_SPI_TRANS_TASK_STACK_SIZE);
    AW_SEMB_DECL(sem_sync);

}awbl_c674x_sdio_dev_t;

/* sdio host �豸��Ϣ  */
typedef struct awbl_c674x_sdio_dev_info {
    awbl_sdio_host_info_t host_info;
    uint32_t              regbase;
    uint32_t              clkfreq;         /**< ����ʱ�ӵ�Ƶ�� */
    uint32_t              sdmmc_peripheral_num;

    uint32_t              task_trans_prio;  /**< �����������ȼ� */

    /** ƽ̨��س�ʼ��������ʱ�ӡ���ʼ�����ŵȲ��� */
    void (*pfunc_plfm_init)(void);
    int                    inum;             /**< SDMMC�жϺ�      */
    uint32_t               sd_status;        /**< SDMMC����״̬*/
    int                    dma_en;           /**< ʹ��DMA����      */
    int                    dma_rx_chan;      /**< DMA����ͨ���� */
    int                    dma_tx_chan;      /**< DMA����ͨ���� */
    int                    dma_status;       /**< DMA����״̬      */
    AW_SEMB_DECL(dma_sem);                   /**< DMA�ź���ʵ��         */
    aw_semb_id_t           dma_sem_id;       /**< DMA�ź���ID     */
    AW_SEMB_DECL(mmc_sem);                   /**< MMC�ź���ʵ��         */
    aw_semb_id_t           mmc_sem_id;       /**< MMC�ź���ID     */
    aw_ti_edma3_chan_res_t tx_chan_res;      /**< ����ͨ����Դ   */
    aw_ti_edma3_chan_res_t rx_chan_res;      /**< ����ͨ����Դ   */

    aw_ti_edma3_param_regs_t tx_param;       /**< ����ͨ����������*/
    aw_ti_edma3_param_regs_t rx_param;       /**< ����ͨ����������*/
}awbl_c674x_sdio_dev_info_t;

void awbl_c674x_sdio_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_c674x_SDIO_H */
