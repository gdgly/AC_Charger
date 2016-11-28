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
 * \brief ��ɫ������
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */

#ifndef __ROLE_H
#define __ROLE_H

typedef uint32_t role_type; /* �����ɫ���� */
typedef uint32_t role_ret;  /* ����ֵ */

struct role;
typedef  role_ret (*pfn_role_do_t)(struct role **pp_this, void *p_arg);  /* ��ɫ���� */

typedef struct role{
    pfn_role_do_t pfn_role_do;   /* ��ɫ���� */
}role_t;

static inline void role_build (role_t       *p_this,
                               pfn_role_do_t pfn_role_do)
{
    p_this->pfn_role_do = pfn_role_do;
}
#endif
