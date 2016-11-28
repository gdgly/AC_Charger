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
  lpc17xx I2C0 ������Ϣ
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_I2C_0

#include "driver/i2c/awbl_ametal_i2c.h"
#include "ametal.h"

#define CLKDIV_VALUE_I2C0  (6)
#define BUS_SPEED_I2C0     (20000)

/**
 * \brief I2C0 �豸��Ϣ
 */
const  struct amdr_i2c_devinfo  g_i2c0_devinfo = {
	BUS_SPEED_I2C0,							/**< \brief I2Cʱ�� */
    AMHW_I2C0,                              /**< \brief ָ��I2C0�Ĵ������ָ�� */
    INUM_I2C0,                              /**< \brief I2C0 �жϱ��          */
};
amdr_i2c_dev_t    g_i2c0_dev;               /**< \brief I2C0 �豸ʵ��          */


/** \brief I2C0 ƽ̨��ʼ������ */
void amhw_plfm_i2c0_init (void)
{
	am_gpio_pin_cfg(PIO1_30, PIO1_30_SDA0);
	am_gpio_pin_cfg(PIO1_31, PIO1_31_SCL0);

	amhw_power_periph_up(AMHW_POWER_I2C0);
}

/** \brief ���I2C0 ƽ̨��ʼ������ */
void amhw_plfm_i2c0_deinit (void)
{
	amhw_power_periph_down(AMHW_POWER_I2C0);
}

/** @} */

/**
 * \brief i2c0 controller platform parameter definition 
 */
am_local const struct awbl_ametal_i2c_devinfo  __g_ametal_i2c0_devinfo = {
    {
		LPC17XX_I2C0_BUSID,         /* ����������Ӧ�����߱��  */
        BUS_SPEED_I2C0,             /* �����������ٶ�          */
        AWBL_I2C_WAITFOREVER        /* ��ʱ                   */
    },
    
    &g_i2c0_dev,
    &g_i2c0_devinfo,
    
    (pfn_i2c_init_t)amdr_i2c_init,
    amhw_plfm_i2c0_init
};   


/* I2C0 �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_i2c_dev __g_ametal_i2c0_dev;


#define AWBL_HWCONF_LPC17XX_I2C_0     \
     {                                \
        AWBL_AMETAL_I2C_NAME,         \
        0,                            \
        AWBL_BUSID_PLB,               \
        0,                            \
        (struct awbl_dev *)&__g_ametal_i2c0_dev,    \
        &__g_ametal_i2c0_devinfo                    \
    },

#else 

#define AWBL_HWCONF_LPC17XX_I2C_0

#endif  /* AW_DEV_LPC17XX_I2C_0 */

