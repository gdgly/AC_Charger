/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * @file
 * @brief shell config
 *
 * @internal
 * @par History
 * - 150428, rnk, First implementation.
 * @endinternal
 */

#include "aw_shell_serial.h"
#include "aw_serial.h"

#ifndef AW_CFG_SHELL_THREAD_PRIO
#define AW_CFG_SHELL_THREAD_PRIO       6u
#endif

#ifndef AW_CFG_SHELL_THREAD_STK_SIZ
#define AW_CFG_SHELL_THREAD_STK_SIZ    1536u
#endif

static struct aw_serial_shell_dev __serial_shell;
AW_TASK_DECL(shell_task, AW_CFG_SHELL_THREAD_STK_SIZ);

aw_err_t aw_serial_shell_cfg()
{
	__serial_shell.tsk = AW_TASK_INIT(shell_task,
			"aw_shell_serial",
			AW_CFG_SHELL_THREAD_PRIO,
			AW_CFG_SHELL_THREAD_STK_SIZ,
			aw_serial_shell_run,
			&__serial_shell);

	return aw_serial_shell_init(&__serial_shell, AW_CFG_CONSOLE_COMID);
}

/* end of file */
