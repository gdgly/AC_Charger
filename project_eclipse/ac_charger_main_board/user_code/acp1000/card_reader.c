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
 * \brief ������ʵ��
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#include "apollo.h"
#include "card_reader.h"
#include "event_node.h"
#include "role.h"
#include "aw_task.h"
#include "string.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "cardreader/aw_iccreader.h"
#include "ac_charge_prj_cfg.h"
#include "des/des.h"
#include "aw_nvram.h"

#define LOCK_TO_CARD(p_this, p_role) \
    struct card_reader *p_this = AW_CONTAINER_OF(p_role, struct card_reader, p_card_lock)

#define AUTH_TO_CARD(p_this, p_role) \
    struct card_reader *p_this = AW_CONTAINER_OF(p_role, struct card_reader, p_card_auth)

#define RECO_TO_CARD(p_this, p_role) \
    struct card_reader *p_this = AW_CONTAINER_OF(p_role, struct card_reader, p_card_reco)

#define EVT_TO_CARD(p_this, p_evt) \
    struct card_reader *p_this = AW_CONTAINER_OF(p_evt, struct card_reader, evt_node)

static uint8_t  g_admin_buf[] = {" administrator "};

extern void acp1000_overtime_check_cancle();
extern void acp1000_overtime_check_restart();
extern void acp1000_buzzer_on (void);
/* =======================================================================  */
/**
 * ��ȡ����������
 */
static aw_err_t card_data_read (card_reader_t        *p_this,
                                uint8_t              *p_id_buf,
                                uint8_t               id_len,
                                uint8_t              *p_key,
                                uint8_t              *p_blk_dat)
{
#define STATE_CARD_ACTIVE   0  /* ��� */
#define STATE_CARD_KEYAUTH  1  /* ��֤��Կ */
#define STATE_CARD_BLKREAD  2  /* ��ȡ������ */


    int      retry = 0, i = 1;
    uint8_t  state = 1;
    uint8_t  buf[32], len;   /* ��������Ϊ30 */

    aw_iccreader_s50s70_ci_t ci;


    aw_iccreader_rf_open(p_this->dat.p_card_driver);

    while (retry <= 3) {

        switch (state) {

        /* ����� */
        case STATE_CARD_ACTIVE:
            if (AW_OK != aw_iccreader_s50s70_active (p_this->dat.p_card_driver, &ci)) {
                retry++;
            } else {
                state = STATE_CARD_KEYAUTH;

            }
            break;

        case STATE_CARD_KEYAUTH:
            if (AW_OK !=
                  aw_iccreader_key_auth(p_this->dat.p_card_driver,
                                        AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYA,
                                        p_id_buf,
                                        id_len,
                                        p_key,
                                        6,
                                        0)) {


                state = STATE_CARD_ACTIVE; /* ��֤ʧ�����¼��� */
                retry++;
            } else {
                state = STATE_CARD_BLKREAD;
                i     = 1;
            }
            break;

        case STATE_CARD_BLKREAD:
//            aw_iccreader_block_write(p_this->dat.p_card_driver,
//                                       g_admin_buf,
//                                       4);
            if (AW_OK != aw_iccreader_block_read(p_this->dat.p_card_driver,
                                                   &p_blk_dat[(i-1) * 16],
                                                   i)) {
                state = STATE_CARD_ACTIVE; /* ��֤ʧ�����¼��� */
                retry++;
            } else {
                i++;
                if (i >= 4) {
                    aw_iccreader_rf_close(p_this->dat.p_card_driver);
                    return AW_OK;
                }
            }
            break;

        default :
            break;
        }
    }
    aw_iccreader_rf_close(p_this->dat.p_card_driver);
    return AW_ERROR;
}

/* ===============================���������ɫ===================================  */

static role_ret play(role_t **pp_role, void *p_arg)  /* ���� */
{
    if ((*pp_role)->pfn_role_do) {
        return (*pp_role)->pfn_role_do(pp_role, p_arg);
    }
    return -AW_EINVAL;
}

/**
 * ��Ƭʶ����
 * p_arg : ����Ŀ�ƬID
 */
static role_ret card_reco_do (struct role **pp_role, void *p_arg)
{
    RECO_TO_CARD(p_this, pp_role);

    uint8_t *p_id_buf = (uint8_t *)p_arg;
    uint8_t  blk_dat[3 * 16];


    if (0 == memcmp(&p_this->dat.id, p_id_buf, 4)) {
        /* �������� ���Ƚ� */
        if (AW_OK != card_data_read(p_this,
                                    p_id_buf,
                                    4,
                                    &(p_this->dat.key),
                                    blk_dat)) {
            return CARD_RECO_INVAID;
        }
        if (AW_OK != memcmp(p_this->dat.blk_dat, blk_dat, sizeof(blk_dat))) {
            return CARD_RECO_INVAID;
        }
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_ING, NULL);
        aw_mdelay(200);
        return CARD_RECO_SAME;
    } else {
        /* ����ͬ�Ŀ� */
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_ING, NULL);
        return CARD_RECO_DIFF;
    }
}

/**
 * ��Ƭ������
 * p_arg : ����Ŀ�Ƭʶ����������
 */
static role_ret card_lock_do (struct role **pp_role, void *p_arg)
{
    LOCK_TO_CARD(p_this, pp_role);
    uint32_t result = (uint32_t )p_arg;

    switch (result) {

    case CARD_RECO_SAME:
        /* ���������¼� */
        event_node_tell_all(&p_this->evt_node, SCREEN_UNLOCK, NULL);

        /* ˢ���ɹ������𿨣�������ˢ�����������µ�ˢ���¼� */
        aw_iccreader_halt(p_this->dat.p_card_driver);
#if ACP1000_OVERTIME_DETECT
       acp1000_overtime_check_restart();
#endif
        break;

    /* ��Ч���Ͳ���ͬ���������������� */
    case CARD_RECO_DIFF   :
    case CARD_RECO_INVAID :
        break;
    }
}


/**
 * ��Ƭ��Ȩ��
 * �������ڣ�������ʱ
 * ��Ȩ��Ƭ�� ����ͬ�����ߵ�ǰ��Ȩ��Ч���������⿨Ƭ
 * p_arg : ����Ŀ�ƬID
 */
static role_ret card_auth_do (struct role **pp_role, void *p_arg)
{
    AUTH_TO_CARD(p_this, pp_role);
    uint8_t key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t *p_id_buf = (uint8_t *)p_arg;
    uint8_t  blk_dat[3 * 16];
    uint32_t pile_order = 0;
    aw_err_t ret;

#if ACP1000_HUB4G_AUTH
    if (!(p_this->dat.key_vaild)) {
        // todo ���濨ƬID
        event_node_tell_all(&p_this->evt_node, CARD_WAIT_KEY, p_arg);
        // todo �ȴ���Կ�·�
        ret = AW_SEMB_TAKE(p_this->p_pile_sem->hub4g_key_sem,
                           aw_ms_to_ticks(ACP1000_WAIT_KEY_TIMEOUT));
        if (ret == -ETIME) {
            event_node_tell_all(&p_this->evt_node, CARD_AUTH_FAIL, NULL);
           return AW_ERROR;
        }
    } else {
        /* ����ȴ�����Կ��ֱ�ӷ���ID */
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_ID, p_arg);
    }
#else
    memcpy(p_this->dat.key, key, 6);
#endif
    // todo ����Ƭ����
    if (AW_OK != card_data_read(p_this, p_id_buf, 4, p_this->dat.key, blk_dat)) {
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_FAIL, NULL);
        return AW_ERROR;
    }
    // todo �����Ȩ���¼�
    event_node_tell_all(&p_this->evt_node, CARD_AUTH_ING, NULL);

    // todo ����Ƭˢ���ɹ��¼�
    event_node_tell_all(&p_this->evt_node, CARD_SWING_OK, blk_dat);

    // todo �ȴ���Ȩ���
#if ACP1000_HUB4G_AUTH
    ret = AW_SEMB_TAKE(p_this->p_pile_sem->hub4g_auth_sem,
                       aw_ms_to_ticks(ACP1000_WAIT_KEY_TIMEOUT));
    if (ret == -ETIME) {
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_FAIL, NULL);
       return AW_ERROR;
    }
    ret = AW_SEMB_TAKE(p_this->p_pile_sem->hub4g_cctrl_sem,
                       aw_ms_to_ticks(ACP1000_WAIT_KEY_TIMEOUT));
    if (ret == -ETIME) {
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_FAIL, NULL);
        return AW_ERROR;
    }
    /* �ж��Ƿ������� */
    card_reader_dev_lock(p_this);
    if (!(p_this->dat.allow_charge)) {
        card_reader_dev_unlock(p_this);
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_FAIL, NULL);
        return AW_ERROR;
    }
    card_reader_dev_unlock(p_this);
#endif
    card_reader_dev_lock(p_this);
    if (p_this->pile_order) {
        card_reader_dev_unlock(p_this);
        event_node_tell_all(&p_this->evt_node, CARD_AUTH_SUS_ORDER, NULL);
        aw_iccreader_halt(p_this->dat.p_card_driver);
        return AW_OK;
    }
    card_reader_dev_unlock(p_this);

    memcpy(p_this->dat.id, p_id_buf, 4);
    memcpy(p_this->dat.blk_dat, blk_dat, sizeof(blk_dat));

//    if (0 == strcmp(g_admin_buf, blk_dat)) {
//        /* ����Ա�� */
//        event_node_tell_all(&p_this->evt_node, CARD_ADMIN_MODE, (void *)TRUE);
//        aw_mdelay(300);
//    }

    event_node_tell_all(&p_this->evt_node, CARD_AUTH_SUS, NULL);
//    aw_card_reader_detect_enable(p_this->dat.p_card_driver, TRUE);
//    /* ˢ���ɹ������𿨣�������ˢ�����������µ�ˢ���¼� */
//    aw_card_reader_halt(p_this->dat.p_card_driver);
//    aw_card_reader_detect_enable(p_this->dat.p_card_driver, FALSE);

#if ACP1000_OVERTIME_DETECT
    acp1000_overtime_check_restart();
#endif
    return AW_OK;
}

void static event_driver(struct event_node *p_evt, event_t event, void *p_arg);

static uint8_t g_sample_buf[1+ACP1000_EEPROM_CARD_KEY] = {0}; /* �����ܻ���ܵ�����*/
static uint8_t g_des_buf[8] = {0};                     /* �������ݻ���������*/
static key_set g_key_sets[17];                         /* ������Կ */
/**
 * ��EEPROM���ؿ���Կ
 * ��û�пɼ��ؿ���Կ�����ʧ�ܣ�����FALSE
 * ���سɹ�������TRUE
 */
static bool_t card_key_load_from_eeprom(uint8_t *p_key, uint8_t *p_des_key)
{
    if(AW_OK == aw_nvram_get(ACP1000_EEPROM_NAME, 6, (char *)g_sample_buf, 0, 8)) {
        des_sub_keys_generate(p_des_key, g_key_sets);
        des_message_process(&g_sample_buf[0], g_des_buf, g_key_sets, 0);
        if (0x55 == g_des_buf[0]) {
            /* ����Կ��Ч */
            memcpy(p_key, &g_des_buf[1], 6);
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * ��EEPROMд�뿨��Կ
 * ��ʧ�ܣ�����FALSE
 *   �ɹ�������TRUE
 */
static bool_t card_key_save_to_eeprom(uint8_t *p_key, uint8_t *p_des_key)
{
    g_sample_buf[0] = 0x55;
    memcpy(&g_sample_buf[1], p_key, 6);

    des_sub_keys_generate(p_des_key, g_key_sets);
    des_message_process(g_sample_buf, g_des_buf, g_key_sets, 1);

    if(AW_OK == aw_nvram_set(ACP1000_EEPROM_NAME, 6, (char *)g_des_buf, 0, 8)) {
        return TRUE;
    }
    return FALSE;
}

/**
 * ������ʵ����ʼ��
 */
void card_reader_inst_init (card_reader_t                 *p_this,
                            aw_iccreader_t                *p_card_driver,
                            const aw_iccreader_transfer_t *p_card_transfer,
                            pile_t                        *p_pile)
{
    static role_t card_auth = {card_auth_do};

    palyer_init(&p_this->player, play);
    event_node_init(&p_this->evt_node);
    p_this->evt_node.pfunc_event = event_driver;
    p_this->p_card_auth          = &card_auth;
    p_this->p_card_lock          = NULL;
    p_this->p_card_reco          = NULL;

    AW_MUTEX_INIT(p_this->role_lock, AW_SEM_Q_PRIORITY);
    AW_MUTEX_INIT(p_this->dev_lock, AW_SEM_Q_PRIORITY);
    memset(&p_this->dat, 0, sizeof(card_dat_t));
    p_this->dat.p_card_driver = p_card_driver;
    p_this->p_pile_sem        = &(p_pile->pile_sem);
    p_this->pile_order        = FALSE;
    p_this->dat.p_des_key     = (uint8_t *)(p_pile->pile_dat.mcu_uid);
    /**
     * ��ȡ��Կ
     */
    if (card_key_load_from_eeprom(p_this->dat.key, p_this->dat.p_des_key)) {
        p_this->dat.key_vaild = TRUE;
    }
    /* ��ʼ�������� */
//    aw_card_reader_zlg_inst_init(p_card_driver);
    aw_iccreader_inst_init(p_card_driver, p_card_transfer);
}

/*=============================�¼�����==========================================*/
void static event_driver(struct event_node *p_evt, event_t event, void *p_arg)
{
    EVT_TO_CARD(p_this, p_evt);
    static role_t card_reco = {card_reco_do};
    static role_t card_auth = {card_auth_do};
    static role_t card_lock = {card_lock_do};
    uint32_t arg = (uint32_t)p_arg;

    switch (event) {

    case CARD_AUTH_SUS:
        /* ��Ȩ�ɹ� */
        AW_MUTEX_LOCK(p_this->role_lock,AW_SEM_WAIT_FOREVER);
        p_this->p_card_reco = &card_reco;
        p_this->p_card_auth = &card_auth;
        p_this->p_card_lock = &card_lock;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        acp1000_buzzer_on();
        break;

    case CARD_AUTH_FAIL:
        /* ��Ȩʧ�� */
       AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
       p_this->p_card_reco = NULL;
       p_this->p_card_auth = &card_auth;
       p_this->p_card_lock = NULL;
       AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CHARGE_MAN_START:
        acp1000_overtime_check_cancle();

    case CHARGE_PIEL_START:
        /* ��翪ʼ */
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_card_reco = &card_reco;
        p_this->p_card_auth = NULL;
        p_this->p_card_lock = &card_lock;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        acp1000_buzzer_on();
        break;

    case CHARGE_PILE_STOP:
        /* ��翪ʼ */
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_card_reco = NULL;
        p_this->p_card_auth = &card_auth;
        p_this->p_card_lock = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case HUB4G_AUTH_KEY:
        card_reader_dev_lock(p_this);
        memcpy(p_this->dat.key, p_arg, 6);
        p_this->dat.key_vaild = TRUE;
        card_reader_dev_unlock(p_this);

        card_key_save_to_eeprom(p_this->dat.key, p_this->dat.p_des_key);
        break;

    case HUB4G_ALLOW_CHARGE:
        card_reader_dev_lock(p_this);
        p_this->dat.allow_charge = p_arg ? TRUE : FALSE;
        card_reader_dev_unlock(p_this);
        break;

    case HUB4G_PILE_ORDER:
        if (arg) {
            card_reader_dev_lock(p_this);
            p_this->pile_order = TRUE;
            card_reader_dev_unlock(p_this);
        }  else {
            card_reader_dev_lock(p_this);
            p_this->pile_order = FALSE;
            card_reader_dev_unlock(p_this);
        }
        break;

    default: break;
    }

}


/*=============================����============================================*/

static void card_swing_event (card_reader_t    *p_this,
                              uint8_t          *p_id_buf,
                              uint8_t           id_len)
{
    role_t *p_reco = NULL;
    role_t *p_auth = NULL;
    role_ret  ret;

    AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
    p_reco = p_this->p_card_reco;
    p_auth = p_this->p_card_auth;
    AW_MUTEX_UNLOCK(p_this->role_lock);

    if (NULL != p_reco) {
        /* �п�Ƭ��Ч  */
        ret = p_this->player.pfn_play(&p_this->p_card_reco, p_id_buf);
        if (NULL != p_auth) {
            /* ���ǰ */
            if (ret == CARD_RECO_DIFF) {
                /* ����ͬ�Ŀ�����Ҫ���¼�Ȩ */
                ret = p_this->player.pfn_play(&p_this->p_card_auth, p_id_buf);
            } else {
                /* ��ͬ�Ŀ�Ƭ����Ҫ��Ȩ��ֱ�ӽ��� */
                ret = p_this->player.pfn_play(&p_this->p_card_lock, ret);
            }
        } else {
            /* ���� */
            ret = p_this->player.pfn_play(&p_this->p_card_lock, ret);
        }
    } else {
        /* �޿�Ƭ��Ч  */
        ret = p_this->player.pfn_play(&p_this->p_card_auth, p_id_buf);
    }
}

bool_t g_card_detect = TRUE;

#define CARD_TASK_PRIO     4
#define CARD_TACK_SIZE     5120
#define CARD_DETECT_PERIOD 500
AW_TASK_DECL_STATIC(card_task, CARD_TACK_SIZE);

uint32_t g_card_detect_period = CARD_DETECT_PERIOD;

/**
 * ��̽������
 */
#define TEST_TITLE "[Test IC Card] "
#define TEST_CARD_UID_STR   TEST_TITLE"Card UID: "

static void card_detect_task (void *p_arg)
{
#define CARD_READER_STATE_INFO_GET      0 /* ��ȡ��������Ϣ */
#define CARD_READER_STATE_ACTIVE        4 /* ������ */

    int check = 0, cnt = 0, tick = 0;
    uint8_t  state = CARD_READER_STATE_ACTIVE;

    card_reader_t    *p_this = (card_reader_t *)p_arg;
    aw_iccreader_t* p_card_reader = NULL;
    aw_iccreader_s50s70_ci_t ci;
    aw_iccreader_info_t info;
    bool_t led_state = FALSE;

    if ( (NULL == p_this) ||
         (NULL == p_this->dat.p_card_driver)) {
        return;
    }

    p_card_reader = p_this->dat.p_card_driver;

    while (1) {
        switch (state) {

        case CARD_READER_STATE_INFO_GET: /* ��ȡ��������Ϣ */
            led_state = !led_state;
//            if (AW_OK != aw_iccreader_info_get(p_card_reader, &info, 8+8+1+23)) {
            if (AW_OK != aw_iccreader_led_set(p_card_reader, led_state, TRUE)) {
                cnt++;
                if (cnt >= 5) {
                /* ���������ͨ�Ź����¼� */
                    event_node_tell_all(&p_this->evt_node, ERR_CARD_READER, TRUE);
                }
            } else {
                /* ���������ͨ�������¼� */
                event_node_tell_all(&p_this->evt_node, ERR_CARD_READER, FALSE);
                cnt   = 0;
                state = CARD_READER_STATE_ACTIVE;
            }
            break;

        case CARD_READER_STATE_ACTIVE :      /* ���Ƭ��ȡUID */
            if (g_card_detect) {
                  aw_iccreader_rf_open(p_card_reader);
                  if (AW_OK == aw_iccreader_s50s70_active (p_card_reader, &ci)) {
                    aw_iccreader_rf_close(p_card_reader);
                    /* ��ӡ����UID */
                    AW_INFOF((TEST_CARD_UID_STR));
                    for(cnt = 0; (cnt < ci.uid_len) && (cnt < 4); cnt++) {
                         AW_INFOF(("%X", ci.uid[ci.uid_len-cnt-1]));
                    }
                    AW_INFOF((" %d \r\n", tick++));

                    uint8_t admin_id[] = {0x20, 0x8E, 0x83, 0xE0};
                    //if (0 == memcmp(admin_id, ci.uid, 4)) {
                        /* ����Ա�� */
                   //     event_node_tell_all(&p_this->evt_node, CARD_ADMIN_MODE, (void *)TRUE);
                   //     aw_mdelay(300);
                   // } else {
                        /* ˢ���¼����� */
                        card_swing_event(p_this, ci.uid, 4);
                   // }
                }
            }
            aw_iccreader_rf_close(p_card_reader);
            check++;
            if (check > 5) {
                check = 0;
                state = CARD_READER_STATE_INFO_GET;
            }
            break;

        default:break;
        }
        aw_mdelay(g_card_detect_period);
    }
}

void card_reader_task_startup (card_reader_t *p_this)
{
    /* ��ʼ������led_task */
    AW_TASK_INIT(card_task,              /* ����ʵ�� */
                 "card_task",            /* �������� */
                 CARD_TASK_PRIO,         /* �������ȼ� */
                 CARD_TACK_SIZE,         /* �����ջ��С */
                 card_detect_task,       /* ������ں��� */
                 (void *)p_this);        /* ������ڲ��� */
    /* �������� */
    AW_TASK_STARTUP(card_task);
}


