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
 * \brief RTC演示例程
 *
 * - 操作步骤：
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_RTC
 *
 * - 实验现象：
 *   1. 设定好初始时间，通过串口可以观察 时间和日期相关信息，1秒更新2次数据。
 *
 * \par 源代码
 * \snippet demo_dev_rtc.c src_dev_rtc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_rtc
 * \copydoc demo_dev_rtc.c
 */

/** [src_dev_rtc] */
#include "apollo.h"
#include "main.h"

#include "aw_delay.h"
#include "aw_led.h"

#include "aw_rtc.h"
#include "aw_vdebug.h"
#include <time.h>
 

/**
*\param[in] void *p_arg(这里没有用到)
*\note 
*/
void rtc_task (void *p_arg)
{

    aw_err_t stat = AW_OK;
    
   /* 定义起始时间 */
    aw_tm_t tm = {
      0,
      41,   
      17,
      7,                    /* day of the month      */
      11 - 1,               /* months since January  */
      2014 - 1900,          /* years since 1900      */
};            
    
    aw_rtc_time_set(0,&tm);                 /* 设置起始时间 */
    
    while (1) {
        
        stat = aw_rtc_time_get (0, &tm);    /* 得到细分时间 */
  
        if (stat != AW_OK) {
            aw_kprintf("rtc 操作失败 %d \r\n",stat);
        } else {
            aw_kprintf("%s\n", asctime((const struct tm *)&tm));   /* 打印细分时间 */
        }                          
        aw_mdelay(500);                                            /* 时间信息 1秒打印两次*/
    }
}

/**
 * \brief 建立RTC任务
 * \return 无
 */
void demo_dev_rtc_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名          */
                   2,                /* 任务优先级      */
                  512,               /* 任务栈大小       */
                  rtc_task,          /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task0);          /* 启动任务        */
}
/** [src_dev_rtc] */

/* end of file */
