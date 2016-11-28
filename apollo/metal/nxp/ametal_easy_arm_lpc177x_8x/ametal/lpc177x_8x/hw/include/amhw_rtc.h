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
 * \brief RTC硬件操作接口
 * 
 * \internal
 * \par Modification history
 * - 1.02 15-09-18  cod, add Event Monitor/Recorder.
 * - 1.01 15-08-20  cod, fix code style and comments,a little improve.
 * - 1.00 15-07-09  ben, first implementation.
 * \endinternal
 */

#ifndef __AMHW_RTC_H
#define __AMHW_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"

/** 
 * \addtogroup amhw_if_rtc
 * \copydoc amhw_rtc.h
 * @{
 */

/**
 * \brief 实时时钟寄存器块的结构体
 */
typedef struct amhw_rtc {                                                                 
    __IO uint32_t ilr;          /**< \brief 中断位置寄存器 */ 
    __I  uint32_t reserved0;    /**< \brief 保留 */
    __IO uint32_t ccr;          /**< \brief 时钟控制 */
    __IO uint32_t ciir;         /**< \brief 计数中断寄存器 */
    __IO uint32_t amr;          /**< \brief 报警掩码寄存器 */
    __I  uint32_t ctime0;       /**< \brief 完整时间寄存器0 0 */
    __I  uint32_t ctime1;       /**< \brief 完整时间寄存器0 1 */
    __I  uint32_t ctime2;       /**< \brief 完整时间寄存器0 2 */
    __IO uint32_t sec;          /**< \brief 秒计数器 */
    __IO uint32_t min;          /**< \brief 分计数器 */
    __IO uint32_t hour;         /**< \brief 时计数器 */
    __IO uint32_t dom;          /**< \brief 日期（月）寄存器 */
    __IO uint32_t dow;          /**< \brief 星期寄存器 */
    __IO uint32_t doy;          /**< \brief 日期（年）寄存器 */
    __IO uint32_t month;        /**< \brief 月寄存器 */
    __IO uint32_t year;         /**< \brief 年寄存器 */
    __IO uint32_t calibration;  /**< \brief 校准值寄存器 */
    __IO uint32_t gpreg0;       /**< \brief 通用寄存器 0 */
    __IO uint32_t gpreg1;       /**< \brief 通用寄存器 1 */
    __IO uint32_t gpreg2;       /**< \brief 通用寄存器 2 */
    __IO uint32_t gpreg3;       /**< \brief 通用寄存器 3 */
    __IO uint32_t gpreg4;       /**< \brief 通用寄存器 4 */
    __IO uint32_t rtc_auxen;    /**< \brief RTC辅助使能寄存器 */
    __IO uint32_t rtc_aux;      /**< \brief RTX辅助控制寄存器 */
    __IO uint32_t alsec;        /**< \brief 秒报警值 */
    __IO uint32_t almin;        /**< \brief 分报警值 */
    __IO uint32_t alhour;       /**< \brief 小时报警值*/
    __IO uint32_t aldom;        /**< \brief 日期（月）报警值 */
    __IO uint32_t aldow;        /**< \brief 星期报警值 */
    __IO uint32_t aldoy;        /**< \brief 日期（年）报警值 */
    __IO uint32_t almonth;      /**< \brief 月报警值 */
    __IO uint32_t alyear;       /**< \brief 年报警值 */
    /* 事件监测器/记录器 */
    __IO uint32_t erstatus;         /**< \brief 状态寄存器  */
    __IO uint32_t ercontrol;        /**< \brief 控制寄存器 */
    __IO uint32_t ercounters;       /**< \brief 计数器寄存器 */
         uint32_t reserved1;        /**< \brief 保留  */
    __IO uint32_t erfirststamp[3];  /**< \brief 首个时间戳寄存器  */
         uint32_t reserved2;        /**< \brief 保留  */
    __IO uint32_t erlaststamp[3];   /**< \brief 末尾时间戳寄存器  */

} amhw_rtc_t;

/** 
 * \name RTC 增量中断位定义
 * \anchor grp_amhw_rtc_im
 * @{
 */
 
/** \brief 增量中断控制位：s    */
#define AMHW_RTC_IM_SEC     AM_BIT(0)

/** \brief 增量中断控制位：min  */
#define AMHW_RTC_IM_MIN     AM_BIT(1)    

/** \brief 增量中断控制位：hour */
#define AMHW_RTC_IM_HOUR    AM_BIT(2)  

/** \brief 增量中断控制位：dom  */
#define AMHW_RTC_IM_DOM     AM_BIT(3)   

/** \brief 增量中断控制位：dow  */
#define AMHW_RTC_IM_DOW     AM_BIT(4)   

/** \brief 增量中断控制位：doy  */
#define AMHW_RTC_IM_DOY     AM_BIT(5) 

/** \brief 增量中断控制位：mon  */
#define AMHW_RTC_IM_MON     AM_BIT(6)    

/** \brief 增量中断控制位：year */
#define AMHW_RTC_IM_YEAR    AM_BIT(7)

/** \brief RTC增量中断掩码      */
#define AMHW_RTC_IM_MASK    ((uint32_t) 0xFF)  

/** @} */

/** 
 * \name RTC 控制位定义
 * @{
 */

/** \brief 报警屏蔽控制位：s    */
#define AMHW_RTC_AMR_SEC     AM_BIT(0)

/** \brief 报警屏蔽控制位：min  */
#define AMHW_RTC_AMR_MIN     AM_BIT(1)    

/** \brief 报警屏蔽控制位：hour */
#define AMHW_RTC_AMR_HOUR    AM_BIT(2)  

/** \brief 报警屏蔽控制位：dom  */
#define AMHW_RTC_AMR_DOM     AM_BIT(3)   

/** \brief 报警屏蔽控制位：dow  */
#define AMHW_RTC_AMR_DOW     AM_BIT(4)   

/** \brief 报警屏蔽控制位：doy  */
#define AMHW_RTC_AMR_DOY     AM_BIT(5) 

/** \brief 报警屏蔽控制位：mon  */
#define AMHW_RTC_AMR_MON     AM_BIT(6)    

/** \brief 报警屏蔽控制位：year */
#define AMHW_RTC_AMR_YEAR    AM_BIT(7)

/** \brief RTC报警屏蔽掩码      */
#define AMHW_RTC_AMR_MASK    ((uint32_t) 0xFF)  

/** @} */

/**
 * \name RTC 中断标志位
 * @{
 */
#define AMHW_RTC_INT_CIF   AM_BIT(0)  /**< \brief RTC增量中断标志      */
#define AMHW_RTC_INT_CALF  AM_BIT(1)  /**< \brief RTC报警中断标志      */
/** @} */

/**
 * \brief RTC寄存器初始化
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return    无
 */
am_static_inline 
void amhw_rtc_registers_reset (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ilr         = 0x00;
    p_hw_rtc->ccr         = 0x00;
    p_hw_rtc->ciir        = 0x00;
    p_hw_rtc->amr         = 0xff;
    p_hw_rtc->calibration = 0x00;
}

/**
 * \brief  读取RTC中断位置寄存器
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    RTC中断位置寄存器值
 */
am_static_inline 
uint32_t amhw_rtc_ilr_read (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->ilr & 0x03;
}

/**
 * \brief  读RTC计数中断
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \retval       0          : 无中断发生
 * \retval AMHW_RTC_INT_CIF : 产生计数增量中断
 */
am_static_inline
uint8_t amhw_rtc_cif_read (amhw_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->ilr & 0x01);
}

/**
 * \brief  读RTC报警中断
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \retval       0          :  无中断发生
 * \retval AMHW_RTC_INT_CIF :  产生RTC报警中断
 */
am_static_inline
uint8_t amhw_rtc_alf_read (amhw_rtc_t *p_hw_rtc)
{
    return (p_hw_rtc->ilr & 0x02);
}

/**
 * \brief  清除RTC中断
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return    无
 */
am_static_inline 
void amhw_rtc_alf2cif_clear (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ilr = 0x03;
}

/**
 * \brief  使能RTC计数器
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return NONE
 */
am_static_inline
void amhw_rtc_count_enable (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr |= 1 << 0;
}

/**
 * \brief  禁止RTC计数器
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return    无
 */
am_static_inline
void amhw_rtc_count_disable (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr &= ~(1 << 0);
}

/**
 * \brief  复位RTC寄存器
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return    无
 */
am_static_inline
void amhw_rtc_rst (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr |= 1 << 1;
}

/**
 * \brief  关闭RTC校准
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return    无
 */
am_static_inline
void amhw_rtc_cali_disable (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr |= 1 << 4;
}

/**
 * \brief  使能RTC校准
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return    无
 */
am_static_inline
void amhw_rtc_cali_enable (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->ccr &= ~(1 << 4);
}

/**
 * \brief  设置指定RTC增量中断
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] flag     : 增量中断，AMHW_RTC_IM_*如(#AMHW_RTC_IM_SEC),
 *                       可同时设置多个中断
 * \return    无
 */
am_static_inline
void amhw_rtc_ciir_set (amhw_rtc_t *p_hw_rtc, uint32_t flag)
{
    p_hw_rtc->ciir = flag;
}

/**
 * \brief  清除指定RTC增量中断
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] flag     : 增量中断，AMHW_RTC_IM_*如(#AMHW_RTC_IM_SEC)
 * \return    无
 */
am_static_inline
void amhw_rtc_ciir_clr (amhw_rtc_t *p_hw_rtc, uint32_t flag)
{
    p_hw_rtc->ciir &= ~flag;
}

/**
 * \brief  获取指定RTC增量中断是否被设置
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    增量中断寄存器
 */
am_static_inline
uint32_t amhw_rtc_ciir_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->ciir & 0xFF;
}


/** 
 * \name RTC时间屏蔽位
 * \anchor grp_amhw_rtc_mask
 * @{
 */

/** \brief 时间设定屏蔽控制位：s    */
#define AMHW_RTC_MASK_SEC     AM_BIT(0)

/** \brief 时间设定屏蔽控制位：min  */
#define AMHW_RTC_MASK_MIN     AM_BIT(1)    

/** \brief 时间设定屏蔽控制位：hour */
#define AMHW_RTC_MASK_HOUR    AM_BIT(2)  

/** \brief 时间设定屏蔽控制位：dom  */
#define AMHW_RTC_MASK_DOM     AM_BIT(3)   

/** \brief 时间设定屏蔽控制位：dow  */
#define AMHW_RTC_MASK_DOW     AM_BIT(4)   

/** \brief 时间设定屏蔽控制位：doy  */
#define AMHW_RTC_MASK_DOY     AM_BIT(5) 

/** \brief 时间设定屏蔽控制位：mon  */
#define AMHW_RTC_MASK_MON     AM_BIT(6)    

/** \brief 时间设定屏蔽控制位：year */
#define AMHW_RTC_MASK_YEAR    AM_BIT(7)

/** \brief RTC 时间设定控制位掩码 */
#define AMHW_RTC_TIME_MASK   ((uint32_t) 0xFF)  

/** @} */

/**
 * \brief  获取RTC时间
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] p_tm      : 要获取的时间
 * \param[in] flags     : 屏蔽字，参见 \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \return    无
 */
void amhw_rtc_get_time (amhw_rtc_t *p_hw_rtc, am_tm_t *p_tm, uint16_t flags);

/**
 * \brief  设置RTC时间
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] p_tm      : 设置的时间
 * \param[in] flags     : 屏蔽字，参见 \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \return    无
 */
void amhw_rtc_set_time (amhw_rtc_t *p_hw_rtc, am_tm_t *p_tm, uint16_t flags);

/**
 * \brief  设定RTC校准值
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] calval   : 校准值
 * \return    无
 */
am_static_inline 
void amhw_rtc_cali_set_value (amhw_rtc_t *p_hw_rtc, uint16_t calval)
{
    p_hw_rtc->calibration = (p_hw_rtc->calibration & (1 << 17)) | \
    		                (calval & 0x1ffff);
}

/**
 * \brief  后向校准RTC
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return    无
 */
am_static_inline 
void amhw_rtc_backward_cali (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->calibration |= (1 << 17); 
}

/**
 * \brief  前向校准RTC
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \return    无
 */
am_static_inline
void amhw_rtc_forward_cali (amhw_rtc_t *p_hw_rtc)
{
    p_hw_rtc->calibration &= ~(1 << 17); 
}

/**
 * \brief  向RTC通用寄存器存储5个32位数据
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] p_data   : 存储到通用寄存器的数据指针
 *
 * \return    无
 */
void amhw_rtc_store_val_in_gpreg (amhw_rtc_t *p_hw_rtc, uint32_t *p_data);

/**
 * \brief  读备份寄存器的值
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] p_data   : 获取5个备份寄存器的值，该指针必须分配内存
 * \return    无
 */
int amhw_rtc_restore_gpreg_val (amhw_rtc_t *p_hw_rtc, uint32_t *p_data);

/**
 * \brief  设置报警寄存器时间
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] p_tm      : 设置的报警时间
 * \param[in] flags     : 屏蔽字，参见 \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \return    无
 */       
void amhw_rtc_alarm_set (amhw_rtc_t *p_hw_rtc, am_tm_t *p_tm, uint16_t flags);

/**
 * \brief  设置报警屏蔽位
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] mask      : 报警屏蔽字 ，参见 \ref grp_amhw_rtc_mask "RTC MASK"
 *
 * \return    无
 */
am_static_inline
void amhw_rtc_set_alarm_mask (amhw_rtc_t *p_hw_rtc, uint16_t mask)
{
    p_hw_rtc->amr = mask;
}

/*****************************************************************************/
/**
 * \name 事件监测器通道初始化控制信息
 * \anchor grp_amhw_er_ctrl_init_flag
 * @{
 */
#define AMHW_RTCER_INTWAKEUP_ENABLE   (1) /**< \brief 中断和唤醒使能    */
#define AMHW_RTCER_INTWAKEUP_DISABLE  (0) /**< \brief 中断和唤醒失能    */

#define AMHW_RTCER_GPCLEAR_ENABLE     (1) /**< \brief 自动使能清除RTC通用寄存器    */
#define AMHW_RTCER_GPCLEAR_DISABLE    (0) /**< \brief 不清除RTC通用寄存器    */

#define AMHW_RTCER_POL_POSTIVE        (1) /**< \brief 输入管脚事件极性为正相沿    */
#define AMHW_RTCER_POL_NEGATIVE       (0) /**< \brief 输入管脚事件极性为负相沿    */

/** @} */

/**
 * \name 事件监测器控制寄存器位信息
 * @{
 */
#define AMHW_RTCER_CTRL_L3_MASK        (0x07) /**< \brief 低三位控制位掩码    */
#define AMHW_RTCER_CTRL_INPUTEN_POS    (3)    /**< \brief 通道0使能位偏移    */
#define AMHW_RTCER_CTRL_CHAN_INTERVAL  (10)   /**< \brief 通道间隔位    */

/**< \brief 指定通道n的控制寄存器位bit偏移    */
#define AMHW_RTCER_CHAN_BIT_POS(bit, n) \
	    (bit << (n * AMHW_RTCER_CTRL_CHAN_INTERVAL))

#define AMHW_RTCER_MODE_BIT_POS    (30)   /**< \brief 模式位偏移    */

/** \brief 模式位掩码    */
#define AMHW_RTCER_MODE_BIT_MASK   (0x03 << AMHW_RTCER_MODE_BIT_POS)
/** @} */

/**
 * \brief 事件监测器通道控制初始化
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] chan      : 指定通道号，值为0/1/2
 * \param[in] flag      : 初始化控制信息,参见 \ref grp_amhw_er_ctrl_init_flag
 *                        将通道信息进行或操作后写入
 * \return    无
 */
am_static_inline
void amhw_rtc_er_init (amhw_rtc_t *p_hw_rtc, uint8_t chan, uint16_t flag)
{
    p_hw_rtc->ercontrol &= \
        ~AMHW_RTCER_CHAN_BIT_POS(AMHW_RTCER_CTRL_L3_MASK, chan);
    p_hw_rtc->ercontrol |= (flag << (chan * AMHW_RTCER_CTRL_CHAN_INTERVAL)) &\
    	AMHW_RTCER_CHAN_BIT_POS(AMHW_RTCER_CTRL_L3_MASK, chan);
}

/**
 * \name 事件监测器通道输入使能控制
 * @{
 */
#define AMHW_RTCER_CHAN_ENABLE   (0x01) /**< \brief 通道输入使能    */
#define AMHW_RTCER_CHAN_DISABLE  (0)    /**< \brief 通道输入失能    */
/** @} */

/**
 * \brief 事件监测器通道输入使能控制
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] chan      : 指定通道号，值为0/1/2
 * \param[in] val       : 输入使能或失能,
 *                        值为(#AMHW_RTCER_CHAN_ENABLE)或
 *                            (#AMHW_RTCER_CHAN_DISABLE)
 *
 * \return    无
 */
am_static_inline
void amhw_rtc_er_chan_enable (amhw_rtc_t *p_hw_rtc, uint8_t chan, uint8_t val)
{
    p_hw_rtc->ercontrol &= \
        ~AMHW_RTCER_CHAN_BIT_POS(AMHW_RTCER_CTRL_INPUTEN_POS, chan);
    p_hw_rtc->ercontrol |= AMHW_RTCER_CHAN_BIT_POS(val & 0x01, chan);
}

/**
 * \name 事件监测器控制模式
 * @{
 */
#define AMHW_RTCER_MODE_CLK_DIABLE  (0UL) /**< \brief 事件监测/记录器时钟被禁止 */
#define AMHW_RTCER_MODE_SAMCLK_16HZ (1UL) /**< \brief 采样时钟16HZ */
#define AMHW_RTCER_MODE_SAMCLK_64HZ (2UL) /**< \brief 采样时钟64HZ */
#define AMHW_RTCER_MODE_SAMCLK_1KHZ (3UL) /**< \brief 采样时钟1kHZ */

/** @} */

/**
 * \brief 事件监测器模式选择
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] mode      : 模式选择,值为AMHW_RTCER_MODE_*如(#AMHW_RTCER_MODE_CLK_DIABLE)
 *
 * \return    无
 */
am_static_inline
void amhw_rtc_er_mode_set (amhw_rtc_t *p_hw_rtc, uint8_t mode)
{
    p_hw_rtc->ercontrol &= ~AMHW_RTCER_MODE_BIT_MASK;
    p_hw_rtc->ercontrol |= (mode << AMHW_RTCER_MODE_BIT_POS) & \
                            AMHW_RTCER_MODE_BIT_MASK;
}

/**
 * \name 事件监测器状态位定义
 * @{
 */
#define AMHW_RTCER_STATUS_EV0  (1 << 0)  /**< \brief 通道0发生事件标志 */
#define AMHW_RTCER_STATUS_EV1  (1 << 1)  /**< \brief 通道1发生事件标志 */
#define AMHW_RTCER_STATUS_EV2  (1 << 2)  /**< \brief 通道2发生事件标志 */

#define AMHW_RTCER_STATUS_GP_CLEARED  (1 << 3) /**< \brief 通用寄存器异步清除标志 */
#define AMHW_RTCER_STATUS_WAKEUP (1UL << 31)   /**< \brief 中断/唤醒请求标志 */

/** @} */

/**
 * \brief 获取事件监控器状态信息
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 *
 * \return 状态位信息，值为AMHW_RTCER_STATUS_*如(#AMHW_RTCER_STATUS_EV0)
 */
am_static_inline
uint32_t amhw_rtc_er_status_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->erstatus;
}

/**
 * \brief 清除事件监控器状态信息
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] status    : 指定状态位，值为AMHW_RTCER_STATUS_*如(#AMHW_RTCER_STATUS_EV0)
 *
 * \return 无
 */
am_static_inline
void amhw_rtc_er_status_clear (amhw_rtc_t *p_hw_rtc, uint32_t status)
{
    p_hw_rtc->erstatus |= status;
}

/**
 * \brief事件监控器指定标志位是否置位
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] status    : 指定状态位，值为AMHW_RTCER_STATUS_*如(#AMHW_RTCER_STATUS_EV0)
 *
 * \retval    TRUE      : 指定标志位置位
 * \retval    FALSE     : 指定标志位未置位
 */
am_static_inline
bool_t amhw_rtc_er_status_check (amhw_rtc_t *p_hw_rtc, uint32_t status)
{
    return (bool_t)((p_hw_rtc->erstatus & status) != 0);
}

/**
 * \name 事件监测器通道计数值
 * @{
 */
#define AMHW_RTCER_EV0_COUNTER(n) (n & 0x07)         /**< \brief 通道0事件计数值  */
#define AMHW_RTCER_EV1_COUNTER(n) ((n >> 8) & 0x07)  /**< \brief 通道1事件计数值  */
#define AMHW_RTCER_EV2_COUNTER(n) ((n >> 16) & 0x07) /**< \brief 通道2事件计数值  */
/** @} */

/**
 * \brief 获取指定通道事件计数值
 *
 * \param[in] p_hw_rtc  : 指向RTC寄存器块的指针
 * \param[in] chan      : 指定通道，值为0/1/2
 *
 * \return 指定通道事件计数值
 */
uint8_t amhw_rtc_er_eventcount_get (amhw_rtc_t *p_hw_rtc, uint8_t chan);


/**
 * \brief 事件监测器/记录器时间戳
 */
typedef struct amhw_rtcer_timestamp
{
    uint32_t sec;   /**< \brief 秒值                      */

    uint32_t min;   /**< \brief 分值                      */

    uint32_t hour;  /**< \brief 小时值                 */

    uint32_t doy;   /**< \brief 日期（年）值  */

} amhw_rtcer_timestamp_t;


/**
 * \name 事件监测器时间戳位定义
 * @{
 */
#define AMHW_RTCER_TIMESTAMP_SEC(n)   (n & 0x3F)          /**< \brief 秒值 */
#define AMHW_RTCER_TIMESTAMP_MIN(n)   ((n >>  6) & 0x3F)  /**< \brief 分值 */
#define AMHW_RTCER_TIMESTAMP_HOUR(n)  ((n >> 12) & 0x1F)  /**< \brief 小时值 */
#define AMHW_RTCER_TIMESTAMP_DOY(n)   ((n >> 17) & 0x1FF) /**< \brief 日期（年）值 */
/** @} */

/**
 * \brief 获取指定通道首个时间戳
 *
 * \param[in]  p_hw_rtc    : 指向RTC寄存器块的指针
 * \param[in]  chan        : 指定通道，值为0/1/2
 * \param[out] p_timestamp : 获取到的时间戳
 *
 * \return 无
 */
void amhw_rtc_er_firsttimestamp_get (amhw_rtc_t             *p_hw_rtc,
                                     uint8_t                 chan,
                                     amhw_rtcer_timestamp_t *p_timestamp);

/**
 * \brief 获取指定通道末尾时间戳
 *
 * \param[in]  p_hw_rtc      : 指向RTC寄存器块的指针
 * \param[in]  chan          : 指定通道，值为0/1/2
 * \param[out] p_timestamp   : 获取到的时间戳
 *
 * \return 无
 */
void amhw_rtc_er_lasttimestamp_get (amhw_rtc_t             *p_hw_rtc,
                                    uint8_t                 chan,
                                    amhw_rtcer_timestamp_t *p_timestamp);

/**
 * @} amhw_if_rtc
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_RTC_H */

/* end of file */
