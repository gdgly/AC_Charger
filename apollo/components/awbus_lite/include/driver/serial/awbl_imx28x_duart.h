/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.embedcontrol.com/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief i.MX28 dbg uart header file
 *
 * \internal
 * \par modification history
 * - 1.00 14-05-13  chenminghao, for i.MX283
 * \endinternal
 */

#ifndef __AWBL_IMX28X_DUART_H
#define __AWBL_IMX28X_DUART_H

/**
 * \addtogroup grp_awbl_drv_duart
 * @{
 */

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_isr_defer.h"
#include "stdint.h"

/*******************************************************************************
    defines
*******************************************************************************/
#if 0
#define AWBL_CONFIG_UART_JOBQ    /* Use job queue for this driver */
#endif

#define AWBL_IMX28X_DUART_NAME "imx28x_duart"

/**
 * \name Register offsets from base address
 * @{
 */
/** \brief imx28x duart register */
typedef struct {
    volatile uint32_t  dr       ;      /**< \brief Data */
    volatile uint32_t  ecr      ;      /**< \brief Receive Status(Read) / Error Clear(Write) */
    volatile uint32_t  pad0[4]  ;
    volatile uint32_t  fr       ;      /**< \brief Flag */
    volatile uint32_t  pad1[1]  ;
    volatile uint32_t  ilpr     ;      /**< \brief IrDA Low-Power Counter */
    volatile uint32_t  ibrd     ;      /**< \brief Integer Baud Rate Divisor */
    volatile uint32_t  fbrd     ;      /**< \brief Fractional Baud Rate Divisor */
    volatile uint32_t  h        ;      /**< \brief Line Control */
    volatile uint32_t  cr       ;      /**< \brief Control */
    volatile uint32_t  ifls     ;      /**< \brief Interrupt FIFO Level Select */
    volatile uint32_t  imsc     ;      /**< \brief Interrupt Mask Set/Clear */
    volatile uint32_t  ris      ;      /**< \brief Raw Interrupt Status */
    volatile uint32_t  mis      ;      /**< \brief Masked Interrupt Status */
    volatile uint32_t  icr      ;      /**< \brief Interrupt Clear */
    volatile uint32_t  macr     ;      /**< \brief DMA Control */
} imx28x_duart_reg;
/** @} */


/*******************************************************************************
    types
*******************************************************************************/

/** \brief duart device channel structure for awbus lite */
struct awbl_imx28x_duart_chan {
    /** \brief driver functions, always goes first */
    aw_const struct aw_sio_drv_funcs *p_drv_funcs;

    /**< \brief device */
    struct awbl_dev          dev;

    /** \brief pointer to xmitr func */
    int  (*pfunc_txchar_get)(void *, char *);

    /** \brief pointer to rcvr func */
    int  (*pfunc_rxchar_put)(void *, char);

    void  *txget_arg;   /**< \brief argument for xmitr func */
    void  *rxput_arg;   /**< \brief argument for rcvr func */

    imx28x_duart_reg *p_regs;    /**< \brief uart registers */

    uint8_t  channel_mode;  /**< \brief such as INT, POLL modes */
    uint8_t  channel_no;    /**< \brief channel number */
    uint8_t  tx_defer;      /**< \brief TX interrupt is currently deferred */
    uint8_t  reg_space;     /**< \brief register address spacing */
    uint16_t fifo_size;     /**< \brief FIFO depth */
    uint16_t options;       /**< \brief hardware setup options */
    uint32_t baud_rate;     /**< \brief baud rate */

    awbl_dev_t *p_dev;              /**< \brief bus subsystem: device ID */

    void             *handle;       /**< \brief register access handle */
    aw_spinlock_isr_t spinlock_isr; /**< \brief ISR-callable spinlock */

#ifdef AWBL_CONFIG_UART_JOBQ
    struct aw_isr_defer_job  isr_jobq;     /**< \brief Job queue for ISR */
#endif

    /**
     * \brief next channel for this device
     *
     * Each device may have multiple channels. Here we maintain
     * a linked list of channels per controller.
     */
    struct awbl_imx28x_duart_chan *p_next;
};

AWBL_METHOD_IMPORT(aw_sio_dev2chan);
struct awbl_imx28x_duart_chan *awbldev_to_nschan(awbl_dev_t *p_dev);

/** \brief imx28x duart initialization structure for plb based AWBus devices */
struct awbl_imx28x_duart_chan_param {
    int      vector;    /**< \brief Actual architectural vector */
    uint32_t base_addr; /**< \brief Virt address of register set */
    uint32_t xtal;      /**< \brief UART clock frequency */

    /** \brief BSP function to pre initialize the device */
    void      (*pfunc_plfm_init)(void);
};

/*******************************************************************************
    uart driver exports
*******************************************************************************/

/** \brief uart driver functions */
aw_export aw_const struct awbl_drvfuncs g_imx28x_duart_awbl_drvfuncs;

/* UART SIO methods */
aw_export void __imx28x_duart_sio_chan_get (awbl_dev_t *p_dev, void *p_arg);
aw_export void __imx28x_duart_sio_chan_connect (awbl_dev_t *p_dev, void *p_arg);


#ifdef __cplusplus
}
#endif

#endif /* __AWBL_IMX28X_DUART_H */
