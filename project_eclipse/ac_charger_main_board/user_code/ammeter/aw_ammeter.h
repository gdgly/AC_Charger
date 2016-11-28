/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief  电表声明头文件
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-12  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"
#include "modbus/aw_mb_master.h"
#include "aw_task.h"                    /* 多任务服务 */

#ifndef __AW_AMMETER_H
#define __AW_AMMETER_H

/** \brief  07年DL645协议 */
#define AW_AMMETER_TRANSFER_PROTOCOL_DL645_07     0
/** \brief 97年DL645协议，暂未支持 */
#define AW_AMMETER_TRANSFER_PROTOCOL_DL645_97     1
/** \brief  modbus-rtu协议 */
#define AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU   2 

/** \brief 电表类型为直流电表 */
#define AW_AMMETER_TYPE_DC    0

/** \brief 电表类型为交电表 */
#define AW_AMMETER_TYPE_AC    1

#define AW_AMMETER_PHASE_A    0    /**< \brief A相 */
#define AW_AMMETER_PHASE_B    1    /**< \brief A相 */
#define AW_AMMETER_PHASE_C    2    /**< \brief A相 */

/** 
 *  \brief 电表
 */
typedef struct aw_ammeter {
    uint32_t energy;                     /**< \brief 当前电量 */
    uint32_t type;                      /**< \brief 电表标识 */
    
    /** 
     * \brief 获取当前正向有功电能，单位0.01 KWh
     * \param[in]  handle   : 指向电表的实例
     * \param[out] p_energy : 指向存放电量的变量
     *  
     * \return AW_OK    : 获取成功
     * \return AW_ERROR : 获取失败
     */
    aw_err_t (*pfn_active_energy_get)(struct aw_ammeter* handle,
                                      uint32_t          *p_energy);
}aw_ammeter_t;

/** 
 *  \brief 电表通信传输结构
 */
typedef struct aw_ammeter_transfer {
    uint8_t  *p_addr;                /**< \brief 通信地址 */
    uint8_t   addr_len;              /**< \brief 通信地址长度 */
    uint8_t   protocol;              /**< \brief 通信协议 */

    /** 
     * \brief 发送数据
     * \param [in] handle  : 电表通信传输的实例
     * \param [in] p_txbuf : 发送数据缓冲区
     * \param [in] nbytes  : 发送字节数
     * \return 错误码： 返回AW_OK时，表示通信成功。
     */
    aw_err_t (*pfn_send)(struct aw_ammeter_transfer* handle,
                         const uint8_t              *p_txbuf,
                         uint32_t                    nbytes);
    /** 
     * \brief 接收数据
     * \param [in] handle  : 电表通信传输的实例
     * \param [in] p_rxbuf : 接收数据缓冲区
     * \param [in] nbytes  : 接收字节数
     * \return 错误码： 返回AW_OK时，表示通信成功。
     */
    int (*pfn_receive)(struct aw_ammeter_transfer* handle,
                       uint8_t                    *p_rxbuf,
                       uint32_t                    nbytes);
}aw_ammeter_transfer_t;

/** 
 *  \brief 电表DL645协议通信传输结构
 */
typedef struct aw_ammeter_transfer_dl645 {
    aw_ammeter_transfer_t super;       /**< \brief 继承的父类 */
    uint32_t              uart_num;    /**< \brief 通信时使用的串口号 */
    uint32_t              uart_buad;   /**< \brief 通信速率 */
    uint32_t              uart_format; /**< \brief 串口通信格式 */
    bool_t                rs485_en;    /**< \brief RS485使能 */
}aw_ammeter_transfer_dl645_t;      

/**
 *  \brief 电表modbus-rtu协议通信传输结构
 */
typedef struct aw_ammeter_transfer_mb {
    aw_ammeter_transfer_t         super;          /**< \brief 继承的父类 */
    aw_mb_master_serial_params_t *p_ser_params;   /**< \brief 串口初始化参数 */
    aw_mb_master_t                master;         /**< \brief 主站 */
    aw_task_id_t                  tid;            /**< \brief 主站数据接收轮询任务id */
}aw_ammeter_transfer_mb_t;


/**
  * \brief 直流电表
  */
typedef struct aw_ammeter_dc {
    aw_ammeter_t super;                 /**< \brief 继承的父类 */
    aw_ammeter_transfer_t *p_transfer;  /**< \brief 关联的通信类 */
}aw_ammeter_dc_t;


/**
 * \brief 直流电表实例初始化
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_dc_inst_init (aw_ammeter_t* handle);

/**
 * \brief 直流电表实例去初始化
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_dc_inst_deinit (aw_ammeter_t* handle);

/**
 * \brief 获取当前电量，单位0.01 KWh
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_energy : 指向存放电量的变量
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_active_energy_get(struct aw_ammeter* handle,
                                      uint32_t          *p_energy);

/**
 * \brief 获取A相电流
 * \param[in]  handle  : 指向电表的实例
 * \param[out] p_curr  : 指向存放电流的变量
 *                        对于07年版本，单位为0.001A
 *                        对于97年版本，单位为0.01A
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_err_t aw_ammeter_current_get(struct aw_ammeter* handle,
                                uint8_t            phase,
                                uint32_t          *p_curr);

/**
 * \brief 获取电压，单位0.1V
 * \param[in]  handle  : 指向电表的实例
 * \param[out] p_vol   : 指向存放电量的变量
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_voltage_get(struct aw_ammeter* handle,
                                uint8_t            phase,
                                int32_t           *p_vol);

/**
 * \brief 获取功率
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_power    : 指向存放压的变量，单位kW
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_err_t aw_ammeter_power_get(struct aw_ammeter* handle, uint32_t *p_power);
#endif
