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
 * \brief cache �����׼�ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_cache.h
 * 
 * �������ṩ�˹��� cache �Ľӿ�
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

#ifndef __AW_CACHE_H
#define __AW_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_cache
 * \copydoc aw_cache.h
 * @{
 */

#include "aw_psp_cache.h"

/** \brief �����ߴ�С */
#define AW_CACHE_LINE_SIZE  AW_PSP_CACHE_LINE_SIZE

/**
 * \brief �����п��Ա���д������ָ����Χ�����ݻ�д���ڴ�
 *
 * \note ͨ�� AW_CACHE_LINE_SIZE �õ�������(cache line)��С
 *
 * \param address   ��ʼ��ַ,���õ�ַ���ǻ����ߵ���ʼ��ַ����ʹ�øõ�ַ����
 *                  �����ߵ���ʼ��ַ
 * \param nbytes    ����, ���ᱻ round up �������ߴ�С
 */
void aw_cache_flush (void *address, size_t nbytes);

/**
 * \brief �����л����н�ָ����Χ�����ݱ��Ϊ��Ч, ���´��ڴ��ж�ȡ
 *
 * \note ͨ�� AW_CACHE_LINE_SIZE �õ�������(cache line)��С
 *
 * \param address   ��ʼ��ַ,���õ�ַ���ǻ����ߵ���ʼ��ַ����ʹ�øõ�ַ����
 *                  �����ߵ���ʼ��ַ
 * \param nbytes    ����, ���ᱻ round up �������ߴ�С
 */
void aw_cache_invalidate (void *address, size_t nbytes);

/**
 * \brief ���� cache-safe �Ļ��������� DMA �豸������
 *
 * \param nbytes    ����, ���ᱻ round up �������ߴ�С
 *
 * \return ��������ʼ��ַ �� NULL
 *
 * \sa aw_cache_dma_free()
 */
void *aw_cache_dma_malloc (size_t nbytes);

/**
 * \brief ���� cache-safe �Ļ��������� DMA �豸������
 *
 * \param nbytes    ����, ���ᱻ round up �������ߴ�С
 * \param align     ���볤��
 * \return ��������ʼ��ַ �� NULL
 *
 * \sa aw_cache_dma_free()
 */
void *aw_cache_dma_align (size_t nbytes, size_t align);


/**
 * \brief �ͷ� cache-safe �Ļ�����
 *
 * \param  ptr ��������ʼ��ַ(���� aw_cache_dma_malloc()��ȡ��)
 *
 * \sa aw_cache_dma_malloc()
 */
void aw_cache_dma_free (void *ptr);

/** @}  grp_aw_if_cache */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_CACHE_H */

/* end of file */
