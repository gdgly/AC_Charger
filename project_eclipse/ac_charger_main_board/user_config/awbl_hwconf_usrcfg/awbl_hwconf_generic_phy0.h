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
 * \file
 * \brief
 *
 * \internal
 * \par modification history
 * - 1.00 15-11-06  snk, first implementation
 * \endinternal
 */
#ifdef AW_DEV_GENERIC_PHY0
#include "aw_gpio.h"
#include "aw_delay.h"                   /* ��ʱ���� */

#include "driver/phy/awbl_generic_phy.h"

#define  PHY0_ADDR         			0x05   /* phy addr */

/* ƽ̨��س�ʼ�� */
aw_local void __generic_phy0_plfm_init (void)
{
	/* ��λ�ܽ� */
}

/* �豸��Ϣ */
aw_local aw_const struct awbl_generic_phy_devinfo __g_gen_phy0_devinfo = {
	PHY0_ADDR,                  /* phy addr */
	AWBL_PHY_LINK_AUTONEG,      /* PHY mode */
	__generic_phy0_plfm_init,   /* ƽ̨��س�ʼ�� */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_generic_phy_dev __g_gen_phy0_dev;


#define AWBL_HWCONF_GENERIC_PHY0   \
    {                               \
		AWBL_GENERIC_PHY_NAME,                  \
        0,        \
        AWBL_BUSID_MII,             \
        LPC17XX_MII0_BUSID,										\
        (struct awbl_dev *)&__g_gen_phy0_dev,         \
        &__g_gen_phy0_devinfo          \
    },
#else

#define AWBL_HWCONF_GENERIC_PHY0

#endif /* AWBL_HWCONF_GENERIC_PHY0_H_ */
/* end of file */

