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
 * \brief ����ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_mailbox.h
 *
 * \par ��ʾ��
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
 * // ������ں���
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
 * // ������ں���
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
 *         aw_task_delay(aw_sys_clkrate_get() * 20);    // ��ʱ
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
 * // �������ݴ���ӡ�����
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
 * \brief �ʼ����Ͷ���
 */

typedef struct rtk_msgq  aw_mailbox_t;

/**
 * \brief �����������, ʹ����Ϣ����ʵ�֣�ÿ����Ϣռ��4���ֽ�
 */
#define AW_MAILBOX_DECL(mailbox, mail_num) \
            AW_MSGQ_DECL(mailbox, mail_num, 4)

/**
 * \brief �����������, ʹ����Ϣ����ʵ�֣�ÿ����Ϣռ��4���ֽ�
 */
#define AW_MAILBOX_DECL_STATIC(mailbox, mail_num) \
            AW_MSGQ_DECL_STATIC(mailbox, mail_num, 4)


/**
 * \brief ��ʼ������
 *
 * \param mailbox       ��ʼ�����������
 *
 * \return �ɹ��Ļ����������ID��ʧ���򷵻�NULL
 */

#define AW_MAILBOX_INIT(mailbox) \
            AW_MSGQ_INIT(mailbox, 0, 0, 0)

/**
 * \brief �����ʼ�
 *
 * \param mailbox       �������
 * \param data          32λ�޷�����������
 * \param timeout       ��ʱʱ��
 *
 * \return ����״̬
 */

#define AW_MAILBOX_SEND(mailbox, data, timeout) \
            aw_mailbox_send(&((mailbox).super), data, timeout)

/**
 * \brief �����ʼ�
 *
 * \param mailbox       �������
 * \param p_data        32λ�޷�����������ָ��
 * \param timeout       ��ʱʱ��
 *
 * \return ����״̬
 */

#define AW_MAILBOX_RECV(mailbox, p_data, timeout) \
            aw_mailbox_recv(&((mailbox).super), p_data, timeout)

/**
 * \brief �����ʼ�����
 *
 * �����ʼ������κεȴ����ʼ������񽫻�������������� -ENXIO ���˺�������
 * �ͷ��ʼ���ص��κ��ڴ档
 *
 * \param   mailbox     �ʼ������� AW_MAILBOX_DECL()�� AW_MAILBOX_DECL_STATIC() ����
 *
 * \return ����״̬
 */

#define AW_MAILBOX_TERMINATE(mailbox) \
            AW_MSGQ_TERMINATE(mailbox)

/**
 * \brief ������д��32λ���������ַ
 *
 * \param p_mailbox     Ҫ���������仺��
 * \param data          ����
 * \param timeout       ��ʱʱ��ֵ
 *
 * \return �����ʼ�״̬
 */

aw_err_t aw_mailbox_send(aw_mailbox_t *p_mailbox, const uint32_t data, int timeout);

/**
 * \brief �������н����ʼ�
 *
 * \param p_mailbox     Ҫ���������仺��
 * \param p_data        Ҫ��ŵ��������������ֽڣ�32λ���޷�����������
 * \param timeout       ��ʱʱ��ֵ
 *
 * \return �����ʼ�״̬
 */

aw_err_t aw_mailbox_recv(aw_mailbox_t *p_mailbox, uint32_t *p_data, int timeout);


#ifdef __cplusplus
}
#endif

#endif /* AW_MAILBOX_H_ */
