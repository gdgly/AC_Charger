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
 * \brief ametal DAC
 *
 * \internal
 * \par modification history:
 * - 1.00 2015-09-08 anu, first implementation
 * \endinternal
 */

#ifndef __AWBL_AMETAL_DAC_H
#define __AWBL_AMETAL_DAC_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#include "awbl_dac.h"
#include "aw_spinlock.h"
#include "aw_isr_defer.h"

#include "am_dac.h"

/** \brief DAC ������ */
#define AWBL_AMETAL_DAC_NAME   "ametal_dac"

typedef am_dac_handle_t (*pfunc_dac_init_t)(void *, void *);

/*******************************************************************************
    defines
*******************************************************************************/

/**
 * \brief ametal DAC �豸��Ϣ
 */
typedef struct awbl_ametal_dac_param {
    
    /** \brief Ӳ������豸 */
    void *p_hw_dev;
    
    /** \brief Ӳ������豸��Ϣ */
    const void *p_hw_devinfo;
    
    /** \brief DAC ���������Ϣ */
    struct awbl_dac_servinfo dac_servinfo;
    
    /** \brief DAC ��ʼ������ */
    pfunc_dac_init_t pfunc_dac_init;

    /** \brief BSP function to pre initialize the device */
    void (*pfunc_plfm_init) (void);
    
} awbl_ametal_dac_param_t;


/**
 * \brief ametal DAC �豸ʵ��
 */
typedef struct awbl_ametal_dac_dev {

    /** \brief �̳��� AWBus �豸 */
    struct awbl_dev super;

    /** \brief DAC ���� */
    struct awbl_dac_service dac_serv;
     
    /** \brief handle */
    am_dac_handle_t handle;
    
} awbl_ametal_dac_dev_t;

/**
 * \brief ametal driver register
 */
void awbl_ametal_dac_drv_register(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_AMETAL_DAC_H */

/* end of file */
