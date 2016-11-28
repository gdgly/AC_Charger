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
 * \brief AWBus AMETAL I2C driver file
 *
 * \internal
 * \par modification history:
 * - 1.00 14-09-20  jon, first implementation
 * \endinternal
 */

#ifndef __AWBL_AMETAL_I2C_H
#define __AWBL_AMETAL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#include "aw_spinlock.h"
#include "awbl_i2cbus.h"
#include "amdr_i2c.h"
#include "am_i2c.h"

#define AWBL_AMETAL_I2C_NAME   "ametal_i2c"


typedef am_i2c_handle_t (*pfn_i2c_init_t)(void *, const void *);
/**
 * \brief AMETAL I2C device information 
 */
typedef struct awbl_ametal_i2c_devinfo {
    
    /** \brief 继承自 AWBus I2C 控制器设备信息 */
    struct awbl_i2c_master_devinfo  i2c_master_devinfo;
    
    /** \breif Pointer to the hardware dev    */
    void                           *p_hw_dev;   
    
    /** \breif Pointer to the hardware device information  */
    const void                     *p_hw_devinfo;
    
    /**< \brief Pointer to the hardware initialize function */
    pfn_i2c_init_t                  pfn_i2c_init;
   
    /** \brief BSP function to pre initialize the device */
    void (*pfn_plfm_init)(void);
    
} awbl_ametal_i2c_devinfo_t;

/**
 * \brief AMETAL I2C device instantiation
 */
typedef struct awbl_ametal_i2c_dev {

    /** \brief inherit from AWBus I2C master controller */
    struct awbl_i2c_master   super;

    /** \brief The current Message */
    struct aw_i2c_message   *p_cur_msg;

    /** \brief The current Transfer */
    struct aw_i2c_transfer  *p_cur_trans;

    /** \brief Transfer counter */
    size_t                   data_ptr;

    /** \brief Controller busy flag */
    bool_t                   busy;

    /** \brief Controller status  */
    int                      state;
    
    /** \brief I2C handle */
    am_i2c_handle_t          handle;
    
    /** \brief Ametal transfer structure definition, make transfer for I2C driver */
    am_i2c_transfer_t        transfer;
    
}awbl_ametal_i2c_dev_t;


/**
 * \brief AMETAL I2C master driver register
 */
void awbl_ametal_i2c_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_AMETAL_I2C_H */

/* end of file */
