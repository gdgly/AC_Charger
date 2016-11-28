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
 * \brief DAC��ʾ����
 *
 * - �������裺
     1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_DAC
 *   2. PIO0_2��������PC���ڵ�TXD��
 *   3. PIO0_3��������PC���ڵ�RXD��
 *
 * - ʵ������
 *   1. ���ڴ�ӡDAC���ȼ�λ����
 *   2. ʹ�����ñ����P0.26�ܽţ��ɹ۲쵽ÿ��2s��ѹ��1.2V��1.8V֮��仯��
 *   3. ��ѹ�仯��LED0��ת��
 *
 * \par Դ����
 * \snippet demo_dev_dac.c src_dev_dac
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-15  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_dac
 * \copydoc demo_dev_dac.c
 */

/** [src_dev_dac] */
#include "apollo.h"
#include "main.h"

#include "aw_task.h"
#include "aw_delay.h"
#include "aw_led.h"
#include "aw_vdebug.h"
#include "aw_dac.h"

/**
 * \brief DAC�������
 *\param[in] p_arg : �������
 * \return ��
 */
static void task_entry (void *p_arg)
{
    int dac_bits = aw_dac_bits_get(0);       /* ��ȡDACͨ��0��ת��λ�� */
    int dac_vref = aw_dac_vref_get(0);       /* ��ȡDACͨ��0�Ĳο���ѹ(��λ��mV) */

    aw_dac_val_t dac_val1, dac_val2;

    aw_kprintf("The bits is %d  \r\n", dac_bits);
    aw_kprintf("The vref is %d  \r\n", dac_vref);

    dac_val1 = 1200 * (1 << dac_bits) / dac_vref;
    dac_val2 = 1800 * (1 << dac_bits) / dac_vref;


    aw_dac_val_set(0, dac_val1);      /* ����DACͨ��0�������ѹΪ 1.2V (δʹ�ܣ���δʵ�����)*/
    aw_dac_enable(0);                 /* ʹ������������ѹΪ1.2V*/

    while (1) {
    	aw_dac_val_set(0, dac_val1);      /*����DACͨ��0�������ѹΪ 1.2V (ǰ����ʹ�ܣ�ʵ�������ѹ1.4V)*/
    	aw_led_toggle(LED0);              /* LED0��ת */
    	aw_mdelay(1000);
        aw_dac_val_set(0, dac_val2);      /*����DACͨ��0�������ѹΪ 1.4V (ǰ����ʹ�ܣ�ʵ�������ѹ1.4V)*/
        aw_led_toggle(LED0);              /* LED0��ת */
        aw_mdelay(1000);

    }
}

/**
 * \brief ����DAC����
 * \return ��
 */
void demo_dev_dac_entry (void)
{
    AW_TASK_DECL_STATIC(task, 1024);

    AW_TASK_INIT(task,               /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL ���� */
                "task",              /* ��������                                            */
                 6,                  /* �������ȼ�                                          */
                 1024,               /* �����ջ��С                                        */
                 task_entry,         /* ������ں���                                        */
                (void*)0);           /* ������ڲ���                                        */

    AW_TASK_STARTUP(task);
}

/** [src_dev_dac] */

/* end of file */
