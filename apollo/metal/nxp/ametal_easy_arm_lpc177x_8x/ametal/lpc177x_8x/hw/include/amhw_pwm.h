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
 * \brief  PWMӲ�������ӿ�
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
 * \brief PWM�Ĵ�����Ľṹ��
 */
typedef struct amhw_pwm { 
    __IO  uint32_t   ir;        /**< \brief �жϼĴ��� */
    __IO  uint32_t   tcr;       /**< \brief ��ʱ�����ƼĴ��� */
    __IO  uint32_t   tc;        /**< \brief ��ʱ�������� */
    __IO  uint32_t   pr;        /**< \brief Ԥ��Ƶ�Ĵ���*/
    __IO  uint32_t   pc;        /**< \brief Ԥ��Ƶ������*/
    __IO  uint32_t   mcr;       /**< \brief ƥ����ƼĴ��� */
    __IO  uint32_t   mr0;       /**< \brief ƥ��Ĵ���0 */
    __IO  uint32_t   mr1;       /**< \brief ƥ��Ĵ���1 */
    __IO  uint32_t   mr2;       /**< \brief ƥ��Ĵ���2 */  
    __IO  uint32_t   mr3;       /**< \brief ƥ��Ĵ���3*/
    __IO  uint32_t   ccr;       /**< \brief ������ƼĴ��� */     
    __I   uint32_t   cr0;       /**< \brief ����Ĵ���0 */
    __I   uint32_t   cr1;       /**< \brief ����Ĵ���1 */   
    __I   uint32_t   cr2;       /**< \brief ����Ĵ���2 */  
    __I   uint32_t   cr3;       /**< \brief ����Ĵ���3*/
    __IO  uint32_t   reserved0; /**< \brief ����                    */
    __IO  uint32_t   mr4;       /**< \brief ƥ��Ĵ���4 */
    __IO  uint32_t   mr5;       /**< \brief ƥ��Ĵ���5 */
    __IO  uint32_t   mr6;       /**< \brief ƥ��Ĵ���6 */
    __IO  uint32_t   pcr;       /**< \brief PWM���ƼĴ��� */
    __IO  uint32_t   ler;       /**< \brief ����ʹ�ܼĴ��� */ 
    __IO  uint32_t   reserved01[7]; /**< \brief ����                           */
    __IO  uint32_t   ctcr;      /**< \brief �������ƼĴ��� */
} amhw_pwm_t;

/**
* \name PWM����ģʽ
 * \anchor grp_amhw_pwm_chan_mode
* @{
*/
/** \brief ������ģʽ*/
#define AMHW_PWM_CHANNEL_SINGLE_EDGE    0  	
/** \brief ˫����ģʽ */
#define AMHW_PWM_CHANNEL_DUAL_EDGE      1	
/** @} */

/**
* \name �жϼĴ����궨��궨��
* @{
*/
/** \brief 6��ͨ����ƥ���ж�λ */
#define AMHW_PWM_IR_PWMMRn(n)    	((uint32_t)((n<4)?(1<<n):(1<<(n+4))))
/** \brief 2�������ж�λ */
#define AMHW_PWM_IR_PWMCAPn(n)		((uint32_t)(1<<(n+4)))
/** \brief �жϼĴ������� */
#define AMHW_PWM_IR_BITMASK			((uint32_t)(0x0000073F))
/** @} */

/**
* \name  ��ʱ�����ƼĴ����궨��
* @{
*/
/** \brief ���ƼĴ���λ���� */
#define AMHW_PWM_TCR_BITMASK			 ((uint32_t)(0x0000000B))
#define AMHW_PWM_TCR_COUNTER_ENABLE      ((uint32_t)(1<<0)) /**< \brief PWM Counter Enable */
#define AMHW_PWM_TCR_COUNTER_RESET       ((uint32_t)(1<<1)) /**< \brief PWM Counter Reset */
#define AMHW_PWM_TCR_PWM_ENABLE          ((uint32_t)(1<<3)) /**< \brief PWM Enable */
/** @} */

/**
* \name ƥ����ƼĴ����궨��
* @{
*/
/** \brief ƥ����ƼĴ���λ���� */
#define AMHW_PWM_MCR_BITMASK		     ((uint32_t)(0x001FFFFF))
/** \brief ƥ��ʱ�����ж� */
#define AMHW_PWM_MCR_INT_ON_MATCH(n)     ((uint32_t)(1<<(((n&0x7)<<1)+(n&0x07))))
/** \brief ƥ��ʱ��λ */
#define AMHW_PWM_MCR_RESET_ON_MATCH(n)   ((uint32_t)(1<<(((n&0x7)<<1)+(n&0x07)+1)))
/** \brief ƥ��ʱֹͣ */
#define AMHW_PWM_MCR_STOP_ON_MATCH(n)    ((uint32_t)(1<<(((n&0x7)<<1)+(n&0x07)+2)))
/** @} */

/**
* \name ������ƼĴ����궨��
* @{
*/
/** \brief ������ƼĴ���λ���� */
#define AMHW_PWM_CCR_BITMASK			((uint32_t)(0x0000003F))
/** \brief ������λ */
#define AMHW_PWM_CCR_CAP_RISING(n) 	 	((uint32_t)(n == 0 ? 1 : 8))
/** \brief �½���λ */
#define AMHW_PWM_CCR_CAP_FALLING(n) 	((uint32_t)(n == 0 ? 2 : 16))
/** \brief �����ж��¼�λ */
#define AMHW_PWM_CCR_INT_ON_CAP(n)  	((uint32_t)(n == 0 ? 4 : 32))
/** @} */


/**
* \name PWM���ƼĴ����궨��
* @{
*/
/** \brief ���ƼĴ���λ���� */
#define AMHW_PWM_PCR_BITMASK		(uint32_t)0x00007E7C
/** \brief PWM����ģʽѡ��λ */
#define AMHW_PWM_PCR_PWMSELn(n)   	((uint32_t)(((n&0x7)<2) ? 0 : (1<<n)))
/** \brief ʹ��PWM���λ */
#define AMHW_PWM_PCR_PWMENAn(n)   	((uint32_t)(((n&0x7)<1) ? 0 : (1<<(n+8))))
/** @} */


/**
* \name ����ʹ�ܼĴ����궨��
* @{
*/
/** \brief ����ʹ�ܼĴ���λ���� */
#define AMHW_PWM_LER_BITMASK			  ((uint32_t)(0x0000007F))
/** \brief ʹ����� */
#define AMHW_PWM_LER_EN_MATCHn_LATCH(n)   ((uint32_t)((n<7) ? (1<<n) : 0))
/** @} */

/**
 * \brief �ж�״̬ö��
 */
typedef enum
{
	AMHW_PWM_INTSTAT_MR0 = AMHW_PWM_IR_PWMMRn(0), 	    /**< PWM match ͨ��0�жϱ�־ */
	AMHW_PWM_INTSTAT_MR1 = AMHW_PWM_IR_PWMMRn(1),		/**< PWM match ͨ��1�жϱ�־ */
	AMHW_PWM_INTSTAT_MR2 = AMHW_PWM_IR_PWMMRn(2),		/**< PWM match ͨ��2�жϱ�־ */
	AMHW_PWM_INTSTAT_MR3 = AMHW_PWM_IR_PWMMRn(3),		/**< PWM match ͨ��3�жϱ�־ */
	AMHW_PWM_INTSTAT_CAP0 = AMHW_PWM_IR_PWMCAPn(0),	    /**< ���벶��0�жϱ�־                 */
	AMHW_PWM_INTSTAT_CAP1 = AMHW_PWM_IR_PWMCAPn(1),	    /**< ���벶��0�жϱ�־                 */
	AMHW_PWM_INTSTAT_MR4 = AMHW_PWM_IR_PWMMRn(4),		/**< PWM match ͨ��4�жϱ�־ */
	AMHW_PWM_INTSTAT_MR5 = AMHW_PWM_IR_PWMMRn(5),		/**< PWM match ͨ��5�жϱ�־ */
	AMHW_PWM_INTSTAT_MR6 = AMHW_PWM_IR_PWMMRn(6)		/**< PWM match ͨ��6�жϱ�־ */
}AMHW_PWM_INTSTAT;


/**
 * \brief �����жϼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_ir_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ir = regvalue;
}

/**
 * \brief ���ö�ʱ�����ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_tcr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->tcr |= regvalue;
}
/**
 * \brief �����ʱ�����ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_tcr_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->tcr &= regvalue;
}

/**
 * \brief ���ü������ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_ctcr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ctcr = regvalue;
}


/**
 * \brief ����ƥ����ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_mcr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->mcr |= regvalue;
}
/**
 * \brief ���ƥ����ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_mcr_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->mcr &= regvalue;
}

/**
 * \brief ���ò�����ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_ccr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ccr |= regvalue;
}

/**
 * \brief ���������ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_ccr_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ccr &= regvalue;
}

/**
 * \brief ���ÿ��ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_pcr_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->pcr |= regvalue;
}

/**
 * \brief ������ƼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_pcr_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->pcr &= regvalue;
}
/**
 * \brief ��������ʹ�ܼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_ler_val_set (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ler |= regvalue;
}
/**
 * \brief �������ʹ�ܼĴ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
void amhw_pwm_ler_val_clr (amhw_pwm_t *p_hw_pwm, uint32_t regvalue)
{   
    p_hw_pwm->ler &= regvalue;
}

/**
 * \brief ����ƥ��Ĵ�����ֵ(��ƥ��Ĵ���0����������)
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] channel  : ͨ��0
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
int amhw_pwm_mr0_set_period (amhw_pwm_t *p_hw_pwm,
                             uint32_t    channel,
                             uint32_t    regvalue)
{  
    if ((p_hw_pwm != AMHW_PWM1) || (channel != 0)) {
        return -AM_EINVAL;  /* ��������ȷ */
    }
	p_hw_pwm->mr0 = regvalue;
	return AM_OK;
}

/**
 * \brief ����ƥ��Ĵ�����ֵ(ƥ��Ĵ���0����)
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] channel  : ͨ��0-5
 * \param[in] regvalue : �Ĵ���ֵ
 * \return    �� 
 */
am_static_inline 
int amhw_pwm_mr_val_set (amhw_pwm_t *p_hw_pwm,
                         uint32_t    channel,
                         uint32_t    regvalue)
{  
    if ((p_hw_pwm != AMHW_PWM1) || (channel > 6)) {
        return -AM_EINVAL;  /* ��������ȷ */
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
 * \brief ��ȡƥ��Ĵ�����ֵ
 *
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] channel  : ͨ��0-6
 * \return    �� 
 */
am_static_inline 
int amhw_pwm_mr_val_get (amhw_pwm_t *p_hw_pwm, uint32_t channel)
{  
    uint32_t regvalue;
    if ((p_hw_pwm != AMHW_PWM1) || (channel > 6)) {
        return -AM_EINVAL;  /* ��������ȷ */
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
 * \brief ��ȡ�����жϱ�־�Ĵ���ָ��λ��ֵ 
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] channel  : ָ��ͨ��
 * \return    ָ��λ��ֵ0����1
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
 * \brief ��������жϱ�־  
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] channel  : ָ��ͨ��
 * \return    ָ��λ��ֵ0����1
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
 * \brief ��ȡ����Ĵ�����ֵ  
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] channel    : ָͨ��
 * \return    cr0��cr1��ֵ
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
 * \brief ��ȡ�жϱ�־�Ĵ���ָ��λ��ֵ 
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] inttype    : ָ��λ
 * \return    ָ��λ��ֵ0����1
 */
am_static_inline 
bool_t amhw_pwm_ir_getflag (amhw_pwm_t *p_hw_pwm, uint32_t inttype)
{
    return ((p_hw_pwm->ir & inttype) ? TRUE : FALSE);    
}

/**
 * \brief ����жϱ�־  
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] inttype    : ָ��λ
 * \return    ָ��λ��ֵ0����1
 */
am_static_inline 
void amhw_pwm_ir_clrflags (amhw_pwm_t *p_hw_pwm, uint32_t inttype)
{
    p_hw_pwm->ir |= inttype;;    
}
/**
 * \brief ��ʼ��PWM�Ĵ���  
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
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
 * \brief �����ء�˫����ģʽѡ��  
 * \param[in] p_hw_pwm   : ָ��pwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��
 * \param[in] option     : ģʽѡ��,�μ�
 *						  \ref grp_amhw_pwm_chan_mode  "Mode Configuration Flags"
 * \return    ��
 */
void amhw_pwm_config_edgemode (amhw_pwm_t *p_hw_pwm,
                               uint8_t     channel,
                               uint8_t     option);
/**
 * \brief ����ƥ����ƼĴ���  
 * \param[in] p_hw_pwm   : ָ��pwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��
 * \param[in] intmatch   : ƥ������ж�
 * \param[in] resetmatch : ƥ�临λѡ��
 * \param[in] stopmatch  : ƥ��ֹͣѡ��
 * \return    ��
 */
void amhw_pwm_config_match_reg (amhw_pwm_t *p_hw_pwm,
                                uint8_t     channel,
                                uint8_t     intmatch,
                                uint8_t     resetmatch,
                                uint8_t     stopmatch);
/**
 * \brief ʵʱ����ƥ��Ĵ�����ֵ  
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \param[in] channel    : ָͨ��
 * \param[in] regvalue   : �Ĵ�����ֵ
 * \return    ��
 */								
void amhw_pwm_fresh_match_reg (amhw_pwm_t *p_hw_pwm,
		                       uint8_t     channel,
					           uint32_t    regvalue);
/**
 * \brief ʹ��ͨ��x��PWM���  
 * \param[in] p_hw_pwm   : ָ��pwm�Ĵ������ָ��
 * \param[in] channel    : ָͨ��
 * \return    ��
 */					
void amhw_pwm_channel_enable (amhw_pwm_t *p_hw_pwm, uint8_t channel);
/**
 * \brief ��ֹͨ����PWM���
 * \param[in] p_hw_pwm   : ָ��pwm�Ĵ������ָ��
 * \param[in] channel    : ָͨ��
 * \return    ��
 */
void amhw_pwm_channel_disable (amhw_pwm_t *p_hw_pwm, uint8_t channel);
/**
 * \brief ��λ������   
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \return    ��
 */
void amhw_pwm_reset_counter (amhw_pwm_t *p_hw_pwm);
/**
 * \brief ������ʹ��  
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \return    ��
 */
void amhw_pwm_counter_enable (amhw_pwm_t *p_hw_pwm);
/**
 * \brief ��ֹ������  
 * \param[in] p_hw_pwm : ָ��pwm�Ĵ������ָ��
 * \return    ��
 */
void amhw_pwm_counter_disable(amhw_pwm_t *p_hw_pwm);
/**
 * \brief ����PWM  
 * \param[in] p_hw_pwm   : ָ��pwm�Ĵ������ָ��
 * \param[in] state      : ��������ֹͣ
 * \return    ��
 */
void amhw_pwm_tcr_cmd(amhw_pwm_t *p_hw_pwm, bool_t state);
/**
 * \brief ���ò�����ƼĴ�����ֵ  
 * \param[in] p_hw_pwm   : ָ��pwm�Ĵ������ָ��
 * \param[in] channel    : ָͨ��
 * \param[in] rising     : TRUE--������ѡ��
 * \param[in] falling    : FALSE--�½���ѡ��
 * \param[in] intcaption : �¼�ѡ��
 * \return    ��
 */
void amhw_pwm_config_capture_reg (amhw_pwm_t *p_hw_pwm,
                                  uint8_t     channel,
                                  uint8_t     rising,
                                  uint8_t     falling,
                                  uint8_t     intcaption);
/**
 * \brief ʵʱ����ƥ��Ĵ�����ֵ����ƥ��Ĵ���0���������ڣ�
 * \param[in] p_hw_pwm   : ָ��pwm�Ĵ������ָ��
 * \param[in] channel    : ָͨ��
 * \param[in] regvalue   : �Ĵ�����ֵ
 * \return    ��
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
    

