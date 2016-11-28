/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

#ifndef __AWBL_HWCONF_LPC5410X_RTC_H
#define __AWBL_HWCONF_LPC5410X_RTC_H

#include "driver/rtc/awbl_ametal_rtc.h"
#include "amdr_rtc.h"

#ifdef AW_DEV_LPC17XX_RTC

/** \brief RTC �豸��Ϣ */
const amdr_rtc_devinfo_t  g_rtc_devinfo = {
    AMHW_RTC,                /**< \brief RTC */
    INUM_RTC
};

/** \brief RTC �豸ʵ�� */
amdr_rtc_dev_t            g_rtc_dev;

/** \brief RTCƽ̨��ʼ�� */
void amhw_plfm_rtc_init (void)
{
    amhw_power_periph_up(AMHW_POWER_RTC);
    
}

/** \brief ���RTCƽ̨��ʼ�� */
void amhw_plfm_rtc_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_RTC);
}

/* �豸��Ϣ */
aw_local aw_const struct awbl_ametal_rtc_param  __g_ametal_rtc_param = {
   {
        LPC17XX_RTC_ID                        /* RTC_ID  */
   },
   &g_rtc_dev,
   &g_rtc_devinfo,
   (pfn_rtc_init_t)amdr_rtc_init,
   amhw_plfm_rtc_init,
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_rtc_dev __g_ametal_rtc_dev;

#define AWBL_HWCONF_LPC17XX_RTC   \
{                                 \
    AWBL_AMETAL_RTC_NAME,         \
    0,                            \
    AWBL_BUSID_PLB,               \
    0,                            \
    &(__g_ametal_rtc_dev.dev),    \
    &(__g_ametal_rtc_param)       \
},
#else

#define AWBL_HWCONF_LPC17XX_RTC

#endif

#endif /* AW_DEV_LPC17XX_RTC */
