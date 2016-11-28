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
 * \brief  RTC����������RTC��׼�ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-08-26  cod, fix code style and comment, a little improve.
 * - 1.00 14-11-27  fft, first implementation.
 * \endinternal
 */

#ifndef __AMDR_RTC_H
#define __AMDR_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_rtc.h"
#include "amhw_rtc.h"
#include "amhw_power.h"

/**
 * \addtogroup amdr_if_rtc
 * \copydoc amdr_rtc.h
 * @{
 */

/** \brief RTC�жϻص��������� */
typedef void (*amdr_pfn_rtc_isr_t)(void *p_arg);

/**
 * \brief RTC �豸��Ϣ�ṹ��
 */
typedef struct amdr_rtc_devinfo {
    amhw_rtc_t  *p_hw_rtc;                  /**< \brief ָ��RTC�Ĵ�����Ľṹ��ָ�� */
    uint8_t      intnum;                    /**< \brief RTC�жϱ�� */
} amdr_rtc_devinfo_t;
    
/**
 * \brief RTC �豸�ṹ��
 */
typedef struct amdr_rtc_dev {
    am_rtc_serv_t             rtc_serv;    /**< \brief RTC��׼����           */
    const amdr_rtc_devinfo_t *p_devinfo;   /**< \brief ָ��RTC�豸��Ϣ��ָ�� */
} amdr_rtc_dev_t;

/**
 * \brief ����RTC����
 *
 * \param[in] p_tm      : ����RTC����ʱ��
 * \param[in] mask      : ��������λ���μ� \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \retval -AM_EINVAL   : p_tmΪ�գ���������
 * \retval AM_OK        : ���óɹ�
 */
int amdr_rtc_alarm_set (am_tm_t *p_tm, uint16_t mask);

/**
 * \brief RTC�����жϻص���������
 * \param[in] type           : RTC�ж����ͣ�ֵΪ
 *                             (#AMHW_RTC_INT_CIF)��(#AMHW_RTC_INT_CALF)
 * \param[in] pfn_alarm_cb   : RTC�жϻص�����
 * \param[in] p_arg          : �ص�������ڲ���
 *
 * \retval   -AM_EINVAL      : ��ڲ�������
 * \retval    AM_OK          : ���ӳɹ�
 */
int amdr_rtc_int_connect (uint32_t           type,
                          amdr_pfn_rtc_isr_t pfn_alarm_cb,
		                  void              *p_arg);

/**
 * \brief RTC�����жϻص������Ͽ�����
 *
 * \param[in] pfn_alarm_cb   : RTC�жϻص�����
 * \param[in] p_arg          : �ص�������ڲ���
 *
 * \retval   -AM_ENXIO       :  �ص�����δ����
 * \retval    AM_OK          :  ���ӳɹ�
 */
int amdr_rtc_int_disconnect (amdr_pfn_rtc_isr_t pfn_alarm_cb,
		                     void *p_arg);

/**
 * \brief ��ʼ��RTC
 *
 * \param[in] p_dev     : ָ��RTC�豸
 * \param[in] p_devinfo : ָ��RTC�豸��Ϣ
 *
 * \return RTC��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_rtc_handle_t amdr_rtc_init (amdr_rtc_dev_t            *p_dev,
                               const amdr_rtc_devinfo_t  *p_devinfo);

/**
 * \brief ���RTC��ʼ��
 * \param[in] p_dev : ָ��RTC�豸
 * \return  ��
 */
void amdr_rtc_deinit(amdr_rtc_dev_t *p_dev);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
