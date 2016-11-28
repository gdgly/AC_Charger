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
 * \brief 内存管理标准接口
 *
 * 使用本服务需要包含以下头文件：
 * \code
 * #include "aw_mem.h"
 * \endcode
 * 本服务提供了动态内存管理的接口
 * \par 简单示例
 * \code
 *
 * \endcode
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history:
 * - 1.00 13-09-22  zen, first implementation
 * \endinternal
 */

#ifndef __AW_MEM_H
#define __AW_MEM_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "aw_psp_mem.h"

/**
 * \addtogroup grp_aw_if_mem
 * \copydoc aw_mem.h
 * @{
 */

void *aw_mem_align(size_t size, size_t align);
void *aw_mem_alloc(size_t size);
void *aw_mem_calloc(size_t nelem, size_t size);
void aw_mem_free(void *ptr);
void *aw_mem_realloc(void *ptr, size_t newsize);

typedef aw_psp_heap_id_t aw_heap_id_t;
void *aw_memp_align(aw_heap_id_t heap_id,size_t size, size_t align);
void *aw_memp_alloc(aw_heap_id_t heap_id,size_t size);
void *aw_memp_calloc(aw_heap_id_t heap_id,size_t nelem, size_t size);
void aw_memp_free(aw_heap_id_t heap_id, void *ptr);
void *aw_memp_realloc(aw_heap_id_t heap_id, void *ptr, size_t newsize);

/** @}  grp_aw_if_mem */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_MEM_H */

/* end of file */

