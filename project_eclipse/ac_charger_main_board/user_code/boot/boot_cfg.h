/*******************************************************************************

*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      aworks.support@zlg.cn
*******************************************************************************/
#ifndef __BOOT_CFG_H
#define __BOOT_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#define  LPC1778_IMAGE_NAME             "ACP1000_IMG"
#define  LPC1778_IMAGE_ADDR             (0)
#define  LPC1778_IMAGE_SIZE             (1024 * 4 * 80)

#define  LPC1778_UPDATE_IMAGE_VALID     " LPC1778_UPDATE_IMAGE_VALID"
#define  LPC1778_UPDATE_IMAGE_ADDR      (LPC1778_IMAGE_ADDR + LPC1778_IMAGE_SIZE)
#define  LPC1778_UPDATE_IMAGE_SIZE      (1024 * 4)

#define  LPC1778_IMAGE_VALID            "LPC1765_IMAGE_VALID"
#define  LPC1778_IMAGE_VALID_ADDR       (LPC1778_UPDATE_IMAGE_ADDR + LPC1778_UPDATE_IMAGE_SIZE)
#define  LPC1778_IMAGE_VALID_SIZE       (1024 * 4)

#define  INTO_UPDATE_FLAG               "INTO_UPDATE_FLAG"
#define  INTO_UPDATE_FLAG_ADDR          (LPC1778_IMAGE_VALID_ADDR + LPC1778_IMAGE_VALID_SIZE)
#define  INTO_UPDATE_FLAG_SIZE          (1024 * 4)



typedef  enum  device_id{
    LPC1778_DEVICE_ID = 81,

    INVALID_DEVICE_ID,
} device_id_t;


#define  APP_RUN_START_BLK_NUM      18
#define  APP_RUN_END_BLK_NUM        28          /* 保留最后一个块，用于加密 */
#define  APP_RUN_START_BLK_ADDR     0x00020000
#define  APP_RUN_ADDR               APP_RUN_START_BLK_ADDR
#define  APP_RUN_ADDR_SP            "0x20000"
#define  APP_RUN_ADDR_PC            "0x20004"



#ifdef __cplusplus
}
#endif

#endif /* __BOOT_CFG_H */
