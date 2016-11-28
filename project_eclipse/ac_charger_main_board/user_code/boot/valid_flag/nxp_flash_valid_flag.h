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

#ifndef __NXP_FLASH_VALID_FLAG_H
#define __NXP_FLASH_VALID_FLAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "valid_flag.h"

struct nxp_flash_valid_flag {
    struct valid_flag       super;
    uint32_t                valid_blk_num;
    uint32_t                valid_blk_addr;
#define  NXP_FLASH_COPY_BUF_SIZE  256
    char                    copy_buf[NXP_FLASH_COPY_BUF_SIZE];
};

struct valid_flag  *nxp_flash_valid_flag_ctor(struct nxp_flash_valid_flag *p_nxp_flash_valid,
                                              uint32_t                     valid_blk_num,
                                              uint32_t                     valid_blk_addr);

#ifdef __cplusplus
}
#endif

#endif /* __NXP_FLASH_VALID_FLAG_H */
