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
 * \brief 调试壳实例声明
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
 * 调试壳的类
 */
typedef struct dubug_shell {
    card_reader_t *p_card_reader; /* 读卡器实例 */
    billing_t     *p_billing;     /* 计费单元实例 */
    charger_t     *p_charger;     /* 计费单元实例 */
    dugs_t        *p_dugs;        /* 串口屏实例 */
    hub4g_t       *p_hub4g;       /* 集中器实例 */
    pile_t        *p_pile;        /* 桩数据实例 */
}dubug_shell_t;


/**
 * 调试类实例初始化
 */
void dubug_shell_inst_init(dubug_shell_t *p_this,
                           card_reader_t *p_card_reader,
                           billing_t     *p_billing,
                           charger_t     *p_charger,
                           dugs_t        *p_dugs,
                           hub4g_t       *p_hub4g,
                           pile_t        *p_pile);

#endif /* __DUBUG_SHELL_H */
