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
* e-mail:      Apollo.support@zlg.cn
*******************************************************************************/

#ifndef __AWBL_HWCONF_PWM_BUZZER_H
#define __AWBL_HWCONF_PWM_BUZZER_H

#ifdef AW_DEV_PWM_BUZZER

#include "driver/buzzer/awbl_buzzer_pwm.h"

aw_local aw_const awbl_pwm_buzzer_param_t __g_pwm_buzzer_param = {
    10,           /* PWMͨ��ID */
    1000000,      /* PWM�����������(��λ: ����) */
    80            /* ��ʼ��� 80% */
};

aw_local awbl_pwm_buzzer_t __g_pwm_buzzer;

#define AWBL_HWCONF_PWM_BUZZER   \
    {                            \
        PWM_BUZZER_NAME,         \
        0,                       \
        AWBL_BUSID_PLB,          \
        0,                       \
        &(__g_pwm_buzzer.dev),   \
        &(__g_pwm_buzzer_param)  \
    },                           \

#else
#define AWBL_HWCONF_PWM_BUZZER

#endif  /* AW_DEV_PWM_BUZZER */

#endif /* __AWBL_HWCONF_PWM_BUZZER_H */

/* end of file */
