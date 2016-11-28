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
 * \brief Apollo����Ϣ���е�ʹ������
 *
 * - �������裺
 *   1. ����demo_os_msgq_entry()����
 *
 * - ʵ������
 *   1.��ʱ���ص�������ÿ��3s�ӷ���һ������ʱ�䣬��һ������500ms
 *                                               �ڶ�������1000ms
 *                                               ����������2000ms
 *
 * \par Դ����
 * \snippet demo_os_msgq.c src_os_msgq 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_msgq
 * \copydoc demo_os_msgq.c
 */

/** [src_os_msgq] */ 

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_msgq.h"
#include "main.h"
#include "aw_input.h"
#include "aw_hwtimer.h"


/* ����һ����Ϣ����(LED��˸ʱ����) */                                    
AW_MSGQ_DECL_STATIC(led_msgq,32,sizeof(uint32_t)); 


/** 
 * \brief ��ʱ���жϷ�����
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return ��
 */
static void my_timer_isr (void *p_arg)
{ 
    static unsigned int time_ms = 0;
    static unsigned int lighton_ms = 0;
    time_ms += 100;
    
    if (time_ms >= 3000) {
       
        time_ms = 0;
        
        /* ÿ3���ӷ���һ������ʱ���һ����500ms.. �ڶ���1000ms... ��������2000 */
        if (lighton_ms == 0 || lighton_ms >= 2000) {
            lighton_ms = 500;
        } else if(lighton_ms == 500){
            lighton_ms = 1000;
        } else if(lighton_ms == 1000){
             lighton_ms = 2000;
        }
        
          
        /* ��ʱ���жϺ��������͵�ǰ��ʱ��ֵ��Ϊ��Ϣ */        
        AW_MSGQ_SEND(led_msgq,                   /* ��Ϣ����         */
                      &lighton_ms,               /* ������Ϣ         */     
            sizeof(unsigned int),                /* д�����ݴ�С������ȶ���ʱ��һ����Ϣ�󣬳������ֲ�д�� */
                 AW_MSGQ_WAIT_FOREVER,           /* ���õȴ���Ϣ�����ͣ���Ϣ������ʱ�� */
                 AW_MSGQ_PRI_NORMAL);         
        
    }   
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
    uint32_t lighton_ms;
 
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
           
        aw_hwtimer_enable(mytmr1,10);              /* ʹ��Ӳ����ʱ�����ж�Ƶ��5Hz */
    } 
   
    AW_FOREVER {
                
        AW_MSGQ_RECEIVE(led_msgq,                   /* ��Ϣ����         */
                        &lighton_ms,                /* ���ջ�����       */     
                   sizeof(uint32_t),                /* ��ȡ��Ϣ��С��ʼ�հ�����ʱ����Ϣ��С��ȡ�����˲�����δʹ�ã�    */
                         AW_MSGQ_WAIT_FOREVER);     /* ���õȴ�һ����Ϣ */
        
        aw_led_on(LED0);
        
        aw_mdelay(lighton_ms);  
        
        aw_led_off(LED0);                 
    }
}

/** 
 * \brief ��Ϣ���д������ں���
 */
void demo_os_msgq_entry (void)
{
    AW_TASK_DECL_STATIC(task,256); 

    AW_TASK_INIT(task,                 /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL ����� */             
                 "task",               /* ��������             */              
                     5,                /* �������ȼ�           */              
                   256,                /* �����ջ��С         */            
                  task_entry,          /* ������ں���         */                
                  (void*)2);           /* ������ڲ���         */
    
    AW_MSGQ_INIT(led_msgq,
                       32,             /* ��Ϣ������    (������δʹ��)       */
                 sizeof(uint32_t),     /* ÿ����Ϣ�Ĵ�С (������δʹ��)      */
                 AW_MSGQ_Q_PRIORITY);  /* ��ʼ��ʱ��ѡ�����ã�AW_SEM_Q_FIFO���Ⱥ�˳���Ŷӣ�  */
                                       /*   AW_SEM_Q_PRIORITY (�����ȼ��Ŷ�) (������δʹ��) */
    AW_TASK_STARTUP(task);
    
}

/** [src_os_msgq] */ 

/* end of file */
