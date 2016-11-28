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
 * \brief EEPROM 硬件操作接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-15  anu, first implementation.
 * \endinternal
 */

#ifndef __AMHW_EEPROM_H
#define __AMHW_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 

/** 
 * \addtogroup amhw_if_eeprom
 * \copydoc amhw_eeprom.h
 * @{
 */


/**
 * \brief eeprom 寄存器块结构体
 */
typedef struct amhw_eeprom {
	__IO uint32_t cmd;			    /**< \brief 命令寄存器   */
	__IO uint32_t addr;				/**< \brief 地址寄存器  */
	__O  uint32_t wdata;			/**< \brief 写数据寄存器  */
	__I  uint32_t rdata;			/**< \brief 读数据寄存器  */
	__IO uint32_t wstate;			/**< \brief 等待状态寄存器  */
	__IO uint32_t clkdiv;			/**< \brief 时钟分频器寄存器  */
	__IO uint32_t pwrdwn;		    /**< \brief 掉电寄存器 */
	     uint32_t reserved0[975];   /**< \brief 保留  */
	__O  uint32_t int_clr_enable;	/**< \brief 中断使能清零 */
	__O  uint32_t int_set_enable;   /**< \brief 中断使能置位  */
	__I  uint32_t int_status;		/**< \brief 中断状态 */
	__I  uint32_t int_enable;       /**< \brief 中断使能 */
	__O  uint32_t int_clr_status;   /**< \brief 中断状态清零  */
	__O  uint32_t int_set_status;   /**< \brief 中断状态置位  */
} amhw_eeprom_t;

/**
 * \name 命令寄存器中命令的定义
 * \anchor grp_amhw_eeprom_cmd
 * @{
 */

typedef uint32_t amhw_eeprom_cmd_t;
#define AMHW_EEPROM_CMD_8BR             0X00   /**< \brief 8 位读取  */
#define AMHW_EEPROM_CMD_16BR            0X01   /**< \brief 16 位读取  */
#define AMHW_EEPROM_CMD_32BR            0X02   /**< \brief 32 位读取  */
#define AMHW_EEPROM_CMD_8BW             0X03   /**< \brief 8 位写入  */
#define AMHW_EEPROM_CMD_16BW            0X04   /**< \brief 16 位写入  */
#define AMHW_EEPROM_CMD_32BW            0X05   /**< \brief 32 位写入  */
#define AMHW_EEPROM_CMD_PROG            0X06   /**< \brief 擦除/编程页  */
#define AMHW_EEPROM_CMD_RSV             0X07   /**< \brief 保留  */
#define AMHW_EEPROM_CMD_RDPREFETCH      0x08   /**< \brief 读取数据预取位   */

/** @} */

/**
 * \brief 设置EEPROM的命令
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] cmd         : 控制命令
 *
 * \return    无
 */
am_static_inline 
void amhw_eeprom_cmd_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_cmd_t cmd)
{
    p_hw_eeprom->cmd = cmd;
}

/**
 * \brief 获取EEPROM的命令
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    命令类型
 */
am_static_inline
amhw_eeprom_cmd_t amhw_eeprom_cmd_get (amhw_eeprom_t *p_hw_eeprom)
{
    return (p_hw_eeprom->cmd & 0x0f);
}


/**
 * \brief 设置EEPROM的地址
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] addr        : 地址 12位地址
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_addr_set (amhw_eeprom_t *p_hw_eeprom, int addr)
{
    p_hw_eeprom->addr = (addr & 0x0FFF);
}

/**
 * \brief 设置EEPROM的地址
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    12位地址
 */
am_static_inline
amhw_eeprom_cmd_t amhw_eeprom_addr_get (amhw_eeprom_t *p_hw_eeprom)
{
    return (p_hw_eeprom->addr & 0x0FFF);
}

/**
 * \brief 设置EEPROM的写数据
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] data        : 数据
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_wdata_set (amhw_eeprom_t *p_hw_eeprom, uint32_t data)
{
    p_hw_eeprom->wdata = data;
}

/**
 * \brief 获取EEPROM的读数据
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    无
 */
am_static_inline
uint32_t amhw_eeprom_rdata_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->rdata;
}

/**
 * \name 等待状态寄存器的位定义
 * \anchor grp_amhw_eeprom_phase
 * @{
 */

typedef uint32_t amhw_eeprom_phase_t;
#define AMHW_EEPROM_PHASE3          (0XFFUL << 0)   /**< \brief 等待状态 3 要求提供至少 15ns 的时间   */
#define AMHW_EEPROM_PHASE2          (0XFFUL << 8)   /**< \brief 等待状态 2 要求提供至少 55ns 的时间   */
#define AMHW_EEPROM_PHASE1          (0XFFUL << 16)  /**< \brief 等待状态 1 要求提供至少 35ns 的时间   */

/** @} */

/**
 * \brief 设置EEPROM的等待状态
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] kind        : 等待状态类型
 * \param[in] val         : 等待时间
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_phase_set (amhw_eeprom_t       *p_hw_eeprom,
                            amhw_eeprom_phase_t  kind,
                            uint32_t             val)
{
    p_hw_eeprom->wstate &= ~kind;
    p_hw_eeprom->wstate |= (val & kind);
}

/**
 * \brief 获取EEPROM的等待状态
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    等待状态
 */
am_static_inline
uint32_t amhw_eeprom_phase_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->wstate;
}

/**
 * \brief 设置EEPROM的分频值
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] div         : 分频数
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_clkdiv_set (amhw_eeprom_t       *p_hw_eeprom,
                             uint16_t             div)
{
    p_hw_eeprom->clkdiv &= ~0xffff;
    p_hw_eeprom->clkdiv |= div;
}

/**
 * \brief 获取EEPROM的分频值
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    分频值
 */
am_static_inline
uint16_t amhw_eeprom_clkdiv_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->clkdiv;
}

/**
 * \brief 设置EEPROM的掉电位  为掉电模式
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_pwrdwn_set (amhw_eeprom_t *p_hw_eeprom)
{
    p_hw_eeprom->pwrdwn |= 0x01;
}

/**
 * \brief 清除EEPROM的为掉电位 为非掉电模式
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_pwrdwn_clr (amhw_eeprom_t *p_hw_eeprom)
{
    p_hw_eeprom->pwrdwn = 0;
}

/**
 * \brief 获取EEPROM的掉电模式状态
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \retval    0 ：为非掉电模式
 * \retval    1 : 为掉电模式
 */
am_static_inline
uint32_t amhw_eeprom_pwrdwn_get (amhw_eeprom_t *p_hw_eeprom)
{
    return (p_hw_eeprom->pwrdwn & 0x01);
}

/**
 * \name 中断存器的位定义
 * \anchor grp_amhw_eeprom_int
 * @{
 */

typedef uint32_t amhw_eeprom_int_t;
#define AMHW_EEPROM_INT_NONE               0             /**< \brief 无中断  */
#define AMHW_EEPROM_INT_RW_DONE            (1UL << 26)   /**< \brief 读/写操作结束中断使能位  */
#define AMHW_EEPROM_INT_PROG_DONE          (1UL << 28)   /**< \brief 编程操作已完成中断使能位   */

/** @} */

/**
 * \brief 设置EEPROM的中断使能
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] type        : 中断类型
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_inten_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_int_t type)
{
    p_hw_eeprom->int_set_enable = type;
}

/**
 * \brief 设置EEPROM的中断失能
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] type        : 中断类型
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_intdis_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_int_t type)
{
    p_hw_eeprom->int_clr_enable = type;
}

/**
 * \brief 读取EEPROM的中断使能
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    无
 */
am_static_inline
amhw_eeprom_int_t amhw_eeprom_int_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->int_enable;
}

/**
 * \brief 设置EEPROM的中断状态使能
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] type        : 中断类型
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_staten_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_int_t type)
{
    p_hw_eeprom->int_set_status = type;
}

/**
 * \brief 设置EEPROM的中断状态失能
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 * \param[in] type        : 中断类型
 *
 * \return    无
 */
am_static_inline
void amhw_eeprom_statdis_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_int_t type)
{
    p_hw_eeprom->int_clr_status = type;
}

/**
 * \brief 读取EEPROM的中断状态
 *
 * \param[in] p_hw_eeprom : 指向EEPROM寄存器块的指针
 *
 * \return    无
 */
am_static_inline
amhw_eeprom_int_t amhw_eeprom_stat_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->int_status;
}

/**
 * @} amhw_if_eeprom
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_EEPROM_H */

/* end of file */
