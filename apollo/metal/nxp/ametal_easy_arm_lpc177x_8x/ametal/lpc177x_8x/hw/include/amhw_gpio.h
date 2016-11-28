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
 * \brief GPIO 硬件操作接口
 * 
 * 1. GPIO 引脚能够通过软件配置为输入输出；
 * 2. 所有GPIO 引脚默认为上拉输入，在复位时中断禁能；
 * 3. 引脚寄存器允许引脚单独配置或多个同时配置。
 *
 * \internal
 * \par Modification history
 * - 1.00 15-04-23  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_GPIO_H
#define __AMHW_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 

/** 
 * \addtogroup amhw_if_gpio 
 * \copydoc amhw_gpio.h
 * @{
 */

/** 
 * \name GPIO 端口编号
 * @{
 */

#define AMHW_GPIO_PORT_0        0        /**< \brief 端口 0  */ 
#define AMHW_GPIO_PORT_1        1        /**< \brief 端口 1  */
#define AMHW_GPIO_PORT_2        2        /**< \brief 端口 2  */ 
#define AMHW_GPIO_PORT_3        3        /**< \brief 端口 3  */
#define AMHW_GPIO_PORT_4        4        /**< \brief 端口 4  */ 

/** @} */

/**
 * \name GPIO 引脚电平
 * @{
 */
 
#define AMHW_GPIO_LEVEL_LOW     0        /**< \brief 低电平 */
#define AMHW_GPIO_LEVEL_HIGH    1        /**< \brief 高电平 */

/** @} */

/*
 * \brief 匿名结构体段的开始
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \brief GPIO 寄存器块结构体
 */
typedef struct amhw_gpio {
  union {
    __IO uint32_t fiodir;     /**< \brief 高速GPIO端口方向控制寄存器                   */
    struct {
      __IO uint16_t fiodirl;  /**< \brief 高速GPIO端口x方向控制低半字寄存器  */
      __IO uint16_t fiodirh;  /**< \brief 高速GPIO端口x方向控制高半字寄存器  */
    };
    struct {
      __IO uint8_t  fiodir0;  /**< \brief 高速GPIO端口x方向控制寄存器0     */
      __IO uint8_t  fiodir1;  /**< \brief 高速GPIO端口x方向控制寄存器1     */
      __IO uint8_t  fiodir2;  /**< \brief 高速GPIO端口x方向控制寄存器2     */
      __IO uint8_t  fiodir3;  /**< \brief 高速GPIO端口x方向控制寄存器3     */
    };
  };
  uint32_t reserved0[3];      /**< \brief 保留                                                                           */
  union {
    __IO uint32_t fiomask;    /**< \brief 高速端口屏蔽寄存器                                         */
    struct {
      __IO uint16_t fiomaskl; /**< \brief 高速GPIO端口x屏蔽低半字寄存器              */
      __IO uint16_t fiomaskh; /**< \brief 高速GPIO端口x屏蔽高半字寄存器              */
    };
    struct {
      __IO uint8_t  fiomask0; /**< \brief 高速GPIO端口x屏蔽寄存器0          */
      __IO uint8_t  fiomask1; /**< \brief 高速GPIO端口x屏蔽寄存器1          */
      __IO uint8_t  fiomask2; /**< \brief 高速GPIO端口x屏蔽寄存器2          */
      __IO uint8_t  fiomask3; /**< \brief 高速GPIO端口x屏蔽寄存器3          */
    };
  };
  union {
    __IO uint32_t fiopin;    /**< \brief 高速端口引脚值寄存器  */
    struct {
      __IO uint16_t fiopinl; /**< \brief 高速GPIO端口x引脚值低半字寄存器     */
      __IO uint16_t fiopinh; /**< \brief 高速GPIO端口x引脚值高半字寄存器     */
    };
    struct {
      __IO uint8_t  fiopin0; /**< \brief 高速GPIO端口x引脚值寄存器0       */
      __IO uint8_t  fiopin1; /**< \brief 高速GPIO端口x引脚值寄存器1       */
      __IO uint8_t  fiopin2; /**< \brief 高速GPIO端口x引脚值寄存器2       */
      __IO uint8_t  fiopin3; /**< \brief 高速GPIO端口x引脚值寄存器3       */
    };
  };
  union {
    __IO uint32_t fioset;    /**< \brief 高速端口输出置位寄存器                             */
    struct {
      __IO uint16_t fiosetl; /**< \brief 高速GPIO端口x输出设置低半字寄存器  */
      __IO uint16_t fioseth; /**< \brief 高速GPIO端口x输出设置高半字寄存器  */
    };
    struct {
      __IO uint8_t  fioset0; /**< \brief 高速GPIO端口x输出设置寄存器0     */
      __IO uint8_t  fioset1; /**< \brief 高速GPIO端口x输出设置寄存器1     */
      __IO uint8_t  fioset2; /**< \brief 高速GPIO端口x输出设置寄存器2     */
      __IO uint8_t  fioset3; /**< \brief 高速GPIO端口x输出设置寄存器3     */
    };
  };
  union {
    __O  uint32_t fioclr;    /**< \brief 高速端口输出清零寄存器                              */
    struct {
      __O  uint16_t fioclrl; /**< \brief 高速GPIO端口x输出清零低半字寄存器  */
      __O  uint16_t fioclrh; /**< \brief 高速GPIO端口x输出清零高半字寄存器  */
    };
    struct {
      __O  uint8_t  fioclr0; /**< \brief 高速GPIO端口x输出清零寄存器0     */
      __O  uint8_t  fioclr1; /**< \brief 高速GPIO端口x输出清零寄存器1     */
      __O  uint8_t  fioclr2; /**< \brief 高速GPIO端口x输出清零寄存器2     */
      __O  uint8_t  fioclr3; /**< \brief 高速GPIO端口x输出清零寄存器3     */
    };
  };
} amhw_gpio_t;

/**
 * \brief 设置GPIO引脚方向为输出
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin_num   : 端口的引脚编号，0 ~ 31
 *
 * \return    无
 */
am_static_inline 
void amhw_gpio_pin_dir_output (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    p_hw_gpio->fiodir |= (1UL << (pin_num & 0x1F));
}

/**
 * \brief 设置GPIO引脚方向为输入
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin_num   : 端口的引脚编号，0 ~ 31
 *
 * \return    无
 */
am_static_inline 
void amhw_gpio_pin_dir_input (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    p_hw_gpio->fiodir  &= ~(1UL << (pin_num & 0x1F));
}

/**
 * \brief 获取指定引脚的方向
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin_num   : 端口的引脚编号，0 ~ 31
 *
 * \retval  0  : 输入
 * \retval  1  : 输出
 */
am_static_inline
int amhw_gpio_pin_dir_get (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    return (((p_hw_gpio->fiodir & 
             (1UL << (pin_num & 0x1F))) != 0) ? 1 : 0);
}

/**
 * \brief 设置GPIO端口的掩码值，用于端口的读和写
 *
 *  该值影响对端口的读和写(置位和清零).写0时，使能读和写；写1时，写入该位的值被忽略，读时始终为0.
 *
 * \param[in] p_hw_gpio  : 指向GPIO寄存器块的指针
 * \param[in] mask_value : 掩码值，可用于读和写
 * 
 * \return    无
 */
am_static_inline 
void amhw_gpio_mask_set (amhw_gpio_t *p_hw_gpio, 
                         uint32_t     mask_value)
{
    p_hw_gpio->fiomask = mask_value;
}

/**
 * \brief 获取GPIO指定端口的掩码值
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] port      : 端口编号，值为 AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 *
 * \return    端口的掩码值
 */
am_static_inline 
uint32_t amhw_gpio_mask_get (amhw_gpio_t *p_hw_gpio, int port)
{
    return p_hw_gpio->fiomask;
}

/**
 * \brief 获取引脚的电平状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin_num   : 端口的引脚编号，0 ~ 31
 *
 * \retval  0  : 低电平
 * \retval  1  : 高电平
 */
am_static_inline 
int amhw_gpio_pin_get (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    return (((p_hw_gpio->fiopin & 
             (1UL << (pin_num & 0x1F))) != 0) ? 1 : 0);
}

/**
 * \brief 设置指定端口的所有GPIO引脚的状态（与掩码有关）
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] value     : 设置在该端口的value值
 *
 * \return 无
 */
am_static_inline 
void amhw_gpio_port_set (amhw_gpio_t *p_hw_gpio, uint32_t value)
{
    p_hw_gpio->fiopin = value;
}

/**
 * \brief 获取指定端口的所有GPIO引脚的状态（与掩码有关）
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \return 端口的引脚状态
 */
am_static_inline 
uint32_t amhw_gpio_port_get (amhw_gpio_t *p_hw_gpio)
{
    return p_hw_gpio->fiopin;
}

/**
 * \brief 设置GPIO引脚输出高电平
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin_num   : 端口的引脚编号，0 ~ 31
 *
 * \return 无
 *
 * \note 该功能仅限于已设置为输出的引脚
 */
am_static_inline 
void amhw_gpio_pin_out_high (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    p_hw_gpio->fioset = (1UL << (pin_num & 0x1F));
}

/**
 * \brief 设置GPIO引脚输出低电平
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin_num   : 端口的引脚编号，0 ~ 31
 *
 * \return    无
 *
 * \note 该功能仅限于已设置为输出的引脚
 */
am_static_inline 
void amhw_gpio_pin_out_low (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    p_hw_gpio->fioclr = (1UL << (pin_num & 0x1F));
}

/**
 * \brief 翻转GPIO输出引脚的电平状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin_num   : 端口的引脚编号，0 ~ 31
 *
 * \return 无
 *
 * \note 该功能仅限于已设置为输出的引脚
 */
am_static_inline 
void amhw_gpio_pin_toggle (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    if (amhw_gpio_pin_get(p_hw_gpio,pin_num) == 0) {
        amhw_gpio_pin_out_high(p_hw_gpio,pin_num);
    } else {
        amhw_gpio_pin_out_low(p_hw_gpio,pin_num);
    }
}

/*
 * \brief 匿名结构体段的结束
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/**
 * @} amhw_if_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_GPIO_H */

/* end of file */
