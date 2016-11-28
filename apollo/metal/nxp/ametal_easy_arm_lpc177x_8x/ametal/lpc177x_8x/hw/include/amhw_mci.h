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
 * \brief SD卡（MCI） 硬件操作接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-21  anu, first implementation.
 * \endinternal
 */

#ifndef __AMHW_MCI_H
#define __AMHW_MCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 
#include "amhw_syscon.h"

/** 
 * \addtogroup amhw_if_mci
 * \copydoc amhw_mci.h
 * @{
 */

/**
 * \name fifo 的个数
 * \anchor grp_amhw_fifo_cnt
 * @{
 */

#define AMHW_FIFO_CNT     16    /**< \brief FIFO 的个数  */

/** @} */

/**
 * \brief MCI 寄存器块结构体
 */
typedef struct amhw_mci {
    __IO uint32_t power;        		/**< \brief 电源控制寄存器        */
    __IO uint32_t clock;       	 		/**< \brief 时钟控制寄存器        */
    __IO uint32_t argument;     		/**< \brief 参数寄存器                  */
    __IO uint32_t command;      		/**< \brief 命令寄存器                  */
    __I  uint32_t resp_cmd;     		/**< \brief 响应命令寄存器        */
    __I  uint32_t resp0;        		/**< \brief 响应寄存器                  */
    __I  uint32_t resp1;        		/**< \brief 响应寄存器                  */
    __I  uint32_t resp2;        		/**< \brief 响应寄存器                  */
    __I  uint32_t resp3;        		/**< \brief 响应寄存器                   */
    __IO uint32_t datatmr;      		/**< \brief 数据定时器                   */
    __IO uint32_t datalen;      		/**< \brief 数据长度寄存器         */
    __IO uint32_t datactrl;     		/**< \brief 数据控制寄存器         */
    __I  uint32_t datacnt;      		/**< \brief 数据计数器                   */
    __I  uint32_t status;       		/**< \brief 状态寄存器                   */
    __O  uint32_t clear;        		/**< \brief 清零寄存器                   */
    __IO uint32_t mask0;        		/**< \brief 中断 0 屏蔽寄存器   */
         uint32_t reserved0[2]; 		/**< \brief 保留                                   */
    __I  uint32_t fifocnt;      		/**< \brief FIFO 计数器                 */
         uint32_t reserved1[13];		/**< \brief 保留                                   */
    __IO uint32_t fifo[AMHW_FIFO_CNT];	/**< \brief 数据 FIFO 寄存器      */
} amhw_mci_t;

/**
 * \name 系统控制和状态寄存器位定义
 * \anchor grp_amhw_syscon_mcipwr
 * @{
 */

#define AMHW_SYSCON_MCI_PWR    (0x1UL << 3)         /**< \brief SD_PWR 高电平有效  */

/** @} */

/**
 * \brief 设置SD_PWR引脚高电平有效
 *
 * \param[in] p_hw_syscon : 指向系统控制块寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_mci_pwr_level_high_set (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs |= AMHW_SYSCON_MCI_PWR;
}

/**
 * \brief 设置SD_PWR引脚低电平有效
 *
 * \param[in] p_hw_syscon : 指向系统控制块寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_mci_pwr_level_low_set (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs &= ~AMHW_SYSCON_MCI_PWR;
}

/**
 * \name MCI 电源控制寄存器位定义
 * \anchor grp_amhw_mci_pwr
 * @{
 */

typedef int amhw_mci_pwr_ctrl_t;                       /**< \brief 电源控制定义  */
#define AMHW_MCI_PWR_CTRL_OFF    (0x00UL << 0)         /**< \brief 电源关闭  */
#define AMHW_MCI_PWR_CTRL_RSV    (0x01UL << 0)         /**< \brief 电源保留  */
#define AMHW_MCI_PWR_CTRL_ON     (0x02UL << 0)         /**< \brief 电源上电  */
#define AMHW_MCI_PWR_CTRL_START  (0x03UL << 0)         /**< \brief 电源启动  */
#define AMHW_MCI_PWR_OD          (1UL << 6)            /**< \brief SD_CMD 输出控制 */
#define AMHW_MCI_PWR_ROD         (1UL << 7)            /**< \brief 控制棒 */

/** @} */

/**
 * \brief 设置电源控制中的某一位
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 * \param[in] pwr_ctrl : 电源控制  配置参数，参见
 *                       \ref grp_amhw_mci_pwr "MCI PWR"
 *
 * \return 无
 */
am_static_inline 
void amhw_mci_pwr_set (amhw_mci_t *p_hw_mci, amhw_mci_pwr_ctrl_t pwr_ctrl)
{
    p_hw_mci->power |= pwr_ctrl;
}

/**
 * \brief 清除电源控制中的某一位
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 * \param[in] pwr_ctrl : 电源控制  配置参数，参见
 *                       \ref grp_amhw_mci_pwr "MCI PWR"
 *
 * \return 无
 */
am_static_inline
void amhw_mci_pwr_clr (amhw_mci_t *p_hw_mci, amhw_mci_pwr_ctrl_t pwr_ctrl)
{
    p_hw_mci->power &= ~pwr_ctrl;
}

/**
 * \brief 获取电源控制的配置
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 电源控制的配置  参见 \ref grp_amhw_mci_pwr "MCI PWR"
 */
am_static_inline
amhw_mci_pwr_ctrl_t amhw_mci_pwr_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->power;
}

/**
 * \name MCI 时钟控制寄存器位定义
 * \anchor grp_amhw_mci_clock
 * @{
 */

typedef uint32_t amhw_mci_clk_en_t;                /**< \brief 时钟控制使能定义 */
#define AMHW_MCI_CLK_EN         (1UL << 8)         /**< \brief 使能SD卡总线时钟 */
#define AMHW_MCI_CLK_PWRSAVE    (1UL << 9)         /**< \brief 总线空闲时,禁止 SD_CLK 输出  */
#define AMHW_MCI_CLK_BYPASS     (1UL << 10)        /**< \brief 使能时钟分频逻辑旁路  */
#define AMHW_MCI_CLK_WIDEBUS    (1UL << 11)        /**< \brief 使能宽总线模式 */

/** @} */

/**
 * \brief 设置使能宽总线模式
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_mci_widebus_set (amhw_mci_t *p_hw_mci)
{
    p_hw_mci->clock |= AMHW_MCI_CLK_WIDEBUS;
}

/**
 * \brief 清除禁能宽总线模式
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_mci_widebus_clr (amhw_mci_t *p_hw_mci)
{
    p_hw_mci->clock &= ~AMHW_MCI_CLK_WIDEBUS;
}

/**
 * \brief 设置在总线空闲时时钟开始输出
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_mci_clking_set (amhw_mci_t *p_hw_mci)
{
    p_hw_mci->clock &= ~AMHW_MCI_CLK_PWRSAVE;
}

/**
 * \brief 清除在总线空闲时时钟输出
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_mci_clking_clr (amhw_mci_t *p_hw_mci)
{
    p_hw_mci->clock |= AMHW_MCI_CLK_PWRSAVE;
}

/**
 * \brief 设置时钟
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 * \param[in] div      : 总线时钟分频
 * \param[in] clk_en   : 需要使能的时钟  配置参数，参见
 *                       \ref grp_amhw_mci_clock "MCI CLOCK ENABLE"
 *
 * \return 无
 */
am_static_inline
void amhw_mci_clk_set (amhw_mci_t        *p_hw_mci,
                       uint8_t            div,
                       amhw_mci_clk_en_t  clk_en)
{
    p_hw_mci->clock = (div | clk_en);
}

/**
 * \brief 获取时钟分频
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 时钟分频
 */
am_static_inline
uint8_t amhw_mci_clk_div_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->clock & 0xff);
}

/**
 * \brief 获取时钟的使能状态
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 时钟的使能状态  参见 \ref grp_amhw_mci_clock "MCI CLOCK ENABLE"
 */
am_static_inline
amhw_mci_clk_en_t amhw_mci_clk_en_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->clock & (~0xff));
}

/**
 * \brief 设置参数
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 * \param[in] arg      : 参数
 *
 * \return 无
 */
am_static_inline
void amhw_mci_arg_set (amhw_mci_t *p_hw_mci, uint32_t arg)
{
    p_hw_mci->argument = arg;
}

/**
 * \brief 获取参数值
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 参数值
 */
am_static_inline
uint32_t amhw_mci_arg_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->argument;
}

/**
 * \name MCI 命令寄存器位定义
 * \anchor grp_amhw_mci_cmd
 * @{
 */

typedef uint32_t amhw_mci_cmd_ctrl_t;           /**< \brief 命令控制定义 */
#define AMHW_MCI_CMD_RESPONSE       (1UL << 6)  /**< \brief CPSM 等待响应 */
#define AMHW_MCI_CMD_LONGRSP        (1UL << 7)  /**< \brief CPSM 接收一个 136 位长响应  */
#define AMHW_MCI_CMD_INTERRUPT      (1UL << 8)  /**< \brief CPSM 禁能命令定时器并等待中断请求  */
#define AMHW_MCI_CMD_PENDING        (1UL << 9)  /**< \brief CPSM 在开始发送命令前等待 CmdPend */
#define AMHW_MCI_CMD_ENABLE         (1UL << 10) /**< \brief CPSM 被使能 */

/** @} */

/**
 * \brief 设置时钟
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 * \param[in] cmdindex : 命令索引
 * \param[in] cmdctrl  : 需要控制的命令类型   配置参数，参见
 *                       \ref grp_amhw_mci_cmd "MCI CMD CTRL"
 *
 * \return 无
 */
am_static_inline
void amhw_mci_cmd_set (amhw_mci_t          *p_hw_mci,
                       uint8_t              cmdindex,
                       amhw_mci_cmd_ctrl_t  cmdctrl)
{
    p_hw_mci->command = ((cmdindex & 0x3f) | cmdctrl);
}

/**
 * \brief 获取命令索引
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 命令索引
 */
am_static_inline
uint8_t amhw_mci_cmd_index_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->command & 0x3f);
}

/**
 * \brief 获取命令控制类型
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 命令使能类型,参见  \ref grp_amhw_mci_cmd "MCI CMD CTRL"
 */
am_static_inline
amhw_mci_cmd_ctrl_t amhw_mci_cmd_en_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->command & (~0x3f));
}

/**
 * \brief 读取命令响应类型
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 命令响应索引
 */
am_static_inline
uint8_t amhw_mci_resp_cmd_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->command & 0x3f);
}

/**
 * \brief 读取卡状态，响应类型 （短响应 卡状态[31:0] 长响应 卡状态[127:96]）
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 卡状态
 */
am_static_inline
uint32_t amhw_mci_resp0_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->resp0;
}

/**
 * \brief 读取卡状态，响应类型 （短响应 未使用   长响应 卡状态[95:64]）
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 卡状态
 */
am_static_inline
uint32_t amhw_mci_resp1_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->resp1;
}

/**
 * \brief 读取卡状态，响应类型 （短响应 未使用   长响应 卡状态[63:32]）
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 卡状态
 */
am_static_inline
uint32_t amhw_mci_resp2_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->resp2;
}

/**
 * \brief 读取卡状态，响应类型 （短响应 未使用   长响应 卡状态[31:1] [0]始终为0）
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 卡状态
 */
am_static_inline
uint32_t amhw_mci_resp3_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->resp3;
}

/**
 * \brief 设置数据定时器寄存器
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 * \param[in] datatime : 数据超时周期
 *
 * \return 无
 */
am_static_inline
void amhw_mci_datatmr_set (amhw_mci_t *p_hw_mci, uint32_t datatime)
{
    p_hw_mci->datatmr = datatime;
}

/**
 * \brief 读取数据定时器的值
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 数据定时器的值
 */
am_static_inline
uint32_t amhw_mci_datatmr_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->datatmr;
}

/**
 * \brief 设置数据长度寄存器
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 * \param[in] datalen  : 数据长度
 *
 * \return 无
 */
am_static_inline
void amhw_mci_datalen_set (amhw_mci_t *p_hw_mci, uint16_t datalen)
{
    p_hw_mci->datalen = datalen;
}

/**
 * \brief 读取数据长度的值
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 数据长度的值
 */
am_static_inline
uint16_t amhw_mci_datalen_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->datalen;
}

/**
 * \name MCI 数据控制寄存器位定义
 * \anchor grp_amhw_mci_datactrl
 * @{
 */

#define AMHW_MCI_DATA_CTRL_EN       (1UL << 0)  /**< \brief 数据传输使能 */
#define AMHW_MCI_DATA_CTRL_DIR      (1UL << 1)  /**< \brief 数据传输方向 */
#define AMHW_MCI_DATA_CTRL_MOD      (1UL << 2)  /**< \brief 数据传输模式 */
#define AMHW_MCI_DATA_CTRL_DMA_EN   (1UL << 3)  /**< \brief 使能DMA     */
#define AMHW_MCI_DATA_CTRL_BLKSIZE  (1UL << 4)  /**< \brief 数据块长度      */

/** @} */

/**
 * \name MCI 数据传输方向定义
 * \anchor grp_amhw_mci_datadir
 * @{
 */

typedef int amhw_mci_data_dir_t;                /**< \brief 数据传输方向定义 */
#define AMHW_MCI_DATA_DIR_M2C       (0UL << 1)  /**< \brief 从控制器到卡 */
#define AMHW_MCI_DATA_DIR_C2M       (1UL << 1)  /**< \brief 从卡到控制器 */

/** @} */

/**
 * \name MCI 数据模式定义
 * \anchor grp_amhw_mci_datamode
 * @{
 */

typedef int amhw_mci_data_mod_t;                 /**< \brief 数据模式定义 */
#define AMHW_MCI_DATA_MOD_BLK_TRAN   (0UL << 2)  /**< \brief 块数据传输 */
#define AMHW_MCI_DATA_DIR_STR_TRAN   (1UL << 2)  /**< \brief 流数据传输 */

/** @} */

/**
 * \name MCI 数据传输方向定义
 * \anchor grp_amhw_mci_datactrl_en
 * @{
 */

typedef int amhw_mci_datactrl_en_t;            /**< \brief 数据传输使能定义 */
#define AMHW_MCI_DATACTRL_EN       (1UL << 0)  /**< \brief 数据传输使能 */
#define AMHW_MCI_DATACTRL_DIS      (0UL << 0)  /**< \brief 数据传输禁能 */
#define AMHW_MCI_DATACTRL_DMA_EN   (1UL << 3)  /**< \brief 数据DMA传输使能 */
#define AMHW_MCI_DATACTRL_DMA_DIS  (0UL << 3)  /**< \brief 数据DMA传输禁能 */

/** @} */

/**
 * \brief 设置数据控制器
 *
 * \param[in] p_hw_mci    : 指向MCI寄存器块的指针
 * \param[in] dir         : 数据方向 配置参数，参见
 *                          \ref grp_amhw_mci_datadir "MCI DATA DIRECTION"
 * \param[in] mod         : 数据发送模式   配置参数，参见
 *                          \ref grp_amhw_mci_datamode "MCI DATA MODE"
 * \param[in] blocksize   : 数据块长度 （2的blocksize次方字节）
 * \param[in] datactrl_en : 数据传输使能   配置参数，参见
 *                          \ref grp_amhw_mci_datactrl_en "MCI DATA TRANS ENABLE"
 *
 * \return 无
 */
am_static_inline
void amhw_mci_datactrl_set (amhw_mci_t             *p_hw_mci,
                            amhw_mci_data_dir_t     dir,
                            amhw_mci_data_mod_t     mod,
                            size_t                  blocksize,
                            amhw_mci_datactrl_en_t  datactrl_en)
{
    p_hw_mci->datactrl = dir |
                         mod |
                         ((blocksize & 0xf) << 4) |
                         datactrl_en;
}

/**
 * \brief 获取数据传输方向
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 数据的方向
 */
am_static_inline
amhw_mci_data_dir_t amhw_mci_data_dir_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->datactrl & AMHW_MCI_DATA_CTRL_DIR);
}

/**
 * \brief 获取数据传输模式
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 数据的模式
 */
am_static_inline
amhw_mci_data_mod_t amhw_mci_data_mod_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->datactrl & AMHW_MCI_DATA_CTRL_MOD);
}

/**
 * \brief 获取数据传输使能的状态位
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 传输的使能状态位
 */
am_static_inline
amhw_mci_datactrl_en_t amhw_mci_datactrl_enable_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->datactrl    &
           (AMHW_MCI_DATA_CTRL_EN |
            AMHW_MCI_DATA_CTRL_DMA_EN));
}

/**
 * \brief 获取数据块长度
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 数据块长度
 */
am_static_inline
size_t amhw_mci_data_blksize_get (amhw_mci_t *p_hw_mci)
{
    return ((p_hw_mci->datactrl & 0xf0) >> 4);
}

/**
 * \brief 读取数据计数器
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 数据剩余的数据
 */
am_static_inline
uint16_t amhw_mci_datacnt_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->datacnt;
}

/**
 * \name MCI 中断类型个数
 * \anchor grp_amhw_mci_int_type_count
 * @{
 */

#define AMHW_MCI_INT_TYPE_COUNT          22       /**< \brief 中断类型的个数  */

/** @} */

/**
 * \name MCI 中断类型定义
 * \anchor grp_amhw_mci_int_type
 * @{
 */

typedef uint32_t amhw_mci_int_type_t;             /**< \brief 中断类型定义 */
#define AMHW_MCI_INT_NONE             (0X0UL)     /**< \brief 无中断  */
#define AMHW_MCI_INT_CMDCRCFAIL       (1UL << 0)  /**< \brief 命令响应接收（未通过 CRC 校验） */
#define AMHW_MCI_INT_DATACRCFAIL      (1UL << 1)  /**< \brief 数据块发送/接收（未通过 CRC 校验） */
#define AMHW_MCI_INT_CMDTIMEOUT       (1UL << 2)  /**< \brief 命令响应超时 */
#define AMHW_MCI_INT_DATATIMEOUT      (1UL << 3)  /**< \brief 数据超时 */
#define AMHW_MCI_INT_TXUNDERRUN       (1UL << 4)  /**< \brief 发送 FIFO 下溢错误 */
#define AMHW_MCI_INT_RXOVERRUN        (1UL << 5)  /**< \brief 接收 FIFO 溢出错误 */
#define AMHW_MCI_INT_CMDRESPEND       (1UL << 6)  /**< \brief 命令响应接收（通过 CRC 校验） */
#define AMHW_MCI_INT_CMDSENT          (1UL << 7)  /**< \brief 命令发送（无需响应） */
#define AMHW_MCI_INT_DATAEND          (1UL << 8)  /**< \brief 数据终止（数据计数器为 0） */
#define AMHW_MCI_INT_STARTBITERR      (1UL << 9)  /**< \brief 在宽总线模式下，所有数据信号上未检测到起始位 */
#define AMHW_MCI_INT_DATABLKEND       (1UL << 10) /**< \brief 数据块发送/接收（通过 CRC 校验） */
#define AMHW_MCI_INT_CMDACTIVE        (1UL << 11) /**< \brief 命令传输正在进行中 */
#define AMHW_MCI_INT_TXACTIVE         (1UL << 12) /**< \brief 数据发送正在进行中 */
#define AMHW_MCI_INT_RXACTIVE         (1UL << 13) /**< \brief 数据接收正在进行中 */
#define AMHW_MCI_INT_TXFIFOHEMPTY     (1UL << 14) /**< \brief 发送 FIFO 为半空 */
#define AMHW_MCI_INT_RXFIFOHFULL      (1UL << 15) /**< \brief 接收 FIFO 为半满 */
#define AMHW_MCI_INT_TXFIFOFULL       (1UL << 16) /**< \brief 发送 FIFO 为满 */
#define AMHW_MCI_INT_RXFIFOFULL       (1UL << 17) /**< \brief 接收 FIFO 为满 */
#define AMHW_MCI_INT_TXFIFOEMPTY      (1UL << 18) /**< \brief 发送 FIFO 为空 */
#define AMHW_MCI_INT_RXFIFOEMPTY      (1UL << 19) /**< \brief 接收 FIFO 为空 */
#define AMHW_MCI_INT_TXDATAAVIBL      (1UL << 20) /**< \brief 发送 FIFO 中存在可用数据 */
#define AMHW_MCI_INT_RXDATAAVIBL      (1UL << 21) /**< \brief 接收 FIFO 中存在可用数据 */
#define AMHW_MCI_INT_ALL              (0X3FFFFFUL)/**< \brief 所有类型中断  */

/** @} */

/**
 * \brief 读取状态寄存器
 *
 * \param[in] p_hw_mci : 指向MCI寄存器块的指针
 *
 * \return 参见 \ref grp_amhw_mci_int_type "MCI STATUS"
 *
 * \note   静态[10:0]： 这些标志会保持为有效， 直至通过写入清除寄存器将它们清除
 *         动态[21:1 1]：这些更改状态取决于底层逻辑的状态（例如，在写入 FIFO 时
 *                       FIFO 满和空标志会作为数据被设为有效和无效） 。
 */
am_static_inline
amhw_mci_int_type_t amhw_mci_status_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->status;
}

/**
 * \brief 设置清零寄存器   清零相应的静态状态标志
 *
 * \param[in] p_hw_mci   : 指向MCI寄存器块的指针
 * \param[in] status_clr : 需要清零的状态位     配置参数，参见
 *                         \ref grp_amhw_mci_int_type "MCI STATUS"
 *                         只有前11位[0:10]可进行清零  其余为保留位
 *
 * \return 无
 */
am_static_inline
void amhw_mci_status_clr (amhw_mci_t          *p_hw_mci,
                          amhw_mci_int_type_t  status_clr)
{
    p_hw_mci->clear = status_clr & 0x7ff;
}

/**
 * \brief 设置中断屏蔽寄存器  使能相应的中断位
 *
 * \param[in] p_hw_mci   : 指向MCI寄存器块的指针
 * \param[in] int_mask   : 需要屏蔽的中断位     配置参数，参见
 *                         \ref grp_amhw_mci_int_type "MCI INT MASK"
 *
 * \return 无
 */
am_static_inline
void amhw_mci_int_enable_set (amhw_mci_t          *p_hw_mci,
                              amhw_mci_int_type_t  int_mask)
{
    p_hw_mci->mask0 |= int_mask;
}

/**
 * \brief 清除中断屏蔽寄存器  禁能相应的中断位
 *
 * \param[in] p_hw_mci   : 指向MCI寄存器块的指针
 * \param[in] int_mask   : 需要屏蔽的中断位     配置参数，参见
 *                         \ref grp_amhw_mci_int_type "MCI INT MASK"
 *
 * \return 无
 */
am_static_inline
void amhw_mci_int_enable_clr (amhw_mci_t          *p_hw_mci,
                              amhw_mci_int_type_t  int_mask)
{
    p_hw_mci->mask0 &= ~int_mask;
}

/**
 * \brief 读取中断屏蔽寄存器
 *
 * \param[in] p_hw_mci   : 指向MCI寄存器块的指针
 *
 * \return 使能的中断位，参见 \ref grp_amhw_mci_int_type "MCI INT MASK"
 */
am_static_inline
amhw_mci_int_type_t amhw_mci_int_mask_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->mask0;
}

/**
 * \brief 读取FIFO计数器
 *
 * \param[in] p_hw_mci   : 指向MCI寄存器块的指针
 *
 * \return FIFO计数值
 */
am_static_inline
uint16_t amhw_mci_fifocnt_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->fifocnt;
}

/**
 * \brief 设置FIFO数据
 *
 * \param[in] p_hw_mci   : 指向MCI寄存器块的指针
 * \param[in] chn        : 通道
 * \param[in] data       : 要写入的数据
 *
 * \return 无
 */
am_static_inline
void amhw_mci_fifodata_set (amhw_mci_t *p_hw_mci, uint32_t chn, uint32_t data)
{
    p_hw_mci->fifo[chn] = data;
}

/**
 * \brief 读取FIFO数据
 *
 * \param[in] p_hw_mci   : 指向MCI寄存器块的指针
 * \param[in] chn        : 通道
 *
 * \return FIFO数据
 */
am_static_inline
uint32_t amhw_mci_fifodata_get (amhw_mci_t *p_hw_mci, uint32_t chn)
{
    return p_hw_mci->fifo[chn];
}

/**
 * @} amhw_if_mci
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MCI_H */

/* end of file */
