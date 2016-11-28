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
 * \brief Buzzer driver.
 *
 * \internal
 * \par modification history
 * - 1.01 14-11-01  ops, redefine the abstract buzzer by using new specification.
 * - 1.00 13-03-08  orz, first implementation.
 * \endinternal
 */

#ifndef __AWBL_BUZZER_H
#define __AWBL_BUZZER_H

#include "aw_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup awbl_buzzer
 * @{
 */

/** \brief buzzer device */
struct awbl_buzzer_dev {
    void (*beep) (struct awbl_buzzer_dev *p_dev, bool_t on);
    aw_err_t (*loud_set) (struct awbl_buzzer_dev *p_dev, int level);
};

/******************************************************************************/
void awbl_buzzer_register_device (struct awbl_buzzer_dev *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_BUZZER_H */

/* end of file */
