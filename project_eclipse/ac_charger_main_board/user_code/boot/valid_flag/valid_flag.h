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

#ifndef __VALID_FLAG_H
#define __VALID_FLAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apollo.h"

#define  VALID_FLAG_KEY    0x55443322

struct valid_flag {
    aw_err_t  (*pfun_valid_flag_set)(struct valid_flag *p_valid, bool_t  is_valid);
    aw_err_t  (*pfun_valid_flag_get)(struct valid_flag *p_valid, bool_t *p_is_valid);
};

aw_local aw_inline aw_err_t  valid_flag_set(struct valid_flag *p_valid, bool_t  is_valid)
{
    if (p_valid != NULL) {
        return  p_valid->pfun_valid_flag_set(p_valid, is_valid);
    }

    return  -AW_EINVAL;
}

aw_local aw_inline aw_err_t  valid_flag_get(struct valid_flag *p_valid, bool_t *p_is_valid)
{
    if ((p_valid != NULL) && (p_is_valid != NULL) ) {
        return  p_valid->pfun_valid_flag_get(p_valid, p_is_valid);
    }

    return  -AW_EINVAL;
}

#ifdef __cplusplus
}
#endif

#endif /* __VALID_FLAG_H */
