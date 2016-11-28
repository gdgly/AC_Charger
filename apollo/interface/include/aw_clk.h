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
 * \brief Apollo CLK �ӿ�ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 14-05-14  zen, first implementation
 * \endinternal
 */

#ifndef __AW_CLK_H
#define __AW_CLK_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "apollo.h"
#include "aw_psp_clk.h"

/** \brief ʱ��ID */
typedef aw_psp_clk_id_t   aw_clk_id_t;

/** \brief ʱ��Ƶ�� (�޷�������) */
typedef aw_psp_clk_rate_t aw_clk_rate_t;

/**
 * \brief ʹ��ʱ��
 *
 * \param[in]   clk_id  ʱ�� ID (��ƽ̨����)
 *
 * \retval      AW_OK   �ɹ�
 * \retval     -ENXIO   ʱ��Ƶ��ID������
 * \retval     -EIO     ʹ��ʧ��
 */
aw_err_t aw_clk_enable(aw_clk_id_t clk_id);

/**
 * \brief ����ʱ��
 *
 * \param[in]   clk_id  ʱ�� ID (��ƽ̨����)
 *
 * \retval      AW_OK   �ɹ�
 * \retval     -ENXIO   ʱ��Ƶ��ID������
 * \retval     -EIO     ����ʧ��
 */
aw_err_t aw_clk_disable(aw_clk_id_t clk_id);

/**
 * \brief ��ȡʱ��Ƶ��
 *
 * \param[in]   clk_id  ʱ�� ID (��ƽ̨����)
 *
 * \retval      0       ʱ��Ƶ��Ϊ0�����ȡʱ��Ƶ��ʧ��
 * \retval      ��ֵ           ʱ��Ƶ��
 */
aw_clk_rate_t aw_clk_rate_get(aw_clk_id_t clk_id);

/**
 * \brief ����ʱ��Ƶ��
 *
 * \param[in]   clk_id  ʱ�� ID (��ƽ̨����)
 * \param[in]   rate    ʱ��Ƶ��
 *
 * \retval      AW_OK   �ɹ�
 * \retval     -ENXIO   ʱ��Ƶ��ID������
 * \retval     -ENOTSUP ��֧��Ҫ����Ƶ��
 */
aw_err_t aw_clk_rate_set(aw_clk_id_t clk_id, aw_clk_rate_t rate);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_CLK_H */

/* end of file */

