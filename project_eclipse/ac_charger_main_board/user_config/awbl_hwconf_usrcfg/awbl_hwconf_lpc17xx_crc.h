/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/


#ifndef __AWBL_HWCONF_LPC17XX_CRC_H
#define __AWBL_HWCONF_LPC17XX_CRC_H

#include "ametal.h"
#include "driver/crc/awbl_ametal_crc.h"

#ifdef AW_DEV_LPC17XX_CRC

/* The CRC device information */
const amdr_crc_devinfo_t  g_crc_devinfo = {
	AMHW_CRC,                /** \brief ָ��CRC�Ĵ������ָ�� */
};

/* Define the device for CRC  */
amdr_crc_dev_t            g_crc_dev;


/** \brief CRCƽ̨��ʼ�� */
void amhw_plfm_crc_init (void)
{
}

/** \brief ���CRCƽ̨��ʼ�� */
void amhw_plfm_crc_deinit (void)
{
}

/* �豸��Ϣ */
aw_local aw_const struct awbl_ametal_crc_param  __g_ametal_crc_param = {
    &g_crc_dev,
    &g_crc_devinfo,
    (pfunc_crc_init_t)amdr_crc_init,
    amhw_plfm_crc_init,
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct  awbl_ametal_crc_dev __g_ametal_crc_dev;

#define AWBL_HWCONF_LPC17XX_CRC   \
{                                 \
    AWBL_AMETAL_CRC_NAME,         \
    0,                            \
    AWBL_BUSID_PLB,               \
    0,                            \
    &(__g_ametal_crc_dev.dev),    \
    &(__g_ametal_crc_param)       \
},
#else   /* AWBL_HWCONF_LPC17XX_CRC */

#define AWBL_HWCONF_LPC17XX_CRC

#endif

#endif /* __AWBL_HWCONF_LPC17XX_CRC_H */
