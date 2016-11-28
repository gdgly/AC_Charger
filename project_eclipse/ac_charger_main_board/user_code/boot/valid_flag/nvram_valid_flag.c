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

#include <boot/valid_flag/nvram_valid_flag.h>
#include "aw_nvram.h"

#define  NVRAM_BUF_SIZE  (256)

/* 由于 SPI FLASH 需要写 256 字节，所以需要开辟一个缓冲区 */
aw_local char  __g_valid_buf[NVRAM_BUF_SIZE] = {0};

aw_local aw_err_t  __nvram_valid_flag_set(struct valid_flag *p_valid, bool_t  is_valid)
{
    aw_err_t  ret = AW_OK;
    uint32_t  valid_key = 0;

    struct nvram_valid_flag *p_nvram_valid = (struct nvram_valid_flag *)p_valid;

    int  buf_size;

    if (NVRAM_VALID_SIZE_4 == p_nvram_valid->valid_size) {
        buf_size = 4;
    } else if (NVRAM_VALID_SIZE_256 == p_nvram_valid->valid_size) {
        buf_size = NVRAM_BUF_SIZE;
    }

    /* 写有效位 */
    if (is_valid) {
        valid_key = VALID_FLAG_KEY;
    } else {
        valid_key = ~VALID_FLAG_KEY;
    }

    __g_valid_buf[0] = valid_key&0xFF;
    __g_valid_buf[1] = (valid_key>>8)&0xFF;
    __g_valid_buf[2] = (valid_key>>16)&0xFF;
    __g_valid_buf[3] = (valid_key>>24)&0xFF;

    ret = aw_nvram_set(p_nvram_valid->p_name,
                       0,
                       __g_valid_buf,
                       0,
                       buf_size
                       );
    if (ret != AW_OK) {
        return  ret;
    }

    return  AW_OK;
}

aw_local aw_err_t  __nvram_valid_flag_get(struct valid_flag *p_valid, bool_t  *p_is_valid)
{
    uint32_t  valid_key;
    aw_err_t  ret = AW_OK;

    struct nvram_valid_flag *p_nvram_valid = (struct nvram_valid_flag *)p_valid;

    ret = aw_nvram_get(p_nvram_valid->p_name,
                       0,
                       (char *)&valid_key,
                       0,
                       sizeof(valid_key));
    if (ret != AW_OK) {
        return  ret;
    }

    if (VALID_FLAG_KEY == valid_key) {
        *p_is_valid = TRUE;
    } else {
        *p_is_valid = FALSE;
    }

    return  AW_OK;
}

struct valid_flag  *nvram_valid_flag_ctor(struct nvram_valid_flag *p_nvram_valid,
                                          char                    *p_name,
                                          nvram_valid_size_t       valid_size)
{
    if ((NULL == p_nvram_valid) ||
        (NULL == p_name)) {
        return  NULL;
    }

    p_nvram_valid->super.pfun_valid_flag_get = __nvram_valid_flag_get;
    p_nvram_valid->super.pfun_valid_flag_set = __nvram_valid_flag_set;

    p_nvram_valid->p_name       = p_name;
    p_nvram_valid->valid_size   = valid_size;

    return  &p_nvram_valid->super;
}

