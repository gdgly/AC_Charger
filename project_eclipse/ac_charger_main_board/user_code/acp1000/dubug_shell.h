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
 * \brief ���Կ�ʵ������
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#ifndef __DUBUG_SHELL_H
#define __DUBUG_SHELL_H

#include "card_reader.h"
#include "billing.h"
#include "pile.h"
#include "ammeter.h"
#include "charger.h"
#include "dugs.h"
#include "hub4g.h"

/**
 * ���Կǵ���
 */
typedef struct dubug_shell {
    card_reader_t *p_card_reader; /* ������ʵ�� */
    billing_t     *p_billing;     /* �Ʒѵ�Ԫʵ�� */
    charger_t     *p_charger;     /* �Ʒѵ�Ԫʵ�� */
    dugs_t        *p_dugs;        /* ������ʵ�� */
    hub4g_t       *p_hub4g;       /* ������ʵ�� */
    pile_t        *p_pile;        /* ׮����ʵ�� */
}dubug_shell_t;


/**
 * ������ʵ����ʼ��
 */
void dubug_shell_inst_init(dubug_shell_t *p_this,
                           card_reader_t *p_card_reader,
                           billing_t     *p_billing,
                           charger_t     *p_charger,
                           dugs_t        *p_dugs,
                           hub4g_t       *p_hub4g,
                           pile_t        *p_pile);

#endif /* __DUBUG_SHELL_H */
