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
 * \brief ��Դ���ƽӿ�
 *
 * 1. �͹��Ŀ���
 * 2. �����Դ����
 *
 * \internal
 * \par History
 * - 1.00 15-04-22  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_POWER_H
#define __AMHW_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"

/**
 * \addtogroup amhw_if_power
 * \copydoc amhw_power.h
 * @{
 */

/**
 * \name �����Դ���ƶ���
 * @{
 */
#define AMHW_POWER_LCD       (1 << 0)    /**< \brief LCD         */
#define AMHW_POWER_TIMER0    (1 << 1)    /**< \brief ��ʱ��0     */
#define AMHW_POWER_TIMER1    (1 << 2)    /**< \brief ��ʱ��1     */
#define AMHW_POWER_UART0     (1 << 3)    /**< \brief UART0       */
#define AMHW_POWER_UART1     (1 << 4)    /**< \brief UART1       */
#define AMHW_POWER_PWM0      (1 << 5)    /**< \brief PWM0        */
#define AMHW_POWER_PWM1      (1 << 6)    /**< \brief PWM1        */
#define AMHW_POWER_I2C0      (1 << 7)    /**< \brief ADC0        */
#define AMHW_POWER_UART4     (1 << 8)    /**< \brief UART4       */
#define AMHW_POWER_RTC       (1 << 9)    /**< \brief RTC         */
#define AMHW_POWER_SSP1      (1 << 10)   /**< \brief SSP1        */
#define AMHW_POWER_EMC       (1 << 11)   /**< \brief EMC         */
#define AMHW_POWER_ADC       (1 << 12)   /**< \brief ADC         */
#define AMHW_POWER_CAN1      (1 << 13)   /**< \brief CAN1        */
#define AMHW_POWER_CAN2      (1 << 14)   /**< \brief CAN2        */
#define AMHW_POWER_GPIO      (1 << 15)   /**< \brief GPIO        */
#define AMHW_POWER_SPIFI     (1 << 16)   /**< \brief SPIFI       */
#define AMHW_POWER_MCPWM     (1 << 17)   /**< \brief MCPWM       */
#define AMHW_POWER_QEI       (1 << 18)   /**< \brief QEI         */
#define AMHW_POWER_I2C1      (1 << 19)   /**< \brief I2C1        */
#define AMHW_POWER_SSP2      (1 << 20)   /**< \brief SSP2        */
#define AMHW_POWER_SSP0      (1 << 21)   /**< \brief SSP0        */
#define AMHW_POWER_TIMER2    (1 << 22)   /**< \brief ��ʱ��2     */
#define AMHW_POWER_TIMER3    (1 << 23)   /**< \brief ��ʱ��3     */
#define AMHW_POWER_UART2     (1 << 24)   /**< \brief UART2       */
#define AMHW_POWER_UART3     (1 << 25)   /**< \brief UART3       */
#define AMHW_POWER_I2C2      (1 << 26)   /**< \brief I2C2        */
#define AMHW_POWER_I2S       (1 << 27)   /**< \brief I2S         */
#define AMHW_POWER_SDC       (1 << 28)   /**< \brief SD��                      */
#define AMHW_POWER_GPDMA     (1 << 29)   /**< \brief GPDMA       */
#define AMHW_POWER_ENET      (1 << 30)   /**< \brief ENET        */
#define AMHW_POWER_USB       (1 << 31)   /**< \brief USB         */

/** @} */

/**
 * \brief �ر������Դ
 * \param[in] powerdownmask ��AMHW_POWER_* ��ֵ���� AMHW_POWER_*���
                              ��OR��ֵ(#AMHW_POWER_I2C2)
 * \return ��
 */
am_static_inline
void amhw_power_periph_down (uint32_t powerdownmask)
{
    AMHW_SYSCON->pconp &= ~powerdownmask;
}

/**
 * \brief �������Դ
 * \param[in] powerupmask ��AMHW_POWER_* ��ֵ���� AMHW_POWER_*���
                            ��OR��ֵ(#AMHW_POWER_I2C2)
 * \return ��
 */
am_static_inline
void amhw_power_periph_up (uint32_t powerupmask)
{
    AMHW_SYSCON->pconp |= powerupmask;
}

/**
 * \name �͹���ģʽ����
 * @{
 */

#define AMHW_POWER_MODE_SLEEP           (1 << 0)    /**< \brief ˯��ģʽ      */
#define AMHW_POWER_MODE_DEEP_SLEEP      (1 << 1)    /**< \brief ���˯��ģʽ  */
#define AMHW_POWER_MODE_POWERDOWN       (1 << 2)    /**< \brief ����ģʽ      */
#define AMHW_POWER_MODE_DEEP_POWERDOWN  (1 << 3)    /**< \brief ��ȵ���ģʽ  */

/** @} */

/**
 * \brief ���õ͹���ģʽ
 * \param[in] mode : �͹���ģʽ����ֵ AMHW_SYSCON_POWER_MODE_*,
 *                   ��#AMHW_SYSCON_POWER_MODE_SLEEP
 * \return ��
 */
void amhw_power_mode_enter (uint32_t mode);

/**
 * \brief ��ȡ��ǰ�ĵ͹���ģʽ
 * \return �͹���ģʽ����ֵ AMHW_SYSCON_POWER_MODE_*,��#AMHW_SYSCON_POWER_MODE_SLEEP
 */
am_static_inline
uint32_t amhw_power_mode_get(void)
{
    return (AMHW_SYSCON->pcon >> 8) & 0x0F;
}

/**
 * \brief ����͹���ģʽ��־
 * \param[in] mode : �͹���ģʽ����ֵ AMHW_SYSCON_POWER_MODE_*,
 *                   ��#AMHW_SYSCON_POWER_MODE_SLEEP
 * \return ��
 */
am_static_inline
void amhw_power_mode_clr (uint32_t mode)
{
    AMHW_SYSCON->pcon |= (mode & 0x0F) << 8;
}

/**
 * \brief ʹ�ܵ͹���ģʽ��BOD����
 * \return ��
 */
am_static_inline
void amhw_power_bod_powermode_enable(void)
{
    AMHW_SYSCON->pcon &= ~(1 << 2);
}
   
/**
 * \brief ���ܵ͹���ģʽ��BOD����
 * \return ��
 */
am_static_inline
void amhw_power_bod_powermode_disable(void)
{
    AMHW_SYSCON->pcon |=  (1 << 2);
}

/**
 * \brief ����ȫ�ֵ�BOD���
 * \return ��
 */
am_static_inline
void amhw_power_bod_global_disable(void)
{
    AMHW_SYSCON->pcon |= (1 << 3);
}

/**
 * \brief ʹ��ȫ�ֵ�BOD���
 * \return ��
 */
am_static_inline
void amhw_power_bod_global_enable(void)
{
    AMHW_SYSCON->pcon &= ~(1 << 3);
}

/**
 * \brief ʹ��BOD��λ
 * \return ��
 */
am_static_inline
void amhw_power_bod_reset_enable(void)
{
    AMHW_SYSCON->pcon &= ~(1 << 4);
}
   
/**
 * \brief ����BOD��λ
 * \return ��
 */
am_static_inline
void amhw_power_bod_reset_disable(void)
{
    AMHW_SYSCON->pcon |=  (1 << 4);
}

/**
 * \brief ������������
 * \return ��
 * \note  ������������ߴ�120MHz
 */
am_static_inline
void amhw_power_boost_enable(void)
{
    AMHW_SYSCON->pboost |= 0x03;
}

/**
 * \brief ���������ر�
 * \return ��
 * \note �������ı�����100MHz����
 */
am_static_inline
void amhw_power_boost_disable(void)
{
    AMHW_SYSCON->pboost &= ~0x03;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_POWER_H */

/* end of file */
