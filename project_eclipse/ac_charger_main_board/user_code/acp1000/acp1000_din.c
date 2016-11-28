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
 * \brief ACP1000 ����������ӿ�ʵ��
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-24  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "acp1000_din.h"
#include "aw_gpio.h"
#include "lpc177x_8x_pin.h"
#include "ac_charge_prj_cfg.h"
#include "aw_delay.h"
#include "charger.h"

#define TP1_VOL_DETECT_TASK_PRIO    1
#define TP1_VOL_DETECT_TACK_SIZE    (1024)
AW_TASK_DECL_STATIC(tp1_vol_detect_task, TP1_VOL_DETECT_TACK_SIZE);

#define TP1_DETECT_PERIOD_MS   15  /* TP1 ������� , ��λms*/
#define TP1_DETECT_SKIP_MS     25  /* TP1 �������, ��λms*/

uint32_t skip_time = 4;

/**
 * \brief ��ȡ����1�ĵ�ѹ
 * \param[in] p_acp1000:  ��������ʵ��
 * \return    ����1�ĵ�ѹֵ�������¿��ܣ�
 *            - 12 : ����Ϊ12V
 *            - 9  : ����Ϊ9V
 *            - 6  : ����Ϊ6V
 */
aw_local uint32_t acp1000_tp1_raw_vol_get ()
{
    static int err_cnt = 0;
    static int last_vol = 0;
    uint8_t vol[3] = {1, 1, 1};
    uint8_t tp1_vol;

    vol[0] = aw_gpio_get(ACP1000_DIN_CP_C0);
    vol[1] = aw_gpio_get(ACP1000_DIN_CP_C1);
    vol[2] = aw_gpio_get(ACP1000_DIN_CP_C2);

//    AW_INFOF(("CP0 = %d\r\nCP1 = %d\r\nCP2 = %d\r\n", vol[0], vol[1], vol[2]));

    if ((vol[0] == 0) && (vol[1] == 1) && (vol[2] == 1)) {
        tp1_vol  = 12;
        err_cnt  = 0;
        last_vol = tp1_vol;
    } else if ((vol[0] == 1) && (vol[1] == 0) && (vol[2] == 1)) {
        tp1_vol = 9;
        err_cnt = 0;
        last_vol = tp1_vol;
    } else if ((vol[0] == 1) && (vol[1] == 1) && (vol[2] == 0)) {
        err_cnt= 0;
        tp1_vol = 6;
        last_vol = tp1_vol;
    } else {
        err_cnt++;
        if (err_cnt > skip_time) {
            tp1_vol = 0; /* ��������Ϊ��12V�������д����� */
            last_vol = tp1_vol;
        }
        /* ����  */
    }

//    AW_INFOF(("Vtp1 = %dV\r\n", tp1_vol));
    return last_vol;
}

/**
 * ����ѹ����
 */
aw_local void charger_tp1_vol_detect_task (void *p_arg)
{
#define __TP1_VOL_DETECT_GET  0  /* ��ȡ��ѹֵ */
#define __TP1_VOL_DETECT_SURE 1  /* ȷ��  */

    charger_t *p_this = (charger_t *)p_arg;
    uint8_t    state        = __TP1_VOL_DETECT_GET;

    uint8_t now_vol, last_vol;
    static  int cnt = 0;


    if (NULL == p_this) {
        return ;
    }
    last_vol = 0;

    while  (1) {
        cnt--;
        if (cnt <= 0) {
            cnt = 0;
        }

        switch (state) {

        case __TP1_VOL_DETECT_GET:
            now_vol = acp1000_tp1_raw_vol_get();
            if (last_vol != now_vol) {
                state = __TP1_VOL_DETECT_SURE;
                aw_mdelay(TP1_DETECT_SKIP_MS); /* ��������ʱ */
            } else {
                break;
            }

        case __TP1_VOL_DETECT_SURE:
            now_vol = acp1000_tp1_raw_vol_get();
            if (last_vol != now_vol) {
                last_vol = now_vol;
                state = __TP1_VOL_DETECT_GET;
#if ACP1000_VTP1_DETECT
                charger_dev_lock(p_this);
                p_this->dat.tp1_vol = now_vol;
                charger_dev_unlock(p_this);
#endif
            }
            break;

        default: break;
        }
        aw_mdelay(TP1_DETECT_PERIOD_MS); /* �����ʱ */
    }
}

/**
 * \brief ����TP1 ��ѹ�������
 * \param[in] p_this : ����ʵ��
 */
void acp1000_tp1_vol_detect_task_startup (charger_t *p_this)
{

    /* ��ʼ������led_task */
    AW_TASK_INIT(tp1_vol_detect_task,              /* ����ʵ�� */
                 "Vtp1_detect_task",               /* �������� */
                 TP1_VOL_DETECT_TASK_PRIO,         /* �������ȼ� */
                 TP1_VOL_DETECT_TACK_SIZE,         /* �����ջ��С */
                 charger_tp1_vol_detect_task,      /* ������ں��� */
                 (void *)p_this);    /* ������ڲ��� */
    /* �������� */
    AW_TASK_STARTUP(tp1_vol_detect_task);


}

/**
 * \brief ��ʼ��������������
 * \return AW_OK : ��ʼ���ɹ�
 * \return AW_ERR: ��ʼ��ʧ��
 */
aw_err_t acp1000_din_init (void)
{
    /* data input */
    int acp_din[] = {
                     ACP1000_DIN_SCREEM  ,
                     ACP1000_DIN_LIGHT   ,
                     ACP1000_DIN_AC1     ,
                     ACP1000_DIN_INGUN   ,
                     ACP1000_DIN_INLOCK  ,
                     ACP1000_DIN_CP_C0   ,
                     ACP1000_DIN_CP_C1   ,
                     ACP1000_DIN_CP_C2   ,
                     ACP1000_DIN_CC      ,
                     };

    int i        = 0;

    /* init din */
    for (i = 0; i < sizeof(acp_din)/sizeof(acp_din[0]); i++) {
        am_gpio_pin_cfg(acp_din[i], AM_GPIO_INPUT);
    }
    am_gpio_pin_cfg(ACP1000_DIN_FAC, AM_GPIO_INPUT);


    return AW_OK;
}
