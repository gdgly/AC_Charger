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
 * \brief  CAN硬件操作接口实现
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-06-02  anu, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_CAN_H
#define __AMHW_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_can 
 * \copydoc amhw_can.h
 * @{
 */

/**
 * \name 验收滤波RAM的尺寸
 * \anchor grp_amhw_canaf_ram_size
 * @{
 */

#define AMHW_CANAF_RAM_SIZE  2048              /**< \brief CAN 滤波 RAM尺寸 */

/** @} */

/**
 * \brief 验收滤波RAM定义
 */
typedef struct amhw_canaf_ram {
  __IO uint32_t mask[AMHW_CANAF_RAM_SIZE / 4]; /**< \brief ID掩码 */
} amhw_canaf_ram_t;

/** 
 * \brief 验收滤波器定义
 */
typedef struct amhw_canaf {
  __IO uint32_t afmr;                   /**< \brief 验收滤波寄存器 */
  __IO uint32_t sff_sa;                 /**< \brief 标准帧单个起始地址寄存器 */
  __IO uint32_t sff_grp_sa;             /**< \brief 标准帧组起始地址寄存器   */
  __IO uint32_t eff_sa;                 /**< \brief 扩展帧起始地址寄存器     */
  __IO uint32_t eff_grp_sa;             /**< \brief 扩展帧组起始地址寄存器   */
  __IO uint32_t endtable;               /**< \brief AF表格结束寄存器  */
  __I  uint32_t lut_errad;              /**< \brief LUT错误地址寄存器 */
  __I  uint32_t lut_err;                /**< \brief LUT错误寄存器     */
  __IO uint32_t fcanie;                 /**< \brief FullCAN中断使能寄存器     */
  __IO uint32_t fcanic0;                /**< \brief FullCAN中断和捕获寄存器0  */
  __IO uint32_t fcanic1;                /**< \brief FullCAN中断和捕获寄存器1  */
} amhw_canaf_t;

/**
 * \brief 中央寄存器
 */
typedef struct amhw_cancr {
  __I  uint32_t can_txsr;              /**< \brief CAN中央发送状态寄存器  */
  __I  uint32_t can_rxsr;              /**< \brief CAN中央接收状态寄存器  */
  __I  uint32_t can_msr;               /**< \brief CAN中央其它寄存器      */
} amhw_cancr_t;

/** 
 * \brief 控制寄存器
 */
typedef struct amhw_can {
  __IO uint32_t mod;                  /**< \brief 控制CAN控制器的操作模式    */
  __O  uint32_t cmr;                  /**< \brief 影响CAN控制器状态的命令位  */
  __IO uint32_t gsr;                  /**< \brief 全局控制状态和错误计数器   */
  __I  uint32_t icr;                  /**< \brief 中断状态，仲裁丢失捕获，错误代码捕获 */
  __IO uint32_t ier;                  /**< \brief 中断使能  */
  __IO uint32_t btr;                  /**< \brief 总线时序  */
  __IO uint32_t ewl;                  /**< \brief 错误警报界限    */
  __I  uint32_t sr;                   /**< \brief 状态寄存器      */
  __IO uint32_t rfs;                  /**< \brief 接收帧状态      */
  __IO uint32_t rid;                  /**< \brief 接收到的标识符  */
  __IO uint32_t rda;                  /**< \brief 接收到的数据字节1～4  */
  __IO uint32_t rdb;                  /**< \brief 接收到的数据字节5～8  */
  __IO uint32_t tfi1;                 /**< \brief 发送帧信息（Tx缓冲器1） */
  __IO uint32_t tid1;                 /**< \brief 发送标识符（Tx缓冲器1） */
  __IO uint32_t tda1;                 /**< \brief 发送数据字节1～4（Tx缓冲器1） */
  __IO uint32_t tdb1;                 /**< \brief 发送数据字节5～8（Tx缓冲器1） */
  __IO uint32_t	tfi2;                 /**< \brief 发送帧信息（Tx缓冲器2）  */
  __IO uint32_t tid2;                 /**< \brief 发送标识符（Tx缓冲器2）  */
  __IO uint32_t tda2;                 /**< \brief 发送数据字节1～4 （Tx缓冲器2） */
  __IO uint32_t tdb2;                 /**< \brief 发送数据字节5～8 （Tx缓冲器2） */
  __IO uint32_t tfi3;                 /**< \brief 发送帧信息（Tx缓冲器3） */
  __IO uint32_t tid3;                 /**< \brief 发送标识符（Tx缓冲器3） */
  __IO uint32_t tda3;                 /**< \brief 发送数据字节1～4 （Tx缓冲器3） */
  __IO uint32_t tdb3;                 /**< \brief 发送数据字节5～8(Tx缓冲器3）   */
} amhw_can_t;

/**
 * \brief CAN 设置FullCAN（标准帧格式）标识符区起始地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 * \param[in] addr       : 起始地址 以4个字节进行偏移
 *
 * \return 无
 */
am_static_inline 
void amhw_canaf_standid_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->sff_sa = addr;
}

/**
 * \brief CAN 设置标准帧组格式标识符区起始地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 * \param[in] addr       : 起始地址 以4个字节进行偏移
 *
 * \return 无
 */
am_static_inline 
void amhw_canaf_standid_group_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->sff_grp_sa = addr;
}
    
/**
 * \brief CAN 设置扩展帧格式标识符区起始地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 * \param[in] addr       : 起始地址 以4个字节进行偏移
 *
 * \return 无
 */
am_static_inline 
void amhw_canaf_externid_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->eff_sa = addr;
}

/**
 * \brief CAN 设置扩展帧组格式标识符区起始地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 * \param[in] addr       : 起始地址 以4个字节进行偏移
 *
 * \return 无
 */
am_static_inline 
void amhw_canaf_externid_group_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->eff_grp_sa = addr;
}

/**
 * \brief CAN 设置结束表地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 * \param[in] addr       : 起始地址 以4个字节进行偏移
 *
 * \return 无
 */
am_static_inline 
void amhw_canaf_endtable_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->endtable = addr;
}

/**
 * \brief CAN 设置FULLCAN中断使能
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 * \param[in] mask       : 中断使能位
 *
 * \return 无
 */
am_static_inline
void amhw_canaf_fcanie_set (amhw_canaf_t *p_hw_canaf, uint32_t mask)
{
    p_hw_canaf->fcanie = mask;
}

/**
 * \brief CAN 设置FULLCAN IC0 中断捕获
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 * \param[in] mask       : 中断使能位
 *
 * \return 无
 */
am_static_inline
void amhw_canaf_fcanic0_set (amhw_canaf_t *p_hw_canaf, uint32_t mask)
{
    p_hw_canaf->fcanic0 = mask;
}

/**
 * \brief CAN 设置FULLCAN IC1 中断捕获
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 * \param[in] mask       : 中断使能位
 *
 * \return 无
 */
am_static_inline
void amhw_canaf_fcanic1_set (amhw_canaf_t *p_hw_canaf, uint32_t mask)
{
    p_hw_canaf->fcanic1 = mask;
}

/**
 * \brief CAN 获取FullCAN（标准帧格式）标识符区起始地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return FullCAN（标准帧格式）标识符区起始地址
 */
am_static_inline
uint32_t amhw_canaf_standid_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->sff_sa;
}

/**
 * \brief CAN 获取标准帧组格式标识符区起始地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 标准帧组格式标识符区起始地址
 */
am_static_inline
uint32_t amhw_canaf_standid_group_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->sff_grp_sa;
}

/**
 * \brief CAN 获取扩展帧格式标识符区起始地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 扩展帧格式标识符区起始地址
 */
am_static_inline
uint32_t amhw_canaf_externid_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->eff_sa;
}

/**
 * \brief CAN 获取扩展帧组格式标识符区起始地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 扩展帧组格式标识符区起始地址
 */
am_static_inline
uint32_t amhw_canaf_externid_group_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->eff_grp_sa;
}

/**
 * \brief CAN 获取结束表地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 结束表地址
 */
am_static_inline
uint32_t amhw_canaf_endtable_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->endtable;
}

/**
 * \brief CAN 获取LUT错误地址
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return LUT错误地址
 */
am_static_inline
uint32_t amhw_canaf_luterrad_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->lut_errad;
}

/**
 * \brief CAN 获取LUT错误
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return LUT错误地址
 */
am_static_inline
uint32_t amhw_canaf_luterr_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->lut_err;
}

/**
 * \brief CAN 获取FULLCAN中断使能
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return FULLCAN中断使能位
 */
am_static_inline
uint32_t amhw_canaf_fcanie_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->fcanie;
}

/**
 * \brief CAN 获取FULLCAN IC0 中断捕获
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return FULLCAN IC0 中断捕获
 */
am_static_inline
uint32_t amhw_canaf_fcanic0_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->fcanic0;
}

/**
 * \brief CAN 获取FULLCAN IC1 中断捕获
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return FULLCAN IC1 中断捕获
 */
am_static_inline
uint32_t amhw_canaf_fcanic1_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->fcanic1;
}

/**
 * \brief CAN 设置 RAM 滤波表的ID或者ID的范围
 *
 * \param[in] p_hw_canaf_ram : 指向CANAF_RAM寄存器块的指针
 * \param[in] block          : 滤波器ram的某一块
 * \param[in] mask           : ID或者ID的范围
 *
 * \return 无
 */
am_static_inline 
void amhw_can_filter_set (amhw_canaf_ram_t *p_hw_canaf_ram, uint16_t block, uint32_t mask)
{
    p_hw_canaf_ram->mask[block] = mask;
}

/**
 * \brief CAN 获取 RAM 滤波表的ID或者ID的范围
 *
 * \param[in] p_hw_canaf_ram : 指向CANAF_RAM寄存器块的指针
 * \param[in] block          : 滤波器ram的某一块
 *
 * \return RAM 滤波表的ID或者ID的范围
 */
am_static_inline 
uint32_t amhw_can_filter_get (amhw_canaf_ram_t *p_hw_canaf_ram, uint16_t block)
{
    return p_hw_canaf_ram->mask[block];
}

/**
 * \name 验收滤波器的位定义
 * \anchor grp_amhw_can_afmr
 * @{
 */
 
#define AMHW_CAN_AFMR_ACCOFF			0   /**< \brief 验收滤波器寄存器的AccOff位  */
#define AMHW_CAN_AFMR_ACCBP				1   /**< \brief 验收滤波器寄存器的AccBP位   */
#define AMHW_CAN_AFMR_EFCAN				2   /**< \brief 验收滤波器寄存器的Efcan位   */
#define AMHW_CAN_AFMR_RVS28				3   /**< \brief 保留                        */

/** @} */

/**
 * \brief CAN开启模式
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_onmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr &= ~(0x01 << AMHW_CAN_AFMR_ACCOFF);
}

/**
 * \brief CAN关闭模式
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_can_offmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr |= (0x01 << AMHW_CAN_AFMR_ACCOFF);
}

/**
 * \brief CAN旁路模式
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_bypassmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr &= ~0x07;
    p_hw_canaf->afmr |= (0x01 << AMHW_CAN_AFMR_ACCBP);
}

/**
 * \brief CAN工作模式
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_workmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr &= ~0x07;
}

/**
 * \brief CANFullCAN模式
 *
 * \param[in] p_hw_canaf : 指向CANAF寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_fullcanmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr &= ~0x07;
    p_hw_canaf->afmr |= (0x01 << AMHW_CAN_AFMR_EFCAN);
}

/**
 * \name 中央发送状态的位定义
 * \anchor grp_amhw_cancr_tx
 * @{
 */

typedef uint32_t amhw_cancr_tx_t;
#define AMHW_CANCR_TS1             (0x01 << 0)    /**< \brief CAN1 正发送消息  */
#define AMHW_CANCR_TS2             (0x01 << 1)    /**< \brief CAN2 正发送消息  */
#define AMHW_CANCR_TBS1            (0x01 << 8)    /**< \brief CAN1 发送缓存有效  */
#define AMHW_CANCR_TBS2            (0x01 << 9)    /**< \brief CAN2 发送缓存有效  */
#define AMHW_CANCR_TCS1            (0x01 << 16)   /**< \brief CAN1 发送完成  */
#define AMHW_CANCR_TCS2            (0x01 << 17)   /**< \brief CAN2 发送完成  */

/** @} */

/**
 * \brief CAN 获取中央发送状态
 *
 * \param[in] p_hw_cancr : 中央控制器基址
 *
 * \return 中央发送状态
 */
am_static_inline
amhw_cancr_tx_t amhw_cancr_txsr_get (amhw_cancr_t *p_hw_cancr)
{
    return p_hw_cancr->can_txsr;
}

/**
 * \name 中央接收状态的位定义
 * \anchor grp_amhw_cancr_rx
 * @{
 */

typedef uint32_t amhw_cancr_rx_t;
#define AMHW_CANCR_RS1             (0x01 << 0)    /**< \brief CAN1 正接收消息  */
#define AMHW_CANCR_RS2             (0x01 << 1)    /**< \brief CAN2 正接收消息  */
#define AMHW_CANCR_RB1             (0x01 << 8)    /**< \brief CAN1 接收消息有效  */
#define AMHW_CANCR_RB2             (0x01 << 9)    /**< \brief CAN2 接收消息有效  */
#define AMHW_CANCR_DOS1            (0x01 << 16)   /**< \brief CAN1 消息未读出  */
#define AMHW_CANCR_DOS2            (0x01 << 17)   /**< \brief CAN2 消息未读出 */

/** @} */

/**
 * \brief CAN 获取中央接收状态
 *
 * \param[in] p_hw_cancr : 中央控制器基址
 *
 * \return 中央接收状态
 */
am_static_inline
amhw_cancr_rx_t amhw_cancr_rxsr_get (amhw_cancr_t *p_hw_cancr)
{
    return p_hw_cancr->can_rxsr;
}

/**
 * \name 中央状态的位定义
 * \anchor grp_amhw_cancr_stat
 * @{
 */

typedef uint32_t amhw_cancr_stat_t;
#define AMHW_CANCR_E1             (0x01 << 0)    /**< \brief CAN1 错误计数达到限制值 */
#define AMHW_CANCR_E2             (0x01 << 1)    /**< \brief CAN2 错误计数达到限制值 */
#define AMHW_CANCR_BS1            (0x01 << 8)    /**< \brief CAN1 当前总线活跃  */
#define AMHW_CANCR_BS2            (0x01 << 9)    /**< \brief CAN2 当前总线活跃  */

/** @} */

/**
 * \brief CAN 获取中央状态
 *
 * \param[in] p_hw_cancr : 中央控制器基址
 *
 * \return 中央状态
 */
am_static_inline
amhw_cancr_stat_t amhw_cancr_msr_get (amhw_cancr_t *p_hw_cancr)
{
    return p_hw_cancr->can_msr;
}

/**
 * \name 模式寄存器的位定义
 * \anchor grp_amhw_can_mod
 * @{
 */
 
#define AMHW_CAN_MOD_RM 		0       /**< \brief 复位模式 */
#define AMHW_CAN_MOD_LOM 		1       /**< \brief 只听模式 */
#define AMHW_CAN_MOD_STM		2       /**< \brief 自测试模式 */
#define AMHW_CAN_MOD_TPM 		3       /**< \brief 发送优先模式 */
#define AMHW_CAN_MOD_SM 		4       /**< \brief 睡眠模式 */
#define AMHW_CAN_MOD_RPM 		5       /**< \brief 接收模式 */
#define AMHW_CAN_MOD_RSV1   	6       /**< \brief 保留 */
#define AMHW_CAN_MOD_TM 		7       /**< \brief 测试模式 */
#define AMHW_CAN_MOD_RSV24 	    8       /**< \brief 保留 */

/** @} */

/**
 * \brief CAN进入正常模式
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_normal_enable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod &= 0x01;
}

/**
 * \brief CAN进入只听模式
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_listenonly_enable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod |= (0x01 << AMHW_CAN_MOD_LOM);
}

/**
 * \brief CAN进入自测试模式
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_selftest_enable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod |= (0x01 << AMHW_CAN_MOD_STM);
}

/**
 * \brief CAN退出自测试模式
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_can_selftest_disable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod &= ~(0x01 << AMHW_CAN_MOD_STM);
}

/**
 * \brief CAN进入复位
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_can_reset_enable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod |= (0x01 << AMHW_CAN_MOD_RM);
}

/**
 * \brief CAN退出复位
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_reset_disable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod &= ~(0x01 << AMHW_CAN_MOD_RM);
}

/**
 * \brief CAN进入休眠
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_sleep (amhw_can_t *p_hw_can)
{
    p_hw_can->mod |= (0x01 << AMHW_CAN_MOD_SM);
}

/**
 * \brief CAN唤醒
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_wakeup (amhw_can_t *p_hw_can)
{
    p_hw_can->mod &= ~(0x01 << AMHW_CAN_MOD_SM);
}


/**
 * \name 命令寄存器的位定义
 * \anchor grp_amhw_can_cmr
 * @{
 */
 
#define AMHW_CAN_CMR_TR					0       /**< \brief 传输请求 */
#define AMHW_CAN_CMR_AT					1       /**< \brief 终止发送 */
#define AMHW_CAN_CMR_RRB				2       /**< \brief 释放接收缓冲器 */
#define AMHW_CAN_CMR_CDO				3       /**< \brief 清除资料超载 */
#define AMHW_CAN_CMR_SRR				4       /**< \brief 自接收请求 */
#define AMHW_CAN_CMR_STB1				5       /**< \brief 选择发送缓存区1 */
#define AMHW_CAN_CMR_STB2				6       /**< \brief 选择发送缓存区2 */
#define AMHW_CAN_CMR_STB3				7       /**< \brief 选择发送缓存区3 */
#define AMHW_CAN_CMR_RVS23			    8       /**< \brief 保留 */

/** @} */

/**
 * \brief CAN 设置命令
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] type     : 命令类型
 *
 * \return 无
 */
am_static_inline
void amhw_can_cmr_set (amhw_can_t *p_hw_can, uint32_t type)
{
    p_hw_can->cmr = type;
}

/**
 * \brief CAN 设置传输请求
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_transrequest_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_TR);
}

/**
 * \brief CAN 中止传输
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_aborttrans_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_AT);
}

/**
 * \brief CAN 清除选择发送缓存区
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_txbuf_clr (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr &= ~((0x01 << AMHW_CAN_CMR_STB1) |
                       (0x01 << AMHW_CAN_CMR_STB2) |
                       (0x01 << AMHW_CAN_CMR_STB3));
}

/**
 * \brief CAN 设置选择发送缓存区1
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_txbuf1_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_STB1);
}

/**
 * \brief CAN 设置选择发送缓存区2
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_txbuf2_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_STB2);
}

/**
 * \brief CAN 设置选择发送缓存区3
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_txbuf3_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_STB3);
}

/**
 * \name 中断寄存器的位定义
 * \anchor grp_amhw_can_ier
 * @{
 */
 
#define AMHW_CAN_IER_RIE			0			/**< \brief 接收中断 */
#define AMHW_CAN_IER_TIE			1			/**< \brief 发送中断 */
#define AMHW_CAN_IER_EIE			2			/**< \brief 错误警告中断 */
#define AMHW_CAN_IER_DOIE			3			/**< \brief 数据超载中断 */
#define AMHW_CAN_IER_WUIE			4			/**< \brief 唤醒中断     */
#define AMHW_CAN_IER_EPIE			5			/**< \brief 被动错误中断 */
#define AMHW_CAN_IER_ALIE			6			/**< \brief 仲裁丢失中断 */
#define AMHW_CAN_IER_BEIE			7			/**< \brief 总线错误中断 */
#define AMHW_CAN_IER_IDIE			8			/**< \brief ID就绪中断 */
#define AMHW_CAN_IER_TIE2			9			/**< \brief 发送中断2  */
#define AMHW_CAN_IER_TIE3			10		    /**< \brief 发送中断3  */
#define AMHW_CAN_IER_RVS20	    	11		    /* Reserved            */

/** @} */

/** \brief 中断类型的总数 */
#define AMHW_CAN_INT_TYPE_COUNT    11

/**
 * \name 中断的类型
 * \anchor grp_amhw_can_int_type
 * @{
 */

typedef uint32_t amhw_can_int_type_t;           /**< \brief 中断类型  */
#define AMHW_CAN_INT_TYPE_NONE		    0X0000  /**< \brief 无中断  */
#define AMHW_CAN_INT_TYPE_RI			0X0001  /**< \brief 接收中断 */
#define AMHW_CAN_INT_TYPE_TI			0X0002  /**< \brief 发送中断 */
#define AMHW_CAN_INT_TYPE_EI			0X0004  /**< \brief 错误警告中断 */
#define AMHW_CAN_INT_TYPE_DOI			0X0008  /**< \brief 数据超载中断 */
#define AMHW_CAN_INT_TYPE_WUI			0X0010  /**< \brief 唤醒中断     */
#define AMHW_CAN_INT_TYPE_EPI			0X0020  /**< \brief 被动错误中断 */
#define AMHW_CAN_INT_TYPE_ALI			0X0040  /**< \brief 仲裁丢失中断 */
#define AMHW_CAN_INT_TYPE_BEI			0X0080  /**< \brief 总线错误中断 */
#define AMHW_CAN_INT_TYPE_IDI			0X0100  /**< \brief ID就绪中断 */
#define AMHW_CAN_INT_TYPE_TI2			0X0200  /**< \brief 发送中断2  */
#define AMHW_CAN_INT_TYPE_TI3			0X0400  /**< \brief 发送中断3  */
#define AMHW_CAN_INT_TYPE_ALL           0X04FF  /**< \brief 所有中断  */

/** @} */

/**
 * \brief CAN 使能中断
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] int_mask : 中断类型  配置参数，参见
 *                       \ref grp_amhw_can_int_type "interrupt type"
 *
 * \return 		无
 * \note        无
 */
am_static_inline
void amhw_can_int_enable (amhw_can_t *p_hw_can, amhw_can_int_type_t int_mask)
{
	p_hw_can->ier |= int_mask;
}

/**
 * \brief CAN失能中断
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] int_mask : 中断类型  配置参数，参见
 *                       \ref grp_amhw_can_int_type "interrupt type"
 *
 * \return 		无
 */
am_static_inline
void amhw_can_int_disable (amhw_can_t *p_hw_can, amhw_can_int_type_t int_mask)
{
	p_hw_can->ier &= ~int_mask;
}


/**
 * \name 时序寄存器的位定义
 * \anchor grp_amhw_can_btr
 * @{
 */
 
#define AMHW_CAN_BTR_BRP			0           /**< \brief 波特率预分频 */
#define AMHW_CAN_BTR_RVS4			10			/**< \brief 保留  */
#define AMHW_CAN_BTR_SJW			14			/**< \brief 同步跳转宽度 */
#define AMHW_CAN_BTR_TESG1		    16			/**< \brief 指定同步到采用点的延时 */
#define AMHW_CAN_BTR_TESG2		    20			/**< \brief 采样点到下个指定同步点的延时 */
#define AMHW_CAN_BTR_SAM			23			/**< \brief 采样 */

/** @} */

/**
 * \brief CAN 清除波特率设置
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_can_baudrate_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->btr &= ~0x7fffff;		/* 清reserved0-22位的数据 */
}

/**
 * \brief CAN 波特率预分频设置
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] brp      : 预分频数
 *
 * \return 无
 */
am_static_inline
void amhw_can_brp_set (amhw_can_t *p_hw_can, uint8_t brp)
{
	p_hw_can->btr |= ((brp & 0X3ff) << AMHW_CAN_BTR_BRP);
}

/**
 * \brief CAN 波特率预分频清零
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 		无
 */
am_static_inline
void amhw_can_brp_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->btr &= ~(0x3ff << AMHW_CAN_BTR_BRP);
}


/**
 * \brief CAN 波特率同步跳转宽度设置
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] sjw      : 同步跳转宽度
 *
 * \return 无
 */
am_static_inline
void amhw_can_sjw_set (amhw_can_t *p_hw_can, uint8_t sjw)
{
	p_hw_can->btr |= ((sjw & 0x03) << AMHW_CAN_BTR_SJW);
}


/**
 * \brief CAN 波特率同步跳转宽度清零
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_can_sjw_clr (amhw_can_t *p_hw_can)
{
    p_hw_can->btr &= ~(0X3 << AMHW_CAN_BTR_SJW);
}


/**
 * \brief CAN 波特率同步到采样点延时设置
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] tesg     : 同步到采样点延时
 *
 * \return 无
 */
am_static_inline
void amhw_can_tesg1_set (amhw_can_t *p_hw_can, uint8_t tesg)
{
	p_hw_can->btr |= ((tesg & 0x0f) << AMHW_CAN_BTR_TESG1);
}


/**
 * \brief CAN 波特率同步到采样点延时清零
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_can_tesg1_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->btr &= ~(0x0f << AMHW_CAN_BTR_TESG1);
}


/**
 * \brief CAN 波特率采样点到同步延时设置
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] tesg     : 采样点到同步延时
 *
 * \return 无
 */
am_static_inline
void amhw_can_tesg2_set (amhw_can_t *p_hw_can, uint8_t tesg)
{
	p_hw_can->btr |= ((tesg & 0x07) << AMHW_CAN_BTR_TESG2);
}


/**
 * \brief CAN 波特率采样点到同步延时清除
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 		无
 */
am_static_inline
void amhw_can_tesg2_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->btr &= ~(0x07 << AMHW_CAN_BTR_TESG2);
}

/**
 * \brief CAN 设置总线被采样次数为3次
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_can_sam_set (amhw_can_t *p_hw_can)
{
    p_hw_can->btr |= (0x01 << AMHW_CAN_BTR_SAM);
}


/**
 * \brief CAN 设置总线被采样次数为1次
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_can_sam_clr (amhw_can_t *p_hw_can)
{
    p_hw_can->btr &= ~(0X01 << AMHW_CAN_BTR_SAM);
}

/**
 * \brief CAN 波特率预分频获取
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 预分频值
 */
am_static_inline
uint16_t amhw_can_brp_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_BRP) & 0X3ff);
}

/**
 * \brief CAN 波特率同步跳转宽度获取
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 同步跳转宽度值
 */
am_static_inline
uint8_t amhw_can_sjw_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_SJW) & 0x03);
}

/**
 * \brief CAN 波特率同步到采样点延时获取
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 同步到采样点延时值
 */
am_static_inline
uint8_t amhw_can_tesg1_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_TESG1) & 0x0f);
}


/**
 * \brief CAN 波特率采样点到同步延时获取
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 采样点到同步延时
 */
am_static_inline
uint8_t amhw_can_tesg2_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_TESG2) & 0x07);
}

/**
 * \brief CAN 获取总线被采样次数是为单次或者3次
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \retval 0 :单次采样
 * \retval 1 :3次采样
 */
am_static_inline
uint8_t amhw_can_sam_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_SAM) & 0x01);
}

/**
 * \brief CAN 错误报警值设置
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] warn_val : 错误报警值设置
 *
 * \return 无
 */
am_static_inline
void amhw_can_ewl_set (amhw_can_t *p_hw_can, uint8_t warn_val)
{
    p_hw_can->ewl = warn_val;
}

/**
 * \brief CAN 状态寄存器
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 状态
 */
am_static_inline
uint32_t amhw_can_sr_get (amhw_can_t *p_hw_can)
{
    return p_hw_can->sr;
}

/**
 * \name 全局状态寄存器的位定义
 * \anchor grp_amhw_can_gsr
 * @{
 */
 
#define AMHW_CAN_GSR_RBS			0			/**< \brief 接收缓冲状态 */
#define AMHW_CAN_GSR_DOS			1			/**< \brief 数据超载状态 */
#define AMHW_CAN_GSR_TBS			2			/**< \brief 发送缓冲器状态 */
#define AMHW_CAN_GSR_TCS			3			/**< \brief 发送结束状态 */
#define AMHW_CAN_GSR_RS				4			/**< \brief 接收状态 */
#define AMHW_CAN_GSR_TS				5			/**< \brief 发送状态 */
#define AMHW_CAN_GSR_ES				6			/**< \brief 错误状态 */
#define AMHW_CAN_GSR_BS				7			/**< \brief 总线状态 */
#define AMHW_CAN_GSR_RVS8			8			/**< \brief 保留 */
#define AMHW_CAN_GSR_RXERR		    16		    /**< \brief Rx错误计数器的当前值 */
#define AMHW_CAN_GSR_TXERR		    24		    /**< \brief Tx错误计数器的当前值 */

/** @} */

/**
 * \brief CAN获取总线状态 是否警告
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \retval 0 总线正常
 * \retval 1 总线警告
 */
am_static_inline
uint8_t amhw_can_buswarn_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->gsr >> AMHW_CAN_GSR_ES) & 0x01);
}

/**
 * \brief CAN获取总线状态 是否关闭
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \retval 0 总线正常
 * \retval 1 总线关闭
 */
am_static_inline
uint8_t amhw_can_busstatus_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->gsr >> AMHW_CAN_GSR_BS) & 0x01);
}


/**
 * \brief CAN获取RX错误计数
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return RX错误计数
 */
am_static_inline
uint8_t amhw_can_rxerrcnt_get (amhw_can_t *p_hw_can)
{
	return (((p_hw_can->gsr) & 0xff0000) >> AMHW_CAN_GSR_RXERR);
}


/**
 * \brief CAN获取TX错误计数
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return TX错误计数的指针
 */
am_static_inline
uint8_t amhw_can_txerrcnt_get (amhw_can_t *p_hw_can)
{
	return (((p_hw_can->gsr) & 0xff000000) >> AMHW_CAN_GSR_TXERR);
}

/**
 * \brief 		CAN清除错误计数
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 		无
 */
am_static_inline
void amhw_can_errcnt_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->gsr &= ~0xffff0000;
}

/**
 * \name 接收帧状态寄存器的位定义
 * \anchor grp_amhw_can_rfs
 * @{
 */
 
#define AMHW_CAN_RFS_ID					0       /**< \brief ID索引字段元 */
#define AMHW_CAN_RFS_BP					10		/**< \brief 旁路模式中接收的报文 */
#define AMHW_CAN_RFS_RVS5				11		/**< \brief 保留 */
#define AMHW_CAN_RFS_DLC				16		/**< \brief 接收到的报文的数据长度代码 */
#define AMHW_CAN_RFS_RVS10		    	20		/**< \brief 保留 */
#define AMHW_CAN_RFS_RTR				30		/**< \brief 接收到的报文的远程传输请求位 */
#define AMHW_CAN_RFS_FF					31		/**< \brief 接收到的报文包含11位的标识符 */

/** @} */

/**
 * \brief CAN 获取数据长度
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 数据长度
 */
am_static_inline 
uint8_t amhw_can_datalen_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rfs >> AMHW_CAN_RFS_DLC) & 0x0ff);
}

/**
 * \brief CAN 获取接收数据远程帧的状态
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \retval 1 为远程帧
 * \retval 0 为数据帧
 */
am_static_inline 
uint8_t amhw_can_remoteflag_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rfs >> AMHW_CAN_RFS_RTR) & 0x01);
}

/**
 * \brief CAN 获取接收数据扩展帧的状态
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \retval 1 为扩展帧
 * \retval 0 为标准帧
 */
am_static_inline 
uint8_t amhw_can_externflag_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rfs >> AMHW_CAN_RFS_FF) & 0x01);
}


/**
 * \brief CAN 获取接收数据扩展帧的ID号
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return ID
 */
am_static_inline 
uint32_t amhw_can_externid_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rid) & 0x1fffffff);
}

/**
 * \brief CAN 获取接收数据标准帧的ID号
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return ID
 */
am_static_inline 
uint8_t amhw_can_standid_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rid) & 0x7ff);
}

	
/**
 * \brief CAN 获取接收缓存的状态
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \retval 1 为超载
 * \retval 0 正常
 */
am_static_inline 
uint8_t amhw_can_rvbuf_status_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->gsr >> AMHW_CAN_GSR_DOS) & 0x01);
}


/**
 * \brief CAN释放接收缓存
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return 无
 */
am_static_inline 
void amhw_can_rvbuff_release_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_RRB);
}


/**
 * \name 发送帧信息寄存器的位定义
 * \anchor grp_amhw_can_tfi
 * @{
 */
 
#define AMHW_CAN_TFI_PRIO				0       /**< \brief 发送优先级 */
#define AMHW_CAN_TFI_RVS8				8       /**< \brief 保留 */
#define AMHW_CAN_TFI_DLC				16		/**< \brief 发送数据长度代码 */
#define AMHW_CAN_TFI_RVS10			    20		/**< \brief 保留 */
#define AMHW_CAN_TFI_RTR				30		/**< \brief 远程帧标志 */
#define AMHW_CAN_TFI_FF					31		/**< \brief 扩展帧标志 */

#define AMDR_CAN_TXBUF_CHN              0X01    /**< \brief CAN 发送缓存的通道号 1-3*/
#define AMDR_CAN_TXBUF_PRIO             0X01    /**< \brief CAN 发送缓存的优先级 */

/** @} */

/**
 * \brief CAN 清除TFI寄存器
 *
 * \param[in] p_hw_can  : 指向CAN寄存器块的指针
 * \param[in] chn       : 指向tfi的哪一通道 1-3通道
 *
 * \return 无
 */
am_static_inline 
void amhw_can_txinfo_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi = ~0xc00f00ff;
}

/**
 * \brief CAN 设置TFI的优先级
 *
 * \param[in] p_hw_can   : 指向CAN寄存器块的指针
 * \param[in] chn 		 : 指向tfi的哪一通道 1-3通道
 * \param[in] prio		 : 优先级
 *
 * \return 无
 */
am_static_inline 
void amhw_can_transprio_set (amhw_can_t *p_hw_can, uint8_t chn, uint8_t prio)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi |= prio << AMHW_CAN_TFI_PRIO;
}


/**
 * \brief CAN 清除 TFI的优先级
 *
 * \param[in] p_hw_can   : 指向CAN寄存器块的指针
 * \param[in] chn 		 : 指向tfi的哪一通道 1-3通道
 *
 * \return 无
 */
am_static_inline 
void amhw_can_transprio_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi &= ~(0xff << AMHW_CAN_TFI_PRIO);
}


/**
 * \brief CAN 设置TFI的数据长度
 *
 * \param[in] p_hw_can  : 指向CAN寄存器块的指针
 * \param[in] chn       : 指向tfi的哪一通道 1-3通道
 * \param[in] len       : 长度
 *
 * \return 无
 */
am_static_inline 
void amhw_can_datalen_set (amhw_can_t *p_hw_can, uint8_t chn, uint8_t len)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi |= len << AMHW_CAN_TFI_DLC;
}

/**
 * \brief CAN 清除TFI的数据长度
 *
 * \param[in] p_hw_can  : 指向CAN寄存器块的指针
 * \param[in] chn       : 指向tfi的哪一通道 1-3通道
 *
 * \return 无
 */
am_static_inline 
void amhw_can_datalen_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi &= ~(0x0f << AMHW_CAN_TFI_DLC);
}


/**
 * \brief CAN 设置TFI远程帧
 *
 * \param[in] p_hw_can   : 指向CAN寄存器块的指针
 * \param[in] chn        : 指向tfi的哪一通道 1-3通道
 * \param[in] remoteflag : 远程帧标志位
 *
 * \return 无
 */
am_static_inline 
void amhw_can_remoteflag_set (amhw_can_t *p_hw_can, uint8_t chn, uint8_t remoteflag)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi |= remoteflag << AMHW_CAN_TFI_RTR;
}


/**
 * \brief CAN 清除TFI远程帧
 *
 * \param[in] p_hw_can   : 指向CAN寄存器块的指针
 * \param[in] chn        : 指向tfi的哪一通道 1-3通道
 *
 * \return 无
 * \note  无
 */
am_static_inline 
void amhw_can_remoteflag_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi &= ~(0x01 << AMHW_CAN_TFI_RTR);
}


/**
 * \brief  CAN 设置TFI扩展帧
 *
 * \param[in] p_hw_can 	 : 指向CAN寄存器块的指针
 * \param[in] chn        : 指向tfi的哪一通道 1-3通道
 * \param[in] externflag : 扩展帧标志位
 *
 * \return 无
 */
am_static_inline 
void amhw_can_externflag_set (amhw_can_t *p_hw_can, uint8_t chn, uint8_t externflag)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi |= externflag << AMHW_CAN_TFI_FF;
}


/**
 * \brief CAN 清除TFI扩展帧
 *
 * \param[in] p_hw_can 	 : 指向CAN寄存器块的指针
 * \param[in] chn        : 指向tfi的哪一通道 1-3通道
 *
 * \return 		无
 */
am_static_inline 
void amhw_can_externflag_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi &= ~((uint32_t)0x80000000);
}

/**
 * \brief CAN 设置TID ID号
 *
 * \param[in] p_hw_can  : 指向CAN寄存器块的指针
 * \param[in] chn       : 指向tfi的哪一通道 1-3通道
 * \param[in] id	    : id号
 *
 * \return 无
 */
am_static_inline 
void amhw_can_id_set (amhw_can_t *p_hw_can, uint8_t chn, uint32_t id)
{
    uint32_t *tid = (uint32_t *)&p_hw_can->tid1 + 4*(chn - 1);
    *tid = id;
}


/**
 * \brief CAN 设置TDA
 *
 * \param[in] p_hw_can  : 指向CAN寄存器块的指针
 * \param[in] chn       : 指向tfi的哪一通道 1-3通道
 * \param[in] data	    : 数据
 *
 * \return 无
 */
am_static_inline 
void amhw_can_txdataa_set (amhw_can_t *p_hw_can, uint8_t chn, uint32_t data)
{
    uint32_t *tda = (uint32_t *)&p_hw_can->tda1 + 4*(chn - 1);
    *tda = data;
}

/**
 * \brief CAN TDB
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 * \param[in] chn      : 指向tfi的哪一通道 1-3通道
 * \param[in] data	   : 数据
 *
 * \return  无
 */
am_static_inline 
void amhw_can_txdatab_set (amhw_can_t *p_hw_can, uint8_t chn, uint32_t data)
{
    uint32_t *tdb = (uint32_t *)&p_hw_can->tdb1 + 4*(chn - 1);
    *tdb = data;
}
	
/**
 * \name CAN中断和捕获寄存器的位定义
 * \anchor grp_amhw_can_icr
 * @{
 */

#define AMHW_CAN_ICR_RI					0				/**< \brief 接收中断 */
#define AMHW_CAN_ICR_TI1				1				/**< \brief 发送中断1 */
#define AMHW_CAN_ICR_EI					2				/**< \brief 错误报警中断 */
#define AMHW_CAN_ICR_DOI				3				/**< \brief 数据超载中断 */
#define AMHW_CAN_ICR_WUI				4				/**< \brief 唤醒中断 */
#define AMHW_CAN_ICR_EPI				5				/**< \brief 错误被动中断 */
#define AMHW_CAN_ICR_ALI				6				/**< \brief 仲裁丢失中断 */
#define AMHW_CAN_ICR_BEI				7				/**< \brief 总线错误中断 */
#define AMHW_CAN_ICR_IDI				8				/**< \brief ID就绪中断 */
#define AMHW_CAN_ICR_TI2				9				/**< \brief 发送中断2 */
#define AMHW_CAN_ICR_TI3				10			    /**< \brief 发送中断3 */
#define AMHW_CAN_ICR_RVS5				11			    /**< \brief 保留 */
#define AMHW_CAN_ICR_ERRBIT			    16			    /**< \brief 错误代码捕获 */
#define AMHW_CAN_ICR_ERRDIR			    21			    /**< \brief 方向捕获 */
#define AMHW_CAN_ICR_ERRC1			    22			    /**< \brief 总线错误捕获 */
#define AMHW_CAN_ICR_ALCBIT			    24			    /**< \brief 仲裁捕获 */

/** @} */

/**
 * \name CAN BUS错误代码
 * \anchor grp_amhw_can_err_code
 * @{
 */

typedef uint32_t amhw_can_err_code_t;                   /**< \brief 总线错误代码   */
#define AMHW_CAN_ERR_CODE_FRAME     			0x03	/**< \brief 帧起始                 */
#define AMHW_CAN_ERR_CODE_ID28_21     			0x02	/**< \brief ID28…ID21   */
#define AMHW_CAN_ERR_CODE_ID20_18     			0x06	/**< \brief ID20…ID18   */
#define AMHW_CAN_ERR_CODE_START     			0x04	/**< \brief 起始位                 */
#define AMHW_CAN_ERR_CODE_IDE     			    0x05	/**< \brief IDE位                   */
#define AMHW_CAN_ERR_CODE_ID17_13     			0x07	/**< \brief ID17…ID13   */
#define AMHW_CAN_ERR_CODE_ID12_5     			0x0F	/**< \brief ID12…ID5    */
#define AMHW_CAN_ERR_CODE_ID4_0     			0x0E	/**< \brief ID4…ID0     */
#define AMHW_CAN_ERR_CODE_RTR     			    0x0C	/**< \brief RTR位                   */
#define AMHW_CAN_ERR_CODE_RSV1     			    0x0D	/**< \brief 保留位1     */
#define AMHW_CAN_ERR_CODE_RSV0     			    0x09	/**< \brief 保留位0     */
#define AMHW_CAN_ERR_CODE_LEN     			    0x0B	/**< \brief 数据长度代码  */
#define AMHW_CAN_ERR_CODE_FIELD     			0x0A	/**< \brief 数据字段            */
#define AMHW_CAN_ERR_CODE_CRC     			    0x08	/**< \brief CRC序列             */
#define AMHW_CAN_ERR_CODE_CRC_SEP     			0x18	/**< \brief CRC分隔符号   */
#define AMHW_CAN_ERR_CODE_SLOT     			    0x19	/**< \brief 应答slot    */
#define AMHW_CAN_ERR_CODE_SEP     			    0x1B	/**< \brief 应答分隔符号 */
#define AMHW_CAN_ERR_CODE_END     			    0x1A	/**< \brief 帧结束                */
#define AMHW_CAN_ERR_CODE_PAUSE     			0x12	/**< \brief 暂停                     */
#define AMHW_CAN_ERR_CODE_STAERR     			0x11	/**< \brief 启动错误标志   */
#define AMHW_CAN_ERR_CODE_ACCERR     			0x16	/**< \brief 认可错误标志   */
#define AMHW_CAN_ERR_CODE_ALWERR     			0x13	/**< \brief 允许的显性位   */
#define AMHW_CAN_ERR_CODE_ERRSEP     			0x17	/**< \brief 错误分隔符号   */
#define AMHW_CAN_ERR_CODE_OUTDATA     			0x1C	/**< \brief 超载标志             */

/** @} */

/**
 * \brief CAN获取总线错误代码
 *
 * \param[in] icr_val : ICR寄存器的值
 *
 * \return CAN BUS错误代码，参见 \ref grp_amhw_can_err_code  "can bus error code"
 */
am_static_inline
amhw_can_err_code_t amhw_can_error_code_get (uint32_t icr_val)
{
	return ((icr_val >> AMHW_CAN_ICR_ERRBIT) & 0x01f);
}

/**
 * \name CAN BUS错误方向
 * \anchor grp_amhw_can_err_dir
 * @{
 */

typedef uint32_t amhw_can_err_dir_t;                    /**< \brief 总线错误方向   */
#define AMHW_CAN_BUS_ERR_DIR_TX     			0x00	/**< \brief 发送错误   */
#define AMHW_CAN_BUS_ERR_DIR_RX      			0x01	/**< \brief 接收错误 */

/** @} */

/**
 * \brief CAN获取总线错误的方向位
 *
 * \param[in] icr_val : ICR寄存器的值
 *
 * \return CAN BUS错误方向，参见 \ref grp_amhw_can_err_dir  "can bus error dir"
 */
am_static_inline
amhw_can_err_dir_t amhw_can_error_dir_get (uint32_t icr_val)
{
	return ((icr_val >> AMHW_CAN_ICR_ERRDIR) & 0x01);
}

/**
 * \name CAN BUS错误代码
 * \anchor grp_amhw_can_bus_err
 * @{
 */
 
typedef uint32_t amhw_can_bus_err_t;                    /**< \brief 总线错误类型   */
#define AMHW_CAN_BUS_ERR_BIT     			0x00	    /**< \brief 位错误   */
#define AMHW_CAN_BUS_ERR_FORM    			0x01	    /**< \brief 格式错误 */
#define AMHW_CAN_BUS_ERR_STUFF  	 		0x10	    /**< \brief 填充错误 */
#define AMHW_CAN_BUS_ERR_UNKNOWN 			0x11	    /**< \brief 未知错误 */

/** @} */

/**
 * \brief CAN获取bus error类型
 *
 * \param[in] icr_val : ICR寄存器的值
 *
 * \return CAN BUS错误类型，参见 \ref grp_amhw_can_bus_err  "can bus error"
 */
am_static_inline
amhw_can_bus_err_t amhw_can_bus_error_get (uint32_t icr_val)
{
	return ((icr_val >> AMHW_CAN_ICR_ERRC1) & 0x03);
}

/**
 * \name CAN 仲裁丢失错误类型
 * \anchor grp_amhw_can_err_alc
 * @{
 */

typedef uint32_t amhw_can_err_alc_t;                    /**< \brief 总线错误仲裁丢失类型   */
#define AMHW_CAN_BUS_ERR_ALC_FIRST    			0x00	/**< \brief 仲裁在标识符的第一位（MS）丢失   */
#define AMHW_CAN_BUS_ERR_ALC_SRTS    			0x0B	/**< \brief 仲裁在SRTS位丢失   */
#define AMHW_CAN_BUS_ERR_ALC_IDE    			0x0C	/**< \brief 仲裁在IDE位丢失   */
#define AMHW_CAN_BUS_ERR_ALC_12TH    			0x0D	/**< \brief 仲裁在标识符的第12位丢失   */
#define AMHW_CAN_BUS_ERR_ALC_LAST    			0x1E	/**< \brief 仲裁在标识符的最后一位丢失   */
#define AMHW_CAN_BUS_ERR_ALC_RTR    			0x1F	/**< \brief 仲裁在RTR位丢失   */

/** @} */

/**
 * \brief CAN获取仲裁丢失错误类型
 *
 * \param[in] icr_val : ICR寄存器的值
 *
 * \return CAN 取仲裁丢失错误类型，列表中无定义则是对应位丢失
 *         参见 \ref amhw_can_err_alc_t  "can alc error kind"
 */
am_static_inline
amhw_can_err_alc_t amhw_can_error_alc_get (uint32_t icr_val)
{
	return ((icr_val >> AMHW_CAN_ICR_ALCBIT) & 0xff);
}

/**
 * \brief CAN获取中断类型
 *
 * \param[in] icr_val : ICR寄存器的值
 *
 * \return  中断类型，参见 \ref grp_amhw_can_int_type "interrupt type"
 */
am_static_inline
amhw_can_int_type_t amhw_can_intstatus_get (uint32_t icr_val)
{
	return (icr_val & 0x07ff);
}

/**
 * \brief CAN获取ICR捕获状态寄存器的值
 *
 * \param[in] p_hw_can : 指向CAN寄存器块的指针
 *
 * \return  ICR捕获状态寄存器的值
 */
am_static_inline
uint32_t amhw_can_icr_get (amhw_can_t *p_hw_can)
{
	return (p_hw_can->icr);
}


/**
 *@} amhw_if_can
 */

#ifdef __cplusplus
}
#endif


#endif /*__AMHW_CAN_H */

/* end of file */

