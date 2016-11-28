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
 * \brief ʱ��ѡ��Ϳ��ƽӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_CLOCK_H
#define __AMHW_CLOCK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"

/**
 * \addtogroup amhw_if_clock
 * \copydoc amhw_clock.h
 * @{
 */

extern uint32_t g_system_clkfreq;      /**< \brief ��ʱ�ӵ�Ƶ�ʣ���λ:Hz��  */
extern uint32_t g_pclk_freq;           /**< \brief ����ʱ��Ƶ�ʣ���λ:Hz��    */
/**
 * \name Ƶ��ֵ����
 * @{
 */
 
#define AMHW_CLOCK_FREQ_OSC      12000000UL   /**< \brief ������Ƶ��(Ĭ������) */
#define AMHW_CLOCK_FREQ_RTC      32768UL      /**< \brief RTC����Ƶ��    */
#define AMHW_CLOCK_FREQ_IRC      12000000UL   /**< \brief �ڲ�IRCƵ��      */
#define AMHW_CLOCK_FREQ_WWDT     500000UL     /**< \brief WWDTʱ��Ƶ��      */
/** @} */


/**
 * \brief ��ȡIRCʱ��Ƶ��
 * \return IRCʱ��Ƶ��
 */
am_static_inline
uint32_t amhw_clock_freq_irc_get (void)
{
    return AMHW_CLOCK_FREQ_IRC;
}

/**
 * \brief ��ȡ��������ʱ��Ƶ��
 * \return ��������ʱ��Ƶ��
 */
uint32_t amhw_clock_freq_osc_get (void);

/**
 * \brief ������������ʱ��Ƶ��
 * \param[in] ��������ʱ��Ƶ��
 */
void amhw_clock_freq_osc_set (uint32_t osc_freq);

/**
 * \brief ��ȡRTC������ʱ��Ƶ��
 * \return RTC������ʱ��Ƶ��
 */
am_static_inline
uint32_t amhw_clock_freq_rtc_get (void)
{
    return AMHW_CLOCK_FREQ_RTC;
}

/**
 * \brief ��ȡ���ڿ��Ź���WWDT����ʱ��Ƶ��
 * \return WWDT��ʱ��Ƶ��
 */
am_static_inline
uint32_t amhw_clock_freq_wwdt_get (void)
{
    return AMHW_CLOCK_FREQ_WWDT;
}

/**
 * \brief ����ϵͳʱ��ȫ�ֱ�����ֵ g_system_clkfreq
 * \return ��
 */
void amhw_clock_freq_update(void);
    

/**
 * \brief ��ȡPLL0������ʱ��Ƶ��
 * \return PLL0������ʱ��Ƶ��
 */
uint32_t amhw_clock_freq_pll0in_get(void);

/**
 * \brief ��ȡPLL0�����ʱ��Ƶ��
 * \return PLL0�����ʱ��Ƶ��
 */
uint32_t amhw_clock_freq_pll0out_get(void);

/**
 * \brief ��ȡPLL1������ʱ��Ƶ��
 * \return PLL0������ʱ��Ƶ��
 */
am_static_inline
uint32_t amhw_clock_freq_pll1in_get (void)
{
    return amhw_clock_freq_osc_get();
}

/**
 * \brief ��ȡPLL1�����ʱ��Ƶ��
 * \return PLL1�����ʱ��Ƶ��
 */
uint32_t amhw_clock_freq_pll1out_get(void);

/**
 * \name PLL0����ʱ��Դ����
 * PLL0����ʱ��Դ����ʱ�����У���־Ϊsysclk����ʹ��USBʱ��ʹ��PLL0���·��ʱ��
 * PLL0������ʱ�ӱ���ΪOSC����CANʱ��Ƶ�ʳ���100kbit/sʱ����Ӧʹ��IRC��Ϊ
 * PLL0ʱ��Դ
 * @{
 */

#define AMHW_CLOCK_PLL0_INSRC_IRC   0   /**< \brief ѡ���ڲ�IRC��ΪPLL0����    */ 
#define AMHW_CLOCK_PLL0_INSRC_OSC   1   /**< \brief ѡ����������ΪPLL0����   */

/** @} */

/**
 * \brief ����PLL0������ʱ��Դ
 * \param[in] insrc �� ֵAMHW_CLOCK_PLL0_INSRC_* ��(#AMHW_CLOCK_PLL0_INSRC_OSC)
 * \return ��
 */
am_static_inline
void amhw_clock_pll0_insrc_set (uint32_t insrc)
{
    AMHW_SYSCON->clksrcsel = insrc & 0x01;
}

/**
 * \brief ʹ��PLL0
 * \return ��
 */
am_static_inline
void amhw_clock_pll0_enable (void)
{
    AMHW_SYSCON->pll0con |= 0x01;
}

/**
 * \brief ����PLL0
 * \return ��
 */
am_static_inline
void amhw_clock_pll0_disable (void)
{
    AMHW_SYSCON->pll0con &= ~0x01;
}

/**
 * \brief ����PLL0�����÷�Ƶֵ�ͱ�Ƶֵ,PLL�����Ƶ��Ӧ�ù̶�Ϊ48MHz
 *
 * PLL0������ʱ�ӹ̶�ΪOSC,m_sel * Fosc = 48MHz
 * ͬʱ�� FCCO / 2P = 48MHz -> FCCO = 2 * p_sel * 48MHz = 2 * p_sel * m_sel * Fosc
 *
 * \param[in] m_sel : PLL0��Ƶֵ
 * \param[in] p_sel ��PLL0��Ƶֵ,ֻ����1��2��4��8
 * \return ��
 */
am_static_inline
void amhw_clock_pll0_cfg (uint32_t m_sel, uint32_t p_sel)
{
    if (p_sel == 8) {
        AMHW_SYSCON->pll0cfg = ((m_sel - 1) & 0x1F) | (3 << 5);
    } else {  /* pse = 1,2,4 */
        AMHW_SYSCON->pll0cfg = ((m_sel - 1) & 0x1F) | (((p_sel >> 1) & 0x03) << 5);
    }
}

/**
 * \brief ��ȡPLL0��ǰʹ�õ�MSELֵ
 * \return PLL0��ǰʹ�õ�MSELֵ
 */
am_static_inline
uint32_t amhw_clock_pll0_msel_get (void)
{
    return (AMHW_SYSCON->pll0stat & 0x1F) + 1;
}

/**
 * \brief ��ȡPLL0��ǰʹ�õ�pSELֵ
 * \return PLL0��ǰʹ�õ�PSELֵ
 */
am_static_inline
uint32_t amhw_clock_pll0_psel_get (void)
{
    return (1 << ((AMHW_SYSCON->pll0stat >> 5) & 0x3));
}

/**
 * \brief ���PLL0��ǰ��ʹ��״̬
 * \return TRUE   �� PLL0�Ѿ�ʹ��
 * \retval FALSE  : PLL0δʹ��
 */
am_static_inline
bool_t amhw_clock_pll0_enable_chk (void)
{
    return (bool_t)((AMHW_SYSCON->pll0stat & (1 << 8)) != 0);
}

/**
 * \brief ��⵱ǰPLL0�Ƿ�����
 * \return TRUE   �� PLL0������
 * \retval FALSE  :  PLL0δ����
 */
am_static_inline
bool_t amhw_clock_pll0_lock_chk (void)
{
    return (bool_t)((AMHW_SYSCON->pll0stat & (1 << 10)) != 0);
}

/**
 * \brief FEED PLL0
 *
 * ֻ��FEED PLL0�����õ�ֵ�Ż����������ã�����FEED����ʱ�ر��жϡ�
 *
 * \return TRUE   �� PLL0������
 * \retval FALSE  :  PLL0δ����
 */
am_static_inline
void amhw_clock_pll0_feed (void)
{
    AMHW_SYSCON->pll0feed = 0xAA;
    AMHW_SYSCON->pll0feed = 0x55;
}

/******************************************************************************/

/**
 * \brief ʹ��PLL1
 * \return ��
 * \note ʹ�ܺ�����PLL1��PLL1���ʱ�ӽ��Զ���ΪUSB������ʱ��
 */
am_static_inline
void amhw_clock_pll1_enable (void)
{
    AMHW_SYSCON->pll1con |= 0x01;
}

/**
 * \brief ����PLL1
 * \return ��
 */
am_static_inline
void amhw_clock_pll1_disable (void)
{
    AMHW_SYSCON->pll1con &= ~0x01;
}

/**
 * \brief ���PLL1��ǰ��ʹ��״̬
 * \return TRUE   �� PLL1�Ѿ�ʹ��
 * \retval FALSE  :  PLL1δʹ��
 */
am_static_inline
bool_t amhw_clock_pll1_enable_chk (void)
{
    return (bool_t)((AMHW_SYSCON->pll1stat & (1 << 8)) != 0);
}

/**
 * \brief ��⵱ǰPLL1�Ƿ�����
 * \return TRUE   �� PLL1������
 * \retval FALSE  :  PLL1δ����
 */
am_static_inline
bool_t amhw_clock_pll1_lock_chk (void)
{
    return (bool_t)((AMHW_SYSCON->pll1stat & (1 << 10)) != 0);
}

/**
 * \brief ����PLL1�����÷�Ƶֵ�ͱ�Ƶֵ,PLL�����Ƶ��Ӧ�ù̶�Ϊ48MHz
 *
 * PLL1������ʱ�ӹ̶�ΪOSC,m_sel * Fosc = 48MHz
 * ͬʱ�� FCCO / 2P = 48MHz -> FCCO = 2 * p_sel * 48MHz = 2 * p_sel * m_sel * Fosc
 *
 * \param[in] m_sel : PLL0��Ƶֵ
 * \param[in] p_sel ��PLL0��Ƶֵ,ֻ����1��2��4��8
 * \return ��
 */
am_static_inline
void amhw_clock_pll1_cfg (uint32_t m_sel, uint32_t p_sel)
{
    if (p_sel == 8) {
        AMHW_SYSCON->pll1cfg = ((m_sel - 1) & 0x1F) | (3 << 5);
    } else {  /* pse = 1,2,4 */
        AMHW_SYSCON->pll1cfg = ((m_sel - 1) & 0x1F) | (((p_sel >> 1) & 0x03) << 5);
    }
}

/**
 * \brief ��ȡPLL1��ǰʹ�õ�MSELֵ
 * \return PLL1��ǰʹ�õ�MSELֵ
 */
am_static_inline
uint32_t amhw_clock_pll1_msel_get (void)
{
    return (AMHW_SYSCON->pll1stat & 0x1F) + 1;
}

/**
 * \brief ��ȡPLL1��ǰʹ�õ�Pֵ
 * \return PLL1��ǰʹ�õ�Pֵ
 */
am_static_inline
uint32_t amhw_clock_pll1_psel_get (void)
{
    return (1 << ((AMHW_SYSCON->pll1stat >> 5) & 0x3));
}

/**
 * \brief FEED PLL1
 *
 * ֻ��FEED PLL1�����õ�ֵ�Ż����������ã�����FEED����ʱ�ر��жϡ�
 *
 * \return ��
 */
am_static_inline
void amhw_clock_pll1_feed (void)
{
    AMHW_SYSCON->pll1feed = 0xAA;
    AMHW_SYSCON->pll1feed = 0x55;
}

/******************************************************************************/
/**
 * \name CCLKʱ��Դ
 * @{
 */
#define AMHW_CLOCK_CCLK_SRC_SYSCLK    0   /**< \brief ѡ��ϵͳʱ����ΪCCLK����    */
#define AMHW_CLOCK_CCLK_SRC_MAINPLL   1   /**< \brief ѡ����PLL��ΪCCLK����    */
/** @} */

/**
 * \brief CPU CLK��ʱ��Դѡ��
 *
 * \param[in] src : CCLKʱ��Դ��ֵΪ(#AMHW_CLOCK_CCLK_SRC_SYSCLK)��
 *                                 (#AMHW_CLOCK_CCLK_SRC_MAINPLL)
 * \return ��
 */
am_static_inline
void amhw_clock_cclk_src_set (uint8_t src)
{
    if (src == AMHW_CLOCK_CCLK_SRC_SYSCLK) {
        AMHW_SYSCON->cclksel &= ~(1 << 8);
    } else {
        AMHW_SYSCON->cclksel |= (1 << 8);
    }
}

/**
 * \brief ����PLL0��CPU CLK��ʱ�ӷ�Ƶ
 *
 * PLL0ʱ�Ӿ����÷�Ƶֵ��Ƶ����ΪCPUʱ��,��ʹ��USBʱ����Ƶ��ʱ������Ϊ18MHZ
 *
 * \param[in] div : ��MCUΪLPC175X_6X,���Ƶֵ�� 1 ~ 256
 *                  ��MCUΪLPC177X_8X,���Ƶֵ�� 0 ~ 31��Ϊ0ʱ����Ƶ���رգ����ṩʱ��
 * \return ��
 */
am_static_inline
void amhw_clock_cclk_div_set (uint16_t div)
{
    uint32_t temp;
    temp = AMHW_SYSCON->cclksel & (1 << 8);

    AMHW_SYSCON->cclksel = temp | (div & 0x1F);

}

/**
 * \brief CPU CLK��ʱ�ӷ�Ƶ
 * 
 * \return ʱ�ӷ�Ƶֵ
 */
am_static_inline
uint32_t amhw_clock_cclk_div_get (void)
{
    return (AMHW_SYSCON->cclksel & 0x1F);
}

/******************************************************************************/
/**
 * \name USBʱ��Դ
 * @{
 */
#define AMHW_CLOCK_USBSRC_SYSCLK  0  /**< \brief ϵͳʱ�ӱ�����USBʱ�ӷ�Ƶ��������  */
#define AMHW_CLOCK_USBSRC_PLL0    1  /**< \brief ��PLL������USBʱ�ӷ�Ƶ��������         */
#define AMHW_CLOCK_USBSRC_PLL1    2  /**< \brief ��PLL������USBʱ�ӷ�Ƶ��������         */
/** @} */

/**
 * \brief ����USBʱ��Դ
 * \param[in] src : USB CLKʱ��Դ��ֵΪ(#AMHW_CLOCK_USBSRC_SYSCLK)��(#AMHW_CLOCK_USBSRC_PLL0)
 *                  ��(#AMHW_CLOCK_USBSRC_PLL1)
 * \param[in] div : ʱ�ӷ�Ƶ��ֵΪ 0,1,2,3
 * \return ��
 */
am_static_inline
void amhw_clock_usbclk_set (uint8_t src, uint8_t div)
{
    AMHW_SYSCON->usbclksel = ((src & 0x03) << 8) | (div & 0x03);
}

/**
 * \brief ��ȡUSBʱ��ѡ��Ĵ���ֵ
 * \return USBʱ��ѡ��Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_clock_usbclk_get (void)
{
    return AMHW_SYSCON->usbclksel;
}

/******************************************************************************/
/**
 * \name EMCʱ�ӷ�Ƶ
 * @{
 */
#define AMHW_CLOCK_EMC_DIV0 0  /**< \brief EMC��CPUʹ��ͬ��ʱ��      */
#define AMHW_CLOCK_EMC_DIV2 1  /**< \brief EMCʱ��ΪCPUʱ�ӵ�һ�� */
/** @} */

/**
 * \brief ����EMC��ʱ��
 * \param[in] clk : EMC��ʱ�ӣ�ֵΪ(#AMHW_CLOCK_EMC_DIV0)��(#AMHW_CLOCK_EMC_DIV2)
 * \return ��
 */
am_static_inline
void amhw_clock_emcclk_set (uint16_t clk)
{
    AMHW_SYSCON->emcclksel =  clk & 0xF;
}

/**
 * \brief ��ȡEMC��ʱ��
 * \retval AMHW_CLOCK_EMC_DIV0: EMC��CPUʹ��ͬ��ʱ��
 * \retval AMHW_CLOCK_EMC_DIV2: EMCʱ��ΪCPUʱ�ӵ�һ��
 */
am_static_inline
uint32_t amhw_clock_emcclk_get (void)
{
    return AMHW_SYSCON->emcclksel & 0x01;
}

/**
 * \brief ����LCDʱ�ӷ�Ƶ
 * \param[in] div : LCDʱ�ӷ�Ƶֵ����СΪ1
 * \return ��
 */
am_static_inline
void amhw_clock_lcdclk_div_set (uint8_t div)
{
    AMHW_SYSCON->lcd_cfg = (div - 1);
}

/**
 * \brief ��ȡLCDʱ�ӷ�Ƶ
 * \return LCDʱ�ӷ�Ƶֵ
 */
am_static_inline
uint32_t amhw_clock_lcdclk_div_get (void)
{
    return (AMHW_SYSCON->lcd_cfg & 0x1F) + 1;
}

/******************************************************************************/
/**
 * \brief �������������Ƶ��
 * \param[in] div  : ʱ�ӷ�Ƶ��ֵΪ0~31.Ϊ0ʱ�����ṩ����ʱ��
 * \return ��
 */
am_static_inline
void amhw_clock_pclk_div_set (uint32_t div)
{
    AMHW_SYSCON->pclksel = div;
}

/**
 * \brief ��ȡ����ʱ�ӵķ�Ƶ
 * \return ����ʱ�ӷ�Ƶֵ
 */
am_static_inline
uint32_t amhw_clock_pclk_div_get (void)
{
    return AMHW_SYSCON->pclksel & 0x1F;
}

/**
 * \brief ��ȡ����ʱ��Ƶ��
 * \return ����ʱ��Ƶ��
 */
uint32_t amhw_clock_freq_pclk_get (void);

/******************************************************************************/
/**
 * \name CLKOUTʱ��Դ����
 * @{
 */

#define AMHW_CLOCK_CLKOUT_CCLK    0        /**< \brief CPUʱ��         */
#define AMHW_CLOCK_CLKOUT_OSCCLK  1        /**< \brief OSCʱ��         */
#define AMHW_CLOCK_CLKOUT_IRC     2        /**< \brief IRCʱ��         */
#define AMHW_CLOCK_CLKOUT_USB     3        /**< \brief USBʱ��         */
#define AMHW_CLOCK_CLKOUT_RTC     4        /**< \brief RTCʱ��         */
#define AMHW_CLOCK_CLKOUT_SPIFI   5        /**< \brief SPIFIʱ��    */
#define AMHW_CLOCK_CLKOUT_WDT     6        /**< \brief WDTʱ��         */

/** @} */

/**
 * \brief ����CLKOUT��ʱ��Դ�����ʱ�ӷ�Ƶ
 * \param[in] clksrc : ʱ��Դ����AMHW_CLOCK_CLKOUT_*ֵ����#AMHW_CLOCK_CLKOUT_OSCCLK
 * \param[in] clkdiv : ʱ�ӷ�Ƶ����Чֵ1 ~ 16
 * \return    ��
 */
void amhw_clock_clkout_cfg(uint32_t clksrc,uint8_t clkdiv);

/**
 * \brief ���CLKOUT�ܽ��Ƿ������ʱ��
 * \retval TRUE  : ���������
 * \retval FALSE : δ���ʱ��
 */
am_static_inline
bool_t amhw_clock_clkout_chk (void)
{
    return (bool_t)((AMHW_SYSCON->clkoutcfg & (1 << 9)) != 0);
}

/**
 * \brief ʹ��CLKOUT���
 * \return ��
 */
am_static_inline
void amhw_clock_clkout_enable(void)
{
    AMHW_SYSCON->clkoutcfg |= (1 << 8);
}
   
/**
 * \brief ����BOD��λ
 * \return ��
 */
am_static_inline
void amhw_clock_clkout_disable(void)
{
    AMHW_SYSCON->clkoutcfg &= ~(1 << 8);
}


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_CLOCK_H */

/* end of file */
