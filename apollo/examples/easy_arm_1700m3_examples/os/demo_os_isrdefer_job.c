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
 * \brief Apollo���ж��ӳٴ����ʹ������
 *
 * - �������裺
 *   1. ����demo_os_isr_deferjob_entry()����
 *
 * - ʵ������
 *   1.ÿ��1s�Ӵ�ӡ��һ����Ϣ
 *
 * - ˵����
 *   �ж��ӳٴ����ж��°벿�֣���
 *   �ж��ǽ�������ͨ����Ҫ�ܿ��ִ����ɡ�
 *
 *   ʹ���ж��ӳٴ����ǽ��жϵĴ󲿷ֹ����������������У�ʹ���ж��ܹ�����
 *   ������ϡ�ͬʱ���ж��ӳٴ��������ͬ�������ȼ���ߵ�����ʹ�ñ������ж�
 *   ����ɵ����飬����ŵ�������Ҳ�ܹ����ٵ���ɡ�
 *   
 *   ʾ������ʹ���ж��ӳٴ�������ʱ���ж�����(��ӡһ����Ϣ����ʱ�ϳ�)
 *           ���ж��ӳٴ������еõ�����
 *
 * \par Դ����
 * \snippet demo_os_isr_deferjob.c src_os_isrdefer_job 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_isrdefer_job
 * \copydoc demo_os_isrdefer_job.c
 */

/** [src_os_isrdefer_job] */  

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
 
#include "aw_led.h"
#include "main.h"
 

/*
 * ʹ���ж��ӳٴ����ܱ��������ͷ�ļ�
 */
#include "aw_isr_defer.h"

/*
 * ʹ�õ���Ӳ����ʱ��������Ӳ����ʱ��ʹ��ϸ�ڲμ��豸�����µ�Ӳ����ʱ��demo
 */
#include "aw_hwtimer.h" 

struct aw_isr_defer_job g_myjob;                     /* �ж��ӳٴ�������       */
 

/** 
 * \brief �ж��ӳٴ�������
 *
 * \param[in] p_aram : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void defer_job (void *p_aram)
{    
    aw_led_toggle(LED0);                             /* �Ƶ���˸            */
}

/** 
 * \brief ��ʱ���жϺ���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return ��
 */
void my_timer_isr (void *p_arg)
{ 

    /* 
     * �жϵľ����������ж��ӳٷ����д��� 
     */  
     aw_isr_defer_job_add(&g_myjob);                /*  ����ж��ӳٴ���   */
    
}

/**
 * \brief �ж��ӳٴ�����ں���
 */
void demo_os_isrdefer_job_entry (void)
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
        
        /* ��ʼ���ж��ӳٴ������� */    
        aw_isr_defer_job_init(&g_myjob, defer_job, (void *)0);
        
        aw_hwtimer_enable(mytmr1,10);     /* ʹ��Ӳ����ʱ�����ж�Ƶ��5Hz */
    } 
}

/** [src_os_isrdefer_job] */ 

/* end of file */
