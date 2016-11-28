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
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
    LED������Ϣ
*******************************************************************************/
#ifdef AW_DEV_LED_GPIO

#include "driver/led/awbl_gpio_led.h"
#include "aw_gpio.h"

/* LED�豸GPIO��Ϣ */
aw_local aw_const uint16_t __g_led_gpios[] = {
        PIO4_4,
};

/* LED�豸��Ϣ */
aw_local aw_const struct awbl_led_gpio_param __g_led_data = {
    /* led_gpio, num_leds, base_num, active_low */
    __g_led_gpios, 
    {
        0,
        0
    },
    AW_NELEMENTS(__g_led_gpios), 
    TRUE,
};

/* LED�豸ʵ���ڴ澲̬���� */
aw_local struct awbl_led_gpio_dev __g_led_dev;


#define AWBL_HWCONF_LED     \
    {                       \
        GPIO_LED_NAME,      \
        0,                  \
        AWBL_BUSID_PLB,     \
        0,                  \
        &(__g_led_dev.dev), \
        &(__g_led_data)     \
    },
#else

#define  AWBL_HWCONF_LED    
    
#endif /* AW_COM_AWBL_LED */

/* end of file */

