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
    lpc5410x timer for capture
*******************************************************************************/

#include "aw_int.h"
#include "driver/cap/awbl_ametal_cap.h"
#include "ametal.h"
#include "amdr_pwm_cap.h"

#ifdef AW_DEV_LPC17XX_MCPWM_CAP

/** \brief  ���� �ܽ����� */
amdr_mcpwm_cap_ioinfo_t __g_mcpwm_cap_ioinfo_list[] = {
	{PIO1_20, PIO1_20_MCI0, PIO1_20_GPIO},
	{PIO1_23, PIO1_23_MCI1, PIO1_23_GPIO},
	{PIO1_24, PIO1_24_MCI2, PIO1_24_GPIO},
};


/** \brief mcpwm���ܵ��豸��Ϣ */
const amdr_mcpwm_cap_devinfo_t  g_mcpwm_cap_devinfo = {
	AMHW_MCPWM,                 /**< \brief ָ��PWM�Ĵ������ָ�� */
	INUM_MCPWM,                 /**< \brief PWM�жϱ��           */
    &__g_mcpwm_cap_ioinfo_list[0],
    3,                         /**< \brief 3��ͨ��    */
};

/** \brief mcpwm���ڲ����ܵ��豸���� */
amdr_mcpwm_cap_dev_t  g_mcpwm_cap_dev;

/**
 * \brief mcpwm���ܵ�ƽ̨��ʼ��
 * \param[in] channel    : ͨ��0-2
 * \return    -AM_EINVAL ��AM_OK
 */
void  amhw_plfm_mcpwm_cap_init (void)
{
    /* ����MCPWM��Դ */
	amhw_power_periph_up(AMHW_POWER_MCPWM);

}

/** \brief  ���ƽ̨��ʼ�� */
void amhw_plfm_mcpwm_cap_deinit (void)
{
    /* �ر�MCPWM��Դ */
	amhw_power_periph_down(AMHW_POWER_MCPWM);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_cap_param __g_awbl_mcpwm_cap_param = {
    &g_mcpwm_cap_dev,
    &g_mcpwm_cap_devinfo,
    {
        11,                       /* The device provide CAP min ID is 11 */
        13,                       /* The device provide CAP max ID is 13 */
    },
    (pfn_cap_init_t)amdr_mcpwm_cap_init,
    amhw_plfm_mcpwm_cap_init      /* pfunc_plfm_init */
};

/*  �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_cap_dev __g_awbl_mcpwm_cap_dev;

#define AWBL_HWCONF_LPC17XX_MCPWM_CAP       \
    {                                       \
        AWBL_AMETAL_CAP_NAME,               \
        LPC17XX_MCPWM_CAP_UNIT_ID,          \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_mcpwm_cap_dev.dev),      \
        &(__g_awbl_mcpwm_cap_param)         \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_MCPWM_CAP

#endif  /* AW_DEV_LPC17XX_MCPWM_CAP */

/* end of file */
