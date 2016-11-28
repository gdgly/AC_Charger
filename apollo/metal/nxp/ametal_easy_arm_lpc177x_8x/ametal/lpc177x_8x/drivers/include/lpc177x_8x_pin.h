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
 * \brief LPC17xx GPIO �������ò�������
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-04-24  tee, first implementation.
 * \endinternal
 */

#ifndef __LPC177X_8X_PIN_H
#define __LPC177X_8X_PIN_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus  */

#include "amdr_gpio_util.h"

/** 
 * \addtogroup amhw_if_pin
 * \copydoc lpc177x_8x_pin.h
 * @{
 */     

/**
 * \name LPC17xx ���ű�Ŷ���
 * @{
 */


#define PIO0_0       0           /**< \brief ���� PIO0_0 */
#define PIO0_1       1           /**< \brief ���� PIO0_1 */
#define PIO0_2       2           /**< \brief ���� PIO0_2 */
#define PIO0_3       3           /**< \brief ���� PIO0_3 */
#define PIO0_4       4           /**< \brief ���� PIO0_4 */
#define PIO0_5       5           /**< \brief ���� PIO0_5 */
#define PIO0_6       6           /**< \brief ���� PIO0_10 */
#define PIO0_7       7           /**< \brief ���� PIO0_7 */
#define PIO0_8       8           /**< \brief ���� PIO0_8 */
#define PIO0_9       9           /**< \brief ���� PIO0_9 */
#define PIO0_10      10          /**< \brief ���� PIO0_10 */
#define PIO0_11      11          /**< \brief ���� PIO0_11 */
#define PIO0_12      12          /**< \brief ���� PIO0_12 */
#define PIO0_13      13          /**< \brief ���� PIO0_13 */
#define PIO0_14      14          /**< \brief ���� PIO0_14 */
#define PIO0_15      15          /**< \brief ���� PIO0_15 */
#define PIO0_16      16          /**< \brief ���� PIO0_16 */
#define PIO0_17      17          /**< \brief ���� PIO0_17 */
#define PIO0_18      18          /**< \brief ���� PIO0_18 */
#define PIO0_19      19          /**< \brief ���� PIO0_19 */
#define PIO0_20      20          /**< \brief ���� PIO0_20 */
#define PIO0_21      21          /**< \brief ���� PIO0_21 */
#define PIO0_22      22          /**< \brief ���� PIO0_22 */
#define PIO0_23      23          /**< \brief ���� PIO0_23 */
#define PIO0_24      24          /**< \brief ���� PIO0_24 */
#define PIO0_25      25          /**< \brief ���� PIO0_25 */
#define PIO0_26      26          /**< \brief ���� PIO0_26 */
#define PIO0_27      27          /**< \brief ���� PIO0_27 */
#define PIO0_28      28          /**< \brief ���� PIO0_28 */
#define PIO0_29      29          /**< \brief ���� PIO0_29 */
#define PIO0_30      30          /**< \brief ���� PIO0_30 */
#define PIO0_31      31          /**< \brief ���� PIO0_31 */

#define PIO1_0       32          /**< \brief ���� PIO1_0 */
#define PIO1_1       33          /**< \brief ���� PIO1_1 */
#define PIO1_2       34          /**< \brief ���� PIO1_2 */
#define PIO1_3       35          /**< \brief ���� PIO1_3 */
#define PIO1_4       36          /**< \brief ���� PIO1_4 */
#define PIO1_5       37          /**< \brief ���� PIO1_5 */
#define PIO1_6       38          /**< \brief ���� PIO1_6 */
#define PIO1_7       39          /**< \brief ���� PIO1_7 */
#define PIO1_8       40          /**< \brief ���� PIO1_8 */
#define PIO1_9       41          /**< \brief ���� PIO1_9 */
#define PIO1_10      42          /**< \brief ���� PIO1_10 */
#define PIO1_11      43          /**< \brief ���� PIO1_11 */
#define PIO1_12      44          /**< \brief ���� PIO1_12 */
#define PIO1_13      45          /**< \brief ���� PIO1_13 */
#define PIO1_14      46          /**< \brief ���� PIO1_14 */
#define PIO1_15      47          /**< \brief ���� PIO1_15 */
#define PIO1_16      48          /**< \brief ���� PIO1_16 */
#define PIO1_17      49          /**< \brief ���� PIO1_17 */
#define PIO1_18      50          /**< \brief ���� PIO1_18 */
#define PIO1_19      51          /**< \brief ���� PIO1_19 */
#define PIO1_20      52          /**< \brief ���� PIO1_20 */
#define PIO1_21      53          /**< \brief ���� PIO1_21 */
#define PIO1_22      54          /**< \brief ���� PIO1_22 */
#define PIO1_23      55          /**< \brief ���� PIO1_23 */
#define PIO1_24      56          /**< \brief ���� PIO1_24 */
#define PIO1_25      57          /**< \brief ���� PIO1_25 */
#define PIO1_26      58          /**< \brief ���� PIO1_26 */
#define PIO1_27      59          /**< \brief ���� PIO1_27 */
#define PIO1_28      60          /**< \brief ���� PIO1_28 */
#define PIO1_29      61          /**< \brief ���� PIO1_29 */
#define PIO1_30      62          /**< \brief ���� PIO1_30 */
#define PIO1_31      63          /**< \brief ���� PIO1_31 */

#define PIO2_0       64          /**< \brief ���� PIO2_0 */
#define PIO2_1       65          /**< \brief ���� PIO2_1 */
#define PIO2_2       66          /**< \brief ���� PIO2_2 */
#define PIO2_3       67          /**< \brief ���� PIO2_3 */
#define PIO2_4       68          /**< \brief ���� PIO2_4 */
#define PIO2_5       69          /**< \brief ���� PIO2_5 */
#define PIO2_6       70          /**< \brief ���� PIO2_6 */
#define PIO2_7       71          /**< \brief ���� PIO2_7 */
#define PIO2_8       72          /**< \brief ���� PIO2_8 */
#define PIO2_9       73          /**< \brief ���� PIO2_9 */
#define PIO2_10      74          /**< \brief ���� PIO2_10 */
#define PIO2_11      75          /**< \brief ���� PIO2_11 */
#define PIO2_12      76          /**< \brief ���� PIO2_12 */
#define PIO2_13      77          /**< \brief ���� PIO2_13 */
#define PIO2_14      78          /**< \brief ���� PIO2_14 */
#define PIO2_15      79          /**< \brief ���� PIO2_15 */
#define PIO2_16      80          /**< \brief ���� PIO2_16 */
#define PIO2_17      81          /**< \brief ���� PIO2_17 */
#define PIO2_18      82          /**< \brief ���� PIO2_18 */
#define PIO2_19      83          /**< \brief ���� PIO2_19 */
#define PIO2_20      84          /**< \brief ���� PIO2_20 */
#define PIO2_21      85          /**< \brief ���� PIO2_21 */
#define PIO2_22      86          /**< \brief ���� PIO2_22 */
#define PIO2_23      87          /**< \brief ���� PIO2_23 */
#define PIO2_24      88          /**< \brief ���� PIO2_24 */
#define PIO2_25      89          /**< \brief ���� PIO2_25 */
#define PIO2_26      90          /**< \brief ���� PIO2_26 */
#define PIO2_27      91          /**< \brief ���� PIO2_27 */
#define PIO2_28      92          /**< \brief ���� PIO2_28 */
#define PIO2_29      93          /**< \brief ���� PIO2_29 */
#define PIO2_30      94          /**< \brief ���� PIO2_30 */
#define PIO2_31      95          /**< \brief ���� PIO2_31 */

#define PIO3_0       96          /**< \brief ���� PIO3_0 */
#define PIO3_1       97          /**< \brief ���� PIO3_1 */
#define PIO3_2       98          /**< \brief ���� PIO3_2 */
#define PIO3_3       99          /**< \brief ���� PIO3_3 */
#define PIO3_4       100         /**< \brief ���� PIO3_4 */
#define PIO3_5       101         /**< \brief ���� PIO3_5 */
#define PIO3_6       102         /**< \brief ���� PIO3_6 */
#define PIO3_7       103         /**< \brief ���� PIO3_7 */
#define PIO3_8       104         /**< \brief ���� PIO3_8 */
#define PIO3_9       105         /**< \brief ���� PIO3_9 */
#define PIO3_10      106         /**< \brief ���� PIO3_10 */
#define PIO3_11      107         /**< \brief ���� PIO3_11 */
#define PIO3_12      108         /**< \brief ���� PIO3_12 */
#define PIO3_13      109         /**< \brief ���� PIO3_13 */
#define PIO3_14      110         /**< \brief ���� PIO3_14 */
#define PIO3_15      111         /**< \brief ���� PIO3_15 */
#define PIO3_16      112         /**< \brief ���� PIO3_16 */
#define PIO3_17      113         /**< \brief ���� PIO3_17 */
#define PIO3_18      114         /**< \brief ���� PIO3_18 */
#define PIO3_19      115         /**< \brief ���� PIO3_19 */
#define PIO3_20      116         /**< \brief ���� PIO3_20 */
#define PIO3_21      117         /**< \brief ���� PIO3_21 */
#define PIO3_22      118         /**< \brief ���� PIO3_22 */
#define PIO3_23      119         /**< \brief ���� PIO3_23 */
#define PIO3_24      120         /**< \brief ���� PIO3_24 */
#define PIO3_25      121         /**< \brief ���� PIO3_25 */
#define PIO3_26      122         /**< \brief ���� PIO3_26 */
#define PIO3_27      123         /**< \brief ���� PIO3_27 */
#define PIO3_28      124         /**< \brief ���� PIO3_28 */
#define PIO3_29      125         /**< \brief ���� PIO3_29 */
#define PIO3_30      126         /**< \brief ���� PIO3_30 */
#define PIO3_31      127         /**< \brief ���� PIO3_31 */

#define PIO4_0       128         /**< \brief ���� PIO4_0 */
#define PIO4_1       129         /**< \brief ���� PIO4_1 */
#define PIO4_2       130         /**< \brief ���� PIO4_2 */
#define PIO4_3       131         /**< \brief ���� PIO4_3 */
#define PIO4_4       132         /**< \brief ���� PIO4_4 */
#define PIO4_5       133         /**< \brief ���� PIO4_5 */
#define PIO4_6       134         /**< \brief ���� PIO4_6 */
#define PIO4_7       135         /**< \brief ���� PIO4_7 */
#define PIO4_8       136         /**< \brief ���� PIO4_8 */
#define PIO4_9       137         /**< \brief ���� PIO4_9 */
#define PIO4_10      138         /**< \brief ���� PIO4_10 */
#define PIO4_11      139         /**< \brief ���� PIO4_11 */
#define PIO4_12      140         /**< \brief ���� PIO4_12 */
#define PIO4_13      141         /**< \brief ���� PIO4_13 */
#define PIO4_14      142         /**< \brief ���� PIO4_14 */
#define PIO4_15      143         /**< \brief ���� PIO4_15 */
#define PIO4_16      144         /**< \brief ���� PIO4_16 */
#define PIO4_17      145         /**< \brief ���� PIO4_17 */
#define PIO4_18      146         /**< \brief ���� PIO4_18 */
#define PIO4_19      147         /**< \brief ���� PIO4_19 */
#define PIO4_20      148         /**< \brief ���� PIO4_20 */
#define PIO4_21      149         /**< \brief ���� PIO4_21 */
#define PIO4_22      150         /**< \brief ���� PIO4_22 */
#define PIO4_23      151         /**< \brief ���� PIO4_23 */
#define PIO4_24      152         /**< \brief ���� PIO4_24 */
#define PIO4_25      153         /**< \brief ���� PIO4_25 */
#define PIO4_26      154         /**< \brief ���� PIO4_26 */
#define PIO4_27      155         /**< \brief ���� PIO4_27 */
#define PIO4_28      156         /**< \brief ���� PIO4_28 */
#define PIO4_29      157         /**< \brief ���� PIO4_29 */
#define PIO4_30      158         /**< \brief ���� PIO4_30 */
#define PIO4_31      159         /**< \brief ���� PIO4_31 */

#define PIO5_0       160         /**< \brief ���� PIO5_0 */
#define PIO5_1       161         /**< \brief ���� PIO5_1 */
#define PIO5_2       162         /**< \brief ���� PIO5_2 */
#define PIO5_3       163         /**< \brief ���� PIO5_3 */
#define PIO5_4       164         /**< \brief ���� PIO5_4 */


#define AMDR_GPIO_PIN_MAX    PIO5_4
#define AMDR_GPIO_PIN_COUNT  (AMDR_GPIO_PIN_MAX + 1)

/** @} */

/**
 * \name GPIO ����ģʽ
 * @{
 */
 
/** \brief ��Ч��������/������ */
#define AMDR_GPIO_FLOAT        AMDR_GPIO_MODE_CODE(0x0)

/** \brief ����ģʽ */
#define AMDR_GPIO_PULLDOWN     AMDR_GPIO_MODE_CODE(0x1)

/** \brief ����ģʽ */
#define AMDR_GPIO_PULLUP       AMDR_GPIO_MODE_CODE(0x2)

/** \brief �м�ģʽ */
#define AMDR_GPIO_REPEATER     AMDR_GPIO_MODE_CODE(0x3)

/** @} */


/**
 * \name PIO0_0 ���Ź��ܶ���
 * @{
 */
#define PIO0_0_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_0_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_0_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_0_RD1          AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief RD1 */
#define PIO0_0_TXD3         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief TXD3 */
#define PIO0_0_SDA1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SDA1 */
#define PIO0_0_TXD0         AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief TXD0 */
/** @} */

/**
 * \name PIO0_0 ����ģʽ����
 * @{
 */
#define PIO0_0_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_0_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_0_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_0_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_0 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_0_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_0_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_0 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_0_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_0_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_0 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_0_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_0_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO0_0 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_0_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_0_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_1 ���Ź��ܶ���
 * @{
 */
#define PIO0_1_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_1_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_1_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_1_TD1          AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief TD1 */
#define PIO0_1_RXD3         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief RXD3 */
#define PIO0_1_SCL1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SCL1 */
#define PIO0_1_RXD0         AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief RXD0 */
/** @} */

/**
 * \name PIO0_1 ����ģʽ����
 * @{
 */
#define PIO0_1_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_1_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_1_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_1_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_1 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_1_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_1_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_1 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_1_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_1_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_1 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_1_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_1_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO0_1 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_1_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_1_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_2 ���Ź��ܶ���
 * @{
 */
#define PIO0_2_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_2_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_2_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_2_TXD0         AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief TXD0 */
#define PIO0_2_TXD3         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief TXD3 */
/** @} */

/**
 * \name PIO0_2 ����ģʽ����
 * @{
 */
#define PIO0_2_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_2_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_2_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_2_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_2 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_2_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_2_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_2 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_2_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_2_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_2 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_2_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_2_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO0_2 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_2_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_2_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_3 ���Ź��ܶ���
 * @{
 */
#define PIO0_3_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_3_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_3_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_3_RXD0         AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief RXD0 */
#define PIO0_2_RXD3         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief RXD3 */
/** @} */

/**
 * \name PIO0_3 ����ģʽ����
 * @{
 */
#define PIO0_3_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_3_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_3_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_3_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_3 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_3_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_3_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_3 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_3_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_3_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_3 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_3_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_3_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO0_3 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_3_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_3_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_4 ���Ź��ܶ���
 * @{
 */
#define PIO0_4_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_4_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_4_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_4_I2SRX_CLK    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief I2SRX_CLK */
#define PIO0_4_RD2          AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief RD2 */
#define PIO0_4_CAP2_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP2.0 */
#define PIO0_4_LCD_VD0      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_VD[0] */

/** @} */

/**
 * \name PIO0_4 ����ģʽ����
 * @{
 */
#define PIO0_4_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_4_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_4_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_4_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_4 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_4_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_4_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_4 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_4_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_4_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_4 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_4_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_4_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO0_4 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_4_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_4_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_5 ���Ź��ܶ���
 * @{
 */
#define PIO0_5_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_5_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_5_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_5_I2SRX_WS     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief I2SRX_WS */
#define PIO0_5_TD2          AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief TD2 */
#define PIO0_5_CAP2_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP2.1 */
#define PIO0_5_LCD_VD1      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_VD[1] */
/** @} */

/**
 * \name PIO0_5 ����ģʽ����
 * @{
 */
#define PIO0_5_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_5_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_5_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_5_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_5 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_5_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_5_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_5 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_5_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_5_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_5 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_5_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_5_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO0_5 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_5_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_5_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_6 ���Ź��ܶ���
 * @{
 */
#define PIO0_6_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_6_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_6_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_6_I2SRX_SDA    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief I2SRX_SDA */
#define PIO0_6_SSEL1        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SSEL1 */
#define PIO0_6_MAT2_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2.0 */
#define PIO0_6_RTS1         AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief U1_RTS */
#define PIO0_6_LCD_VD8      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_VD[8] */

/** @} */

/**
 * \name PIO0_6 ����ģʽ����
 * @{
 */
#define PIO0_6_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_6_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_6_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_6_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_6 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_6_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_6_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_6 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_6_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_6_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_6 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_6_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_6_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_6 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_6_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_6_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_7 ���Ź��ܶ���
 * @{
 */
#define PIO0_7_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_7_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_7_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_7_I2STX_CLK    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief I2STX_CLK */
#define PIO0_7_SCK1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SCK1 */
#define PIO0_7_MAT2_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2_1 */
#define PIO0_7_RTC_EV0      AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief RTC_EV0 */
#define PIO0_7_LCD_VD9      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_VD[9] */

/** @} */

/**
 * \name PIO0_7 ����ģʽ����
 * @{
 */
#define PIO0_7_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_7_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_7_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_7_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_7 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_7_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_7_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_7 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_7_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_7_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_7 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_7_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_7_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */


/**
 * \name PIO0_7 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_7_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_7_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_7 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_7_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_7_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_8 ���Ź��ܶ���
 * @{
 */
#define PIO0_8_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_8_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_8_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_8_I2STX_WS     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief I2STX_WS */
#define PIO0_8_MISO1        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief MISO1 */
#define PIO0_8_MAT2_2       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2.2 */
#define PIO0_8_RTC_EV1      AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief RTC_EV1 */
#define PIO0_8_LCD_VD16     AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_VD[16] */

/** @} */

/**
 * \name PIO0_8 ����ģʽ����
 * @{
 */
#define PIO0_8_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_8_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_8_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_8_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_8 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_8_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_8_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_8 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_8_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_8_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_8 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_8_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_8_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */


/**
 * \name PIO0_8 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_8_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_8_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_8 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_8_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_8_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_9 ���Ź��ܶ���
 * @{
 */
#define PIO0_9_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_9_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_9_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_9_I2STX_SDA    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief I2STX_SDA */
#define PIO0_9_MOSI1        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief MOSI1 */
#define PIO0_9_MAT2_3       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2.3 */
#define PIO0_9_RTC_EV2      AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief RTC_EV1 */
#define PIO0_9_LCD_VD17     AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_VD[17] */

/** @} */

/**
 * \name PIO0_9 ����ģʽ����
 * @{
 */
#define PIO0_9_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_9_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_9_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_9_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_9 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_9_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_9_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_9 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_9_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_9_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_9 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_9_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_9_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */


/**
 * \name PIO0_9 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_9_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_9_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_9 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_9_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_9_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_10 ���Ź��ܶ���
 * @{
 */
#define PIO0_10_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_10_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_10_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_10_TXD2        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief TXD2 */
#define PIO0_10_SDA2        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SDA2 */
#define PIO0_10_MAT3_0      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT3.0 */
/** @} */

/**
 * \name PIO0_10 ����ģʽ����
 * @{
 */
#define PIO0_10_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_10_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_10_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_10_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_10 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_10_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_10_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_10 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_10_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_10_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_10 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_10_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_10_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */




/**
 * \name PIO0_10 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_10_OD_DISABLE  AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_10_OD_ENABLE   AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_11 ���Ź��ܶ���
 * @{
 */
#define PIO0_11_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_11_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_11_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_11_RXD2        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief RXD2 */
#define PIO0_11_SCL2        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SCL2 */
#define PIO0_11_MAT3_1      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT3.1 */
/** @} */

/**
 * \name PIO0_11 ����ģʽ����
 * @{
 */
#define PIO0_11_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_11_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_11_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_11_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_11 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_11_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_11_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_11 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_11_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_11_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_11 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_11_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_11_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */




/**
 * \name PIO0_11 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_11_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_11_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/


/**
 * \name PIO0_12 ���Ź��ܶ���
 * @{
 */
#define PIO0_12_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_12_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_12_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_12_USB2_PPWR   AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB2_PPWR */
#define PIO0_12_MISO1       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief MISO1 */
#define PIO0_12_AD0_6       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief AD0.6 */
/** @} */

/**
 * \name PIO0_12 ����ģʽ����
 * @{
 */
#define PIO0_12_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_12_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_12_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_12_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_12 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_12_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_12_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_12 ģ��/����ģʽѡ����
 * @{
 */
#define PIO0_12_ADMODE_ANALOG   AMDR_GPIO_ADMODEENBIT_ANALOG    /**< \brief ģ��ģʽ               */
#define PIO0_12_ADMODE_DIGITAL  AMDR_GPIO_ADMODEENBIT_DIGITAL   /**< \brief ����ģʽ (Ĭ��)*/
/** @} */

/**
 * \name PIO0_12 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_12_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_12_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */

/**
 * \name PIO0_12 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_12_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_12_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_13 ���Ź��ܶ���
 * @{
 */
#define PIO0_13_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_13_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_13_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_13_USB2_UP_LED AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB2_UP_LED */
#define PIO0_13_MOSI1       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief MOSI1 */
#define PIO0_13_AD0_7       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief AD0.7*/
/** @} */

/**
 * \name PIO0_13 ����ģʽ����
 * @{
 */
#define PIO0_13_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_13_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_13_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_13_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_13 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_13_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_13_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_13 ģ��/����ģʽѡ����
 * @{
 */
#define PIO0_13_ADMODE_ANALOG   AMDR_GPIO_ADMODEENBIT_ANALOG    /**< \brief ģ��ģʽ               */
#define PIO0_13_ADMODE_DIGITAL  AMDR_GPIO_ADMODEENBIT_DIGITAL   /**< \brief ����ģʽ (Ĭ��)*/
/** @} */

/**
 * \name PIO0_13 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_13_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_13_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */

/**
 * \name PIO0_13 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_13_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_13_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_14 ���Ź��ܶ���
 * @{
 */
#define PIO0_14_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_14_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_14_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_14_USB2_HSTEN   AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB2 HSTEN */
#define PIO0_14_SSEL1        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SSP1_SSEL */
#define PIO0_14_USB2_CONNECT AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief USB2_CONNECT */
/** @} */

/**
 * \name PIO0_14 ����ģʽ����
 * @{
 */
#define PIO0_14_PULLUP       AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_14_REPEATER     AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_14_FLOAT        AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_14_PULLDOWN     AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO0_14 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_14_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_14_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_14 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_14_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_14_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_14 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_14_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_14_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO0_14 ��©ʹ�ܶ���
 * @{
*/
#define PIO0_14_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_14_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_15 ���Ź��ܶ���
 * @{
 */
#define PIO0_15_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_15_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_15_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_15_TXD1        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief TXD1 */
#define PIO0_15_SCK0        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SCK0 */
#define PIO0_15_SPIFI_IO2   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SPIFI_IO[2] */

/** @} */

/**
 * \name PIO0_15 ����ģʽ����
 * @{
 */
#define PIO0_15_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_15_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_15_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_15_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_15 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_15_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_15_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_15 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_15_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_15_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_15 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_15_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_15_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_15 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_15_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_15_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_16 ���Ź��ܶ���
 * @{
 */
#define PIO0_16_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_16_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_16_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_16_RXD1        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief RXD1 */
#define PIO0_16_SSEL0       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SSEL0 */
#define PIO0_16_SPIFI_IO3   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SPIFI_IO[3] */
/** @} */

/**
 * \name PIO0_16 ����ģʽ����
 * @{
 */
#define PIO0_16_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_16_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_16_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_16_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_16 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_16_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_16_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_16 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_16_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_16_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_16 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_16_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_16_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_16 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_16_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_16_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_17 ���Ź��ܶ���
 * @{
 */
#define PIO0_17_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_17_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_17_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_17_CTS1        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief CTS1 */
#define PIO0_17_MISO0       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief MISO0 */
#define PIO0_17_SPIFI_IO1   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SPIFI_IO[1] */
/** @} */

/**
 * \name PIO0_17 ����ģʽ����
 * @{
 */
#define PIO0_17_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_17_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_17_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_17_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_17 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_17_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_17_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_17 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_17_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_17_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_17 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_17_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_17_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_17 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_17_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_17_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_18 ���Ź��ܶ���
 * @{
 */
#define PIO0_18_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_18_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_18_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_18_DCD1        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief DCD1  */
#define PIO0_18_MOSI0       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief MOSI0 */
#define PIO0_18_SPIFI_IO0   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SPIFI_IO[0] */
/** @} */

/**
 * \name PIO0_18 ����ģʽ����
 * @{
 */
#define PIO0_18_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_18_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_18_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_18_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_18 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_18_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_18_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_18 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_18_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_18_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_18 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_18_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_18_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_18 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_18_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_18_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_19 ���Ź��ܶ���
 * @{
 */
#define PIO0_19_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_19_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_19_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_19_DSR1        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief DSR1 */
#define PIO0_19_SD_CLK      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD_CLK */
#define PIO0_19_SDA1        AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SDA1 */
/** @} */

/**
 * \name PIO0_19 ����ģʽ����
 * @{
 */
#define PIO0_19_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_19_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_19_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_19_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_19 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_19_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_19_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_19 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_19_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_19_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_19 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_19_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_19_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_19 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_19_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_19_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_20 ���Ź��ܶ���
 * @{
 */
#define PIO0_20_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_20_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_20_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_20_DTR1        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief DTR1 */
#define PIO0_20_SD_CMD      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD_CMD */
#define PIO0_20_SCL1        AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SCL1 */

/** @} */

/**
 * \name PIO0_20 ����ģʽ����
 * @{
 */
#define PIO0_20_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_20_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_20_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_20_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_20 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_20_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_20_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_20 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_20_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_20_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_20 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_20_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_20_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_20 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_20_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_20_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_21 ���Ź��ܶ���
 * @{
 */
#define PIO0_21_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_21_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_21_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_21_RI1         AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief RI1 */
#define PIO0_21_SD_PWR      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD_PWR */
#define PIO0_21_OE4         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART4_OE */
#define PIO0_21_RD1         AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief RD1 */
#define PIO0_21_SCLK4       AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SCLK4 */
/** @} */

/**
 * \name PIO0_21 ����ģʽ����
 * @{
 */
#define PIO0_21_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_21_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_21_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_21_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_21 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_21_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_21_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_21 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_21_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_21_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_21 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_21_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_21_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_21 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_21_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_21_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_22 ���Ź��ܶ���
 * @{
 */
#define PIO0_22_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_22_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_22_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_22_RTS1        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief RTS1 */
#define PIO0_22_SD_DAT0     AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD DAT[0] */
#define PIO0_22_TXD4        AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART4 TXD */
#define PIO0_22_TD1         AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief CAN1 TD */
#define PIO0_22_SPIFI_CLK   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SPIFI CLK */
/** @} */

/**
 * \name PIO0_22 ����ģʽ����
 * @{
 */
#define PIO0_22_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_22_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_22_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_22_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_22 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO0_22_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO0_22_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO0_22 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_22_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_22_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_22 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO0_22_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO0_22_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO0_22 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_22_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_22_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_23 ���Ź��ܶ���
 * @{
 */
#define PIO0_23_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_23_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO0_23_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_23_AD0_0       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief AD0.0       */
#define PIO0_23_I2SRX_CLK   AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2SRX_CLK   */
#define PIO0_23_CAP3_0      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP3.0      */
/** @} */

/**
 * \name PIO0_23 ����ģʽ����
 * @{
 */
#define PIO0_23_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_23_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_23_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_23_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_23 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_23_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_23_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_23 ģ��/����ģʽѡ����
 * @{
 */
#define PIO0_23_ADMODE_ANALOG   AMDR_GPIO_ADMODEENBIT_ANALOG    /**< \brief ģ��ģʽ               */
#define PIO0_23_ADMODE_DIGITAL  AMDR_GPIO_ADMODEENBIT_DIGITAL   /**< \brief ����ģʽ (Ĭ��)*/
/** @} */

/**
 * \name PIO0_23 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_23_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_23_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */


/**
 * \name PIO0_23 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_23_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_23_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_24 ���Ź��ܶ���
 * @{
 */
#define PIO0_24_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_24_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO0_24_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_24_AD0_1       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief AD0.1       */
#define PIO0_24_I2SRX_WS    AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2SRX_WS    */
#define PIO0_24_CAP3_1      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP3.1      */
/** @} */

/**
 * \name PIO0_24 ����ģʽ����
 * @{
 */
#define PIO0_24_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_23_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_24_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_24_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_24 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_24_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_24_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_24 ģ��/����ģʽѡ����
 * @{
 */
#define PIO0_24_ADMODE_ANALOG   AMDR_GPIO_ADMODEENBIT_ANALOG    /**< \brief ģ��ģʽ               */
#define PIO0_24_ADMODE_DIGITAL  AMDR_GPIO_ADMODEENBIT_DIGITAL   /**< \brief ����ģʽ (Ĭ��)*/
/** @} */

/**
 * \name PIO0_24 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_24_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_24_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */


/**
 * \name PIO0_24 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_24_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_24_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_25 ���Ź��ܶ���
 * @{
 */
#define PIO0_25_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_25_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_25_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_25_AD0_2       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief AD0.2     */
#define PIO0_25_I2SRX_SDA   AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2SRX_SDA */
#define PIO0_25_TXD3        AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief TXD3      */
/** @} */

/**
 * \name PIO0_25 ����ģʽ����
 * @{
 */
#define PIO0_25_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_25_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_25_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_25_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_25 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_25_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_25_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_25 ģ��/����ģʽѡ����
 * @{
 */
#define PIO0_25_ADMODE_ANALOG   AMDR_GPIO_ADMODEENBIT_ANALOG    /**< \brief ģ��ģʽ               */
#define PIO0_25_ADMODE_DIGITAL  AMDR_GPIO_ADMODEENBIT_DIGITAL   /**< \brief ����ģʽ (Ĭ��)*/
/** @} */

/**
 * \name PIO0_25 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_25_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_25_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */


/**
 * \name PIO0_25 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_25_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_25_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_26 ���Ź��ܶ���
 * @{
 */
#define PIO0_26_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_26_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_26_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_26_AD0_3       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief AD0.3 */
#define PIO0_26_AOUT        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief AOUT  */
#define PIO0_26_RXD3        AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief RXD3 */
/** @} */

/**
 * \name PIO0_26 ����ģʽ����
 * @{
 */
#define PIO0_26_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO0_26_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO0_26_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO0_26_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO0_26 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_26_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_26_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_26 ģ��/����ģʽѡ����
 * @{
 */
#define PIO0_26_ADMODE_ANALOG   AMDR_GPIO_ADMODEENBIT_ANALOG    /**< \brief ģ��ģʽ               */
#define PIO0_26_ADMODE_DIGITAL  AMDR_GPIO_ADMODEENBIT_DIGITAL   /**< \brief ����ģʽ (Ĭ��)*/
/** @} */

/**
 * \name PIO0_26 DACʹ�ܶ���
 * @{
 */
#define PIO0_26_DAC_DISABLE   AMDR_GPIO_DACENBIT_DISABLE    /**< \brief DAC���� (Ĭ��) */
#define PIO0_26_DAC_ENABLE    AMDR_GPIO_DACENBIT_ENABLE     /**< \brief DACʹ�� */
/** @} */

/**
 * \name PIO0_26 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO0_26_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO0_26_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */


/**
 * \name PIO0_26 ��©ʹ�ܶ���
 * @{
 */
#define PIO0_26_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO0_26_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_27 ���Ź��ܶ���
 * @{
 */
#define PIO0_27_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_27_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_27_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_27_SDA0        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief SDA0    */
#define PIO0_27_USB_SDA     AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief USB_SDA */

/** @} */

/**
 * \name PIO0_27 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_27_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_27_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_27 ���뷴�����ʹ�ܶ���
 * @{
 */

/**< \brief I2C 50nsë���˲�����ת����������ʧ��     */
#define PIO0_27_HS_DISABLE   AMDR_GPIO_HSENBIT_DISABLE
/**< \brief I2C 50nsë���˲�����ת����������ʹ�� (Ĭ��)    */
#define PIO0_27_HS_ENABLE    AMDR_GPIO_HSENBIT_ENABLE
/** @} */


/******************************************************************************/

/**
 * \name PIO0_28 ���Ź��ܶ���
 * @{
 */
#define PIO0_28_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_28_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_28_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_28_SCL0         AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief SCL0 */
#define PIO0_28_USB_SCL      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief USB_SCL */

/** @} */

/**
 * \name PIO0_28 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO0_28_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO0_28_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO0_28 ���뷴�����ʹ�ܶ���
 * @{
 */

/**< \brief I2C 50nsë���˲�����ת����������ʧ��     */
#define PIO0_28_HS_DISABLE   AMDR_GPIO_HSENBIT_DISABLE
/**< \brief I2C 50nsë���˲�����ת����������ʹ�� (Ĭ��)    */
#define PIO0_28_HS_ENABLE    AMDR_GPIO_HSENBIT_ENABLE
/** @} */

/******************************************************************************/

/**
 * \name PIO0_29 ���Ź��ܶ���
 * @{
 */
#define PIO0_29_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_29_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_29_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_29_USB1_D_P     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 D+ */
#define PIO0_29_EINT0        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief EINT0 */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_30 ���Ź��ܶ���
 * @{
 */
#define PIO0_30_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_30_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_30_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_30_USB1_D_N     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 D-      */
#define PIO0_30_EINT1        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief EIN1 */
/** @} */

/******************************************************************************/


/**
 * \name PIO0_31 ���Ź��ܶ���
 * @{
 */
#define PIO0_31_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO0_31_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO0_31_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO0_31_USB2_D_P     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB2 D+      */

/** @} */

/******************************************************************************/

/**
 * \name PIO1_0 ���Ź��ܶ���
 * @{
 */
#define PIO1_0_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_0_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_0_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_0_ENET_TXD0    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_TXD0      */
#define PIO1_0_CAP3_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP3_1      */
#define PIO1_0_SCK2         AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief SSP2 SCK    */
/** @} */

/**
 * \name PIO1_0 ����ģʽ����
 * @{
 */
#define PIO1_0_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_0_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_0_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_0_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_0 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_0_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_0_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_0 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_0_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_0_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_0 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_0_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_0_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_0 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_0_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_0_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_1 ���Ź��ܶ���
 * @{
 */
#define PIO1_1_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_1_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_1_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_1_ENET_TXD1    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_TXD1    */
#define PIO1_1_MAT3_3       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MATCH T3_CH3  */
#define PIO1_1_MOSI2        AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief SSP2 MOSI    */
/** @} */

/**
 * \name PIO1_1 ����ģʽ����
 * @{
 */
#define PIO1_1_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_1_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_1_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_1_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_1 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_1_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_1_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_1 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_1_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_1_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_1 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_1_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_1_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_1 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_1_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_1_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO1_2 ���Ź��ܶ���
 * @{
 */
#define PIO1_2_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_2_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_2_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_2_ENET_TXD2    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_TXD2    */
#define PIO1_2_SD_CLK       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD CLK  */
#define PIO1_2_PWM0_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief PWM0_1    */
 /** @} */

/**
 * \name PIO1_2 ����ģʽ����
 * @{
 */
#define PIO1_2_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_2_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_2_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_2_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_2 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_2_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_2_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_2 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_2_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_2_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_2 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_2_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_2_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_2 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_2_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_2_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO1_3 ���Ź��ܶ���
 * @{
 */
#define PIO1_3_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_3_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_3_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_3_ENET_TXD3    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_TXD3    */
#define PIO1_3_SD_CMD       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD CMD       */
#define PIO1_3_PWM0_2       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief PWM0_2       */
/** @} */

/**
 * \name PIO1_3 ����ģʽ����
 * @{
 */
#define PIO1_3_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_3_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_3_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_3_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_3 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_3_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_3_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_3 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_3_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_3_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_3 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_3_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_3_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_3 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_3_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_3_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_4 ���Ź��ܶ���
 * @{
 */
#define PIO1_4_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_4_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_4_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_4_ENET_TX_EN   AMDR_GPIO_FUNCBITS_CODE(0x01)   /**< \brief ENET_TX_EN    */
#define PIO1_4_MAT3_2       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MATCH T3_CH2  */
#define PIO1_4_MISO2        AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief SSP2 MISO    */
/** @} */

/**
 * \name PIO1_4 ����ģʽ����
 * @{
 */
#define PIO1_4_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_4_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_4_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_4_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_4 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_4_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_4_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_4 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_4_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_4_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_4 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_4_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_4_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_4 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_4_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_4_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_5 ���Ź��ܶ���
 * @{
 */
#define PIO1_5_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_5_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_5_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_5_ENET_TX_ER   AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_TX_ER    */
#define PIO1_5_SD_PWR       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD PWR  */
#define PIO1_5_PWM0_3       AMDR_GPIO_FUNCBITS_CODE(0x03)   /**< \brief PWM0_3    */
/** @} */

/**
 * \name PIO1_5 ����ģʽ����
 * @{
 */
#define PIO1_5_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_5_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_5_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_5_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_5 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_5_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_5_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_5 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_5_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_5_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_5 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_5_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_5_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_5 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_5_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_5_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO1_6 ���Ź��ܶ���
 * @{
 */
#define PIO1_6_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_6_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_6_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_6_ENET_TX_CLK  AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_TX_ER    */
#define PIO1_6_SD_DAT0      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD DAT[0]  */
#define PIO1_6_PWM0_4       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief PWM0_4    */
/** @} */

/**
 * \name PIO1_6 ����ģʽ����
 * @{
 */
#define PIO1_6_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_6_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_6_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_6_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_6 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_6_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_6_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_6 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_6_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_6_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_6 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_6_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_6_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_6 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_6_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_6_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO1_7 ���Ź��ܶ���
 * @{
 */
#define PIO1_7_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_7_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_7_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_7_ENET_COL     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET COL    */
#define PIO1_7_SD_DAT1      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD DAT[1]  */
#define PIO1_7_PWM0_5       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief PWM0_5    */
/** @} */

/**
 * \name PIO1_7 ����ģʽ����
 * @{
 */
#define PIO1_7_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_7_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_7_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_7_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_7 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_7_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_7_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_7 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_7_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_7_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_7 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_7_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_7_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_7 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_7_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_7_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_8 ���Ź��ܶ���
 * @{
 */
#define PIO1_8_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_8_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_8_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_8_ENET_CRS     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_CRS     */
#define PIO1_8_MAT3_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T3 MAT1      */
#define PIO1_8_SSEL2        AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief SSP2 SSEL    */


/** @} */

/**
 * \name PIO1_8 ����ģʽ����
 * @{
 */
#define PIO1_8_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_8_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_8_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_8_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_8 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_8_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_8_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_8 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_8_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_8_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_8 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_8_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_8_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_8 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_8_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_8_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_9 ���Ź��ܶ���
 * @{
 */
#define PIO1_9_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_9_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_9_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_9_ENET_RXD0    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_RXD0     */
#define PIO1_9_MAT3_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T3 MAT0     */


/** @} */

/**
 * \name PIO1_9 ����ģʽ����
 * @{
 */
#define PIO1_9_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_9_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_9_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_9_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_9 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_9_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_9_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_9 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_9_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_9_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_9 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_9_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_9_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_9 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_9_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_9_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_10 ���Ź��ܶ���
 * @{
 */
#define PIO1_10_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_10_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_10_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_10_ENET_RXD1    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_RXD1     */
#define PIO1_10_CAP3_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T3 CAP0     */

/** @} */

/**
 * \name PIO1_10 ����ģʽ����
 * @{
 */
#define PIO1_10_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_10_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_10_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_10_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_10 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_10_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_10_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_10 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_10_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_10_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_10 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_10_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_10_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_10 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_10_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_10_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/


/**
 * \name PIO1_11 ���Ź��ܶ���
 * @{
 */
#define PIO1_11_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_11_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_11_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_11_ENET_RXD2    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_RXD2     */
#define PIO1_11_SD_DAT2      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD DAT[2]     */
#define PIO1_11_PWM0_6       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief PWM0[6]       */
/** @} */

/**
 * \name PIO1_11 ����ģʽ����
 * @{
 */
#define PIO1_11_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_11_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_11_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_11_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_11 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_11_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_11_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_11 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_11_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_11_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_11 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_11_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_11_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_11 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_11_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_11_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/
/**
 * \name PIO1_12 ���Ź��ܶ���
 * @{
 */
#define PIO1_12_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_12_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_12_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_12_ENET_RXD3    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_RXD3     */
#define PIO1_12_SD_DAT3      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD DAT[3]     */
#define PIO1_12_PCAP0_0      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief PWM0 CAP0       */
/** @} */

/**
 * \name PIO1_12 ����ģʽ����
 * @{
 */
#define PIO1_12_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_12_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_12_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_12_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_12 ����ģʽ����
 * @{
 */
#define PIO1_12_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_12_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_12_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_12_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_12 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_12_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_12_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_12 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_12_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_12_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_12 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_12_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_12_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_12 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_12_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_12_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO1_13 ���Ź��ܶ���
 * @{
 */
#define PIO1_13_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_13_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_13_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_13_ENET_RX_DV   AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_RX_DV     */
/** @} */

/**
 * \name PIO1_13 ����ģʽ����
 * @{
 */
#define PIO1_13_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_13_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_13_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_13_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_13 ����ģʽ����
 * @{
 */
#define PIO1_13_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_13_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_13_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_13_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO1_13 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_13_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_13_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_13 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_13_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_13_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_13 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_13_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_13_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_13 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_13_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_13_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_14 ���Ź��ܶ���
 * @{
 */
#define PIO1_14_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_14_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_14_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_14_ENET_RX_ER   AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_RX_ER   */
#define PIO1_14_CAP2_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T2 CAP0   */


/** @} */

/**
 * \name PIO1_14 ����ģʽ����
 * @{
 */
#define PIO1_14_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_14_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_14_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_14_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_14 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_14_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_14_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_14 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_14_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_14_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_14 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_14_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_14_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_14 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_14_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_14_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_15 ���Ź��ܶ���
 * @{
 */
#define PIO1_15_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_15_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��  */
#define PIO1_15_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������  */
#define PIO1_15_ENET_REF_CLK AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_REF_CLK */
#define PIO1_15_SDA2         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief I2C2 SDA   */

/** @} */

/**
 * \name PIO1_15 ����ģʽ����
 * @{
 */
#define PIO1_15_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_15_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_15_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_15_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_15 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_15_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_15_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_15 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_15_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_15_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_15 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_15_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_15_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_15 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_15_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_15_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_16 ���Ź��ܶ���
 * @{
 */
#define PIO1_16_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_16_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��  */
#define PIO1_16_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������  */
#define PIO1_16_ENET_MDC     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief ENET_MDC     */
#define PIO1_16_TX_MCLK      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2S TX MCLK  */

/** @} */

/**
 * \name PIO1_16 ����ģʽ����
 * @{
 */
#define PIO1_16_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_16_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_16_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_16_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_16 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_16_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_16_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_16 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_16_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_16_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_16 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_16_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_16_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_16 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_16_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_16_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_17 ���Ź��ܶ���
 * @{
 */
#define PIO1_17_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_17_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��  */
#define PIO1_17_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������  */
#define PIO1_17_ENET_MDIO    AMDR_GPIO_FUNCBITS_CODE(0x01)   /**< \brief ENET_MDIO     */
#define PIO1_17_RX_MCLK      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2S RX MCLK  */

/** @} */

/**
 * \name PIO1_17 ����ģʽ����
 * @{
 */
#define PIO1_17_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_17_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_17_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_17_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_17 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_17_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_17_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_17 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_17_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_17_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_17 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_17_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_17_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_17 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_17_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_17_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_18 ���Ź��ܶ���
 * @{
 */
#define PIO1_18_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_18_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��  */
#define PIO1_18_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������  */
#define PIO1_18_USB1_UP_LED  AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1_UP_LED    */
#define PIO1_18_PWM1_1       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.1        */
#define PIO1_18_CAP1_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP1.0        */
#define PIO1_18_MISO1        AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SSP1 MISO     */

/** @} */

/**
 * \name PIO1_18 ����ģʽ����
 * @{
 */
#define PIO1_18_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_18_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_18_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_18_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_18 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_18_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_18_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_18 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_18_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_18_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_18 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_18_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_18_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_18 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_18_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_18_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_19 ���Ź��ܶ���
 * @{
 */
#define PIO1_19_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_19_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��  */
#define PIO1_19_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������  */
#define PIO1_19_USB1_TX_E    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 TX EN   */
#define PIO1_19_USB1_PPWR    AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief USB1_PPWR     */
#define PIO1_19_CAP1_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP1.1       */
#define PIO1_19_MCOA0        AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCOA0        */
#define PIO1_19_SCK1         AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SSP1 SCK     */
#define PIO1_19_OE2          AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief USART2 OE    */
/** @} */

/**
 * \name PIO1_19 ����ģʽ����
 * @{
 */
#define PIO1_19_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_19_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_19_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_19_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_19 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_19_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_19_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_19 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_19_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_19_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_19 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_19_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_19_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_19 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_19_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_19_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_20 ���Ź��ܶ���
 * @{
 */
#define PIO1_20_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_20_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_20_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_20_USB1_TX_DP  AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 TX DP */
#define PIO1_20_PWM1_2      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.2 */
#define PIO1_20_PHA         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief QEI PHA    */
#define PIO1_20_MCI0       AMDR_GPIO_FUNCBITS_CODE(0x04)     /**< \brief MCPWM0 FEED OUTPUT  */
#define PIO1_20_SCK0        AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SSP0 SCK   */
#define PIO1_20_LCD_VD6     AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[6]  */
#define PIO1_20_LCD_VD10    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[10] */
/** @} */

/**
 * \name PIO1_20 ����ģʽ����
 * @{
 */
#define PIO1_20_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_20_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_20_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_20_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_20 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_20_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_20_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_20 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_20_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_20_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_20 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_20_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_20_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_20 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_20_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_20_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_21 ���Ź��ܶ���
 * @{
 */
#define PIO1_21_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_21_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_21_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_21_USB1_TX_DM  AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1_TX_DM */
#define PIO1_21_PWM1_3      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.3 */
#define PIO1_21_SSEL0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SSEL0 */
#define PIO1_21_MCABORT     AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCABORT */
#define PIO1_21_LCD_VD7     AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[7]  */
#define PIO1_21_LCD_VD11    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[11] */
/** @} */

/**
 * \name PIO1_21 ����ģʽ����
 * @{
 */
#define PIO1_21_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_21_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_21_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_21_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_21 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_21_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_21_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_21 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_21_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_21_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_21 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_21_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_21_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_21 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_21_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_21_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_22 ���Ź��ܶ���
 * @{
 */
#define PIO1_22_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_22_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_22_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_22_USB1_RCV    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 RCV    */
#define PIO1_22_USB1_PWRD   AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief USB1 PWR */
#define PIO1_22_MAT1_0      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT1.0   */
#define PIO1_22_MCOB0       AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCOB0       */
#define PIO1_22_MOSI1       AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SSP1 MOSI   */
#define PIO1_22_LCD_VD8     AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[8]  */
#define PIO1_22_LCD_VD12    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[12] */
/** @} */

/**
 * \name PIO1_22 ����ģʽ����
 * @{
 */
#define PIO1_22_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_22_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_22_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_22_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_22 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_22_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_22_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_22 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_22_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_22_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_22 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_22_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_22_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_22 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_22_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_22_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_23 ���Ź��ܶ���
 * @{
 */
#define PIO1_23_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_23_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_23_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_23_USB1_RX_DP  AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 RX_DP    */
#define PIO1_23_PWM1_4      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.4 */
#define PIO1_23_PHB         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief QEI PHB */
#define PIO1_23_MCI1       AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCPWM01 FEED OUTPUT  */
#define PIO1_23_MISO0       AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief MISO0      */
#define PIO1_23_LCD_VD9     AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[9]  */
#define PIO1_23_LCD_VD13    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[13] */
/** @} */

/**
 * \name PIO1_23 ����ģʽ����
 * @{
 */
#define PIO1_23_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_23_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_23_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_23_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_23 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_23_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_23_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_23 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_23_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_23_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_23 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_23_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_23_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_23 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_23_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_23_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_24 ���Ź��ܶ���
 * @{
 */
#define PIO1_24_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_24_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_24_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_24_USB1_RX_DM  AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 RX DM */
#define PIO1_24_PWM1_5      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.5 */
#define PIO1_24_IDX         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief QEI IDX    */
#define PIO1_24_MCI2       AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCPWM FB2  */
#define PIO1_24_MOSI0       AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief MOSI0  */
#define PIO1_23_LCD_VD10_14 AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[10]/VD[14] */
#define PIO1_23_LCD_VD14_10 AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[14]/VD[10] */

/** @} */

/**
 * \name PIO1_24 ����ģʽ����
 * @{
 */
#define PIO1_24_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_24_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_24_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_24_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_24 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_24_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_24_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_24 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_24_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_24_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_24 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_24_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_24_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_24 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_24_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_24_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_25 ���Ź��ܶ���
 * @{
 */
#define PIO1_25_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_25_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_25_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_25_USB1_LS     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1_LS    */
#define PIO1_25_USB1_HSTEN  AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief USB1_HSTEN    */
#define PIO1_25_MAT1_1      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT1.1   */
#define PIO1_25_MCOA1       AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCOA1    */
#define PIO1_25_CLKOUT      AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief CLKOUT    */
#define PIO1_25_LCD_VD11    AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[11]  */
#define PIO1_25_LCD_VD15    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[15] */
/** @} */

/**
 * \name PIO1_25 ����ģʽ����
 * @{
 */
#define PIO1_25_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_25_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_25_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_25_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_25 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_25_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_25_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_25 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_25_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_25_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_25 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_25_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_25_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_25 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_25_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_25_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_26 ���Ź��ܶ���
 * @{
 */
#define PIO1_26_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_26_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_26_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_26_USB1_SSPND  AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB SSPND */
#define PIO1_26_PWM1_6      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.6    */
#define PIO1_26_CAP0_0      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP0.0    */
#define PIO1_26_MCOB1       AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCOB1     */
#define PIO1_26_SSEL1       AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SSP1 SSEL */
#define PIO1_26_LCD_VD12    AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[12]*/
#define PIO1_26_LCD_VD20    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[20]*/
/** @} */

/**
 * \name PIO1_26 ����ģʽ����
 * @{
 */
#define PIO1_26_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_26_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_26_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_26_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_26 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_26_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_26_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_26 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_26_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_26_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_26 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_26_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_26_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_26 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_26_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_26_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_27 ���Ź��ܶ���
 * @{
 */
#define PIO1_27_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_27_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_27_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_27_USB1_INT    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 INT    */
#define PIO1_27_USB1_OVRCR  AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief USB_OVRCR   */
#define PIO1_27_CAP0_1      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP0.1      */
#define PIO1_27_CLKOUT      AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief CLKOUT      */
#define PIO1_27_LCD_VD13    AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[13]*/
#define PIO1_27_LCD_VD21    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[21]*/
/** @} */

/**
 * \name PIO1_27 ����ģʽ����
 * @{
 */
#define PIO1_27_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_27_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_27_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_27_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_27 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_27_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_27_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_27 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_27_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_27_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_27 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_27_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_27_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_27 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_27_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_27_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_28 ���Ź��ܶ���
 * @{
 */
#define PIO1_28_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_28_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_28_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_28_USB1_SCL    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB SCL1    */
#define PIO1_28_PCAP1_0     AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PCAP1.0     */
#define PIO1_28_MAT0_0      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT0.0      */
#define PIO1_28_MCOA2       AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCPWM ͨ��2���A  */
#define PIO1_28_SSEL0       AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SSP1 SSEL */
#define PIO1_28_LCD_VD14    AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[14]*/
#define PIO1_28_LCD_VD22    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[22]*/
/** @} */

/**
 * \name PIO1_28 ����ģʽ����
 * @{
 */
#define PIO1_28_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_28_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_28_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_28_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_28 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_28_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_28_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_28 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_28_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_28_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_28 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_28_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_28_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO1_28 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_28_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_28_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_29 ���Ź��ܶ���
 * @{
 */
#define PIO1_29_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_29_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO1_29_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_29_USB1_SDA    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1 SDA    */
#define PIO1_29_PCAP1_1     AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PCAP1.1     */
#define PIO1_29_MAT0_1      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT0.1      */
#define PIO1_29_MCOB2       AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief MCOB2       */
#define PIO1_29_TXD4        AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief USART4 TXD  */
#define PIO1_29_LCD_VD15    AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[15]  */
#define PIO1_29_LCD_VD23    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[23]  */
/** @} */

/**
 * \name PIO1_29 ����ģʽ����
 * @{
 */
#define PIO1_29_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_29_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_29_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_29_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_29 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO1_29_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO1_29_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO1_29 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_29_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_29_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_29 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO1_29_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO1_29_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO1_29 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_29_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_29_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_30 ���Ź��ܶ���
 * @{
 */
#define PIO1_30_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_30_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_30_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_30_USB2_PWRD   AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB2 PWRD   */
#define PIO1_30_VBUS        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief VBUS        */
#define PIO1_30_AD0_4       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief AD0.4       */
#define PIO1_30_SDA0        AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief I2C0 SDA    */
#define PIO1_30_OE3         AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief UART3 OE    */
/** @} */

/**
 * \name PIO1_30 ����ģʽ����
 * @{
 */
#define PIO1_30_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_30_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_30_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_30_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_30 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_30_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_30_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_30 ģ��/����ģʽѡ����
 * @{
 */
#define PIO1_30_ADMODE_ANALOG   AMDR_GPIO_ADMODEENBIT_ANALOG    /**< \brief ģ��ģʽ               */
#define PIO1_30_ADMODE_DIGITAL  AMDR_GPIO_ADMODEENBIT_DIGITAL   /**< \brief ����ģʽ (Ĭ��)*/
/** @} */

/**
 * \name PIO1_30 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO1_30_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO1_30_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */

/**
 * \name PIO1_30 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_30_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_30_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_31 ���Ź��ܶ���
 * @{
 */
#define PIO1_31_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO1_31_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO1_31_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO1_31_USB2_OVRCR  AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB2 OVRCR  */
#define PIO1_31_SCK1        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SCK1        */
#define PIO1_31_AD0_5       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief AD0.5       */
#define PIO1_31_SCL0        AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief I2C0 SCL    */

/** @} */

/**
 * \name PIO1_31 ����ģʽ����
 * @{
 */
#define PIO1_31_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO1_31_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO1_31_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO1_31_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO1_31 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO1_31_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO1_31_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO1_31 ģ��/����ģʽѡ����
 * @{
 */
#define PIO1_31_ADMODE_ANALOG   AMDR_GPIO_ADMODEENBIT_ANALOG    /**< \brief ģ��ģʽ               */
#define PIO1_31_ADMODE_DIGITAL  AMDR_GPIO_ADMODEENBIT_DIGITAL   /**< \brief ����ģʽ (Ĭ��)*/
/** @} */

/**
 * \name PIO1_31 ����ë���˲���ʹ�ܶ���
 * @{
 */

/** \brief ������������ˣ�����ʧ�ܣ�  */
#define PIO1_31_FILTER_DISABLE   AMDR_GPIO_FILTERENBIT_DISABLE
/** \brief ����Լ10ns�����������ˣ�Ĭ�ϣ�                 */
#define PIO1_31_FILTER_ENABLE    AMDR_GPIO_FILTERENBIT_ENABLE
/** @} */



/**
 * \name PIO1_31 ��©ʹ�ܶ���
 * @{
 */
#define PIO1_31_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO1_31_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_0 ���Ź��ܶ���
 * @{
 */
#define PIO2_0_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_0_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_0_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_0_PWM1_1       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief PWM1.1 */
#define PIO2_0_TXD1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief TXD1   */
#define PIO2_0_LCD_PWR      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_PWR   */

/** @} */

/**
 * \name PIO2_0 ����ģʽ����
 * @{
 */
#define PIO2_0_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_0_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_0_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_0_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_0 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_0_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_0_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_0 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_0_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_0_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_0 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_0_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_0_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_0 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_0_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_0_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_1 ���Ź��ܶ���
 * @{
 */
#define PIO2_1_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_1_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_1_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_1_PWM1_2       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief PWM1.2 */
#define PIO2_1_RXD1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief RXD1 */
#define PIO2_1_LCD_LE       AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_LE   */


/** @} */

/**
 * \name PIO2_1 ����ģʽ����
 * @{
 */
#define PIO2_1_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_1_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_1_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_1_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_1 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_1_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_1_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_1 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_1_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_1_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_1 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_1_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_1_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_1 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_1_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_1_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_2 ���Ź��ܶ���
 * @{
 */
#define PIO2_2_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_2_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_2_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_2_PWM1_3       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief PWM1.3 */
#define PIO2_2_CTS1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief CTS1 */
#define PIO2_2_MAT2_3       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2_3  */
#define PIO2_2_TRACEDATA3   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief TRACEDATA[3]   */
#define PIO2_2_LCD_DCLK     AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_DCLK  */


/** @} */

/**
 * \name PIO2_2 ����ģʽ����
 * @{
 */
#define PIO2_2_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_2_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_2_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_2_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_2 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_2_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_2_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_2 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_2_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_2_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_2 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_2_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_2_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_2 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_2_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_2_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_3 ���Ź��ܶ���
 * @{
 */
#define PIO2_3_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_3_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_3_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_3_PWM1_4       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief PWM1.4 */
#define PIO2_3_DCD1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief DCD1   */
#define PIO2_3_MAT2_2       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2_2  */
#define PIO2_3_TRACEDATA2   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief TRACEDATA[2]   */
#define PIO2_3_LCD_FP       AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_FP  */

/** @} */

/**
 * \name PIO2_3 ����ģʽ����
 * @{
 */
#define PIO2_3_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_3_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_3_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_3_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_3 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_3_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_3_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_3 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_3_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_3_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_3 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_3_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_3_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_3 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_3_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_3_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_4 ���Ź��ܶ���
 * @{
 */
#define PIO2_4_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_4_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_4_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_4_PWM1_5       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief PWM1.5 */
#define PIO2_4_DSR1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief DSR1   */
#define PIO2_4_MAT2_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2_1  */
#define PIO2_4_TRACEDATA1   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief TRACEDATA[1]   */
#define PIO2_4_LCD_ENAB_M   AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_ENAB_M  */

/** @} */

/**
 * \name PIO2_4 ����ģʽ����
 * @{
 */
#define PIO2_4_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_4_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_4_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_4_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_4 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_4_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_4_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_4 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_4_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_4_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_4 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_4_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_4_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_4 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_4_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_4_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_5 ���Ź��ܶ���
 * @{
 */
#define PIO2_5_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_5_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_5_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_5_PWM1_6       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief PWM1.6 */
#define PIO2_5_DTR1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief DTR1   */
#define PIO2_5_MAT2_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2_0  */
#define PIO2_5_TRACEDATA0   AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief TRACEDATA[0]   */
#define PIO2_5_LCD_LP       AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD_LP  */

/** @} */

/**
 * \name PIO2_5 ����ģʽ����
 * @{
 */
#define PIO2_5_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_5_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_5_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_5_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_5 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_5_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_5_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_5 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_5_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_5_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_5 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_5_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_5_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_5 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_5_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_5_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_6 ���Ź��ܶ���
 * @{
 */
#define PIO2_6_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_6_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_6_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_6_PCAP1_0      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief PCAP1.0 */
#define PIO2_6_RI1          AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief RI1     */
#define PIO2_6_CAP2_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2_3  */
#define PIO2_6_OE2          AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief UART2 OE  */
#define PIO2_6_TRACECLK     AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief TRACECLK   */
#define PIO2_6_LCD_VD0      AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[0]  */
#define PIO2_6_LCD_VD4      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[4]  */

/** @} */

/**
 * \name PIO2_6 ����ģʽ����
 * @{
 */
#define PIO2_6_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_6_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_6_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_6_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_6 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_6_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_6_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_6 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_6_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_6_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_6 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_6_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_6_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_6 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_6_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_6_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_7 ���Ź��ܶ���
 * @{
 */
#define PIO2_7_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_7_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_7_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_7_RD2          AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief RD2      */
#define PIO2_7_RTS1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief RTS1     */
#define PIO2_7_SPIFI_CS     AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief SPIFI CS   */
#define PIO2_7_LCD_VD1      AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[1]  */
#define PIO2_7_LCD_VD5      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[5]  */

/** @} */

/**
 * \name PIO2_7 ����ģʽ����
 * @{
 */
#define PIO2_7_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_7_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_7_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_7_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_7 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_7_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_7_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_7 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_7_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_7_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_7 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_7_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_7_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_7 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_7_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_7_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_8 ���Ź��ܶ���
 * @{
 */
#define PIO2_8_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_8_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_8_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_8_TD2          AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief TD2  */
#define PIO2_8_TXD2         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief TXD2 */
#define PIO2_8_CTS1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART1 CTS  */
#define PIO2_8_ENET_MDC     AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief ENET_MDC   */
#define PIO2_8_LCD_VD2      AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[2]  */
#define PIO2_8_LCD_VD6      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[6]  */
/** @} */

/**
 * \name PIO2_8 ����ģʽ����
 * @{
 */
#define PIO2_8_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_8_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_8_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_8_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_8 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_8_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_8_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_8 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_8_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_8_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_8 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_8_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_8_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_8 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_8_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_8_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_9 ���Ź��ܶ���
 * @{
 */
#define PIO2_9_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_9_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO2_9_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_9_USB1_CONNECT AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief USB1_CONNECT  */
#define PIO2_9_RXD2         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief RXD2 */
#define PIO2_9_RXD4         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART4 RXD  */
#define PIO2_9_ENET_MDIO    AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief ENET_MDIO */
#define PIO2_9_LCD_VD3      AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[3]  */
#define PIO2_9_LCD_VD7      AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[7]  */
/** @} */

/**
 * \name PIO2_9 ����ģʽ����
 * @{
 */
#define PIO2_9_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_9_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_9_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_9_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_9 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_9_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_9_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_9 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_9_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_9_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_9 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_9_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_9_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_9 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_9_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_9_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_10 ���Ź��ܶ���
 * @{
 */
#define PIO2_10_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_10_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_10_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_10_EINT0        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EINT0       */
#define PIO2_10_NMI          AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief NMI         */
/** @} */

/**
 * \name PIO2_10 ����ģʽ����
 * @{
 */
#define PIO2_10_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_10_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_10_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_10_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_10 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_10_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_10_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_10 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_10_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_10_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_10 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_10_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_10_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_10 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_10_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_10_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_11 ���Ź��ܶ���
 * @{
 */
#define PIO2_11_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_11_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_11_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_11_EINT1        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EINT1       */
#define PIO2_11_SD_DAT1      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief UART4 RXD  */
#define PIO2_11_I2STX_CLK    AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief I2STX_CLK   */
#define PIO2_11_LCD_CLKIN    AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[7]  */

/** @} */

/**
 * \name PIO2_11 ����ģʽ����
 * @{
 */
#define PIO2_11_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_11_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_11_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_11_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_11 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_11_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_11_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_11 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_11_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_11_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_11 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_11_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_11_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_11 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_11_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_11_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_12 ���Ź��ܶ���
 * @{
 */
#define PIO2_12_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_12_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_12_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_12_EINT2        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EINT2       */
#define PIO2_12_SD_DAT2      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SD DAT[2]  */
#define PIO2_12_I2STX_WS     AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief I2STX_WS    */
#define PIO2_12_LCD_VD4      AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief LCD VD[4]  */
#define PIO2_12_LCD_VD3      AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief LCD VD[3]  */
#define PIO2_12_LCD_VD8      AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[8]  */
#define PIO2_12_LCD_VD18     AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[18] */

/** @} */

/**
 * \name PIO2_12 ����ģʽ����
 * @{
 */
#define PIO2_12_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_12_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_12_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_12_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_12 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_12_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_12_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_12 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_12_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_12_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_12 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_12_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_12_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_12 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_12_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_12_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_13 ���Ź��ܶ���
 * @{
 */
#define PIO2_13_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_13_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_13_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_13_EINT3        AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EINT3       */
#define PIO2_13_SD_DAT3      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief UART4 RXD  */
#define PIO2_13_I2STX_SDA    AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief I2STX_SDA   */
#define PIO2_13_LCD_VD5      AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief LCD VD[5]  */
#define PIO2_13_LCD_VD9      AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[9]  */
#define PIO2_13_LCD_VD19     AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[19] */

/** @} */

/**
 * \name PIO2_13 ����ģʽ����
 * @{
 */
#define PIO2_13_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_13_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_13_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_13_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO2_13 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_13_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_13_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_13 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_13_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_13_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_13 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_13_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_13_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */



/**
 * \name PIO2_13 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_13_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_13_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_14 ���Ź��ܶ���
 * @{
 */
#define PIO2_14_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_14_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_14_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_14_EMC_CS2      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CS2     */
#define PIO2_14_SDA1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2C1_SDA    */
#define PIO2_14_CAP2_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T2 CAP0     */
/** @} */

/**
 * \name PIO2_14 ����ģʽ����
 * @{
 */
#define PIO2_14_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_14_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_14_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_14_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_14 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_14_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_14_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_14 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_14_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_14_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_14 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_14_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_14_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_14 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_14_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_14_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_15 ���Ź��ܶ���
 * @{
 */
#define PIO2_15_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_15_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_15_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_15_EMC_CS3      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CS3     */
#define PIO2_15_SCL1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2C1_SCL    */
#define PIO2_15_CAP2_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T2 CAP1     */
/** @} */

/**
 * \name PIO2_15 ����ģʽ����
 * @{
 */
#define PIO2_15_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_15_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_15_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_15_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_15 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_15_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_15_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_15 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_15_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_15_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_15 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_15_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_15_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_15 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_15_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_15_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_16 ���Ź��ܶ���
 * @{
 */
#define PIO2_16_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_16_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_16_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_16_EMC_CAS      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CAS     */
/** @} */

/**
 * \name PIO2_16 ����ģʽ����
 * @{
 */
#define PIO2_16_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_16_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_16_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_16_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_16 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_16_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_16_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_16 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_16_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_16_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_16 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_16_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_16_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_16 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_16_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_16_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_17 ���Ź��ܶ���
 * @{
 */
#define PIO2_17_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_17_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_17_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_17_EMC_RAS      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC RAS     */
/** @} */

/**
 * \name PIO2_17 ����ģʽ����
 * @{
 */
#define PIO2_17_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_17_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_17_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_17_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_17 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_17_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_17_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_17 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_17_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_17_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_17 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_17_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_17_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_17 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_17_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_17_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_18 ���Ź��ܶ���
 * @{
 */
#define PIO2_18_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_18_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_18_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_18_EMC_CLK0     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CLK0     */
/** @} */

/**
 * \name PIO2_18 ����ģʽ����
 * @{
 */
#define PIO2_18_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_18_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_18_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_18_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_18 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_18_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_18_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_18 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_18_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_18_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_18 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_18_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_18_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */


/**
 * \name PIO2_18 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_18_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_18_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_19 ���Ź��ܶ���
 * @{
 */
#define PIO2_19_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_19_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_19_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_19_EMC_CLK1     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CLK1    */
/** @} */

/**
 * \name PIO2_19 ����ģʽ����
 * @{
 */
#define PIO2_19_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_19_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_19_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_19_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_19 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_19_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_19_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_19 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_19_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_19_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_19 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_19_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_19_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_19 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_19_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_19_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_20 ���Ź��ܶ���
 * @{
 */
#define PIO2_20_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_20_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_20_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_20_EMC_DYCS0    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC DYCS0   */
/** @} */

/**
 * \name PIO2_20 ����ģʽ����
 * @{
 */
#define PIO2_20_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_20_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_20_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_20_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_20 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_20_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_20_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_20 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_20_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_20_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_20 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_20_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_20_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_20 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_20_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_20_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_21 ���Ź��ܶ���
 * @{
 */
#define PIO2_21_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_21_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_21_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_21_EMC_DYCS1    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC DYCS1   */
/** @} */

/**
 * \name PIO2_21 ����ģʽ����
 * @{
 */
#define PIO2_21_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_21_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_21_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_21_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_21 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_21_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_21_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_21 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_21_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_21_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_21 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_21_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_21_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_21 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_21_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_21_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_22 ���Ź��ܶ���
 * @{
 */
#define PIO2_22_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_22_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_22_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_22_EMC_DYCS2    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC DYCS2   */
#define PIO2_22_SCK0         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SSP0 SCK    */
#define PIO2_22_CAP3_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP3.0      */
/** @} */

/**
 * \name PIO2_22 ����ģʽ����
 * @{
 */
#define PIO2_22_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_22_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_22_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_22_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_22 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_22_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_22_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_22 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_22_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_22_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_22 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_22_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_22_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */


/**
 * \name PIO2_22 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_22_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_22_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_23 ���Ź��ܶ���
 * @{
 */
#define PIO2_23_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_23_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_23_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_23_EMC_DYCS3    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC DYCS3   */
#define PIO2_23_SSEL0        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SSP0 SSEL   */
#define PIO2_23_CAP3_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP3.1      */
/** @} */

/**
 * \name PIO2_23 ����ģʽ����
 * @{
 */
#define PIO2_23_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_23_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_23_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_23_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_23 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_23_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_23_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_23 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_23_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_23_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_23 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_23_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_23_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_23 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_23_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_23_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO2_24 ���Ź��ܶ���
 * @{
 */
#define PIO2_24_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_24_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_24_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_24_EMC_CKE0    AMDR_GPIO_FUNCBITS_CODE(0x01)     /**< \brief EMC CKE0   */
/** @} */

/**
 * \name PIO2_24 ����ģʽ����
 * @{
 */
#define PIO2_24_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_24_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_24_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_24_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_24 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_24_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_24_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_24 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_24_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_24_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_24 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_24_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_24_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_24 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_24_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_24_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_25 ���Ź��ܶ���
 * @{
 */
#define PIO2_25_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_25_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_25_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_25_EMC_CKE1     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CKE1   */
/** @} */

/**
 * \name PIO2_25 ����ģʽ����
 * @{
 */
#define PIO2_25_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_25_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_25_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_25_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_25 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_25_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_25_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_25 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_25_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_25_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_25 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_25_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_25_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_25 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_25_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_25_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_26 ���Ź��ܶ���
 * @{
 */
#define PIO2_26_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_26_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_26_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_26_EMC_CKE2     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CKE2     */
#define PIO2_26_MISO0        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SSP0 MISO    */
#define PIO2_26_MAT3_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT3_0       */
/** @} */

/**
 * \name PIO2_26 ����ģʽ����
 * @{
 */
#define PIO2_26_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_26_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_26_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_26_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_26 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_26_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_26_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_26 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_26_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_26_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_26 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_26_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_26_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_26 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_26_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_26_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_27 ���Ź��ܶ���
 * @{
 */
#define PIO2_27_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_27_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_27_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_27_EMC_CKE3     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CKE3     */
#define PIO2_27_MOSI0        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief SSP0 MOSI    */
#define PIO2_27_MAT3_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT3_1       */
/** @} */

/**
 * \name PIO2_27 ����ģʽ����
 * @{
 */
#define PIO2_27_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_27_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_27_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_27_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_27 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_27_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_27_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_27 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_27_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_27_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_27 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_27_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_27_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_27 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_27_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_27_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_28 ���Ź��ܶ���
 * @{
 */
#define PIO2_28_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_28_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_28_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_28_EMC_DQM0     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC DQM0    */
/** @} */

/**
 * \name PIO2_28 ����ģʽ����
 * @{
 */
#define PIO2_28_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_28_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_28_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_28_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_28 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_28_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_28_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_28 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_28_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_28_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_28 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_28_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_28_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_28 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_28_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_28_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_29 ���Ź��ܶ���
 * @{
 */
#define PIO2_29_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_29_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO2_29_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO2_29_EMC_DQM1     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC DQM1    */
/** @} */

/**
 * \name PIO2_29 ����ģʽ����
 * @{
 */
#define PIO2_29_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_29_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_29_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_29_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_29 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_29_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_29_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_29 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_29_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_29_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_29 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_29_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_29_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_29 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_29_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_29_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_30 ���Ź��ܶ���
 * @{
 */
#define PIO2_30_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_30_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO2_30_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO2_30_EMC_DQM2     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC DQM2     */
#define PIO2_30_SDA2         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2C2 SDA     */
#define PIO2_30_MAT3_2       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT3_2       */
/** @} */

/**
 * \name PIO2_30 ����ģʽ����
 * @{
 */
#define PIO2_30_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_30_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_30_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_30_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_30 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_30_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_30_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_30 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_30_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_30_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_30 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_30_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_30_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_30 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_30_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_30_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO2_31 ���Ź��ܶ���
 * @{
 */
#define PIO2_31_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO2_31_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO2_31_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO2_31_EMC_DQM3     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC DQM3     */
#define PIO2_31_SCL2         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2C2 SCL     */
#define PIO2_31_MAT3_3       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT3_3       */
/** @} */

/**
 * \name PIO2_31 ����ģʽ����
 * @{
 */
#define PIO2_31_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO2_31_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO2_31_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO2_31_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO2_31 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO2_31_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO2_31_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO2_31 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO2_31_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO2_31_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO2_31 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO2_31_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO2_31_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO2_31 ��©ʹ�ܶ���
 * @{
 */
#define PIO2_31_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO2_31_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_0 ���Ź��ܶ���
 * @{
 */
#define PIO3_0_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_0_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_0_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_0_EMC_D0       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D0       */
/** @} */

/**
 * \name PIO3_0 ����ģʽ����
 * @{
 */
#define PIO3_0_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_0_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_0_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_0_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_0 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_0_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_0_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_0 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_0_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_0_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_0 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_0_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_0_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_0 ��©ʹ�ܶ���
 * @{
*/
#define PIO3_0_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_0_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_1 ���Ź��ܶ���
 * @{
 */
#define PIO3_1_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_1_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_1_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_1_EMC_D1       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D1       */
/** @} */

/**
 * \name PIO3_1 ����ģʽ����
 * @{
 */
#define PIO3_1_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_1_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_1_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_1_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_1 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_1_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_1_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_1 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_1_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_1_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_1 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_1_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_1_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_1 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_1_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_1_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_2 ���Ź��ܶ���
 * @{
 */
#define PIO3_2_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_2_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_2_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_2_EMC_D2       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D2       */
/** @} */

/**
 * \name PIO3_2 ����ģʽ����
 * @{
 */
#define PIO3_2_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_2_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_2_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_2_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_2 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_2_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_2_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_2 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_2_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_2_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_2 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_2_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_2_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_2 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_2_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_2_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_3 ���Ź��ܶ���
 * @{
 */
#define PIO3_3_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_3_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_3_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_3_EMC_D3       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D3       */
/** @} */

/**
 * \name PIO3_3 ����ģʽ����
 * @{
 */
#define PIO3_3_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_3_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_3_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_3_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_3 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_3_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_3_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_3 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_3_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_3_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_3 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_3_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_3_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_3 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_3_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_3_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO3_4 ���Ź��ܶ���
 * @{
 */
#define PIO3_4_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_4_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_4_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_4_EMC_D4       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D4       */
/** @} */

/**
 * \name PIO3_4 ����ģʽ����
 * @{
 */
#define PIO3_4_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_4_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_4_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_4_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_4 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_4_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_4_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_4 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_4_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_4_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_4 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_4_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_4_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_4 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_4_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_4_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_5 ���Ź��ܶ���
 * @{
 */
#define PIO3_5_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_5_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_5_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_5_EMC_D5       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D5       */
/** @} */

/**
 * \name PIO3_5 ����ģʽ����
 * @{
 */
#define PIO3_5_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_5_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_5_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_5_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_5 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_5_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_5_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_5 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_5_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_5_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_5 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_5_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_5_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_5 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_5_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_5_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO3_6 ���Ź��ܶ���
 * @{
 */
#define PIO3_6_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_6_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_6_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_6_EMC_D6       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D6       */
/** @} */

/**
 * \name PIO3_6 ����ģʽ����
 * @{
 */
#define PIO3_6_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_6_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_6_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_6_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_6 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_6_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_6_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_6 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_6_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_6_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_6 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_6_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_6_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_6 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_6_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_6_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_7 ���Ź��ܶ���
 * @{
 */
#define PIO3_7_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_7_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_7_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_7_EMC_D7       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D7       */
/** @} */

/**
 * \name PIO3_7 ����ģʽ����
 * @{
 */
#define PIO3_7_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_7_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_7_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_7_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_7 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_7_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_7_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_7 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_7_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_7_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_7 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_7_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_7_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_7 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_7_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_7_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_8 ���Ź��ܶ���
 * @{
 */
#define PIO3_8_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_8_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_8_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_8_EMC_D8       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D8       */
/** @} */

/**
 * \name PIO3_8 ����ģʽ����
 * @{
 */
#define PIO3_8_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_8_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_8_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_8_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_8 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_8_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_8_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_8 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_8_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_8_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_8 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_8_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_8_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_8 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_8_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_8_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_9 ���Ź��ܶ���
 * @{
 */
#define PIO3_9_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_9_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_9_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_9_EMC_D9       AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D9       */
/** @} */

/**
 * \name PIO3_9 ����ģʽ����
 * @{
 */
#define PIO3_9_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_9_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_9_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_9_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_9 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_9_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_9_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_9 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_9_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_9_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_9 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_9_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_9_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_9 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_9_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_9_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_10 ���Ź��ܶ���
 * @{
 */
#define PIO3_10_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_10_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_10_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_10_EMC_D10      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D10       */
/** @} */

/**
 * \name PIO3_10 ����ģʽ����
 * @{
 */
#define PIO3_10_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_10_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_10_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_10_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_10 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_10_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_10_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_10 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_10_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_10_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_10 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_10_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_10_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_10 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_10_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_10_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_11 ���Ź��ܶ���
 * @{
 */
#define PIO3_11_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_11_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_11_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_11_EMC_D11      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D11       */
/** @} */

/**
 * \name PIO3_11 ����ģʽ����
 * @{
 */
#define PIO3_11_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_11_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_11_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_11_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_11 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_11_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_11_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_11 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_11_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_11_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_11 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_11_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_11_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_11 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_11_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_11_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_12 ���Ź��ܶ���
 * @{
 */
#define PIO3_12_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_12_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_12_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_12_EMC_D12      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D12       */
/** @} */

/**
 * \name PIO3_12 ����ģʽ����
 * @{
 */
#define PIO3_12_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_12_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_12_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_12_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_12 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_12_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_12_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_12 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_12_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_12_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_12 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_12_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_12_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_12 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_12_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_12_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_13 ���Ź��ܶ���
 * @{
 */
#define PIO3_13_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_13_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_13_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_13_EMC_D13      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D13       */
/** @} */

/**
 * \name PIO3_13 ����ģʽ����
 * @{
 */
#define PIO3_13_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_13_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_13_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_13_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_13 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_13_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_13_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_13 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_13_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_13_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_13 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_13_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_13_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_13 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_13_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_13_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_14 ���Ź��ܶ���
 * @{
 */
#define PIO3_14_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_14_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_14_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_14_EMC_D14      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D14       */
/** @} */

/**
 * \name PIO3_14 ����ģʽ����
 * @{
 */
#define PIO3_14_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_14_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_14_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_14_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_14 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_14_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_14_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_14 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_14_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_14_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_14 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_14_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_14_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_14 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_14_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_14_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_15 ���Ź��ܶ���
 * @{
 */
#define PIO3_15_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_15_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_15_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_15_EMC_D15      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D15       */
/** @} */

/**
 * \name PIO3_15 ����ģʽ����
 * @{
 */
#define PIO3_15_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_15_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_15_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_15_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_15 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_15_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_15_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_15 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_15_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_15_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_15 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_15_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_15_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_15 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_15_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_15_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_16 ���Ź��ܶ���
 * @{
 */
#define PIO3_16_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_16_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_16_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_16_EMC_D16      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D16      */
#define PIO3_16_PWM0_1       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM0.1       */
#define PIO3_16_TXD1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART1 TXD    */
/** @} */

/**
 * \name PIO3_16 ����ģʽ����
 * @{
 */
#define PIO3_16_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_16_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_16_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_16_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_16 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_16_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_16_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_16 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_16_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_16_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_16 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_16_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_16_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_16 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_16_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_16_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_17 ���Ź��ܶ���
 * @{
 */
#define PIO3_17_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_17_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_17_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_17_EMC_D17      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D17      */
#define PIO3_17_PWM0_2       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM0.2       */
#define PIO3_17_RXD1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART1 RXD    */
/** @} */

/**
 * \name PIO3_17 ����ģʽ����
 * @{
 */
#define PIO3_17_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_17_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_17_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_17_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_17 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_17_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_17_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_17 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_17_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_17_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_17 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_17_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_17_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_17 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_17_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_17_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_18 ���Ź��ܶ���
 * @{
 */
#define PIO3_18_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_18_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_18_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_18_EMC_D18      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D18      */
#define PIO3_18_PWM0_3       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM0.3       */
#define PIO3_18_CTS1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART1 CTS    */
/** @} */

/**
 * \name PIO3_18 ����ģʽ����
 * @{
 */
#define PIO3_18_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_18_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_18_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_18_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_18 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_18_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_18_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_18 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_18_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_18_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_18 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_18_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_18_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_18 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_18_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_18_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
* \name PIO3_19 ���Ź��ܶ���
* @{
*/
#define PIO3_19_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_19_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_19_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_19_EMC_D19      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D19      */
#define PIO3_19_PWM0_4       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM0.4       */
#define PIO3_19_DCD1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART1 DCD    */
/** @} */

/**
* \name PIO3_19 ����ģʽ����
* @{
*/
#define PIO3_19_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_19_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_19_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_19_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_19 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_19_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_19_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_19 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_19_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_19_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_19 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_19_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_19_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
* \name PIO3_19 ��©ʹ�ܶ���
* @{
*/
#define PIO3_19_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_19_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_20 ���Ź��ܶ���
 * @{
 */
#define PIO3_20_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_20_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_20_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_20_EMC_D20      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D20      */
#define PIO3_20_PWM0_5       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM0.5       */
#define PIO3_20_DSR1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART1 DSR    */
/** @} */

/**
 * \name PIO3_20 ����ģʽ����
 * @{
 */
#define PIO3_20_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_20_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_20_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_20_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_20 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_20_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_20_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_20 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_20_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_20_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_20 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_20_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_20_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_20 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_20_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_20_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
* \name PIO3_21 ���Ź��ܶ���
* @{
*/
#define PIO3_21_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_21_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_21_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_21_EMC_D21      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D21      */
#define PIO3_21_PWM0_6       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM0.6       */
#define PIO3_21_DTR1         AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART1 DTR    */
/** @} */

/**
* \name PIO3_21 ����ģʽ����
* @{
*/
#define PIO3_21_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_21_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_21_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_21_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_21 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_21_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_21_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_21 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_21_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_21_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_21 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_21_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_21_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
* \name PIO3_21 ��©ʹ�ܶ���
* @{
*/
#define PIO3_21_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_21_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_22 ���Ź��ܶ���
 * @{
 */
#define PIO3_22_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_22_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_22_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_22_EMC_D22      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D22      */
#define PIO3_22_PCAP0_0      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM0 CAP0    */
#define PIO3_22_RI1          AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief UART1 RI     */
/** @} */

/**
 * \name PIO3_22 ����ģʽ����
 * @{
 */
#define PIO3_22_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_22_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_22_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_22_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_22 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_22_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_22_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_22 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_22_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_22_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_22 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_22_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_22_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_22 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_22_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_22_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO3_23 ���Ź��ܶ���
 * @{
 */
#define PIO3_23_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_23_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_23_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_23_EMC_D23      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D23      */
#define PIO3_23_PCAP1_0      AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1 CAP0    */
#define PIO3_23_CAP0_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T0 CAP0      */
/** @} */

/**
 * \name PIO3_23 ����ģʽ����
 * @{
 */
#define PIO3_23_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_23_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_23_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_23_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_23 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_23_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_23_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_23 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_23_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_23_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_23 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_23_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_23_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_23 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_23_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_23_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_24 ���Ź��ܶ���
 * @{
 */
#define PIO3_24_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_24_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��    */
#define PIO3_24_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO�������    */
#define PIO3_24_EMC_D24      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D24      */
#define PIO3_24_PWM1_1       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.1    */
#define PIO3_24_CAP0_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T0 CAP1      */
/** @} */

/**
 * \name PIO3_24 ����ģʽ����
 * @{
 */
#define PIO3_24_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_24_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_24_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_24_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_24 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_24_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_24_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_24 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_24_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_24_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_24 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_24_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_24_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_24 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_24_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_24_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO3_25 ���Ź��ܶ���
 * @{
 */
#define PIO3_25_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_25_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO3_25_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO3_25_EMC_D25      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D25      */
#define PIO3_25_PWM1_2       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.2       */
#define PIO3_25_MAT0_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT0.0       */
/** @} */

/**
 * \name PIO3_25 ����ģʽ����
 * @{
 */
#define PIO3_25_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_25_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_25_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_25_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO3_25 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_25_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_25_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_25 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_25_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_25_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_25 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_25_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_25_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */


/**
 * \name PIO3_25 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_25_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_25_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_26 ���Ź��ܶ���
 * @{
 */
#define PIO3_26_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_26_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO3_26_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO3_26_EMC_D26      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D25     */
#define PIO3_26_PWM1_3       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.3       */
#define PIO3_26_MAT0_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT0.1       */
#define PIO3_26_STCLK        AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief STCLK       */
/** @} */

/**
 * \name PIO3_26 ����ģʽ����
 * @{
 */
#define PIO3_26_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_26_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_26_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_26_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO3_26 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_26_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_26_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_26 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_26_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_26_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_26 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_26_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_26_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */


/**
 * \name PIO3_26 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_26_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_26_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/


/**
 * \name PIO3_27 ���Ź��ܶ���
 * @{
 */
#define PIO3_27_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_27_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO3_27_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO3_27_EMC_D27      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D27     */
#define PIO3_27_PWM1_4       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.3       */
#define PIO3_27_CAP1_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP0.1       */
/** @} */

/**
 * \name PIO3_27 ����ģʽ����
 * @{
 */
#define PIO3_27_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_27_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_27_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_27_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_27 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_27_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_27_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_27 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_27_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_27_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_27 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_27_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_27_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_27 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_27_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_27_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO3_28 ���Ź��ܶ���
 * @{
 */
#define PIO3_28_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_28_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO3_28_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO3_28_EMC_D28      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D28     */
#define PIO3_28_PWM1_5       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.5       */
#define PIO3_28_CAP1_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief CAP0.1       */
/** @} */

/**
 * \name PIO3_28 ����ģʽ����
 * @{
 */
#define PIO3_28_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_28_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_28_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_28_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_28 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_28_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_28_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_28 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_28_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_28_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_28 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_28_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_28_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_28 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_28_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_28_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO3_29 ���Ź��ܶ���
 * @{
 */
#define PIO3_29_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_29_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO3_29_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO3_29_EMC_D29      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D29     */
#define PIO3_29_PWM1_6       AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief PWM1.6       */
#define PIO3_29_MAT1_0       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT1.0       */
/** @} */

/**
 * \name PIO3_29 ����ģʽ����
 * @{
 */
#define PIO3_29_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_29_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_29_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_29_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_29 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_29_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_29_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_29 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_29_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_29_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_29 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_29_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_29_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_29 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_29_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_29_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO3_30 ���Ź��ܶ���
 * @{
 */
#define PIO3_30_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_30_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO3_30_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO3_30_EMC_D30      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D30     */
#define PIO3_30_RTS1         AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief UART1 RTS    */
#define PIO3_30_MAT1_1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT1.1       */
/** @} */

/**
 * \name PIO3_30 ����ģʽ����
 * @{
 */
#define PIO3_30_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_30_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_30_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_30_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_30 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_30_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_30_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_30 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_30_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_30_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_30 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_30_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_30_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_30 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_30_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_30_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO3_31 ���Ź��ܶ���
 * @{
 */
#define PIO3_31_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO3_31_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦�� */
#define PIO3_31_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO3_31_EMC_D31      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC D31     */
#define PIO3_31_MAT1_2       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT1.2       */
/** @} */

/**
 * \name PIO3_31 ����ģʽ����
 * @{
 */
#define PIO3_31_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO3_31_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO3_31_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO3_31_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO3_31 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO3_31_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO3_31_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO3_31 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO3_31_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO3_31_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO3_31 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO3_31_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO3_31_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO3_31 ��©ʹ�ܶ���
 * @{
 */
#define PIO3_31_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO3_31_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_0 ���Ź��ܶ���
 * @{
 */
#define PIO4_0_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_0_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_0_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_0_EMC_A0      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A0 */

/** @} */

/**
 * \name PIO4_0 ����ģʽ����
 * @{
 */
#define PIO4_0_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_0_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_0_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_0_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_0 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_0_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_0_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_0 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_0_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_0_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_0 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_0_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_0_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_0 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_0_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_0_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_1 ���Ź��ܶ���
 * @{
 */
#define PIO4_1_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_1_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_1_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_1_EMC_A1      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A1 */

/** @} */

/**
 * \name PIO4_1 ����ģʽ����
 * @{
 */
#define PIO4_1_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_1_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_1_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_1_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_1 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_1_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_1_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_1 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_1_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_1_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_1 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_1_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_1_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_1 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_1_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_1_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO4_2 ���Ź��ܶ���
 * @{
 */
#define PIO4_2_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_2_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_2_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_2_EMC_A2      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A2 */

/** @} */

/**
 * \name PIO4_2 ����ģʽ����
 * @{
 */
#define PIO4_2_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_2_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_2_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_2_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_2 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_2_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_2_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_2 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_2_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_2_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_2 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_2_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_2_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_2 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_2_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_2_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_3 ���Ź��ܶ���
 * @{
 */
#define PIO4_3_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_3_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_3_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_3_EMC_A3      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A3 */

/** @} */

/**
 * \name PIO4_3 ����ģʽ����
 * @{
 */
#define PIO4_3_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_3_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_3_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_3_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_3 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_3_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_3_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_3 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_3_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_3_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_3 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_3_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_3_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_3 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_3_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_3_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_4 ���Ź��ܶ���
 * @{
 */
#define PIO4_4_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_4_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_4_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_4_EMC_A4      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A4 */

/** @} */

/**
 * \name PIO4_4 ����ģʽ����
 * @{
 */
#define PIO4_4_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_4_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_4_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_4_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_4 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_4_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_4_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_4 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_4_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_4_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_4 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_4_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_4_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_4 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_4_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_4_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_5 ���Ź��ܶ���
 * @{
 */
#define PIO4_5_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_5_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_5_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_5_EMC_A5      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A5 */

/** @} */

/**
 * \name PIO4_5 ����ģʽ����
 * @{
 */
#define PIO4_5_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_5_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_5_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_5_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_5 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_5_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_5_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_5 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_5_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_5_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_5 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_5_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_5_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_5 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_5_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_5_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO4_6 ���Ź��ܶ���
 * @{
 */
#define PIO4_6_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_6_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_6_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_6_EMC_A6      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A6 */

/** @} */

/**
 * \name PIO4_6 ����ģʽ����
 * @{
 */
#define PIO4_6_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_6_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_6_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_6_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_6 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_6_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_6_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_6 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_6_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_6_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_6 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_6_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_6_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_6 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_6_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_6_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_7 ���Ź��ܶ���
 * @{
 */
#define PIO4_7_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_7_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_7_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_7_EMC_A7      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A7 */

/** @} */

/**
 * \name PIO4_7 ����ģʽ����
 * @{
 */
#define PIO4_7_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_7_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_7_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_7_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_7 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_7_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_7_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_7 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_7_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_7_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_7 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_7_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_7_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_7 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_7_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_7_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_8 ���Ź��ܶ���
 * @{
 */
#define PIO4_8_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_8_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_8_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_8_EMC_A8      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A8 */

/** @} */

/**
 * \name PIO4_8 ����ģʽ����
 * @{
 */
#define PIO4_8_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_8_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_8_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_8_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_8 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_8_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_8_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_8 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_8_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_8_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_8 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_8_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_8_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */


/**
 * \name PIO4_8 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_8_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_8_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_9 ���Ź��ܶ���
 * @{
 */
#define PIO4_9_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_9_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_9_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_9_EMC_A9      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A9 */

/** @} */

/**
 * \name PIO4_9 ����ģʽ����
 * @{
 */
#define PIO4_9_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_9_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_9_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_9_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_9 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_9_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_9_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_9 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_9_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_9_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_9 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_9_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_9_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_9 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_9_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_9_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_10 ���Ź��ܶ���
 * @{
 */
#define PIO4_10_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_10_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_10_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_10_EMC_A10     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A10 */

/** @} */

/**
 * \name PIO4_10 ����ģʽ����
 * @{
 */
#define PIO4_10_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_10_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_10_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_10_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_10 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_10_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_10_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_10 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_10_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_10_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_10 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_10_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_10_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_10 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_10_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_10_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_11 ���Ź��ܶ���
 * @{
 */
#define PIO4_11_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_11_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_11_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_11_EMC_A11     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A11 */

/** @} */

/**
 * \name PIO4_11 ����ģʽ����
 * @{
 */
#define PIO4_11_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_11_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_11_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_11_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_11 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_11_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_11_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_11 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_11_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_11_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_11 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_11_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_11_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_11 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_11_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_11_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/
/**
 * \name PIO4_12 ���Ź��ܶ���
 * @{
 */
#define PIO4_12_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_12_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_12_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_12_EMC_A12     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A12 */

/** @} */

/**
 * \name PIO4_12 ����ģʽ����
 * @{
 */
#define PIO4_12_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_12_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_12_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_12_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_12 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_12_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_12_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_12 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_12_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_12_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_12 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_12_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_12_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_12 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_12_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_12_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_13 ���Ź��ܶ���
 * @{
 */
#define PIO4_13_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_13_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_13_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_13_EMC_A13     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A13 */

/** @} */

/**
 * \name PIO4_13 ����ģʽ����
 * @{
 */
#define PIO4_13_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_13_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_13_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_13_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_13 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_13_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_13_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_13 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_13_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_13_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_13 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_13_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_13_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_13 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_13_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_13_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_14 ���Ź��ܶ���
 * @{
 */
#define PIO4_14_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_14_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_14_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_14_EMC_A14     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A14 */

/** @} */

/**
 * \name PIO4_14 ����ģʽ����
 * @{
 */
#define PIO4_14_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_14_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_14_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_14_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_14 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_14_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_14_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_14 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_14_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_14_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_14 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_14_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_14_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_14 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_14_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_14_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO4_15 ���Ź��ܶ���
 * @{
 */
#define PIO4_15_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_15_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_15_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_15_EMC_A15     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A15 */

/** @} */

/**
 * \name PIO4_15 ����ģʽ����
 * @{
 */
#define PIO4_15_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_15_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_15_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_15_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_15 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_15_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_15_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_15 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_15_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_15_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_15 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_15_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_15_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_15 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_15_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_15_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_16 ���Ź��ܶ���
 * @{
 */
#define PIO4_16_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_16_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_16_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_16_EMC_A16     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A16 */

/** @} */

/**
 * \name PIO4_16 ����ģʽ����
 * @{
 */
#define PIO4_16_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_16_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_16_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_16_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_16 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_16_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_16_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_16 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_16_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_16_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_16 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_16_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_16_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_16 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_16_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_16_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/
/**
 * \name PIO4_17 ���Ź��ܶ���
 * @{
 */
#define PIO4_17_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_17_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_17_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_17_EMC_A17     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A17 */

/** @} */

/**
 * \name PIO4_17 ����ģʽ����
 * @{
 */
#define PIO4_17_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_17_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_17_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_17_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_17 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_17_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_17_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_17 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_17_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_17_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_17 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_17_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_17_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_17 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_17_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_17_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_18 ���Ź��ܶ���
 * @{
 */
#define PIO4_18_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_18_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_18_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_18_EMC_A18     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A18 */

/** @} */

/**
 * \name PIO4_18 ����ģʽ����
 * @{
 */
#define PIO4_18_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_18_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_18_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_18_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_18 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_18_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_18_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_18 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_18_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_18_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_18 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_18_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_18_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_18 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_18_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_18_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_19 ���Ź��ܶ���
 * @{
 */
#define PIO4_19_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_19_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_19_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_19_EMC_A19     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A19 */

/** @} */

/**
 * \name PIO4_19 ����ģʽ����
 * @{
 */
#define PIO4_19_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_19_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_19_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_19_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_19 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_19_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_19_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_19 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_19_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_19_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_19 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_19_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_19_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_19 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_19_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_19_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_20 ���Ź��ܶ���
 * @{
 */
#define PIO4_20_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_20_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_20_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_20_EMC_A20     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A20 */
#define PIO4_20_SDA2        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2C2 SDA */
#define PIO4_20_SCK1        AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SSP1 SCK */
/** @} */

/**
 * \name PIO4_20 ����ģʽ����
 * @{
 */
#define PIO4_20_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_20_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_20_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_20_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_20 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_20_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_20_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_20 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_20_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_20_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_20 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_20_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_20_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_20 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_20_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_20_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_21 ���Ź��ܶ���
 * @{
 */
#define PIO4_21_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_21_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_21_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_21_EMC_A21     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A21 */
#define PIO4_21_SCL2        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief I2C2 SCL */
#define PIO4_21_SSEL1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SSP1 SSEL */
/** @} */

/**
 * \name PIO4_21 ����ģʽ����
 * @{
 */
#define PIO4_21_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_21_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_21_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_21_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_21 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_21_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_21_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_21 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_21_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_21_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_21 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_21_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_21_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_21 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_21_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_21_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_22 ���Ź��ܶ���
 * @{
 */
#define PIO4_22_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_22_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_22_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_22_EMC_A22     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A22 */
#define PIO4_22_TXD2        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief UART2 TXD */
#define PIO4_22_MISO1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SSP1 MISO */
/** @} */

/**
 * \name PIO4_22 ����ģʽ����
 * @{
 */
#define PIO4_22_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_22_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_22_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_22_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_22 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_22_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_22_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_22 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_22_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_22_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_22 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_22_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_22_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_22 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_22_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_22_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_23 ���Ź��ܶ���
 * @{
 */
#define PIO4_23_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_23_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_23_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_23_EMC_A23     AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A23 */
#define PIO4_23_RXD2        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief UART2 RXD */
#define PIO4_23_MOSI1       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief SSP1 MOSI */
/** @} */

/**
 * \name PIO4_23 ����ģʽ����
 * @{
 */
#define PIO4_23_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_23_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_23_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_23_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_23 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_23_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_23_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_23 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_23_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_23_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_23 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_23_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_23_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_23 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_23_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_23_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_24 ���Ź��ܶ���
 * @{
 */
#define PIO4_24_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_24_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_24_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_24_EMC_OE      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC OE */
/** @} */

/**
 * \name PIO4_24 ����ģʽ����
 * @{
 */
#define PIO4_24_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_24_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_24_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_24_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_24 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_24_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_24_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_24 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_24_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_24_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_24 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_24_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_24_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_24 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_24_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_24_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_25 ���Ź��ܶ���
 * @{
 */
#define PIO4_25_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_25_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_25_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_25_EMC_WE      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC WE */
/** @} */

/**
 * \name PIO4_25 ����ģʽ����
 * @{
 */
#define PIO4_25_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_25_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_25_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_25_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_25 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_25_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_25_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_25 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_25_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_25_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_25 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_25_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_25_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_25 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_25_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_25_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */
/******************************************************************************/

/**
 * \name PIO4_26 ���Ź��ܶ���
 * @{
 */
#define PIO4_26_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_26_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_26_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_26_EMC_BLS0    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC BLS0 */
/** @} */

/**
 * \name PIO4_26 ����ģʽ����
 * @{
 */
#define PIO4_26_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_26_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_26_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_26_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_26 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_26_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_26_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_26 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_26_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_26_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_26 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_26_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_26_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_26 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_26_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_26_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_27 ���Ź��ܶ���
 * @{
 */
#define PIO4_27_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_27_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_27_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_27_EMC_BLS1    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC BLS1 */
/** @} */

/**
 * \name PIO4_27 ����ģʽ����
 * @{
 */
#define PIO4_27_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_27_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_27_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_27_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_27 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_27_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_27_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_27 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_27_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_27_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_27 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_27_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_27_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_27 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_27_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_27_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */


/******************************************************************************/

/**
 * \name PIO4_28 ���Ź��ܶ���
 * @{
 */
#define PIO4_28_GPIO        AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_28_INPUT       AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_28_OUTPUT      AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_28_EMC_BLS2    AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC BLS2  */
#define PIO4_28_TXD3        AMDR_GPIO_FUNCBITS_CODE(0x02)    /**< \brief TXD3      */
#define PIO4_28_MAT2_0      AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief MAT2.0    */
#define PIO4_28_LCD_VD6     AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief LCD VD[6] */
#define PIO4_28_LCD_VD10    AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[10]*/
#define PIO4_28_LCD_VD2     AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[2] */
/** @} */

/**
 * \name PIO4_28 ����ģʽ����
 * @{
 */
#define PIO4_28_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_28_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_28_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_28_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO4_28 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_28_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_28_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_28 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_28_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_28_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_28 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_28_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_28_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */


/**
 * \name PIO4_28 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_28_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_28_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_29 ���Ź��ܶ���
 * @{
 */
#define PIO4_29_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_29_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_29_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_29_EMC_BLS3    AMDR_GPIO_FUNCBITS_CODE(0x01)     /**< \brief EMC BLS3  */
#define PIO4_29_RXD3        AMDR_GPIO_FUNCBITS_CODE(0x02)     /**< \brief RXD3 */
#define PIO4_29_MAT2_1      AMDR_GPIO_FUNCBITS_CODE(0x03)     /**< \brief MAT2.1 */
#define PIO4_29_SCL2        AMDR_GPIO_FUNCBITS_CODE(0x04)     /**< \brief I2C2 SCL */
#define PIO4_29_LCD_VD7     AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief LCD VD[7] */
#define PIO4_29_LCD_VD11    AMDR_GPIO_FUNCBITS_CODE(0x06)    /**< \brief LCD VD[11]*/
#define PIO4_29_LCD_VD3     AMDR_GPIO_FUNCBITS_CODE(0x07)    /**< \brief LCD VD[3] */
/** @} */

/**
 * \name PIO4_29 ����ģʽ����
 * @{
 */
#define PIO4_29_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_29_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_29_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_29_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */


/**
 * \name PIO4_29 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_29_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_29_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_29 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_29_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_29_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_29 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_29_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_29_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_29 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_29_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_29_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_30 ���Ź��ܶ���
 * @{
 */
#define PIO4_30_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_30_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_30_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_30_EMC_CS0      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CS0     */
/** @} */

/**
 * \name PIO4_30 ����ģʽ����
 * @{
 */
#define PIO4_30_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_30_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_30_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_30_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_30 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_30_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_30_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_30 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_30_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_30_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_30 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_30_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_30_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_30 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_30_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_30_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO4_31 ���Ź��ܶ���
 * @{
 */
#define PIO4_31_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO4_31_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO4_31_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO4_31_EMC_CS1      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC CS1    */
/** @} */

/**
 * \name PIO4_31 ����ģʽ����
 * @{
 */
#define PIO4_31_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO4_31_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO4_31_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO4_31_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO4_31 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO4_31_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO4_31_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO4_31 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO4_31_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO4_31_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO4_31 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO4_31_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO4_31_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO4_31 ��©ʹ�ܶ���
 * @{
 */
#define PIO4_31_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO4_31_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO5_0 ���Ź��ܶ���
 * @{
 */
#define PIO5_0_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO5_0_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO5_0_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO5_0_EMC_A24      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A24    */
#define PIO5_0_MAT2_2       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T2 MAT2    */
/** @} */

/**
 * \name PIO5_0 ����ģʽ����
 * @{
 */
#define PIO5_0_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO5_0_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO5_0_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO5_0_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO5_0 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO5_0_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO5_0_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO5_0 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO5_0_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO5_0_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO5_0 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO5_0_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO5_0_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO5_0 ��©ʹ�ܶ���
 * @{
 */
#define PIO5_0_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO5_0_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO5_1 ���Ź��ܶ���
 * @{
 */
#define PIO5_1_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO5_1_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO5_1_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO5_1_EMC_A25      AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief EMC A25    */
#define PIO5_1_MAT2_3       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T2 MAT2    */
/** @} */

/**
 * \name PIO5_1 ����ģʽ����
 * @{
 */
#define PIO5_1_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO5_1_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO5_1_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO5_1_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO5_1 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO5_1_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO5_1_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO5_1 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO5_1_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO5_1_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO5_1 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO5_1_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO5_1_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO5_1 ��©ʹ�ܶ���
 * @{
 */
#define PIO5_1_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO5_1_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/******************************************************************************/

/**
 * \name PIO5_2 ���Ź��ܶ���
 * @{
 */
#define PIO5_2_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO5_2_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO5_2_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO5_2_MAT3_2       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T3 MAT2    */
#define PIO5_2_SDA0         AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief I2C0 SDA   */
/** @} */

/**
 * \name PIO5_2 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO5_2_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO5_2_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO5_2 ���뷴�����ʹ�ܶ���
 * @{
 */

/**< \brief I2C 50nsë���˲�����ת����������ʧ��     */
#define PIO5_2_HS_DISABLE   AMDR_GPIO_HSENBIT_DISABLE
/**< \brief I2C 50nsë���˲�����ת����������ʹ�� (Ĭ��)    */
#define PIO5_2_HS_ENABLE    AMDR_GPIO_HSENBIT_ENABLE
/** @} */

/**
 * \name PIO5_2 �ܽŹ�����������ƶ���
 * @{
 */

/** \brief ������������Ϊ4mA��Ĭ�ϣ�  */
#define PIO5_2_HIDRIVE_4MA   AMDR_GPIO_HIDRIVEENBIT_4MA
/** \brief ������������Ϊ20mA��Ĭ�ϣ�                 */
#define PIO5_2_HIDRIVE_20MA    AMDR_GPIO_HIDRIVEENBIT_20MA
/** @} */

/******************************************************************************/

/**
 * \name PIO5_3 ���Ź��ܶ���
 * @{
 */
#define PIO5_3_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO5_3_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO5_3_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO5_3_RXD4         AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief UART4 RXD  */
#define PIO5_3_SCL0         AMDR_GPIO_FUNCBITS_CODE(0x05)    /**< \brief I2C0 SCL   */
/** @} */

/**
 * \name PIO5_3 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO5_3_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO5_3_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO5_3 ���뷴�����ʹ�ܶ���
 * @{
 */

/**< \brief I2C 50nsë���˲�����ת����������ʧ��     */
#define PIO5_3_HS_DISABLE   AMDR_GPIO_HSENBIT_DISABLE
/**< \brief I2C 50nsë���˲�����ת����������ʹ�� (Ĭ��)    */
#define PIO5_3_HS_ENABLE    AMDR_GPIO_HSENBIT_ENABLE
/** @} */

/**
 * \name PIO5_3 �ܽŹ�����������ƶ���
 * @{
 */

/** \brief ������������Ϊ4mA��Ĭ�ϣ�  */
#define PIO5_3_HIDRIVE_4MA   AMDR_GPIO_HIDRIVEENBIT_4MA
/** \brief ������������Ϊ20mA��Ĭ�ϣ�                 */
#define PIO5_3_HIDRIVE_20MA    AMDR_GPIO_HIDRIVEENBIT_20MA
/** @} */

/******************************************************************************/

/**
 * \name PIO5_4 ���Ź��ܶ���
 * @{
 */
#define PIO5_4_GPIO         AMDR_GPIO_FUNCBITS_CODE(0x00)    /**< \brief GPIO���� (Ĭ��) */
#define PIO5_4_INPUT        AMDR_GPIO_FUNC_INPUT(0x00)       /**< \brief GPIO���빦��*/
#define PIO5_4_OUTPUT       AMDR_GPIO_FUNC_OUTPUT(0x00)      /**< \brief GPIO������� */
#define PIO5_4_OE0          AMDR_GPIO_FUNCBITS_CODE(0x01)    /**< \brief UART0 OE   */
#define PIO5_4_MAT3_3       AMDR_GPIO_FUNCBITS_CODE(0x03)    /**< \brief T3 MAT3    */
#define PIO5_4_TXD4         AMDR_GPIO_FUNCBITS_CODE(0x04)    /**< \brief UART4 TXD  */
/** @} */

/**
 * \name PIO5_4 ����ģʽ����
 * @{
 */
#define PIO5_4_PULLUP      AMDR_GPIO_PULLUP         /**< \brief �ڲ����� (Ĭ��)  */
#define PIO5_4_REPEATER    AMDR_GPIO_REPEATER       /**< \brief �м�ģʽ */
#define PIO5_4_FLOAT       AMDR_GPIO_FLOAT          /**< \brief ����(�Ȳ�����Ҳ������) */
#define PIO5_4_PULLDOWN    AMDR_GPIO_PULLDOWN       /**< \brief �ڲ����� */
/** @} */

/**
 * \name PIO5_4 ����ģʽʹ�ܶ���
 * @{
 */
#define PIO5_4_HYS_DISABLE   AMDR_GPIO_HYSENBIT_DISABLE    /**< \brief ���ͽ���               */
#define PIO5_4_HYS_ENABLE    AMDR_GPIO_HYSENBIT_ENABLE     /**< \brief ����ʹ�� (Ĭ��)*/
/** @} */

/**
 * \name PIO5_4 ���뷴�����ʹ�ܶ���
 * @{
 */
#define PIO5_4_INVERT_DISABLE   AMDR_GPIO_INVERTENBIT_DISABLE    /**< \brief ����δ����Ĭ�ϣ�     */
#define PIO5_4_INVERT_ENABLE    AMDR_GPIO_INVERTENBIT_ENABLE     /**< \brief ���뷴��ʹ��                   */
/** @} */

/**
 * \name PIO5_4 ������ת�����ʿ���ʹ�ܶ���
 * @{
 */

/** \brief ����ģʽ�£����ת�����ʿ��Ʊ�����   */
#define PIO5_4_SLEW_DISABLE   AMDR_GPIO_SLEWENBIT_DISABLE
/** \brief ��׼ģʽ�£����ת�����ʿ���ʹ�ܣ�Ĭ�ϣ�                  */
#define PIO5_4_SLEW_ENABLE    AMDR_GPIO_SLEWENBIT_ENABLE
/** @} */

/**
 * \name PIO5_4 ��©ʹ�ܶ���
 * @{
 */
#define PIO5_4_OD_DISABLE   AMDR_GPIO_ODENBIT_DISABLE    /**< \brief ��©���� (Ĭ��) */
#define PIO5_4_OD_ENABLE    AMDR_GPIO_ODENBIT_ENABLE     /**< \brief ��©ʹ�� */
/** @} */

/**
 * @} amhw_if_pin
 */

#ifdef __cplusplus
}
#endif

#endif/* __LPC177X_8X_PIN_H */

/* end of file */
