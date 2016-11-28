/*******************************************************************************
*                                 AnyWhere
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
  LPC5410x GPIO 配置信息  
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_GPIO

#include "apollo.h"
#include "awbl_gpio.h"
#include "lpc177x_8x_pin.h"

#include "driver/gpio/awbl_ametal_gpio.h"
#include "amdr_gpio.h"
#include "am_gpio.h"
#include "ametal.h"

/**
 * \brief 对于100脚的封装，PIO0 + PIO2 = 28 + 14 = 42,即最大管脚中断数目为42，
 * 对于80脚的封装，PIO0 + PIO2 = 19 + 11 = 30,即最大管脚中断数目为30，为节省
 * 空间，可以将该值设置为实际用到的管脚中断数目（如10），且不要超过上限值。
 */
#define GPIO_INT_COUNT    64

/** \brief 引脚触发信息内存 */
static struct amdr_gpio_trigger_info g_gpio_triginfos[GPIO_INT_COUNT];

/** \brief GPIO设备信息 */
const amdr_gpio_devinfo_t g_gpio_devinfo = {

    AMHW_GPIO_BASE,    /**< \brief GPIO的基地址                  */
    AMHW_PINCON,       /**< \brief 指向Pin connect寄存器块的指针  */
    AMHW_GPIOINT,      /**< \brief 指向引脚中断寄存器块的指针     */

    INUM_GPIO,        /**< \brief GPIO中断号             */

    GPIO_INT_COUNT,    /**< \brief 使用到的管脚中断数目          */
    
    g_gpio_triginfos   /**< \brief 引脚触发信息内存              */
};

/** \brief GPIO设备实例 */
amdr_gpio_dev_t g_gpio_dev;

/** \brief GPIO平台初始化 */
void amhw_plfm_gpio_init (void)
{
    /* GPIO上电 */
    amhw_power_periph_up(AMHW_POWER_GPIO);
}

/** \brief GPIO平台去初始化 */
void amhw_plfm_gpio_deinit (void)
{
    /* GPIO关闭电源 */
    amhw_power_periph_down(AMHW_POWER_GPIO);
}

/** \brief GPIO 设备信息 */
aw_local struct awbl_ametal_gpio_param __g_lpc17xx_gpio_param = {
    &g_gpio_dev,
    &g_gpio_devinfo,
    
    {
        PIO0_0,            /**< \brief 支持的最小引脚编号     */
        PIO5_4,           /**< \brief 支持的最大引脚编号     */
    },
    
    {
        INUM_PIO0_0,       /**< \brief 支持的最小引脚中断编号 */
        INUM_PIO5_4       /**< \brief 支持的最小引脚中断编号 */
    },
    
    (pfunc_gpio_init_t)(&amdr_gpio_init),
    &amhw_plfm_gpio_init
};

/** \brief GPIO 设备实例内存静态分配 */
awbl_ametal_gpio_dev_t __g_ametal_gpio_dev;


#define AWBL_HWCONF_LPC17XX_GPIO    \
    {                               \
        AWBL_AMETAL_GPIO_NAME,      \
        0,                          \
        AWBL_BUSID_PLB,             \
        0,                          \
        (struct awbl_dev *)&__g_ametal_gpio_dev,   \
        &__g_lpc17xx_gpio_param    \
    },

#else

#define  AWBL_HWCONF_LPC17XX_GPIO
 
#endif  /* AW_DRV_AWBL_LPC17XX_GPIO */

/* end of file */

