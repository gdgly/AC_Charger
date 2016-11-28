/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LCDӲ�������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-19  cod, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LCD_H
#define __AMHW_LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_common.h"

/**
 * \addtogroup amhw_if_lcd
 * \copydoc amhw_lcd.h
 * @{
 */

/**
 * \brief LCD�������Ĵ�����ṹ��
 */
typedef struct amhw_lcd {
    __IO uint32_t timh;           /**< \brief ˮƽʱ����ƼĴ���                  */
    __IO uint32_t timv;           /**< \brief ��ֱʱ����ƼĴ���                  */
    __IO uint32_t pol;            /**< \brief ʱ�Ӻ��źż��Կ��ƼĴ���   */
    __IO uint32_t le;             /**< \brief ��ĩ���ƼĴ���                 */
    __IO uint32_t upbase;         /**< \brief ����֡��ַ�Ĵ���            */
    __IO uint32_t lpbase;         /**< \brief ����֡��ַ�Ĵ���            */
    __IO uint32_t ctrl;           /**< \brief LCD���ƼĴ���                    */
    __IO uint32_t intmsk;         /**< \brief �ж����μĴ���                  */
    __I  uint32_t intraw;         /**< \brief ԭʼ�ж�״̬�Ĵ���         */
    __I  uint32_t intstat;        /**< \brief �������ж�״̬�Ĵ���     */
    __O  uint32_t intclr;         /**< \brief �ж�����Ĵ���                    */
    __I  uint32_t upcurr;         /**< \brief ������ǰ��ֵַ�Ĵ���      */
    __I  uint32_t lpcurr;         /**< \brief ������ǰ��ֵַ�Ĵ���      */
         uint32_t reserved0[115]; /**< \brief ����      */
    __IO uint32_t pal[128];       /**< \brief 256��16λ��ɫ��ɫ��Ĵ���   */
         uint32_t reserved1[256]; /**< \brief ����                                   */
    __IO uint32_t crsr_img[256];  /**< \brief ���ͼ��Ĵ���           */
    __IO uint32_t crsr_ctrl;      /**< \brief �����ƼĴ���           */
    __IO uint32_t crsr_cfg;       /**< \brief ������üĴ���            */
    __IO uint32_t crsr_pal0;      /**< \brief ����ɫ��Ĵ���0  */
    __IO uint32_t crsr_pal1;      /**< \brief ����ɫ��Ĵ���1  */
    __IO uint32_t crsr_xy;        /**< \brief ���XYλ�üĴ���        */
    __IO uint32_t crsr_clip;      /**< \brief ������λ�üĴ���    */
         uint32_t reserved2[2];   /**< \brief ����       */
    __IO uint32_t crsr_intmsk;    /**< \brief ����ж����μĴ���      */
    __O  uint32_t crsr_intclr;    /**< \brief ����ж�����Ĵ���      */
    __I  uint32_t crsr_intraw;    /**< \brief ���ԭʼ�ж�״̬�Ĵ���      */
    __I  uint32_t crsr_intstat;   /**< \brief ����������ж�״̬�Ĵ���  */
} amhw_lcd_t;

#define AMHW_LCD_PWR_DIS_DLY  10000UL   /**< \brief LCD�ϵ�ϵ���ʱ           */

/**
 * \name LCD����λ����
 * \anchor grp_amhw_lcd_ctrl_flags
 * @{
 */
#define AMHW_LCD_DISABLE         (0)      /**< \brief LCD��ֹ  */
#define AMHW_LCD_ENABLE          (1 << 0) /**< \brief LCDʹ��  */

#define AMHW_LCD_BPP_1           (0 << 1) /**< \brief 1bpp  */
#define AMHW_LCD_BPP_2           (1 << 1) /**< \brief 2bpp  */
#define AMHW_LCD_BPP_4           (2 << 1) /**< \brief 4bpp  */
#define AMHW_LCD_BPP_8           (3 << 1) /**< \brief 8bpp  */
#define AMHW_LCD_BPP_16          (4 << 1) /**< \brief 16bpp */
#define AMHW_LCD_BPP_24          (5 << 1) /**< \brief 24bpp����ΪTFT��ʾ����*/
#define AMHW_LCD_BPP_16_565Mode  (6 << 1) /**< \brief 16bpp 5:6:5ģʽ */
#define AMHW_LCD_BPP_12_444Mode  (7 << 1) /**< \brief 12bpp 4:4:4ģʽ */

#define AMHW_LCD_STN_COLOR       (0)      /**< \brief STN LCD�ǲ�ɫ */
#define AMHW_LCD_STN_MONO        (1 << 4) /**< \brief STN LCD�ǵ�ɫ */

#define AMHW_LCD_TYPE_STN        (0)      /**< \brief LCDΪSTN��ʾ�� */
#define AMHW_LCD_TYPE_TFT        (1 << 5) /**< \brief LCDΪTFT��ʾ�� */

#define AMHW_LCD_STN_MONO_4BIT   (0)      /**< \brief ��ɫSTN LCDʹ��4λ���нӿ�  */
#define AMHW_LCD_STN_MONO_8BIT   (1 << 6) /**< \brief ��ɫSTN LCDʹ��8λ���нӿ�  */

#define AMHW_LCD_SINGLE_PANEL    (0)      /**< \brief ���� */
#define AMHW_LCD_DUAL_PANEL      (1 << 7) /**< \brief ˫�� */

#define AMHW_LCD_COLOR_FORMAT_RGB (0)      /**< \brief RGB(�������) */
#define AMHW_LCD_COLOR_FORMAT_BGR (1 << 8) /**< \brief BGR(��������) */

#define AMHW_LCD_BYTE_LITTLE_ENDIAN (0)      /**< \brief �ڴ��ֽ�С��ģʽ */
#define AMHW_LCD_BYTE_BIG_ENDIAN    (1 << 9) /**< \brief �ڴ��ֽڴ��ģʽ*/

#define AMHW_LCD_PIXEL_LITTLE_ENDIAN  (0)       /**< \brief �ֽ�����С��ģʽ */
#define AMHW_LCD_PIXEL_BIG_ENDIAN     (1 << 10) /**< \brief �ֽ����ش��ģʽ */

#define AMHW_LCD_PWR_ENABLE          (1 << 11) /**< \brief LCD��Դʹ�� */
#define AMHW_LCD_PWR_DISABLE         (0)       /**< \brief LCD��Դʧ�� */

#define AMHW_LCD_VCOMP_VERTICAL_SYNC (0 << 12) /**< \brief VComp�жϴ�ֱͬ����ʼ */
#define AMHW_LCD_VCOMP_BACK_PORCH    (1 << 12) /**< \brief VComp�жϺ��ؿ�ʼ */
#define AMHW_LCD_VCOMP_ACTIVE_VIDEO  (2 << 12) /**< \brief VComp�ж���Ч��Ƶ��ʼ */
#define AMHW_LCD_VCOMP_FRONT_PORCH   (3 << 12) /**< \brief VComp�ж�ǰ�ؿ�ʼ*/

#define AMHW_LCD_DMA_FIFO_EMPTY4   (0)       /**< \brief FIFO >=4���յ�Ԫ����DMA���� */
#define AMHW_LCD_DMA_FIFO_EMPTY8   (1 << 16) /**< \brief FIFO >=8���յ�Ԫ����DMA���� */
/** @} */

/**
 * \brief LCD����
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : LCD������Ϣ,�μ�\ref grp_amhw_lcd_ctrl_flags "LCD CTRL FLAG"
 * \return ��
 */
am_static_inline
void amhw_lcd_ctrl_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl = flag;
}

/**
 * \brief LCDʹ��
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lcd_enable (amhw_lcd_t *p_hw_lcd)
{
    p_hw_lcd->ctrl |= AMHW_LCD_ENABLE;
}

/**
 * \brief LCDʧ��
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lcd_disable (amhw_lcd_t *p_hw_lcd)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_ENABLE;
}

/**
 * \brief LCD��Դʹ��
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lcd_power_on (amhw_lcd_t *p_hw_lcd)
{
    volatile int i;
    p_hw_lcd->ctrl |= AMHW_LCD_ENABLE ;
    for (i = 0; i < AMHW_LCD_PWR_DIS_DLY; i++);
    p_hw_lcd->ctrl |= AMHW_LCD_PWR_ENABLE;
}

/**
 * \brief LCD��Դʧ��
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_lcd_power_off (amhw_lcd_t *p_hw_lcd)
{
    volatile int i;
    p_hw_lcd->ctrl &= ~AMHW_LCD_PWR_ENABLE;
    for (i = 0; i < AMHW_LCD_PWR_DIS_DLY; i++);
    p_hw_lcd->ctrl &= ~AMHW_LCD_ENABLE;
}

/**
 * \brief LCD����λ������
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : LCD������Ҫ��λ��,ֵΪAMHW_LCD_BPP_*(#AMHW_LCD_BPP_1)
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_bpp_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~(0x7 << 1);
    p_hw_lcd->ctrl |= flag & (0x7 << 1);
}

/**
 * \brief STN LCD��ɫ/��ɫѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ��ɫ/��ɫ��ֵΪ#AMHW_LCD_STN_COLOR �� #AMHW_LCD_STN_MONO
 *
 * \return ��
 * \note   TFTģʽ�ò���û������
 */
am_static_inline
void amhw_lcd_stn_bw_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_STN_MONO;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_STN_MONO;
}

/**
 * \brief LCD��ʾ��TFT����ѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : TFT����ѡ��ֵΪ#AMHW_LCD_TYPE_STN �� #AMHW_LCD_TYPE_TFT
 *
 * \return ��
 * \note   TFTģʽ�ò���û������
 */
am_static_inline
void amhw_lcd_tft_type_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_TYPE_TFT;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_TYPE_TFT;
}

/**
 * \brief ��ɫSTN LCD�ӿڿ������
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ��ɫLCD�ӿڿ�ȣ�ֵΪ#AMHW_LCD_STN_MONO_8BIT
 *                       �� #AMHW_LCD_STN_MONO_4BIT
 *
 * \return ��
 * \note   �ò���ֻ�Ե�ɫSTN LCD�����壬����ģʽ������
 */
am_static_inline
void amhw_lcd_mono_interfacewidth_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_STN_MONO_8BIT;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_STN_MONO_8BIT;
}

/**
 * \brief STN LCD�ӿڵ���/˫��ѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ����/˫����ֵΪ#AMHW_LCD_SINGLE_PANEL
 *                       �� #AMHW_LCD_DUAL_PANEL
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_dual_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_DUAL_PANEL;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_DUAL_PANEL;
}

/**
 * \brief LCDɫ��ģʽѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : RGB��BGRģʽ��ֵΪ#AMHW_LCD_COLOR_FORMAT_RGB
 *                       ��#AMHW_LCD_COLOR_FORMAT_BGR
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_color_mode_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_COLOR_FORMAT_BGR;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_COLOR_FORMAT_BGR;
}

/**
 * \brief �����ڴ����ֽ�����
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ���/С��ģʽ��ֵΪ#AMHW_LCD_BYTE_LITTLE_ENDIAN
 *                       ��#AMHW_LCD_BYTE_BIG_ENDIAN
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_byte_endian_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_BYTE_BIG_ENDIAN;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_BYTE_BIG_ENDIAN;
}

/**
 * \brief �����ֽ�����������
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ���/С��ģʽ��ֵΪ#AMHW_LCD_PIXEL_LITTLE_ENDIAN
 *                       ��#AMHW_LCD_PIXEL_BIG_ENDIAN
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_pixel_endian_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_PIXEL_BIG_ENDIAN;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_PIXEL_BIG_ENDIAN;
}

/**
 * \brief ����Ƚ��ж�(VComp)����ѡ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] type     : �ж����ͣ�ֵΪAMHW_LCD_VCOMP_*(#AMHW_LCD_VCOMP_VERTICAL_SYNC)
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_vcomp_type_sel (amhw_lcd_t *p_hw_lcd, uint32_t type)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_VCOMP_FRONT_PORCH;
    p_hw_lcd->ctrl |= type & AMHW_LCD_VCOMP_FRONT_PORCH;
}

/**
 * \brief LCD DMA FIFOˮλ������
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : DMA FIFOˮλ�ߣ�ֵΪ#AMHW_LCD_DMA_FIFO_EMPTY4
 *                       ��#AMHW_LCD_DMA_FIFO_EMPTY8
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_dma_watermark_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->ctrl &= ~AMHW_LCD_DMA_FIFO_EMPTY8;
    p_hw_lcd->ctrl |= flag & AMHW_LCD_DMA_FIFO_EMPTY8;
}

/*****************************************************************************/
/**
 * \name LCDʱ��������Ϣ
 * \anchor grp_amhw_lcd_pol_flags
 * @{
 */
#define AMHW_LCD_POL_PCD_LO(n)   ((n) & 0x1F)   /**< \brief ��ʾ��ʱ�ӷ�Ƶ����5λ */

#define AMHW_LCD_POL_CLKSEL_CCLK    (0)         /**< \brief LCDʱ��ԴCCLK*/
#define AMHW_LCD_POL_CLKSEL_CLKIN   (1 << 5)    /**< \brief LCDʱ��ԴLCD_CLKIN */

/** \brief ACƫ�ùܽ�Ƶ�� */
#define AMHW_LCD_POL_ACB(n)    (((n) & 0x1F) << 6)

#define AMHW_LCD_POL_IVS_HI    (0)       /**< \brief LCD_FP�ܽŸߵ�ƽ��Ч */
#define AMHW_LCD_POL_IVS_LO    (1 << 11) /**< \brief LCD_FP�ܽŵ͵�ƽ��Ч */

#define AMHW_LCD_POL_IHS_HI    (0)       /**< \brief LCD_LP�ܽŸߵ�ƽ��Ч */
#define AMHW_LCD_POL_IHS_LO    (1 << 12) /**< \brief LCD_LP�ܽŵ͵�ƽ��Ч */

#define AMHW_LCD_POL_IPC_RISE  (0)       /**< \brief ������LCD_DCLK�����ر����� */
#define AMHW_LCD_POL_IPC_FALL  (1 << 13) /**< \brief ������LCD_DCLK�����ر����� */

#define AMHW_LCD_POL_IOE_HI    (0)       /**< \brief LCD_ENAB_M�ܽ�TFTģʽ�ߵ�ƽ��Ч */
#define AMHW_LCD_POL_IOE_LO    (1 << 14) /**< \brief LCD_ENAB_M�ܽ�TFTģʽ�͵�ƽ��Ч */

/** \brief ÿ��LCD_DCLKʱ����  */
#define AMHW_LCD_POL_CPL(n)    ((((n) - 1) & 0x3FF) << 16)

/** \brief ��·����ʱ�ӷ�Ƶ�� */
#define AMHW_LCD_POL_BCD_SET   (1 << 26)

/** \brief ��ʾ��ʱ�ӷ�Ƶ����5λ */
#define AMHW_LCD_POL_PCD_HI(n) (((n) & 0x1F) << 27)

/** @} */

/**
 * \brief LCDʱ��������Ϣ����
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : LCDʱ��������Ϣ,�μ�
 *                       \ref grp_amhw_lcd_pol_flags "LCD POL FLAG"
 * \return ��
 */
am_static_inline
void amhw_lcd_pol_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->pol = flag;
}

/**
 * \name LCDˮƽʱ�������Ϣ
 * \anchor grp_amhw_lcd_timh_flag
 * @{
 */

/** \brief ����ÿ��ʱ���� */
#define AMHW_LCD_TIMH_PPL(n) (((((n) >> 4) - 1) & 0x3F) << 2)

/** \brief ͬ������ʱ���� */
#define AMHW_LCD_TIMH_HSW(n) ((((n) - 1) & 0xFF) << 8)

/** \brief ˮƽǰ��ʱ���� */
#define AMHW_LCD_TIMH_HFP(n) ((((n) - 1) & 0xFF) << 16)

/** \brief ˮƽ����ʱ���� */
#define AMHW_LCD_TIMH_HBP(n) ((((n) - 1) & 0xFF) << 24)
/** @} */

/**
 * \brief ����ˮƽʱ�������Ϣ
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ˮƽʱ����Ϣ���μ�
 *                       \ref grp_amhw_lcd_timh_flag "LCD TIMH FLAG"
 * \return    ��
 */
am_static_inline
void amhw_lcd_timh_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->timh = flag;
}

/**
 * \name LCD��ֱʱ�������Ϣ
 * \anchor grp_amhw_lcd_timv_flag
 * @{
 */

/** \brief ÿ��������Ч����n */
#define AMHW_LCD_TIMV_LPP(n) ((((n) - 1) & 0x3FF) <<  0)

/** \brief ˮƽͬ������ */
#define AMHW_LCD_TIMV_VSW(n) ((((n) - 1) & 0x3F)  << 10)

/** \brief ��ֱǰ�� */
#define AMHW_LCD_TIMV_VFP(n) (((n) & 0xFF)  << 16)

/** \brief ��ֱ���� */
#define AMHW_LCD_TIMV_VBP(n) (((n) & 0xFF)  << 24)
/** @} */

/**
 * \brief ���ô�ֱʱ�������Ϣ
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ��ֱʱ����Ϣ���μ�
 *                       \ref grp_amhw_lcd_timv_flag "LCD TIMV FLAG"
 * \return    ��
 */
am_static_inline
void amhw_lcd_timv_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->timv = flag;
}

/**
 * \brief ������ĩ�ӳ�LCDCLKʱ��������
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] val      : ��ĩ�ӳ�LCDCLKʱ��������
 * \return    ��
 */
am_static_inline
void amhw_lcd_le_dly_set (amhw_lcd_t *p_hw_lcd, uint32_t val)
{
    p_hw_lcd->le |= (val - 1) & 0x7F;
}

/**
 * \brief ��ĩʹ������
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] state    : ��ĩʹ��/ʧ�ܣ�ֵΪTRUE��ʹ�ܣ���FALSE��ʧ�ܣ�
 * \return    ��
 */
am_static_inline
void amhw_lcd_le_enable (amhw_lcd_t *p_hw_lcd, bool_t state)
{
    if (state == FALSE) {
        p_hw_lcd->le &= ~(1 << 16);
    } else {
        p_hw_lcd->le |= (1 << 16);
    }
}

/**
 * \brief ����LCD����֡��ַ
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] addr     : ����֡��ַ
 * \return ��
 * \note д���ַ����˫�ֶ���
 */
am_static_inline
void amhw_lcd_upbase_set (amhw_lcd_t *p_hw_lcd, uint32_t addr)
{
    p_hw_lcd->upbase = addr;
}

/**
 * \brief ����LCD����֡��ַ
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] addr     : ����֡��ַ
 * \return ��
 * \note д���ַ����˫�ֶ���
 */
am_static_inline
void amhw_lcd_lpbase_set (amhw_lcd_t *p_hw_lcd, uint32_t addr)
{
    p_hw_lcd->lpbase = addr;
}

/**
 * \brief ��ȡLCD������ǰ��ַ
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \return LCD������ǰ��ַ
 */
am_static_inline
uint32_t amhw_lcd_upcur_addr_get (amhw_lcd_t *p_hw_lcd)
{
    return p_hw_lcd->upcurr;
}

/**
 * \brief ��ȡLCD������ǰ��ַ
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \return LCD������ǰ��ַ
 */
am_static_inline
uint32_t amhw_lcd_lpcur_addr_get (amhw_lcd_t *p_hw_lcd)
{
    return p_hw_lcd->lpcurr;
}

/**
 * \brief LCD�ж����Ͷ���
 */
typedef enum amhw_lcd_int_type {
    AMHW_LCD_INT_FUF    = (1 << 0x1),  /**< \brief FIFO����ж�  */
    AMHW_LCD_INT_LNBU   = (1 << 0x2),  /**< \brief LCD�»�ַ�����ж� */
    AMHW_LCD_INT_VCOMP  = (1 << 0x3),  /**< \brief ����Ƚ��ж�  */
    AMHW_LCD_INT_BER    = (1 << 0x4),  /**< \brief AHB���豸�����ж�ʹ�� */
    AMHW_LCD_INT_MASK   = (0xF << 1)   /**< \brief LCD�ж����� */
} amhw_lcd_int_type_t;

/**
 * \brief ʹ��/ʧ��LCDָ���ж�
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] type     : LCD�ж�����
 * \param[in] state    : ָ���ж�ʹ��/ʧ�ܣ�ֵΪTRUE��ʹ�ܣ���FALSE��ʧ�ܣ�
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_int_enable (amhw_lcd_t         *p_hw_lcd,
                          amhw_lcd_int_type_t type,
                          bool_t              state)
{
    if (state == FALSE) {
        p_hw_lcd->intmsk &= ~(uint32_t)type;
    } else {
        p_hw_lcd->intmsk |=  (uint32_t)type;
    }
}

/**
 * \brief ָ��LCDԭʼ�ж��Ƿ���λ
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] type     : LCD�ж�����
 *
 * \retval    TRUE     : ָ��ԭʼ�ж���λ
 * \retval    FALSE    : ָ��ԭʼ�ж�δ��λ
 */
am_static_inline
bool_t amhw_lcd_intraw_get (amhw_lcd_t         *p_hw_lcd,
                             amhw_lcd_int_type_t type)
{
    return (bool_t)((p_hw_lcd->intraw & (uint32_t)type) != 0);
}

/**
 * \brief ָ��LCD�������Σ��ж��Ƿ���λ
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] type     : LCD�ж�����
 *
 * \retval    TRUE     : ָ���ж���λ
 * \retval    FALSE    : ָ���ж�δ��λ
 */
am_static_inline
bool_t amhw_lcd_intstat_get (amhw_lcd_t         *p_hw_lcd,
                             amhw_lcd_int_type_t type)
{
    return (bool_t)((p_hw_lcd->intstat & (uint32_t)type) != 0);
}

/**
 * \brief ���ָ��LCD�ж�
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] type     : ָ���ж����ͣ�ֵΪAMHW_LCD_INT_*(#AMHW_LCD_INT_FUF)
 *                       �ɻ����ͬʱ�������жϡ�
 * \return ��
 */
am_static_inline
void amhw_lcd_int_clr (amhw_lcd_t *p_hw_lcd,
                       uint32_t    type)
{
    p_hw_lcd->intclr = type;
}

/**
 * \brief ���ز�ɫ��ɫ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] p_pal    : ��ɫ��ɫ������
 * \param[in] size     : ��Ҫ���õĵ�ɫ��Ĵ�����Ŀ
 * \return    ��
 */
void amhw_lcd_palette_load (amhw_lcd_t *p_hw_lcd,
                            uint32_t   *p_pal,
                            uint8_t     size);
/*****************************************************************************/
/**
 * \brief ���ù��ͼ��
 *
 * \param[in] p_hw_lcd  : ָ��LCD�Ĵ������ָ��
 * \param[in] num       : ���ͼ���ţ�ֵΪ0/1/2/3
 * \param[in] p_cursor  : ���ͼ�����ݵ�ַ
 * \param[in] size      : ���ͼ���С
 *
 * \return ��
 *
 * \note �����ͼ���СΪ64*64������ͼ����ֻ��Ϊ0
 */
void amhw_lcd_crsr_img_set (amhw_lcd_t     *p_hw_lcd,
                            uint8_t         num,
                            const uint32_t *p_cursor,
                            uint16_t        size);

/**
 * \brief ʹ����ʾָ�����
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] num      : ��ʾ�Ĺ�ֵ꣬Ϊ0~3
 * \return ��
 */
am_static_inline
void amhw_lcd_cursor_enable (amhw_lcd_t *p_hw_lcd, uint8_t num)
{
    p_hw_lcd->crsr_ctrl = 0x01 | (num << 4);
}

/**
 * \brief �رչ����ʾ
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_cursor_disable (amhw_lcd_t *p_hw_lcd)
{
    p_hw_lcd->crsr_ctrl = 0;
}

/**
 * \name LCD���������Ϣ����
 * \anchor grp_amhw_lcd_crsr_cfg_flag
 * @{
 */
#define AMHW_LCD_CRSR_SIZE_32  (0)  /**< \brief ���ߴ�Ϊ32*32  */
#define AMHW_LCD_CRSR_SIZE_64  (1)  /**< \brief ���ߴ�Ϊ64*64  */

#define AMHW_LCD_CRSR_FRAME_SYNC    (1 << 1)  /**< \brief ���������֡ͬ������ͬ��  */
#define AMHW_LCD_CRSR_FRAME_NO_SYNC (0)       /**< \brief ������겻ͬ��  */
/** @} */

/**
 * \brief ���������Ϣ����
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ���������Ϣ���μ�
 *                       \ref grp_amhw_lcd_crsr_cfg_flag "CRSR CFG Flag"
 *
 * \return ��
 *
 */
am_static_inline
void amhw_lcd_cursor_cfg_set (amhw_lcd_t *p_hw_lcd, uint32_t flag)
{
    p_hw_lcd->crsr_cfg = flag & 0x03;
}

/**
 * \name LCD����ɫ������
 * \anchor grp_amhw_lcd_crsr_palette_flag
 * @{
 */

/** \brief ����ɫ���ɫ���� */
#define AMHW_LCD_CRSR_PAL_RED(n)   ((n) & 0xFF)

/** \brief ����ɫ����ɫ���� */
#define AMHW_LCD_CRSR_PAL_GREEN(n) (((n) & 0xFF) <<  8)

/** \brief ����ɫ����ɫ���� */
#define AMHW_LCD_CRSR_PAL_BLUE(n)  (((n) & 0xFF) << 16)
/** @} */

/**
 * \brief ���ù���ɫ��0��Ϣ
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ����ɫ����Ϣ��
 *                       �μ�\ref grp_amhw_lcd_crsr_palette_flag "CRSR Palette Flag"
 *
 * \return ��
 *
 */
am_static_inline
void amhw_lcd_crsr_palette0_load (amhw_lcd_t *p_hw_lcd,
                                  uint32_t    flag)
{
    p_hw_lcd->crsr_pal0 = flag;
}

/**
 * \brief ���ù���ɫ��1��Ϣ
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] flag     : ����ɫ����Ϣ��
 *                       �μ�\ref grp_amhw_lcd_crsr_palette_flag "CRSR Palette Flag"
 *
 * \return ��
 *
 */
am_static_inline
void amhw_lcd_crsr_palette1_load (amhw_lcd_t *p_hw_lcd,
                                  uint32_t    flag)
{
    p_hw_lcd->crsr_pal1 = flag;
}

/**
 * \brief ���ù��XYλ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] x        : �������X����
 * \param[in] y        : �������Y����
 *
 * \return ��
 *
 */
am_static_inline
void amhw_lcd_crsr_xy_set (amhw_lcd_t *p_hw_lcd,
                           uint16_t    x,
                           uint16_t    y)
{
    p_hw_lcd->crsr_xy = (x & 0x3FF) | ((y & 0x3FF) << 16);
}

/**
 * \brief ��ȡ���XYλ����Ϣ
 *
 * \param[in]  p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[out] *x       : �������X����
 * \param[out] *y       : �������Y����
 *
 * \return ��
 *
 */
am_static_inline
void amhw_lcd_crsr_xy_get (amhw_lcd_t *p_hw_lcd,
                           uint16_t   *x,
                           uint16_t   *y)
{
    *x = p_hw_lcd->crsr_xy & 0x3FF;
    *y = (p_hw_lcd->crsr_xy >> 16) & 0x3FF;
}

/**
 * \brief ���ù�����λ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] x        : X����Ĺ�����λ��
 * \param[in] y        : Y����Ĺ�����λ��
 *
 * \return ��
 * \note ȷ��ָ��֡�ļ�����λ����Ϣһ�£����ڲ���XY�Ĵ���ǰִ�иò�����
 */
am_static_inline
void amhw_lcd_crsr_clip_set (amhw_lcd_t *p_hw_lcd,
                             uint16_t    x,
                             uint16_t    y)
{
    p_hw_lcd->crsr_clip = (x & 0x3F) | ((y & 0x3F) << 8);
}

/**
 * \brief ���ù���ж�ʹ��
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 * \param[in] state    : ����ж�ʹ��ֵ��ֵΪTRUE���ж�ʹ��,
 *                       ֵΪFALSE���ж�ʧ��
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_crsr_int_enable (amhw_lcd_t *p_hw_lcd,
                               bool_t      state)
{
    p_hw_lcd->crsr_intmsk &= ~0x1UL;
    p_hw_lcd->crsr_intmsk |= (uint8_t)state & 0x01;
}

/**
 * \brief �������ж�
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lcd_crsr_int_clr (amhw_lcd_t *p_hw_lcd)
{
    p_hw_lcd->crsr_intclr = 0x01;
}

/**
 * \brief ��ȡ���ԭʼ�ж�״̬
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 *
 * \retval TRUE  : ���ԭʼ�ж�״̬��λ
 * \retval FALSE : ���ԭʼ�ж�δ��λ
 */
am_static_inline
bool_t amhw_lcd_crsr_intraw_get (amhw_lcd_t *p_hw_lcd)
{
    return (bool_t)((p_hw_lcd->crsr_intraw & 0x01) != 0);
}

/**
 * \brief ��ȡ��꣨�����Σ��ж�״̬
 *
 * \param[in] p_hw_lcd : ָ��LCD�Ĵ������ָ��
 *
 * \retval TRUE  : ����ж�״̬��λ
 * \retval FALSE : ����ж�δ��λ
 */
am_static_inline
bool_t amhw_lcd_crsr_intstat_get (amhw_lcd_t *p_hw_lcd)
{
    return (bool_t)((p_hw_lcd->crsr_intstat & 0x01) != 0);
}

/**
 * @} amhw_if_lcd
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_LCD_H */

/* end of file */

