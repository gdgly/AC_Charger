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
 * \brief Apollo�ж������ź�����ʹ������
 *
 * - �������裺
 *   1. ����demo_os_semb_entry()����
 *
 * - ʵ������
 *   1.LED0��100ms��ʱ��������
 *
 * \par Դ����
 * \snippet demo_os_semb.c src_os_semb 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_os_semb
 * \copydoc demo_os_semb.c
 */

/** [src_os_semb] */

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_sem.h"
#include "main.h"
#include "aw_input.h"
#include "aw_hwtimer.h"

AW_SEMB_DECL_STATIC(led_semb);                        /* ����һ���������ź��� */

 
/** 
 * \brief ��ʱ���жϺ���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return ��
 */
static void my_timer_isr (void *p_arg)
{               
    AW_SEMB_GIVE(led_semb);   /* �������ź������ֵ��Ϊ1���ͷ��ٶ࣬ʹ��һ��Ҳ��������*/       
}

/** 
 * \brief ������ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void task_entry(void *p_arg)
{   

    static aw_hwtimer_handle_t mytmr1;
       
    /*  
     * ����õ�һ����ʱ��
     */
    mytmr1 = aw_hwtimer_alloc( 1000000,               /* �����Ķ�ʱ������Ƶ�� */
                                 10,                  /* ��ʱ���жϵ���СƵ�� */
                                100000,               /* ��ʱ���жϵ����Ƶ�� */
                             AW_HWTIMER_AUTO_RELOAD,  /* ��ʱ���ܹ��Զ���װ�� */
                              my_timer_isr,           /* ��ʱ���жϻص�����   */
                                (void *)0);           /* ���ݸ��ص������Ĳ��� */
                              
                                                       
                                      
    if (mytmr1 == AW_HWTIMER_NULL) {
         /*  ������ʱ������ʧ�� */
         
    } else {
           
        aw_hwtimer_enable(mytmr1,10);     /* ʹ��Ӳ����ʱ�����ж�Ƶ��5Hz */
    } 
    
    AW_FOREVER {
                
        AW_SEMB_TAKE(led_semb,AW_SEM_WAIT_FOREVER);
        
        /* �յ��������ź����󣬷�תLED��*/
        aw_led_toggle(LED0);               
    }
}

/** 
 * \brief �������ź����������ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return ��
 */
void demo_os_semb_entry (void *p_arg)
{

    AW_TASK_DECL_STATIC(task,256);   
    
    AW_TASK_INIT(task,          /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL ����� */
                "task",         /* ��������     */
                         5,     /* �������ȼ�   */
                       256,     /* �����ջ��С */
                 task_entry,    /* ������ں��� */      
                  (void*)0);    /* ������ڲ��� */
    
    
    AW_SEMB_INIT(led_semb,
                 AW_SEM_EMPTY,    /* ��ʼ��Ϊ��״̬                                   */
                 AW_SEM_Q_FIFO);  /* ��ʼ��ʱ��ѡ�����ã�AW_SEM_Q_FIFO���Ⱥ�˳���Ŷӣ�*/
                                  /* AW_SEM_Q_PRIORITY (�����ȼ��Ŷ�)                 */
    AW_TASK_STARTUP(task);      
    
}

/** [src_os_semb] */

/* end of file */
