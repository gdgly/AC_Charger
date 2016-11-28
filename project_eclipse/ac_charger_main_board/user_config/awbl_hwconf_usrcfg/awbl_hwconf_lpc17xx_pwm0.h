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

#ifdef AW_DEV_LPC17XX_PWM0

/* The PWM0 ~ PWM5 �ܽ����� */
amdr_pwm_ioinfo_t __g_pwm0_ioinfo_list[] = {
	{PIO1_2,  PIO1_2_PWM0_1,  PIO1_2_GPIO},
	{PIO1_3,  PIO1_3_PWM0_2,  PIO1_3_GPIO},
	{PIO1_5,  PIO1_5_PWM0_3,  PIO1_5_GPIO},
	{PIO1_6,  PIO1_6_PWM0_4,  PIO1_6_GPIO},
	{PIO1_7,  PIO1_7_PWM0_5,  PIO1_7_GPIO},
	{PIO1_11, PIO1_11_PWM0_6, PIO1_11_GPIO},
};

/** \brief pwm���ܵ��豸��Ϣ */
const amdr_pwm_devinfo_t  g_pwm0_devinfo = {
    AMHW_PWM0,                 /**< \brief ָ��PWM�Ĵ������ָ�� */
    INUM_PWM0,                 /**< \brief PWM�жϱ��           */
    &__g_pwm0_ioinfo_list[0],
    6,                         /* 6��ͨ��    */
};

/** \brief pwm���ܵ��豸���� */
amdr_pwm_dev_t  g_pwm0_dev;

/** \brief pwm���ܵ�ƽ̨��ʼ�� */
void  amhw_plfm_pwm0_init (void)
{
    /* ����PWM��Դ */
	amhw_power_periph_up(AMHW_POWER_PWM0);
}

/** \brief  ���ƽ̨��ʼ�� */
void amhw_plfm_pwm0_deinit (void)
{
    /* �ر�MCPWM��Դ */
	amhw_power_periph_down(AMHW_POWER_PWM0);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_pwm_param __g_awbl_pwm0_param = {
    &g_pwm0_dev,
    &g_pwm0_devinfo,
    {
        1,                        /* The device provide PWM min ID is 1 */
        6,                        /* The device provide PWM max ID is 6 */
    },
    (pfn_pwm_init_t)amdr_pwm_init,
    amhw_plfm_pwm0_init           /* pfunc_plfm_init */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_pwm_dev __g_awbl_pwm0_dev;

#define AWBL_HWCONF_LPC17XX_PWM0            \
    {                                       \
        AWBL_AMETAL_PWM_NAME,               \
        0,                                  \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_pwm0_dev.dev),           \
        &(__g_awbl_pwm0_param)              \
    },

#else

#define AWBL_HWCONF_LPC17XX_PWM0

#endif  /* AW_DEV_LPC17XX_PWM */

/* end of file */
