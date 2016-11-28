/*******************************************************************************
*                                 apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.embedcontrol.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

#include "apollo.h"                     /* 此头文件必须被首先包含  */
#include "main.h"                       /* 用户程序主头文件        */

/* 本程序用到了以下服务 */
#include "aw_task.h"                    /* 多任务服务 */
#include "aw_delay.h"                   /* 延时服务 */
#include "aw_led.h"                     /* LED服务 */
#include "aw_vdebug.h"
#include "aw_serial.h"

extern void rtk_cpu_usage_shell_init (void);
void test_uart_acp1000(void);
void test_rtc (void);
void test_acp_pio (void);
void test_curr_pwm (void);
void test_ammeter (void);
void test_card_reader (void);
void test_dgus (void);

void ac_charger_board_startup (void);
void test_mb_dugs (void);
void acp_main_startup (void);
void test_uart_shell_init(void);
void test_switch_startup (void);
void test_adc(void);
void test_serial_write (void);
void test_iccreader_shell();

int aw_main (void)
{
    aw_kprintf ("Start up successful,configured by tools!\r\n");
    rtk_stk_chk_shell_init();
    rtk_cpu_usage_shell_init();

    aw_serial_ioctl(COM0, SIO_MODE_SET, (void *)SIO_MODE_INT);
    aw_serial_ioctl(COM0, AM_UART_RS485_ENABLE_SET, 1);
//    test_uart_shell_init();
//    test_acp_pio();
//    test_curr_pwm();
//    test_dgus();
//    test_ammeter ();
//    test_card_reader();
//    test_uart_acp1000();
//    test_mb_dugs();
//    test_rtc ();
//    ac_charger_board_startup();
//    aw_buzzer_loud_set(50);
//    aw_buzzer_beep(500);
//    test_serial_write();
//      test_iccreader_shell();
    acp_main_startup();
//    test_adc();
//    test_switch_startup();
    AW_FOREVER {

        aw_led_toggle(LED0);
        aw_mdelay(1000);
    }

    return  AW_OK;
}

/* end of file */
