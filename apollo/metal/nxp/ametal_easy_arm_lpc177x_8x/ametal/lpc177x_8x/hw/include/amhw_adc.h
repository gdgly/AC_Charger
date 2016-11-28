/*******************************************************************************
*                                Apollo
*                      ----------------------------
*                      innovating embedded platform
*
*Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
*All rights reserved.
*
*Contact information:
*web site:    http://www.zlg.cn/
*e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC Ӳ����ӿ�
 *
 * - 12λ���αƽ�ʽģ��ת������
 * - 8�����Ÿ���ΪA/D����ţ�
 * - ���е���ģʽ��
 * - ������Χ��0~VREFP��ͨ��Ϊ3V��������VDDA����
 * - 12λת��ʱ�䣬200KHz��
 * - һ�����������Burstת��ģʽ��
 * - ��ѡ�������������ʱ��ƥ���źŴ���ת����
 *
 * \internal
 * \par Modification history
 * - 1.01 15-08-19  cod, fix code style and comments.
 * - 1.00 15-05-26  ben, first implementation.
 * \endinternal
 */
#ifndef  __AMHW_ADC_H
#define  __AMHW_ADC_H

#ifdef __cplusplus
extern "C" {
#endif
#include "am_types.h"

/**
 * \addtogroup amhw_if_adc
 * \copydoc amhw_adc.h
 * @{
 */

/**
 * \brief �����ṹ��εĿ�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */


/**
 * \brief ADC �Ĵ����ṹ
 */
typedef struct amhw_adc {
    __IO uint32_t ctrl;               /**< \brief ADC ���ƼĴ���          */
    __IO uint32_t gdat;               /**< \brief ADC ȫ�����ݼĴ���      */
	     uint32_t reserved;           /**< \brief ����          */
	__IO uint32_t inten;              /**< \brief ADC �ж�ʹ�ܼĴ��� */
    union {
        __I uint32_t dat[8];          /**< \brief ADC ͨ�����ݼĴ���    */
        struct {
            __I uint32_t dat0;        /**< \brief ADC ͨ��0���ݼĴ���   */
            __I uint32_t dat1;        /**< \brief ADC ͨ��1���ݼĴ���   */
            __I uint32_t dat2;        /**< \brief ADC ͨ��2���ݼĴ���   */
            __I uint32_t dat3;        /**< \brief ADC ͨ��3���ݼĴ���   */
            __I uint32_t dat4;        /**< \brief ADC ͨ��4���ݼĴ���   */
            __I uint32_t dat5;        /**< \brief ADC ͨ��5���ݼĴ���   */
            __I uint32_t dat6;        /**< \brief ADC ͨ��6���ݼĴ���   */
            __I uint32_t dat7;        /**< \brief ADC ͨ��7���ݼĴ���   */
        };
    };
    __I  uint32_t status;             /**< \brief ADC ״̬�Ĵ���.   */
    __IO uint32_t trim;               /**< \brief ADC trim �Ĵ���.  */
} amhw_adc_t;


/**
 * \name ADC ͨ��������
 * \anchor grp_amhw_adc_chan
 * @{
 */

#define AMHW_ADC_CHAN_0          0          /**< \brief ADC  ͨ��0  */
#define AMHW_ADC_CHAN_1          1          /**< \brief ADC  ͨ��1  */
#define AMHW_ADC_CHAN_2          2          /**< \brief ADC  ͨ��2  */
#define AMHW_ADC_CHAN_3          3          /**< \brief ADC  ͨ��3  */
#define AMHW_ADC_CHAN_4          4          /**< \brief ADC  ͨ��4  */
#define AMHW_ADC_CHAN_5          5          /**< \brief ADC  ͨ��5  */
#define AMHW_ADC_CHAN_6          6          /**< \brief ADC  ͨ��6  */
#define AMHW_ADC_CHAN_7          7          /**< \brief ADC  ͨ��7  */

/** @} */

#define AMHW_ADC_CHAN_CNT        8          /**< \brief ͨ������     */

/**
 * \name ADC ����ʹ��/ʧ��
 * @{
 */
#define AMHW_ADC_FUN_ENABLE     (1UL)		/**< \brief ʹ��               */
#define AMHW_ADC_FUN_DISABLE    (0UL)		/**< \brief ʧ��               */

/** @} */

/**
 * \name ADC ���ƼĴ���λ
 * \anchor grp_amhw_adc_ctrl
 * @{
 */
#define AMHW_ADC_CTRL_PINS_SEL(pin)    (1UL << (pin))       /**< \brief ѡ�� AD0 7:0 ��Ϊ�����ܽ�     */
#define AMHW_ADC_CTRL_CLK_DIV(x)       (((x) & 0xFF) << 8)  /**< \brief ���� ADCʱ�ӷ�Ƶ        */
#define AMHW_ADC_CTRL_BURST_REPEAT     (1UL << 16)          /**< \brief ADC burst �ظ�װ��	    */
#define AMHW_ADC_CTRL_BURST_SOFT       (0UL << 16)	        /**< \brief ADC burst �������		*/
#define AMHW_ADC_CTRL_PDN_SET          (1UL << 21)	    	/**< \brief ����ADC��������ͨģʽ   */
#define AMHW_ADC_CTRL_PDN_RESET        (0UL << 21)	    	/**< \brief ����ADC����ģʽ         */
#define AMHW_ADC_CTRL_START_CONFIG(x)  (((x) & 0x7) << 24)  /**< \brief ����ADC����ת��������   */
#define AMHW_ADC_CTRL_TRIG_EDGE        (1UL << 27)	    	/**< \brief ����ADC���ش�������		*/

/** \brief ��������ת��               */
#define AMHW_ADC_CTRL_START_NOW	   (1UL)

/** \brief ��λ27ѡ��ı��س�����P2.10/EINT0/NMI��ʱ����ת��          */
#define AMHW_ADC_CTRL_START_EINT0  (2UL)

/** \brief ��λ27ѡ��ı��س�����P1.27/CLKOUT/USB_OVRCRn/CAP0.1��ʱ����ת��    */
#define AMHW_ADC_CTRL_START_CAP01  (3UL)

/** \brief ��λ27ѡ��ı��س�����MAT0.1ʱ����ת��                  */
#define AMHW_ADC_CTRL_START_MAT01  (4UL)

/** \brief ��λ27ѡ��ı��س�����MAT0.3ʱ����ת��                  */
#define AMHW_ADC_CTRL_START_MAT03  (5UL)

/** \brief ��λ27ѡ��ı��س�����MAT1.0ʱ����ת��                  */
#define AMHW_ADC_CTRL_START_MAT10  (6UL)

/** \brief ��λ27ѡ��ı��س�����MAT1.1ʱ����ת��                  */
#define AMHW_ADC_CTRL_START_MAT11  (7UL)

/** @} */

#define AMHW_ADC_CTRL_START_MASK       (7UL << 24)	    	/**< \brief ����ADC������������  	*/

/**
 * \brief ����ADCת������.
 *
 * \param[in] p_hw_adc : ָ��ADC����ַ.
 *
 * \retval  AM_OK      : �����ɹ�
 * \retval -AM_ETIME   : ������ʱ.
 */
int amhw_adc_startup(amhw_adc_t *p_hw_adc);


/**
 * \brief ����ADCת��Ƶ��
 * \param[in] p_hw_adc : ָ��ADC����ַ.
 * \param[in] convfreq : ADC����Ƶ��
 */

void amhw_adc_set_freq (amhw_adc_t *p_hw_adc, uint32_t convfreq);

/**
 * \brief ADC���ƼĴ���
 *
 * \param[in] p_hw_adc : ADC�Ĵ�������ַ
 * \param[in] flags    : ������,�μ�
 *                       \ref grp_amhw_adc_ctrl "ADC Ctrl Flags"
 *
 * \return    None
 */
am_static_inline
void amhw_adc_config (amhw_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->ctrl = flags;
}

/**
 * \brief ���ADC���ƼĴ���״̬
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����
 * \return    ���ƼĴ���״̬
 */
am_static_inline
uint32_t amhw_adc_ctrl_get (amhw_adc_t *p_hw_adc)
{
    return p_hw_adc->ctrl;
}
/**
 * \brief ����ADCת��ͨ��
 *
 * \param[in] p_hw_adc : ADC����ַ
 * \param[in] channel  : ͨ����,ֵΪ: AMHW_ADC_CHAN_*(#AMHW_ADC_CHAN_0)
 * \param[in] state    : ״̬,ֵΪ��(#AMHW_ADC_FUN_ENABLE)��(#AMHW_ADC_FUN_DISABLE)
 * \return    ��
 */
am_static_inline
void amhw_adc_channel_sel(amhw_adc_t *p_hw_adc, uint8_t channel, uint8_t state)
{
	if(AMHW_ADC_FUN_ENABLE == state){
		p_hw_adc->ctrl |= AMHW_ADC_CTRL_PINS_SEL(channel);
	} else{
	    p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_PINS_SEL(channel);
	}
}

/**
 * \brief ����ADC������ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ�����
 * \param[in] mode     : ѡ������ת��������,
 *                       ֵΪAMHW_ADC_CTRL_START_*(#AMHW_ADC_CTRL_START_NOW)
 * \return    ��
 */
am_static_inline
void amhw_adc_start_cmd (amhw_adc_t *p_hw_adc, uint8_t mode)
{
    p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_START_MASK;
    p_hw_adc->ctrl |=  AMHW_ADC_CTRL_START_CONFIG(mode);
}

/**
 * \brief Burst ģʽ
 *
 * \param[in] p_hw_adc  : ָ��ADC�Ĵ�����
 * \param[in] burstmode : �Ƿ�ʹ��Burstģʽ,
 *                        ֵΪ:(#AMHW_ADC_FUN_ENABLE)��(#AMHW_ADC_FUN_DISABLE)
 * \return    ��
 */
am_static_inline
void amhw_adc_burst_cmd(amhw_adc_t *p_hw_adc, uint8_t burstmode)
{
	p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_BURST_REPEAT;
	if( AMHW_ADC_FUN_ENABLE == burstmode){
		p_hw_adc->ctrl |= AMHW_ADC_CTRL_BURST_REPEAT;
	}
}
/**
 * \brief ���õ�Դģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC����ַ
 * \param[in] mode	   : ����ģʽ,
 *                       ֵΪ:(#AMHW_ADC_FUN_ENABLE)��(#AMHW_ADC_FUN_DISABLE)
 * \return    ��
 */
am_static_inline
void amhw_adc_powerdown_cmd(amhw_adc_t *p_hw_adc,uint8_t mode)
{
	p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_PDN_SET;
	if(AMHW_ADC_FUN_ENABLE == mode){
		p_hw_adc->ctrl |= AMHW_ADC_CTRL_PDN_SET;
	}
}
/**
 * \brief ����ADC��������ģʽ
 *
 * \param[in] p_hw_adc : ָ��ADC����ַ
 * \param[in] mode 	   : ʹ�ܻ��߽���
 *                       ֵΪ:(#AMHW_ADC_FUN_ENABLE)��(#AMHW_ADC_FUN_DISABLE)
 * \return    ��
 */
am_static_inline
void amhw_adc_edgstart_cmd(amhw_adc_t *p_hw_adc,uint8_t mode)
{
	p_hw_adc->ctrl &= ~AMHW_ADC_CTRL_TRIG_EDGE;
	if (AMHW_ADC_FUN_ENABLE == mode){
		p_hw_adc->ctrl |= AMHW_ADC_CTRL_TRIG_EDGE;
	}
}


/**
 * \name ȫ�ּĴ���λ����
 * @{
 */
#define AMHW_ADC_DATA_OVERRUN_FLAG    (1UL << 30)            /**< \brief ���һ��ת��ʧ�ܱ�־      */
#define AMHW_ADC_DATA_DONE_FLAG       (1UL << 31)			 /**< \brief ת����ɱ�־                          */
#define AMHW_ADC_GDATA_RESULT(n) 	  (((n) >> 4) & 0xFFF) 	 /**< \brief ��ȡADCֵ                                  */
#define AMHW_ADC_GDATA_GET_CHN(x)     (((x) >> 24) & 0x7 )   /**< \brief ��ȡָ��ͨ����ǰADCֵ     */

/** @} */

/**
 * \brief ��ȡָ��ͨ��������ֵ
 *
 * \param[in] p_hw_adc : ADC����ַ
 * \param[in] chan     : ADCͨ�����,ֵΪ: AMHW_ADC_CHAN_*(#AMHW_ADC_CHAN_0)
 *
 * \return  ת�����ADCֵ
 */
am_static_inline
uint32_t amhw_adc_chan_data_get (amhw_adc_t *p_hw_adc, int chan)
{
    return (p_hw_adc->dat[chan]);
}

/**
 * \brief ��ȫ�����ݼĴ����л��ADC����.
 *
 * \param[in] p_hw_adc :ָ��ADC����ַ
 *
 * \return    ADCת��ֵ
 */
am_static_inline
uint32_t amhw_adc_glo_data_get (amhw_adc_t *p_hw_adc)
{
    return (p_hw_adc->gdat );
}


/**
 * \name ADC �ж�ʹ�ܼĴ���λ����
 * \anchor grp_amhw_adc_inten
 * @{
 */

#define AMHW_ADC_INTEN_ENABLE(ch)   (0x1UL << ch)   /**< \brief ʹ��ָ��ͨ���ж�    */
#define AMHW_ADC_INTEN_DISABLE(ch)  (0x0UL << ch)   /**< \brief ��ָֹ��ͨ���ж�    */
#define AMHW_ADC_INTEN_EN_SEL       (0x1UL << 8)    /**< \brief �жϴ���ѡ��              */

/** \brief ADC�ж����� */
typedef enum
{
	AMHW_ADC_ADINTEN0 = 0,		/**< \brief �ж�ͨ�� 0 */
	AMHW_ADC_ADINTEN1,			/**< \brief �ж�ͨ�� 1 */
	AMHW_ADC_ADINTEN2,			/**< \brief �ж�ͨ�� 2 */
	AMHW_ADC_ADINTEN3,			/**< \brief �ж�ͨ�� 3 */
	AMHW_ADC_ADINTEN4,			/**< \brief �ж�ͨ�� 4 */
	AMHW_ADC_ADINTEN5,			/**< \brief �ж�ͨ�� 5 */
	AMHW_ADC_ADINTEN6,			/**< \brief �ж�ͨ�� 6 */
	AMHW_ADC_ADINTEN7,			/**< \brief �ж�ͨ�� 7 */
	AMHW_ADC_ADGINTEN			/**< \brief ʹ��ȫ���ж� */
}amhw_adc_type_int_opt;


/** @} */

/**
 * \brief �ж�����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ��������ַ
 * \param[in] intch    : ѡ��ͨ�����,ֵΪ��AMHW_ADC_ADINTEN*(#AMHW_ADC_ADINTEN0)
 * \param[in] state    : ʹ�ܡ����ã�
 *                       ֵΪ:(#AMHW_ADC_FUN_ENABLE)��(#AMHW_ADC_FUN_DISABLE)
 *
 * \return  None
 */
am_static_inline
void amhw_adc_int_config (amhw_adc_t           *p_hw_adc,
		                  amhw_adc_type_int_opt intch,
		                  uint8_t               state)
{
    p_hw_adc->inten &= ~AMHW_ADC_INTEN_ENABLE(intch);
    if(AMHW_ADC_FUN_ENABLE == state){
		p_hw_adc->inten |= AMHW_ADC_INTEN_ENABLE(intch);
    }
}


/**
 * \name ADC ״̬�Ĵ���λ��
 * \anchor grp_amhw_adc_status
 * @{
 */
#define  AMHW_ADC_STATUS_DONE_FLAG(ch)    (1UL << (ch))   /**< \brief װ�����     			*/
#define  AMHW_ADC_STATUS_OVERRUN_FLAG(ch) (1UL << (ch))   /**< \brief ת����ʱ   				*/
#define  AMHW_ADC_STATUS_GINT_FLAG        (1UL << 16)     /**< \brief �κ�ͨ��ת�����ʱ��λ	*/

/** @} */

#define  AMHW_ADC_STA_DONE          	    (1UL)    /**< \brief ת�����   */
#define  AMHW_ADC_STA_OVERRUN               (0UL)    /**< \brief ת����ʱ   */

/**
 * \brief ��ȡADCͨ�����ݼĴ���״̬
 *
 * \param[in] p_hw_adc  : ADC����ַ�Ĵ���
 * \param[in] chan      : ͨ����,ֵΪ: AMHW_ADC_CHAN_*(#AMHW_ADC_CHAN_0)
 * \param[in] flag      : ��ɻ��߳�ʱ��־��
 *                        ֵΪ (#AMHW_ADC_STA_DONE)��  (#AMHW_ADC_STA_OVERRUN)
 * \retval    AM_OK     : ��λ
 * \retval    AM_EINVAL : Ϊ��
 */
am_static_inline uint8_t amhw_adc_channel_get_status(amhw_adc_t *p_hw_adc,
		                                             uint8_t     chan,
		                                             uint8_t     flag)
{
	uint32_t temp;
	temp = p_hw_adc->dat[chan];
	if(flag == AMHW_ADC_STA_DONE){
		temp &= AMHW_ADC_DATA_DONE_FLAG;
	} else {
		temp &= AMHW_ADC_DATA_OVERRUN_FLAG;
	}
	if (temp) {
	    return AM_OK;
	} else {
		return AM_EINVAL;
	}
}

/**
 * \brief ��ȡADCȫ�����ݼĴ���״̬
 *
 * \param[in] p_hw_adc   : ADC����ַ�Ĵ���
 * \param[in] flag       : ��ɻ��߳�ʱ��־,
 *                         ֵΪ (#AMHW_ADC_STA_DONE)��  (#AMHW_ADC_STA_OVERRUN)
 * \retval    AM_OK      : ��λ
 * \retval    AM_EINVAL  : Ϊ��
 */
am_static_inline uint8_t amhw_adc_global_get_status(amhw_adc_t *p_hw_adc,
		                                            uint8_t     flag)
{
	uint32_t temp;
	temp = p_hw_adc->gdat;
	if(flag == AMHW_ADC_STA_DONE){
		temp &= AMHW_ADC_DATA_DONE_FLAG;
	} else {
		temp &= AMHW_ADC_DATA_OVERRUN_FLAG;
	}
	if (temp) {
	    return AM_OK;
	} else {
		return AM_EINVAL;
	}
}


/**
 * \name ADC TRIM �Ĵ���
 * \anchor grp_amhw_adc_trim
 * @{
 */
#define AMHW_ADC_TRIM_ADCOFFS(offs)   (((offs) & 0xF) << 4) 			/**< \brief ����ADCƫ�� */

/**
 * \brief  �����ṹ��εĽ���
 * @{
 */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/** @} */


/**
 *@} amhw_if_adc
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMHW_ADC_H */

/* end of file */
