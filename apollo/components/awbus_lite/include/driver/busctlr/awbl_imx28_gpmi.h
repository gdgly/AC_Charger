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
 * \brief IMX28 GPMI head file
 *
 * define IMX28 GPMI data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 14-12-11  deo, first implementation
 * \endinternal
 */
#ifndef __AWBL_IMX28_GPMI_NAND_H
#define __AWBL_IMX28_GPMI_NAND_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "aw_spinlock.h"
#include "awbl_nandbus.h"
#include "driver/dma/awbl_imx28_dma.h"

#define AWBL_IMX28_GPMI_NAME "awbl_imx28_gpmi"

/* CE ID define */
#define AWBL_IMX28_GPMI_CE0		0
#define AWBL_IMX28_GPMI_CE1		1
#define AWBL_IMX28_GPMI_CE2		2
#define AWBL_IMX28_GPMI_CE3		3
#define AWBL_IMX28_GPMI_CE4		4
#define AWBL_IMX28_GPMI_CE5		5
#define AWBL_IMX28_GPMI_CE6		6
#define AWBL_IMX28_GPMI_CE7		7

/* IMX28 GPMI information. */
struct awbl_imx28_gpmi_devinfo {
	struct awbl_nand_controller_info	controller_info;

	uint32_t							clk_id;
	uint32_t    						gpmi_regbase;
	uint32_t							bch_regbase;

    uint32_t 							dma_channel;	/* DMA channel */
    uint32_t 							dma_regbase;	/* register base */
    int      							dma_inum;		/* DMA IRQ */

	void (*pfunc_plfm_init)(void);
};

/* IMX28 GPMI */
struct awbl_imx28_gpmi {
	struct awbl_nand_controller	controller;
	struct awbl_nand_chip		*cur_chip;

	awbl_imx28_dma_desc_t		*dma_desc;
	uint8_t						*dma_buf;
	awbl_imx28_dma_chan_dev		dma_chan_dev;

};

void awbl_imx28_gpmi_drv_register (void);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AWBL_IMX28_GPMI_NAND_H */
