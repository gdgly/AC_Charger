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
 * \brief Freescale i.MX28ϵ��I2C��������
 *
 * \internal
 * \par modification history:
 * - 1.00 14-05-08  wengyedong, first implemetation
 * \endinternal
 */

#ifndef __AWBL_IMX28_I2C_H
#define __AWBL_IMX28_I2C_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbl_i2cbus.h"
#include "aw_spinlock.h"

#define AWBL_IMX28_I2C_NAME            "imx28_i2c"

/**
 * \brief imx28 I2C �豸��Ϣ
 */
struct awbl_imx28_i2c_devinfo {

    /** \brief �̳��� AWBus I2C �������豸��Ϣ */
    struct awbl_i2c_master_devinfo i2c_master_devinfo;

    uint32_t regbase;               /**< �Ĵ�������ַ */
    int      inum;                  /**< �жϺ� */
    uint32_t clkfreq;               /**< ����ʱ��Ƶ�� */
    void (*pfunc_plfm_init)(void);  /**< ƽ̨��س�ʼ��������ʱ�ӡ���ʼ������ */
};


/**
 * \brief imx28 I2C �豸ʵ��
 */
struct awbl_imx28_i2c_dev {

    /** \brief �̳��� AWBus I2C ���������� */
    struct awbl_i2c_master  super;

    /** \brief ��ǰ���ڴ���� Message */
    struct aw_i2c_message *p_cur_msg;

    /** \brief ��ǰ���ڴ���� Transfer */
    struct aw_i2c_transfer *p_cur_trans;

    /** \brief �������ݼ��� */
    size_t      data_ptr;

    /** \brief Ӳ��ÿ��������̵����ݼ��� */
    uint16_t    reg_data_ptr;

    /** \brief ������æ��־ */
    bool_t        busy;

    bool_t		stop_sent;

    /** \brief ������״̬��״̬  */
    int         state;
};

/**
 * \brief imx28 I2C master driver register
 */
void awbl_imx28_i2c_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_IMX28_I2C_H_ */
