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
 * \brief AWBus AMETAL SPI driver file
 *
 *
 * \internal
 * \par modification history:
 * - 1.00 15-1-16  jon, first implementation
 * \endinternal
 */


#ifndef __AWBL_AMETAL_SPI_H
#define __AWBL_AMETAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */



#include "aw_spinlock.h"
#include "awbl_spibus.h"
#include "am_spi.h"

#define AWBL_AMETAL_SPI_NAME   "ametal_spi"

typedef am_spi_handle_t (*pfn_spi_init_t)(void *, const void *);
/**
 * \brief AMETAL SPI device information 
 */
typedef struct awbl_ametal_spi_devinfo {

    /** \brief 继承自 AWBus SPI 控制器设备信息 */
    struct awbl_spi_master_devinfo spi_master_devinfo;
    
     /** \breif Pointer to the hardware dev    */
    void                           *p_hw_dev;   
    
    /** \breif Pointer to the hardware device information  */
    const void                     *p_hw_devinfo;
    
    /** \brief Pointer to the hardware initialize function */
    pfn_spi_init_t  pfn_spi_init;

    void (*pfn_plfm_init)(void);
}awbl_ametal_spi_devinfo_t;

/**
 * \brief AMETAL SPI device instantiation
 */
typedef struct awbl_ametal_spi_dev {

    /** \brief inherit from AWBus SPI master controller */
    struct awbl_spi_master  super;

    /** \brief The current Message      */
    struct aw_spi_message  *p_cur_msg;

    /** \brief The current Transfer     */
    struct aw_spi_transfer *p_cur_trans;
    
    /** \brief The current trans flags  */
    uint32_t               trans_flags;

    /** \brief Controller busy flag */
    bool_t                  busy;

     /** \brief Controller status  */
    int                     state; 
    
    /** \brief The controller current speed */
    uint32_t                cur_speed; 
    
    /** \brief The controller current the length of frame */
    uint8_t                 cur_bpw; 
    
    /** \brief The controller current mode  */       
    uint8_t                 cur_mode;    
    
    /** \brief CS lock flag */
    uint8_t                 cs_toggle;       
    
    /** \brief Current lock device */
    aw_spi_device_t        *p_tgl_dev;  
    
    /** \brief I2C handle */
    am_spi_handle_t         handle;
    
    /* 
     * Ametal transfer structure definition, 
     * get aw_transfer_t information, make transfer for SPI driver 
     */
    struct am_spi_transfer  ametal_transfer;

    /*
     * Ametal configure information structure definition, 
     * get user need configure information, and reconfigure 
     */
    struct am_spi_cfg_info  ametal_cfg_info;

} awbl_ametal_spi_dev_t;
 

/**
 * \brief AMETAL SPI master driver register
 */
void awbl_ametal_spi_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_AMETAL_SPI_H */

/* end of file */
