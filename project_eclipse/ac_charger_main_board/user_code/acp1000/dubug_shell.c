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
 * \brief 调试壳实例
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#include "dubug_shell.h"
#include "apollo.h"
#include "aw_shell.h"
#include "aw_vdebug.h"
#include "aw_delay.h"
#include "mb/aw_mb_dgus_regmap.h"
#include "acp1000_dout.h"
#include "aw_nvram.h"
#include "des/des.h"

static dubug_shell_t *gp_dubug_shell = NULL;

static void dugs_info_printf(dugs_t *p_this) {
    uint8_t  usr_id[17] = {0};
    uint32_t usr_balance;

    dugs_lock(p_this);
    memcpy(usr_id, p_this->super.rd_reg.usr_id, 16);
    usr_balance = p_this->super.rd_reg.usr_balance[0] << 16 |
                  p_this->super.rd_reg.usr_balance[1];
    AW_INFOF(("Usr  id : %s\r\n", usr_id[0]==0 ? "NULL" : usr_id));
    AW_INFOF(("Blance: %d\r\n\r\n",  usr_balance));

    AW_INFOF(("Card cnt:   %d\r\n",  p_this->super.rd_reg.card_cnt));
    AW_INFOF(("Card state: 0x%02X\r\n\r\n",  p_this->super.rd_reg.card_stat));

    AW_INFOF(("Pile state: 0x%02X\r\n",  p_this->super.rd_reg.pile_stat));
    AW_INFOF(("Pile Order: 0x%02X\r\n\r\n",  p_this->super.rd_reg.pile_order));

    AW_INFOF(("Blance state:  0x%02X\r\n",  p_this->super.rd_reg.balance_stat));
    AW_INFOF(("Gun    state:  0x%02X\r\n",  p_this->super.rd_reg.gun_stat));
    AW_INFOF(("Charge state:  0x%02X\r\n",  p_this->super.rd_reg.charge_stat));
    AW_INFOF(("Work   state:  0x%02X\r\n\r\n",  p_this->super.rd_reg.work_stat));

    AW_INFOF(("Used Time:    %d\r\n",  p_this->super.rd_reg.used_time));
    AW_INFOF(("Used amount:  %d\r\n",  p_this->super.rd_reg.used_amount));
    AW_INFOF(("Used energy:  %d\r\n",  p_this->super.rd_reg.used_energy));
    AW_INFOF(("Stop reason:  %d\r\n\r\n",  p_this->super.rd_reg.stop_reason));

    AW_INFOF(("Charge ctrl:   %d\r\n", p_this->super.wr_reg.charge_ctrl));
    AW_INFOF(("Charge way:    %d\r\n", p_this->super.wr_reg.charge_way));
    AW_INFOF(("Charge time:   %d\r\n", p_this->super.wr_reg.charge_time));
    AW_INFOF(("Charge amount: %d\r\n", p_this->super.wr_reg.charge_amount));
    AW_INFOF(("Charge energy: %d\r\n\r\n", p_this->super.wr_reg.charge_energy));
    dugs_unlock(p_this);
}

static void charger_info_printf(charger_t *p_this)
{
    charger_dev_lock(p_this);
    AW_INFOF(("AC    state : %d\r\n",  p_this->dat.ac_enable));
    AW_INFOF(("Allow state : %d\r\n",  p_this->dat.allow_charge));
    AW_INFOF(("Exit  code  : %d\r\n",  p_this->dat.exit_code));
    AW_INFOF(("Max   curr  : %d\r\n",  p_this->dat.max_curr));
    AW_INFOF(("Pile  alarm : %d\r\n",  p_this->dat.pile_alarm));
    AW_INFOF(("Vtp1        : %d\r\n\r\n",  p_this->dat.tp1_vol));
    charger_dev_unlock(p_this);
}

static void pile_info_printf(pile_t *p_this)
{
    int i = 0, j = 0;

    pile_dev_lock(p_this);
    AW_INFOF(("Auth   state : %d\r\n",  p_this->pile_dat.auth_state));
    AW_INFOF(("Charge state : %d\r\n",  p_this->pile_dat.charge_state));
    AW_INFOF(("Gun    state : %d\r\n",  p_this->pile_dat.gun_state));
    AW_INFOF(("Light  state : %d\r\n",  p_this->pile_dat.light_state));
    AW_INFOF(("Scram  state : %d\r\n",  p_this->pile_dat.scram_state));
    AW_INFOF(("Charge cnt   : %d\r\n",  p_this->pile_dat.charge_cnt));
    AW_INFOF(("Err    cnt   : %d\r\n\r\n",  p_this->pile_dat.err_cnt));

    AW_INFOF(("Alarm mask   : 0x%04X\r\n",  p_this->pile_alarm.alarm_mask));
    AW_INFOF(("hub4g addr   : %d\r\n",  p_this->pile_dat.hub4g_addr));
    AW_INFOF(("Input curr   : %d\r\n",  p_this->pile_dat.input_curr));
    AW_INFOF(("Input vol    : %d\r\n",  p_this->pile_dat.input_vol));
    AW_INFOF(("Now  price   : %d\r\n",  p_this->pile_time.now_price));
    AW_INFOF(("Run   time   : %d\r\n\r\n",  p_this->pile_dat.run_time));


    AW_INFOF(("Mcu  Id      : "));
    for (i = 0; i < 4; i++) {
          for (j = 0; j < 4; j++) {
              AW_INFOF(("%02X", (p_this->pile_dat.mcu_uid[i] >> (j*8)) & 0xFF ));
          }

    }
    AW_INFOF(("\r\n\r\n"));
//    AW_INFOF(("Now Time   : %d\r\n",  p_this->pile_time.tm));

    pile_dev_unlock(p_this);
}

static void billing_info_printf(billing_t *p_this)
{
    billing_dev_lock(p_this);
    AW_INFOF(("Now energy   : %d\r\n",  p_this->dat.now_energy));
    AW_INFOF(("Now price    : %d\r\n",  p_this->dat.now_price));
    AW_INFOF(("Start energy : %d\r\n",  p_this->dat.start_energy));
    AW_INFOF(("Start time   : %d\r\n",  p_this->dat.start_time));
    AW_INFOF(("Stop reason  : %d\r\n",  p_this->dat.stop_reason));
    AW_INFOF(("Used amount  : %d\r\n",  p_this->dat.used_amount));
    AW_INFOF(("Used energy  : %d\r\n",  p_this->dat.used_energy));
    AW_INFOF(("Used time    : %d\r\n",  p_this->dat.used_time));
    AW_INFOF(("Usr balance  : %d\r\n\r\n",  p_this->dat.usr_balance));
    billing_dev_unlock(p_this);
}


/**
 * 打印充电机状态
 */
static int charger_info(int argc, char *argv[])
{
    uint32_t vol = 0;

//    if (argc != 1) {
//        return AW_ERROR;
//    }
//    vol = strtol(argv[0], NULL , 0);
    if (gp_dubug_shell->p_dugs) {
        dugs_info_printf(gp_dubug_shell->p_dugs);
    }
    if (gp_dubug_shell->p_charger) {
        charger_info_printf(gp_dubug_shell->p_charger);
    }
    if (gp_dubug_shell->p_pile) {
        pile_info_printf(gp_dubug_shell->p_pile);
    }
    if (gp_dubug_shell->p_billing) {
        billing_info_printf(gp_dubug_shell->p_billing);
    }
    return AW_OK;
}

static int test_ac(int argc, char *argv[])
{
    extern void charger_ac_output_enable(charger_t *p_this, bool_t enable);

    if (gp_dubug_shell->p_charger) {
        AW_INFOF(("AC switch testing...\r\n"));
        charger_ac_output_enable(gp_dubug_shell->p_charger, TRUE);
        aw_mdelay(1200);
        if (gp_dubug_shell->p_pile->pile_alarm.alarm_mask & PILE_ALARM_ACLOCK) {
            AW_INFOF(("AC switch is bad.\r\n"));
            return AW_OK;
        }
        charger_ac_output_enable(gp_dubug_shell->p_charger, FALSE);
        aw_mdelay(1200);
        if (gp_dubug_shell->p_pile->pile_alarm.alarm_mask & PILE_ALARM_ACLOCK) {
            AW_INFOF(("AC switch is bad.\r\n"));
            return AW_OK;
        }
        AW_INFOF(("AC switch is good.\r\n"));
    } else {
        AW_INFOF(("This test item not be installed.\r\n"));
    }
    return AW_OK;
}

static int test_switch(int argc, char *argv[])
{
    uint32_t cnt = 1;
    uint32_t dly = 1000;

    if (argc < 1) {
        return AW_ERROR;
    }
    cnt = strtol(argv[0], NULL , 0);
    if (argc == 2) {
        dly = strtol(argv[1], NULL , 0);
    }
    while (cnt-- > 0) {
        aw_gpio_set(ACP1000_DOUT_AC, 1);
        aw_mdelay(dly);
        aw_gpio_set(ACP1000_DOUT_AC, 0);
        aw_mdelay(dly);
    }

    return AW_OK;
}

static int set_pile_id(int argc, char *argv[])
{
    uint8_t pile_id[8];

    if (argc != 1) {
        return AW_ERROR;
    }
#if 0
    if(AW_OK == aw_nvram_set(ACP1000_EEPROM_NAME, 1, argv[0], 0, 8)) {    // 设置非易失性数据"桩ID"
        AW_INFOF(("写入桩ID：%s\r\n", argv[0]));
        if(AW_OK == aw_nvram_get(ACP1000_EEPROM_NAME, 1, pile_id, 0, 8)) {    // 设置非易失性数据"桩ID"
            AW_INFOF(("读出桩ID： %s\r\n", pile_id));
        } else {
            AW_INFOF(("读出桩ID失败！\r\n"));
        }
    } else {
        AW_INFOF(("写入桩ID失败！\r\n"));
    }
#endif
    event_node_tell(&(gp_dubug_shell->p_hub4g->evt_node), HUB4G_PILE_ID, (void *)argv[0]);

    return AW_OK;
}

static int set_hub4g_addr(int argc, char *argv[])
{
    uint8_t addr;

    if (argc != 1) {
        return AW_ERROR;
    }
    addr = strtol(argv[0], NULL , 0);
#if 0
    if(AW_OK == aw_nvram_set(ACP1000_EEPROM_NAME, 2, &addr, 0, 1)) {    // 设置非易失性数据"桩ID"
        AW_INFOF(("写入集中器地址：0x%02X\r\n", addr));
        addr = 0;
        if(AW_OK == aw_nvram_get(ACP1000_EEPROM_NAME, 2, &addr, 0, 1)) {    // 设置非易失性数据"桩ID"
            AW_INFOF(("读出集中器地址：0x%02X\r\n", addr));
        } else {
            AW_INFOF(("读出集中器地址失败！\r\n"));
        }
    } else {
        AW_INFOF(("写入集中器地址失败！\r\n"));
    }
#endif
    event_node_tell_all(&(gp_dubug_shell->p_dugs->evt_node), DUGS_HUB4G_ADDR, (void *)addr);

    return AW_OK;
}

static void charge_history_printf(uint8_t *p_buf)
{
    uint8_t  usr_id[17] = {0};
    time_t   time;
    uint32_t dat32;
    uint16_t dat16;
    aw_tm_t  tm;

    memcpy(usr_id, p_buf, 16);
    AW_INFOF(("-------------------------------------------------\r\n"));
    AW_INFOF(("Usr  id     : %s\r\n", usr_id[0]==0 ? "NULL" : usr_id));
    memcpy(&dat32,  &p_buf[16], sizeof(dat32));
    AW_INFOF(("Usr balance : %d\r\n\r\n",  dat32));
    memcpy(&time,  &p_buf[20], sizeof(time_t));
    if (AW_OK != aw_time_to_tm(&time, &tm)) {
        AW_INFOF(("Start time   : %ld\r\n",  time));
    } else {
        AW_INFOF(("Start time   : %d-%d-%d %d:%d:%d\r\n",  tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
                                                         tm.tm_hour, tm.tm_min, tm.tm_sec));
    }
    memcpy(&dat32,  &p_buf[28], sizeof(dat32));
    AW_INFOF(("Start energy : %d\r\n",  dat32));
    memcpy(&dat16,  &p_buf[32], sizeof(dat16));
    AW_INFOF(("Used time    : %d\r\n",  dat16));
    memcpy(&dat32,  &p_buf[34], sizeof(dat32));
    AW_INFOF(("Used amount  : %d\r\n",  dat32));
    memcpy(&dat16,  &p_buf[38], sizeof(dat16));
    AW_INFOF(("Used energy  : %d\r\n",  dat16));
    memcpy(&dat16,  &p_buf[40], sizeof(dat16));
    AW_INFOF(("Stop reason  : %d\r\n",  dat16));
    memcpy(&dat16,  &p_buf[42], sizeof(dat16));
    AW_INFOF(("Charge pirce : %d\r\n\r\n",  dat16));
}

static int charge_history(int argc, char *argv[])
{
    uint8_t nums  = 1;
    uint8_t total = 0;  /* eeprom目前有效的记录数 */
    int16_t last  = 0;  /* 上一次记录的偏移位置 */
    uint8_t buf[44];
    uint8_t offset = 0; /* 偏移地址 */

    if (argc == 1) {
        nums = strtol(argv[0], NULL , 0);
    } else if (argc > 1){
        return AW_ERROR;
    }

#if ACP1000_EEPROM_CHARGE_DAT_GET
    /* 获取到上次的记录位置 */
    if(AW_OK != aw_nvram_get(ACP1000_EEPROM_NAME, 4, (char *)buf, 0, 2)) {
        AW_INFOF(("Get charge history failed!\r\n"));
        return AW_OK;
    }
    total = buf[0];
    if ((total > ACP1000_EEPROM_CHARGE_MAX_NUMS) ||
        (total == 0)) {
        /* 错误的数据，任务无效，一般EEPROM 出厂即使0xFF */
        AW_INFOF(("There is no charge history\r\n"));
        return AW_OK;
    } else {
        last  = buf[1];
    }
    AW_INFOF(("Total : %d , Last : %d\r\n", total, last));
    while (nums-- > 0) {
        offset =   last * sizeof(buf);
        memset(buf, 0, sizeof(buf));
        if(AW_OK != aw_nvram_get(ACP1000_EEPROM_NAME, 5, (char *)buf, offset, sizeof(buf))) {
            AW_INFOF(("Get charge history failed in %d.\r\n", last));
            return AW_OK;
        }

        /* 打印记录 */
        charge_history_printf(buf);

        if (0 == last) {
            last = total - 1;
        } else {
            last--;
        }
    }
#endif

    return AW_OK;
}

extern aw_err_t billing_info_eeprom_save (billing_dat_t  *p_billing_dat,
                                          billing_mode_t *p_billing_mode);

static int history_add (int argc, char *argv[])
{
    billing_dat_t  billing_dat;
    billing_mode_t billing_mode;
    aw_tm_t  tm;
    time_t   now_time;


    if (argc != 1) {
        return AW_ERROR;
    }

    memset(&billing_dat, 0, sizeof(billing_dat));
    memset(&billing_mode, 0, sizeof(billing_mode));

    memcpy(billing_mode.usr_id, argv[0], strlen(argv[0]) + 1);
    billing_mode.usr_balance = 10000;
    /* 获取起始时间 */
    aw_rtc_time_get(ACP1000_RTC_NUM, &tm);
    aw_tm_to_time(&tm, &now_time);
    memcpy(&billing_dat.start_time, &now_time, sizeof(now_time));

    if (AW_OK != billing_info_eeprom_save(&billing_dat, &billing_mode)) {
        AW_INFOF(("Failed to add charge history.\r\n"));
    } else {
        AW_INFOF(("Add charge history sus.\r\n"));
    }
    return AW_OK;
}

static int test_curr (int argc, char *argv[])
{
    uint8_t state = 0;

    if (argc != 1) {
        return AW_ERROR;
    }
    state = strtol(argv[0], NULL , 0);
    if (state > 2) {
        return AW_ERROR;
    }
    event_node_tell_all(&(gp_dubug_shell->p_pile->evt_node), ERR_AMMETER_CURR, state);
    return AW_OK;
}

static int test_vol (int argc, char *argv[])
{
    uint8_t state = 0;

    if (argc != 1) {
        return AW_ERROR;
    }
    state = strtol(argv[0], NULL , 0);
    if (state > 2) {
        return AW_ERROR;
    }
    event_node_tell_all(&(gp_dubug_shell->p_pile->evt_node), ERR_AMMETER_VOL, state);
    return AW_OK;
}

static int charge_way (int argc, char *argv[])
{
    uint32_t way, arg;

    if (argc <= 1) {
        return AW_ERROR;
    }

    way = strtol(argv[0], NULL , 0);
    arg = strtol(argv[1], NULL , 0);
    if (way > 5) {
        return AW_ERROR;
    }
    dugs_lock(gp_dubug_shell->p_dugs);
    gp_dubug_shell->p_dugs->super.wr_reg.charge_way = way;
    if (way == 2) {
        gp_dubug_shell->p_dugs->super.wr_reg.charge_amount = arg;
    } else if (way == 3) {
        gp_dubug_shell->p_dugs->super.wr_reg.charge_energy = arg;
    } else if (way == 4) {
        gp_dubug_shell->p_dugs->super.wr_reg.charge_time = arg;
    }
    dugs_unlock(gp_dubug_shell->p_dugs);


    return AW_OK;
}

static int history_clean (int argc, char *argv[])
{
    uint8_t buf[2] = {0, 0};

    if(AW_OK != aw_nvram_set(ACP1000_EEPROM_NAME, 4, (char *)buf, 0, 2)) {
       AW_INFOF(("Clean charge history failed!\r\n"));
    } else {
        AW_INFOF(("Clean charge history sus!\r\n"));
    }
    return AW_OK;
}

static int balance_clr (int argc, char *argv[])
{
    dugs_lock(gp_dubug_shell->p_dugs);
    gp_dubug_shell->p_dugs->super.rd_reg.balance_stat = AW_MB_DGUS_BALANCE_ENOUGH;
    dugs_unlock(gp_dubug_shell->p_dugs);

    return AW_OK;
}


static int ac_en(int argc, char *argv[])
{
    uint32_t cnt = 1;

    if (argc != 1) {
        return AW_ERROR;
    }
    cnt = strtol(argv[0], NULL , 0);
    aw_gpio_set(ACP1000_DOUT_AC, cnt?1:0);
    return AW_OK;
}

extern uint32_t skip_time;

static int set_skip(int argc, char *argv[])
{
    uint32_t cnt = 1;

    if (argc != 1) {
        return AW_ERROR;
    }
    skip_time = strtol(argv[0], NULL , 4);
    AW_INFOF(("set skip susccess!\r\n"));
    return AW_OK;
}

extern bool_t g_ac_check_en;

static int check_ac(int argc, char *argv[])
{
    uint32_t cnt = 1;

    if (argc != 1) {
        return AW_ERROR;
    }
    cnt = strtol(argv[0], NULL , 1);
    g_ac_check_en = cnt ? TRUE : FALSE;
    AW_INFOF(("set done en: %d!\r\n", g_ac_check_en));
    return AW_OK;
}

extern bool_t g_card_detect;

static int card_detect(int argc, char *argv[])
{
    uint32_t vol = 0;

    if (argc != 1) {
        return AW_ERROR;
    }
    vol = strtol(argv[0], NULL , 0);
    g_card_detect = vol ? TRUE : FALSE;
    return AW_OK;
}

extern uint32_t g_card_detect_period;

static int card_period(int argc, char *argv[])
{

    if (argc != 1) {
        return AW_ERROR;
    }
    g_card_detect_period = strtol(argv[0], NULL , 500);
    return AW_OK;
}
//
//extern uint32_t g_card_rx_timeout;
//
//static int card_timeout(int argc, char *argv[])
//{
//
//    if (argc != 1) {
//        return AW_ERROR;
//    }
//    g_card_rx_timeout = strtol(argv[0], NULL , 100);
//    return AW_OK;
//}
//
//extern uint32_t g_card_rx_ch_timeout;
//
//static int card_timeout_ch(int argc, char *argv[])
//{
//
//    if (argc != 1) {
//        return AW_ERROR;
//    }
//    g_card_rx_ch_timeout = strtol(argv[0], NULL , 10);
//    return AW_OK;
//}

static uint8_t key[8]       = {0};
static uint8_t sample[8]    = {0};
static uint8_t encrypt[8]   = {0};
static key_set key_sets[17];
static int des_encrypt(int argc, char *argv[])
{


    int i = 0;
    aw_tick_t   start_ticks, end_ticks;


    if (argc != 2) {
        return AW_ERROR;
    }
    for (i = 0; i < 8*2; i++) {
       if ((argv[0][i] >= 'a') && (argv[0][i] <= 'z')) {
           argv[0][i] = argv[0][i] - 'a' + 'A';
       }
       if ((argv[1][i] >= 'a') && (argv[1][i] <= 'z')) {
           argv[1][i] = argv[1][i] - 'a' + 'A';
       }
    }
    for (i = 0; i < 8*2; i++) {
       if ((argv[0][i] >= 'A') && (argv[0][i] <= 'Z')) {
           argv[0][i] = argv[0][i] - 'A' + 10;
       } else {
           argv[0][i] = argv[0][i] - '0';
       }
       if ((argv[1][i] >= 'A') && (argv[1][i] <= 'Z')) {
           argv[1][i] = argv[1][i] - 'A' + 10;
       } else {
           argv[1][i] = argv[1][i] - '0';
       }
    }

    for (i = 0; i < 8; i++) {
        key[i] = (argv[0][i*2] << 4) | (argv[0][i*2+1] << 0);
    }
    for (i = 0; i < 8; i++) {
        sample[i] = (argv[1][i*2] << 4) | (argv[1][i*2+1] << 0);
    }
    start_ticks = aw_sys_tick_get();
    des_sub_keys_generate(key, key_sets);
    des_message_process(sample, encrypt, key_sets, 1);
    end_ticks = aw_sys_tick_get();



    AW_INFOF(("key: "));
    for (i = 0; i < 8; i++) {
        AW_INFOF(("%02X", key[i]));
    }
    AW_INFOF(("  sample: "));
    for (i = 0; i < 8; i++) {
        AW_INFOF(("%02X", sample[i]));
    }
    AW_INFOF(("\r\n"));

    AW_INFOF(("Encrypt: "));
    for (i = 0; i < 8; i++) {
        AW_INFOF(("%02X", encrypt[i]));
    }
    AW_INFOF(("\r\n"));
    AW_INFOF(("Use time: %d ticks, %d ms", (end_ticks - start_ticks),
            aw_ticks_to_ms(end_ticks - start_ticks)));

    return AW_OK;
}

static int des_decrypt(int argc, char *argv[])
{
    int i = 0;
    aw_tick_t   start_ticks, end_ticks;

    if (argc != 2) {
        return AW_ERROR;
    }

    for (i = 0; i < 8*2; i++) {
       if ((argv[0][i] >= 'a') && (argv[0][i] <= 'z')) {
           argv[0][i] = argv[0][i] - 'a' + 'A';
       }
    }
    for (i = 0; i < 8*2; i++) {
       if ((argv[1][i] >= 'a') && (argv[1][i] <= 'z')) {
           argv[1][i] = argv[1][i] - 'a' + 'A';
       }
    }

    for (i = 0; i < 8*2; i++) {
       if ((argv[0][i] >= 'A') && (argv[0][i] <= 'Z')) {
           argv[0][i] = argv[0][i] - 'A' + 10;
       } else {
           argv[0][i] = argv[0][i] - '0';
       }
    }
    for (i = 0; i < 8*2; i++) {
       if ((argv[1][i] >= 'A') && (argv[1][i] <= 'Z')) {
           argv[1][i] = argv[1][i] - 'A' + 10;
       } else {
           argv[1][i] = argv[1][i] - '0';
       }
    }

    for (i = 0; i < 8; i++) {
        key[i] = (argv[0][i*2] << 4) | (argv[0][i*2+1] << 0);
    }
    for (i = 0; i < 8; i++) {
        encrypt[i] = (argv[1][i*2] << 4) | (argv[1][i*2+1] << 0);
    }
    start_ticks = aw_sys_tick_get();
    des_sub_keys_generate(key, key_sets);
    des_message_process(encrypt, sample, key_sets, 0);
    end_ticks = aw_sys_tick_get();

    AW_INFOF(("Sample: "));
    for (i = 0; i < 8; i++) {
        AW_INFOF(("%02X", sample[i]));
    }
    AW_INFOF(("\r\n"));
    AW_INFOF(("\r\n"));
    AW_INFOF(("Use time: %d ticks, %d ms", (end_ticks - start_ticks),
            aw_ticks_to_ms(end_ticks - start_ticks)));


    return AW_OK;
}

/**
 * 管理员模式调试
 */
static int admin_mode(int argc, char *argv[])
{
    uint32_t enable;

    if (argc != 1) {
        return AW_ERROR;
    }
    enable = strtol(argv[0], NULL , 0);
    if ( gp_dubug_shell->p_dugs) {
        dugs_lock(gp_dubug_shell->p_dugs);
        gp_dubug_shell->p_dugs->super.rd_reg.admin_flag = enable ? 0x55 : 0xAA;
        dugs_unlock(gp_dubug_shell->p_dugs);
    }
    return AW_OK;
}

/**
 * 清除卡密钥密文
 */
static int clen_key(int argc, char *argv[])
{
    uint8_t  buf[8]= {0};

    if(AW_OK != aw_nvram_set(ACP1000_EEPROM_NAME, 6, (char *)buf, 0, 8)) {
        return AW_ERROR;
    }
    return AW_OK;
}


static const struct aw_shell_cmd __g_dubug_shell_cmds[] = {
    {charger_info,   "charger_info",  "NULL  - ACP state get"},
    {test_ac,         "test_ac",       "NULL  - AC switch test"},
    {ac_en,           "ac_en",         "[en]  - ac en 1/enable 0/disable"},
    {test_switch,     "test_switch",   "[cnt] <dly> - AC switch press test"},
    {set_pile_id,     "set_pile_id",   "[id] - set pile id"},
    {charge_history,   "history_show", "<nums> - get charge history"},
    {history_add,      "history_add",   "[id] - add charge history"},
    {history_clean,    "history_clean",  "NULL - clean all charge history"},
    {balance_clr,      "balance_clr",    "NULL - clean balance notenough mark"},
    {test_curr,        "test_curr",      "[err] - current error test 0/normal 1/low 2/high"},
    {test_vol,         "test_vol",      "[err] - vol error test 0/normal 1/low 2/high"},
    {charge_way,       "charge_way",    "[way] [arg]- way: 1/auto 2/amount 3/energy 4/time 5/app"},
    {set_skip,          "set_skip",     "[times] each skip is 15ms "},
    {check_ac,          "check_ac",     "[en] enable/disable ac switch err check"},
    {card_detect,   "card_detect",  "[en]  - enable/disable card detect"},
    {card_period,   "card_period",  "[period]  - set card detect period"},
//    {card_timeout,   "card_timeout",  "[timeout]  - set card rx timeout"},
//    {card_timeout_ch,   "card_timeout_ch",  "[timeout]  - set card byte rx timeout"},
    {des_encrypt,   "des_encrypt",  "[key] [sample]  - des_encrypt"},
    {des_decrypt,   "des_decrypt",  "[key] [encrypt] - des_encrypt"},
    {admin_mode,    "admin_mode",  "[en] 1/enter mode  0/exit mode"},
    {clen_key,      "clen_key",  "clean up the auth key"},
};


void dubug_shell_inst_init(dubug_shell_t *p_this,
                           card_reader_t *p_card_reader,
                           billing_t     *p_billing,
                           charger_t     *p_charger,
                           dugs_t        *p_dugs,
                           hub4g_t       *p_hub4g,
                           pile_t        *p_pile)
{
    static struct aw_shell_cmd_list cl;

    if (NULL == p_this) {
        return ;
    }

    p_this->p_card_reader = p_card_reader;
    p_this->p_billing     = p_billing;
    p_this->p_charger     = p_charger;
    p_this->p_dugs        = p_dugs;
    p_this->p_hub4g       = p_hub4g;
    p_this->p_pile        = p_pile;

    gp_dubug_shell = p_this;

    AW_SHELL_REGISTER_CMDS(&cl, __g_dubug_shell_cmds);
}
