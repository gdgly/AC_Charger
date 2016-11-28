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
    lpc5410x 标准定时器配置信息
*******************************************************************************/

#include "aw_int.h"
#include "driver/timer/awbl_ametal_timer.h"
#include "aw_hwtimer.h"
#include "ametal.h"
#include "amdr_timer_timing.h"

/*******************************************************************************
  Standard timer3 for timing configure infomation
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_TIMER3_TIMING

/** \brief 定时器3设备信息 */
const amdr_timer_timing_devinfo_t  g_timer3_timing_devinfo = {
    AMHW_TIMER3,                /**< \brief 指向定时器3寄存器块的指针  */
    INUM_TIMER3,                /**< \brief 定时器3中断号 */
};

/** \brief 定时器3设备 */
amdr_timer_timing_dev_t  g_timer3_timing_dev;

/** \brief 定时器3平台初始化 */
void amhw_plfm_timer3_timing_init (void)
{
    amhw_power_periph_up(AMHW_POWER_TIMER3);
}

/** \brief 解除定时器3平台初始化 */
void amhw_plfm_timer3_timing_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_TIMER3);
}

/* The Timer channel,The Timer has only 1 channel      */
aw_local struct awbl_ametal_timer_chan  __g_awbl_timer3_timing_chan[1];

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_timer_param __g_awbl_timer3_timing_param = {
    
    &g_timer3_timing_dev,
    &g_timer3_timing_devinfo,
    &__g_awbl_timer3_timing_chan[0],
    AW_HWTIMER_NOT_ALLOC_BY_NAME,
    (pfunc_timer_init_t)amdr_timer_timing_init,
    amhw_plfm_timer3_timing_init          /* pfunc_plfm_init */
};

/* 32 bit timer 3 设备实例内存静态分配 */
aw_local struct awbl_ametal_timer_dev __g_awbl_timer3_timing_dev;

#define AWBL_HWCONF_LPC17XX_TIMER3_TIMING   \
    {                                       \
        AWBL_AMETAL_TIMER_NAME,             \
        LPC17XX_TIMER3_TIMING_UNIT_ID,      \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_timer3_timing_dev.dev),  \
        &(__g_awbl_timer3_timing_param)     \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_TIMER3_TIMING

#endif  /* AW_DEV_LPC17XX_TIMER3_TIMING */
    
/* end of file */
