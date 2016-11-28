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
 * \brief LCD驱动及服务接口
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
 * \brief LCD屏幕类型
 */
typedef enum amdr_lcd_type {
    AMDR_LCD_TFT,      /**< \brief TFTS显示屏 */
    AMDR_LCD_MONO_4,   /**< \brief 4bit接口宽度STN显示屏  */
    AMDR_LCD_MONO_8,   /**< \brief 8bit接口宽度STN显示屏  */
    AMDR_LCD_CSTN,     /**< \brief 彩色STN显示屏  */
} amdr_lcd_type_t;

/**
 * \brief 象素位
 */
typedef enum amdr_lcd_bpp {
    AMDR_LCD_BPP_1           = (0 << 1),  /**< \brief 1bpp  */
    AMDR_LCD_BPP_2           = (1 << 1),  /**< \brief 2bpp  */
    AMDR_LCD_BPP_4           = (2 << 1),  /**< \brief 4bpp  */
    AMDR_LCD_BPP_8           = (3 << 1),  /**< \brief 8bpp  */
    AMDR_LCD_BPP_16          = (4 << 1),  /**< \brief 16bpp */
    AMDR_LCD_BPP_24          = (5 << 1),  /**< \brief 24bpp（仅为TFT显示屏）*/
    AMDR_LCD_BPP_16_565Mode  = (6 << 1),  /**< \brief 16bpp 5:6:5模式 */
    AMDR_LCD_BPP_12_444Mode  = (7 << 1),  /**< \brief 12bpp 4:4:4模式 */
} amdr_lcd_bpp_t;

/**
 * \brief 上下屏选择
 */
typedef enum amdr_lcd_panel
{
    AMDR_LCD_PANEL_UPPER,    /**< \brief 上屏  */
    AMDR_LCD_PANEL_LOWER,    /**< \brief 下屏  */
} amdr_lcd_panel_t;

/**
 * \brief LCD配置信息
 */
typedef struct amdr_lcd_cfginfo {

    /** \brief 屏幕类型，值为AMDR_LCD_*(#AMDR_LCD_TFT)  */
    amdr_lcd_type_t  lcd_type;

    /** \brief 水平分量  */
    uint16_t         h_size;

    /** \brief 垂直 分量 */
    uint16_t         v_size;

    /** \brief 水平时序配置信息，参见\ref grp_amhw_lcd_timh_flag */
    uint32_t         hconfig;

    /** \brief 垂直时序配置信息，参见\ref grp_amhw_lcd_timv_flag */
    uint32_t         vconfig;

    /** \brief 时钟与信号极性配置信息，参见\ref grp_amhw_lcd_pol_flags */
    uint32_t         polarity;

    /** \brief LCD屏时钟频率  */
    uint32_t         panel_clk;

    /** \brief 象素位选择，值为 AMDR_LCD_BPP_*(#AMDR_LCD_BPP_1) */
    amdr_lcd_bpp_t   bpp;

    /** \brief 双屏选择，双屏值为TRUE，单屏值为FALSE */
    bool_t           dual;

    /** \brief BGR格式选择，若为BGR格式值为TRUE，RGB格式值为FALSE */
    bool_t           bgr;

    /** \brief 内存字节大端模式选择，大端模式值为TRUE，反之值为FALSE */
    bool_t           big_endian_byte;

    /** \brief 象素字节大端模式选择，大端模式值为TRUE，反之值为FALSE */
    bool_t           big_endian_pixel;

    /** \brief 上屏缓冲区   */
    uint32_t         upbase;

    /** \brief 下屏缓冲区   */
    uint32_t         lpbase;
} amdr_lcd_cfginfo_t;

/**
 * \brief LCD 光标配置信息
 */
typedef struct amdr_lcd_cursor_cfginfo {
    uint32_t  cursor_num;     /**< \brief 光标编号，值为0~3  */
    uint32_t  img_addr;       /**< \brief 光标图像缓冲区地址   */
    uint8_t   size;           /**< \brief 光标尺寸大小(32*32)或(64*64),值为32或64 */
    bool_t    framesync;      /**< \brief 光标帧同步，为TRUE则同步，FALSE不同步  */
    uint32_t  palette[2];     /**< \brief 光标调色板信息  */
} amdr_lcd_cursor_cfginfo_t;


/** \brief LCD设备信息 */
typedef struct amdr_lcd_devinfo {

    amhw_lcd_t         *p_hw_lcd;        /**< \brief 指向LCD寄存器块的指针 */

    amhw_syscon_t      *p_hw_syscon;     /**< \brief 指向系统控制寄存器块的指针 */

    uint8_t             inum;            /**< \brief LCD中断号 */

    amdr_lcd_cfginfo_t *p_lcd_cfginfo;   /**< \brief LCD配置信息 */

} amdr_lcd_devinfo_t;

/**
 * \brief LCD设备实例
 */
typedef struct amdr_lcd_dev {

    /** \brief 指向LCD设备信息的指针 */
    const amdr_lcd_devinfo_t *p_devinfo;

} amdr_lcd_dev_t;

/**
 * \brief 设置LCD屏幕图像
 *
 * \param[in] panel   : 上下屏选择，值为#AMDR_LCD_PANEL_UPPER或#AMDR_LCD_PANEL_LOWER
 * \param[in] p_img   : 图像缓冲区
 *
 * \retval  AM_OK     : 设置成功
 * \retval -AM_EINVAL : 参数错误
 */
int amdr_lcd_image_set (amdr_lcd_panel_t panel, const uint8_t *p_img);

/**
 * \brief 画一个象素点
 *
 * \param[in] panel   : 上下屏选择，值为#AMDR_LCD_PANEL_UPPER或#AMDR_LCD_PANEL_LOWER
 * \param[in] x       : 象素点x轴位置
 * \param[in] y       : 象素点y轴位置
 * \param[in] color   : 象素点颜色
 *
 * \retval  AM_OK     : 设置成功
 * \retval -AM_EINVAL : 参数错误
 */
int amdr_lcd_pixel_set (amdr_lcd_panel_t panel,
                        uint32_t         x,
                        uint32_t         y,
                        uint32_t         color);

/**
 * \brief 指定位置加载图片
 *
 * \param[in] panel    : 上下屏选择，值为#AMDR_LCD_PANEL_UPPER或#AMDR_LCD_PANEL_LOWER
 * \param[in] start_x  : 图片x轴起始位置
 * \param[in] start_y  : 图片y轴起始位置
 * \param[in] hsize    : 图片水平象素长度
 * \param[in] vsize    : 图像垂直象素长度
 * \param[in] p_picbuf : 图片缓冲区
 *
 * \retval  AM_OK      : 设置成功
 * \retval -AM_EINVAL  : 参数错误
 */
void amdr_lcd_pic_load (amdr_lcd_panel_t panel,
                        uint16_t         start_x,
                        uint16_t         start_y,
                        uint32_t         hsize,
                        uint32_t         vsize,
                        const uint8_t   *p_picbuf);

/**
 * \brief LCD指定区域填充方框
 *
 * \param[in] panel    : 上下屏选择，值为#AMDR_LCD_PANEL_UPPER或#AMDR_LCD_PANEL_LOWER
 * \param[in] start_x  : 方框x轴起始位置
 * \param[in] start_y  : 方框y轴起始位置
 * \param[in] end_x    : 方框x轴终止位置
 * \param[in] end_y    : 方框y轴终止位置
 * \param[in] color    : 方框填充颜色
 *
 * \return    无
 */
void amdr_lcd_rect_fill (amdr_lcd_panel_t panel,
                         uint32_t         start_x,
                         uint32_t         start_y,
                         uint32_t         end_x,
                         uint32_t         end_y,
                         uint32_t         color);

/**
 * \brief LCD光标初始化配置
 *
 * \param[in] p_cfginfo : 光标配置信息
 *
 * \retval  AM_OK       : 初始化配置成功
 * \retval -AM_EINVAL   : 参数错误
 *
 */
int amdr_lcd_cursor_init (amdr_lcd_cursor_cfginfo_t *p_cfginfo);

/**
 * \brief 移动光标
 *
 * \param[in] x  : 光标x轴位置
 * \param[in] y  : 光标y轴位置
 *
 * \return    无
 */
void amdr_lcd_cursor_move (uint16_t x, uint16_t y);

/**
 * \brief 使能/失能指定光标
 *
 * \param[in] num    : 光标编号， 0~3
 * \param[in] enable : 使能/失能，值为TRUE为使能，为FALSE为失能
 *
 * \return    无
 */
int amdr_lcd_cursor_enable (uint8_t num, bool_t enable);

/**
 * \brief LCD初始化
 *
 * \param[in] p_dev     : 指向LCD设备的指针
 * \param[in] p_devinfo : 指向LCD设备信息的指针
 *
 * \retval  AM_OK       : 初始化成功
 *
 * \note 本接口默认使用内部时钟作为LCD时钟
 */
int amdr_lcd_init(amdr_lcd_dev_t *p_dev, const amdr_lcd_devinfo_t *p_devinfo);

/**
 * \brief LCD去初始化
 *
 * \param[in] p_dev : 指向LCD设备的指针
 *
 * \return  无
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
