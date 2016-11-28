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
 * \brief AWBus IMX283оƬ�ڲ����Ź��ӿ�ͷ�ļ�
 *
 * ʹ�ñ�ģ����Ҫ��������ͷ�ļ���
 * \code
 * #include "awbl_imx283_wdt.h"
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 14-08-27  may, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX283_WDT_H
#define __AWBL_IMX283_WDT_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


/*******************************************************************************
  includes
*******************************************************************************/
#include "apollo.h"
#include "awbus_lite.h"
#include "awbl_wdt.h"


/*******************************************************************************
  define
*******************************************************************************/

/** \brief  ����IMX283���Ź������� */
#define  IMX283_WDT_NAME  "imx283-wdt"

/** \brief ����IMX283���Ź�ʱ����Ϣ */
struct  imx283_wdt_param {
    uint32_t    reg_base;       /**< RTC register base address*/
    uint32_t    wdt_time;       /**< \brief watchdog time (ms)*/
};

/** \brief ����IMX283���Ź��豸 */
struct  imx283_wdt_device {
    struct awbl_dev          dev;    /**< the AWBus device */
    struct awbl_hwwdt_info   info;   /**< hwwdt info */
    uint32_t                 reg_base;
};

/**
 * \brief IMX283 wdt driver register
 */
void  awbl_imx283_wdt_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_IMX283_WDT_H */
