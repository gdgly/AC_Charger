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
 * \brief C674X EMIFA driver head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-08-31  deo, first implementation
 * \endinternal
 */


#ifndef __AWBL_C674X_EMIFA_H
#define __AWBL_C674X_EMIFA_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "aw_spinlock.h"
#include "awbl_nandbus.h"

#define AWBL_C674X_EMIFA_NAME "awbl_c674x_emifa_name"


/* CS and wait pin define */
#define AWBL_C674X_EMIFA_CS2			(0x00)
#define AWBL_C674X_EMIFA_CS3			(0x01)
#define AWBL_C674X_EMIFA_CS4			(0x02)
#define AWBL_C674X_EMIFA_CS5			(0x03)
#define AWBL_C674X_EMIFA_WAIT0			(0x00)
#define AWBL_C674X_EMIFA_WAIT1			(0x04)
#define AWBL_C674X_EMIFA_BUS_8BIT		(0x00)
#define AWBL_C674X_EMIFA_BUS_16BIT		(0x08)

struct awbl_c674x_emifa_addrbase {
	uint32_t	reg;
	uint32_t	data;
	uint32_t	addr;
	uint32_t	cmd;
};

/* C674X EMIFA information. */
struct awbl_c674x_emifa_devinfo {
	struct awbl_nand_controller_info		controller_info;
	const struct awbl_c674x_emifa_addrbase	*base;
	int										irq_id;
	uint32_t								module_clk_feq;
	void (*pfunc_plfm_init)(void);
};

/* C674X EMIFA */
struct awbl_c674x_emifa {
	struct awbl_nand_controller	controller;
	struct awbl_nand_chip		*cur_chip;
	uint32_t					timing_set;
};

void awbl_c674x_emifa_drv_register (void);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/


#endif /* __AWBL_C674X_EMIFA_H */
