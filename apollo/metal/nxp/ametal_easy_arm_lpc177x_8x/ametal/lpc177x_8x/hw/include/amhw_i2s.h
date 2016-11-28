/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site    http://www.zlg.cn/
* e-mail      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief I2S 硬件操作接口 
 *
 * \internal
 * \par Modification History
 * - 1.01 15-07-14  sam, first implementation.
 * \endinternal
 */

#ifndef __AMHW_I2S_H
#define __AMHW_I2S_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_common.h"	
	
/**
 * \addtogroup amhw_if_i2s
 * \copydoc amhw_i2s.h
 * @{ 	
 */	

/**
 * \brief I2S 寄存器结构体	
 */
typedef struct amhw_i2s {
    __IO uint32_t i2sdao;        /**< \brief 数字音频输出寄存器        */
    __IO uint32_t i2sdai;        /**< \brief 数字音频输入寄存器        */
    __O  uint32_t i2stxfifo;     /**< \brief 发送FIFO            */
    __I  uint32_t i2srxfifo;     /**< \brief 接收FIFO            */
    __I  uint32_t i2sstate;      /**< \brief 状态反馈寄存器                  */
    __IO uint32_t i2sdma1;       /**< \brief DMA配置寄存器1       */
    __IO uint32_t i2sdma2;       /**< \brief DMA配置寄存器2       */
    __IO uint32_t i2sirq;        /**< \brief 中断请求控制寄存器         */
    __IO uint32_t i2stxrate;     /**< \brief 发送MCLK分频器                    */
    __IO uint32_t i2srxrate;     /**< \brief 接收MCLK分频器                    */
    __IO uint32_t i2stxbitrate;  /**< \brief 发送位速率分频器                */
    __IO uint32_t i2srxbitrate;  /**< \brief 接收位速率分频器                 */
    __IO uint32_t i2stxmode;     /**< \brief 发送模式控制                          */
    __IO uint32_t i2srxmode;     /**< \brief 接收模式控制                           */
}	amhw_i2s_t;


/**
 * \name 定义I2S数据输出格式
 * \anchor grp_amhw_i2s_i2sdao_cfg_flags
 * @{
 */
/* 设置字宽 */
#define AMHW_I2S_I2SDAO_WORDWIDTH8     0              /**< \brief 字宽8位   */ 
#define AMHW_I2S_I2SDAO_WORDWIDTH16    1              /**< \brief 字宽16位  */ 
#define AMHW_I2S_I2SDAO_WORDWIDTH32    3              /**< \brief 字宽32位  */ 
 
/* 设置声音模式 */  
#define AMHW_I2S_I2SDAO_MONO           (1 << 2)       /**< \brief 单声道  */ 
#define AMHW_I2S_I2SDAO_STEREO         (0 << 2)       /**< \brief 立体声  */ 

#define AMHW_I2S_I2SDAO_STOP           (1 << 3)       /**< \brief 停止输出  */  
 
#define AMHW_I2S_I2SDAO_RESET          (1 << 4)       /**< \brief 复位输出  */ 

#define AMHW_I2S_I2SDAO_NOMUTE         (1 << 15)      /**< \brief 关闭FIFOs  */ 

/* 设置主从模式 */
#define AMHW_I2S_I2SDAO_MASTER        ~(1 << 5)       /**< \brief 主机模式  */ 
#define AMHW_I2S_I2SDAO_SLAVE          (1 << 5)       /**< \brief 从机模式  */ 

#define AMHW_I2S_I2SDAO_WSHALFPERIOD   (0x1FF << 6)   /**< \brief 传输周期 */

#define AMHW_I2S_I2SDAO_MUTE           (1 << 15)      /**< \brief 关闭发送  */ 

/** @} */

/**
 * \name 定义I2S发送格式
 * \anchor grp_amhw_i2s_i2sdai_cfg_flags
 * @{
 */

/* 设置字宽 */
#define AMHW_I2S_I2SDAI_WORDWIDTH8     0              /**< \brief 字宽8位   */
#define AMHW_I2S_I2SDAI_WORDWIDTH16    1              /**< \brief 字宽16位  */ 
#define AMHW_I2S_I2SDAI_WORDWIDTH32    3              /**< \brief 字宽32位  */ 

/* 设置声音模式 */
#define AMHW_I2S_I2SDAI_MONO           (1 << 2)       /**< \brief 单声道  */ 
#define AMHW_I2S_I2SDAI_STEREO         (0 << 2)       /**< \brief 立体声  */ 

#define AMHW_I2S_I2SDAI_STOP           (1 << 3)       /**< \brief 停止输入  */   

#define AMHW_I2S_I2SDAI_RESET          (1 << 4)       /**< \brief 复位输入  */
  
/* 设置主从模式 */
#define AMHW_I2S_I2SDAI_MASTER        ~(1 << 5)       /**< \brief 主机模式  */ 
#define AMHW_I2S_I2SDAI_SLAVE          (1 << 5)       /**< \brief 从机模式  */
#define AMHW_I2S_I2SDAI_WSHALFPERIOD   (0x1FF << 6)   /**< \brief 传输周期 */

/** @} */

/**
 * \name  I2SSTATE 的宏定义 
 * @{     
 */
#define AMHW_I2S_I2SSTATE_IRQ          (1 << 0)       /**< \brief 普通发送接收中断状态  */
 
#define AMHW_I2S_I2SSTATE_DMAREQ1      (1 << 1)       /**< \brief DMA1发送接收中断状态  */
#define AMHW_I2S_I2SSTATE_DMAREQ2      (1 << 2)       /**< \brief DMA2发送接收中断状态  */

#define AMHW_I2S_I2SSTATE_RXLEVEL      (0x0F << 8)    /**< \brief 接收缓存当前值  */

#define AMHW_I2S_I2SSTATE_TXLEVEL      (0x0F << 16)   /**< \brief 发送缓存当前值  */

/** @} */

/**
 * \name 定义I2S DMA1传输格式
 * \anchor grp_amhw_i2s_i2sdma1_cfg_flags
 * @{
 */
#define AMHW_I2S_I2SDMA1_RXENABLE      (1 << 0)       /**< \brief 使能DMA1接收中断 */

#define AMHW_I2S_I2SDMA1_TXENABLE      (1 << 1)       /**< \brief 使能DMA1发送中断 */

#define AMHW_I2S_I2SDMA1_RXDEPTH       (0xF << 8)     /**< \brief 设置DMA1接收FIFO触发中断 深度值*/

#define AMHW_I2S_I2SDMA1_TXDEPTH       (0xF << 16)    /**< \brief 设置DMA1发送FIFO触发中断 深度值*/

/** @} */

/**
 * \name 定义I2S DMA2传输格式
 * \anchor grp_amhw_i2s_i2sdma2_cfg_flags
 * @{
 */ 
#define AMHW_I2S_I2SDMA2_RXENABLE      (1 << 0)       /**< \brief 使能DMA2接收中断 */

#define AMHW_I2S_I2SDMA2_TXENABLE      (1 << 1)       /**< \brief 使能DMA2发送中断 */
 
#define AMHW_I2S_I2SDMA2_RXDEPTH       (0xF << 8)     /**< \brief 设置DMA2接收FIFO触发中断 深度值*/

#define AMHW_I2S_I2SDMA2_TXDEPTH       (0xF << 16)    /**< \brief 设置DMA2发送FIFO触发中断 深度值*/

/** @} */

/**
 * \name I2SIRQ 的宏定义
 * @{
 */

#define AMHW_I2S_RXIRQ_ENABLE          (1 << 0)       /**< \brief 使能接收中断 */

#define AMHW_I2S_TXIRQ_ENABLE          (1 << 1)       /**< \brief 使能发送中断 */

#define AMHW_I2S_RXIRQ_DEPTH           (0xF << 8)     /**< \brief 设置接收FIFO触发中断 深度值*/

#define AMHW_I2S_TXIRQ_DEPTH           (0xF << 16)    /**< \brief 设置发送FIFO触发中断 深度值*/

/** @} */

/**
 * \name I2SRXMODE 的宏定义
 * @{  
 */
#define AMHW_I2S_RXCLKSEL_FRACCLOCK    0              /**< \brief 设置接收时钟为分频时钟*/
#define AMHW_I2S_RXCLKSEL_RXMCLK       2              /**< \brief 设置发送时钟为主时钟*/
#define AMHW_I2S_I2SRXMODE_RX4PIN      (1 << 2)       /**< \brief 设置为4-pin接收模式*/

#define AMHW_I2S_I2SRXMODE_RXMCENA     (1 << 3)       /**< \brief 使能接收主时钟*/

/** @} */

/**
 * \name  I2STXMODE 的宏定义 
 * @{     
 */
#define AMHW_I2S_TXCLKSEL_FRACCLOCK    0               /**< \brief 设置发送时钟为分频时钟*/
#define AMHW_I2S_TXCLKSEL_TXMCLK       2               /**< \brief 设置接收时钟为主时钟*/

#define AMHW_I2S_I2STXMODE_TX4PIN      (1 << 2)        /**< \brief 设置为4-pin接收模式*/

#define AMHW_I2S_I2STXMODE_TXMCENA     (1 << 3)        /**< \brief 使能发送主时钟*/

/** @} */

/**
 * \brief I2S中断使能
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] int_enable : 使能位，值为 AMHW_I2S_* (AMHW_I2S_RXIRQ_ENABLE)
 *
 * \return    无
 */
am_static_inline
void amhw_i2s_int_enable (amhw_i2s_t *p_hw_i2s, uint32_t int_enable)
{
     p_hw_i2s->i2sirq |= int_enable;
}

/**
 * \brief  I2S 中断禁能
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] int_disable : 禁能位，值为 AMHW_I2S_* (AMHW_I2S_TXIRQ_ENABLE)
 *
 * \return    无
 */
am_static_inline
void amhw_i2s_int_disable (amhw_i2s_t *p_hw_i2s, uint32_t int_disable)
{
     p_hw_i2s->i2sirq &= ~int_disable;
}

/**
 * \brief I2S 发送中断深度触发值设置
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] depth : 深度值  ，值为 AMHW_I2S_* (#AMHW_I2S_TXIRQ_DEPTH)
 *
 * \return    无
 */
am_static_inline
void amhw_i2s_txdepth_irqset (amhw_i2s_t *p_hw_i2s, char depth)
{
     p_hw_i2s->i2sirq |= depth << 16;
	   p_hw_i2s->i2sirq |= 1 << 8;     /* 默认接收level值为1 */
}

/**
 * \brief  I2S 接收中断深度触发值设置
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] depth : 深度值 ， 值为   AMHW_I2S_* (#AMHW_I2S_RXIRQ_DEPTH)
 *
 * \return    无
 */
am_static_inline
void amhw_i2s_rxdepth_irqset (amhw_i2s_t *p_hw_i2s, char depth)
{
     p_hw_i2s->i2sirq |= depth << 8;
	   p_hw_i2s->i2sirq |= 8 << 16;   /* 默认发送level值为8 */
}

/**
 * \brief 获取I2S中断状态
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 *
 * \return  I2S中断状态
 */
am_static_inline
uint32_t amhw_i2s_stat_get (amhw_i2s_t *p_hw_i2s)
{
    return p_hw_i2s->i2sstate; 
}

/**
 * \brief 配置I2S发送格式
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] cfg_flags  : 配置值 ， 参见
 *                         \ref grp_amhw_i2s_i2sdao_cfg_flags "Transfer Configuration Flags"
 *                         
 * \return  无
 */
am_static_inline
void amhw_i2s_i2sdao_config (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdao &= cfg_flags;
}

/**
 * \brief 配置主机发送
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] cfg_flags  : 配置值，值为AMHW_I2S_I2SDAO_MASTER
 *                         
 * \return  无
 */
am_static_inline
void amhw_i2s_i2sdao_master (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdao &= cfg_flags;
}

/**
 * \brief 配置从机发送
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] cfg_flags  : 配置值，值为AMHW_I2S_I2SDAO_SLAVE
 *                         
 * \return  无
 */
am_static_inline
void amhw_i2s_i2sdao_slave (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdao |= cfg_flags;
}


/**
 * \brief 配置I2S接收格式
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] cfg_flags  : 配置值， 参见
 *                         \ref grp_amhw_i2s_i2sdai_cfg_flags "Receive Configuration Flags"
 *                         
 * \return  无
 */
am_static_inline
void amhw_i2s_i2sdai_config (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdai |= cfg_flags;
}

/**
 * \brief 配置主机接收
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] cfg_flags  : 配置值，值为AMHW_I2S_I2SDAI_MASTER
 *                         
 * \return  无
 */
am_static_inline
void amhw_i2s_i2sdai_master (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdai &= cfg_flags;
}

/**
 * \brief 配置从机接收
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] cfg_flags  : 配置值，值为AMHW_I2S_I2SDAI_SLAVE
 *                         
 * \return  无
 */
am_static_inline
void amhw_i2s_i2sdai_slave (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdai &= cfg_flags;
}


/**
 * \brief 使能传输
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针       
 *
 * \return  无
 */
am_static_inline
void amhw_i2s_transmit_enable(amhw_i2s_t *p_hw_i2s)
{
    p_hw_i2s->i2sdai &= ~(AMHW_I2S_I2SDAI_STOP | AMHW_I2S_I2SDAI_RESET);
	p_hw_i2s->i2sdao &= ~(AMHW_I2S_I2SDAO_STOP | AMHW_I2S_I2SDAO_RESET);
    p_hw_i2s->i2sdao &= ~AMHW_I2S_I2SDAO_NOMUTE;	 
}
	
/**
 * \brief 配置I2S的DMA1的格式
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针       
 * \param[in] cfg_flags  : 配置值，参见
 *                         \ref grp_amhw_i2s_i2sdma1_cfg_flags"DMA1 Transmit Configuration Flags"
 *                         
 * \return  无
 */
am_static_inline
void amhw_i2s_i2sdma1_config (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdma1 |= cfg_flags;
}

/**
 * \brief 配置I2S的DMA2的格式
 *
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针       
 * \param[in] cfg_flags  : 配置值，参见
 *                         \ref grp_amhw_i2s_i2sdma2_cfg_flags"DMA2 Transmit Configuration Flags"
 *                         
 * \return  无
 */
am_static_inline
void amhw_i2s_i2sdma2_config (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdma2 |= cfg_flags;
}

/**
 * \brief 获取I2S当前接收数据个数值
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针      
 *
 * \return 无
 */
am_static_inline
uint32_t amhw_i2s_rxcurlevel_get (amhw_i2s_t *p_hw_i2s)
{
    return (char)((p_hw_i2s->i2sstate) >> 8); 
}

/**
 * \brief 获取I2S当前发送数据个数值
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针 
 *
 * \return 无
 */
am_static_inline
uint32_t amhw_i2s_txcurlevel_get (amhw_i2s_t *p_hw_i2s)
{
    return (char)((p_hw_i2s->i2sstate) >> 16);
}

/**
 * \brief 设置I2S发送速率
 * \param[in] p_hw_i2s :  指向I2S寄存器块的指针 
 * \param[in] tx_rate : 16位无符号整形
 *
 * \return 无
 */
am_static_inline
void amhw_i2s_i2stxrate_set (amhw_i2s_t *p_hw_i2s, uint32_t tx_rate)
{
    p_hw_i2s->i2stxrate |= tx_rate; 
}

/**
 * \brief 设置I2S接收速率
 * \param[in] p_hw_i2s :  指向I2S寄存器块的指针 
 * \param[in] rx_rate : 16位无符号整形
 *
 * \return 无
 */
am_static_inline
void amhw_i2s_i2srxrate_set (amhw_i2s_t *p_hw_i2s, uint32_t rx_rate)
{
    p_hw_i2s->i2srxrate |= rx_rate; 
}

/**
 * \brief 设置I2S接收模式
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针 
 * \param[in] mode_flag : 值为AMHW_I2S_* (AMHW_I2S_TXCLKSEL_FRACCLOCK)
 *
 * \return 无
 */
am_static_inline
void amhw_i2s_rxmode_set (amhw_i2s_t *p_hw_i2s, char mode_flag)
{
    p_hw_i2s->i2srxmode |= mode_flag; 
}

/**
 * \brief 设置I2S发送模式
 * \param[in] p_hw_i2s : 指向I2S寄存器块的指针
 * \param[in] mode_flag : 配置值，值为AMHW_I2S_* (AMHW_I2S_RXCLKSEL_FRACCLOCK)
 *
 * \return 无
 */
am_static_inline
void amhw_i2s_txmode_set (amhw_i2s_t *p_hw_i2s, char mode_flag)
{
    p_hw_i2s->i2stxmode |= mode_flag; 
}	


/** @}*/


/**
 * @} amhw_if_i2s
 */	
	
#ifdef __cplusplus
}
#endif

#endif /* __AMHW_I2S_H */

/* end of file */

