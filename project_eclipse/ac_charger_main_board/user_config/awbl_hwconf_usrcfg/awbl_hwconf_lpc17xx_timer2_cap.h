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
#include "aw_hwtimer.h"
#include "ametal.h"
#include "amdr_timer_cap.h"

/*******************************************************************************
  Standard timer 2 for capture configure information
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_TIMER2_CAP

/** \brief ��ʱ��2���ڲ��� IO������Ϣ */
amdr_timer_cap_ioinfo_t __g_timer2_cap_ioinfo_list[] = {
    {PIO0_4,  PIO0_4_CAP2_0, PIO0_4_GPIO | PIO0_4_INPUT}, /**< \brief ͨ�� 0, IO������Ϣ */
    {PIO0_5,  PIO0_5_CAP2_1, PIO0_5_GPIO | PIO0_5_INPUT}, /**< \brief ͨ�� 1, IO������Ϣ */
};

/** \brief ��ʱ��2���ڲ����ܵ��豸��Ϣ */
const amdr_timer_cap_devinfo_t  g_timer2_cap_devinfo = {
    AMHW_TIMER2,               /**< \brief ָ��ʱ��2�Ĵ������ָ�� */
    INUM_TIMER2,               /**< \brief ��ʱ��2 �жϱ�� */
    2,                         /**< \brief 3������ͨ��      */
    &__g_timer2_cap_ioinfo_list[0],
};

/** \brief ��ʱ��2���ڲ����ܵ��豸���� */
amdr_timer_cap_dev_t  g_timer2_cap_dev;

/** \brief ��ʱ��2���ڲ�����ƽ̨��ʼ�� */
void amhw_plfm_timer2_cap_init (void)
{
    amhw_power_periph_up(AMHW_POWER_TIMER2);
}

/** \brief �����ʱ��2���ڲ�����ƽ̨��ʼ�� */
void amhw_plfm_timer2_cap_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_TIMER2);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_cap_param __g_awbl_timer2_cap_param = {
    &g_timer2_cap_dev,
    &g_timer2_cap_devinfo,
    {
        4,                        /* The device provide CAP min ID is 4 */
        5,                       /* The device provide CAP max ID is 5 */
    },
    (pfn_cap_init_t)amdr_timer_cap_init,
    amhw_plfm_timer2_cap_init      /* pfunc_plfm_init */
};

/* 32 bit timer 2 �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_cap_dev __g_awbl_timer2_cap_dev;

#define AWBL_HWCONF_LPC17XX_TIMER2_CAP     \
    {                                       \
        AWBL_AMETAL_CAP_NAME,               \
        LPC17XX_TIMER2_CAP_UNIT_ID,         \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_timer2_cap_dev.dev),     \
        &(__g_awbl_timer2_cap_param)        \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_TIMER2_CAP

#endif  /* AW_DEV_LPC17XX_TIMER2_CAP */

/* end of file */
