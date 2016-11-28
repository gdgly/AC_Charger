/*******************************************************************************
*                                 Apollo
*                       ---------------------------
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
 * \file
 * \brief isr deferal job library configure file
 *
 * \internal
 * \par modification history:
 * - 1.00 14-03-12  zen, first implementation
 * \endinternal
 */

#include "apollo.h"
#include "aw_int.h"
#include "aw_isr_defer.h"
#include "aw_sem.h"
#include "aw_assert.h"

/*******************************************************************************
  import
*******************************************************************************/
aw_import void aw_isr_defer_lib_init2 (aw_semc_id_t sem_id);
aw_import void aw_isr_defer_task(aw_semc_id_t semc_id);

/*******************************************************************************
  locals
*******************************************************************************/
AW_TASK_DECL_STATIC(__g_info_jobq, AW_CFG_ISR_DEFER_TASK_STACK_SIZE);
AW_SEMC_DECL_STATIC(__g_jobq_semc);

/*******************************************************************************
  implementation
*******************************************************************************/

/**
 *  \brief isr deferral ø‚≥ı ºªØ
 */
void aw_isr_defer_lib_init (void)
{
	aw_semc_id_t sem_id;
    aw_task_id_t task_id;


    sem_id = AW_SEMC_INIT(__g_jobq_semc, 0, AW_SEM_Q_PRIORITY);
    aw_assert(aw_semc_valid(sem_id));

    aw_isr_defer_lib_init2(sem_id);

    task_id = AW_TASK_INIT(__g_info_jobq,
                           "isr_defer",
                           AW_CFG_ISR_DEFER_TASK_PRIO,
                           AW_CFG_ISR_DEFER_TASK_STACK_SIZE,
                           aw_isr_defer_task,
                           (void *)sem_id);

    aw_assert(aw_task_valid(task_id));
    aw_task_startup(task_id);
}

/* end of file */

