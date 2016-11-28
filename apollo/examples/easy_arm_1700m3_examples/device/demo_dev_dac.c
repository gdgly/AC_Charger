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
 * \brief DAC演示例程
 *
 * - 操作步骤：
     1. aw_prj_params.h中使能AW_DEV_LPC17XX_DAC
 *   2. PIO0_2引脚连接PC串口的TXD；
 *   3. PIO0_3引脚连接PC串口的RXD；
 *
 * - 实验现象：
 *   1. 串口打印DAC精度及位数。
 *   2. 使用万用表测量P0.26管脚，可观察到每隔2s电压在1.2V和1.8V之间变化，
 *   3. 电压变化，LED0翻转。
 *
 * \par 源代码
 * \snippet demo_dev_dac.c src_dev_dac
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-15  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_dac
 * \copydoc demo_dev_dac.c
 */

/** [src_dev_dac] */
#include "apollo.h"
#include "main.h"

#include "aw_task.h"
#include "aw_delay.h"
#include "aw_led.h"
#include "aw_vdebug.h"
#include "aw_dac.h"

/**
 * \brief DAC任务入口
 *\param[in] p_arg : 任务参数
 * \return 无
 */
static void task_entry (void *p_arg)
{
    int dac_bits = aw_dac_bits_get(0);       /* 读取DAC通道0的转换位数 */
    int dac_vref = aw_dac_vref_get(0);       /* 读取DAC通道0的参考电压(单位：mV) */

    aw_dac_val_t dac_val1, dac_val2;

    aw_kprintf("The bits is %d  \r\n", dac_bits);
    aw_kprintf("The vref is %d  \r\n", dac_vref);

    dac_val1 = 1200 * (1 << dac_bits) / dac_vref;
    dac_val2 = 1800 * (1 << dac_bits) / dac_vref;


    aw_dac_val_set(0, dac_val1);      /* 设置DAC通道0的输出电压为 1.2V (未使能，还未实际输出)*/
    aw_dac_enable(0);                 /* 使能输出，输出电压为1.2V*/

    while (1) {
    	aw_dac_val_set(0, dac_val1);      /*设置DAC通道0的输出电压为 1.2V (前面已使能，实际输出电压1.4V)*/
    	aw_led_toggle(LED0);              /* LED0翻转 */
    	aw_mdelay(1000);
        aw_dac_val_set(0, dac_val2);      /*设置DAC通道0的输出电压为 1.4V (前面已使能，实际输出电压1.4V)*/
        aw_led_toggle(LED0);              /* LED0翻转 */
        aw_mdelay(1000);

    }
}

/**
 * \brief 建立DAC任务
 * \return 无
 */
void demo_dev_dac_entry (void)
{
    AW_TASK_DECL_STATIC(task, 1024);

    AW_TASK_INIT(task,               /* 任务实体:AW_TASK_DECL_STATIC 或者 AW_TASK_DECL 定义 */
                "task",              /* 任务名字                                            */
                 6,                  /* 任务优先级                                          */
                 1024,               /* 任务堆栈大小                                        */
                 task_entry,         /* 任务入口函数                                        */
                (void*)0);           /* 任务入口参数                                        */

    AW_TASK_STARTUP(task);
}

/** [src_dev_dac] */

/* end of file */
