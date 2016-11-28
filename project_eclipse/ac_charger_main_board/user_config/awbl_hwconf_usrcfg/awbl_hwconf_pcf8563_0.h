/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      aworks.support@zlg.cn
*******************************************************************************/

/** 
 * \file 
 * \brief RTC PCF8563 配置文件
 * 
 * \par
 * \internal 
 * \par modification history:
 * -1.00 16-02-23 lnk, first implementation
 * \endinternal
 */

#ifdef AW_DEV_EXTEND_PCF8563_0

#include "driver/rtc/awbl_pcf8563.h"

/**
 * \addtogroup grp_aw_plfm_ext_pcf8563_usrcfg
 * @{
 */

/* PCF8563 设备信息 */
aw_local aw_const struct awbl_pcf8563_devinfo __g_pcf8563_0_devinfo = {
    {
        2     /* RTC 设备编号 */
    },
    0xA2      /* I2C 从机地址 */
};

/* PCF8563 设备实例内存静态分配 */
aw_local struct awbl_pcf8563_dev __g_pcf8563_0_dev;

#define AWBL_HWCONF_PCF8563_0   \
    {                           \
        AWBL_PCF8563_NAME,      \
        0,                      \
        AWBL_BUSID_I2C,         \
        LPC17XX_I2C0_BUSID,      \
        (struct awbl_dev *)&__g_pcf8563_0_dev,    \
        &__g_pcf8563_0_devinfo                    \
    },
    
#else
#define AWBL_HWCONF_PCF8563_0
#endif  /* AW_DEV_EXTEND_PCF8563_0 */

/* end of file */

