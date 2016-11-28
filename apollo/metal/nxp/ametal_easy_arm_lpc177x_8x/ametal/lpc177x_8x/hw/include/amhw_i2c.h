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
 * \brief I2C Ӳ�������ӿ�
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
 * \brief I2C �Ĵ�����ṹ��
 */
typedef struct amhw_i2c {
    __IO uint32_t  conset;           /**< \brief I2C ������λ�Ĵ���       */
    __I  uint32_t  stat;             /**< \brief I2C ״̬�Ĵ���           */
    __IO uint32_t  dat;              /**< \brief I2C ���ݼĴ���           */
    __IO uint32_t  adr0;             /**< \brief I2C �ӵ�ַ�Ĵ���0        */
    __IO uint32_t  sclh;             /**< \brief I2C SCLռ�ձȼĴ����߰��� */
    __IO uint32_t  scll;             /**< \brief I2C SCLռ�ձȼĴ����Ͱ��� */
    __O  uint32_t  conclr;           /**< \brief I2C ��������Ĵ���        */
    __O  uint32_t  mmctrl;           /**< \brief I2C ���ģʽ���ƼĴ���    */
	__IO uint32_t  adr1;             /**< \brief I2C �ӵ�ַ�Ĵ���1         */
    __IO uint32_t  adr2;             /**< \brief I2C �ӵ�ַ�Ĵ���2         */
    __IO uint32_t  adr3;             /**< \brief I2C �ӵ�ַ�Ĵ���3         */
    __I  uint32_t  data_buffer;      /**< \brief I2C ���ݻ���Ĵ���        */
    __IO uint32_t  mask0;            /**< \brief I2C �ӵ�ַ���μĴ���0     */
    __IO uint32_t  mask1;            /**< \brief I2C �ӵ�ַ���μĴ���1     */
    __IO uint32_t  mask2;            /**< \brief I2C �ӵ�ַ���μĴ���2     */
    __IO uint32_t  mask3;            /**< \brief I2C �ӵ�ַ���μĴ���3     */
} amhw_i2c_t;



/**
 * \name I2C ������λ�Ĵ�������λ��ϸ����
 * \anchor grp_amhw_i2c_conset_bit
 * @{
 */

#define AMHW_I2C_I2CONSET_AA			((0x04)) /**< \brief  Ӧ���־ */
#define AMHW_I2C_I2CONSET_SI			((0x08)) /**< \brief  �жϱ�־ */
#define AMHW_I2C_I2CONSET_STO			((0x10)) /**< \brief  ������־ */
#define AMHW_I2C_I2CONSET_STA			((0x20)) /**< \brief  ��ʼ��־ */
#define AMHW_I2C_I2CONSET_I2EN			((0x40)) /**< \brief  ʹ�ܱ�־ */

/** @} */

/**
 * \name I2C ��������Ĵ�������λ��ϸ����
 * \anchor grp_amhw_i2c_conclr_bit
 * @{
 */

#define AMHW_I2C_I2CONCLR_AAC			((1<<2)) /**< \brief Ӧ���־ */
#define AMHW_I2C_I2CONCLR_SIC			((1<<3)) /**< \brief �жϱ�־ */
#define AMHW_I2C_I2CONCLR_STAC			((1<<5)) /**< \brief ��ʼ��־ */
#define AMHW_I2C_I2CONCLR_I2ENC			((1<<6)) /**< \brief ʹ�ܱ�־ */

/** @} */

/**
 * \name I2C ���ݼĴ���λ����
 * @{
 */ 

/** \brief I2C���ݼĴ������� */
#define AMHW_I2C_I2DAT_BITMASK			((0xFF))

/** \brief ��������ֵ */
#define AMHW_I2C_I2DAT_IDLE_CHAR		(0xFF)

/** @} */

/**
 * \name I2C ���ģʽ���ƼĴ���λ����
 * @{
 */ 
 
#define AMHW_I2C_I2MMCTRL_MM_ENA		((1<<0))		/**< \brief ���ģʽʹ��       */
#define AMHW_I2C_I2MMCTRL_ENA_SCL		((1<<1))		/**< \brief ʱ�����ʹ��       */
#define AMHW_I2C_I2MMCTRL_MATCH_ALL		((1<<2))		/**< \brief ѡ���жϼĴ���ƥ�� */
#define AMHW_I2C_I2MMCTRL_BITMASK		((0x07))		/**< \brief I2MMCTRL�Ĵ������� */

/** @} */

/**
 * \name I2C ���ݻ���Ĵ���λ����
 * @{
 */ 

/** \brief ���ݻ������� */
#define AMHW_I2DATA_BUFFER_BITMASK		((0xFF))

/** @} */

/**
 * \name I2C ״̬�Ĵ����궨��
 * @{
 */

#define AMHW_I2C_STAT_CODE_BITMASK		((0xF8)) /**< \brief ״̬�Ĵ������� */

#define AMHW_I2C_I2STAT_NO_INF			((0xF8)) /**< \brief �޹���Ϣ       */

/** @} */

/**
 * \name I2C ״̬�Ĵ���ֵ����
 * @{
 */

#define AMHW_I2C_SETUP_STATUS_ARBF   (1<<8)	  /**< \brief �ٲô���    */
#define AMHW_I2C_SETUP_STATUS_NOACKF (1<<9)	  /**< \brief ��Ӧ�𷵻�  */
#define AMHW_I2C_SETUP_STATUS_DONE   (1<<10)  /**< \brief ���״̬    */

/** @} */

/**
 * \name I2C ������ģʽ����
 * @{
 */
/** \brief ��ʼ�����ѷ���          */
#define AMHW_I2C_I2STAT_M_TX_START					((0x08))
/** \brief �ظ���ʼ�����ѷ���      */
#define AMHW_I2C_I2STAT_M_TX_RESTART				((0x10))
/** \brief SLA+W�ѷ��ͣ�ACK�ѽ���  */
#define AMHW_I2C_I2STAT_M_TX_SLAW_ACK				((0x18))
/** \brief SLA+W�ѷ��ͣ�NACK�ѽ��� */
#define AMHW_I2C_I2STAT_M_TX_SLAW_NACK				((0x20))
/** \brief �����ѷ��ͣ�ACK�ѽ���   */
#define AMHW_I2C_I2STAT_M_TX_DAT_ACK				((0x28))
/** \brief �����ѷ��ͣ�NACK�ѽ���  */
#define AMHW_I2C_I2STAT_M_TX_DAT_NACK				((0x30))
/** \brief �ٲö�ʧ   */
#define AMHW_I2C_I2STAT_M_TX_ARB_LOST				((0x38))

/** @} */


/**
 * \name I2C ������ģʽ����
 * @{
 */
/** \brief ��ʼ�����ѷ���    */
#define AMHW_I2C_I2STAT_M_RX_START					((0x08))
/** \brief �ظ���ʼ�����ѷ���      */
#define AMHW_I2C_I2STAT_M_RX_RESTART				((0x10))
/** \brief �ٲö�ʧ */
#define AMHW_I2C_I2STAT_M_RX_ARB_LOST				((0x38))
/** \brief SLA+R�ѷ��ͣ�ACK�ѽ���  */
#define AMHW_I2C_I2STAT_M_RX_SLAR_ACK				((0x40))
/** \brief SLA+R�ѷ��ͣ�NACK�ѽ��� */
#define AMHW_I2C_I2STAT_M_RX_SLAR_NACK				((0x48))
/** \brief �����ѽ��գ�ACK�ѷ���   */
#define AMHW_I2C_I2STAT_M_RX_DAT_ACK				((0x50))
/** \brief �����ѽ��գ�NACK�ѷ���   */
#define AMHW_I2C_I2STAT_M_RX_DAT_NACK				((0x58)) 

/** @} */

/**
 * \name I2C �ӽ���ģʽ����
 * @{
 */
/** \brief �ӻ���ַ�ѽ��գ�Ӧ���ѷ���    */
#define AMHW_I2C_I2STAT_S_RX_SLAW_ACK				((0x60))

/** \brief �ٲö�ʧ */
#define AMHW_I2C_I2STAT_S_RX_ARB_LOST_M_SLA			((0x68))

/** \brief ͨ�õ��õ�ַ�ѽ��գ�Ӧ���ѷ��� */
#define AMHW_I2C_I2STAT_S_RX_GENCALL_ACK			((0x70))

/** \brief �ٲö�ʧ  */
#define AMHW_I2C_I2STAT_S_RX_ARB_LOST_M_GENCALL		((0x78))

/** \brief �ӻ�ģʽ�������ѽ��գ�Ӧ���ѷ���    */
#define AMHW_I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK		((0x80))
/** \brief �ӻ�ģʽ�������ѽ��գ���Ӧ���ѷ���  */
#define AMHW_I2C_I2STAT_S_RX_PRE_SLA_DAT_NACK		((0x88))
/** \brief ͨ�õ��������ѽ��գ�Ӧ���ѷ���      */
#define AMHW_I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK	((0x90))
/** \brief ͨ�õ��������ѽ��գ���Ӧ���ѷ���    */
#define AMHW_I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK	((0x98))
/** \brief ֹͣ����/�ظ���ʼ�����ѽ���         */
#define AMHW_I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX	((0xA0))

/** @} */

/**
 * \name I2C �ӷ���ģʽ����
 * @{
 */

/** \brief SLA+R�ѽ��գ�Ӧ���ѷ���  */
#define AMHW_I2C_I2STAT_S_TX_SLAR_ACK				((0xA8))

/** \brief �ٲö�ʧ */
#define AMHW_I2C_I2STAT_S_TX_ARB_LOST_M_SLA			((0xB0))

/** \brief �����Ѿ�������Ӧ���ѷ���    */
#define AMHW_I2C_I2STAT_S_TX_DAT_ACK				((0xB8))
/** \brief �����Ѿ���������Ӧ���ѷ���  */
#define AMHW_I2C_I2STAT_S_TX_DAT_NACK				((0xC0))
/** \brief ���һ�������Ѿ�������NACK�ѷ���   */
#define AMHW_I2C_I2STAT_S_TX_LAST_DAT_ACK			((0xC8))

/** \brief �ӻ�ģʽ��ʱ  */
#define AMHW_I2C_SLAVE_TIME_OUT						0x10000UL

/** @} */


/**
 * @brief ����ģʽ����
 */
typedef enum {
	I2C_MODE_POLLING = 0,		/**< \brief ��ѯģʽ */
	I2C_MODE_INTERRUPT			/**< \brief �ж�ģʽ */
} i2c_mode_type_t;



/**
 * \brief  ����conset�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \param[in] value    ������ֵ���μ�
 *                      \ref grp_amhw_i2c_conset_bit
 * \return ��
 */
am_static_inline
void amhw_i2c_conset_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->conset = value;
}

/**
 * \brief  ��ȡconset�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \return ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_i2c_conset_val_get (amhw_i2c_t *p_hw_i2c)
{
	return p_hw_i2c->conset;
}

/**
 * \brief  ����conclr�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \param[in] value    ������ֵ���μ�
 *                      \ref grp_amhw_i2c_conclr_bit
 * \return ��
 */
am_static_inline
void amhw_i2c_conclr_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->conclr = value;
}

/**
 * \brief  ����dat�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \param[in] value    ������ֵ
 * \return ��
 */
am_static_inline
void amhw_i2c_dat_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->dat = value;
}

/**
 * \brief  ��ȡdat�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \return ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_i2c_dat_val_get (amhw_i2c_t *p_hw_i2c)
{
	return p_hw_i2c->dat;
}

/**
 * \brief  ��ȡstat�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \return ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_i2c_stat_val_get (amhw_i2c_t *p_hw_i2c)
{
	return p_hw_i2c->stat;
}

/**
 * \brief  ����sclh�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \param[in] value    ������ֵ
 * \return ��
 */
am_static_inline
void amhw_i2c_sclh_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->sclh = value;
}

/**
 * \brief  ��ȡsclh�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \return ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_i2c_sclh_val_get (amhw_i2c_t *p_hw_i2c)
{
	return p_hw_i2c->sclh;
}

/**
 * \brief  ����scll�Ĵ���ֵ
 * \param[in] p_hw_i2c ������ָ��
 * \param[in] value    ������ֵ
 * \return ��
 */
am_static_inline
void amhw_i2c_scll_val_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
	p_hw_i2c->scll = value;
}


/**
 * \brief  ����ʱ��
 * \param[in] p_hw_i2c     : ָ��I2C�Ĵ������ָ��
 * \param[in] target_clock : I2Cʱ��
 *
 * \return ��
 */
void amhw_i2c_setclock (amhw_i2c_t *p_hw_i2c, uint32_t target_clock);

/**
 * \brief  I2C��ʼ��
 * \param[in] p_hw_i2c  : ָ��I2C�Ĵ������ָ��
 * \param[in] clockrate : I2Cʱ��
 *
 * \return ��
 */
void amhw_i2c_init (amhw_i2c_t *p_hw_i2c, uint32_t clockrate);

/**
 * \brief  ��ģʽ����
 * \param[in] p_hw_i2c  : ָ��I2C�Ĵ������ָ��
 *
 * \return ��
 */
void amhw_i2c_master_handler (amhw_i2c_t  *p_hw_i2c);


/**
 * \brief  ��ģʽ�������
 * \param[in] p_hw_i2c  : ָ��I2C�Ĵ������ָ��
 *
 * \return ��
 */
uint32_t amhw_i2c_mastertransfer_ok (amhw_i2c_t *p_hw_i2c);

/**
 * \brief ��ģʽ����
 * \param[in] p_hw_i2c  : ָ��I2C�Ĵ������ָ��
 *
 * \return ��
 */
void amhw_i2c_slave_handler (amhw_i2c_t  *p_hw_i2c);

/**
 * \brief  ��ģʽ�������
 * \param[in] p_hw_i2c  : ָ��I2C�Ĵ������ָ��
 *
 * \return ��
 */
uint32_t amhw_i2c_slave_transfer_ok (amhw_i2c_t *p_hw_i2c);

/**
 * \brief  I2Cʹ��
 * \param[in] p_hw_i2c  : ָ��I2C�Ĵ������ָ��
 * \param[in] state     : ʹ�ܻ�ʹ�ܱ�־
 *
 * \return ��
 */
void amhw_i2c_cmd (amhw_i2c_t* p_hw_i2c, bool_t state);

/**
 * \brief     ��ȡI2C��
 * \param[in] p_hw_i2c : I2C����AMHW_I2C0..2
 * \return    I2C��    : 0..2
 */
int32_t amhw_i2c_getnum (amhw_i2c_t *p_hw_i2c);

/**
 * \brief     i2c�жϺ���
 *
 * \param[in] p_hw_i2c : I2C����AMHW_I2C0..2
 * \param[in] p_trans  : �������
 *
 * \return    AM_OK     : �ɹ�
 * \return    AM_ERROR  : ʧ��
 */
int amhw_i2c_handler (amhw_i2c_t  *p_hw_i2c,am_i2c_transfer_t *p_trans);

/**
 * \brief     i2c�жϴ��亯��
 * \param[in] p_hw_i2c      : I2C����AMHW_I2C0..2
 * \param[in] transfer_cfg  : �������
 *
 * \return    ��
 */
bool_t amhw_i2c_int_transfer (amhw_i2c_t *p_hw_i2c, am_i2c_transfer_t  *transfer_cfg);

/**
 * \brief     ��ģʽ�����շ�
 * \param[in] p_hw_i2c      : I2C����AMHW_I2C0..2
 * \param[in] transfer_cfg  : ���ͽṹ��
 * \param[in] option        : ���ͷ�ʽ
 * \return    �ɹ�����1��ʧ�ܷ���0
 */
bool_t amhw_i2c_master_transfer (amhw_i2c_t         *p_hw_i2c,
		                         am_i2c_transfer_t  *transfer_cfg,
								 i2c_mode_type_t     option);

/**
 * \brief     ��ģʽ�����շ�
 * \param[in] p_hw_i2c      : I2C����AMHW_I2C0..2
 * \param[in] transfer_cfg  : ���ͽṹ��
 * \param[in] option        : ���ͷ�ʽ
 * \return    �ɹ�����1��ʧ�ܷ���0
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
