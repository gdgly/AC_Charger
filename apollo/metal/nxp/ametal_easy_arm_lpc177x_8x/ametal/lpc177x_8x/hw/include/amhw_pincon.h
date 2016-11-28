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
 * \brief �ܽ�����(Pin connect)����
 * 
 * \internal
 * \par Modification History
 * - 1.01 15-08-29  cod, added support Lpc177x_8x
 * - 1.00 15-04-23  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_PINCON_H
#define __AMHW_PINCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
    
 /** 
 * \addtogroup amhw_if_pincon
 * \copydoc amhw_pincon.h
 * @{
 */

/**
  * \brief LPC17xx PIN connect �Ĵ�����ṹ��
 */
typedef struct amhw_pincon {
    __IO uint32_t iocon[5][32];   /**< \brief �ܽ����üĴ���                        */
} amhw_pincon_t;

/**
 * \name IOCON�Ĵ���λƫ�ƺ�����
 * @{
 */

#define AMHW_PINCON_FUNC_POS     0  /**< \brief IOCON�Ĵ�������λƫ��ֵ   */
#define AMHW_PINCON_MODE_POS     3  /**< \brief IOCON�Ĵ���ģʽλƫ��ֵ   */
#define AMHW_PINCON_HYS_POS      5  /**< \brief IOCON�Ĵ�������λƫ��ֵ   */
#define AMHW_PINCON_INVERT_POS   6  /**< \brief IOCON�Ĵ������뼫��λƫ��ֵ   */
#define AMHW_PINCON_ADMODE_POS   7  /**< \brief IOCON�Ĵ���ADģʽλƫ��ֵ   */
#define AMHW_PINCON_FILTER_POS   8  /**< \brief IOCON�Ĵ���FILTERλƫ��ֵ   */
#define AMHW_PINCON_HS_POS       8  /**< \brief IOCON�Ĵ���HSλƫ��ֵ   */
#define AMHW_PINCON_SLEW_POS     9  /**< \brief IOCON�Ĵ���SLEWλƫ��ֵ   */
#define AMHW_PINCON_HIDRIVE_POS  9  /**< \brief IOCON�Ĵ���HIDRIVEλƫ��ֵ   */
#define AMHW_PINCON_OD_POS       10 /**< \brief IOCON�Ĵ�����©ģʽλƫ��ֵ   */
#define AMHW_PINCON_DACEN_POS    16 /**< \brief IOCON�Ĵ���DACʹ��λƫ��ֵ   */

#define AMHW_PINCON_FUNC_MASK   (0x07 << 0)   /**< \brief IOCON����λ����   */
#define AMHW_PINCON_MODE_MASK   (0x03 << 3)   /**< \brief IOCONģʽλ����   */

/** @} */

/**
 * \name �ܽŹ��ܶ���
 * @{
 */
#define AMHW_PINCON_SEL_FUNC0    0    /**< \brief ����0��ͨ��ΪGPIO       */
#define AMHW_PINCON_SEL_FUNC1    1    /**< \brief ���ù���1               */
#define AMHW_PINCON_SEL_FUNC2    2    /**< \brief ���ù���2               */
#define AMHW_PINCON_SEL_FUNC3    3    /**< \brief ���ù���3               */
#define AMHW_PINCON_SEL_FUNC4    4    /**< \brief ���ù���4               */
#define AMHW_PINCON_SEL_FUNC5    5    /**< \brief ���ù���5               */
#define AMHW_PINCON_SEL_FUNC6    6    /**< \brief ���ù���6               */
#define AMHW_PINCON_SEL_FUNC7    7    /**< \brief ���ù���7               */

/** @} */

/**
 * \brief Pin connect��������(�����ܽŵĹ���)
 *
 * \param[in] p_hw_pincon : ָ��PINCON�Ĵ������ָ��
 * \param[in] port        : �˿ں�   ��0 ~ 4,��ΪLPC177X_8X,�˿ںţ�0~5
 * \param[in] pin_num     : ���ű�� : 0 ~ 31,,��ΪLPC177X_8X,�˿�5���ֻ��0~4
 * \param[in] func_sel    : ����ѡ��ʹ�ú�ֵ��AMHW_PINCON_SEL_FUNC*(#AMHW_PINCON_SEL_FUNC0)
 *
 * \return ��
 */
am_static_inline
void amhw_pincon_sel_cfg (amhw_pincon_t *p_hw_pincon,
                          uint8_t        port,
                          uint8_t        pin_num,
                          uint8_t        func_sel)
{
    p_hw_pincon->iocon[port][pin_num] = \
        (p_hw_pincon->iocon[port][pin_num] & (~AMHW_PINCON_FUNC_MASK)) | \
        (func_sel & AMHW_PINCON_FUNC_MASK);

}


/**
 * \name �ܽ�ģʽ����
 * @{
 */

#define AMHW_PINCON_MODE_FLOAT     0     /**< \brief ����ģʽ                     */
#define AMHW_PINCON_MODE_PULLDOWN  1     /**< \brief ����ģʽ                      */
#define AMHW_PINCON_MODE_PULLUP    2     /**< \brief ����ģʽ                      */
#define AMHW_PINCON_MODE_REPEATER  3     /**< \brief �м�ģʽ                    */

/** @} */

/**
 * \brief Pin connectģʽ����(�����ܽŵ�ģʽ)
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 * \param[in] mode         : ģʽѡ��ʹ�ú�ֵ��
 *                           AMHW_PINCON_MODE_*(#AMHW_PINCON_MODE_PULLUP)
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_mode_cfg (amhw_pincon_t *p_hw_pincon,
                           uint8_t        port,
                           uint8_t        pin_num,
                           uint8_t        mode)
{
    p_hw_pincon->iocon[port][pin_num] = \
            (p_hw_pincon->iocon[port][pin_num] & (~AMHW_PINCON_MODE_MASK)) | \
            ((mode << AMHW_PINCON_MODE_POS) & AMHW_PINCON_MODE_MASK);

}

/**
 * \brief �ܽų���ģʽʹ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_hys_enable (amhw_pincon_t     *p_hw_pincon,
                             uint8_t            port,
                             uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_HYS_POS);
}

/**
 * \brief �ܽų���ģʽʧ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_hys_disable (amhw_pincon_t     *p_hw_pincon,
                              uint8_t            port,
                              uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_HYS_POS);
}

/**
 * \brief �ܽ����뷴��ʹ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_invert_enable (amhw_pincon_t     *p_hw_pincon,
                                uint8_t            port,
                                uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_INVERT_POS);
}

/**
 * \brief �ܽ����뷴�����
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_invert_disable (amhw_pincon_t *p_hw_pincon,
                                 uint8_t        port,
                                 uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_INVERT_POS);
}

/**
 * \brief �ܽ�ADģʽ����Ϊģ��ģʽ
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_admode_analog (amhw_pincon_t *p_hw_pincon,
                                uint8_t        port,
                                uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_ADMODE_POS);
}

/**
 * \brief �ܽ�ADģʽ����Ϊ����ģʽ
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_admode_digital (amhw_pincon_t     *p_hw_pincon,
                                 uint8_t            port,
                                 uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_ADMODE_POS);
}

/**
 * \brief �ܽ�ë���˲������ˣ�����10ns���������屻����  ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_filter_enable (amhw_pincon_t *p_hw_pincon,
                                uint8_t        port,
                                uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_FILTER_POS);
}

/**
 * \brief �ܽ�ë���˲���ʧ�ܣ�������������� ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_filter_disable (amhw_pincon_t *p_hw_pincon,
                                 uint8_t        port,
                                 uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_FILTER_POS);
}

/**
 * \brief �ܽ�������ת������ʹ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4
 *
 * \return    ��
 *
 * \note ��׼ģʽ�£����ת�����ʿ���ʹ��
 */
am_static_inline
void amhw_pincon_slew_enable (amhw_pincon_t     *p_hw_pincon,
                              uint8_t            port,
                              uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_SLEW_POS);
}

/**
 * \brief �ܽ�������ת�����ʽ���
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4
 *
 * \return    ��
 *
 * \note ����ģʽ�£����ת�����ʿ��ƽ���
 */
am_static_inline
void amhw_pincon_slew_disable (amhw_pincon_t     *p_hw_pincon,
                              uint8_t            port,
                              uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_SLEW_POS);
}

/**
 * \brief �ܽſ�©ʹ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_od_enable (amhw_pincon_t *p_hw_pincon,
                            uint8_t        port,
                            uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_OD_POS);
}

/**
 * \brief �ܽſ�©ʧ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 */
am_static_inline
void amhw_pincon_od_disable (amhw_pincon_t *p_hw_pincon,
                             uint8_t        port,
                             uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_OD_POS);
}

/**
 * \brief �ܽ�I2C 50nsë���˲�����ת�����ʿ���ʹ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 *
 * \note ������ֻ��PIO0.27��PIO0.28��PIO5.2��PIO5.3��Ч
 */
am_static_inline
void amhw_pincon_i2cfilter_enable (amhw_pincon_t     *p_hw_pincon,
                                   uint8_t            port,
                                   uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_HS_POS);
}

/**
 * \brief �ܽ�I2C 50nsë���˲�����ת�����ʿ���ʧ��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 *
 * \note ������ֻ��PIO0.27��PIO0.28��PIO5.2��PIO5.3��Ч
 */
am_static_inline
void amhw_pincon_i2cfilter_disable (amhw_pincon_t     *p_hw_pincon,
                                   uint8_t            port,
                                   uint8_t            pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_HS_POS);
}

/**
 * \brief �ܽ�����������������4mA
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 *
 * \note �ù���ֻ��Թܽ�PIO5_2��PIO5_3.
 */
am_static_inline
void amhw_pincon_hidrive_4ma (amhw_pincon_t *p_hw_pincon,
                              uint8_t        port,
                              uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] &= ~(1 << AMHW_PINCON_HIDRIVE_POS);
}

/**
 * \brief �ܽ�����������������20mA
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 *
 * \return    ��
 *
 * \note �ù���ֻ��Թܽ�PIO5_2��PIO5_3.
 */
am_static_inline
void amhw_pincon_hidrive_20ma (amhw_pincon_t *p_hw_pincon,
                               uint8_t        port,
                               uint8_t        pin_num)
{
    p_hw_pincon->iocon[port][pin_num] |= (1 << AMHW_PINCON_HIDRIVE_POS);
}



/**
 * \name I2C�ܽ�ģʽ
 * @{
 */

#define AMHW_PINCON_I2CMODE_FAST_STANDARD   0    /**< \brief ��׼ģʽ/FMģʽ            */
#define AMHW_PINCON_I2CMODE_OPENDRAINIO     1    /**< \brief ��©ģʽ(��I2Cģʽ) */
#define AMHW_PINCON_I2CMODE_FASTMODEPLUS    2    /**< \brief I2C FM+ģʽ                      */
/** @} */

/**
 * \brief ���ùܽ�I2Cģʽ
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 * \param[in] port         : �˿ں�   ��0 ~ 5
 * \param[in] pin_num      : ���ű�� : 0 ~ 31, �˿�Ϊ5ʱ,���Ϊ0~4.
 * \param[in] mode         : I2Cģʽѡ��ֵΪ(#AMHW_PINCON_I2CMODE_FAST_STANDARD)��
 *                          (#AMHW_PINCON_I2CMODE_OPENDRAINIO)��
 *                          (#AMHW_PINCON_I2CMODE_FASTMODEPLUS)
 *
 * \return    ��
 */
void amhw_pincon_i2cmode_set (amhw_pincon_t *p_hw_pincon,
                             uint8_t        port,
                             uint8_t        pin_num,
                             uint8_t        mode);

/**
 * \brief DACʹ�ܣ��ܽ�PIO0_26��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 *
 * \return ��
 *
 */
am_static_inline
void amhw_pincon_dac_enable (amhw_pincon_t *p_hw_pincon)
{
    p_hw_pincon->iocon[0][26] |= (1 << AMHW_PINCON_DACEN_POS);
}

/**
 * \brief DAC���ܣ��ܽ�PIO0_26��
 *
 * \param[in] p_hw_pincon  : ָ��PINCON�Ĵ������ָ��
 *
 * \return    ��
 *
 */
am_static_inline
void amhw_pincon_dac_disable (amhw_pincon_t *p_hw_pincon)
{
    p_hw_pincon->iocon[0][26] &= ~(1 << AMHW_PINCON_DACEN_POS);
}


/**
 * @} amhw_if_pincon
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_PINCON_H */

/* end of file */
