/*******************************************************************************
*                                 Apollo
*                       ----------------------------
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
 * awbl_imx28_can.h
 * \internal
 * \par modification history:
 * - 1.01 15-11-16  cae, first implementation
 * \endinternal
 */


#ifndef AWBL_IMX28_CAN_H_
#define AWBL_IMX28_CAN_H_

#define AWBL_IMX28_CAN_NAME "imx28_can"

#include "awbl_can.h"

/*******************************************************************************
    types
*******************************************************************************/
/** \brief imx28 can device channel structure for awbus lite */
typedef struct awbl_imx28x_can_dev {

	/**< \brief device */
	struct awbl_dev  dev;

	 /** \brief driver functions, always goes first */
    struct awbl_can_service can_serv;

    /**< \brief 用于记录发送类型 */
    uint8_t sendtype;

} awbl_imx28x_can_dev_t;

/** \brief imx28 can initialization structure for plb based AWBus devices */
typedef struct awbl_imx28x_can_dev_info {

    awbl_can_servinfo_t  servinfo;
    uint8_t              int_num;
    uint32_t             reg_base;

    void   (*pfn_plfm_init)(void);
} awbl_imx28x_can_dev_info_t;


void awbl_imx28_flexcan_registration(void);

#endif /* AWBL_IMX28_can_H_ */
