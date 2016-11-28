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
 * \brief CANͨѶ��ʾ����
 *
 * - �������裺
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_CAN1��AW_DEV_LPC17XX_CAN2
 *
 * - ʵ������
 *   1. CAN���յ���λ�����ݺ��ط�����λ����
 *
 * \par Դ����
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

/* CAN���ߴ���ص�����  */
static void can_err_status_cb (uint8_t chn, aw_can_bus_err_t error_status)
{

	if (error_status & AW_CAN_BUS_ERR_BIT) {

		aw_kprintf(("AW_CAN_BUS_ERR_BIT\n"));        /**< \brief λ���� */
	}

	if (error_status &AW_CAN_BUS_ERR_ACK) {
		aw_kprintf(("AW_CAN_BUS_ERR_ACK\n"));        /**< \brief Ӧ����� */
	}

	if (error_status &AW_CAN_BUS_ERR_CRC) {
		aw_kprintf(("AW_CAN_BUS_ERR_CRC\n"));        /**< \brief CRC���� */
	}

	if (error_status &AW_CAN_BUS_ERR_FORM) {
		aw_kprintf(("AW_CAN_BUS_ERR_FORM\n"));       /**< \brief ��ʽ���� */
	}

	if (error_status &AW_CAN_BUS_ERR_STUFF) {
		aw_kprintf(("AW_CAN_BUS_ERR_STUFF\n"));      /**< \brief ������ */
	}

	if (error_status &AW_CAN_BUS_ERR_UNKNOWN) {
		aw_kprintf(("AW_CAN_BUS_ERR_UNKNOWN\n"));    /**< \brief δ֪���� */
	}

	if (error_status &AW_CAN_BUFF_ERR_RCVFULL) {
		aw_kprintf(("AW_CAN_BUFF_ERR_RCVFULL\n"));   /**< \brief ���ջ������� */
	}

	if (error_status &AW_CAN_BUFF_ERR_TXDFULL ) {
		aw_kprintf(("AW_CAN_BUFF_ERR_TXDFULL\n"));   /**< \brief ���ͻ������� */
	}
}

/* ����״̬�ص����� */
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

/* CANͨѶ���� */
void can_task (void *p_arg)
{
	struct aw_can_bps_param  can_baud_rate = {2, 0, 1, 9}; /* LPC17XX 4��Ƶ 500kbps */

	/* ���ûص����� */
	struct aw_can_App_CBfun  can_app_callback_fun = {can_err_status_cb,
			                                         can_bus_status_cb,
			                                         NULL,
			                                         NULL};

	struct aw_can_msg		 can_msg[10] = {{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};

	uint32_t framecnt  = 0;
	uint32_t donecnt   = 0;
	uint32_t ulresault = 0;

	/* CAN��ʼ�� */
	aw_can_init (0, AW_WORK_MODE_NROMAL, &can_baud_rate, &can_app_callback_fun);

	AW_INFOF(("CAN start up!\n"));

	/* ����������ѭ�� */
	AW_FOREVER {

		/* ����һ֡���� */
		framecnt = aw_can_frames_rcv (0, can_msg, 10, 0);
		if (framecnt) {

			/* �����ѽ�������*/
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
 * \brief ����CAN����
 * \return ��
 */
void demo_dev_can_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0, 1024);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������          */
                   2,                /* �������ȼ�      */
                  1024,              /* ����ջ��С       */
                  can_task,          /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */

    AW_TASK_STARTUP(task0);          /* ��������        */
}
/** [src_dev_can] */

/* end of file */
