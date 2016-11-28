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
 * \brief GPIB 标准接口
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
 * \name GPIB 接口请求
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
 * \brief GPIB 接口请求处理函数
 *
 * \param p_ctx     应用上下文
 * \param req       请求
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
 * \brief 初始化 GPIB 设备
 *
 * \param addr          GPIB 设备地址
 * \param ifmsg_handler 接口消息处理函数，接口消息请参考"GPIB接口消息"
 * \param p_ctx         应用程序回调函数上下文，ifmsg_handler 中回调函数的参数
 *
 * \retval AW_OK        成功
 * \retval 负值         错误，具体含义请参考“错误返回码”
 */
aw_err_t aw_gpib_port_init (uint8_t                  addr,
                            aw_gpib_req_handler_t    ifmsg_handler,
                            void                     *p_ctx);

/**
 * \brief 读取 GPIB 消息
 *
 * \attention   通常在 GPIB 接口消息处理函数中，当收到"接收消息完成"时，调用本函
 *              数读取消息，然后处理消息 (通常交由SCPI-Parser 处理)
 *
 * \param p_buf 接收数据缓冲区
 * \param len   缓冲区长度
 *
 * \return      成功读取到的字节个数
 */
size_t aw_gpib_data_recv (char *p_buf, size_t len);

/**
 * \brief 发送 GPIB 消息
 *
 * \attention   通常是先接收到消息，然后根据消息的内容发送消息
 *
 * \param p_buf 数据缓冲区
 * \param len   缓冲区长度
 *
 * \return      成功写入到GPIB输出队列的字节个数
 */
size_t aw_gpib_data_send (const char *p_buf, size_t len);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_GPIB_H */

/* end of file */
