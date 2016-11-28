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
 * \brief Apollo中软件定时器的使用例程
 *
 * - 操作步骤：
 *   1. 调用demo_os_softtime_entry()函数
 *   
 * - 实验现象：
 *   1.可以看到LED，以1Hz的频率闪烁。
 *
 * \par 源代码
 * \snippet demo_os_softtimer.c src_os_softtimer
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_softtimer
 * \copydoc demo_os_softtimer.c
 */

/** [src_os_softtimer] */ 

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
 
#include "aw_led.h"
#include "main.h"
 

/*
 * 使用软件定时器功能必须包含此头文件
 */
#include "aw_timer.h"


/** 
 * \brief 定时器回调函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数
 *
 * \return 无
 */
void my_callback (void *p_arg)
{ 
    aw_timer_t  *p_timer = p_arg;   
    
    aw_led_toggle(LED0);
    
    aw_timer_start(p_timer, aw_ms_to_ticks(500));     /* 再次定时500ms */
}

/** 
 * \brief 软件定时演示入口函数
 */
void demo_os_softtimer_entry (void)
{
    static aw_timer_t  timer;
    
    /* 初始化定时器          */
    aw_timer_init(&timer, 
                  my_callback,                         /* 定时器回调函数                           */
                  &timer);                             /* 将定时器作为参数传递给回调函数           */
                                                       /* 以便在回调函数中再次启动，完成周期性时间 */
    /* 启动定时器，定时500ms */
    aw_timer_start(&timer, aw_ms_to_ticks(500));       /* 软件定时器是以系统tick为单位的           */
       
}

/** [src_os_softtimer] */ 

/* end of file */
