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
 * \brief 可嵌套向量中断控制器(NVIC) 硬件操作接口
 * 
 * 1. ARM Cortex-M3内部包含有嵌套向量中断控制器；
 * 2. 与内核紧密联系的中断控制器，可支持低中断延时；
 * 3. 可对系统异常和外设中断进行控制；
 * 4. 支持33个嵌套向量中断；
 * 5. 32个可编程的中断优先级；
 * 6. 硬件优先级屏蔽；
 *    - 4个可编程中断优先级，硬件优先级可屏蔽；
 *    - 中断向量表偏移寄存器 VTOR；
 * 7. 任意中断可配置为不可屏蔽中断。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  hbt, first implementation.
 * \endinternal
 */


#ifndef __AMHW_INT_H
#define __AMHW_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc177x_8x.h"

/** 
 * \addtogroup amhw_if_int
 * \copydoc amhw_int.h
 * @{
 */

/**
 * \brief NVIC 寄存器块结构体
 */
typedef struct amhw_int {
    __IO uint32_t  iser[2];                    /**< \brief 中断使能寄存器       */
    __I  uint32_t  reserved1[30];              /**< \brief 保留                 */
    __IO uint32_t  icer[2];                    /**< \brief 清除中断使能寄存器   */   
    __I  uint32_t  reserved2[30];              /**< \brief 保留                 */
    __IO uint32_t  ispr[2];                    /**< \brief 中断等待寄存器       */ 
    __I  uint32_t  reserved3[30];              /**< \brief 保留                 */
    __IO uint32_t  icpr[2];                    /**< \brief 清除中断等待寄存器   */  
    __I  uint32_t  reserved4[30];              /**< \brief 保留                 */
    __I  uint32_t  iabr[2];                    /**< \brief 中断有效寄存器       */ 
    __I  uint32_t  reserved5[62];              /**< \brief 保留                 */
    __IO uint8_t   ipr[44];                    /**< \brief 中断优先级寄存器     */ 
    __I  uint32_t  reserved6[566];             /**< \brief 保留                 */
    __I  uint32_t  icsr;                       /**< \brief 中断控制和状态寄存器 */ 
    __I  uint32_t  reserved7[126];             /**< \brief 保留                 */
    __O  uint32_t  stir;                       /**< \brief 软件触发中断寄存器   */
} amhw_int_t;                                                              

  
/**
 * \brief 获取当前中断号
 * \param[in] p_hw_int : 指向NVIC寄存器块的指针
 * \return 中断号
 */
am_static_inline 
int amhw_inum_get (amhw_int_t *p_hw_int)
{
    return (int)((p_hw_int->icsr - 16) & 0xFF);
}

/**
 * \brief 使能中断
 *
 * \param[in] p_hw_int : 指向NVIC寄存器块的指针
 * \param[in] inum     : 中断号\sa lpc17xx_inum.h
 *
 * \return 无
 */
am_static_inline 
void amhw_int_enable (amhw_int_t *p_hw_int, int inum)
{
    p_hw_int->iser[(uint32_t)(inum) >> 5] = (1UL << ((uint32_t)(inum) & 0x1F));
}

/**
 * \brief 禁能中断
 *
 * \param[in] p_hw_int : 指向NVIC寄存器块的指针
 * \param[in] inum     : 中断号
 * \sa lpc17xx_inum.h
 *
 * \return 无
 */
am_static_inline 
void amhw_int_disable (amhw_int_t *p_hw_int, int inum)
{
    p_hw_int->icer[(uint32_t)(inum) >> 5] = (1UL << ((uint32_t)(inum) & 0x1F));
}

/**
 * \brief 置位中断等待
 *
 * \param[in] p_hw_int : 指向NVIC寄存器块的指针
 * \param[in] inum     : 中断号\sa lpc17xx_inum.h
 *
 * \return    无
 */
am_static_inline 
void amhw_int_set_pending (amhw_int_t *p_hw_int, int inum)
{
    p_hw_int->ispr[(uint32_t)(inum) >> 5] = (1UL << ((uint32_t)(inum) & 0x1F));
}

/**
 * \brief 清除等待中断
 *
 * \param[in] p_hw_int : 指向NVIC寄存器块的指针
 * \param[in] inum     : 中断号
 * \sa lpc17xx_inum.h
 *
 * \return    无
 */
am_static_inline 
void amhw_int_clr_pending(amhw_int_t *p_hw_int, int inum)
{
    p_hw_int->icpr[(uint32_t)(inum) >> 5] = (1UL << ((uint32_t)(inum) & 0x1F));
}

/**
 * \brief 获取中断有效状态
 *
 * \param[in] p_hw_int : 指向NVIC寄存器块的指针
 * \param[in] inum     : 中断号\sa lpc17xx_inum.h
 * 
 * \retval TRUE  : 有效中断
 * \retval FALSE : 无效中断
 */
am_static_inline 
bool_t amhw_int_active_state(amhw_int_t *p_hw_int, int inum)
{
    return ((p_hw_int->iabr[(uint32_t)(inum) >> 5] & 
            (1UL << ((uint32_t)(inum) & 0x1F))) ? TRUE : FALSE);
}

/**
 * \brief 设置中断优先级
 *
 * \param[in] p_hw_int : 指向NVIC寄存器块的指针
 * \param[in] inum     : 中断号\sa lpc17xx_inum.h
 * \param[in] prio     : 中断优先级
 * 
 * \return   无
 */
am_static_inline 
void amhw_int_set_priority (amhw_int_t *p_hw_int, int inum, uint32_t prio)
{
    AMHW_INT->ipr[(uint32_t)(inum) >> 5] = ((prio << 4) & 0xFF);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_INT_H */

/* end of file */
