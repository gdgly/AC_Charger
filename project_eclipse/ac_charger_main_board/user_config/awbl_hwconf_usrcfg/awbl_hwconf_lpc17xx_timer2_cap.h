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

/** \brief 定时器2用于捕获 IO配置信息 */
amdr_timer_cap_ioinfo_t __g_timer2_cap_ioinfo_list[] = {
    {PIO0_4,  PIO0_4_CAP2_0, PIO0_4_GPIO | PIO0_4_INPUT}, /**< \brief 通道 0, IO配置信息 */
    {PIO0_5,  PIO0_5_CAP2_1, PIO0_5_GPIO | PIO0_5_INPUT}, /**< \brief 通道 1, IO配置信息 */
};

/** \brief 定时器2用于捕获功能的设备信息 */
const amdr_timer_cap_devinfo_t  g_timer2_cap_devinfo = {
    AMHW_TIMER2,               /**< \brief 指向定时器2寄存器块的指针 */
    INUM_TIMER2,               /**< \brief 定时器2 中断编号 */
    2,                         /**< \brief 3个捕获通道      */
    &__g_timer2_cap_ioinfo_list[0],
};

/** \brief 定时器2用于捕获功能的设备定义 */
amdr_timer_cap_dev_t  g_timer2_cap_dev;

/** \brief 定时器2用于捕获功能平台初始化 */
void amhw_plfm_timer2_cap_init (void)
{
    amhw_power_periph_up(AMHW_POWER_TIMER2);
}

/** \brief 解除定时器2用于捕获功能平台初始化 */
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

/* 32 bit timer 2 设备实例内存静态分配 */
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
