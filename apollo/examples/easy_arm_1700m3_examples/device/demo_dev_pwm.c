/*******************************************************************************
 *                                 Apollo
 *                       ---------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.embedcontrol.com/
 * e-mail:      apollo.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief PWM��ʾ����
 * - LED�ܽţ�|  ��         |   ID   |   �ܽ�         |    ��ɫ   |
 *            -----------------------------------------
 *            | LED0  |   0    |  PIO0_16 |    ��ɫ   |
 *
 * - PWM�ӿڣ�| �ܽ�       | ͨ����    |
 *            ------------------
 *            |PIO2_0 |  PWM0  |
 *            ------------------
 *            |PIO2_1 |  PWM1  |
 *            ------------------
 *            |PIO2_2 |  PWM3  |
 * - �������裺
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_MCPWM��AW_DEV_LPC17XX_PWM
 *   2. ��PWM�������ӵ��߼������ǻ�ʾ�����Ȳ��������ϣ���Ⲩ�Ρ�
 *
 * - ʵ������     
 *   1. PWM0��PWM1��PWM2��·ͬʱ������PWM0 10%;PWM2 20%;PWM3 50%����
 *   2. ��ʱ1s PWM1ֹͣ������
 *   3. LED ���200ms ��˸��
 *
 * \par Դ����
 * \snippet demo_dev_pwm.c src_dev_pwm
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_dev_pwm
 * \copydoc demo_dev_pwm.c
 */

/** [src_dev_pwm] */
#include "apollo.h"
#include "main.h"

#include "aw_delay.h"
#include "aw_gpio.h"
#include "aw_pwm.h"
#include "aw_buzzer.h"
#include "aw_input.h"


#define PWM0        0
#define PWM1        1
#define PWM2        2

#define PERIOD      1000000

/**
 * \brief pwm_task program entry 
 * \details ����������ѡPWMͨ������Чʱ������ڣ���ʹ��ʱ������ͨ��ͬʱֻ�����ó�
 *          ͬһ���ڣ�Ȼ��ʹ�ܶ�Ӧ��ͨ���� Ƶ��1KHz
 *          [1].����3·PWM����������1--PWMͨ���� ����2--PWMռ�ձ� ����3--PWM����
 *          [2].ʹ��PWM
 *          
 *\note ���PWM
 */
void pwm_task (void *p_arg)
{

    aw_pwm_config(PWM0, PERIOD / 10, PERIOD);   /* ����PWM0����Чʱ�䣨�ߵ�ƽʱ�䣩10% ,���� */
    aw_pwm_config(PWM1, PERIOD / 5, PERIOD);    /* ����PWM1����Чʱ�䣨�ߵ�ƽʱ�䣩20% ,���� */ 
    aw_pwm_config(PWM2, PERIOD / 2, PERIOD);    /* ����PWM1����Чʱ�䣨�ߵ�ƽʱ�䣩20% ,���� */
    aw_pwm_enable(PWM0);     /* ʹ��ͨ��0 */
    aw_pwm_enable(PWM1);     /* ʹ��ͨ��1 */
    aw_pwm_enable(PWM2);     /* ʹ��ͨ��2 */
    aw_mdelay(1000);
    aw_pwm_disable(PWM1);    /* ����ͨ��1 */


}

/**
 * \brief ����PWM����
 * \return ��
 */
void demo_dev_pwm_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������          */
                   2,                /* �������ȼ�      */
                  512,               /* ����ջ��С       */
                  pwm_task,          /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task0);          /* ��������        */
}

/** [src_dev_pwm] */

/* end of file */
