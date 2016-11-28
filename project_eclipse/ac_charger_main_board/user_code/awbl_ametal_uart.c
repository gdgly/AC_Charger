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
 * \brief The ametal uart driver directly from Ametal
 *
 * this driver is the implementation of AWBus uart for lpc54xxx
 *
 * \internal
 * \par modification history:
 * -1.00 14-09-16  jon, first implementation
 * \endinternal
 */

#include "apollo.h"
#include "aw_spinlock.h"
#include "aw_clk.h"
#include "awbus_lite.h"

#include "aw_common.h"
#include "aw_int.h"
#include "awbl_sio.h"
#include "aw_serial.h"
#include "aw_assert.h"

#include "driver/serial/awbl_ametal_uart.h"
#include "am_uart.h"
#include "am_int.h"

#define __DEV_GET_UART(p_dev) \
    ((struct awbl_ametal_uart_dev *)(p_dev))

#define __CHAN_GET_UART(p_chan) \
    ((struct awbl_ametal_uart_dev *)(AW_CONTAINER_OF(p_chan,struct awbl_ametal_uart_dev,chan)))

#define __DEV_GET_CHAN(p_dev) \
    ((struct awbl_uart_chan *)(&(__DEV_GET_UART(p_dev)->chan)))

#define __DEV_GET_PARAM(p_dev) \
    ((struct awbl_ametal_uart_param *)AWBL_DEVINFO_GET(p_dev))


/*******************************************************************************
  forward declarations
*******************************************************************************/
aw_local void __uart_inst_init(awbl_dev_t *p_dev);
aw_local void __uart_inst_init2(awbl_dev_t *p_dev);
aw_local void __uart_inst_connect(awbl_dev_t *p_dev);

/* sio drv  functions definitions */
aw_local aw_err_t __uart_ioctl (struct aw_sio_chan *p_siochan,
                                int                 request,
                                void               *p_arg);
                                
aw_local aw_err_t __uart_tx_startup (struct aw_sio_chan *p_siochan);
                                
aw_local aw_err_t __uart_callback_install (struct aw_sio_chan *p_siochan,
                                           int                 callback_type,
                                           aw_err_t          (*pfunc_callback)(void *),
                                           void               *callback_arg);
                                        
aw_local aw_err_t __uart_poll_input (struct aw_sio_chan *p_siochan,
                                     char               *p_char);

aw_local aw_err_t __uart_poll_output (struct aw_sio_chan  *p_siochan,
                                      char                 outchar);

/** \brief sio driver functions */
aw_local aw_const struct aw_sio_drv_funcs __g_ametal_uart_sio_drv_funcs = {
    __uart_ioctl,
    __uart_tx_startup,
    __uart_callback_install,
    __uart_poll_input,
    __uart_poll_output
};

/*******************************************************************************
    locals
*******************************************************************************/

int __options_convert_aw_to_ametal (int aw_options)
{
    int ametal_options = 0;
    
    switch (aw_options & CSIZE) {  
    case CS5:
        ametal_options |= AM_UART_CS5;
        break;
    case CS6:
        ametal_options |= AM_UART_CS6;
        break;
    case CS7:
        ametal_options |= AM_UART_CS7;
        break;
    case CS8:
        ametal_options |= AM_UART_CS8;
        break;
    default:
        break;
    }

    /* is two stop bits ? */
    if (aw_options & STOPB) {
        ametal_options |= AM_UART_STOPB;
    }
     
    if (aw_options & PARODD) {
        ametal_options |= AM_UART_PARODD;
    }
 
    if (aw_options & PARENB) {
        ametal_options |= AM_UART_PARENB;
    }

    return ametal_options;
}
    
int __options_convert_ametal_to_aw (int ametal_options)
{
    int aw_options = 0;
    
    switch (ametal_options & AM_UART_CSIZE) {  
    case AM_UART_CS5:
        aw_options |= CS5;
        break;
    case AM_UART_CS6:
        aw_options |= CS6;
        break;
    case AM_UART_CS7:
        aw_options |= CS7;
        break;
    case AM_UART_CS8:
        aw_options |= CS8;
        break;
    default:
        break;
    }

    /* is two stop bits ? */
    if (ametal_options & AM_UART_STOPB) {
        aw_options |= STOPB;
    }
     
    if (ametal_options & AM_UART_PARODD) {
        aw_options |= PARODD;
    }
 
    if (ametal_options &  AM_UART_PARENB) {
        aw_options |= PARENB;
    }

    return aw_options;
}

/**
 * \brief special device control
 *
 * Includes commands to get/set baud rate, mode (INT,POLL), hardware options
 * (parity, number of data bits), and modem control (RTS/CTS).
 * The ioctl command SIO_HUP is sent by ttyDrv when the last close() function
 * call is made. Likewise SIO_OPEN is sent when the first open() function call
 * is made.
 *
 * \return AW_OK on success, EIO on device AW_ERROR,
 *         ENOSYS on unsupported request
 */
aw_local aw_err_t __uart_ioctl (struct aw_sio_chan  *p_siochan,
                                  int                  request,
                                  void                *p_arg)
{
    struct awbl_ametal_uart_dev *p_uart    = __CHAN_GET_UART(p_siochan);
    am_uart_handle_t             handle  = p_uart->handle;
    aw_err_t                     status    = AW_OK;
    
    int tmp;
    
    switch (request) {

    case SIO_BAUD_SET: 
        if (am_uart_ioctl(handle,AM_UART_BAUD_SET,p_arg) != AM_OK) {
            status = -EIO;
        }
        break;
        
    case SIO_BAUD_GET:        
        if (am_uart_ioctl(handle,AM_UART_BAUD_GET,p_arg) != AM_OK) {
            status = -EIO;
        }
        break;
    
    case SIO_MODE_SET:
        
        if (((int)p_arg & SIO_MODE_INT) != 0) {
            tmp = AM_UART_MODE_INT;
        } else if (((int)p_arg & SIO_MODE_POLL) != 0) {
            tmp = AM_UART_MODE_POLL;
        } else {
            return -EIO;
        }
        if (am_uart_ioctl(handle,AM_UART_MODE_SET,(void *)tmp) != AM_OK) {
            status = -EIO;
        }
        break;
        
    case SIO_MODE_GET:
        if (am_uart_ioctl(handle,AM_UART_MODE_GET,(void *)&tmp) != AM_OK) {
            status = -EIO;
        }
        
        if ((tmp & AM_UART_MODE_INT) != 0) {
            *(int *)p_arg = SIO_MODE_INT;
        } else if ((tmp & AM_UART_MODE_POLL) != 0) {
            *(int *)p_arg = SIO_MODE_POLL;
        } else {
            return -EIO;
        }
        break;
        
    case SIO_AVAIL_MODES_GET:
        if (am_uart_ioctl(handle,AM_UART_AVAIL_MODES_GET,(void *)&tmp) != AM_OK) {
            status = -EIO;
        }
        
        *(int *)p_arg = 0;
        
        if ((tmp & AM_UART_MODE_INT) != 0) {
            *(int *)p_arg |= SIO_MODE_INT;
        }
        
        if ((tmp & AM_UART_MODE_POLL) != 0) {
            *(int *)p_arg |= SIO_MODE_POLL;
        }
        
        break;
        
    case SIO_HW_OPTS_SET:
        
        tmp = __options_convert_aw_to_ametal((int)p_arg);
        if (am_uart_ioctl(handle,AM_UART_OPTS_SET,(void *)tmp) != AM_OK) {
            status = -EIO;
        }
        break;

    case SIO_HW_OPTS_GET:
        if (am_uart_ioctl(handle,AM_UART_OPTS_GET,(void *)&tmp) != AM_OK) {
            status = -EIO;
        }
        *(int *)p_arg = __options_convert_ametal_to_aw(tmp);
        break;

    case SIO_HUP:

        break;

    case SIO_OPEN:
        break;

    /* add by xjc (temporary)*/
    case AM_UART_RS485_ENABLE_SET:
        if (am_uart_ioctl(handle,AM_UART_RS485_ENABLE_SET,(void *)p_arg) != AM_OK) {
            status = -EIO;
        }
        break;
    /* end */

    default:
        status = -ENOSYS;
        break;
    }

    return (status);
}


/**
 * \brief transmitter startup routine
 *
 * Call interrupt level character output routine and enable interrupt if it is
 * in interrupt mode with no hardware flow control.
 * If the option for hardware flow control is enabled and CTS is set TRUE,
 * then the Tx interrupt is enabled.
 *
 * \return AW_OK, or -ENOSYS if in polled mode
 */
aw_local aw_err_t __uart_tx_startup (struct aw_sio_chan *p_siochan)
{
    
    struct awbl_ametal_uart_dev *p_uart  = __CHAN_GET_UART(p_siochan);
    am_uart_handle_t             handle  = p_uart->handle;
    
    if (am_uart_tx_startup(handle) != AM_OK) {
        return (-ENOSYS);
    }
    
    return (AW_OK);
}


/**
 * \brief install ISR call backs
 *
 * This routine installs the call back functions to get/put chars for the
 * driver.
 *
 * \param p_siochan         pointer to device to control
 * \param callback_type     callback type(Tx or receive)
 * \param pfunc_callback    pointer to callback function
 * \param callback_arg      callback function argument
 *
 * \return AW_OK on success, ENOSYS on unsupported call back type
 */
aw_local aw_err_t __uart_callback_install (
                                struct aw_sio_chan *p_siochan,
                                int                 callback_type,
                                aw_err_t          (*pfunc_callback)(void *),
                                void               *callback_arg)
{
    struct awbl_ametal_uart_dev *p_uart  = __CHAN_GET_UART(p_siochan);
    am_uart_handle_t             handle  = p_uart->handle;

    switch (callback_type) {
        
    case AW_SIO_CALLBACK_GET_TX_CHAR:
        am_uart_callback_set(handle,
                             AM_UART_CALLBACK_GET_TX_CHAR,
                             pfunc_callback,
                             callback_arg);
        return (AW_OK);
    case AW_SIO_CALLBACK_PUT_RCV_CHAR:
        am_uart_callback_set(handle,
                             AM_UART_CALLBACK_PUT_RCV_CHAR,
                             pfunc_callback,
                             callback_arg);        
        return (AW_OK);
    default:
        return (-ENOSYS);
    }
}

/**
 * \brief output a character in polled mode
 *
 * This routine transmits a character in polled mode.
 *
 * \return AW_OK if a character sent, -EAGAIN if the output buffer is full
 */
aw_local aw_err_t __uart_poll_output (struct aw_sio_chan  *p_siochan,
                                      char                 outchar)
{
    struct awbl_ametal_uart_dev *p_uart  = __CHAN_GET_UART(p_siochan);
    am_uart_handle_t             handle  = p_uart->handle;
    
    if (am_uart_poll_putchar(handle,outchar) != AM_OK) {
        return (-EAGAIN);
    }
    
    return (AW_OK);
}

/**
 * \brief poll for input
 *
 * This routine polls the device for input.
 *
 * \return AW_OK if a character arrived, -EAGAIN if the input buffer if empty
 */
aw_local aw_err_t __uart_poll_input (struct aw_sio_chan *p_siochan,
                                     char               *p_char)
{
    struct awbl_ametal_uart_dev *p_uart  = __CHAN_GET_UART(p_siochan);
    am_uart_handle_t             handle  = p_uart->handle;
    
    if (am_uart_poll_getchar(handle,p_char) != AM_OK) {
        return (-EAGAIN);
    }
    
    return (AW_OK);
}

/**
 * \brief initialize lpc54xxx auart device
 *
 * This is the lpc54xxx auart initialization routine.
 *
 * \note
 */
extern void am_int_init(void);

aw_local void __uart_inst_init (awbl_dev_t *p_dev)
{
    struct awbl_uart_chan          *p_chan;
    struct awbl_ametal_uart_param  *p_param;
    struct awbl_ametal_uart_dev    *p_uart;
    
    /* get the parameter */
    p_param = __DEV_GET_PARAM(p_dev);
    
    p_uart  = __DEV_GET_UART(p_dev);
    
    /* Get the channel */
    p_chan  = __DEV_GET_CHAN(p_dev);
    
    p_chan->p_drv_funcs = &__g_ametal_uart_sio_drv_funcs;
    
    /* Call platform initialize function first */
    if (NULL != p_param->pfunc_plfm_init) {
        p_param->pfunc_plfm_init();
    }
    
    /* Call initialize function first */
    if (NULL != p_param->pfunc_uart_init) {
        p_uart->handle = p_param->pfunc_uart_init(p_param->p_hw_dev,
                                                  p_param->p_hw_devinfo);
                                                     
    }
    
    /* The COM ID is the device UNIT number */
    p_uart->com_id = AWBL_DEV_UNIT_GET(p_dev);
}

/**
 * \brief initialize lpc54xxx uart device
 */
aw_local void __uart_inst_init2 (awbl_dev_t *p_dev)
{
    
}


/**
 * \brief connect lpc54xxx auart device to system
 */
aw_local void __uart_inst_connect (awbl_dev_t *p_dev)
{

}


/**
 * \brief METHOD: get p_chan for the specified interface
 *
 * This routine returns the p_chan structure pointer for the
 * specified interface.
 */
void awbl_ametal_uart_sio_chan_get (awbl_dev_t *p_dev, void *p_arg)
{
    struct awbl_uart_chan          *p_chan;
    struct awbl_ametal_uart_dev    *p_uart   = __DEV_GET_UART(p_dev);

    struct aw_sio_chan_info  *p_info = (struct aw_sio_chan_info *)p_arg;

    if (p_uart->com_id == p_info->chan_no) {
        p_chan  = __DEV_GET_CHAN(p_dev);
        p_info->p_chan = p_chan;
    } else {
        return;
    }
}

/**
 * \brief METHOD: connect the specified interface to sio channel
 *
 * This routine connects the specified channel number to the SIO channel.
 * If successful, it returns the p_chan structure pointer of the channel
 * connected in the SIO_CHANNEL_INFO struct.
 *
 * If the specified channel is -1, or if the specified channel matches
 * any channel on this instance, then connect the channel.
 */
void awbl_ametal_uart_sio_chan_connect (awbl_dev_t *p_dev, void *p_arg)
{
    
    struct awbl_uart_chan          *p_chan;
    struct awbl_ametal_uart_dev    *p_uart;

    struct aw_sio_chan_info *p_info = (struct aw_sio_chan_info *)p_arg;
    
    p_uart  = __DEV_GET_UART(p_dev);
    p_chan  = __DEV_GET_CHAN(p_dev);
     
    /* Check previous instance success */
    if (p_info->p_chan != NULL) {
        return;
    }

    if (p_uart->com_id != p_info->chan_no) {
        return;
    }

    /* sanity check */
    if (p_chan == NULL) {
        return;
    }
 
    /* connect interrupts */
    am_uart_connect(p_uart->handle);

    /* notify caller and downstream instances of success */
    p_info->p_chan = p_chan;
    
}
 
aw_local aw_const struct awbl_drvfuncs g_uart_awbl_drvfuncs = {
    __uart_inst_init,        /* devInstanceInit */
    __uart_inst_init2,       /* devInstanceInit2 */
    __uart_inst_connect      /* devConnect */
};

/* methods for lpc54xxx uart driver */
aw_local aw_const struct awbl_dev_method g_uart_plb_awbl_methods[] = {
    AWBL_METHOD(aw_sio_chan_get,      awbl_ametal_uart_sio_chan_get),
    AWBL_METHOD(aw_sio_chan_connect,  awbl_ametal_uart_sio_chan_connect),
    AWBL_METHOD_END
};

/**
 * driver registration (must defined as aw_const)
 */
aw_local aw_const struct awbl_drvinfo __g_uart_drv_registration = {
    AWBL_VER_1,                         /* awb_ver */
    AWBL_BUSID_PLB,                     /* bus_id */
    AWBL_AMETAL_UART_NAME,              /* p_drvname */
    &g_uart_awbl_drvfuncs,              /* p_busfuncs */
    g_uart_plb_awbl_methods,            /* p_methods */
    NULL                                /* pfunc_drv_probe */
};


/**
 * \brief register lpc54xxx uart driver
 *
 * This routine registers the lpc54xxx uart driver and device recognition
 * data with the AWBus subsystem.
 *
 * NOTE: This routine is called early during system initialization, and
 * *MUST NOT* make calls to OS facilities such as memory allocation
 * and I/O.
 */
void awbl_ametal_uart_drv_register (void)
{
    awbl_drv_register(&__g_uart_drv_registration);
}
/* end of file */
