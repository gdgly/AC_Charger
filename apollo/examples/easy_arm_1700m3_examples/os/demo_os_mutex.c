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
 * \brief Apollo�л�������ʹ������
 *
 * - �������裺
 *   1. ����demo_os_mutex_entry()����
 *
 * - ʵ������
 *   1.�����ʹ�û����ź���������ע�͵� USE_MUTEX �ĺ궨�塣���ƻ���������ȫ�ֱ���
 *     ���ʳ�����Ԥ�����������������2�������ǽ���������29�����ּ���29�����ʼ��
 *     ����ֵ����29��ͬ��
 *
 * - ˵����
 *   �ź�������ȡ���ͷ���ͬһ�������У�������Զ�λ�ȡ����Ҳ�����Ӧ����ͷš�
 *              ��������һ�������л�ȡ������һ���������ͷš�
 *              �����ź�����Ҫ�����豸������Ļ�����ʡ�����ǰ���룬���ʺ��ͷ���Դ��
 *              һ�������гɶԳ��ֻ�ȡ��LOCK�����ͷ�(UNLOCK)��
 *
 *   ����1������2��������ȫ�ֱ���g_data��
 *   Ϊ��ȷ�����ʵ���ȷ�ԣ��ͱ���ʹ�û����ź���������б�������֤ȫ�ֱ����ķ����ǻ���ġ�
 *   ������1ʹ��ʱ������2�Ͳ���ʹ�ã�����2ʹ��ʱ������1����ʹ��ȷ���˱������ʵ���ȷ�ԡ�
 *   
 * \par Դ����
 * \snippet demo_os_mutex.c src_os_mutex 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_mutex
 * \copydoc demo_os_mutex.c
 */

/** [src_os_mutex] */

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_sem.h"
#include "main.h"
#include "aw_input.h"


/* ʹ�û����ź�������ȫ�ֱ����ķ��� */
#define USE_MUTEX


unsigned int g_data = 0;
AW_MUTEX_DECL_STATIC(data_mutex);                        /* ȫ�ֱ��������ź��� */


/** 
 * \brief ����2��ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void task2_entry(void *p_arg)
{   
    unsigned int temp;
    volatile unsigned int i,j;
    
    /* ����ͨ������ʽ����һ����ѭ��������ѭ�� */
    AW_FOREVER {

#ifdef USE_MUTEX        
        AW_MUTEX_LOCK(data_mutex,AW_SEM_WAIT_FOREVER);           /* ���õȴ� */       
#endif
        /* do something for g_data. eg. increase value */
        temp = g_data; 
         aw_kprintf("before:gdata = %d\r\n",g_data);   
        /* if there do something use a lot of time. some wrong likely happen if not use mutex */
        for (i = 0; i < 10000; i++) {
            for (j = 0; j < 502; j++) {
                ;
            }           
        }
        
        g_data += 29;
        
        /* �����ʹ�� MUTEX ���Է��֣���ӡ������������Ԥ�ڲ���,ʹ�ú�����ȫ����ϵ� */
        aw_kprintf("after add 29: gdata = %d\r\n",g_data);    
        
        if ((temp + 29) != g_data) {
            //aw_kprintf("δʹ�û��⣬���ʳ���\r\n");
            aw_led_on(LED0);                                     /* LED0��  */
        }
            
#ifdef USE_MUTEX              
        AW_MUTEX_UNLOCK(data_mutex);
#endif
        aw_mdelay(2);       
    }
}

/** 
 * \brief ����1��ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return    ��
 */
static void task1_entry(void *p_arg)
{
    unsigned int temp;
    
    AW_FOREVER {
#ifdef USE_MUTEX          
        AW_MUTEX_LOCK(data_mutex,AW_SEM_WAIT_FOREVER);           /* ���õȴ� */  
#endif        
         /* do something for g_data. eg. decrease value */
        temp = g_data; 
        g_data -= 11;
        
        if ((temp - 11) != g_data) {
            aw_led_on(LED0);                                     /* LED0��  */
        }
#ifdef USE_MUTEX  
        AW_MUTEX_UNLOCK(data_mutex);
#endif        
        aw_mdelay(1);
 
    }
}

/** 
 * \brief �������������ں�����
 */
void demo_os_mutex_entry (void)
{

    AW_TASK_DECL_STATIC(task1,512);   
    AW_TASK_DECL_STATIC(task2,512); 
    
    AW_TASK_INIT(task1,         /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL ����� */
                "task1name",    /* ��������     */
                         5,     /* �������ȼ�   */
                       512,     /* �����ջ��С */
                 task1_entry,   /* ������ں��� */
                  (void*)1);    /* ������ڲ��� */
    
    AW_TASK_INIT(task2,         /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL ����� */
                 "task2name",   /* ��������     */
                     6,         /* �������ȼ�   */
                   512,         /* �����ջ��С */
                  task2_entry,  /* ������ں��� */
                  (void*)2);    /* ������ڲ��� */
    
    AW_MUTEX_INIT(data_mutex,AW_SEM_Q_FIFO);  /* ��ʼ��ʱ��ѡ�����ã�AW_SEM_Q_FIFO���Ⱥ�˳���Ŷӣ�*/
                                              /*               AW_SEM_Q_PRIORITY (�����ȼ��Ŷ�) */
    AW_TASK_STARTUP(task1);      
    AW_TASK_STARTUP(task2);
    
}

/** [src_os_mutex] */

/* end of file */
