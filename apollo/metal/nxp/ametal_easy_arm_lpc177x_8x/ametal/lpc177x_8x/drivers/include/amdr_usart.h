
/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USART驱动，服务USART标准接口
 *
 * \internal
 * \par Modification History
 * - 1.01 15-06-13  sam, first implementation.
 * \endinternal
 */

#ifndef __AMDR_USART_H
#define __AMDR_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"	
#include "amhw_usart.h"		

/**
 * \addtogroup amdr_if_usart
 * \copydoc amdr_usart.h
 * @{
 */	
	
/**
 *  命名相关错误码的错误回调函数
 *  错误回调函数模型 :
    
 *  int uart_err (void *p_arg, int code, void *p_data, int size);
    
 *  能够调用 am_uart_callback_set() 安装错误回调函数
 * @{
 */
 
/** 
 * \brief 对于其他中断, p_data 的数据类型是 "uint32_t",
 *        值为 USART 中断状态,大小为 1.
 */ 
#define AMDR_UART_ERRCODE_USART_OTHER_INT 2

/** @} */

/**
 * \brief LPC17XX UART设备信息
 */	
typedef struct amdr_usart_devinfo {
  
    amhw_usart_t *p_hw_usart;       /**< \brief 指向UART寄存器块的指针 */
    
    uint8_t      inum;              /**< \brief USART 控制器的中断号     */
    uint32_t     cfg_flags;         /**< \brief 配置标志                                    */
    uint32_t     ctl_flags;         /**< \brief 控制标志                                    */
    uint32_t     baud_rate;         /**< \brief 波特率设置                                */
    uint32_t     fifo_level;        /**< \brief 接收FIFO级别                           */
    uint8_t      fifo_size;         /**< \brief 发送FIFO大小                          */

    uint8_t      rs485_ctrl;        /**< \brief RS485配置信息，参见
                                        \ref grp_amhw_usart_rs485_ctrl_flags */
    uint8_t      rs485_dly;         /**< \brief RS485延时值，值为0~255  */

    void (*pfunc_rs485_gpio_dir_set) (uint8_t dir);

    /** \brief 硬件流控配置信息（仅串口1有效）， 为0表示不支持 */
    uint8_t      flowctrl_flags;

    /**
     * \brief  USART 其他中断使能,例如值为 AMHW_USART_INT_*         
     */
    uint32_t other_int_enable;
	
} amdr_usart_devinfo_t;

/**
 * \brief LPC17XX USART 设备
 */
typedef struct amdr_usart_dev {

    am_uart_serv_t  uart_serv;                  /**< \brief USART标准服务 */
 
    int (*pfn_txchar_get)(void *, char *);      /**< \brief 发送函数指针      */
    int (*pfn_rxchar_put)(void *, char);        /**< \brief 接收函数指针       */
    int (*pfn_err)(void *, int, void *, int);   /**< \brief 错误函数指针        */

    void     *txget_arg;                        /**< \brief 发送函数参数指针    */
    void     *rxput_arg;                        /**< \brief 接收函数参数指针     */
    void     *err_arg;                          /**< \brief 错误函数参数指针    */
    
    uint8_t   channel_mode;                     /**< \brief 例如中断，轮询模式    */
    uint32_t  baud_rate;                        /**< \brief 波特率                  */
    uint16_t  options;                          /**< \brief 硬件设置选择    */
    
    uint32_t  other_int_enable;                 /**< \brief 其他特殊中断使能 */

	uint8_t   rs485_enable;                     /**< \brief RS485使能           */

	uint8_t   rs485_txing;                      /**< \brief RS485正在发送标志       */

	uint8_t   flowctrl_mode;                    /**< \brief 流控制模式 ，仅UART1有效  */

    /** \brief 指向设备信息指针 */
    const amdr_usart_devinfo_t *p_devinfo;
	
} amdr_usart_dev_t;

/**
 * \brief USART初始化
 *
 * \param[in] p_dev     : 指向USART设备的指针
 * \param[in] p_devinfo : 指向USART设备信息的指针 
 *
 * \return 标准USART接口服务.如为NULL，则初始化失败
 */
am_uart_handle_t amdr_usart_init(amdr_usart_dev_t           *p_dev,
                                 const amdr_usart_devinfo_t *p_devinfo);

/**
 * \brief USART 解初始化
 * \param[in] p_dev : 指向USART设备的指针
 * \return None
 */
void amdr_usart_deinit(amdr_usart_dev_t *p_dev);

/** 
 * @} 
 */
#ifdef __cplusplus
}
#endif

#endif    /* __AMDR_USART_H */

/* end of file */

