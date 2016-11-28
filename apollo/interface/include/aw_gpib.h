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
 * \brief GPIB ��׼�ӿ�
 *
 * \internal
 * \par modification history:
 * - 1.00 13-08-05  zen, first implementation
 * \endinternal
 */

#ifndef __AW_GPIB_H
#define __AW_GPIB_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/**
 * \name GPIB �ӿ�����
 * @{
 */

#define AW_GPIB_REQ_CLEAR               0
#define AW_GPIB_REQ_REMOTE_CONTROL      1
#define AW_GPIB_REQ_LOCAL_CONTROL       2
#define AW_GPIB_REQ_FINISH_RECEIVE      3
#define AW_GPIB_REQ_FINISH_SEND         4
#define AW_GPIB_REQ_READ_ERROR          5
#define AW_GPIB_REQ_WRITE_ERROR         6

/** @} */

/**
 * \brief GPIB �ӿ���������
 *
 * \param p_ctx     Ӧ��������
 * \param req       ����
 *
 * \code
 * #include <aw_gpib.h>
 *
 * aw_err_t gpib_req_handler (void *p_ctx, int req)
 * {
 *     switch (req) {
 *
 *     case AW_GPIB_REQ_CLEAR:
 *          break;
 *
 *     case AW_GPIB_REQ_FINISH_RECEIVE:
 *          aw_gpib_msg_read(...);
 *          break;
 *      ...
 *     }
 * }
 * \endcode
 */
typedef aw_err_t (* aw_gpib_req_handler_t) (void *p_ctx, int req);


/**
 * \brief ��ʼ�� GPIB �豸
 *
 * \param addr          GPIB �豸��ַ
 * \param ifmsg_handler �ӿ���Ϣ���������ӿ���Ϣ��ο�"GPIB�ӿ���Ϣ"
 * \param p_ctx         Ӧ�ó���ص����������ģ�ifmsg_handler �лص������Ĳ���
 *
 * \retval AW_OK        �ɹ�
 * \retval ��ֵ         ���󣬾��庬����ο������󷵻��롱
 */
aw_err_t aw_gpib_port_init (uint8_t                  addr,
                            aw_gpib_req_handler_t    ifmsg_handler,
                            void                     *p_ctx);

/**
 * \brief ��ȡ GPIB ��Ϣ
 *
 * \attention   ͨ���� GPIB �ӿ���Ϣ�������У����յ�"������Ϣ���"ʱ�����ñ���
 *              ����ȡ��Ϣ��Ȼ������Ϣ (ͨ������SCPI-Parser ����)
 *
 * \param p_buf �������ݻ�����
 * \param len   ����������
 *
 * \return      �ɹ���ȡ�����ֽڸ���
 */
size_t aw_gpib_data_recv (char *p_buf, size_t len);

/**
 * \brief ���� GPIB ��Ϣ
 *
 * \attention   ͨ�����Ƚ��յ���Ϣ��Ȼ�������Ϣ�����ݷ�����Ϣ
 *
 * \param p_buf ���ݻ�����
 * \param len   ����������
 *
 * \return      �ɹ�д�뵽GPIB������е��ֽڸ���
 */
size_t aw_gpib_data_send (const char *p_buf, size_t len);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_GPIB_H */

/* end of file */
