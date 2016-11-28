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
 * \brief ϵͳ���ƽӿ�
 *
 * 1. ��λ���ƣ�
 * 2. BOD�������⣩���ã�
 * 3. �ⲿ�ж�����(External Interrupt Inputs)
 * 4. ����ϵͳ���ƺ�״̬
 *
 * \internal
 * \par History
 * - 1.00 15-09-02  cod, first implementation.
 * \endinternal
 */

#ifndef __AMHW_SYSCON_H
#define __AMHW_SYSCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc177x_8x.h"

/**
 * \addtogroup amhw_if_syscon
 * \copydoc amhw_syscon.h
 * @{
 */

/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef struct amhw_syscon {
    __IO uint32_t flashcfg;          /**< \brief Flash����������    */
         uint32_t reserved0[31];     /**< \brief ��������Ӧʹ��     */
    __IO uint32_t pll0con;           /**< \brief PLL0���ƼĴ���     */
    __IO uint32_t pll0cfg;           /**< \brief PLL0���üĴ���     */
    __I  uint32_t pll0stat;          /**< \brief PLL0״̬�Ĵ���     */
    __O  uint32_t pll0feed;          /**< \brief PLL0 FEED�Ĵ���    */
         uint32_t reserved1[4];      /**< \brief ��������Ӧʹ��     */
    __IO uint32_t pll1con;           /**< \brief PLL1���ƼĴ���     */
    __IO uint32_t pll1cfg;           /**< \brief PLL1���üĴ���     */
    __I  uint32_t pll1stat;          /**< \brief PLL1״̬�Ĵ���     */
    __O  uint32_t pll1feed;          /**< \brief PLL1 FEED�Ĵ���    */
         uint32_t reserved2[4];      /**< \brief ��������Ӧʹ��      */
    __IO uint32_t pcon;              /**< \brief ��Դ���ƼĴ���      */
    __IO uint32_t pconp;             /**< \brief �����Դ���ƼĴ���  */
         uint32_t reserved3[14];     /**< \brief ��������Ӧʹ��      */
    __IO uint32_t emcclksel;         /**< \brief �ⲿ�洢������ʱ��ѡ��Ĵ���    */
    __IO uint32_t cclksel;           /**< \brief CPUʱ��ѡ��Ĵ���   */
    __IO uint32_t usbclksel;         /**< \brief USBʱ��ѡ��Ĵ���   */
    __IO uint32_t clksrcsel;         /**< \brief ʱ��Դѡ��Ĵ���    */
    __IO uint32_t cansleepclr;       /**< \brief CAN ͨ��˯��״̬    */
    __IO uint32_t canwakeflags;      /**< \brief CAN ͨ�����ѱ�־    */
         uint32_t reserved4[10];     /**< \brief ��������Ӧʹ��      */
    __IO uint32_t extint;            /**< \brief �ⲿ�жϼĴ���      */
         uint32_t reserved5;         /**< \brief ��������Ӧʹ��      */
    __IO uint32_t extmode;           /**< \brief �ⲿ�ж�ģʽ�Ĵ���  */
    __IO uint32_t extpolar;          /**< \brief �ⲿ�жϼ��ԼĴ���  */
         uint32_t reserved6[12];     /**< \brief ��������Ӧʹ��      */
    __IO uint32_t rsid;              /**< \brief ʱ��Դ�Ĵ���        */
         uint32_t reserved7;         /**< \brief ��������Ӧʹ��      */
    __IO uint32_t matrixarb;         /**< \brief �����ٲüĴ���    */
         uint32_t reserved8[5];      /**< \brief ��������Ӧʹ��      */
    __IO uint32_t scs;               /**< \brief ϵͳ����/״̬�Ĵ���  */
    __IO uint32_t irctrim;           /**< \brief IRC�����Ĵ���                 */
    __IO uint32_t pclksel;           /**< \brief ����ʱ��ѡ��Ĵ���     */
         uint32_t reserved9;         /**< \brief ��������Ӧʹ��               */
    __IO uint32_t pboost;            /**< \brief �����������ƼĴ���     */
    __IO uint32_t spificlksel;       /**< \brief SPIFIʱ��ѡ��Ĵ���  */
    __IO uint32_t lcd_cfg;           /**< \brief LCDʱ�����ƼĴ���        */
         uint32_t reserved10;        /**< \brief ��������Ӧʹ��               */
    __IO uint32_t usbintst;          /**< \brief USB�ж�״̬�Ĵ���    */
    __IO uint32_t dmareqsel;         /**< \brief DMA����Դѡ��Ĵ���  */
    __IO uint32_t clkoutcfg;         /**< \brief ʱ��������üĴ���   */
    __IO uint32_t rstcon0;           /**< \brief ��λ���ƼĴ���0   */
    __IO uint32_t rstcon1;           /**< \brief ��λ���ƼĴ���1   */
         uint32_t reserved11[2];     /**< \brief ��������Ӧʹ��           */
    __IO uint32_t emcdlyctl;         /**< \brief EMC�ӳٿ��ƼĴ���    */
    __IO uint32_t emccal;            /**< \brief EMCУ׼�Ĵ���             */
} amhw_syscon_t;


/**
 * \name ��λԴ����
 * @{
 */

#define AMHW_SYSCON_RSID_POR       (1 << 0)      /**< \brief �ϵ縴λ             */
#define AMHW_SYSCON_RSID_EXTR      (1 << 1)      /**< \brief �ⲿ�ܽţ�RESET����λ */
#define AMHW_SYSCON_RSID_WDTR      (1 << 2)      /**< \brief ���Ź���λ          */
#define AMHW_SYSCON_RSID_BODR      (1 << 3)      /**< \brief �����⸴λ          */
#define AMHW_SYSCON_RSID_SYSRESET  (1 << 4)      /**< \brief ϵͳ����λ          */
#define AMHW_SYSCON_RSID_LOCKUP    (1 << 5)      /**< \brief ������������λ      */


/** @} */

/**
 * \brief �õ���λԴ
 * \return ��λԴ,ֵΪAMHW_SYSCON_RSID_*(�磺#AMHW_SYSCON_RSID_WDTR)
 */
am_static_inline
uint32_t amhw_syscon_rsid_get (void)
{
    return (AMHW_SYSCON->rsid & 0x0F);
}

/**
 * \brief ��⸴λԴ�Ƿ���ĳ��ָ���ĸ�λԴ
 * \param[in] rsid : �����ĸ�λԴ��AMHW_SYSCON_RSID_*��(#AMHW_SYSCON_RSID_WDTR)
 * \retval TRUE    : ��λԴ��ָ���Ĵ����ĸ�λԴ
 * \retval FALSE   : ��λԴ����ָ���Ĵ����ĸ�λԴ
 */
am_static_inline
bool_t amhw_syscon_rsid_chk (uint32_t rsid)
{
    return (bool_t)((AMHW_SYSCON->rsid & rsid) != 0);
}

/**
 * \brief ���ָ���ĸ�λԴ
 * \param[in] rsid : �����ĸ�λԴ��AMHW_SYSCON_RSID_*��(#AMHW_SYSCON_RSID_WDTR)
 * \return    ��
 */
am_static_inline
void amhw_syscon_rsid_clr (uint32_t rsid)
{
    AMHW_SYSCON->rsid |= rsid;
}

/**
 * \name EINT�ж�Դ����
 * @{
 */

#define AMHW_SYSCON_EINT0  (1 << 0)    /**< \brief �ⲿ�ж�0        */
#define AMHW_SYSCON_EINT1  (1 << 1)    /**< \brief �ⲿ�ж�1        */
#define AMHW_SYSCON_EINT2  (1 << 2)    /**< \brief �ⲿ�ж�2        */
#define AMHW_SYSCON_EINT3  (1 << 3)    /**< \brief �ⲿ�ж�3        */

/** @} */

/**
 * \brief �õ��ⲿ�жϵ�״̬
 * \return ��ӦλΪ1�������ⲿ�жϴ��ڼ���״̬
 */
am_static_inline
uint32_t amhw_syscon_eint_get (void)
{
    return (AMHW_SYSCON->extint & 0x0F);
}

/**
 * \brief ���ָ���ⲿ�ж��Ƿ��ڼ���̬
 * \param[in] eint_id : �������ⲿ�жϣ�AMHW_SYSCON_EINT*��(#AMHW_SYSCON_EINT0)
 * \retval TRUE       : �ⲿ�жϴ��ڼ���״̬
 * \retval FALSE      : �ⲿ�ж�δ���ڼ���״̬
 */
am_static_inline
bool_t amhw_syscon_eint_chk (uint32_t eint_id)
{
    return (bool_t)((AMHW_SYSCON->extint & eint_id) != 0);
}

/**
 * \brief ���ָ���ⲿ�жϵ�״̬
 * \param[in] eint_id : AMHW_SYSCON_EINT*ֵ�������ֵ���磺(#AMHW_SYSCON_EINT3)
 * \return    ��
 */
am_static_inline
void amhw_syscon_eint_clr (uint32_t eint_id)
{
    AMHW_SYSCON->extint = eint_id & 0x0F;
}

/**
 * \name EINTģʽ
 * @{
 */

#define AMHW_SYSCON_EINTMODE_LEVEL  0    /**< \brief ��ƽ��Ч     */
#define AMHW_SYSCON_EINTMODE_EDGE   1    /**< \brief ������Ч     */
 
/** @} */

/**
 * \brief ����EXTINT��ģʽ
 * \param[in] eint_id : AMHW_SYSCON_EINT*ֵ�������ֵ���磺(#AMHW_SYSCON_EINT3)
 * \param[in] mode    : AMHW_SYSCON_EINTMODE_LEVEL ���� AMHW_SYSCON_EINTMODE_EDGE
 * \return None
 */
am_static_inline
void amhw_syscon_eintmode_set (uint32_t eint_id, uint32_t mode)
{
    if (mode == AMHW_SYSCON_EINTMODE_EDGE) {
        AMHW_SYSCON->extmode |= eint_id;
    } else {
        AMHW_SYSCON->extmode &= ~eint_id;
    }
}

/**
 * \name EINTģʽ
 * @{
 */

#define AMHW_SYSCON_EINTPOLAR_1   1    /**< \brief �ߵ�ƽ�������أ�����ģʽ��     */
#define AMHW_SYSCON_EINTPOLAR_0   0    /**< \brief �͵�ƽ���½��أ�����ģʽ��     */
 
/** @} */

/**
 * \brief ����EXTINT�ļ���
 * \param[in] eint_id : AMHW_SYSCON_EINT*ֵ�������ֵ���磺(#AMHW_SYSCON_EINT3)
 * \param[in] polar   : AMHW_SYSCON_EINTPOLAR_0 ���� AMHW_SYSCON_EINTPOLAR_1
 * \return None
 */
am_static_inline
void amhw_syscon_eintpolar_set (uint32_t eint_id, uint32_t polar)
{
    if (polar == AMHW_SYSCON_EINTPOLAR_1) {
        AMHW_SYSCON->extpolar |= eint_id;
    } else {
        AMHW_SYSCON->extpolar &= ~eint_id;
    }
}

/**
 * \name ������(main oscillator)�ķ�Χ
 * @{
 */

#define AMHW_SYSCON_OSCRANGE_1_20MHz    0    /**< \brief ��Χ��1  ~ 20MHz     */
#define AMHW_SYSCON_OSCRANGE_15_25MHz   1    /**< \brief ��Χ��15 ~ 25MHz     */
 
/** @} */

/**
 * \brief ����������(main oscillator)�ķ�Χ
 * \param[in] range : AMHW_SYSCON_OSCRANGE_1_20MHz ���� AMHW_SYSCON_OSCRANGE_15_25MHz
 * \return ��
 */
am_static_inline
void amhw_syscon_oscrange_set (uint32_t range)
{
    if (range == AMHW_SYSCON_OSCRANGE_15_25MHz) {
        AMHW_SYSCON->scs |= (1 << 4);
    } else {
        AMHW_SYSCON->scs &= ~(1 << 4);
    }
}


/**
 * \brief ʹ��������(main oscillator)
 * \return ��
 */
am_static_inline
void amhw_syscon_osc_enable (void)
{
    AMHW_SYSCON->scs |= (1 << 5);
}

/**
 * \brief ����������(main oscillator)
 * \return ��
 */
am_static_inline
void amhw_syscon_osc_disable (void)
{
    AMHW_SYSCON->scs &= ~(1 << 5);
}


/**
 * \brief ����������Ƿ�׼������
 * \retval TRUE  : ׼�����������Ա���������ʱ�ӵ�ʱ��Դ
 * \retval FALSE : δ׼��������������������ʱ�ӵ�ʱ��Դ
 */
am_static_inline
bool_t amhw_syscon_osc_ready_chk (void)
{
    return (bool_t)((AMHW_SYSCON->scs & (1 << 6)) != 0);
}


/**
 * \name ��λ���ƼĴ���0--��λ����λ����
 * @{
 */
#define AMWH_RSTCON0_LCD     (1 << 0)       /**< \brief LCD��������λ */
#define AMWH_RSTCON0_TIM0    (1 << 1)       /**< \brief ��ʱ��/������0��λ */
#define AMWH_RSTCON0_TIM1    (1 << 2)       /**< \brief ��ʱ��/������1��λ */
#define AMWH_RSTCON0_UART0   (1 << 3)       /**< \brief UART0��λ */
#define AMWH_RSTCON0_UART1   (1 << 4)       /**< \brief UART1��λ */
#define AMWH_RSTCON0_PWM0    (1 << 5)       /**< \brief PWM0��λ */
#define AMWH_RSTCON0_PWM1    (1 << 6)       /**< \brief PWM1��λ */
#define AMWH_RSTCON0_I2C0    (1 << 7)       /**< \brief I2C0��λ */
#define AMWH_RSTCON0_UART4   (1 << 8)       /**< \brief UART4��λ */
#define AMWH_RSTCON0_RTC     (1 << 9)       /**< \brief RTC���¼���������λ */
#define AMWH_RSTCON0_SSP1    (1 << 10)      /**< \brief SSP1��λ */
#define AMWH_RSTCON0_EMC     (1 << 11)      /**< \brief EMC��λ */
#define AMWH_RSTCON0_ADC     (1 << 12)      /**< \brief ADC��λ */
#define AMWH_RSTCON0_CAN1    (1 << 13)      /**< \brief CAN1��λ */
#define AMWH_RSTCON0_CAN2    (1 << 14)      /**< \brief CAN2��λ */
#define AMWH_RSTCON0_GPIO    (1 << 15)      /**< \brief GPIO��λ */

#define AMWH_RSTCON0_MCPWM   (1 << 17)      /**< \brief MCPWM��λ */
#define AMWH_RSTCON0_QEI     (1 << 18)      /**< \brief QEI��λ */
#define AMWH_RSTCON0_I2C1    (1 << 19)      /**< \brief I2C1��λ */
#define AMWH_RSTCON0_SSP2    (1 << 20)      /**< \brief SSP2��λ */
#define AMWH_RSTCON0_SSP0    (1 << 21)      /**< \brief SSP0��λ */
#define AMWH_RSTCON0_TIM2    (1 << 22)      /**< \brief TIM2��λ */
#define AMWH_RSTCON0_TIM3    (1 << 23)      /**< \brief TIM3��λ */
#define AMWH_RSTCON0_UART2   (1 << 24)      /**< \brief UART2��λ */
#define AMWH_RSTCON0_UART3   (1 << 25)      /**< \brief UART3��λ */
#define AMWH_RSTCON0_I2C2    (1 << 26)      /**< \brief I2C2��λ */
#define AMWH_RSTCON0_I2S     (1 << 27)      /**< \brief I2S��λ */
#define AMWH_RSTCON0_SDC     (1 << 28)      /**< \brief SD����λ */
#define AMWH_RSTCON0_GPDMA   (1 << 29)      /**< \brief GPDMA��λ */
#define AMWH_RSTCON0_ENET    (1 << 30)      /**< \brief ��̫����λ */
#define AMWH_RSTCON0_USB     (1 << 31)      /**< \brief USB��λ */

/** @} */

/**
 * \brief  ���踴λ�Ĵ���0--ָ�����踴λ
 * \param[in] per : �����ţ�ֵΪAMHW_SYSCON_RST*(��#AMHW_RSTCON0_LCD)
 *
 * \return ��
 */
am_static_inline
void amhw_syscon_periph_reset0 (uint32_t per)
{
   AMHW_SYSCON->rstcon0 |= per;
   AMHW_SYSCON->rstcon0 &= ~per;
}


/**
 * \name ��λ���ƼĴ���1--��λ����λ����
 * @{
 */
#define AMWH_RSTCON1_IOCON     (1 << 0)     /**< \brief IOCON�Ĵ�����λ */
#define AMWH_RSTCON1_DAC       (1 << 1)     /**< \brief DACת������λ */
#define AMWH_RSTCON1_CANACC    (1 << 2)     /**< \brief CAN�����˲�����λ */
/** @} */
/**
 * \brief  ���踴λ�Ĵ���1--ָ�����踴λ
 * \param[in] per : �����ţ�ֵΪAMHW_SYSCON_RST*(��#AMHW_RSTCON1_IOCON)
 *
 * \return ��
 */
am_static_inline
void amhw_syscon_periph_reset1 (uint32_t per)
{
   AMHW_SYSCON->rstcon1 |= per;
   AMHW_SYSCON->rstcon1 &= ~per;
}

/**
 * \brief ����FLASH������
 * \param[in] cpu_freq : ϵͳʱ��Ƶ�ʣ���λHz
 * \return ��
 */
am_static_inline
void amhw_syscon_flash_cfg (uint32_t cpu_freq)
{
    if (cpu_freq <= 20000000) {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (0 << 12);
    } else if (cpu_freq <= 40000000) {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (1 << 12);
    } else if (cpu_freq <= 60000000) {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (2 << 12);
    } else if (cpu_freq <= 80000000) {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (3 << 12);
    } else {
        AMHW_SYSCON->flashcfg = (AMHW_SYSCON->flashcfg & ~0x0000F000) | (4 << 12);
    }
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_SYSCON_H */

/* end of file */
