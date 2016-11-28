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
 * \file aw_loglib_cfg.c
 * \brief ��־��Ϣ�⺯�������ļ�
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
 * - 1.00 14-11-2  liuke��wangfeilin, first implementation
 * \endinternal
 */
 
/*******************************************************************************
  headers
*******************************************************************************/
#include "apollo.h"
#include "aw_errno.h"
#include "aw_sem.h"
#include "aw_task.h"
#include "aw_msgq.h"
#include "aw_int.h"
#include "aw_list.h"
#include "aw_serial.h"
#include "aw_vdebug.h"
#include "aw_loglib.h"

#include <stdlib.h>
#include <string.h>

/*******************************************************************************
  Default configure
*******************************************************************************/

/**\brief ָ����ջ��С */
#ifndef AW_CFG_LOG_TASK_STACKSIZE
#define AW_CFG_LOG_TASK_STACKSIZE 	1024
#endif

/**\brief ָ����Ϣ���г��� */
#ifndef AW_CFG_LOG_MSQ_NUM
#define AW_CFG_LOG_MSQ_NUM 		    10
#endif

#define __LOG_MSG_SIZE              sizeof(int [8])

/**\brief ָ���������ȼ�*/
#ifndef AW_CFG_LOG_TASK_PRIORITY
#define AW_CFG_LOG_TASK_PRIORITY    (aw_task_lowest_priority() - 2)
#endif

/*******************************************************************************
  Import functions
*******************************************************************************/
extern void aw_loglib_task(void *arg);


/*******************************************************************************
  Locals
*******************************************************************************/

/**\brief ����һ������ */
AW_TASK_DECL_STATIC(loglib_task, AW_CFG_LOG_TASK_STACKSIZE);

/**\brief ����һ������ */
AW_MSGQ_DECL_STATIC(loglib_msgq, AW_CFG_LOG_MSQ_NUM, __LOG_MSG_SIZE);

/*******************************************************************************
  loglib�����ú���
*******************************************************************************/
aw_err_t aw_loglib_cfg_init (void)
{
    aw_task_id_t log_task_id;
    aw_msgq_id_t msgq_id;
        
    msgq_id = AW_MSGQ_INIT(loglib_msgq,
                           AW_CFG_LOG_MSQ_NUM,
                           __LOG_MSG_SIZE,
                           AW_MSGQ_Q_FIFO);

    if (msgq_id == NULL) {
        return -ENOMEM;
    }
    
    log_task_id = AW_TASK_INIT(loglib_task, 
                               "log_task", 
                               AW_CFG_LOG_TASK_PRIORITY, 
                               AW_CFG_LOGTASK_STACKSIZE, 
                               aw_loglib_task,
                               (void *)0);

    if (log_task_id == NULL) {
        aw_msgq_terminate(msgq_id);
        return -ENOMEM;
    }
    
    aw_loglib_init(log_task_id, msgq_id);
    
    return AW_OK;
}

/* end of file */
