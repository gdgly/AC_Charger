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
 * \brief Apollo���ӳ���ҵ��ʹ������
 *
 * - �������裺
 *   1. ����demo_os_delayedwork_entry()����
 *
 * - ʵ������
 *   1.ʹ���ӳٹ�����ʹ�����ӳ�500ms�����С����Կ���LED����1Hz��Ƶ����˸��
 *   2.10sʱ�����˸10�κ󣩣��رն�ʱ����LED������˸ 
 *
 * \par Դ����
 * \snippet demo_os_delayedwork.c src_os_delayedwork 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_delayedwork
 * \copydoc demo_os_delayedwork.c
 */

/** [src_os_delayedwork] */

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
 
#include "aw_led.h"
#include "main.h"
 
/*
 * ʹ���ӳ���ҵ���ܱ��������ͷ�ļ�
 */
#include "aw_delayed_work.h"

static struct aw_delayed_work work;                 /* �����ӳٹ����ṹ����� */

/** 
 * \brief �ӳٹ�����������
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void my_work (void *p_arg)
{ 
    struct aw_delayed_work  *p_work = (struct aw_delayed_work  *) p_arg;   
    
    aw_led_toggle(LED0);
    
    aw_delayed_work_start(p_work, 500);     /* �ٴ��ӳٹ���������������������� */
}

/** 
 * \brief �������ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void task_entry(void *p_arg)
{
    aw_delayed_work_init(&work, my_work, &work);    /* ��ʼ��work         */
                                          
    /* �����ӳٹ�������500ms�������ӳٹ�������    */
    aw_delayed_work_start(&work, 500);              /* �ӳ�500ms���������� */
    
    /* ��ʱ 10S.    */
    aw_task_delay(aw_ms_to_ticks(10 * 1000));
    
    /* ֹͣ�ӳٹ��� */
    aw_delayed_work_stop(&work); 
    
    AW_FOREVER {
         
        /*do some other things */
        
        aw_mdelay(10);
    }        
}


/** 
 * \brief �ӳ���ҵ��ں���
 */
void demo_os_delayedwork_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������           */
                   8,                /* �������ȼ�       */
                  512,               /* ����ջ��С       */
                  task_entry,        /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task0);          /* ��������         */
}

/** [src_os_delayedwork] */

/* end of file */
