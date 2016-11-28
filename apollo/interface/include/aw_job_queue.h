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
 * \brief job queue library
 *
 * 使用本服务需要包含以下头文件:
 * \code
 * #include "aw_job_queue.h"
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 14-03-19  zen, first implementation
 * - 1.00 15-06-02  deo, add aw_job_queue_fill_job
 * \endinternal
 */

#ifndef __AW_JOB_QUEUE_H
#define __AW_JOB_QUEUE_H

/**
 * \addtogroup grp_aw_if_job_queue
 * \copydoc aw_isr_defer.h
 * @{
 */

#include "aw_task.h"
#include "aw_sem.h"
#include "aw_list.h"
#include "aw_spinlock.h"

#include <string.h>

#ifndef AW_SRCFG_QJOB_NUM_PRI
#define AW_SRCFG_QJOB_NUM_PRI   32
#endif

#if AW_SRCFG_QJOB_NUM_PRI > 32
#error "AW_SRCFG_QJOB_NUM_PRI can not bigger than 32"
#endif

#define AW_QJOB_ENQUEUED	0x100
#define AW_QJOB_POOL_ALLOC  0x200

#define AW_QJOB_BUSY	0x20 /* managed by client */

#define AW_QJOB_IS_BUSY(p_job)  ((p_job)->flags & AW_QJOB_BUSY)
#define AW_QJOB_SET_BUSY(p_job) ((p_job)->flags |= AW_QJOB_BUSY)
#define AW_QJOB_CLR_BUSY(p_job) ((p_job)->flags &= ~AW_QJOB_BUSY)

#define AW_QJOB_PRI_LOWEST	0	    /* minimum, least urgent priority */
#define AW_QJOB_PRI_HIGHEST 31	    /* maximum, most urgent priority */
#define AW_QJOB_NUM_PRI     32	    /* Number of prioritiies */
#define AW_QJOB_PRI_MASK    0x1f	/* Mask for priority bits */

/** 
 * \brief A QJOB is typically a member of a larger structure with information
 * used by the handler function 'func'. func() is passed a pointer to
 * the QJOB as its only argument.  
 */
typedef struct aw_qjob {
    aw_pfuncvoid_t      func;
    void               *p_arg;
    uint16_t            pri;
    uint16_t            flags;
    struct aw_list_head node;
} aw_qjob_t;

typedef struct aw_qjob_std {
    aw_qjob_t base;
    void     *arg1;
    void     *arg2;
    void     *arg3;
    void     *arg4;
} aw_qjob_std_t;


typedef struct aw_qjob_std_pool {
    struct aw_list_head  free;		/* The free list of standard jobs */
    struct aw_list_head  blocks;    /* The list of blocks of std. jobs */
    size_t               ref_count; /* How many attached job queues? */
    aw_spinlock_isr_t    *p_lock;
} aw_qjob_std_pool_t, *aw_qjob_std_pool_id_t;

typedef struct aw_job_queue {
    struct aw_list_head  jobs[AW_SRCFG_QJOB_NUM_PRI];
    uint32_t             active_pri;
    aw_qjob_std_pool_t  *p_std_pool;
    
    aw_task_id_t         task_id;   /* Task currently running */  
    AW_SEMB_DECL(semb);

    uint32_t             flags;
#define AW_JOBQ_FLG_RUNNING	0x01
#define AW_JOBQ_FLG_CREATED	0x02

    void *		        user_val;	/* reserved for queue creator */

    aw_spinlock_isr_t   lock;
} aw_job_queue_t, * aw_job_queue_id_t;

/** @} grp_aw_if_job_queue */



aw_err_t aw_job_queue_init (aw_job_queue_t        *p_jobq,
                            aw_qjob_std_pool_id_t std_pool_id);

void aw_job_queue_fill_job (aw_qjob_t       *p_job,
                            aw_pfuncvoid_t  func,
                            void            *p_arg,
                            uint16_t        pri,
                            uint16_t        flags);

aw_job_queue_id_t aw_job_queue_create (aw_qjob_std_pool_id_t std_pool_id);

void aw_job_queue_delete (aw_job_queue_id_t p_jobq);

aw_err_t aw_job_queue_post (aw_job_queue_id_t job_queue_id, aw_qjob_t *p_job);

aw_err_t aw_job_queue_std_post (aw_job_queue_id_t job_queue_id,
                                int               priority,
                                aw_pfuncvoid_t    func,
                                void             *arg1,
                                void             *arg2,
                                void             *arg3,
                                void             *arg4);

aw_err_t aw_job_queue_process (aw_job_queue_id_t job_queue_id);


aw_err_t aw_job_queue_std_pool_init (aw_qjob_std_pool_id_t std_pool_id);

aw_err_t aw_job_queue_std_jobs_alloc (aw_qjob_std_pool_id_t std_pool_id,
                                      size_t                njobs);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_JOB_QUEUE_H */

/* end of file */

