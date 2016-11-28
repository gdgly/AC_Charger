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


#ifndef __AWBL_AMETAL_WDT_H
#define __AWBL_AMETAL_WDT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_sem.h"
#include "awbus_lite.h"
#include "am_wdt.h"
#include "awbl_wdt.h"

#define AWBL_AMETAL_WDT_NAME               "ametal_wdt"

/*******************************************************************************
  types
*******************************************************************************/

/**< \brief The Pointer to the hardware initialize function */
typedef am_wdt_handle_t (*pfn_wdt_init_t)(void *,const void *); 


/** \brief ametal wdt initialization structure for plb based AWBus devices */
struct awbl_ametal_wdt_param {
    uint32_t                timeout_ms;  /**< \brief time out value in ms */ 
    void                   *p_hw_dev;    /**< \brief Pointer to the hardware dev    */
        
    /**< \breif Pointer to the hardware device information */
    const void             *p_hw_devinfo;
    
    /** \brief Pointer to the hardware initialize function */
    pfn_wdt_init_t          pfn_wdt_init; 
    
    /** \brief BSP function to pre initialize the device */
    void (*pfn_plfm_init)(void);
};

/** \brief ametal wwdt dev. one dev may contain multi chan.  */
struct awbl_ametal_wdt_dev {

    struct awbl_dev         dev;       /**< \brief awbl device data               */
    am_wdt_handle_t         handle;    /**< \brief The handle from hardware       */
	
	struct awbl_hwwdt_info  info;
};

void awbl_ametal_wdt_drv_register (void);


#ifdef __cplusplus
}
#endif

#endif /* __AWBL_AMETAL_WWDT_H */


/* end of file */
