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
  Standard mcpwm configure infomation
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_MCPWM

/*   �ܽ����� */
amdr_mcpwm_ioinfo_t __g_mcpwm_ioinfo_list[] = {
	{PIO1_19, PIO1_19_MCOA0, PIO1_19_GPIO},
	{PIO1_22, PIO1_22_MCOB0, PIO1_22_GPIO},
	{PIO1_25, PIO1_25_MCOA1, PIO1_25_GPIO},
	{PIO1_26, PIO1_26_MCOB1, PIO1_26_GPIO},
	{PIO1_28, PIO1_28_MCOA2, PIO1_28_GPIO},
	{PIO1_29, PIO1_29_MCOB2, PIO1_29_GPIO},
};

/** \brief mcpwm���ܵ��豸��Ϣ */
const amdr_mcpwm_devinfo_t  g_mcpwm_devinfo = {
	AMHW_MCPWM,                 /**< \brief ָ��MCPWM�Ĵ������ָ�� */
	INUM_MCPWM,                 /**< \brief PWM�жϱ��           */
    &__g_mcpwm_ioinfo_list[0],
    3,                          /* 3��ͨ��    */
};


/** \brief mcpwm���ܵ��豸���� */
amdr_mcpwm_dev_t  g_mcpwm_dev;

/** \brief mcpwm���ܵ�ƽ̨��ʼ�� */
void  amhw_plfm_mcpwm_init (void)
{
    /* ����MCPWM��Դ */
	amhw_power_periph_up(AMHW_POWER_MCPWM);
}

/** \brief  ���ƽ̨��ʼ�� */
void amhw_plfm_mcpwm_deinit (void)
{
    /* �ر�MCPWM��Դ */
	amhw_power_periph_down(AMHW_POWER_MCPWM);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_pwm_param __g_awbl_mcpwm_param = {
    &g_mcpwm_dev,
    &g_mcpwm_devinfo,
    {
        13,                        /* The device provide PWM min ID is 13 */
        15,                        /* The device provide PWM max ID is 15 */
    },
    (pfn_pwm_init_t)amdr_mcpwm_init,
    amhw_plfm_mcpwm_init            /* pfunc_plfm_init */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_pwm_dev __g_awbl_mcpwm_dev;

#define AWBL_HWCONF_LPC17XX_MCPWM           \
    {                                       \
        AWBL_AMETAL_PWM_NAME,               \
        LPC17XX_MCPWM_UNIT_ID,              \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_mcpwm_dev.dev),          \
        &(__g_awbl_mcpwm_param)             \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_MCPWM

#endif  /* AW_DEV_LPC17XX_MCPWM */

/* end of file */
