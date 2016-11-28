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
 * \brief �����������ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�:
 * \code
 * #include "aw_buzzer.h"
 * \endcode
 *
 * \par ʹ��ʾ��
 * \code
 * #include "aw_buzzer.h"
 *
 * (1)GPIO����ֱ��������
 * aw_buzzer_on();      // ����������
 * aw_buzzer_off();     // �رշ���������
 * aw_buzzer_beep(100); // ����������100����
 *
 * (2)ǿ�ȵ����豸������Դ������
 * aw_buzzer_loud_set(80);  // ���������еȼ�
 * aw_buzzer_beep(100);     // ����������100����
 *
 * \endcode
 *
 * \note ʹ��˳��Լ��
 *       [1]��ʹ��aw_buzzer_loud_set
 *       [2]��ʹ��aw_buzzer_beep/aw_buzzer_on/aw_buzzer_off
 *
 * \internal
 * \par modification history
 * - 1.01 14-07-09  ops, add aw_buzzer_loud_set
 * - 1.00 13-03-08  orz, first implementation.
 * \endinternal
 */

#ifndef __AW_BUZZER_H
#define __AW_BUZZER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_buzzer
 * \copydoc aw_buzzer.h
 * @{
 */

/** \brief ���������� */
void aw_buzzer_on (void);

/** \brief �رշ��������� */
void aw_buzzer_off (void);

/**
 * \brief ����������һ��
 * \param beep_time_ms ����ʱ�䣬��λ���롣
 * \note ����ӿڻ�ʹ�����߳����ߣ�����ʱ��Ϊ���е�ʱ�䡣������ͬʱʹ��
 *      ����ӿڻ���ɷ�Ԥ�ڵ�����Ч����
 */
void aw_buzzer_beep (unsigned int beep_time_ms);

/**
 * \brief ���÷������������
 * \param beep_level ������ȵȼ� (0 - 100)
 * \note  �ýӿڽ���ʹ����ǿ�ȵ��ڵķ�������Ч������ͨʹ��GPIO���Ƶ�
 *        ��������������øýӿ������������
 */
void aw_buzzer_loud_set (unsigned int beep_level);

/** @} grp_aw_if_buzzer */

#ifdef __cplusplus
}
#endif

#endif /* __AW_BUZZER_H */

/* end of file */
