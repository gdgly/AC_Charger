/*******************************************************************************
*                                 AnyWhere
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
  RTC PCF85063 0 ������Ϣ
*******************************************************************************/
#define AW_DRV_AWBL_PCF85063
#ifdef AW_DRV_AWBL_PCF85063

#include "driver/rtc/awbl_pcf85063.h"

/**
 * \addtogroup grp_aw_plfm_ext_pcf85063_usrcfg
 * @{
 */

/* PCF85063 �豸��Ϣ */
aw_local aw_const struct awbl_pcf85063_devinfo __g_pcf85063_0_devinfo = {
    {
        1     /* RTC �豸��� */
    },
    0xA2                    /* I2C �ӻ���ַ */
};

/* PCF85063 �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_pcf85063_dev __g_pcf85063_0_dev;

#define AWBL_HWCONF_PCF85063_0   \
    {                            \
        "pcf85063",              \
        0,                       \
        AWBL_BUSID_I2C,          \
        LPC17XX_I2C0_BUSID,        \
        (struct awbl_dev *)&__g_pcf85063_0_dev,    \
        &__g_pcf85063_0_devinfo                    \
    },
#else
#define AWBL_HWCONF_PCF85063_0
#endif  /* AW_DEV_EXTEND_PCF85063_0 */

/* end of file */

