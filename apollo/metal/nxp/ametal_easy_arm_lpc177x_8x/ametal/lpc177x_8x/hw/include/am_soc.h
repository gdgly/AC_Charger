/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SOC(片上系统),包含了芯片所有的外设
 *
 * \internal
 * \par Modification History
 * - 1.00 15-09-02  cod, first implementation.
 * \endinternal
 */

#ifndef __AM_SOC_H
#define __AM_SOC_H


#ifdef __cplusplus
extern "C" {
#endif

#include "amhw_lpc177x_8x.h"
#include "lpc177x_8x_pin.h"
#include "lpc177x_8x_inum.h"
#include "amhw_syscon.h"
#include "amhw_clock.h"
#include "amhw_pll.h"
#include "amhw_power.h"
#include "amhw_pincon.h"
#include "amhw_gpioint.h"
#include "amhw_gpio.h"
#include "amhw_int.h"
#include "amhw_systick.h"
#include "amhw_adc.h"
#include "amhw_dma.h"
#include "amhw_can.h"
#include "amhw_dac.h"
#include "amhw_i2c.h"
#include "amhw_timer.h"
#include "amhw_usart.h"
#include "amhw_mcpwm.h"
#include "amhw_rtc.h"
#include "amhw_i2s.h"
#include "amhw_qei.h"
#include "amhw_pwm.h"
#include "amhw_iap.h"
#include "amhw_ssp.h"
#include "amhw_wwdt.h"
#include "amhw_emc.h"
#include "amhw_wwdt.h"
#include "amhw_eeprom.h"
#include "amhw_crc.h"
#include "amhw_lcd.h"
#include "amhw_enet.h"
#include "amhw_mci.h"
#include "amhw_usbd.h"

#ifdef __cplusplus
}
#endif

#endif /*__AM_SOC_H */

/* end of file */
