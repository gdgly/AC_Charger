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

#ifdef AW_DEV_LPC17XX_PWM0_CAP

/** \brief  捕获 管脚配置 */
amdr_pwm_cap_ioinfo_t __g_pwm0_cap_ioinfo_list[] = {
	{PIO1_12, PIO1_12_PCAP0_0, PIO1_12_GPIO}
};


/** \brief pwm功能的设备信息 */
const amdr_pwm_cap_devinfo_t  g_pwm0_cap_devinfo = {
    AMHW_PWM0,                 /**< \brief 指向PWM寄存器块的指针 */
    INUM_PWM0,                 /**< \brief PWM中断编号           */
    &__g_pwm0_cap_ioinfo_list[0],
    1,                         /* 2个通道    */
};

/** \brief pwm功能的设备定义 */
amdr_pwm_cap_dev_t  g_pwm0_cap_dev;

/** \brief pwm功能的平台初始化 */
void  amhw_plfm_pwm0_cap_init (void)
{
    /* 开启PWM电源 */
	amhw_power_periph_up(AMHW_POWER_PWM0);
}

/** \brief  解除平台初始化 */
void amhw_plfm_pwm0_cap_deinit (void)
{
    /* 关闭MCPWM电源 */
	amhw_power_periph_down(AMHW_POWER_PWM0);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_cap_param __g_awbl_pwm0_cap_param = {
    &g_pwm0_cap_dev,
    &g_pwm0_cap_devinfo,
    {
        8,                       /* The device provide CAP min ID is 8 */
        8,                       /* The device provide CAP max ID is 8 */
    },
    (pfn_cap_init_t)amdr_pwm_cap_init,
    amhw_plfm_pwm0_cap_init      /* pfunc_plfm_init */
};

/* 设备实例内存静态分配 */
aw_local struct awbl_ametal_cap_dev __g_awbl_pwm0_cap_dev;

#define AWBL_HWCONF_LPC17XX_PWM0_CAP        \
    {                                       \
        AWBL_AMETAL_CAP_NAME,               \
        LPC17XX_PWM0_CAP_UNIT_ID,            \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_pwm0_cap_dev.dev),        \
        &(__g_awbl_pwm0_cap_param)           \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_PWM0_CAP

#endif  /* AW_DEV_LPC17XX_PWM0_CAP */

/* end of file */
