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

#include "nxp_flash_valid_flag.h"

#include "aw_int.h"
#include "amhw_iap.h"


aw_local aw_err_t  __nxp_flash_valid_flag_get(struct valid_flag *p_valid, bool_t  *p_is_valid)
{
    uint32_t  valid_key = 0;

    struct nxp_flash_valid_flag *p_nxp_flash_valid = (struct nxp_flash_valid_flag *)p_valid;

    /* 小端模式 */
    valid_key |= ((p_nxp_flash_valid->copy_buf)[0] << 0);
    valid_key |= ((p_nxp_flash_valid->copy_buf)[1] << 8);
    valid_key |= ((p_nxp_flash_valid->copy_buf)[2] << 16);
    valid_key |= ((p_nxp_flash_valid->copy_buf)[3] << 24);

    if (VALID_FLAG_KEY == valid_key) {
        *p_is_valid = TRUE;
    } else {
        *p_is_valid = FALSE;
    }

    return  AW_OK;
}

aw_local aw_err_t  __nxp_flash_valid_flag_set(struct valid_flag *p_valid, bool_t  is_valid)
{
    struct nxp_flash_valid_flag *p_nxp_flash_valid = (struct nxp_flash_valid_flag *)p_valid;

    AW_INT_CPU_LOCK_DECL(key);
    amhw_iap_stat_t stat;
    uint32_t        valid_key;

    AW_INT_CPU_LOCK(key);
    stat = amhw_iap_prepare(p_nxp_flash_valid->valid_blk_num,
                            p_nxp_flash_valid->valid_blk_num);
    stat = amhw_iap_erase_sector(p_nxp_flash_valid->valid_blk_num,
                                 p_nxp_flash_valid->valid_blk_num,
                                 g_system_clkfreq);
    AW_INT_CPU_UNLOCK(key);

    /* 写有效位 */
    if (is_valid) {
        valid_key = VALID_FLAG_KEY;
    } else {
        valid_key = ~VALID_FLAG_KEY;
    }

    AW_INT_CPU_LOCK(key);

    /* 小端模式 */
    (p_nxp_flash_valid->copy_buf)[0] = valid_key&0xFF;
    (p_nxp_flash_valid->copy_buf)[1] = (valid_key>>8)&0xFF;
    (p_nxp_flash_valid->copy_buf)[2] = (valid_key>>16)&0xFF;
    (p_nxp_flash_valid->copy_buf)[3] = (valid_key>>24)&0xFF;

    stat = amhw_iap_prepare(p_nxp_flash_valid->valid_blk_num,
                            p_nxp_flash_valid->valid_blk_num);
    stat = amhw_iap_copy(p_nxp_flash_valid->valid_blk_addr,
                         (uint32_t)p_nxp_flash_valid->copy_buf,
                         sizeof(p_nxp_flash_valid->copy_buf),
                         g_system_clkfreq);
    AW_INT_CPU_UNLOCK(key);

    /* check image save valid */
    stat = amhw_iap_compare(p_nxp_flash_valid->valid_blk_addr,
                           (uint32_t)p_nxp_flash_valid->copy_buf,
                           sizeof(p_nxp_flash_valid->copy_buf));
    if (stat != AMHW_IAP_STAT_SUCCESS) {
        return  -AW_EPERM;
    }

    return  AW_OK;
}

struct valid_flag  *nxp_flash_valid_flag_ctor(struct nxp_flash_valid_flag *p_nxp_flash_valid,
                                              uint32_t                     valid_blk_num,
                                              uint32_t                     valid_blk_addr)
{
    if (NULL == p_nxp_flash_valid) {
        return NULL;
    }

    p_nxp_flash_valid->super.pfun_valid_flag_get = __nxp_flash_valid_flag_get;
    p_nxp_flash_valid->super.pfun_valid_flag_set = __nxp_flash_valid_flag_set;

    p_nxp_flash_valid->valid_blk_num  = valid_blk_num;
    p_nxp_flash_valid->valid_blk_addr = valid_blk_addr;

    return  &p_nxp_flash_valid->super;
}
