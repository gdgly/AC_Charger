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
 * \brief Apollo ��ʱ��׼�ӿ�
 *
 * ʹ�ñ�ģ����Ҫ��������ͷ�ļ���
 * \code
 * #include "aw_delay.h"
 * \endcode
 *
 * \par ��ʾ��
 * \code
 *  #include "apollo.h"
 *  #include "aw_delay.h"
 *
 *  aw_mdelay(100);     // ��ʱ100 ms
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 12-07-09  zyr, first implementation
 * \endinternal
 */

#ifndef __AW_DELAY_H
#define __AW_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_delay
 * \copydoc aw_delay.h
 * @{
 */

/*lint ++flb */
#include "stdint.h"
#include "aw_task.h"
#include "aw_psp_delay.h"

/**
 * \brief ��ʱ����
 *
 * \param[in] ms   ��ʱ������
 *
 * \return  none
 */
extern void aw_mdelay(uint32_t ms);

/**
 * \brief ��ʱ΢��
 *
 * \attention ����ʱʹ��CPU����ʵ��
 *
 * \param[in] us   ��ʱ΢����
 *
 * \return  none
 */
extern void aw_udelay(uint32_t us);

/** @}  grp_aw_if_delay */

#ifdef __cplusplus
}
#endif

#endif /* __AW_DELAY_H */

/* end of file */
