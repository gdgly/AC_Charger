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
 * \brief 串口演示例程，包含中断模式和轮询模式
 *
 * - 操作步骤：
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_UART0
 *   2. PIO0_2引脚连接PC串口的TXD；
 *   3. PIO0_3引脚连接PC串口的RXD。
 *
 * - 实验现象：
 *   1. 首先进入UART0 查询模式 上位机输入10个字符 接收发送到的数据 (10次)；
 *   2. 接着进入中断模式      上位机输入10个字符 接收发送到的数据 (10次)。 
 *
 * \par 源代码
 * \snippet demo_dev_serial.c src_dev_serial
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_serial
 * \copydoc demo_dev_serial.c
 */

/** [src_dev_serial] */
#include "apollo.h"

#include "aw_delay.h"
#include "aw_serial.h"                  /* 串行设备服务 */
#include "aw_gpio.h"


/**
*\brief serial_task program entry 
*\details [1].先进行初始化配置工作(串口参数配置)
*         [2].配置查询模式 发送字符串 上位机输入10个字符 接收发送到的数据 (10次)
*         [3].配置中断模式 发送字符串 上位机输入10个字符 接收发送到的数据 (10次)
*     
*\param[in] void *p_arg 
*\note    上位机发送字符时，不要选择【发送新行】选项
*/
void serial_task (void)
{

    static char buf[32];
    int len=0; 
    int i = 0; 
    /* 串口初始化配置 波特率115200 */
    aw_serial_ioctl(COM0, SIO_BAUD_SET, (void *)115200);

    /* 串口参数 ：8个数据位 1个停止位，无奇偶校验 */
    aw_serial_ioctl(COM0, SIO_HW_OPTS_SET, (void *)(CS8 | CLOCAL));
    
    /* 串口模式 ：查询模式 发送字符串 */
    aw_serial_ioctl(COM0, SIO_MODE_SET, (void *)SIO_MODE_POLL);
    aw_serial_poll_write(COM0, "Hello,Enter Serial Poll Mode:\r\n", 32);
    
    for(i = 0; i < 10; i++) {
        len = aw_serial_poll_read(COM0, buf, 10);
            if (len > 0) {
                aw_serial_poll_write(COM0, buf, len);            
            }
        aw_serial_poll_write(COM0, "\r\n", len);
    }
    
    /* 再次配置串口模式 ：中断模式 */
    aw_serial_ioctl(COM0, SIO_MODE_SET, (void *)SIO_MODE_INT);
    aw_serial_write(COM0, "Hello,Enter Serial INT  Mode:\r\n", 32);
    for(i = 0; i < 10; i++) {
        len = aw_serial_read(COM0, buf, 10);
            if (len > 0) {
                aw_serial_write(COM0, buf, len);            
            }
        aw_serial_write(COM0, "\r\n", len);
    }
    
}


/**
 * \brief 建立SERIAL任务
 * \return 无
 */
void demo_dev_serial_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名          */
                   2,                /* 任务优先级      */
                  512,               /* 任务栈大小       */
                  serial_task,       /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task0);          /* 启动任务        */
}
/** [src_dev_serial] */

/* end of file */
