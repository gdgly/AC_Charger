/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ������(touch screen)�м��
 *
 * \internal
 * \par modification history
 * - 1.01 14-09-12  ops, add algorithm operator for ts_dev.
 * - 1.00 14-07-25  ops, first implementation.
 * \endinternal
 */
#ifndef AWBL_TOUCH_SCREEN_H_
#define AWBL_TOUCH_SCREEN_H_

#include "apollo.h"
#include "awbus_lite.h"
#include "aw_touch_screen.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ����ϵͳ����״̬�� */
#define AW_TOUCH_STATE_MACHINE_IDLE       0     /* ����̬ */
#define AW_TOUCH_STATE_MACHINE_START      1     /* ��������̬ */
#define AW_TOUCH_STATE_MACHINE_COMPLETE   2     /* ��ȫ����̬ */

/** \brief touch screen device */
typedef struct awbl_ts_dev {

	void (*__ts_dev_touch_lock) (struct awbl_ts_dev *tdev, bool_t lock);
	void (*__ts_dev_touch_active_x)(struct awbl_ts_dev *tdev);
	void (*__ts_dev_touch_active_y)(struct awbl_ts_dev *tdev);
    void (*__ts_dev_touch_measure_x)(struct awbl_ts_dev *tdev, uint16_t *sample, int count);
    void (*__ts_dev_touch_measure_y)(struct awbl_ts_dev *tdev, uint16_t *sample, int count);

}awbl_ts_dev_t;

/** \brief touch screen ע�ắ�� */
void awbl_ts_register_device(struct awbl_ts_dev *dev);

#ifdef __cplusplus
}
#endif


#endif /* AWBL_TOUCH_SCREEN_H_ */
