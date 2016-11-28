/*******************************************************************************
*                                 AWORKS
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
 * \file
 * \brief modbus从机协议栈用户接口头文件
 *
 * \internal
 * \par modification history
 * - 1.03 2016-04-27  cod, support muti-instance.
 * - 1.02 2015-05-22  cod, fix code style and comments, a little improve.
 * - 1.01 2013-03-29  liuweiyun, fix code style and comments, a little improve.
 * - 1.00 2012-05-03  ygy, first implementation
 * \endinternal
 */

#ifndef __AW_MB_SLAVE_H /* { */
#define __AW_MB_SLAVE_H

/**
 * \addtogroup grp_aw_if_mbslave_if
 * \copydoc mbslave.h
 * @{
 */

#include "modbus/aw_mb_config.h"
#include "modbus/aw_mb_err.h"
#include "modbus/aw_mb_comm.h"
#include "modbus/aw_mb_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 功能码回调函数类型 */
enum aw_mb_func_cb_type {
	AW_MB_FUNC_COILS_CALLBACK,                /**< \brief 读写线圈操作回调 */
	AW_MB_FUNC_DISCRETEINPUTS_CALLBACK,       /**< \brief 读离散量操作回调 */
	AW_MB_FUNC_HOLDREGISTERS_CALLBACK,        /**< \brief 读写保存寄存器回调 */
	AW_MB_FUNC_INPUTREGISTERS_CALLBACK,       /**< \brief 读输入寄存器回调 */
};

/** 功能码回调函数操作类型 */
enum aw_mb_func_cb_op {
	AW_MB_FUNC_CALLBACK_READ,   /**< \brief 读操作 */
	AW_MB_FUNC_CALLBACK_WRITE,  /**< \brief 写操作 */
};

/** Modbus从栈句柄定义 */
typedef void *aw_mb_slave_t;

/******************************************************************************/

/**
 * \file
 *
 * callback function
 *
 * Read the ON/OFF status of discrete outputs(DO)in the slave. The coils status
 * is packed as per bit of data field. Status is indicated as: 1=ON, 0=OFF.
 * The LSB of the first data byte contains the coil addressed in the query.
 * If the coil quantity is not a multiple of eight, the remaining bits in the
 * final data byte will be padded with zeros.
 *
 * For example. addr = 0x0013  num = 10,
 * status of coils 20 ~ 27 is ON-ON-OFF-OFF-ON-OFF-ON-OFF 28~29 ON-ON,
 * so the buf[0] = 01010011(0x53)  buf[1] = 00000011
 *
 * buf[0]:
 * 7  |6  |5  |4  |3  |2  |1  |0
 * ---|---|---|---|---|---|---|---
 * 27 |26 |25 |24 |23 |22 |21 |20
 * OFF|ON |OFF|ON |OFF|OFF|ON |ON
 * 0  |1  |0  |1  |0  |0  |1  |1
 *
 * buf[1]:
 * 7  |6  |5  |4  |3  |2  |1  |0
 * ---|---|---|---|---|---|---|----
 * -  |-  |-  |-  |-  |-  |29 |28
 * 0  |0  |0  |0  |0  |0  |ON |ON
 * 0  |0  |0  |0  |0  |0  |1  |1
 */

/**
 * \brief 读写线圈，读离散量，读写保存寄存器，读输入寄存器回调函数原型
 * @note  当使用本库提供的读写线圈，读离散量，读写保存寄存器，
 * 		     读输入寄存器等功能码处理函数时，需要注册
 * @code
 * aw_mb_exception_t my_coils_callback(aw_mb_slave_t slave,
 *                                     uint8_t   *buf,
 *                                     uint16_t   addr,
 *                                     uint16_t   num)
 * {
 *     //读线圈操作
 * }
 *
 * //在启动slave之前进行如下操作：
 * aw_mb_slave_register_callback(slave,
 *                            	 AW_MB_FUNC_COILS_CALLBACK,
 *                            	 AW_MB_FUNC_CALLBACK_READ,
 *                            	 my_coils_callback);
 * @endcode
 *
 * @param[in] slave 从机句柄
 * @param[in,out] buf  读写操作缓冲区
 * @param[in] addr 读写操作开始地址
 * @param[in] num  读写操作个数
 * @return 如果没有异常，返回AW_MB_EXP_NONE，否则返回对应的异常号
 * @see aw_mb_slave_register_callback
 */
typedef aw_mb_exception_t (*aw_mb_slave_fn_code_callback_t)(
	aw_mb_slave_t slave,
	uint8_t      *p_buf,
    uint16_t   	  addr,
    uint16_t      num);

/**
 * \brief 注册读写线圈，读离散量，读写保存寄存器，读输入寄存器回调函数.
 * @note  当使用本库提供的读写线圈，读离散量，读写保存寄存器，读输入寄存器功能码
 * 		     处理函数时, 必须使用该函数进行回调函数注册，否则主机会获得非法功能码异常
 *
 * @param[in] slave 从机句柄
 * @param[in] type 功能码回调函数类型
 * @param[in] op 功能码回调函数操作类型
 * @param[in] callback 回调函数
 * @return 如果没有错误返回MB_ERR_NOERR,否则返回对应的错误号
 */
aw_mb_err_t aw_mb_slave_register_callback (
	aw_mb_slave_t                  slave,
	enum aw_mb_func_cb_type        type,
	enum aw_mb_func_cb_op          op,
	aw_mb_slave_fn_code_callback_t callback);

/**
 * \brief 功能码处理函数原型.
 * @note  当从机收到一帧数据以后，将根据功能码调用对应的处理函数。
 * 		     处理函数由用户通过\a aw_mb_slave_register_handler 来注册。
 *		     同时已经定义基本的读写线圈，读离散量，读写保存寄存器，读输入寄存器
 * 		     等处理函数，具体参考\a mbslavefun.h
 *
 * @param[in] slave Modbus从栈句柄
 * @param[in,out] p_pdubuf PDU数据(包含功能码)
 *         - [in]  请求PDU数据
 *         - [out] 应答PDU数据
 * @param[in,out] p_pdulen PDU数据长度
 *         - [in]  请求PDU数据长度
 *         - [out] 应答PDU数据长度
 * @return 如果没有异常，返回AW_MB_EXP_NONE，否则返回对应的异常号
 */
typedef aw_mb_exception_t (*aw_mb_fn_code_handler_t) (aw_mb_slave_t slave,
                                                  	  uint8_t      *p_pdubuf,
                                                  	  uint16_t     *p_pdulen);

/******************************************************************************/

/**
 * \brief 创建并初始化一个Modbus从站
 * @note  在调用所有从机函数之前，必须先调用该函数
 * @note  允许不同网络创建多个从站
 *
 * @param[in] mode    : 通信模式
 * @param[in] p_param : 初始化参数，对于MB_RTU/MB_ASCII模式使用
 *                      struct aw_mb_serial_param作为参数
 *                      对于AW_MB_TCP模式，param作为端口号参数使用,直接传入形参
 * @param[out] p_err  : 错误号. 如果对错误号不感兴趣可以传递AW_MB_NULL参数。
 *                      如果没有错误，其值为AW_MB_ERR_NOERR
 * @return Modbus从栈句柄，如果发生错误返回NULL
 */
aw_mb_slave_t aw_mb_slave_init (enum aw_mb_mode mode,
							    void     	   *p_param,
								aw_mb_err_t    *p_err);

/**
 * \brief 关闭Modbus从站.
 * @note  退出系统或者不需要再使用从机时调用
 *
 * @param[in] slave : Modbus从栈句柄
 * @return 如果没有错误返回AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_close (aw_mb_slave_t slave);

/**
 * \brief 启动Modbus从栈.
 * @note  该函数必须在调用aw_mb_slave_init函数后或者调用aw_mb_slave_stop函数后被调用
 *
 * @param[in] slave : Modbus从栈句柄
 * @return 如果没有错误返回AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_start (aw_mb_slave_t slave);

/**
 * \brief 停止Modbus从栈.
 *
 * @param[in] slave : Modbus从栈句柄
 * @return 如果没有错误返回AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_stop (aw_mb_slave_t slave);

/**
 * \brief 注册功能码处理函数.
 * @note  初始化Modbus从站以后，可以调用该函数来注册对应的功能码处理函数。用来扩展功能码
 *
 * @note 可以注册的功能码处理函数个数在aw_mb_config.h中AW_MB_FUNC_CODE_HANDLER_MAX定义。
 *       超过该个数将无法再注册。同一个功能码只能有一个处理函数，如果注册两次同
 *       一个功能码处理函数，将只使用最后注册的处理函数。
 * @param[in] slave    : Modbus从栈句柄
 * @param[in] funcode  : 功能码号
 * @param[in] handler  : 功能码处理函数
 * @return 如果没有错误返回AW_MB_ERR_NOERR;
 *  如果参数错误返回AW_MB_ERR_EINVAL;
 *  如果无法再注册功能码返回AW_MB_ERR_ENORES.
 */
aw_mb_err_t aw_mb_slave_register_handler (aw_mb_slave_t            slave,
                                    	  uint8_t                  funcode,
                                    	  aw_mb_fn_code_handler_t  handler);

/**
 * \brief Modbus从栈查询操作.
 * @note  接收数据帧并处理该数据帧，其为Modbus从栈协议的核心。该函数必须被周期性的调用。
 *        其时间间隔依赖具体应用和主栈要求的时间间隔。
 *
 * @param[in] slave : Modbus从站句柄
 * @return 如果没有错误返回AW_MB_ERR_NOERR，反之返回相应的错误类型.
 */
aw_mb_err_t aw_mb_slave_poll (aw_mb_slave_t slave);

/**
 * \brief 设置Modbus从栈信息.
 * 用来设置Modbus从栈类型说明，当前状态和其他一些特殊信息。
 * @note 本实现定义了Modbus从栈信息最大长度为32个字节，其中：
 *    - 栈类型说明占一个字节
 *    - 当前状态占一个字节
 *    - 其他信息长度<= 30个信息\n
 *  在使用是要特别注意.
 *
 * @param[in] slave        : Modbus从栈句柄
 * @param[in] slave_id     : 类型说明
 * @param[in] is_running   : 当前状态
 * @param[in] p_additional : 其他一些特殊信息
 * @param[in] alen         : 其他一些特殊信息长度
 *
 * @return 如果没有错误返回AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_set_id (aw_mb_slave_t     slave,
                                uint8_t           slave_id,
                                uint8_t           is_running,
                                const uint8_t    *p_additional,
                                uint16_t          alen);

/**
 * \brief 设置Modbus从栈地址.
 * @note  默认情况下在调用aw_mb_slave_init进行初始化时，初始化参数里面已经有设置从栈地址；
 * 		     当如果有需要在运行时修改从栈地址，可以使用该函数。
 *
 * @param[in] slave : Modbus从栈句柄
 * @param[in] addr  : 新的Modbus从栈地址
 * @return 如果没有错误返回AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_set_addr (aw_mb_slave_t slave, uint8_t addr);

#ifdef __cplusplus
}
#endif

/** @} grp_aw_if_mbslave_if */

#endif /* } __AW_MB_SLAVE_H */

/* end of file */
