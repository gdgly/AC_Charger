/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 工具宏例程
 *
 * - 实验现象：
 *   1. 打印出可视化调试信息、普通调试信息以及警告信息
 *   
 * 
 * \par 源代码
 * \snippet demo_utility_others.c src_utility_others
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-08-13  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_utility_others
 * \copydoc demo_utility_others.c
 */
 
/** [src_utility_others] */
#define AW_VDEBUG_DEBUG
#include "aw_vdebug.h" 

#include "apollo.h"
#include "aw_delay.h"
#include "aw_types.h"
#include "string.h"
#include "aw_errno.h"
#include "aw_common.h" 


/**
 * \brief 工具宏测试函数
 * 函数描述：利用工具宏，实现错误编码以及可视化调试。
 */

static void utility_others_task_entry (void *p_arg)
{
    struct my_struct{
        int  m1;   
        char m2;
    };
    
    struct my_struct  my_st = {10,'w'};
    char             *p_m2  = &my_st.m2;
    int offset_m2           = AW_OFFSET( struct my_struct, m2); /*  结构体元素偏移量                */
    struct my_struct *p_st  = AW_CONTAINER_OF(p_m2, struct my_struct, m2);  /*  由元素地址得到结构体地址        */
    int a[3];
    
    aw_kprintf((const char *)p_st);
    aw_kprintf("偏移字节数= %d \n" , offset_m2);
    aw_kprintf("结构体成员= %d,%c \n" , p_st->m1,p_st->m2);
    aw_kprintf("结构体成员大小= %d,%d \n" ,AW_MEMBER_SIZE(struct my_struct, m1),AW_MEMBER_SIZE(struct my_struct, m2) );
    aw_kprintf("数组元素个数= %d \n" , AW_NELEMENTS(a));
    
    aw_kprintf("向上舍入= %d \n",AW_ROUND_UP(15, 4));
    aw_kprintf("向下舍入= %d \n",AW_ROUND_DOWN(15, 4));
    aw_kprintf("倍数向上舍入= %d \n",AW_DIV_ROUND_UP(15, 8));
        
    if(AW_ALIGNED(0x789d, 4)){
        aw_kprintf("四字节对齐\n");
    } else {
        aw_kprintf("四字节没有对齐，错误等级为 %d \n",EFAULT);
    }
        
    aw_kprintf("将字节组成字符串为 %s\n ",AW_XSTR(a)AW_XSTR(p)AW_XSTR(o)AW_XSTR(l)AW_XSTR(l)AW_XSTR(o));
        
   /*
    * 可视化调试
    */        
    AW_LOGF(("调试信息打印中\n "));
    AW_INFOF(("This is a normal information\n"));                   /* 打印普通信息，没使能，不会输出 */
    AW_DBGF(("Value of register is %x\n"));                         /* 打印调试信息                   */
    AW_WARNF(("Warning: invalid argument: %d\n"));                  /* 打印警告信息                   */

    aw_mdelay(100);        
}

/** 
 * \brief 延迟作业入口函数
 */
void demo_utility_others_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名           */
                   8,                /* 任务优先级       */
                  512,               /* 任务栈大小       */
                  utility_others_task_entry, /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task0);          /* 启动任务         */
}

/** [src_utility_others] */

/* end of file */
