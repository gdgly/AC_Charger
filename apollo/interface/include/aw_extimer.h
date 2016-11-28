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
 * \brief ��չ��ʱ����
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_extimer.h
 *
 * \par ��ʾ��
 * \code
 *
 * aw_local aw_extimer_t __g_extimer;
 *
 * aw_local void __extimer_callback(void *p_param)
 * {
 *     AW_INFOF(("__extimer_callback!\n"));
 * }
 *
 * aw_extimer_init((aw_extimer_t *)&__g_extimer,
 *         __extimer_callback, NULL);
 *
 * // �������ж�ʱ��
 * aw_extimer_start((aw_extimer_t *)&__g_extimer,
 *         aw_ms_to_ticks(1000),
 *         AW_TIMER_FLAG_ONE_SHOT);
 *
 * \internal
 * \par modification history
 * - 1.00 15-06-17  dav, create file
 * @endinternal
 */

#ifndef AW_EXTIMER_H_
#define AW_EXTIMER_H_

#include "rtk.h"
#include "aw_common.h"
#include "aw_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!< �������б��                */
#ifndef AW_TIMER_FLAG_ONE_SHOT
#define AW_TIMER_FLAG_ONE_SHOT              0x00
#endif

/*!< �ظ����б��                */
#ifndef AW_TIMER_FLAG_PERIODIC
#define AW_TIMER_FLAG_PERIODIC              0x01
#endif

/**
 * \brief ��չ��ʱ������
 * \note ��Ҫֱ�Ӳ������ṹ�ĳ�Ա
 */
struct aw_extimer
{
    struct rtk_tick     timer;
    unsigned int        flag;               /*!< timer_flag to determinate timer is ONE_SHOT or PERIODIC */
    unsigned int        tick;               /*!< initial tick count             */
    void (*timeout_callback)( void *);      /*!< timeout callback function      */
    void                *arg;               /*!< timeout callback parameter     */
};

typedef struct aw_extimer aw_extimer_t;

/**
 * \brief ��ʼ��ʱ��ṹ��
 *
 * \param p_extimer     ��ʱ������ָ��
 * \param p_func        ʱ�䶨ʱ���ص�����
 * \param p_arg         �ص������еĲ���
 *
 * \return ����״̬
 */
aw_err_t aw_extimer_init(aw_extimer_t *p_extimer, aw_pfuncvoid_t p_func, void *p_arg);

/**
 * \brief ������ʱ��
 *
 * \param p_extimer     ��ʱ������ָ��
 * \param ticks         ��ʱ����ִ��ʱ��
 * \param flag          ��ʱ�����õ�������ʽ�����λ����ظ�����
 *
 * \return ����״̬
 */
aw_err_t aw_extimer_start(aw_extimer_t *p_extimer, unsigned int ticks, unsigned int flag);

/**
 * \brief ֹͣ��ʱ��
 *
 * \param p_extimer     ��ʱ������ָ��
 *
 * \return ����״̬
 */
aw_err_t aw_extimer_stop(aw_extimer_t *p_extimer);

#ifdef __cplusplus
}
#endif


#endif /* AW_EXTIMER_H_ */
