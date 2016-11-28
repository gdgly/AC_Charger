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
 * \brief SPI-Flash driver source file
 *
 * define SPI-Flash driver
 *
 * \internal
 * \par modification history:
 * - 1.00 14-10-31  deo, first implementation
 * \endinternal
 */


/*******************************************************************************
  includes
*******************************************************************************/
#include "apollo.h"
#include "aw_vdebug.h"
#include "aw_spinlock.h"
#include "awbus_lite.h"
#include "awbl_plb.h"
#include "driver/norflash/awbl_spi_flash.h"
#include "awbl_nvram.h"
#include "aw_delay.h"
#include <string.h>

/*******************************************************************************
  macro operate
*******************************************************************************/
#define __SPI_FLASH_DEVINFO_DECL(p_info, p_spi_dev) \
        awbl_spi_flash_devinfo_t *p_info = \
        (awbl_spi_flash_devinfo_t *)AWBL_DEVINFO_GET(p_spi_dev)

#define __SPI_DEV_TO_FLASH_DEC(p_dev, p_spi_dev) \
        struct awbl_spi_flash_dev *p_dev = (struct awbl_spi_flash_dev *) \
                AW_CONTAINER_OF(p_spi_dev, struct awbl_spi_flash_dev, spi_dev)

#define __MTD_DEV_TO_FLASH_DEC(p_dev, p_mtd) \
        struct awbl_spi_flash_dev *p_dev = (struct awbl_spi_flash_dev *) \
                AW_CONTAINER_OF(p_mtd, struct awbl_spi_flash_dev, mtd)

/******************************************************************************/
aw_local aw_err_t __spi_flash_rd_status_reg (awbl_spi_flash_dev_t  *p_dev,
                                             uint8_t               *status)
{
    struct aw_spi_message  spi_msg;
    struct aw_spi_transfer trans1;
    struct aw_spi_transfer trans2;
    uint8_t                status_reg;

    aw_spi_msg_init(&spi_msg, NULL, NULL);

    status_reg = 0x05;

    aw_spi_mktrans(&trans1,
                   &status_reg,
                   NULL,
                   1,
                   0,
                   0,
                   0,
                   p_dev->spi_dev.spi_dev.max_speed_hz,
                   0);

    aw_spi_mktrans(&trans2,
                   NULL,
                   status,
                   1,
                   0,
                   0,
                   0,
                   p_dev->spi_dev.spi_dev.max_speed_hz,
                   0);

    aw_spi_trans_add_tail(&spi_msg, &trans1);
    aw_spi_trans_add_tail(&spi_msg, &trans2);

    return aw_spi_sync(&(p_dev->spi_dev.spi_dev), &spi_msg);
}

/******************************************************************************/
aw_local aw_err_t __spi_flash_wait_busy (awbl_spi_flash_dev_t *p_dev)
{
    uint8_t     status;
    uint32_t    timeout = 0;
    aw_err_t    err;
#define __TIMEOUT_US    (2*1000*1000)

    while(1) {
        __spi_flash_rd_status_reg(p_dev, &status);
        if ((status & 0x03) == 0x03) {
            aw_udelay(1);
            timeout++;
            if (timeout == __TIMEOUT_US) {
                err = -ETIME;
                break;
            }
        } else {
            err = AW_OK;
            break;
        }
    }

    return err;
}

/******************************************************************************/
aw_local aw_err_t __spi_flash_enable_wr (awbl_spi_flash_dev_t *p_dev)
{
    struct aw_spi_message   spi_msg;
    struct aw_spi_transfer  trans;
    uint8_t                 status_reg;

    aw_spi_msg_init(&spi_msg, NULL, NULL);

    status_reg = 0x06;

    aw_spi_mktrans(&trans,
                   &status_reg,
                   NULL,
                   1,
                   0,
                   0,
                   0,
                   p_dev->spi_dev.spi_dev.max_speed_hz,
                   0);

    aw_spi_trans_add_tail(&spi_msg, &trans);

    return aw_spi_sync(&(p_dev->spi_dev.spi_dev), &spi_msg);
}


/******************************************************************************/
aw_local aw_err_t __spi_flash_hs_read_nbytes (awbl_spi_flash_dev_t  *p_dev,
                                              uint32_t              addr,
                                              uint8_t               *p_buf,
                                              uint32_t              len)
{
    struct aw_spi_message   spi_msg;
    struct aw_spi_transfer  trans1;
    struct aw_spi_transfer  trans2;
    uint8_t                 cmd_buf[5];
    aw_err_t                err;

    AW_MUTEX_LOCK(p_dev->devlock, AW_SEM_WAIT_FOREVER);

    if (AW_OK != __spi_flash_wait_busy(p_dev)) {
        return -ETIME;
    }

    /* initialize message */
    aw_spi_msg_init(&spi_msg, NULL, NULL);

    cmd_buf[0] = 0x0b;
    cmd_buf[1] = (addr & 0xFFFFFF) >> 16;
    cmd_buf[2] = (addr & 0xFFFF) >> 8;
    cmd_buf[3] = addr & 0xFF;
    cmd_buf[4] = 0xFF;

    aw_spi_mktrans(&trans1,
                   cmd_buf,
                   NULL,
                   5,
                   0,
                   0,
                   0,
                   p_dev->spi_dev.spi_dev.max_speed_hz,
                   0);

    aw_spi_mktrans(&trans2,
                   NULL,
                   p_buf,
                   len,
                   0,
                   0,
                   0,
                   p_dev->spi_dev.spi_dev.max_speed_hz,
                   0);

    aw_spi_trans_add_tail(&spi_msg, &trans1);
    aw_spi_trans_add_tail(&spi_msg, &trans2);

    err = aw_spi_sync(&(p_dev->spi_dev.spi_dev), &spi_msg);

    AW_MUTEX_UNLOCK(p_dev->devlock);

    return err;
}

/******************************************************************************/
aw_local aw_err_t __spi_flash_program_nbyte (awbl_spi_flash_dev_t  *p_dev,
                                             uint32_t              addr,
                                             uint8_t               *p_buf,
                                             uint32_t              len)
{
    struct aw_spi_message   spi_msg;
    struct aw_spi_transfer  trans1;
    struct aw_spi_transfer  trans2;
    uint8_t                 cmd_buf[4];
    aw_err_t                err;

    AW_MUTEX_LOCK(p_dev->devlock, AW_SEM_WAIT_FOREVER);


    if (AW_OK != __spi_flash_wait_busy(p_dev)) {
        return -ETIME;
    }

    __spi_flash_enable_wr(p_dev);

    if (AW_OK != __spi_flash_wait_busy(p_dev)) {
        return -ETIME;
    }
    aw_spi_msg_init(&spi_msg, NULL, NULL);

    cmd_buf[0] = 0x02;
    cmd_buf[1] = (addr & 0xFFFFFF) >> 16;
    cmd_buf[2] = (addr & 0xFFFF) >> 8;
    cmd_buf[3] = addr & 0xFF;

    aw_spi_mktrans(&trans1,
                   cmd_buf,
                   NULL,
                   4,
                   0,
                   0,
                   0,
                   p_dev->spi_dev.spi_dev.max_speed_hz,
                   0);

    aw_spi_mktrans(&trans2,
                   p_buf,
                   NULL,
                   len,
                   0,
                   0,
                   0,
                   p_dev->spi_dev.spi_dev.max_speed_hz,
                   0);

    aw_spi_trans_add_tail(&spi_msg, &trans1);
    aw_spi_trans_add_tail(&spi_msg, &trans2);

    err = aw_spi_sync(&(p_dev->spi_dev.spi_dev), &spi_msg);

    AW_MUTEX_UNLOCK(p_dev->devlock);

    return err;
}

/******************************************************************************/
aw_local aw_err_t __spi_flash_erase_sector (awbl_spi_flash_dev_t  *p_dev,
                                            uint32_t              addr)
{
    struct aw_spi_message  spi_msg;
    struct aw_spi_transfer trans;
    uint8_t                cmd_buf[4];
    aw_err_t                err;

    AW_MUTEX_LOCK(p_dev->devlock, AW_SEM_WAIT_FOREVER);

    if (AW_OK != __spi_flash_wait_busy(p_dev)) {
        return -ETIME;
    }

    __spi_flash_enable_wr(p_dev);

    if (AW_OK != __spi_flash_wait_busy(p_dev)) {
        return -ETIME;
    }

    aw_spi_msg_init(&spi_msg, NULL, NULL);

    cmd_buf[0] = 0x20;
    cmd_buf[1] = (addr & 0xFFFFFF) >> 16;
    cmd_buf[2] = (addr & 0xFFFF) >> 8;
    cmd_buf[3] = addr & 0xFF;

    aw_spi_mktrans(&trans,
                   cmd_buf,
                   NULL,
                   4,
                   0,
                   0,
                   0,
                   p_dev->spi_dev.spi_dev.max_speed_hz,
                   0);

    aw_spi_trans_add_tail(&spi_msg, &trans);

    err = aw_spi_sync(&(p_dev->spi_dev.spi_dev), &spi_msg);

    AW_MUTEX_UNLOCK(p_dev->devlock);

    return err;

}


/******************************************************************************/
aw_local int __spi_flash_ioctl (struct aw_block_dev *dev,
                                int                 cmd,
                                void                *arg)
{
    int ret = 0;

    switch (cmd) {
    case AW_BDIO_GET_GEOMETRY:
        if (NULL == arg) {
            ret = -EINVAL;
        } else {
            struct aw_block_dev_geometry *g = arg;
            g->heads          = 1;
            g->cylinders      = 1;
            g->total_blocks   = dev->nblocks;
            g->secs_per_track = dev->nblocks;
            g->block_size     = dev->block_size;
        }
        break;
    case AW_BDIO_SOFT_EJECT:
    case AW_BDIO_HARD_EJECT:
        aw_event_raise(&g_block_dev_event_remove, dev, EVENT_PROC_FLAG_ASYNC);
        break;
    case AW_BDIO_GET_BASE_NAME:
        ret = aw_block_dev_name(dev, arg);
        break;
    case AW_BDIO_SYNC:
        break;
    case AW_BDIO_TEST:
        break;
    case AW_BDIO_STACK_COMPLETE:
        break;
    default:
        ret = -ENOTSUP;
        break;
    }
    return ret;
}

/******************************************************************************/
aw_local int __spi_flash_xfr (struct aw_block_dev *dev,
                              struct aw_block_io  *bio)
{
    uint_t                  nbytes;
    sector_t                nblocks;
    awbl_spi_flash_dev_t    *p_dev = \
            AW_CONTAINER_OF(dev, awbl_spi_flash_dev_t, bd_dev);
    __SPI_FLASH_DEVINFO_DECL(p_info, p_dev);

    /* iterate through the chain, running each bio as we get it */
    for (; bio != NULL; bio = bio->next) {
        nblocks = bio->nbytes / dev->block_size; /* fits in the disk */

        /* if our starting block number is bad, done with error */
        if (dev->nblocks <= bio->blk_no) {
            bio->residual = bio->nbytes;
            aw_block_io_complete(bio, -ENOSPC);
            continue;
        }
        /* if we overrun the end of the disk, truncate the block number */
        if (dev->nblocks < bio->blk_no + nblocks) {
            nblocks = dev->nblocks - bio->blk_no;
        }
        /* calculate the real size and residual */
        nbytes          = (uint_t)nblocks * dev->block_size;
        bio->residual   = bio->nbytes - nbytes;

        /* now we actually do the operation */
        if (0 == nblocks) {
            /* if we have less than 1 block, set the resid */
            bio->residual = bio->nbytes;
        } else if (bio->flags & AW_BLOCK_IO_READ) {
            __spi_flash_hs_read_nbytes(
                                p_dev,
                                (bio->blk_no + p_info->reserved_nblks)
                                * dev->block_size,
                                bio->data,
                               nbytes);
        } else {
            uint32_t  npages = (dev->block_size) / (p_info->page_size);
            uint32_t  addr = (bio->blk_no + p_info->reserved_nblks)
                                    * dev->block_size;
            uint8_t  *ptr = bio->data;

            while(nblocks--) {
                __spi_flash_erase_sector(p_dev, addr);
                while (npages--) {
                    __spi_flash_program_nbyte(
                                    p_dev,
                                    addr,
                                    ptr,
                                    p_info->page_size);
                    addr += p_info->page_size;
                    ptr  += p_info->page_size;
                }
            }
        }
        aw_block_io_complete(bio, 0);
    }
    return 0;
}

/******************************************************************************/
aw_local int __spi_flash_dump (struct aw_block_dev *dev,
                               sector_t             pos,
                               void                *data,
                               size_t               n)
{
    struct aw_block_io bio;

    bio.dev      = dev;
    bio.blk_no   = pos;
    bio.nbytes   = n;
    bio.data     = data;
    bio.error    = 0;
    bio.flags    = AW_BLOCK_IO_WRITE;
    bio.complete = NULL;
    bio.next     = NULL;

    __spi_flash_xfr(dev, &bio);

    /* Assume that it is synchronous - don't copy this ! */
    return bio.error;
}

#if 0
/******************************************************************************/
aw_local const struct aw_block_dev_funcs __g_spi_flash_funcs = {
    __spi_flash_ioctl,
    __spi_flash_xfr,
    __spi_flash_dump
};
#endif


/******************************************************************************/
aw_local aw_err_t __spiflash_nvram_get (struct awbl_dev *p_dev,
                                        char            *p_name,
                                        int              unit,
                                        void            *p_buf,
                                        int              offset,
                                        int              len)
{
    __SPI_FLASH_DEVINFO_DECL(p_devinfo, p_dev);
    const struct awbl_nvram_segment *p_seg = p_devinfo->p_seglst;

    int         i;
    int         copylen;
    aw_err_t    ret;

    for (i = 0; i < p_devinfo->seglst_count; i++) {
        if ((p_seg->unit == unit) &&
            (strcmp(p_seg->p_name, p_name) == 0)) {
            copylen = len;
            if (offset + len > p_seg->seg_size) {
                copylen = p_seg->seg_size - offset;
                if (copylen < 0) {
                    return -EIO;
                }
            }
            if (p_seg->seg_addr + offset + copylen  >
                (p_devinfo->block_size * p_devinfo->nblocks)) {
                return  -ENXIO;
            }

            ret = __spi_flash_hs_read_nbytes (
                    (awbl_spi_flash_dev_t *)p_dev,
                    p_seg->seg_addr + offset,
                    (uint8_t *)p_buf,
                    copylen);

            return ret != AW_OK ? -EIO : AW_OK;
        }
        p_seg++;
    }

    return -ENXIO;
}


/******************************************************************************/
aw_local aw_err_t __spiflash_nvram_set (struct awbl_dev *p_dev,
                                        char            *p_name,
                                        int              unit,
                                        char            *p_buf,
                                        int              offset,
                                        int              len)
{
    __SPI_FLASH_DEVINFO_DECL(p_devinfo, p_dev);
    const struct awbl_nvram_segment *p_seg = p_devinfo->p_seglst;

    int         i;
    int         copylen;
    aw_err_t    ret;

    for (i = 0; i < p_devinfo->seglst_count; i++) {
        if ((p_seg->unit == unit) && (strcmp(p_seg->p_name, p_name) == 0)) {

            uint32_t  block_curr_addr   = 0;
            uint32_t  current_addr      = 0;
            uint32_t  curr_copy_size    = 0;

            copylen = len;
            if (offset + len > p_seg->seg_size) {
                copylen = p_seg->seg_size - offset;
                if (copylen < 0) {
                    return -EIO;
                }
            }
            if (p_seg->seg_addr + offset + copylen  >
                (p_devinfo->block_size * p_devinfo->nblocks)) {
                return  -ENXIO;
            }

            /* 计算当前的存储地址 */
            current_addr = p_seg->seg_addr + offset;
            if (current_addr%p_devinfo->page_size != 0) {
                return  -AW_EPERM;
            }

            block_curr_addr = current_addr/p_devinfo->block_size*p_devinfo->block_size;

            if (current_addr%p_devinfo->block_size == 0) {
                /* 擦除块区  */
                ret = __spi_flash_erase_sector ((awbl_spi_flash_dev_t *)p_dev,
                        block_curr_addr);
                if (ret != AW_OK) {
                    return  ret;
                }
            }

            for (curr_copy_size = 0; curr_copy_size < copylen; ) {

                if (current_addr - block_curr_addr == p_devinfo->block_size) {
                    /* 擦除块区  */
                    ret = __spi_flash_erase_sector ((awbl_spi_flash_dev_t *)p_dev,
                            block_curr_addr);
                    if (ret != AW_OK) {
                        return  ret;
                    }
                    block_curr_addr += p_devinfo->block_size;
                }

                ret = __spi_flash_program_nbyte ((awbl_spi_flash_dev_t *)p_dev,
                                                 current_addr,
                                                 (uint8_t *)p_buf,
                                                 p_devinfo->page_size);
                if (ret != AW_OK) {
                    return  ret;
                }

                current_addr += p_devinfo->page_size;
                p_buf += p_devinfo->page_size;
                curr_copy_size += p_devinfo->page_size;
            }

            return  AW_OK;
        }
        p_seg++;
    }

    return -ENXIO;
}

/******************************************************************************/
AWBL_METHOD_IMPORT(awbl_nvram_get);
AWBL_METHOD_IMPORT(awbl_nvram_set);

aw_local aw_const struct awbl_dev_method __g_spiflash_methods[] = {
    AWBL_METHOD(awbl_nvram_get, __spiflash_nvram_get),
    AWBL_METHOD(awbl_nvram_set, __spiflash_nvram_set),
    AWBL_METHOD_END
};

#ifdef AW_DRV_MTD_DEV
/******************************************************************************/
aw_local int __check_offs_len(struct aw_mtd_info  *mtd,
                              off_t               offs,
                              size_t              len)
{
    __MTD_DEV_TO_FLASH_DEC(p_flash, mtd);

    if (mtd == NULL) {
        return -EINVAL;
    }

    /* Start address must align on block boundary */
    if (offs & p_flash->erase_align_mask) {
        return -EINVAL;
    }

    /* Length must align on block boundary */
    if (len & p_flash->erase_align_mask) {
        return -EINVAL;
    }

    /* Do not allow past end of device */
    if (offs + len > mtd->size) {
        return -EINVAL;
    }

    return AW_OK;
}

/******************************************************************************/
aw_local int __spiflash_mtd_erase ( struct aw_mtd_info          *mtd,
                                    struct aw_mtd_erase_info    *instr)
{
    __MTD_DEV_TO_FLASH_DEC(p_flash, mtd);
    __SPI_FLASH_DEVINFO_DECL(p_info, &p_flash->spi_dev);
    int                             err;
    size_t                          len;
    int                             addr;

    if (mtd == NULL || instr == NULL) {
        return -EINVAL;
    }

    if (__check_offs_len(mtd, instr->addr, instr->len)) {
        return -EINVAL;
    }

    instr->fail_addr    = AW_MTD_ERASE_FAIL_ADDR_UNKNOWN;
    instr->state        = AW_MTD_ERASE_PROCESSING;

    /* get the start address */
    addr =  (int)(instr->addr + p_flash->addr_offset);

    len = instr->len;

    while (len) {

        err = __spi_flash_erase_sector( p_flash,
                                        addr);
        /* See if block erase succeeded */
        if (err != AW_OK) {
            instr->state     = AW_MTD_ERASE_FAILED;
            instr->fail_addr = (off_t)(addr - p_flash->addr_offset);
            goto _exit;
        }

        /* Increment page address and decrement length */
        len  -= p_info->block_size;
        addr += p_info->block_size;
    }

    instr->state = AW_MTD_ERASE_DONE;
    aw_mtd_erase_callback(instr);

_exit:
    err = (instr->state == AW_MTD_ERASE_DONE) ? 0 : -EIO;
    return err;
}

/******************************************************************************/
aw_local int __spiflash_mtd_read (struct aw_mtd_info  *mtd,
                                  off_t               from,
                                  size_t              len,
                                  size_t              *retlen,
                                  void                *buf)
{
    __MTD_DEV_TO_FLASH_DEC(p_flash, mtd);
    int                             err;
    int                             addr;

    if (mtd == NULL || buf == NULL || len == 0) {
        return -EINVAL;
    }

    /* Do not allow reads past end of device */
    if ((from + len) > mtd->size) {
        return -EINVAL;
    }
    if (!len) {
        return AW_OK;
    }

    addr = from + p_flash->addr_offset;
    err = __spi_flash_hs_read_nbytes(p_flash,
                                     addr,
                                     buf,
                                     len);
    if (err == AW_OK) {
        *retlen = len;
    }

    return err;
}

/******************************************************************************/
aw_local int __spiflash_mtd_write (struct aw_mtd_info   *mtd,
                                  off_t                 to,
                                  size_t                len,
                                  size_t                *retlen,
                                  const void            *buf)
{
    __MTD_DEV_TO_FLASH_DEC(p_flash, mtd);
    int                             err;
    int                             addr;
    int                             offs;
    int                             bytes;
    int                             length = len;
    uint8_t                         *ptr = (uint8_t *)buf;

    if (mtd == NULL || buf == NULL || len == 0) {
        return -EINVAL;
    }

    /* Do not allow write past end of device */
    if ((to + len) > mtd->size) {
        return -EINVAL;
    }
    if (!length) {
        return AW_OK;
    }

    /* get the start address */
    addr = (int)(to + p_flash->addr_offset);
    offs = (int)(addr & (mtd->write_size - 1));

    while (length) {
        bytes = min(mtd->write_size - offs, length);

        err = __spi_flash_program_nbyte (p_flash,
                                         addr,
                                         ptr,
                                         bytes);
        if (err != AW_OK) {
            goto _exit;
        }

        ptr    += bytes;
        length -= bytes;
        offs   =  0;
        addr   += bytes;
    }

_exit:
    *retlen = len - length;
    return err;
}

/******************************************************************************/
aw_local const struct aw_mtd_ops __g_mtd_ops = {
    __spiflash_mtd_erase,       /* mtd_erase */
    NULL,                       /* mtd_sync */
    __spiflash_mtd_read,        /* mtd_read */
    __spiflash_mtd_write,       /* mtd_write */
    NULL,                       /* mtd_panic_write */
    NULL,                       /* mtd_oob_read */
    NULL,                       /* mtd_oob_write */
    NULL,                       /* mtd_block_is_bad */
    NULL,                       /* mtd_block_mark_bad */
    NULL,                       /* mtd_is_locked */
    NULL,                       /* mtd_lock */
    NULL,                       /* mtd_unlock */
};
#endif

/******************************************************************************/
aw_local void __spi_flash_inst_init1 (struct awbl_dev *p_awdev)
{
    return ;
}

/******************************************************************************/
aw_local void __spi_flash_inst_init2 (struct awbl_dev *p_awdev)
{
    __SPI_FLASH_DEVINFO_DECL(p_info, p_awdev);
    __SPI_DEV_TO_FLASH_DEC(p_dev, p_awdev);

    /* platform initialization */
    if (p_info->pfunc_plfm_init != NULL) {
        p_info->pfunc_plfm_init();
    }

    AW_MUTEX_INIT(p_dev->devlock, AW_SEM_Q_PRIORITY);

    /* SPI device */
    aw_spi_mkdev(&(p_dev->spi_dev.spi_dev),
                 p_dev->spi_dev.super.p_devhcf->bus_index,
                 8,
                 p_info->spi_mode,
                 p_info->spi_speed,
                 p_info->spi_cs_pin,
                 NULL);

    aw_spi_setup(&(p_dev->spi_dev.spi_dev));
    if (p_info->spi_speed != p_dev->spi_dev.spi_dev.max_speed_hz) {
        AW_ERRF(("SPI flash: max speed %d not be supported, change to %d.\n",
                p_info->spi_speed,
                p_dev->spi_dev.spi_dev.max_speed_hz));
    }

#ifdef AW_DRV_MTD_DEV
    /* MTD device */
    p_dev->mtd.size              = (p_info->nblocks - p_info->reserved_nblks)
                                            * p_info->block_size;
    p_dev->mtd.type              = AW_MTD_TYPE_NOR_FLASH;
    p_dev->mtd.flags             = AW_MTD_FLAGS_NOR_FLASH;
    p_dev->mtd.erase_size        = p_info->block_size;
    p_dev->mtd.write_size        = p_info->page_size;
    p_dev->mtd.write_buf_size    = 0;
    p_dev->mtd.oob_size          = 0;
    p_dev->mtd.oob_avail         = 0;
    p_dev->mtd.bitflip_threshold = 0;
    p_dev->mtd.ecc_strength      = 0;
    p_dev->mtd.oob_layout        = NULL;
    p_dev->mtd.ops               = &__g_mtd_ops;

    p_dev->erase_align_mask = (~0) % p_info->block_size;
    p_dev->addr_offset      = p_info->reserved_nblks * p_info->block_size;

    if (aw_mtd_dev_add( &p_dev->mtd,
                        p_info->name,
                        NULL) != AW_OK) {
        AW_ERRF(("SPI flash: adding mtd dev failed.\n"));
    }
#endif

#ifdef AW_DRV_BLOCK_DEV
    /* block device */
    if (p_info->nblocks > p_info->reserved_nblks) {
        aw_block_dev_attach(&p_dev->bd_dev,
                         &__g_spi_flash_funcs,
                         p_info->name,
                         p_info->block_size,
                         p_info->nblocks - p_info->reserved_nblks);
    }
#endif
    return;
}

/******************************************************************************/
aw_local void __spi_flash_inst_connect (struct awbl_dev *p_awdev)
{

//#define __ERASE_BLOCKS__ 2048
#ifdef __ERASE_BLOCKS__
    __SPI_FLASH_DEVINFO_DECL(p_info, p_awdev);
    __SPI_DEV_TO_FLASH_DEC(p_dev, p_awdev);
    int i;
    for (i = 0; i < __ERASE_BLOCKS__; i++) {
        __spi_flash_erase_sector(p_dev, i * p_info->block_size);
    }
#endif
    return ;
}

/******************************************************************************/
aw_local aw_const struct awbl_drvfuncs __g_spi_flash_drvfuncs = {
        __spi_flash_inst_init1,
        __spi_flash_inst_init2,
        __spi_flash_inst_connect
};

/******************************************************************************/
aw_local aw_const awbl_plb_drvinfo_t __g_spi_flash_drv_registration = {
    {
        AWBL_VER_1,                             /* awb_ver */
        AWBL_BUSID_SPI,                         /* bus_id */
        AWBL_SPI_FLASH_NAME,                    /* p_drvname */
        &__g_spi_flash_drvfuncs,                /* p_busfuncs */
        &__g_spiflash_methods[0],               /* p_methods */
        NULL                                    /* pfunc_drv_probe */
    }
};

/******************************************************************************/
void awbl_spi_flash_drv_register (void)
{
    aw_err_t err;
    err = awbl_drv_register((struct awbl_drvinfo *)&__g_spi_flash_drv_registration);
    while (err != 0) {
    }
    return;
}
