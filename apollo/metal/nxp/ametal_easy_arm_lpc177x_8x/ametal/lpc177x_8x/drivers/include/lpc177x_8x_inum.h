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
 * \brief LPC177X_8X �жϺŶ���
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-02 cod, first implementation.
 * \endinternal
 */


#ifndef __LPC177X_8X_INUM_H
#define __LPC177X_8X_INUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc177x_8x.h"

/** 
 * \addtogroup amhw_if_inum
 * \copydoc lpc177x_8x_inum.h
 * @{
 */

/**
 * \name LPC177x_8x CPU �жϺ�
 * @{
 */

#define INUM_WWDT                0    /**< \brief ���ڿ��Ź��жϺ�        */
#define INUM_TIMER0              1    /**< \brief Timer0�жϺ�        */
#define INUM_TIMER1              2    /**< \brief Timer1�жϺ�        */
#define INUM_TIMER2              3    /**< \brief Timer2�жϺ�        */
#define INUM_TIMER3              4    /**< \brief Timer3�жϺ�        */
#define INUM_UART0               5    /**< \brief UART0�жϺ�         */
#define INUM_UART1               6    /**< \brief UART1�жϺ�         */
#define INUM_UART2               7    /**< \brief UART2�жϺ�         */
#define INUM_UART3               8    /**< \brief UART3�жϺ�         */
#define INUM_PWM1                9    /**< \brief PWM1�жϺ�          */
#define INUM_I2C0                10   /**< \brief I2C0�жϺ�          */
#define INUM_I2C1                11   /**< \brief I2C1�жϺ�          */
#define INUM_I2C2                12   /**< \brief I2C2�жϺ�          */
#define INUM_SSP0                14   /**< \brief SSP0�жϺ�          */
#define INUM_SSP1                15   /**< \brief SSP1�жϺ�          */
#define INUM_PLL0                16   /**< \brief PLL0�жϺ�          */
#define INUM_RTC                 17   /**< \brief RTC�жϺ�           */
#define INUM_EINT0               18   /**< \brief EINT0�жϺ�         */
#define INUM_EINT1               19   /**< \brief EINT1�жϺ�         */
#define INUM_EINT2               20   /**< \brief EINT2�жϺ�         */
#define INUM_EINT3               21   /**< \brief EINT3�жϺ�         */
#define INUM_ADC                 22   /**< \brief ADC�жϺ�           */
#define INUM_BOD                 23   /**< \brief �������жϺ�       */
#define INUM_USB                 24   /**< \brief USB�жϺ�           */
#define INUM_CAN                 25   /**< \brief CAN�жϺ�           */
#define INUM_GPDMA               26   /**< \brief GPDMA�жϺ�         */
#define INUM_I2S                 27   /**< \brief I2S�жϺ�           */
#define INUM_ENET                28   /**< \brief Ethernet �жϺ�     */
#define INUM_SDC                 29   /**< \brief SDC �жϺ�          */
#define INUM_MCPWM               30   /**< \brief MCPWM �жϺ�        */
#define INUM_QEI                 31   /**< \brief QEI �жϺ�          */
#define INUM_PLL1                32   /**< \brief PLL1 �жϺ�         */
#define INUM_USB_ACT             33   /**< \brief USB Activity �жϺ� */
#define INUM_CAN_ACT             34   /**< \brief CAN Activity �жϺ� */
#define INUM_UART4               35   /**< \brief UART4�жϺ�         */
#define INUM_SSP2                36   /**< \brief SSP2�жϺ�            */
#define INUM_LCD                 37   /**< \brief LCD�жϺ�               */
#define INUM_GPIO                38   /**< \brief GPIO�жϺ�            */
#define INUM_PWM0                39   /**< \brief PWM0�жϺ�             */
#define INUM_EEPROM              40   /**< \brief EEPROM�жϺ�        */
/** @} */

/** \brief ���ж���Ŀ  */
#define INUM_INTERNAL_COUNT     (INUM_EEPROM - INUM_WWDT + 1)

/** \brief ����жϺ�  */
#define INUM_INTERNAL_MAX        INUM_EEPROM

/** \brief ��С�жϺ�  */
#define INUM_INTERNAL_MIN        INUM_WWDT

/**
 * \name lpc17xx �����жϺ�
 * @{
 */
 
#define IMUN_GPIO0_START          35    /**< \brief GPIO0�����жϵ���ʼ��� */
#define IMUN_GPIO1_START          67    /**< \brief GPIO1�����жϵ���ʼ��� */
#define IMUN_GPIO2_START          99    /**< \brief GPIO2�����жϵ���ʼ��� */
#define IMUN_GPIO3_START          131   /**< \brief GPIO3�����жϵ���ʼ��� */
#define IMUN_GPIO4_START          163   /**< \brief GPIO4�����жϵ���ʼ��� */
#define IMUN_GPIO5_START          195   /**< \brief GPIO5�����жϵ���ʼ��� */

#define INUM_PIO0_0      (IMUN_GPIO0_START + 0)    /**< \brief PIO0_0�жϺ�  */
#define INUM_PIO0_1      (IMUN_GPIO0_START + 1)    /**< \brief PIO0_1�жϺ�  */
#define INUM_PIO0_2      (IMUN_GPIO0_START + 2)    /**< \brief PIO0_2�жϺ�  */
#define INUM_PIO0_3      (IMUN_GPIO0_START + 3)    /**< \brief PIO0_3�жϺ�  */
#define INUM_PIO0_4      (IMUN_GPIO0_START + 4)    /**< \brief PIO0_4�жϺ�  */
#define INUM_PIO0_5      (IMUN_GPIO0_START + 5)    /**< \brief PIO0_5�жϺ�  */
#define INUM_PIO0_6      (IMUN_GPIO0_START + 6)    /**< \brief PIO0_6�жϺ�  */
#define INUM_PIO0_7      (IMUN_GPIO0_START + 7)    /**< \brief PIO0_7�жϺ�  */
#define INUM_PIO0_8      (IMUN_GPIO0_START + 8)    /**< \brief PIO0_8�жϺ�  */
#define INUM_PIO0_9      (IMUN_GPIO0_START + 9)    /**< \brief PIO0_9�жϺ�  */
#define INUM_PIO0_10     (IMUN_GPIO0_START + 10)   /**< \brief PIO0_10�жϺ� */
#define INUM_PIO0_11     (IMUN_GPIO0_START + 11)   /**< \brief PIO0_11�жϺ� */
#define INUM_PIO0_12     (IMUN_GPIO0_START + 12)   /**< \brief PIO0_12�жϺ� */
#define INUM_PIO0_13     (IMUN_GPIO0_START + 13)   /**< \brief PIO0_13�жϺ� */
#define INUM_PIO0_14     (IMUN_GPIO0_START + 14)   /**< \brief PIO0_14�жϺ� */
#define INUM_PIO0_15     (IMUN_GPIO0_START + 15)   /**< \brief PIO0_15�жϺ� */
#define INUM_PIO0_16     (IMUN_GPIO0_START + 16)   /**< \brief PIO0_16�жϺ� */
#define INUM_PIO0_17     (IMUN_GPIO0_START + 17)   /**< \brief PIO0_17�жϺ� */
#define INUM_PIO0_18     (IMUN_GPIO0_START + 18)   /**< \brief PIO0_18�жϺ� */
#define INUM_PIO0_19     (IMUN_GPIO0_START + 19)   /**< \brief PIO0_19�жϺ� */
#define INUM_PIO0_20     (IMUN_GPIO0_START + 20)   /**< \brief PIO0_20�жϺ� */
#define INUM_PIO0_21     (IMUN_GPIO0_START + 21)   /**< \brief PIO0_21�жϺ� */
#define INUM_PIO0_22     (IMUN_GPIO0_START + 22)   /**< \brief PIO0_22�жϺ� */
#define INUM_PIO0_23     (IMUN_GPIO0_START + 23)   /**< \brief PIO0_23�жϺ� */
#define INUM_PIO0_24     (IMUN_GPIO0_START + 24)   /**< \brief PIO0_24�жϺ� */
#define INUM_PIO0_25     (IMUN_GPIO0_START + 25)   /**< \brief PIO0_25�жϺ� */
#define INUM_PIO0_26     (IMUN_GPIO0_START + 26)   /**< \brief PIO0_26�жϺ� */
#define INUM_PIO0_27     (IMUN_GPIO0_START + 27)   /**< \brief PIO0_27�жϺ� */
#define INUM_PIO0_28     (IMUN_GPIO0_START + 28)   /**< \brief PIO0_28�жϺ� */
#define INUM_PIO0_29     (IMUN_GPIO0_START + 29)   /**< \brief PIO0_29�жϺ� */
#define INUM_PIO0_30     (IMUN_GPIO0_START + 30)   /**< \brief PIO0_30�жϺ� */
#define INUM_PIO0_31     (IMUN_GPIO0_START + 31)   /**< \brief PIO0_31�жϺ� */


#define INUM_PIO1_0      (IMUN_GPIO1_START + 0)    /**< \brief PIO1_0�жϺ�  */
#define INUM_PIO1_1      (IMUN_GPIO1_START + 1)    /**< \brief PIO1_1�жϺ�  */
#define INUM_PIO1_2      (IMUN_GPIO1_START + 2)    /**< \brief PIO1_2�жϺ�  */
#define INUM_PIO1_3      (IMUN_GPIO1_START + 3)    /**< \brief PIO1_3�жϺ�  */
#define INUM_PIO1_4      (IMUN_GPIO1_START + 4)    /**< \brief PIO1_4�жϺ�  */
#define INUM_PIO1_5      (IMUN_GPIO1_START + 5)    /**< \brief PIO1_5�жϺ�  */
#define INUM_PIO1_6      (IMUN_GPIO1_START + 6)    /**< \brief PIO1_6�жϺ�  */
#define INUM_PIO1_7      (IMUN_GPIO1_START + 7)    /**< \brief PIO1_7�жϺ�  */
#define INUM_PIO1_8      (IMUN_GPIO1_START + 8)    /**< \brief PIO1_8�жϺ�  */
#define INUM_PIO1_9      (IMUN_GPIO1_START + 9)    /**< \brief PIO1_9�жϺ�  */
#define INUM_PIO1_10     (IMUN_GPIO1_START + 10)   /**< \brief PIO1_10�жϺ� */
#define INUM_PIO1_11     (IMUN_GPIO1_START + 11)   /**< \brief PIO1_11�жϺ� */
#define INUM_PIO1_12     (IMUN_GPIO1_START + 12)   /**< \brief PIO1_12�жϺ� */
#define INUM_PIO1_13     (IMUN_GPIO1_START + 13)   /**< \brief PIO1_13�жϺ� */
#define INUM_PIO1_14     (IMUN_GPIO1_START + 14)   /**< \brief PIO1_14�жϺ� */
#define INUM_PIO1_15     (IMUN_GPIO1_START + 15)   /**< \brief PIO1_15�жϺ� */
#define INUM_PIO1_16     (IMUN_GPIO1_START + 16)   /**< \brief PIO1_16�жϺ� */
#define INUM_PIO1_17     (IMUN_GPIO1_START + 17)   /**< \brief PIO1_17�жϺ� */
#define INUM_PIO1_18     (IMUN_GPIO1_START + 18)   /**< \brief PIO1_18�жϺ� */
#define INUM_PIO1_19     (IMUN_GPIO1_START + 19)   /**< \brief PIO1_19�жϺ� */
#define INUM_PIO1_20     (IMUN_GPIO1_START + 20)   /**< \brief PIO1_20�жϺ� */
#define INUM_PIO1_21     (IMUN_GPIO1_START + 21)   /**< \brief PIO1_21�жϺ� */
#define INUM_PIO1_22     (IMUN_GPIO1_START + 22)   /**< \brief PIO1_22�жϺ� */
#define INUM_PIO1_23     (IMUN_GPIO1_START + 23)   /**< \brief PIO1_23�жϺ� */
#define INUM_PIO1_24     (IMUN_GPIO1_START + 24)   /**< \brief PIO1_24�жϺ� */
#define INUM_PIO1_25     (IMUN_GPIO1_START + 25)   /**< \brief PIO1_25�жϺ� */
#define INUM_PIO1_26     (IMUN_GPIO1_START + 26)   /**< \brief PIO1_26�жϺ� */
#define INUM_PIO1_27     (IMUN_GPIO1_START + 27)   /**< \brief PIO1_27�жϺ� */
#define INUM_PIO1_28     (IMUN_GPIO1_START + 28)   /**< \brief PIO1_28�жϺ� */
#define INUM_PIO1_29     (IMUN_GPIO1_START + 29)   /**< \brief PIO1_29�жϺ� */
#define INUM_PIO1_30     (IMUN_GPIO1_START + 30)   /**< \brief PIO1_30�жϺ� */
#define INUM_PIO1_31     (IMUN_GPIO1_START + 31)   /**< \brief PIO1_31�жϺ� */


#define INUM_PIO2_0      (IMUN_GPIO2_START + 0)    /**< \brief PIO2_0�жϺ�  */
#define INUM_PIO2_1      (IMUN_GPIO2_START + 1)    /**< \brief PIO2_1�жϺ�  */
#define INUM_PIO2_2      (IMUN_GPIO2_START + 2)    /**< \brief PIO2_2�жϺ�  */
#define INUM_PIO2_3      (IMUN_GPIO2_START + 3)    /**< \brief PIO2_3�жϺ�  */
#define INUM_PIO2_4      (IMUN_GPIO2_START + 4)    /**< \brief PIO2_4�жϺ�  */
#define INUM_PIO2_5      (IMUN_GPIO2_START + 5)    /**< \brief PIO2_5�жϺ�  */
#define INUM_PIO2_6      (IMUN_GPIO2_START + 6)    /**< \brief PIO2_6�жϺ�  */
#define INUM_PIO2_7      (IMUN_GPIO2_START + 7)    /**< \brief PIO2_7�жϺ�  */
#define INUM_PIO2_8      (IMUN_GPIO2_START + 8)    /**< \brief PIO2_8�жϺ�  */
#define INUM_PIO2_9      (IMUN_GPIO2_START + 9)    /**< \brief PIO2_9�жϺ�  */
#define INUM_PIO2_10     (IMUN_GPIO2_START + 10)   /**< \brief PIO2_10�жϺ� */
#define INUM_PIO2_11     (IMUN_GPIO2_START + 11)   /**< \brief PIO2_11�жϺ� */
#define INUM_PIO2_12     (IMUN_GPIO2_START + 12)   /**< \brief PIO2_12�жϺ� */
#define INUM_PIO2_13     (IMUN_GPIO2_START + 13)   /**< \brief PIO2_13�жϺ� */
#define INUM_PIO2_14     (IMUN_GPIO2_START + 14)   /**< \brief PIO2_14�жϺ� */
#define INUM_PIO2_15     (IMUN_GPIO2_START + 15)   /**< \brief PIO2_15�жϺ� */
#define INUM_PIO2_16     (IMUN_GPIO2_START + 16)   /**< \brief PIO2_16�жϺ� */
#define INUM_PIO2_17     (IMUN_GPIO2_START + 17)   /**< \brief PIO2_17�жϺ� */
#define INUM_PIO2_18     (IMUN_GPIO2_START + 18)   /**< \brief PIO2_18�жϺ� */
#define INUM_PIO2_19     (IMUN_GPIO2_START + 19)   /**< \brief PIO2_19�жϺ� */
#define INUM_PIO2_20     (IMUN_GPIO2_START + 20)   /**< \brief PIO2_20�жϺ� */
#define INUM_PIO2_21     (IMUN_GPIO2_START + 21)   /**< \brief PIO2_21�жϺ� */
#define INUM_PIO2_22     (IMUN_GPIO2_START + 22)   /**< \brief PIO2_22�жϺ� */
#define INUM_PIO2_23     (IMUN_GPIO2_START + 23)   /**< \brief PIO2_23�жϺ� */
#define INUM_PIO2_24     (IMUN_GPIO2_START + 24)   /**< \brief PIO2_24�жϺ� */
#define INUM_PIO2_25     (IMUN_GPIO2_START + 25)   /**< \brief PIO2_25�жϺ� */
#define INUM_PIO2_26     (IMUN_GPIO2_START + 26)   /**< \brief PIO2_26�жϺ� */
#define INUM_PIO2_27     (IMUN_GPIO2_START + 27)   /**< \brief PIO2_27�жϺ� */
#define INUM_PIO2_28     (IMUN_GPIO2_START + 28)   /**< \brief PIO2_28�жϺ� */
#define INUM_PIO2_29     (IMUN_GPIO2_START + 29)   /**< \brief PIO2_29�жϺ� */
#define INUM_PIO2_30     (IMUN_GPIO2_START + 30)   /**< \brief PIO2_30�жϺ� */
#define INUM_PIO2_31     (IMUN_GPIO2_START + 31)   /**< \brief PIO2_31�жϺ� */


#define INUM_PIO3_0      (IMUN_GPIO3_START + 0)    /**< \brief PIO3_0�жϺ�  */
#define INUM_PIO3_1      (IMUN_GPIO3_START + 1)    /**< \brief PIO3_1�жϺ�  */
#define INUM_PIO3_2      (IMUN_GPIO3_START + 2)    /**< \brief PIO3_2�жϺ�  */
#define INUM_PIO3_3      (IMUN_GPIO3_START + 3)    /**< \brief PIO3_3�жϺ�  */
#define INUM_PIO3_4      (IMUN_GPIO3_START + 4)    /**< \brief PIO3_4�жϺ�  */
#define INUM_PIO3_5      (IMUN_GPIO3_START + 5)    /**< \brief PIO3_5�жϺ�  */
#define INUM_PIO3_6      (IMUN_GPIO3_START + 6)    /**< \brief PIO3_6�жϺ�  */
#define INUM_PIO3_7      (IMUN_GPIO3_START + 7)    /**< \brief PIO3_7�жϺ�  */
#define INUM_PIO3_8      (IMUN_GPIO3_START + 8)    /**< \brief PIO3_8�жϺ�  */
#define INUM_PIO3_9      (IMUN_GPIO3_START + 9)    /**< \brief PIO3_9�жϺ�  */
#define INUM_PIO3_10     (IMUN_GPIO3_START + 10)   /**< \brief PIO3_10�жϺ� */
#define INUM_PIO3_11     (IMUN_GPIO3_START + 11)   /**< \brief PIO3_11�жϺ� */
#define INUM_PIO3_12     (IMUN_GPIO3_START + 12)   /**< \brief PIO3_12�жϺ� */
#define INUM_PIO3_13     (IMUN_GPIO3_START + 13)   /**< \brief PIO3_13�жϺ� */
#define INUM_PIO3_14     (IMUN_GPIO3_START + 14)   /**< \brief PIO3_14�жϺ� */
#define INUM_PIO3_15     (IMUN_GPIO3_START + 15)   /**< \brief PIO3_15�жϺ� */
#define INUM_PIO3_16     (IMUN_GPIO3_START + 16)   /**< \brief PIO3_16�жϺ� */
#define INUM_PIO3_17     (IMUN_GPIO3_START + 17)   /**< \brief PIO3_17�жϺ� */
#define INUM_PIO3_18     (IMUN_GPIO3_START + 18)   /**< \brief PIO3_18�жϺ� */
#define INUM_PIO3_19     (IMUN_GPIO3_START + 19)   /**< \brief PIO3_19�жϺ� */
#define INUM_PIO3_20     (IMUN_GPIO3_START + 20)   /**< \brief PIO3_20�жϺ� */
#define INUM_PIO3_21     (IMUN_GPIO3_START + 21)   /**< \brief PIO3_21�жϺ� */
#define INUM_PIO3_22     (IMUN_GPIO3_START + 22)   /**< \brief PIO3_22�жϺ� */
#define INUM_PIO3_23     (IMUN_GPIO3_START + 23)   /**< \brief PIO3_23�жϺ� */
#define INUM_PIO3_24     (IMUN_GPIO3_START + 24)   /**< \brief PIO3_24�жϺ� */
#define INUM_PIO3_25     (IMUN_GPIO3_START + 25)   /**< \brief PIO3_25�жϺ� */
#define INUM_PIO3_26     (IMUN_GPIO3_START + 26)   /**< \brief PIO3_26�жϺ� */
#define INUM_PIO3_27     (IMUN_GPIO3_START + 27)   /**< \brief PIO3_27�жϺ� */
#define INUM_PIO3_28     (IMUN_GPIO3_START + 28)   /**< \brief PIO3_28�жϺ� */
#define INUM_PIO3_29     (IMUN_GPIO3_START + 29)   /**< \brief PIO3_29�жϺ� */
#define INUM_PIO3_30     (IMUN_GPIO3_START + 30)   /**< \brief PIO3_30�жϺ� */
#define INUM_PIO3_31     (IMUN_GPIO3_START + 31)   /**< \brief PIO3_31�жϺ� */


#define INUM_PIO4_0      (IMUN_GPIO4_START + 0)    /**< \brief PIO4_0�жϺ�  */
#define INUM_PIO4_1      (IMUN_GPIO4_START + 1)    /**< \brief PIO4_1�жϺ�  */
#define INUM_PIO4_2      (IMUN_GPIO4_START + 2)    /**< \brief PIO4_2�жϺ�  */
#define INUM_PIO4_3      (IMUN_GPIO4_START + 3)    /**< \brief PIO4_3�жϺ�  */
#define INUM_PIO4_4      (IMUN_GPIO4_START + 4)    /**< \brief PIO4_4�жϺ�  */
#define INUM_PIO4_5      (IMUN_GPIO4_START + 5)    /**< \brief PIO4_5�жϺ�  */
#define INUM_PIO4_6      (IMUN_GPIO4_START + 6)    /**< \brief PIO4_6�жϺ�  */
#define INUM_PIO4_7      (IMUN_GPIO4_START + 7)    /**< \brief PIO4_7�жϺ�  */
#define INUM_PIO4_8      (IMUN_GPIO4_START + 8)    /**< \brief PIO4_8�жϺ�  */
#define INUM_PIO4_9      (IMUN_GPIO4_START + 9)    /**< \brief PIO4_9�жϺ�  */
#define INUM_PIO4_10     (IMUN_GPIO4_START + 10)   /**< \brief PIO4_10�жϺ� */
#define INUM_PIO4_11     (IMUN_GPIO4_START + 11)   /**< \brief PIO4_11�жϺ� */
#define INUM_PIO4_12     (IMUN_GPIO4_START + 12)   /**< \brief PIO4_12�жϺ� */
#define INUM_PIO4_13     (IMUN_GPIO4_START + 13)   /**< \brief PIO4_13�жϺ� */
#define INUM_PIO4_14     (IMUN_GPIO4_START + 14)   /**< \brief PIO4_14�жϺ� */
#define INUM_PIO4_15     (IMUN_GPIO4_START + 15)   /**< \brief PIO4_15�жϺ� */
#define INUM_PIO4_16     (IMUN_GPIO4_START + 16)   /**< \brief PIO4_16�жϺ� */
#define INUM_PIO4_17     (IMUN_GPIO4_START + 17)   /**< \brief PIO4_17�жϺ� */
#define INUM_PIO4_18     (IMUN_GPIO4_START + 18)   /**< \brief PIO4_18�жϺ� */
#define INUM_PIO4_19     (IMUN_GPIO4_START + 19)   /**< \brief PIO4_19�жϺ� */
#define INUM_PIO4_20     (IMUN_GPIO4_START + 20)   /**< \brief PIO4_20�жϺ� */
#define INUM_PIO4_21     (IMUN_GPIO4_START + 21)   /**< \brief PIO4_21�жϺ� */
#define INUM_PIO4_22     (IMUN_GPIO4_START + 22)   /**< \brief PIO4_22�жϺ� */
#define INUM_PIO4_23     (IMUN_GPIO4_START + 23)   /**< \brief PIO4_23�жϺ� */
#define INUM_PIO4_24     (IMUN_GPIO4_START + 24)   /**< \brief PIO4_24�жϺ� */
#define INUM_PIO4_25     (IMUN_GPIO4_START + 25)   /**< \brief PIO4_25�жϺ� */
#define INUM_PIO4_26     (IMUN_GPIO4_START + 26)   /**< \brief PIO4_26�жϺ� */
#define INUM_PIO4_27     (IMUN_GPIO4_START + 27)   /**< \brief PIO4_27�жϺ� */
#define INUM_PIO4_28     (IMUN_GPIO4_START + 28)   /**< \brief PIO4_28�жϺ� */
#define INUM_PIO4_29     (IMUN_GPIO4_START + 29)   /**< \brief PIO4_29�жϺ� */
#define INUM_PIO4_30     (IMUN_GPIO4_START + 30)   /**< \brief PIO4_30�жϺ� */
#define INUM_PIO4_31     (IMUN_GPIO4_START + 31)   /**< \brief PIO4_31�жϺ� */

#define INUM_PIO5_0      (IMUN_GPIO5_START + 0)    /**< \brief PIO5_0�жϺ�  */
#define INUM_PIO5_1      (IMUN_GPIO5_START + 1)    /**< \brief PIO5_1�жϺ�  */
#define INUM_PIO5_2      (IMUN_GPIO5_START + 2)    /**< \brief PIO5_2�жϺ�  */
#define INUM_PIO5_3      (IMUN_GPIO5_START + 3)    /**< \brief PIO5_3�жϺ�  */
#define INUM_PIO5_4      (IMUN_GPIO5_START + 4)    /**< \brief PIO5_4�жϺ�  */

/** @} */

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC177X_8X_INUM_H */

/* end of file */
