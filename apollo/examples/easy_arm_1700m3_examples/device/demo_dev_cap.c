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
 * \brief 在输入捕获(CAP)演示例程，适用平台EasyARM-1700M3
 *
 * - 操作步骤:
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_TIMER0_CAP
 *   2. USART0接口和PC串口连接起来；
 *   3. 将P1.26(定时器0输入捕获管脚)与P2.2（LED0）连接。
 *
 * - 实验现象:
 *   1. 串口打印输入捕获时间。
 *
 * \par 源代码
 * \snippet demo_dev_cap.c src_dev_cap
 *
 * \internal
 * \par History
 * - 1.00 15-10-13  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_cap
 * \copydoc demo_dev_cap.c
 */

/** [src_dev_cap] */
#include "apollo.h"                     /* 此头文件必须被首先包含 */

/* 本程序用到了以下服务 */
#include "aw_delay.h"                   /* 延时服务              */
#include "aw_cap.h"                     /* 输入捕获服务              */
#include "aw_led.h"                     /* LED 服务              */
#include "aw_gpio.h"
#include "aw_vdebug.h"
#include "aw_sem.h"

#define CAP_CHANNEL  0   /* 输入捕获通道号 */

/* 捕获led的脉冲  */
static void __my_callback(void *arg, unsigned int count)
{
    static unsigned int num = 0;
    static unsigned int count1;
    unsigned int period_ns;

    if (num == 0) {
        count1 = count;        /* 第一次捕获得到的值 */
        num = 1;
    } else {
        /* 得到两次上升沿之间的时间，即波形的周期 */
        aw_cap_count_to_time(0, count1, count, &period_ns);
        aw_kprintf("测得波形的周期为:%d ns\n",period_ns);
    }
    count1 = count;            /*  保存值 */
}

/* 该任务利用LED0翻转，产生一个脉冲来被捕获  */
static void led_task_entry(void)
{
	for (;;) {
		aw_led_toggle(0);
		aw_mdelay(40);
	}

}

/**
 * \brief 输入捕获任务
 **/
void cap_task (void)
{
	/* 输入捕获配置，双边沿触发 */
	aw_cap_config(CAP_CHANNEL, AW_CAP_TRIGGER_BOTH_EDGES, &__my_callback, 0);
    aw_cap_enable(CAP_CHANNEL);  /* 使能输入捕获 */

    while (1) {
    	aw_mdelay(5);
    }

}


/**
 * \brief 建立CAP任务
 * \return 无
 */
void demo_dev_cap_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0, 512);
    AW_TASK_DECL_STATIC(led_toggle_task, 512);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名          */
                   2,                /* 任务优先级      */
                  512,               /* 任务栈大小       */
                  cap_task,          /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */

    AW_TASK_STARTUP(task0);          /* 启动任务        */

    /* 初始化任务led_task */
     AW_TASK_INIT(led_toggle_task,         /* 任务实体 */
                  "led_task",              /* 任务名字 */
                  5,                       /* 任务优先级 */
                  512,                     /* 任务堆栈大小 */
                  led_task_entry,          /* 任务入口函数 */
                  (void *)0);              /* 任务入口参数 */

     AW_TASK_STARTUP(led_toggle_task);          /* 启动任务        */
}
/** [src_dev_cap] */

/* end of file */
