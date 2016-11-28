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
 * \brief NandFlash driver head file
 *
 * define NandFlash driver data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 14-12-17  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_NANDFLASH_H
#define __AWBL_NANDFLASH_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "awbl_nandbus.h"
#include "mtd/aw_mtd.h"

#define AWBL_NANDFLASH_DRV_NAME		"awbl_nandflash_drv_name"

/**
 * \name nand flash chip attribute
 * @{
 */
/* SAMSUNG K9F2G08 */
#define NANDFLASH_K9F2G08_TIMING \
	20, \
	5, \
	15, \
	5, \
	15, \
	5, \
	15, \
	5, \
	15, \
	20, \
	25, \
	30, \
	30, \
	100, \
	10, \
	15, \
	30
#define NANDFLASH_K9F2G08_ECC_STRENGTH \
	4
#define NANDFLASH_K9F2G08 \
	2048, \
	64, \
	64, \
	2048, \
	0, \
	8, \
	128*1024,\
	256*1024*1024, \
	0xEC, \
	0xDA

/* MXIC MX30LF1G08 */
#define NANDFLASH_MX30LF1G08_TIMING \
	20, \
	5, \
	15, \
	5, \
	15, \
	5, \
	5, \
	5, \
	15, \
	20, \
	25, \
	50, \
	30, \
	50, \
	15, \
	15, \
	30
#define NANDFLASH_MX30LF1G08_ECC_STRENGTH \
	4
#define NANDFLASH_MX30LF1G08 \
	2048, \
	64, \
	64, \
	1024, \
	0, \
	8, \
	128*1024,\
	128*1024*1024, \
	0xC2, \
	0xF1

/* MXIC MX30LF2G28 */
#define NANDFLASH_MX30LF2G28_TIMING \
	15, \
	5, \
	10, \
	5, \
	10, \
	5, \
	7, \
	5, \
	10, \
	16, \
	25, \
	50, \
	20, \
	100, \
	10, \
	10, \
	20
#define NANDFLASH_MX30LF2G28_ECC_STRENGTH \
	8
#define NANDFLASH_MX30LF2G28\
	2048, \
	112, \
	64, \
	2048, \
	0, \
	8, \
	128*1024,\
	128*1024*2048, \
	0xC2, \
	0xDA

/* SPANSION S34ML01G2 */
#define NANDFLASH_S34ML01G2_TIMING \
	20, \
	5, \
	10, \
	5, \
	10, \
	5, \
	10, \
	5, \
	12, \
	20, \
	25, \
	30, \
	25, \
	100, \
	10, \
	12, \
	25
#define NANDFLASH_S34ML01G2_ECC_STRENGTH \
	4
#define NANDFLASH_S34ML01G2\
	2048, \
	64, \
	64, \
	1024, \
	0, \
	8, \
	128*1024, \
	128*1024*1024, \
	0x01, \
	0xF1

/**
 * \name nand flash partition
 * @{
 */
struct awbl_nandflash_partition_info {
	const char					*name;

	/** \brief start block of this partition */
    uint32_t					start_blk_num;

    /** \brief end block of this partition */
    uint32_t					end_blk_num;
};

struct awbl_nandflash_partition {
	const struct awbl_nandflash_partition_info *p_info;

	struct awbl_nandflash		*p_flash;

    /** \brief this is a MTD device */
    struct aw_mtd_info			mtd;
    struct aw_mtd_oob_layout	oob_layout;
    struct aw_mtd_oob_space		ecc_pos[3];
    struct aw_mtd_oob_space		oob_free[3];

	/** \brief mask erase align on block boundary */
	off_t						erase_align_mask;
	/** \brief N bits to shift to page address */
	int							page_shift;
	/** \brief start page in the full chip */
	size_t						page_offset;
};

/**
 * \name nand flash information
 * @{
 */
struct awbl_nandflash_info {
	/** \brief base information */
	struct awbl_nand_chip_info	chip_info;

	/** \brief page size */
	uint16_t				page_size;

	/** \brief spare size in per page */
	uint8_t					spare_size;

	/** \brief N pages in per block */
	uint16_t				pages_per_blk;

	/** \brief number of blocks */
	uint32_t				nblks;

	/** \brief offset of bad block mark in the spare */
    uint8_t 				bad_blk_byte_offs;

    /** \brief N bits of per flash cell */
    uint8_t 				bits_per_cell;

    /** \brief block size */
    uint32_t 				blk_size;

    /** \brief chip size */
    uint32_t				chip_size;

    /** \brief manufacturer ID */
    uint8_t					maker_id;

    /** \brief device ID */
    uint8_t					device_id;

    /** \brief partition table */
    const struct awbl_nandflash_partition_info	*p_ptab_info;
    struct awbl_nandflash_partition				*p_ptab;
    int											npartition;
};


/**
 * \name nand flash
 * @{
 */
struct awbl_nandflash {
	struct awbl_nand_chip			chip;
	struct awbl_nandflash_info  	*p_info;
};


/** \brief register nand flash driver */
void awbl_nandflash_drv_register (void);

/** \brief reset nand flash */
aw_err_t awbl_nandflash_reset (struct awbl_nandflash *p_nandflash);

/** \brief check if the block is bad,
 * return	0:		not bad
 * 			1:		bad
 * 			other:	I/O or other error
 *  */
int awbl_nandflash_block_is_bad (
					struct awbl_nandflash	*p_nandflash,
					uint32_t				page_addr);

/** \brief mark the block bad */
int awbl_nandflash_block_mark_bad (
					struct awbl_nandflash	*p_nandflash,
					uint32_t				page_addr);

/** \brief erase the block of the nand flash */
aw_err_t awbl_nandflash_erase_block (	struct awbl_nandflash	*p_nandflash,
										uint32_t				page_addr);



/** \brief write data to the nand flash */
aw_err_t awbl_nandflash_write (struct awbl_nandflash	*p_nandflash,
							   uint16_t					col_addr,
							   uint32_t					page_addr,
							   const void				*p_buf,
							   uint32_t					len,
							   void						*ecc_buf);

/** \brief read data from the nand flash */
aw_err_t awbl_nandflash_read (struct awbl_nandflash	*p_nandflash,
							  uint16_t				col_addr,
							  uint32_t				page_addr,
							  void					*p_buf,
							  uint32_t				len,
							  void					*ecc_buf);

aw_err_t awbl_nandflash_page_write (struct awbl_nandflash	*p_nandflash,
									uint32_t				page_addr,
									const void				*p_buf,
									void					*ecc_buf);

aw_err_t awbl_nandflash_page_read (	struct awbl_nandflash	*p_nandflash,
									uint32_t				page_addr,
									void					*p_buf,
									void					*ecc_buf);

/** \brief read spare data from the nand flash */
aw_err_t awbl_nandflash_spare_read (struct awbl_nandflash	*p_nandflash,
									uint8_t					offs,
									uint32_t				page_addr,
									void					*p_buf,
									uint8_t					len);

/** \brief write spare data to the nand flash */
aw_err_t awbl_nandflash_spare_write (	struct awbl_nandflash	*p_nandflash,
										uint8_t					offs,
										uint32_t				page_addr,
										const void				*p_buf,
										uint8_t					len);


#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AWBL_NANDFLASH_H */
