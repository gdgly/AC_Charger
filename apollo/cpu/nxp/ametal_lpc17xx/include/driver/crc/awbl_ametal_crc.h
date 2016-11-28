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
 * \brief Ametal ϵ�� CRC ����
 *
 * \par 1.������Ϣ
 *
 *  - ������:  "ametal_crc"
 *  - ��������: AWBL_BUSID_PLB
 *  - �豸��Ϣ: struct awbl_ametal_crc_param
 *
 * \par 2.�����豸
 *
 *  - ʹ�ñ�׼����ӿڵ��豸
 *
 * \par 3.�豸����/����
 *
 *  - \ref grp_awbl_drv_crc_hwconf
 *
 * \par 4.�û��ӿ�
 *
 *  - \ref grp_aw_serv_hwtimer
 *
 * \internal
 * \par modification history
 * - 1.00 14-08-20  tee, first implementation
 * \endinternal
 */

#ifndef __AWBL_AMETAL_CRC_H
#define __AWBL_AMETAL_CRC_H

#include "awbl_crc.h"
#include "am_crc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AWBL_AMETAL_CRC_NAME      "ametal_crc"

/** \brief The Pointer to the hardware initialize function */
typedef am_crc_handle_t (*pfunc_crc_init_t)(void *,const void *); 

/** \brief ametal timer initialization structure for plb based AWBus devices */
struct awbl_ametal_crc_param {
    
    /** \breif Pointer to the hardware dev    */
    void                            *p_hw_dev;   
    
    /** \breif Pointer to the hardware device information  */
    const void                      *p_hw_devinfo;
     
    /**< \brief Pointer to the hardware initialize function */
    pfunc_crc_init_t                 pfn_crc_init; 
    
    /** \brief BSP function to pre initialize the device    */
    void (*pfn_plfm_init)(void);
};

/** \brief ametal timer dev   */
struct awbl_ametal_crc_dev {
    struct awbl_dev                  dev;        /**< \brief awbl device data         */
    am_crc_handle_t                  handle;     /**< \brief The handle from hardware */
    
    /** \brief CRC �������غ��� */
    const struct awbl_crc_functions *p_servfuncs;

    bool_t                           isallocated;    
};

void awbl_ametal_crc_drv_register (void);

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_LPC11XX_TIMER_H */

/* end of file */
