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
    lpc5410x ��׼��ʱ��������Ϣ
*******************************************************************************/

#include "ametal.h"
#include "aw_int.h"
#include "driver/pwm/awbl_ametal_pwm.h"

/*******************************************************************************
  Standard pwm configure infomation
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_PWM1

/* The PWM0 ~ PWM5 �ܽ����� */
amdr_pwm_ioinfo_t __g_pwm1_ioinfo_list[] = {
    {PIO3_24, PIO3_24_PWM1_1, PIO3_24_GPIO},
	{PIO3_25, PIO3_25_PWM1_2, PIO3_25_GPIO},
	{PIO3_26, PIO3_26_PWM1_3, PIO3_26_GPIO},
	{PIO2_3, PIO2_3_PWM1_4, PIO2_3_GPIO},
	{PIO2_4, PIO2_4_PWM1_5, PIO2_4_GPIO},
	{PIO2_5, PIO2_5_PWM1_6, PIO2_5_GPIO},
};

/** \brief pwm���ܵ��豸��Ϣ */
const amdr_pwm_devinfo_t  g_pwm1_devinfo = {
    AMHW_PWM1,                 /**< \brief ָ��PWM�Ĵ������ָ�� */
    INUM_PWM1,                 /**< \brief PWM�жϱ��           */
    &__g_pwm1_ioinfo_list[0],
    6,                         /* 6��ͨ��    */
};

/** \brief pwm���ܵ��豸���� */
amdr_pwm_dev_t  g_pwm1_dev;

/** \brief pwm���ܵ�ƽ̨��ʼ�� */
void  amhw_plfm_pwm1_init (void)
{
    /* ����PWM��Դ */
	amhw_power_periph_up(AMHW_POWER_PWM1);
}

/** \brief  ���ƽ̨��ʼ�� */
void amhw_plfm_pwm1_deinit (void)
{
    /* �ر�MCPWM��Դ */
	amhw_power_periph_down(AMHW_POWER_PWM1);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_pwm_param __g_awbl_pwm1_param = {
    &g_pwm1_dev,
    &g_pwm1_devinfo,
    {
        7,                        /* The device provide PWM min ID is 7 */
        12,                       /* The device provide PWM max ID is 12 */
    },
    (pfn_pwm_init_t)amdr_pwm_init,
    amhw_plfm_pwm1_init           /* pfunc_plfm_init */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_pwm_dev __g_awbl_pwm1_dev;

#define AWBL_HWCONF_LPC17XX_PWM1             \
    {                                       \
        AWBL_AMETAL_PWM_NAME,               \
        1,                                   \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_pwm1_dev.dev),            \
        &(__g_awbl_pwm1_param)               \
    },

#else

#define AWBL_HWCONF_LPC17XX_PWM1

#endif  /* AW_DEV_LPC17XX_PWM */

/* end of file */
