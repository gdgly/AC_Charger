/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief isr deferral library
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_isr_defer.h
 *
 * \par ��ʾ��
 * \code
 *  #include "aw_isr_defer.h"
 *  #include "aw_vdebug.h"
 *
 *  struct aw_isr_defer_job g_myjob;                    // �ж��ӳٴ�������
 *
 *  // �ж��ӳٴ�������
 *  static void defer_job (void *param)
 *  {
 *      aw_kprintf("isr defer job is running...  (param = %d) \n", (int)param);
 *  }
 *
 *  // �����ʱ���жϷ�����
 *  void timer_isr (void *p_arg)
 *  {
 *      aw_isr_defer_job_add(&g_myjob);                 // ����ж��ӳٴ�������
 *      aw_timer_start(p_arg, aw_ms_to_ticks(500));     // �ٴζ�ʱ500ms
 *  }
 *
 *
 *  int main (void)
 *  {
 *      static aw_timer_t  timer;
 *
 *      // ��ʼ���ж��ӳٴ�������
 *      aw_isr_defer_job_init(&g_myjob, defer_job, (void *)0x12345678);
 *
 *      // ��ʼ�������������ʱ��
 *      aw_timer_init(&timer, timer_isr, (void *)&timer);
 *      aw_timer_start(&timer, aw_ms_to_ticks(500));    // ��ʱ500ms
 *  }
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.10 13-02-26  zen, modify module name from aw_isr_differ_xxxx to
 *                  aw_isr_defer_xxxx
 * - 1.00 12-12-10  liangyaozhan, first implementation
 * \endinternal
 */

#ifndef __AW_ISR_DEFER_H
#define __AW_ISR_DEFER_H

/**
 * \addtogroup grp_aw_if_isr_defer
 * \copydoc aw_isr_defer.h
 * @{
 */

#include "aw_task.h"
#include "aw_list.h"

/** \brief �ӳٴ������� */
struct aw_isr_defer_job
{
	struct aw_list_head node; /*!< node in the job queue. Empty means done */
    void (*func)(void *);     /*!< function pointer                        */
    void *param;              /*!< parameter                               */
};

/**
 *  \brief �ж��ӳٴ�����ʼ��
 */
void aw_isr_defer_lib_init( void );

/**
 * \brief ��ʼ��һ�� job
 *
 * \param[in] p_job     job �ڵ�ָ��
 * \param[in] pfunc     job �ص�����
 * \param[in] p_arg     job �ص������Ĳ���
 *
 * \par ʾ��
 * \code
 *  #include "aw_isr_defer.h"
 *  #include "aw_vdebug.h"
 *
 *  struct aw_isr_defer_job g_myjob;                    // �ж��ӳٴ�������
 *
 *  // �ж��ӳٴ�������
 *  static void defer_job (void *param)
 *  {
 *      aw_kprintf("isr defer job is running...  (param = %d) \n", (int)param);
 *  }
 *
 *  // �����ʱ���жϷ�����
 *  void timer_isr (void *p_arg)
 *  {
 *      aw_isr_defer_job_add(&g_myjob);                 // ����ж��ӳٴ�������
 *      aw_timer_start(p_arg, aw_ms_to_ticks(500));     // �ٴζ�ʱ500ms
 *  }
 *
 *
 *  int main (void)
 *  {
 *      static aw_timer_t  timer;
 *
 *      // ��ʼ���ж��ӳٴ�������
 *      aw_isr_defer_job_init(&g_myjob, defer_job, (void *)0x12345678);
 *
 *      // ��ʼ�������������ʱ��
 *      aw_timer_init(&timer, timer_isr, (void *)&timer);
 *      aw_timer_start(&timer, aw_ms_to_ticks(500));    // ��ʱ500ms
 *  }
 * \endcode
 */
void aw_isr_defer_job_init (struct   aw_isr_defer_job *p_job,
                            void    (*pfunc) (void *),
                            void     *p_arg);

/**
 * \brief ���������ӵ���������
 *
 * \param[in] p_job     job �ڵ�ָ�롣
 *
 * \retval  AW_OK    �� list_empty(&p_job->node)Ϊ�����
 *                  (p_job->node.next == NULL && p_job->node.prev == NULL)ʱ��
 *                  �ɹ��ӵ������С�
 *
 * \retval -EEXIST  �������ʧ�ܡ��ڵ���Ȼ�ڶ����С�
 *
 * \attention       �ڵ㱻�������list_empty(&p_job->node)Ϊ�档
 *                  �ر�أ���ʹ��list_empty(&p_job->node)ʱ��Ҫע����жϣ�
 *                  ����ʹ�� aw_isr_defer_job_is_usable()���档
 *
 * \par ʾ��
 * ��ο� aw_isr_defer_job_init()
 */
aw_err_t aw_isr_defer_job_add(struct aw_isr_defer_job *p_job);

/**
 * \brief �жϽڵ��Ƿ����
 *
 * \param[in] p_job  �ڵ�ָ�롣
 *
 * \retval  true    �ڵ����
 * \retval  false   �ڵ㲻����, �Ѿ�����ӵ�������
 *
 * \par ʾ��
 * \code
 *  void timer_isr (void *param)
 *  {
 *      if (aw_isr_defer_job_is_usable(&g_myjob) == true) {
 *          // �ڵ���ã�������ӵ�������
 *          aw_isr_defer_job_add(&g_myjob);
 *      } else {
 *          // �ڵ㲻���ã��Ѿ�����ӵ�������
 *      }
 *  }
 * \endcode
 */
bool_t aw_isr_defer_job_is_usable (struct aw_isr_defer_job *p_job);

/** @} grp_aw_if_isr_defer */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_ISR_DEFER_H */

/* end of file */

