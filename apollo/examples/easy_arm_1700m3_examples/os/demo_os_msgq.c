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
 * \brief Apollo中消息队列的使用例程
 *
 * - 操作步骤：
 *   1. 调用demo_os_msgq_entry()函数
 *
 * - 实验现象：
 *   1.定时器回调函数，每隔3s钟发送一个亮灯时间，第一次亮灯500ms
 *                                               第二次亮灯1000ms
 *                                               第三次亮灯2000ms
 *
 * \par 源代码
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


/* 定义一个消息队列(LED闪烁时间间隔) */                                    
AW_MSGQ_DECL_STATIC(led_msgq,32,sizeof(uint32_t)); 


/** 
 * \brief 定时器中断服务函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数 
 *
 * \return 无
 */
static void my_timer_isr (void *p_arg)
{ 
    static unsigned int time_ms = 0;
    static unsigned int lighton_ms = 0;
    time_ms += 100;
    
    if (time_ms >= 3000) {
       
        time_ms = 0;
        
        /* 每3秒钟发送一次亮灯时间第一次亮500ms.. 第二次1000ms... 第三次亮2000 */
        if (lighton_ms == 0 || lighton_ms >= 2000) {
            lighton_ms = 500;
        } else if(lighton_ms == 500){
            lighton_ms = 1000;
        } else if(lighton_ms == 1000){
             lighton_ms = 2000;
        }
        
          
        /* 定时器中断函数，发送当前的时间值作为消息 */        
        AW_MSGQ_SEND(led_msgq,                   /* 消息队列         */
                      &lighton_ms,               /* 发送消息         */     
            sizeof(unsigned int),                /* 写入数据大小，如果比定义时的一条消息大，超出部分不写入 */
                 AW_MSGQ_WAIT_FOREVER,           /* 永久等待消息被发送（消息队列满时） */
                 AW_MSGQ_PRI_NORMAL);         
        
    }   
}

/** 
 * \brief 任务入口函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数
 *
 * \return 无
 */
static void task_entry(void *p_arg)
{   
    uint32_t lighton_ms;
 
    static aw_hwtimer_handle_t mytmr1;
       
    /*  
     * 申请得到一个定时器
     */
    mytmr1 = aw_hwtimer_alloc( 1000000,               /* 期望的定时器输入频率 */
                                 10,                  /* 定时器中断的最小频率 */
                                100000,               /* 定时器中断的最大频率 */
                             AW_HWTIMER_AUTO_RELOAD,  /* 定时器能够自动重装载 */
                              my_timer_isr,           /* 定时器中断回调函数   */
                                (void *)0);           /* 传递给回调函数的参数 */
                              
                                                       
                                      
    if (mytmr1 == AW_HWTIMER_NULL) {
         /*  表明定时器分配失败 */
         
    } else {
           
        aw_hwtimer_enable(mytmr1,10);              /* 使能硬件定时器，中断频率5Hz */
    } 
   
    AW_FOREVER {
                
        AW_MSGQ_RECEIVE(led_msgq,                   /* 消息队列         */
                        &lighton_ms,                /* 接收缓冲区       */     
                   sizeof(uint32_t),                /* 读取消息大小，始终按定义时的消息大小读取（即此参数暂未使用）    */
                         AW_MSGQ_WAIT_FOREVER);     /* 永久等待一个消息 */
        
        aw_led_on(LED0);
        
        aw_mdelay(lighton_ms);  
        
        aw_led_off(LED0);                 
    }
}

/** 
 * \brief 消息队列处理的入口函数
 */
void demo_os_msgq_entry (void)
{
    AW_TASK_DECL_STATIC(task,256); 

    AW_TASK_INIT(task,                 /* 任务实体:AW_TASK_DECL_STATIC 或者 AW_TASK_DECL 定义的 */             
                 "task",               /* 任务名字             */              
                     5,                /* 任务优先级           */              
                   256,                /* 任务堆栈大小         */            
                  task_entry,          /* 任务入口函数         */                
                  (void*)2);           /* 任务入口参数         */
    
    AW_MSGQ_INIT(led_msgq,
                       32,             /* 消息的条数    (参数暂未使用)       */
                 sizeof(uint32_t),     /* 每条消息的大小 (参数暂未使用)      */
                 AW_MSGQ_Q_PRIORITY);  /* 初始化时，选项设置：AW_SEM_Q_FIFO（先后顺序排队）  */
                                       /*   AW_SEM_Q_PRIORITY (按优先级排队) (参数暂未使用) */
    AW_TASK_STARTUP(task);
    
}

/** [src_os_msgq] */ 

/* end of file */
