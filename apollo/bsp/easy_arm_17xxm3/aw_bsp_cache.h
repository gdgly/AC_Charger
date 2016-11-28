/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief cache management
 *
 * \internal
 * \par modification history:
 * - 1.00 14-06-13  zen, first implementation
 * \endinternal
 */

#ifndef __AW_BSP_CACHE_H
#define __AW_BSP_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "apollo.h"
#include "arch/arm/armv4/armv4_mmu.h"

/******************************************************************************/
#define AW_PLFM_CACHE_LINE_SIZE     32

/******************************************************************************/
aw_static_inline void aw_cache_invalidate (void *address, size_t nbytes)
{
    mmu_invalidate_dcache((uint32_t)address, (uint32_t)nbytes);
}

/******************************************************************************/
aw_static_inline void aw_cache_flush (void *address, size_t nbytes)
{
    mmu_clean_dcache((uint32_t)address, (uint32_t)nbytes);
}

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_BSP_CACHE_H */

/* end of file */
