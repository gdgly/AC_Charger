/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief ACP1000 ��Ȩ��ʱ���
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-27  xjc, first implementation
 * \endinternal
 */
#include "aw_delayed_work.h"
#include "aw_vdebug.h"
#include "event_node.h"
static struct aw_delayed_work g_overtime_check_work; /* ��Ȩ���޲�����ʱ��⹤��  */
/*
 *  ˢ����3�����޿�ʼ��磨�����¼�Ȩ��
 *  �ó�ʱӦ�ô��ڲ�ǹ���������ʱ�䣬�Լ��ȴ���������ʱ��֮��
 * */
#define OVERTIME_NO_OPS         180000

/**
 * ��Ȩ���޲�����ʱ�������
 */
static void overtime_check_work (void *p_arg)
{
    struct event_manager *p_this = (struct event_manager *)p_arg;

    event_manager_tell_all(p_this, CARD_AUTH_FAIL, NULL);
}

/**
  * \brief ����������ʱ���
  */
void acp1000_overtime_check_restart()
{
    aw_delayed_work_stop(&g_overtime_check_work);
    aw_delayed_work_start(&g_overtime_check_work, OVERTIME_NO_OPS);
}

/**
  * \brief ȡ����ʱ���
  */
void acp1000_overtime_check_cancle()
{
    aw_delayed_work_stop(&g_overtime_check_work);
}

/**
  * \brief ��Ȩ���޲�����ʱ���
  */
void acp1000_overtime_task_startup (struct event_manager *p_this)
{
    aw_delayed_work_init(&g_overtime_check_work,
                          overtime_check_work,
                          p_this);
    aw_delayed_work_start(&g_overtime_check_work, OVERTIME_NO_OPS);
}


