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
 * \brief Apollo�������ʱ����ʹ������
 *
 * - �������裺
 *   1. ����demo_os_softtime_entry()����
 *   
 * - ʵ������
 *   1.���Կ���LED����1Hz��Ƶ����˸��
 *
 * \par Դ����
 * \snippet demo_os_softtimer.c src_os_softtimer
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_os_softtimer
 * \copydoc demo_os_softtimer.c
 */

/** [src_os_softtimer] */ 

#include "apollo.h"
#include "aw_task.h"
#include "aw_delay.h"
 
#include "aw_led.h"
#include "main.h"
 

/*
 * ʹ�������ʱ�����ܱ��������ͷ�ļ�
 */
#include "aw_timer.h"


/** 
 * \brief ��ʱ���ص�����
 *
 * \param[in] p_arg : ע��ʱ�û�������Զ������
 *
 * \return ��
 */
void my_callback (void *p_arg)
{ 
    aw_timer_t  *p_timer = p_arg;   
    
    aw_led_toggle(LED0);
    
    aw_timer_start(p_timer, aw_ms_to_ticks(500));     /* �ٴζ�ʱ500ms */
}

/** 
 * \brief �����ʱ��ʾ��ں���
 */
void demo_os_softtimer_entry (void)
{
    static aw_timer_t  timer;
    
    /* ��ʼ����ʱ��          */
    aw_timer_init(&timer, 
                  my_callback,                         /* ��ʱ���ص�����                           */
                  &timer);                             /* ����ʱ����Ϊ�������ݸ��ص�����           */
                                                       /* �Ա��ڻص��������ٴ����������������ʱ�� */
    /* ������ʱ������ʱ500ms */
    aw_timer_start(&timer, aw_ms_to_ticks(500));       /* �����ʱ������ϵͳtickΪ��λ��           */
       
}

/** [src_os_softtimer] */ 

/* end of file */
