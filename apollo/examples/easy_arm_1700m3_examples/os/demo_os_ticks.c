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
 * \brief 利用操作系统节拍服务测量程序耗时的例程
 *
 * - 操作步骤：
 *   1. 调用demo_os_ticks_entry()函数
 *   
 * - 实验现象：
 *   1. 打印程序耗时等相关信息。
 
 * - 说明：
 *   测量程序耗时是在操作系统的节拍下测量的，因此时间精度只能为ms级。
 *
 * \par 源代码
 * \snippet demo_os_ticks.c src_os_ticks 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_ticks 
 * \copydoc demo_os_ticks.c
 */

/** [src_os_ticks ] */  

/* 使用节拍服务只需要包含 "apollo.h"头文件 */
#include "apollo.h"
#include "aw_delay.h"
#include "aw_digitron_disp.h"
#include "aw_vdebug.h"
 

/** 
 * \brief 程序耗时测量的入口函数
 *
 * \param[in] p_arg : 注册时用户传入的自定义参数 
 *
 * \return 无
 */
void demo_os_ticks_entry (void *p_arg)
{
    unsigned int tick;
    unsigned int mtime;
    unsigned int clkrate;
 
    /*
     * 系统的节拍是操作系统的"心脏".
     * 系统的节拍与时间的关系，可由系统节拍的频率得到。系统的节拍频率在：
     * aw_prj_param.h文件中的系统配置中设置。默认设置为：
     *        #define AW_CFG_TICKS_PER_SECOND          1000
     * 如设置为1000,即系统节拍频率为1000Hz，一个节拍就为 1 ms.
     * 系统提供了接口函数获取节拍频率。
     */
    
    clkrate = aw_sys_clkrate_get();            /* 获取系统的节拍频率         */
      

    tick = aw_sys_tick_get();                  /* 获取当前系统的节拍         */
    
    aw_mdelay(500);                            /* 可以放入需要测量时间的代码 */
   
    tick = aw_sys_tick_get() - tick;           /* 当前节拍减去上次的节拍     */
    
    mtime = aw_ticks_to_ms(tick);              /* 将节拍转换为时间           */   
    
    aw_kprintf("系统节拍频率：%4d,测得程序耗时：%4d",clkrate,mtime);     
}

/** [src_os_ticks ] */  

/* end of file */
