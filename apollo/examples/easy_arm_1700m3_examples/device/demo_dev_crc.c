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
 * \brief CRC演示例程
 *
 * - 操作步骤:
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_CRC
 *   2. USART0接口和PC串口连接起来；
 *
 * - 实验现象：
 *   1. 串口打印CRC校验结果。
 * 
 * - 备注：
 *   若MCU为LPC175X_6X则使用软件CRC；
 *   若MCU为LPC177X_8X则使用硬件CRC。
 *
 * \par 源代码
 * \snippet demo_dev_crc.c src_dev_crc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-16  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_crc
 * \copydoc demo_dev_crc.c
 */

/** [src_dev_crc] */
#include "apollo.h"
#include "main.h"
#include "aw_led.h"
#include "aw_delay.h"
#include "aw_crc.h"
#include "aw_vdebug.h"

/**
 * \brief LED任务入口
 *\param[in] p_arg : 任务参数
 * \return 无
 */
static void task_entry (void *p_arg)
{
    uint8_t  ret;
    uint8_t  ndata[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    uint32_t crc;

    /* 定义了一个模型，该模型就是常用的CRC-16模型，如WinRAR中就是使用的该模型 */
    AW_CRC_DECL(crc16,         /* crc模型 crc16 */
                16,            /* crc宽度 16 */
                0x8005,        /* 生成多项式 */
                0x0000,        /* 初始值 */
                TRUE,          /* refin */
                TRUE,          /* refout */
                0x0000);       /* xorout */


     ret =  AW_CRC_INIT(crc16,               /* crc模型，由AW_CRC_DECL()定义的 */
                        crctable16_1021_ref, /* crc表，系统的，不需要计算 */
                        AW_CRC_FLAG_AUTO);   /* 自动模式，自动选择硬件或软件实现 */
    if (ret != AW_OK) {
        /* 初始化失败 */
    	aw_kprintf("计算 error\n");
    } else {
        AW_CRC_CAL(crc16,                /* crc模型，由AW_CRC_DECL()定义的 */
                   ndata,                /* 待进行CRC计算的数据 */
                   sizeof(ndata));       /* 此次计算的数据 */

        /* 中间可以继续计算 */
        /* ... */


        /* 最后可以提取出最终结果    计算结果应为：0xbb3d  */
        crc = AW_CRC_FINAL(crc16);  /* crc模型，由AW_CRC_DECL()定义的 */

        aw_kprintf("计算结果为:%x\n",crc);

        /* 如果后续还需计算，则需要重新调用AW_CRC_INIT()初始化后再计算 */
    }

    while (1) {
    	aw_mdelay(5);
    }
}

/**
 * \brief 建立CRC任务
 * \return 无
 */
void demo_dev_crc_entry (void)
{
    AW_TASK_DECL_STATIC(task, 256);

    AW_TASK_INIT(task,               /* 任务实体:AW_TASK_DECL_STATIC 或者 AW_TASK_DECL 定义 */
                "task",              /* 任务名字                                            */
                 6,                  /* 任务优先级                                          */
                 256,                /* 任务堆栈大小                                        */
                 task_entry,         /* 任务入口函数                                        */
                (void*)0);           /* 任务入口参数                                        */

    AW_TASK_STARTUP(task);
}

/** [src_dev_crc] */

/* end of file */
