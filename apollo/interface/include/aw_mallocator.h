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
 * \brief ��̬�ڴ��������
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ���
 * \code
 * #include "aw_mallocator.h"
 * \endcode
 *
 * \par ��ʾ��
 * \code
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 13-09-04  zen, first implementation
 * \endinternal
 */

#ifndef __AW_MEM_ALLOC_LIB_H
#define __AW_MEM_ALLOC_LIB_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_malloc
 * \copydoc aw_mallocator.h
 * @{
 */

typedef void *aw_mallocator_id_t;

aw_mallocator_id_t aw_mallocator_init(void *heap_mem, size_t heap_size, size_t min_size);

void *aw_mallocator_malloc(aw_mallocator_id_t allocator, size_t size);
void *aw_mallocator_calloc(aw_mallocator_id_t allocator, size_t count, size_t size);
void aw_mallocator_free(aw_mallocator_id_t allocator,  void *rmem);
void *aw_mallocator_trim(aw_mallocator_id_t allocator, void *rmem, size_t newsize);

/** @}  grp_aw_if_malloc */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_MEM_ALLOC_LIB_H */

/* end of file */

