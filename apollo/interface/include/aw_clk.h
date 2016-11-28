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
 * \brief Apollo CLK 接口头文件
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

/** \brief 时钟ID */
typedef aw_psp_clk_id_t   aw_clk_id_t;

/** \brief 时钟频率 (无符号类型) */
typedef aw_psp_clk_rate_t aw_clk_rate_t;

/**
 * \brief 使能时钟
 *
 * \param[in]   clk_id  时钟 ID (由平台定义)
 *
 * \retval      AW_OK   成功
 * \retval     -ENXIO   时钟频率ID不存在
 * \retval     -EIO     使能失败
 */
aw_err_t aw_clk_enable(aw_clk_id_t clk_id);

/**
 * \brief 禁能时钟
 *
 * \param[in]   clk_id  时钟 ID (由平台定义)
 *
 * \retval      AW_OK   成功
 * \retval     -ENXIO   时钟频率ID不存在
 * \retval     -EIO     禁能失败
 */
aw_err_t aw_clk_disable(aw_clk_id_t clk_id);

/**
 * \brief 获取时钟频率
 *
 * \param[in]   clk_id  时钟 ID (由平台定义)
 *
 * \retval      0       时钟频率为0，或获取时钟频率失败
 * \retval      正值           时钟频率
 */
aw_clk_rate_t aw_clk_rate_get(aw_clk_id_t clk_id);

/**
 * \brief 设置时钟频率
 *
 * \param[in]   clk_id  时钟 ID (由平台定义)
 * \param[in]   rate    时钟频率
 *
 * \retval      AW_OK   成功
 * \retval     -ENXIO   时钟频率ID不存在
 * \retval     -ENOTSUP 不支持要设置频率
 */
aw_err_t aw_clk_rate_set(aw_clk_id_t clk_id, aw_clk_rate_t rate);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_CLK_H */

/* end of file */

