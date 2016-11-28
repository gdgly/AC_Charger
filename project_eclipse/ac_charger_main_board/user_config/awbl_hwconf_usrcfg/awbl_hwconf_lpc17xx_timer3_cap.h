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
  Standard timer 3 for capture configure information
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_TIMER3_CAP

/** \brief 定时器1用于捕获 IO配置信息 */
amdr_timer_cap_ioinfo_t __g_timer3_cap_ioinfo_list[] = {
    {PIO0_23,  PIO0_23_CAP3_0, PIO0_23_GPIO | PIO0_23_INPUT}, /**< \brief 通道 0, IO配置信息 */
    {PIO0_24,  PIO0_24_CAP3_1, PIO0_24_GPIO | PIO0_24_INPUT}, /**< \brief 通道 1, IO配置信息 */
};

/** \brief 定时器3用于捕获功能的设备信息 */
const amdr_timer_cap_devinfo_t  g_timer3_cap_devinfo = {
    AMHW_TIMER3,               /**< \brief 指向定时器3寄存器块的指针 */
    INUM_TIMER3,               /**< \brief 定时器3 中断编号 */
    1,                         /**< \brief 1个捕获通道      */
    &__g_timer3_cap_ioinfo_list[0],
};

/** \brief 定时器3用于捕获功能的设备定义 */
amdr_timer_cap_dev_t  g_timer3_cap_dev;

/** \brief 定时器3用于捕获功能平台初始化 */
void amhw_plfm_timer3_cap_init (void)
{
    amhw_power_periph_up(AMHW_POWER_TIMER3);
}

/** \brief 解除定时器3用于捕获功能平台初始化 */
void amhw_plfm_timer3_cap_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_TIMER3);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_cap_param __g_awbl_timer3_cap_param = {
    &g_timer3_cap_dev,
    &g_timer3_cap_devinfo,
    {
        6,                        /* The device provide CAP min ID is 6 */
        7,                        /* The device provide CAP max ID is 7 */
    },
    (pfn_cap_init_t)amdr_timer_cap_init,
    amhw_plfm_timer3_cap_init      /* pfunc_plfm_init */
};

/* 32 bit timer 1 设备实例内存静态分配 */
aw_local struct awbl_ametal_cap_dev __g_awbl_timer3_cap_dev;

#define AWBL_HWCONF_LPC17XX_TIMER3_CAP      \
    {                                       \
        AWBL_AMETAL_CAP_NAME,               \
        LPC17XX_TIMER3_CAP_UNIT_ID,         \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_timer3_cap_dev.dev),     \
        &(__g_awbl_timer3_cap_param)        \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_TIMER3_CAP

#endif  /* AW_DEV_LPC17XX_TIMER3_CAP */

/* end of file */
