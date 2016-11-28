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
 * \brief Apollo中计数信号量的使用例程
 *
 * - 操作步骤：
 *   1. 调用demo_os_sembc_entry()函数
 *
 * - 实验现象：
 *   1.每隔1s，LED0闪烁两次
 *
 * - 说明：
 *   计数信号量与二进制信号量的区别，计数信号量可以计数，1,2,3... 
 *   二进制信号量只能实现1和0，比如连续GIVE两次，二进制信号量只能
 *   TAKE1次，但计数信号量可以TAKE两次
 *
 * \par 源代码
 * \snippet demo_os_semc.c src_os_semc 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_semc
 * \copydoc demo_os_semc.c
 */

/** [src_os_semc] */  

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_sem.h"
#include "main.h"
#include "aw_hwtimer.h"


AW_SEMC_DECL_STATIC(led_semc);                        /* 定义一个二进制信号量 */


/** 
 * \brief 定时器中断函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数
 *
 * \return 无
 */
static void my_timer_isr (void *p_arg)
{               
    static unsigned int count = 0;
    count++;
    
    if(count >= 10) {
        count = 0;
        /* 每隔1s发送两次信号量 */
        AW_SEMC_GIVE(led_semc);    /* 计数信号量加1 */    
        AW_SEMC_GIVE(led_semc);    /* 计数信号量加1 */              
    }
    
 
}

/** 
 * \brief 任务入口函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数
 *
 * \return 无
 */
static void task_entry(void *p_arg)
{   

    static aw_hwtimer_handle_t mytmr1;
       
    /*  
     * 申请得到一个定时器
     */
    mytmr1 = aw_hwtimer_alloc( 1000000,               /* 期望的定时器输入频率 */
                                 10,                  /* 定时器中断的最小频率 */
                                100000,               /* 定时器中断的最大频率 */
                             AW_HWTIMER_AUTO_RELOAD,  /* 定时器能够自动重装载 */
                              my_timer_isr,           /* 定时器中断回调函数   */
                                (void *)0);           /* 传递给回调函数的参数 */
                              
                                                       
                                      
    if (mytmr1 == AW_HWTIMER_NULL) {
         /*  表明定时器分配失败 */
         
    } else {
           
        aw_hwtimer_enable(mytmr1,10);     /* 使能硬件定时器，中断频率5Hz */
    } 
    
    AW_FOREVER {
                
        AW_SEMC_TAKE(led_semc,AW_SEM_WAIT_FOREVER);
        
        /* 收到二进制信号量后，翻转LED灯*/
        aw_led_toggle(LED0); 
        aw_mdelay(200);
        aw_led_toggle(LED0); 
        aw_mdelay(200);
               
    }
}

/** 
 * \brief 计数信号量处理的入口函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数 
 *
 * \return    无
 */
void demo_os_semc_entry (void *p_arg)
{

    AW_TASK_DECL_STATIC(task,256);  
    
    AW_TASK_INIT(task,               /* 任务实体:AW_TASK_DECL_STATIC 或者 AW_TASK_DECL 定义的  */            
                "task",              /* 任务名字                   */ 
                         6,          /* 任务优先级                 */ 
                       256,          /* 任务堆栈大小               */ 
                 task_entry,         /* 任务入口函数               */ 
                  (void*)1);         /* 任务入口参数               */ 
    
    
    AW_SEMC_INIT(led_semc,
                         0,          /* 初始化为空状态                                   */
                 AW_SEM_Q_FIFO);     /* 初始化时，选项设置：AW_SEM_Q_FIFO（先后顺序排队）*/
                                     /*               AW_SEM_Q_PRIORITY (按优先级排队)   */
    AW_TASK_STARTUP(task);      
  
}

/** [src_os_semc] */

/* end of file */
