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

#include "aw_int.h"
#include "driver/timer/awbl_ametal_timer.h"
#include "aw_hwtimer.h"
#include "ametal.h"
#include "amdr_timer_timing.h"

/*******************************************************************************
  Standard timer0 for timing configure infomation
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_TIMER0_TIMING

/** \brief ��ʱ��0�豸��Ϣ */
const amdr_timer_timing_devinfo_t  g_timer0_timing_devinfo = {
    AMHW_TIMER0,                /**< \brief ָ��ʱ��0�Ĵ������ָ��  */
    INUM_TIMER0,                /**< \brief ��ʱ��0�жϺ� */
};

/** \brief ��ʱ��0�豸 */
amdr_timer_timing_dev_t  g_timer0_timing_dev;

/** \brief ��ʱ��0ƽ̨��ʼ�� */
void amhw_plfm_timer0_timing_init (void)
{
    amhw_power_periph_up(AMHW_POWER_TIMER0);
}

/** \brief �����ʱ��0ƽ̨��ʼ�� */
void amhw_plfm_timer0_timing_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_TIMER0);
}

/* The Timer channel,The Timer has only 1 channel      */
aw_local struct awbl_ametal_timer_chan  __g_awbl_timer0_timing_chan[1];

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_timer_param __g_awbl_timer0_timing_param = {
    
    &g_timer0_timing_dev,
    &g_timer0_timing_devinfo,
    &__g_awbl_timer0_timing_chan[0],
    AW_HWTIMER_CHAN_ALLOC_BY_NAME(0),
    (pfunc_timer_init_t)amdr_timer_timing_init,
    amhw_plfm_timer0_timing_init          /* pfunc_plfm_init */
};

/* 32 bit timer 0 �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_timer_dev __g_awbl_timer0_timing_dev;

#define AWBL_HWCONF_LPC17XX_TIMER0_TIMING   \
    {                                       \
        AWBL_AMETAL_TIMER_NAME,             \
        LPC17XX_TIMER0_TIMING_UNIT_ID,      \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_timer0_timing_dev.dev),  \
        &(__g_awbl_timer0_timing_param)     \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_TIMER0_TIMING

#endif  /* AW_DEV_LPC17XX_TIMER0_TIMING */

/* end of file */
