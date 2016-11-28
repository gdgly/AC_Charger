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
 * \brief  PLL���ýӿ�
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
 * \brief ����PLL0��һ��ͨ�õĺ���
 *
 * ͨ������£����øú�������ʵ��PLL�������ã����øú���ǰ�����ú�PLL��ʱ�����롣
 * PLL0�����Ƶ�ʷ�Χ��9.75MHz ~ 160MHz��
 *
 * \param[in] clksrc        : PLL����ʱ��Դ
 * \param[in] desiredrate   : ������PLL���Ƶ��
 *
 * \retval > 0  PLL���ý�����ʵ�ʵ����Ƶ��
 * \retval = 0  PLL����ʧ��
 *
 */
uint32_t amhw_pll0_config(uint8_t clksrc, uint32_t desiredrate);

/**
 * \brief ����PLL1
 *
 * \param[in] desiredrate   : ������PLL1���Ƶ��
 *
 * \retval > 0  PLL1���ý�����ʵ�ʵ����Ƶ��
 * \retval = 0  PLL1����ʧ��
 * \note ����ʱ�ӹ̶�ΪOSC,PLL1����ֻ��ΪUSBʱ�ӣ�PLL1Ƶ��(MHz)ֻ������Ϊ48,96,144
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
