/*******************************************************************************
 *                                 Apollo
 *                       ---------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.embedcontrol.com/
 * e-mail:      apollo.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief GPIO����
 *
 * - ʵ������
 *   1. LED��0.5s��������˸5�Σ�
 *   2. LED��0.1s�����ڳ�����˸��
 *
 * \par Դ����
 * \snippet demo_dev_gpio.c src_dev_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_gpio
 * \copydoc demo_dev_gpio.c
 */

/** [src_dev_gpio] */
#include "apollo.h"
#include "main.h"

#include "aw_task.h" 
#include "aw_delay.h"
#include "aw_gpio.h"

#define LED_PIN  PIO2_2
/**
 * \brief GPIO�������    
 *\param[in] p_arg : �������
 * \return ��
 */
static void task_entry (void *p_arg)
{
    int i = 0;
    
    /* GPIO �������� */  
    aw_gpio_pin_cfg(LED_PIN, AW_GPIO_OUTPUT | AW_GPIO_PULL_UP);

    /* LED��0.5s��������˸5�� */
    for (i = 0; i < 5; i++) {
        aw_gpio_set(LED_PIN, 0);
        aw_mdelay(500);
        
        aw_gpio_set(LED_PIN, 1);
        aw_mdelay(500);
    }
    
    /* LED��0.1s�����ڳ�����˸ */
    while (1) {
        aw_gpio_toggle(LED_PIN);
        aw_mdelay(100);
    }
}

/**
 * \brief ����GPIO����
 * \return ��
 */
void demo_dev_gpio_entry (void)
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

/** [src_dev_gpio] */
 
/* end of file */
