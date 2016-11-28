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
 * \brief ametal serial driver  header file
 *
 * \internal
 * \par modification history:
 * - 1.00 14-09-20  tee, first implementation
 * \endinternal
 */


#ifndef __AWBL_AMETAL_UART_H
#define __AWBL_AMETAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_spinlock.h"
#include "aw_serial.h"
#include "am_uart.h"
#include "amdr_usart.h"
#include "aw_compiler.h"

#define AWBL_AMETAL_UART_NAME               "ametal_uart"

/*******************************************************************************
  types
*******************************************************************************/

/**< \brief The Pointer to the hardware initialize function */
typedef am_uart_handle_t (*pfunc_uart_init_t)(void *,const void *); 

typedef struct awbl_uart_chan {
    
    /** \brief driver functions, always goes first */
    aw_const struct aw_sio_drv_funcs *p_drv_funcs;

} awbl_uart_chan_t;

/** \brief ametal auart initialization structure for plb based AWBus devices */
struct awbl_ametal_uart_param {
    
    /** \brief Pointer to the hardware dev    */
    void        *p_hw_dev;  
         
    /**< \breif Pointer to the hardware device information */
    const void  *p_hw_devinfo;
    
    /**< \brief Pointer to the hardware initialize function */
    pfunc_uart_init_t  pfunc_uart_init; 
    
    /** \brief BSP function to pre initialize the device */
    void (*pfunc_plfm_init)(void);
};

/** \brief ametal uart dev. one dev may contain multi chan.  */
struct awbl_ametal_uart_dev {
    struct awbl_dev         dev;       /**< \brief awbl device data               */
    awbl_uart_chan_t        chan;
    am_uart_handle_t        handle;    /**< \brief The handle from hardware       */
    uint8_t                 com_id;    /**< \brief The COM id,usually id unit num */
};

void awbl_ametal_uart_drv_register (void);


#ifdef __cplusplus
}
#endif

#endif /* __AWBL_AMETAL_UART_H */


/* end of file */
