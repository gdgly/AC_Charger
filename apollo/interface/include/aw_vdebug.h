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
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_vdebug.h
 *
 * \par ��ʾ��
 * \code
 *  #include "apollo.h"
 *  #include "aw_vdebug.h"
 *
 *  int age = 18;
 *  aw_kprintf("I'm %d years old!\n", age);
 * \endcode
 *
 * // �������ݴ���ӡ�����
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
 * \brief ʹ��aw_mem_alloc���뻺��������ʽ���ַ�����һ��ָ�����ȵ��ַ����˻�������
 *
 * \param pp_buffer     �����ʽ���ַ����Ļ�����
 * \param fmt           ��ʽ���ַ���
 * \param ap            ��ʽ���ַ����Ĳ����б�
 *
 * \return �ַ�������
 *
 * \par ʾ��
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
 * \brief ��ʽ���ַ�����һ��ָ�����ȵ��ַ�����������
 *
 * \param buf   �����ʽ���ַ����Ļ�����
 * \param sz    ��������С
 * \param fmt   ��ʽ���ַ���
 * \param ...   ��ʽ���ַ����Ĳ����б�
 *
 * \return number of char put into buffer
 *
 * \par ʾ��
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
 * \brief �ں˸�ʽ����ӡ����
 *
 * ����������ʽ���ַ����������ǰ�Ŀ���̨��
 *
 * \param fmt ��ʽ���ַ���
 * \param ... ��ʽ���ַ����Ĳ����б�
 *
 * \return ���������̨���ַ�����
 *
 * \par ʾ��
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
