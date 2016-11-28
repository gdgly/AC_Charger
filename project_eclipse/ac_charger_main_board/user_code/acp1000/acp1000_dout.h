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
 * \brief ACP1000 ����������ӿ�ʵ��
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
#define ACP1000_DOUT_INLOCK  PIO4_11  /* DO_INLOCK (׮���õ�����ǹ��ʱ���ϣ���Ȩ�ɹ������) */
#define ACP1000_DOUT_UNLOCK  PIO4_12 /* DO_REV2 */

#define ACP1000_GREEN_LED    ACP1000_DOUT_LED3 /* ����������ʱ�̵ƺ���  */
#define ACP1000_YELLOW_LED   ACP1000_DOUT_LED2 /* ���������ʱ�Ƶƺ���  */
#define ACP1000_LED_RED      ACP1000_DOUT_LED1 /* �쳣ʱ��ƺ��� */

#define ACP1000_LED_STATE_GREEN   0
#define ACP1000_LED_STATE_YELLOW  1
#define ACP1000_LED_STATE_RED     2

#define ACP1000_INLOCK_LOCK       1 /* ��ס׮�ϵ�ǹ�� */
#define ACP1000_INLOCK_UNLOCK     0 /* ���׮�ϵ�ǹ�� */

/**
 * \brief ��ʼ�������������
 * \return AW_OK : ��ʼ���ɹ�
 * \return AW_ERR: ��ʼ��ʧ��
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
 * ׮�ϵ�ǹ����
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
 * ׮�ϵ�ǹ����
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
 * \brief ����LED�ȵ�״̬
 * param[in] state       : �Ƶ�״̬
 * param[in] is_charging : �Ƿ����ڳ��
 */
void acp1000_state_led_set(int state, bool_t is_charging);

#endif /* __ACP1000_DOUT_H */
