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
  lpc17xx I2C1 配置信息
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_I2C_1

#include "ametal.h"
#include "driver/i2c/awbl_ametal_i2c.h"

#define BUS_SPEED_I2C1     (400000)

/**
 * \brief I2C1 设备信息
 */
const  struct amdr_i2c_devinfo  g_i2c1_devinfo = {
	BUS_SPEED_I2C1,					 		/**< \brief I2C时钟 */
    AMHW_I2C1,                              /**< \brief 指向I2C1寄存器块的指针 */
    INUM_I2C1,                              /**< \brief I2C1 中断编号 */
};
amdr_i2c_dev_t    g_i2c1_dev;                  /**< \brief I2C1 设备实例 */

/** \brief I2C1 平台初始化函数 */
void amhw_plfm_i2c1_init (void)
{
	am_gpio_pin_cfg(PIO0_19, PIO0_19_SDA1 | PIO0_19_OD_ENABLE);
    am_gpio_pin_cfg(PIO0_20, PIO0_20_SCL1 | PIO0_20_OD_ENABLE);

	amhw_power_periph_up(AMHW_POWER_I2C1);
}

/** \brief 解除I2C1 平台初始化函数 */
void amhw_plfm_i2c1_deinit (void)
{
	amhw_power_periph_down(AMHW_POWER_I2C1);
}

/** @} */

/**
 * \brief i2c1 controller platform parameter definition 
 */
am_local const struct awbl_ametal_i2c_devinfo  __g_ametal_i2c1_devinfo = {
    {
		LPC17XX_I2C1_BUSID,         /* 控制器所对应的总线编号  */
        BUS_SPEED_I2C1,             /* 控制器总线速度          */
        AWBL_I2C_WAITFOREVER        /* 超时                   */
    },
    
    &g_i2c1_dev,
    &g_i2c1_devinfo,
    
    (pfn_i2c_init_t)amdr_i2c_init,
    amhw_plfm_i2c1_init
};   


/* I2C1 设备实例内存静态分配 */
aw_local struct awbl_ametal_i2c_dev __g_ametal_i2c1_dev;


#define AWBL_HWCONF_LPC17XX_I2C_1    \
     {                               \
        AWBL_AMETAL_I2C_NAME,       \
        1,                           \
        AWBL_BUSID_PLB,              \
        0,                           \
        (struct awbl_dev *)&__g_ametal_i2c1_dev,    \
        &__g_ametal_i2c1_devinfo                    \
    },

#else 

#define AWBL_HWCONF_LPC17XX_I2C_1

#endif  /* AW_DEV_LPC17XX_I2C_1 */
