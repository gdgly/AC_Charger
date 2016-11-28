/*******************************************************************************
 *                                 Apollo
 *                       ---------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.embedcontrol.com/
 * e-mail:      anywhere.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief GPIO引脚触发例程
 *
 * - 操作步骤：
 *   1. 连接基础扩展板KEY1 <---> PIO2_6
 *
 * - 实验现象：
 *   1. 按下按键KEY1，LED状态翻转。
 *
 * \par 源代码
 * \snippet demo_dev_gpio_trigger.c src_dev_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_gpio_trigger
 * \copydoc demo_dev_gpio_trigger.c
 */

/** [src_dev_gpio_trigger] */
#include "apollo.h"
#include "main.h"

#include "aw_task.h" 
#include "aw_delay.h"
#include "aw_gpio.h"  
#include "aw_led.h"

#define KEY1_PIN  PIO2_6

/**
 * \brief GPIO引脚触发中断服务函数
 *\param[in] p_arg : 任务参数
 * \return 无
 */
static void gpio_trig_isr (void *p_arg)
{
    int led = (int)p_arg;
    
    aw_led_toggle(led);
}


/**
 * \brief GPIO引脚触发任务入口   
 *\param[in] p_arg : 任务参数
 * \return 无
 */
static void task_entry (void *p_arg)
{
    /* 连接中断服务函数到引脚，必须先调用该函数，才能调用 aw_gpio_trigger_cfg() */
    aw_gpio_trigger_connect(KEY1_PIN, gpio_trig_isr, (void *)LED0);
    
    /* GPIO 引脚配置 */
    aw_gpio_trigger_cfg(KEY1_PIN, AW_GPIO_TRIGGER_FALL);
    
    /* 使能引脚触发 */
    aw_gpio_trigger_on(KEY1_PIN);
    
    while (1) {
        aw_mdelay(10);
    }
}

/**
 * \brief 建立GPIO任务
 * \return 无
 */
void demo_dev_gpio_trigger_entry (void)
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

/** [src_dev_gpio_trigger] */
 
/* end of file */

