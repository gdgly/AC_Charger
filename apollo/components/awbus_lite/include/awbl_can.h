/*******************************************************************************
*                                 Apollo
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
 * \internal
 * \par modification history:
 * - 1.02 15-11-16  cae, first implementation
 * \endinternal
 */
#ifndef __AWBL_CAN_H
#define __AWBL_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_can.h"
#include "aw_msgq.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "aw_list.h"

/** \brief can Interrupt status */
#define AWBL_CAN_INT_NONE                 0x00  /** \brief 无错误                 */
#define AWBL_CAN_INT_TX                   0x01  /** \brief 发送成功 中断*/
#define AWBL_CAN_INT_RX                   0x02  /** \brief 接收 中断          */
#define AWBL_CAN_INT_WAKE_UP              0x04  /** \brief 唤醒中断           */
#define AWBL_CAN_INT_ERROR                0x08  /** \brief 错误中断           */
#define AWBL_CAN_INT_DATAOVER             0x10  /** \brief 总线超载 中断*/
#define AWBL_CAN_INT_WARN                 0x20  /** \brief 错误报警 中断*/
#define AWBL_CAN_INT_ERROR_PASSIVE        0x40  /** \brief 错误被动中断 */
#define AWBL_CAN_INT_BUS_OFF              0x80  /** \brief 总线关闭中断 */
#define AWBL_CAN_INT_STATUS               0xf8
#define AWBL_CAN_INT_ALL                  0xffffffff
typedef uint32_t awbl_can_int_type_t;

#define AWBL_CAN_CHN_INIT                 0x00  /** \brief 无错误                 */
#define AWBL_CAN_CHN_START                0x01  /** \brief 错误中断           */
#define AWBL_CAN_CHN_STOP                 0x02  /** \brief 总线关闭中断 */

typedef struct awbl_can_drv_funcs {
    /** \brief 初始化相关函数 */
    aw_can_err_t (*pfn_can_init)  (void *, uint8_t);

    /** \brief CAN启动 */
    aw_can_err_t (*pfn_can_start) (void *);
    
    /** \brief CAN复位（停止） */
    aw_can_err_t (*pfn_can_reset) (void *);
    
    /** \brief CAN休眠 */
    aw_can_err_t (*pfn_can_sleep) (void *);

    /** \brief CAN唤醒 */
    aw_can_err_t (*pfn_can_wakeup)(void *);

    /** \brief 中断使能 、禁能 */
    aw_can_err_t (*pfn_can_int_enable)  (void *, awbl_can_int_type_t);
    aw_can_err_t (*pfn_can_int_disable) (void *, awbl_can_int_type_t);

    /** \brief 波特率设置 */
    aw_can_err_t (*pfn_can_baud_set) (void *, aw_can_baud_param_t*);

    /** \brief 波特率设置 */
    aw_can_err_t (*pfn_can_baud_get) (void *, aw_can_baud_param_t*);

    /** \brief 获取错误计数 */
    aw_can_err_t (*pfn_can_err_cnt_get) (void *, aw_can_err_cnt_t*);
    
    /** \brief 清除错误计数 */
    aw_can_err_t (*pfn_can_err_cnt_clr) (void *);

    /** \brief CAN收发相关函数 */
    aw_can_err_t (*pfn_can_reg_msg_read)  (void *, aw_can_msg_t*);
    aw_can_err_t (*pfn_can_reg_msg_write) (void *, aw_can_msg_t*);
    aw_can_err_t (*pfn_can_msg_snd_stop)  (void *);

    /** \brief 验收滤波相关函数 */
    aw_can_err_t (*pfn_can_filter_table_set) (void *, uint8_t*, size_t);
    aw_can_err_t (*pfn_can_filter_table_get) (void *, uint8_t*, size_t*);

    /** \brief CAN bus相关状态获取 */
    aw_can_err_t (*pfn_can_int_status_get) (void *, awbl_can_int_type_t*,
                                                    aw_can_bus_err_t*);

    /** \brief 操作寄存器函数接口，特殊的CAN控制器用到 */
    aw_can_err_t (*pfn_can_reg_write) (void *, uint32_t,uint8_t*, size_t);
    aw_can_err_t (*pfn_can_reg_read ) (void *, uint32_t,uint8_t*, size_t);

} awbl_can_drv_funcs_t;

/** \brief 锁定控制器 */
#define AWBL_CAN_CONTROLLER_LOCK(p_serv) \
    aw_spinlock_isr_take(&((struct awbl_can_service *)p_serv)->lock_dev)

/** \brief 解除控制器锁定 */
#define AWBL_CAN_CONTROLLER_UNLOCK(p_serv) \
    aw_spinlock_isr_give(&((struct awbl_can_service *)p_serv)->lock_dev)

typedef struct awbl_can_servinfo {
    int                chn;              /** \brief 当前通道号     */
    uint8_t            ctr_type;         /** \brief 当前控制器类型 */
    uint8_t            sizeof_msg;       /** \brief 当前报文长度   */
    uint32_t           rxd_buf_size;     /** \brief 接收报文缓冲区大小*/
    void              *p_rxd_buf;        /** \brief 接收报文缓冲区指针*/
    struct aw_rngbuf  *p_rxd_buf_ctr;    /** \brief 接收报文缓冲区控制字*/

}awbl_can_servinfo_t;

/**
 * \brief AWBus CAN 服务实例
 */
typedef struct awbl_can_service {

    /** \brief 指向下一个 CAN 服务 */
    struct awbl_can_service *p_next;

    /** \brief CAN 服务的相关信息 */
    awbl_can_servinfo_t     *p_info;

    /** \brief 通道状态    */
    uint8_t  chn_status;

    /** \brief 发送繁忙标志   */
    uint8_t  txd_busy;

    /** \brief 设备锁 */
    aw_spinlock_isr_t lock_dev;

    /** \brief 设备互斥量 */
    AW_MUTEX_DECL(dev_mux);

    /**< \brief 接收信号量 */
    AW_SEMB_DECL(rcv_start_sem);

    /** \brief CAN 控制器消息队列 */
    struct aw_list_head transfer_list;

    /** \brief 当前发送的消息*/
    aw_can_transfer_t *p_curr_trans;

    /** \brief CAN服务的相关函数 */
    awbl_can_drv_funcs_t *p_servfuncs;

    /** \brief 用户APP回调函数 */
    aw_can_app_callbacks_t *p_app_cb_funcs;

    void *p_cookie;

} awbl_can_service_t;

/** \brief 服务初始化函数 */
aw_err_t awbl_can_service_init (awbl_can_service_t    *p_serv,
                                awbl_can_servinfo_t   *p_servinfo,
                                awbl_can_drv_funcs_t  *p_servfuncs);
/** \brief CAN服务注册 */
aw_err_t awbl_can_service_register (awbl_can_service_t *p_serv);

/** \brief 中断服务函数 */
void awbl_can_isr_handler (awbl_can_service_t *p_serv);

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_CAN_H */

