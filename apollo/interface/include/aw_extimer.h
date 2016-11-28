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
 * \brief 扩展定时器类
 *
 * 使用本服务需要包含头文件 aw_extimer.h
 *
 * \par 简单示例
 * \code
 *
 * aw_local aw_extimer_t __g_extimer;
 *
 * aw_local void __extimer_callback(void *p_param)
 * {
 *     AW_INFOF(("__extimer_callback!\n"));
 * }
 *
 * aw_extimer_init((aw_extimer_t *)&__g_extimer,
 *         __extimer_callback, NULL);
 *
 * // 单次运行定时器
 * aw_extimer_start((aw_extimer_t *)&__g_extimer,
 *         aw_ms_to_ticks(1000),
 *         AW_TIMER_FLAG_ONE_SHOT);
 *
 * \internal
 * \par modification history
 * - 1.00 15-06-17  dav, create file
 * @endinternal
 */

#ifndef AW_EXTIMER_H_
#define AW_EXTIMER_H_

#include "rtk.h"
#include "aw_common.h"
#include "aw_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!< 单次运行标记                */
#ifndef AW_TIMER_FLAG_ONE_SHOT
#define AW_TIMER_FLAG_ONE_SHOT              0x00
#endif

/*!< 重复运行标记                */
#ifndef AW_TIMER_FLAG_PERIODIC
#define AW_TIMER_FLAG_PERIODIC              0x01
#endif

/**
 * \brief 扩展定时器对象
 * \note 不要直接操作本结构的成员
 */
struct aw_extimer
{
    struct rtk_tick     timer;
    unsigned int        flag;               /*!< timer_flag to determinate timer is ONE_SHOT or PERIODIC */
    unsigned int        tick;               /*!< initial tick count             */
    void (*timeout_callback)( void *);      /*!< timeout callback function      */
    void                *arg;               /*!< timeout callback parameter     */
};

typedef struct aw_extimer aw_extimer_t;

/**
 * \brief 初始化时间结构体
 *
 * \param p_extimer     定时器对象指针
 * \param p_func        时间定时器回调函数
 * \param p_arg         回调函数中的参数
 *
 * \return 操作状态
 */
aw_err_t aw_extimer_init(aw_extimer_t *p_extimer, aw_pfuncvoid_t p_func, void *p_arg);

/**
 * \brief 启动定时器
 *
 * \param p_extimer     定时器对象指针
 * \param ticks         定时器的执行时间
 * \param flag          定时器采用的运行形式，单次还是重复运行
 *
 * \return 操作状态
 */
aw_err_t aw_extimer_start(aw_extimer_t *p_extimer, unsigned int ticks, unsigned int flag);

/**
 * \brief 停止定时器
 *
 * \param p_extimer     定时器对象指针
 *
 * \return 操作状态
 */
aw_err_t aw_extimer_stop(aw_extimer_t *p_extimer);

#ifdef __cplusplus
}
#endif


#endif /* AW_EXTIMER_H_ */
