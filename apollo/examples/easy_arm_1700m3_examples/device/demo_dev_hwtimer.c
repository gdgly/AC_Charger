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
 * e-mail:      appollo.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief 硬件定时器例程
 *
 * - 操作步骤：
 *   1. PIO0_0引脚连接PC串口的TXD；
 *   2. PIO0_1引脚连接PC串口的RXD；
 *
 * - 实验现象：
 *   1. LED以1s的周期持续闪烁。
 *   2. 如果定时器分配失败，串口输出失败信息。
 *
 * \par 源代码
 * \snippet demo_dev_hwtimer.c src_dev_hwtimer
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_hwtimer
 * \copydoc demo_dev_hwtimer.c
 */

/** [src_dev_hwtimer] */
#include "apollo.h"
#include "main.h"

#include "aw_delay.h"  
#include "aw_led.h"
#include "aw_hwtimer.h"   
#include "aw_vdebug.h"

#define RIT_UNIT_ID 7

/**
 * \brief 硬件定时器中断服务函数。
 * \param[in] p_arg : 任务参数
 * \return 无
 */
static void mytimer_isr (void *p_arg)
{
    aw_led_toggle(LED0);  
}

/**
 * \brief 硬件定时器任务入口
 * \param[in] p_arg : 任务参数
 * \return 无
 */
static void task_entry (void *p_arg)
{
    static aw_hwtimer_handle_t  mytmr;  /* 定时器句柄 */

    mytmr = aw_hwtimer_alloc(100000,                     /* 申请输入频率100kHz */
							 1,                          /* 最小频率1Hz  */
							 80000,                      /* 最大频率80kHz   */
							 AW_HWTIMER_CAN_INTERRUPT |  /* 能产生中断   */
							 AW_HWTIMER_AUTO_RELOAD,     /* 自动重装   */
							 &mytimer_isr,               /* 中断服务函数         */
							 (void *) NULL);             /* 中断服务函数入口函数 */
    if (AW_HWTIMER_NULL != mytmr) {

		aw_hwtimer_enable (mytmr, 1);  /* 使能定时中断 1Hz     */
		aw_mdelay(20000);              /* 等待20s     */
		aw_hwtimer_disable (mytmr);    /* 关闭定时器     */

		aw_hwtimer_release(mytmr);     /* 定时器不再使用，释放该定时器 */
    } else {
        aw_kprintf("Timer allocation fail!\n");
    }
}

/**
 * \brief 建立硬件定时器任务
 * \return 无
 */
void demo_dev_hwtimer_entry (void)
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

/** [src_dev_hwtimer] */
 
/* end of file */
