/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief GPIO平台辅助工具宏
 *
 * 该文件被包含于 \sa lpc177x_8x_pin.h. 其定义了GPIO平台引脚的各个功能。
 *
 * \internal
 * \par Modification History
 * - 1.00 15-09-02  cod, first implementation.
 * \endinternal
 */

#ifndef __AMDR_GPIO_UTIL_H
#define __AMDR_GPIO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 


/** 
 * \addtogroup amdr_if_gpio_util
 * \copydoc amdr_gpio_util.h
 * @{
 */

/**
 * \name 使能位，10种设置对象，对应 bit[19 : 12]
 * @{
 */

/** \brief 功能设置使能位                                 */
#define AMDR_GPIO_FUNCEN_BIT      AM_BIT(12)
/** \brief 模式设置使能位                                  */
#define AMDR_GPIO_MODEEN_BIT      AM_BIT(13)
/** \brief 迟滞设置使能位                                 */
#define AMDR_GPIO_HYSEN_BIT       AM_BIT(14)
/** \brief DAC使能控制使能位                                 */
#define AMDR_GPIO_DACENEN_BIT     AM_BIT(14)
/** \brief 输入极性设置使能位                        */
#define AMDR_GPIO_INVERTEN_BIT    AM_BIT(15)
/** \brief 模拟/数字模式设置使能位           */
#define AMDR_GPIO_ADMODEEN_BIT    AM_BIT(16)
/** \brief I2C 50ns毛刺滤波器及转换速率设置使能位       */
#define AMDR_GPIO_HSEN_BIT        AM_BIT(17)
/** \brief 控制毛刺滤波器设置使能位         */
#define AMDR_GPIO_FILTEREN_BIT    AM_BIT(17)
/** \brief 驱动速率设置使能位                        */
#define AMDR_GPIO_SLEWEN_BIT      AM_BIT(18)
/** \brief 控制管脚灌电流能力设置使能位       */
#define AMDR_GPIO_HIDRIVEEN_BIT   AM_BIT(18)
/** \brief OD（开漏）设置 使能位                  */
#define AMDR_GPIO_ODEN_BIT        AM_BIT(19)

/** \brief 功能设置使能位是否是能              */
#define AMDR_GPIO_FUNCEN_ISSET(a)     ((a) & AMDR_GPIO_FUNCEN_BIT)
/** \brief 模式设置使能位是否是能                */
#define AMDR_GPIO_MODEEN_ISSET(a)     ((a) & AMDR_GPIO_MODEEN_BIT)
/** \brief 迟滞设置使能位是否是能                */
#define AMDR_GPIO_HYSEN_ISSET(a)      ((a) & AMDR_GPIO_HYSEN_BIT)
/** \brief DAC使能设置使能位是否是能                */
#define AMDR_GPIO_DACENEN_ISSET(a)      ((a) & AMDR_GPIO_DACENEN_BIT)
/** \brief 输入极性设置使能位是否是能                */
#define AMDR_GPIO_INVERTEN_ISSET(a)   ((a) & AMDR_GPIO_INVERTEN_BIT)
/** \brief 模拟/数字模式使能位是否是能                */
#define AMDR_GPIO_ADMODEEN_ISSET(a)   ((a) & AMDR_GPIO_ADMODEEN_BIT)
/** \brief 控制毛刺滤波器设置使能位是否是能                */
#define AMDR_GPIO_FILTEREN_ISSET(a)   ((a) & AMDR_GPIO_FILTEREN_BIT)
/** \brief I2C毛刺滤波器及转换速率设置使能位是否是能                */
#define AMDR_GPIO_HSEN_ISSET(a)       ((a) & AMDR_GPIO_HSEN_BIT)
/** \brief 驱动速率设置使能位是否是能                */
#define AMDR_GPIO_SLEWEN_ISSET(a)     ((a) & AMDR_GPIO_SLEWEN_BIT)
/** \brief 控制管脚灌电流能力设置使能位是否是能                */
#define AMDR_GPIO_HIDRIVEEN_ISSET(a)  ((a) & AMDR_GPIO_HIDRIVEEN_BIT)
/** \brief OD（开漏）设置 使能位是否是能         */
#define AMDR_GPIO_ODEN_ISSET(a)       ((a) & AMDR_GPIO_ODEN_BIT)

/** @} */

/**
 * \name 功能码，对应 bit[23 : 20]
 *
 * bit[22 : 20] 表示功能，GPIO功能、复用功能1~7
 * bit[23]      表示功能为GPIO时的方向
 *
 * @{
 */

#define AMDR_GPIO_FUNCBITS_START         20           /**< \brief 功能起始位   */
#define AMDR_GPIO_FUNCBITS_LEN           3            /**< \brief 功能码长度   */

/** \brief 置功能码 */
#define AMDR_GPIO_FUNCBITS_CODE(a)      (AM_SBF((a), AMDR_GPIO_FUNCBITS_START) |  \
                                         AMDR_GPIO_FUNCEN_BIT)
/** \brief 方向位偏移 */
#define AMDR_GPIO_DIRBIT_OFFSET          23

/** \brief GPIO输入*/
#define AMDR_GPIO_FUNC_INPUT_VAL         0
/** \brief GPIO输出 */
#define AMDR_GPIO_FUNC_OUTPUT_VAL        1

/** \brief 置方向码 */
#define AMDR_GPIO_DIR_CODE(a)           (AM_SBF((a), AMDR_GPIO_DIRBIT_OFFSET))


/** \brief 获取功能码 */
#define AMDR_GPIO_FUNC_GET(data)         AM_BITS_GET((data), AMDR_GPIO_FUNCBITS_START, \
                                         AMDR_GPIO_FUNCBITS_LEN)

/** \brief 获取方向码 */
#define AMDR_GPIO_DIR_GET(data)          AM_BIT_GET((data), AMDR_GPIO_DIRBIT_OFFSET)

/** \brief 设置功能的时候同时设定方向为输入（仅功能为GPIO时有效）*/
#define AMDR_GPIO_FUNC_INPUT(a) \
        (AMDR_GPIO_FUNCBITS_CODE(a) | \
         AMDR_GPIO_DIR_CODE(AMDR_GPIO_FUNC_INPUT_VAL))


/** \brief 设置功能的时候同时设定方向为输出 （仅功能为GPIO时有效）*/
#define AMDR_GPIO_FUNC_OUTPUT(a) \
        (AMDR_GPIO_FUNCBITS_CODE(a) | \
         AMDR_GPIO_DIR_CODE(AMDR_GPIO_FUNC_OUTPUT_VAL))

/** @} */

/**
 * \name 模式码，对应 bit[25 : 24]
 * @{
 */

/** \brief 模式起始位 */
#define AMDR_GPIO_MODEBITS_START         24

/** \brief 模式码长度 */
#define AMDR_GPIO_MODEBITS_LEN           2

/** \brief 设置模式码 */
#define AMDR_GPIO_MODE_CODE(a)          (AM_SBF((a), AMDR_GPIO_MODEBITS_START) | \
                                         AMDR_GPIO_MODEEN_BIT)

/** \brief 获取模式码 */
#define AMDR_GPIO_MODE_GET(data)        AM_BITS_GET((data), \
                                                    AMDR_GPIO_MODEBITS_START, \
                                                    AMDR_GPIO_MODEBITS_LEN)
/** @} */


/**
 * \name 迟滞模式控制，对应 bit[26]
 * @{
 */

/** \brief 迟滞模式位偏移 */
#define AMDR_GPIO_HYSBIT_OFFSET          26

/** \brief 迟滞模式失能值*/
#define AMDR_GPIO_HYSBIT_DISABLE_VAL     0
/** \brief 迟滞模式使能值 */
#define AMDR_GPIO_HYSBIT_ENABLE_VAL      1

/** \brief 迟滞模式位码 */
#define AMDR_GPIO_HYSBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_HYSBIT_OFFSET) | \
            AMDR_GPIO_HYSEN_BIT)

/** \brief 获取迟滞模式位码 */
#define AMDR_GPIO_HYSBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_HYSBIT_OFFSET)

/** \brief 迟滞模式失能*/
#define AMDR_GPIO_HYSENBIT_DISABLE  \
          AMDR_GPIO_HYSBIT_CODE(AMDR_GPIO_HYSBIT_DISABLE_VAL)

/** \brief 迟滞模式使能 */
#define AMDR_GPIO_HYSENBIT_ENABLE \
          AMDR_GPIO_HYSBIT_CODE(AMDR_GPIO_HYSBIT_ENABLE_VAL)

/** @} */

/**
 * \name DAC使能控制，对应 bit[26]
 * @{
 */

/** \brief DAC使能位偏移 */
#define AMDR_GPIO_DACENBIT_OFFSET          26

/** \brief DAC使能失能值*/
#define AMDR_GPIO_DACENBIT_DISABLE_VAL     0
/** \brief DAC使能使能值 */
#define AMDR_GPIO_DACENBIT_ENABLE_VAL      1

/** \brief DAC使能位码 */
#define AMDR_GPIO_DACENBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_DACENBIT_OFFSET) | \
            AMDR_GPIO_DACENEN_BIT)

/** \brief 获取DAC使能位码 */
#define AMDR_GPIO_DACENBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_DACENBIT_OFFSET)

/** \brief DAC失能*/
#define AMDR_GPIO_DACENBIT_DISABLE  \
          AMDR_GPIO_DACENBIT_CODE(AMDR_GPIO_DACENBIT_DISABLE_VAL)

/** \brief DAC使能 */
#define AMDR_GPIO_DACENBIT_ENABLE \
        AMDR_GPIO_DACENBIT_CODE(AMDR_GPIO_DACENBIT_ENABLE_VAL)

/** @} */

/**
 * \name 输入反向控制，对应 bit[27]
 * @{
 */

/** \brief 输入反向控制位偏移 */
#define AMDR_GPIO_INVERTBIT_OFFSET          27

/** \brief 输入反向失能值 */
#define AMDR_GPIO_INVERTBIT_DISABLE_VAL     0
/** \brief 输入反向使能值 */
#define AMDR_GPIO_INVERTBIT_ENABLE_VAL      1

/** \brief 输入反向控制位码 */
#define AMDR_GPIO_INVERTBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_INVERTBIT_OFFSET) | \
            AMDR_GPIO_INVERTEN_BIT)

/** \brief 获取输入反向控制位码 */
#define AMDR_GPIO_INVERTBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_INVERTBIT_OFFSET)

/** \brief 输入反向失能 */
#define AMDR_GPIO_INVERTENBIT_DISABLE  \
          AMDR_GPIO_INVERTBIT_CODE(AMDR_GPIO_INVERTBIT_DISABLE_VAL)

/** \brief 输入反向使能  */
#define AMDR_GPIO_INVERTENBIT_ENABLE \
          AMDR_GPIO_INVERTBIT_CODE(AMDR_GPIO_INVERTBIT_ENABLE_VAL)

/** @} */

/**
 * \name 模拟/数字模式选择控制，对应 bit[28]
 * @{
 */

/** \brief 模拟/数字模式控制位偏移 */
#define AMDR_GPIO_ADMODEBIT_OFFSET          28

/** \brief 模拟/数字模式失能值 */
#define AMDR_GPIO_ADMODEBIT_ANALOG_VAL       0
/** \brief 模拟/数字模式使能值 */
#define AMDR_GPIO_ADMODEBIT_DIGITAL_VAL      1

/** \brief 模拟/数字模式控制位码 */
#define AMDR_GPIO_ADMODEBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_ADMODEBIT_OFFSET) | \
            AMDR_GPIO_ADMODEEN_BIT)

/** \brief 获取模拟/数字模式控制位码 */
#define AMDR_GPIO_ADMODEBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_ADMODEBIT_OFFSET)

/** \brief 模拟模式*/
#define AMDR_GPIO_ADMODEENBIT_ANALOG  \
          AMDR_GPIO_ADMODEBIT_CODE(AMDR_GPIO_ADMODEBIT_ANALOG_VAL)

/** \brief 数字模式  */
#define AMDR_GPIO_ADMODEENBIT_DIGITAL \
          AMDR_GPIO_ADMODEBIT_CODE(AMDR_GPIO_ADMODEBIT_DIGITAL_VAL)

/** @} */

/**
 * \name I2C 50ns毛刺滤波器及转换速率设置使能位控制，对应 bit[29]
 * @{
 */

/** \brief I2C 50ns毛刺滤波器及转换速率控制位偏移 */
#define AMDR_GPIO_HSBIT_OFFSET              29

/** \brief I2C 50ns毛刺滤波器及转换速率控制失能值 */
#define AMDR_GPIO_HSBIT_DISABLE_VAL          0
/** \brief I2C 50ns毛刺滤波器及转换速率控制使能值 */
#define AMDR_GPIO_HSBIT_ENABLE_VAL           1

/** \brief I2C 50ns毛刺滤波器及转换速率设置控制位码 */
#define AMDR_GPIO_HSBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_HSBIT_OFFSET) | \
            AMDR_GPIO_HSEN_BIT)

/** \brief 获取 I2C 50ns毛刺滤波器及转换速率设置控制位码 */
#define AMDR_GPIO_HSBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_HSBIT_OFFSET)

/** \brief I2C 50ns毛刺滤波器及转换速率设置失能 */
#define AMDR_GPIO_HSENBIT_DISABLE \
          AMDR_GPIO_HSBIT_CODE(AMDR_GPIO_HSBIT_DISABLE_VAL)

/** \brief I2C 50ns毛刺滤波器及转换速率设置使能  */
#define AMDR_GPIO_HSENBIT_ENABLE \
          AMDR_GPIO_HSBIT_CODE(AMDR_GPIO_HSBIT_ENABLE_VAL)

/** @} */

/**
 * \name 控制毛刺滤波器设置使能位控制，对应 bit[29]
 * @{
 */

/** \brief 控制毛刺滤波器设置控制位偏移 */
#define AMDR_GPIO_FILTERBIT_OFFSET              29

/** \brief 控制毛刺滤波器设置控制失能值 */
#define AMDR_GPIO_FILTERBIT_DISABLE_VAL          0
/** \brief 控制毛刺滤波器设置控制使能值 */
#define AMDR_GPIO_FILTERBIT_ENABLE_VAL           1

/** \brief 控制毛刺滤波器设置控制位码 */
#define AMDR_GPIO_FILTERBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_FILTERBIT_OFFSET) | \
            AMDR_GPIO_FILTEREN_BIT)

/** \brief 控制毛刺滤波器设置控制控制位码 */
#define AMDR_GPIO_FILTERBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_FILTERBIT_OFFSET)

/** \brief 控制毛刺滤波器设置控制设置失能 */
#define AMDR_GPIO_FILTERENBIT_DISABLE \
          AMDR_GPIO_FILTERBIT_CODE(AMDR_GPIO_FILTERBIT_DISABLE_VAL)

/** \brief 控制毛刺滤波器设置控制使能  */
#define AMDR_GPIO_FILTERENBIT_ENABLE \
          AMDR_GPIO_FILTERBIT_CODE(AMDR_GPIO_FILTERBIT_ENABLE_VAL)

/** @} */

/**
 * \name 驱动器转换速率设置使能位控制，对应 bit[30]
 * @{
 */

/** \brief 驱动器转换速率设置控制位偏移 */
#define AMDR_GPIO_SLEWBIT_OFFSET              30

/** \brief 驱动器转换速率设置失能值 */
#define AMDR_GPIO_SLEWBIT_DISABLE_VAL          0
/** \brief 驱动器转换速率设置使能值 */
#define AMDR_GPIO_SLEWBIT_ENABLE_VAL           1

/** \brief 驱动器转换速率设置控制位码 */
#define AMDR_GPIO_SLEWBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_SLEWBIT_OFFSET) | \
            AMDR_GPIO_SLEWEN_BIT)

/** \brief 驱动器转换速率设置控制位码 */
#define AMDR_GPIO_SLEWBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_SLEWBIT_OFFSET)

/** \brief 驱动器转换速率设置失能 */
#define AMDR_GPIO_SLEWENBIT_DISABLE \
          AMDR_GPIO_SLEWBIT_CODE(AMDR_GPIO_SLEWBIT_DISABLE_VAL)

/** \brief 驱动器转换速率设置使能  */
#define AMDR_GPIO_SLEWENBIT_ENABLE \
          AMDR_GPIO_SLEWBIT_CODE(AMDR_GPIO_SLEWBIT_ENABLE_VAL)

/** @} */

/**
 * \name 控制管脚灌电流能力设置位控制，对应 bit[30]
 * @{
 */

/** \brief 控制管脚灌电流能力设置位偏移 */
#define AMDR_GPIO_HIDRIVEBIT_OFFSET          30

/** \brief 控制管脚输出灌电流能力值4mA */
#define AMDR_GPIO_HIDRIVEBIT_4MA_VAL          0
/** \brief 控制管脚输出灌电流能力值20mA */
#define AMDR_GPIO_HIDRIVEBIT_20MA_VAL         1

/** \brief 控制管脚灌电流能力设置位码 */
#define AMDR_GPIO_HIDRIVEBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_HIDRIVEBIT_OFFSET) | \
            AMDR_GPIO_HIDRIVEEN_BIT)

/** \brief 控制管脚灌电流能力设置位码 */
#define AMDR_GPIO_HIDRIVEBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_HIDRIVEBIT_OFFSET)

/** \brief 控制管脚输出灌电流能力4mA*/
#define AMDR_GPIO_HIDRIVEENBIT_4MA \
          AMDR_GPIO_HIDRIVEBIT_CODE(AMDR_GPIO_HIDRIVEBIT_4MA_VAL)

/** \brief 控制管脚输出灌电流能力4mA */
#define AMDR_GPIO_HIDRIVEENBIT_20MA \
          AMDR_GPIO_HIDRIVEBIT_CODE(AMDR_GPIO_HIDRIVEBIT_20MA_VAL)

/** @} */

/**
 * \name 开漏模式控制，对应 bit[31]
 * @{
 */

/** \brief 开漏模式位偏移 */
#define AMDR_GPIO_ODBIT_OFFSET          31

/** \brief 开漏模式失能值*/
#define AMDR_GPIO_ODBIT_DISABLE_VAL     0
/** \brief 开漏模式使能值 */
#define AMDR_GPIO_ODBIT_ENABLE_VAL      1

/** \brief 开漏模式位码 */
#define AMDR_GPIO_ODBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_ODBIT_OFFSET) | \
            AMDR_GPIO_ODEN_BIT)

/** \brief 获取开漏模式位码 */
#define AMDR_GPIO_ODBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_ODBIT_OFFSET)

/** \brief 开漏模式失能*/
#define AMDR_GPIO_ODENBIT_DISABLE  \
          AMDR_GPIO_ODBIT_CODE(AMDR_GPIO_ODBIT_DISABLE_VAL)

/** \brief 开漏模式使能 */
#define AMDR_GPIO_ODENBIT_ENABLE \
          AMDR_GPIO_ODBIT_CODE(AMDR_GPIO_ODBIT_ENABLE_VAL)

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_GPIO_UTIL_H */

/* end of file */
