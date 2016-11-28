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
 * \brief ʱ�����ط���
 *
 * ��Ҫ������ aw_timestamp.h �Ϳ���ʹ�ñ�����
 *
 * \par ��ʾ��:�������ִ��ʱ��,us�����ʱ�����
 * \code
 *  #include "aw_timestamp.h"
 *
 *  int main()
 *  {
 *      unsigned int stamps;
 *
 *      stamps = aw_timestamp_get();
 *      //  do something
 *      stamps = aw_timestamp_get() - stamps;
 *      aw_kprintf("stamps used=%d\n , time=%d us",
 *                  stamps,
 *                  aw_stamps_to_us(tick));
 *      return 0;
 *  }
 * \endcode
 *
 * //�������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.01 14-08-18  tee,   modified and tested. 
 * - 1.00 13-02-27  zen,   first implementation
 * \endinternal
 */

#ifndef __AW_TIMESTAMP_H
#define __AW_TIMESTAMP_H

#include "aw_types.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_timestamp
 * \copydoc aw_timestamp.h
 * @{
 */
 
/** \brief ����ʱ���Ƶ�ʵ����� */
typedef aw_psp_timestamp_freq_t aw_timestamp_freq_t;

/**
 * \brief ��ȡʱ��� (32λ)
 *
 * \return ϵͳ��ǰʱ���ֵ(ʱ�����ʱ���ļ���ֵ)
 */
uint32_t aw_timestamp_get(void);

/**
 * \brief  ��ʱ���ת��Ϊʱ��(us)
 * \param  stamps ʱ�������
 * \return ����ʱ���������ת���õ���ʱ��us��
 */
uint32_t aw_timestamps_to_us(uint32_t stamps);
    
/**
 * \brief ��ȡʱ�����ʱ��Ƶ�� (32λ)
 *
 * \return ʱ�����ʱ��Ƶ��, Hz
 */
aw_timestamp_freq_t aw_timestamp_freq_get(void);

/**
 * \brief ��ȡʱ��� (64λ)
 *
 * \return ϵͳ��ǰʱ���ֵ(ʱ�����ʱ���ļ���ֵ)
 */
uint64_t aw_timestamp_get64(void);

  
/** @} grp_aw_if_system */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif    /* __AW_SYSTEM_H    */

/* end of file */
