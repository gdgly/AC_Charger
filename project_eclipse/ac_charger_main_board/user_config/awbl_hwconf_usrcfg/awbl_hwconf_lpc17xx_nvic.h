/*******************************************************************************
*                                 AnyWhere
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
  中断控制器配置信息
*******************************************************************************/
#include "driver/intctlr/awbl_armcm_nvic.h"
#include "ametal.h"

#ifdef AW_DEV_LPC17XX_NVIC

/*******************************************************************************
  ARM Cortex-M NVIC 配置信息
*******************************************************************************/

/* ISR 信息映射内存静态分配 */
aw_local uint8_t __g_armcm_nvic_infomap[INUM_INTERNAL_COUNT];

/* ISR 信息内存静态分配 */
aw_local struct awbl_armcm_nvic_isrinfo
    __g_armcm_nvic_isrinfos[AW_CFG_ARMCM_NVIC_ISRINFO_COUNT];

/* NVIC 设备信息 */
aw_local aw_const struct awbl_armcm_nvic_devinfo __g_armcm_nvic_devinfo = {
    
    16,
    
    {
        INUM_WWDT,                     /* 支持的起始中断号 */
        INUM_EEPROM,                 /* 支持的结束中断号 */
    },

    INUM_INTERNAL_COUNT,              /* 中断个数 */

    &__g_armcm_nvic_infomap[0],       /* ISR 映射信息内存(大小等于input_cnt) */

    AW_CFG_ARMCM_NVIC_ISRINFO_COUNT,  /* ISR 信息条数 */
    &__g_armcm_nvic_isrinfos[0],      /* ISR 信息槽内存(大小等于isrinfo_cnt) */
};

/* NVIC 设备实例内存静态分配*/
aw_local struct awbl_armcm_nvic_dev __g_armcm_nvic_dev;

#define AWBL_HWCONF_LPC17XX_NVIC   \
    {                              \
        AWBL_ARMCM_NVIC_NAME,      \
        0,                         \
        AWBL_BUSID_PLB,            \
        0,                         \
        (struct awbl_dev *)&__g_armcm_nvic_dev, \
        &__g_armcm_nvic_devinfo    \
    },
 
#else

#define AWBL_HWCONF_LPC17XX_NVIC

#endif  /* AW_DEV_LPC17XX_NVIC */

/* end of file */

