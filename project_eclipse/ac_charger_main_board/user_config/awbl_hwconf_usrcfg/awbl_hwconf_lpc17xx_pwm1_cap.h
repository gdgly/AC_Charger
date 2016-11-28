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
    lpc17xx pwm for capture
*******************************************************************************/

#include "aw_int.h"
#include "driver/cap/awbl_ametal_cap.h"
#include "ametal.h"
#include "amdr_pwm_cap.h"

#ifdef AW_DEV_LPC17XX_PWM1_CAP

/** \brief  ���� �ܽ����� */
amdr_pwm_cap_ioinfo_t __g_pwm1_cap_ioinfo_list[] = {
	{PIO1_28, PIO1_28_PCAP1_0, PIO1_28_GPIO},
	{PIO1_29, PIO1_29_PCAP1_1, PIO1_29_GPIO},
};


/** \brief pwm���ܵ��豸��Ϣ */
const amdr_pwm_cap_devinfo_t  g_pwm1_cap_devinfo = {
    AMHW_PWM1,                 /**< \brief ָ��PWM�Ĵ������ָ�� */
    INUM_PWM1,                 /**< \brief PWM�жϱ��           */
    &__g_pwm1_cap_ioinfo_list[0],
    2,                         /* 2��ͨ��    */
};

/** \brief pwm���ܵ��豸���� */
amdr_pwm_cap_dev_t  g_pwm1_cap_dev;

/** \brief pwm���ܵ�ƽ̨��ʼ�� */
void  amhw_plfm_pwm1_cap_init (void)
{
    /* ����PWM��Դ */
	amhw_power_periph_up(AMHW_POWER_PWM1);
}

/** \brief  ���ƽ̨��ʼ�� */
void amhw_plfm_pwm1_cap_deinit (void)
{
    /* �ر�MCPWM��Դ */
	amhw_power_periph_down(AMHW_POWER_PWM1);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_cap_param __g_awbl_pwm1_cap_param = {
    &g_pwm1_cap_dev,
    &g_pwm1_cap_devinfo,
    {
        9,                       /* The device provide CAP min ID is 9 */
        10,                      /* The device provide CAP max ID is 10 */
    },
    (pfn_cap_init_t)amdr_pwm_cap_init,
    amhw_plfm_pwm1_cap_init      /* pfunc_plfm_init */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_cap_dev __g_awbl_pwm1_cap_dev;

#define AWBL_HWCONF_LPC17XX_PWM1_CAP        \
    {                                       \
        AWBL_AMETAL_CAP_NAME,               \
        LPC17XX_PWM1_CAP_UNIT_ID,           \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_pwm1_cap_dev.dev),        \
        &(__g_awbl_pwm1_cap_param)           \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_PWM1_CAP

#endif  /* AW_DEV_LPC17XX_PWM1_CAP */

/* end of file */
