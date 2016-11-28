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
 * \brief Apollo中中断延迟处理的使用例程
 *
 * - 操作步骤：
 *   1. 调用demo_os_isr_deferjob_entry()函数
 *
 * - 实验现象：
 *   1.每隔1s钟打印出一条消息
 *
 * - 说明：
 *   中断延迟处理（中断下半部分）：
 *   中断是紧急任务，通常需要很快的执行完成。
 *
 *   使用中断延迟处理，是将中断的大部分工作放在任务下运行，使得中断能够快速
 *   运行完毕。同时，中断延迟处理的任务同样是优先级最高的任务，使得本来在中断
 *   下完成的事情，就算放到任务里也能够快速的完成。
 *   
 *   示例程序：使用中断延迟处理，将定时器中断任务(打印一条消息，耗时较长)
 *           在中断延迟处理工作中得到处理。
 *
 * \par 源代码
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
 * 使用中断延迟处理功能必须包含此头文件
 */
#include "aw_isr_defer.h"

/*
 * 使用到了硬件定时器，具体硬件定时器使用细节参见设备服务下的硬件定时器demo
 */
#include "aw_hwtimer.h" 

struct aw_isr_defer_job g_myjob;                     /* 中断延迟处理任务       */
 

/** 
 * \brief 中断延迟处理任务
 *
 * \param[in] p_aram : 注册时用户传入的自定义参数
 *
 * \return 无
 */
static void defer_job (void *p_aram)
{    
    aw_led_toggle(LED0);                             /* 黄灯闪烁            */
}

/** 
 * \brief 定时器中断函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数 
 *
 * \return 无
 */
void my_timer_isr (void *p_arg)
{ 

    /* 
     * 中断的具体任务在中断延迟服务中处理 
     */  
     aw_isr_defer_job_add(&g_myjob);                /*  添加中断延迟处理   */
    
}

/**
 * \brief 中断延迟处理入口函数
 */
void demo_os_isrdefer_job_entry (void)
{
   
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
        
        /* 初始化中断延迟处理任务 */    
        aw_isr_defer_job_init(&g_myjob, defer_job, (void *)0);
        
        aw_hwtimer_enable(mytmr1,10);     /* 使能硬件定时器，中断频率5Hz */
    } 
}

/** [src_os_isrdefer_job] */ 

/* end of file */
