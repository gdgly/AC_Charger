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
 * \brief 邮箱接口
 *
 * 使用本服务需要包含头文件 aw_mailbox.h
 *
 * \par 简单示例
 * \code
 *
 * #include "apollo.h"
 * #include "aw_mailbox.h"
 *
 * AW_MAILBOX_DECL(g_mailbox, 60);
 *
 * uint32_t g_mb_buffer[60];
 *
 * static char mb_str1[] = "I'm a mail!";
 * static char mb_str2[] = "this is another mail!";
 *
 * // 任务入口函数
 * void mb_task0_entry (void *p_arg)
 * {
 *   unsigned char *str;
 *
 *     while (1) {
 *         if (AW_MAILBOX_RECV(g_mailbox, (uint32_t* )&str,
 *                 AW_SEM_WAIT_FOREVER) == AW_OK) {
 *
 *             aw_kprintf("mb_task0 get mail from mailbox, the content is %s\n",
 *                     str);
 *
 *             aw_task_delay(aw_sys_clkrate_get() * 10);
 *         }
 *     }
 *
 *     AW_SEMC_GIVE( g_sem_exit );
 * }
 *
 * // 任务入口函数
 * void mb_task1_entry (void *p_arg)
 * {
 *     uint8_t count = 0;
 *
 *     while (1) {
 *         count++;
 *
 *         if (count & 0x01) {
 *             AW_MAILBOX_SEND(g_mailbox, (uint32_t )&mb_str1[0],
 *                     AW_SEM_WAIT_FOREVER);
 *         } else {
 *             AW_MAILBOX_SEND(g_mailbox, (uint32_t )&mb_str2[0],
 *                     AW_SEM_WAIT_FOREVER);
 *         }
 *
 *         aw_task_delay(aw_sys_clkrate_get() * 20);    // 延时
 *     }
 *
 *     AW_SEMC_GIVE( g_sem_exit );
 * }
 *
 * void test_mailbox (void)
 * {
 *     AW_MAILBOX_INIT(g_mailbox);
 *
 *     AW_SEMC_INIT( g_sem_exit, 0, AW_SEM_Q_PRIORITY );
 *
 *     AW_TASK_INIT(mb_task0,
 *                  "mb_task0",
 *                  APP_TASK0_PRIO,
 *                  APP_TASK0_STACK_SIZE,
 *                  mb_task0_entry,
 *                  NULL);
 *
 *     AW_TASK_STARTUP(mb_task0);
 *
 *     AW_TASK_INIT(mb_task1,
 *                  "mb_task1",
 *                  APP_TASK0_PRIO,
 *                  APP_TASK0_STACK_SIZE,
 *                  mb_task1_entry,
 *                  NULL);
 *
 *     AW_TASK_STARTUP(mb_task1);
 *
 *     AW_SEMC_TAKE( g_sem_exit, AW_SEM_WAIT_FOREVER );
 *     AW_SEMC_TAKE( g_sem_exit, AW_SEM_WAIT_FOREVER );
 *
 *     AW_MAILBOX_TERMINATE(g_mailbox) ;
 * }
 * \endcode
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history
 * - 1.00 15-06-12  dav, create file
 * @endinternal
 */
#ifndef AW_MAILBOX_H_
#define AW_MAILBOX_H_

#include "aw_common.h"
#include "aw_msgq.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief 邮件类型定义
 */

typedef struct rtk_msgq  aw_mailbox_t;

/**
 * \brief 定义邮箱对象, 使用消息队列实现，每条消息占用4个字节
 */
#define AW_MAILBOX_DECL(mailbox, mail_num) \
            AW_MSGQ_DECL(mailbox, mail_num, 4)

/**
 * \brief 定义邮箱对象, 使用消息队列实现，每条消息占用4个字节
 */
#define AW_MAILBOX_DECL_STATIC(mailbox, mail_num) \
            AW_MSGQ_DECL_STATIC(mailbox, mail_num, 4)


/**
 * \brief 初始化邮箱
 *
 * \param mailbox       初始化的邮箱对象
 *
 * \return 成功的话返回邮箱的ID，失败则返回NULL
 */

#define AW_MAILBOX_INIT(mailbox) \
            AW_MSGQ_INIT(mailbox, 0, 0, 0)

/**
 * \brief 发送邮件
 *
 * \param mailbox       邮箱对象
 * \param data          32位无符号整形数据
 * \param timeout       超时时间
 *
 * \return 操作状态
 */

#define AW_MAILBOX_SEND(mailbox, data, timeout) \
            aw_mailbox_send(&((mailbox).super), data, timeout)

/**
 * \brief 接收邮件
 *
 * \param mailbox       邮箱对象
 * \param p_data        32位无符号整形数据指针
 * \param timeout       超时时间
 *
 * \return 操作状态
 */

#define AW_MAILBOX_RECV(mailbox, p_data, timeout) \
            aw_mailbox_recv(&((mailbox).super), p_data, timeout)

/**
 * \brief 销毁邮件对象
 *
 * 销毁邮件对象。任何等待此邮件的任务将会解阻塞，并返回 -ENXIO 。此函数不会
 * 释放邮件相关的任何内存。
 *
 * \param   mailbox     邮件对象，由 AW_MAILBOX_DECL()或 AW_MAILBOX_DECL_STATIC() 定义
 *
 * \return 操作状态
 */

#define AW_MAILBOX_TERMINATE(mailbox) \
            AW_MSGQ_TERMINATE(mailbox)

/**
 * \brief 向邮箱写入32位的整数或地址
 *
 * \param p_mailbox     要操作的邮箱缓冲
 * \param data          数据
 * \param timeout       超时时间值
 *
 * \return 发送邮件状态
 */

aw_err_t aw_mailbox_send(aw_mailbox_t *p_mailbox, const uint32_t data, int timeout);

/**
 * \brief 从邮箱中接收邮件
 *
 * \param p_mailbox     要操作的邮箱缓冲
 * \param p_data        要存放到缓冲区的数据字节，32位的无符号整形数据
 * \param timeout       超时时间值
 *
 * \return 接收邮件状态
 */

aw_err_t aw_mailbox_recv(aw_mailbox_t *p_mailbox, uint32_t *p_data, int timeout);


#ifdef __cplusplus
}
#endif

#endif /* AW_MAILBOX_H_ */
