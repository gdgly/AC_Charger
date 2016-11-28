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
 * \brief USB host mass storage class
 *
 * \internal
 * \par modification history:
 * - 1.00 15-05-23  deo, first implementation
 * \endinternal
 */

#ifndef __AW_USBH_MS_TRANSFER_H
#define __AW_USBH_MS_TRANSFER_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#define MS_PR_CBI               0x00    /* Control/Bulk/Interrupt.   */
#define MS_PR_CB                0x01    /* Control/Bulk.             */
#define MS_PR_BULK              0x50    /* bulk only.                */
#define MS_PR_ANY               0xFF    /* Don't care of protocol.   */

/* class request bRequest */
#define MS_BULK_RESET           0xff
#define MS_BULK_GET_MAX_LUN     0xfe
#define MS_CBI_ADSC             0x00


#define MS_CBW_SIGNATURE        0x43425355
#define MS_CSW_SIGNATURE        0x53425355

#define MS_CBW_FLAG_IN          0x80
#define MS_CBW_FLAG_OUT         0x00

/* CBW */
struct aw_usbh_bulk_only_cbw
{
    uint32_t signature;
    uint32_t tag;
    uint32_t data_trf_len;
    uint8_t  flags;
    uint8_t  lun;
    uint8_t  cb_length;
    uint8_t  cb[16];
};

/* CSW */
struct aw_usbh_bulk_only_csw
{
    uint32_t signature;
    uint32_t tag;
    uint32_t data_residue;
    uint8_t  status;
};
/****************************************************************************/
aw_err_t aw_usbh_ms_bulk_get_max_lun (
            struct awbl_usbh_mass_storage *p_ms,
            uint8_t                       *p_maxlun);

/****************************************************************************/
aw_err_t aw_usbh_ms_bulk_reset (struct awbl_usbh_mass_storage *p_ms);

/****************************************************************************/
aw_err_t aw_usbh_ms_transport (struct awbl_usbh_ms_lun *p_lun,
                               void                    *p_cmd,
                               uint8_t                 cmd_len,
                               void                    *p_data,
                               uint32_t                data_len,
                               uint8_t                 dir);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AW_USBH_MS_TRANSFER_H */
