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
 * \brief  phyӲ�������ӿ�
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
 * \name KSZ8041 �궨��
 * @{
 */
/**  \brief ��λ��ʱ */
#define AM_KSZ8041_PHY_RESP_TOUT       0x100000UL
#define AM_KSZ8041_PHY_REG_BMCR        0x00        /**<  \brief ����ģʽ���ƼĴ��� */
#define AM_KSZ8041_PHY_REG_BMSR        0x01        /**<  \brief ����ģʽ״̬�Ĵ��� */
#define AM_KSZ8041_PHY_REG_IDR1        0x02        /**<  \brief PHY��ݼĴ���1 */
#define AM_KSZ8041_PHY_REG_IDR2        0x03        /**<  \brief PHY��ݼĴ���2 */

#define AM_KSZ8041_PHY_BMCR_RESET                (1<<15)     /**<  \brief ��λ0x8000 */
#define AM_KSZ8041_PHY_BMCR_SPEED_SEL            (1<<13)     /**<  \brief �ٶ�ѡ�� */
#define AM_KSZ8041_PHY_BMCR_AN                   (1<<12)     /**<  \brief �Զ�����0x1000 */
#define AM_KSZ8041_PHY_BMCR_POWERDOWN            (1<<11)     /**<  \brief ����ģʽ0x800 */
#define AM_KSZ8041_PHY_BMCR_DUPLEX               (1<<8)      /**<  \brief ˫��ģʽ */

#define AM_KSZ8041_PHY_BMSR_AUTO_DONE            (1<<5)      /**<  \brief �Զ�������� */
#define AM_KSZ8041_PHY_BMSR_LINK_ESTABLISHED     (1<<2)      /**<  \brief ����״̬ */

#define AM_KSZ8041_DEF_ADR                       0x0500       /**<  \brief  Ĭ�ϣУȣٵ�ַ��*/
#define AM_KSZ8041_PHY_SR_FULL_DUP               ((1<<14)|(1<<12))/**<  \brief ȫ��״̬ */
/** @} */




/**
 * \name �������ú궨��
 * @{
 */

/**  \brief ����ģʽ���ƼĴ��� ,ֵΪ0x00 */
#define AMHW_EMAC_PHY_REG_BMCR           AM_KSZ8041_PHY_REG_BMCR
/**  \brief ����ģʽ״̬�Ĵ��� ,ֵΪ0x01 */
#define AMHW_EMAC_PHY_REG_BMSR           AM_KSZ8041_PHY_REG_BMSR
/**  \brief PHY��ݼĴ���1 ,ֵΪ0x02 */
#define AMHW_EMAC_PHY_REG_IDR1           AM_KSZ8041_PHY_REG_IDR1
/**  \brief PHY��ݼĴ���2 ,ֵΪ 0x03 */
#define AMHW_EMAC_PHY_REG_IDR2           AM_KSZ8041_PHY_REG_IDR2

/**  \brief ��λ ,ֵΪ(1<<15) */
#define AMHW_EMAC_PHY_BMCR_RESET         AM_KSZ8041_PHY_BMCR_RESET
/**  \brief �͹��� ,ֵΪ(1<<11) */
#define AMHW_EMAC_PHY_BMCR_POWERDOWN     AM_KSZ8041_PHY_BMCR_POWERDOWN
/**  \brief �ٶ�ѡ�� ,ֵΪ1<<13 */
#define AMHW_EMAC_PHY_BMCR_SPEED_SEL     AM_KSZ8041_PHY_BMCR_SPEED_SEL
/**  \brief ˫��ģʽ ,ֵΪ1<<8 */
#define AMHW_EMAC_PHY_BMCR_DUPLEX        AM_KSZ8041_PHY_BMCR_DUPLEX
/**  \brief �Զ����� ,ֵΪ1<<12 */
#define AMHW_EMAC_PHY_BMCR_AN            AM_KSZ8041_PHY_BMCR_AN

/**  \brief �Զ��������  ,ֵΪ(1<<5)*/
#define AMHW_EMAC_PHY_BMSR_AUTO_DONE     AM_KSZ8041_PHY_BMSR_AUTO_DONE

/**  \brief PHY�����Կ��*/
#define AMHW_EMAC_PHY_ID                 ((0x22 << 16) | (0x1513  & 0xFFF0))

/**  \brief ��λ��ʱ */
#define AMHW_EMAC_PHY_RESP_TOUT          AM_KSZ8041_PHY_RESP_TOUT
/**  \brief 0x0500Ĭ��PHY��ַ��*/
#define AMHW_EMAC_PHY_DEF_ADR            0x0500  

/** @} */



/**
 * \brief ��λPHY
 *
 * \param[in]  p_hw_enet       ������ָ��
 * \param[in]  p_phy_addr_mode ��phyģʽ��ַָ��
 *
 * \retval    -AM_EINVAL ������
 * \retval     AM_OK     ���ɹ�
 */
int am_phyksz8041_reset (amhw_enet_t             *p_hw_enet,
                         amhw_phy_addr_mode_t    *p_phy_addr_mode);


/**
 * \brief ����PHY״̬
 *
 * \param[in]  p_hw_enet       ������ָ��
 * \param[in]  p_phy_addr_mode ��phyģʽ��ַָ��
 *
 * \retval    -AM_EINVAL ������
 * \retval     AM_OK     ���ɹ�
 */
int am_phyksz8041_status_update (amhw_enet_t             *p_hw_enet,
                                 amhw_phy_addr_mode_t    *p_phy_addr_mode);

/**
 * \brief ����PHY�Ĺ���ģʽ
 *
 * \param[in]  p_hw_enet       ������ָ��
 * \param[in]  p_phy_addr_mode ��phyģʽ��ַָ��
 *
 * \retval    -AM_EINVAL ������
 * \retval     AM_OK     �����
 */
int am_phyksz8041_mode_set (amhw_enet_t             *p_hw_enet,
                            amhw_phy_addr_mode_t    *p_phy_addr_mode);


/**
 * \brief ��ʼ��PHY
 *
 * \param[in]  p_hw_enet       ������ָ��
 * \param[in]  p_phy_addr_mode ��phyģʽ��ַָ��
 *
 * \retval    -AM_EINVAL ������
 * \retval     AM_OK     ���ɹ�
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


