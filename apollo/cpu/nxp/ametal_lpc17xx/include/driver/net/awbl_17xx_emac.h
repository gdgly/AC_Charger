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
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC17XX EMAC Driver
 *
 * \internal
 * \par modification history:
 * - 1.00 15-10-20, snk, first implementation.
 * \endinternal
 */

#ifndef __AWBL_17XX_EMAC_H
#define __AWBL_17XX_EMAC_H

#include "aw_spinlock.h"
#include "aw_assert.h"
#include "aw_task.h"                    /* 多任务服务 */
#include "aw_msgq.h"
#include "aw_sem.h"

#include "amhw_enet.h"
#include "awbl_miibus.h"

/* Sitara DriverLib Header Files required for this interface driver. */
#include "netif/ethernetif.h"


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#define AWBL_17XX_EMAC_NAME  		"awbl_17xx_emac"  /**< MAC名字 */

/**
 * \brief 17XXPHY模式
 */
typedef enum {
	AWBL_17XXPHY_RMII_MODE = 0,  /**< 选择RMII模式  */
} awbl_17xxphy_interface_mode_t;

/**
 * mac接口 Helper struct to hold private data used to operate the ethernet interface.
 */
struct awbl_emacif {
    struct ethernet_if      ethif;           /**< ethernet_if结构体 */
    amhw_enet_t            *p_hw_reg;        /**< MAC基地址  */
    /* emac output mutex */
    AW_MUTEX_DECL(emac_out_mutex);
};

/**
 * \brief 17xx emac 设备信息
 */
struct awbl_17xx_emac_devinfo {
	uint32_t                emac_unit; 				    /**< MAC address nvram unit */
	char                   *p_hwaddr_name;              /**< MAC address nvram name*/

	amhw_enet_t            *p_hw_enet;                  /**< MAC基地址  */
    uint32_t                inum;			 			/**< 中断向量号		   */

    int                     create_mii_bus_id;          /**< 此EMAC创建的MII bus编号 */
    int                     phy_use_mii_bus_id;         /**< 此EMAC链接的PHY使用的MII bus编号 */

    awbl_17xxphy_interface_mode_t interface_mode;       /**< AWBL_PHY_RMII_MODE or AWBL_PHY_MII_MODE */

    /** 平台相关初始化 */
    void (*pfunc_plfm_init)(void);
} awbl_17xx_emac_devinfo_t;

/**
 * \brief 17xx emac 设备实例
 */
struct awbl_17xx_emac_dev {
	struct awbl_dev         emac_dev;         /**< AWBus 设备实例结构体  */
	struct awbl_emacif      emac_if;          /**< mac接口  */

	struct awbl_mii_master  mii_master;		  /**< mii总线 */
	struct awbl_dev        *p_emac_mii_dev;   /**< mii设备实例 */

	awbl_miibus_read_t      mii_phy_read;     /**< phy读 */
	awbl_miibus_write_t     mii_phy_write;    /**< phy写 */

	AW_SEMB_DECL(mii_dev_semb);

	uint32_t                phy_mode;         /**< phy的工作模式 */
	uint32_t                phy_stat;         /**< phy的状态 */

	int                     emac_init_flg;    /**< 初始化完成标志 */
} awbl_17xx_emac_dev_t;


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_17XX_EMAC_H */

