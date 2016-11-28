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
 * \brief 输入子系统通用标准接口
 *
 *    通用输入接口包括鼠标、键盘、摇杆、触摸设备等
 *
 *    输入设备通常会发出多种输入事件, 例如, 鼠标发出相对坐标事件、按键事件, 键盘发出按键事件,
 *    触摸屏发出绝对坐标事件. 而输入子系统并不关心事件由哪个具体的设备发出, 它仅负责投递事件.
 *
 *    输入子系统在使用上遵循"谁关心谁订阅"的原则, 用户注册回调函数进系统, 在回调函数中, 将数
 *    据强制转换为所关心的数据类型即可.
 *
 * \par 使用说明
 * \code
 *
 * (1) 使用上报事件标准接口前, 请先确认已配置输入子系统(aw_prj_params.h)
 *
 * ......
 *
 * #define AW_COM_AWBL_INPUT_EV             // Input Service事件管理
 * #define AW_COM_AWBL_INPUT_EV_KEY         // Input Service按键事件
 * #define AW_COM_AWBL_INPUT_EV_ABS         // Input Service绝对事件
 *
 * ......
 *
 * (2) 初始化事件库, 以及向Apollo平台注册输入子系统(aw_prj_config.c)
 * static void aw_prj_task_level_init( void )
 * {
 * ......
 *
 *   aw_event_lib_init();           // event lib initialization
 *
 * #ifdef AW_COM_AWBL_INPUT_EV
 *   awbl_input_ev_mgr_register();
 * #endif
 *
 * ......
 * }
 *
 * (3) 在任意处使用输入子系统标准接口前，请先包含aw_input.h头文件
 *
 * \endcode
 *
 * \par 简单示例
 * \code
 *
 * #include "aw_input.h"
 *
 * (1) 可在任意处调用上报接口, 上报数据
 *
 * aw_input_report_key(EV_KEY, KEY_1, 1);
 *
 * (2) 使用回调接收上报数据
 *
 * void key_proc0_cb (void *p_input_data, void *p_usr_data)
 * {
 *     struct aw_input_event *p_input_ev = (struct aw_input_event *)p_input_data;
 *
 *	   if (p_input_ev->ev_type != EV_KEY) {
 *
 *	       return;
 *	   }
 *
 *	   struct aw_input_key_data *key_data = (struct aw_input_key_data *)p_input_data;
 *
 *	   switch (key_data->key_code) {
 *
 *	   case KEY_1 : if (key_data->key_state) {
 *
 *	                    AW_INFOF(("key_proc0_cb : KEY1 is down : %d. \n", key_data->key_state));
 *                  }
 *                  else {
 *
 *               	    AW_INFOF(("key_proc0_cb : KEY1 is up : %d. \n", key_data->key_state));
 *                  }
 *  	            break;
 *     }
 * }
 *
 * void my_func (void *p_arg)
 * {
 *     aw_local struct aw_input_handler input_hdlr;
 *
 *	   aw_input_handler_register(&input_hdlr, key_proc0_cb, NULL);
 * }
 *
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.01 15-01-07  ops, encapsulate aw_input_handler and redefine how to register/unregister.
 * - 1.00 14-07-18  ops, first implementation.
 * \endinternal
 */

#ifndef __AW_INPUT_H
#define __AW_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_input
 * \copydoc aw_input.h
 * @{
 */

#include "aw_input_code.h"
#include "aw_types.h"
#include "aw_event.h"

struct aw_input_pos {

	int x, y, z;
};

struct aw_input_event {

	int ev_type;                        /* 事件类型码 */
};

/** \brief 按键数据 */
struct aw_input_key_data {

	struct aw_input_event input_ev;     /* 事件类型 */
	int                   key_code;     /* 按键类型码 */
	int                   key_state;    /* 按键状态, DOWN : 0, UP : 非0*/
};

/** \brief 指针输入设备数据 */
struct aw_input_ptr_data {

	struct aw_input_event input_ev;     /* 事件类型 */
	int                   ptr_code;     /* 指针输入设备类型码 */
	struct aw_input_pos   pos;          /* 坐标值 */
};

union aw_input_data {

	struct aw_input_key_data key_data;
	struct aw_input_ptr_data ptr_data;

};

/**
 * \brief 输入子系统数据接收回调函数类型.
 *
 * \param p_input_data   输入数据.
 * \param p_usr_data     用户数据.
 */
typedef void input_cb_func_t (void *p_input_data, void *p_usr_data);

/**
 * \brief 输入子系统句柄.
 */
struct aw_input_handler {

	struct event_handler ev_handler;
	input_cb_func_t      *p_cb_func;
	void                 *p_usr_data;
};

/***********************************************************************************
 *
 *    输入子系统     -  数据上报接口
 *
 ***********************************************************************************/

/**
 * \brief 上报一个按键事件到输入子系统
 *
 * \param ev_type     事件类型码
 * \param code        类型码
 * \param is_pressed  按键状态
 *
 * \return  AW_OK   上报成功
 *        -ENODEV   未注册该事件
 */
int aw_input_report_key (int ev_type, int code, int is_pressed);

/**
 * \brief 上报一个坐标事件到输入子系统
 *
 * \param ev_type     事件类型码
 * \param code        类型码  (ABS_COORD : 绝对坐标, REL_COORD : 相对坐标)
 * \param coord_x     X坐标
 * \param coord_y     Y坐标
 * \param coord_z     Z坐标
 *
 * \return  AW_OK   上报成功
 *        -ENODEV   未注册该事件
 */
int aw_input_report_coord (int ev_type, int code, int coord_x, int coord_y, int coord_z);


/***********************************************************************************
 *
 *     输入子系统     -  注册/注销接口
 *
 ***********************************************************************************/

/**
 * \brief 注册一个输入句柄到输入子系统
 *
 * \param p_input_handler    待注册的输入子系统句柄.
 * \param p_cb_func          数据接收回调函数.
 * \param p_usr_data         用户自定义数据, 如无, 则为NULL.
 *
 * \return  AW_OK      成功注册.
 *          -EINVAL    当p_input_handler或p_cb_func为NULL时, 注册失败.
 */
aw_err_t aw_input_handler_register (struct aw_input_handler  *p_input_handler,
		                            input_cb_func_t          *p_cb_func,
		                            void                     *p_usr_data);

/**
 * \brief 从输入子系统中注销指定的输入句柄
 *
 * \param p_input_handler    待注销的输入子系统句柄.
 *
 * \return  AW_OK      成功注销.
 *          -EINVAL    当p_input_handler为NULL时, 注销失败.
 */
aw_err_t aw_input_handler_unregister (struct aw_input_handler *p_input_handler);


/** @} grp_aw_if_input */

#ifdef __cplusplus
}
#endif

#endif /* __AW_INPUT_H */

/* end of file */
