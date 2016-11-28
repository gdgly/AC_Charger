/*
 * awbl_lpc17xx_sdio.h
 *
 *  Created on: 2014-9-15
 *      Author: wengyedong
 */

#ifndef AWBL_IMX28_SDIO_H_
#define AWBL_IMX28_SDIO_H_


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#ifdef AW_LPC177X_8X

#include "awbl_sdiobus.h"
#include "driver/dma/awbl_lpc17xx_dma.h"
#include "amdr_mci.h"

#define AWBL_LPC17XX_SDIO_NAME            "lpc17xx_sdio"

#define __SDIO_SPI_TRANS_TASK_STACK_SIZE        2048


/** \brief LPC17x MCI 初始化函数类型 */
typedef int (*pfunc_mci_init_t) (void *, const void *);

/**
 * \brief lpc17xx sdio 设备实例
 */
typedef struct awbl_lpc17xx_sdio_dev {
    /** \brief 继承自 AWBus SDIO 主机控制器 */
	awbl_sdio_host_t  host;

	uint32_t		speed;

	AW_SEMB_DECL(dma_complete_sem);

	AW_TASK_DECL(trans_task, __SDIO_SPI_TRANS_TASK_STACK_SIZE);
    AW_SEMB_DECL(sem_sync);                 /**< /brief 用于同步传输任务的信号量 */

}awbl_lpc17xx_sdio_dev_t;

/* sdio host 设备信息  */
typedef struct awbl_lpc17xx_sdio_dev_info {
	awbl_sdio_host_info_t host_info;

    uint8_t		dma_en;
    uint32_t    dma_channel;  	/**< DMA通道号 */
    uint32_t    fifo_regaddr;   /**< SDIO FIFO的地址 */
    uint32_t    task_trans_prio;/**< 传输任务优先级 */


    /**< \brief 设备 */
    void        *p_hw_dev;

    /**< \breif 设备信息 */
    const void  *p_hw_devinfo;

    /**< \brief 接口初始化 */
    pfunc_mci_init_t  pfunc_mci_init;

    /**< \brief 平台相关初始化：开启时钟、初始化引脚等操作 */
    void (*pfunc_plfm_init)(void);

}awbl_lpc17xx_sdio_dev_info_t;

void awbl_lpc17xx_sdio_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AW_LPC177X_8X */

#endif /* AWBL_IMX28_SDIO_H_ */
