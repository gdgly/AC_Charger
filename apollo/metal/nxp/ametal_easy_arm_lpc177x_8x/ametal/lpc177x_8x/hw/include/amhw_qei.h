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
 * \brief  QEI硬件层实现
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  anu, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_QEI_H
#define __AMHW_QEI_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "am_types.h"

/** 
 * \addtogroup amhw_if_qei
 * \copydoc amhw_qei.h
 * @{
 */
    
/** 
 * \brief  QEI寄存器汇总列表
 */
typedef struct amhw_qei{
    __O  uint32_t qeicon;       /**< \brief 控制寄存器 */
    __I  uint32_t qeistat;      /**< \brief 编码状态寄存器 */
    __IO uint32_t qeiconf;      /**< \brief 配置寄存器 */
    __I  uint32_t qeipos;       /**< \brief 位置寄存器 */
    __IO uint32_t qeimaxpos;    /**< \brief 最大位置寄存器 */
    __IO uint32_t cmpos0;       /**< \brief 位置比较寄存器0 */
    __IO uint32_t cmpos1;       /**< \brief 位置比较寄存器1 */
    __IO uint32_t cmpos2;       /**< \brief 位置比较寄存器2 */
    __I  uint32_t inxcnt;       /**< \brief 索引计数寄存器 */
    __IO uint32_t inxcmp;       /**< \brief 索引比较寄存器 */
    __IO uint32_t qeiload;      /**< \brief 速度定时器重载寄存器 */
    __I  uint32_t qeitime;      /**< \brief 速度定时器寄存器 */
    __I  uint32_t qeivel;       /**< \brief 速度计数器寄存器 */
    __I  uint32_t qeicap;       /**< \brief 速度捕获寄存器 */
    __IO uint32_t velcomp;      /**< \brief 速度比较寄存器 */
    __IO uint32_t filter;       /**< \brief 数字滤波寄存器 */
         uint32_t reserved[998];/**< \brief 保护区 */
    __O  uint32_t qeiiec;       /**< \brief 中断使能清除寄存器 */
    __O  uint32_t qeiies;       /**< \brief 中断使能置位寄存器 */
    __I  uint32_t qeiintstat;   /**< \brief 中断状态寄存器 */
    __I  uint32_t qeiie;        /**< \brief 中断使能寄存器 */
    __O  uint32_t qeiclr;       /**< \brief 中断状态清除寄存器 */
    __O  uint32_t qeiset;       /**< \brief 中断状态设置寄存器 */
} amhw_qei_t;

/**
 * \name QEI控制寄存器位定义
 * \anchor grp_amhw_qei_con
 * @{
 */

#define AMHW_QEI_CON_RESP    (1UL << 0) /**< \brief 复位位置计数器 */
#define AMHW_QEI_CON_RESPI   (1UL << 1) /**< \brief 索引脉冲出现时复位位置计数器 */
#define AMHW_QEI_CON_RESV    (1UL << 2) /**< \brief 复位速度 */
#define AMHW_QEI_CON_RESI    (1UL << 3) /**< \brief 复位索引计数器 */

/** @} */

/**
 * \brief 复位位置计数器
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_pos_rst (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeicon = AMHW_QEI_CON_RESP;
}

/**
 * \brief 设置脉冲索引出现时复位位置计数器
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_indexpos_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeicon = AMHW_QEI_CON_RESPI;
}

/**
 * \brief 复位速度
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_velocity_rst (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeicon = AMHW_QEI_CON_RESV;
}

/**
 * \brief 复位索引计数器
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_index_rst (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeicon = AMHW_QEI_CON_RESI;
}

/**
 * \name QEI配置寄存器位定义
 * \anchor grp_amhw_qei_conf
 * @{
 */

#define AMHW_QEI_CONF_DIRINV     (1UL << 0) /**< \brief 方向反相 */
#define AMHW_QEI_CONF_SIGMODE    (1UL << 1) /**< \brief 信号模式 */
#define AMHW_QEI_CONF_CAPMODE    (1UL << 2) /**< \brief 捕获模式 */
#define AMHW_QEI_CONF_INVINX     (1UL << 3) /**< \brief 索引脉冲反相 */

/** @} */

/**
 * \brief 设置方向反相 求DIR反码
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_dirinv_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf |= AMHW_QEI_CONF_DIRINV;
}

/**
 * \brief 清除方向反相
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_dirinv_clr (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf &= ~AMHW_QEI_CONF_DIRINV;
}

/**
 * \brief 设置信号模式 A为方向信号 B为时钟信号
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_sigmode_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf |= AMHW_QEI_CONF_SIGMODE;
}

/**
 * \brief 清除信号模式 AB作为正交相位信号
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_sigmode_clr (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf &= ~AMHW_QEI_CONF_SIGMODE;
}

/**
 * \brief 设置捕获模式 同时对AB相进行计数4X
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_capmode_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf |= AMHW_QEI_CONF_CAPMODE;
}

/**
 * \brief 清除捕获模式 只对A相进行计数2X
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_capmode_clr (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf &= ~AMHW_QEI_CONF_CAPMODE;
}

/**
 * \brief 设置输入索引脉冲反相
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_invinx_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf |= AMHW_QEI_CONF_INVINX;
}

/**
 * \brief 清除输入索引脉冲反相
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_invinx_clr (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf &= ~AMHW_QEI_CONF_INVINX;
}

/**
 * \name QEI状态寄存器位定义
 * \anchor grp_amhw_qei_stat
 * @{
 */

#define AMHW_QEI_STAT_DIR     (1UL << 0)     /**< \brief 方向位 */

/** @} */

/**
 * \brief 获取方向位
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 0为正向
 * \retval 1为反向
 */
am_static_inline 
uint32_t amhw_qei_dir_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeistat & AMHW_QEI_STAT_DIR)? 1 : 0;
}

/**
 * \brief 获取当前的位置值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 位置值
 */
am_static_inline 
uint32_t amhw_qei_pos_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeipos);
}

/**
 * \brief 设置最大的位置值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] maxpos   : 位置值
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_maxpos_set (amhw_qei_t *p_hw_qei, uint32_t maxpos)
{
    p_hw_qei->qeimaxpos = maxpos;
}

/**
 * \brief 获取最大的位置值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 最大的位置值
 */
am_static_inline 
uint32_t amhw_qei_maxpos_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeimaxpos);
}

/**
 * \brief 设置位置比较器0
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] pos      : 位置值
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_cmpos0_set (amhw_qei_t *p_hw_qei, uint32_t pos)
{
    p_hw_qei->cmpos0 = pos;
}

/**
 * \brief 获取位置比较器0的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 位置值
 */
am_static_inline 
uint32_t amhw_qei_cmpos0_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->cmpos0);
}

/**
 * \brief 设置位置比较器1
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] pos      : 位置值
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_cmpos1_set (amhw_qei_t *p_hw_qei, uint32_t pos)
{
    p_hw_qei->cmpos1 = pos;
}

/**
 * \brief 获取位置比较器1的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 位置值
 */
am_static_inline 
uint32_t amhw_qei_cmpos1_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->cmpos1);
}

/**
 * \brief 设置位置比较器2
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] pos      : 位置值
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_cmpos2_set (amhw_qei_t *p_hw_qei, uint32_t pos)
{
    p_hw_qei->cmpos2 = pos;
}

/**
 * \brief 获取位置比较器2的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 位置值
 */
am_static_inline 
uint32_t amhw_qei_cmpos2_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->cmpos2);
}

/**
 * \brief 获取索引计数寄存器
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 位置值
 */
am_static_inline 
uint32_t amhw_qei_inxcnt_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->inxcnt);
}

/**
 * \brief 设置索引比较器
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] index    : 位置值
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_inxcmp_set (amhw_qei_t *p_hw_qei, uint32_t index)
{
    p_hw_qei->inxcmp = index;
}

/**
 * \brief 获取索引比较器的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 索引值
 */
am_static_inline 
uint32_t amhw_qei_inxcmp_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->inxcmp);
}

/**
 * \brief 设置定时器装载
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] time     : 装载时间数
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_timeload_set (amhw_qei_t *p_hw_qei, uint32_t time)
{
    p_hw_qei->qeiload = time;
}

/**
 * \brief 获取定时器装载的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 定时器的装载时间
 */
am_static_inline 
uint32_t amhw_qei_timeload_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeiload);
}

/**
 * \brief 获取当前速度定时器的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 速度定时器的值
 */
am_static_inline 
uint32_t amhw_qei_timevel_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeivel);
}

/**
 * \brief 获取当前速度脉冲的计数
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 速度脉冲计数值
 */
am_static_inline 
uint32_t amhw_qei_time_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeitime);
}

/**
 * \brief 获取当前速度捕获计数
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 速度脉冲计数值
 */
am_static_inline 
uint32_t amhw_qei_capture_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeicap);
}

/**
 * \brief 设置速度比较的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] vel      : 速度的比较值
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_velocitycmp_set (amhw_qei_t *p_hw_qei, uint32_t vel)
{
    p_hw_qei->velcomp = vel;
}

/**
 * \brief 获取速度比较的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 速度比较的值
 */
am_static_inline 
uint32_t amhw_qei_velocitycmp_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->velcomp);
}

/**
 * \brief 设置数字滤波器采样延时 如果采样个数为0则滤波被旁路
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] time     : 0则旁路 1~4,294,967,295个采样时钟
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_filter_set (amhw_qei_t *p_hw_qei, uint32_t time)
{
    p_hw_qei->filter = time;
}

/**
 * \brief 获取速度比较的值
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 采样延时的值
 */
am_static_inline 
uint32_t amhw_qei_filter_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->filter);
}

/**
 * \brief QEI 中断类型
 */
typedef uint32_t amhw_qei_int_type_t;

#define AMHW_QEI_INT_TYPE_COUNT    13  /**< \brief 中断类型的总数 */


/**
 * \name QEI中断寄存器位定义
 * \anchor grp_amhw_qei_int
 * @{
 */

#define AMHW_QEI_INT_INX         (1UL << 0)  /**< \brief 检测到一个索引脉冲 */
#define AMHW_QEI_INT_TIM         (1UL << 1)  /**< \brief 检测到速度定时器溢出 */
#define AMHW_QEI_INT_VELC        (1UL << 2)  /**< \brief 检测到捕获速度小于比较速度 */
#define AMHW_QEI_INT_DIR         (1UL << 3)  /**< \brief 检测到方向改变 */
#define AMHW_QEI_INT_ERR         (1UL << 4)  /**< \brief 检测到编码器相位错误 */
#define AMHW_QEI_INT_ENCLK       (1UL << 5)  /**< \brief 检测编码器时钟脉冲 */
#define AMHW_QEI_INT_POS0        (1UL << 6)  /**< \brief 检测到位置0比较值与当前位置相等 */
#define AMHW_QEI_INT_POS1        (1UL << 7)  /**< \brief 检测到位置1比较值与当前位置相等 */
#define AMHW_QEI_INT_POS2        (1UL << 8)  /**< \brief 检测到位置2比较值与当前位置相等 */
#define AMHW_QEI_INT_REV         (1UL << 9)  /**< \brief 检测到索引比较值等于当前索引 */
#define AMHW_QEI_INT_POS0REV     (1UL << 10) /**< \brief 检测到位置0和旋转计数中断组合 */
#define AMHW_QEI_INT_POS1REV     (1UL << 11) /**< \brief 检测到位置1和旋转计数中断组合 */
#define AMHW_QEI_INT_POS2REV     (1UL << 12) /**< \brief 检测到位置2和旋转计数中断组合 */
#define AMHW_QEI_INT_ALL         (0XFFFFFFFF)/**< \brief 设置所有中断 */

/** @} */

/**
 * \brief 获取中断状态
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 中断的类型，参见 \ref grp_amhw_qei_int "interrupt type"
 */
am_static_inline 
amhw_qei_int_type_t amhw_qei_intstat_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeiintstat);
}

/**
 * \brief 中断设置状态
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] inttype  : 中断类型 配置参数，参见
 *                       \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_intstat_set (amhw_qei_t *p_hw_qei, amhw_qei_int_type_t inttype)
{
	p_hw_qei->qeiset = inttype;
}


/**
 * \brief 中断清除状态
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] inttype  : 中断类型 配置参数，参见
 *                       \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_intstat_clr (amhw_qei_t *p_hw_qei, amhw_qei_int_type_t inttype)
{
	p_hw_qei->qeiclr = inttype;
}

/**
 * \brief 中断使能
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 *
 * \retval 中断类型，参见 \ref grp_amhw_qei_int "interrupt type"
 */
am_static_inline 
amhw_qei_int_type_t amhw_qei_int_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeiie);
}

/**
 * \brief 中断使能置位
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] inttype  : 中断类型 配置参数，参见
 *                       \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_int_set (amhw_qei_t *p_hw_qei, amhw_qei_int_type_t inttype)
{
	p_hw_qei->qeiies = inttype;
}

/**
 * \brief 中断使能清除
 *
 * \param[in] p_hw_qei : 指向QEI寄存器块的指针
 * \param[in] inttype  : 中断类型 配置参数，参见
 *                       \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval 无
 */
am_static_inline 
void amhw_qei_int_clr (amhw_qei_t *p_hw_qei, amhw_qei_int_type_t inttype)
{
	p_hw_qei->qeiiec = inttype;
}

/** 
 * @} amhw_if_qei
 */

#ifdef __cplusplus
}
#endif


#endif  /* __AMDR_QEI_H */

/*end of file */

