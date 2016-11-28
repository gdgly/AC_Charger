/*******************************************************************************
 *                                 apollo
 *                       ---------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.embedcontrol.com/
 * e-mail:      apollo.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief LED例程
 *
 * - 实验现象：
 *   1. LED以0.5s的周期持续闪烁。
 *
 * \par 源代码
 * \snippet demo_dev_led.c src_dev_led
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_led
 * \copydoc demo_dev_led.c
 */

/** [src_dev_led] */
#include "apollo.h"
#include "main.h"

#include "aw_delay.h"
#include "aw_led.h"

/**
 * \brief LED任务入口    
 *\param[in] p_arg : 任务参数
 * \return 无
 */
static void task_entry (void *p_arg)
{
    while (1) {
        aw_led_on(LED0);            /* 点亮LED2灯   */
        aw_mdelay(500);             /* 延时0.5s     */
        aw_led_off(LED0);
        aw_mdelay(500); 
        
        aw_led_set(LED0, TRUE);     /* 点亮LED3灯   */
        aw_mdelay(500);
        aw_led_set(LED0, FALSE);    /* 熄灭LED灯    */
        aw_mdelay(500);

        aw_led_toggle(LED0);        /* LED状态翻转  */
        aw_mdelay(500);
        aw_led_toggle(LED0);        /* LED状态翻转  */
        aw_mdelay(500);
    } 
}

/**
 * \brief 建立LED任务
 * \return 无
 */
void demo_dev_led_entry (void)
{
    AW_TASK_DECL_STATIC(task, 256);
    
    AW_TASK_INIT(task,               /* 任务实体:AW_TASK_DECL_STATIC 或者 AW_TASK_DECL 定义 */
                "task",              /* 任务名字                                            */ 
                 6,                  /* 任务优先级                                          */ 
                 256,                /* 任务堆栈大小                                        */ 
                 task_entry,         /* 任务入口函数                                        */ 
                (void*)0);           /* 任务入口参数                                        */ 
    
    AW_TASK_STARTUP(task);
}

/** [src_dev_led] */
 
/* end of file */
