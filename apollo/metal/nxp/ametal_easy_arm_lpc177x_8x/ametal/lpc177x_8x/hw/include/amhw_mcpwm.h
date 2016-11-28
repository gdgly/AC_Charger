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
 * \brief  MCPWMӲ�������ӿ�
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
 * \brief MCPWM�Ĵ�����Ľṹ��
 */
typedef struct amhw_mcpwm {
    __I   uint32_t  mccon;         /**< \brief PWM���ƼĴ�����        */
    __O   uint32_t  mcconset;      /**< \brief PWM���ƼĴ���д        */
    __O   uint32_t  mcconclr;      /**< \brief PWM���ƼĴ�������      */
    __I   uint32_t  mccapcon;      /**< \brief ����Ĵ�����           */
    __O   uint32_t  mccapconset;   /**< \brief ����Ĵ���д           */
    __O   uint32_t  mccapconclr;   /**< \brief ����Ĵ�������         */  
    __IO  uint32_t  mctc0;         /**< \brief ��ʱ�����Ĵ�����ͨ��0  */
    __IO  uint32_t  mctc1;         /**< \brief ��ʱ�����Ĵ�����ͨ��1  */
    __IO  uint32_t  mctc2;         /**< \brief ��ʱ�����Ĵ�����ͨ��2  */
    __IO  uint32_t  mclim0;        /**< \brief ���޼Ĵ�����ͨ��0      */
    __IO  uint32_t  mclim1;        /**< \brief ���޼Ĵ�����ͨ��1      */
    __IO  uint32_t  mclim2;        /**< \brief ���޼Ĵ�����ͨ��2      */
    __IO  uint32_t  mcmat0;        /**< \brief ƥ��Ĵ�����ͨ��0      */
    __IO  uint32_t  mcmat1;        /**< \brief ƥ��Ĵ�����ͨ��1      */
    __IO  uint32_t  mcmat2;        /**< \brief ƥ��Ĵ�����ͨ��2      */  
    __IO  uint32_t  mcdt;          /**< \brief ����ʱ��Ĵ���         */
    __IO  uint32_t  mccp;          /**< \brief ͨ�Ÿ�ʽ�Ĵ���         */     
    __IO  uint32_t  mccap0;        /**< \brief ����Ĵ�����ͨ��0      */
    __IO  uint32_t  mccap1;        /**< \brief ����Ĵ�����ͨ��1      */   
    __IO  uint32_t  mccap2;        /**< \brief ����Ĵ�����ͨ��2      */  
    __I   uint32_t  mcinten;       /**< \brief �ж�ʹ�ܶ��Ĵ���       */
    __O   uint32_t  mcintenset;    /**< \brief �ж�ʹ��д�Ĵ���       */
    __O   uint32_t  mcintenclr;    /**< \brief �ж�����Ĵ���         */
    __I   uint32_t  mccntcon;      /**< \brief �������ƶ��Ĵ���       */
    __O   uint32_t  mccntconset;   /**< \brief ��������д�Ĵ���       */
    __O   uint32_t  mccntconclr;   /**< \brief ������������Ĵ���     */ 
    __I   uint32_t  mcintf;        /**< \brief �жϱ�־���Ĵ���       */
    __O   uint32_t  mcintfset;     /**< \brief �жϱ�־д�Ĵ���       */
    __O   uint32_t  mcintfclr;     /**< \brief �жϱ�־����Ĵ���     */
    __O   uint32_t  mccapclr;      /**< \brief ��������Ĵ���         */
} amhw_mcpwm_t;


/**
* \name MCPWMͨ��ģʽ
* @{
*/
/** \brief MCPWMͨ���ı���ģʽ  */
#define AMHW_MCPWM_CHANNEL_EDGE_MODE		((uint32_t)(0))
/** \brief MCPWMͨ��������ģʽ  */
#define AMHW_MCPWM_CHANNEL_CENTER_MODE		((uint32_t)(1))

/** \brief MCOA��MCOB���ŵļ��ԣ��͵�ƽ����Ч״̬���ߵ�ƽ����Ч״̬ */
#define AMHW_MCPWM_CHANNEL_PASSIVE_LO		((uint32_t)(0))
/** \brief MCOA��MCOB�����ļ��ԣ��ߵ�ƽ����Ч״̬���͵�ƽ����Ч״̬ */
#define AMHW_MCPWM_CHANNEL_PASSIVE_HI		((uint32_t)(1))

/**
 * @}
 */
 
 /**
 * \name �����ж����Ͳ���
 * \anchor grp_amhw_mcpwm_inttype_flags
 * @{
 */
/** \brief ͨ��0�Ľ����ж� */
#define AMHW_MCPWM_INTFLAG_LIM0	AMHW_MCPWM_INT_ILIM(0)
/** \brief ͨ��0��ƥ���ж� */
#define AMHW_MCPWM_INTFLAG_MAT0	AMHW_MCPWM_INT_IMAT(0)
/** \brief ͨ��0�Ĳ����ж� */
#define AMHW_MCPWM_INTFLAG_CAP0	AMHW_MCPWM_INT_ICAP(0)

/** \brief ͨ��1�Ľ����ж� */
#define AMHW_MCPWM_INTFLAG_LIM1	AMHW_MCPWM_INT_ILIM(1)
/** \brief ͨ��1��ƥ���ж� */
#define AMHW_MCPWM_INTFLAG_MAT1	AMHW_MCPWM_INT_IMAT(1)
/** \brief ͨ��1�Ĳ����ж� */
#define AMHW_MCPWM_INTFLAG_CAP1	AMHW_MCPWM_INT_ICAP(1)

/** \brief ͨ��2�Ľ����ж� */
#define AMHW_MCPWM_INTFLAG_LIM2	AMHW_MCPWM_INT_ILIM(2)
/** \brief ͨ��2��ƥ���ж� */
#define AMHW_MCPWM_INTFLAG_MAT2	AMHW_MCPWM_INT_IMAT(2)
/** \brief ͨ��2�Ĳ����ж� */
#define AMHW_MCPWM_INTFLAG_CAP2	AMHW_MCPWM_INT_ICAP(2)

/** \brief ������ֹ�ж� */
#define AMHW_MCPWM_INTFLAG_ABORT	AMHW_MCPWM_INT_ABORT


/** @} */

 /**
 * \name �������ģʽ���ò���
 * \anchor grp_amhw_mcpwm_patent_flags
 * @{
 */

/** \brief MCOA0�����ڲ�MCOA0 */
#define AMHW_MCPWM_PATENT_A0		((uint32_t)(1<<0))
/** \brief MCOB0�����ڲ�MCOA0 */
#define AMHW_MCPWM_PATENT_B0		((uint32_t)(1<<1))
/** \brief MCOA1�����ڲ�MCOA0 */
#define AMHW_MCPWM_PATENT_A1		((uint32_t)(1<<2))
/** \brief MCOB1�����ڲ�MCOA0 */
#define AMHW_MCPWM_PATENT_B1		((uint32_t)(1<<3))
/** \brief MCOA2�����ڲ�MCOA0 */
#define AMHW_MCPWM_PATENT_A2		((uint32_t)(1<<4))
/** \brief MCOB2�����ڲ�MCOA0 */
#define AMHW_MCPWM_PATENT_B2		((uint32_t)(1<<5))	

/** @} */

/**
 * \name MCPWM���ƼĴ�������λ��ϸ����
 * @{ 
 */

/**  \brief ����ͨ��n  */
#define AMHW_MCPWM_CON_RUN(n)		((n<=2) ? ((uint32_t)(1<<((n*8)+0))) : (0))
/**  \brief  ͨ��n����/����ģʽ */
#define AMHW_MCPWM_CON_CENTER(n)	((n<=2) ? ((uint32_t)(1<<((n*8)+1))) : (0))	
/**  \brief  ѡ��A/B�༫�� */
#define AMHW_MCPWM_CON_POLAR(n)		((n<=2) ? ((uint32_t)(1<<((n*8)+2))) : (0))	
/**  \brief  ����ʱ������ */
#define AMHW_MCPWM_CON_DTE(n)		((n<=2) ? ((uint32_t)(1<<((n*8)+3))) : (0))	
/**  \brief  ʹ�ܸ��¼Ĵ��� */
#define AMHW_MCPWM_CON_DISUP(n)		((n<=2) ? ((uint32_t)(1<<((n*8)+4))) : (0))
/**  \brief  ���Կ��� */
#define AMHW_MCPWM_CON_INVBDC		((uint32_t)(1<<29))	
/**  \brief  ����ACģʽѡ�� */
#define AMHW_MCPWM_CON_ACMODE		((uint32_t)(1<<30))	
/**  \brief  ����DCģʽѡ�� */
#define AMHW_MCPWM_CON_DCMODE		((uint32_t)((uint32_t)1<<31))	

/** @} */


/**
* \name ������ƼĴ���λ
* @{
*/
/** \brief ʹ��ͨ�������ز����¼� */
#define AMHW_MCPWM_CAPCON_CAPMCI_RE(cap,mci)	(((cap<=2)&&(mci<=2)) ? ((uint32_t)(1<<((cap*6)+(mci*2)+0))) : (0))
/** \brief ʹ��ͨ���½��ز����¼� */
#define AMHW_MCPWM_CAPCON_CAPMCI_FE(cap,mci)	(((cap<=2)&&(mci<=2)) ? ((uint32_t)(1<<((cap*6)+(mci*2)+1))) : (0))
/** \brief ��ʱ����λ�����¼� */
#define AMHW_MCPWM_CAPCON_RT(n)				((n<=2) ? ((uint32_t)(1<<(18+(n)))) : (0))
/** \brief Ӳ���������� */
#define AMHW_MCPWM_CAPCON_HNFCAP(n)			((n<=2) ? ((uint32_t)(1<<(21+(n)))) : (0))
/** @} */


/**
* \name �ж�ʹ�ܡ��жϱ�־λ
* @{
*/
/** \brief ͨ��n���޼Ĵ����ж� */
#define AMHW_MCPWM_INT_ILIM(n)	(((n>=0)&&(n<=2)) ? ((uint32_t)(1<<((n*4)+0))) : (0))
/** \brief ͨ��nƥ��Ĵ����ж� */
#define AMHW_MCPWM_INT_IMAT(n)	(((n>=0)&&(n<=2)) ? ((uint32_t)(1<<((n*4)+1))) : (0))
/** \brief ͨ��n����Ĵ����ж� */
#define AMHW_MCPWM_INT_ICAP(n)	(((n>=0)&&(n<=2)) ? ((uint32_t)(1<<((n*4)+2))) : (0))
/** \brief �����ж� */
#define AMHW_MCPWM_INT_ABORT	((uint32_t)(1<<15))
/** @} */


/**
* \name �жϼ������ƼĴ���λ
* @{
*/
/** \brief �����ؼ��� */
#define AMHW_MCPWM_CNTCON_TCMCI_RE(tc,mci)	(((tc>=0)&&(tc<=2)&&(mci>=0)&&(mci<=2)) ? ((uint32_t)(1<<((6*tc)+(2*mci)+0))) : (0))
/** \brief �½��ؼ��� */
#define AMHW_MCPWM_CNTCON_TCMCI_FE(tc,mci)	(((tc>=0)&&(tc<=2)&&(mci>=0)&&(mci<=2)) ? ((uint32_t)(1<<((6*tc)+(2*mci)+1))) : (0))
/** \brief ͨ��n����ģʽ */
#define AMHW_MCPWM_CNTCON_CNTR(n)			(((n>=0)&&(n<=2)) ? ((uint32_t)(1<<(29+n))) : (0))
/** @} */

/** \brief ͨ��n������ʱ��x */
#define AMHW_MCPWM_DT(n,x)		((n<=2) ? ((uint32_t)((x&0x3FF)<<(n*10))) : (0))


/**
* \name ͨ�Ÿ�ʽ�Ĵ���λ
* @{
*/
#define AMHW_MCPWM_CP_A0		((uint32_t)(1<<0))	/**< \brief MCOA0 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_B0		((uint32_t)(1<<1))	/**< \brief MCOB0 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_A1		((uint32_t)(1<<2))	/**< \brief MCOA1 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_B1		((uint32_t)(1<<3))	/**< \brief MCOB1 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_A2		((uint32_t)(1<<4))	/**< \brief MCOA2 tracks internal MCOA0 */
#define AMHW_MCPWM_CP_B2		((uint32_t)(1<<5))	/**< \brief MCOB2 tracks internal MCOA0 */
/** @} */

/** \brief ��������Ĵ��� */
#define AMHW_MCPWM_CAPCLR_CAP(n)		((n<=2) ? ((uint32_t)(1<<n)) : (0))


/**
 * \brief ����һ��ͨ���Ķ�ʱ/�����Ĵ���ֵ
 *
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \param[in] regvalue   : �Ĵ���ֵ
 * \return    �� 
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
 * \brief ʹ��ͨ��x�Ķ�ʱ��
 *
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
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
 * \brief ����ͨ��x�Ķ�ʱ��
 *
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    �� 
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
 * \brief ����һ��ͨ���Ľ��޼Ĵ���ֵ��PWM���ڣ�
 *
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \param[in] regvalue   : �Ĵ���ֵ
 * \return    ��
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
 * \brief ����һ��ͨ����ƥ��Ĵ���ֵ��PWMռ�ձȣ�
 *
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \param[in] regvalue   : �Ĵ���ֵ
 * \return    ��
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
 * \brief ����һ��ͨ���Ķ���ģʽֵ
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_center_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_CENTER(channel);
}
/**
 * \brief ���һ��ͨ���Ķ���ģʽֵ
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_center_val_clr (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_CENTER(channel);
}

/**
 * \brief ����һ��ͨ������Ч��ƽ״̬����
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_pola_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_POLAR(channel);
}
/**
 * \brief ���һ��ͨ������Ч��ƽ״̬����
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_pola_val_clr (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_POLAR(channel);
}

/**
 * \brief ����һ��ͨ��������ʱ��ʹ��
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_dte_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_DTE(channel);
}
/**
 * \brief ��ֹһ��ͨ��������ʱ��
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_dte_val_clr (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_DTE(channel);
}


/**
 * \brief ����һ��ͨ��������ʱ��
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \param[in] deadtime    : ����ʱ��
 * \return    ��
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
 * \brief ʹ�ܹ��ܼĴ�������
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_disup_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_DISUP(channel);
}
/**
 * \brief ��ֹ���ܼĴ�������
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ������Чֵ��0 ~ 2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_disup_val_clr (amhw_mcpwm_t *p_hw_mcpwm, uint8_t channel)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_DISUP(channel);
}

/**
 * \brief ʹ��DCģʽ
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_dcmode_val_set (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconset = (uint32_t)1<<31; 

}
/**
 * \brief ��ֹDCģʽ
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_dcmode_val_clr (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_DCMODE;
}

/**
 * \brief ʹ��ACģʽ
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_acmode_val_set (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_ACMODE;
}
/**
 * \brief ��ֹACģʽ
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_acmode_val_clr (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_ACMODE;
}

/**
 * \brief ���MCCPx�Ĵ��� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_capclr_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mccapclr = AMHW_MCPWM_CAPCLR_CAP(channel);
}

/**
 * \brief ��������жϱ�־ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_flagilim_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintfclr = AMHW_MCPWM_INT_ILIM(channel);
}
/**
 * \brief ���ƥ���жϱ�־ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_flagimat_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintfclr = AMHW_MCPWM_INT_IMAT(channel);
}
/**
 * \brief ��������жϱ�־ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_flagicap_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintfclr = AMHW_MCPWM_INT_ICAP(channel);
}

/**
 * \brief ��������ж�ʹ�� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_enilim_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintenclr = AMHW_MCPWM_INT_ILIM(channel);
}
/**
 * \brief ���ƥ���ж�ʹ�� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_enimat_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintenclr = AMHW_MCPWM_INT_IMAT(channel);
}
/**
 * \brief ��������ж�ʹ�� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_enicap_clr (amhw_mcpwm_t *p_hw_mcpwm, int channel)
{
    p_hw_mcpwm->mcintenclr = AMHW_MCPWM_INT_ICAP(channel);
}



/**
 * \brief ʹMCOB��MCOA����ķ����෴ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_invbdc_set (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconset = AMHW_MCPWM_CON_INVBDC;
}
/**
 * \brief ȡ��MCOB��MCOA����ķ����෴���� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_invbdc_clr (amhw_mcpwm_t *p_hw_mcpwm)
{
    p_hw_mcpwm->mcconclr = AMHW_MCPWM_CON_INVBDC;
}

/**
 * \brief ����ͨ�Ÿ�ʽ
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] pattern    : ͨ�Ÿ�ʽ���μ�
 *                         \ref grp_amhw_mcpwm_patent_flags  "Patent Configuration Flags"
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_mccp_val_set (amhw_mcpwm_t *p_hw_mcpwm, uint32_t pattern )
{  
    p_hw_mcpwm->mccp = pattern;
}
/**
 * \brief ��ȡ�жϱ�־�Ĵ���ָ��λ��ֵ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] inttype    : ָ��λ
 * \return    ָ��λ��ֵ0����1
 */
am_static_inline 
bool_t amhw_mcpwm_mcintf_getvalue (amhw_mcpwm_t *p_hw_mcpwm, uint32_t inttype)
{
	return ((p_hw_mcpwm->mcintf & inttype) ? TRUE : FALSE);
}

/**
 * \brief ��ȡ����Ĵ�����ֵ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ����ͨ��0-2��ʱ����ʵʱֵ
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
 * \brief �����ж����� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] inttype    : �ж����ͣ��μ�
 *							\ref grp_amhw_mcpwm_inttype_flags  "Inttype Configuration Flags"
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_mcinten_set (amhw_mcpwm_t *p_hw_mcpwm, uint32_t inttype)
{
	p_hw_mcpwm->mcintenset = inttype;
}
/**
 * \brief ����ж����� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] inttype    : �ж����ͣ��μ�
 *							\ref grp_amhw_mcpwm_inttype_flags  "Inttype Configuration Flags"
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_mcinten_clr(amhw_mcpwm_t *p_hw_mcpwm, uint32_t inttype)
{
	p_hw_mcpwm->mcintenclr = inttype;
}
/**
 * \brief ����ж��жϱ�־ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] inttype    : �ж����ͣ��μ�
 *							\ref grp_amhw_mcpwm_inttype_flags  "Inttype Configuration Flags"
 * \return    ��
 */
am_static_inline 
void amhw_mcpwm_mcintf_clr (amhw_mcpwm_t *p_hw_mcpwm, uint32_t inttype)
{
	p_hw_mcpwm->mcintfclr = inttype;
}

/**
 * \brief ��ȡ�жϱ�־�Ĵ�������λ��ֵ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] num        : ͨ��0-2
 * \return    ָ��λ��ֵ0����1
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
 * \brief ����жϲ����־ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] num        : ͨ��0-2
 * \return    ��
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
 * \brief �����жϲ������� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] num        : ͨ��0-2
 * \return    ��
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
 * \brief ��ȡ���޼Ĵ�����ֵ 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \return    ����ͨ��0-2���޵�ֵ
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
 * \brief ��ʼ��MCPWM
 * \param[in]  p_hw_mcpwm : MCPWMָ�� 
 * \return     ��
 */
void amhw_mcpwm_init(amhw_mcpwm_t *p_hw_mcpwm);
/**
 * \brief ��ʼ��MCPWMͨ��
 * \param[in]  p_hw_mcpwm : MCPWMָ��  
 * \return     ��
 */
void amhw_mcpwm_configchannel(amhw_mcpwm_t *p_hw_mcpwm);
/**
 * \brief �����ʼ�� 
 * \param[in] p_hw_mcpwm : ָ��mcpwm�Ĵ������ָ��
 * \param[in] channel    : ͨ��0-2
 * \param[in] options    : 1--�����ء�2--�½���
 * \param[in] channelnum : 0-2
 * \return    ��
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
    

