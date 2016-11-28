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
 * \brief Apollo WATCHDOG(���Ź�) ��׼�ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ���
 * \code
 * #include "aw_wdt.h"
 * \endcode
 *
 * �������ṩ�˶�������Ź���ӡ�ι���Ľӿڣ����ϵͳδ�ڹ涨ʱ����
 * ����ι������ô�ͻᵼ��ϵͳ��λ��
 *
 * ע�⣺��ϵͳ�й涨��Ӳ�����Ź���ʱ��������1ms��
 *
 * \par ��ʾ��
 * \code
 * #include "aw_wdt.h"
 *
 * // ���ÿ��Ź�ʱ��Ϊ1200ms
 * struct awbl_wdt   wdt_dev;
 * aw_wdt_add(&wdt_dev, 1200);
 *
 * // ι��
 * aw_wdt_feed(&wdt_dev);
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 14-08-27  may, first implementation
 * \endinternal
 */


#ifndef __AW_WDT_H
#define __AW_WDT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apollo.h"
#include "aw_timer.h"

/**
 * \brief AWBus watchdog �豸
 */
struct awbl_wdt {

    /** \brief watchdog ʱ�� */
    uint32_t   period_ms;

    /** \brief ���ڿ��Ź���ʱ�������ʱ�� */
    aw_timer_t sftimer;
};

/**
 * \addtogroup grp_aw_if_watchdog
 * \copydoc aw_wdt.h
 * @{
 */
/**
 * \brief    ��ӿ��Ź��������ÿ��Ź�ʱ��
 *
 * \param    p_wdt:   watchdog�豸
 * \param    t_ms:    watchdogʱ��(ms)
 *
 * \retval   AW_OK:   �ɹ�
 * \retval  -EINVAL   p_wdtֵ��Ч
 * \retval  -EPERM    ����������
 */
aw_err_t  aw_wdt_add (struct awbl_wdt  *p_wdt, uint32_t  t_ms);

/**
 * \brief   ִ��ι������
 *
 * \param   p_wdt:    watchdog�豸
 *
 * \retval  AW_OK:    �ɹ�
 * \retval  -EINVAL   p_wdtֵ��Ч
 * \retval  -EPERM    ����������
 */
aw_err_t  aw_wdt_feed (struct awbl_wdt  *p_wdt);

/** @} grp_aw_if_watchdog */

#ifdef __cplusplus
}
#endif


#endif /* __AW_WDT_H */
