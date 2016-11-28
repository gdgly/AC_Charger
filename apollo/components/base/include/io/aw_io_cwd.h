/*******************************************************************************
*                                  Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Current work directory management
 *
 * \internal
 * \par modification history:
 * - 150420 deo, first implementation.
 * \endinternal
 */
#ifndef AW_IO_CWD_H_
#define AW_IO_CWD_H_

#include "apollo.h"
#include "aw_sem.h"
#include "io/aw_dirent.h"

struct aw_cwd_struct {
	char	cwd[NAME_MAX];
	int		err;
	int		id;
	struct aw_cwd_struct *p_next;
	AW_MUTEX_DECL(mutex);
};

void aw_cwd_init (void);

int aw_cwd_register (struct aw_cwd_struct *cwd, int user_id);

struct aw_cwd_struct *aw_find_cwd_struct (int user_id);

char *aw_cwd_get (struct aw_cwd_struct *p_cwd);
char *aw_cwd_uget (int user_id);

int aw_cwd_set (struct aw_cwd_struct *p_cwd, char *path);
int aw_cwd_uset (int user_id, char *path);

int aw_cwd_err_set (struct aw_cwd_struct *p_cwd, int err);
int aw_cwd_err_check (struct aw_cwd_struct *p_cwd, int *err);

#endif /* AW_IO_CWD_H_ */
