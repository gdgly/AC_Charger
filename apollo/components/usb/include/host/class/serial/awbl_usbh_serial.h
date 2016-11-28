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
 * \brief USB to serial drvier head file
 *
 * define USB to serial driver data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 15-06-15  deo, first implementation
 * \endinternal
 */


#ifndef __AWBL_USBH_SERIAL_DRV_H
#define __AWBL_USBH_SERIAL_DRV_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbl_sio.h"
#include "aw_list.h"
#include "aw_rngbuf.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "host/awbl_usbhbus.h"

#define AWBL_USBH_SERIAL_DRV_NAME   "awbl_usbh_serial_driver"

/** \brief USB serial channel */
struct awbl_usbh_serial_chan {
    struct aw_sio_chan      sio_chan;       /**< \brief USB EndPoint address */
    int                     (*txchar_get)(void *, char *);
    int                     (*rxchar_put)(void *, char);
    void                    *txget_arg;
    void                    *rxput_arg;
    int                     channel_no;     /**< \brief channel number */
    uint8_t                 channel_mode;
    uint16_t                options;        /**< \brief channel options */
    uint32_t                baud_rate;
    uint8_t                 ctrl_line;
};

/** \brief USB serial port EndiPoint */
struct awbl_usbh_serial_port_ep {
    uint8_t                 ep_addr;    /**< \brief USB EndPoint address */
    struct aw_rngbuf        fifo;       /**< \brief FIFO for tish EP to transfer data */
    bool_t                  fifo_valid; /**< \brief instruct if FIFO is valid. */
    AW_SEMB_DECL(sem);
    void                    *p_buf;     /**< \brief data to be transfer by USB. */
    int                     buf_size;
    struct awbl_usbh_trp    trp;        /**< \brief USB TRP for this EP. */
};

/** \brief USB serial port */
struct awbl_usbh_serial_port {

    /** \brief point to father USB serial. */
    struct awbl_usbh_serial         *p_serial;

    /** \brief all EPs for this port */
    struct awbl_usbh_serial_port_ep bulk_in_ep;
    struct awbl_usbh_serial_port_ep bulk_out_ep;
    struct awbl_usbh_serial_port_ep intr_in_ep;
    struct awbl_usbh_serial_port_ep intr_out_ep;

    /** \brief SIO chan */
    struct awbl_usbh_serial_chan    chan;

    /** \brief instruct this port if in TX state. */
    bool_t                          tx_startup;

    uint8_t                         line_status;

    aw_spinlock_isr_t               lock;

    /** \brief private pointer for sub driver. */
    void                            *private;
};

/** \brief USB serial  */
struct awbl_usbh_serial {
    /** \brief point to USB device . */
    struct awbl_usbh_device         *p_udev;
    /** \brief point to USB interface . */
    struct awbl_usbh_interface      *p_itf;

    AW_MUTEX_DECL(mutex);

    /** \brief ports of this serial. */
    struct awbl_usbh_serial_port    *ports;
    /** \brief count of ports. */
    uint8_t                         num_ports;

    uint8_t                         num_intr_in;
    uint8_t                         num_intr_out;
    uint8_t                         num_bulk_in;
    uint8_t                         num_bulk_out;

    struct aw_list_head             node;

    /** \brief private pointer for sub device. */
    void                            *private;
};

/** \brief USB serial driver */
struct awbl_usbh_serial_drv {

    /** \brief father driver. */
    struct awbl_usbh_itfdev_drv itf_drv;

    /** \brief start up this serial, call by connect. */
    int (*startup) (struct awbl_usbh_serial_port *p_port);
    /** \brief set serial termios. */
    int (*set_termios) (struct awbl_usbh_serial_port *p_port);
    /** \brief callback function of EPs. */
    int (*bulk_rx_callback) (struct awbl_usbh_serial_port *p_port);
    int (*bulk_tx_callback) (struct awbl_usbh_serial_port *p_port);
    int (*intr_rx_callback) (struct awbl_usbh_serial_port *p_port);
    int (*intr_tx_callback) (struct awbl_usbh_serial_port *p_port);
};


/** \brief initialize the serial */
aw_err_t awbl_usbh_serial_init (struct awbl_usbh_serial    *p_ser,
                                struct awbl_usbh_interface *p_itf);

/** \brief register the serial */
void awbl_usbh_serial_register (struct awbl_usbh_serial *p_ser);

/** \brief remove the serial */
aw_err_t awbl_usbh_serial_remove (struct awbl_usbh_serial *p_ser);

/** \brief channel get for the SIO */
void awbl_usbh_serial_sio_chan_get (struct awbl_usbh_serial *p_ser,
                                    struct aw_sio_chan_info *p_info);

/** \brief channel connect for the SIO */
void awbl_usbh_serial_sio_chan_connect (struct awbl_usbh_serial *p_ser,
                                        struct aw_sio_chan_info *p_info);
#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_SERIAL_DRV_H */
