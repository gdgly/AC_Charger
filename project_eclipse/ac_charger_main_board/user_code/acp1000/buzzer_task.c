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
 * \brief ����������
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#include "aw_delayed_work.h"
#include "aw_gpio.h"
#include "aw_delay.h"
#include "ac_charge_prj_cfg.h"

#define BUZZER_PIN     PIO2_1
#define BUZZER_TIME    50

static struct aw_delayed_work g_buzzer_work; /* acĸ�ż�⹤��  */

static uint32_t time = 0;                    /* ����������ÿ��ʱ��Ϊ12ms  */

/**
 * ׮�쳣�������
 */
static void buzzer_detect_work (void *p_arg)
{
    uint32_t gpio = (uint32_t)p_arg;
    uint32_t i    = 0;

    time++;
    if (time >= BUZZER_TIME) {
        time = 0;
    } else {
        aw_delayed_work_start(&g_buzzer_work, 2);
    }
    for (i = 0; i < 3; i++) {
        aw_gpio_set(gpio, 1);
        aw_udelay(500);
        aw_gpio_set(gpio, 0);
        aw_udelay(100);
    }
}

/**
 * ����������
 */
void acp1000_buzzer_on (void)
{
#if ACP1000_BUZZER_TASK
    aw_delayed_work_stop(&g_buzzer_work);
    aw_delayed_work_start(&g_buzzer_work, 10);
#endif
}

/**
  * \brief ׮�쳣���
  */
void buzzer_task_startup(void)
{
    aw_gpio_pin_cfg(BUZZER_PIN, AW_GPIO_OUTPUT);
    aw_delayed_work_init(&g_buzzer_work,
                          buzzer_detect_work,
                          (void *)BUZZER_PIN);
    aw_delayed_work_start(&g_buzzer_work, 100);


}
