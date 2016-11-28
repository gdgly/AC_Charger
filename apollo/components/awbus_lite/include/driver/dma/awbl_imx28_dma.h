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
 * \brief
 *
 * \internal
 * \par modification history:
 * - 1.00 140618, axn, first implementation.
 * \endinternal
 */
#ifndef __AWBL_IMX28_DMA_H
#define __AWBL_IMX28_DMA_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_spinlock.h"

#include "aw_sem.h"                     /* 信号量服务 */

#define AWBL_IMX28_DMA_NAME   "imx28_dma"

#define DMA_CHANNEL_0				0
#define DMA_CHANNEL_1				1
#define DMA_CHANNEL_2				2
#define DMA_CHANNEL_3				3
#define DMA_CHANNEL_4				4
#define DMA_CHANNEL_5				5
#define DMA_CHANNEL_6				6
#define DMA_CHANNEL_7				7
#define DMA_CHANNEL_8				8
#define DMA_CHANNEL_9				9
#define DMA_CHANNEL_10				10
#define DMA_CHANNEL_11				11
#define DMA_CHANNEL_12				12
#define DMA_CHANNEL_13				13
#define DMA_CHANNEL_14				14
#define DMA_CHANNEL_15				15

#define	IMX28_DMA_CHANNEL_SSP0			DMA_CHANNEL_0
#define	IMX28_DMA_CHANNEL_SSP1			DMA_CHANNEL_1
#define	IMX28_DMA_CHANNEL_SSP2			DMA_CHANNEL_2
#define	IMX28_DMA_CHANNEL_SSP3			DMA_CHANNEL_3
#define	IMX28_DMA_CHANNEL_GPMI0			DMA_CHANNEL_4
#define	IMX28_DMA_CHANNEL_GPMI1			DMA_CHANNEL_5
#define	IMX28_DMA_CHANNEL_GPMI2			DMA_CHANNEL_6
#define IMX28_DMA_CHANNEL_GPMI3			DMA_CHANNEL_7
#define	IMX28_DMA_CHANNEL_GPMI4			DMA_CHANNEL_8
#define	IMX28_DMA_CHANNEL_GPMI5			DMA_CHANNEL_9
#define	IMX28_DMA_CHANNEL_GPMI6			DMA_CHANNEL_10
#define	IMX28_DMA_CHANNEL_GPMI7			DMA_CHANNEL_11
#define	IMX28_DMA_CHANNEL_HSADC			DMA_CHANNEL_12
#define	IMX28_DMA_CHANNEL_LCDIF			DMA_CHANNEL_13

#define	IMX28_DMA_CHANNEL_AUART4_RX		DMA_CHANNEL_0
#define	IMX28_DMA_CHANNEL_AUART4_TX		DMA_CHANNEL_1
#define	IMX28_DMA_CHANNEL_SPDIF_TX		DMA_CHANNEL_2
//#define	IMX28_DMA_CHANNEL_EMPTY		DMA_CHANNEL_3
#define	IMX28_DMA_CHANNEL_SAIF0			DMA_CHANNEL_4
#define	IMX28_DMA_CHANNEL_SAIF1			DMA_CHANNEL_5
#define	IMX28_DMA_CHANNEL_I2C0			DMA_CHANNEL_6
#define	IMX28_DMA_CHANNEL_I2C1			DMA_CHANNEL_7
#define	IMX28_DMA_CHANNEL_AUART0_RX		DMA_CHANNEL_8
#define	IMX28_DMA_CHANNEL_AUART0_TX		DMA_CHANNEL_9
#define	IMX28_DMA_CHANNEL_AUART1_RX		DMA_CHANNEL_10
#define	IMX28_DMA_CHANNEL_AUART1_TX		DMA_CHANNEL_11
#define	IMX28_DMA_CHANNEL_AUART2_RX		DMA_CHANNEL_12
#define	IMX28_DMA_CHANNEL_AUART2_TX		DMA_CHANNEL_13
#define	IMX28_DMA_CHANNEL_AUART3_RX		DMA_CHANNEL_14
#define	IMX28_DMA_CHANNEL_AUART3_TX		DMA_CHANNEL_15

#define IMX28_DMA_TRANS_OK              0
#define IMX28_DMA_DESC_ERR              1
#define IMX28_DMA_NOT_INIT				2

/*
 * 	DMA CMD
 */
#define IMX28_DMA_CMD_XFER_COUNT(x)         (x << 16) /* 16bit, 0 表示64KB */
#define IMX28_DMA_CMD_CMDWORDS(x)           (x << 12) /* 4bit */
#define IMX28_DMA_CMD_HALTONTERMINATE(x)    (x << 8)  /* 1bit */
#define IMX28_DMA_CMD_WAIT4ENDCMD(x)        (x << 7)  /* 1bit */
#define IMX28_DMA_CMD_SEMAPHORE(x)          (x << 6)  /* 1bit */
#define IMX28_DMA_CMD_NANDWAIT4READY(x)     (x << 5)  /* 1bit */
#define IMX28_DMA_CMD_NANDLOCK(x)           (x << 4)  /* 1bit */

#define IMX28_DMA_CMD_IRQONCMPLT(x)         (x << 3)  /* 1bit */
#define IMX28_DMA_CMD_CHAIN(x)     			(x << 2)  /* 1bit */
#define IMX28_DMA_CMD_COMMAND(x)           	(x << 0)  /* 2bit */

#define IMX28_CMD_COMMAND_NO_DMA_XFER       0
#define IMX28_CMD_COMMAND_DMA_WRITE         1
#define IMX28_CMD_COMMAND_DMA_READ          2
#define IMX28_CMD_COMMAND_DMA_SENSE         3


#if !defined(MAX_PIO_WORDS)
#define MAX_PIO_WORDS   (15)
#endif


/**
 * \brief imx28 dma 设备信息
 */
struct awbl_imx28_dma_devinfo {

    uint32_t apbh_regbase;               /**< apbh 寄存器基地址 */
    uint32_t apbx_regbase;               /**< apbx 寄存器基地址 */

    /** 平台相关初始化 */
    void (*pfunc_plfm_init)(void);
};

/**
 * \brief imx28 SSP 设备实例
 */
struct awbl_imx28_dma_dev {
	struct awbl_dev dma_dev;
	void *p_data;
};


/**
 * DMA descriptor
 */
typedef struct _DMA_DESCRIPTOR {
    volatile uint32_t next_cmd_desc;
    volatile uint32_t command;
    volatile uint32_t buf_addr;
    volatile uint32_t pio_word[MAX_PIO_WORDS];
} awbl_imx28_dma_desc_t;

typedef awbl_imx28_dma_desc_t awbl_imx28_ssp_dma_desc;
typedef awbl_imx28_dma_desc_t awbl_imx28_gpmi_dma_desc;
typedef awbl_imx28_dma_desc_t awbl_imx28_hsadc_dma_desc;
typedef awbl_imx28_dma_desc_t awbl_imx28_lcdif_dma_desc;
typedef awbl_imx28_dma_desc_t awbl_imx28_auart_dma_desc;
typedef awbl_imx28_dma_desc_t awbl_imx28_i2c_dma_desc;
typedef awbl_imx28_dma_desc_t awbl_imx28_spdif_dma_desc;
typedef awbl_imx28_dma_desc_t awbl_imx28_saif_dma_desc;


/**
 * \brief imx28 DMA 通道结构
 */
typedef struct  imax_dma_chan{

	uint32_t     		    regbase;
	uint32_t     		    channel;
	awbl_imx28_dma_desc_t  *p_dma_desc;

	AW_SEMB_DECL(dma_sem_sync);   /**< /brief 用于同步传输任务的信号量 */

    uint32_t                trans_counter;
    uint8_t                 init_flg;
    aw_pfuncvoid_t          pfunc_complete_cb;
    void 				   *parg;
    int                     status;
}awbl_imx28_dma_chan_dev;

typedef enum _DMA_BURST_SIZE{
	BURST0 = 0,
	BURST4 = 1,
	BURST8 = 2
}DMA_BURST_SIZE;

uint8_t   imx28_dma_chan_brust_set(awbl_imx28_dma_chan_dev *dma_chan_dev, DMA_BURST_SIZE burst_size);

void      aw_imx28_dma_chan_init(	uint32_t dma_regbase,
									uint32_t dma_channel,
									uint32_t dma_inum,
									awbl_imx28_dma_chan_dev *dma_chan_dev);

aw_err_t aw_imx28_dma_chan_start_sync(awbl_imx28_dma_chan_dev *dma_chan_dev,
                                      uint8_t                  dma_semaphore,
                                      uint32_t                 timeout);

uint32_t  aw_imx28_dma_chan_start_async(awbl_imx28_dma_chan_dev *dma_chan_dev,
										uint8_t dma_semaphore,
										aw_pfuncvoid_t pfunc_complete,
										void *parg);

void aw_imx28_dma_chan_stop(awbl_imx28_dma_chan_dev *dma_chan_dev);
#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif

/* end of file */


