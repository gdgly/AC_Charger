/*******************************************************************************
 *                                 Apollo
 *                       ---------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.embedcontrol.com/
 * e-mail:      apollo.support@zlg.cn
 *******************************************************************************/
/**
 * \file
 * \brief �����벶��(CAP)��ʾ���̣�����ƽ̨EasyARM-1700M3
 *
 * - ��������:
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_TIMER0_CAP
 *   2. USART0�ӿں�PC��������������
 *   3. ��P1.26(��ʱ��0���벶��ܽ�)��P2.2��LED0�����ӡ�
 *
 * - ʵ������:
 *   1. ���ڴ�ӡ���벶��ʱ�䡣
 *
 * \par Դ����
 * \snippet demo_dev_cap.c src_dev_cap
 *
 * \internal
 * \par History
 * - 1.00 15-10-13  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_cap
 * \copydoc demo_dev_cap.c
 */

/** [src_dev_cap] */
#include "apollo.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */

/* �������õ������·��� */
#include "aw_delay.h"                   /* ��ʱ����              */
#include "aw_cap.h"                     /* ���벶�����              */
#include "aw_led.h"                     /* LED ����              */
#include "aw_gpio.h"
#include "aw_vdebug.h"
#include "aw_sem.h"

#define CAP_CHANNEL  0   /* ���벶��ͨ���� */

/* ����led������  */
static void __my_callback(void *arg, unsigned int count)
{
    static unsigned int num = 0;
    static unsigned int count1;
    unsigned int period_ns;

    if (num == 0) {
        count1 = count;        /* ��һ�β���õ���ֵ */
        num = 1;
    } else {
        /* �õ�����������֮���ʱ�䣬�����ε����� */
        aw_cap_count_to_time(0, count1, count, &period_ns);
        aw_kprintf("��ò��ε�����Ϊ:%d ns\n",period_ns);
    }
    count1 = count;            /*  ����ֵ */
}

/* ����������LED0��ת������һ��������������  */
static void led_task_entry(void)
{
	for (;;) {
		aw_led_toggle(0);
		aw_mdelay(40);
	}

}

/**
 * \brief ���벶������
 **/
void cap_task (void)
{
	/* ���벶�����ã�˫���ش��� */
	aw_cap_config(CAP_CHANNEL, AW_CAP_TRIGGER_BOTH_EDGES, &__my_callback, 0);
    aw_cap_enable(CAP_CHANNEL);  /* ʹ�����벶�� */

    while (1) {
    	aw_mdelay(5);
    }

}


/**
 * \brief ����CAP����
 * \return ��
 */
void demo_dev_cap_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0, 512);
    AW_TASK_DECL_STATIC(led_toggle_task, 512);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������          */
                   2,                /* �������ȼ�      */
                  512,               /* ����ջ��С       */
                  cap_task,          /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */

    AW_TASK_STARTUP(task0);          /* ��������        */

    /* ��ʼ������led_task */
     AW_TASK_INIT(led_toggle_task,         /* ����ʵ�� */
                  "led_task",              /* �������� */
                  5,                       /* �������ȼ� */
                  512,                     /* �����ջ��С */
                  led_task_entry,          /* ������ں��� */
                  (void *)0);              /* ������ڲ��� */

     AW_TASK_STARTUP(led_toggle_task);          /* ��������        */
}
/** [src_dev_cap] */

/* end of file */
