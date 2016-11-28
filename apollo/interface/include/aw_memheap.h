/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief ∂—π‹¿Ì∆˜
 *
 * \internal
 * \par modification history:
 * - 1.00 14-06-13  zen, first impementation
 * \endinternal
 */

#ifndef __AW_MEMHEAP_H
#define __AW_MEMHEAP_H

#include "apollo.h"
#include "aw_sem.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_memheap
 * \copydoc aw_memheap.h
 * @{
 */

/**
 * \brief memory item on the memory heap
 */
typedef struct aw_memheap_item
{
    uint32_t                magic;                      /**< magic number for memheap */
    struct aw_memheap      *pool_ptr;                   /**< point of pool */

    struct aw_memheap_item *next;                       /**< next memheap item */
    struct aw_memheap_item *prev;                       /**< prev memheap item */

    struct aw_memheap_item *next_free;                  /**< next free memheap item */
    struct aw_memheap_item *prev_free;                  /**< prev free memheap item */
} aw_memheap_item_t;

/**
 * \brief memory heap
 */
typedef struct aw_memheap
{
    const char             *name;               /**< pool name */
    void                   *start_addr;         /**< pool start address and size */

    uint32_t                pool_size;          /**< pool size */
    uint32_t                available_size;     /**< available size */
    uint32_t                max_used_size;      /**< maximum allocated size */

    struct aw_memheap_item *block_list;         /**< used block list */

    struct aw_memheap_item *free_list;          /**< free block list */
    struct aw_memheap_item  free_header;        /**< free block list header */

    AW_MUTEX_DECL(lock);                        /**< semaphore lock */
} aw_memheap_t;

aw_err_t aw_memheap_init(struct aw_memheap *memheap,
                         const char        *name,
                         void              *start_addr,
                         uint32_t           size);

aw_err_t aw_memheap_detach(struct aw_memheap *heap);
void *aw_memheap_alloc(struct aw_memheap *heap, uint32_t size);
void *aw_memheap_realloc(struct aw_memheap *heap, void *ptr, size_t newsize);
void aw_memheap_free(void *ptr);

/** @}  grp_aw_if_memheap */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AW_MEMHEAP_H    */

/* end of file */
