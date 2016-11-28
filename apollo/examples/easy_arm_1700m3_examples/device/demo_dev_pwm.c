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
 * e-mail:      apollo.support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief PWM演示例程
 * - LED管脚：|  宏         |   ID   |   管脚         |    颜色   |
 *            -----------------------------------------
 *            | LED0  |   0    |  PIO0_16 |    红色   |
 *
 * - PWM接口：| 管脚       | 通道号    |
 *            ------------------
 *            |PIO2_0 |  PWM0  |
 *            ------------------
 *            |PIO2_1 |  PWM1  |
 *            ------------------
 *            |PIO2_2 |  PWM3  |
 * - 操作步骤：
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_MCPWM及AW_DEV_LPC17XX_PWM
 *   2. 将PWM引脚连接到逻辑分析仪或示波器等测量工具上，检测波形。
 *
 * - 实验现象：     
 *   1. PWM0、PWM1、PWM2三路同时工作（PWM0 10%;PWM2 20%;PWM3 50%）；
 *   2. 延时1s PWM1停止工作；
 *   3. LED 间隔200ms 闪烁。
 *
 * \par 源代码
 * \snippet demo_dev_pwm.c src_dev_pwm
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_dev_pwm
 * \copydoc demo_dev_pwm.c
 */

/** [src_dev_pwm] */
#include "apollo.h"
#include "main.h"

#include "aw_delay.h"
#include "aw_gpio.h"
#include "aw_pwm.h"
#include "aw_buzzer.h"
#include "aw_input.h"


#define PWM0        0
#define PWM1        1
#define PWM2        2

#define PERIOD      1000000

/**
 * \brief pwm_task program entry 
 * \details 首先配置所选PWM通道的有效时间和周期，在使用时，所有通道同时只能配置成
 *          同一周期，然后使能对应的通道。 频率1KHz
 *          [1].配置3路PWM参数，参数1--PWM通道号 参数2--PWM占空比 参数3--PWM周期
 *          [2].使能PWM
 *          
 *\note 输出PWM
 */
void pwm_task (void *p_arg)
{

    aw_pwm_config(PWM0, PERIOD / 10, PERIOD);   /* 配置PWM0的有效时间（高电平时间）10% ,周期 */
    aw_pwm_config(PWM1, PERIOD / 5, PERIOD);    /* 配置PWM1的有效时间（高电平时间）20% ,周期 */ 
    aw_pwm_config(PWM2, PERIOD / 2, PERIOD);    /* 配置PWM1的有效时间（高电平时间）20% ,周期 */
    aw_pwm_enable(PWM0);     /* 使能通道0 */
    aw_pwm_enable(PWM1);     /* 使能通道1 */
    aw_pwm_enable(PWM2);     /* 使能通道2 */
    aw_mdelay(1000);
    aw_pwm_disable(PWM1);    /* 禁能通道1 */


}

/**
 * \brief 建立PWM任务
 * \return 无
 */
void demo_dev_pwm_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名          */
                   2,                /* 任务优先级      */
                  512,               /* 任务栈大小       */
                  pwm_task,          /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task0);          /* 启动任务        */
}

/** [src_dev_pwm] */

/* end of file */
