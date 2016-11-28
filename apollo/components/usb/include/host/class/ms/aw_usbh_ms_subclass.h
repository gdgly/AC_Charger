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

#ifndef __AW_USBH_MS_SUBCLASS_H
#define __AW_USBH_MS_SUBCLASS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#define MS_SC_RBC               0x01    /* flash devices.            */
#define MS_SC_8020              0x02    /* CD's DVD's.               */
#define MS_SC_QIC               0x03    /* Tapes.                    */
#define MS_SC_UFI               0x04    /* Floppy.                   */
#define MS_SC_8070              0x05    /* Floppies(mostly).         */
#define MS_SC_SCSI              0x06    /* SCSI devices.             */
#define MS_SC_RAMD              0x13    /* Ram disk device.          */


/*---- SCSI command codes ----*/
#define TEST_UNIT_READY       0x00
#define REZERO_UNIT           0x01
#define REQUEST_SENSE         0x03
#define FORMAT_UNIT           0x04
#define READ_BLOCK_LIMITS     0x05
#define REASSIGN_BLOCKS       0x07
#define INITIALIZE_ELEMENT_STATUS 0x07
#define READ_6                0x08
#define WRITE_6               0x0a
#define SEEK_6                0x0b
#define READ_REVERSE          0x0f
#define WRITE_FILEMARKS       0x10
#define SPACE                 0x11
#define INQUIRY               0x12
#define RECOVER_BUFFERED_DATA 0x14
#define MODE_SELECT           0x15
#define RESERVE               0x16
#define RELEASE               0x17
#define COPY                  0x18
#define ERASE                 0x19
#define MODE_SENSE            0x1a
#define START_STOP            0x1b
#define RECEIVE_DIAGNOSTIC    0x1c
#define SEND_DIAGNOSTIC       0x1d
#define ALLOW_MEDIUM_REMOVAL  0x1e

#define READ_FORMAT_CAPACITIES 0x23
#define SET_WINDOW            0x24
#define READ_CAPACITY         0x25
#define READ_10               0x28
#define WRITE_10              0x2a
#define SEEK_10               0x2b
#define POSITION_TO_ELEMENT   0x2b
#define WRITE_VERIFY          0x2e
#define VERIFY                0x2f
#define SEARCH_HIGH           0x30
#define SEARCH_EQUAL          0x31
#define SEARCH_LOW            0x32
#define SET_LIMITS            0x33
#define PRE_FETCH             0x34
#define READ_POSITION         0x34
#define SYNCHRONIZE_CACHE     0x35
#define LOCK_UNLOCK_CACHE     0x36
#define READ_DEFECT_DATA      0x37
#define MEDIUM_SCAN           0x38
#define COMPARE               0x39
#define COPY_VERIFY           0x3a
#define WRITE_BUFFER          0x3b
#define READ_BUFFER           0x3c
#define UPDATE_BLOCK          0x3d
#define READ_LONG             0x3e
#define WRITE_LONG            0x3f
#define CHANGE_DEFINITION     0x40
#define WRITE_SAME            0x41
#define UNMAP                 0x42
#define READ_TOC              0x43
#define READ_HEADER           0x44
#define GET_EVENT_STATUS_NOTIFICATION 0x4a
#define LOG_SELECT            0x4c
#define LOG_SENSE             0x4d
#define XDWRITEREAD_10        0x53
#define MODE_SELECT_10        0x55
#define RESERVE_10            0x56
#define RELEASE_10            0x57
#define MODE_SENSE_10         0x5a
#define PERSISTENT_RESERVE_IN 0x5e
#define PERSISTENT_RESERVE_OUT 0x5f
#define VARIABLE_LENGTH_CMD   0x7f
#define REPORT_LUNS           0xa0
#define SECURITY_PROTOCOL_IN  0xa2
#define MAINTENANCE_IN        0xa3
#define MAINTENANCE_OUT       0xa4
#define MOVE_MEDIUM           0xa5
#define EXCHANGE_MEDIUM       0xa6
#define READ_12               0xa8
#define WRITE_12              0xaa
#define READ_MEDIA_SERIAL_NUMBER 0xab
#define WRITE_VERIFY_12       0xae
#define VERIFY_12             0xaf
#define SEARCH_HIGH_12        0xb0
#define SEARCH_EQUAL_12       0xb1
#define SEARCH_LOW_12         0xb2
#define SECURITY_PROTOCOL_OUT 0xb5
#define READ_ELEMENT_STATUS   0xb8
#define SEND_VOLUME_TAG       0xb6
#define WRITE_LONG_2          0xea
#define EXTENDED_COPY         0x83
#define RECEIVE_COPY_RESULTS  0x84
#define ACCESS_CONTROL_IN     0x86
#define ACCESS_CONTROL_OUT    0x87
#define READ_16               0x88
#define COMPARE_AND_WRITE     0x89
#define WRITE_16              0x8a
#define READ_ATTRIBUTE        0x8c
#define WRITE_ATTRIBUTE       0x8d
#define VERIFY_16             0x8f
#define SYNCHRONIZE_CACHE_16  0x91
#define WRITE_SAME_16         0x93
#define SERVICE_ACTION_IN     0x9e




/****************************************************************************/
aw_err_t aw_usbh_ms_scis_inquiry (struct awbl_usbh_ms_lun *p_lun,
                                  void                    *p_buf,
                                  uint8_t                 len);

/****************************************************************************/
aw_err_t aw_usbh_ms_scis_unit_ready(struct awbl_usbh_ms_lun *p_lun);

/****************************************************************************/
aw_err_t aw_usbh_ms_scis_read_format_capacities (
                struct awbl_usbh_ms_lun *p_lun,
                void                    *p_buf,
                uint32_t                len);

/****************************************************************************/
aw_err_t aw_usbh_ms_scis_read_capacity (
                    struct awbl_usbh_ms_lun *p_lun,
                    uint32_t                *p_nblks,
                    uint32_t                *p_blk_size);

/****************************************************************************/
aw_err_t aw_usbh_ms_scis_request_sense (struct awbl_usbh_ms_lun *p_lun,
                                        void                    *p_buf,
                                        uint8_t                 len);

/****************************************************************************/
aw_err_t aw_usbh_ms_scis_mode_sense (struct awbl_usbh_ms_lun *p_lun,
                                     void                    *p_data,
                                     uint8_t                  len);

/****************************************************************************/
aw_err_t aw_usbh_ms_scis_read10 (struct awbl_usbh_ms_lun *p_lun,
                                 uint32_t                block_addr,
                                 uint32_t                nblock,
                                 void                    *p_buf,
                                 uint32_t                len);

/****************************************************************************/
aw_err_t aw_usbh_ms_scis_write10 (struct awbl_usbh_ms_lun *p_lun,
                                  uint32_t                block_addr,
                                  uint32_t                nblock,
                                  void                    *p_buf,
                                  uint32_t                len);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AW_USBH_MS_SUBCLASS_H */
