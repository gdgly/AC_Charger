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
 * \brief RTC��ʾ����
 *
 * - �������裺
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_RTC
 *
 * - ʵ������
 *   1. �趨�ó�ʼʱ�䣬ͨ�����ڿ��Թ۲� ʱ������������Ϣ��1�����2�����ݡ�
 *
 * \par Դ����
 * \snippet demo_dev_rtc.c src_dev_rtc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_rtc
 * \copydoc demo_dev_rtc.c
 */

/** [src_dev_rtc] */
#include "apollo.h"
#include "main.h"

#include "aw_delay.h"
#include "aw_led.h"

#include "aw_rtc.h"
#include "aw_vdebug.h"
#include <time.h>
 

/**
*\param[in] void *p_arg(����û���õ�)
*\note 
*/
void rtc_task (void *p_arg)
{

    aw_err_t stat = AW_OK;
    
   /* ������ʼʱ�� */
    aw_tm_t tm = {
      0,
      41,   
      17,
      7,                    /* day of the month      */
      11 - 1,               /* months since January  */
      2014 - 1900,          /* years since 1900      */
};            
    
    aw_rtc_time_set(0,&tm);                 /* ������ʼʱ�� */
    
    while (1) {
        
        stat = aw_rtc_time_get (0, &tm);    /* �õ�ϸ��ʱ�� */
  
        if (stat != AW_OK) {
            aw_kprintf("rtc ����ʧ�� %d \r\n",stat);
        } else {
            aw_kprintf("%s\n", asctime((const struct tm *)&tm));   /* ��ӡϸ��ʱ�� */
        }                          
        aw_mdelay(500);                                            /* ʱ����Ϣ 1���ӡ����*/
    }
}

/**
 * \brief ����RTC����
 * \return ��
 */
void demo_dev_rtc_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������          */
                   2,                /* �������ȼ�      */
                  512,               /* ����ջ��С       */
                  rtc_task,          /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task0);          /* ��������        */
}
/** [src_dev_rtc] */

/* end of file */
