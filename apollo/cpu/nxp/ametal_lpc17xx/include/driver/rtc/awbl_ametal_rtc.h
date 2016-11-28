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
 * - 1.00 14-01-09  fft, first implementation
 * \endinternal
 */


#ifndef __AWBL_AMETAL_RTC_H
#define __AWBL_AMETAL_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_sem.h"
#include "awbus_lite.h"
#include "awbl_rtc.h"
#include "am_rtc.h"

#define AWBL_AMETAL_RTC_NAME               "ametal_rtc"

/*******************************************************************************
  types
*******************************************************************************/

/** \brief The Pointer to the hardware initialize function */
typedef am_rtc_handle_t (*pfn_rtc_init_t)(void *,const void *); 

/** \brief ametal rtc initialization structure for plb based AWBus devices */
struct awbl_ametal_rtc_param {
    
    /** \brief RTC 服务配置信息 */
    struct awbl_rtc_servinfo  rtc_servinfo;  
   
    void                      *p_hw_dev;  /**< \brief Pointer to the hardware dev    */
    
    /** \breif Pointer to the hardware device information */
    const void                *p_hw_devinfo;
    
    /**< \brief Pointer to the hardware initialize function */
    pfn_rtc_init_t             pfn_rtc_init; 
    
    /** \brief BSP function to pre initialize the device */
    void (*pfn_plfm_init)(void);
};

/** \brief ametal rtc dev. one dev may contain multi chan.  */
struct awbl_ametal_rtc_dev {

    struct awbl_dev         dev;       /**< \brief awbl device data               */
    am_rtc_handle_t         handle;    /**< \brief The handle from hardware       */
	/** \brief RTC 服务 */
    struct awbl_rtc_service rtc_serv;
    AW_MUTEX_DECL(devlock);
};

void awbl_ametal_rtc_drv_register (void);


#ifdef __cplusplus
}
#endif

#endif /* __AWBL_AMETAL_RTC_H */


/* end of file */
