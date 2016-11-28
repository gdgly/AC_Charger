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
 * \brief SD CARD driver head file
 *
 * define SD CARD driver data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 14-11-14  deo, first implementation
 * \endinternal
 */


#ifndef __AW_SDCARD_H
#define __AW_SDCARD_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "fs/aw_block_dev.h"
#include "awbl_sdiobus.h"
#include "mtd/aw_mtd.h"

#define AWBL_SDCARD_NAME    "awbl_sdcard_driver"
#define AWBL_SDCARD_MTD_EN  0

typedef struct awbl_sdio_card_cid awbl_sdio_card_cid_t;
typedef struct awbl_sdio_card_scr awbl_sdio_card_scr_t;
typedef struct awbl_sdio_card_ssr awbl_sdio_card_ssr_t;


/* CID */
struct awbl_sdio_card_cid {
    uint32_t    mid;
    uint16_t    oid;
    char        pnm[8];
    uint8_t     prv;
    uint32_t    psn;
    uint16_t    year;
    uint8_t     month;
    uint8_t     hwrev;
    uint8_t     fwrev;
};

/* SCR register */
struct awbl_sdio_card_scr {
    uint8_t             structure;
    uint8_t             sda_vsn;
    uint8_t             sda_spec3;
    uint8_t             bus_widths;
#define SD_SCR_BUS_WIDTH_1  (1<<0)
#define SD_SCR_BUS_WIDTH_4  (1<<2)
    uint8_t             cmds;
#define SD_SCR_CMD20_SUPPORT   (1<<0)
#define SD_SCR_CMD23_SUPPORT   (1<<1)
    uint8_t             erase_value;
};

/* SSR register */
struct awbl_sdio_card_ssr {
    uint32_t            au_size;            /* In sectors */
    uint32_t            erase_timeout;      /* In milliseconds */
    uint32_t            erase_offset;       /* In milliseconds */
};



/**
 * \brief SD CARD struct
 */
typedef struct awbl_sdcard_dev {
    awbl_sdio_card_t        super;
    struct aw_list_head     node;

    struct aw_block_dev     bd_dev;

#if AWBL_SDCARD_MTD_EN
    struct aw_mtd_info      mtd;
    int                     sector_shift;
    uint8_t                 *rd_buf;
    uint8_t                 *wr_buf;
#endif

    AW_MUTEX_DECL(devlock);

    uint32_t    ocr;                /* OCR */
    uint32_t    rca;                /* address */

    uint16_t    attribute;          /* attribute */

    uint8_t     mmca_vsn;           /* MMC version */
    uint32_t    au_size;            /* allocate unit size */
    uint32_t    max_tr_speed;       /* MAX transfer speed */
    uint16_t    cmd_class;          /* command class  */
    uint16_t    sector_size;        /* sector size */
    uint32_t    sector_cnt;         /* sector count */
    uint16_t    block_size;

    awbl_sdio_card_cid_t cid;
    awbl_sdio_card_scr_t scr;
} awbl_sdcard_dev_t;

struct awbl_sdcard_remove_cb {
    struct aw_list_head   node;
    const char            *name;
    void                  (*callback)(void *arg);
    void                  *arg;
};



/**
 * \brief sdcard driver register
 */
void awbl_sdcard_drv_register (void);

struct awbl_sdcard_dev *awbl_sdcard_find_by_name (const char *name);

aw_err_t awbl_sdcard_wr_sector (awbl_sdcard_dev_t   *p_sdcard,
                                uint32_t            sector,
                                uint8_t             *p_buf,
                                uint32_t            sector_cnt);

aw_err_t awbl_sdcard_rd_sector (awbl_sdcard_dev_t   *p_sdcard,
                                uint32_t            sector,
                                uint8_t             *p_buf,
                                uint32_t            sector_cnt);

bool_t awbl_sdcard_is_insert (const char *name);
aw_err_t awbl_sdcard_wait_insert (const char *name, int timeout);

void awbl_sdcard_remove_cb_register (
                        struct awbl_sdcard_remove_cb  *p_remove_cb,
                        const char                    *name,
                        void                          (*callback)(void *arg),
                        void                          *arg);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif
