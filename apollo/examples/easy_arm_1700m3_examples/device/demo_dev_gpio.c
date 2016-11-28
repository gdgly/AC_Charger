/*******************************************************************************
 *                                 Apollo
 *                       ---------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.embedcontrol.com/
 * e-mail:      apollo.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief GPIO例程
 *
 * - 实验现象：
 *   1. LED以0.5s的周期闪烁5次；
 *   2. LED以0.1s的周期持续闪烁。
 *
 * \par 源代码
 * \snippet demo_dev_gpio.c src_dev_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_gpio
 * \copydoc demo_dev_gpio.c
 */

/** [src_dev_gpio] */
#include "apollo.h"
#include "main.h"

#include "aw_task.h" 
#include "aw_delay.h"
#include "aw_gpio.h"

#define LED_PIN  PIO2_2
/**
 * \brief GPIO任务入口    
 *\param[in] p_arg : 任务参数
 * \return 无
 */
static void task_entry (void *p_arg)
{
    int i = 0;
    
    /* GPIO 引脚配置 */  
    aw_gpio_pin_cfg(LED_PIN, AW_GPIO_OUTPUT | AW_GPIO_PULL_UP);

    /* LED以0.5s的周期闪烁5次 */
    for (i = 0; i < 5; i++) {
        aw_gpio_set(LED_PIN, 0);
        aw_mdelay(500);
        
        aw_gpio_set(LED_PIN, 1);
        aw_mdelay(500);
    }
    
    /* LED以0.1s的周期持续闪烁 */
    while (1) {
        aw_gpio_toggle(LED_PIN);
        aw_mdelay(100);
    }
}

/**
 * \brief 建立GPIO任务
 * \return 无
 */
void demo_dev_gpio_entry (void)
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

/** [src_dev_gpio] */
 
/* end of file */
