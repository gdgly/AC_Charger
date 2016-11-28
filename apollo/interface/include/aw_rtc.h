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
 * \brief RTC (ʵʱʱ��) ��׼����
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_rtc.h
 *
 * \par ʹ��ʾ��
 * \code
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 13-09-05  zen, first implementation
 * \endinternal
 */

#ifndef __AW_RTC_H
#define __AW_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_time.h"

/**
 * \addtogroup grp_aw_if_rtc
 * \copydoc aw_rtc.h
 * @{
 */

/**
 * \brief ����RTCʱ��
 * \param rtc_id    RTC �豸���, ��0��ʼ����
 * \param p_tm      Ҫ���õ�ʱ��
 *
 * \retval AW_OK    �ɹ�
 * \retval -ENODEV  RTC�豸������
 * \retval -EIO     ����ʧ��
 */
aw_err_t aw_rtc_time_set (int rtc_id, aw_tm_t *p_tm);

/**
 * \brief ��ȡRTCʱ��
 * \param rtc_id    RTC �豸���, ��0��ʼ����
 * \param p_tm    ��ȡ��ʱ��
 *
 * \retval AW_OK    �ɹ�
 * \retval -ENODEV  RTC�豸������
 * \retval -EIO     ��ȡʧ��
 */
aw_err_t aw_rtc_time_get (int rtc_id, aw_tm_t *p_tm);

/** @} grp_aw_if_rtc */

#ifdef __cplusplus
}
#endif

#endif /* __AW_RTC_H */

/* end of file */

