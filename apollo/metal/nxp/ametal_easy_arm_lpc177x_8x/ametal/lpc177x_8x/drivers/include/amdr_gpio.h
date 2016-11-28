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
 * \brief GPIO驱动，服务GPIO标准接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-5-08  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_GPIO_H
#define __AMDR_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"  
#include "am_bitops.h"
#include "lpc177x_8x_pin.h"

#include "amhw_gpio.h"
#include "amhw_pincon.h"
#include "amhw_gpioint.h"
    
/** 
 * \addtogroup amdr_if_gpio
 * \copydoc amdr_gpio.h
 * @{
 */

/**
 * \brief 引脚的触发信息 
 */
struct amdr_gpio_trigger_info {

    /** \brief 触发回调函数 */
    am_pfnvoid_t  pfn_callback;

    /** \brief 回调函数的参数 */
    void         *p_arg;
};

/**
 * \brief GPIO 设备信息
 */
typedef struct amdr_gpio_devinfo {
    
    /** \brief 指向GPIO寄存器块的基地址 */
    uint32_t       gpio_regbase;
    
    /** \brief 指向IOCON寄存器块的指针 */
    amhw_pincon_t  *p_hw_pincon;

    /** \brief 指向引脚中断寄存器块的指针 */
    amhw_gpioint_t *p_hw_gpioint;

    /** \brief GPIO引脚中断号，与EXTINT3共享中断号 */
    int8_t         gpioint_inum;

    /** 
     * \brief GPIO引脚中断号数量,仅PORT0和PORT2支持中断，该值最大为64
     *        请根据实际用到中断数量设置该值，
     */
    size_t         gpioint_count;

    /** \brief 指向引脚触发信息的指针,大小应该与pint_count一致 */
    struct amdr_gpio_trigger_info *p_triginfo;
    
} amdr_gpio_devinfo_t;

/**
 * \brief GPIO设备
 */
typedef struct amdr_gpio_dev {
    
    /** \brief 指向GPIO设备信息的指针 */
    const amdr_gpio_devinfo_t *p_devinfo;

    /** \brief 触发信息映射 */
    uint8_t                    infomap[AWBL_GPIOPIN_COUNT_MAX];
    
    /** \brief 触发状态保存 */
    uint8_t                    trig_state[AWBL_GPIOPIN_COUNT_MAX];
    
} amdr_gpio_dev_t;

/**
 * \brief GPIO初始化 
 *
 * \param[in] p_dev     : 指向GPIO设备的指针 
 * \param[in] p_devinfo : 指向GPIO设备信息的指针 
 *
 * \retval AM_OK : 操作成功 
 */
int amdr_gpio_init(amdr_gpio_dev_t           *p_dev, 
                   const amdr_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIO解初始化
 *
 * \param[in] p_dev : 指向GPIO设备的指针 
 *
 * \return 无 
 */
void amdr_gpio_deinit(amdr_gpio_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_GPIO_H */

/* end of file */
