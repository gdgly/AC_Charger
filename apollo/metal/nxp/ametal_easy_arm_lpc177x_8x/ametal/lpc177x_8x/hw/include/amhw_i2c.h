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
 * \brief I2C 硬件操作接口
 * 
 *   
 *
 * \internal
 * \par Modification History
 * - 1.00 15-06-16  snk, first implementation.
 * \endinternal
 */

#ifndef __AMHW_I2C_H
#define __AMHW_I2C_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
#include "am_i2c.h"
/**
 * @addtogroup amhw_if_i2c
 * @copydoc amhw_i2c.h
 * @{
 */
    
/**
 * \brief I2C 寄存器块结构体
 */
typedef struct amhw_i2c {
    __IO uint32_t  conset;           /**< \brief I2C 控制置位寄存器       */
    __I  uint32_t  stat;             /**< \brief I2C 状态寄存器           */
    __IO uint32_t  dat;              /**< \brief I2C 数据寄存器           */
    __IO uint32_t  adr0;             /**< \brief I2C 从地址寄存器0        */
    __IO uint32_t  sclh;             /**< \brief I2C SCL占空比寄存器高半字 */
    __IO uint32_t  scll;             /**< \brief I2C SCL占空比寄存器低半字 */
    __O  uint32_t  conclr;           /**< \brief I2C 控制清零寄存器        */
    __O  uint32_t  mmctrl;           /**< \brief I2C 监控模式控制寄存器    */
	__IO uint32_t  adr1;             /**< \brief I2C 从地址寄存器1         */
    __IO uint32_t  adr2;             /**< \brief I2C 从地址寄存器2         */
    __IO uint32_t  adr3;             /**< \brief I2C 从地址寄存器3         */
    __I  uint32_t  data_buffer;      /**< \brief I2C 数据缓冲寄存器        */
    __IO uint32_t  mask0;            /**< \brief I2C 从地址屏蔽寄存器0     */
    __IO uint32_t  mask1;            /**< \brief I2C 从地址屏蔽寄存器1     */
    __IO uint32_t  mask2;            /**< \brief I2C 从地址屏蔽寄存器2     */
    __IO uint32_t  mask3;            /**< \brief I2C 从地址屏蔽寄存器3     */
} amhw_i2c_t;



/**
 * \name I2C 控制置位寄存器各个位详细定义
 * \anchor grp_amhw_i2c_conset_bit
 * @{
 */

#define AMHW_I2C_I2CONSET_AA			((0x04)) /**< \brief  应答标志 */
#define AMHW_I2C_I2CONSET_SI			((0x08)) /**< \brief  中断标志 */
#define AMHW_I2C_I2CONSET_STO			((0x10)) /**< \brief  结束标志 */
#define AMHW_I2C_I2CONSET_STA			((0x20)) /**< \brief  开始标志 */
#define AMHW_I2C_I2CONSET_I2EN			((0x40)) /**< \brief  使能标志 */

/** @} */

/**
 * \name I2C 控制清零寄存器各个位详细定义
 * \anchor grp_amhw_i2c_conclr_bit
 * @{
 */

#define AMHW_I2C_I2CONCLR_AAC			((1<<2)) /**< \brief 应答标志 */
#define AMHW_I2C_I2CONCLR_SIC			((1<<3)) /**< \brief 中断标志 */
#define AMHW_I2C_I2CONCLR_STAC			((1<<5)) /**< \brief 开始标志 */
#define AMHW_I2C_I2CONCLR_I2ENC			((1<<6)) /**< \brief 使能标志 */

/** @} */

/**
 * \name I2C 数据寄存器位定义
 * @{
 */ 

/** \brief I2C数据寄存器掩码 */
#define AMHW_I2C_I2DAT_BITMASK			((0xFF))

/** \brief 空闲数据值 */
#define AMHW_I2C_I2DAT_IDLE_CHAR		(0xFF)

/** @} */

/**
 * \name I2C 监控模式控制寄存器位定义
 * @{
 */ 
 
#define AMHW_I2C_I2MMCTRL_MM_ENA		((1<<0))		/**< \brief 监控模式使能       */
#define AMHW_I2C_I2MMCTRL_ENA_SCL		((1<<1))		/**< \brief 时钟输出使能       */
#define AMHW_I2C_I2MMCTRL_MATCH_ALL		((1<<2))		/**< \brief 选择中断寄存器匹配 */
#define AMHW_I2C_I2MMCTRL_BITMASK		((0x07))		/**< \brief I2MMCTRL寄存器掩码 */

/** @} */

/**
 * \name I2C 数据缓冲寄存器位定义
 * @{
 */ 

/** \brief 数据缓存掩码 */
#define AMHW_I2DATA_BUFFER_BITMASK		((0xFF))

/** @} */

/**
 * \name I2C 状态寄存器宏定义
 * @{
 */

#define AMHW_I2C_STAT_CODE_BITMASK		((0xF8)) /**< \brief 状态寄存器掩码 */

#define AMHW_I2C_I2STAT_NO_INF			((0xF8)) /**< \brief 无关信息       */

/** @} */

/**
 * \name I2C 状态寄存器值定义
 * @{
 */

#define AMHW_I2C_SETUP_STATUS_ARBF   (1<<8)	  /**< \brief 仲裁错误    */
#define AMHW_I2C_SETUP_STATUS_NOACKF (1<<9)	  /**< \brief 无应答返回  */
#define AMHW_I2C_SETUP_STATUS_DONE   (1<<10)  /**< \brief 完成状态    */

/** @} */

/**
 * \name I2C 主发送模式定义
 * @{
 */
/** \brief 起始条件已发送          */
#define AMHW_I2C_I2STAT_M_TX_START					((0x08))
/** \brief 重复起始条件已发送      */
#define AMHW_I2C_I2STAT_M_TX_RESTART				((0x10))
/** \brief SLA+W已发送，ACK已接收  */
#define AMHW_I2C_I2STAT_M_TX_SLAW_ACK				((0x18))
/** \brief SLA+W已发送，NACK已接收 */
#define AMHW_I2C_I2STAT_M_TX_SLAW_NACK				((0x20))
/** \brief 数据已发送，ACK已接收   */
#define AMHW_I2C_I2STAT_M_TX_DAT_ACK				((0x28))
/** \brief 数据已发送，NACK已接收  */
#define AMHW_I2C_I2STAT_M_TX_DAT_NACK				((0x30))
/** \brief 仲裁丢失   */
#define AMHW_I2C_I2STAT_M_TX_ARB_LOST				((0x38))

/** @} */


/**
 * \name I2C 主接收模式定义
 * @{
 */
/** \brief 起始条件已发送    */
#define AMHW_I2C_I2STAT_M_RX_START					((0x08))
/** \brief 重复起始条件已发送      */
#define AMHW_I2C_I2STAT_M_RX_RESTART				((0x10))
/** \brief 仲裁丢失 */
#define AMHW_I2C_I2STAT_M_RX_ARB_LOST				((0x38))
/** \brief SLA+R已发送，ACK已接收  */
#define AMHW_I2C_I2STAT_M_RX_SLAR_ACK				((0x40))
/** \brief SLA+R已发送，NACK已接收 */
#define AMHW_I2C_I2STAT_M_RX_SLAR_NACK				((0x48))
/** \brief 数据已接收，ACK已返回   */
#define AMHW_I2C_I2STAT_M_RX_DAT_ACK				((0x50))
/** \brief 数据已接收，NACK已返回   */
#define AMHW_I2C_I2STAT_M_RX_DAT_NACK				((0x58)) 

/** @} */

/**
 * \name I2C 从接收模式定义
 * @{
 */
/** \brief 从机地址已接收，应答已返回    */
#define AMHW_I2C_I2STAT_S_RX_SLAW_ACK				((0x60))

/** \brief 仲裁丢失 */
#define AMHW_I2C_I2STAT_S_RX_ARB_LOST_M_SLA			((0x68))

/** \brief 通用调用地址已接收，应答已返回 */
#define AMHW_I2C_I2STAT_S_RX_GENCALL_ACK			((0x70))

/** \brief 仲裁丢失  */
#define AMHW_I2C_I2STAT_S_RX_ARB_LOST_M_GENCALL		((0x78))

/** \brief 从机模式：数据已接收，应答已返回    */
#define AMHW_I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK		((0x80))
/** \brief 从机模式：数据已接收，非应答已返回  */
#define AMHW_I2C_I2STAT_S_RX_PRE_SLA_DAT_NACK		((0x88))
/** \brief 通用调用数据已接收，应答已返回      */
#define AMHW_I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK	((0x90))
/** \brief 通用调用数据已接收，非应答已返回    */
#define AMHW_I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK	((0x98))
/** \brief 停止条件/重复起始条件已接收         */
#define AMHW_I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX	((0xA0))

/** @} */

/**
 * \name I2C 从发送模式定义
 * @{
 */

/** \brief SLA+R已接收，应答已返回  */
#define AMHW_I2C_I2STAT_S_TX_SLAR_ACK				((0xA8))

/** \brief 仲裁丢失 */
#define AMHW_I2C_I2STAT_S_TX_ARB_LOST_M_SLA			((0xB0))

/** \brief 数据已经发生，应答已返回    */
#define AMHW_I2C_I2STAT_S_TX_DAT_ACK				((0xB8))
/** \brief 数据已经发生，非应答已返回  */
#define AMHW_I2C_I2STAT_S_TX_DAT_NACK				((0xC0))
/** \brief 最后一个数据已经发生，NACK已返回   */
#define AMHW_I2C_I2STAT_S_TX_LAST_DAT_ACK			((0xC8))

/** \brief 从机模式超时  */
#define AMHW_I2C_SLAVE_TIME_OUT						0x10000UL

/** @} */


/**
 * @brief 传输模式定义
 */
typedef enum {
	I2C_MODE_POLLING = 0,		/**< \brief 轮询模式 */
	I2C_MODE_INTERRUPT			/**< \brief 中断模式 */
} i2c_mode_type_t;



/**
 * \brief  设置conset寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \param[in] value    ：设置值，参见
 *                      \ref grp_amhw_i2c_conset_bit
 * \return 无
 */
am_static_inline
void amhw_i2c_conset_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->conset = value;
}

/**
 * \brief  获取conset寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \return 当前寄存器值
 */
am_static_inline
uint32_t amhw_i2c_conset_val_get (amhw_i2c_t *p_hw_i2c)
{
	return p_hw_i2c->conset;
}

/**
 * \brief  设置conclr寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \param[in] value    ：设置值，参见
 *                      \ref grp_amhw_i2c_conclr_bit
 * \return 无
 */
am_static_inline
void amhw_i2c_conclr_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->conclr = value;
}

/**
 * \brief  设置dat寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \param[in] value    ：设置值
 * \return 无
 */
am_static_inline
void amhw_i2c_dat_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->dat = value;
}

/**
 * \brief  获取dat寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \return 当前寄存器值
 */
am_static_inline
uint32_t amhw_i2c_dat_val_get (amhw_i2c_t *p_hw_i2c)
{
	return p_hw_i2c->dat;
}

/**
 * \brief  获取stat寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \return 当前寄存器值
 */
am_static_inline
uint32_t amhw_i2c_stat_val_get (amhw_i2c_t *p_hw_i2c)
{
	return p_hw_i2c->stat;
}

/**
 * \brief  设置sclh寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \param[in] value    ：设置值
 * \return 无
 */
am_static_inline
void amhw_i2c_sclh_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->sclh = value;
}

/**
 * \brief  获取sclh寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \return 当前寄存器值
 */
am_static_inline
uint32_t amhw_i2c_sclh_val_get (amhw_i2c_t *p_hw_i2c)
{
	return p_hw_i2c->sclh;
}

/**
 * \brief  设置scll寄存器值
 * \param[in] p_hw_i2c ：外设指针
 * \param[in] value    ：设置值
 * \return 无
 */
am_static_inline
void amhw_i2c_scll_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->scll = value;
}


/**
 * \brief  设置时钟
 * \param[in] p_hw_i2c     : 指向I2C寄存器块的指针
 * \param[in] target_clock : I2C时钟
 *
 * \return 无
 */
void amhw_i2c_setclock (amhw_i2c_t *p_hw_i2c, uint32_t target_clock);

/**
 * \brief  I2C初始化
 * \param[in] p_hw_i2c  : 指向I2C寄存器块的指针
 * \param[in] clockrate : I2C时钟
 *
 * \return 无
 */
void amhw_i2c_init (amhw_i2c_t *p_hw_i2c, uint32_t clockrate);

/**
 * \brief  主模式处理
 * \param[in] p_hw_i2c  : 指向I2C寄存器块的指针
 *
 * \return 无
 */
void amhw_i2c_master_handler (amhw_i2c_t  *p_hw_i2c);


/**
 * \brief  主模式传输完成
 * \param[in] p_hw_i2c  : 指向I2C寄存器块的指针
 *
 * \return 无
 */
uint32_t amhw_i2c_mastertransfer_ok (amhw_i2c_t *p_hw_i2c);

/**
 * \brief 从模式处理
 * \param[in] p_hw_i2c  : 指向I2C寄存器块的指针
 *
 * \return 无
 */
void amhw_i2c_slave_handler (amhw_i2c_t  *p_hw_i2c);

/**
 * \brief  从模式传输完成
 * \param[in] p_hw_i2c  : 指向I2C寄存器块的指针
 *
 * \return 无
 */
uint32_t amhw_i2c_slave_transfer_ok (amhw_i2c_t *p_hw_i2c);

/**
 * \brief  I2C使能
 * \param[in] p_hw_i2c  : 指向I2C寄存器块的指针
 * \param[in] state     : 使能或使能标志
 *
 * \return 无
 */
void amhw_i2c_cmd (amhw_i2c_t* p_hw_i2c, bool_t state);

/**
 * \brief     获取I2C号
 * \param[in] p_hw_i2c : I2C外设AMHW_I2C0..2
 * \return    I2C号    : 0..2
 */
int32_t amhw_i2c_getnum (amhw_i2c_t *p_hw_i2c);

/**
 * \brief     i2c中断函数
 *
 * \param[in] p_hw_i2c : I2C外设AMHW_I2C0..2
 * \param[in] p_trans  : 传输变量
 *
 * \return    AM_OK     : 成功
 * \return    AM_ERROR  : 失败
 */
int amhw_i2c_handler (amhw_i2c_t  *p_hw_i2c,am_i2c_transfer_t *p_trans);

/**
 * \brief     i2c中断传输函数
 * \param[in] p_hw_i2c      : I2C外设AMHW_I2C0..2
 * \param[in] transfer_cfg  : 传输变量
 *
 * \return    无
 */
bool_t amhw_i2c_int_transfer (amhw_i2c_t *p_hw_i2c, am_i2c_transfer_t  *transfer_cfg);

/**
 * \brief     主模式数据收发
 * \param[in] p_hw_i2c      : I2C外设AMHW_I2C0..2
 * \param[in] transfer_cfg  : 传送结构体
 * \param[in] option        : 传送方式
 * \return    成功返回1，失败返回0
 */
bool_t amhw_i2c_master_transfer (amhw_i2c_t         *p_hw_i2c,
		                         am_i2c_transfer_t  *transfer_cfg,
								 i2c_mode_type_t     option);

/**
 * \brief     从模式数据收发
 * \param[in] p_hw_i2c      : I2C外设AMHW_I2C0..2
 * \param[in] transfer_cfg  : 传送结构体
 * \param[in] option        : 传送方式
 * \return    成功返回1，失败返回0
 */
bool_t amhw_i2c_slave_transfer (amhw_i2c_t        *p_hw_i2c,
		                        am_i2c_transfer_t *transfer_cfg,
								i2c_mode_type_t    option);

/** 
 * @} amhw_if_i2c 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_I2C_H */


/* end of file */
