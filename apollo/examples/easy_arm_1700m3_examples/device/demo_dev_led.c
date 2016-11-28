/*******************************************************************************
 *                                 apollo
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
 * \brief LED����
 *
 * - ʵ������
 *   1. LED��0.5s�����ڳ�����˸��
 *
 * \par Դ����
 * \snippet demo_dev_led.c src_dev_led
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_led
 * \copydoc demo_dev_led.c
 */

/** [src_dev_led] */
#include "apollo.h"
#include "main.h"

#include "aw_delay.h"
#include "aw_led.h"

/**
 * \brief LED�������    
 *\param[in] p_arg : �������
 * \return ��
 */
static void task_entry (void *p_arg)
{
    while (1) {
        aw_led_on(LED0);            /* ����LED2��   */
        aw_mdelay(500);             /* ��ʱ0.5s     */
        aw_led_off(LED0);
        aw_mdelay(500); 
        
        aw_led_set(LED0, TRUE);     /* ����LED3��   */
        aw_mdelay(500);
        aw_led_set(LED0, FALSE);    /* Ϩ��LED��    */
        aw_mdelay(500);

        aw_led_toggle(LED0);        /* LED״̬��ת  */
        aw_mdelay(500);
        aw_led_toggle(LED0);        /* LED״̬��ת  */
        aw_mdelay(500);
    } 
}

/**
 * \brief ����LED����
 * \return ��
 */
void demo_dev_led_entry (void)
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

/** [src_dev_led] */
 
/* end of file */
