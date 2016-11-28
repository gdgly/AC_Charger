/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief SPI-Flash driver head file
 *
 * define SPI-Flash driver data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 14-10-31  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_SPI_FLASH_H
#define __AWBL_SPI_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "aw_spi.h"
#include "awbl_spibus.h"
#include "fs/aw_block_dev.h"
#include "mtd/aw_mtd.h"
#include "awbl_nvram.h"

#define AWBL_SPI_FLASH_NAME   "awbl_spi_flash"

/**
 * \brief spi flash device information
 */
typedef struct awbl_spi_flash_devinfo {

	struct awbl_nvram_segment	*p_seglst;
	uint_t						seglst_count;
	uint8_t						*p_blk_buf;		/**< \brief buffer for NVRAM to write */

	const char					*name;

    uint_t						block_size;		/**< \brief block size */
    sector_t					nblocks;		/**< \brief number of blocks */
    uint_t						page_size;		/**< \brief page size */
    uint_t						reserved_nblks;	/**< \brief reserved blocks for others */

	uint16_t					spi_mode;
	int							spi_cs_pin;
	uint32_t					spi_speed;

    void (*pfunc_plfm_init)(void);
}awbl_spi_flash_devinfo_t;

/**
 * \brief spi flash device
 */
typedef struct awbl_spi_flash_dev {
    struct awbl_spi_device	spi_dev;	/** \brief SPI device */
    struct aw_block_dev		bd_dev;		/** \brief block device */

    struct aw_mtd_info		mtd;		/** \brief MTD device */
	/** \brief mask erase align on block boundary */
	off_t					erase_align_mask;

	/** \brief start address in the full chip */
	int						addr_offset;

    AW_MUTEX_DECL(devlock);
} awbl_spi_flash_dev_t;

/**
 * \brief spi flash driver register
 */
void awbl_spi_flash_drv_register (void);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AWBL_SPI_FLASH_H */
