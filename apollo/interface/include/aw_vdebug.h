/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief Visible debug interface, internal use only
 *
 * 使用本服务需要包含头文件 aw_vdebug.h
 *
 * \par 简单示例
 * \code
 *  #include "apollo.h"
 *  #include "aw_vdebug.h"
 *
 *  int age = 18;
 *  aw_kprintf("I'm %d years old!\n", age);
 * \endcode
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history:
 * - 1.00 12-11-23  orz, first implementation
 * \endinternal
 */

#ifndef __AW_VDEBUG_H
#define __AW_VDEBUG_H

#include <stdarg.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_vdebug
 * \copydoc aw_vdebug.h
 * @{
 */

/*******************************************************************************
    debug macro defines
*******************************************************************************/

/** \brief format log message and output */
#ifdef AW_VDEBUG
#define AW_LOGF(msg)    (void)aw_kprintf msg
#else
#define AW_LOGF(msg)
#endif

/** \brief format information message */
#ifdef AW_VDEBUG_INFO
#define AW_INFOF(info)  AW_LOGF(info)
#else
#define AW_INFOF(info)
#endif

/** \brief format information message */
#ifdef AW_VDEBUG_DEBUG
#define AW_DBGF(info)   AW_LOGF(info)
#else
#define AW_DBGF(info)
#endif

/** \brief format warning message */
#ifdef AW_VDEBUG_WARN
#define AW_WARNF(info)  AW_LOGF(info)
#else
#define AW_WARNF(info)
#endif

/** \brief format error message */
#ifdef AW_VDEBUG_ERROR
#define AW_ERRF(info)   AW_LOGF(info)
#else
#define AW_ERRF(info)
#endif

/*******************************************************************************
    debug function declare
*******************************************************************************/
extern int aw_vfprintf_do (void       *fil,
                           int       (*f_putc) (const char  c, void *fil),
                           int       (*f_puts) (const char *s, void *fil),
                           const char *str,
                           va_list     arp);

int aw_vsnprintf (char *buf, size_t sz, const char *fmt, va_list args);


/**
 * \brief 使用aw_mem_alloc申请缓冲区并格式化字符串到一个指定长度的字符串此缓冲区中
 *
 * \param pp_buffer     保存格式化字符串的缓冲区
 * \param fmt           格式化字符串
 * \param ap            格式化字符串的参数列表
 *
 * \return 字符串长度
 *
 * \par 示例
 * \code
 *  #include "apollo.h"
 *  #include "aw_vdebug.h"
 *  #include "aw_serial.h"
 *  #include <string.h>
 *
 *  char *str = NULL;
 *  int   len = 0;
 *  len = aw_asprintf(&str, "I'm %d years old!\n", 18);
 *  if ( str ) {
 *      aw_kprintf( "%s", str );
 *      aw_mem_free( str );
 *  }
 * \endcode
 */
int aw_asprintf(char **ret, const char *format, ...);
int aw_vasprintf(char **pp_buffer, const char *format, va_list args);




/**
 * \brief 格式化字符串到一个指定长度的字符串缓冲区中
 *
 * \param buf   保存格式化字符串的缓冲区
 * \param sz    缓冲区大小
 * \param fmt   格式化字符串
 * \param ...   格式化字符串的参数列表
 *
 * \return number of char put into buffer
 *
 * \par 示例
 * \code
 *  #include "apollo.h"
 *  #include "aw_vdebug.h"
 *  #include "aw_serial.h"
 *  #include <string.h>
 *
 *  char buf[64];
 *  int age = 18;
 *  aw_snprintf(&buf[0], sizeof(buf), "I'm %d years old!\n", age);
 *  aw_serial_write(COM1, &buf[0], strlen(buf));
 * \endcode
 */
#ifndef AW_SNPRINTF_DEFINED
extern int aw_snprintf (char *buf, size_t sz, const char *fmt, ...);
#endif  /* AW_SNPRINTF_DEFINED */

/**
 * \brief 内核格式化打印函数
 *
 * 本函数将格式化字符串输出到当前的控制台。
 *
 * \param fmt 格式化字符串
 * \param ... 格式化字符串的参数列表
 *
 * \return 输出到控制台的字符个数
 *
 * \par 示例
 * \code
 *  #include "apollo.h"
 *  #include "aw_vdebug.h"
 *
 *  int age = 18;
 *  aw_kprintf("I'm %d years old!\n", age);
 * \endcode
 */
#ifndef AW_KPRINTF_DEFINED
extern int aw_kprintf (const char *fmt, ...);
#endif  /* AW_KPRINTF_DEFINED */

/* @} grp_aw_if_vdebug */

#ifdef __cplusplus
}
#endif

#endif /* __AW_VDEBUG_H */

/* end of file */
