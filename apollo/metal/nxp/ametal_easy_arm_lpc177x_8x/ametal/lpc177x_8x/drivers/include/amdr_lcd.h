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
 * \brief LCD����������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-23  cod, first implementation.
 * \endinternal
 */

#ifndef __AMDR_LCD_H
#define __AMDR_LCD_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lcd.h"
#include "amhw_syscon.h"

/**
 * \addtogroup amdr_if_lcd
 * \copydoc amdr_lcd.h
 * @{
 */

/**
 * \brief LCD��Ļ����
 */
typedef enum amdr_lcd_type {
    AMDR_LCD_TFT,      /**< \brief TFTS��ʾ�� */
    AMDR_LCD_MONO_4,   /**< \brief 4bit�ӿڿ��STN��ʾ��  */
    AMDR_LCD_MONO_8,   /**< \brief 8bit�ӿڿ��STN��ʾ��  */
    AMDR_LCD_CSTN,     /**< \brief ��ɫSTN��ʾ��  */
} amdr_lcd_type_t;

/**
 * \brief ����λ
 */
typedef enum amdr_lcd_bpp {
    AMDR_LCD_BPP_1           = (0 << 1),  /**< \brief 1bpp  */
    AMDR_LCD_BPP_2           = (1 << 1),  /**< \brief 2bpp  */
    AMDR_LCD_BPP_4           = (2 << 1),  /**< \brief 4bpp  */
    AMDR_LCD_BPP_8           = (3 << 1),  /**< \brief 8bpp  */
    AMDR_LCD_BPP_16          = (4 << 1),  /**< \brief 16bpp */
    AMDR_LCD_BPP_24          = (5 << 1),  /**< \brief 24bpp����ΪTFT��ʾ����*/
    AMDR_LCD_BPP_16_565Mode  = (6 << 1),  /**< \brief 16bpp 5:6:5ģʽ */
    AMDR_LCD_BPP_12_444Mode  = (7 << 1),  /**< \brief 12bpp 4:4:4ģʽ */
} amdr_lcd_bpp_t;

/**
 * \brief ������ѡ��
 */
typedef enum amdr_lcd_panel
{
    AMDR_LCD_PANEL_UPPER,    /**< \brief ����  */
    AMDR_LCD_PANEL_LOWER,    /**< \brief ����  */
} amdr_lcd_panel_t;

/**
 * \brief LCD������Ϣ
 */
typedef struct amdr_lcd_cfginfo {

    /** \brief ��Ļ���ͣ�ֵΪAMDR_LCD_*(#AMDR_LCD_TFT)  */
    amdr_lcd_type_t  lcd_type;

    /** \brief ˮƽ����  */
    uint16_t         h_size;

    /** \brief ��ֱ ���� */
    uint16_t         v_size;

    /** \brief ˮƽʱ��������Ϣ���μ�\ref grp_amhw_lcd_timh_flag */
    uint32_t         hconfig;

    /** \brief ��ֱʱ��������Ϣ���μ�\ref grp_amhw_lcd_timv_flag */
    uint32_t         vconfig;

    /** \brief ʱ�����źż���������Ϣ���μ�\ref grp_amhw_lcd_pol_flags */
    uint32_t         polarity;

    /** \brief LCD��ʱ��Ƶ��  */
    uint32_t         panel_clk;

    /** \brief ����λѡ��ֵΪ AMDR_LCD_BPP_*(#AMDR_LCD_BPP_1) */
    amdr_lcd_bpp_t   bpp;

    /** \brief ˫��ѡ��˫��ֵΪTRUE������ֵΪFALSE */
    bool_t           dual;

    /** \brief BGR��ʽѡ����ΪBGR��ʽֵΪTRUE��RGB��ʽֵΪFALSE */
    bool_t           bgr;

    /** \brief �ڴ��ֽڴ��ģʽѡ�񣬴��ģʽֵΪTRUE����ֵ֮ΪFALSE */
    bool_t           big_endian_byte;

    /** \brief �����ֽڴ��ģʽѡ�񣬴��ģʽֵΪTRUE����ֵ֮ΪFALSE */
    bool_t           big_endian_pixel;

    /** \brief ����������   */
    uint32_t         upbase;

    /** \brief ����������   */
    uint32_t         lpbase;
} amdr_lcd_cfginfo_t;

/**
 * \brief LCD ���������Ϣ
 */
typedef struct amdr_lcd_cursor_cfginfo {
    uint32_t  cursor_num;     /**< \brief ����ţ�ֵΪ0~3  */
    uint32_t  img_addr;       /**< \brief ���ͼ�񻺳�����ַ   */
    uint8_t   size;           /**< \brief ���ߴ��С(32*32)��(64*64),ֵΪ32��64 */
    bool_t    framesync;      /**< \brief ���֡ͬ����ΪTRUE��ͬ����FALSE��ͬ��  */
    uint32_t  palette[2];     /**< \brief ����ɫ����Ϣ  */
} amdr_lcd_cursor_cfginfo_t;


/** \brief LCD�豸��Ϣ */
typedef struct amdr_lcd_devinfo {

    amhw_lcd_t         *p_hw_lcd;        /**< \brief ָ��LCD�Ĵ������ָ�� */

    amhw_syscon_t      *p_hw_syscon;     /**< \brief ָ��ϵͳ���ƼĴ������ָ�� */

    uint8_t             inum;            /**< \brief LCD�жϺ� */

    amdr_lcd_cfginfo_t *p_lcd_cfginfo;   /**< \brief LCD������Ϣ */

} amdr_lcd_devinfo_t;

/**
 * \brief LCD�豸ʵ��
 */
typedef struct amdr_lcd_dev {

    /** \brief ָ��LCD�豸��Ϣ��ָ�� */
    const amdr_lcd_devinfo_t *p_devinfo;

} amdr_lcd_dev_t;

/**
 * \brief ����LCD��Ļͼ��
 *
 * \param[in] panel   : ������ѡ��ֵΪ#AMDR_LCD_PANEL_UPPER��#AMDR_LCD_PANEL_LOWER
 * \param[in] p_img   : ͼ�񻺳���
 *
 * \retval  AM_OK     : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
int amdr_lcd_image_set (amdr_lcd_panel_t panel, const uint8_t *p_img);

/**
 * \brief ��һ�����ص�
 *
 * \param[in] panel   : ������ѡ��ֵΪ#AMDR_LCD_PANEL_UPPER��#AMDR_LCD_PANEL_LOWER
 * \param[in] x       : ���ص�x��λ��
 * \param[in] y       : ���ص�y��λ��
 * \param[in] color   : ���ص���ɫ
 *
 * \retval  AM_OK     : ���óɹ�
 * \retval -AM_EINVAL : ��������
 */
int amdr_lcd_pixel_set (amdr_lcd_panel_t panel,
                        uint32_t         x,
                        uint32_t         y,
                        uint32_t         color);

/**
 * \brief ָ��λ�ü���ͼƬ
 *
 * \param[in] panel    : ������ѡ��ֵΪ#AMDR_LCD_PANEL_UPPER��#AMDR_LCD_PANEL_LOWER
 * \param[in] start_x  : ͼƬx����ʼλ��
 * \param[in] start_y  : ͼƬy����ʼλ��
 * \param[in] hsize    : ͼƬˮƽ���س���
 * \param[in] vsize    : ͼ��ֱ���س���
 * \param[in] p_picbuf : ͼƬ������
 *
 * \retval  AM_OK      : ���óɹ�
 * \retval -AM_EINVAL  : ��������
 */
void amdr_lcd_pic_load (amdr_lcd_panel_t panel,
                        uint16_t         start_x,
                        uint16_t         start_y,
                        uint32_t         hsize,
                        uint32_t         vsize,
                        const uint8_t   *p_picbuf);

/**
 * \brief LCDָ��������䷽��
 *
 * \param[in] panel    : ������ѡ��ֵΪ#AMDR_LCD_PANEL_UPPER��#AMDR_LCD_PANEL_LOWER
 * \param[in] start_x  : ����x����ʼλ��
 * \param[in] start_y  : ����y����ʼλ��
 * \param[in] end_x    : ����x����ֹλ��
 * \param[in] end_y    : ����y����ֹλ��
 * \param[in] color    : ���������ɫ
 *
 * \return    ��
 */
void amdr_lcd_rect_fill (amdr_lcd_panel_t panel,
                         uint32_t         start_x,
                         uint32_t         start_y,
                         uint32_t         end_x,
                         uint32_t         end_y,
                         uint32_t         color);

/**
 * \brief LCD����ʼ������
 *
 * \param[in] p_cfginfo : ���������Ϣ
 *
 * \retval  AM_OK       : ��ʼ�����óɹ�
 * \retval -AM_EINVAL   : ��������
 *
 */
int amdr_lcd_cursor_init (amdr_lcd_cursor_cfginfo_t *p_cfginfo);

/**
 * \brief �ƶ����
 *
 * \param[in] x  : ���x��λ��
 * \param[in] y  : ���y��λ��
 *
 * \return    ��
 */
void amdr_lcd_cursor_move (uint16_t x, uint16_t y);

/**
 * \brief ʹ��/ʧ��ָ�����
 *
 * \param[in] num    : ����ţ� 0~3
 * \param[in] enable : ʹ��/ʧ�ܣ�ֵΪTRUEΪʹ�ܣ�ΪFALSEΪʧ��
 *
 * \return    ��
 */
int amdr_lcd_cursor_enable (uint8_t num, bool_t enable);

/**
 * \brief LCD��ʼ��
 *
 * \param[in] p_dev     : ָ��LCD�豸��ָ��
 * \param[in] p_devinfo : ָ��LCD�豸��Ϣ��ָ��
 *
 * \retval  AM_OK       : ��ʼ���ɹ�
 *
 * \note ���ӿ�Ĭ��ʹ���ڲ�ʱ����ΪLCDʱ��
 */
int amdr_lcd_init(amdr_lcd_dev_t *p_dev, const amdr_lcd_devinfo_t *p_devinfo);

/**
 * \brief LCDȥ��ʼ��
 *
 * \param[in] p_dev : ָ��LCD�豸��ָ��
 *
 * \return  ��
 */
void amdr_lcd_deinit(amdr_lcd_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_LCD_H */

/* end of file */
