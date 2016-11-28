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
 * \brief lpc17xx USB device controller driver head file
 *
 * \internal
 * \par modification history:
 * - 1.01 15-10-20  cod, first implementation
 * - 1.00 15-08-13  deo, first implementation
 * \endinternal
 */


#ifndef __AWBL_LPC17XX_USBD_H
#define __AWBL_LPC17XX_USBD_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "device/awbl_usbd.h"
#include "aw_spinlock.h"
#include "aw_pool.h"

#define AWBL_LPC17XX_USBD_NAME  "awbl_lpc17xx_usbd"

/**
 * \name  DD control Bit defined
 * @{
 */
#define __DMA_MODE_NORMAL     (0 << 0)   /**< \brief Normal mode */
#define __DMA_MODE_ATLE       (1 << 0)   /**< \brief ATLE mode */
#define __NEXT_DD_VALID       (1 << 2)   /**< \brief next dd vaild */
#define __ISO_EP              (1 << 4)   /**< \brief iso endpoint */

/** \brief maxpacket size */
#define __MAX_PKT_SIZE(size)       ((size & 0x7FF) << 5)

/** \brief Get maxpacket size */
#define __MAX_PKT_SIZE_GET(size)   ((size >> 5) & 0x7FF)

/** \brief DD buf len */
#define __DMA_BUF_LEN(len)         ((len & 0xFFFF) << 16)

/** @} */

/**
* \name DD status bit defined
* @{
*/
#define __RETIRED               (1 << 0)
#define __STATUS(info)          (((info) >> 1) & 0xF)

#define __NOTSERVICED           0x0
#define __BEINGSERVICED         0x1
#define __NORMALCOMPLETION      0x2
#define __DATAUNDERRUN          0x3
#define __DATAOVERRUN           0x8
#define __SYSTEMERROR           0x9

#define __PKT_VALID             (1 << 5)
#define __PRESENT_DMA_CNT(info) ((info >> 16) & 0xFFFF)
/** @} */


/** \brief lpc17xx USB device DMA struct */
struct awbl_lpc17xx_usbd_dma_desc {
    uint32_t    next;           /**< \brief next dd address */

    uint32_t    control;        /**< \brief DD control information */

    uint32_t    buf;            /**< \brief DD Buffer address */

    uint32_t    status;         /**< \brief DD status */

    uint32_t    iso_buf;        /**< \brief iso buffer  */

};

/* current endpoint state */
#define __EP_ST_DISABLE 0x00    /* Endpoint disable */
#define __EP_ST_ENABLE  0x01    /* Endpoint enable  */
#define __EP_ST_RESET   0x02    /* Endpoint reset   */

/** \brief lpc17xx USB EPs struct */
struct awbl_lpc17xx_usbd_ep {

    /** \brief usb ep */
    struct awbl_usbd_ep                 ep;

    /** \brief lpc17xx usbd device */
    struct awbl_lpc17xx_usbd           *p_usbd;

    /** \brief current endpoint transfer */
    struct awbl_usbd_transfer          *p_transfer;

    /** \brief current endpoint DMA descriptor list */
    struct awbl_lpc17xx_usbd_dma_desc  *p_dd_list;

    /** \brief current endpoint DD control information */
    uint32_t                            control;

    /* endpoint state*/
    uint8_t                             state;

};

/** \brief lpc17xx USB device controller struct */
struct awbl_lpc17xx_usbd {

    /** \brief usbd device */
    struct awbl_usbd                        usbd;

    /** \brief EPs (IN and OUT) */
    struct awbl_lpc17xx_usbd_ep            *eps;

    /** \brief EP DMA descriptor address table */
    uint32_t                               *udca;

    /** \brief Remain EPRAM */
    uint16_t                                remain_epram;

    /** \brief DMA descriptor pool */
    struct aw_pool                          dd_pool;

    /** \brief spinlock */
    aw_spinlock_isr_t                       lock;

    /** \brief usb ctrl request */
    struct awbl_usb_ctrlreq                 setup;

    /** \brief usb ep0 OUT transfer */
    struct awbl_usbd_transfer              *p_transfer_out;

    /** \brief usb ep0 IN transfer */
    struct awbl_usbd_transfer              *p_transfer_in;
};

/** \brief lpc17xx USB device controller information */
struct awbl_lpc17xx_usbd_info {

    /** \brief controller information */
    struct awbl_usbd_info usbd_info;

    /** \brief controller register base */
    uint32_t    regbase;

    /** \brief IRQ number */
    int         inum;

    /* 128 bytes for UDCAH register,
     * must aligned to 128 bytes boundaries. */
    void        *udca;

    /** \brief  used endpoints(must be less than 32)*/
    uint8_t      ep_num;

    /* memory for DMA descriptor pool,
     * must aligned to 4 bytes boundaries. */
    void        *p_dd;

    /* DMA descriptor number */
    int          dd_num;

    /* platform init */
    void (*pfunc_plfm_init)(void);
};

void awbl_lpc17xx_usbd_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */


#endif /* __AWBL_LPC17XX_USBD_H */
