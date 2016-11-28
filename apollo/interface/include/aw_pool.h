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
 * \brief �ڴ�ؿ�
 *
 * �ڴ���ṩ��һ�ֿ�����Ч���ڴ����ʽ��ʹ���ڴ�ؼ����˴Ӷ��з����ڴ�Ĵ���
 * (ʹ�� malloc())���Ӷ�������Ƶ�����䡢�ͷ��ڴ������µ��ڴ���Ƭ��
 *
 * �ڴ���е����ж��󶼾�����ͬ�Ĵ�С��
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_mallocator.h
 *
 * \par ��ʾ��
 * \code
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.01 14-11-05  orz, add aw_pool_item_size() function.
 * - 1.00 13-09-04  zen, first implementation.
 * \endinternal
 */

#ifndef __AW_POOL_H
#define __AW_POOL_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "aw_compiler.h"

/**
 * \addtogroup grp_aw_if_pool
 * \copydoc aw_pool.h
 * @{
 */

typedef struct aw_pool {

    /** \brief The head of the linked list of free blocks */
    void *p_free;

    /** \brief the original start this pool */
    void *p_start;

    /** \brief the last memory block managed by this memory pool */
    void *p_end;

    /** \brief maximum item size (in bytes) */
    size_t item_size;

    /** \brief total number of items */
    size_t item_count;

    /** \brief number of free blocks remaining */
    size_t nfree;

    /**
     * \brief minimum number of free blocks ever present in this pool
     *
     * \note this attribute remembers the low watermark of the pool,
     * which provides a valuable information for sizing event pools.
     * \sa aw_pool_margin_get().
    */
    size_t nmin;

} aw_pool_t;


typedef aw_pool_t *aw_pool_id_t;

aw_pool_id_t aw_pool_init(aw_pool_t *p_pool,
                          void      *p_pool_mem,
                          size_t     pool_size,
                          size_t     item_size);

void *aw_pool_item_get (aw_pool_id_t pool_id);

aw_err_t aw_pool_item_return (aw_pool_id_t pool_id, void *p_item);

aw_static_inline size_t aw_pool_item_size (aw_pool_id_t pool_id)
{
    return pool_id->item_size;
}

/** @}  grp_aw_if_pool_lib */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_POOL_H */

/* end of file */

