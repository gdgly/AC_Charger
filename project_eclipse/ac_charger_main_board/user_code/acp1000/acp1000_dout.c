/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief ACP1000 数字输出检测接口实现
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-24  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "acp1000_dout.h"
#include "aw_gpio.h"
#include "lpc177x_8x_pin.h"

/**
 * \brief 初始化数字输出引脚
 * \return AW_OK : 初始化成功
 * \return AW_ERR: 初始化失败
 */
aw_err_t acp1000_dout_init (void)
{
    /* data input */
    int acp_dout[] = {
#ifdef ACP1000_DOUT_GUNLOCK
                      ACP1000_DOUT_GUNLOCK,
#endif
                      ACP1000_DOUT_LED1,
                      ACP1000_DOUT_LED2,
                      ACP1000_DOUT_LED3,
                      ACP1000_DOUT_LEDS,
                      ACP1000_DOUT_AC  ,
                      ACP1000_DOUT_INLOCK,
                      ACP1000_DOUT_UNLOCK,
                      };

    int i           = 0;

    /* init dout */
    for (i = 0; i < sizeof(acp_dout)/sizeof(acp_dout[0]); i++) {
        am_gpio_pin_cfg(acp_dout[i], AM_GPIO_OUTPUT);
        aw_gpio_set(acp_dout[i], 0);
    }
    aw_gpio_set(ACP1000_GREEN_LED,  1); /* 上电默认常亮绿灯 */
    return AW_OK;
}


/**
 * 设置LED等的状态
 */
void acp1000_state_led_set(int state, bool_t is_charging)
{
    switch (state) {

    case ACP1000_LED_STATE_GREEN:
//        aw_gpio_set(ACP1000_GREEN_LED,  1);
//        aw_gpio_set(ACP1000_YELLOW_LED, 0);
        aw_gpio_set(ACP1000_LED_RED,    0);
        break;

    case ACP1000_LED_STATE_YELLOW:
//            aw_gpio_set(ACP1000_GREEN_LED,  0);
//            aw_gpio_set(ACP1000_YELLOW_LED, 1);
            aw_gpio_set(ACP1000_LED_RED,    0);
            break;

    case ACP1000_LED_STATE_RED:
    default:
//            aw_gpio_set(ACP1000_GREEN_LED,  0);
//            aw_gpio_set(ACP1000_YELLOW_LED, 0);
            aw_gpio_set(ACP1000_LED_RED,    1);
            break;
    }

    if (is_charging) {
        aw_gpio_set(ACP1000_YELLOW_LED, 1);
    } else {
        aw_gpio_set(ACP1000_YELLOW_LED, 0);
    }
}

