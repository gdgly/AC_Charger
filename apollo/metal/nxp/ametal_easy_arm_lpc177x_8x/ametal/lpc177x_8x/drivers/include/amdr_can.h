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
 * \brief  CAN驱动层实现
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-06-02  anu, first implementation.
 * \endinternal
 */
 

#ifndef __AMDR_CAN_H
#define __AMDR_CAN_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "am_types.h"
#include "am_can.h"
#include "amhw_can.h"

/**
 * \addtogroup amdr_if_can
 * \copydoc amdr_can.h
 * @{
 */

/**
 * \name 设置滤波操作
 * \anchor grp_amdr_canaf_act
 * @{
 */

#define AMDR_CANAF_ACT_OPERATE   0x00         /**< \brief 进入验收滤波模式 */
#define AMDR_CANAF_ACT_BYPASS    0x01         /**< \brief 进入旁路模式 */
#define AMDR_CANAF_ACT_ADD       0x02         /**< \brief 增加滤波记录 */
#define AMDR_CANAF_ACT_DEL       0x03         /**< \brief 删除所有滤波记录 */

/** @} */

/**
 * \name 验收滤波的类型
 * \anchor grp_amdr_canaf_ram_type
 * @{
 */

typedef uint32_t amdr_canaf_rec_type_t;        /**< \brief 验收滤波的类型 */
#define AMDR_CANAF_REC_TYPE_SSF   0x00         /**< \brief 单个标准帧验收滤波记录 */
#define AMDR_CANAF_REC_TYPE_GSF   0x01         /**< \brief 标准帧组验收滤波记录 */
#define AMDR_CANAF_REC_TYPE_SEF   0x02         /**< \brief 单个扩展帧验收滤波记录 */
#define AMDR_CANAF_REC_TYPE_GEF   0x03         /**< \brief 扩展帧组验收滤波记录 */
#define AMDR_CANAF_REC_TYPE_NONE  0XFF         /**< \brief 无设置验收滤波类型 */

/** @} */

/** \brief CAN公共部分中断服务例行信息 */
typedef struct amdr_can_comm_isr_info {

    /** \brief 触发回调函数 */
    am_pfnvoid_t  pfn_isr;

    /** \brief 回调函数的参数 */
    void         *p_arg;

} amdr_can_comm_isr_info_t;

/**
 * \brief CAN 公共部分设备信息
 */
typedef struct amdr_can_comm_devinfo {

    amhw_canaf_ram_t        *p_hw_canaf_ram;        /**< \brief CAN 滤波器RAM 基址 */
    amhw_canaf_t            *p_hw_canaf;            /**< \brief CAN 滤波器基址     */
    amhw_cancr_t            *p_hw_cancr;            /**< \brief CAN 中心控制寄存器基址 */

    /** \brief 中断号 */
    int inum;

    /** \brief ISR 信息数量 即CAN设备的数量 */
    int isrinfo_cnt;

    /** \brief ISR 信息映射内存(大小与 isrinfo_cnt 一致) */
    amdr_can_comm_isr_info_t *p_isrinfo;

} amdr_can_comm_devinfo_t;

/**
 * \brief CAN公共部分设备实例
 */
typedef struct amdr_can_comm_dev {

    /** \brief 指向中断设备信息的指针 */
    const amdr_can_comm_devinfo_t *p_devinfo;

    /** \brief CAN 滤波类型  */
    amdr_canaf_rec_type_t          filter_type;

} amdr_can_comm_dev_t;

/**
 * \brief 中断回调信息 
 */
typedef struct amdr_can_intcb_info {

    /** \brief 触发回调函数   */
    am_pfnvoid_t  pfn_callback;

    /** \brief 回调函数的参数 */
    void         *p_arg;
	
} amdr_can_intcb_info_t;

/**
 * \brief CAN 设备信息 
 */
typedef struct amdr_can_devinfo {

    amhw_can_t              *p_hw_can;              /**< \brief CAN 寄存器基址        */
    amdr_can_intcb_info_t   *p_intcb_info;          /**< \brief CAN 中断回调 */	
    int                      can_id;              	/**< \brief CAN 的ID号(从0开始)*/

} amdr_can_devinfo_t;


/**
 * \brief 设备
 */
typedef struct amdr_can_dev {

     /** \brief CAN 标准服务 */
    am_can_serv_t              handle;
    
    /** \brief CAN 设备信息  */
    const amdr_can_devinfo_t  *p_devinfo;

    /** \brief CAN 记录发送类型  */
    uint8_t                    send_type;

    /** \brief CAN 记录发送命令  */
    uint32_t                   send_cmd;

} amdr_can_dev_t;

/**
 * \brief  CAN公共部分初始化
 *
 * \param[in] p_dev     : 设备实例
 * \param[in] p_devinfo : 设备信息
 *
 * \retval AM_OK      ：成功
 * \retval -AM_EINVAL ：参数错误
 * \retval -AM_EPERM  ：没有空的内存映射
 */
int amdr_can_comm_init (amdr_can_comm_dev_t           *p_dev,
                        const amdr_can_comm_devinfo_t *p_devinfo);

/**
 * \brief  CAN公共部分解初始化
 *
 * \param[in] p_dev     : 设备实例
 *
 * \retval AM_OK      ：成功
 * \retval -AM_EINVAL ： 参数错误
 * \retval -AM_EPERM  ： 操作不予许
 */
int amdr_can_comm_deinit (amdr_can_comm_dev_t *p_dev);

/**
 * \brief  CAN初始化
 *
 * \param[in] p_dev     : 设备实例
 * \param[in] p_devinfo : 设备信息
 *
 * \return handle
 */
am_can_handle_t amdr_can_init (amdr_can_dev_t           *p_dev,
                               const amdr_can_devinfo_t *p_devinfo);

/**
 * \brief 解初始化
 *
 * \param[in] p_dev     : 设备实例
 *
 * \return 无
 */
void amdr_can_deinit (amdr_can_dev_t *p_dev);

/** 
 * @} amdr_if_can
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_CAN_H */

/*end of file */



