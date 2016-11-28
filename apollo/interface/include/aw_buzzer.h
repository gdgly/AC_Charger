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
 * \brief 蜂鸣器操作接口
 *
 * 使用本服务需要包含以下头文件:
 * \code
 * #include "aw_buzzer.h"
 * \endcode
 *
 * \par 使用示例
 * \code
 * #include "aw_buzzer.h"
 *
 * (1)GPIO驱动直流蜂鸣器
 * aw_buzzer_on();      // 蜂鸣器鸣叫
 * aw_buzzer_off();     // 关闭蜂鸣器鸣叫
 * aw_buzzer_beep(100); // 蜂鸣器鸣叫100毫秒
 *
 * (2)强度调节设备驱动无源蜂鸣器
 * aw_buzzer_loud_set(80);  // 蜂鸣器鸣叫等级
 * aw_buzzer_beep(100);     // 蜂鸣器鸣叫100毫秒
 *
 * \endcode
 *
 * \note 使用顺序约束
 *       [1]先使用aw_buzzer_loud_set
 *       [2]后使用aw_buzzer_beep/aw_buzzer_on/aw_buzzer_off
 *
 * \internal
 * \par modification history
 * - 1.01 14-07-09  ops, add aw_buzzer_loud_set
 * - 1.00 13-03-08  orz, first implementation.
 * \endinternal
 */

#ifndef __AW_BUZZER_H
#define __AW_BUZZER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_buzzer
 * \copydoc aw_buzzer.h
 * @{
 */

/** \brief 蜂鸣器鸣叫 */
void aw_buzzer_on (void);

/** \brief 关闭蜂鸣器鸣叫 */
void aw_buzzer_off (void);

/**
 * \brief 蜂鸣器鸣叫一声
 * \param beep_time_ms 鸣叫时间，单位毫秒。
 * \note 这个接口会使调用线程休眠，休眠时间为鸣叫的时间。多任务同时使用
 *      这个接口会造成非预期的鸣叫效果。
 */
void aw_buzzer_beep (unsigned int beep_time_ms);

/**
 * \brief 设置蜂鸣器鸣叫响度
 * \param beep_level 鸣叫响度等级 (0 - 100)
 * \note  该接口仅对使用了强度调节的蜂鸣器有效，如普通使用GPIO控制的
 *        蜂鸣器则无需调用该接口设置鸣叫响度
 */
void aw_buzzer_loud_set (unsigned int beep_level);

/** @} grp_aw_if_buzzer */

#ifdef __cplusplus
}
#endif

#endif /* __AW_BUZZER_H */

/* end of file */
