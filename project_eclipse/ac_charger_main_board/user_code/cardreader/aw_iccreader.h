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
 * \brief  读卡器（国网规范）声明头文件
 *
 * \internal
 * \par modification history:
 * - 1.00 16-06-22  xjc, first implementation
 * \endinternal
 */
#include "apollo.h"

#ifndef __AW_ICCREADER_H
#define __AW_ICCREADER_H

#define AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYA   (0x60u) /**< \brief 密钥A */
#define AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYB   (0x61u) /**< \brief 密钥B */

typedef struct aw_iccreader_info {
    uint8_t cpu_interface[8];  /**< 由银联定义的读卡器规范版本信息*/
    uint8_t acq_interface[8];  /**< 由受理方定义的版本信息 */
    uint8_t manu_len;          /**< 厂商自定义数据信息长度 */
    uint8_t manu_info[50];     /**< 厂家自定义信息 */
    uint8_t reserv[2];         /**< 保留 */
}aw_iccreader_info_t;


typedef struct aw_iccreader_s50s70_ci {
    uint8_t key_type;    /**< 卡类型 */
    uint8_t uid_len;     /**< 卡UID长度 */
    uint8_t uid[4];      /**< 卡UID */
}aw_iccreader_s50s70_ci_t;


/** 
 *  \brief 通信传输信息配置
 */
typedef struct aw_iccreader_transfer {
    uint32_t              uart_num;    /**< \brief 通信时使用的串口号 */
    uint32_t              uart_buad;   /**< \brief 通信速率 */
    uint32_t              uart_format; /**< \brief 串口通信格式 */
    bool_t                rs485_en;    /**< \brief RS485使能 */
}aw_iccreader_transfer_t;

/**
 *  \brief 读卡器
 */
typedef struct aw_iccreader {
    const aw_iccreader_transfer_t *p_transfer;    /**< \brief 传输信息配置 */
    /** 
     * \brief 发送数据
     * \param [in] handle  : 读卡器的实例
     * \param [in] p_txbuf : 发送数据缓冲区
     * \param [in] nbytes  : 发送字节数
     * \return 错误码： 返回AW_OK时，表示通信成功。
     */
    aw_err_t (*pfn_send)(struct aw_iccreader* handle,
                         const uint8_t       *p_txbuf,
                         uint32_t             nbytes);
    /** 
     * \brief 接收数据
     * \param [in] handle  : 读卡器的实例
     * \param [in] p_rxbuf : 接收数据缓冲区
     * \param [in] nbytes  : 接收字节数
     * \return 错误码： 返回AW_OK时，表示通信成功。
     */
    int (*pfn_receive)(struct aw_iccreader* handle,
                       uint8_t             *p_rxbuf,
                       uint32_t              nbytes);
}aw_iccreader_t;

/**
 * CPU卡片上电复位回应信息
 */
typedef struct aw_iccreader_samc_info {
    uint8_t   ptl;         /**< PTL */
    uint8_t  atr[50];      /**< ATR不定长 */
    uint16_t status;       /**<  状态信息 */
}aw_iccreader_samc_info_t;

/**
 * \brief IC卡读卡器实例初始化
 * \return AW_OK       : 初始化成功
 * \return -AW_EINVAL  : 参数错误
 */
aw_err_t aw_iccreader_inst_init (struct aw_iccreader           *handle,
                                 const aw_iccreader_transfer_t *p_transfer);


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
 */
aw_err_t aw_iccreader_transfer(struct aw_iccreader* handle,
                               uint32_t  cmd,
                               void     *p_txbuf,
                               uint16_t  tlen,
                               void     *p_rxbuf,
                               uint16_t  rlen);


aw_err_t aw_iccreader_block_read (struct aw_iccreader *handle,
                                  uint8_t          *p_buf,
                                  uint8_t           block);

aw_err_t aw_iccreader_block_write (struct aw_iccreader *handle,
                                   uint8_t          *p_buf,
                                   uint8_t           block);

aw_err_t aw_iccreader_key_auth (struct aw_iccreader* handle,
                                uint8_t              key_type,
                                uint8_t             *p_uid,
                                uint8_t              uid_len,
                                uint8_t             *p_key,
                                uint8_t              key_len,
                                uint8_t              block);

aw_err_t aw_iccreader_rf_close (struct aw_iccreader* handle);

aw_err_t aw_iccreader_rf_open (struct aw_iccreader* handle);

aw_err_t aw_iccreader_led_set (struct aw_iccreader* handle, bool_t led1_en, bool_t led2_en);
aw_err_t aw_iccreader_buzzer_set (struct aw_iccreader* handle, uint16_t dlytime, uint8_t times);
aw_err_t aw_iccreader_baud_set (struct aw_iccreader* handle, uint8_t baud_code);
aw_err_t aw_iccreader_info_get (struct aw_iccreader* handle, void *p_rxbuf, uint32_t rlen);

aw_err_t aw_iccreader_s50s70_active (struct aw_iccreader      *handle,
                                     aw_iccreader_s50s70_ci_t *p_card);

aw_err_t aw_iccreader_halt(struct aw_iccreader *handle);

aw_err_t aw_iccreader_samc_power_on(struct aw_iccreader *handle,
                                    uint8_t card_no,
                                    uint16_t dly_time,
                                    aw_iccreader_samc_info_t *p_info);

aw_err_t aw_iccreader_samc_power_off(struct aw_iccreader *handle,
                                    uint8_t               card_no);
#endif
