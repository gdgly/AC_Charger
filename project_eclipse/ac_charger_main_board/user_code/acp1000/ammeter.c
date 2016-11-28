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
 * \brief ���ʵ��
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "event_node.h"
#include "role.h"
#include "aw_task.h"
#include "string.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "ammeter.h"
#include "ammeter/aw_ammeter.h"
#include "ac_charge_prj_cfg.h"

#define VOL_TO_AMMETER(p_this, pp_role) \
    struct ammeter *p_this = AW_CONTAINER_OF(pp_role, struct ammeter, p_ammeter_vol)

#define CURR_TO_AMMETER(p_this, pp_role) \
    struct ammeter *p_this = AW_CONTAINER_OF(pp_role, struct ammeter, p_ammeter_curr)


#define EVT_TO_AMMETER(p_this, p_evt) \
    struct ammeter *p_this = AW_CONTAINER_OF(p_evt, struct ammeter, evt_node)

static void event_driver(struct event_node *p_evt, event_t event, void *p_arg);
static role_ret play(role_t **pp_role, void *p_arg);  /* ���� */

static role_ret ammeter_vol_do (struct role **pp_role, void *p_arg);


#define PILE_OVER_VOL_VAL    2500  /* ��ѹֵ  ��λ0.1V */
#define PILE_UNDER_VOL_VAL   1700  /* Ƿѹֵ  ��λ0.1V */

#define PILE_CURR_POINT       20000        /* ������ص�  20A*/
#define PILE_CURR_TIMEOUT     5000         /* �����쳣���ʱʱ�� ���쳣ʱ����ڸ�ʱ��ȷ��Ϊ�쳣 */
#define PILE_CURR_MIN_TIMEOUT 60000        /* ���������ص�ʱ��  */
#define PILE_CURR_MIN         3000         /* �������У��������С����  3A */

/**
 *  \brief ���ģ��ʵ����ʼ��
 *  param [in]   p_this        : ���ģ��ʵ��
 *  */
void ammeter_inst_init(ammeter_t *p_this, aw_ammeter_t *p_ammeter_driver, uint32_t max_curr)
{
    static role_t ammeter_vol    = {ammeter_vol_do};  /* �ɰ��ݵĽ�ɫ - ��ѹ����� */
    p_this->player.pfn_play      = play;
    p_this->evt_node.pfunc_event = event_driver;
    p_this->p_ammeter_driver     = p_ammeter_driver;
    p_this->p_ammeter_curr       = NULL;
    p_this->p_ammeter_vol        = &ammeter_vol;
    p_this->max_curr             = max_curr;
    p_this->start_ticks          = 0;
    p_this->abnormal_state       = FALSE;
    p_this->enable_curr_check    = TRUE;
    AW_MUTEX_INIT(p_this->dev_lock, AW_SEM_Q_PRIORITY);
    AW_MUTEX_INIT(p_this->role_lock, AW_SEM_Q_PRIORITY);
}

/* ===============================���������ɫ===================================  */
static role_ret play(role_t **pp_role, void *p_arg)  /* ���� */
{
    if ((*pp_role)->pfn_role_do) {
        return (*pp_role)->pfn_role_do(pp_role, p_arg);
    }
    return -AW_EINVAL;
}
/* ��ѹ��ؽ�ɫ */
static role_ret ammeter_vol_do (struct role **pp_role, void *p_arg)
{
#define VOL_DETECT_STEP_IDLE   0  /* ��ѹ������״̬  */
#define VOL_DETECT_STEP_UNDER  1  /* Ƿѹȷ��״̬  */
#define VOL_DETECT_STEP_OVER   2  /* ��ѹȷ��״̬  */

    VOL_TO_AMMETER(p_this, pp_role);
    int32_t  vol = (int32_t)p_arg;

    switch (p_this->vol_step) {

    case  VOL_DETECT_STEP_IDLE:
        if (PILE_UNDER_VOL_VAL >= vol) {
            /* Ƿѹ */
            p_this->vol_step = VOL_DETECT_STEP_UNDER;
        } else if (PILE_OVER_VOL_VAL <= vol) {
            /* ��ѹ */
            p_this->vol_step = VOL_DETECT_STEP_OVER;
        } else {
           if ( p_this->vol_state != AMMETER_VOL_STATE_NORMAL) {
               p_this->vol_state = AMMETER_VOL_STATE_NORMAL;
               /* todo �����ѹ�����¼� */
               event_node_tell_all(&p_this->evt_node, ERR_AMMETER_VOL, p_this->vol_state);
           }
        }

        break;

    case  VOL_DETECT_STEP_UNDER:
        if (PILE_UNDER_VOL_VAL >= vol) {
            /* Ƿѹ */
            if ( p_this->vol_state != AMMETER_VOL_STATE_UNDER) {
                p_this->vol_state = AMMETER_VOL_STATE_UNDER;
                /* todo ����Ƿѹ�쳣�¼� */
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER_VOL, p_this->vol_state);
            }
        } else {
            p_this->vol_step = VOL_DETECT_STEP_IDLE;
        }
        break;


    case VOL_DETECT_STEP_OVER:
        if (PILE_OVER_VOL_VAL <= vol) {
            /* ��ѹ */
            if ( p_this->vol_state != AMMETER_VOL_STATE_OVER) {
                p_this->vol_state = AMMETER_VOL_STATE_OVER;
                /* todo �����ѹ�쳣�¼� */
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER_VOL, p_this->vol_state);
            }
        } else {
            p_this->vol_step = VOL_DETECT_STEP_IDLE;
        }
        break;
    default:break;
    }
    return AW_OK;
}

/* ������ؽ�ɫ */
static role_ret ammeter_curr_do (struct role **pp_role, void *p_arg)
{
    CURR_TO_AMMETER(p_this, pp_role);
    uint32_t curr = (uint32_t)p_arg;
    aw_tick_t  end_ticks;
    uint32_t   timeout_ms;

    if (curr <= PILE_CURR_MIN) {
        /* �����쳣*/
        if (0 == p_this->start_ticks) {
            p_this->start_ticks = aw_sys_tick_get() + 1;
        } else {
            end_ticks  = aw_sys_tick_get();
            timeout_ms = aw_ticks_to_ms(end_ticks - p_this->start_ticks);
            if (timeout_ms > PILE_CURR_MIN_TIMEOUT) {
                 /* ���͵����쳣�ź� �������쳣 ��*/
                if (p_this->curr_state != AMMETER_CURR_STATE_UNDER) {
                    /* todo ����Ƿ���¼�*/
                    p_this->curr_state = AMMETER_CURR_STATE_UNDER;
                    event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
                }

            }
        }
    } else if (p_this->max_curr <= PILE_CURR_POINT) {

        if (curr > ( p_this->max_curr + 2000)) {
            /* �����쳣*/
            if (0 == p_this->start_ticks) {
                p_this->start_ticks = aw_sys_tick_get();
            } else {
                end_ticks  = aw_sys_tick_get();
                timeout_ms = aw_ticks_to_ms(end_ticks - p_this->start_ticks);
                if (timeout_ms > PILE_CURR_TIMEOUT) {
                     /* ���͵����쳣�ź� �������쳣 ��*/
                    if (p_this->curr_state != AMMETER_CURR_STATE_OVER) {
                        /* todo ���͹����¼�*/
                        p_this->curr_state = AMMETER_CURR_STATE_OVER;
                        event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
                    }
                }
            }
        } else  {
            /* todo �������� */
            p_this->start_ticks = 0;
            if (p_this->curr_state != AMMETER_CURR_STATE_NORMAL) {
                /* todo ���͵��������¼�*/
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
            }
            p_this->curr_state = AMMETER_CURR_STATE_NORMAL;
        }
    } else {
        if (curr > ((uint32_t)(p_this->max_curr * 1.1))) {
            /* �����쳣*/
            if (0 == p_this->start_ticks) {
                p_this->start_ticks = aw_sys_tick_get();
            } else {
                end_ticks  = aw_sys_tick_get();
                timeout_ms = aw_ticks_to_ms(end_ticks - p_this->start_ticks);
                if (timeout_ms > PILE_CURR_TIMEOUT) {

                    if (p_this->curr_state != AMMETER_CURR_STATE_OVER) {
                        /* todo ���͹����¼�*/
                        p_this->curr_state = AMMETER_CURR_STATE_OVER;
                        event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
                    }

                }
            }
        } else {
            /* todo �������� */
            p_this->start_ticks = 0;
            if (p_this->curr_state != AMMETER_CURR_STATE_NORMAL) {
                /* todo ���͵��������¼�*/
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
            }
            p_this->curr_state = AMMETER_CURR_STATE_NORMAL;

        }
    }
    return AW_OK;
}


static void event_driver(struct event_node *p_evt, event_t event, void *p_arg)
{
    EVT_TO_AMMETER(p_this, p_evt);

    static role_t ammeter_curr  = {ammeter_curr_do};

    switch (event) {

    case CHARGE_PIEL_START:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_ammeter_curr = &ammeter_curr;
        p_this->curr_state     = AMMETER_CURR_STATE_NORMAL;
        p_this->start_ticks    = 0;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    case CHARGE_PILE_STOP:
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_this->p_ammeter_curr = NULL;
        AW_MUTEX_UNLOCK(p_this->role_lock);
        break;

    default : break;

    }

}

/* ========================================================================= */
#define AMMETER_TASK_PRIO       4
#define AMMETER_TACK_SIZE       2048
#define AMMETER_DETECT_PERIOD   1000
AW_TASK_DECL_STATIC(ammeter_task, AMMETER_TACK_SIZE);

/**
 * ��̽������
 */
static void ammeter_task_entry (void *p_arg)
{
    ammeter_t *p_this = (ammeter_t *)p_arg;

    uint32_t energy = 0, scnt = 0, cnt = 0;
    int32_t  vol    = 0;
    uint32_t curr   = 0;
    role_t     *p_role[2];
    uint8_t     state = FALSE;

    if ((NULL == p_this) ||
        (NULL == p_this->p_ammeter_driver)) {
        return ;
    }
    aw_ammeter_dc_inst_init(p_this->p_ammeter_driver);

    while (1) {

        scnt++;
        /* ��ȡ���� */
        if ((AW_OK == aw_ammeter_active_energy_get(p_this->p_ammeter_driver, &energy))) {
            state = 0;
//            aw_kprintf("eng: %06d (0.01KWh)     Err: %d - %d\r\n", energy, scnt, cnt);
#if ACP1000_AMMETER_ERR_DETECT
            cnt = 0;
            if (TRUE == p_this->abnormal_state) {
                p_this->abnormal_state = FALSE;
                event_node_tell_all(&p_this->evt_node, ERR_AMMETER, FALSE);
            }
#endif
        } else {
            state = 0x1;
#if ACP1000_AMMETER_ERR_DETECT
            cnt++;
            if (cnt >= 2) {
                /* ͨ��3��ʧ�ܣ���Ϊ������쳣 */
                if (FALSE == p_this->abnormal_state) {
                    p_this->abnormal_state = TRUE;
                    event_node_tell_all(&p_this->evt_node, ERR_AMMETER, TRUE);
                }
            }
#endif
        }
        aw_mdelay(30);
        /* ��ȡ��ѹ */
        if (AW_OK == aw_ammeter_voltage_get(p_this->p_ammeter_driver, 0, &vol)) {
            state &= ~0x2;
        } else {
            state |=  0x2;
        }
        aw_mdelay(30);
        /* ��ȡ���� */
        if (AW_OK == aw_ammeter_current_get(p_this->p_ammeter_driver, 0, &curr)) {
            state &= ~0x4;
        } else {
            state |=  0x4;
        }

        if (state == 0) {
            ammeter_dev_lock(p_this);
            p_this->dat.now_curr   = curr;
            p_this->dat.now_vol    = vol;
            p_this->dat.now_energy = energy;
            ammeter_dev_unlock(p_this);

            /* ���͵������� */
            event_node_tell_all(&p_this->evt_node, AMETER_MEASURE, &p_this->dat);
        }

#if ACP1000_VOL_ERR_DETECT
        AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
        p_role[0] = p_this->p_ammeter_vol;
        AW_MUTEX_UNLOCK(p_this->role_lock);

        /* ��ص�ѹ */
        if (NULL != p_role[0]) {
            p_this->player.pfn_play(&p_this->p_ammeter_vol, vol);
        }
#endif

#if ACP1000_CURR_ERR_DETECT
        if (p_this->enable_curr_check) {
            AW_MUTEX_LOCK(p_this->role_lock, AW_SEM_WAIT_FOREVER);
            p_role[1] = p_this->p_ammeter_curr;
            AW_MUTEX_UNLOCK(p_this->role_lock);

            /* ��ص���*/
            if (NULL != p_role[1]) {
                p_this->player.pfn_play(&p_this->p_ammeter_curr, curr);
            } else {
                /* �����ص���ʱ ����Ϊ�������� */
                if (p_this->curr_state != AMMETER_CURR_STATE_NORMAL) {
                    p_this->curr_state     = AMMETER_CURR_STATE_NORMAL;
                    event_node_tell_all(&p_this->evt_node, ERR_AMMETER_CURR, p_this->curr_state);
                }
            }
        }
#endif
        aw_mdelay(AMMETER_DETECT_PERIOD);
    }
}

void ammeter_task_startup (ammeter_t *p_this)
{
    AW_TASK_INIT(ammeter_task,           /* ����ʵ�� */
                 "ammeter_task",            /* �������� */
                 AMMETER_TASK_PRIO,      /* �������ȼ� */
                 AMMETER_TACK_SIZE,      /* �����ջ��С */
                 ammeter_task_entry,     /* ������ں��� */
                 (void *)p_this);        /* ������ڲ��� */
    /* �������� */
    AW_TASK_STARTUP(ammeter_task);
}


