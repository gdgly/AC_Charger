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
 * \brief 外设驱动头文件,包含了所有外设驱动的头文件
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-01-17  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DRIVERS_H
#define __AM_DRIVERS_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "lpc177x_8x_pin.h"
    
#include "amdr_gpio.h"
#include "amdr_gpio_util.h"
#include "amdr_int.h"
#include "amdr_adc.h"
#include "amdr_can.h"
#include "amdr_dma.h"
#include "amdr_dac.h"
#include "amdr_i2c.h"
#include "amdr_mcpwm.h"
#include "amdr_mcpwm_cap.h"
#include "amdr_pwm.h"
#include "amdr_pwm_cap.h"
#include "amdr_timer_timing.h"
#include "amdr_timer_cap.h"
#include "amdr_usart.h"
#include "amdr_rtc.h"
#include "amdr_i2s.h"
#include "amdr_ssp.h"
#include "amdr_qei.h"
#include "amdr_eeprom.h"
#include "amdr_wwdt.h"
#include "amdr_mci.h"
#include "amdr_crc.h"
#include "amdr_lcd.h"
#include "amdr_mci.h"

#ifdef __cplusplus
}
#endif

#endif /*__AM_DRIVERS_H */

/* end of file */
