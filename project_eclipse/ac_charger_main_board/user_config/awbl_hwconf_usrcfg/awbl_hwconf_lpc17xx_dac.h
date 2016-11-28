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

#include "apollo.h"
#include "aw_spinlock.h"
#include "awbus_lite.h"

/*******************************************************************************
  ADC ������Ϣ
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_DAC

#include "driver/dac/awbl_ametal_dac.h"
#include "ametal.h"

/** \brief DAC �豸��Ϣ */
const amdr_dac_devinfo_t  g_dac_devinfo = {
    AMHW_DAC,                 /* ָ��DAC�Ĵ������ָ�� */
    10,                       /* DAC��������   10bits  */
    3300                      /* �ο���ѹ 3.3V        */
};

/** \brief DAC�豸ʵ��  */
amdr_dac_dev_t            g_dac_dev;

/** \brief DACƽ̨��ʼ�� */
void amhw_plfm_dac_init (void)
{
	/* ����GPIO���Ź��� , δʹ��DAC*/
	am_gpio_pin_cfg(PIO0_26,
					PIO0_26_AOUT  |
					PIO0_26_FLOAT |
					PIO0_26_ADMODE_ANALOG);

}

/** \brief ���DAC ƽ̨��ʼ�� */
void amhw_plfm_dac_deinit (void)
{
	/* DAC�ܽ�����Ϊ����ģʽ��DAC���� */
	am_gpio_pin_cfg(PIO0_26,
					PIO0_26_GPIO |
					PIO0_26_ADMODE_DIGITAL |
					PIO0_26_DAC_DISABLE);
}

/* DAC0 �豸��Ϣ */
aw_local aw_const struct awbl_ametal_dac_param __g_awbl_dac_param = {
    &g_dac_dev,
    &g_dac_devinfo,

    {
       0,        /*  the minimum channel  */
       0         /*  the maximum channel  */
    },

    (pfunc_dac_init_t)amdr_dac_init,
    amhw_plfm_dac_init
};

/* ADC �豸ʵ���ڴ澲̬����*/
aw_local struct awbl_ametal_dac_dev __g_awbl_dac_dev;

#define AWBL_HWCONF_LPC17XX_DAC      \
    {                                \
		AWBL_AMETAL_DAC_NAME,        \
        0,                           \
        AWBL_BUSID_PLB,              \
        0,                           \
        (struct awbl_dev *)&__g_awbl_dac_dev,  \
        &__g_awbl_dac_param                    \
    },

#else

#define AWBL_HWCONF_LPC17XX_DAC

#endif  /* AW_DEV_LPC17XX_DAC */

/* end of file */
