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
 * \brief Apollo�м����ź�����ʹ������
 *
 * - �������裺
 *   1. ����demo_os_sembc_entry()����
 *
 * - ʵ������
 *   1.ÿ��1s��LED0��˸����
 *
 * - ˵����
 *   �����ź�����������ź��������𣬼����ź������Լ�����1,2,3... 
 *   �������ź���ֻ��ʵ��1��0����������GIVE���Σ��������ź���ֻ��
 *   TAKE1�Σ��������ź�������TAKE����
 *
 * \par Դ����
 * \snippet demo_os_semc.c src_os_semc 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_semc
 * \copydoc demo_os_semc.c
 */

/** [src_os_semc] */  

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_sem.h"
#include "main.h"
#include "aw_hwtimer.h"


AW_SEMC_DECL_STATIC(led_semc);                        /* ����һ���������ź��� */


/** 
 * \brief ��ʱ���жϺ���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void my_timer_isr (void *p_arg)
{               
    static unsigned int count = 0;
    count++;
    
    if(count >= 10) {
        count = 0;
        /* ÿ��1s���������ź��� */
        AW_SEMC_GIVE(led_semc);    /* �����ź�����1 */    
        AW_SEMC_GIVE(led_semc);    /* �����ź�����1 */              
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
                
        AW_SEMC_TAKE(led_semc,AW_SEM_WAIT_FOREVER);
        
        /* �յ��������ź����󣬷�תLED��*/
        aw_led_toggle(LED0); 
        aw_mdelay(200);
        aw_led_toggle(LED0); 
        aw_mdelay(200);
               
    }
}

/** 
 * \brief �����ź����������ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return    ��
 */
void demo_os_semc_entry (void *p_arg)
{

    AW_TASK_DECL_STATIC(task,256);  
    
    AW_TASK_INIT(task,               /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL �����  */            
                "task",              /* ��������                   */ 
                         6,          /* �������ȼ�                 */ 
                       256,          /* �����ջ��С               */ 
                 task_entry,         /* ������ں���               */ 
                  (void*)1);         /* ������ڲ���               */ 
    
    
    AW_SEMC_INIT(led_semc,
                         0,          /* ��ʼ��Ϊ��״̬                                   */
                 AW_SEM_Q_FIFO);     /* ��ʼ��ʱ��ѡ�����ã�AW_SEM_Q_FIFO���Ⱥ�˳���Ŷӣ�*/
                                     /*               AW_SEM_Q_PRIORITY (�����ȼ��Ŷ�)   */
    AW_TASK_STARTUP(task);      
  
}

/** [src_os_semc] */

/* end of file */
