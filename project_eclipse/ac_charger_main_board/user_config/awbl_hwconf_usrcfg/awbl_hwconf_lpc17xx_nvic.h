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
  �жϿ�����������Ϣ
*******************************************************************************/
#include "driver/intctlr/awbl_armcm_nvic.h"
#include "ametal.h"

#ifdef AW_DEV_LPC17XX_NVIC

/*******************************************************************************
  ARM Cortex-M NVIC ������Ϣ
*******************************************************************************/

/* ISR ��Ϣӳ���ڴ澲̬���� */
aw_local uint8_t __g_armcm_nvic_infomap[INUM_INTERNAL_COUNT];

/* ISR ��Ϣ�ڴ澲̬���� */
aw_local struct awbl_armcm_nvic_isrinfo
    __g_armcm_nvic_isrinfos[AW_CFG_ARMCM_NVIC_ISRINFO_COUNT];

/* NVIC �豸��Ϣ */
aw_local aw_const struct awbl_armcm_nvic_devinfo __g_armcm_nvic_devinfo = {
    
    16,
    
    {
        INUM_WWDT,                     /* ֧�ֵ���ʼ�жϺ� */
        INUM_EEPROM,                 /* ֧�ֵĽ����жϺ� */
    },

    INUM_INTERNAL_COUNT,              /* �жϸ��� */

    &__g_armcm_nvic_infomap[0],       /* ISR ӳ����Ϣ�ڴ�(��С����input_cnt) */

    AW_CFG_ARMCM_NVIC_ISRINFO_COUNT,  /* ISR ��Ϣ���� */
    &__g_armcm_nvic_isrinfos[0],      /* ISR ��Ϣ���ڴ�(��С����isrinfo_cnt) */
};

/* NVIC �豸ʵ���ڴ澲̬����*/
aw_local struct awbl_armcm_nvic_dev __g_armcm_nvic_dev;

#define AWBL_HWCONF_LPC17XX_NVIC   \
    {                              \
        AWBL_ARMCM_NVIC_NAME,      \
        0,                         \
        AWBL_BUSID_PLB,            \
        0,                         \
        (struct awbl_dev *)&__g_armcm_nvic_dev, \
        &__g_armcm_nvic_devinfo    \
    },
 
#else

#define AWBL_HWCONF_LPC17XX_NVIC

#endif  /* AW_DEV_LPC17XX_NVIC */

/* end of file */

