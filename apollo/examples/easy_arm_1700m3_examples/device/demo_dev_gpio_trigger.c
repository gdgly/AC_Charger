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
 * e-mail:      anywhere.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief GPIO���Ŵ�������
 *
 * - �������裺
 *   1. ���ӻ�����չ��KEY1 <---> PIO2_6
 *
 * - ʵ������
 *   1. ���°���KEY1��LED״̬��ת��
 *
 * \par Դ����
 * \snippet demo_dev_gpio_trigger.c src_dev_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_gpio_trigger
 * \copydoc demo_dev_gpio_trigger.c
 */

/** [src_dev_gpio_trigger] */
#include "apollo.h"
#include "main.h"

#include "aw_task.h" 
#include "aw_delay.h"
#include "aw_gpio.h"  
#include "aw_led.h"

#define KEY1_PIN  PIO2_6

/**
 * \brief GPIO���Ŵ����жϷ�����
 *\param[in] p_arg : �������
 * \return ��
 */
static void gpio_trig_isr (void *p_arg)
{
    int led = (int)p_arg;
    
    aw_led_toggle(led);
}


/**
 * \brief GPIO���Ŵ����������   
 *\param[in] p_arg : �������
 * \return ��
 */
static void task_entry (void *p_arg)
{
    /* �����жϷ����������ţ������ȵ��øú��������ܵ��� aw_gpio_trigger_cfg() */
    aw_gpio_trigger_connect(KEY1_PIN, gpio_trig_isr, (void *)LED0);
    
    /* GPIO �������� */
    aw_gpio_trigger_cfg(KEY1_PIN, AW_GPIO_TRIGGER_FALL);
    
    /* ʹ�����Ŵ��� */
    aw_gpio_trigger_on(KEY1_PIN);
    
    while (1) {
        aw_mdelay(10);
    }
}

/**
 * \brief ����GPIO����
 * \return ��
 */
void demo_dev_gpio_trigger_entry (void)
{
    AW_TASK_DECL_STATIC(task, 256);
    
    AW_TASK_INIT(task,               /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL ���� */
                "task",              /* ��������                                            */ 
                 6,                  /* �������ȼ�                                          */ 
                 256,                /* �����ջ��С                                        */ 
                 task_entry,         /* ������ں���                                        */ 
                (void*)0);           /* ������ڲ���                                        */ 
    
    AW_TASK_STARTUP(task);
}

/** [src_dev_gpio_trigger] */
 
/* end of file */

