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
 * \brief  PWM硬件操作接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-16  snk, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_PWM_H
#define __AMHW_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc177x_8x.h"

/** 
 * \addtogroup amhw_if_pwm
 * \copydoc amhw_pwm.h
 * @{
 */

    
/**
 * \brief PWM寄存器块的结构体
 */
typedef struct amhw_pwm { 
    __IO  uint32_t   ir;        /**< \brief 中断寄存器 */
    __IO  uint32_t   tcr;       /**< \brief 定时器控制寄存器 */
    __IO  uint32_t   tc;        /**< \brief 定时器计数器 */
    __IO  uint32_t   pr;        /**< \brief 预分频寄存器*/
    __IO  uint32_t   pc;        /**< \brief 预分频计数器*/
    __IO  uint32_t   mcr;       /**< \brief 匹配控制寄存器 */
    __IO  uint32_t   mr0;       /**< \brief 匹配寄存器0 */
    __IO  uint32_t   mr1;       /**< \brief 匹配寄存器1 */
    __IO  uint32_t   mr2;       /**< \brief 匹配寄存器2 */  
    __IO  uint32_t   mr3;       /**< \brief 匹配寄存器3*/
    __IO  uint32_t   ccr;       /**< \brief 捕获控制寄存器 */     
    __I   uint32_t   cr0;       /**< \brief 捕获寄存器0 */
    __I   uint32_t   cr1;       /**< \brief 捕获寄存器1 */   
    __I   uint32_t   cr2;       /**< \brief 捕获寄存器2 */  
    __I   uint32_t   cr3;       /**< \brief 捕获寄存器3*/
    __IO  uint32_t   reserved0; /**< \brief 保留                    */
    __IO  uint32_t   mr4;       /**< \brief 匹配寄存器4 */
    __IO  uint32_t   mr5;       /**< \brief 匹配寄存器5 */
    __IO  uint32_t   mr6;       /**< \brief 匹配寄存器6 */
    __IO  uint32_t   pcr;       /**< \brief PWM控制寄存器 */
    __IO  uint32_t   ler;       /**< \brief 加载使能寄存器 */ 
    __IO  uint32_t   reserved01[7]; /**< \brief 保留                           */
    __IO  uint32_t   ctcr;      /**< \brief 计数控制寄存器 */
} amhw_pwm_t;

/**
* \name PWM边沿模式
 * \anchor grp_amhw_pwm_chan_mode
* @{
*/
/** \brief 单边沿模式*/
#define AMHW_PWM_CHANNEL_SINGLE_EDGE    0  	
/** \brief 双边沿模式 */
#define AMHW_PWM_CHANNEL_DUAL_EDGE      1	
/** @} */

/**
* \name 中断寄存器宏定义宏定义
* @{
*/
/** \brief 6个通道的匹配中断位 */
#define AMHW_PWM_IR_PWMMRn(n)    	((uint32_t)((n<4)?(1<<n):(1<<(n+4))))
/** \brief 2个捕获中断位 */
#define AMHW_PWM_IR_PWMCAPn(n)		((uint32_t)(1<<(n+4)))
/** \brief 中断寄存器掩码 */
#define AMHW_PWM_IR_BITMASK			((uint32_t)(0x0000073F))
/** @} */

/**
* \name  定时器控制寄存器宏定义
* @{
*/
/** \brief 控制寄存器位掩码 */
#define AMHW_PWM_TCR_BITMASK			 ((uint32_t)(0x0000000B))
#define AMHW_PWM_TCR_COUNTER_ENABLE      ((uint32_t)(1<<0)) /**< \brief PWM Counter Enable */
#define AMHW_PWM_TCR_COUNTER_RESET       ((uint32_t)(1<<1)) /**< \brief PWM Counter Reset */
#define AMHW_PWM_TCR_PWM_ENABLE          ((uint32_t)(1<<3)) /**< \brief PWM Enable */
/** @} */

/**
* \name 匹配控制寄存器宏定义
* @{
*/
/** \brief 匹配控制寄存器位掩码 */
#define AMHW_PWM_MCR_BITMASK		     ((uint32_t)(0x001FFFFF))
/** \brief 匹配时产生中断 */
#define AMHW_PWM_MCR_INT_ON_MATCH(n)     ((uint32_t)(1<<(((n&0x7)<<1)+(n&0x07))))
/** \brief 匹配时复位 */
#define AMHW_PWM_MCR_RESET_ON_MATCH(n)   ((uint32_t)(1<<(((n&0x7)<<1)+(n&0x07)+1)))
/** \brief 匹配时停止 */
#define AMHW_PWM_MCR_STOP_ON_MATCH(n)    ((uint32_t)(1<<(((n&0x7)<<1)+(n&0x07)+2)))
/** @} */

/**
* \name 捕获控制寄存器宏定义
* @{
*/
/** \brief 捕获控制寄存器位掩码 */
#define AMHW_PWM_CCR_BITMASK			((uint32_t)(0x0000003F))
/** \brief 上升沿位 */
#define AMHW_PWM_CCR_CAP_RISING(n) 	 	((uint32_t)(n == 0 ? 1 : 8))
/** \brief 下降沿位 */
#define AMHW_PWM_CCR_CAP_FALLING(n) 	((uint32_t)(n == 0 ? 2 : 16))
/** \brief 捕获中断事件位 */
#define AMHW_PWM_CCR_INT_ON_CAP(n)  	((uint32_t)(n == 0 ? 4 : 32))
/** @} */


/**
* \name PWM控制寄存器宏定义
* @{
*/
/** \brief 控制寄存器位掩码 */
#define AMHW_PWM_PCR_BITMASK		(uint32_t)0x00007E7C
/** \brief PWM边沿模式选择位 */
#define AMHW_PWM_PCR_PWMSELn(n)   	((uint32_t)(((n&0x7)<2) ? 0 : (1<<n)))
/** \brief 使能PWM输出位 */
#define AMHW_PWM_PCR_PWMENAn(n)   	((uint32_t)(((n&0x7)<1) ? 0 : (1<<(n+8))))
/** @} */


/**
* \name 锁存使能寄存器宏定义
* @{
*/
/** \brief 锁存使能寄存器位掩码 */
#define AMHW_PWM_LER_BITMASK			  ((uint32_t)(0x0000007F))
/** \brief 使能输出 */
#define AMHW_PWM_LER_EN_MATCHn_LATCH(n)   ((uint32_t)((n<7) ? (1<<n) : 0))
/** @} */

/**
 * \brief 中断状态枚举
 */
typedef enum
{
	AMHW_PWM_INTSTAT_MR0 = AMHW_PWM_IR_PWMMRn(0), 	    /**< PWM match 通道0中断标志 */
	AMHW_PWM_INTSTAT_MR1 = AMHW_PWM_IR_PWMMRn(1),		/**< PWM match 通道1中断标志 */
	AMHW_PWM_INTSTAT_MR2 = AMHW_PWM_IR_PWMMRn(2),		/**< PWM match 通道2中断标志 */
	AMHW_PWM_INTSTAT_MR3 = AMHW_PWM_IR_PWMMRn(3),		/**< PWM match 通道3中断标志 */
	AMHW_PWM_INTSTAT_CAP0 = AMHW_PWM_IR_PWMCAPn(0),	    /**< 输入捕获0中断标志                 */
	AMHW_PWM_INTSTAT_CAP1 = AMHW_PWM_IR_PWMCAPn(1),	    /**< 输入捕获0中断标志                 */
	AMHW_PWM_INTSTAT_MR4 = AMHW_PWM_IR_PWMMRn(4),		/**< PWM match 通道4中断标志 */
	AMHW_PWM_INTSTAT_MR5 = AMHW_PWM_IR_PWMMRn(5),		/**< PWM match 通道5中断标志 */
	AMHW_PWM_INTSTAT_MR6 = AMHW_PWM_IR_PWMMRn(6)		/**< PWM match 通道6中断标志 */
}AMHW_PWM_INTSTAT;


/**
 * \brief 设置中断寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_ir_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ir = regvalue;
}

/**
 * \brief 设置定时器控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_tcr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->tcr |= regvalue;
}
/**
 * \brief 清除定时器控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_tcr_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->tcr &= regvalue;
}

/**
 * \brief 设置计数控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_ctcr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ctcr = regvalue;
}


/**
 * \brief 设置匹配控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_mcr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->mcr |= regvalue;
}
/**
 * \brief 清除匹配控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_mcr_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->mcr &= regvalue;
}

/**
 * \brief 设置捕获控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_ccr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ccr |= regvalue;
}

/**
 * \brief 清除捕获控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_ccr_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ccr &= regvalue;
}

/**
 * \brief 设置控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_pcr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->pcr |= regvalue;
}

/**
 * \brief 清除控制寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_pcr_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->pcr &= regvalue;
}
/**
 * \brief 设置锁存使能寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_ler_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ler |= regvalue;
}
/**
 * \brief 清除锁存使能寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_pwm_ler_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ler &= regvalue;
}

/**
 * \brief 设置匹配寄存器的值(仅匹配寄存器0，设置周期)
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] channel  : 通道0
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
int amhw_pwm_mr0_set_period (amhw_pwm_t *p_hw_pwm,
                             uint32_t    channel,
                             uint32_t    regvalue)
{  
    if ((p_hw_pwm != AMHW_PWM1) || (channel != 0)) {
        return -AM_EINVAL;  /* 参数不正确 */
    }
	p_hw_pwm->mr0 = regvalue;
	return AM_OK;
}

/**
 * \brief 设置匹配寄存器的值(匹配寄存器0除外)
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] channel  : 通道0-5
 * \param[in] regvalue : 寄存器值
 * \return    无 
 */
am_static_inline 
int amhw_pwm_mr_val_set (amhw_pwm_t *p_hw_pwm,
                         uint32_t    channel,
                         uint32_t    regvalue)
{  
    if ((p_hw_pwm != AMHW_PWM1) || (channel > 6)) {
        return -AM_EINVAL;  /* 参数不正确 */
    }
    
	switch (channel) {

	case 0:
		p_hw_pwm->mr1 = regvalue;
		break;
	case 1:
		p_hw_pwm->mr2 = regvalue;
		break;
	case 2:
		p_hw_pwm->mr3 = regvalue;
		break;
	case 3:
		p_hw_pwm->mr4 = regvalue;
		break;
	case 4:
		p_hw_pwm->mr5 = regvalue;
		break;
	case 5:
		p_hw_pwm->mr6 = regvalue;
		break;
	}
    return AM_OK;
}
/**
 * \brief 获取匹配寄存器的值
 *
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] channel  : 通道0-6
 * \return    无 
 */
am_static_inline 
int amhw_pwm_mr_val_get (amhw_pwm_t *p_hw_pwm, uint32_t channel)
{  
    uint32_t regvalue;
    if ((p_hw_pwm != AMHW_PWM1) || (channel > 6)) {
        return -AM_EINVAL;  /* 参数不正确 */
    }
    
	switch (channel) {
	case 0:
		regvalue = p_hw_pwm->mr0;
		break;
	case 1:
		regvalue = p_hw_pwm->mr1;
		break;
	case 2:
		regvalue = p_hw_pwm->mr2;
		break;
	case 3:
		regvalue = p_hw_pwm->mr3;
		break;
	case 4:
		regvalue = p_hw_pwm->mr4;
		break;
	case 5:
		regvalue = p_hw_pwm->mr5;
		break;
	case 6:
		regvalue = p_hw_pwm->mr6;
		break;
	}
    return regvalue;
}

/**
 * \brief 获取捕获中断标志寄存器指定位的值 
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] channel  : 指定通道
 * \return    指定位的值0或者1
 */
am_static_inline 
bool_t amhw_pwm_ir_getvalue (amhw_pwm_t *p_hw_pwm, uint32_t channel)
{
    if (channel == 0) {
        return ((p_hw_pwm->ir & AMHW_PWM_INTSTAT_CAP0) ? TRUE : FALSE);    
    } else if (channel == 1) {
        return ((p_hw_pwm->ir & AMHW_PWM_INTSTAT_CAP1) ? TRUE : FALSE);    
    } else  {
        return FALSE;    
    } 
}

/**
 * \brief 清除捕获中断标志  
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] channel  : 指定通道
 * \return    指定位的值0或者1
 */
am_static_inline 
void amhw_pwm_ir_clrflag (amhw_pwm_t *p_hw_pwm, uint32_t channel)
{
    if (channel == 0) {
        p_hw_pwm->ir |= AMHW_PWM_INTSTAT_CAP0;;    
    } 
    if (channel == 1) {
        p_hw_pwm->ir |= AMHW_PWM_INTSTAT_CAP1;;    
    } 
}

/**
 * \brief 获取捕获寄存器的值  
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] channel    : 指通道
 * \return    cr0或cr1的值
 */
am_static_inline 
uint32_t amhw_pwm_get_capture_value (amhw_pwm_t *p_hw_pwm, uint8_t channel)
{ 
    
	switch (channel) {
	case 0:
		return p_hw_pwm->cr0;

	case 1:
		return p_hw_pwm->cr1;

	default:
		return (0);
	}
}

/**
 * \brief 获取中断标志寄存器指定位的值 
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] inttype    : 指定位
 * \return    指定位的值0或者1
 */
am_static_inline 
bool_t amhw_pwm_ir_getflag (amhw_pwm_t *p_hw_pwm, uint32_t inttype)
{
    return ((p_hw_pwm->ir & inttype) ? TRUE : FALSE);    
}

/**
 * \brief 清除中断标志  
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] inttype    : 指定位
 * \return    指定位的值0或者1
 */
am_static_inline 
void amhw_pwm_ir_clrflags (amhw_pwm_t *p_hw_pwm, uint32_t inttype)
{
    p_hw_pwm->ir |= inttype;;    
}
/**
 * \brief 初始化PWM寄存器  
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 */
am_static_inline 
void amhw_pwm_init(amhw_pwm_t *p_hw_pwm)
{
	p_hw_pwm->ir = 0xFF & AMHW_PWM_IR_BITMASK;
	p_hw_pwm->tcr = 0x00;
	p_hw_pwm->ctcr = 0x00;
	p_hw_pwm->mcr = 0x00;
	p_hw_pwm->ccr = 0x00;
	p_hw_pwm->pcr = 0x00;
	p_hw_pwm->ler = 0x00;
}


/**
 * \brief 单边沿、双边沿模式选择  
 * \param[in] p_hw_pwm   : 指向pwm寄存器块的指针
 * \param[in] channel    : 通道
 * \param[in] option     : 模式选择,参见
 *						  \ref grp_amhw_pwm_chan_mode  "Mode Configuration Flags"
 * \return    无
 */
void amhw_pwm_config_edgemode (amhw_pwm_t *p_hw_pwm,
                               uint8_t     channel,
                               uint8_t     option);
/**
 * \brief 配置匹配控制寄存器  
 * \param[in] p_hw_pwm   : 指向pwm寄存器块的指针
 * \param[in] channel    : 通道
 * \param[in] intmatch   : 匹配产生中断
 * \param[in] resetmatch : 匹配复位选择
 * \param[in] stopmatch  : 匹配停止选择
 * \return    无
 */
void amhw_pwm_config_match_reg (amhw_pwm_t *p_hw_pwm,
                                uint8_t     channel,
                                uint8_t     intmatch,
                                uint8_t     resetmatch,
                                uint8_t     stopmatch);
/**
 * \brief 实时更新匹配寄存器的值  
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \param[in] channel    : 指通道
 * \param[in] regvalue   : 寄存器的值
 * \return    无
 */								
void amhw_pwm_fresh_match_reg (amhw_pwm_t *p_hw_pwm,
		                       uint8_t     channel,
					           uint32_t    regvalue);
/**
 * \brief 使能通道x的PWM输出  
 * \param[in] p_hw_pwm   : 指向pwm寄存器块的指针
 * \param[in] channel    : 指通道
 * \return    无
 */					
void amhw_pwm_channel_enable (amhw_pwm_t *p_hw_pwm, uint8_t channel);
/**
 * \brief 禁止通道的PWM输出
 * \param[in] p_hw_pwm   : 指向pwm寄存器块的指针
 * \param[in] channel    : 指通道
 * \return    无
 */
void amhw_pwm_channel_disable (amhw_pwm_t *p_hw_pwm, uint8_t channel);
/**
 * \brief 复位计数器   
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \return    无
 */
void amhw_pwm_reset_counter (amhw_pwm_t *p_hw_pwm);
/**
 * \brief 计数器使能  
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \return    无
 */
void amhw_pwm_counter_enable (amhw_pwm_t *p_hw_pwm);
/**
 * \brief 禁止计数器  
 * \param[in] p_hw_pwm : 指向pwm寄存器块的指针
 * \return    无
 */
void amhw_pwm_counter_disable(amhw_pwm_t *p_hw_pwm);
/**
 * \brief 启动PWM  
 * \param[in] p_hw_pwm   : 指向pwm寄存器块的指针
 * \param[in] state      : 启动或者停止
 * \return    无
 */
void amhw_pwm_tcr_cmd(amhw_pwm_t *p_hw_pwm, bool_t state);
/**
 * \brief 配置捕获控制寄存器的值  
 * \param[in] p_hw_pwm   : 指向pwm寄存器块的指针
 * \param[in] channel    : 指通道
 * \param[in] rising     : TRUE--上升沿选择
 * \param[in] falling    : FALSE--下降沿选择
 * \param[in] intcaption : 事件选择
 * \return    无
 */
void amhw_pwm_config_capture_reg (amhw_pwm_t *p_hw_pwm,
                                  uint8_t     channel,
                                  uint8_t     rising,
                                  uint8_t     falling,
                                  uint8_t     intcaption);
/**
 * \brief 实时更新匹配寄存器的值（仅匹配寄存器0，设置周期）
 * \param[in] p_hw_pwm   : 指向pwm寄存器块的指针
 * \param[in] channel    : 指通道
 * \param[in] regvalue   : 寄存器的值
 * \return    无
 */
void amhw_pwm_fresh_match_reg0_period (amhw_pwm_t *p_hw_pwm,
                                       uint8_t     channel,
					                   uint32_t    regvalue);


/**
 * @} amhw_if_pwm
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_PWM_H */

/* end of file */
    

