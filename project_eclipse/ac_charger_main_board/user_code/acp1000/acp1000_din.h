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
 * \brief ACP1000 ����������ӿ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-24  xjc, first implementation
 * \endinternal
 */
#ifndef __ACP1000_DIN_H
#define __ACP1000_DIN_H

#include "charger.h"

#define ACP1000_DIN_SCREEM    PIO0_3  /* DI_SCREEM */
#define ACP1000_DIN_LIGHT     PIO0_2  /* DI_LIGHT */
#define ACP1000_DIN_AC1       PIO3_1  /* DI_AC1 */
#define ACP1000_DIN_INGUN     PIO5_4  /* DI_INLOCK ����ǹ���� ǹ��λ��� */
#define ACP1000_DIN_INLOCK    PIO3_2  /* DI_INLOCK2 ����� */
#define ACP1000_DIN_CP_C0     PIO1_22 /* DI_CP_C0 12V */
#define ACP1000_DIN_CP_C1     PIO1_21 /* DI_CP_C1 9V */
#define ACP1000_DIN_CP_C2     PIO1_20 /* DI_CP_C2 6V */
#define ACP1000_DIN_CC        PIO1_18 /* FAC */
#define ACP1000_DIN_FAC       PIO3_6  /* FAC */


/**
 * \brief ��ʼ��������������
 * \return AW_OK : ��ʼ���ɹ�
 * \return AW_ERR: ��ʼ��ʧ��
 */
aw_err_t acp1000_din_init (void);

/**
 * \brief ����TP1 ��ѹ�������
 * \param[in] p_acp1000_work_state : ����״̬ʵ��
 */
void acp1000_tp1_vol_detect_task_startup (charger_t *p_this);
#endif /* __ACP1000_DIN_H */
