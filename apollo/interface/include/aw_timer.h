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
 * \brief  �����ʱ���ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_timer.h
 *
 * \par ��ʾ��
 * \code
 *  #include "aw_timer.h"
 *
 *  // ��ʱ���ص�����
 *  void my_callback (void *p_arg)
 *  {
 *      aw_timer_t  *p_timer = p_arg;
 *     // ...
 *     aw_timer_start(p_timer, aw_ms_to_tick(500));     // �ٴζ�ʱ500ms
 *  }
 *
 *  int main() {
 *      aw_timer_t  timer;
 *
 *      // ��ʼ����ʱ��
 *      aw_timer_init(&timer, my_callback, &timer);
 *
 *      // ������ʱ������ʱ500ms
 *      aw_timer_start(&timer, aw_ms_to_tick(500));
 *
 *      // ��ʱ 20S.
 *      aw_task_delay(aw_ms_to_tick(20 * 1000));
 *
 *      // ֹͣ��ʱ��
 *      aw_timer_stop(&timer);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.10 13-03-21  zen, refine the description
 * - 1.01 13-02-22  orz, fix the defines and code style.
 * - 1.00 12-10-23  liangyaozhan, first implementation.
 * \endinternal
 */

#ifndef __AW_TIMER_H
#define __AW_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_timer
 * \copydoc aw_timer.h
 * @{
 */

#include "aw_psp_timer.h"

/**
 * \brief �����ʱ������
 * \hideinitializer
 */
typedef aw_psp_timer_t   aw_timer_t;

/**
 * \brief ��ʼ�������ʱ��
 *
 *  \attention ��ͼ��ʼ��һ�����ڹ����Ķ�ʱ�����ƻ��ں����ݽṹ��
 *             �û�������ʹ�� aw_timer_stop() ����ֹͣ��ʱ�����ٳ�ʼ����
 *
 * \param p_timer   �����ʱ��
 * \param p_func    ��ʱ���ص���������ʱ����ʱ�����ô˻ص����������������
 * \param p_arg     �ص������Ĳ���
 *
 * \return  �ɹ����������ʱ����ID��ʧ���򷵻�NULL
 *
 * \par ����
 * �� aw_timer_start()
 *
 * \sa aw_timer_start(), aw_timer_stop()
 */
void aw_timer_init (aw_timer_t *p_timer, aw_pfuncvoid_t p_func, void *p_arg);


/**
 * \brief ���������ʱ��
 *
 * ����ʱ����ʱ�������ʱ�������Զ�ֹͣ������Ҫ�����ԵĶ�ʱ������Ҫ�ڻص�������
 * �ٴε��� aw_timer_start() ��
 *
 * \attention ���Ա���������������һ������Ϊ׼��
 *
 * \param p_timer   �����ʱ��
 * \param ticks     ��ʱ���ȣ���λ��ϵͳ����������ʹ�� aw_ms_to_ticks()
 *                  ��������ת��Ϊ������
 * \par ����
 * \code
 *  #include "aw_timer.h"
 *
 *  // ��ʱ���ص�����
 *  void my_callback (void *p_arg)
 *  {
 *      aw_timer_t  *p_timer = p_arg;
 *     // ...
 *     aw_timer_start(p_timer, aw_ms_to_tick(500));     // �ٴζ�ʱ500ms
 *  }
 *
 *  int main() {
 *      aw_timer_t  timer;
 *
 *      // ��ʼ����ʱ��
 *      aw_timer_init(&timer, my_callback, &timer);
 *
 *      // ������ʱ������ʱ500ms
 *      aw_timer_start(&timer, aw_ms_to_tick(500));
 *
 *      // ��ʱ 20S.
 *      aw_task_delay(aw_ms_to_tick(20 * 1000));
 *
 *      // ֹͣ��ʱ��
 *      aw_timer_stop(&timer);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \sa aw_timer_init(), aw_timer_stop()
 */
void aw_timer_start (aw_timer_t *p_timer, unsigned int ticks);

/**
 * \brief ֹͣ�����ʱ��
 *
 * \param p_timer  �����ʱ��
 *
 * \par ����
 * �� aw_timer_start()
 *
 * \sa aw_timer_init(), aw_timer_start()
 */
void aw_timer_stop (aw_timer_t *p_timer);

/** @} grp_aw_if_timer */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_TIMER_H */

/* end of file */

