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
 * \brief  MCPWM硬件操作接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-02  snk, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_MCPWM_H
#define __AMHW_MCPWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_mcpwm
 * \copydoc amhw_mcpwm.h
 * @{
 */

    
/**
 * \brief MCPWM寄存器块的结构体
 */
typedef struct amhw_mcpwm {
    __I   uint32_t  mccon;         /**< \brief PWM控制寄存器读        */
    __O   uint32_t  mcconset;      /**< \brief PWM控制寄存器写        */
    __O   uint32_t  mcconclr;      /**< \brief PWM控制寄存器清零      */
    __I   uint32_t  mccapcon;      /**< \brief 捕获寄存器读           */
    __O   uint32_t  mccapconset;   /**< \brief 捕获寄存器写           */
    __O   uint32_t  mccapconclr;   /**< \brief 捕获寄存器清零         */  
    __IO  uint32_t  mctc0;         /**< \brief 定时计数寄存器，通道0  */
    __IO  uint32_t  mctc1;         /**< \brief 定时计数寄存器，通道1  */
    __IO  uint32_t  mctc2;         /**< \brief 定时计数寄存器，通道2  */
    __IO  uint32_t  mclim0;        /**< \brief 界限寄存器，通道0      */
    __IO  uint32_t  mclim1;        /**< \brief 界限寄存器，通道1      */
    __IO  uint32_t  mclim2;        /**< \brief 界限寄存器，通道2      */
    __IO  uint32_t  mcmat0;        /**< \brief 匹配寄存器，通道0      */
    __IO  uint32_t  mcmat1;        /**< \brief 匹配寄存器，通道1      */
    __IO  uint32_t  mcmat2;        /**< \brief 匹配寄存器，通道2      */  
    __IO  uint32_t  mcdt;          /**< \brief 死区时间寄存器         */
    __IO  uint32_t  mccp;          /**< \brief 通信格式寄存器         */     
    __IO  uint32_t  mccap0;        /**< \brief 捕获寄存器，通道0      */
    __IO  uint32_t  mccap1;        /**< \brief 捕获寄存器，通道1      */   
    __IO  uint32_t  mccap2;        /**< \brief 捕获寄存器，通道2      */  
    __I   uint32_t  mcinten;       /**< \brief 中断使能读寄存器       */
    __O   uint32_t  mcintenset;    /**< \brief 中断使能写寄存器       */
    __O   uint32_t  mcintenclr;    /**< \brief 中断清零寄存器         */
    __I   uint32_t  mccntcon;      /**< \brief 计数控制读寄存器       */
    __O   uint32_t  mccntconset;   /**< \brief 计数控制写寄存器       */
    __O   uint32_t  mccntconclr;   /**< \brief 计数控制清零寄存器     */ 
    __I   uint32_t  mcintf;        /**< \brief 中断标志读寄存器       */
    __O   uint32_t  mcintfset;     /**< \brief 中断标志写寄存器       */
    __O   uint32_t  mcintfclr;     /**< \brief 中断标志清零寄存器     */
    __O   uint32_t  mccapclr;      /**< \brief 捕获清除寄存器         */
} amhw_mcpwm_t;


/**
* \name MCPWM通道模式
* @{
*/
/** \brief MCPWM通道的边沿模式  */
#define AMHW_MCPWM_CHANNEL_EDGE_MODE		((uint32_t)(0))
/** \brief MCPWM通道的中心模式  */
#define AMHW_MCPWM_CHANNEL_CENTER_MODE		((uint32_t)(1))

/** \brief MCOA和MCOB引脚的极性：低电平是无效状态，高电平是有效状态 */
#define AMHW_MCPWM_CHANNEL_PASSIVE_LO		((uint32_t)(0))
/** \brief MCOA和MCOB引进的极性：高电平是无效状态，低电平是有效状态 */
#define AMHW_MCPWM_CHANNEL_PASSIVE_HI		((uint32_t)(1))

/**
 * @}
 */
 
 /**
 * \name 定义中断类型参数
 * \anchor grp_amhw_mcpwm_inttype_flags
 * @{
 */
/** \brief 通道0的界限中断 */
#define AMHW_MCPWM_INTFLAG_LIM0	AMHW_MCPWM_INT_ILIM(0)
/** \brief 通道0的匹配中断 */
#define AMHW_MCPWM_INTFLAG_MAT0	AMHW_MCPWM_INT_IMAT(0)
/** \brief 通道0的捕获中断 */
#define AMHW_MCPWM_INTFLAG_CAP0	AMHW_MCPWM_INT_ICAP(0)

/** \brief 通道1的界限中断 */
#define AMHW_MCPWM_INTFLAG_LIM1	AMHW_MCPWM_INT_ILIM(1)
/** \brief 通道1的匹配中断 */
#define AMHW_MCPWM_INTFLAG_MAT1	AMHW_MCPWM_INT_IMAT(1)
/** \brief 通道1的捕获中断 */
#define AMHW_MCPWM_INTFLAG_CAP1	AMHW_MCPWM_INT_ICAP(1)

/** \brief 通道2的界限中断 */
#define AMHW_MCPWM_INTFLAG_LIM2	AMHW_MCPWM_INT_ILIM(2)
/** \brief 通道2的匹配中断 */
#define AMHW_MCPWM_INTFLAG_MAT2	AMHW_MCPWM_INT_IMAT(2)
/** \brief 通道2的捕获中断 */
#define AMHW_MCPWM_INTFLAG_CAP2	AMHW_MCPWM_INT_ICAP(2)

/** \brief 快速中止中断 */
#define AMHW_MCPWM_INTFLAG_ABORT	AMHW_MCPWM_INT_ABORT


/** @} */

 /**
 * \name 定义输出模式配置参数
 * \anchor grp_amhw_mcpwm_patent_flags
 * @{
 */

/** \brief MCOA0连接内部MCOA0 */
#define AMHW_MCPWM_PATENT_A0		((uint32_t)(1<<0))
/** \brief MCOB0连接内部MCOA0 */
#define AMHW_MCPWM_PATENT_B0		((uint32_t)(1<<1))
/** \brief MCOA1连接内部MCOA0 */
#define AMHW_MCPWM_PATENT_A1		((uint32_t)(1<<2))
/** \brief MCOB1连接内部MCOA0 */
#define AMHW_MCPWM_PATENT_B1		((uint32_t)(1<<3))
/** \brief MCOA2连接内部MCOA0 */
#define AMHW_MCPWM_PATENT_A2		((uint32_t)(1<<4))
/** \brief MCOB2连接内部MCOA0 */
#define AMHW_MCPWM_PATENT_B2		((uint32_t)(1<<5))	

/** @} */

/**
 * \name MCPWM控制寄存器各个位详细定义
 * @{ 
 */

/**  \brief 启动通道n  */
#define AMHW_MCPWM_CON_RUN(n)		((n<=2) ? ((uint32_t)(1<<((n*8)+0))) : (0))
/**  \brief  通道n边沿/中心模式 */
#define AMHW_MCPWM_CON_CENTER(n)	((n<=2) ? ((uint32_t)(1<<((n*8)+1))) : (0))	
/**  \brief  选择A/B相极性 */
#define AMHW_MCPWM_CON_POLAR(n)		((n<=2) ? ((uint32_t)(1<<((n*8)+2))) : (0))	
/**  \brief  死区时间设置 */
#define AMHW_MCPWM_CON_DTE(n)		((n<=2) ? ((uint32_t)(1<<((n*8)+3))) : (0))	
/**  \brief  使能更新寄存器 */
#define AMHW_MCPWM_CON_DISUP(n)		((n<=2) ? ((uint32_t)(1<<((n*8)+4))) : (0))
/**  \brief  极性控制 */
#define AMHW_MCPWM_CON_INVBDC		((uint32_t)(1<<29))	
/**  \brief  三相AC模式选择 */
#define AMHW_MCPWM_CON_ACMODE		((uint32_t)(1<<30))	
/**  \brief  三相DC模式选择 */
#define AMHW_MCPWM_CON_DCMODE		((uint32_t)((uint32_t)1<<31))	

/** @} */


/**
* \name 捕获控制寄存器位
* @{
*/
/** \brief 使能通道上升沿捕获事件 */
#define AMHW_MCPWM_CAPCON_CAPMCI_RE(cap,mci)	(((cap<=2)&&(mci<=2)) ? ((uint32_t)(1<<((cap*6)+(mci*2)+0))) : (0))
/** \brief 使能通道下降沿捕获事件 */
#define AMHW_MCPWM_CAPCON_CAPMCI_FE(cap,mci)	(((cap<=2)&&(mci<=2)) ? ((uint32_t)(1<<((cap*6)+(mci*2)+1))) : (0))
/** \brief 定时器复位捕获事件 */
#define AMHW_MCPWM_CAPCON_RT(n)				((n<=2) ? ((uint32_t)(1<<(18+(n)))) : (0))
/** \brief 硬件噪声过滤 */
#define AMHW_MCPWM_CAPCON_HNFCAP(n)			((n<=2) ? ((uint32_t)(1<<(21+(n)))) : (0))
/** @} */


/**
* \name 中断使能、中断标志位
* @{
*/
/** \brief 通道n界限寄存器中断 */
#define AMHW_MCPWM_INT_ILIM(n)	(((n>=0)&&(n<=2)) ? ((uint32_t)(1<<((n*4)+0))) : (0))
/** \brief 通道n匹配寄存器中断 */
#define AMHW_MCPWM_INT_IMAT(n)	(((n>=0)&&(n<=2)) ? ((uint32_t)(1<<((n*4)+1))) : (0))
/** \brief 通道n捕获寄存器中断 */
#define AMHW_MCPWM_INT_ICAP(n)	(((n>=0)&&(n<=2)) ? ((uint32_t)(1<<((n*4)+2))) : (0))
/** \brief 快速中断 */
#define AMHW_MCPWM_INT_ABORT	((uint32_t)(1<<15))
/** @} */


/**
* \name 中断计数控制寄存器位
* @{
*/
/** \brief 上升沿计数 */
#define AMHW_MCPWM_CNTCON_TCMCI_RE(tc,mci)	(((tc>=0)&&(tc<=2)&&(mci>=0)&&(mci<=2)) ? ((uint32_t)(1<<((6*tc)+(2*mci)+0))) : (0))
/** \brief 下降沿计数 */
#define AMHW_MCPWM_CNTCON_TCMCI_FE(tc,mci)	(((tc>=0)&&(tc<=2)&&(mci>=0)&&(mci<=2)) ? ((uint32_t)(1<<((6*tc)+(2*mci)+1))) : (0))
/** \brief 通道n计数模式 */
#define AMHW_MCPWM_CNTCON_CNTR(n)			(((n>=0)&&(n<=2)) ? ((uint32_t)(1<<(29+n))) : (0))
/** @} */

/** \brief 通道n的死区时间x */
#define AMHW_MCPWM_DT(n,x)		((n<=2) ? ((uint32_t)((x&0x3FF)<<(n*10))) : (0))


/**
* \name 通信格式寄存器位
* @{
*/
#define AMHW_MCPWM_CP_A0		((uint32_t)(1<<0))	/**< \brief MCOA0 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_B0		((uint32_t)(1<<1))	/**< \brief MCOB0 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_A1		((uint32_t)(1<<2))	/**< \brief MCOA1 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_B1		((uint32_t)(1<<3))	/**< \brief MCOB1 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_A2		((uint32_t)(1<<4))	/**< \brief MCOA2 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_B2		((uint32_t)(1<<5))	/**< \brief MCOB2 tracks internal MCOA0 */
/** @} */

/** \brief 捕获清除寄存器 */
#define AMHW_MCPWM_CAPCLR_CAP(n)		((n<=2) ? ((uint32_t)(1<<n)) : (0))


/**
 * \brief 设置一个通道的定时/计数寄存器值
 *
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \param[in] regvalue   : 寄存器值
 * \return    无 
 */
am_static_inline 
void amhw_mcpwm_mctc_val_set (amhw_mcpwm_t *p_hw_mcpwm,
                              uint8_t       channel,
                              uint32_t      regvalue)
{   
    switch (channel) {
        
    case 0:
        p_hw_mcpwm->mctc0 = regvalue;
        break;
    case 1:
        p_hw_mcpwm->mctc1 = regvalue;
        break;
    case 2:
        p_hw_mcpwm->mctc2 = regvalue;
        break; 
    default:
        return  ;
    }    
}


/**
 * \brief 使能通道x的定时器
 *
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_pwm_enable (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
 	uint32_t regvalue = 0;
 
    switch (channel) {
        
    case 0:
        regvalue = AMHW_MCPWM_CON_RUN(0);
        break;
    case 1:
        regvalue = AMHW_MCPWM_CON_RUN(1);
        break;
    case 2:
        regvalue = AMHW_MCPWM_CON_RUN(2);
        break; 
    default:
        return ;
    }    
   
    p_hw_mcpwm->mcconset |= regvalue;
}
/**
 * \brief 禁能通道x的定时器
 *
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无 
 */
am_static_inline 
void amhw_mcpwm_pwm_disable (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
 	uint32_t regvalue = 0;
   
    switch (channel) {
        
    case 0:
        regvalue = AMHW_MCPWM_CON_RUN(0);
        break;
    case 1:
        regvalue = AMHW_MCPWM_CON_RUN(1);
        break;
    case 2:
        regvalue = AMHW_MCPWM_CON_RUN(2);
        break; 
    default:
        return ;
    }      
    p_hw_mcpwm->mcconclr = regvalue;    
}

/**
 * \brief 设置一个通道的界限寄存器值（PWM周期）
 *
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \param[in] regvalue   : 寄存器值
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mclim_val_set (amhw_mcpwm_t *p_hw_mcpwm,
                               uint8_t       channel,
                               uint32_t      regvalue)
{
    
    switch (channel) {
        
    case 0:
        p_hw_mcpwm->mclim0 = regvalue;
        break;
    case 1:
        p_hw_mcpwm->mclim1 = regvalue;
        break;
    case 2:
        p_hw_mcpwm->mclim2 = regvalue;
        break; 
    default:
        return ;
    }    
}

/**
 * \brief 设置一个通道的匹配寄存器值（PWM占空比）
 *
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \param[in] regvalue   : 寄存器值
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mcmat_val_set (amhw_mcpwm_t *p_hw_mcpwm,
                               uint8_t       channel,
                               uint32_t      regvalue)
{

    switch (channel) {
        
    case 0:
        p_hw_mcpwm->mcmat0 = regvalue;
        break;
    case 1:
        p_hw_mcpwm->mcmat1 = regvalue;
        break;
    case 2:
        p_hw_mcpwm->mcmat2 = regvalue;
        break; 
    default:
        return ;
    }     
}
/**
 * \brief 设置一个通道的对齐模式值
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_center_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_CENTER(channel);
}
/**
 * \brief 清除一个通道的对齐模式值
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_center_val_clr (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_CENTER(channel);
}

/**
 * \brief 设置一个通道的有效电平状态极性
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_pola_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_POLAR(channel);
}
/**
 * \brief 清除一个通道的有效电平状态极性
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_pola_val_clr (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_POLAR(channel);
}

/**
 * \brief 设置一个通道的死区时间使能
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_dte_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_DTE(channel);
}
/**
 * \brief 禁止一个通道的死区时间
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_dte_val_clr (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_DTE(channel);
}


/**
 * \brief 设置一个通道的死区时间
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \param[in] deadtime    : 死区时间
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mcdt_val_set (amhw_mcpwm_t *p_hw_mcpwm,
                              uint8_t       channel,
                              uint32_t      deadtime)
{
    p_hw_mcpwm->mcdt &= ~(AMHW_MCPWM_DT(channel, 0x3FF));
    p_hw_mcpwm->mcdt |= AMHW_MCPWM_DT(channel, deadtime);    
}


/**
 * \brief 使能功能寄存器更新
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_disup_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_DISUP(channel);
}
/**
 * \brief 禁止功能寄存器更新
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道：有效值，0 ~ 2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_disup_val_clr (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_DISUP(channel);
}

/**
 * \brief 使能DC模式
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_dcmode_val_set (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconset = (uint32_t)1<<31; 

}
/**
 * \brief 禁止DC模式
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_dcmode_val_clr (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_DCMODE;
}

/**
 * \brief 使能AC模式
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_acmode_val_set (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_ACMODE;
}
/**
 * \brief 禁止AC模式
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_acmode_val_clr (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_ACMODE;
}

/**
 * \brief 清除MCCPx寄存器 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_capclr_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mccapclr = AMHW_MCPWM_CAPCLR_CAP(channel);
}

/**
 * \brief 清除界限中断标志 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_flagilim_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintfclr = AMHW_MCPWM_INT_ILIM(channel);
}
/**
 * \brief 清除匹配中断标志 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_flagimat_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintfclr = AMHW_MCPWM_INT_IMAT(channel);
}
/**
 * \brief 清除捕获中断标志 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_flagicap_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintfclr = AMHW_MCPWM_INT_ICAP(channel);
}

/**
 * \brief 清除界限中断使能 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_enilim_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintenclr = AMHW_MCPWM_INT_ILIM(channel);
}
/**
 * \brief 清除匹配中断使能 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_enimat_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintenclr = AMHW_MCPWM_INT_IMAT(channel);
}
/**
 * \brief 清除捕获中断使能 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_enicap_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintenclr = AMHW_MCPWM_INT_ICAP(channel);
}



/**
 * \brief 使MCOB与MCOA输出的方向相反 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_invbdc_set (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_INVBDC;
}
/**
 * \brief 取消MCOB与MCOA输出的方向相反设置 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_invbdc_clr (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_INVBDC;
}

/**
 * \brief 设置通信格式
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] pattern    : 通信格式，参见
 *                         \ref grp_amhw_mcpwm_patent_flags  "Patent Configuration Flags"
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mccp_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint32_t pattern )
{  
    p_hw_mcpwm->mccp = pattern;
}
/**
 * \brief 获取中断标志寄存器指定位的值 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] inttype    : 指定位
 * \return    指定位的值0或者1
 */
am_static_inline 
bool_t amhw_mcpwm_mcintf_getvalue (amhw_mcpwm_t *p_hw_mcpwm, uint32_t inttype)
{
	return ((p_hw_mcpwm->mcintf & inttype) ? TRUE : FALSE);
}

/**
 * \brief 获取捕获寄存器的值 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    返回通道0-2定时器的实时值
 */
am_static_inline 
uint32_t amhw_mcpwm_mccap_getvalue (amhw_mcpwm_t *p_hw_mcpwm, uint32_t channel)
{
	if (channel == 0){
		return (p_hw_mcpwm->mccap0);
	} else if (channel == 1) {
		return (p_hw_mcpwm->mccap1);
	} else if (channel == 2) {
		return (p_hw_mcpwm->mccap2);
	}
	return (0);
}
/**
 * \brief 设置中断类型 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] inttype    : 中断类型，参见
 *							\ref grp_amhw_mcpwm_inttype_flags  "Inttype Configuration Flags"
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mcinten_set (amhw_mcpwm_t *p_hw_mcpwm, uint32_t inttype)
{
	p_hw_mcpwm->mcintenset = inttype;
}
/**
 * \brief 清除中断类型 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] inttype    : 中断类型，参见
 *							\ref grp_amhw_mcpwm_inttype_flags  "Inttype Configuration Flags"
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mcinten_clr(amhw_mcpwm_t *p_hw_mcpwm, uint32_t inttype)
{
	p_hw_mcpwm->mcintenclr = inttype;
}
/**
 * \brief 清除中断中断标志 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] inttype    : 中断类型，参见
 *							\ref grp_amhw_mcpwm_inttype_flags  "Inttype Configuration Flags"
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mcintf_clr (amhw_mcpwm_t *p_hw_mcpwm, uint32_t inttype)
{
	p_hw_mcpwm->mcintfclr = inttype;
}

/**
 * \brief 获取中断标志寄存器捕获位的值 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] num        : 通道0-2
 * \return    指定位的值0或者1
 */
am_static_inline 
bool_t amhw_mcpwm_mcintf_cap_getvalue (amhw_mcpwm_t *p_hw_mcpwm, int num)
{
    uint32_t inttype = 0;
    
    if (num == 0) {
        inttype = AMHW_MCPWM_INTFLAG_CAP0;
    } else if (num == 1) {
        inttype = AMHW_MCPWM_INTFLAG_CAP1;
    } else if (num == 2) {
        inttype = AMHW_MCPWM_INTFLAG_CAP2;
    }
    
	return ((p_hw_mcpwm->mcintf & inttype) ? TRUE : FALSE);
}

/**
 * \brief 清除中断捕获标志 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] num        : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mcintf_cap_clr(amhw_mcpwm_t *p_hw_mcpwm, int num)
{
    uint32_t inttype = 0;
    
    if (num == 0) {
        inttype = AMHW_MCPWM_INTFLAG_CAP0;
    } else if (num == 1) {
        inttype = AMHW_MCPWM_INTFLAG_CAP1;
    } else if (num == 2) {
        inttype = AMHW_MCPWM_INTFLAG_CAP2;
    }    
	p_hw_mcpwm->mcintfclr = inttype;
}

/**
 * \brief 设置中断捕获类型 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] num        : 通道0-2
 * \return    无
 */
am_static_inline 
void amhw_mcpwm_mcinten_cap_set(amhw_mcpwm_t *p_hw_mcpwm, int num)
{
    uint32_t inttype = 0;
    
    if (num == 0) {
        inttype = AMHW_MCPWM_INTFLAG_CAP0;
    } else if (num == 1) {
        inttype = AMHW_MCPWM_INTFLAG_CAP1;
    } else if (num == 2) {
        inttype = AMHW_MCPWM_INTFLAG_CAP2;
    }      
	p_hw_mcpwm->mcintenset = inttype;
}

/**
 * \brief 获取界限寄存器的值 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \return    返回通道0-2界限的值
 */
am_static_inline 
uint32_t amhw_mcpwm_mclim_getvalue(amhw_mcpwm_t *p_hw_mcpwm, uint32_t channel)
{
	if (channel == 0) {
		return (p_hw_mcpwm->mclim0);
	} else if (channel == 1) {
		return (p_hw_mcpwm->mclim1);
	} else if (channel == 2) {
		return (p_hw_mcpwm->mclim2);
	}
	return (0);
}
/**
 * \brief 初始化MCPWM
 * \param[in]  p_hw_mcpwm : MCPWM指针 
 * \return     无
 */
void amhw_mcpwm_init(amhw_mcpwm_t *p_hw_mcpwm);
/**
 * \brief 初始化MCPWM通道
 * \param[in]  p_hw_mcpwm : MCPWM指针  
 * \return     无
 */
void amhw_mcpwm_configchannel(amhw_mcpwm_t *p_hw_mcpwm);
/**
 * \brief 捕获初始化 
 * \param[in] p_hw_mcpwm : 指向mcpwm寄存器块的指针
 * \param[in] channel    : 通道0-2
 * \param[in] options    : 1--上升沿、2--下降沿
 * \param[in] channelnum : 0-2
 * \return    无
 */
void amhw_mcpwm_configcapture(amhw_mcpwm_t *p_hw_mcpwm,
                              uint32_t      channel,
                              unsigned int  options,
                              uint32_t      channelnum);


/**
 * @} amhw_if_mcpwm
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MCPWM_H */

/* end of file */
    

