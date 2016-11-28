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
 * \brief 看门狗（WDT）演示例程，适用平台EasyARM-1700M3
 *
 * - 操作步骤:
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_WDT
 *   2. USART0接口和PC串口连接起来；
 *
 * - 实验现象:
 *   1. 4位数码管显示数字"1024".
 *   2. 程序启动，串口打印"Add WDT device!"
 *   3. 每喂狗一次，打印"Feed"
 *   4. 若喂狗超时，程序复位，重新打印出"Add WDT device!".
 *
 * \par 源代码
 * \snippet demo_dev_wdt.c src_dev_wdt
 *
 * \internal
 * \par History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_wdt
 * \copydoc demo_dev_wdt.c
 */

/** [src_dev_wdt] */
#include "apollo.h"                     /* 此头文件必须被首先包含 */

/* 本程序用到了以下服务 */
#include "aw_delay.h"                   /* 延时服务              */
#include "aw_wdt.h"                     /* WDT 服务              */
#include "aw_led.h"                     /* LED 服务              */
#include "aw_gpio.h"
#include "aw_vdebug.h"
#include "aw_sem.h"

#define WDT_TIMEOUT_MS     1200   /* 看门狗时间  */
#define FEED_TIME_MS       1000   /* 喂狗时间  */

/**
 * \brief 测试demo
 **/
void wdt_task (void)
{
	struct awbl_wdt wdt_dev;

	aw_wdt_add(&wdt_dev, WDT_TIMEOUT_MS);   /* 设置看门狗时间 */

	aw_kprintf("Add WDT device!\r\n");
	aw_kprintf("WDT timeout is %d ms!\r\n", WDT_TIMEOUT_MS);

    /* LED0 间隔闪烁 */
    while (1) {
		aw_wdt_feed(&wdt_dev);    /* 喂狗   */
		aw_mdelay(FEED_TIME_MS);
		aw_kprintf("Feed!\r\n");
    }

}


/**
 * \brief 建立WDT任务
 * \return 无
 */
void demo_dev_wdt_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0, 512);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名          */
                   2,                /* 任务优先级      */
                  512,               /* 任务栈大小       */
                  wdt_task,          /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */

    AW_TASK_STARTUP(task0);          /* 启动任务        */
}
/** [src_dev_wdt] */

/* end of file */
