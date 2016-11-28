/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Data Co-Processor (DCP) for i.MX28 .
 *
 * \internal
 * \par modification history:
 * - 1.00 14-06-05, zen, first implementation.
 * \endinternal
 */

#ifndef __AWBL_IMX28_DCP_H
#define __AWBL_IMX28_DCP_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
typedef struct {
    volatile uint32_t dat; /**< \brief data value (both read and write) register */
    volatile uint32_t set; /**< \brief data bits field set register */
    volatile uint32_t clr; /**< \brief data bits field clear register */
    volatile uint32_t tog; /**< \brief data bits field toggle register */
} __imx28_reg_t;

/**
 * \addtogroup grp_imx28_dcp
 * @{
 */

/** \brief DCP cipher context */
typedef struct imx28x_dcp_cipher_ctx {
    uint8_t data[16];
} imx28x_dcp_cipher_ctx_t;

/** \brief DCP hash context */
typedef struct imx28x_dcp_hash_ctx {
    uint8_t data[36];
} imx28x_dcp_hash_ctx_t;

/** \brief Channel context */
typedef struct imx28x_dcp_chan_ctx {
    imx28x_dcp_cipher_ctx_t cipher_ctx;
    imx28x_dcp_hash_ctx_t   hash_ctx;
} imx28x_dcp_chan_ctx_t;

/** \brief DCP Context Buffer Layout */
typedef struct imx28x_dcp_ctx {
    imx28x_dcp_chan_ctx_t chan_ctx[4]; /* channel[4:0] */
} imx28x_dcp_ctx_t;

/** \brief DCP Work Packet Structure */
typedef struct imx28x_dcp_packet {
    uint32_t next;
    uint32_t ctrl0;
    uint32_t ctrl1;
    uint32_t src;
    uint32_t dst;
    uint32_t nbytes;
    uint32_t payld;
    uint32_t stat;
} imx28x_dcp_packet_t;

typedef struct imx28x_dcp_chan_regs {
    volatile __imx28_reg_t cmd_ptr;
    volatile __imx28_reg_t sema;
    volatile __imx28_reg_t stat;
    volatile __imx28_reg_t opts;
} imx28x_dcp_chan_regs_t;

/** \brief DCP registers */
typedef struct imx28x_dcp_regs {
    volatile __imx28_reg_t ctrl;
    volatile __imx28_reg_t stat;
    volatile __imx28_reg_t chan_ctrl;
    volatile __imx28_reg_t capability0;
    volatile __imx28_reg_t capability1;
    volatile __imx28_reg_t context;
    volatile __imx28_reg_t key;
    volatile __imx28_reg_t key_data;
    volatile __imx28_reg_t packet0;
    volatile __imx28_reg_t packet1;
    volatile __imx28_reg_t packet2;
    volatile __imx28_reg_t packet3;
    volatile __imx28_reg_t packet4;
    volatile __imx28_reg_t packet5;
    volatile __imx28_reg_t packet6;
    volatile __imx28_reg_t reserved0[1];
    volatile imx28x_dcp_chan_regs_t chan[4];
    volatile __imx28_reg_t reserved1[32];
    volatile __imx28_reg_t dbg_select;
    volatile __imx28_reg_t dbg_data;
    volatile __imx28_reg_t ch3_pagetable;
    volatile __imx28_reg_t ch3_version;
} imx28x_dcp_regs_t;

void 	 aw_imx28_dcp_init(uint32_t reg_base_addr);
uint32_t aw_imx28_dcp_memcpy (void *pdst, void *psrc, uint32_t len);
uint32_t aw_imx28_dcp_endian_conversion (void *pdst, void *psrc, uint32_t len);
void 	 aw_imx28_dcp_eth_endian_conversion (void *pdst, void *psrc, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* } __IMX28_DCP_H */

/* end of file */

