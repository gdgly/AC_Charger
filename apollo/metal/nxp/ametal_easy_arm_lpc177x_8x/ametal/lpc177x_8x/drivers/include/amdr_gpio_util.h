/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief GPIOƽ̨�������ߺ�
 *
 * ���ļ��������� \sa lpc177x_8x_pin.h. �䶨����GPIOƽ̨���ŵĸ������ܡ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-09-02  cod, first implementation.
 * \endinternal
 */

#ifndef __AMDR_GPIO_UTIL_H
#define __AMDR_GPIO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 


/** 
 * \addtogroup amdr_if_gpio_util
 * \copydoc amdr_gpio_util.h
 * @{
 */

/**
 * \name ʹ��λ��10�����ö��󣬶�Ӧ bit[19 : 12]
 * @{
 */

/** \brief ��������ʹ��λ                                 */
#define AMDR_GPIO_FUNCEN_BIT      AM_BIT(12)
/** \brief ģʽ����ʹ��λ                                  */
#define AMDR_GPIO_MODEEN_BIT      AM_BIT(13)
/** \brief ��������ʹ��λ                                 */
#define AMDR_GPIO_HYSEN_BIT       AM_BIT(14)
/** \brief DACʹ�ܿ���ʹ��λ                                 */
#define AMDR_GPIO_DACENEN_BIT     AM_BIT(14)
/** \brief ���뼫������ʹ��λ                        */
#define AMDR_GPIO_INVERTEN_BIT    AM_BIT(15)
/** \brief ģ��/����ģʽ����ʹ��λ           */
#define AMDR_GPIO_ADMODEEN_BIT    AM_BIT(16)
/** \brief I2C 50nsë���˲�����ת����������ʹ��λ       */
#define AMDR_GPIO_HSEN_BIT        AM_BIT(17)
/** \brief ����ë���˲�������ʹ��λ         */
#define AMDR_GPIO_FILTEREN_BIT    AM_BIT(17)
/** \brief ������������ʹ��λ                        */
#define AMDR_GPIO_SLEWEN_BIT      AM_BIT(18)
/** \brief ���ƹܽŹ������������ʹ��λ       */
#define AMDR_GPIO_HIDRIVEEN_BIT   AM_BIT(18)
/** \brief OD����©������ ʹ��λ                  */
#define AMDR_GPIO_ODEN_BIT        AM_BIT(19)

/** \brief ��������ʹ��λ�Ƿ�����              */
#define AMDR_GPIO_FUNCEN_ISSET(a)     ((a) & AMDR_GPIO_FUNCEN_BIT)
/** \brief ģʽ����ʹ��λ�Ƿ�����                */
#define AMDR_GPIO_MODEEN_ISSET(a)     ((a) & AMDR_GPIO_MODEEN_BIT)
/** \brief ��������ʹ��λ�Ƿ�����                */
#define AMDR_GPIO_HYSEN_ISSET(a)      ((a) & AMDR_GPIO_HYSEN_BIT)
/** \brief DACʹ������ʹ��λ�Ƿ�����                */
#define AMDR_GPIO_DACENEN_ISSET(a)      ((a) & AMDR_GPIO_DACENEN_BIT)
/** \brief ���뼫������ʹ��λ�Ƿ�����                */
#define AMDR_GPIO_INVERTEN_ISSET(a)   ((a) & AMDR_GPIO_INVERTEN_BIT)
/** \brief ģ��/����ģʽʹ��λ�Ƿ�����                */
#define AMDR_GPIO_ADMODEEN_ISSET(a)   ((a) & AMDR_GPIO_ADMODEEN_BIT)
/** \brief ����ë���˲�������ʹ��λ�Ƿ�����                */
#define AMDR_GPIO_FILTEREN_ISSET(a)   ((a) & AMDR_GPIO_FILTEREN_BIT)
/** \brief I2Cë���˲�����ת����������ʹ��λ�Ƿ�����                */
#define AMDR_GPIO_HSEN_ISSET(a)       ((a) & AMDR_GPIO_HSEN_BIT)
/** \brief ������������ʹ��λ�Ƿ�����                */
#define AMDR_GPIO_SLEWEN_ISSET(a)     ((a) & AMDR_GPIO_SLEWEN_BIT)
/** \brief ���ƹܽŹ������������ʹ��λ�Ƿ�����                */
#define AMDR_GPIO_HIDRIVEEN_ISSET(a)  ((a) & AMDR_GPIO_HIDRIVEEN_BIT)
/** \brief OD����©������ ʹ��λ�Ƿ�����         */
#define AMDR_GPIO_ODEN_ISSET(a)       ((a) & AMDR_GPIO_ODEN_BIT)

/** @} */

/**
 * \name �����룬��Ӧ bit[23 : 20]
 *
 * bit[22 : 20] ��ʾ���ܣ�GPIO���ܡ����ù���1~7
 * bit[23]      ��ʾ����ΪGPIOʱ�ķ���
 *
 * @{
 */

#define AMDR_GPIO_FUNCBITS_START         20           /**< \brief ������ʼλ   */
#define AMDR_GPIO_FUNCBITS_LEN           3            /**< \brief �����볤��   */

/** \brief �ù����� */
#define AMDR_GPIO_FUNCBITS_CODE(a)      (AM_SBF((a), AMDR_GPIO_FUNCBITS_START) |  \
                                         AMDR_GPIO_FUNCEN_BIT)
/** \brief ����λƫ�� */
#define AMDR_GPIO_DIRBIT_OFFSET          23

/** \brief GPIO����*/
#define AMDR_GPIO_FUNC_INPUT_VAL         0
/** \brief GPIO��� */
#define AMDR_GPIO_FUNC_OUTPUT_VAL        1

/** \brief �÷����� */
#define AMDR_GPIO_DIR_CODE(a)           (AM_SBF((a), AMDR_GPIO_DIRBIT_OFFSET))


/** \brief ��ȡ������ */
#define AMDR_GPIO_FUNC_GET(data)         AM_BITS_GET((data), AMDR_GPIO_FUNCBITS_START, \
                                         AMDR_GPIO_FUNCBITS_LEN)

/** \brief ��ȡ������ */
#define AMDR_GPIO_DIR_GET(data)          AM_BIT_GET((data), AMDR_GPIO_DIRBIT_OFFSET)

/** \brief ���ù��ܵ�ʱ��ͬʱ�趨����Ϊ���루������ΪGPIOʱ��Ч��*/
#define AMDR_GPIO_FUNC_INPUT(a) \
        (AMDR_GPIO_FUNCBITS_CODE(a) | \
         AMDR_GPIO_DIR_CODE(AMDR_GPIO_FUNC_INPUT_VAL))


/** \brief ���ù��ܵ�ʱ��ͬʱ�趨����Ϊ��� ��������ΪGPIOʱ��Ч��*/
#define AMDR_GPIO_FUNC_OUTPUT(a) \
        (AMDR_GPIO_FUNCBITS_CODE(a) | \
         AMDR_GPIO_DIR_CODE(AMDR_GPIO_FUNC_OUTPUT_VAL))

/** @} */

/**
 * \name ģʽ�룬��Ӧ bit[25 : 24]
 * @{
 */

/** \brief ģʽ��ʼλ */
#define AMDR_GPIO_MODEBITS_START         24

/** \brief ģʽ�볤�� */
#define AMDR_GPIO_MODEBITS_LEN           2

/** \brief ����ģʽ�� */
#define AMDR_GPIO_MODE_CODE(a)          (AM_SBF((a), AMDR_GPIO_MODEBITS_START) | \
                                         AMDR_GPIO_MODEEN_BIT)

/** \brief ��ȡģʽ�� */
#define AMDR_GPIO_MODE_GET(data)        AM_BITS_GET((data), \
                                                    AMDR_GPIO_MODEBITS_START, \
                                                    AMDR_GPIO_MODEBITS_LEN)
/** @} */


/**
 * \name ����ģʽ���ƣ���Ӧ bit[26]
 * @{
 */

/** \brief ����ģʽλƫ�� */
#define AMDR_GPIO_HYSBIT_OFFSET          26

/** \brief ����ģʽʧ��ֵ*/
#define AMDR_GPIO_HYSBIT_DISABLE_VAL     0
/** \brief ����ģʽʹ��ֵ */
#define AMDR_GPIO_HYSBIT_ENABLE_VAL      1

/** \brief ����ģʽλ�� */
#define AMDR_GPIO_HYSBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_HYSBIT_OFFSET) | \
            AMDR_GPIO_HYSEN_BIT)

/** \brief ��ȡ����ģʽλ�� */
#define AMDR_GPIO_HYSBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_HYSBIT_OFFSET)

/** \brief ����ģʽʧ��*/
#define AMDR_GPIO_HYSENBIT_DISABLE  \
          AMDR_GPIO_HYSBIT_CODE(AMDR_GPIO_HYSBIT_DISABLE_VAL)

/** \brief ����ģʽʹ�� */
#define AMDR_GPIO_HYSENBIT_ENABLE \
          AMDR_GPIO_HYSBIT_CODE(AMDR_GPIO_HYSBIT_ENABLE_VAL)

/** @} */

/**
 * \name DACʹ�ܿ��ƣ���Ӧ bit[26]
 * @{
 */

/** \brief DACʹ��λƫ�� */
#define AMDR_GPIO_DACENBIT_OFFSET          26

/** \brief DACʹ��ʧ��ֵ*/
#define AMDR_GPIO_DACENBIT_DISABLE_VAL     0
/** \brief DACʹ��ʹ��ֵ */
#define AMDR_GPIO_DACENBIT_ENABLE_VAL      1

/** \brief DACʹ��λ�� */
#define AMDR_GPIO_DACENBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_DACENBIT_OFFSET) | \
            AMDR_GPIO_DACENEN_BIT)

/** \brief ��ȡDACʹ��λ�� */
#define AMDR_GPIO_DACENBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_DACENBIT_OFFSET)

/** \brief DACʧ��*/
#define AMDR_GPIO_DACENBIT_DISABLE  \
          AMDR_GPIO_DACENBIT_CODE(AMDR_GPIO_DACENBIT_DISABLE_VAL)

/** \brief DACʹ�� */
#define AMDR_GPIO_DACENBIT_ENABLE \
        AMDR_GPIO_DACENBIT_CODE(AMDR_GPIO_DACENBIT_ENABLE_VAL)

/** @} */

/**
 * \name ���뷴����ƣ���Ӧ bit[27]
 * @{
 */

/** \brief ���뷴�����λƫ�� */
#define AMDR_GPIO_INVERTBIT_OFFSET          27

/** \brief ���뷴��ʧ��ֵ */
#define AMDR_GPIO_INVERTBIT_DISABLE_VAL     0
/** \brief ���뷴��ʹ��ֵ */
#define AMDR_GPIO_INVERTBIT_ENABLE_VAL      1

/** \brief ���뷴�����λ�� */
#define AMDR_GPIO_INVERTBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_INVERTBIT_OFFSET) | \
            AMDR_GPIO_INVERTEN_BIT)

/** \brief ��ȡ���뷴�����λ�� */
#define AMDR_GPIO_INVERTBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_INVERTBIT_OFFSET)

/** \brief ���뷴��ʧ�� */
#define AMDR_GPIO_INVERTENBIT_DISABLE  \
          AMDR_GPIO_INVERTBIT_CODE(AMDR_GPIO_INVERTBIT_DISABLE_VAL)

/** \brief ���뷴��ʹ��  */
#define AMDR_GPIO_INVERTENBIT_ENABLE \
          AMDR_GPIO_INVERTBIT_CODE(AMDR_GPIO_INVERTBIT_ENABLE_VAL)

/** @} */

/**
 * \name ģ��/����ģʽѡ����ƣ���Ӧ bit[28]
 * @{
 */

/** \brief ģ��/����ģʽ����λƫ�� */
#define AMDR_GPIO_ADMODEBIT_OFFSET          28

/** \brief ģ��/����ģʽʧ��ֵ */
#define AMDR_GPIO_ADMODEBIT_ANALOG_VAL       0
/** \brief ģ��/����ģʽʹ��ֵ */
#define AMDR_GPIO_ADMODEBIT_DIGITAL_VAL      1

/** \brief ģ��/����ģʽ����λ�� */
#define AMDR_GPIO_ADMODEBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_ADMODEBIT_OFFSET) | \
            AMDR_GPIO_ADMODEEN_BIT)

/** \brief ��ȡģ��/����ģʽ����λ�� */
#define AMDR_GPIO_ADMODEBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_ADMODEBIT_OFFSET)

/** \brief ģ��ģʽ*/
#define AMDR_GPIO_ADMODEENBIT_ANALOG  \
          AMDR_GPIO_ADMODEBIT_CODE(AMDR_GPIO_ADMODEBIT_ANALOG_VAL)

/** \brief ����ģʽ  */
#define AMDR_GPIO_ADMODEENBIT_DIGITAL \
          AMDR_GPIO_ADMODEBIT_CODE(AMDR_GPIO_ADMODEBIT_DIGITAL_VAL)

/** @} */

/**
 * \name I2C 50nsë���˲�����ת����������ʹ��λ���ƣ���Ӧ bit[29]
 * @{
 */

/** \brief I2C 50nsë���˲�����ת�����ʿ���λƫ�� */
#define AMDR_GPIO_HSBIT_OFFSET              29

/** \brief I2C 50nsë���˲�����ת�����ʿ���ʧ��ֵ */
#define AMDR_GPIO_HSBIT_DISABLE_VAL          0
/** \brief I2C 50nsë���˲�����ת�����ʿ���ʹ��ֵ */
#define AMDR_GPIO_HSBIT_ENABLE_VAL           1

/** \brief I2C 50nsë���˲�����ת���������ÿ���λ�� */
#define AMDR_GPIO_HSBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_HSBIT_OFFSET) | \
            AMDR_GPIO_HSEN_BIT)

/** \brief ��ȡ I2C 50nsë���˲�����ת���������ÿ���λ�� */
#define AMDR_GPIO_HSBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_HSBIT_OFFSET)

/** \brief I2C 50nsë���˲�����ת����������ʧ�� */
#define AMDR_GPIO_HSENBIT_DISABLE \
          AMDR_GPIO_HSBIT_CODE(AMDR_GPIO_HSBIT_DISABLE_VAL)

/** \brief I2C 50nsë���˲�����ת����������ʹ��  */
#define AMDR_GPIO_HSENBIT_ENABLE \
          AMDR_GPIO_HSBIT_CODE(AMDR_GPIO_HSBIT_ENABLE_VAL)

/** @} */

/**
 * \name ����ë���˲�������ʹ��λ���ƣ���Ӧ bit[29]
 * @{
 */

/** \brief ����ë���˲������ÿ���λƫ�� */
#define AMDR_GPIO_FILTERBIT_OFFSET              29

/** \brief ����ë���˲������ÿ���ʧ��ֵ */
#define AMDR_GPIO_FILTERBIT_DISABLE_VAL          0
/** \brief ����ë���˲������ÿ���ʹ��ֵ */
#define AMDR_GPIO_FILTERBIT_ENABLE_VAL           1

/** \brief ����ë���˲������ÿ���λ�� */
#define AMDR_GPIO_FILTERBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_FILTERBIT_OFFSET) | \
            AMDR_GPIO_FILTEREN_BIT)

/** \brief ����ë���˲������ÿ��ƿ���λ�� */
#define AMDR_GPIO_FILTERBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_FILTERBIT_OFFSET)

/** \brief ����ë���˲������ÿ�������ʧ�� */
#define AMDR_GPIO_FILTERENBIT_DISABLE \
          AMDR_GPIO_FILTERBIT_CODE(AMDR_GPIO_FILTERBIT_DISABLE_VAL)

/** \brief ����ë���˲������ÿ���ʹ��  */
#define AMDR_GPIO_FILTERENBIT_ENABLE \
          AMDR_GPIO_FILTERBIT_CODE(AMDR_GPIO_FILTERBIT_ENABLE_VAL)

/** @} */

/**
 * \name ������ת����������ʹ��λ���ƣ���Ӧ bit[30]
 * @{
 */

/** \brief ������ת���������ÿ���λƫ�� */
#define AMDR_GPIO_SLEWBIT_OFFSET              30

/** \brief ������ת����������ʧ��ֵ */
#define AMDR_GPIO_SLEWBIT_DISABLE_VAL          0
/** \brief ������ת����������ʹ��ֵ */
#define AMDR_GPIO_SLEWBIT_ENABLE_VAL           1

/** \brief ������ת���������ÿ���λ�� */
#define AMDR_GPIO_SLEWBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_SLEWBIT_OFFSET) | \
            AMDR_GPIO_SLEWEN_BIT)

/** \brief ������ת���������ÿ���λ�� */
#define AMDR_GPIO_SLEWBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_SLEWBIT_OFFSET)

/** \brief ������ת����������ʧ�� */
#define AMDR_GPIO_SLEWENBIT_DISABLE \
          AMDR_GPIO_SLEWBIT_CODE(AMDR_GPIO_SLEWBIT_DISABLE_VAL)

/** \brief ������ת����������ʹ��  */
#define AMDR_GPIO_SLEWENBIT_ENABLE \
          AMDR_GPIO_SLEWBIT_CODE(AMDR_GPIO_SLEWBIT_ENABLE_VAL)

/** @} */

/**
 * \name ���ƹܽŹ������������λ���ƣ���Ӧ bit[30]
 * @{
 */

/** \brief ���ƹܽŹ������������λƫ�� */
#define AMDR_GPIO_HIDRIVEBIT_OFFSET          30

/** \brief ���ƹܽ�������������ֵ4mA */
#define AMDR_GPIO_HIDRIVEBIT_4MA_VAL          0
/** \brief ���ƹܽ�������������ֵ20mA */
#define AMDR_GPIO_HIDRIVEBIT_20MA_VAL         1

/** \brief ���ƹܽŹ������������λ�� */
#define AMDR_GPIO_HIDRIVEBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_HIDRIVEBIT_OFFSET) | \
            AMDR_GPIO_HIDRIVEEN_BIT)

/** \brief ���ƹܽŹ������������λ�� */
#define AMDR_GPIO_HIDRIVEBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_HIDRIVEBIT_OFFSET)

/** \brief ���ƹܽ�������������4mA*/
#define AMDR_GPIO_HIDRIVEENBIT_4MA \
          AMDR_GPIO_HIDRIVEBIT_CODE(AMDR_GPIO_HIDRIVEBIT_4MA_VAL)

/** \brief ���ƹܽ�������������4mA */
#define AMDR_GPIO_HIDRIVEENBIT_20MA \
          AMDR_GPIO_HIDRIVEBIT_CODE(AMDR_GPIO_HIDRIVEBIT_20MA_VAL)

/** @} */

/**
 * \name ��©ģʽ���ƣ���Ӧ bit[31]
 * @{
 */

/** \brief ��©ģʽλƫ�� */
#define AMDR_GPIO_ODBIT_OFFSET          31

/** \brief ��©ģʽʧ��ֵ*/
#define AMDR_GPIO_ODBIT_DISABLE_VAL     0
/** \brief ��©ģʽʹ��ֵ */
#define AMDR_GPIO_ODBIT_ENABLE_VAL      1

/** \brief ��©ģʽλ�� */
#define AMDR_GPIO_ODBIT_CODE(a) \
           (AM_SBF((a), AMDR_GPIO_ODBIT_OFFSET) | \
            AMDR_GPIO_ODEN_BIT)

/** \brief ��ȡ��©ģʽλ�� */
#define AMDR_GPIO_ODBIT_GET(data) \
           AM_BIT_GET((data), AMDR_GPIO_ODBIT_OFFSET)

/** \brief ��©ģʽʧ��*/
#define AMDR_GPIO_ODENBIT_DISABLE  \
          AMDR_GPIO_ODBIT_CODE(AMDR_GPIO_ODBIT_DISABLE_VAL)

/** \brief ��©ģʽʹ�� */
#define AMDR_GPIO_ODENBIT_ENABLE \
          AMDR_GPIO_ODBIT_CODE(AMDR_GPIO_ODBIT_ENABLE_VAL)

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_GPIO_UTIL_H */

/* end of file */
