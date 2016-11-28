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

/** \brief WWDT �豸��Ϣ */
const amdr_wwdt_devinfo_t  g_wwdt_devinfo = {
    AMHW_WWDT,       /* ָ��WWDT�Ĵ������ָ�� */
};

/** \brief WWDT�豸ʵ��  */
amdr_wwdt_dev_t            g_wwdt_dev;

/** \brief WWDT ƽ̨��ʼ�� */
void amhw_plfm_wwdt_init (void)
{
}

/** \brief ���WWDT ƽ̨��ʼ�� */
void amhw_plfm_wwdt_deinit (void)
{
}

/* �豸��Ϣ */
aw_local aw_const struct awbl_ametal_wdt_param  __g_ametal_wdt_param = {
    1000,                           /* The time out is 12s  */
    &g_wwdt_dev,
    &g_wwdt_devinfo,
    (pfn_wdt_init_t)amdr_wwdt_init,
    amhw_plfm_wwdt_init,
};

/* �豸ʵ���ڴ澲̬���� */
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
