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
 * \brief 扮演者类声明
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */
#ifndef __PLAYER_H
#define __PLAYER_H

#include "apollo.h"
#include "role.h"

typedef  role_ret (*pfn_play_t)(role_t **pp_role, void *p_arg);  /* 扮演接口 */

typedef struct player{
    pfn_play_t pfn_play;
}player_t;


static void inline palyer_init(player_t *p_this, pfn_play_t pfn_play)
{
    p_this->pfn_play = pfn_play;
}

#endif
