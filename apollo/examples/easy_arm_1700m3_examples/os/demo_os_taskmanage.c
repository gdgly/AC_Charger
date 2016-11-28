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
 * \brief Apollo������������ط������񴴽���ɾ��������
 *
 * - �������裺
 *   1. ����demo_os_taskmanage_entry()����
 *   
 * - ʵ������
 *   1��LED0��100ms��ʱ��������
 *   2��ÿ��500ms ������ ����500ms 
 *
 * \par Դ����
 * \snippet demo_os_taskmanage.c src_os_taskmanage 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_taskmanage 
 * \copydoc demo_os_taskmanage.c
 */

/** [src_os_taskmanage ] */  

/* ʹ�ý��ķ���ֻ��Ҫ���� "aw_task.h"ͷ�ļ� */
#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_buzzer.h"
#include "main.h"


/* 
 * ȫ�ֵķ�ʽ����һ�����񣬿��Բ���Ҫʹ��STATIC
 * ���ǣ�����ô���������񲻹��ⲿ������C�ļ���ʹ�ã�Ϊ�˱���ģ�������������ͻ���Լ�����
 * ����ģ������������������ʹ��AW_TASK_DECL_STATIC����������������������ڱ�C�ļ���
 *
 * ע���������ģ����Ҫʹ�ã�����벻��STATIC��ʹ��AW_TASK_DECL������������Ҫʹ�õ�
 *     �ط���ʹ�� AW_TASK_IMPORT() ���������ʵ�塣�磺AW_TASK_IMPORT(task2)
 *     ���������ʾ���ֶ��巽����ʵ���У�����ʹ��AW_TASK_DECL_STATIC��������
 */
AW_TASK_DECL(task2,256);


/** 
 * \brief ����2��ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return ��
 */
static void task2_entry(void *p_arg)
{     
    aw_task_id_t task2_id = aw_task_id_self();                    /* ��ȡ��ǰ�����ID  */
       
    /* ����ͨ������ʽ����һ����ѭ��������ѭ�� */
    AW_FOREVER {
        aw_buzzer_loud_set(80);
        aw_buzzer_beep(500);
        
        aw_mdelay(500);
    }
}

/** 
 * \brief ����1��ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return ��
 */
static void task1_entry(void *p_arg)
{
    aw_task_id_t task2_id;                         /* ���弴������������2��ID������ID������񴴽�*/
    
    /* 
     * �����������д�������һ������������ʾ����������2
     */   
    task2_id = AW_TASK_INIT(        task2,        /* ����ʵ��         */ 
                              "task2name",        /* ������           */
                                       4 ,        /* �������ȼ�       */ 
                                      256,        /* �����ջ��С     */
                               task2_entry,       /* ������ڲ���     */
                                (void*)2);        /* ���ݸ�����Ĳ��� */
 
    aw_task_startup (task2_id);                   /* ����ʹ������ID����һ������       */
                                                  /* ��AW_TASK_STARTUP(task2)Ч����ͬ */
    
    /* 
     * ��������ʱ�������һ��������ã���������2���ȼ�������1���ȼ��ߣ����ȼ���ֵԽС�����ȼ�Խ�ߣ�
     * ��ˣ������󣬻�����ȥִ������2����������2����ʱ����ʱ���Ż��ͷ�CPU���ص�����2����ִ��
     *
     */
    
    /* ����ͨ������ʽ����һ����ѭ��������ѭ�� */
    AW_FOREVER {
        
        aw_led_on(LED0);
        aw_task_delay(aw_sys_clkrate_get() * 100 / 1000); /* ������ʱ 100ms����aw_mdelay(100)��ͬ */
        aw_led_off(LED0);      
        aw_task_delay(aw_sys_clkrate_get() * 100 / 1000); /* ������ʱ 100ms����aw_mdelay(100)��ͬ */    
    }
}

/** 
 * \brief ��������������ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
void demo_os_taskmanage_entry (void *p_arg)
{
    /*
     * ���õĴ�������ķ�ʽ�����ú괴����
     * ʹ�ú��������������������1����������ʵ��  AW_TASK_DECL_STATIC  ���� AW_TASK_DECL
     *                         2����ʼ������    AW_TASK_INIT
     *                         3����������      AW_TASK_STARTUP
     */
    
    /* ��������ʵ�壬�����ڣ����������ڣ����䣬����ʹ��STATIC */
    AW_TASK_DECL_STATIC(task1,           /* ������������������У���ʹ�ø������� */
                         256);   
    AW_TASK_INIT(task1,         // ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL �����              
                "task1name",    // ��������                
                         5,     // �������ȼ�                 
                       256,     // �����ջ��С                 
                 task1_entry,   // ������ں���                 
                  (void*)1);    // ������ڲ���
    
    AW_TASK_STARTUP(task1);     //����task1,���ڵ�ǰ�����ȼ���ߣ��������к���task1_entry 
}

/** [src_os_taskmanage ] */ 

/* end of file */
