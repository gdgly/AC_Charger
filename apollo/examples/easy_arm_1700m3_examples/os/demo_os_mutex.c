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
 * \brief Apollo中互斥量的使用例程
 *
 * - 操作步骤：
 *   1. 调用demo_os_mutex_entry()函数
 *
 * - 实验现象：
 *   1.如果不使用互斥信号量保护，注释掉 USE_MUTEX 的宏定义。则红灯会亮，表明全局变量
 *     访问出错（与预期情况不符），任务2，本来是将变量加上29，发现加上29后与初始读
 *     到的值加上29不同。
 *
 * - 说明：
 *   信号量：获取和释放在同一个任务中，任务可以多次获取，但也必须对应多次释放。
 *              不可以在一个任务中获取，另外一个任务中释放。
 *              互斥信号量主要用于设备、区域的互斥访问。访问前申请，访问后释放资源。
 *              一个任务中成对出现获取（LOCK）和释放(UNLOCK)。
 *
 *   任务1和任务2都访问了全局变量g_data。
 *   为了确保访问的正确性，就必须使用互斥信号量对其进行保护，保证全局变量的访问是互斥的。
 *   即任务1使用时，任务2就不能使用；任务2使用时，任务1不能使用确保了变量访问的正确性。
 *   
 * \par 源代码
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


/* 使用互斥信号量保护全局变量的访问 */
#define USE_MUTEX


unsigned int g_data = 0;
AW_MUTEX_DECL_STATIC(data_mutex);                        /* 全局变量互斥信号量 */


/** 
 * \brief 任务2入口函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数
 *
 * \return 无
 */
static void task2_entry(void *p_arg)
{   
    unsigned int temp;
    volatile unsigned int i,j;
    
    /* 任务通常的形式：有一个主循环，永久循环 */
    AW_FOREVER {

#ifdef USE_MUTEX        
        AW_MUTEX_LOCK(data_mutex,AW_SEM_WAIT_FOREVER);           /* 永久等待 */       
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
        
        /* 如果不使用 MUTEX 可以发现，打印出来的数据与预期不符,使用后是完全相符合的 */
        aw_kprintf("after add 29: gdata = %d\r\n",g_data);    
        
        if ((temp + 29) != g_data) {
            //aw_kprintf("未使用互斥，访问出错\r\n");
            aw_led_on(LED0);                                     /* LED0亮  */
        }
            
#ifdef USE_MUTEX              
        AW_MUTEX_UNLOCK(data_mutex);
#endif
        aw_mdelay(2);       
    }
}

/** 
 * \brief 任务1入口函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数 
 *
 * \return    无
 */
static void task1_entry(void *p_arg)
{
    unsigned int temp;
    
    AW_FOREVER {
#ifdef USE_MUTEX          
        AW_MUTEX_LOCK(data_mutex,AW_SEM_WAIT_FOREVER);           /* 永久等待 */  
#endif        
         /* do something for g_data. eg. decrease value */
        temp = g_data; 
        g_data -= 11;
        
        if ((temp - 11) != g_data) {
            aw_led_on(LED0);                                     /* LED0亮  */
        }
#ifdef USE_MUTEX  
        AW_MUTEX_UNLOCK(data_mutex);
#endif        
        aw_mdelay(1);
 
    }
}

/** 
 * \brief 互斥量处理的入口函数。
 */
void demo_os_mutex_entry (void)
{

    AW_TASK_DECL_STATIC(task1,512);   
    AW_TASK_DECL_STATIC(task2,512); 
    
    AW_TASK_INIT(task1,         /* 任务实体:AW_TASK_DECL_STATIC 或者 AW_TASK_DECL 定义的 */
                "task1name",    /* 任务名字     */
                         5,     /* 任务优先级   */
                       512,     /* 任务堆栈大小 */
                 task1_entry,   /* 任务入口函数 */
                  (void*)1);    /* 任务入口参数 */
    
    AW_TASK_INIT(task2,         /* 任务实体:AW_TASK_DECL_STATIC 或者 AW_TASK_DECL 定义的 */
                 "task2name",   /* 任务名字     */
                     6,         /* 任务优先级   */
                   512,         /* 任务堆栈大小 */
                  task2_entry,  /* 任务入口函数 */
                  (void*)2);    /* 任务入口参数 */
    
    AW_MUTEX_INIT(data_mutex,AW_SEM_Q_FIFO);  /* 初始化时，选项设置：AW_SEM_Q_FIFO（先后顺序排队）*/
                                              /*               AW_SEM_Q_PRIORITY (按优先级排队) */
    AW_TASK_STARTUP(task1);      
    AW_TASK_STARTUP(task2);
    
}

/** [src_os_mutex] */

/* end of file */
