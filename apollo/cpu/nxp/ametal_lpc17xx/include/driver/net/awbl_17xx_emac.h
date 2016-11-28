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
#include "aw_task.h"                    /* ��������� */
#include "aw_msgq.h"
#include "aw_sem.h"

#include "amhw_enet.h"
#include "awbl_miibus.h"

/* Sitara DriverLib Header Files required for this interface driver. */
#include "netif/ethernetif.h"


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#define AWBL_17XX_EMAC_NAME  		"awbl_17xx_emac"  /**< MAC���� */

/**
 * \brief 17XXPHYģʽ
 */
typedef enum {
	AWBL_17XXPHY_RMII_MODE = 0,  /**< ѡ��RMIIģʽ  */
} awbl_17xxphy_interface_mode_t;

/**
 * mac�ӿ� Helper struct to hold private data used to operate the ethernet interface.
 */
struct awbl_emacif {
    struct ethernet_if      ethif;           /**< ethernet_if�ṹ�� */
    amhw_enet_t            *p_hw_reg;        /**< MAC����ַ  */
    /* emac output mutex */
    AW_MUTEX_DECL(emac_out_mutex);
};

/**
 * \brief 17xx emac �豸��Ϣ
 */
struct awbl_17xx_emac_devinfo {
	uint32_t                emac_unit; 				    /**< MAC address nvram unit */
	char                   *p_hwaddr_name;              /**< MAC address nvram name*/

	amhw_enet_t            *p_hw_enet;                  /**< MAC����ַ  */
    uint32_t                inum;			 			/**< �ж�������		   */

    int                     create_mii_bus_id;          /**< ��EMAC������MII bus��� */
    int                     phy_use_mii_bus_id;         /**< ��EMAC���ӵ�PHYʹ�õ�MII bus��� */

    awbl_17xxphy_interface_mode_t interface_mode;       /**< AWBL_PHY_RMII_MODE or AWBL_PHY_MII_MODE */

    /** ƽ̨��س�ʼ�� */
    void (*pfunc_plfm_init)(void);
} awbl_17xx_emac_devinfo_t;

/**
 * \brief 17xx emac �豸ʵ��
 */
struct awbl_17xx_emac_dev {
	struct awbl_dev         emac_dev;         /**< AWBus �豸ʵ���ṹ��  */
	struct awbl_emacif      emac_if;          /**< mac�ӿ�  */

	struct awbl_mii_master  mii_master;		  /**< mii���� */
	struct awbl_dev        *p_emac_mii_dev;   /**< mii�豸ʵ�� */

	awbl_miibus_read_t      mii_phy_read;     /**< phy�� */
	awbl_miibus_write_t     mii_phy_write;    /**< phyд */

	AW_SEMB_DECL(mii_dev_semb);

	uint32_t                phy_mode;         /**< phy�Ĺ���ģʽ */
	uint32_t                phy_stat;         /**< phy��״̬ */

	int                     emac_init_flg;    /**< ��ʼ����ɱ�־ */
} awbl_17xx_emac_dev_t;


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_17XX_EMAC_H */

