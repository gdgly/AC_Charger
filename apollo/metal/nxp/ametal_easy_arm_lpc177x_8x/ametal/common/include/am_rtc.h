/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief  RTC ��׼�ӿ�
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-11-27  fft, first implementation.
 * \endinternal
 */

#ifndef __AM_RTC_H
#define __AM_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"
    
/** 
 * \addtogroup am_if_rtc
 * \copydoc am_rtc.h
 * @{
 */

/**
 * \brief ϸ��ʱ��, ���ṹ���� <time.h> �е� struct tm ����, ��ʹ�� <time.h> ��
 * �ĸ��������������� (ʹ��ǿ��ת�� (struct tm *)xx )
 */
typedef struct am_tm {
    int tm_sec;        /**< \brief ������ȡֵΪ[0, 59]             */
    int tm_min;        /**< \brief ���ӣ�ȡֵΪ[0, 59]             */
    int tm_hour;       /**< \brief ʱ ��ȡֵΪ[0, 23]               */
    int tm_mday;       /**< \brief ���ڣ����¼��㣩��ȡֵΪ[1, 31]  */
    int tm_mon;        /**< \brief �·ݣ� ȡֵΪ[0, 11]             */
    int tm_year;       /**< \brief ��ݣ���1900�꿪ʼ                                       */
    int tm_wday;       /**< \brief ���ڣ������ڼ��㣩��ȡֵΪ[0, 6] */
    int tm_yday;       /**< \brief ���ڣ�������㣩�� ȡֵΪ[0, 365] */
    int tm_isdst;      /**< \brief ����ʱ��־��                                                      */
} am_tm_t;
    
/** 
 * \brief RTC��������
 */
struct am_rtc_drv_funcs {
     
    /** \brief ���õ�ǰ��ϸ��ʱ�� */
    int (*pfn_rtc_time_set)(void *p_drv, am_tm_t *p_tm);
    
    /** \brief ��ȡ��ǰ��ϸ��ʱ�� */
    int (*pfn_rtc_time_get)(void *p_drv, am_tm_t *p_tm);
    
};


/** 
 * \brief RTC��׼����
 */
typedef struct am_rtc_serv {

    /** \brief RTC�������� */
    struct am_rtc_drv_funcs *p_funcs; 
    
    /** \brief ����������һ����ڲ��� */
    void                    *p_drv;
} am_rtc_serv_t;

/** \brief RTC��׼�������������� */
typedef am_rtc_serv_t *am_rtc_handle_t;

/**
 * \brief ���õ�ǰ��ϸ��ʱ��
 *
 * \param[in] handle : RTC��׼����������
 * \param[in] p_tm   : Ҫ���õ�ʱ��
 *
 * \return    AM_OK    : ���óɹ�
 * \retval  -AM_EINVAL : ��������
 */
am_static_inline
int am_rtc_time_set (am_rtc_handle_t handle, am_tm_t *p_tm)
{
    return handle->p_funcs->pfn_rtc_time_set(handle->p_drv, p_tm);
}

/**
 * \brief ��ȡ��ǰ��ϸ��ʱ��
 *
 * \param[in]  handle  : RTC��׼����������
 * \param[out] p_tm    : ��ȡ��ʱ��
 *
 * \return   AM_OK     : ��ȡʱ��ɹ�
 * \retval  -AM_EINVAL : ��������
 */
am_static_inline
int am_rtc_time_get (am_rtc_handle_t handle, am_tm_t *p_tm)
{
    return handle->p_funcs->pfn_rtc_time_get(handle->p_drv, p_tm);
}


/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_RTC_H */

/* end of file */
