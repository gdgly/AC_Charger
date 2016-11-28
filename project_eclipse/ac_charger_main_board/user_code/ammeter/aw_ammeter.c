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

#include "aw_ammeter.h"
#include "aw_serial.h"
#include "aw_ioctl.h"
#include "aw_delay.h"

#include "aw_vdebug.h"
#include "aw_task.h"                    /* 多任务服务 */
#include <string.h>

#define __DL645_RX_BYTE_TIMEOUT_CFG    100   /* 最大允许接收单字节超时配置，单位ms */
#define __DL645_RX_FRAME_TIMEOUT_CFG   1000 /* 最大允许接收帧超时超时配置，单位ms */


#define __DL645_GUIDE_CODE  (0xFEu)  /* DL645协议引导码 */
#define __DL645_START_CODE  (0x68u)  /* DL645起始符     */
#define __DL645_END_CODE    (0x16u)  /* DL645结束符     */
#define __DL645_ADDR_LEN    (6)      /* 地址长度，单位字节 */

#define __DL645_07_CTRL_CODE_DATGET    (0x11u)        /* 读取数据控制码(07年版本) */
#define __DL645_07_DATAID_ENERGY       (0x00010000u)  /* 电量读取标识(07年版本) */
#define __DL645_07_DATAID_A_CURR       (0x02020100u)  /* A相电流标识(07年版本) */
#define __DL645_07_DATAID_A_VOL        (0x02010100u)  /* A相电压标识(07年版本) */
#define __DL645_07_DATAID_POWER        (0x02030000u)  /* 瞬时有功功率标识(07年版本) */

#define __DL645_97_CTRL_CODE_DATGET    (0x01u)        /* 读取数据控制码(97年版本) */
#define __DL645_97_DATAID_ENERGY       (0x9010u)     /* 电量读取标识(97年版本) */
#define __DL645_97_DATAID_A_CURR       (0xB621u)     /* A相电流标识(97年版本) */
#define __DL645_97_DATAID_A_VOL        (0xB611u)     /* A相电压标识(97年版本) */
#define __DL645_97_DATAID_POWER        (0xB630u)     /* 瞬时有功功率标识(97年版本) */


#define __DL645_PROTOCOL_LENGTH 12    /**< \brief 通讯帧协议字节数 */
#define __DL645_INFO_MAX_LENGTH 200   /**< \brief 通讯帧最大字节数 */
/** \brief 通讯帧信息最小字节数（新帧格式） */
#define __DL645_PACKET_MIN_SIZE (__DL645_PROTOCOL_LENGTH)
/** \brief 通讯帧信息最大字节数（新帧格式）*/
#define __DL645_PACKET_MAX_SIZE (__DL645_PROTOCOL_LENGTH + \
                                 __DL645_INFO_MAX_LENGTH)

/** \brief 驱动支持DL645 07年协议  */
#define __DL645_07_SUPPORT   1

/** \brief 驱动支持DL645 97年协议  */
#define __DL645_97_SUPPORT   0

/** \brief 驱动支持modbus协议  */
#define __MODBUS_SUPPORT     0

#if __MODBUS_SUPPORT
#include "modbus/aw_mb_master.h"
#endif
/*******************************************************************************
  macro operate
*******************************************************************************/
/** \brief 由电表父类指针转成到直流电表子类 */
#define __AMETER_DC_DECL(p_ammeter_dc, handle) \
                   aw_ammeter_dc_t *p_ammeter_dc = (aw_ammeter_dc_t *)((handle))

/** \brief 由通信类父类指针转成到DL645通信子类 */
#define __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle) \
                   aw_ammeter_transfer_dl645_t *p_ammeter_transfer_dl645 = \
                                      (aw_ammeter_transfer_dl645_t *)((handle))


/** \brief 由通信类父类指针转成到modbus-rtu通信子类 */
#define __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, handle) \
                   aw_ammeter_transfer_mb_t *p_ammeter_transfer_mb = \
                                      (aw_ammeter_transfer_mb_t *)((handle))

/**
 * \brief 通信实例初始化
 * \param[in]  handle  : 指向电表的指针
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_transfer_inst_init (aw_ammeter_transfer_t* handle);

#if __DL645_07_SUPPORT || __DL645_97_SUPPORT
/** 
 * \brief 按DL645协议发送数据
 * \param [in] handle  : 电表通信传输的实例
 * \param [in] p_txbuf : 发送数据缓冲区
 *                       p_txbuf[0] 固定用于控制码使用
 * \param [in] nbytes  : 发送字节数
 *                       nbytes 比须大于0（因为至少有一个控制码）
 *
 * \return AW_OK      : 通信成功
 * \return -AW_EINVAL : 参数错误
 * \return -AW_EIO    : 硬件通信IO发送错误
 * 
 * \note DL/T 645协议 数据通用发送接口，函数自动添加帧头、地址以及校验信息，
 *      用户只需关心待发送的控制码，以及数据标识（数据域）即可
 */
aw_local aw_err_t __dl645_send(struct aw_ammeter_transfer* handle,
                               const uint8_t              *p_txbuf,
                               uint32_t                    nbytes)
{
    __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle);
    uint8_t tx_data[50 + 12] = {__DL645_GUIDE_CODE, __DL645_GUIDE_CODE,
                                __DL645_GUIDE_CODE, __DL645_GUIDE_CODE,
                                __DL645_START_CODE};
    uint32_t i   = 0;
    uint8_t  sum = 0;  /* 8位校验和 */
    uint8_t  dat_num;  /* 去除控制码后的数据数 */
    
    aw_tick_t start_ticks, end_ticks;
    uint32_t  timeout_ms;



    if ((NULL == p_ammeter_transfer_dl645)     ||
        (NULL == handle->p_addr)               ||
        (__DL645_ADDR_LEN != handle->addr_len) || /* DL T645 仅支持6字节的地址 */
        (nbytes < 1) || (nbytes > 51)) {          /* 写数据时，数据域最长允许50个字节 */
        return -AW_EINVAL;
    }
   
    dat_num  = nbytes - 1;
    
    /* 填充地址 */
    for (i = 0; i < __DL645_ADDR_LEN; i++) {
        tx_data[i + 5] = handle->p_addr[i];
    }
    tx_data[__DL645_ADDR_LEN + 5] = __DL645_START_CODE; /* 第二个帧起始符 */
    tx_data[__DL645_ADDR_LEN + 6] = p_txbuf[0];         /* 控制码 */
    tx_data[__DL645_ADDR_LEN + 7] = dat_num;           /*  数据域长度 */
    /*  数据域长度 */
    for (i = 1; i < nbytes; i++) {
        tx_data[__DL645_ADDR_LEN + 7 + i] = p_txbuf[i] + 0x33u;
    }
    /* 计算校验和 */
    sum = 0;
    for (i = 4; i < nbytes + 13; i++) {
        sum += tx_data[i];
    }
    
    /* 检验码 */
    tx_data[__DL645_ADDR_LEN + 7 + nbytes]     = sum;
    /* 结束码 */
    tx_data[__DL645_ADDR_LEN + 7 + nbytes + 1] = __DL645_END_CODE;
    
    /* 发送数据帧 */
//    start_ticks = aw_sys_tick_get();

//    if ((nbytes + 15) != aw_serial_write(p_ammeter_transfer_dl645->uart_num,
//                                          (char *)tx_data,
//                                          nbytes + 15)) {
    if ((nbytes + 15) != aw_serial_poll_write(p_ammeter_transfer_dl645->uart_num,
                                              (char *)tx_data,
                                              nbytes + 15)) {
        return -AW_EIO;
    }
//    end_ticks = aw_sys_tick_get();
//    timeout_ms = aw_ticks_to_ms(end_ticks - start_ticks);
//    AW_INFOF(("Ticks: %d \r\n", timeout_ms));
    return AW_OK;
}


/**
 * \brief 从串口中读取数据
 * \param [in] handle    : 电表通信传输的实例
 * \param [out] p_rxbuf  : 存储数据的指针
 * \param [in]  nbytes   : 接收个数
 * \param [in]  timeout  : 最大允许超时时间，单位ms
 *
 * \return   >0          : 实际读取的字节数
 * \return -AW_ETIMEDOUT : 超时错误
 * \return -AW_ENOMEM    : 接收缓冲区p_rxbuf空间不足
 *
 * \note 若接收成功，p_rxbuf[nbytes-1]为接收的控制码
 */
aw_local int __dl645_recevie_timeout (struct aw_ammeter_transfer* handle,
                                      uint8_t  *p_rxbuf,
                                      uint8_t   nbytes,
                                      uint32_t  timeout)

{
#define __DL645_STATE_START_CODE_FIND   0  /* 查找协议头 */
#define __DL645_STATE_CTRL_CODE_GET     1  /* 获取控制吗  */
#define __DL645_STATE_DAT_GET           2  /* 获取数据域 和校验和以及结束符 */

    __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle);
    uint32_t uart_num;
    int      state = __DL645_STATE_START_CODE_FIND;
    int      cnt   = 0; /* 目前协议数据的计数 */
    uint8_t rx_data[__DL645_PACKET_MAX_SIZE], sum;
    aw_tick_t start_ticks, end_ticks;
    uint32_t  timeout_ms;
    uint8_t  *p_rbuf = &rx_data[0];
    uint8_t  rlen    = 1, rlen_tmp;

    uart_num = p_ammeter_transfer_dl645->uart_num;
    start_ticks = aw_sys_tick_get();

    while (1) {

        end_ticks  = aw_sys_tick_get();
        timeout_ms = aw_ticks_to_ms(end_ticks - start_ticks);
        if (timeout_ms > timeout) {
            return -AW_ETIMEDOUT;
        }

        /* 读取帧起始符和地址，一帧至少是12个字节 */
        if (0 >= (rlen_tmp = aw_serial_read(uart_num, (char *)p_rbuf, rlen))) {
            state  = __DL645_STATE_START_CODE_FIND;
            rlen   = 1;
            p_rbuf = &rx_data[0];
            aw_mdelay(5);
            continue;
        } else if (rlen != rlen_tmp){
            rlen  -= rlen_tmp;
            p_rbuf = p_rbuf + rlen_tmp;
            continue;
        }

        switch (state) {
        case __DL645_STATE_START_CODE_FIND:
             if (rx_data[0] == __DL645_START_CODE) {
                 rlen = 9;
                 p_rbuf = &rx_data[1];
                 state = __DL645_STATE_CTRL_CODE_GET;
             }
             break;

        case __DL645_STATE_CTRL_CODE_GET:

            if (rx_data[7] != __DL645_START_CODE) {
                p_rbuf = &rx_data[0];
                rlen   = 1;
                break;
            }
            /* 判断地址是否一直 */
            for (cnt = 0; cnt < __DL645_ADDR_LEN; cnt++) {
                if (rx_data[1+cnt] != handle->p_addr[cnt]) {
                    p_rbuf = &rx_data[0];
                    rlen   = 1;
                    break;
                }
            }
            if ((rx_data[9] <= __DL645_INFO_MAX_LENGTH) &&
                (rx_data[9] == (nbytes - 1))) { /* 判断数据长度是否为有效 */
               p_rbuf = &rx_data[10];
               rlen   = rx_data[9]+2;
               state  = __DL645_STATE_DAT_GET;
            } else {
                p_rbuf = &rx_data[0];
                rlen   = 1;
                state  = __DL645_STATE_START_CODE_FIND;
            }
            break;

        case __DL645_STATE_DAT_GET:
            p_rbuf = &rx_data[0];
            rlen   = 1;
            state  = __DL645_STATE_START_CODE_FIND;
            if (rx_data[rx_data[9]+11] != __DL645_END_CODE) {
                break;
            }

            /* 计算校验和 */
            sum  = 0;
            for (cnt = 0; cnt < rx_data[9]+10; cnt++) {
                sum += rx_data[cnt];
            }

            if (sum == rx_data[rx_data[9]+10]) {
                if ((rx_data[9] + 1) < nbytes) {
                    return -AW_ENOMEM;
                }
                /* 数据接收完毕 */
                p_rxbuf[rx_data[9]] = rx_data[8]; /* 保存控制码 */
                for (cnt = 0; cnt < rx_data[9]; cnt++) {
                    p_rxbuf[cnt] = rx_data[cnt+10] - 0x33u;
                }
                return rx_data[9] + 1; /* 控制码+数据 */
            }
            break;

        default:break;
        }
    }
    return AW_ERROR;
}
/** 
 * \brief 按DL645协议接收数据
 * \param [in] handle  : 电表通信传输的实例
 * \param [in] p_rxbuf : 接收数据缓冲区
 * \param [in] nbytes  : 接收字节数
 *
 * \return   >0          : 实际读取的字节数
 * \return -AW_EINVAL : 参数错误
 * \return -AW_ETIMEDOUT : 超时错误
 *
 * \note DL/T 645协议 数据通用接收接口，函数复制识别帧头，地址以及校验信息，
 *      用户只需关心接收到的控制码，以及数据（包括数据标识）即可.
 *    若接收成功，p_rxbuf[nbytes-1]为接收的控制码
 *    返回数据格式
 *    07年 ： 数据标识（4字节） | 数据域 | 控制码（1字节）
 *    97年 ： 数据标识（2字节） | 数据域 | 控制码（1字节）
 *
 */
aw_local int __dl645_receive(struct aw_ammeter_transfer* handle,
                             uint8_t                    *p_rxbuf,
                             uint32_t                    nbytes)
{
    __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle);

    if ((NULL == p_ammeter_transfer_dl645)     ||
        (NULL == handle->p_addr)               ||
        (__DL645_ADDR_LEN != handle->addr_len) || /* DL T645 仅支持6字节的地址 */
        (nbytes < 1) || (nbytes > 200)) {         /* 读数据时，数据域最长允许200个字节 */
        return -AW_EINVAL;
    }

    return __dl645_recevie_timeout(handle, p_rxbuf, nbytes, __DL645_RX_FRAME_TIMEOUT_CFG);
}

/**
 * \brief 获取当前电量，单位0.01 KWh(DTL645 07年协议获取)
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_energy : 指向存放电量的变量
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dl645_07_active_energy_get(struct aw_ammeter* handle,
                                               uint32_t          *p_energy)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[9] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_07_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_07_DATAID_ENERGY ;
    buf[2] = (uint8_t)(__DL645_07_DATAID_ENERGY >> 8);
    buf[3] = (uint8_t)(__DL645_07_DATAID_ENERGY >> 16);
    buf[4] = (uint8_t)(__DL645_07_DATAID_ENERGY >> 24);
    /* 发送请求 */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    5)) {
        return  AW_ERROR;
    }
    /* 读取数据 */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (9 != len) {
        return AW_ERROR;
    }
    /* buf[0-3] 存储着4个字节的数据标志
     * buf[4-7] 存储着写个数据的电量数据，格式为 XXXXXX.XX KWh (LSB格式存放) */
    p_ammeter_dc->super.energy = (AW_BCD_TO_HEX(buf[7]) * 1000000) +
                                (AW_BCD_TO_HEX(buf[6]) * 10000)   +
                                (AW_BCD_TO_HEX(buf[5]) * 100)     +
                                (AW_BCD_TO_HEX(buf[4]) );

    if (NULL != p_energy) {
        *p_energy = p_ammeter_dc->super.energy;
    }
    return AW_OK;
}
#if __DL645_97_SUPPORT
/**
 * \brief 获取当前电量，单位0.01 KWh(DTL645 97年协议获取)
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_energy : 指向存放电量的变量
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dl645_97_active_energy_get(struct aw_ammeter* handle,
                                               uint32_t          *p_energy)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[7] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          || 
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_97_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_97_DATAID_ENERGY ;
    buf[2] = (uint8_t)(__DL645_97_DATAID_ENERGY >> 8);
    /* 发送请求 */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    3)) {
        return  AW_ERROR;                    
    }
    /* 读取数据 */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;                    
    }

    if (7 != len) {
        return AW_ERROR;
    }

    p_ammeter_dc->super.power = (AW_BCD_TO_HEX(buf[5]) * 1000000) +
                                (AW_BCD_TO_HEX(buf[4]) * 10000)   +
                                (AW_BCD_TO_HEX(buf[3]) * 100)     +
                                (AW_BCD_TO_HEX(buf[2]) );
                                
    if (NULL != p_energy) {
        *p_energy = p_ammeter_dc->super.power;
    }
    return AW_OK;
}
#endif

/**
 * \brief 获取A相电流（07年版本）
 * \param[in]  handle   : 指向电表的实例
 * \param[in]  phase    : 获取的相，0-A相，1-B相，2-C相
 * \param[out] p_curr   : 指向存放电流的变量，单位0.001A
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dl645_07_current_get(struct aw_ammeter* handle,
                                           uint8_t            phase,
                                           uint32_t          *p_curr)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[8] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_07_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_07_DATAID_A_CURR ;
    buf[2] = (uint8_t)(__DL645_07_DATAID_A_CURR >> 8) + phase;
    buf[3] = (uint8_t)(__DL645_07_DATAID_A_CURR >> 16);
    buf[4] = (uint8_t)(__DL645_07_DATAID_A_CURR >> 24);
    /* 发送请求 */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    5)) {
        return  AW_ERROR;
    }
    /* 读取数据 */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_curr) {
        *p_curr = (AW_BCD_TO_HEX(buf[6]) * 10000) +
                  (AW_BCD_TO_HEX(buf[5]) * 100)     +
                  (AW_BCD_TO_HEX(buf[4]) );
    }
    return AW_OK;
}

/**
 * \brief 获取A相电压（07年版本）
 * \param[in]  handle   : 指向电表的实例
 * \param[in]  phase    : 获取的相，0-A相，1-B相，2-C相
 * \param[out] p_vol    : 指向存放压的变量，单位0.1V
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dl645_07_vol_get(struct aw_ammeter* handle,
                                       uint8_t            phase,
                                       uint32_t          *p_vol)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[7] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_07_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_07_DATAID_A_VOL ;
    buf[2] = (uint8_t)(__DL645_07_DATAID_A_VOL >> 8) + phase;
    buf[3] = (uint8_t)(__DL645_07_DATAID_A_VOL >> 16);
    buf[4] = (uint8_t)(__DL645_07_DATAID_A_VOL >> 24);
    /* 发送请求 */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    5)) {
        return  AW_ERROR;
    }
    /* 读取数据 */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_vol) {
        *p_vol =   (AW_BCD_TO_HEX(buf[5]) * 100)     +
                   (AW_BCD_TO_HEX(buf[4]) );
    }
    return AW_OK;
}

/**
 * \brief 获取瞬时功率（07年版本）
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_power  : 指向存放功率的变量，单位kW
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dl645_07_power_get(struct aw_ammeter* handle,
                                       uint32_t          *p_power)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[8] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_07_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_07_DATAID_POWER ;
    buf[2] = (uint8_t)(__DL645_07_DATAID_POWER >> 8);
    buf[3] = (uint8_t)(__DL645_07_DATAID_POWER >> 16);
    buf[4] = (uint8_t)(__DL645_07_DATAID_POWER >> 24);
    /* 发送请求 */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    5)) {
        return  AW_ERROR;
    }
    /* 读取数据 */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_power) {
        *p_power = (AW_BCD_TO_HEX(buf[6]) * 10000) +
                   (AW_BCD_TO_HEX(buf[5]) * 100)     +
                   (AW_BCD_TO_HEX(buf[4]) );
    }
    return AW_OK;
}

#if __DL645_97_SUPPORT
/**
 * \brief 获取A相电流(97年版本)
 * \param[in]  handle   : 指向电表的实例
 * \param[in]  phase    : 获取的相，0-A相，1-B相，2-C相
 * \param[out] p_curr   : 指向存放电流的变量，单位0.01A
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dl645_97_current_get(struct aw_ammeter* handle,
                                           uint8_t            phase,
                                           uint32_t          *p_curr)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[5] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_97_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_97_DATAID_A_CURR + phase;
    buf[2] = (uint8_t)(__DL645_97_DATAID_A_CURR >> 8);
    /* 发送请求 */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    3)) {
        return  AW_ERROR;
    }
    /* 读取数据 */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_curr) {
        *p_curr = (AW_BCD_TO_HEX(buf[3]) * 100)     +
                  (AW_BCD_TO_HEX(buf[2]) );
    }
    return AW_OK;
}

/**
 * \brief 获取A相电压（97年版本）
 * \param[in]  handle   : 指向电表的实例
 * \param[in]  phase    : 获取的相，0-A相，1-B相，2-C相
 * \param[out] p_vol    : 指向存放压的变量，单位V
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dl645_97_vol_get(struct aw_ammeter* handle,
                                     uint8_t            phase,
                                     uint32_t          *p_vol)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[5] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_97_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_97_DATAID_A_VOL + phase;
    buf[2] = (uint8_t)(__DL645_97_DATAID_A_VOL >> 8);
    /* 发送请求 */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    3)) {
        return  AW_ERROR;
    }
    /* 等待响应 */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_vol) {
        *p_vol =   (AW_BCD_TO_HEX(buf[3]) * 100)     +
                   (AW_BCD_TO_HEX(buf[2]) );
    }
    return AW_OK;
}

/**
 * \brief 获取瞬时功率（97年版本）
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_power  : 指向存放功率的变量，单位kW
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dl645_97_power_get(struct aw_ammeter* handle,
                                       uint32_t          *p_power)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[6] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t)__DL645_97_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_97_DATAID_POWER ;
    buf[2] = (uint8_t)(__DL645_97_DATAID_POWER >> 8);
    /* 发送请求 */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    3)) {
        return  AW_ERROR;
    }
    /* 读取数据 */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_power) {
        *p_power = (AW_BCD_TO_HEX(buf[4]) * 10000) +
                   (AW_BCD_TO_HEX(buf[3]) * 100)     +
                   (AW_BCD_TO_HEX(buf[2]) );
    }
    return AW_OK;
}
#endif

/**
 * \brief DL645协议通信实例初始化
 * \param[in]  handle  : 指向电表的实例
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_transfer_dl645_inst_init (aw_ammeter_transfer_t* handle)
{
    __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle);
    uint32_t uart_num;
    
    if (NULL == p_ammeter_transfer_dl645) {
        return -AW_EINVAL;
    }
    uart_num = p_ammeter_transfer_dl645->uart_num;
    aw_ammeter_transfer_inst_init(&(p_ammeter_transfer_dl645->super));
    
    p_ammeter_transfer_dl645->super.pfn_send    = __dl645_send;
    p_ammeter_transfer_dl645->super.pfn_receive = __dl645_receive;
    
    /* 串口初始化配置, 如波特率 115200 */
    aw_serial_ioctl(uart_num,
                    SIO_BAUD_SET, 
                   (void *)(p_ammeter_transfer_dl645->uart_buad));
    /* 串口参数 如：8 个数据位 1 个停止位，无奇偶校验 */
    aw_serial_ioctl(uart_num,
                    SIO_HW_OPTS_SET,
                    (void *)(p_ammeter_transfer_dl645->uart_format));

    /* 设置读取超时时间 */
    aw_serial_ioctl(uart_num, AW_TIOCRDTIMEOUT, (void *)__DL645_RX_BYTE_TIMEOUT_CFG);


    /* 设置是否使能RS485 */
    aw_serial_ioctl(uart_num, AM_UART_RS485_ENABLE_SET, (void *)(
            (p_ammeter_transfer_dl645->rs485_en ? RS485_ENABLE:RS485_DISABLE)));

    return AW_OK;
}

#endif

#if __MODBUS_SUPPORT

/**
 * \brief 获取当前正向有功电能，单位0.01 KWh (modbus协议实现获取)
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_energy : 指向存放电量的变量
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dc_md_active_energy_get(struct aw_ammeter* handle,
                                            uint32_t          *p_energy)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, p_ammeter_dc->p_transfer);
    aw_mb_err_t err     = AW_MB_ERR_NOERR;
    uint16_t    rbuf[2];

    /* 读保持寄存器---从地址1000开始，读取20个保持寄存器，读取数据放入rd_buf缓冲区 */
    err = aw_mb_holding_reg_read(p_ammeter_transfer_mb->master,
                                 p_ammeter_dc->p_transfer->p_addr[0],
                                 0x2000,
                                 2,
                                 rbuf);
    if (err != AW_MB_ERR_NOERR) {
        return AW_ERROR;
    }
//    p_ammeter_dc->super.power = (AW_BCD_TO_HEX((rbuf[1] & 0xFF00) >> 8) * 1000000) +
//                                (AW_BCD_TO_HEX( rbuf[1] & 0xFF) * 10000) +
//                                (AW_BCD_TO_HEX((rbuf[0] & 0xFF00) >> 8) * 100) +
//                                (AW_BCD_TO_HEX( rbuf[0] & 0xFF) );
    p_ammeter_dc->super.power = ((rbuf[0] & 0xFFFF) << 16) | (rbuf[1] & 0xFFFF);
    if (NULL != p_energy) {
        *p_energy = p_ammeter_dc->super.power;
    }
    return AW_OK;
}

/**
 * \brief 获取当前电压，单位0.01V (modbus协议实现获取)
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_vol    : 指向存放电压的变量
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dc_md_voltage_get(struct aw_ammeter* handle,
                                      int32_t           *p_vol)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, p_ammeter_dc->p_transfer);
    aw_mb_err_t err     = AW_MB_ERR_NOERR;
    uint16_t    rbuf[2];

    /* 读保持寄存器---从地址1000开始，读取20个保持寄存器，读取数据放入rd_buf缓冲区 */
    err = aw_mb_holding_reg_read(p_ammeter_transfer_mb->master,
                                 p_ammeter_dc->p_transfer->p_addr[0],
                                 0x1000,
                                 2,
                                 rbuf);
    if (err != AW_MB_ERR_NOERR) {
        return AW_ERROR;
    }

    if (NULL != p_vol) {
        *p_vol = ((rbuf[0] & 0xFFFF) << 16) | (rbuf[1] & 0xFFFF);
    }
    return AW_OK;
}

/**
 * \brief 主站接收线程
 */
aw_local void __aw_ammeter_task_modbus_poll (aw_mb_master_t master)
{
    aw_mb_err_t    err = AW_MB_ERR_NOERR;

    AW_INFOF(("[Ammeter] Modbus Master: Poll Task Startup!\n"));
    AW_FOREVER {
        err = aw_mb_master_poll(master);
        if (err != AW_MB_ERR_NOERR) {
            AW_ERRF(("Modbus Master Poll Failed, err: %d!\r\n", err));
        }
        aw_mdelay(1000);
    }
}

/**
 * \brief 电表modbus协议通信实例初始化
 * \param[in]  handle  : 指向电表的实例
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 * \return  AW_ERROR   : 初始化失败
 */
aw_err_t aw_ammeter_transfer_mb_inst_init (aw_ammeter_transfer_t* handle)
{
    __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, handle);
    aw_mb_master_t  master;
    aw_mb_err_t     err = AW_MB_ERR_NOERR;
    aw_task_id_t    tid ;

    if ((NULL == p_ammeter_transfer_mb) ||
        (NULL == p_ammeter_transfer_mb->p_ser_params)) {
        return -AW_EINVAL;
    }
    aw_ammeter_transfer_inst_init(&(p_ammeter_transfer_mb->super));

    master = aw_mb_master_create();
    if (master == NULL) {
        AW_ERRF(("Modbus Master Create Failed\r\n"));
        return AW_ERROR;
    }
    /* 主站配置为RTU模式，配置串口信息 */
    err = aw_mb_master_config(master, AW_MB_RTU, p_ammeter_transfer_mb->p_ser_params);
    if (err != AW_MB_ERR_NOERR) {
        AW_ERRF(("Modbus Master Config Failed, err: %d!\r\n", err));
        aw_mb_master_delete(master);  /* 配置失败，删除主站 */
        return AW_ERROR;
    }
    /* 启动主站  */
    err = aw_mb_master_start(master);
    if (err != AW_MB_ERR_NOERR) {
        AW_ERRF(("Modbus Master Start Failed, err: %d\r\n", err));
        return AW_ERROR;
    }
    tid = aw_task_create("task_modbus_poll",              /* 任务名字 */
                          26,                             /* 任务优先级 */
                          1024,                           /* 任务堆栈大小 */
                          __aw_ammeter_task_modbus_poll,  /* 任务入口函数 */
                          (void *)master);                /* 任务入口参数 */

    p_ammeter_transfer_mb->master = master;
    p_ammeter_transfer_mb->tid    = tid;
    return aw_task_startup(tid);
}
#endif

/**
 * \brief 获取当前电量，单位0.01 KWh
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_energy : 指向存放电量的变量
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dc_active_energy_get(struct aw_ammeter* handle,
                                         uint32_t          *p_energy)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);

    if ((NULL != p_ammeter_dc) &&
        (NULL != p_ammeter_dc->p_transfer)) {
        switch (p_ammeter_dc->p_transfer->protocol) {
#if __MODBUS_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU:
            return __dc_md_active_energy_get(handle, p_energy);
#endif

#if __DL645_07_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
            return __dl645_07_active_energy_get(handle, p_energy);
#endif

#if __DL645_97_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
            return __dl645_97_active_energy_get(handle, p_energy);
#endif

        default:
            break;
        }
    }
    return -AW_EINVAL;
}

/**
 * \brief 获取A相电流
 * \param[in]  handle   : 指向电表的实例
 * \param[in]  phase    : 获取的相，0-A相，1-B相，2-C相
 * \param[out] p_curr   : 指向存放电流的变量
 *                        对于07年版本，单位为0.001A
 *                        对于97年版本，单位为0.01A
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dc_current_get(struct aw_ammeter* handle,
                                     uint8_t            phase,
                                     uint32_t          *p_curr)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);

    if ((NULL != p_ammeter_dc) &&
        (NULL != p_ammeter_dc->p_transfer)) {
        switch (p_ammeter_dc->p_transfer->protocol) {
#if __MODBUS_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU:
            break;
#endif

#if __DL645_07_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
            return __dl645_07_current_get(handle, phase, p_curr);
#endif

#if __DL645_97_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
            return __dl645_97_current_get(handle, p_curr);
#endif

        default:
            break;
        }
    }
    return -AW_EINVAL;
}

/**
 * \brief 获取A相电压（07年版本）
 * \param[in]  handle   : 指向电表的实例
 * \param[in]  phase    : 获取的相，0-A相，1-B相，2-C相
 * \param[out] p_vol    : 指向存放压的变量
 * *                      对于07年版本，单位为0.1V
 *                        对于97年版本，单位为V
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_local aw_err_t __dc_vol_get(struct aw_ammeter* handle,
                               uint8_t            phase,
                               uint32_t          *p_vol)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);

    if ((NULL != p_ammeter_dc) &&
        (NULL != p_ammeter_dc->p_transfer)) {
        switch (p_ammeter_dc->p_transfer->protocol) {
#if __MODBUS_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU:
            break;
#endif

#if __DL645_07_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
            return __dl645_07_vol_get(handle, phase, p_vol);
#endif

#if __DL645_97_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
            return __dl645_97_vol_get(handle, phase, p_vol);
            break;
#endif

        default:
            break;
        }
    }
    return -AW_EINVAL;
}


/**
 * \brief 通信实例初始化
 * \param[in]  handle  : 指向电表的指针
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_transfer_inst_init (aw_ammeter_transfer_t* handle)
{
    if (NULL == handle) {
        return -AW_EINVAL;
    }
    handle->pfn_send    = NULL;
    handle->pfn_receive = NULL;
    return AW_OK;
}


/**
 * \brief 按照一定通信格式初始化对应通信对象
 * \param[in]  handle  : 指向电表的实例
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 * \return -AW_ENOTSUP : 协议不支持
 */
aw_local aw_err_t __ammeter_transfer_factory (aw_ammeter_transfer_t* handle)
{
    if (NULL == handle) {
        return -AW_EINVAL;
    }
    
    switch (handle->protocol) {
    
#if __DL645_07_SUPPORT || __DL645_97_SUPPORT
    case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
    case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
        return aw_ammeter_transfer_dl645_inst_init(handle);
#endif
        
#if __MODBUS_SUPPORT
    case AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU:
        return aw_ammeter_transfer_mb_inst_init(handle);
#endif
        
    default:break;
    }
    
    return -AW_ENOTSUP;
}

/**
 * \brief 电表初始化
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_inst_init (aw_ammeter_t* handle)
{
    if (NULL == handle) {
        return -AW_EINVAL;
    }
    handle->energy                = 0;
    handle->pfn_active_energy_get = NULL;
    return AW_OK;
}

/**
 * \brief 直流电表初始化
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_dc_inst_init (aw_ammeter_t* handle)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    
    if (NULL == p_ammeter_dc) {
        return -AW_EINVAL;
    }
    aw_ammeter_inst_init(&(p_ammeter_dc->super));
    
    p_ammeter_dc->super.pfn_active_energy_get = __dc_active_energy_get;
    /* 初始化对应的通信实例信息 */
    return  __ammeter_transfer_factory(p_ammeter_dc->p_transfer);
}

/**
 * \brief 直流电表去初始化
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_dc_inst_deinit (aw_ammeter_t* handle)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, NULL);

    if ((NULL == p_ammeter_dc) ||
        (NULL == p_ammeter_dc->p_transfer)) {
        return -AW_EINVAL;
    }
#if __MODBUS_SUPPORT
    /* 如果使用modbus协议，删除线程资源 */
    if (p_ammeter_dc->p_transfer->protocol ==  AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU) {

        p_ammeter_transfer_mb = (aw_ammeter_transfer_mb_t *)(p_ammeter_dc->p_transfer);
        aw_task_terminate(p_ammeter_transfer_mb->tid);
    }
#endif
    /* 初始化对应的通信实例信息 */
    return  AW_OK;
}



/**
 * \brief 获取当前电量，单位0.01 KWh
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_energy : 指向存放电量的变量
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 *
 * \note 建议如果读取失败（如电表通信失败则在1s内返回），建议重试3次.测试发现电表有时候并不能及时作出回应.
 */
aw_err_t aw_ammeter_active_energy_get(struct aw_ammeter* handle, uint32_t *p_energy)
{
    if ((NULL == handle) ||
        (NULL == handle->pfn_active_energy_get)) {
        return -AW_EINVAL;
    }
    return  handle->pfn_active_energy_get(handle, p_energy);
}


/**
 * \brief 获取电压，单位0.1V
 * \param[in]  handle  : 指向电表的实例
 * \param[in]  phase    : 获取的相，0-A相，1-B相，2-C相
 * \param[out] p_vol   : 指向存放电量的变量
 *
 * \return AW_OK       : 获取成功
 * \return AW_ERROR    : 获取失败
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_ammeter_voltage_get(struct aw_ammeter* handle,
                                uint8_t            phase,
                                int32_t           *p_vol)
{
    return  __dc_vol_get(handle, phase,  p_vol);
}


/**
 * \brief 获取A相电流
 * \param[in]  handle  : 指向电表的实例
 * \param[in]  phase    : 获取的相，0-A相，1-B相，2-C相
 * \param[out] p_curr  : 指向存放电流的变量
 *                        对于07年版本，单位为0.001A
 *                        对于97年版本，单位为0.01A
 *
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_err_t aw_ammeter_current_get(struct aw_ammeter* handle,
                                uint8_t            phase,
                                uint32_t          *p_curr)
{
    return  __dc_current_get(handle, phase, p_curr);
}


/**
 * \brief 获取功率
 * \param[in]  handle   : 指向电表的实例
 * \param[out] p_power    : 指向存放压的变量，单位kW
 * \return AW_OK    : 获取成功
 * \return AW_ERROR : 获取失败
 */
aw_err_t aw_ammeter_power_get(struct aw_ammeter* handle, uint32_t *p_power)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);

    if ((NULL != p_ammeter_dc) &&
        (NULL != p_ammeter_dc->p_transfer)) {
        switch (p_ammeter_dc->p_transfer->protocol) {

#if __DL645_07_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
            return __dl645_07_power_get(handle, p_power);
#endif

#if __DL645_97_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
            return __dl645_97_power_get(handle, p_power);
            break;
#endif

        default:
            break;
        }
    }
    return -AW_EINVAL;
}
