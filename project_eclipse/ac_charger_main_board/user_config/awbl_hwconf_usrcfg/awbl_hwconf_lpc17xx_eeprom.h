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

/*******************************************************************************
  EEPROM������������Ϣ
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_EEPROM

#include "driver/eeprom/awbl_lpc17xx_eeprom.h"
#include "ametal.h"

typedef int (* pfunc_eeprom_init_t)(void *, void *);

/**
 * \brief EEPROM �жϸ���
 */
#define EEPROM_INT_COUNT    2

/** \brief ���Ŵ�����Ϣ�ڴ� */
static amdr_eeprom_intcb_info_t __g_eeprom_intcb_infos[EEPROM_INT_COUNT];

/**
 * \brief �ڲ�EEPROM �洢�������б�
 */
aw_local aw_const struct awbl_nvram_segment __g_lpc17xx_eeprom_seglst[] = {
    /* ����һ���洢�Σ��洢������, ��Ԫ��, ��ʼ��ַ������ */
    {"lpc17_eeprom", 0, 0, 64*64},        /* ����EEPROM�洢�ռ� */
    {"lpc17_eeprom", 1, 0, 8},            /* ׮ID */
    {"lpc17_eeprom", 2, 8, 1},            /* ��������ַ */
    {"lpc17_eeprom", 3, 9, 48},           /* ��������ַ */
    {"lpc17_eeprom", 4, 62, 2},           /* ����Ŀ��Ϣ */
    {"lpc17_eeprom", 5, 64, 90*44},       /* ��Ŀ���� */
    {"lpc17_eeprom", 6, 64 + 90*44, 72},  /* ��Կ */
};

/** \brief EEPROM �豸��Ϣ */
const amdr_eeprom_devinfo_t g_eeprom_devinfo = {

	AMHW_EEPROM,              /**< \brief EEPROM�Ļ���ַ                  */

	__g_eeprom_intcb_infos,   /**< \brief ���Ŵ�����Ϣ�ڴ�              */

	INUM_EEPROM,              /**< \brief EEPROM�жϺ�             */

	EEPROM_INT_COUNT,         /**< \brief ʹ�õ��Ĺܽ��ж���Ŀ          */
};

/** \brief EEPROM�豸ʵ�� */
amdr_eeprom_dev_t g_eeprom_dev;

/* �豸��Ϣ */
aw_local aw_const struct awbl_lpc17xx_eeprom_param __g_lpc17xx_eeprom_param = {
	&__g_lpc17xx_eeprom_seglst[0],
	AW_NELEMENTS(__g_lpc17xx_eeprom_seglst),
    &g_eeprom_dev,                           /* EEPROM �豸               */
    &g_eeprom_devinfo,                       /* EEPROM �豸��Ϣʱ         */
    (pfunc_eeprom_init_t)amdr_eeprom_init,   /* EEPROM ��ʼ������         */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_lpc17xx_eeprom_dev __g_lpc17xx_eeprom_dev;

#define AWBL_HWCONF_LPC17XX_EEPROM                  \
    {                                               \
        AWBL_LPC17XX_EEPROM_NAME,                   \
        0,                                          \
        AWBL_BUSID_PLB,                             \
        0,                                          \
        (struct awbl_dev *)&__g_lpc17xx_eeprom_dev, \
        &__g_lpc17xx_eeprom_param                   \
    },

#else

#define  AWBL_HWCONF_LPC17XX_EEPROM

#endif    /* AW_DEV_LPC17XX_EEPROM */

/* end of file */
