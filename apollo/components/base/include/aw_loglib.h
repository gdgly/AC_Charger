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
 * \brief ��־��Ϣ��ͷ�ļ�
 * \note 
 *       
 * \par �򵥾���
 * \code
 * aw_log_dev_t dev_uart;
 *
 * aw_loglib_cfg_init();  
 *
 * // ��ʼ���豸�ṹ��dev_uart
 * aw_loglib_log_dev_init(&dev_uart, COM0, aw_serial_write);
 * aw_loglib_dev_register(&dev_uart); // ע���豸dev_uart
 *   
 * aw_log_msg("Hello, I'm aw_log_msg\n", 0, 0, 0, 0, 0, 0);
 *
 * aw_loglib_dev_unregister(&dev_uart); // �豸dev_uartȡ��ע�� 
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
/**\brief ����һ������ָ������ */
typedef ssize_t (*aw_pfn_logger_print_t)(struct aw_logger *p_logger,
                                         const char       *p_buf,
                                         size_t            nbytes);

/**
 * \brief �豸�ṹ��.
 * �ýṹ��ʹ��˫�������豸�ڵ���������
 */
typedef struct aw_logger {
    struct aw_list_head     node;
    aw_pfn_logger_print_t   print;
} aw_logger_t;
 

/**
 * \brief ���loglib��ʼ��
 * \param[in] task_id  ����ID
 * \param[in] msgq_id  ����ID
 *
 * \retval  AW_OK        �ɹ�
 * \retval  -AW_ENOMEM   �ռ�(�ڴ�)����
 * \retval  -AW_EINVAL   ��Ч����
 */
aw_err_t aw_loglib_init (aw_task_id_t task_id, aw_msgq_id_t msgq_id);


/**
 * \brief ������Ϣ
 * \param[in] p_fmt  ��ʽ���ַ���ָ��   
 * \param[in] arg1   ����1
 * \param[in] arg2   ����2
 * \param[in] arg3   ����3
 * \param[in] arg4   ����4
 * \param[in] arg5   ����5
 * \param[in] arg6   ����6
 *
 * \retval    AW_OK    �ɹ�
 * \retval    -EINVAL  ������Ч
 * \retval    -ETIME   ������Ϣ��ʱ
 * \retval    -ENXIO   �ٵȴ���ʱ����Ϣ���б���ֹ
 * \retval    -EAGAIN  ������Ϣʧ��,�Ժ�����(timeout = AW_MSGQ_NO_WAITʱ) 
 */
aw_err_t aw_log_msg (char *p_fmt, 
                     int   arg1, 
                     int   arg2,
                     int   arg3,                            
                     int   arg4, 
                     int   arg5, 
                     int   arg6);

/**
 * \brief �豸ע��
 * \param[in] p_logger   �豸�ṹ��ָ��
 *           
 * \retval    AW_OK       �ɹ�
 * \retval    -AW_EINVAL  ������Ч
 * \retval    -AW_EPERM   ������Ĳ��������ж��е����˱�����
 * \retval    -AW_ENXIO   �����ѹر�,�޷�ע���豸
 * \retval    -EAGAIN     ����æ,������
 */                                
aw_err_t aw_logger_register(aw_logger_t          *p_logger,
                            aw_pfn_logger_print_t print);
                                
/**
 * \brief �豸ע��
 * \param[in] p_log_dev   �豸�ṹ��ָ��
 *           
 * \retval    AW_OK       �ɹ�
 * \retval    -AW_EINVAL  ������Ч
 * \retval    -AW_EPERM   ������Ĳ��������ж��е����˱�����
 * \retval    -AW_ENXIO   �����ѹر�,�޷�ע���豸
 * \retval    -EAGAIN     ����æ,������
 */
aw_err_t aw_logger_unregister(aw_logger_t *p_logger);

/** @} aw_loglib */

#ifdef __cplusplus
}
#endif

#endif /* __AW_LOGLIB_H */

/* end of file */
