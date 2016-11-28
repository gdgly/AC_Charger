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
 * \brief  电表操作实现
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-12  xjc, first implementation
 * \endinternal
 */

#include "aw_iccreader.h"
#include "aw_serial.h"
#include "aw_ioctl.h"
#include "aw_delay.h"

#include "aw_vdebug.h"
#include "aw_task.h"                    /* 多任务服务 */
#include <string.h>

#define __ICC_RX_BYTE_TIMEOUT_CFG    5    /* 最大允许接收单字节超时配置，单位ms */
#define __ICC_RX_FRAME_TIMEOUT_CFG   1000 /* 最大允许接收帧超时超时配置，单位ms */


#define __ICC_START_CODE  (0x02u)  /* 协议起始符     */
#define __ICC_END_CODE    (0x03u)  /* 协议结束符     */


#define __ICC_PROTOCOL_LENGTH 5     /**< \brief 通讯帧协议控制字节数 */
#define __ICC_INFO_MAX_LENGTH 265   /**< \brief 通讯帧数据单元最大字节数(符合所有未被拉长处理的APDU包字节要求) */
/** \brief 通讯帧信息最小字节数（新帧格式） */
#define __ICC_PACKET_MIN_SIZE (__ICC_PROTOCOL_LENGTH)
/** \brief 通讯帧信息最大字节数（新帧格式）*/
#define __ICC_PACKET_MAX_SIZE (__ICC_PROTOCOL_LENGTH + __ICC_INFO_MAX_LENGTH)

#define __ICC_CMD_EXE_STATE(rbuf, rlen) \
                            ((rbuf[rlen - 2] == 0) && \
                             (rbuf[rlen - 1] == 0))

#define __CMD_S50S70_KEY_AUTH   0x0246 /* 直接密钥认证 */
#define __CMD_S50S70_BLK_READ   0x0247 /* 块读 */
#define __CMD_S50S70_BLK_WRITE  0x0248 /* 块写 */
#define __CMD_S50S70_VAL_OPT    0x024A /* 值操作 */
#define __CMD_S50S70_VAL_SET    0x0250 /* 值设置 */
#define __CMD_S50S70_VAL_GET    0x0251 /* 值获取 */

#define __CMD_CTRL_BAUD_SET     0x3001 /* 波特率设置 */
#define __CMD_CTRL_INFO_GET     0x3111 /* 信息获取 */
#define __CMD_CTRL_BUZZER_SET   0x3113 /* 蜂鸣器设置 */
#define __CMD_CTRL_LED_SET      0x3114 /* LED设置 */
#define __CMD_CTRL_RF_OPEN      0x3190 /* 打开射频 */
#define __CMD_CTRL_RF_CLOSE     0x3191 /* 关闭射频 */

#define __CMD_CARD_POWER_ON     0x3222 /* 接触卡上电 */
#define __CMD_CARD_POWER_OFF    0x3223 /* 接触卡掉电 */
#define __CMD_CARD_ACTIVE       0x3224 /* 激活非接触卡 */
#define __CMD_CARD_APDU         0x3226 /* APDU命令传输 */


/** 
 * \brief 通过串口发送数据
 * \param [in] handle  : 读卡器实例
 * \param [in] p_txbuf : 发送数据缓冲区
 *                       p_txbuf[0] 固定用于控制码使用
 * \param [in] nbytes  : 发送字节数
 *                       nbytes 比须大于0（因为至少有一个控制码）
 *
 * \return AW_OK      : 通信成功
 * \return -AW_EINVAL : 参数错误
 * \return -AW_EIO    : 硬件通信IO发送错误
 * 
 * \note 协议数据通用发送接口，函数自动添加帧头、地址以及校验信息，
 *      用户只需关心待发送的控制码，以及数据标识（数据域）即可
 */
aw_local aw_err_t __serial_send(struct aw_iccreader* handle,
                                const uint8_t       *p_txbuf,
                                uint32_t             nbytes)
{
    uint8_t tx_data[__ICC_PACKET_MAX_SIZE];
    uint32_t i   = 0;
    uint8_t  sum = 0;  /* 8位校验和 */
    
    if ((NULL == handle)||
        (NULL == handle->p_transfer) ||
        ((nbytes-2) > __ICC_INFO_MAX_LENGTH)) {
        return -AW_EINVAL;
    }
   
    tx_data[0] = __ICC_START_CODE;
    tx_data[1] = (nbytes >> 8);
    tx_data[2] = (nbytes >> 0);
    tx_data[3] = p_txbuf[0];
    tx_data[4] = p_txbuf[1];
    memcpy(&tx_data[5], &p_txbuf[2], (nbytes-2));
    sum  = tx_data[3];
    sum ^= tx_data[4];
    for (i = 0; i < (nbytes-2); i++) {
        sum ^= tx_data[5+i];
    }
    tx_data[5 + (nbytes-2)] = sum;
    tx_data[5 + (nbytes-2) + 1] = __ICC_END_CODE;
    
    /* 发送数据帧 */
    if ((nbytes + 5) != aw_serial_poll_write(handle->p_transfer->uart_num,
                                              (char *)tx_data,
                                              nbytes + 5)) {
        return -AW_EIO;
    }
    return AW_OK;
}


/**
 * \brief 从串口中读取数据
 * \param [in] handle    : 读卡器实例
 * \param [out] p_rxbuf  : 存储数据的指针
 * \param [in]  nbytes   : 接收个数
 * \param [in]  timeout  : 最大允许超时时间，单位ms
 *
 * \return   >0          : 实际读取的字节数
 * \return -AW_ETIMEDOUT : 超时错误
 * \return -AW_ENOMEM    : 接收缓冲区p_rxbuf空间不足
 *
 * \note 若接收成功，p_rxbuf[nbytes-1],p_rxbuf[nbytes-2]为接收的状态字
 */
aw_local int __recevie_timeout (struct aw_iccreader* handle,
                                 uint8_t  *p_rxbuf,
                                 uint8_t   nbytes,
                                 uint32_t  timeout)

{
#define __ICC_STATE_START_CODE_FIND   0  /* 查找协议头 */
#define __ICC_STATE_CTRL_CODE_GET     1  /* 获取控制吗  */
#define __ICC_STATE_DAT_GET           2  /* 获取数据域 和校验和以及结束符 */

    uint32_t uart_num;
    int      state = __ICC_STATE_START_CODE_FIND;
    int      cnt   = 0; /* 目前协议数据的计数 */
    uint8_t rx_data[__ICC_PACKET_MAX_SIZE], sum;
    aw_tick_t start_ticks, end_ticks;
    uint32_t  timeout_ms;
    uint8_t  *p_rbuf = &rx_data[0];
    uint16_t  rlen = 1, rlen_tmp;

    uart_num = handle->p_transfer->uart_num;
    start_ticks = aw_sys_tick_get();

    while (1) {

        if (__ICC_STATE_START_CODE_FIND == state) {
            /* 帧起始时，要检测回应超时*/
            end_ticks  = aw_sys_tick_get();
            timeout_ms = aw_ticks_to_ms(end_ticks - start_ticks);
            if (timeout_ms > timeout) {
                return -AW_ETIMEDOUT;
            }
        }

        /* 读取帧起始符和地址，一帧至少是12个字节 */
        if (0 >= (rlen_tmp = aw_serial_read(uart_num, (char *)p_rbuf, rlen))) {
            if (__ICC_STATE_START_CODE_FIND != state) {
                /* 帧起始后，要检测字节超时*/
                return -AW_ETIMEDOUT;
            }
            continue;
        } else if (rlen != rlen_tmp){
            rlen  -= rlen_tmp;
            p_rbuf = p_rbuf + rlen_tmp;
            continue;
        }

        switch (state) {
        case __ICC_STATE_START_CODE_FIND:
             if (rx_data[0] == __ICC_START_CODE) {
                 rlen = 4;
                 p_rbuf = &rx_data[1];
                 state = __ICC_STATE_CTRL_CODE_GET;
             }
             break;

        case __ICC_STATE_CTRL_CODE_GET:
            rlen = (rx_data[1] << 8) | (rx_data[2]);
            if ((rlen > __ICC_INFO_MAX_LENGTH) || (rlen < 2)) {
                return -AW_ENOMEM;
            }
            p_rbuf = &rx_data[5];
            state  = __ICC_STATE_DAT_GET;
            break;

        case __ICC_STATE_DAT_GET:
            rlen = (rx_data[1] << 8) | (rx_data[2]);
            if (__ICC_END_CODE != rx_data[rlen + 4]) {
                return AW_ERROR; /* 帧格式错误 */
            }

//            if (rlen != nbytes) {
//                return AW_ERROR; /* 帧格式错误 */
//            }

            /* 计算校验和 */
            sum  = rx_data[3];
            for (cnt = 1; cnt < rlen; cnt++) {
                sum ^= rx_data[3 + cnt];
            }

            if (sum != rx_data[rlen + 3]) {
                return AW_ERROR;  /* 帧格式错误 */
            }

            memcpy(p_rxbuf, &rx_data[5], rlen-2);
            p_rxbuf[rlen - 2] = rx_data[3];
            p_rxbuf[rlen - 1] = rx_data[4];
            return rlen;
            break;

        default:break;
        }
    }
    return AW_ERROR;
}
/** 
 * \brief 接收数据
 * \param [in] handle  : 读卡器实例
 * \param [in] p_rxbuf : 接收数据缓冲区
 * \param [in] nbytes  : 接收字节数
 *
 * \return   >0          : 实际读取的字节数
 * \return -AW_EINVAL : 参数错误
 * \return -AW_ETIMEDOUT : 超时错误
 *
 * \note 数据通用接收接口，函数复制识别帧头，地址以及校验信息，
 *      用户只需关心接收到的控制码，以及数据（包括数据标识）即可.
 *    若接收成功，p_rxbuf[nbytes-2], p_rxbuf[nbytes-1]为接收的状态字
 *    返回数据格式
 *     数据域 | 状态字（2字节）
 *
 */
aw_local int __serial_receive(struct aw_iccreader* handle,
                              uint8_t             *p_rxbuf,
                              uint32_t             nbytes)
{

    if ((NULL == handle)                     ||
        (NULL == handle->p_transfer)         ||
        (nbytes < 2) || (nbytes > __ICC_INFO_MAX_LENGTH)) {
        return -AW_EINVAL;
    }

    return __recevie_timeout(handle, p_rxbuf, nbytes, __ICC_RX_FRAME_TIMEOUT_CFG);
}


/**
 * \brief 传输数据
 * \param[in]  handle   : 指向读卡器的实例
 * \param[in]  cmd      : 命令类型
 * \param[in]  p_txbuf  : 发送缓冲器
 * \param[in]  tlen     : 发送缓冲器长度
 * \param[out] p_rxbuf  : 接收缓冲器
 * \param[in]  rlen     : 接收缓冲器长度
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_transfer(struct aw_iccreader* handle,
                               uint32_t  cmd,
                               void     *p_txbuf,
                               uint16_t  tlen,
                               void     *p_rxbuf,
                               uint16_t  rlen)
{
    uint8_t  buf[__ICC_PACKET_MAX_SIZE] = {0};
    int      len      = 0;

    if ((NULL == handle)              ||
        (NULL == handle->p_transfer)  ||
        (NULL == handle->pfn_send)    ||
        (NULL == handle->pfn_receive) ) {
        return -AW_EINVAL;
    }

    if (((tlen + 2) > __ICC_PACKET_MAX_SIZE) ||
        ((rlen + 2) > __ICC_PACKET_MAX_SIZE)) {
        return -AW_EINVAL;
    }

    buf[0] = (uint8_t)(cmd >> 8);
    buf[1] = (uint8_t)(cmd >> 0);
    memcpy(&buf[2], p_txbuf, tlen);
    /* 发送请求 */
    if (AW_OK != handle->pfn_send(handle, buf, 2+tlen)) {
        return  AW_ERROR;
    }
    /* 读取数据 */
    if (0 > (len = handle->pfn_receive(handle, buf, 2+rlen))) {
        return  AW_ERROR;
    }

    if (!__ICC_CMD_EXE_STATE(buf, len)) {
        /* 异常回应帧 */
        //memcpy(p_rxbuf, &buf[len-2], 2);
        return -AW_EPERM;
    }
    memcpy(p_rxbuf, buf, rlen);
    return AW_OK;
}

/**
 * \brief 设置读卡器模块通信波特率
 * \param[in]  handle    : 指向读卡器的实例
 * \param[in]  baud_code : 波特率代号
 *                         0x00 : 9600
 *                         0x01 : 19200
 *                         0x02 : 38400
 *                         0x03 : 57600
 *                         0x04 : 115200
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_baud_set (struct aw_iccreader* handle, uint8_t baud_code)
{
    return aw_iccreader_transfer(handle, __CMD_CTRL_BAUD_SET, &baud_code, 1, NULL, 0);
}

/**
 * \brief 获取读卡器版本信息
 * \param[in]  handle    : 指向读卡器的实例
 * \param[in]  p_rxbuf   : 存放版本信息的缓冲器
 * \param[in]  rlen      : 读取版本信息的字节数
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_info_get (struct aw_iccreader* handle, void *p_rxbuf, uint32_t rlen)
{
    return aw_iccreader_transfer(handle, __CMD_CTRL_INFO_GET, NULL, 0, p_rxbuf, rlen);
}

/**
 * \brief 获取读卡器版本信息
 * \param[in]  handle    : 指向读卡器的实例
 * \param[in]  dlytime   : 蜂鸣器鸣响时间
 * \param[in]  times     : 蜂鸣器鸣响次数
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_buzzer_set (struct aw_iccreader* handle, uint16_t dlytime, uint8_t times)
{
    uint8_t buf[3] = {dlytime>>8, dlytime, times};

    return aw_iccreader_transfer(handle, __CMD_CTRL_BUZZER_SET, buf, 3, NULL, 0);
}

/**
 * \brief 控制LED状态
 * \param[in]  handle    : 指向读卡器的实例
 * \param[in]  led1_en   :LED1控制：TRUE-亮灯，FALSE-灭灯
 * \param[in]  led2_en   :LED2控制：TRUE-亮灯，FALSE-灭灯
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_led_set (struct aw_iccreader* handle, bool_t led1_en, bool_t led2_en)
{
    uint8_t state = (led1_en ? (1 << 7) : 0) | (led2_en ? (1 << 6) : 0);

    return aw_iccreader_transfer(handle, __CMD_CTRL_LED_SET, &state, 1, NULL, 0);
}

/**
 * \brief 打开射频
 * \param[in]  handle    : 指向读卡器的实例
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_rf_open (struct aw_iccreader* handle)
{
    return aw_iccreader_transfer(handle, __CMD_CTRL_RF_OPEN, NULL, 0, NULL, 0);
}


/**
 * \brief 关闭射频
 * \param[in]  handle    : 指向读卡器的实例
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_rf_close (struct aw_iccreader* handle)
{
    return aw_iccreader_transfer(handle, __CMD_CTRL_RF_CLOSE, NULL, 0, NULL, 0);
}

/**
 * \brief 卡直接密钥验证
 * \param [in] handle   : 指向读卡器的实例
 * \param [in] key_type : 密钥类型， 密钥A #AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYA
 *                                 密钥B #AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYB
 * \param [in] p_uid    : 卡的UID缓冲区
 * \param [in] uid_len  : 卡的UID的长度( 只能是4个字节)
 * \param [in] p_uid    : 密钥
 * \param [in] uid_len  : 密钥的长度( 只能是6或16个字节)
 * \param [in] block    : 验证块
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_key_auth (struct aw_iccreader* handle,
                                uint8_t              key_type,
                                uint8_t             *p_uid,
                                uint8_t              uid_len,
                                uint8_t             *p_key,
                                uint8_t              key_len,
                                uint8_t              block)
{
    uint8_t buf[22] = {0};

    buf[0] = key_type;
    memcpy(&buf[1], p_uid, 4);
    memcpy(&buf[1+4], p_key, key_len);
    buf[1+4+key_len] = block;

    return aw_iccreader_transfer(handle, __CMD_S50S70_KEY_AUTH, buf, 2+4+key_len, NULL, 0);
}

/**
 * \brief 读取某块的数据
 * \param [in] handle   : IC卡读卡器的实例
 * \param [in] block    : 验证块
 * \param [out] p_buf   : 缓冲区，长度是块的长度（16字节）
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_block_read (struct aw_iccreader *handle,
                                  uint8_t             *p_buf,
                                  uint8_t              block)
{
    return aw_iccreader_transfer(handle, __CMD_S50S70_BLK_READ, &block, 1, p_buf, 16);
}

/**
 * \brief 写某块的数据
 * \param [in] handle   : IC卡读卡器的实例
 * \param [in] block    : 验证块
 * \param [out] p_buf   : 缓冲区，长度是块的长度（16字节）
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_block_write (struct aw_iccreader *handle,
                                   uint8_t             *p_buf,
                                   uint8_t              block)
{
    uint8_t buf[17] = {0};

    buf[0] = block;
    memcpy(&buf[1], p_buf, 16);
    return aw_iccreader_transfer(handle, __CMD_S50S70_BLK_WRITE, buf, 17, NULL, 0);
}

/**
 * \brief 激活s50s70卡
 * \param [in] handle   : IC卡读卡器的实例
 * \param [in] aw_iccreader_s50s70_ci_t    : 激活卡的信息
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_s50s70_active (struct aw_iccreader      *handle,
                                     aw_iccreader_s50s70_ci_t *p_card)
{
    uint8_t buf[2] = {0};
    return aw_iccreader_transfer(handle, __CMD_CARD_ACTIVE, buf, 2, p_card, 6);
}


/**
 * \brief S50S70卡挂起
 * \param[in]  handle  : 指向IC卡的实例
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_iccreader_halt(struct aw_iccreader *handle)
{

    return AW_OK;
}

/**
 * \brief 给接触卡上电
 * \param [in] handle   : IC卡读卡器的实例
 * \param [in] card_no  : 卡座号（用户卡： 00H~0FH， PSAM 卡：10H~1FH）
 * \param [in] dly_time : 等待插卡时间(ms)（0 无需等待，无卡直接返回）
 * \param [in] dly_time : 等待插卡时间(ms)（0 无需等待，无卡直接返回）
 * \param [in] p_info   : 卡信息
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_samc_power_on(struct aw_iccreader *handle,
                                    uint8_t card_no,
                                    uint16_t dly_time,
                                    aw_iccreader_samc_info_t *p_info)
{
    uint8_t buf[3] = {0};

    buf[0] = (uint8_t)(dly_time >> 8);
    buf[1] = (uint8_t)(dly_time >> 0);
    buf[2] = card_no;
    return aw_iccreader_transfer(handle, __CMD_CARD_POWER_ON, buf, 3, p_info, 50);
}

/**
 * \brief 给接触卡下电
 * \param [in] handle   : IC卡读卡器的实例
 * \param [in] card_no  : 卡座号（用户卡： 00H~0FH， PSAM 卡：10H~1FH）
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_EPERM   : 操作不允许（设备回应了异常帧）
 */
aw_err_t aw_iccreader_samc_power_off(struct aw_iccreader *handle,
                                    uint8_t               card_no)
{
    return aw_iccreader_transfer(handle, __CMD_CARD_POWER_OFF, &card_no, 1, NULL, 0);
}

/**
 * \brief 读卡器初始化
 * \param[in]  handle  : 指向IC卡的实例
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
 aw_err_t aw_iccreader_inst_init (struct aw_iccreader           *handle,
                                  const aw_iccreader_transfer_t *p_transfer)
{
    uint32_t uart_num;

    if ((NULL == handle) ||
        (NULL == p_transfer)) {
        return -AW_EINVAL;
    }
    uart_num = p_transfer->uart_num;

    handle->pfn_send    = __serial_send;
    handle->pfn_receive = __serial_receive;
    handle->p_transfer  = p_transfer;

    /* 串口初始化配置, 如波特率 115200 */
    aw_serial_ioctl(uart_num,
                    SIO_BAUD_SET,
                   (void *)(p_transfer->uart_buad));
    /* 串口参数 如：8 个数据位 1 个停止位，无奇偶校验 */
    aw_serial_ioctl(uart_num,
                    SIO_HW_OPTS_SET,
                    (void *)(p_transfer->uart_format));
    /* 设置读取超时时间 */
    aw_serial_ioctl(uart_num, AW_TIOCRDTIMEOUT, (void *)__ICC_RX_BYTE_TIMEOUT_CFG);

    return AW_OK;
}



