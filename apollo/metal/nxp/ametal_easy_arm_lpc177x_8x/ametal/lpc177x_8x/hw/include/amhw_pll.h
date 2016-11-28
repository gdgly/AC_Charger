/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief  PLL配置接口
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_PLL_H
#define __AMHW_PLL_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"
#include "amhw_clock.h"

/**
 * \addtogroup amhw_if_pll
 * \copydoc amhw_pll.h
 * @{
 */

/**
 * \brief 配置PLL0，一个通用的函数
 *
 * 通常情况下，调用该函数即可实现PLL基本设置，调用该函数前，配置好PLL的时钟输入。
 * PLL0的输出频率范围（9.75MHz ~ 160MHz）
 *
 * \param[in] clksrc        : PLL输入时钟源
 * \param[in] desiredrate   : 期望的PLL输出频率
 *
 * \retval > 0  PLL配置结束后实际的输出频率
 * \retval = 0  PLL配置失败
 *
 */
uint32_t amhw_pll0_config(uint8_t clksrc, uint32_t desiredrate);

/**
 * \brief 配置PLL1
 *
 * \param[in] desiredrate   : 期望的PLL1输出频率
 *
 * \retval > 0  PLL1配置结束后实际的输出频率
 * \retval = 0  PLL1配置失败
 * \note 输入时钟固定为OSC,PLL1输入只作为USB时钟，PLL1频率(MHz)只能设置为48,96,144
 */
uint32_t amhw_pll1_config(uint32_t desiredrate);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_PLL_H */

/* end of file */
