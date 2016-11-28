/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief i.MX28 dbg uart private header file
 *
 * \internal
 * \par modification history:
 * - 1.00 14-05-13  chenminghao, for i.MX283
 * \endinternal
 */

#ifndef __AWBL_IMX28X_DUART_PRIVATE_H /* { */
#define __AWBL_IMX28X_DUART_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/******************************************************************************/
/** \brief imx28x duart bits*/
struct __duart_reg_type{
    int len;
    int start;
};
typedef struct __duart_reg_type duart_reg_type;

duart_reg_type dr_data                        = { 8,  0};
duart_reg_type dr_fe                          = { 1,  8};
duart_reg_type dr_pe                          = { 1,  9};
duart_reg_type dr_be                          = { 1, 10};
duart_reg_type dr_oe                          = { 1, 11};

duart_reg_type ecr_fe                         = { 1,  0};
duart_reg_type ecr_pe                         = { 1,  1};
duart_reg_type ecr_be                         = { 1,  2};
duart_reg_type ecr_oe                         = { 3,  3};
duart_reg_type ecr_ec                         = { 4,  4};

duart_reg_type fr_cts                         = { 1,  0};
duart_reg_type fr_dsr                         = { 1,  1};
duart_reg_type fr_dcd                         = { 1,  2};
duart_reg_type fr_busy                        = { 1,  3};
duart_reg_type fr_rxfe                        = { 1,  4};
duart_reg_type fr_txff                        = { 1,  5};
duart_reg_type fr_rxff                        = { 1,  6};
duart_reg_type fr_txfe                        = { 1,  7};
duart_reg_type fr_ri                          = { 1,  8};

duart_reg_type ilpr_ilpdvsr                   = { 8,  0};

duart_reg_type ibrd_baud_divint               = {16,  0};

duart_reg_type fbrd_baud_divfrac              = { 6,  0};

duart_reg_type h_brk                          = { 1,  0};
duart_reg_type h_pen                          = { 1,  1};
duart_reg_type h_eps                          = { 1,  2};
duart_reg_type h_stp2                         = { 1,  3};
duart_reg_type h_fen                          = { 1,  4};
duart_reg_type h_wlen                         = { 2,  5};
duart_reg_type h_sps                          = { 1,  7};

duart_reg_type cr_uarten                      = { 1,  0};
duart_reg_type cr_siren                       = { 1,  1};
duart_reg_type cr_sirlp                       = { 1,  2};
duart_reg_type cr_lbe                         = { 1,  7};
duart_reg_type cr_txe                         = { 1,  8};
duart_reg_type cr_rxe                         = { 1,  9};
duart_reg_type cr_dtr                         = { 1, 10};
duart_reg_type cr_rts                         = { 1, 11};
duart_reg_type cr_out1                        = { 1, 12};
duart_reg_type cr_out2                        = { 1, 13};
duart_reg_type cr_rtsen                       = { 1, 14};
duart_reg_type cr_ctsen                       = { 1, 15};

duart_reg_type ifls_txiflsel                  = { 3,  0};
duart_reg_type ifls_rxiflsel                  = { 3,  3};

duart_reg_type imsc_rimim                     = { 1,  0};
duart_reg_type imsc_ctsmim                    = { 1,  1};
duart_reg_type imsc_dcdmim                    = { 1,  2};
duart_reg_type imsc_dsrmim                    = { 1,  3};
duart_reg_type imsc_rxim                      = { 1,  4};
duart_reg_type imsc_txim                      = { 1,  5};
duart_reg_type imsc_rtim                      = { 1,  6};
duart_reg_type imsc_feim                      = { 1,  7};
duart_reg_type imsc_peim                      = { 1,  8};
duart_reg_type imsc_beim                      = { 1,  9};
duart_reg_type imsc_oeim                      = { 1, 10};

duart_reg_type ris_rirmis                     = { 1,  0};
duart_reg_type ris_ctsrmis                    = { 1,  1};
duart_reg_type ris_dcdrmis                    = { 1,  2};
duart_reg_type ris_dsrrmis                    = { 1,  3};
duart_reg_type ris_rxris                      = { 1,  4};
duart_reg_type ris_txris                      = { 1,  5};
duart_reg_type ris_rtris                      = { 1,  6};
duart_reg_type ris_feris                      = { 1,  7};
duart_reg_type ris_peris                      = { 1,  8};
duart_reg_type ris_beris                      = { 1,  9};
duart_reg_type ris_oeris                      = { 1, 10};

duart_reg_type mis_rimmis                     = { 1,  0};
duart_reg_type mis_ctsmmis                    = { 1,  1};
duart_reg_type mis_dcdmmis                    = { 1,  2};
duart_reg_type mis_dsrmmis                    = { 1,  3};
duart_reg_type mis_rxmis                      = { 1,  4};
duart_reg_type mis_txmis                      = { 1,  5};
duart_reg_type mis_rtmis                      = { 1,  6};
duart_reg_type mis_femis                      = { 1,  7};
duart_reg_type mis_pemis                      = { 1,  8};
duart_reg_type mis_bemis                      = { 1,  9};
duart_reg_type mis_oemis                      = { 1, 10};

duart_reg_type icr_rimic                      = { 1,  0};
duart_reg_type icr_ctsmic                     = { 1,  1};
duart_reg_type icr_dcdmic                     = { 1,  2};
duart_reg_type icr_dsrmic                     = { 1,  3};
duart_reg_type icr_rxic                       = { 1,  4};
duart_reg_type icr_txic                       = { 1,  5};
duart_reg_type icr_rtic                       = { 1,  6};
duart_reg_type icr_feic                       = { 1,  7};
duart_reg_type icr_peic                       = { 1,  8};
duart_reg_type icr_beic                       = { 1,  9};
duart_reg_type icr_oeic                       = { 1, 10};

duart_reg_type macr_rxdmae                    = { 1,  0};
duart_reg_type macr_txdmae                    = { 1,  1};
duart_reg_type macr_dmaonerr                  = { 1,  2};

/******************************************************************************/

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* } __AWBL_IMX28X_DUART_H */

/* end of file */
