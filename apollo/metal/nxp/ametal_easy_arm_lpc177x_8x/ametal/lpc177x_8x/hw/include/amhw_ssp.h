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
 * \brief  SSPӲ�������ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.01 15-08-19  cod, fix code style and comments.
 * - 1.00 15-07-20  ben, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_SSP_H
#define __AMHW_SSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_ssp
 * \copydoc amhw_ssp.h
 * @{
 */
    
/**
 * \brief ssp�Ĵ�����Ľṹ��
 */
typedef struct amhw_ssp {
    __IO  uint32_t  cr0;    /**< \brief �������ʣ��������ͣ����ݳ���      */
    __IO  uint32_t  cr1;    /**< \brief ѡ������/�ӻ�������ģʽ           */
    __IO  uint32_t  dr;     /**< \brief ���ݼĴ���                       */
    __I   uint32_t  sr;     /**< \brief ״̬�Ĵ���                       */
    __IO  uint32_t  cpsr;   /**< \brief ʱ��Ԥ��Ƶ�Ĵ���                  */ 
    __IO  uint32_t  imsr;   /**< \brief �ж�������������Ĵ���            */
    __IO  uint32_t  ris;    /**< \brief ԭʼ�ж�״̬�Ĵ���                */
    __IO  uint32_t  mis;    /**< \brief ���κ���ж�״̬�Ĵ���            */
    __O   uint32_t  icr;    /**< \brief �ж�����Ĵ���                    */
    __IO  uint32_t  dmacr;  /**< \brief DMA���ƼĴ���                     */ 
    
} amhw_ssp_t;


/**
 * \brief ѡ��ssp���ݴ�С
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] dss      : ���ݴ�С
 * \return    ��
 * \note   λ������ 4��16λ
 */

am_static_inline 
void amhw_ssp_data_size_select (amhw_ssp_t *p_hw_ssp, uint8_t dss)
{
    p_hw_ssp->cr0 = ((p_hw_ssp->cr0 << 4) | (dss & 0xf));
}

/**
 * \name SSP֡��ʽ
 * @{
 */

/** \brief ͨѶ֡��ʽλSPI */
#define AMHW_SSP_FRF_SPI        0

/** \brief ͨѶ֡��ʽλSSI */
#define AMHW_SSP_FRF_SSI        1

/** \brief ͨѶ֡��ʽλMICWIRE */
#define AMHW_SSP_FRF_MICWIRE    2

/** @} */

/**
 * \brief ����֡��ʽ����
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] frf      : ֡��ʽ��ֵΪAMHW_SSP_FRF_*��(#AMHW_SSP_FRF_SPI)
 * \return    ��
 * \note      λ������ 4��16λ
 */
am_static_inline 
void amhw_ssp_frame_format_set (amhw_ssp_t *p_hw_ssp, uint8_t frf)
{
    p_hw_ssp->cr0 &= ~((uint32_t) 3 << 4);
    p_hw_ssp->cr0 |= ((uint32_t)(frf & 0x3) << 4);
}

/**
 * \brief ���Կ���
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] cpol     : ���Կ��ƣ�ֵΪ1��0
 * \return ��
 */
am_static_inline
void amhw_ssp_cpol_set(amhw_ssp_t *p_hw_ssp, uint8_t cpol)
{
    if (cpol) {
        p_hw_ssp->cr0 |= (1 << 6);
    } else {
        p_hw_ssp->cr0 &= ~(1 << 6);
    }    
}

/**
 * \brief ��λ����
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] cpha     : ��λ,ֵΪ1��0
 * \return ��
 */
am_static_inline
void amhw_ssp_cpha_set (amhw_ssp_t *p_hw_ssp, uint8_t cpha)
{
    if (cpha) {
        p_hw_ssp->cr0 |= (1 << 7);
    } else {
        p_hw_ssp->cr0 &= ~(1 << 7);
    }    
}

/**
 * \brief λ����
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] scr      : ����ʱ������
 * \return ��
 */
am_static_inline
void amhw_ssp_scr_set (amhw_ssp_t *p_hw_ssp, uint8_t scr)
{
    p_hw_ssp->cr0 &= ~((uint32_t) 0xff << 8);
    p_hw_ssp->cr0 |= ((uint32_t)(scr & 0xff) << 8);
}

/**
 * \brief �ػ�ģʽѡ��
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] mode     : ���û���ã���0Ϊ����
 * \return    ��
 */
am_static_inline
void amhw_ssp_mode (amhw_ssp_t *p_hw_ssp, uint8_t mode)
{
    if (mode) {
        p_hw_ssp->cr1 |= 1 << 0;
    }
    else {
        p_hw_ssp->cr1 &=~(1 << 0);
    }
}

/**
 * \brief SSPʹ��
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_ssp_enable (amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->cr1 |= 1 << 1; 
}

/**
 * \brief SSPʧ��
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_disable (amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->cr1 &= ~(1 << 1);
}

/**
 * \brief ��������ģʽ
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_master_mode (amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->cr1 &= ~(1 << 2); 
}

/**
 * \brief ���ôӻ�ģʽ
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_slave_mode(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->cr1 |= 1 << 2;
}
/**
 * \brief �ӻ��������
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] value    : 1Ϊ���ã�0Ϊ����
 * \return    ��
 */
am_static_inline
void amhw_ssp_slave_out_set(amhw_ssp_t *p_hw_ssp, uint8_t value)
{
    if (value) p_hw_ssp->cr1 |= 1 << 3;
    else       p_hw_ssp->cr1 &= ~(1 << 3);
}

/**
 * \brief ��������
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] data     : ����
 * \return    ��
 */
am_static_inline
void amhw_ssp_send_data(amhw_ssp_t *p_hw_ssp,uint16_t data)
{
    p_hw_ssp->dr = data;
}
/**
 * \brief ��һ���ֽ�
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    �������ֽ�
 */
am_static_inline
uint8_t amhw_ssp_read_8bit_data(amhw_ssp_t *p_hw_ssp)
{
    return (uint8_t)(p_hw_ssp->dr);
}

/**
 * \brief ��һ����
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��������
 */
am_static_inline
uint16_t amhw_ssp_read_16bit_data(amhw_ssp_t *p_hw_ssp)
{
    return (uint16_t)(p_hw_ssp->dr);
}

/** \brief ���ͻ���Ϊ��  */
#define AMHW_SSP_ST_TF_EMPTY       AM_BIT(0)

/** \brief ���ͻ���δ��   */
#define AMHW_SSP_ST_TF_NOT_FULL    AM_BIT(1)

/** \brief ���ջ��治Ϊ��  */
#define AMHW_SSP_ST_RF_NOT_EMPTY   AM_BIT(2)

/** \brief ���ջ�������   */
#define AMHW_SSP_ST_RF_FULL        AM_BIT(3)

/** \brief ����æ��־   */
#define AMHW_SSP_ST_LINE_BUSY      AM_BIT(4)

/**
 * \brief ��״̬�Ĵ���
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return ������״̬
 */
am_static_inline
uint8_t amhw_ssp_read_status(amhw_ssp_t *p_hw_ssp)
{
    return (uint8_t)(p_hw_ssp->sr);
}

/**
 * \brief ����ʱ�ӷ�Ƶ
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] prescale : ��Ƶ
 * \return    ��
 */
am_static_inline
void amhw_ssp_set_clock_prescale(amhw_ssp_t *p_hw_ssp, uint8_t prescale)
{
    p_hw_ssp->cpsr = prescale; /* prescale > 2 && prescale < 254 && even */
}

/**
 * \name SSP�ж�����
 * @{
 */

/** \brief ��������ж�   */
#define AMHW_SSP_IM_ROR  AM_BIT(0)

/** \brief ���ճ�ʱ�ж�   */
#define AMHW_SSP_IM_RT   AM_BIT(1)

/** \brief Rx FIFO������һ��Ϊ��ʱ�����ж�   */
#define AMHW_SSP_IM_RX   AM_BIT(2)

/** \brief Tx FIFO������һ��Ϊ��ʱ�����ж�    */
#define AMHW_SSP_IM_TX   AM_BIT(3)

/** @} */

/**
 * \brief �����ж�
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] flags    : �жϱ�־��ֵΪAMHW_SSP_IM_* ��(#AMHW_SSP_IM_ROR)
 * \return none
 */
am_static_inline
void amhw_ssp_int_set(amhw_ssp_t *p_hw_ssp, uint8_t flags)
{
    p_hw_ssp->imsr = (flags & 0xf);
}

/**
 * \brief �ж�����
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] flags    : �жϱ�־��ֵΪAMHW_SSP_IM_* ��(#AMHW_SSP_IM_ROR)
 * \return    ��
 */
am_static_inline
void amhw_ssp_int_clear(amhw_ssp_t *p_hw_ssp, uint8_t flags)
{
    p_hw_ssp->imsr &= ~(flags);
}

/**
 * \name SSP MIS�ж�
 * @{
 */

/** \brief ��������ж�   */
#define AMHW_SSP_MIS_ROR  AM_BIT(0)

/** \brief ���ճ�ʱ�ж�   */
#define AMHW_SSP_MIS_RT   AM_BIT(1)

/** \brief Rx FIFO������һ��Ϊ��ʱ�����ж� */
#define AMHW_SSP_MIS_RX   AM_BIT(2)

/** \brief Tx FIFO������һ��Ϊ��ʱ�����ж�   */
#define AMHW_SSP_MIS_TX   AM_BIT(3)

/** @} */

/**
 * \brief ���ж�״̬�Ĵ���
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ������״̬��,ֵΪAMHW_SSP_MIS_* ��(#AMHW_SSP_MIS_ROR)
 */
am_static_inline
uint8_t amhw_ssp_int_status_read(amhw_ssp_t *p_hw_ssp)
{
    return (uint8_t)p_hw_ssp->mis;
}

/**
 * \brief �������ж�
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_clear_roric(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->icr |= 1 << 0; /**< \brief �����������жϱ�־  */
}

/**
 * \brief ������ճ�ʱ�ж�
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_clear_rtic(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->icr |= 1 << 1; /**< \brief  ������ճ�ʱ�жϱ�־ */
}

/**
 * \brief dma����ʹ��
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_dma_rx_enable(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->dmacr |= 1 << 0; 
}

/**
 * \brief dma���ս���
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_dma_rx_disable(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->dmacr &= ~(1 << 0); 
}

/**
 * \brief dma����ʹ��
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_dma_tx_enable(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->dmacr |= 1 << 1;
}

/**
 * \brief dma���ͽ���
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_ssp_dma_tx_disable(amhw_ssp_t *p_hw_ssp)
{
    p_hw_ssp->dmacr &= ~(1 << 1);
}

/**
 * \brief ����SSPʱ��Ƶ��
 * \param[in] p_hw_ssp : ָ��SSP�Ĵ������ָ��
 * \param[in] target_clock : SSPʱ��Ƶ��
 * \param[in] ssp_pclk : SSP����ʱ��Ƶ��
 * \return    ���ú�SSPʱ��Ƶ��
 */
uint32_t amhw_ssp_set_clock(amhw_ssp_t *p_hw_ssp,uint32_t target_clock,uint32_t ssp_pclk);

/**
 * @} amhw_if_ssp
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_SSP_H */

/* end of file */ 

