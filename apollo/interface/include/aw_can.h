
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
 * \brief Apollo CAN 接口头文件
 *
 * \internal
 * \par modification history:
 * - 1.01 15-12-02  cae, first implementation
 * \endinternal
 */

#ifndef __AW_CAN_H
#define __AW_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_types.h"

/** \brief can controller type */
#define AW_CAN_CTLR_HS                  0x00    /**< \brief 高速CAN */
#define AW_CAN_CTLR_FD                  0x01    /**< \brief CANFD */

/** \brief can work mode */
#define AW_CAN_WORK_MODE_NORMAL         0x00    /**< \brief 正常工作模式 */
#define AW_CAN_WORK_MODE_LISTEN_ONLY    0x01    /**< \brief 只听工作模式 */

/** \brief can bus error type */
#define AW_CAN_BUS_ERR_NONE             0x00    /**< \brief 无错误 */
#define AW_CAN_BUS_ERR_BIT              0x01    /**< \brief 位错误 */
#define AW_CAN_BUS_ERR_ACK              0x02    /**< \brief 应答错误 */
#define AW_CAN_BUS_ERR_CRC              0x04    /**< \brief CRC错误 */
#define AW_CAN_BUS_ERR_FORM             0x08    /**< \brief 格式错误 */
#define AW_CAN_BUS_ERR_STUFF            0x10    /**< \brief 填充错误 */
#define AW_CAN_BUS_ERR_DATAOVER         0x20    /**< \brief 超载错误 */
#define AW_CAN_BUS_ERR_RCVBUFF_FULL     0x40    /**< \brief 接收缓冲区满 */
#define AW_CAN_BUS_ERR_TXDBUFF_FULL     0x80    /**< \brief 发送缓冲区满 */
typedef uint32_t aw_can_bus_err_t;

/** \brief status code returned by */
#define AW_CAN_BUS_STATUS_OK            0x00    /**< \brief 总线正常 */
#define AW_CAN_BUS_STATUS_ERROR         0xE1    /**< \brief 总线错误 */
#define AW_CAN_BUS_STATUS_WARN          0xE2    /**< \brief 总线警告 */
#define AW_CAN_BUS_STATUS_PASSIVE       0xE3    /**< \brief 总线消极 */
#define AW_CAN_BUS_STATUS_OFF           0xE4    /**< \brief 总线关闭 */
#define AW_CAN_BUS_STATUS_DATAOVER      0xE5    /**< \brief 总线超载 */
#define AW_CAN_BUS_STATUS_WAKE          0xE6    /**< \brief 总线唤醒 */
typedef uint32_t aw_can_bus_status_t;

/** \brief Macro definitions to be used with filtering*/
#define AW_CAN_COMPARE_ALL_STD_IDS      0x7FF
#define AW_CAN_COMPARE_ALL_EXT_IDS      0x1FFFFFFF
#define AW_CAN_ACCEPT_ALL_IDS           0

/** \brief STATUS error codes returned by CAN interface functions */
#define AW_CAN_ERR_NONE                         0
#define AW_CAN_ERR_BASE                         0
#define AW_CAN_ERR_BUSY                        (AW_CAN_ERR_BASE + 80)
#define AW_CAN_ERR_NOT_INITIALIZED             (AW_CAN_ERR_BASE + 81)
#define AW_CAN_ERR_NONE_DRIVER_FUNC            (AW_CAN_ERR_BASE + 82)
#define AW_CAN_ERR_ILLEGAL_CHANNEL_NO          (AW_CAN_ERR_BASE + 83)
#define AW_CAN_ERR_ILLEGAL_CHANNEL_MODE        (AW_CAN_ERR_BASE + 84)
#define AW_CAN_ERR_ILLEGAL_CTRL_TYPE           (AW_CAN_ERR_BASE + 85)
#define AW_CAN_ERR_INCOMPATIBLE_CTRL_TYPE      (AW_CAN_ERR_BASE + 86)
#define AW_CAN_ERR_CTRL_NOT_START              (AW_CAN_ERR_BASE + 87)
#define AW_CAN_ERR_NO_OP                       (AW_CAN_ERR_BASE + 88)
#define AW_CAN_ERR_ILLEGAL_DATA_LENGTH         (AW_CAN_ERR_BASE + 89)
#define AW_CAN_ERR_ILLEGAL_MASK_VALUE          (AW_CAN_ERR_BASE + 90)
#define AW_CAN_ERR_INVALID_PARAMETER           (AW_CAN_ERR_BASE + 91)
#define AW_CAN_ERR_ILLEGAL_OFFSET              (AW_CAN_ERR_BASE + 92)
#define AW_CAN_ERR_SLEEP_IN_RESET_MODE         (AW_CAN_ERR_BASE + 93)
#define AW_CAN_ERR_CANNOT_SET_WAKEUPINT        (AW_CAN_ERR_BASE + 94)
#define AW_CAN_ERR_CANNOT_SET_BOFFINT          (AW_CAN_ERR_BASE + 95)
#define AW_CAN_ERR_CANNOT_SET_ERRINT           (AW_CAN_ERR_BASE + 96)
#define AW_CAN_ERR_BAUDRATE_ERROR              (AW_CAN_ERR_BASE + 97)
#define AW_CAN_ERR_ABORT_TRANSMITTED           (AW_CAN_ERR_BASE + 98)
#define AW_CAN_ERR_TRANSMITTED_TIMEOUT         (AW_CAN_ERR_BASE + 99)
#define AW_CAN_ERR_BUS_FAULT                   (AW_CAN_ERR_BASE + 100)
#define AW_CAN_ERR_RXD_BUFF_UNUSED             (AW_CAN_ERR_BASE + 101)
#define AW_CAN_ERR_NONE_RCV_FUNC               (AW_CAN_ERR_BASE + 102)



#define AW_CAN_ERR_UNKNOWN_ERROR               (AW_CAN_ERR_BASE + 255)

typedef int32_t aw_can_err_t;

/** \brief message  timeout*/
#define AW_CAN_WAIT_FOREVER                  AW_WAIT_FOREVER
#define AW_CAN_NO_WAIT                       AW_NO_WAIT

/** \brief message send type*/
#define AW_CAN_MSG_SEND_NORMAL               0   /**< \brief 正常发送*/
#define AW_CAN_MSG_SEND_ONCE                 1   /**< \brief 单次发送*/
#define AW_CAN_MSG_SEND_SELF                 2   /**< \brief 自发自收*/
#define AW_CAN_MSG_SEND_SELFONCE             3   /**< \brief 单次自发自收*/

/** \brief error information save or not*/
#define AW_CAN_ERR_INFO_UNREC                0   /**< \brief 不记录CAN错误信息*/
#define AW_CAN_ERR_INFO_REC                  1   /**< \brief 记录CAN错误信息 */

/** \brief error information save or not*/
#define AW_CAN_RXD_BUFF_UNUSED               0   /**< \brief 不使用RXD_BUFF*/
#define AW_CAN_RXD_BUFF_USED                 1   /**< \brief 使用RXD_BUFF */

/** \brief message flag bit define*/
#define AW_CAN_MSG_FLAG_REMOTE              0x0020
#define AW_CAN_MSG_FLAG_EXTERND             0x0040
#define AW_CAN_MSG_FLAG_ERROR               0x0080
#define AW_CAN_MSG_FLAG_FD_CTRL             0x0100
#define AW_CAN_MSG_FLAG_CTLR_CHCK           0x0300


/*******************************************************************************
                       CAN波特率、报文、传输块结构体
*******************************************************************************/
/** \brief define CAN message type */
typedef struct aw_can_msg {
    uint32_t      timestamp; /**< \brief timestamp  时间戳 */
    uint32_t      id; /**< \brief id 帧ID */

    /** \brief flags 报文信息的标志
     * -----------------------------------------------------------
     * | 15:10                             | 9:8 controller type |
     * -----------------------------------------------------------
     * -----------------------------------------------------------
     * | 7:iserrmsg |6:SEF | 5:SDF | 4:reseverd | 0:3 sendtype |
     * -----------------------------------------------------------
     * bit7:iserrmsg 是否为错误信息 (1:err错误信息 0:normal正常报文)
     * bit6:SEF 帧格式 (1:extended扩展帧 0:std 标准帧)
     * bit5:SDF 帧类型 (1:remote远程帧   0:data数据帧)
     * bit4:reseverd 保留
     * bit0~3:发送类型  (sendtype:见宏定义)
     */
    uint16_t      flags; /**< \brief msginfo 报文信息 */
    uint8_t       chn; /**< \brief chn 报文所在通道号 */
    uint8_t       length; /**< \brief msglen 报文长度 */
}aw_can_msg_t;

/** \brief define CAN stander message type */
typedef struct aw_can_std_msg {
    aw_can_msg_t      can_msg;
    uint8_t           msgbuff[8];
}aw_can_std_msg_t;

/** \brief define CAN fd message type */
typedef struct aw_can_fd_msg {
    aw_can_msg_t      can_msg;
    uint8_t           msgbuff[64];
}aw_can_fd_msg_t;

/** \brief CAN传输块 */
typedef struct aw_can_transfer {
    aw_can_msg_t     *p_msgs;         /**< \brief 传输块的CAN报文缓冲器首地址*/
    uint16_t          msgs_num;       /**< \brief 请求传输报文个数 */
    uint16_t          done_num;       /**< \brief 成功处理的传输报文个数 */
    aw_pfuncvoid_t    pfunc_complete; /**< \brief 传输完成回调函数,异步传输有效*/
    void             *p_arg;          /**< \brief 传递给 pfunc_complete 的参数 */
    int               status;         /**< \brief 当前传输块的状态如下: */
                                      /**< \brief -ENOTCONN:未排队*/
                                      /**< \brief -EISCONN:排队*/
                                      /**< \brief -EINPROGRESS:处理*/
                                      /**< \brief -ETIME:超时*/
                                      /**< \brief -ENETDOWN:总线关闭，设备停止*/
                                      /**< \brief AW_OK:完成*/
    void             *ctlrdata[2];    /**< \brief 控制器使用 */
} aw_can_transfer_t;

/** \brief can baud rate parameters
* ----------------------------------------------------------
* | sync |        tseg1      |   tseg2                     |
* |                     sample point                       |
* ----------------------------------------------------------
* f(tq)= fpclk(can外设时钟) /brp（分频值），通常CAN控制器默认分频值+1
*
* baudrate = ftq / (sync + tseg1 + tseg2),
*
* sync: 同步段：默认为1
*
* tseg1:相位缓冲段1: tseg1（控制器默认+1），Tseg1请详细参考CAN控制器解释
*
* tseg2:相位缓冲段2: tseg2（控制器默认+1），tseg2 >= sjw
*
* smp: 采样次数: 控制器采样总线次数，通常设置为单次采样
*
*/
typedef struct aw_can_baud_param {
    uint8_t     tseg1;          /**< \brief tseg1 相位段1 */
    uint8_t     tseg2;          /**< \brief tseg2 相位段2 */
    uint8_t     sjw;            /**< \brief sjw 同步跳转宽度 */
    uint16_t    brp;            /**< \brief brp 分频值 */
    uint8_t     smp;            /**< \brief smp 采样模式0:单次 1:三次 */
}aw_can_baud_param_t;

/** \brief 错误计数器*/
typedef struct aw_can_err_cnt{
    uint8_t rx_err_cnt;         /**< \brief rx_error_cnt  接收错误计数器 */
    uint8_t tx_err_cnt;         /**< \brief tx_error_cnt  发送错误计数器 */
}aw_can_err_cnt_t;

/*******************************************************************************
                                                      用户APP函数回调函数信息结构体
*******************************************************************************/
typedef uint32_t (*aw_can_timestamp_get_callback_t)(void);
typedef uint32_t (*aw_can_proto_rx_callback_t)     (int chn, aw_can_msg_t* p_msg);
typedef uint32_t (*aw_can_proto_tx_callback_t)     (int chn);
typedef uint32_t (*aw_can_bus_err_sta_callback_t)  (int chn,
                                                    aw_can_bus_err_t    err,
                                                    aw_can_bus_status_t sta);

typedef uint32_t (*aw_can_dev_wakeup_callback_t)   (int chn);

typedef struct aw_can_app_callbacks {
    /**< \brief  获取系统时间戳   回调函数地址  */
    aw_can_timestamp_get_callback_t  timestamp_get_cb;

    /**< \brief  总线接收一帧 报文      回调函数地址
     *   函数返回值决定接收到的报文是否存入rngbuf，
     *   TRUE:不保存，FALSE:保存
     */
    aw_can_proto_rx_callback_t       proto_rx_cb;

    /**< \brief  总线发送完成        回调函数地址  */
    aw_can_proto_tx_callback_t       proto_tx_cb;

    /**< \brief  应用层错误及总线状态处理   回调函数地址
     * 函数返回值决定错误消息是否存入rngbuf，
     * TRUE:不保存，FALSE:保存
     */
    aw_can_bus_err_sta_callback_t    bus_err_sta_cb;

    /**< \brief  总线唤醒               回调函数地址  */
    aw_can_dev_wakeup_callback_t     dev_wakeup_cb;

}aw_can_app_callbacks_t;

/*******************************************************************************
                           CAN 接口函数
*******************************************************************************/
/**
 * \brief CAN初始化函数，初始化通道，模式，波特率，回调函数等操作
 *
 * \param[in] chn:       选择通道，chn: 0~AW_CFG_NUM_CAN。
 *
 * \param[in] work_mode: 设置 工作模式，
 *                       AW_WORK_MODE_NROMAL(正常模式)、
 *                       AW_WORK_MODE_LISTEN_ONLY（只听模式）。
 *
 * \param[in] p_baud:    配置波特率，波特率参数参考结构体说明。
 *
 * \param[in] p_app_cb:  用户回调，发生相应的事件，回调用户APP，可设置为NULL。
 *
 * \retval aw_can_err_t: 见函数返回错误码。
 *
 * \code
 */
aw_can_err_t aw_can_init (int                     chn,
                          uint8_t                 work_mode,
                          aw_can_baud_param_t    *p_baud,
                          aw_can_app_callbacks_t *p_app_cb);

/**
 * \brief  start can
 *  启动CAN，使CAN控制器进入正常模式，可以进行通信。
 *
 * \param[in] chn:          通道号。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_start (int chn);

/**
 * \brief stop/reset can device
 * 复位CAN控制器，使CAN控制器进入复位模式，CAN控制器不进行总线通信。
 *
 * \param[in] chn:          通道号。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_reset (int chn);

/**
 * \brief put into sleep mode
 * 将CAN控制器进入睡眠模式
 *
 * \param[in] chn:          通道号。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_sleep (int chn);

/**
 * \brief force the CAN controller out of sleep mode
 *  唤醒CAN控制器
 *
 * \param[in] chn:          通道号。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_wakeup (int chn);

/**
 * \brief set the bit timing parameters of the controller
 * 设置CAN波特率
 *
 * \param[in] chn:          通道号。
 *
 * \param[in] p_baud:       波特率参数。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_baudrate_set (int chn, aw_can_baud_param_t *p_baud);

/**
 * \brief set the bit timing parameters of the controller
 * 获取CAN波特率
 *
 * \param[in] chn:          通道号。
 *
 * \param[in] p_baud:       波特率参数。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_baudrate_get (int chn, aw_can_baud_param_t *p_baud);

/**
 * \brief clear send and receive error count of the controller
 *  清除发送和接受错误计数
 *
 * \param[in] chn:          通道号。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_err_cnt_clr (int chn);

/**
 * \brief get send and receive error count
 * 获取发送和接收错误计数器
 *
 * \param[in] chn:          通道号。
 *
 * \param[in] p_can_err_reg:错误寄存器值指针。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_err_cnt_get (int chn, aw_can_err_cnt_t *p_err_cnt);


/** \brief 验收滤波相关函数 */
/**
 * \brief aw_can_set_filter_table
 * *
 *  设置CAN滤波表。此接口函数为通用格式，即，只有表首地址和表长度（字节个数）。
 *  不同的控制器滤波表不同，格式也不同，因此 滤波表格式由用户自己定义。
 *
 * \param[in] chn:          通道号。
 *
 * \param[in] p_filter_buff:滤波表首地址。
 *
 * \param[in] length:       滤波表长度（字节个数）。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_filter_table_set (int      chn,
                                      uint8_t *p_filter_buff,
                                      size_t   length);
/**
 * \brief aw_can_get_filter_table
 * *
 *  获取CAN滤波表。此接口函数为通用格式，即，只有表首地址和表长度（字节个数）。
 *  不同的控制器滤波表不同，格式也不同，因此 滤波表格式由用户自己定义。
 *
 * \param[in] chn:          通道号。
 *
 * \param[in] p_filter_buff:滤波表首地址。
 *
 * \param[in] p_length:     返回滤波表长度（字节个数）。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_filter_table_get (int       chn,
                                      uint8_t  *p_filter_buff,
                                      size_t   *p_length);

/**
 * \brief 设置CAN传输结构体参数
 *
 * \param p_transfer        CAN报文传输描述符指针
 * \param p_msgs            组成传输块的报文
 * \param trans_num         报文的个数
 * \param pfunc_complete    传输完成回调函数
 *                          (仅调用 aw_can_msgs_send_async() 时此参数有效,
 *                          调用 aw_can_msgs_send_sync()时本参数无效)
 * \param p_arg             传递给回调函数的参数
 *
 * \par 范例
 * \code
 * #include "aw_can.h"
 *
 * aw_can_transfer_t transfer;  // 传输块描述结构体
 * aw_can_std_msg_t  msgs[2];   // 组成传输块的报文缓冲区
 *
 * // 设置传输描述结构体
 * aw_i2c_mktrans(&transfer,    // 传输块描述结构
 *                msgs,         // 组成传输块的报文缓冲区首地址
 *                2，                             // 传输个数
 *                my_callback,  // 传输完成回调函数
 *                my_arg);      // 传输完成回调函数的参数
 *
 *  函数实现：
 *  p_transfer->p_msgs         = (aw_can_msg_t*)p_msgs;
 *  p_transfer->msgs_num       = msgs_num;
 *  p_transfer->done_num       = 0;
 *  p_transfer->pfunc_complete = pfunc_complete;
 *  p_transfer->p_arg          = p_arg;
 *  p_transfer->status         = -ENOTCONN;
 *
 *
 * \endcode
 */
 void aw_can_mkmsg (aw_can_transfer_t  *p_transfer,
                    aw_can_std_msg_t   *p_msgs,
                    uint16_t            msgs_num,
                    aw_pfuncvoid_t      pfunc_complete,
                    void               *p_arg);

/**
 * \brief aw_can_msgs_send_async
 * 产生一次CAN报文的异步传输，接口参数使用传输块，
 * 如果当前有传输块正在传输则把新传输块添加到发送列表，
 * 用户的传输块必须是有效传输块，未传输结束之前不能释放该传输块，否则发送失败。
 * 传输块如何制作请参考函数aw_can_mkmsg内容；
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] p_transfer:   传输块p_transfer的地址。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_msgs_send_async (int                chn,
                                     aw_can_transfer_t *p_transfer);

/**
 * \brief synchronous can transfer 同步传输
 * 产生一次同步传输，发送一批CAN报文，报文个数由用户给出
 * 用户的传输块必须是有效传输块，未传输结束之前不能释放该传输块，否则发送失败。
 *
 * \param[in] p_serv:       CAN服务地址。
 *
 * \param[in] p_transfer:   传输块地址。
 *
 * \param[in] timeout:      传输超时间。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_msgs_send_sync (int                chn,
                                    aw_can_transfer_t *p_transfer,
                                    uint32_t           timeout);

/**
 * \brief saw_can_fd_msgs_send
 * CANFD的报文发送函数，CANFD控制器时候使用，
 * 报文格式采用CANFD报文格式，请参考：aw_can_fd_msg_t
 * 用户的传输块必须是有效传输块，未传输结束之前不能释放改传输块，否则发送失败。
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] p_msgs:       FD报文缓冲区地址。
 *
 * \param[in] msgs_num:     缓冲区报文个数。
 *
 * \param[in] p_done_num:   实际发送成功个数地址。
 *
 * \param[in] timeout:      发送超时时间，须大于0。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_fd_msgs_send (int              chn,
                                  aw_can_fd_msg_t *p_msgs,
                                  uint32_t         msgs_num,
                                  uint32_t        *p_done_num,
                                  uint32_t         timeout);

/**
 * \brief saw_can_std_msgs_send
 * 标准的CAN报文发送函数，高速CAN控制器时候使用，
 * 报文格式采用标准CAN报文格式，请参考：aw_can_std_msg_t
 * 用户的传输块必须是有效传输块，未传输结束之前不能释放改传输块，否则发送失败。
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] p_msgs:       标准报文缓冲区地址。
 *
 * \param[in] msgs_num:     缓冲区报文个数。
 *
 * \param[in] p_done_num:   实际发送成功个数地址。
 *
 * \param[in] timeout:      发送超时时间，须大于0。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_std_msgs_send (int               chn,
                                   aw_can_std_msg_t *p_msgs,
                                   uint32_t          msgs_num,
                                   uint32_t         *p_done_num,
                                   uint32_t          timeout);

/**
 * \brief aw_can_msgs_stop_send
 * 停止发送函数，
 * 注意，用于异步传输停止发送，用户调用此接口aw_can_msgs_send_async，使用。
 * 使用同步传输，发生超时事件，系统会自动调用停止传输，用户无需调用。
 * 用户会停止当前报文发送，并清除传输块列表。
 * 用户接口函数；
 *
 * \param[in] chn:          CAN通道号。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_msgs_stop_send (int chn);


/** \brief 接收相关函数 */
/**
 * \brief aw_can_rcv_msgs_num
 * 获取接收缓冲区已经接收can报文的个数，
 *
 * \param[in] chn:      CAN通道号。
 *
 * \retval frame count: 缓冲区报文个数。
 *
 */
uint32_t aw_can_rcv_msgs_num (int chn);

/**
 * \brief aw_can_rcv_fifo_size
 * 缓冲区只大小。
 *
 * \param[in] chn:     CAN通道号。。
 *
 * \retval fifo size:  缓冲区实际大小（报文个数）。
 *
 */
uint32_t aw_can_rcv_fifo_size (int chn);

/**
 * \brief aw_can_msgs_rcv
 * 接收CAN报文，缓冲区只要有数据就会成功返回，
 * 实际个数值在aw_can_transfer_t的元素done_num中，
 * 只有缓冲区没有数据的时候，超时时间有效，
 * 为了保证接收数据实时性，在超时等待时候，当接收到有效数据，立刻返回。
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] p_transfer:   传输块地址。
 *
 * \param[in] timeout:      接收缓冲区中无报文的超时时间。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_msgs_rcv (int                chn,
                              aw_can_transfer_t *p_transfer,
                              uint32_t           timeout);

/**
 * \brief aw_can_std_msgs_rcv
 * 接收【标准CAN报文】，缓冲区只要有数据就会成功返回，
 * 实际个数值在存放在p_done_num中，
 * 只有缓冲区没有数据的时候，超时时间有效，
 * 为了保证接收数据实时性，在超时等待时候，当接收到有效数据，立刻返回。
 * 用户接口函数；
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] p_msgs:       接收报文缓冲区地址。
 *
 * \param[in] msgs_num:     缓冲区报文个数。
 *
 * \param[in] p_done_num:   实际读取个数地址。
 *
 * \param[in] timeout:      接收缓冲区中无报文的超时时间。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_std_msgs_rcv (int               chn,
                                  aw_can_std_msg_t *p_msgs,
                                  uint32_t          msgs_num,
                                  uint32_t         *p_done_num,
                                  uint32_t          timeout);

/**
 * \brief aw_can_std_msgs_rcv
 * 接收标准CAN报文，缓冲区只要有数据就会成功返回，
 * 实际个数值在存放在p_done_num中，
 * 只有缓冲区没有数据的时候，超时时间有效，
 * 为了保证接收数据实时性，在超时等待时候，当接收到有效数据，立刻返回。
 * 用户接口函数；
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] p_msgs:       接收FD报文缓冲区地址。
 *
 * \param[in] msgs_num:     缓冲区报文个数。
 *
 * \param[in] p_done_num:   实际读取个数地址。
 *
 * \param[in] timeout:      无报文超时时间。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_fd_msgs_rcv (int              chn,
                                 aw_can_fd_msg_t *p_msgs,
                                 uint32_t         msgs_num,
                                 uint32_t        *p_done_num,
                                 uint32_t         timeout);
/**
 * \brief 写CAN寄存器
 * 写CAN寄存器，适用于CAN驱动框架不包含的，特殊的CAN操作
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] offset:       寄存器地址
 *
 * \param[in] p_data:       内容。
 *
 * \param[in] length:       长度。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_reg_write (int      chn,
                               uint32_t offset,
                               uint8_t *p_data,
                               size_t   length);

/**
 * \brief 读取CAN寄存器
 * 读取CAN寄存器，适用于CAN驱动框架不包含的，特殊的CAN操作
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] offset:       寄存器地址
 *
 * \param[in] p_data:       读取内容。
 *
 * \param[in] length:       读取长度。
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_reg_read (int      chn,
                              uint32_t offset,
                              uint8_t *p_data,
                              size_t   length);
/**
 * \brief 向CAN寄存器写报文，
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] p_msg:        报文指针
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_reg_msg_write (int                 chn,
                                   aw_can_msg_t       *p_msg);

/**
 * \brief 读取CAN报文，
 * 从CAN寄存器中读取报文
 *
 * \param[in] chn:          CAN通道号。
 *
 * \param[in] p_msg:        报文指针
 *
 * \retval aw_can_err_t:    见函数返回错误码。
 *
 */
aw_can_err_t aw_can_reg_msg_read  (int                 chn,
                                   aw_can_msg_t       *p_msg);

#ifdef __cplusplus
}
#endif

#endif /* __AW_CAN_H */
