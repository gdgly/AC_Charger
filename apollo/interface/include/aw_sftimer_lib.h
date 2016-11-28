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
 * \brief  软件定时器库
 *
 * 使用本服务需要包含以下头文件：
 * \code
 * #include "aw_timer_lib.h"
 * \endcode
 *
 * \par 简单示例
 * \code
 *  #include "aw_timer_lib.h"
 *
 *  // 定时器回调函数
 *  void my_callback (void *p_arg)
 *  {
 *      aw_timer_t  *p_timer = p_arg;
 *     // ...
 *     aw_timer_start(p_timer, aw_ms_to_tick(500));     // 再次定时500ms
 *  }
 *
 *  int main() {
 *      aw_timer_t  timer;
 *
 *      // 初始化定时器
 *      aw_timer_init(&timer, my_callback, &timer);
 *
 *      // 启动定时器，定时500ms
 *      aw_timer_start(&timer, aw_ms_to_tick(500));
 *
 *      // 延时 20S.
 *      aw_task_delay(aw_ms_to_tick(20 * 1000));
 *
 *      // 停止定时器
 *      aw_timer_stop(&timer);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history:
 * - 1.10 13-03-21  zen, refine the description
 * - 1.01 13-02-22  orz, fix the defines and code style.
 * - 1.00 12-10-23  liangyaozhan, first implementation.
 * \endinternal
 */

#ifndef __AW_SFTIMER_LIB_H
#define __AW_SFTIMER_LIB_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/*
 * \addtogroup grp_aw_if_timer
 * \copydoc aw_timer.h
 * @{
 */

#include "aw_list.h"


/** \brief timer bucket */
struct aw_sftimer_bucket {
    struct aw_list_head list_head;
};

/** \brief timer group */
struct aw_sftimer_group {
    struct aw_sftimer_bucket *p_buckets;
    size_t                    bucket_cnt;
    unsigned int              cur_bucket;
    unsigned int              clkrate;
};


/** \brief timer data type, user should never modify the fields directily */
struct aw_sftimer {
    struct aw_list_head listnode;   /**< \brief timer list node */
    uint32_t            bucket;     /**< \brief bucket index */
    uint32_t            round;      /**< \brief round number of all bunckets */
    uint32_t            expires;    /**< \brief expire time */

    void (*func)(void *arg);        /**< \brief timeout function */
    void  *arg;                     /**< \brief timeout function argument */

    struct aw_sftimer_group *p_timer_grp;
};

void aw_sftimer_group_tick (struct aw_sftimer_group *p_timer_grp);

aw_err_t aw_sftimer_group_init (struct aw_sftimer_group  *p_timer_grp,
                                struct aw_sftimer_bucket *p_buckets,
                                size_t                    bucket_cnt,
                                unsigned int              clkrate);

aw_err_t aw_sftimer_init (struct aw_sftimer *p_timer,
                          struct aw_sftimer_group *p_timer_grp,
                          void     (*func) (void *arg),
                          void      *arg);

aw_err_t aw_sftimer_start (struct aw_sftimer *p_timer,
                           unsigned int  ticks);

aw_err_t aw_sftimer_start_ms (struct aw_sftimer *p_timer,
                              unsigned int       ms);

aw_err_t aw_sftimer_restart (struct aw_sftimer *p_timer);

aw_err_t aw_sftimer_stop (struct aw_sftimer *p_timer);

/** @} grp_aw_if_timer */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_SFTIMER_LIB_H */

/* end of file */

