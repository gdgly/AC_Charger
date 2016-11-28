/*******************************************************************************
*                                 Apollo
*                       ---------------------------
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
 * \brief LPC17xx EEPROM driver
 *
 * \internal
 * \par modification history:
 * - 1.00 15-12-28  cod, first implementation
 * \endinternal
 */

#ifndef __AWBL_LPC17XX_EEPROM_H
#define __AWBL_LPC17XX_EEPROM_H

#include "awbus_lite.h"
#include "awbl_nvram.h"
#include "aw_sem.h"
#include "amdr_eeprom.h"

#ifdef __cplusplus
extern "C" {
#endif


#define AWBL_LPC17XX_EEPROM_NAME   "lpc17xx_eeprom"

/** \brief LPC17xx EEPROM 初始化函数类型 */
typedef int (*pfunc_eeprom_init_t) (void *, void *);

/**
 * \brief LPC17xx EEPROM 设备信息
 */
typedef struct awbl_lpc17xx_eeprom_param {

    /** \brief 非易失性存储段配置列表 */
    const struct awbl_nvram_segment *p_seglst;

    /** \brief 非易失性存储段配置列表条目数 */
    size_t                           seglst_count;

	/** \brief LPC17xx EEPROM 设备 */
    struct amdr_eeprom_dev          *p_dev;

    /** \brief LPC17xx EEPROM 设备信息 */
    struct amdr_eeprom_devinfo      *p_devinfo;

    /** \brief EEPROM 初始化函数 */
    pfunc_eeprom_init_t              pfunc_eeprom_init;

} awbl_lpc17xx_eeprom_param_t;

/**
 * \brief lpc17xx EEPROM设备实例
 */
typedef struct awbl_lpc17xx_eeprom_dev {

    /** \brief 继承自 AWBus 设备 */
    struct awbl_dev super;

    AW_SEMB_DECL(program_ok_semb);

} awbl_lpc17xx_eeprom_dev_t;

/*****************************************************************************/

void awbl_lpc17xx_eeprom_drv_register(void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_LPC17XX_EEPROM_H */

/* end of file */


