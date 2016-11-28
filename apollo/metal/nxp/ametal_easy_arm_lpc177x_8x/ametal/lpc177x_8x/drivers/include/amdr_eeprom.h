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
 * \brief EEPROM驱动及服务接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-15  anu, first implementation.
 * \endinternal
 */

#ifndef __AMDR_EEPROM_H
#define __AMDR_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_eeprom.h"
    
/** 
 * \addtogroup amdr_if_eeprom
 * \copydoc amdr_eeprom.h
 * @{
 */

/**
 * \brief EEPROM 中断回调信息
 */
typedef struct amdr_eeprom_intcb_info {

    am_pfnvoid_t  pfn_callback;                /**< \brief 触发回调函数 */
    void         *p_arg;                       /**< \brief 回调函数的参数 */

} amdr_eeprom_intcb_info_t;

/**
 * \brief EEPROM 设备信息
 */
typedef struct amdr_eeprom_devinfo {
    
    amhw_eeprom_t              *p_hw_eeprom;    /**< \brief EEPROM 寄存器首地址  */
    amdr_eeprom_intcb_info_t   *p_intcb_info;   /**< \brief EEPROM 回调信息 */
    uint16_t                    inum;           /**< \brief EEPROM 中断号  */
    uint16_t                    int_count;      /**< \brief EEPROM 中断号  */
    
} amdr_eeprom_devinfo_t;

/**
 * \brief EEPROM 设备
 */
typedef struct amdr_eeprom_dev {
    
    /** \brief 指向EEPROM设备信息的指针 */
    const amdr_eeprom_devinfo_t *p_devinfo;

} amdr_eeprom_dev_t;

/**
 * \brief  EEPROM 操作模式
 */
typedef enum
{
    AMDR_EEPROM_MODE_8_BIT,
    AMDR_EEPROM_MODE_16_BIT,
    AMDR_EEPROM_MODE_32_BIT
}amdr_eeprom_mode_type_t;

/**
 * \name 中断存器的位定义
 * \anchor grp_amdr_eeprom_int
 * @{
 */

typedef uint32_t amdr_eeprom_int_t;
#define AMDR_EEPROM_INT_NONE               0X00   /**< \brief 无中断  */
#define AMDR_EEPROM_INT_RW_DONE            0X01   /**< \brief 读/写操作结束中断使能位  */
#define AMDR_EEPROM_INT_PROG_DONE          0X02   /**< \brief 编程操作已完成中断使能位   */

/** @} */

/**
 * \brief EEPROM 连接中断
 *
 * \param[in] p_dev        : EEPROM设备实例
 *
 * \retval  AM_OK     : 操作完成
 * \retval -AM_EINVAL : 参数不合法
 */
int amdr_eeprom_int_connect (amdr_eeprom_dev_t *p_dev);

/**
 * \brief EEPROM 安装回调函数
 *
 * \param[in] p_dev          : EEPROM设备实例
 * \param[in] inttype        : 中断类型
 * \param[in] pfn_callback   : 回调函数
 * \param[in] p_arg          : 参数
 *
 * \retval  AM_OK     : 操作完成
 * \retval -AM_EINVAL : 参数不合法
 */
int amdr_eeprom_install_callback (amdr_eeprom_dev_t   *p_dev,
                                  amdr_eeprom_int_t    inttype,
                                  am_pfnvoid_t         pfn_callback,
                                  void                *p_arg);

/**
 * \brief EEPROM 删除回调函数
 *
 * \param[in] p_dev          : EEPROM设备实例
 * \param[in] inttype        : 中断类型
 *
 * \retval  AM_OK     : 操作完成
 * \retval -AM_EINVAL : 参数不合法
 */
int amdr_eeprom_remove_callback (amdr_eeprom_dev_t   *p_dev,
                                 amdr_eeprom_int_t    inttype);
/**
 * \brief EEPROM 写操作
 *
 * \param[in] p_dev        : EEPROM设备实例
 * \param[in] page_offset  : 页数据地址
 * \param[in] page_address : 页地址
 * \param[in] p_data       : 要写入的数据
 * \param[in] mode         : 写入的模式
 * \param[in] count        : 写入的数据个数
 *
 * \retval  AM_OK     : 写操作完成
 * \retval -AM_EINVAL : 参数不合法
 * \retval -AM_EFAULT : 地址错误 (对齐错误)
 */
int amdr_eeprom_write (amdr_eeprom_dev_t       *p_dev,
                       uint16_t                 page_offset,
                       uint16_t                 page_address,
                       void                    *p_data,
                       amdr_eeprom_mode_type_t  mode,
                       uint32_t                 count);

/**
 * \brief EEPROM 读操作
 *
 * \param[in] p_dev        : EEPROM设备实例
 * \param[in] page_offset  : 页数据地址
 * \param[in] page_address : 页地址
 * \param[in] p_data       : 要写入的数据
 * \param[in] mode         : 写入的模式
 * \param[in] count        : 写入的数据个数
 *
 * \retval  AM_OK     : 写操作完成
 * \retval -AM_EINVAL : 参数不合法
 * \retval -AM_EFAULT : 地址错误 (对齐错误)
 */
int amdr_eeprom_read (amdr_eeprom_dev_t       *p_dev,
                      uint16_t                 page_offset,
                      uint16_t                 page_address,
                      void                    *p_data,
                      amdr_eeprom_mode_type_t  mode,
                      uint32_t                 count);

/**
 * \brief EEPROM 初始化
 *
 * \param[in] p_dev     : EEPROM设备实例
 * \param[in] p_devinfo : EEPROM设备信息
 *
 * \retval AM_OK : 操作成功 
 */
int amdr_eeprom_init(amdr_eeprom_dev_t           *p_dev,
                     const amdr_eeprom_devinfo_t *p_devinfo);

/**
 * \brief EEPROM 解初始化
 *
 * \param[in] p_dev : EEPROM设备实例
 *
 * \return 无 
 */
int amdr_eeprom_deinit (amdr_eeprom_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_EEPROM_H */

/* end of file */
