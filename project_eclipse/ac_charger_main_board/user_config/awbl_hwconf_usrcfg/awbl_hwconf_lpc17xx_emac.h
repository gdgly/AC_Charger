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
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
  lpc17xx EMAC 配置信息
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_EMAC

#include "driver/net/awbl_17xx_emac.h"
#include "ametal.h"


/** \brief 平台初始化函数 */
void amhw_plfm_emac_init (void)
{
    /* 配置GPIO引脚功能 */
    am_gpio_pin_cfg(PIO1_0,  PIO1_0_ENET_TXD0);
    am_gpio_pin_cfg(PIO1_1,  PIO1_1_ENET_TXD1);
    am_gpio_pin_cfg(PIO1_4,  PIO1_4_ENET_TX_EN);
    am_gpio_pin_cfg(PIO1_8,  PIO1_8_ENET_CRS);
    am_gpio_pin_cfg(PIO1_9,  PIO1_9_ENET_RXD0);
    am_gpio_pin_cfg(PIO1_10, PIO1_10_ENET_RXD1);
    am_gpio_pin_cfg(PIO1_14, PIO1_14_ENET_RX_ER);
    am_gpio_pin_cfg(PIO1_15, PIO1_15_ENET_REF_CLK);
    am_gpio_pin_cfg(PIO1_16, PIO1_16_ENET_MDC);
    am_gpio_pin_cfg(PIO1_17, PIO1_17_ENET_MDIO);
    /* 开启电源 */
    amhw_power_periph_up(AMHW_POWER_ENET);
}

/** \brief 解除平台初始化函数 */
void amhw_plfm_emac_deinit (void)
{
    /* 关闭电源 */
	amhw_power_periph_down(AMHW_POWER_ENET);
}




/** \brief 设备信息 */
aw_local aw_const struct awbl_17xx_emac_devinfo __g_17xx_emac_devinfo = {
	0,					   /* emac unit0*/
	"otp_zy_mac",          /* MAC address nvram name*/

	AMHW_EMAC,             /* emac寄存器基地址 */
	INUM_ENET,             /* 中断编号    */

	LPC17XX_MII0_BUSID,   /* 此EMAC创建的MII bus编号 */
	LPC17XX_MII0_BUSID,   /* 此EMAC链接的PHY使用的MII bus编号 */
    AWBL_17XXPHY_RMII_MODE,    /* PHY MODE */
    amhw_plfm_emac_init,       /* 平台相关初始化 */
};

/** \brief 设备实例内存静态分配 */
aw_local struct awbl_17xx_emac_dev __g_17xx_emac_dev;

#define AWBL_HWCONF_LPC17XX_EMAC   \
    {                               \
		AWBL_17XX_EMAC_NAME,                  \
		0,        \
        AWBL_BUSID_PLB,             \
        0,										\
        (struct awbl_dev *)&__g_17xx_emac_dev,         \
        &__g_17xx_emac_devinfo          \
    },


#else

#define AWBL_HWCONF_LPC17XX_EMAC

#endif  /* AW_DEV_LPC17XX_EMAC */

/* end of file */
