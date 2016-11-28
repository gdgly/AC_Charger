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
 * \brief ���Ź���WDT����ʾ���̣�����ƽ̨EasyARM-1700M3
 *
 * - ��������:
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_WDT
 *   2. USART0�ӿں�PC��������������
 *
 * - ʵ������:
 *   1. 4λ�������ʾ����"1024".
 *   2. �������������ڴ�ӡ"Add WDT device!"
 *   3. ÿι��һ�Σ���ӡ"Feed"
 *   4. ��ι����ʱ������λ�����´�ӡ��"Add WDT device!".
 *
 * \par Դ����
 * \snippet demo_dev_wdt.c src_dev_wdt
 *
 * \internal
 * \par History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_wdt
 * \copydoc demo_dev_wdt.c
 */

/** [src_dev_wdt] */
#include "apollo.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */

/* �������õ������·��� */
#include "aw_delay.h"                   /* ��ʱ����              */
#include "aw_wdt.h"                     /* WDT ����              */
#include "aw_led.h"                     /* LED ����              */
#include "aw_gpio.h"
#include "aw_vdebug.h"
#include "aw_sem.h"

#define WDT_TIMEOUT_MS     1200   /* ���Ź�ʱ��  */
#define FEED_TIME_MS       1000   /* ι��ʱ��  */

/**
 * \brief ����demo
 **/
void wdt_task (void)
{
	struct awbl_wdt wdt_dev;

	aw_wdt_add(&wdt_dev, WDT_TIMEOUT_MS);   /* ���ÿ��Ź�ʱ�� */

	aw_kprintf("Add WDT device!\r\n");
	aw_kprintf("WDT timeout is %d ms!\r\n", WDT_TIMEOUT_MS);

    /* LED0 �����˸ */
    while (1) {
		aw_wdt_feed(&wdt_dev);    /* ι��   */
		aw_mdelay(FEED_TIME_MS);
		aw_kprintf("Feed!\r\n");
    }

}


/**
 * \brief ����WDT����
 * \return ��
 */
void demo_dev_wdt_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0, 512);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������          */
                   2,                /* �������ȼ�      */
                  512,               /* ����ջ��С       */
                  wdt_task,          /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */

    AW_TASK_STARTUP(task0);          /* ��������        */
}
/** [src_dev_wdt] */

/* end of file */
