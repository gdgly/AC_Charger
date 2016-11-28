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
 * \brief  软件定时器接口
 *
 * 使用本服务需要包含头文件 aw_timer.h
 *
 * \par 简单示例
 * \code
 *  #include "aw_timer.h"
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

#ifndef __AW_TIMER_H
#define __AW_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_timer
 * \copydoc aw_timer.h
 * @{
 */

#include "aw_psp_timer.h"

/**
 * \brief 软件定时器类型
 * \hideinitializer
 */
typedef aw_psp_timer_t   aw_timer_t;

/**
 * \brief 初始化软件定时器
 *
 *  \attention 试图初始化一个正在工作的定时器会破坏内核数据结构。
 *             用户可以先使用 aw_timer_stop() 函数停止定时器后再初始化。
 *
 * \param p_timer   软件定时器
 * \param p_func    定时器回调函数，定时结束时将调用此回调函数并传入其参数
 * \param p_arg     回调函数的参数
 *
 * \return  成功返回软件定时器的ID，失败则返回NULL
 *
 * \par 范例
 * 见 aw_timer_start()
 *
 * \sa aw_timer_start(), aw_timer_stop()
 */
void aw_timer_init (aw_timer_t *p_timer, aw_pfuncvoid_t p_func, void *p_arg);


/**
 * \brief 启动软件定时器
 *
 * 当定时结束时，软件定时器将会自动停止，若需要周期性的定时，则需要在回调函数中
 * 再次调用 aw_timer_start() 。
 *
 * \attention 可以被多次启动，以最后一次启动为准。
 *
 * \param p_timer   软件定时器
 * \param ticks     定时长度，单位：系统节拍数。可使用 aw_ms_to_ticks()
 *                  将毫秒数转换为节拍数
 * \par 范例
 * \code
 *  #include "aw_timer.h"
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
 * \sa aw_timer_init(), aw_timer_stop()
 */
void aw_timer_start (aw_timer_t *p_timer, unsigned int ticks);

/**
 * \brief 停止软件定时器
 *
 * \param p_timer  软件定时器
 *
 * \par 范例
 * 见 aw_timer_start()
 *
 * \sa aw_timer_init(), aw_timer_start()
 */
void aw_timer_stop (aw_timer_t *p_timer);

/** @} grp_aw_if_timer */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_TIMER_H */

/* end of file */

