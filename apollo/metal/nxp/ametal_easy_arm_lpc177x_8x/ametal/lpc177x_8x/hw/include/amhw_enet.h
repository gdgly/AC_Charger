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
 * \brief  ENET硬件操作接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-08-02  snk, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_ENET_H
#define __AMHW_ENET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_enet
 * \copydoc amhw_enet.h
 * @{
 */

    
/**
 * \brief ENET寄存器块的结构体
 */
typedef struct amhw_enet {
    __IO uint32_t mac1;    				/**< \brief MAC配置寄存器1  */                
    __IO uint32_t mac2;    				/**< \brief MAC配置寄存器2  */
    __IO uint32_t ipgt;    				/**< \brief 连续的两包的内部包间隔寄存器  */
    __IO uint32_t ipgr;					/**< \brief 非连续的两包的内部包间隔寄存器  */
    __IO uint32_t clrt;					/**< \brief 冲突窗口/重试寄存器  */
    __IO uint32_t maxf;					/**< \brief 最大帧寄存器  */
    __IO uint32_t supp;					/**< \brief PHY支持寄存器  */
    __IO uint32_t test;					/**< \brief 测试寄存器  */
    __IO uint32_t mcfg;					/**< \brief MII Mgmt配置寄存器  */
    __IO uint32_t mcmd;					/**< \brief MII Mgmt命令寄存器  */
    __IO uint32_t madr;					/**< \brief MII Mgmt地址寄存器  */
    __O  uint32_t mwtd;					/**< \brief MII Mgmt写数据寄存器  */
    __I  uint32_t mrdd;					/**< \brief MII Mgmt读数据寄存器  */
    __I  uint32_t mind;					/**< \brief MII Mgmt指示寄存器  */
         uint32_t reserverd0[2];		/**< \brief 保留  */
    __IO uint32_t sa0;					/**< \brief 站地址0寄存器  */
    __IO uint32_t sa1;					/**< \brief 站地址1寄存器  */
    __IO uint32_t sa2;					/**< \brief 站地址2寄存器  */
         uint32_t reserved1[45];		/**< \brief 保留  */
    __IO uint32_t command;   			/**< \brief 命令寄存器  */             
    __I  uint32_t status;				/**< \brief 状态寄存器  */
    __IO uint32_t rx_descriptor;		/**< \brief 接收描述符基址寄存器  */
    __IO uint32_t rx_status;			/**< \brief 接收状态基址寄存器  */
    __IO uint32_t rx_descriptor_number;	/**< \brief 接收描述符数目寄存器  */
    __I  uint32_t rx_produce_index;		/**< \brief 接收产生索引寄存器  */
    __IO uint32_t rx_consume_index;		/**< \brief 接收消耗索引寄存器  */
    __IO uint32_t tx_descriptor;		/**< \brief 发送描述符基址寄存器 */
    __IO uint32_t tx_status;			/**< \brief 发送状态基址寄存器  */
    __IO uint32_t tx_descriptor_number; /**< \brief 发送描述符数目寄存器 */
    __IO uint32_t tx_produce_index;		/**< \brief 发送产生索引寄存器  */
    __I  uint32_t tx_consume_index;		/**< \brief 发送消耗索引寄存器  */
         uint32_t reserved2[10];		/**< \brief 保留  */
    __I  uint32_t tsv0;					/**< \brief 发送状态向量0寄存器  */
    __I  uint32_t tsv1;					/**< \brief 发送状态向量1寄存器  */
    __I  uint32_t rsv;					/**< \brief 发送状态向量2寄存器  */
         uint32_t reserved3[3];			/**< \brief 保留  */
    __IO uint32_t flow_control_counter;	/**< \brief 流控制计数器寄存器  */
    __I  uint32_t flow_control_status;	/**< \brief 流控制状态寄存器  */
         uint32_t reserved4[34];		/**< \brief 保留  */
    __IO uint32_t rx_filter_ctrl;  		/**< \brief 接收过滤寄存器  */
    __IO uint32_t rx_filter_wol_status;	/**< \brief 接收过滤器WoL状态寄存器  */
    __IO uint32_t rx_filter_wol_clear;	/**< \brief 接收过滤器WoL清零寄存器  */
         uint32_t reserved5;			/**< \brief 保留  */
    __IO uint32_t hash_filter_l;		/**< \brief Hash过滤器表LSBs寄存器  */
    __IO uint32_t hash_filter_h;		/**< \brief Hash过滤器表MSBs寄存器  */
         uint32_t reserved6[882];		/**< \brief 保留  */
    __I  uint32_t int_status;  			/**< \brief 中断状态寄存器  */
    __IO uint32_t int_enable;			/**< \brief 中断使能寄存器  */
    __O  uint32_t int_clear;			/**< \brief 中断清零寄存器  */
    __O  uint32_t int_set;				/**< \brief 中断置位寄存器  */
         uint32_t reserved7;			/**< \brief 保留  */
    __IO uint32_t power_down;			/**< \brief 掉电寄存器  */
         uint32_t reserved8;			/**< \brief 保留  */
    __IO uint32_t module_id;			/**< \brief 模块控制寄存器  */
} amhw_enet_t;


/**
 * \name EMAC PHY状态类型定义
 * \anchor grp_amhw_enet_phy_state
 * @{
 */
#define AMHW_EMAC_PHY_STAT_LINK			(0)		/**<  \brief Link状态 */
#define AMHW_EMAC_PHY_STAT_SPEED		(1)		/**<  \brief Speed状态 */
#define AMHW_EMAC_PHY_STAT_DUP			(2)		/**<  \brief Duplex状态 */
/** @} */


/**
 * \name 配置16k的以太网内存缓存
 * @{
 */
#define AMHW_EMAC_NUM_RX_FRAG         4           /**<  \brief 接收帧 4*1536= 6.0kB */
#define AMHW_EMAC_NUM_TX_FRAG         4           /**<  \brief 发送帧 4*1536= 6.0kB */
#define AMHW_EMAC_ETH_MAX_FLEN        1536        /**<  \brief 帧大小  */
#define AMHW_EMAC_TX_FRAME_TOUT       0x00100000  /**<  \brief 帧传输超时 */
/** @} */


/**
* \name EMAC 收发基址宏定义
* @{
*/
#define AMHW_EMAC_ETH_FRAG_SIZE       1536         /**<  \brief  包大小 */

extern uint8_t __g_amhw_emac_buf[((AMHW_EMAC_NUM_RX_FRAG + AMHW_EMAC_NUM_TX_FRAG) \
    * AMHW_EMAC_ETH_MAX_FLEN) + \
     (AMHW_EMAC_NUM_TX_FRAG * 2 + AMHW_EMAC_NUM_TX_FRAG) * 8 + \
     (AMHW_EMAC_NUM_RX_FRAG * 4)] __attribute__((section(".ahb_bss"))) \
                                  __attribute__((aligned(4)));

/**  \brief 接收描述符基址  */
#define AMHW_EMAC_RX_DESC_BASE        ((uint32_t)&__g_amhw_emac_buf[0])

#define AMHW_EMAC_RX_STAT_BASE        (AMHW_EMAC_RX_DESC_BASE + AMHW_EMAC_NUM_RX_FRAG * 8) /**<  \brief 接收状态基址  */
#define AMHW_EMAC_TX_DESC_BASE        (AMHW_EMAC_RX_STAT_BASE + AMHW_EMAC_NUM_RX_FRAG * 8) /**<  \brief 发送描述符基址  */
#define AMHW_EMAC_TX_STAT_BASE        (AMHW_EMAC_TX_DESC_BASE + AMHW_EMAC_NUM_TX_FRAG * 8) /**<  \brief 发送状态基址  */
#define AMHW_EMAC_RX_BUF_BASE         (AMHW_EMAC_TX_STAT_BASE + AMHW_EMAC_NUM_TX_FRAG * 4) /**<  \brief 接收缓冲基址  */
#define AMHW_EMAC_TX_BUF_BASE         (AMHW_EMAC_RX_BUF_BASE  + AMHW_EMAC_NUM_RX_FRAG * AMHW_EMAC_ETH_FRAG_SIZE) /**<  \brief 接收缓冲基址  */

#define AMHW_EMAC_RX_DESC_PACKET(i)   (*(unsigned int *)(AMHW_EMAC_RX_DESC_BASE     + 8 * i)) /**<  \brief 接收包基址  */
#define AMHW_EMAC_RX_DESC_CTRL(i)     (*(unsigned int *)(AMHW_EMAC_RX_DESC_BASE + 4 + 8 * i)) /**<  \brief 接收控制基址  */
#define AMHW_EMAC_RX_STAT_INFO(i)     (*(unsigned int *)(AMHW_EMAC_RX_STAT_BASE     + 8 * i)) /**<  \brief 接收信息基址  */
#define AMHW_EMAC_RX_STAT_HASHCRC(i)  (*(unsigned int *)(AMHW_EMAC_RX_STAT_BASE + 4 + 8 * i)) /**<  \brief 接收CRC基址  */
#define AMHW_EMAC_TX_DESC_PACKET(i)   (*(unsigned int *)(AMHW_EMAC_TX_DESC_BASE     + 8 * i)) /**<  \brief 发送包基址  */
#define AMHW_EMAC_TX_DESC_CTRL(i)     (*(unsigned int *)(AMHW_EMAC_TX_DESC_BASE + 4 + 8 * i)) /**<  \brief 发送控制基址  */
#define AMHW_EMAC_TX_STAT_INFO(i)     (*(unsigned int *)(AMHW_EMAC_TX_STAT_BASE     + 4 * i)) /**<  \brief 发送信息基址  */
#define AMHW_EMAC_RX_BUF(i)           (AMHW_EMAC_RX_BUF_BASE + AMHW_EMAC_ETH_FRAG_SIZE * i)   /**<  \brief  接收数组基址 */
#define AMHW_EMAC_TX_BUF(i)           (AMHW_EMAC_TX_BUF_BASE + AMHW_EMAC_ETH_FRAG_SIZE * i)   /**<  \brief  发送数组基址 */

#define AMHW_EMAC_RCTRL_INT           0x80000000  /**< \brief 接收完成中断  */

/** @} */

/**
 * \name EMAC PHY工作模式
 * @{
 */
#define AMHW_EMAC_MODE_AUTO				(0)		/**<  \brief 自动模式 */
#define AMHW_EMAC_MODE_10M_FULL			(1)		/**<  \brief 10M全双工模式 */
#define AMHW_EMAC_MODE_10M_HALF			(2)		/**<  \brief 10M半双工模式 */
#define AMHW_EMAC_MODE_100M_FULL		(3)		/**<  \brief 100M全双工模式 */
#define AMHW_EMAC_MODE_100M_HALF		(4)		/**<  \brief 100M半双工模式 */
/** @} */

/* 位定义 */

/**
 * \name MAC配置寄存器1位定义
 * @{
 */
#define AMHW_EMAC_MAC1_REC_EN         0x00000001  /**<  \brief 接收使能 */
#define AMHW_EMAC_MAC1_PASS_ALL       0x00000002  /**<  \brief 传递所有接收帧 */
#define AMHW_EMAC_MAC1_RX_FLOWC       0x00000004  /**<  \brief 接收流控制 */
#define AMHW_EMAC_MAC1_TX_FLOWC       0x00000008  /**<  \brief 发送流控制 */
#define AMHW_EMAC_MAC1_LOOPB          0x00000010  /**<  \brief 回环模式 */
#define AMHW_EMAC_MAC1_RES_TX         0x00000100  /**<  \brief 复位发送逻辑 */
#define AMHW_EMAC_MAC1_RES_MCS_TX     0x00000200  /**<  \brief 复位MAC发送控制子层 */
#define AMHW_EMAC_MAC1_RES_RX         0x00000400  /**<  \brief 复位接收逻辑 */
#define AMHW_EMAC_MAC1_RES_MCS_RX     0x00000800  /**<  \brief 复位MAC接收控制子层 */
#define AMHW_EMAC_MAC1_SIM_RES        0x00004000  /**<  \brief 随机发生器复位 */
#define AMHW_EMAC_MAC1_SOFT_RES       0x00008000  /**<  \brief 软件复位MAC */
/** @} */

/**
 * \name MAC配置寄存器2位定义
 * @{
 */
#define AMHW_EMAC_MAC2_FULL_DUP       0x00000001  /**<  \brief 全双工模式 */
#define AMHW_EMAC_MAC2_FRM_LEN_CHK    0x00000002  /**<  \brief 帧长校验 */
#define AMHW_EMAC_MAC2_HUGE_FRM_EN    0x00000004  /**<  \brief 巨帧使能 */
#define AMHW_EMAC_MAC2_DLY_CRC        0x00000008  /**<  \brief 延时校验 */
#define AMHW_EMAC_MAC2_CRC_EN         0x00000010  /**<  \brief 扩展延时校验到每帧 */
#define AMHW_EMAC_MAC2_PAD_EN         0x00000020  /**<  \brief 填充短帧 */
#define AMHW_EMAC_MAC2_VLAN_PAD_EN    0x00000040  /**<  \brief VLAN填充使能 */
#define AMHW_EMAC_MAC2_ADET_PAD_EN    0x00000080  /**<  \brief 自动检测填充使能 */
#define AMHW_EMAC_MAC2_PPREAM_ENF     0x00000100  /**<  \brief 校验导言内容 */
#define AMHW_EMAC_MAC2_LPREAM_ENF     0x00000200  /**<  \brief 校验导言长度 */
#define AMHW_EMAC_MAC2_NO_BACKOFF     0x00001000  /**<  \brief 后退算法 */
#define AMHW_EMAC_MAC2_BACK_PRESSURE  0x00002000  /**<  \brief 背压/后退 */
#define AMHW_EMAC_MAC2_EXCESS_DEF     0x00004000  /**<  \brief 载波侦听 */
/** @} */

/**
 * \name 连续的两包的内部包间隔（ipgt）寄存器  
 * @{
 */
/**  \brief 连续的两包的内部包间隔寄存器位宏定义 */
#define AMHW_EMAC_IPGT_BBIPG(n)		 (n&0x7F)
/**  \brief 全双工模式 */
#define AMHW_EMAC_IPGT_FULL_DUP		 (AMHW_EMAC_IPGT_BBIPG(0x15))
/**  \brief 半双工模式 */
#define AMHW_EMAC_IPGT_HALF_DUP      (AMHW_EMAC_IPGT_BBIPG(0x12))
/** @} */

/**
 * \name 非连续的两包的内部包间隔（ipgr）寄存器  
 * @{
 */
/**  \brief 非连续的两包的内部包间隔寄存器位定义 */
#define AMHW_EMAC_IPGR_NBBIPG_P2(n)	(n&0x7F)
/**  \brief 非连续的两包的内部包间隔寄存器部分2 */
#define AMHW_EMAC_IPGR_P2_DEF		(AMHW_EMAC_IPGR_NBBIPG_P2(0x12))
/**  \brief 服从载波字段 */
#define AMHW_EMAC_IPGR_NBBIPG_P1(n)	((n&0x7F)<<8)
/**  \brief 非连续的两包的内部包间隔寄存器部分1 */
#define AMHW_EMAC_IPGR_P1_DEF        AMHW_EMAC_IPGR_NBBIPG_P1(0x0C)
/** @} */

/* 冲突窗口/重试寄存器 */
/**
 * \name 非连续的两包的内部包间隔寄存器  ipgr位定义
 * @{
 */
/**  \brief 冲突之后重新发送次数 */
#define AMHW_EMAC_CLRT_MAX_RETX(n)	(n&0x0F)
/**  \brief 时间槽/冲突窗口设置 */
#define AMHW_EMAC_CLRT_COLL(n)		((n&0x3F)<<8)
/**  \brief 时间槽/冲突窗口默认值 */
#define AMHW_EMAC_CLRT_DEF          ((AMHW_EMAC_CLRT_MAX_RETX(0x0F))|\
                                    (AMHW_EMAC_CLRT_COLL(0x37)))
/** @} */

/**
 * \name 最大帧寄存器位定义
 * @{
 */
/**  \brief 最大帧寄存器位宏定义 */
#define AMHW_EMAC_MAXF_MAXFRMLEN(n)	(n&0xFFFF)
/** @} */

/**
 * \name PHY支持寄存器位定义
 * @{
 */
#define AMHW_EMAC_SUPP_SPEED			0x00000100  	/**<  \brief 配置简化的MII逻辑以用于当前的操作速率 */
#define AMHW_EMAC_SUPP_RES_RMII         0x00000800  	/**<  \brief 简化的MII逻辑 */
/** @} */

/**
 * \name 测试寄存器位定义
 * @{
 */
#define AMHW_EMAC_TEST_SHCUT_PQUANTA  0x00000001  	/**<  \brief 减少量子时间 */
#define AMHW_EMAC_TEST_TST_PAUSE      0x00000002  	/**<  \brief 测试暂停 */
#define AMHW_EMAC_TEST_TST_BACKP      0x00000004  	/**<  \brief 产生背压 */
/** @} */

/**
 * \name MII Management配置寄存器位定义
 * @{
 */
#define AMHW_EMAC_MCFG_SCAN_INC       0x00000001  	/**<  \brief 连续读取PHY地址 */
#define AMHW_EMAC_MCFG_SUPP_PREAM     0x00000002  	/**<  \brief 禁止导言 */
#define AMHW_EMAC_MCFG_CLK_SEL(n)     ((n&0x0F)<<2)  /**<  \brief 时钟选择域 */
#define AMHW_EMAC_MCFG_RES_MII        0x00008000  	/**<  \brief 复位MII硬件 */
#define AMHW_EMAC_MCFG_MII_MAXCLK	  2500000UL		/**<  \brief MII最大时钟 */
/** @} */


/**
 * \name MII Management命令寄存器位定义
 * @{
 */
#define AMHW_EMAC_MCMD_READ           0x00000001  	/**<  \brief MII读 */
#define AMHW_EMAC_MCMD_SCAN           0x00000002  	/**<  \brief MII连续浏览 */
#define AMHW_EMAC_MII_WR_TOUT         0x00050000  	/**<  \brief MII写超时 */
#define AMHW_EMAC_MII_RD_TOUT         0x00050000  	/**<  \brief MII读超时 */


/**
 * \name MII Management地址寄存器位定义
 * @{
 */
#define AMHW_EMAC_MADR_REG_ADR(n)     (n&0x1F)  	/**<  \brief MII寄存器地址域 */
#define AMHW_EMAC_MADR_PHY_ADR(n)     ((n&0x1F)<<8)  /**<  \brief PHY地址域 */
/** @} */

/**
 * \name MII管理写数据寄存器位定义
 * @{
 */
/**  \brief MII管理写数据寄存器 */
#define AMHW_EMAC_MWTD_DATA(n)		(n&0xFFFF)		
/** @} */

/**
 * \name MII管理读数据寄存器位定义
 * @{
 */
/**  \brief MII管理读数据寄存器 */
#define AMHW_EMAC_MRDD_DATA(n)		(n&0xFFFF)		
/** @} */

/**
 * \name MII管理指示寄存器位定义
 * @{
 */
#define AMHW_EMAC_MIND_BUSY           0x00000001  	/**<  \brief MII忙 */
#define AMHW_EMAC_MIND_SCAN           0x00000002  	/**<  \brief MII扫描正在进行 */
#define AMHW_EMAC_MIND_NOT_VAL        0x00000004  	/**<  \brief MII读数据无效 */
#define AMHW_EMAC_MIND_MII_LINK_FAIL  0x00000008  	/**<  \brief MII连接失败 */
/** @} */


/* 控制寄存器宏定义 */
/**
 * \name 命令寄存器位定义
 * @{
 */
#define AMHW_EMAC_CR_RX_EN            0x00000001  	/**<  \brief 接收使能 */
#define AMHW_EMAC_CR_TX_EN            0x00000002  	/**<  \brief 发送使能 */
#define AMHW_EMAC_CR_REG_RES          0x00000008  	/**<  \brief 寄存器复位 */
#define AMHW_EMAC_CR_TX_RES           0x00000010  	/**<  \brief 发送通道复位 */
#define AMHW_EMAC_CR_RX_RES           0x00000020  	/**<  \brief 接收通道复位 */
#define AMHW_EMAC_CR_PASS_RUNT_FRM    0x00000040  	/**<  \brief 短帧滤除 */
#define AMHW_EMAC_CR_PASS_RX_FILT     0x00000080  	/**<  \brief 接收过滤 */
#define AMHW_EMAC_CR_TX_FLOW_CTRL     0x00000100  	/**<  \brief 发送流控制 */
#define AMHW_EMAC_CR_RMII             0x00000200  	/**<  \brief 精简MII接口 */
#define AMHW_EMAC_CR_FULL_DUP         0x00000400  	/**<  \brief 全双工 */
/** @} */

/**
 * \name 状态寄存器位定义
 * @{
 */
#define AMHW_EMAC_SR_RX_EN            0x00000001  	/**<  \brief 接收使能  */
#define AMHW_EMAC_SR_TX_EN            0x00000002  	/**<  \brief 发送使能 */
/** @} */

/**
 * \name 发送状态向量0寄存器位宏定义
 * @{
 */
#define AMHW_EMAC_TSV0_CRC_ERR        0x00000001  /**<  \brief CRC错误 */
#define AMHW_EMAC_TSV0_LEN_CHKERR     0x00000002  /**<  \brief 长度校验错误 */
#define AMHW_EMAC_TSV0_LEN_OUTRNG     0x00000004  /**<  \brief 长度区域 */
#define AMHW_EMAC_TSV0_DONE           0x00000008  /**<  \brief 发送完成 */
#define AMHW_EMAC_TSV0_MCAST          0x00000010  /**<  \brief 包的目标地址为多播地址 */
#define AMHW_EMAC_TSV0_BCAST          0x00000020  /**<  \brief 包的目标地址为广播地址 */
#define AMHW_EMAC_TSV0_PKT_DEFER      0x00000040  /**<  \brief 包延迟 */
#define AMHW_EMAC_TSV0_EXC_DEFER      0x00000080  /**<  \brief 包延迟时间超出规定值 */
#define AMHW_EMAC_TSV0_EXC_COLL       0x00000100  /**<  \brief 延迟冲突 */
#define AMHW_EMAC_TSV0_LATE_COLL      0x00000200  /**<  \brief 产生的冲突超出了冲突窗口 */
#define AMHW_EMAC_TSV0_GIANT          0x00000400  /**<  \brief 巨帧 */
#define AMHW_EMAC_TSV0_UNDERRUN       0x00000800  /**<  \brief 主机方引起的缓冲区下溢 */
#define AMHW_EMAC_TSV0_BYTES          0x0FFFF000  /**<  \brief 包含冲突尝试帧内的传输字节数 */
#define AMHW_EMAC_TSV0_CTRL_FRAME     0x10000000  /**<  \brief 控制帧*/
#define AMHW_EMAC_TSV0_PAUSE          0x20000000  /**<  \brief 暂停帧 */
#define AMHW_EMAC_TSV0_BACK_PRESS     0x40000000  /**<  \brief 背压应用 */
#define AMHW_EMAC_TSV0_VLAN           0x80000000  /**<  \brief VLAN帧 */
/** @} */

/**
 * \name 发送状态向量寄存器1定义
 * @{
 */
#define AMHW_EMAC_TSV1_BYTE_CNT       0x0000FFFF  /**<  \brief 传送字节总数 */
#define AMHW_EMAC_TSV1_COLL_CNT       0x000F0000  /**<  \brief 传送冲突计数 */
/** @} */

/**
 * \name 接收状态向量寄存器位定义
 * @{
 */
#define AMHW_EMAC_RSV_BYTE_CNT        0x0000FFFF  /**<  \brief 接收帧信息长度 */
#define AMHW_EMAC_RSV_PKT_IGNORED     0x00010000  /**<  \brief 忽略前一个包 */
#define AMHW_EMAC_RSV_RXDV_SEEN       0x00020000  /**<  \brief 前一事件长度不够，不能成为有效包 */
#define AMHW_EMAC_RSV_CARR_SEEN       0x00040000  /**<  \brief 前一接收统计后，检测到载波事件 */
#define AMHW_EMAC_RSV_REC_CODEV       0x00080000  /**<  \brief 接收代码无效 */
#define AMHW_EMAC_RSV_CRC_ERR         0x00100000  /**<  \brief CRC错误 */
#define AMHW_EMAC_RSV_LEN_CHKERR      0x00200000  /**<  \brief 长度校验错误 */
#define AMHW_EMAC_RSV_LEN_OUTRNG      0x00400000  /**<  \brief 长度范围 */
#define AMHW_EMAC_RSV_REC_OK          0x00800000  /**<  \brief 帧接收正常 */
#define AMHW_EMAC_RSV_MCAST           0x01000000  /**<  \brief 包的目标地址为多播地址 */
#define AMHW_EMAC_RSV_BCAST           0x02000000  /**<  \brief 包的目标地址为广播地址 */
#define AMHW_EMAC_RSV_DRIB_NIBB       0x04000000  /**<  \brief 接收到包之后又接收到另一个1-7位的数据 */
#define AMHW_EMAC_RSV_CTRL_FRAME      0x08000000  /**<  \brief 控制帧 */
#define AMHW_EMAC_RSV_PAUSE           0x10000000  /**<  \brief 暂停帧 */
#define AMHW_EMAC_RSV_UNSUPP_OPC      0x20000000  /**<  \brief 未知操作码 */
#define AMHW_EMAC_RSV_VLAN            0x40000000  /**<  \brief VLAN帧 */
/** @} */

/**
 * \name 流控制计数器寄存器定义
 * @{
 */
#define AMHW_EMAC_FCC_MIRR_CNT(n)        	(n&0xFFFF)  		/**<  \brief 重新发送暂停控制帧之前的周期数 */
#define AMHW_EMAC_FCC_PAUSE_TIM(n)       	((n&0xFFFF)<<16)  	/**<  \brief 暂停定时器值 */
/** @} */

/**
 * \name 流控制状态寄存器定义
 * @{
 */
#define AMHW_EMAC_FCS_MIRR_CNT(n)        	(n&0xFFFF)  		/**<  \brief 镜像计算器当前值 */
/** @} */


/* 接收过滤寄存器定义 */
/**
 * \name 接收过滤器控制寄存器位定义
 * @{
 */
#define AMHW_EMAC_RFC_UCAST_EN        0x00000001  /**<  \brief 接收所有的单播帧 */
#define AMHW_EMAC_RFC_BCAST_EN        0x00000002  /**<  \brief 接收所有广播帧 */
#define AMHW_EMAC_RFC_MCAST_EN        0x00000004  /**<  \brief 使能接收多播帧 */
#define AMHW_EMAC_RFC_UCAST_HASH_EN   0x00000008  /**<  \brief 接受通过不完全hash过滤器的单播帧 */
#define AMHW_EMAC_RFC_MCAST_HASH_EN   0x00000010  /**<  \brief 接受通过不完全hash过滤器的多播帧 */
#define AMHW_EMAC_RFC_PERFECT_EN      0x00000020  /**<  \brief 接收目标地址与站地址相同的帧 */
#define AMHW_EMAC_RFC_MAGP_WOL_EN     0x00001000  /**<  \brief 魔法包过滤器中断使能 */
#define AMHW_EMAC_RFC_PFILT_WOL_EN    0x00002000  /**<  \brief 完全地址匹配过滤器与不完全hash过滤器的结果匹配中断使能 */
/** @} */

/**
 * \name 接收过滤器LAN上唤醒状态寄存器位定义
 * @{
 */
#define AMHW_EMAC_WOL_UCAST           0x00000001  /**<  \brief 单播帧引起WoL */
#define AMHW_EMAC_WOL_BCAST           0x00000002  /**<  \brief 广播帧引起WoL */
#define AMHW_EMAC_WOL_MCAST           0x00000004  /**<  \brief 多播帧引起WoL */
#define AMHW_EMAC_WOL_UCAST_HASH      0x00000008  /**<  \brief 一个通过不完全hash过滤器的单播帧引起WoL */
#define AMHW_EMAC_WOL_MCAST_HASH      0x00000010  /**<  \brief 一个通过不完全hash过滤器的多播帧引起WoL */
#define AMHW_EMAC_WOL_PERFECT         0x00000020  /**<  \brief 完全地址匹配过滤器引起WoL */
#define AMHW_EMAC_WOL_RX_FILTER       0x00000080  /**<  \brief 接收过滤器引起WoL */
#define AMHW_EMAC_WOL_MAG_PACKET      0x00000100  /**<  \brief 魔法包过滤器引起WoL */
#define AMHW_EMAC_WOL_BITMASK		  0x01BF      /**<  \brief 接收过滤器Wol状态寄存器位掩码 */
/** @} */

/* 模块控制寄存器 */
/**
 * \name 中断状态使能、清零、置位位定义
 * \anchor grp_amhw_enet_int
 * @{
 */
#define AMHW_EMAC_INT_RX_OVERRUN      0x00000001  /**<  \brief 接收队列溢出错误时中断置位 */
#define AMHW_EMAC_INT_RX_ERR          0x00000002  /**<  \brief 接收错误 */
#define AMHW_EMAC_INT_RX_FIN          0x00000004  /**<  \brief 所有接收描述符已处理完 */
#define AMHW_EMAC_INT_RX_DONE         0x00000008  /**<  \brief 接收完成 */
#define AMHW_EMAC_INT_TX_UNDERRUN     0x00000010  /**<  \brief 发送队列溢出错误时中断置位 */
#define AMHW_EMAC_INT_TX_ERR          0x00000020  /**<  \brief 发送错误 */
#define AMHW_EMAC_INT_TX_FIN          0x00000040  /**<  \brief 所有发送描述符已处理完 */
#define AMHW_EMAC_INT_TX_DONE         0x00000080  /**<  \brief 发送完成 */
#define AMHW_EMAC_INT_SOFT_INT        0x00001000  /**<  \brief 软件触发中断 */
#define AMHW_EMAC_INT_WAKEUP          0x00002000  /**<  \brief 唤醒事件中断 */
/** @} */

/**
 * \name 掉电寄存器定义
 * @{
 */
#define AMHW_EMAC_PD_POWER_DOWN       0x80000000  /**<  \brief 阻塞除PD寄存器外的所有AHB访问 */
/** @} */


/* 描述符和状态格式 */
/**
 * \name 接收描述符控制字定义
 * @{
 */
#define AMHW_EMAC_RCTRL_SIZE(n)       (n&0x7FF)  	/**<  \brief 数据缓冲区大小 */
#define AMHW_EMAC_RCTRL_INT           0x80000000  	/**<  \brief 产生接收完成中断 */
/** @} */

/**
 * \name 接收状态Hash CRC字定义
 * @{
 */
#define EMAC_RHASH_SA            0x000001FF  	/**<  \brief 从源地址中计算而得的Hash CRC */
#define EMAC_RHASH_DA            0x001FF000  	/**<  \brief 从目的地址中计算而得的Hash CRC */
/** @} */

/**
 * \name 接收状态信息字定义
 * \anchor grp_amhw_enet_rinfo
 * @{
 */
#define AMHW_EMAC_RINFO_SIZE          0x000007FF  /**<  \brief 实际数据的字节数 */
#define AMHW_EMAC_RINFO_CTRL_FRAME    0x00040000  /**<  \brief 控制帧 */
#define AMHW_EMAC_RINFO_VLAN          0x00080000  /**<  \brief VLAN帧 */
#define AMHW_EMAC_RINFO_FAIL_FILT     0x00100000  /**<  \brief 接收过滤区域 */
#define AMHW_EMAC_RINFO_MCAST         0x00200000  /**<  \brief 多播帧 */
#define AMHW_EMAC_RINFO_BCAST         0x00400000  /**<  \brief 广播帧 */
#define AMHW_EMAC_RINFO_CRC_ERR       0x00800000  /**<  \brief 接收的帧有CRC错误 */
#define AMHW_EMAC_RINFO_SYM_ERR       0x01000000  /**<  \brief PHY接口报告有一个错误 */
#define AMHW_EMAC_RINFO_LEN_ERR       0x02000000  /**<  \brief 帧长度错误 */
#define AMHW_EMAC_RINFO_RANGE_ERR     0x04000000  /**<  \brief 包最大长度限制 */
#define AMHW_EMAC_RINFO_ALIGN_ERR     0x08000000  /**<  \brief 对齐错误 */
#define AMHW_EMAC_RINFO_OVERRUN       0x10000000  /**<  \brief 接收溢出 */
#define AMHW_EMAC_RINFO_NO_DESCR      0x20000000  /**<  \brief 没有新的接收描述符可用 */
#define AMHW_EMAC_RINFO_LAST_FLAG     0x40000000  /**<  \brief 帧的最后一个片段 */
#define AMHW_EMAC_RINFO_ERR           0x80000000  /**<  \brief 帧接收过程中出现错误 */

/**  \brief 帧接收错误掩码  */
#define AMHW_EMAC_RINFO_ERR_MASK     (AMHW_EMAC_RINFO_FAIL_FILT |\
                                      AMHW_EMAC_RINFO_CRC_ERR   |\
                                      AMHW_EMAC_RINFO_SYM_ERR   |\
                                      AMHW_EMAC_RINFO_LEN_ERR   |\
                                      AMHW_EMAC_RINFO_ALIGN_ERR |\
                                      AMHW_EMAC_RINFO_OVERRUN)
/** @} */

/**
 * \name 发送描述符的控制字位定义
 * @{
 */
#define AMHW_EMAC_TCTRL_SIZE          0x000007FF  /**<  \brief 数据缓冲区大小  */
#define AMHW_EMAC_TCTRL_OVERRIDE      0x04000000  /**<  \brief 忽略每一帧 */
#define AMHW_EMAC_TCTRL_HUGE          0x08000000  /**<  \brief 使能巨帧 */
#define AMHW_EMAC_TCTRL_PAD           0x10000000  /**<  \brief 将短帧填充到64字节 */
#define AMHW_EMAC_TCTRL_CRC           0x20000000  /**<  \brief 将一个硬件CRC添加到帧内 */
#define AMHW_EMAC_TCTRL_LAST          0x40000000  /**<  \brief 发送帧中最后一个片段的描述符 */
#define AMHW_EMAC_TCTRL_INT           0x80000000  /**<  \brief 产生发送完成中断 */
/** @} */

/**
 * \name 发送状态的信息字位定义
 * @{
 */
#define AMHW_EMAC_TINFO_COL_CNT       0x01E00000  /**<  \brief 冲突次数 */
#define AMHW_EMAC_TINFO_DEFER         0x02000000  /**<  \brief 由于媒体被占据而遭延迟 */
#define AMHW_EMAC_TINFO_EXCESS_DEF    0x04000000  /**<  \brief 延迟超出了最大的延迟限制并被中止 */
#define AMHW_EMAC_TINFO_EXCESS_COL    0x08000000  /**<  \brief 包超出了最大的冲突限制并被中止 */
#define AMHW_EMAC_TINFO_LATE_COL      0x10000000  /**<  \brief 冲突窗口超出范围，导致发送包中止 */
#define AMHW_EMAC_TINFO_UNDERRUN      0x20000000  /**<  \brief 没产生发送数据而出现发送下溢 */
#define AMHW_EMAC_TINFO_NO_DESCR      0x40000000  /**<  \brief 无可用的描述符 */
#define AMHW_EMAC_TINFO_ERR           0x80000000  /**<  \brief 发送过程中出现的错误 */
/** @} */


/**
 * @brief 发送数据缓存结构体
 */
typedef struct amhw_mac_packet_type {
	uint32_t  data_length;      /**<  \brief 数据长度  */
	uint32_t *p_data_buf;		/**<  \brief 数据指针 */
} amhw_mac_packet_type_t;



/**
 * @brief PHY模式/地址
 */
typedef struct amhw_phy_addr_mode {
    uint32_t            mode;          /**<  \brief
                                            - AMHW_EMAC_MODE_AUTO
                                            - AMHW_EMAC_MODE_10M_FULL
                                            - AMHW_EMAC_MODE_10M_HALF
                                            - AMHW_EMAC_MODE_100M_FULL
                                            - AMHW_EMAC_MODE_100M_HALF
                                            */
    uint32_t            phy_addr;    /**<  \brief PHY地址 */
} amhw_phy_addr_mode_t;


/** \brief PHY初始化函数指针 */
typedef int  (*pfn_amhw_phy_init) (amhw_enet_t             *p_hw_enet,
                                   amhw_phy_addr_mode_t    *p_phy_addr_mode);

/**
 * @brief enet配置结构体
 */
typedef struct amhw_enet_config {
	uint8_t               *p_mac_addr;    /**<  \brief MAC地址 */
	amhw_phy_addr_mode_t   phy_addr_mode; /**<  \brief PHY地址 */
	pfn_amhw_phy_init      pfn_phy_init;  /**<  \brief PHY初始化函数指针 */
} amhw_enet_config_t;




/**
 * \brief  设置mac1值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_mac1_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->mac1 = regvalue;
}

/**
 * \brief  设置mac1位值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_mac1_val_set_bit (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->mac1 |= regvalue;
}

/**
 * \brief  设置mac2值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_mac2_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->mac2 = regvalue;
}
/**
 * \brief  设置mac2位
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_mac2_val_set_bit (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->mac2 |= regvalue;
}

/**
 * \brief  设置command值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_command_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->command = regvalue;
}

/**
 * \brief  设置command位值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_command_val_set_bit (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->command |= regvalue;
}


/**
 * \brief  设置supp值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_supp_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->supp = regvalue;
}


/**
 * \brief  设置ipgt值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_ipgt_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->ipgt = regvalue;
}


/**
 * \brief  设置rx_descriptor值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_rx_descriptor_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->rx_descriptor = regvalue;
}

/**
 * \brief  设置rx_status值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_rx_status_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->rx_status = regvalue;
}

/**
 * \brief  设置rx_descriptor_number值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_rx_descriptor_number_val_set (amhw_enet_t *p_hw_enet,
                                             uint32_t     regvalue)
{   
	p_hw_enet->rx_descriptor_number = regvalue;
}

/**
 * \brief  设置rx_consume_index值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_rx_consume_index_val_set (amhw_enet_t *p_hw_enet,
                                         uint32_t     regvalue)
{   
	p_hw_enet->rx_consume_index = regvalue;
}


/**
 * \brief  设置tx_descriptor值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_tx_descriptor_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->tx_descriptor = regvalue;
}

/**
 * \brief  设置tx_status值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_tx_status_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->tx_status = regvalue;
}

/**
 * \brief  设置tx_descriptor_number值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_tx_descriptor_number_val_set (amhw_enet_t *p_hw_enet,
                                             uint32_t     regvalue)
{   
	p_hw_enet->tx_descriptor_number = regvalue;
}

/**
 * \brief  设置tx_produce_index值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline 
void amhw_enet_tx_produce_index_val_set (amhw_enet_t *p_hw_enet,
                                         uint32_t     regvalue)
{   
	p_hw_enet->tx_produce_index = regvalue;
}

/**
 * \brief  获取tx_produce_index值
 *
 * \param[in] p_hw_enet ：外设指针
 *
 *  return   当前寄存器值
 */
am_static_inline
uint32_t amhw_enet_tx_produce_index_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->tx_produce_index;
}


/**
 * \brief  设置madr值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_madr_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->madr = regvalue;
}

/**
 * \brief  设置mwtd值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_mwtd_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->mwtd = regvalue;
}

/**
 * \brief  获取mind值
 *
 * \param[in] p_hw_enet ：外设指针
 *
 *  return   当前寄存器值
 */
am_static_inline
uint32_t amhw_enet_mind_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->mind;
}

/**
 * \brief  设置mcmd值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_mcmd_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->mcmd = regvalue;
}

/**
 * \brief  获取mrdd值
 *
 * \param[in] p_hw_enet ：外设指针
 *
 * return   当前寄存器值
 */
am_static_inline
uint32_t amhw_enet_mrdd_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->mrdd;
}

/**
 * \brief  设置sa0值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_sa0_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->sa0 = regvalue;
}

/**
 * \brief  设置sa1值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_sa1_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->sa1 = regvalue;
}

/**
 * \brief  设置sa2值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_sa2_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->sa2 = regvalue;
}

/**
 * \brief  设置maxf值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_maxf_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->maxf = regvalue;
}

/**
 * \brief  设置mcfg值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_mcfg_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->mcfg = regvalue;
}

/**
 * \brief  设置mcfg值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_mcfg_val_clr (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->mcfg &= regvalue;
}

/**
 * \brief  设置clrt值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_clrt_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->clrt = regvalue;
}

/**
 * \brief  设置ipgr值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_ipgr_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->ipgr = regvalue;
}

/**
 * \brief  设置rx_filter_ctrl值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_rx_filter_ctrl_val_set (amhw_enet_t *p_hw_enet,
                                       uint32_t     regvalue)
{
	p_hw_enet->rx_filter_ctrl = regvalue;
}

/**
 * \brief  设置int_enable值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_int_enable_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->int_enable = regvalue;
}

/**
 * \brief  设置int_enable值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_int_enable_val_or (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->int_enable |= regvalue;
}

/**
 * \brief  设置int_enable值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_int_enable_val_clr (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->int_enable &= regvalue;
}

/**
 * \brief  设置int_enable值
 *
 * \param[in] p_hw_enet ：外设指针
 *
 *  return   当前寄存器值
 */
am_static_inline
uint32_t amhw_enet_int_enable_val_get (amhw_enet_t *p_hw_enet)
{
	return  p_hw_enet->int_enable;
}


/**
 * \brief  设置int_clear值
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] regvalue  ：寄存器值
 *
 * \return    无
 */
am_static_inline
void amhw_enet_int_clear_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->int_clear = regvalue;
}

/**
 * \brief  获取rx_consume_index值
 *
 * \param[in] p_hw_enet ：外设指针
 *
 * return   当前寄存器值
 */
am_static_inline
uint32_t amhw_enet_rx_consume_index_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->rx_consume_index;
}


/**
 * \brief  获取int_status值
 *
 * \param[in] p_hw_enet ：外设指针
 *
 * return   当前寄存器值
 */
am_static_inline
uint32_t amhw_enet_int_status_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->int_status;
}

/**
 * \brief  获取tx_consume_index值
 *
 * \param[in] p_hw_enet ：外设指针
 *
 * return   当前寄存器值
 */
am_static_inline
uint32_t amhw_enet_tx_consume_index_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->tx_consume_index;
}




/**
 * \brief 初始化接收描述符和接收状态数组
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] p_config  ：配置参数指针
 *
 * \return     无
 */
void amhw_enet_rx_descr_init (amhw_enet_t        *p_hw_enet);

/**
 * \brief 初始化发送描述符和发送状态数组
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] p_config  ：配置参数指针
 *
 * \return     无
 */
void amhw_enet_tx_descr_init (amhw_enet_t        *p_hw_enet);

/**
 * \brief 将value写到PHY寄存器中
 *
 * \param[in]  p_hw_enet       ：外设指针
 * \param[in]  p_phy_addr_mode ：phy模式地址指针
 * \param[in]  phy_reg   ：寄存器地址 
 * \param[in]  value     ：数值
 *
 * \retval    -AM_EINVAL ：出错
 * \retval     AM_OK     ：成功
 */
int amhw_enet_phy_write (amhw_enet_t             *p_hw_enet,
                         amhw_phy_addr_mode_t    *p_phy_addr_mode,
                         uint32_t                 phy_reg,
                         uint16_t                 value);

/**
 * \brief 读PHY寄存器
 *
 * \param[in]  p_hw_enet       ：外设指针
 * \param[in]  p_phy_addr_mode ：phy模式地址指针
 * \param[in]  phy_reg         ：寄存器地址
 *
 * \retval    -AM_EINVAL ：出错
 * \retval     寄存器值
 */
int32_t amhw_enet_phy_read (amhw_enet_t             *p_hw_enet,
                            amhw_phy_addr_mode_t    *p_phy_addr_mode,
                            uint32_t                 phy_reg);

/**
 * \brief 设置MAC地址
 *
 * \param[in]  p_hw_enet ：外设指针
 * \param[in]  mac_addr  ：MAC地址 
 *
 * \return     无
 */
void amhw_enet_mac_addr_set (amhw_enet_t *p_hw_enet, uint8_t mac_addr[]);

/**
 * \brief 初始化以太网模块
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] p_config  ：配置参数指针
 *
 * \retval    -AM_EINVAL ：出错
 * \retval     AM_OK     ：成功
 */
int amhw_enet_init (amhw_enet_t *p_hw_enet, amhw_enet_config_t *p_config);

/**
 * \brief 写数据到发送缓存
 *
 * \param[in] p_hw_enet     ：外设指针
 * \param[in] p_data_struct ：需要写的数据
 *
 * \retval    无
 */
void amhw_enet_packet_buffer_write (amhw_enet_t            *p_hw_enet,
                                    amhw_mac_packet_type_t *p_data_struct);

/**
 * \brief 读数据到接收缓存
 *
 * \param[in] p_hw_enet     ：外设指针
 * \param[in] p_data_struct ：需要写的数据
 *
 * \retval    无
 */
void amhw_enet_packet_buffer_read (amhw_enet_t            *p_hw_enet,
                                   amhw_mac_packet_type_t *p_data_struct);

/**
 * \brief 使能/失能ENET中断
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] int_type  :中断类型，参见
 *                       \ref grp_amhw_enet_int
 * \param[in] state    :使能TRUE/失能FALSE
 *
 * \retval     无
 */
void amhw_enet_int_cmd(amhw_enet_t *p_hw_enet, uint32_t int_type, bool_t state);

/**
 * \brief 获取中断状态
 * \param[in] p_hw_enet ：外设指针
 * \param[in] int_type  : 中断类型，参见
 *                       \ref grp_amhw_enet_int
 *
 * \retval     TRUE  ：有效
 * \retval     FALSE ：无效
 */
bool_t amhw_enet_int_status_get (amhw_enet_t *p_hw_enet, uint32_t int_type);

/**
 * \brief 检测产生索引和消费索引是否相等
 *
 * \param[in] p_hw_enet ：外设指针
 *
 * \retval     TRUE  ：相等
 * \retval     FALSE ：不等
 */
bool_t amhw_enet_receive_index_check(amhw_enet_t *p_hw_enet);

/**
 * \brief 检测发产生索引和消费索引是否相等
 *
 * \param[in] p_hw_enet ：外设指针
 *
 * \retval     TRUE  ：相等
 * \retval     FALSE ：不等
 */
bool_t amhw_enet_transmit_index_check (amhw_enet_t *p_hw_enet);

/**
 * \brief 获取当前接收信息状态
 *
 * \param[in] p_hw_enet             ：外设指针
 * \param[in] p_config              ：配置参数指针
 * \param[in] amhw_enet_rx_stat_type：接收信息类型，参见
 *                                   \ref grp_amhw_enet_rinfo
 *
 * \retval     TRUE      ：有效
 * \retval     FALSE     ：无效
 */
bool_t amhw_enet_receive_data_status_check (amhw_enet_t        *p_hw_enet,
                                            amhw_enet_config_t *p_config,
                                            uint32_t            amhw_enet_rx_stat_type);

/**
 * \brief 获取当前接收数据的大小
 *
 * \param[in] p_hw_enet ：外设指针
 * \param[in] p_config  ：配置参数指针
 *
 * \return    接收数据长度
 */
uint32_t amhw_enet_receive_data_size_get (amhw_enet_t        *p_hw_enet,
                                          amhw_enet_config_t *p_config);

/**
 * \brief 更新接收消费索引
 *
 * \param[in] p_hw_enet ：外设指针
 *
 * \return    无
 */
void amhw_enet_rx_consume_index_update(amhw_enet_t *p_hw_enet);

/**
 * \brief 更新发送产生索引
 *
 * \param[in] p_hw_enet ：外设指针
 *
 * \return    无
 */
void amhw_enet_tx_produce_index_update (amhw_enet_t *p_hw_enet);



/**
 * @} amhw_if_enet
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ENET_H */

/* end of file */
    

