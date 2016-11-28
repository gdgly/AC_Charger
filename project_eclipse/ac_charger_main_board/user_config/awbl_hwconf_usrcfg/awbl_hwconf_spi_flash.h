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
    /* �洢������, ��Ԫ��, ��ʼ��ַ������ */
    {"spi_flash_nvram",  0, 0, 2*1024*1024},

    /* �洢������, ��Ԫ��, ��ʼ��ַ������ */
    {"spi_flash_nvram",  0, 0, 2*1024*1024},
    {LPC1778_IMAGE_NAME,  0,  LPC1778_IMAGE_ADDR,  LPC1778_IMAGE_SIZE},
    {LPC1778_UPDATE_IMAGE_VALID,  0,  LPC1778_UPDATE_IMAGE_ADDR,  LPC1778_UPDATE_IMAGE_SIZE},
    {LPC1778_IMAGE_VALID, 0, LPC1778_IMAGE_VALID_ADDR, LPC1778_IMAGE_VALID_SIZE},
    {INTO_UPDATE_FLAG, 0, INTO_UPDATE_FLAG_ADDR, INTO_UPDATE_FLAG_SIZE},
};

/* ƽ̨��س�ʼ�� */
aw_local void __spi_flash_plfm_init (void)
{
    aw_gpio_pin_cfg(PIO0_14, AW_GPIO_OUTPUT | AW_GPIO_PULL_UP);

    aw_gpio_set(PIO0_14, 1);
};

/* ʹ�� NVRAM �ӿڶ�дSPI Flash ʱ����Ҫ�Ŀ黺�棬����Ӧ����Сһ��*/
//aw_local uint8_t __g_block_buf[4096] = {0};

aw_local aw_const awbl_spi_flash_devinfo_t __g_spi_flash_devinfo0 = {
    &__g_spiflash_seglst[0],            /* ����ʧ�Դ洢�������б� */
    AW_NELEMENTS(__g_spiflash_seglst),  /* ����ʧ�Դ洢�������б���Ŀ�� */
    NULL, //__g_block_buf,
    "/sflash0",                         /* flash ע��ɿ��豸������ */
    4096,                               /* flash ���������Ŀ��С */
    512,                                /* flash ��Ӧ������ */
    256,                                /* flash д������ҳ��С */
    0,                                  /* ����0���飬��0MB�Ŀռ� */
    AW_SPI_MODE_0,                      /* �ӿ�ʱ��ģʽ */
    PIO0_14,                             /* Ƭѡ���� */
    30000000,                           /* SPI����ʱ�� */
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
