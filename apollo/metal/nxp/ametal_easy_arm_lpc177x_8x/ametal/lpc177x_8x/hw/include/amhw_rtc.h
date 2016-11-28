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
 * \brief RTCӲ�������ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.02 15-09-18  cod, add Event Monitor/Recorder.
 * - 1.01 15-08-20  cod, fix code style and comments,a little improve.
 * - 1.00 15-07-09  ben, first implementation.
 * \endinternal
 */

#ifndef __AMHW_RTC_H
#define __AMHW_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"

/** 
 * \addtogroup amhw_if_rtc
 * \copydoc amhw_rtc.h
 * @{
 */

/**
 * \brief ʵʱʱ�ӼĴ�����Ľṹ��
 */
typedef struct amhw_rtc {                                                                 
    __IO uint32_t ilr;          /**< \brief �ж�λ�üĴ��� */ 
    __I  uint32_t reserved0;    /**< \brief ���� */
    __IO uint32_t ccr;          /**< \brief ʱ�ӿ��� */
    __IO uint32_t ciir;         /**< \brief �����жϼĴ��� */
    __IO uint32_t amr;          /**< \brief ��������Ĵ��� */
    __I  uint32_t ctime0;       /**< \brief ����ʱ��Ĵ���0 0 */
    __I  uint32_t ctime1;       /**< \brief ����ʱ��Ĵ���0 1 */
    __I  uint32_t ctime2;       /**< \brief ����ʱ��Ĵ���0 2 */
    __IO uint32_t sec;          /**< \brief ������� */
    __IO uint32_t min;          /**< \brief �ּ����� */
    __IO uint32_t hour;         /**< \brief ʱ������ */
    __IO uint32_t dom;          /**< \brief ���ڣ��£��Ĵ��� */
    __IO uint32_t dow;          /**< \brief ���ڼĴ��� */
    __IO uint32_t doy;          /**< \brief ���ڣ��꣩�Ĵ��� */
    __IO uint32_t month;        /**< \brief �¼Ĵ��� */
    __IO uint32_t year;         /**< \brief ��Ĵ��� */
    __IO uint32_t calibration;  /**< \brief У׼ֵ�Ĵ��� */
    __IO uint32_t gpreg0;       /**< \brief ͨ�üĴ��� 0 */
    __IO uint32_t gpreg1;       /**< \brief ͨ�üĴ��� 1 */
    __IO uint32_t gpreg2;       /**< \brief ͨ�üĴ��� 2 */
    __IO uint32_t gpreg3;       /**< \brief ͨ�üĴ��� 3 */
    __IO uint32_t gpreg4;       /**< \brief ͨ�üĴ��� 4 */
    __IO uint32_t rtc_auxen;    /**< \brief RTC����ʹ�ܼĴ��� */
    __IO uint32_t rtc_aux;      /**< \brief RTX�������ƼĴ��� */
    __IO uint32_t alsec;        /**< \brief �뱨��ֵ */
    __IO uint32_t almin;        /**< \brief �ֱ���ֵ */
    __IO uint32_t alhour;       /**< \brief Сʱ����ֵ*/
    __IO uint32_t aldom;        /**< \brief ���ڣ��£�����ֵ */
    __IO uint32_t aldow;        /**< \brief ���ڱ���ֵ */
    __IO uint32_t aldoy;        /**< \brief ���ڣ��꣩����ֵ */
    __IO uint32_t almonth;      /**< \brief �±���ֵ */
    __IO uint32_t alyear;       /**< \brief �걨��ֵ */
    /* �¼������/��¼�� */
    __IO uint32_t erstatus;         /**< \brief ״̬�Ĵ���  */
    __IO uint32_t ercontrol;        /**< \brief ���ƼĴ��� */
    __IO uint32_t ercounters;       /**< \brief �������Ĵ��� */
         uint32_t reserved1;        /**< \brief ����  */
    __IO uint32_t erfirststamp[3];  /**< \brief �׸�ʱ����Ĵ���  */
         uint32_t reserved2;        /**< \brief ����  */
    __IO uint32_t erlaststamp[3];   /**< \brief ĩβʱ����Ĵ���  */

} amhw_rtc_t;

/** 
 * \name RTC �����ж�λ����
 * \anchor grp_amhw_rtc_im
 * @{
 */
 
/** \brief �����жϿ���λ��s    */
#define AMHW_RTC_IM_SEC     AM_BIT(0)

/** \brief �����жϿ���λ��min  */
#define AMHW_RTC_IM_MIN     AM_BIT(1)    

/** \brief �����жϿ���λ��hour */
#define AMHW_RTC_IM_HOUR    AM_BIT(2)  

/** \brief �����жϿ���λ��dom  */
#define AMHW_RTC_IM_DOM     AM_BIT(3)   

/** \brief �����жϿ���λ��dow  */
#define AMHW_RTC_IM_DOW     AM_BIT(4)   

/** \brief �����жϿ���λ��doy  */
#define AMHW_RTC_IM_DOY     AM_BIT(5) 

/** \brief �����жϿ���λ��mon  */
#define AMHW_RTC_IM_MON     AM_BIT(6)    

/** \brief �����жϿ���λ��year */
#define AMHW_RTC_IM_YEAR    AM_BIT(7)

/** \brief RTC�����ж�����      */
#define AMHW_RTC_IM_MASK    ((uint32_t) 0xFF)  

/** @} */

/** 
 * \name RTC ����λ����
 * @{
 */

/** \brief �������ο���λ��s    */
#define AMHW_RTC_AMR_SEC     AM_BIT(0)

/** \brief �������ο���λ��min  */
#define AMHW_RTC_AMR_MIN     AM_BIT(1)    

/** \brief �������ο���λ��hour */
#define AMHW_RTC_AMR_HOUR    AM_BIT(2)  

/** \brief �������ο���λ��dom  */
#define AMHW_RTC_AMR_DOM     AM_BIT(3)   

/** \brief �������ο���λ��dow  */
#define AMHW_RTC_AMR_DOW     AM_BIT(4)   

/** \brief �������ο���λ��doy  */
#define AMHW_RTC_AMR_DOY     AM_BIT(5) 

/** \brief �������ο���λ��mon  */
#define AMHW_RTC_AMR_MON     AM_BIT(6)    

/** \brief �������ο���λ��year */
#define AMHW_RTC_AMR_YEAR    AM_BIT(7)

/** \brief RTC������������      */
#define AMHW_RTC_AMR_MASK    ((uint32_t) 0xFF)  

/** @} */

/**
 * \name RTC �жϱ�־λ
 * @{
 */
#define AMHW_RTC_INT_CIF   AM_BIT(0)  /**< \brief RTC�����жϱ�־      */
#define AMHW_RTC_INT_CALF  AM_BIT(1)  /**< \brief RTC�����жϱ�־      */
/** @} */

/**
 * \brief RTC�Ĵ�����ʼ��
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline 
void amhw_rtc_registers_reset (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ilr         = 0x00;
    p_hw_rtc->ccr         = 0x00;
    p_hw_rtc->ciir        = 0x00;
    p_hw_rtc->amr         = 0xff;
    p_hw_rtc->calibration = 0x00;
}

/**
 * \brief  ��ȡRTC�ж�λ�üĴ���
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    RTC�ж�λ�üĴ���ֵ
 */
am_static_inline 
uint32_t amhw_rtc_ilr_read (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->ilr & 0x03;
}

/**
 * \brief  ��RTC�����ж�
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \retval       0          : ���жϷ���
 * \retval AMHW_RTC_INT_CIF : �������������ж�
 */
am_static_inline
uint8_t amhw_rtc_cif_read (amhw_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->ilr & 0x01);
}

/**
 * \brief  ��RTC�����ж�
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \retval       0          :  ���жϷ���
 * \retval AMHW_RTC_INT_CIF :  ����RTC�����ж�
 */
am_static_inline
uint8_t amhw_rtc_alf_read (amhw_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->ilr & 0x02);
}

/**
 * \brief  ���RTC�ж�
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline 
void amhw_rtc_alf2cif_clear (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ilr = 0x03;
}

/**
 * \brief  ʹ��RTC������
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return NONE
 */
am_static_inline
void amhw_rtc_count_enable (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr |= 1 << 0;
}

/**
 * \brief  ��ֹRTC������
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
void amhw_rtc_count_disable (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr &= ~(1 << 0);
}

/**
 * \brief  ��λRTC�Ĵ���
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
void amhw_rtc_rst (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr |= 1 << 1;
}

/**
 * \brief  �ر�RTCУ׼
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
void amhw_rtc_cali_disable (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr |= 1 << 4;
}

/**
 * \brief  ʹ��RTCУ׼
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
void amhw_rtc_cali_enable (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr &= ~(1 << 4);
}

/**
 * \brief  ����ָ��RTC�����ж�
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] flag     : �����жϣ�AMHW_RTC_IM_*��(#AMHW_RTC_IM_SEC),
 *                       ��ͬʱ���ö���ж�
 * \return    ��
 */
am_static_inline
void amhw_rtc_ciir_set (amhw_rtc_t *p_hw_rtc, uint32_t flag)
{
    p_hw_rtc->ciir = flag;
}

/**
 * \brief  ���ָ��RTC�����ж�
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] flag     : �����жϣ�AMHW_RTC_IM_*��(#AMHW_RTC_IM_SEC)
 * \return    ��
 */
am_static_inline
void amhw_rtc_ciir_clr (amhw_rtc_t *p_hw_rtc, uint32_t flag)
{
    p_hw_rtc->ciir &= ~flag;
}

/**
 * \brief  ��ȡָ��RTC�����ж��Ƿ�����
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    �����жϼĴ���
 */
am_static_inline
uint32_t amhw_rtc_ciir_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->ciir & 0xFF;
}


/** 
 * \name RTCʱ������λ
 * \anchor grp_amhw_rtc_mask
 * @{
 */

/** \brief ʱ���趨���ο���λ��s    */
#define AMHW_RTC_MASK_SEC     AM_BIT(0)

/** \brief ʱ���趨���ο���λ��min  */
#define AMHW_RTC_MASK_MIN     AM_BIT(1)    

/** \brief ʱ���趨���ο���λ��hour */
#define AMHW_RTC_MASK_HOUR    AM_BIT(2)  

/** \brief ʱ���趨���ο���λ��dom  */
#define AMHW_RTC_MASK_DOM     AM_BIT(3)   

/** \brief ʱ���趨���ο���λ��dow  */
#define AMHW_RTC_MASK_DOW     AM_BIT(4)   

/** \brief ʱ���趨���ο���λ��doy  */
#define AMHW_RTC_MASK_DOY     AM_BIT(5) 

/** \brief ʱ���趨���ο���λ��mon  */
#define AMHW_RTC_MASK_MON     AM_BIT(6)    

/** \brief ʱ���趨���ο���λ��year */
#define AMHW_RTC_MASK_YEAR    AM_BIT(7)

/** \brief RTC ʱ���趨����λ���� */
#define AMHW_RTC_TIME_MASK   ((uint32_t) 0xFF)  

/** @} */

/**
 * \brief  ��ȡRTCʱ��
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] p_tm      : Ҫ��ȡ��ʱ��
 * \param[in] flags     : �����֣��μ� \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \return    ��
 */
void amhw_rtc_get_time (amhw_rtc_t *p_hw_rtc, am_tm_t *p_tm, uint16_t flags);

/**
 * \brief  ����RTCʱ��
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] p_tm      : ���õ�ʱ��
 * \param[in] flags     : �����֣��μ� \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \return    ��
 */
void amhw_rtc_set_time (amhw_rtc_t *p_hw_rtc, am_tm_t *p_tm, uint16_t flags);

/**
 * \brief  �趨RTCУ׼ֵ
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] calval   : У׼ֵ
 * \return    ��
 */
am_static_inline 
void amhw_rtc_cali_set_value (amhw_rtc_t *p_hw_rtc, uint16_t calval)
{
    p_hw_rtc->calibration = (p_hw_rtc->calibration & (1 << 17)) | \
    		                (calval & 0x1ffff);
}

/**
 * \brief  ����У׼RTC
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline 
void amhw_rtc_backward_cali (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->calibration |= (1 << 17); 
}

/**
 * \brief  ǰ��У׼RTC
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
void amhw_rtc_forward_cali (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->calibration &= ~(1 << 17); 
}

/**
 * \brief  ��RTCͨ�üĴ����洢5��32λ����
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] p_data   : �洢��ͨ�üĴ���������ָ��
 *
 * \return    ��
 */
void amhw_rtc_store_val_in_gpreg (amhw_rtc_t *p_hw_rtc, uint32_t *p_data);

/**
 * \brief  �����ݼĴ�����ֵ
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] p_data   : ��ȡ5�����ݼĴ�����ֵ����ָ���������ڴ�
 * \return    ��
 */
int amhw_rtc_restore_gpreg_val (amhw_rtc_t *p_hw_rtc, uint32_t *p_data);

/**
 * \brief  ���ñ����Ĵ���ʱ��
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] p_tm      : ���õı���ʱ��
 * \param[in] flags     : �����֣��μ� \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \return    ��
 */       
void amhw_rtc_alarm_set (amhw_rtc_t *p_hw_rtc, am_tm_t *p_tm, uint16_t flags);

/**
 * \brief  ���ñ�������λ
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] mask      : ���������� ���μ� \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \return    ��
 */
am_static_inline
void amhw_rtc_set_alarm_mask (amhw_rtc_t *p_hw_rtc, uint16_t mask)
{
    p_hw_rtc->amr = mask;
}

/*****************************************************************************/
/**
 * \name �¼������ͨ����ʼ��������Ϣ
 * \anchor grp_amhw_er_ctrl_init_flag
 * @{
 */
#define AMHW_RTCER_INTWAKEUP_ENABLE   (1) /**< \brief �жϺͻ���ʹ��    */
#define AMHW_RTCER_INTWAKEUP_DISABLE  (0) /**< \brief �жϺͻ���ʧ��    */

#define AMHW_RTCER_GPCLEAR_ENABLE     (1) /**< \brief �Զ�ʹ�����RTCͨ�üĴ���    */
#define AMHW_RTCER_GPCLEAR_DISABLE    (0) /**< \brief �����RTCͨ�üĴ���    */

#define AMHW_RTCER_POL_POSTIVE        (1) /**< \brief ����ܽ��¼�����Ϊ������    */
#define AMHW_RTCER_POL_NEGATIVE       (0) /**< \brief ����ܽ��¼�����Ϊ������    */

/** @} */

/**
 * \name �¼���������ƼĴ���λ��Ϣ
 * @{
 */
#define AMHW_RTCER_CTRL_L3_MASK        (0x07) /**< \brief ����λ����λ����    */
#define AMHW_RTCER_CTRL_INPUTEN_POS    (3)    /**< \brief ͨ��0ʹ��λƫ��    */
#define AMHW_RTCER_CTRL_CHAN_INTERVAL  (10)   /**< \brief ͨ�����λ    */

/**< \brief ָ��ͨ��n�Ŀ��ƼĴ���λbitƫ��    */
#define AMHW_RTCER_CHAN_BIT_POS(bit, n) \
	    (bit << (n * AMHW_RTCER_CTRL_CHAN_INTERVAL))

#define AMHW_RTCER_MODE_BIT_POS    (30)   /**< \brief ģʽλƫ��    */

/** \brief ģʽλ����    */
#define AMHW_RTCER_MODE_BIT_MASK   (0x03 << AMHW_RTCER_MODE_BIT_POS)
/** @} */

/**
 * \brief �¼������ͨ�����Ƴ�ʼ��
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] chan      : ָ��ͨ���ţ�ֵΪ0/1/2
 * \param[in] flag      : ��ʼ��������Ϣ,�μ� \ref grp_amhw_er_ctrl_init_flag
 *                        ��ͨ����Ϣ���л������д��
 * \return    ��
 */
am_static_inline
void amhw_rtc_er_init (amhw_rtc_t *p_hw_rtc, uint8_t chan, uint16_t flag)
{
    p_hw_rtc->ercontrol &= \
        ~AMHW_RTCER_CHAN_BIT_POS(AMHW_RTCER_CTRL_L3_MASK, chan);
    p_hw_rtc->ercontrol |= (flag << (chan * AMHW_RTCER_CTRL_CHAN_INTERVAL)) &\
    	AMHW_RTCER_CHAN_BIT_POS(AMHW_RTCER_CTRL_L3_MASK, chan);
}

/**
 * \name �¼������ͨ������ʹ�ܿ���
 * @{
 */
#define AMHW_RTCER_CHAN_ENABLE   (0x01) /**< \brief ͨ������ʹ��    */
#define AMHW_RTCER_CHAN_DISABLE  (0)    /**< \brief ͨ������ʧ��    */
/** @} */

/**
 * \brief �¼������ͨ������ʹ�ܿ���
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] chan      : ָ��ͨ���ţ�ֵΪ0/1/2
 * \param[in] val       : ����ʹ�ܻ�ʧ��,
 *                        ֵΪ(#AMHW_RTCER_CHAN_ENABLE)��
 *                            (#AMHW_RTCER_CHAN_DISABLE)
 *
 * \return    ��
 */
am_static_inline
void amhw_rtc_er_chan_enable (amhw_rtc_t *p_hw_rtc, uint8_t chan, uint8_t val)
{
    p_hw_rtc->ercontrol &= \
        ~AMHW_RTCER_CHAN_BIT_POS(AMHW_RTCER_CTRL_INPUTEN_POS, chan);
    p_hw_rtc->ercontrol |= AMHW_RTCER_CHAN_BIT_POS(val & 0x01, chan);
}

/**
 * \name �¼����������ģʽ
 * @{
 */
#define AMHW_RTCER_MODE_CLK_DIABLE  (0UL) /**< \brief �¼����/��¼��ʱ�ӱ���ֹ */
#define AMHW_RTCER_MODE_SAMCLK_16HZ (1UL) /**< \brief ����ʱ��16HZ */
#define AMHW_RTCER_MODE_SAMCLK_64HZ (2UL) /**< \brief ����ʱ��64HZ */
#define AMHW_RTCER_MODE_SAMCLK_1KHZ (3UL) /**< \brief ����ʱ��1kHZ */

/** @} */

/**
 * \brief �¼������ģʽѡ��
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] mode      : ģʽѡ��,ֵΪAMHW_RTCER_MODE_*��(#AMHW_RTCER_MODE_CLK_DIABLE)
 *
 * \return    ��
 */
am_static_inline
void amhw_rtc_er_mode_set (amhw_rtc_t *p_hw_rtc, uint8_t mode)
{
    p_hw_rtc->ercontrol &= ~AMHW_RTCER_MODE_BIT_MASK;
    p_hw_rtc->ercontrol |= (mode << AMHW_RTCER_MODE_BIT_POS) & \
                            AMHW_RTCER_MODE_BIT_MASK;
}

/**
 * \name �¼������״̬λ����
 * @{
 */
#define AMHW_RTCER_STATUS_EV0  (1 << 0)  /**< \brief ͨ��0�����¼���־ */
#define AMHW_RTCER_STATUS_EV1  (1 << 1)  /**< \brief ͨ��1�����¼���־ */
#define AMHW_RTCER_STATUS_EV2  (1 << 2)  /**< \brief ͨ��2�����¼���־ */

#define AMHW_RTCER_STATUS_GP_CLEARED  (1 << 3) /**< \brief ͨ�üĴ����첽�����־ */
#define AMHW_RTCER_STATUS_WAKEUP (1UL << 31)   /**< \brief �ж�/���������־ */

/** @} */

/**
 * \brief ��ȡ�¼������״̬��Ϣ
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 *
 * \return ״̬λ��Ϣ��ֵΪAMHW_RTCER_STATUS_*��(#AMHW_RTCER_STATUS_EV0)
 */
am_static_inline
uint32_t amhw_rtc_er_status_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->erstatus;
}

/**
 * \brief ����¼������״̬��Ϣ
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] status    : ָ��״̬λ��ֵΪAMHW_RTCER_STATUS_*��(#AMHW_RTCER_STATUS_EV0)
 *
 * \return ��
 */
am_static_inline
void amhw_rtc_er_status_clear (amhw_rtc_t *p_hw_rtc, uint32_t status)
{
    p_hw_rtc->erstatus |= status;
}

/**
 * \brief�¼������ָ����־λ�Ƿ���λ
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] status    : ָ��״̬λ��ֵΪAMHW_RTCER_STATUS_*��(#AMHW_RTCER_STATUS_EV0)
 *
 * \retval    TRUE      : ָ����־λ��λ
 * \retval    FALSE     : ָ����־λδ��λ
 */
am_static_inline
bool_t amhw_rtc_er_status_check (amhw_rtc_t *p_hw_rtc, uint32_t status)
{
    return (bool_t)((p_hw_rtc->erstatus & status) != 0);
}

/**
 * \name �¼������ͨ������ֵ
 * @{
 */
#define AMHW_RTCER_EV0_COUNTER(n) (n & 0x07)         /**< \brief ͨ��0�¼�����ֵ  */
#define AMHW_RTCER_EV1_COUNTER(n) ((n >> 8) & 0x07)  /**< \brief ͨ��1�¼�����ֵ  */
#define AMHW_RTCER_EV2_COUNTER(n) ((n >> 16) & 0x07) /**< \brief ͨ��2�¼�����ֵ  */
/** @} */

/**
 * \brief ��ȡָ��ͨ���¼�����ֵ
 *
 * \param[in] p_hw_rtc  : ָ��RTC�Ĵ������ָ��
 * \param[in] chan      : ָ��ͨ����ֵΪ0/1/2
 *
 * \return ָ��ͨ���¼�����ֵ
 */
uint8_t amhw_rtc_er_eventcount_get (amhw_rtc_t *p_hw_rtc, uint8_t chan);


/**
 * \brief �¼������/��¼��ʱ���
 */
typedef struct amhw_rtcer_timestamp
{
    uint32_t sec;   /**< \brief ��ֵ                      */

    uint32_t min;   /**< \brief ��ֵ                      */

    uint32_t hour;  /**< \brief Сʱֵ                 */

    uint32_t doy;   /**< \brief ���ڣ��ֵ꣩  */

} amhw_rtcer_timestamp_t;


/**
 * \name �¼������ʱ���λ����
 * @{
 */
#define AMHW_RTCER_TIMESTAMP_SEC(n)   (n & 0x3F)          /**< \brief ��ֵ */
#define AMHW_RTCER_TIMESTAMP_MIN(n)   ((n >>  6) & 0x3F)  /**< \brief ��ֵ */
#define AMHW_RTCER_TIMESTAMP_HOUR(n)  ((n >> 12) & 0x1F)  /**< \brief Сʱֵ */
#define AMHW_RTCER_TIMESTAMP_DOY(n)   ((n >> 17) & 0x1FF) /**< \brief ���ڣ��ֵ꣩ */
/** @} */

/**
 * \brief ��ȡָ��ͨ���׸�ʱ���
 *
 * \param[in]  p_hw_rtc    : ָ��RTC�Ĵ������ָ��
 * \param[in]  chan        : ָ��ͨ����ֵΪ0/1/2
 * \param[out] p_timestamp : ��ȡ����ʱ���
 *
 * \return ��
 */
void amhw_rtc_er_firsttimestamp_get (amhw_rtc_t             *p_hw_rtc,
                                     uint8_t                 chan,
                                     amhw_rtcer_timestamp_t *p_timestamp);

/**
 * \brief ��ȡָ��ͨ��ĩβʱ���
 *
 * \param[in]  p_hw_rtc      : ָ��RTC�Ĵ������ָ��
 * \param[in]  chan          : ָ��ͨ����ֵΪ0/1/2
 * \param[out] p_timestamp   : ��ȡ����ʱ���
 *
 * \return ��
 */
void amhw_rtc_er_lasttimestamp_get (amhw_rtc_t             *p_hw_rtc,
                                    uint8_t                 chan,
                                    amhw_rtcer_timestamp_t *p_timestamp);

/**
 * @} amhw_if_rtc
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_RTC_H */

/* end of file */
