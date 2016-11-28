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
 * \brief CAN通讯演示例程
 *
 * - 操作步骤：
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_CAN1及AW_DEV_LPC17XX_CAN2
 *
 * - 实验现象：
 *   1. CAN接收到上位机数据后，重发给上位机。
 *
 * \par 源代码
 * \snippet demo_dev_can.c src_dev_can
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-13  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_can
 * \copydoc demo_dev_can.c
 */

/** [src_dev_can] */
#include "apollo.h"
#include "main.h"
#include "aw_delay.h"
#include "aw_led.h"
#include "aw_can.h"
#include "aw_vdebug.h"

/* CAN总线错误回调函数  */
static void can_err_status_cb (uint8_t chn, aw_can_bus_err_t error_status)
{

	if (error_status & AW_CAN_BUS_ERR_BIT) {

		aw_kprintf(("AW_CAN_BUS_ERR_BIT\n"));        /**< \brief 位错误 */
	}

	if (error_status &AW_CAN_BUS_ERR_ACK) {
		aw_kprintf(("AW_CAN_BUS_ERR_ACK\n"));        /**< \brief 应答错误 */
	}

	if (error_status &AW_CAN_BUS_ERR_CRC) {
		aw_kprintf(("AW_CAN_BUS_ERR_CRC\n"));        /**< \brief CRC错误 */
	}

	if (error_status &AW_CAN_BUS_ERR_FORM) {
		aw_kprintf(("AW_CAN_BUS_ERR_FORM\n"));       /**< \brief 格式错误 */
	}

	if (error_status &AW_CAN_BUS_ERR_STUFF) {
		aw_kprintf(("AW_CAN_BUS_ERR_STUFF\n"));      /**< \brief 填充错误 */
	}

	if (error_status &AW_CAN_BUS_ERR_UNKNOWN) {
		aw_kprintf(("AW_CAN_BUS_ERR_UNKNOWN\n"));    /**< \brief 未知错误 */
	}

	if (error_status &AW_CAN_BUFF_ERR_RCVFULL) {
		aw_kprintf(("AW_CAN_BUFF_ERR_RCVFULL\n"));   /**< \brief 接收缓冲区满 */
	}

	if (error_status &AW_CAN_BUFF_ERR_TXDFULL ) {
		aw_kprintf(("AW_CAN_BUFF_ERR_TXDFULL\n"));   /**< \brief 发送缓冲区满 */
	}
}

/* 总线状态回调函数 */
static void can_bus_status_cb (uint8_t chn, aw_can_bus_status_t bus_status)
{
	switch (bus_status) {

	case AW_CAN_BUS_STATE_OK:
		aw_kprintf(("AW_CAN_BUS_STATE_OK\n"));
		break;

	case AW_CAN_BUS_STATE_WARN:
		aw_kprintf(("AW_CAN_BUS_STATE_WARN\n"));
		break;

	case AW_CAN_BUS_STATE_OFF:
		aw_kprintf(("AW_CAN_BUS_STATE_OFF\n"));
		break;

	default:
		break;
	}

}

/* CAN通讯任务 */
void can_task (void *p_arg)
{
	struct aw_can_bps_param  can_baud_rate = {2, 0, 1, 9}; /* LPC17XX 4分频 500kbps */

	/* 设置回调函数 */
	struct aw_can_App_CBfun  can_app_callback_fun = {can_err_status_cb,
			                                         can_bus_status_cb,
			                                         NULL,
			                                         NULL};

	struct aw_can_msg		 can_msg[10] = {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};

	uint32_t framecnt  = 0;
	uint32_t donecnt   = 0;
	uint32_t ulresault = 0;

	/* CAN初始化 */
	aw_can_init (0, AW_WORK_MODE_NROMAL, &can_baud_rate, &can_app_callback_fun);

	AW_INFOF(("CAN start up!\n"));

	/* 主任务永久循环 */
	AW_FOREVER {

		/* 接收一帧数据 */
		framecnt = aw_can_frames_rcv (0, can_msg, 10, 0);
		if (framecnt) {

			/* 发送已接受数据*/
			ulresault = aw_can_frames_send (0, can_msg, framecnt, &donecnt, 3000);
			if (ulresault == AW_CAN_SEND_FRAME_TIME_OUT) {
				AW_INFOF(("CAN send frame timeout!\n"));
			}
		} else {
			aw_mdelay(2);
		}
	}

}

/**
 * \brief 建立CAN任务
 * \return 无
 */
void demo_dev_can_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0, 1024);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名          */
                   2,                /* 任务优先级      */
                  1024,              /* 任务栈大小       */
                  can_task,          /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */

    AW_TASK_STARTUP(task0);          /* 启动任务        */
}
/** [src_dev_can] */

/* end of file */
