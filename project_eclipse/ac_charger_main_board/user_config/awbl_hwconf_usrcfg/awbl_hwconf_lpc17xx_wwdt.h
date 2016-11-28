/*
 * awbl_hwconf_lpc54xxx_rtc.h
 *
 *  Created on: 2014-10-13
 *      Author: wangcheng
 */

#ifndef __AWBL_HWCONF_LPC5410X_WWDT_H
#define __AWBL_HWCONF_LPC5410X_WWDT_H

#include "driver/wdt/awbl_ametal_wdt.h"
#include "ametal.h"

#ifdef AW_DEV_LPC17XX_WDT

/** \brief WWDT 设备信息 */
const amdr_wwdt_devinfo_t  g_wwdt_devinfo = {
    AMHW_WWDT,       /* 指向WWDT寄存器块的指针 */
};

/** \brief WWDT设备实例  */
amdr_wwdt_dev_t            g_wwdt_dev;

/** \brief WWDT 平台初始化 */
void amhw_plfm_wwdt_init (void)
{
}

/** \brief 解除WWDT 平台初始化 */
void amhw_plfm_wwdt_deinit (void)
{
}

/* 设备信息 */
aw_local aw_const struct awbl_ametal_wdt_param  __g_ametal_wdt_param = {
    1000,                           /* The time out is 12s  */
    &g_wwdt_dev,
    &g_wwdt_devinfo,
    (pfn_wdt_init_t)amdr_wwdt_init,
    amhw_plfm_wwdt_init,
};

/* 设备实例内存静态分配 */
aw_local struct awbl_ametal_wdt_dev __g_ametal_wdt_dev;

#define AWBL_HWCONF_LPC17XX_WDT    \
{                                  \
    AWBL_AMETAL_WDT_NAME,          \
    0,                             \
    AWBL_BUSID_PLB,                \
    0,                             \
    &(__g_ametal_wdt_dev.dev),     \
    &(__g_ametal_wdt_param)        \
},
#else   

#define AWBL_HWCONF_LPC17XX_WDT

#endif  /* AWBL_HWCONF_LPC17XX_WDT         */

#endif  /* AW_DEV_LPC17XX_WDT */
