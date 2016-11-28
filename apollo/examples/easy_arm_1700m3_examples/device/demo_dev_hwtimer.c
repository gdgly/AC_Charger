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
 * e-mail:      appollo.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief Ӳ����ʱ������
 *
 * - �������裺
 *   1. PIO0_0��������PC���ڵ�TXD��
 *   2. PIO0_1��������PC���ڵ�RXD��
 *
 * - ʵ������
 *   1. LED��1s�����ڳ�����˸��
 *   2. �����ʱ������ʧ�ܣ��������ʧ����Ϣ��
 *
 * \par Դ����
 * \snippet demo_dev_hwtimer.c src_dev_hwtimer
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_hwtimer
 * \copydoc demo_dev_hwtimer.c
 */

/** [src_dev_hwtimer] */
#include "apollo.h"
#include "main.h"

#include "aw_delay.h"  
#include "aw_led.h"
#include "aw_hwtimer.h"   
#include "aw_vdebug.h"

#define RIT_UNIT_ID 7

/**
 * \brief Ӳ����ʱ���жϷ�������
 * \param[in] p_arg : �������
 * \return ��
 */
static void mytimer_isr (void *p_arg)
{
    aw_led_toggle(LED0);  
}

/**
 * \brief Ӳ����ʱ���������
 * \param[in] p_arg : �������
 * \return ��
 */
static void task_entry (void *p_arg)
{
    static aw_hwtimer_handle_t  mytmr;  /* ��ʱ����� */

    mytmr = aw_hwtimer_alloc(100000,                     /* ��������Ƶ��100kHz */
							 1,                          /* ��СƵ��1Hz  */
							 80000,                      /* ���Ƶ��80kHz   */
							 AW_HWTIMER_CAN_INTERRUPT |  /* �ܲ����ж�   */
							 AW_HWTIMER_AUTO_RELOAD,     /* �Զ���װ   */
							 &mytimer_isr,               /* �жϷ�����         */
							 (void *) NULL);             /* �жϷ�������ں��� */
    if (AW_HWTIMER_NULL != mytmr) {

		aw_hwtimer_enable (mytmr, 1);  /* ʹ�ܶ�ʱ�ж� 1Hz     */
		aw_mdelay(20000);              /* �ȴ�20s     */
		aw_hwtimer_disable (mytmr);    /* �رն�ʱ��     */

		aw_hwtimer_release(mytmr);     /* ��ʱ������ʹ�ã��ͷŸö�ʱ�� */
    } else {
        aw_kprintf("Timer allocation fail!\n");
    }
}

/**
 * \brief ����Ӳ����ʱ������
 * \return ��
 */
void demo_dev_hwtimer_entry (void)
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

/** [src_dev_hwtimer] */
 
/* end of file */
