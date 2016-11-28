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

#ifndef __NVRAM_VALID_FLAG_H
#define __NVRAM_VALID_FLAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "valid_flag.h"

typedef enum {
    NVRAM_VALID_SIZE_4,
    NVRAM_VALID_SIZE_256
} nvram_valid_size_t;

struct nvram_valid_flag {
    struct valid_flag       super;
    char                   *p_name;
    nvram_valid_size_t      valid_size;
};

struct valid_flag  *nvram_valid_flag_ctor(struct nvram_valid_flag *p_nvram_valid,
                                          char                    *p_name,
                                          nvram_valid_size_t       valid_size);

#ifdef __cplusplus
}
#endif

#endif /* __NVRAM_VALID_FLAG_H */
