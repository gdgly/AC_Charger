#include "apollo.h"
#include "cardreader/aw_iccreader.h"
#include "aw_vdebug.h"
#include "aw_shell.h"
#include "string.h"
#include "aw_serial.h"
#include "aw_delay.h"

static struct aw_iccreader *gp_iccreader = NULL;

static test(const char *info, aw_err_t state, const char *file, int line)
{
    if (state != AW_OK) {
        AW_INFOF(("Test Failed(%s in line %d): %s\r\n", file, line, info));
    }
}

#define TEST(info, state)  test(info, state, __FILE__, __LINE__)

static void test_iccreader_baud_set()
{

}


static void test_iccreader_led_set()
{
    int i = 20;
    while (i--> 0) {
        aw_iccreader_led_set(gp_iccreader, FALSE, FALSE);
        aw_mdelay(100);
        aw_iccreader_led_set(gp_iccreader, TRUE, TRUE);
        aw_mdelay(100);
        aw_iccreader_led_set(gp_iccreader, FALSE, FALSE);
        aw_mdelay(100);
        aw_iccreader_led_set(gp_iccreader, TRUE, FALSE);
        aw_mdelay(100);
        aw_iccreader_led_set(gp_iccreader, FALSE, TRUE);
        aw_mdelay(100);
    }
}


static void test_iccreader_rf()
{
    aw_iccreader_rf_close(gp_iccreader);
    aw_mdelay(200);
    aw_iccreader_rf_open(gp_iccreader);
    aw_mdelay(200);
}

static void test_iccreader_buzzer()
{
    uint32_t i = 0;
    for (i = 100; i <= 1000; i += 50) {
        aw_iccreader_buzzer_set(gp_iccreader, i, 1);
    }
    aw_iccreader_buzzer_set(gp_iccreader, 500, 4);
}

static void iccreader_info_printf(aw_iccreader_info_t *p_info)
{
    int i = 0;
    if (NULL == p_info) {
        return;
    }

    AW_INFOF(("CPU Interface: "));
    for (i = 0 ; i < 8; i++) {
        AW_INFOF(("%02X ", p_info->cpu_interface[i]));
    }
    AW_INFOF(("\r\n"));

    AW_INFOF(("ACQ Interface: "));
    for (i = 0 ; i < 8; i++) {
        AW_INFOF(("%02X ", p_info->acq_interface[i]));
    }
    AW_INFOF(("\r\n"));

    AW_INFOF(("Manu len: %02X\r\n", p_info->manu_len));

    AW_INFOF(("Manu Interface: "));
    for (i = 0 ; i < p_info->manu_len; i++) {
        AW_INFOF(("%02X ", p_info->manu_info[i]));
    }
    AW_INFOF(("\r\n"));


}
static void test_iccreader_info()
{
    aw_iccreader_info_t info;
    int i = 10;
    while (i-- > 0) {
        memset(&info, 0, sizeof(info));
        aw_iccreader_info_get(gp_iccreader, &info, 8+8+1+23);
        iccreader_info_printf(&info);
    }
}

static void test_iccreader_read( uint8_t *p_uid,  uint8_t *p_key, int blk)
{
    uint8_t buf[16] = {0};
    int i;

    TEST("key auth",
         aw_iccreader_key_auth(gp_iccreader, AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYA, p_uid, 4, p_key, 6, blk));

    TEST("block read", aw_iccreader_block_read(gp_iccreader, buf, blk));

    AW_INFOF(("Blk dat: "));
    for (i = 0 ; i < 16; i++) {
        AW_INFOF(("%02X ", buf[i]));
    }
    AW_INFOF(("\r\n"));
}


static void test_iccreader_write( uint8_t *p_uid,  uint8_t *p_key, int blk)
{
    uint8_t buf[16] = {0};
    int i;

    for (i = 0 ; i < 16; i++) {
        buf[i] = i;
    }

    TEST("key auth",
         aw_iccreader_key_auth(gp_iccreader, AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYA, p_uid, 4, p_key, 6, blk));

    TEST("block write", aw_iccreader_block_write(gp_iccreader, buf, blk));
    memset(buf, 0, sizeof(buf));
    TEST("block read", aw_iccreader_block_read(gp_iccreader, buf, blk));

    AW_INFOF(("Blk dat: "));
    for (i = 0 ; i < 16; i++) {
        AW_INFOF(("%02X ", buf[i]));
    }
    AW_INFOF(("\r\n"));
}

static void s50s70_card_info_printf(aw_iccreader_s50s70_ci_t *p_ci)
{
    int i = 0;
    if (NULL == p_ci) {
        return ;
    }

    AW_INFOF(("Card type: %02X\r\n", p_ci->key_type));
    AW_INFOF(("Card UID: "));
    for (i = 0 ; i < 4; i++) {
        AW_INFOF(("%02X ", p_ci->uid[i]));
    }
    AW_INFOF(("\r\n"));
}
static void test_iccreader_active( aw_iccreader_s50s70_ci_t *p_ci)
{

    memset(p_ci, 0, sizeof(aw_iccreader_s50s70_ci_t));

    TEST("Card Active", aw_iccreader_s50s70_active(gp_iccreader, p_ci));
    s50s70_card_info_printf(p_ci);

}


static void test_iccreader()
{
    aw_iccreader_s50s70_ci_t ci;
    uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    test_iccreader_led_set();
    test_iccreader_buzzer();
    test_iccreader_rf();
    test_iccreader_info();
    test_iccreader_active(&ci);
    test_iccreader_read(ci.uid, key, 2);
    test_iccreader_write(ci.uid, key, 2);
}

static void test_iccreader_card()
{
    aw_iccreader_s50s70_ci_t ci;
    uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    test_iccreader_active(&ci);
    test_iccreader_read(ci.uid, key, 2);
    test_iccreader_write(ci.uid, key, 2);
}


static const struct aw_shell_cmd __g_test_icc_cmds[] = {
    {test_iccreader,          "test_icc",   "NULL  - test IC Card Reader"},
    {test_iccreader_led_set,  "icc_led",    "NULL  - test iccr LED"},
    {test_iccreader_buzzer,   "icc_buzzer", "NULL  - test iccr buzzer"},
    {test_iccreader_rf,       "icc_rf",     "NULL  - test iccr rf"},
    {test_iccreader_info,     "icc_info",   "NULL  - test iccr info"},
    {test_iccreader_card,     "icc_card",   "NULL  - test iccr card"},
};

static aw_iccreader_t g_iccreader;
static struct aw_iccreader_transfer g_transfer = {
    .uart_num    = COM3,  /* 设置串口号  */
    .uart_buad   = 57600,                   /* 设置通信波特率 */
    .uart_format = CLOCAL | CREAD | CS8,    /* 通信格式 */
    .rs485_en    = FALSE,
};

void test_iccreader_shell()
{
    static struct aw_shell_cmd_list cl;
    int com = 0;

    aw_iccreader_inst_init(&g_iccreader, &g_transfer);
    gp_iccreader = &g_iccreader;
    AW_SHELL_REGISTER_CMDS(&cl, __g_test_icc_cmds);
}





