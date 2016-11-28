/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      aworks.support@zlg.cn
*******************************************************************************/

#ifndef __AWBL_HWCONF_SPI_FLASH_H
#define __AWBL_HWCONF_SPI_FLASH_H

#ifdef  AW_DEV_NOR_FLASH

#include "aw_gpio.h"
#include "aw_spi.h"
#include "driver/norflash/awbl_spi_flash.h"

#include "boot/boot_cfg.h"

aw_local struct awbl_nvram_segment __g_spiflash_seglst[] = {
    /* 存储段名称, 单元号, 起始地址，长度 */
    {"spi_flash_nvram",  0, 0, 2*1024*1024},

    /* 存储段名称, 单元号, 起始地址，长度 */
    {"spi_flash_nvram",  0, 0, 2*1024*1024},
    {LPC1778_IMAGE_NAME,  0,  LPC1778_IMAGE_ADDR,  LPC1778_IMAGE_SIZE},
    {LPC1778_UPDATE_IMAGE_VALID,  0,  LPC1778_UPDATE_IMAGE_ADDR,  LPC1778_UPDATE_IMAGE_SIZE},
    {LPC1778_IMAGE_VALID, 0, LPC1778_IMAGE_VALID_ADDR, LPC1778_IMAGE_VALID_SIZE},
    {INTO_UPDATE_FLAG, 0, INTO_UPDATE_FLAG_ADDR, INTO_UPDATE_FLAG_SIZE},
};

/* 平台相关初始化 */
aw_local void __spi_flash_plfm_init (void)
{
    aw_gpio_pin_cfg(PIO0_14, AW_GPIO_OUTPUT | AW_GPIO_PULL_UP);

    aw_gpio_set(PIO0_14, 1);
};

/* 使用 NVRAM 接口读写SPI Flash 时，需要的块缓存，容量应与块大小一致*/
//aw_local uint8_t __g_block_buf[4096] = {0};

aw_local aw_const awbl_spi_flash_devinfo_t __g_spi_flash_devinfo0 = {
    &__g_spiflash_seglst[0],            /* 非易失性存储段配置列表 */
    AW_NELEMENTS(__g_spiflash_seglst),  /* 非易失性存储段配置列表条目数 */
    NULL, //__g_block_buf,
    "/sflash0",                         /* flash 注册成块设备的名字 */
    4096,                               /* flash 擦除操作的块大小 */
    512,                                /* flash 对应块数量 */
    256,                                /* flash 写操作的页大小 */
    0,                                  /* 保留0个块，即0MB的空间 */
    AW_SPI_MODE_0,                      /* 接口时序模式 */
    PIO0_14,                             /* 片选引脚 */
    30000000,                           /* SPI总线时钟 */
    __spi_flash_plfm_init,
};

aw_local awbl_spi_flash_dev_t __g_spi_flash_dev0;

#define AWBL_HWCONF_SPI_FLASH0                  \
    {                                           \
        AWBL_SPI_FLASH_NAME,                    \
        0,                                      \
        AWBL_BUSID_SPI,                         \
        GPIO_SPI0_BUSID,                        \
        &(__g_spi_flash_dev0.spi_dev.super),    \
        &__g_spi_flash_devinfo0                 \
    },

#else
#define AWBL_HWCONF_SPI_FLASH0

#endif  /* AW_DEV_NOR_FLASH */

#endif  /* __AWBL_HWCONF_SPI_FLASH_H */

/* end of file */
