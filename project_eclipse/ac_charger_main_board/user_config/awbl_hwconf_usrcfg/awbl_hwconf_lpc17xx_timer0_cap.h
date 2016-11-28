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
  Standard timer0 for capture configure information
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_TIMER0_CAP


/** \brief 定时器0用于捕获 IO配置信息 */
amdr_timer_cap_ioinfo_t __g_timer0_cap_ioinfo_list[] = {
    {PIO1_26,  PIO1_26_CAP0_0, PIO1_26_GPIO | PIO1_26_INPUT}, /**< \brief 通道 0, IO配置信息 */
    {PIO1_27,  PIO1_27_CAP0_1, PIO1_27_GPIO | PIO1_27_INPUT}, /**< \brief 通道 1, IO配置信息 */
};

/** \brief 定时器0用于捕获功能的设备信息 */
const amdr_timer_cap_devinfo_t  g_timer0_cap_devinfo = {
    AMHW_TIMER0,               /**< \brief 指向定时器0寄存器块的指针 */
    INUM_TIMER0,               /**< \brief 定时器0 中断编号 */
    2,                         /**< \brief 4个捕获通道      */
    &__g_timer0_cap_ioinfo_list[0],
};

/** \brief 定时器0用于捕获功能的设备定义  */
amdr_timer_cap_dev_t  g_timer0_cap_dev;

/** \brief 定时器0用于捕获功能平台初始化 */
void amhw_plfm_timer0_cap_init (void)
{
    amhw_power_periph_up(AMHW_POWER_TIMER0);
}

/** \brief 定时器0用于捕获功能平台初始化 */
void amhw_plfm_timer0_cap_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_TIMER0);
}

/* The param for decvice  */
aw_local aw_const struct awbl_ametal_cap_param __g_awbl_timer0_cap_param = {
    &g_timer0_cap_dev,
    &g_timer0_cap_devinfo,
    {
        0,                        /* The device provide CAP min ID is 0 */
        1,                        /* The device provide CAP max ID is 1 */
    },
    (pfn_cap_init_t)amdr_timer_cap_init,
    amhw_plfm_timer0_cap_init      /* pfunc_plfm_init */
};

/* 32 bit timer 0 设备实例内存静态分配 */
aw_local struct awbl_ametal_cap_dev __g_awbl_timer0_cap_dev;

#define AWBL_HWCONF_LPC17XX_TIMER0_CAP      \
    {                                       \
        AWBL_AMETAL_CAP_NAME,               \
        LPC17XX_TIMER0_CAP_UNIT_ID,         \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &(__g_awbl_timer0_cap_dev.dev),     \
        &(__g_awbl_timer0_cap_param)        \
    },                            
    
#else
    
#define AWBL_HWCONF_LPC17XX_TIMER0_CAP

#endif  /* AW_DEV_LPC17XX_TIMER0_CAP */

/* end of file */
