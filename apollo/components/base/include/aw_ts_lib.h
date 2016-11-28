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
 * \brief 触摸算法标准接口
 *
 * 使用本接口需要包含以下头文件：
 * \code
 * #include "aw_ts_lib.h"
 * \endcode
 *
 *     本接口针对触摸子系统的误差来源, 为抽象触摸设备提供了滤波、坐标校准等算法的实现
 *
 * \par 简单示例
 * \code
 *
 * \endcode
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history:
 * - 1.01 14-10-14  ops, add five point calibration algorithm.
 * - 1.00 14-09-12  ops, first implementation
 * \endinternal
 */

#ifndef AW_TS_LIB_H_
#define AW_TS_LIB_H_

#include "apollo.h"
#include "aw_types.h"

#define AW_TS_LIB_TWO_POINT    0
#define AW_TS_LIB_FIVE_POINT   1

#define AW_TS_LIB_COORD_X    0
#define AW_TS_LIB_COORD_Y    1

typedef struct point {

	long x, y;

}aw_point_t;

typedef struct factor {

	long det;
	long det_x1, det_x2, det_x3;
	long det_y1, det_y2, det_y3;

}aw_factor_t;

typedef struct minmax {

	long min, max;

}aw_minmax_t;

struct two_point_data {

	uint16_t lcd_size;        /* 该方向的lcd屏幕长度 */
	uint16_t log_a;           /* a点逻辑坐标 */
	uint16_t log_b;           /* b点逻辑坐标 */
	uint16_t phy_a;           /* a点物理坐标 */
	uint16_t phy_b;           /* b点物理坐标 */

};

struct aw_ts_lib_two_point_data {

	struct two_point_data   horizontal;
	struct two_point_data   vertical;

};

struct aw_ts_lib_five_point_data {

	aw_point_t  log[5], phy[5];   //五个点的逻辑值和物理值
	uint16_t lcd_x_size, lcd_y_size;

};

/**********************************************************************
 *
 *   滤波算法
 *
 **********************************************************************/

/** \brief 带阀值的中值滤波
 *
 *  算法原理
 *   (1) 连续采样NUM次, 按大小值对NUM次采样进行排列(使用冒泡排序, 形成降序数列).
 *   (2) 取中间两个样本, 如差值大于阀值, 则丢弃. 如小于阀值, 则计算两个样本的均值,
 *       作为本次采样的有效值.
 *
 *  \param   sample      样本集合
 *           num         样本数量
 *           threshold   阀值
 *
 *  \return  滤波后的采样值
 *
 *  \error  -EDOM  中间两个样本的差值大于阀值
 */
int aw_ts_lib_filter_median(int *sample, int num, int threshold);


/** \brief 带窗口的均值滤波
 *
 *  算法原理
 *   (1) 连续采样NUM次, 按大小值对NUM次采样进行排列(使用冒泡排序, 形成降序数列).
 *   (2) 取窗口尺寸WIN_SIZE个数据, 进行均值计算, 作为本次采样的有效值.
 *       (窗口尺寸指的是数列中间的若干个数据.)
 *
 *  \param   sample    样本集合
 *           num       样本数量
 *           win_size  窗口尺寸
 *
 *  \return  滤波后的采样值
 *
 *  \error -EINVAL  窗口尺寸大于样本数量, 窗口尺寸小于等于零
 */
int aw_ts_lib_filter_mean(uint16_t *sample, int num, int win_size);

/**********************************************************************
 *
 *   校准算法
 *
 *   使用约束 ：先调用校准接口, 后调用计算接口
 *
 **********************************************************************/

/**
 * \brief 两点触摸校准
 *
 * \param orientation     校准方向   X轴 : AW_TS_LIB_COORD_X, Y轴 : AW_TS_LIB_COORD_Y
 *        phy_minmax      该方向上的最大和最小的A/D转换值
 *        lcd_size        该方向上的lcd尺寸
 *        log_a           A点在该方向上的逻辑值
 *        log_b           B点在该方向上的逻辑值
 *        phy_a           A点逻辑值对应的A/D转换值
 *        phy_b           B点逻辑值对应的A/D转换值
 *
 * \return AW_OK     校准完成
 *
 * \error  -EINVAL   非法的校准方向
 */
int aw_ts_lib_two_point_calibrate (int orientation, aw_minmax_t *phy_minmax, int lcd_size, int log_a, int log_b, int phy_a, int phy_b);

/**
 * \brief 根据A/D转换值计算坐标值 (调用该接口前, 请先调用两点校准接口)
 *
 * \param orientation     校准方向   X轴 : AW_TS_LIB_COORD_X, Y轴 : AW_TS_LIB_COORD_Y
 *        phy             该计算点的A/D转换值
 *
 * \return  返回该校准方向上的物理值
 *
 * \error  -EINVAL   非法的校准方向, 没有先调用对应校准接口
 */
int aw_ts_lib_two_point_calculate_coord(int orientation, int phy);


/**
 * \brief 五点触摸校准
 *
 * \param pdata       校准数据
 *        threshold   验证阀值
 *                    (该算法计算完成后, 进行验证, 计算值与原值的差值需小于验证阀值, 算法才判定校准成功.)
 *
 * \return AW_OK     校准完成
 *
 * \error  -EDOM     计算值与原值的差值大于验证阀值
 */
int aw_ts_lib_five_point_calibrate(struct aw_ts_lib_five_point_data *pdata, int threshold);

/**
 * \brief 根据A/D转换值计算坐标值 (调用该接口前, 请先调用五点校准接口)
 *
 * \param  phy_x   该计算点在X轴上的A/D转换值
 *         phy_y   该计算点在Y轴上的A/D转换值
 *
 * \return log   返回该点的逻辑值
 *
 * \error  log = (-1, -1)  没有先调用对应校准接口, 不进行计算, 返回(-1, -1)
 */
aw_point_t aw_ts_lib_five_point_calculate_coord(int phy_x, int phy_y);


#endif /* AW_TS_LIB_H_ */
