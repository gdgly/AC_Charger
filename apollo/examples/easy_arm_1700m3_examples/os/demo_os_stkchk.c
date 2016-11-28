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
 * \brief ��ջ�������
 *
 * - �������裺
 *   1. ����demo_os_stkchk_entry()����
 *   
 * - ʵ������
 *   1. ���ڴ�ӡ��ջʹ������������Ϣ
 *
 * \par Դ����
 * \snippet demo_os_stkchk.c src_os_stkchk
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_os_stkchk 
 * \copydoc demo_os_stkchk.c
 */

/** [src_os_stkchk] */ 

#include "apollo.h"
#include "main.h"                     
#include "aw_delay.h"
#include "aw_temp.h"
#include "aw_timer.h"
#include "aw_led.h"
#include "aw_isr_defer.h"
#include "aw_vdebug.h"
#include "aw_digitron_disp.h"
 
/** ������ */
AW_TASK_DECL_STATIC(ledtask,512);
AW_TASK_DECL_STATIC(stkchktask,512);
 
/** 
 * \brief LED������ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������ 
 *
 * \return ��
 */
static void led_entry(void *p_arg)
{
        
    AW_FOREVER{
        
        aw_led_on(LED0);
        aw_mdelay(200);
        aw_led_off(LED0);
        aw_mdelay(200);
    }        
    
}

/** 
 * \brief ��ջ���������ں���
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void stkchk_entry(void *p_arg) 
{
    
    unsigned int ledtask_total,ledtask_free;
    unsigned int stkchktask_total,stkchktask_free;
        
    AW_FOREVER {
        
        AW_TASK_STACK_CHECK(ledtask,&ledtask_total,&ledtask_free); 
        
        AW_TASK_STACK_CHECK_SELF(&stkchktask_total,&stkchktask_free);
        
        /* �������ʾ��������Ķ�ջʣ����� */
        aw_kprintf("led    task : ���� %4d,��ʹ�ã�%4d\n",ledtask_total,ledtask_free);
        aw_kprintf("stkchk task : ���� %4d,��ʹ�ã�%4d\n",stkchktask_total,stkchktask_free);
        aw_mdelay(500);

    }        
}

/** 
 * \brief ��ջ�����ʾ��ں���
 */
void demo_os_stkchk_entry (void)
{    
  
    AW_TASK_INIT(ledtask,    "ledtask",   3, 512, led_entry,    0);
    AW_TASK_INIT(stkchktask, "ledtask",   3, 512, stkchk_entry, 0);
    
    AW_TASK_STARTUP(ledtask);
    AW_TASK_STARTUP(stkchktask);
    
    /* �ú�������������ã���˴˴���������Ϊ������(aw_main��һ������ĺ�����)��ջʹ����� */
    // AW_TASK_STACK_CHECK_SELF(&total,&free);    
    // aw_kprintf("maintask:total: %d,free:%d \r\n",total,free);    
}

/** [src_os_stkchk] */ 

/* end of file */
