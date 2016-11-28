/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
  EEPROM控制器配置信息
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_EEPROM

#include "driver/eeprom/awbl_lpc17xx_eeprom.h"
#include "ametal.h"

typedef int (* pfunc_eeprom_init_t)(void *, void *);

/**
 * \brief EEPROM 中断个数
 */
#define EEPROM_INT_COUNT    2

/** \brief 引脚触发信息内存 */
static amdr_eeprom_intcb_info_t __g_eeprom_intcb_infos[EEPROM_INT_COUNT];

/**
 * \brief 内部EEPROM 存储段配置列表
 */
aw_local aw_const struct awbl_nvram_segment __g_lpc17xx_eeprom_seglst[] = {
    /* 定义一个存储段：存储段名称, 单元号, 起始地址，长度 */
    {"lpc17_eeprom", 0, 0, 64*64},        /* 整个EEPROM存储空间 */
    {"lpc17_eeprom", 1, 0, 8},            /* 桩ID */
    {"lpc17_eeprom", 2, 8, 1},            /* 集中器地址 */
    {"lpc17_eeprom", 3, 9, 48},           /* 集中器地址 */
    {"lpc17_eeprom", 4, 62, 2},           /* 总条目信息 */
    {"lpc17_eeprom", 5, 64, 90*44},       /* 条目数据 */
    {"lpc17_eeprom", 6, 64 + 90*44, 72},  /* 密钥 */
};

/** \brief EEPROM 设备信息 */
const amdr_eeprom_devinfo_t g_eeprom_devinfo = {

	AMHW_EEPROM,              /**< \brief EEPROM的基地址                  */

	__g_eeprom_intcb_infos,   /**< \brief 引脚触发信息内存              */

	INUM_EEPROM,              /**< \brief EEPROM中断号             */

	EEPROM_INT_COUNT,         /**< \brief 使用到的管脚中断数目          */
};

/** \brief EEPROM设备实例 */
amdr_eeprom_dev_t g_eeprom_dev;

/* 设备信息 */
aw_local aw_const struct awbl_lpc17xx_eeprom_param __g_lpc17xx_eeprom_param = {
	&__g_lpc17xx_eeprom_seglst[0],
	AW_NELEMENTS(__g_lpc17xx_eeprom_seglst),
    &g_eeprom_dev,                           /* EEPROM 设备               */
    &g_eeprom_devinfo,                       /* EEPROM 设备信息时         */
    (pfunc_eeprom_init_t)amdr_eeprom_init,   /* EEPROM 初始化函数         */
};

/* 设备实例内存静态分配 */
aw_local struct awbl_lpc17xx_eeprom_dev __g_lpc17xx_eeprom_dev;

#define AWBL_HWCONF_LPC17XX_EEPROM                  \
    {                                               \
        AWBL_LPC17XX_EEPROM_NAME,                   \
        0,                                          \
        AWBL_BUSID_PLB,                             \
        0,                                          \
        (struct awbl_dev *)&__g_lpc17xx_eeprom_dev, \
        &__g_lpc17xx_eeprom_param                   \
    },

#else

#define  AWBL_HWCONF_LPC17XX_EEPROM

#endif    /* AW_DEV_LPC17XX_EEPROM */

/* end of file */
