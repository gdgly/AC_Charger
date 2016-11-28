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
 * \brief  CANӲ�������ӿ�ʵ��
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
 * \name �����˲�RAM�ĳߴ�
 * \anchor grp_amhw_canaf_ram_size
 * @{
 */

#define AMHW_CANAF_RAM_SIZE  2048              /**< \brief CAN �˲� RAM�ߴ� */

/** @} */

/**
 * \brief �����˲�RAM����
 */
typedef struct amhw_canaf_ram {
  __IO uint32_t mask[AMHW_CANAF_RAM_SIZE / 4]; /**< \brief ID���� */
} amhw_canaf_ram_t;

/** 
 * \brief �����˲�������
 */
typedef struct amhw_canaf {
  __IO uint32_t afmr;                   /**< \brief �����˲��Ĵ��� */
  __IO uint32_t sff_sa;                 /**< \brief ��׼֡������ʼ��ַ�Ĵ��� */
  __IO uint32_t sff_grp_sa;             /**< \brief ��׼֡����ʼ��ַ�Ĵ���   */
  __IO uint32_t eff_sa;                 /**< \brief ��չ֡��ʼ��ַ�Ĵ���     */
  __IO uint32_t eff_grp_sa;             /**< \brief ��չ֡����ʼ��ַ�Ĵ���   */
  __IO uint32_t endtable;               /**< \brief AF�������Ĵ���  */
  __I  uint32_t lut_errad;              /**< \brief LUT�����ַ�Ĵ��� */
  __I  uint32_t lut_err;                /**< \brief LUT����Ĵ���     */
  __IO uint32_t fcanie;                 /**< \brief FullCAN�ж�ʹ�ܼĴ���     */
  __IO uint32_t fcanic0;                /**< \brief FullCAN�жϺͲ���Ĵ���0  */
  __IO uint32_t fcanic1;                /**< \brief FullCAN�жϺͲ���Ĵ���1  */
} amhw_canaf_t;

/**
 * \brief ����Ĵ���
 */
typedef struct amhw_cancr {
  __I  uint32_t can_txsr;              /**< \brief CAN���뷢��״̬�Ĵ���  */
  __I  uint32_t can_rxsr;              /**< \brief CAN�������״̬�Ĵ���  */
  __I  uint32_t can_msr;               /**< \brief CAN���������Ĵ���      */
} amhw_cancr_t;

/** 
 * \brief ���ƼĴ���
 */
typedef struct amhw_can {
  __IO uint32_t mod;                  /**< \brief ����CAN�������Ĳ���ģʽ    */
  __O  uint32_t cmr;                  /**< \brief Ӱ��CAN������״̬������λ  */
  __IO uint32_t gsr;                  /**< \brief ȫ�ֿ���״̬�ʹ��������   */
  __I  uint32_t icr;                  /**< \brief �ж�״̬���ٲö�ʧ���񣬴�����벶�� */
  __IO uint32_t ier;                  /**< \brief �ж�ʹ��  */
  __IO uint32_t btr;                  /**< \brief ����ʱ��  */
  __IO uint32_t ewl;                  /**< \brief ���󾯱�����    */
  __I  uint32_t sr;                   /**< \brief ״̬�Ĵ���      */
  __IO uint32_t rfs;                  /**< \brief ����֡״̬      */
  __IO uint32_t rid;                  /**< \brief ���յ��ı�ʶ��  */
  __IO uint32_t rda;                  /**< \brief ���յ��������ֽ�1��4  */
  __IO uint32_t rdb;                  /**< \brief ���յ��������ֽ�5��8  */
  __IO uint32_t tfi1;                 /**< \brief ����֡��Ϣ��Tx������1�� */
  __IO uint32_t tid1;                 /**< \brief ���ͱ�ʶ����Tx������1�� */
  __IO uint32_t tda1;                 /**< \brief ���������ֽ�1��4��Tx������1�� */
  __IO uint32_t tdb1;                 /**< \brief ���������ֽ�5��8��Tx������1�� */
  __IO uint32_t	tfi2;                 /**< \brief ����֡��Ϣ��Tx������2��  */
  __IO uint32_t tid2;                 /**< \brief ���ͱ�ʶ����Tx������2��  */
  __IO uint32_t tda2;                 /**< \brief ���������ֽ�1��4 ��Tx������2�� */
  __IO uint32_t tdb2;                 /**< \brief ���������ֽ�5��8 ��Tx������2�� */
  __IO uint32_t tfi3;                 /**< \brief ����֡��Ϣ��Tx������3�� */
  __IO uint32_t tid3;                 /**< \brief ���ͱ�ʶ����Tx������3�� */
  __IO uint32_t tda3;                 /**< \brief ���������ֽ�1��4 ��Tx������3�� */
  __IO uint32_t tdb3;                 /**< \brief ���������ֽ�5��8(Tx������3��   */
} amhw_can_t;

/**
 * \brief CAN ����FullCAN����׼֡��ʽ����ʶ������ʼ��ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 * \param[in] addr       : ��ʼ��ַ ��4���ֽڽ���ƫ��
 *
 * \return ��
 */
am_static_inline 
void amhw_canaf_standid_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->sff_sa = addr;
}

/**
 * \brief CAN ���ñ�׼֡���ʽ��ʶ������ʼ��ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 * \param[in] addr       : ��ʼ��ַ ��4���ֽڽ���ƫ��
 *
 * \return ��
 */
am_static_inline 
void amhw_canaf_standid_group_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->sff_grp_sa = addr;
}
    
/**
 * \brief CAN ������չ֡��ʽ��ʶ������ʼ��ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 * \param[in] addr       : ��ʼ��ַ ��4���ֽڽ���ƫ��
 *
 * \return ��
 */
am_static_inline 
void amhw_canaf_externid_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->eff_sa = addr;
}

/**
 * \brief CAN ������չ֡���ʽ��ʶ������ʼ��ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 * \param[in] addr       : ��ʼ��ַ ��4���ֽڽ���ƫ��
 *
 * \return ��
 */
am_static_inline 
void amhw_canaf_externid_group_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->eff_grp_sa = addr;
}

/**
 * \brief CAN ���ý������ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 * \param[in] addr       : ��ʼ��ַ ��4���ֽڽ���ƫ��
 *
 * \return ��
 */
am_static_inline 
void amhw_canaf_endtable_set (amhw_canaf_t *p_hw_canaf, uint32_t addr)
{
    p_hw_canaf->endtable = addr;
}

/**
 * \brief CAN ����FULLCAN�ж�ʹ��
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 * \param[in] mask       : �ж�ʹ��λ
 *
 * \return ��
 */
am_static_inline
void amhw_canaf_fcanie_set (amhw_canaf_t *p_hw_canaf, uint32_t mask)
{
    p_hw_canaf->fcanie = mask;
}

/**
 * \brief CAN ����FULLCAN IC0 �жϲ���
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 * \param[in] mask       : �ж�ʹ��λ
 *
 * \return ��
 */
am_static_inline
void amhw_canaf_fcanic0_set (amhw_canaf_t *p_hw_canaf, uint32_t mask)
{
    p_hw_canaf->fcanic0 = mask;
}

/**
 * \brief CAN ����FULLCAN IC1 �жϲ���
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 * \param[in] mask       : �ж�ʹ��λ
 *
 * \return ��
 */
am_static_inline
void amhw_canaf_fcanic1_set (amhw_canaf_t *p_hw_canaf, uint32_t mask)
{
    p_hw_canaf->fcanic1 = mask;
}

/**
 * \brief CAN ��ȡFullCAN����׼֡��ʽ����ʶ������ʼ��ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return FullCAN����׼֡��ʽ����ʶ������ʼ��ַ
 */
am_static_inline
uint32_t amhw_canaf_standid_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->sff_sa;
}

/**
 * \brief CAN ��ȡ��׼֡���ʽ��ʶ������ʼ��ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return ��׼֡���ʽ��ʶ������ʼ��ַ
 */
am_static_inline
uint32_t amhw_canaf_standid_group_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->sff_grp_sa;
}

/**
 * \brief CAN ��ȡ��չ֡��ʽ��ʶ������ʼ��ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return ��չ֡��ʽ��ʶ������ʼ��ַ
 */
am_static_inline
uint32_t amhw_canaf_externid_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->eff_sa;
}

/**
 * \brief CAN ��ȡ��չ֡���ʽ��ʶ������ʼ��ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return ��չ֡���ʽ��ʶ������ʼ��ַ
 */
am_static_inline
uint32_t amhw_canaf_externid_group_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->eff_grp_sa;
}

/**
 * \brief CAN ��ȡ�������ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return �������ַ
 */
am_static_inline
uint32_t amhw_canaf_endtable_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->endtable;
}

/**
 * \brief CAN ��ȡLUT�����ַ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return LUT�����ַ
 */
am_static_inline
uint32_t amhw_canaf_luterrad_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->lut_errad;
}

/**
 * \brief CAN ��ȡLUT����
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return LUT�����ַ
 */
am_static_inline
uint32_t amhw_canaf_luterr_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->lut_err;
}

/**
 * \brief CAN ��ȡFULLCAN�ж�ʹ��
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return FULLCAN�ж�ʹ��λ
 */
am_static_inline
uint32_t amhw_canaf_fcanie_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->fcanie;
}

/**
 * \brief CAN ��ȡFULLCAN IC0 �жϲ���
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return FULLCAN IC0 �жϲ���
 */
am_static_inline
uint32_t amhw_canaf_fcanic0_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->fcanic0;
}

/**
 * \brief CAN ��ȡFULLCAN IC1 �жϲ���
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return FULLCAN IC1 �жϲ���
 */
am_static_inline
uint32_t amhw_canaf_fcanic1_get (amhw_canaf_t *p_hw_canaf)
{
    return p_hw_canaf->fcanic1;
}

/**
 * \brief CAN ���� RAM �˲����ID����ID�ķ�Χ
 *
 * \param[in] p_hw_canaf_ram : ָ��CANAF_RAM�Ĵ������ָ��
 * \param[in] block          : �˲���ram��ĳһ��
 * \param[in] mask           : ID����ID�ķ�Χ
 *
 * \return ��
 */
am_static_inline 
void amhw_can_filter_set (amhw_canaf_ram_t *p_hw_canaf_ram, uint16_t block, uint32_t mask)
{
    p_hw_canaf_ram->mask[block] = mask;
}

/**
 * \brief CAN ��ȡ RAM �˲����ID����ID�ķ�Χ
 *
 * \param[in] p_hw_canaf_ram : ָ��CANAF_RAM�Ĵ������ָ��
 * \param[in] block          : �˲���ram��ĳһ��
 *
 * \return RAM �˲����ID����ID�ķ�Χ
 */
am_static_inline 
uint32_t amhw_can_filter_get (amhw_canaf_ram_t *p_hw_canaf_ram, uint16_t block)
{
    return p_hw_canaf_ram->mask[block];
}

/**
 * \name �����˲�����λ����
 * \anchor grp_amhw_can_afmr
 * @{
 */
 
#define AMHW_CAN_AFMR_ACCOFF			0   /**< \brief �����˲����Ĵ�����AccOffλ  */
#define AMHW_CAN_AFMR_ACCBP				1   /**< \brief �����˲����Ĵ�����AccBPλ   */
#define AMHW_CAN_AFMR_EFCAN				2   /**< \brief �����˲����Ĵ�����Efcanλ   */
#define AMHW_CAN_AFMR_RVS28				3   /**< \brief ����                        */

/** @} */

/**
 * \brief CAN����ģʽ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_onmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr &= ~(0x01 << AMHW_CAN_AFMR_ACCOFF);
}

/**
 * \brief CAN�ر�ģʽ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_offmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr |= (0x01 << AMHW_CAN_AFMR_ACCOFF);
}

/**
 * \brief CAN��·ģʽ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_bypassmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr &= ~0x07;
    p_hw_canaf->afmr |= (0x01 << AMHW_CAN_AFMR_ACCBP);
}

/**
 * \brief CAN����ģʽ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_workmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr &= ~0x07;
}

/**
 * \brief CANFullCANģʽ
 *
 * \param[in] p_hw_canaf : ָ��CANAF�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_fullcanmode (amhw_canaf_t *p_hw_canaf)
{
    p_hw_canaf->afmr &= ~0x07;
    p_hw_canaf->afmr |= (0x01 << AMHW_CAN_AFMR_EFCAN);
}

/**
 * \name ���뷢��״̬��λ����
 * \anchor grp_amhw_cancr_tx
 * @{
 */

typedef uint32_t amhw_cancr_tx_t;
#define AMHW_CANCR_TS1             (0x01 << 0)    /**< \brief CAN1 ��������Ϣ  */
#define AMHW_CANCR_TS2             (0x01 << 1)    /**< \brief CAN2 ��������Ϣ  */
#define AMHW_CANCR_TBS1            (0x01 << 8)    /**< \brief CAN1 ���ͻ�����Ч  */
#define AMHW_CANCR_TBS2            (0x01 << 9)    /**< \brief CAN2 ���ͻ�����Ч  */
#define AMHW_CANCR_TCS1            (0x01 << 16)   /**< \brief CAN1 �������  */
#define AMHW_CANCR_TCS2            (0x01 << 17)   /**< \brief CAN2 �������  */

/** @} */

/**
 * \brief CAN ��ȡ���뷢��״̬
 *
 * \param[in] p_hw_cancr : �����������ַ
 *
 * \return ���뷢��״̬
 */
am_static_inline
amhw_cancr_tx_t amhw_cancr_txsr_get (amhw_cancr_t *p_hw_cancr)
{
    return p_hw_cancr->can_txsr;
}

/**
 * \name �������״̬��λ����
 * \anchor grp_amhw_cancr_rx
 * @{
 */

typedef uint32_t amhw_cancr_rx_t;
#define AMHW_CANCR_RS1             (0x01 << 0)    /**< \brief CAN1 ��������Ϣ  */
#define AMHW_CANCR_RS2             (0x01 << 1)    /**< \brief CAN2 ��������Ϣ  */
#define AMHW_CANCR_RB1             (0x01 << 8)    /**< \brief CAN1 ������Ϣ��Ч  */
#define AMHW_CANCR_RB2             (0x01 << 9)    /**< \brief CAN2 ������Ϣ��Ч  */
#define AMHW_CANCR_DOS1            (0x01 << 16)   /**< \brief CAN1 ��Ϣδ����  */
#define AMHW_CANCR_DOS2            (0x01 << 17)   /**< \brief CAN2 ��Ϣδ���� */

/** @} */

/**
 * \brief CAN ��ȡ�������״̬
 *
 * \param[in] p_hw_cancr : �����������ַ
 *
 * \return �������״̬
 */
am_static_inline
amhw_cancr_rx_t amhw_cancr_rxsr_get (amhw_cancr_t *p_hw_cancr)
{
    return p_hw_cancr->can_rxsr;
}

/**
 * \name ����״̬��λ����
 * \anchor grp_amhw_cancr_stat
 * @{
 */

typedef uint32_t amhw_cancr_stat_t;
#define AMHW_CANCR_E1             (0x01 << 0)    /**< \brief CAN1 ��������ﵽ����ֵ */
#define AMHW_CANCR_E2             (0x01 << 1)    /**< \brief CAN2 ��������ﵽ����ֵ */
#define AMHW_CANCR_BS1            (0x01 << 8)    /**< \brief CAN1 ��ǰ���߻�Ծ  */
#define AMHW_CANCR_BS2            (0x01 << 9)    /**< \brief CAN2 ��ǰ���߻�Ծ  */

/** @} */

/**
 * \brief CAN ��ȡ����״̬
 *
 * \param[in] p_hw_cancr : �����������ַ
 *
 * \return ����״̬
 */
am_static_inline
amhw_cancr_stat_t amhw_cancr_msr_get (amhw_cancr_t *p_hw_cancr)
{
    return p_hw_cancr->can_msr;
}

/**
 * \name ģʽ�Ĵ�����λ����
 * \anchor grp_amhw_can_mod
 * @{
 */
 
#define AMHW_CAN_MOD_RM 		0       /**< \brief ��λģʽ */
#define AMHW_CAN_MOD_LOM 		1       /**< \brief ֻ��ģʽ */
#define AMHW_CAN_MOD_STM		2       /**< \brief �Բ���ģʽ */
#define AMHW_CAN_MOD_TPM 		3       /**< \brief ��������ģʽ */
#define AMHW_CAN_MOD_SM 		4       /**< \brief ˯��ģʽ */
#define AMHW_CAN_MOD_RPM 		5       /**< \brief ����ģʽ */
#define AMHW_CAN_MOD_RSV1   	6       /**< \brief ���� */
#define AMHW_CAN_MOD_TM 		7       /**< \brief ����ģʽ */
#define AMHW_CAN_MOD_RSV24 	    8       /**< \brief ���� */

/** @} */

/**
 * \brief CAN��������ģʽ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_normal_enable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod &= 0x01;
}

/**
 * \brief CAN����ֻ��ģʽ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_listenonly_enable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod |= (0x01 << AMHW_CAN_MOD_LOM);
}

/**
 * \brief CAN�����Բ���ģʽ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_selftest_enable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod |= (0x01 << AMHW_CAN_MOD_STM);
}

/**
 * \brief CAN�˳��Բ���ģʽ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_selftest_disable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod &= ~(0x01 << AMHW_CAN_MOD_STM);
}

/**
 * \brief CAN���븴λ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_reset_enable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod |= (0x01 << AMHW_CAN_MOD_RM);
}

/**
 * \brief CAN�˳���λ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_reset_disable (amhw_can_t *p_hw_can)
{
    p_hw_can->mod &= ~(0x01 << AMHW_CAN_MOD_RM);
}

/**
 * \brief CAN��������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_sleep (amhw_can_t *p_hw_can)
{
    p_hw_can->mod |= (0x01 << AMHW_CAN_MOD_SM);
}

/**
 * \brief CAN����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_wakeup (amhw_can_t *p_hw_can)
{
    p_hw_can->mod &= ~(0x01 << AMHW_CAN_MOD_SM);
}


/**
 * \name ����Ĵ�����λ����
 * \anchor grp_amhw_can_cmr
 * @{
 */
 
#define AMHW_CAN_CMR_TR					0       /**< \brief �������� */
#define AMHW_CAN_CMR_AT					1       /**< \brief ��ֹ���� */
#define AMHW_CAN_CMR_RRB				2       /**< \brief �ͷŽ��ջ����� */
#define AMHW_CAN_CMR_CDO				3       /**< \brief ������ϳ��� */
#define AMHW_CAN_CMR_SRR				4       /**< \brief �Խ������� */
#define AMHW_CAN_CMR_STB1				5       /**< \brief ѡ���ͻ�����1 */
#define AMHW_CAN_CMR_STB2				6       /**< \brief ѡ���ͻ�����2 */
#define AMHW_CAN_CMR_STB3				7       /**< \brief ѡ���ͻ�����3 */
#define AMHW_CAN_CMR_RVS23			    8       /**< \brief ���� */

/** @} */

/**
 * \brief CAN ��������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] type     : ��������
 *
 * \return ��
 */
am_static_inline
void amhw_can_cmr_set (amhw_can_t *p_hw_can, uint32_t type)
{
    p_hw_can->cmr = type;
}

/**
 * \brief CAN ���ô�������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_transrequest_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_TR);
}

/**
 * \brief CAN ��ֹ����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_aborttrans_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_AT);
}

/**
 * \brief CAN ���ѡ���ͻ�����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_txbuf_clr (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr &= ~((0x01 << AMHW_CAN_CMR_STB1) |
                       (0x01 << AMHW_CAN_CMR_STB2) |
                       (0x01 << AMHW_CAN_CMR_STB3));
}

/**
 * \brief CAN ����ѡ���ͻ�����1
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_txbuf1_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_STB1);
}

/**
 * \brief CAN ����ѡ���ͻ�����2
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_txbuf2_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_STB2);
}

/**
 * \brief CAN ����ѡ���ͻ�����3
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_txbuf3_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_STB3);
}

/**
 * \name �жϼĴ�����λ����
 * \anchor grp_amhw_can_ier
 * @{
 */
 
#define AMHW_CAN_IER_RIE			0			/**< \brief �����ж� */
#define AMHW_CAN_IER_TIE			1			/**< \brief �����ж� */
#define AMHW_CAN_IER_EIE			2			/**< \brief ���󾯸��ж� */
#define AMHW_CAN_IER_DOIE			3			/**< \brief ���ݳ����ж� */
#define AMHW_CAN_IER_WUIE			4			/**< \brief �����ж�     */
#define AMHW_CAN_IER_EPIE			5			/**< \brief ���������ж� */
#define AMHW_CAN_IER_ALIE			6			/**< \brief �ٲö�ʧ�ж� */
#define AMHW_CAN_IER_BEIE			7			/**< \brief ���ߴ����ж� */
#define AMHW_CAN_IER_IDIE			8			/**< \brief ID�����ж� */
#define AMHW_CAN_IER_TIE2			9			/**< \brief �����ж�2  */
#define AMHW_CAN_IER_TIE3			10		    /**< \brief �����ж�3  */
#define AMHW_CAN_IER_RVS20	    	11		    /* Reserved            */

/** @} */

/** \brief �ж����͵����� */
#define AMHW_CAN_INT_TYPE_COUNT    11

/**
 * \name �жϵ�����
 * \anchor grp_amhw_can_int_type
 * @{
 */

typedef uint32_t amhw_can_int_type_t;           /**< \brief �ж�����  */
#define AMHW_CAN_INT_TYPE_NONE		    0X0000  /**< \brief ���ж�  */
#define AMHW_CAN_INT_TYPE_RI			0X0001  /**< \brief �����ж� */
#define AMHW_CAN_INT_TYPE_TI			0X0002  /**< \brief �����ж� */
#define AMHW_CAN_INT_TYPE_EI			0X0004  /**< \brief ���󾯸��ж� */
#define AMHW_CAN_INT_TYPE_DOI			0X0008  /**< \brief ���ݳ����ж� */
#define AMHW_CAN_INT_TYPE_WUI			0X0010  /**< \brief �����ж�     */
#define AMHW_CAN_INT_TYPE_EPI			0X0020  /**< \brief ���������ж� */
#define AMHW_CAN_INT_TYPE_ALI			0X0040  /**< \brief �ٲö�ʧ�ж� */
#define AMHW_CAN_INT_TYPE_BEI			0X0080  /**< \brief ���ߴ����ж� */
#define AMHW_CAN_INT_TYPE_IDI			0X0100  /**< \brief ID�����ж� */
#define AMHW_CAN_INT_TYPE_TI2			0X0200  /**< \brief �����ж�2  */
#define AMHW_CAN_INT_TYPE_TI3			0X0400  /**< \brief �����ж�3  */
#define AMHW_CAN_INT_TYPE_ALL           0X04FF  /**< \brief �����ж�  */

/** @} */

/**
 * \brief CAN ʹ���ж�
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] int_mask : �ж�����  ���ò������μ�
 *                       \ref grp_amhw_can_int_type "interrupt type"
 *
 * \return 		��
 * \note        ��
 */
am_static_inline
void amhw_can_int_enable (amhw_can_t *p_hw_can, amhw_can_int_type_t int_mask)
{
	p_hw_can->ier |= int_mask;
}

/**
 * \brief CANʧ���ж�
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] int_mask : �ж�����  ���ò������μ�
 *                       \ref grp_amhw_can_int_type "interrupt type"
 *
 * \return 		��
 */
am_static_inline
void amhw_can_int_disable (amhw_can_t *p_hw_can, amhw_can_int_type_t int_mask)
{
	p_hw_can->ier &= ~int_mask;
}


/**
 * \name ʱ��Ĵ�����λ����
 * \anchor grp_amhw_can_btr
 * @{
 */
 
#define AMHW_CAN_BTR_BRP			0           /**< \brief ������Ԥ��Ƶ */
#define AMHW_CAN_BTR_RVS4			10			/**< \brief ����  */
#define AMHW_CAN_BTR_SJW			14			/**< \brief ͬ����ת��� */
#define AMHW_CAN_BTR_TESG1		    16			/**< \brief ָ��ͬ�������õ����ʱ */
#define AMHW_CAN_BTR_TESG2		    20			/**< \brief �����㵽�¸�ָ��ͬ�������ʱ */
#define AMHW_CAN_BTR_SAM			23			/**< \brief ���� */

/** @} */

/**
 * \brief CAN �������������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_baudrate_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->btr &= ~0x7fffff;		/* ��reserved0-22λ������ */
}

/**
 * \brief CAN ������Ԥ��Ƶ����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] brp      : Ԥ��Ƶ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_brp_set (amhw_can_t *p_hw_can, uint8_t brp)
{
	p_hw_can->btr |= ((brp & 0X3ff) << AMHW_CAN_BTR_BRP);
}

/**
 * \brief CAN ������Ԥ��Ƶ����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return 		��
 */
am_static_inline
void amhw_can_brp_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->btr &= ~(0x3ff << AMHW_CAN_BTR_BRP);
}


/**
 * \brief CAN ������ͬ����ת�������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] sjw      : ͬ����ת���
 *
 * \return ��
 */
am_static_inline
void amhw_can_sjw_set (amhw_can_t *p_hw_can, uint8_t sjw)
{
	p_hw_can->btr |= ((sjw & 0x03) << AMHW_CAN_BTR_SJW);
}


/**
 * \brief CAN ������ͬ����ת�������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_sjw_clr (amhw_can_t *p_hw_can)
{
    p_hw_can->btr &= ~(0X3 << AMHW_CAN_BTR_SJW);
}


/**
 * \brief CAN ������ͬ������������ʱ����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] tesg     : ͬ������������ʱ
 *
 * \return ��
 */
am_static_inline
void amhw_can_tesg1_set (amhw_can_t *p_hw_can, uint8_t tesg)
{
	p_hw_can->btr |= ((tesg & 0x0f) << AMHW_CAN_BTR_TESG1);
}


/**
 * \brief CAN ������ͬ������������ʱ����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_tesg1_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->btr &= ~(0x0f << AMHW_CAN_BTR_TESG1);
}


/**
 * \brief CAN �����ʲ����㵽ͬ����ʱ����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] tesg     : �����㵽ͬ����ʱ
 *
 * \return ��
 */
am_static_inline
void amhw_can_tesg2_set (amhw_can_t *p_hw_can, uint8_t tesg)
{
	p_hw_can->btr |= ((tesg & 0x07) << AMHW_CAN_BTR_TESG2);
}


/**
 * \brief CAN �����ʲ����㵽ͬ����ʱ���
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return 		��
 */
am_static_inline
void amhw_can_tesg2_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->btr &= ~(0x07 << AMHW_CAN_BTR_TESG2);
}

/**
 * \brief CAN �������߱���������Ϊ3��
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_sam_set (amhw_can_t *p_hw_can)
{
    p_hw_can->btr |= (0x01 << AMHW_CAN_BTR_SAM);
}


/**
 * \brief CAN �������߱���������Ϊ1��
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_can_sam_clr (amhw_can_t *p_hw_can)
{
    p_hw_can->btr &= ~(0X01 << AMHW_CAN_BTR_SAM);
}

/**
 * \brief CAN ������Ԥ��Ƶ��ȡ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return Ԥ��Ƶֵ
 */
am_static_inline
uint16_t amhw_can_brp_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_BRP) & 0X3ff);
}

/**
 * \brief CAN ������ͬ����ת��Ȼ�ȡ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ͬ����ת���ֵ
 */
am_static_inline
uint8_t amhw_can_sjw_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_SJW) & 0x03);
}

/**
 * \brief CAN ������ͬ������������ʱ��ȡ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ͬ������������ʱֵ
 */
am_static_inline
uint8_t amhw_can_tesg1_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_TESG1) & 0x0f);
}


/**
 * \brief CAN �����ʲ����㵽ͬ����ʱ��ȡ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return �����㵽ͬ����ʱ
 */
am_static_inline
uint8_t amhw_can_tesg2_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_TESG2) & 0x07);
}

/**
 * \brief CAN ��ȡ���߱�����������Ϊ���λ���3��
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \retval 0 :���β���
 * \retval 1 :3�β���
 */
am_static_inline
uint8_t amhw_can_sam_get (amhw_can_t *p_hw_can)
{
    return ((p_hw_can->btr >> AMHW_CAN_BTR_SAM) & 0x01);
}

/**
 * \brief CAN ���󱨾�ֵ����
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] warn_val : ���󱨾�ֵ����
 *
 * \return ��
 */
am_static_inline
void amhw_can_ewl_set (amhw_can_t *p_hw_can, uint8_t warn_val)
{
    p_hw_can->ewl = warn_val;
}

/**
 * \brief CAN ״̬�Ĵ���
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ״̬
 */
am_static_inline
uint32_t amhw_can_sr_get (amhw_can_t *p_hw_can)
{
    return p_hw_can->sr;
}

/**
 * \name ȫ��״̬�Ĵ�����λ����
 * \anchor grp_amhw_can_gsr
 * @{
 */
 
#define AMHW_CAN_GSR_RBS			0			/**< \brief ���ջ���״̬ */
#define AMHW_CAN_GSR_DOS			1			/**< \brief ���ݳ���״̬ */
#define AMHW_CAN_GSR_TBS			2			/**< \brief ���ͻ�����״̬ */
#define AMHW_CAN_GSR_TCS			3			/**< \brief ���ͽ���״̬ */
#define AMHW_CAN_GSR_RS				4			/**< \brief ����״̬ */
#define AMHW_CAN_GSR_TS				5			/**< \brief ����״̬ */
#define AMHW_CAN_GSR_ES				6			/**< \brief ����״̬ */
#define AMHW_CAN_GSR_BS				7			/**< \brief ����״̬ */
#define AMHW_CAN_GSR_RVS8			8			/**< \brief ���� */
#define AMHW_CAN_GSR_RXERR		    16		    /**< \brief Rx����������ĵ�ǰֵ */
#define AMHW_CAN_GSR_TXERR		    24		    /**< \brief Tx����������ĵ�ǰֵ */

/** @} */

/**
 * \brief CAN��ȡ����״̬ �Ƿ񾯸�
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \retval 0 ��������
 * \retval 1 ���߾���
 */
am_static_inline
uint8_t amhw_can_buswarn_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->gsr >> AMHW_CAN_GSR_ES) & 0x01);
}

/**
 * \brief CAN��ȡ����״̬ �Ƿ�ر�
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \retval 0 ��������
 * \retval 1 ���߹ر�
 */
am_static_inline
uint8_t amhw_can_busstatus_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->gsr >> AMHW_CAN_GSR_BS) & 0x01);
}


/**
 * \brief CAN��ȡRX�������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return RX�������
 */
am_static_inline
uint8_t amhw_can_rxerrcnt_get (amhw_can_t *p_hw_can)
{
	return (((p_hw_can->gsr) & 0xff0000) >> AMHW_CAN_GSR_RXERR);
}


/**
 * \brief CAN��ȡTX�������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return TX���������ָ��
 */
am_static_inline
uint8_t amhw_can_txerrcnt_get (amhw_can_t *p_hw_can)
{
	return (((p_hw_can->gsr) & 0xff000000) >> AMHW_CAN_GSR_TXERR);
}

/**
 * \brief 		CAN����������
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return 		��
 */
am_static_inline
void amhw_can_errcnt_clr (amhw_can_t *p_hw_can)
{
	p_hw_can->gsr &= ~0xffff0000;
}

/**
 * \name ����֡״̬�Ĵ�����λ����
 * \anchor grp_amhw_can_rfs
 * @{
 */
 
#define AMHW_CAN_RFS_ID					0       /**< \brief ID�����ֶ�Ԫ */
#define AMHW_CAN_RFS_BP					10		/**< \brief ��·ģʽ�н��յı��� */
#define AMHW_CAN_RFS_RVS5				11		/**< \brief ���� */
#define AMHW_CAN_RFS_DLC				16		/**< \brief ���յ��ı��ĵ����ݳ��ȴ��� */
#define AMHW_CAN_RFS_RVS10		    	20		/**< \brief ���� */
#define AMHW_CAN_RFS_RTR				30		/**< \brief ���յ��ı��ĵ�Զ�̴�������λ */
#define AMHW_CAN_RFS_FF					31		/**< \brief ���յ��ı��İ���11λ�ı�ʶ�� */

/** @} */

/**
 * \brief CAN ��ȡ���ݳ���
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ���ݳ���
 */
am_static_inline 
uint8_t amhw_can_datalen_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rfs >> AMHW_CAN_RFS_DLC) & 0x0ff);
}

/**
 * \brief CAN ��ȡ��������Զ��֡��״̬
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \retval 1 ΪԶ��֡
 * \retval 0 Ϊ����֡
 */
am_static_inline 
uint8_t amhw_can_remoteflag_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rfs >> AMHW_CAN_RFS_RTR) & 0x01);
}

/**
 * \brief CAN ��ȡ����������չ֡��״̬
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \retval 1 Ϊ��չ֡
 * \retval 0 Ϊ��׼֡
 */
am_static_inline 
uint8_t amhw_can_externflag_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rfs >> AMHW_CAN_RFS_FF) & 0x01);
}


/**
 * \brief CAN ��ȡ����������չ֡��ID��
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ID
 */
am_static_inline 
uint32_t amhw_can_externid_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rid) & 0x1fffffff);
}

/**
 * \brief CAN ��ȡ�������ݱ�׼֡��ID��
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ID
 */
am_static_inline 
uint8_t amhw_can_standid_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->rid) & 0x7ff);
}

	
/**
 * \brief CAN ��ȡ���ջ����״̬
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \retval 1 Ϊ����
 * \retval 0 ����
 */
am_static_inline 
uint8_t amhw_can_rvbuf_status_get (amhw_can_t *p_hw_can)
{
	return ((p_hw_can->gsr >> AMHW_CAN_GSR_DOS) & 0x01);
}


/**
 * \brief CAN�ͷŽ��ջ���
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_rvbuff_release_set (amhw_can_t *p_hw_can)
{
    p_hw_can->cmr |= (0x01 << AMHW_CAN_CMR_RRB);
}


/**
 * \name ����֡��Ϣ�Ĵ�����λ����
 * \anchor grp_amhw_can_tfi
 * @{
 */
 
#define AMHW_CAN_TFI_PRIO				0       /**< \brief �������ȼ� */
#define AMHW_CAN_TFI_RVS8				8       /**< \brief ���� */
#define AMHW_CAN_TFI_DLC				16		/**< \brief �������ݳ��ȴ��� */
#define AMHW_CAN_TFI_RVS10			    20		/**< \brief ���� */
#define AMHW_CAN_TFI_RTR				30		/**< \brief Զ��֡��־ */
#define AMHW_CAN_TFI_FF					31		/**< \brief ��չ֡��־ */

#define AMDR_CAN_TXBUF_CHN              0X01    /**< \brief CAN ���ͻ����ͨ���� 1-3*/
#define AMDR_CAN_TXBUF_PRIO             0X01    /**< \brief CAN ���ͻ�������ȼ� */

/** @} */

/**
 * \brief CAN ���TFI�Ĵ���
 *
 * \param[in] p_hw_can  : ָ��CAN�Ĵ������ָ��
 * \param[in] chn       : ָ��tfi����һͨ�� 1-3ͨ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_txinfo_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi = ~0xc00f00ff;
}

/**
 * \brief CAN ����TFI�����ȼ�
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] chn 		 : ָ��tfi����һͨ�� 1-3ͨ��
 * \param[in] prio		 : ���ȼ�
 *
 * \return ��
 */
am_static_inline 
void amhw_can_transprio_set (amhw_can_t *p_hw_can, uint8_t chn, uint8_t prio)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi |= prio << AMHW_CAN_TFI_PRIO;
}


/**
 * \brief CAN ��� TFI�����ȼ�
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] chn 		 : ָ��tfi����һͨ�� 1-3ͨ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_transprio_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi &= ~(0xff << AMHW_CAN_TFI_PRIO);
}


/**
 * \brief CAN ����TFI�����ݳ���
 *
 * \param[in] p_hw_can  : ָ��CAN�Ĵ������ָ��
 * \param[in] chn       : ָ��tfi����һͨ�� 1-3ͨ��
 * \param[in] len       : ����
 *
 * \return ��
 */
am_static_inline 
void amhw_can_datalen_set (amhw_can_t *p_hw_can, uint8_t chn, uint8_t len)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi |= len << AMHW_CAN_TFI_DLC;
}

/**
 * \brief CAN ���TFI�����ݳ���
 *
 * \param[in] p_hw_can  : ָ��CAN�Ĵ������ָ��
 * \param[in] chn       : ָ��tfi����һͨ�� 1-3ͨ��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_datalen_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi &= ~(0x0f << AMHW_CAN_TFI_DLC);
}


/**
 * \brief CAN ����TFIԶ��֡
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] chn        : ָ��tfi����һͨ�� 1-3ͨ��
 * \param[in] remoteflag : Զ��֡��־λ
 *
 * \return ��
 */
am_static_inline 
void amhw_can_remoteflag_set (amhw_can_t *p_hw_can, uint8_t chn, uint8_t remoteflag)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi |= remoteflag << AMHW_CAN_TFI_RTR;
}


/**
 * \brief CAN ���TFIԶ��֡
 *
 * \param[in] p_hw_can   : ָ��CAN�Ĵ������ָ��
 * \param[in] chn        : ָ��tfi����һͨ�� 1-3ͨ��
 *
 * \return ��
 * \note  ��
 */
am_static_inline 
void amhw_can_remoteflag_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi &= ~(0x01 << AMHW_CAN_TFI_RTR);
}


/**
 * \brief  CAN ����TFI��չ֡
 *
 * \param[in] p_hw_can 	 : ָ��CAN�Ĵ������ָ��
 * \param[in] chn        : ָ��tfi����һͨ�� 1-3ͨ��
 * \param[in] externflag : ��չ֡��־λ
 *
 * \return ��
 */
am_static_inline 
void amhw_can_externflag_set (amhw_can_t *p_hw_can, uint8_t chn, uint8_t externflag)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi |= externflag << AMHW_CAN_TFI_FF;
}


/**
 * \brief CAN ���TFI��չ֡
 *
 * \param[in] p_hw_can 	 : ָ��CAN�Ĵ������ָ��
 * \param[in] chn        : ָ��tfi����һͨ�� 1-3ͨ��
 *
 * \return 		��
 */
am_static_inline 
void amhw_can_externflag_clr (amhw_can_t *p_hw_can, uint8_t chn)
{
    uint32_t *tfi = (uint32_t *)&p_hw_can->tfi1 + 4*(chn - 1);
    *tfi &= ~((uint32_t)0x80000000);
}

/**
 * \brief CAN ����TID ID��
 *
 * \param[in] p_hw_can  : ָ��CAN�Ĵ������ָ��
 * \param[in] chn       : ָ��tfi����һͨ�� 1-3ͨ��
 * \param[in] id	    : id��
 *
 * \return ��
 */
am_static_inline 
void amhw_can_id_set (amhw_can_t *p_hw_can, uint8_t chn, uint32_t id)
{
    uint32_t *tid = (uint32_t *)&p_hw_can->tid1 + 4*(chn - 1);
    *tid = id;
}


/**
 * \brief CAN ����TDA
 *
 * \param[in] p_hw_can  : ָ��CAN�Ĵ������ָ��
 * \param[in] chn       : ָ��tfi����һͨ�� 1-3ͨ��
 * \param[in] data	    : ����
 *
 * \return ��
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
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 * \param[in] chn      : ָ��tfi����һͨ�� 1-3ͨ��
 * \param[in] data	   : ����
 *
 * \return  ��
 */
am_static_inline 
void amhw_can_txdatab_set (amhw_can_t *p_hw_can, uint8_t chn, uint32_t data)
{
    uint32_t *tdb = (uint32_t *)&p_hw_can->tdb1 + 4*(chn - 1);
    *tdb = data;
}
	
/**
 * \name CAN�жϺͲ���Ĵ�����λ����
 * \anchor grp_amhw_can_icr
 * @{
 */

#define AMHW_CAN_ICR_RI					0				/**< \brief �����ж� */
#define AMHW_CAN_ICR_TI1				1				/**< \brief �����ж�1 */
#define AMHW_CAN_ICR_EI					2				/**< \brief ���󱨾��ж� */
#define AMHW_CAN_ICR_DOI				3				/**< \brief ���ݳ����ж� */
#define AMHW_CAN_ICR_WUI				4				/**< \brief �����ж� */
#define AMHW_CAN_ICR_EPI				5				/**< \brief ���󱻶��ж� */
#define AMHW_CAN_ICR_ALI				6				/**< \brief �ٲö�ʧ�ж� */
#define AMHW_CAN_ICR_BEI				7				/**< \brief ���ߴ����ж� */
#define AMHW_CAN_ICR_IDI				8				/**< \brief ID�����ж� */
#define AMHW_CAN_ICR_TI2				9				/**< \brief �����ж�2 */
#define AMHW_CAN_ICR_TI3				10			    /**< \brief �����ж�3 */
#define AMHW_CAN_ICR_RVS5				11			    /**< \brief ���� */
#define AMHW_CAN_ICR_ERRBIT			    16			    /**< \brief ������벶�� */
#define AMHW_CAN_ICR_ERRDIR			    21			    /**< \brief ���򲶻� */
#define AMHW_CAN_ICR_ERRC1			    22			    /**< \brief ���ߴ��󲶻� */
#define AMHW_CAN_ICR_ALCBIT			    24			    /**< \brief �ٲò��� */

/** @} */

/**
 * \name CAN BUS�������
 * \anchor grp_amhw_can_err_code
 * @{
 */

typedef uint32_t amhw_can_err_code_t;                   /**< \brief ���ߴ������   */
#define AMHW_CAN_ERR_CODE_FRAME     			0x03	/**< \brief ֡��ʼ                 */
#define AMHW_CAN_ERR_CODE_ID28_21     			0x02	/**< \brief ID28��ID21   */
#define AMHW_CAN_ERR_CODE_ID20_18     			0x06	/**< \brief ID20��ID18   */
#define AMHW_CAN_ERR_CODE_START     			0x04	/**< \brief ��ʼλ                 */
#define AMHW_CAN_ERR_CODE_IDE     			    0x05	/**< \brief IDEλ                   */
#define AMHW_CAN_ERR_CODE_ID17_13     			0x07	/**< \brief ID17��ID13   */
#define AMHW_CAN_ERR_CODE_ID12_5     			0x0F	/**< \brief ID12��ID5    */
#define AMHW_CAN_ERR_CODE_ID4_0     			0x0E	/**< \brief ID4��ID0     */
#define AMHW_CAN_ERR_CODE_RTR     			    0x0C	/**< \brief RTRλ                   */
#define AMHW_CAN_ERR_CODE_RSV1     			    0x0D	/**< \brief ����λ1     */
#define AMHW_CAN_ERR_CODE_RSV0     			    0x09	/**< \brief ����λ0     */
#define AMHW_CAN_ERR_CODE_LEN     			    0x0B	/**< \brief ���ݳ��ȴ���  */
#define AMHW_CAN_ERR_CODE_FIELD     			0x0A	/**< \brief �����ֶ�            */
#define AMHW_CAN_ERR_CODE_CRC     			    0x08	/**< \brief CRC����             */
#define AMHW_CAN_ERR_CODE_CRC_SEP     			0x18	/**< \brief CRC�ָ�����   */
#define AMHW_CAN_ERR_CODE_SLOT     			    0x19	/**< \brief Ӧ��slot    */
#define AMHW_CAN_ERR_CODE_SEP     			    0x1B	/**< \brief Ӧ��ָ����� */
#define AMHW_CAN_ERR_CODE_END     			    0x1A	/**< \brief ֡����                */
#define AMHW_CAN_ERR_CODE_PAUSE     			0x12	/**< \brief ��ͣ                     */
#define AMHW_CAN_ERR_CODE_STAERR     			0x11	/**< \brief ���������־   */
#define AMHW_CAN_ERR_CODE_ACCERR     			0x16	/**< \brief �Ͽɴ����־   */
#define AMHW_CAN_ERR_CODE_ALWERR     			0x13	/**< \brief ���������λ   */
#define AMHW_CAN_ERR_CODE_ERRSEP     			0x17	/**< \brief ����ָ�����   */
#define AMHW_CAN_ERR_CODE_OUTDATA     			0x1C	/**< \brief ���ر�־             */

/** @} */

/**
 * \brief CAN��ȡ���ߴ������
 *
 * \param[in] icr_val : ICR�Ĵ�����ֵ
 *
 * \return CAN BUS������룬�μ� \ref grp_amhw_can_err_code  "can bus error code"
 */
am_static_inline
amhw_can_err_code_t amhw_can_error_code_get (uint32_t icr_val)
{
	return ((icr_val >> AMHW_CAN_ICR_ERRBIT) & 0x01f);
}

/**
 * \name CAN BUS������
 * \anchor grp_amhw_can_err_dir
 * @{
 */

typedef uint32_t amhw_can_err_dir_t;                    /**< \brief ���ߴ�����   */
#define AMHW_CAN_BUS_ERR_DIR_TX     			0x00	/**< \brief ���ʹ���   */
#define AMHW_CAN_BUS_ERR_DIR_RX      			0x01	/**< \brief ���մ��� */

/** @} */

/**
 * \brief CAN��ȡ���ߴ���ķ���λ
 *
 * \param[in] icr_val : ICR�Ĵ�����ֵ
 *
 * \return CAN BUS�����򣬲μ� \ref grp_amhw_can_err_dir  "can bus error dir"
 */
am_static_inline
amhw_can_err_dir_t amhw_can_error_dir_get (uint32_t icr_val)
{
	return ((icr_val >> AMHW_CAN_ICR_ERRDIR) & 0x01);
}

/**
 * \name CAN BUS�������
 * \anchor grp_amhw_can_bus_err
 * @{
 */
 
typedef uint32_t amhw_can_bus_err_t;                    /**< \brief ���ߴ�������   */
#define AMHW_CAN_BUS_ERR_BIT     			0x00	    /**< \brief λ����   */
#define AMHW_CAN_BUS_ERR_FORM    			0x01	    /**< \brief ��ʽ���� */
#define AMHW_CAN_BUS_ERR_STUFF  	 		0x10	    /**< \brief ������ */
#define AMHW_CAN_BUS_ERR_UNKNOWN 			0x11	    /**< \brief δ֪���� */

/** @} */

/**
 * \brief CAN��ȡbus error����
 *
 * \param[in] icr_val : ICR�Ĵ�����ֵ
 *
 * \return CAN BUS�������ͣ��μ� \ref grp_amhw_can_bus_err  "can bus error"
 */
am_static_inline
amhw_can_bus_err_t amhw_can_bus_error_get (uint32_t icr_val)
{
	return ((icr_val >> AMHW_CAN_ICR_ERRC1) & 0x03);
}

/**
 * \name CAN �ٲö�ʧ��������
 * \anchor grp_amhw_can_err_alc
 * @{
 */

typedef uint32_t amhw_can_err_alc_t;                    /**< \brief ���ߴ����ٲö�ʧ����   */
#define AMHW_CAN_BUS_ERR_ALC_FIRST    			0x00	/**< \brief �ٲ��ڱ�ʶ���ĵ�һλ��MS����ʧ   */
#define AMHW_CAN_BUS_ERR_ALC_SRTS    			0x0B	/**< \brief �ٲ���SRTSλ��ʧ   */
#define AMHW_CAN_BUS_ERR_ALC_IDE    			0x0C	/**< \brief �ٲ���IDEλ��ʧ   */
#define AMHW_CAN_BUS_ERR_ALC_12TH    			0x0D	/**< \brief �ٲ��ڱ�ʶ���ĵ�12λ��ʧ   */
#define AMHW_CAN_BUS_ERR_ALC_LAST    			0x1E	/**< \brief �ٲ��ڱ�ʶ�������һλ��ʧ   */
#define AMHW_CAN_BUS_ERR_ALC_RTR    			0x1F	/**< \brief �ٲ���RTRλ��ʧ   */

/** @} */

/**
 * \brief CAN��ȡ�ٲö�ʧ��������
 *
 * \param[in] icr_val : ICR�Ĵ�����ֵ
 *
 * \return CAN ȡ�ٲö�ʧ�������ͣ��б����޶������Ƕ�Ӧλ��ʧ
 *         �μ� \ref amhw_can_err_alc_t  "can alc error kind"
 */
am_static_inline
amhw_can_err_alc_t amhw_can_error_alc_get (uint32_t icr_val)
{
	return ((icr_val >> AMHW_CAN_ICR_ALCBIT) & 0xff);
}

/**
 * \brief CAN��ȡ�ж�����
 *
 * \param[in] icr_val : ICR�Ĵ�����ֵ
 *
 * \return  �ж����ͣ��μ� \ref grp_amhw_can_int_type "interrupt type"
 */
am_static_inline
amhw_can_int_type_t amhw_can_intstatus_get (uint32_t icr_val)
{
	return (icr_val & 0x07ff);
}

/**
 * \brief CAN��ȡICR����״̬�Ĵ�����ֵ
 *
 * \param[in] p_hw_can : ָ��CAN�Ĵ������ָ��
 *
 * \return  ICR����״̬�Ĵ�����ֵ
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

