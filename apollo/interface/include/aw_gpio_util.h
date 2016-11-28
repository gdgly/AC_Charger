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
 * \brief GPIO 标准接口工具头文件
 *
 * 本文件提供了与GPIO接口相关的辅助宏等工具软件
 *
 * \internal
 * \par modification history:
 * - 1.00 12-08-23  zen, first implementation
 * \endinternal
 */

#ifndef __AW_GPIO_UTIL_H
#define __AW_GPIO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/* bit[2:0] function code */

#define AW_GPIO_FUNCBITS_START          0
#define AW_GPIO_FUNCBITS_LEN            3
#define AW_GPIO_FUNC_INVALID_VAL        0x0
#define AW_GPIO_INPUT_VAL               0x1
#define AW_GPIO_OUTPUT_VAL              0x2
#define AW_GPIO_OUTPUT_INIT_HIGH_VAL    0x3
#define AW_GPIO_OUTPUT_INIT_LOW_VAL     0x4


#define AW_GPIO_FUNCBITS_CODE(value) AW_SBF((value), AW_GPIO_FUNCBITS_START)
#define AW_GPIO_FUNCBITS_GET(data)   AW_BITS_GET((data), \
                                                 AW_GPIO_FUNCBITS_START, \
                                                 AW_GPIO_FUNCBITS_LEN)

#define AW_GPIO_FUNC_INVALID    AW_GPIO_FUNCBITS_CODE(AW_GPIO_FUNC_INVALID_VAL)


/* bit[5:3] mode code */

#define AW_GPIO_MODEBITS_START      3
#define AW_GPIO_MODEBITS_LEN        3
#define AW_GPIO_MODE_INVALID_VAL    0x0
#define AW_GPIO_PULL_UP_VAL         0x1
#define AW_GPIO_PULL_DOWN_VAL       0x2
#define AW_GPIO_FLOAT_VAL           0x3
#define AW_GPIO_OPEN_DRAIN_VAL      0x4
#define AW_GPIO_PUSH_PULL_VAL       0x5

#define AW_GPIO_MODEBITS_CODE(value) AW_SBF((value), AW_GPIO_MODEBITS_START)
#define AW_GPIO_MODEBITS_GET(data)   AW_BITS_GET((data), \
                                                 AW_GPIO_MODEBITS_START, \
                                                 AW_GPIO_MODEBITS_LEN)

#define AW_GPIO_MODE_INVALID    AW_GPIO_MODEBITS_CODE(AW_GPIO_MODE_INVALID_VAL)

/* bit[11:6] reserved */

/* bit[31:12] defined by platform */

#define AW_GPIO_PLFMBITS_START      12
#define AW_GPIO_PLFMBITS_LEN        20

#define AW_GPIO_PLFMBITS_SET(data, value) AW_BITS_SET((data), \
                                                      AW_GPIO_PLFMBITS_START, \
                                                      AW_GPIO_PLFMBITS_LEN, \
                                                      (value))

#define AW_GPIO_PLFMBITS_GET(data)  AW_BITS_GET((data), \
                                                 AW_GPIO_PLFMBITS_START, \
                                                 AW_GPIO_PLFMBITS_LEN)

#ifdef __cplusplus
}
#endif

#endif /* __AW_GPIO_UTIL_H */

/* end of file */
