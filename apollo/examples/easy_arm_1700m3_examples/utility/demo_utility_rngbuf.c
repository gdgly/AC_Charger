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
 * \brief 环形缓冲区例程
 *
 * - 实验现象：
 *   1. 打印环形缓冲区的信息：已填充的字节数、剩余的字节数
 *   2. 打印环形缓冲区的数据
 * 
 * \par 源代码
 * \snippet demo_utility_rngbuf.c src_utility_rngbuf 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-08-13  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_utility_rngbuf
 * \copydoc demo_utility_rngbuf.c
 */
 
/** [src_utility_rngbuf] */
#include "apollo.h"
#include "aw_vdebug.h"
#include "aw_rngbuf.h"
#include "aw_delay.h"
#include "aw_types.h"
#include "string.h"


///**
// * \brief 函数声明
// */
//void rngbuf_task_entry(void *p_arg);



/**
 * \brief 环形缓冲区的的基础服务函数
 */
static void rngbuf_task_entry (void *p_arg)
{
    char data;
    char *str1 = " you are using aworks platform";
    char strtemp[64];
    
    AW_RNGBUF_DEFINE(char_buf, char, 64);                                 /* 64个char空间的环形缓冲区char data;     */
    aw_rngbuf_putchar(&char_buf, 'd');                                    /* 存放1个字符到缓冲区                    */
    aw_rngbuf_getchar(&char_buf, &data);                                  /* 从缓冲区读取1个字                      */
    aw_kprintf("list_task_entry1 \n");        
    aw_kprintf("取出的字符= %c \n" ,data);        
    
    aw_rngbuf_flush (&char_buf);                                          /*  清空缓冲区                            */
    aw_rngbuf_put (&char_buf, str1, strlen(str1));
    aw_kprintf("缓冲区已填充的字节数= %d \n" ,aw_rngbuf_nbytes (&char_buf));        
    aw_kprintf("缓冲区剩下的字节数= %d \n" , aw_rngbuf_freebytes(&char_buf));    
    
    aw_rngbuf_get (&char_buf, strtemp, strlen(str1));
    aw_kprintf("缓冲区已填充的字节数= %d \n" ,aw_rngbuf_nbytes (&char_buf));        
    aw_kprintf("缓冲区剩下的字节数= %d \n" , aw_rngbuf_freebytes(&char_buf));    
     aw_kprintf("取出的字符串= %s \n" ,strtemp);
    

    aw_rngbuf_flush (&char_buf);
    memset(strtemp,0,64);
    if(aw_rngbuf_isempty(&char_buf)){                                       /* 判断缓冲区是否为空                    */
            aw_rngbuf_putchar(&char_buf, 'a');                              /* 写入数据'a'                          */
            aw_rngbuf_put_ahead(&char_buf, 'b', 0);                         /* 写入数据'b'，但这个'b'读不到          */
            aw_rngbuf_put_ahead(&char_buf, 'c', 1);                         /* 写入数据'c'，这个'c'也读不到          */
            aw_rngbuf_move_ahead(&char_buf, 2);                             /* 往前移动数据指针2个字节               */
            aw_rngbuf_get(&char_buf, strtemp, 3);                           /* 此时可以把"abc"都读出来               */
    }
    aw_kprintf("取出的字符串= %s \n" ,strtemp);        


      aw_mdelay(100);        
}

/** 
 * \brief 建立ringbuf任务
 */
void demo_utility_rngbuf_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名           */
                   8,                /* 任务优先级       */
                  512,               /* 任务栈大小       */
                  rngbuf_task_entry, /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task0);          /* 启动任务         */
}

/** [src_utility_rngbuf] */

/* end of file */
