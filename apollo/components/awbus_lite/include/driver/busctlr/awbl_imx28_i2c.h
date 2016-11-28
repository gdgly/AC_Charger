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
 * \brief Freescale i.MX28系列I2C外设驱动
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
 * \brief imx28 I2C 设备信息
 */
struct awbl_imx28_i2c_devinfo {

    /** \brief 继承自 AWBus I2C 控制器设备信息 */
    struct awbl_i2c_master_devinfo i2c_master_devinfo;

    uint32_t regbase;               /**< 寄存器基地址 */
    int      inum;                  /**< 中断号 */
    uint32_t clkfreq;               /**< 输入时钟频率 */
    void (*pfunc_plfm_init)(void);  /**< 平台相关初始化：开启时钟、初始化引脚 */
};


/**
 * \brief imx28 I2C 设备实例
 */
struct awbl_imx28_i2c_dev {

    /** \brief 继承自 AWBus I2C 主机控制器 */
    struct awbl_i2c_master  super;

    /** \brief 当前正在处理的 Message */
    struct aw_i2c_message *p_cur_msg;

    /** \brief 当前正在处理的 Transfer */
    struct aw_i2c_transfer *p_cur_trans;

    /** \brief 传输数据计数 */
    size_t      data_ptr;

    /** \brief 硬件每个传输过程的数据计数 */
    uint16_t    reg_data_ptr;

    /** \brief 控制器忙标志 */
    bool_t        busy;

    bool_t		stop_sent;

    /** \brief 控制器状态机状态  */
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
