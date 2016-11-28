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
 * \brief Apollo中延迟作业的使用例程
 *
 * - 操作步骤：
 *   1. 调用demo_os_delayedwork_entry()函数
 *
 * - 实验现象：
 *   1.使用延迟工作，使任务延迟500ms再运行。可以看到LED，以1Hz的频率闪烁。
 *   2.10s时间后（闪烁10次后），关闭定时器，LED不再闪烁 
 *
 * \par 源代码
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
 * 使用延迟作业功能必须包含此头文件
 */
#include "aw_delayed_work.h"

static struct aw_delayed_work work;                 /* 定义延迟工作结构体变量 */

/** 
 * \brief 延迟工作的任务函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数
 *
 * \return 无
 */
static void my_work (void *p_arg)
{ 
    struct aw_delayed_work  *p_work = (struct aw_delayed_work  *) p_arg;   
    
    aw_led_toggle(LED0);
    
    aw_delayed_work_start(p_work, 500);     /* 再次延迟工作函数，变成周期性任务 */
}

/** 
 * \brief 任务的入口函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数
 *
 * \return 无
 */
static void task_entry(void *p_arg)
{
    aw_delayed_work_init(&work, my_work, &work);    /* 初始化work         */
                                          
    /* 启动延迟工作任务，500ms后运行延迟工作函数    */
    aw_delayed_work_start(&work, 500);              /* 延迟500ms后运行任务 */
    
    /* 延时 10S.    */
    aw_task_delay(aw_ms_to_ticks(10 * 1000));
    
    /* 停止延迟工作 */
    aw_delayed_work_stop(&work); 
    
    AW_FOREVER {
         
        /*do some other things */
        
        aw_mdelay(10);
    }        
}


/** 
 * \brief 延迟作业入口函数
 */
void demo_os_delayedwork_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名           */
                   8,                /* 任务优先级       */
                  512,               /* 任务栈大小       */
                  task_entry,        /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task0);          /* 启动任务         */
}

/** [src_os_delayedwork] */

/* end of file */
