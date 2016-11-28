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
 * \brief  phy硬件操作接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-11-12  snk, first implementation.
 * \endinternal
 */

#ifndef __AM_PHYLAN_KSZ8041_H
#define __AM_PHYLAN_KSZ8041_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_phylan_ksz8041.h"

/**
 * \addtogroup am_if_phylan_ksz8041
 * \copydoc am_phylan_ksz8041.h
 * @{
 */

/**
 * \name KSZ8041 宏定义
 * @{
 */
/**  \brief 复位超时 */
#define AM_KSZ8041_PHY_RESP_TOUT       0x100000UL
#define AM_KSZ8041_PHY_REG_BMCR        0x00        /**<  \brief 基本模式控制寄存器 */
#define AM_KSZ8041_PHY_REG_BMSR        0x01        /**<  \brief 基本模式状态寄存器 */
#define AM_KSZ8041_PHY_REG_IDR1        0x02        /**<  \brief PHY身份寄存器1 */
#define AM_KSZ8041_PHY_REG_IDR2        0x03        /**<  \brief PHY身份寄存器2 */

#define AM_KSZ8041_PHY_BMCR_RESET                (1<<15)     /**<  \brief 复位0x8000 */
#define AM_KSZ8041_PHY_BMCR_SPEED_SEL            (1<<13)     /**<  \brief 速度选择 */
#define AM_KSZ8041_PHY_BMCR_AN                   (1<<12)     /**<  \brief 自动适配0x1000 */
#define AM_KSZ8041_PHY_BMCR_POWERDOWN            (1<<11)     /**<  \brief 掉电模式0x800 */
#define AM_KSZ8041_PHY_BMCR_DUPLEX               (1<<8)      /**<  \brief 双工模式 */

#define AM_KSZ8041_PHY_BMSR_AUTO_DONE            (1<<5)      /**<  \brief 自动适配完成 */
#define AM_KSZ8041_PHY_BMSR_LINK_ESTABLISHED     (1<<2)      /**<  \brief 连接状态 */

#define AM_KSZ8041_DEF_ADR                       0x0500       /**<  \brief  默认ＰＨＹ地址　*/
#define AM_KSZ8041_PHY_SR_FULL_DUP               ((1<<14)|(1<<12))/**<  \brief 全速状态 */
/** @} */




/**
 * \name 函数调用宏定义
 * @{
 */

/**  \brief 基本模式控制寄存器 ,值为0x00 */
#define AMHW_EMAC_PHY_REG_BMCR           AM_KSZ8041_PHY_REG_BMCR
/**  \brief 基本模式状态寄存器 ,值为0x01 */
#define AMHW_EMAC_PHY_REG_BMSR           AM_KSZ8041_PHY_REG_BMSR
/**  \brief PHY身份寄存器1 ,值为0x02 */
#define AMHW_EMAC_PHY_REG_IDR1           AM_KSZ8041_PHY_REG_IDR1
/**  \brief PHY身份寄存器2 ,值为 0x03 */
#define AMHW_EMAC_PHY_REG_IDR2           AM_KSZ8041_PHY_REG_IDR2

/**  \brief 复位 ,值为(1<<15) */
#define AMHW_EMAC_PHY_BMCR_RESET         AM_KSZ8041_PHY_BMCR_RESET
/**  \brief 低功耗 ,值为(1<<11) */
#define AMHW_EMAC_PHY_BMCR_POWERDOWN     AM_KSZ8041_PHY_BMCR_POWERDOWN
/**  \brief 速度选择 ,值为1<<13 */
#define AMHW_EMAC_PHY_BMCR_SPEED_SEL     AM_KSZ8041_PHY_BMCR_SPEED_SEL
/**  \brief 双工模式 ,值为1<<8 */
#define AMHW_EMAC_PHY_BMCR_DUPLEX        AM_KSZ8041_PHY_BMCR_DUPLEX
/**  \brief 自动适配 ,值为1<<12 */
#define AMHW_EMAC_PHY_BMCR_AN            AM_KSZ8041_PHY_BMCR_AN

/**  \brief 自动适配完成  ,值为(1<<5)*/
#define AMHW_EMAC_PHY_BMSR_AUTO_DONE     AM_KSZ8041_PHY_BMSR_AUTO_DONE

/**  \brief PHY身份密钥　*/
#define AMHW_EMAC_PHY_ID                 ((0x22 << 16) | (0x1513  & 0xFFF0))

/**  \brief 复位超时 */
#define AMHW_EMAC_PHY_RESP_TOUT          AM_KSZ8041_PHY_RESP_TOUT
/**  \brief 0x0500默认PHY地址　*/
#define AMHW_EMAC_PHY_DEF_ADR            0x0500  

/** @} */



/**
 * \brief 复位PHY
 *
 * \param[in]  p_hw_enet       ：外设指针
 * \param[in]  p_phy_addr_mode ：phy模式地址指针
 *
 * \retval    -AM_EINVAL ：错误
 * \retval     AM_OK     ：成功
 */
int am_phyksz8041_reset (amhw_enet_t             *p_hw_enet,
                         amhw_phy_addr_mode_t    *p_phy_addr_mode);


/**
 * \brief 更新PHY状态
 *
 * \param[in]  p_hw_enet       ：外设指针
 * \param[in]  p_phy_addr_mode ：phy模式地址指针
 *
 * \retval    -AM_EINVAL ：错误
 * \retval     AM_OK     ：成功
 */
int am_phyksz8041_status_update (amhw_enet_t             *p_hw_enet,
                                 amhw_phy_addr_mode_t    *p_phy_addr_mode);

/**
 * \brief 设置PHY的工作模式
 *
 * \param[in]  p_hw_enet       ：外设指针
 * \param[in]  p_phy_addr_mode ：phy模式地址指针
 *
 * \retval    -AM_EINVAL ：错误
 * \retval     AM_OK     ：完成
 */
int am_phyksz8041_mode_set (amhw_enet_t             *p_hw_enet,
                            amhw_phy_addr_mode_t    *p_phy_addr_mode);


/**
 * \brief 初始化PHY
 *
 * \param[in]  p_hw_enet       ：外设指针
 * \param[in]  p_phy_addr_mode ：phy模式地址指针
 *
 * \retval    -AM_EINVAL ：错误
 * \retval     AM_OK     ：成功
 */
int am_phyksz8041_init (amhw_enet_t             *p_hw_enet,
                        amhw_phy_addr_mode_t    *p_phy_addr_mode);

/**
 * @} am_phylan_ksz8041
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_PHYLAN_KSZ8041_H */

/* end of file */


