/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief 工程入口，启动配置
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "charger.h"
#include "acp1000_din.h"
#include "acp1000_dout.h"
#include "ac_charge_prj_cfg.h"
#include "cardreader/aw_iccreader.h"
#include "event_node.h"
#include "dugs.h"
#include "card_reader.h"
#include "modbus/aw_mb_comm.h"
#include "billing.h"
#include "ammeter/aw_ammeter.h"
#include "ammeter.h"
#include "pile.h"
#include "hub4g.h"
#include "dubug_shell.h"
#include "aw_vdebug.h"
#include "amhw_iap.h"

aw_local charger_t      g_charger;
aw_local dugs_t         g_dugs;
aw_local card_reader_t  g_card_reader;
aw_local billing_t      g_billing;
aw_local ammeter_t      g_ammeter;
aw_local pile_t         g_pile;
aw_local hub4g_t        g_hub4g;
aw_local dubug_shell_t  g_dubug_shell;

aw_local modbus_info_t g_mb_info = {
    0x05,
    ACP1000_DBUGS_COM,
    115200,
    AW_MB_PAR_NONE
};

aw_local modbus_info_t g_hub4g_info = {
    0x01,
    ACP1000_HUB4G_COM,
    19200,
    AW_MB_PAR_NONE
};


/**
 * ZLG600A读卡器传输类
 */
aw_local aw_iccreader_transfer_t __g_aw_card_reader_transfer_zlg600a = {
    .uart_num    = ACP1000_CARDREADER_COM,  /* 设置串口号  */
    .uart_buad   = 57600,                   /* 设置通信波特率 */
    .uart_format = CLOCAL | CREAD | CS8,    /* 通信格式 */
    .rs485_en    = FALSE,
};

/** \brief 周立功读卡器 */
static aw_iccreader_t __g_aw_card_reader_zlg;


/* DL45协议通信地址 */
//aw_local uint8_t __g_dl645_addr[6] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
aw_local uint8_t __g_dl645_addr[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};


/* DL45协议通信实例（协议符合07年规约） */
aw_local aw_ammeter_transfer_dl645_t __g_aw_ammeter_transfer_dl645 = {
    {
        .p_addr   = __g_dl645_addr,
        .addr_len = 6,
        .protocol = AW_AMMETER_TRANSFER_PROTOCOL_DL645_07,
    },
    .uart_num    = ACP1000_AMMETER_COM,           /* 设置串口号  */
    .uart_buad   = 2400,                          /* 设置通信波特率 */
    .uart_format = PARENB | CLOCAL | CREAD | CS8, /* 通信格式, 8E1 */
    .rs485_en    = TRUE,                          /* 使能RS485方向控制 */
};

/* 直流电表实例 */
aw_local aw_ammeter_dc_t __g_aw_ammeter_dc = {
    {
        .type   = AW_AMMETER_TYPE_DC,
    },
    .p_transfer    = &(__g_aw_ammeter_transfer_dl645.super), /* 依赖的通信类  */
};


static event_manager_t g_event_manager;


extern void acp1000_overtime_task_startup (struct event_manager *p_this);
extern void led_task_startup (pile_t *p_pile);
extern void buzzer_task_startup(void);
extern void pile_temp_task_startup (pile_t *p_this);

void acp_main_startup (void)
{
    aw_kprintf ("Software version: V%d.%02d\r\n", ACP1000_VERSION_MAJOR, ACP1000_VERSION_MINOR);


    /*-------------------------------模块初始化---------------------------------*/
    acp1000_din_init();
    acp1000_dout_init();

    pile_inst_init(&g_pile);

    amhw_iap_unique_id_read(g_pile.pile_dat.mcu_uid);

#if ACP1000_DUGS_TASK
    dugs_inst_init(&g_dugs, &g_mb_info);
#endif

#if ACP1000_CARD_DETECT_TASK
    card_reader_inst_init(&g_card_reader, &__g_aw_card_reader_zlg, &__g_aw_card_reader_transfer_zlg600a, &(g_pile));
#endif

    charger_inst_init(&g_charger,  &(g_pile.pile_sem));

#if ACP1000_BILING_DETECT_TASK
    billing_inst_init(&g_billing, ACP1000_RTC_NUM, &(g_pile.pile_sem), &g_pile);
#endif

#if ACP1000_AMMETER_DETECT_TASK
    ammeter_inst_init(&g_ammeter, &__g_aw_ammeter_dc.super, ACP1000_PILE_MAX_CURR);
#endif

    if (am_gpio_get(ACP1000_DIN_FAC) == 0) {
        /* 低电平不是能电流检测,为FALSE，默认TRUE */
        g_ammeter.enable_curr_check = FALSE;
    }


#if ACP1000_HUB4G_TASK
    hub4g_inst_init(&g_hub4g, &g_hub4g_info, &(g_pile.pile_sem), g_card_reader.dat.key_vaild);
#endif

#if ACP1000_DUBUG_SHELL_TASK
    dubug_shell_inst_init(&g_dubug_shell, NULL, &g_billing, &g_charger, &g_dugs, &g_hub4g, &g_pile);
#endif

    /*-------------------------------事件注册---------------------------------*/
    event_manager_init(&g_event_manager);
    event_manager_add(&g_event_manager, &g_charger.evt_node);

#if ACP1000_CARD_DETECT_TASK
    event_manager_add(&g_event_manager, &g_card_reader.evt_node);
#endif

#if ACP1000_DUGS_TASK
    event_manager_add(&g_event_manager, &g_dugs.evt_node);
#endif

#if ACP1000_BILING_DETECT_TASK
    event_manager_add(&g_event_manager, &g_billing.evt_node);
#endif

#if ACP1000_AMMETER_DETECT_TASK
    event_manager_add(&g_event_manager, &g_ammeter.evt_node);
#endif

    event_manager_add(&g_event_manager, &g_pile.evt_node);

#if ACP1000_HUB4G_TASK
    event_manager_add(&g_event_manager, &g_hub4g.evt_node);
#endif

    /*-------------------------------任务启动---------------------------------*/
#if ACP1000_VTP1_DETECT_TASK
    acp1000_tp1_vol_detect_task_startup(&g_charger);
#endif

#if ACP1000_CARD_DETECT_TASK
    card_reader_task_startup(&g_card_reader);
#endif

#if ACP1000_AMMETER_DETECT_TASK
    ammeter_task_startup(&g_ammeter);
#endif

#if ACP1000_CHARGE_TASK
    charger_task_startup(&g_charger);
#endif

#if ACP1000_BILING_DETECT_TASK
    billing_task_startup(&g_billing);
#endif

#if ACP1000_LEDLOCK_TASK
    led_task_startup(&g_pile);
#endif

#if ACP1000_PILE_ERR_DETECT_TASK
    pile_task_startup(&g_pile);
#endif

#if ACP1000_OVERTIME_DETECT
    acp1000_overtime_task_startup(&g_event_manager);
#endif

#if ACP1000_BUZZER_TASK
    buzzer_task_startup();
#endif

#if ACP1000_PILE_TEMP_TASK
    pile_temp_task_startup(&g_pile);
#endif


}
