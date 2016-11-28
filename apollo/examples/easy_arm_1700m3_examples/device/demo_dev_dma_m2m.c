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
 * \brief DMA内存到内存的数据传输例程
 *
 * - 操作步骤：
     1. aw_prj_params.h中使能AW_DEV_LPC17XX_DMA
 *   2. PIO0_2引脚连接PC串口的TXD；
 *   3. PIO0_3引脚连接PC串口的RXD；
 *
 * - 实验现象：
 *   1. DMA传输成功，LED常亮；
 *   2. DMA传输失败，LED闪烁。
 *
 * \par 源代码
 * \snippet demo_dev_dma_m2m.c src_dev_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_dma_m2m
 * \copydoc demo_dev_dma_m2m.c
 */

/** [src_dev_dma_m2m] */
#include "apollo.h"
#include "main.h"

#include "aw_task.h" 
#include "aw_delay.h"
#include "aw_led.h"
#include "aw_vdebug.h"
#include "aw_lpc17xx_dma.h"

/**
 * \brief DMA任务入口
 *\param[in] p_arg : 任务参数
 * \return 无
 */
static void task_entry (void *p_arg)
{
    /* DMA通道描述符 */
    aw_lpc17xx_dma_desc_t g_desc;

    /* 数据缓冲区 */
    uint8_t src_buf[256];
    uint8_t dst_buf[256];

    uint32_t flags;
    int      i;


    aw_lpc17xx_dma_chan_setup(AW_DMA_CHAN_0,	             /* DMA通道号                    */
    	                      AW_DMA_CONN_NONE,              /* 无传输源外设                    */
    		    		      AW_DMA_CONN_NONE,              /* 无传输目标外设                    */
#if 1  /* 若为LPC177x_8x，此处不用配置 */
    		    		      AW_DMA_CCONFIG_SREQ_NONE    |  /* 传输源为存储器，可忽略       */
                        	  AW_DMA_CCONFIG_DREQ_NONE	  |  /* 传输目标为存储器，可忽略     */
#endif
                        	  AW_DMA_CCONFIG_TRANTYPE_M2M |  /* 存储器到存储器               */
                        	  AW_DMA_CCONFIG_IE_VALID 	  |  /* 允许触发中断错误             */
                        	  AW_DMA_CCONFIG_ITC_VALID    |  /* 允许触发终端计数中断         */
                        	  AW_DMA_CCONFIG_TRANS_UNLOCK ); /* 不锁定传输                   */

    for (i = 0; i < 256; i++) {
        src_buf[i] = i;
        dst_buf[i] = 0;
    }

	/* DMA传输配置 */
	flags = AW_DMA_CCONTROL_SBSIZE_32     |   /* 源突发传输数据量 SIZE = 32      */
			AW_DMA_CCONTROL_DBSIZE_32     |   /* 目标突发传输数据量 SIZE = 32    */
			AW_DMA_CCONTROL_SWIDTH_32BIT  |   /* 源传输数据宽度 32Bits           */
			AW_DMA_CCONTROL_DWIDTH_32BIT  |   /* 目标传输数据宽度 32Bits    		*/
			AW_DMA_CCONTROL_SI_ENABLE     |   /* 指定源地址自动增加           	*/
			AW_DMA_CCONTROL_DI_ENABLE     |   /* 指定目标地址自动增加         	*/
			AW_DMA_CCONTROL_ITC_ENABLE;	      /* 使能终端计数中断                */

	aw_lpc17xx_dma_desc_build(&g_desc,              /* 通道描述符                      */
							  (uint32_t)src_buf,    /* 源端数据地址                    */
							  (uint32_t)dst_buf,    /* 目标端数据地址                  */
							  256,                  /* 传输的字节数                    */
							  flags);               /* 传输配置参数                    */

    /* DMA 同步传输 */
    aw_lpc17xx_dma_tran_sync(AW_DMA_CHAN_0, &g_desc);

    /* 停止通道传输  */
    aw_lpc17xx_dma_tran_stop(AW_DMA_CHAN_0);

    for (i = 0; i < 256; i++) {
        if (src_buf[i] != dst_buf[i]) {
            while (1) {
                aw_led_toggle(0);
                aw_mdelay(100);
            }
        }
    }

    aw_led_on(0);
    
    while (1) {
        aw_mdelay(1);
   }
}

/**
 * \brief 建立DMA任务
 * \return 无
 */
void demo_dev_dma_m2m_entry (void)
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

/** [src_dev_dma_m2m] */
 
/* end of file */
