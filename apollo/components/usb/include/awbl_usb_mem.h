/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief USB memory support head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-04-28  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USB_MEM_H
#define __AWBL_USB_MEM_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#if 0
/** \brief USB DMA buffer struct */
struct awbl_usb_dma_buf {
    /** \brief number of data buffer */
    size_t  nbuf;

    /** \brief raw data */
    void    *p_data;

    /** \brief direction */
    bool_t  is_in;

    struct {
        void    *p_buf;
        size_t  len;
        bool_t  remap;
    }b[0];
};
#endif

/** \brief USB memory initial */
void awbl_usb_mem_init (void);

/** \brief allocate cache-safe memory */
void *awbl_usb_uncached_mem_alloc (size_t size);

/** \brief allocate cache-safe memory with align */
void *awbl_usb_uncached_mem_alloc_align (size_t size,
                                         size_t align);

/** \brief free cache-safe memory */
void awbl_usb_uncached_mem_free (void *ptr);

/** \brief allocate cache memory */
void *awbl_usb_cached_mem_alloc (size_t size);

/** \brief free cache memory */
void awbl_usb_cached_mem_free (void *ptr);

/** \brief allocate a USB memory buffer */
struct awbl_usb_dma_buf *
awbl_usb_buf_alloc (void *p_data, size_t len, bool_t is_in);

/** \brief free a USB memory buffer */
aw_err_t awbl_usb_buf_free (struct awbl_usb_dma_buf *p_buf);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USB_MEM_H */
