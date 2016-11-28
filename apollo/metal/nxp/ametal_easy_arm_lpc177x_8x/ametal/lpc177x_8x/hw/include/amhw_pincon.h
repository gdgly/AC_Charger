/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 管脚连接(Pin connect)配置
 * 
 * \internal
 * \par Modification History
 * - 1.01 15-08-29  cod, added support Lpc177x_8x
 * - 1.00 15-04-23  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_PINCON_H
#define __AMHW_PINCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
    
 /** 
 * \addtogroup amhw_if_pincon
 * \copydoc amhw_pincon.h
 * @{
 */

/**
  * \brief LPC17xx PIN connect 寄存器块结构体
 */
typedef struct amhw_pincon {
    __IO uint32_t iocon[5][32];   /**< \brief 管脚配置寄存器                        */
} amhw_pincon_t;

/**
 * \name IOCON寄存器位偏移和掩码
 * @{
 */

#define AMHW_PINCON_FUNC_POS     0  /**< \brief IOCON寄存器功能位偏移值   */
#define AMHW_PINCON_MODE_POS     3  /**< \brief IOCON寄存器模式位偏移值   */
#define AMHW_PINCON_HYS_POS      5  /**< \brief IOCON寄存器迟滞位偏移值   */
#define AMHW_PINCON_INVERT_POS   6  /**< \brief IOCON寄存器输入极性位偏移值   */
#define AMHW_PINCON_ADMODE_POS   7  /**< \brief IOCON寄存器AD模式位偏移值   */
#define AMHW_PINCON_FILTER_POS   8  /**< \brief IOCON寄存器FILTER位偏移值   */
#define AMHW_PINCON_HS_POS       8  /**< \brief IOCON寄存器HS位偏移值   */
#define AMHW_PINCON_SLEW_POS     9  /**< \brief IOCON寄存器SLEW位偏移值   */
#define AMHW_PINCON_HIDRIVE_POS  9  /**< \brief IOCON寄存器HIDRIVE位偏移值   */
#define AMHW_PINCON_OD_POS       10 /**< \brief IOCON寄存器开漏模式位偏移值   */
#define AMHW_PINCON_DACEN_POS    16 /**< \brief IOCON寄存器DAC使能位偏移值   */

#define AMHW_PINCON_FUNC_MASK   (0x07 << 0)   /**< \brief IOCON功能位掩码   */
#define AMHW_PINCON_MODE_MASK   (0x03 << 3)   /**< \brief IOCON模式位掩码   */

/** @} */

/**
 * \name 管脚功能定义
 * @{
 */
#define AMHW_PINCON_SEL_FUNC0    0    /**< \brief 功能0，通常为GPIO       */
#define AMHW_PINCON_SEL_FUNC1    1    /**< \brief 复用功能1               */
#define AMHW_PINCON_SEL_FUNC2    2    /**< \brief 复用功能2               */
#define AMHW_PINCON_SEL_FUNC3    3    /**< \brief 复用功能3               */
#define AMHW_PINCON_SEL_FUNC4    4    /**< \brief 复用功能4               */
#define AMHW_PINCON_SEL_FUNC5    5    /**< \brief 复用功能5               */
#define AMHW_PINCON_SEL_FUNC6    6    /**< \brief 复用功能6               */
#define AMHW_PINCON_SEL_FUNC7    7    /**< \brief 复用功能7               */

/** @} */

/**
 * \brief Pin connect功能设置(决定管脚的功能)
 *
 * \param[in] p_hw_pincon : 指向PINCON寄存器块的指针
 * \param[in] port        : 端口号   ：0 ~ 4,若为LPC177X_8X,端口号：0~5
 * \param[in] pin_num     : 引脚编号 : 0 ~ 31,,若为LPC177X_8X,端口5编号只有0~4
 * \param[in] func_sel    : 功能选择，使用宏值：AMHW_PINCON_SEL_FUNC*(#AMHW_PINCON_SEL_FUNC0)
 *
 * \return 无
 */
am_static_inline
void amhw_pincon_sel_cfg (amhw_pincon_t *p_hw_pincon,
                          uint8_t        port,
                          uint8_t        pin_num,
                          uint8_t        func_sel)
{
    p_hw_pincon->iocon[port][pin_num] = \
        (p_hw_pincon->iocon[port][pin_num] & (~AMHW_PINCON_FUNC_MASK)) | \
        (func_sel & AMHW_PINCON_FUNC_MASK);

}


/**
 * \name 管脚模式定义
 * @{
 */

#define AMHW_PINCON_MODE_FLOAT     0     /**< \brief 浮空模式                     */
#define AMHW_PINCON_MODE_PULLDOWN  1     /**< \brief 下拉模式                      */
#define AMHW_PINCON_MODE_PULLUP    2     /**< \brief 上拉模式                      */
#define AMHW_PINCON_MODE_REPEATER  3     /**< \brief 中继模式                    */

/** @} */

/**
 * \brief Pin connect模式设置(决定管脚的模式)
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 * \param[in] mode         : 模式选择，使用宏值：
 *                           AMHW_PINCON_MODE_*(#AMHW_PINCON_MODE_PULLUP)
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_mode_cfg (amhw_pincon_t *p_hw_pincon,
                           uint8_t        port,
                           uint8_t        pin_num,
                           uint8_t        mode)
{
    p_hw_pincon->iocon[port][pin_num] = \
            (p_hw_pincon->iocon[port][pin_num] & (~AMHW_PINCON_MODE_MASK)) | \
            ((mode << AMHW_PINCON_MODE_POS) & AMHW_PINCON_MODE_MASK);

}

/**
 * \brief 管脚迟滞模式使能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_hys_enable (amhw_pincon_t     *p_hw_pincon,
                             uint8_t            port,
                             uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_HYS_POS);
}

/**
 * \brief 管脚迟滞模式失能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_hys_disable (amhw_pincon_t     *p_hw_pincon,
                              uint8_t            port,
                              uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_HYS_POS);
}

/**
 * \brief 管脚输入反向使能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_invert_enable (amhw_pincon_t     *p_hw_pincon,
                                uint8_t            port,
                                uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_INVERT_POS);
}

/**
 * \brief 管脚输入反向禁能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_invert_disable (amhw_pincon_t *p_hw_pincon,
                                 uint8_t        port,
                                 uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_INVERT_POS);
}

/**
 * \brief 管脚AD模式设置为模拟模式
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_admode_analog (amhw_pincon_t *p_hw_pincon,
                                uint8_t        port,
                                uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_ADMODE_POS);
}

/**
 * \brief 管脚AD模式设置为数字模式
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_admode_digital (amhw_pincon_t     *p_hw_pincon,
                                 uint8_t            port,
                                 uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_ADMODE_POS);
}

/**
 * \brief 管脚毛刺滤波器过滤（低于10ns的噪声脉冲被过滤  ）
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_filter_enable (amhw_pincon_t *p_hw_pincon,
                                uint8_t        port,
                                uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_FILTER_POS);
}

/**
 * \brief 管脚毛刺滤波器失能（不进行输入过滤 ）
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_filter_disable (amhw_pincon_t *p_hw_pincon,
                                 uint8_t        port,
                                 uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_FILTER_POS);
}

/**
 * \brief 管脚驱动器转换速率使能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4
 *
 * \return    无
 *
 * \note 标准模式下，输出转换速率控制使能
 */
am_static_inline
void amhw_pincon_slew_enable (amhw_pincon_t     *p_hw_pincon,
                              uint8_t            port,
                              uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_SLEW_POS);
}

/**
 * \brief 管脚驱动器转换速率禁能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4
 *
 * \return    无
 *
 * \note 高速模式下，输出转换速率控制禁能
 */
am_static_inline
void amhw_pincon_slew_disable (amhw_pincon_t     *p_hw_pincon,
                              uint8_t            port,
                              uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_SLEW_POS);
}

/**
 * \brief 管脚开漏使能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_od_enable (amhw_pincon_t *p_hw_pincon,
                            uint8_t        port,
                            uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_OD_POS);
}

/**
 * \brief 管脚开漏失能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 */
am_static_inline
void amhw_pincon_od_disable (amhw_pincon_t *p_hw_pincon,
                             uint8_t        port,
                             uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_OD_POS);
}

/**
 * \brief 管脚I2C 50ns毛刺滤波器及转换速率控制使能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 *
 * \note 该设置只对PIO0.27、PIO0.28、PIO5.2、PIO5.3有效
 */
am_static_inline
void amhw_pincon_i2cfilter_enable (amhw_pincon_t     *p_hw_pincon,
                                   uint8_t            port,
                                   uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_HS_POS);
}

/**
 * \brief 管脚I2C 50ns毛刺滤波器及转换速率控制失能
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 *
 * \note 该设置只对PIO0.27、PIO0.28、PIO5.2、PIO5.3有效
 */
am_static_inline
void amhw_pincon_i2cfilter_disable (amhw_pincon_t     *p_hw_pincon,
                                   uint8_t            port,
                                   uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_HS_POS);
}

/**
 * \brief 管脚输出驱动灌电流能力4mA
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 *
 * \note 该功能只针对管脚PIO5_2和PIO5_3.
 */
am_static_inline
void amhw_pincon_hidrive_4ma (amhw_pincon_t *p_hw_pincon,
                              uint8_t        port,
                              uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_HIDRIVE_POS);
}

/**
 * \brief 管脚输出驱动灌电流能力20mA
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 *
 * \return    无
 *
 * \note 该功能只针对管脚PIO5_2和PIO5_3.
 */
am_static_inline
void amhw_pincon_hidrive_20ma (amhw_pincon_t *p_hw_pincon,
                               uint8_t        port,
                               uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_HIDRIVE_POS);
}



/**
 * \name I2C管脚模式
 * @{
 */

#define AMHW_PINCON_I2CMODE_FAST_STANDARD   0    /**< \brief 标准模式/FM模式            */
#define AMHW_PINCON_I2CMODE_OPENDRAINIO     1    /**< \brief 开漏模式(非I2C模式) */
#define AMHW_PINCON_I2CMODE_FASTMODEPLUS    2    /**< \brief I2C FM+模式                      */
/** @} */

/**
 * \brief 设置管脚I2C模式
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 * \param[in] port         : 端口号   ：0 ~ 5
 * \param[in] pin_num      : 引脚编号 : 0 ~ 31, 端口为5时,编号为0~4.
 * \param[in] mode         : I2C模式选择，值为(#AMHW_PINCON_I2CMODE_FAST_STANDARD)或
 *                          (#AMHW_PINCON_I2CMODE_OPENDRAINIO)或
 *                          (#AMHW_PINCON_I2CMODE_FASTMODEPLUS)
 *
 * \return    无
 */
void amhw_pincon_i2cmode_set (amhw_pincon_t *p_hw_pincon,
                             uint8_t        port,
                             uint8_t        pin_num,
                             uint8_t        mode);

/**
 * \brief DAC使能（管脚PIO0_26）
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 *
 * \return 无
 *
 */
am_static_inline
void amhw_pincon_dac_enable (amhw_pincon_t *p_hw_pincon)
{
    p_hw_pincon->iocon[0][26] |= (1 << AMHW_PINCON_DACEN_POS);
}

/**
 * \brief DAC禁能（管脚PIO0_26）
 *
 * \param[in] p_hw_pincon  : 指向PINCON寄存器块的指针
 *
 * \return    无
 *
 */
am_static_inline
void amhw_pincon_dac_disable (amhw_pincon_t *p_hw_pincon)
{
    p_hw_pincon->iocon[0][26] &= ~(1 << AMHW_PINCON_DACEN_POS);
}


/**
 * @} amhw_if_pincon
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_PINCON_H */

/* end of file */
