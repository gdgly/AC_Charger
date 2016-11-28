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
#ifndef __ACP1000_DOUT_H
#define __ACP1000_DOUT_H

#include "apollo.h"
#include "aw_gpio.h"
#include "aw_delay.h"

//#define ACP1000_DOUT_GUNLOCK    PIO0_6 /* DO_LOCK */
#define ACP1000_DOUT_LED1    PIO2_5 /* DO_LED1 */
#define ACP1000_DOUT_LED2    PIO2_6 /* DO_LED2 */
#define ACP1000_DOUT_LED3    PIO2_7  /* DO_LED3 */
#define ACP1000_DOUT_LEDS    PIO2_3  /* DO_LEDS */
#define ACP1000_DOUT_AC      PIO2_4  /* DO_AC */
#define ACP1000_DOUT_INLOCK  PIO4_11  /* DO_INLOCK (桩内置的锁，枪来时锁上，鉴权成功后解锁) */
#define ACP1000_DOUT_UNLOCK  PIO4_12 /* DO_REV2 */

#define ACP1000_GREEN_LED    ACP1000_DOUT_LED3 /* 正常，空闲时绿灯恒亮  */
#define ACP1000_YELLOW_LED   ACP1000_DOUT_LED2 /* 正常，充电时黄灯恒亮  */
#define ACP1000_LED_RED      ACP1000_DOUT_LED1 /* 异常时红灯恒亮 */

#define ACP1000_LED_STATE_GREEN   0
#define ACP1000_LED_STATE_YELLOW  1
#define ACP1000_LED_STATE_RED     2

#define ACP1000_INLOCK_LOCK       1 /* 锁住桩上的枪锁 */
#define ACP1000_INLOCK_UNLOCK     0 /* 解除桩上的枪锁 */

/**
 * \brief 初始化数字输出引脚
 * \return AW_OK : 初始化成功
 * \return AW_ERR: 初始化失败
 */
aw_err_t acp1000_dout_init (void);


aw_local inline void acp1000_led1_set(bool_t is_en)
{
    aw_gpio_set(ACP1000_DOUT_LED1, is_en);
}

aw_local inline void acp1000_led2_set(bool_t is_en)
{
    aw_gpio_set(ACP1000_DOUT_LED1, is_en);
}

aw_local inline void acp1000_led3_set(bool_t is_en)
{
    aw_gpio_set(ACP1000_DOUT_LED1, is_en);
}

/**
 * 桩上的枪解锁
 */
aw_local inline void acp1000_gun_unlock()
{
    aw_gpio_set(ACP1000_DOUT_UNLOCK, 1);
    aw_gpio_set(ACP1000_DOUT_INLOCK, 0);
    aw_mdelay(200);
    aw_gpio_set(ACP1000_DOUT_UNLOCK, 0);
    aw_gpio_set(ACP1000_DOUT_INLOCK, 0);
}

/**
 * 桩上的枪锁闭
 */
aw_local inline void acp1000_gun_lock()
{
    aw_gpio_set(ACP1000_DOUT_INLOCK, 1);
    aw_gpio_set(ACP1000_DOUT_UNLOCK, 0);
    aw_mdelay(200);
    aw_gpio_set(ACP1000_DOUT_UNLOCK, 0);
    aw_gpio_set(ACP1000_DOUT_INLOCK, 0);
}



/**
 * \brief 设置LED等的状态
 * param[in] state       : 灯的状态
 * param[in] is_charging : 是否正在充电
 */
void acp1000_state_led_set(int state, bool_t is_charging);

#endif /* __ACP1000_DOUT_H */
