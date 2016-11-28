/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file aw_loglib.h
 * \brief 日志消息库头文件
 * \note 
 *       
 * \par 简单举例
 * \code
 * aw_log_dev_t dev_uart;
 *
 * aw_loglib_cfg_init();  
 *
 * // 初始化设备结构体dev_uart
 * aw_loglib_log_dev_init(&dev_uart, COM0, aw_serial_write);
 * aw_loglib_dev_register(&dev_uart); // 注册设备dev_uart
 *   
 * aw_log_msg("Hello, I'm aw_log_msg\n", 0, 0, 0, 0, 0, 0);
 *
 * aw_loglib_dev_unregister(&dev_uart); // 设备dev_uart取消注册 
 * \endcode
 * \internal
 * \par modification history:
 * - 1.00 14-11-2  win&bob, first implementation
 * \endinternal
 */
#ifndef __AW_LOGLIB_H
#define __AW_LOGLIB_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup aw_loglib
 * \copydoc aw_loglib.h
 * @{
 */
#include "aw_list.h"
#include "aw_errno.h" 
#include "aw_task.h"
#include "aw_msgq.h"

struct aw_logger;
/**\brief 定义一个函数指针类型 */
typedef ssize_t (*aw_pfn_logger_print_t)(struct aw_logger *p_logger,
                                         const char       *p_buf,
                                         size_t            nbytes);

/**
 * \brief 设备结构体.
 * 该结构体使用双向链表将设备节点链接起来
 */
typedef struct aw_logger {
    struct aw_list_head     node;
    aw_pfn_logger_print_t   print;
} aw_logger_t;
 

/**
 * \brief 完成loglib初始化
 * \param[in] task_id  任务ID
 * \param[in] msgq_id  队列ID
 *
 * \retval  AW_OK        成功
 * \retval  -AW_ENOMEM   空间(内存)不足
 * \retval  -AW_EINVAL   无效参数
 */
aw_err_t aw_loglib_init (aw_task_id_t task_id, aw_msgq_id_t msgq_id);


/**
 * \brief 发送消息
 * \param[in] p_fmt  格式化字符串指针   
 * \param[in] arg1   参数1
 * \param[in] arg2   参数2
 * \param[in] arg3   参数3
 * \param[in] arg4   参数4
 * \param[in] arg5   参数5
 * \param[in] arg6   参数6
 *
 * \retval    AW_OK    成功
 * \retval    -EINVAL  参数无效
 * \retval    -ETIME   发送消息超时
 * \retval    -ENXIO   再等待的时候消息队列被终止
 * \retval    -EAGAIN  发送消息失败,稍后再试(timeout = AW_MSGQ_NO_WAIT时) 
 */
aw_err_t aw_log_msg (char *p_fmt, 
                     int   arg1, 
                     int   arg2,
                     int   arg3,                            
                     int   arg4, 
                     int   arg5, 
                     int   arg6);

/**
 * \brief 设备注册
 * \param[in] p_logger   设备结构体指针
 *           
 * \retval    AW_OK       成功
 * \retval    -AW_EINVAL  参数无效
 * \retval    -AW_EPERM   不允许的操作，在中断中调用了本函数
 * \retval    -AW_ENXIO   任务已关闭,无法注册设备
 * \retval    -EAGAIN     任务忙,请重试
 */                                
aw_err_t aw_logger_register(aw_logger_t          *p_logger,
                            aw_pfn_logger_print_t print);
                                
/**
 * \brief 设备注销
 * \param[in] p_log_dev   设备结构体指针
 *           
 * \retval    AW_OK       成功
 * \retval    -AW_EINVAL  参数无效
 * \retval    -AW_EPERM   不允许的操作，在中断中调用了本函数
 * \retval    -AW_ENXIO   任务已关闭,无法注销设备
 * \retval    -EAGAIN     任务忙,请重试
 */
aw_err_t aw_logger_unregister(aw_logger_t *p_logger);

/** @} aw_loglib */

#ifdef __cplusplus
}
#endif

#endif /* __AW_LOGLIB_H */

/* end of file */
