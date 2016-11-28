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
 * @brief A simple shell.
 *
 * @internal
 * @par History
 * - 151203, dcf, 将函数指针io_printf标志为删除状态, 增加aw_shell_printf(),aw_shell_putc/s, aw_shell_getc
 * - 150428, rnk, support multiuser
 * - 140115, orz, first implementation.
 * @endinternal
 */

#ifndef __AW_SHELL_H
#define __AW_SHELL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include "aw_vdebug.h"
#include "aw_common.h"
#include "aw_list.h"
#include "io/aw_dirent.h"

/******************************************************************************/
/**
 * @defgroup shell_cfg Shell configurations
 * The tty shell dependent on standard I/O
 * @{
 */
#define SHELL_ENABLED

/** Use shell symbol */
//#define SHELL_USE_SYMBOL

/** Use cursor */
#define SHELL_USE_CURSOR

/**
 * SHELL_USE_DAEMON             Enable shell command run as daemon
 * SHELL_DAEMON_THREAD_PRIO     Daemon thread prio
 * SHELL_DAEMON_THREAD_STKSIZ   Daemon thread stack size
 */
//#define SHELL_USE_DAEMON
#define SHELL_DAEMON_THREAD_PRIO    (1u)
#define SHELL_DAEMON_THREAD_STKSIZ  1024u

/**
 * SHELL_USE_HISTORY        Use history
 * SHELL_HISTORY_COUNT      History count
 */
#define SHELL_USE_HISTORY
#define SHELL_HISTORY_COUNT         9u

/**
 * SHELL_USE_MEMDUMP      Memory dump command
 */
//#define SHELL_USE_MEMDUMP

/******************************************************************************/
/** \brief shell I/O function */
struct aw_shell_user;
typedef int (*aw_shell_io_printf_t)(struct aw_shell_user *sh, const char *fmt, ...);
typedef int (*aw_shell_io_puts_t)(struct aw_shell_user *sh, const char *s);
typedef int (*aw_shell_io_putc_t)(struct aw_shell_user *sh, int ch);
typedef int (*aw_shell_io_getc_t)(struct aw_shell_user *sh);

typedef enum shell_user_state {
	SUS_UNINIT = 0,
	SUS_RUNING,
	SUS_EXITING,
	SUS_DEAD,
}shell_user_state_t;

typedef struct aw_fs_state {
    char pwd[NAME_MAX];
    char path[NAME_MAX];
    char buf[NAME_MAX];
}aw_fs_state_t;

struct aw_shell_context;
typedef struct aw_shell_user {
	aw_shell_io_printf_t io_printf; /* NOTE: 不要使用此函数， 准备删除  */
	aw_shell_io_puts_t io_puts;
	aw_shell_io_putc_t io_putc;
	aw_shell_io_getc_t io_getc;
	shell_user_state_t state;
	struct aw_shell_context *sc;
	void* user_arg;
	aw_fs_state_t      fs_state;
}aw_shell_user_t;

/** \brief dbg shell io function */
struct aw_shell_user *aw_dbg_shell_user();
#define AW_DBG_SHELL_IO aw_dbg_shell_user()

/** \brief shell命令的函数原型 */
typedef int (*aw_shellcmd_t)(int argc, char *argv[], struct aw_shell_user *);

/** \brief shell command item */
typedef struct aw_shell_cmd {
	aw_shellcmd_t entry;/* Command entry */
    const char *name;   /* Name */
    const char *desc;   /* Descriptions (usage) */
}aw_shell_cmd_item_t;

/** \brief shell command array list */
typedef struct aw_shell_cmd_list {
	struct aw_shell_cmd_list *next;     	  /* Next commands list */
    const struct aw_shell_cmd *start;    /* Head of this commands array */
    const struct aw_shell_cmd *end;      /* Tail of this commands array */
}aw_shell_cmd_list_t;

/** \brief register a shell command list */
aw_err_t aw_shell_register_cmds(struct aw_shell_cmd_list *list,
        const struct aw_shell_cmd *start,
        const struct aw_shell_cmd *end);

#define AW_SHELL_REGISTER_CMDS(p_list, cmds) \
	aw_shell_register_cmds(p_list, &cmds[0], &cmds[AW_NELEMENTS(cmds)])

/** \brief unregister a shell command list */
aw_err_t aw_shell_unregister_cmds(struct aw_shell_cmd_list *list);

/**
 * \brief call a shell command presented by a string.
 *        目前aw_shell_system默认调用的shell实例为串口实例
 * \param cmd_name_arg command name and argument string, e.g. "help clr".
 * \return returns -ENOENT if command not find, return other value is command
 *         execute error number, AW_OK for success, \see errno.
 */
int aw_shell_system(const char *cmd_name_arg);


/**
 * \brief shell printf
 */
int aw_shell_printf(aw_shell_user_t *sh, const char *fmt, ... );

/**
 * \brief
 */
aw_inline aw_local int aw_shell_putc( aw_shell_user_t *__sh, int c )
{
	if ( __sh->io_putc ) {
		return __sh->io_putc( __sh, c );
	}
	else {
		return -1;
	}
}

/**
 * \brief
 */
aw_inline aw_local int aw_shell_puts( aw_shell_user_t *__sh, const char *str )
{
	if ( __sh->io_puts ) {
		return __sh->io_puts( __sh, str );
	} else {
		return -1;
	}
}

/**
 * \brief shell user getc
 *
 */
aw_inline aw_local int aw_shell_getc( aw_shell_user_t *__sh )
{
	if ( __sh->io_getc ) {
		return __sh->io_getc( __sh );
	} else {
		return -1;
	}
}

/******************************************************************************/
/** \brief shell context define */
#define SHELL_LINE_SIZE         79u
#ifndef SHELL_HISTORY_COUNT
#define SHELL_HISTORY_COUNT     5u
#elif SHELL_HISTORY_COUNT < 2u
#undef SHELL_HISTORY_COUNT
#define SHELL_HISTORY_COUNT     2u
#endif

#ifdef SHELL_USE_HISTORY
struct aw_shell_his {
    struct aw_list_head  list;    /* double ring list node */
    int                  len;     /* length of history input */
    char                 buf[SHELL_LINE_SIZE + 1];
};
#endif /* SHELL_USE_HISTORY */

typedef enum {
    SHELL_UNINIT = 0,   /* Uninitialized state */
    SHELL_WAIT_INPUT,   /* Wait for user input a command */
    SHELL_EXE_CMD       /* Execute a command */
} shellstate_t;

/**
 * @brief Simple shell context struct.
 */
struct aw_shell_context {
    shellstate_t         state;      /* Shell state */
    int                  line_len;
#ifdef SHELL_USE_CURSOR
    int                  cursor_pos; /* position of cursor */
#endif
    char                 line_buf[SHELL_LINE_SIZE + 1];
#ifdef SHELL_USE_HISTORY
    int                  his_count; /* Counter for history serach */
    struct aw_list_head *his_in;    /* history ring list in point */
    struct aw_list_head *his_out;   /* history ring list out point */
    struct aw_shell_his  his_buf[SHELL_HISTORY_COUNT];
#endif
};

/**
 * \brief 运行一个shell实例
 * \param sc        shell运行时上下文结构体
 * \param sh        shell在用户任务中的上下文
 * \retval AW_OK    运行成功
 */
aw_err_t aw_shell_init(struct aw_shell_context *sc, struct aw_shell_user *sh);
aw_err_t aw_shell_server(struct aw_shell_context *sc, struct aw_shell_user *sh);

/**
 * \brief 从shell中读取一行
 * \param s         shell在用户任务中的上下文
 * \param s         传入字符缓冲区
 * \param count     传入字符缓冲区的长度
 * \retval          成功返回读取到的字节数
 */
int aw_shell_gets(struct aw_shell_user *sh, char *s, int count);
/*int aw_shell_scanf(struct aw_shell_user *sh, char* fmt, ...);*/

#ifdef __cplusplus
}
#endif

#endif /* __AW_SHELL_H */

/* end of file */
