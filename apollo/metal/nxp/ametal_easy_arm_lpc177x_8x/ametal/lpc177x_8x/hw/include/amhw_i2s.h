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
 * \brief I2S Ӳ�������ӿ� 
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
 * \brief I2S �Ĵ����ṹ��	
 */
typedef struct amhw_i2s {
    __IO uint32_t i2sdao;        /**< \brief ������Ƶ����Ĵ���        */
    __IO uint32_t i2sdai;        /**< \brief ������Ƶ����Ĵ���        */
    __O  uint32_t i2stxfifo;     /**< \brief ����FIFO            */
    __I  uint32_t i2srxfifo;     /**< \brief ����FIFO            */
    __I  uint32_t i2sstate;      /**< \brief ״̬�����Ĵ���                  */
    __IO uint32_t i2sdma1;       /**< \brief DMA���üĴ���1       */
    __IO uint32_t i2sdma2;       /**< \brief DMA���üĴ���2       */
    __IO uint32_t i2sirq;        /**< \brief �ж�������ƼĴ���         */
    __IO uint32_t i2stxrate;     /**< \brief ����MCLK��Ƶ��                    */
    __IO uint32_t i2srxrate;     /**< \brief ����MCLK��Ƶ��                    */
    __IO uint32_t i2stxbitrate;  /**< \brief ����λ���ʷ�Ƶ��                */
    __IO uint32_t i2srxbitrate;  /**< \brief ����λ���ʷ�Ƶ��                 */
    __IO uint32_t i2stxmode;     /**< \brief ����ģʽ����                          */
    __IO uint32_t i2srxmode;     /**< \brief ����ģʽ����                           */
}	amhw_i2s_t;


/**
 * \name ����I2S���������ʽ
 * \anchor grp_amhw_i2s_i2sdao_cfg_flags
 * @{
 */
/* �����ֿ� */
#define AMHW_I2S_I2SDAO_WORDWIDTH8     0              /**< \brief �ֿ�8λ   */ 
#define AMHW_I2S_I2SDAO_WORDWIDTH16    1              /**< \brief �ֿ�16λ  */ 
#define AMHW_I2S_I2SDAO_WORDWIDTH32    3              /**< \brief �ֿ�32λ  */ 
 
/* ��������ģʽ */  
#define AMHW_I2S_I2SDAO_MONO           (1 << 2)       /**< \brief ������  */ 
#define AMHW_I2S_I2SDAO_STEREO         (0 << 2)       /**< \brief ������  */ 

#define AMHW_I2S_I2SDAO_STOP           (1 << 3)       /**< \brief ֹͣ���  */  
 
#define AMHW_I2S_I2SDAO_RESET          (1 << 4)       /**< \brief ��λ���  */ 

#define AMHW_I2S_I2SDAO_NOMUTE         (1 << 15)      /**< \brief �ر�FIFOs  */ 

/* ��������ģʽ */
#define AMHW_I2S_I2SDAO_MASTER        ~(1 << 5)       /**< \brief ����ģʽ  */ 
#define AMHW_I2S_I2SDAO_SLAVE          (1 << 5)       /**< \brief �ӻ�ģʽ  */ 

#define AMHW_I2S_I2SDAO_WSHALFPERIOD   (0x1FF << 6)   /**< \brief �������� */

#define AMHW_I2S_I2SDAO_MUTE           (1 << 15)      /**< \brief �رշ���  */ 

/** @} */

/**
 * \name ����I2S���͸�ʽ
 * \anchor grp_amhw_i2s_i2sdai_cfg_flags
 * @{
 */

/* �����ֿ� */
#define AMHW_I2S_I2SDAI_WORDWIDTH8     0              /**< \brief �ֿ�8λ   */
#define AMHW_I2S_I2SDAI_WORDWIDTH16    1              /**< \brief �ֿ�16λ  */ 
#define AMHW_I2S_I2SDAI_WORDWIDTH32    3              /**< \brief �ֿ�32λ  */ 

/* ��������ģʽ */
#define AMHW_I2S_I2SDAI_MONO           (1 << 2)       /**< \brief ������  */ 
#define AMHW_I2S_I2SDAI_STEREO         (0 << 2)       /**< \brief ������  */ 

#define AMHW_I2S_I2SDAI_STOP           (1 << 3)       /**< \brief ֹͣ����  */   

#define AMHW_I2S_I2SDAI_RESET          (1 << 4)       /**< \brief ��λ����  */
  
/* ��������ģʽ */
#define AMHW_I2S_I2SDAI_MASTER        ~(1 << 5)       /**< \brief ����ģʽ  */ 
#define AMHW_I2S_I2SDAI_SLAVE          (1 << 5)       /**< \brief �ӻ�ģʽ  */
#define AMHW_I2S_I2SDAI_WSHALFPERIOD   (0x1FF << 6)   /**< \brief �������� */

/** @} */

/**
 * \name  I2SSTATE �ĺ궨�� 
 * @{     
 */
#define AMHW_I2S_I2SSTATE_IRQ          (1 << 0)       /**< \brief ��ͨ���ͽ����ж�״̬  */
 
#define AMHW_I2S_I2SSTATE_DMAREQ1      (1 << 1)       /**< \brief DMA1���ͽ����ж�״̬  */
#define AMHW_I2S_I2SSTATE_DMAREQ2      (1 << 2)       /**< \brief DMA2���ͽ����ж�״̬  */

#define AMHW_I2S_I2SSTATE_RXLEVEL      (0x0F << 8)    /**< \brief ���ջ��浱ǰֵ  */

#define AMHW_I2S_I2SSTATE_TXLEVEL      (0x0F << 16)   /**< \brief ���ͻ��浱ǰֵ  */

/** @} */

/**
 * \name ����I2S DMA1�����ʽ
 * \anchor grp_amhw_i2s_i2sdma1_cfg_flags
 * @{
 */
#define AMHW_I2S_I2SDMA1_RXENABLE      (1 << 0)       /**< \brief ʹ��DMA1�����ж� */

#define AMHW_I2S_I2SDMA1_TXENABLE      (1 << 1)       /**< \brief ʹ��DMA1�����ж� */

#define AMHW_I2S_I2SDMA1_RXDEPTH       (0xF << 8)     /**< \brief ����DMA1����FIFO�����ж� ���ֵ*/

#define AMHW_I2S_I2SDMA1_TXDEPTH       (0xF << 16)    /**< \brief ����DMA1����FIFO�����ж� ���ֵ*/

/** @} */

/**
 * \name ����I2S DMA2�����ʽ
 * \anchor grp_amhw_i2s_i2sdma2_cfg_flags
 * @{
 */ 
#define AMHW_I2S_I2SDMA2_RXENABLE      (1 << 0)       /**< \brief ʹ��DMA2�����ж� */

#define AMHW_I2S_I2SDMA2_TXENABLE      (1 << 1)       /**< \brief ʹ��DMA2�����ж� */
 
#define AMHW_I2S_I2SDMA2_RXDEPTH       (0xF << 8)     /**< \brief ����DMA2����FIFO�����ж� ���ֵ*/

#define AMHW_I2S_I2SDMA2_TXDEPTH       (0xF << 16)    /**< \brief ����DMA2����FIFO�����ж� ���ֵ*/

/** @} */

/**
 * \name I2SIRQ �ĺ궨��
 * @{
 */

#define AMHW_I2S_RXIRQ_ENABLE          (1 << 0)       /**< \brief ʹ�ܽ����ж� */

#define AMHW_I2S_TXIRQ_ENABLE          (1 << 1)       /**< \brief ʹ�ܷ����ж� */

#define AMHW_I2S_RXIRQ_DEPTH           (0xF << 8)     /**< \brief ���ý���FIFO�����ж� ���ֵ*/

#define AMHW_I2S_TXIRQ_DEPTH           (0xF << 16)    /**< \brief ���÷���FIFO�����ж� ���ֵ*/

/** @} */

/**
 * \name I2SRXMODE �ĺ궨��
 * @{  
 */
#define AMHW_I2S_RXCLKSEL_FRACCLOCK    0              /**< \brief ���ý���ʱ��Ϊ��Ƶʱ��*/
#define AMHW_I2S_RXCLKSEL_RXMCLK       2              /**< \brief ���÷���ʱ��Ϊ��ʱ��*/
#define AMHW_I2S_I2SRXMODE_RX4PIN      (1 << 2)       /**< \brief ����Ϊ4-pin����ģʽ*/

#define AMHW_I2S_I2SRXMODE_RXMCENA     (1 << 3)       /**< \brief ʹ�ܽ�����ʱ��*/

/** @} */

/**
 * \name  I2STXMODE �ĺ궨�� 
 * @{     
 */
#define AMHW_I2S_TXCLKSEL_FRACCLOCK    0               /**< \brief ���÷���ʱ��Ϊ��Ƶʱ��*/
#define AMHW_I2S_TXCLKSEL_TXMCLK       2               /**< \brief ���ý���ʱ��Ϊ��ʱ��*/

#define AMHW_I2S_I2STXMODE_TX4PIN      (1 << 2)        /**< \brief ����Ϊ4-pin����ģʽ*/

#define AMHW_I2S_I2STXMODE_TXMCENA     (1 << 3)        /**< \brief ʹ�ܷ�����ʱ��*/

/** @} */

/**
 * \brief I2S�ж�ʹ��
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] int_enable : ʹ��λ��ֵΪ AMHW_I2S_* (AMHW_I2S_RXIRQ_ENABLE)
 *
 * \return    ��
 */
am_static_inline
void amhw_i2s_int_enable (amhw_i2s_t *p_hw_i2s, uint32_t int_enable)
{
     p_hw_i2s->i2sirq |= int_enable;
}

/**
 * \brief  I2S �жϽ���
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] int_disable : ����λ��ֵΪ AMHW_I2S_* (AMHW_I2S_TXIRQ_ENABLE)
 *
 * \return    ��
 */
am_static_inline
void amhw_i2s_int_disable (amhw_i2s_t *p_hw_i2s, uint32_t int_disable)
{
     p_hw_i2s->i2sirq &= ~int_disable;
}

/**
 * \brief I2S �����ж���ȴ���ֵ����
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] depth : ���ֵ  ��ֵΪ AMHW_I2S_* (#AMHW_I2S_TXIRQ_DEPTH)
 *
 * \return    ��
 */
am_static_inline
void amhw_i2s_txdepth_irqset (amhw_i2s_t *p_hw_i2s, char depth)
{
     p_hw_i2s->i2sirq |= depth << 16;
	   p_hw_i2s->i2sirq |= 1 << 8;     /* Ĭ�Ͻ���levelֵΪ1 */
}

/**
 * \brief  I2S �����ж���ȴ���ֵ����
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] depth : ���ֵ �� ֵΪ   AMHW_I2S_* (#AMHW_I2S_RXIRQ_DEPTH)
 *
 * \return    ��
 */
am_static_inline
void amhw_i2s_rxdepth_irqset (amhw_i2s_t *p_hw_i2s, char depth)
{
     p_hw_i2s->i2sirq |= depth << 8;
	   p_hw_i2s->i2sirq |= 8 << 16;   /* Ĭ�Ϸ���levelֵΪ8 */
}

/**
 * \brief ��ȡI2S�ж�״̬
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 *
 * \return  I2S�ж�״̬
 */
am_static_inline
uint32_t amhw_i2s_stat_get (amhw_i2s_t *p_hw_i2s)
{
    return p_hw_i2s->i2sstate; 
}

/**
 * \brief ����I2S���͸�ʽ
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] cfg_flags  : ����ֵ �� �μ�
 *                         \ref grp_amhw_i2s_i2sdao_cfg_flags "Transfer Configuration Flags"
 *                         
 * \return  ��
 */
am_static_inline
void amhw_i2s_i2sdao_config (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdao &= cfg_flags;
}

/**
 * \brief ������������
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] cfg_flags  : ����ֵ��ֵΪAMHW_I2S_I2SDAO_MASTER
 *                         
 * \return  ��
 */
am_static_inline
void amhw_i2s_i2sdao_master (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdao &= cfg_flags;
}

/**
 * \brief ���ôӻ�����
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] cfg_flags  : ����ֵ��ֵΪAMHW_I2S_I2SDAO_SLAVE
 *                         
 * \return  ��
 */
am_static_inline
void amhw_i2s_i2sdao_slave (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdao |= cfg_flags;
}


/**
 * \brief ����I2S���ո�ʽ
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] cfg_flags  : ����ֵ�� �μ�
 *                         \ref grp_amhw_i2s_i2sdai_cfg_flags "Receive Configuration Flags"
 *                         
 * \return  ��
 */
am_static_inline
void amhw_i2s_i2sdai_config (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdai |= cfg_flags;
}

/**
 * \brief ������������
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] cfg_flags  : ����ֵ��ֵΪAMHW_I2S_I2SDAI_MASTER
 *                         
 * \return  ��
 */
am_static_inline
void amhw_i2s_i2sdai_master (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdai &= cfg_flags;
}

/**
 * \brief ���ôӻ�����
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] cfg_flags  : ����ֵ��ֵΪAMHW_I2S_I2SDAI_SLAVE
 *                         
 * \return  ��
 */
am_static_inline
void amhw_i2s_i2sdai_slave (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdai &= cfg_flags;
}


/**
 * \brief ʹ�ܴ���
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��       
 *
 * \return  ��
 */
am_static_inline
void amhw_i2s_transmit_enable(amhw_i2s_t *p_hw_i2s)
{
    p_hw_i2s->i2sdai &= ~(AMHW_I2S_I2SDAI_STOP | AMHW_I2S_I2SDAI_RESET);
	p_hw_i2s->i2sdao &= ~(AMHW_I2S_I2SDAO_STOP | AMHW_I2S_I2SDAO_RESET);
    p_hw_i2s->i2sdao &= ~AMHW_I2S_I2SDAO_NOMUTE;	 
}
	
/**
 * \brief ����I2S��DMA1�ĸ�ʽ
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��       
 * \param[in] cfg_flags  : ����ֵ���μ�
 *                         \ref grp_amhw_i2s_i2sdma1_cfg_flags"DMA1 Transmit Configuration Flags"
 *                         
 * \return  ��
 */
am_static_inline
void amhw_i2s_i2sdma1_config (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdma1 |= cfg_flags;
}

/**
 * \brief ����I2S��DMA2�ĸ�ʽ
 *
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��       
 * \param[in] cfg_flags  : ����ֵ���μ�
 *                         \ref grp_amhw_i2s_i2sdma2_cfg_flags"DMA2 Transmit Configuration Flags"
 *                         
 * \return  ��
 */
am_static_inline
void amhw_i2s_i2sdma2_config (amhw_i2s_t *p_hw_i2s, uint32_t cfg_flags)
{
    p_hw_i2s->i2sdma2 |= cfg_flags;
}

/**
 * \brief ��ȡI2S��ǰ�������ݸ���ֵ
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��      
 *
 * \return ��
 */
am_static_inline
uint32_t amhw_i2s_rxcurlevel_get (amhw_i2s_t *p_hw_i2s)
{
    return (char)((p_hw_i2s->i2sstate) >> 8); 
}

/**
 * \brief ��ȡI2S��ǰ�������ݸ���ֵ
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ�� 
 *
 * \return ��
 */
am_static_inline
uint32_t amhw_i2s_txcurlevel_get (amhw_i2s_t *p_hw_i2s)
{
    return (char)((p_hw_i2s->i2sstate) >> 16);
}

/**
 * \brief ����I2S��������
 * \param[in] p_hw_i2s :  ָ��I2S�Ĵ������ָ�� 
 * \param[in] tx_rate : 16λ�޷�������
 *
 * \return ��
 */
am_static_inline
void amhw_i2s_i2stxrate_set (amhw_i2s_t *p_hw_i2s, uint32_t tx_rate)
{
    p_hw_i2s->i2stxrate |= tx_rate; 
}

/**
 * \brief ����I2S��������
 * \param[in] p_hw_i2s :  ָ��I2S�Ĵ������ָ�� 
 * \param[in] rx_rate : 16λ�޷�������
 *
 * \return ��
 */
am_static_inline
void amhw_i2s_i2srxrate_set (amhw_i2s_t *p_hw_i2s, uint32_t rx_rate)
{
    p_hw_i2s->i2srxrate |= rx_rate; 
}

/**
 * \brief ����I2S����ģʽ
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ�� 
 * \param[in] mode_flag : ֵΪAMHW_I2S_* (AMHW_I2S_TXCLKSEL_FRACCLOCK)
 *
 * \return ��
 */
am_static_inline
void amhw_i2s_rxmode_set (amhw_i2s_t *p_hw_i2s, char mode_flag)
{
    p_hw_i2s->i2srxmode |= mode_flag; 
}

/**
 * \brief ����I2S����ģʽ
 * \param[in] p_hw_i2s : ָ��I2S�Ĵ������ָ��
 * \param[in] mode_flag : ����ֵ��ֵΪAMHW_I2S_* (AMHW_I2S_RXCLKSEL_FRACCLOCK)
 *
 * \return ��
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

