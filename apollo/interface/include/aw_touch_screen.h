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
 * \brief 触摸屏(touch screen)标准接口
 *
 * 使用本服务需要包含以下头文件:
 * \code
 * #include "aw_touch_screen.h"
 * \endcode
 *
 * \note
 *
 *  (1) 抽象触摸设备与具体的触摸控制器无关, 它为GUI提供通用的触摸操作, 可直接替换GUI的触摸系统.
 *
 *      例如, 使用Apollo抽象触摸设备替换emwin的触摸系统
 *
 *      GUI_PID_STATE        th;                // emwin指针输入设备状态结构体
 *      struct aw_touch_state   ts_state;       // apollo触摸状态结构体
 *
 *      AW_FOREVER {
 *
 *          aw_touch_get_log_state(&ts_state);  // 获取抽象触摸设备当前逻辑坐标状态
 *
 *          th.x = ts_state.x;
 *          th.y = ts_state.y;
 *          th.Pressed = ts_state.pressed;
 *
 *          GUI_TOUCH_StoreStateEx(&th);        // 把结果存储进emwin
 *
 *          aw_touch_exec()                     // 定期对触摸设备进行轮询
 *          aw_mdelay(10);
 *      }
 *
 *
 *  (2) 如直接使用GUI的触摸系统, 则调用抽象触摸设备底层原始测量接口与GUI模块对接即可
 *
 *      void aw_touch_raw_active_x(void) — 准备Y轴电压值的测量
 *      void aw_touch_raw_active_y(void) — 准备X轴电压值的测量
 *
 *      void aw_touch_raw_measure_x(int *sample, int count);  - 测量X轴坐标
 *      void aw_touch_raw_measure_y(int *sample, int count);  - 测量Y轴坐标
 *
 *
 *  (3) 直接控制Touch Screen Controller的标准接口
 *      aw_touch_lock(bool_t lock)  — 触摸屏锁屏 (TRUE: 锁屏, FALSE: 解锁)
 *
 *
 * \internal
 * \par modification history
 * - 1.01 14-09-22  chenshuyi, add the implementation of abstract touch device.
 * - 1.00 14-07-25  chenshuyi, first implementation.
 * \endinternal
 */
#ifndef AW_TOUCH_SCREEN_H_
#define AW_TOUCH_SCREEN_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_input_touch
 * \copydoc aw_touch_screen.h
 * @{
 */


#include "apollo.h"
#include "aw_ts_lib.h"


#define AW_TOUCH_SWAP_XY    (1 << 2)


/**
 * \brief 触摸点状态
 */
struct aw_touch_state {

	uint16_t x, y;        /* x,y 坐标值 */
	uint8_t pressed;      /* 是否触摸, 1 : 触摸, 0 : 未触摸 */

};

typedef void calib_cb_func_t (void *calib_data);

/**
 * \brief 触摸屏校准(图形校准)
 *
 * \param  algorithm    校准算法
 *         pfunc        回调函数(在此回调函数中, 使用GUI绘图操作绘制校准界面)
 *
 */
int aw_touch_gui_calibrate(int algorithm, calib_cb_func_t *pfunc);

/**
 * \brief 触摸屏校准(原始接口)
 *
 * \param  info        校准数据
 *         algorithm   校准算法
 */
int aw_touch_raw_calibrate(void *info, int algorithm);

/**
 * \brief 触摸屏轮询
 *
 *        该接口需要定期调用, 对触摸屏进行轮询.
 */
void aw_touch_exec(void);

/**
 * \brief 设置触摸坐标轴方向
 *
 *        触摸坐标轴方向默认为横屏显示
 *
 * \param flags  显示标记
 *
 *        AW_TS_LIB_SWAP_XY : 交换坐标轴
 */
void aw_touch_set_orientation(int flags);

/**
 * \brief 获取触摸点逻辑状态
 */
void aw_touch_get_log_state(struct aw_touch_state *pstate);

/**
 * \brief 清除触摸点逻辑状态
 */
void aw_touch_flush_log_state(void);

/**
 * \brief 获取触摸点物理状态
 */
void aw_touch_get_phy_state(struct aw_touch_state *pstate);

/**
 * \brief 清除触摸点物理状态
 */
void aw_touch_flush_phy_state(void);

/**
 * \brief 获取滤波后的触摸测量值
 *
 *        单次触摸, 对采样后的数据集进行滤波处理,
 *        最后返回经过滤波的测量值
 *
 * \param orientation : 坐标轴方向
 */
int aw_touch_get_phys(int orientation);

/**
 * \brief 触摸屏锁屏
 *
 * \param lock  true : 锁屏
 *              false: 解锁
 */
void aw_touch_lock (bool_t lock);

/***********************************************************************************
 *
 *    抽象触摸设备底层原始测量接口
 *
 ***********************************************************************************/

/**
 * \brief 准备Y轴测量
 *
 *        (1) 接通X的测量电压, 准备对Y测量.
 *        (2) 切断Y的电压,禁用对X的测量.
 */
void aw_touch_raw_active_x (void);

/**
 * \brief 准备X轴测量
 *
 *        (1) 接通Y的测量电压, 准备对X测量.
 *        (2) 切断X的电压,禁用对Y的测量.
 */
void aw_touch_raw_active_y (void);

/**
 * \brief 测量X轴坐标
 *
 * \param sample : 存储采样值
 *        count  : 采样次数
 */
void aw_touch_raw_measure_x(uint16_t *sample, int count);

/**
 * \brief 测量Y轴坐标
 *
 * \param sample : 存储采样值
 *        count  : 采样次数
 */
void aw_touch_raw_measure_y(uint16_t *sample, int count);


#ifdef __cplusplus
}
#endif

#endif /* AW_TOUCH_SCREEN_H_ */

/* end of file */
