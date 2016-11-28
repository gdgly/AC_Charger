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
 * \brief  ENETӲ�������ӿ�
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
 * \brief ENET�Ĵ�����Ľṹ��
 */
typedef struct amhw_enet {
    __IO uint32_t mac1;    				/**< \brief MAC���üĴ���1  */                
    __IO uint32_t mac2;    				/**< \brief MAC���üĴ���2  */
    __IO uint32_t ipgt;    				/**< \brief �������������ڲ�������Ĵ���  */
    __IO uint32_t ipgr;					/**< \brief ���������������ڲ�������Ĵ���  */
    __IO uint32_t clrt;					/**< \brief ��ͻ����/���ԼĴ���  */
    __IO uint32_t maxf;					/**< \brief ���֡�Ĵ���  */
    __IO uint32_t supp;					/**< \brief PHY֧�ּĴ���  */
    __IO uint32_t test;					/**< \brief ���ԼĴ���  */
    __IO uint32_t mcfg;					/**< \brief MII Mgmt���üĴ���  */
    __IO uint32_t mcmd;					/**< \brief MII Mgmt����Ĵ���  */
    __IO uint32_t madr;					/**< \brief MII Mgmt��ַ�Ĵ���  */
    __O  uint32_t mwtd;					/**< \brief MII Mgmtд���ݼĴ���  */
    __I  uint32_t mrdd;					/**< \brief MII Mgmt�����ݼĴ���  */
    __I  uint32_t mind;					/**< \brief MII Mgmtָʾ�Ĵ���  */
         uint32_t reserverd0[2];		/**< \brief ����  */
    __IO uint32_t sa0;					/**< \brief վ��ַ0�Ĵ���  */
    __IO uint32_t sa1;					/**< \brief վ��ַ1�Ĵ���  */
    __IO uint32_t sa2;					/**< \brief վ��ַ2�Ĵ���  */
         uint32_t reserved1[45];		/**< \brief ����  */
    __IO uint32_t command;   			/**< \brief ����Ĵ���  */             
    __I  uint32_t status;				/**< \brief ״̬�Ĵ���  */
    __IO uint32_t rx_descriptor;		/**< \brief ������������ַ�Ĵ���  */
    __IO uint32_t rx_status;			/**< \brief ����״̬��ַ�Ĵ���  */
    __IO uint32_t rx_descriptor_number;	/**< \brief ������������Ŀ�Ĵ���  */
    __I  uint32_t rx_produce_index;		/**< \brief ���ղ��������Ĵ���  */
    __IO uint32_t rx_consume_index;		/**< \brief �������������Ĵ���  */
    __IO uint32_t tx_descriptor;		/**< \brief ������������ַ�Ĵ��� */
    __IO uint32_t tx_status;			/**< \brief ����״̬��ַ�Ĵ���  */
    __IO uint32_t tx_descriptor_number; /**< \brief ������������Ŀ�Ĵ��� */
    __IO uint32_t tx_produce_index;		/**< \brief ���Ͳ��������Ĵ���  */
    __I  uint32_t tx_consume_index;		/**< \brief �������������Ĵ���  */
         uint32_t reserved2[10];		/**< \brief ����  */
    __I  uint32_t tsv0;					/**< \brief ����״̬����0�Ĵ���  */
    __I  uint32_t tsv1;					/**< \brief ����״̬����1�Ĵ���  */
    __I  uint32_t rsv;					/**< \brief ����״̬����2�Ĵ���  */
         uint32_t reserved3[3];			/**< \brief ����  */
    __IO uint32_t flow_control_counter;	/**< \brief �����Ƽ������Ĵ���  */
    __I  uint32_t flow_control_status;	/**< \brief ������״̬�Ĵ���  */
         uint32_t reserved4[34];		/**< \brief ����  */
    __IO uint32_t rx_filter_ctrl;  		/**< \brief ���չ��˼Ĵ���  */
    __IO uint32_t rx_filter_wol_status;	/**< \brief ���չ�����WoL״̬�Ĵ���  */
    __IO uint32_t rx_filter_wol_clear;	/**< \brief ���չ�����WoL����Ĵ���  */
         uint32_t reserved5;			/**< \brief ����  */
    __IO uint32_t hash_filter_l;		/**< \brief Hash��������LSBs�Ĵ���  */
    __IO uint32_t hash_filter_h;		/**< \brief Hash��������MSBs�Ĵ���  */
         uint32_t reserved6[882];		/**< \brief ����  */
    __I  uint32_t int_status;  			/**< \brief �ж�״̬�Ĵ���  */
    __IO uint32_t int_enable;			/**< \brief �ж�ʹ�ܼĴ���  */
    __O  uint32_t int_clear;			/**< \brief �ж�����Ĵ���  */
    __O  uint32_t int_set;				/**< \brief �ж���λ�Ĵ���  */
         uint32_t reserved7;			/**< \brief ����  */
    __IO uint32_t power_down;			/**< \brief ����Ĵ���  */
         uint32_t reserved8;			/**< \brief ����  */
    __IO uint32_t module_id;			/**< \brief ģ����ƼĴ���  */
} amhw_enet_t;


/**
 * \name EMAC PHY״̬���Ͷ���
 * \anchor grp_amhw_enet_phy_state
 * @{
 */
#define AMHW_EMAC_PHY_STAT_LINK			(0)		/**<  \brief Link״̬ */
#define AMHW_EMAC_PHY_STAT_SPEED		(1)		/**<  \brief Speed״̬ */
#define AMHW_EMAC_PHY_STAT_DUP			(2)		/**<  \brief Duplex״̬ */
/** @} */


/**
 * \name ����16k����̫���ڴ滺��
 * @{
 */
#define AMHW_EMAC_NUM_RX_FRAG         4           /**<  \brief ����֡ 4*1536= 6.0kB */
#define AMHW_EMAC_NUM_TX_FRAG         4           /**<  \brief ����֡ 4*1536= 6.0kB */
#define AMHW_EMAC_ETH_MAX_FLEN        1536        /**<  \brief ֡��С  */
#define AMHW_EMAC_TX_FRAME_TOUT       0x00100000  /**<  \brief ֡���䳬ʱ */
/** @} */


/**
* \name EMAC �շ���ַ�궨��
* @{
*/
#define AMHW_EMAC_ETH_FRAG_SIZE       1536         /**<  \brief  ����С */

extern uint8_t __g_amhw_emac_buf[((AMHW_EMAC_NUM_RX_FRAG + AMHW_EMAC_NUM_TX_FRAG) \
    * AMHW_EMAC_ETH_MAX_FLEN) + \
     (AMHW_EMAC_NUM_TX_FRAG * 2 + AMHW_EMAC_NUM_TX_FRAG) * 8 + \
     (AMHW_EMAC_NUM_RX_FRAG * 4)] __attribute__((section(".ahb_bss"))) \
                                  __attribute__((aligned(4)));

/**  \brief ������������ַ  */
#define AMHW_EMAC_RX_DESC_BASE        ((uint32_t)&__g_amhw_emac_buf[0])

#define AMHW_EMAC_RX_STAT_BASE        (AMHW_EMAC_RX_DESC_BASE + AMHW_EMAC_NUM_RX_FRAG * 8) /**<  \brief ����״̬��ַ  */
#define AMHW_EMAC_TX_DESC_BASE        (AMHW_EMAC_RX_STAT_BASE + AMHW_EMAC_NUM_RX_FRAG * 8) /**<  \brief ������������ַ  */
#define AMHW_EMAC_TX_STAT_BASE        (AMHW_EMAC_TX_DESC_BASE + AMHW_EMAC_NUM_TX_FRAG * 8) /**<  \brief ����״̬��ַ  */
#define AMHW_EMAC_RX_BUF_BASE         (AMHW_EMAC_TX_STAT_BASE + AMHW_EMAC_NUM_TX_FRAG * 4) /**<  \brief ���ջ����ַ  */
#define AMHW_EMAC_TX_BUF_BASE         (AMHW_EMAC_RX_BUF_BASE  + AMHW_EMAC_NUM_RX_FRAG * AMHW_EMAC_ETH_FRAG_SIZE) /**<  \brief ���ջ����ַ  */

#define AMHW_EMAC_RX_DESC_PACKET(i)   (*(unsigned int *)(AMHW_EMAC_RX_DESC_BASE     + 8 * i)) /**<  \brief ���հ���ַ  */
#define AMHW_EMAC_RX_DESC_CTRL(i)     (*(unsigned int *)(AMHW_EMAC_RX_DESC_BASE + 4 + 8 * i)) /**<  \brief ���տ��ƻ�ַ  */
#define AMHW_EMAC_RX_STAT_INFO(i)     (*(unsigned int *)(AMHW_EMAC_RX_STAT_BASE     + 8 * i)) /**<  \brief ������Ϣ��ַ  */
#define AMHW_EMAC_RX_STAT_HASHCRC(i)  (*(unsigned int *)(AMHW_EMAC_RX_STAT_BASE + 4 + 8 * i)) /**<  \brief ����CRC��ַ  */
#define AMHW_EMAC_TX_DESC_PACKET(i)   (*(unsigned int *)(AMHW_EMAC_TX_DESC_BASE     + 8 * i)) /**<  \brief ���Ͱ���ַ  */
#define AMHW_EMAC_TX_DESC_CTRL(i)     (*(unsigned int *)(AMHW_EMAC_TX_DESC_BASE + 4 + 8 * i)) /**<  \brief ���Ϳ��ƻ�ַ  */
#define AMHW_EMAC_TX_STAT_INFO(i)     (*(unsigned int *)(AMHW_EMAC_TX_STAT_BASE     + 4 * i)) /**<  \brief ������Ϣ��ַ  */
#define AMHW_EMAC_RX_BUF(i)           (AMHW_EMAC_RX_BUF_BASE + AMHW_EMAC_ETH_FRAG_SIZE * i)   /**<  \brief  ���������ַ */
#define AMHW_EMAC_TX_BUF(i)           (AMHW_EMAC_TX_BUF_BASE + AMHW_EMAC_ETH_FRAG_SIZE * i)   /**<  \brief  ���������ַ */

#define AMHW_EMAC_RCTRL_INT           0x80000000  /**< \brief ��������ж�  */

/** @} */

/**
 * \name EMAC PHY����ģʽ
 * @{
 */
#define AMHW_EMAC_MODE_AUTO				(0)		/**<  \brief �Զ�ģʽ */
#define AMHW_EMAC_MODE_10M_FULL			(1)		/**<  \brief 10Mȫ˫��ģʽ */
#define AMHW_EMAC_MODE_10M_HALF			(2)		/**<  \brief 10M��˫��ģʽ */
#define AMHW_EMAC_MODE_100M_FULL		(3)		/**<  \brief 100Mȫ˫��ģʽ */
#define AMHW_EMAC_MODE_100M_HALF		(4)		/**<  \brief 100M��˫��ģʽ */
/** @} */

/* λ���� */

/**
 * \name MAC���üĴ���1λ����
 * @{
 */
#define AMHW_EMAC_MAC1_REC_EN         0x00000001  /**<  \brief ����ʹ�� */
#define AMHW_EMAC_MAC1_PASS_ALL       0x00000002  /**<  \brief �������н���֡ */
#define AMHW_EMAC_MAC1_RX_FLOWC       0x00000004  /**<  \brief ���������� */
#define AMHW_EMAC_MAC1_TX_FLOWC       0x00000008  /**<  \brief ���������� */
#define AMHW_EMAC_MAC1_LOOPB          0x00000010  /**<  \brief �ػ�ģʽ */
#define AMHW_EMAC_MAC1_RES_TX         0x00000100  /**<  \brief ��λ�����߼� */
#define AMHW_EMAC_MAC1_RES_MCS_TX     0x00000200  /**<  \brief ��λMAC���Ϳ����Ӳ� */
#define AMHW_EMAC_MAC1_RES_RX         0x00000400  /**<  \brief ��λ�����߼� */
#define AMHW_EMAC_MAC1_RES_MCS_RX     0x00000800  /**<  \brief ��λMAC���տ����Ӳ� */
#define AMHW_EMAC_MAC1_SIM_RES        0x00004000  /**<  \brief �����������λ */
#define AMHW_EMAC_MAC1_SOFT_RES       0x00008000  /**<  \brief �����λMAC */
/** @} */

/**
 * \name MAC���üĴ���2λ����
 * @{
 */
#define AMHW_EMAC_MAC2_FULL_DUP       0x00000001  /**<  \brief ȫ˫��ģʽ */
#define AMHW_EMAC_MAC2_FRM_LEN_CHK    0x00000002  /**<  \brief ֡��У�� */
#define AMHW_EMAC_MAC2_HUGE_FRM_EN    0x00000004  /**<  \brief ��֡ʹ�� */
#define AMHW_EMAC_MAC2_DLY_CRC        0x00000008  /**<  \brief ��ʱУ�� */
#define AMHW_EMAC_MAC2_CRC_EN         0x00000010  /**<  \brief ��չ��ʱУ�鵽ÿ֡ */
#define AMHW_EMAC_MAC2_PAD_EN         0x00000020  /**<  \brief ����֡ */
#define AMHW_EMAC_MAC2_VLAN_PAD_EN    0x00000040  /**<  \brief VLAN���ʹ�� */
#define AMHW_EMAC_MAC2_ADET_PAD_EN    0x00000080  /**<  \brief �Զ�������ʹ�� */
#define AMHW_EMAC_MAC2_PPREAM_ENF     0x00000100  /**<  \brief У�鵼������ */
#define AMHW_EMAC_MAC2_LPREAM_ENF     0x00000200  /**<  \brief У�鵼�Գ��� */
#define AMHW_EMAC_MAC2_NO_BACKOFF     0x00001000  /**<  \brief �����㷨 */
#define AMHW_EMAC_MAC2_BACK_PRESSURE  0x00002000  /**<  \brief ��ѹ/���� */
#define AMHW_EMAC_MAC2_EXCESS_DEF     0x00004000  /**<  \brief �ز����� */
/** @} */

/**
 * \name �������������ڲ��������ipgt���Ĵ���  
 * @{
 */
/**  \brief �������������ڲ�������Ĵ���λ�궨�� */
#define AMHW_EMAC_IPGT_BBIPG(n)		 (n&0x7F)
/**  \brief ȫ˫��ģʽ */
#define AMHW_EMAC_IPGT_FULL_DUP		 (AMHW_EMAC_IPGT_BBIPG(0x15))
/**  \brief ��˫��ģʽ */
#define AMHW_EMAC_IPGT_HALF_DUP      (AMHW_EMAC_IPGT_BBIPG(0x12))
/** @} */

/**
 * \name ���������������ڲ��������ipgr���Ĵ���  
 * @{
 */
/**  \brief ���������������ڲ�������Ĵ���λ���� */
#define AMHW_EMAC_IPGR_NBBIPG_P2(n)	(n&0x7F)
/**  \brief ���������������ڲ�������Ĵ�������2 */
#define AMHW_EMAC_IPGR_P2_DEF		(AMHW_EMAC_IPGR_NBBIPG_P2(0x12))
/**  \brief �����ز��ֶ� */
#define AMHW_EMAC_IPGR_NBBIPG_P1(n)	((n&0x7F)<<8)
/**  \brief ���������������ڲ�������Ĵ�������1 */
#define AMHW_EMAC_IPGR_P1_DEF        AMHW_EMAC_IPGR_NBBIPG_P1(0x0C)
/** @} */

/* ��ͻ����/���ԼĴ��� */
/**
 * \name ���������������ڲ�������Ĵ���  ipgrλ����
 * @{
 */
/**  \brief ��ͻ֮�����·��ʹ��� */
#define AMHW_EMAC_CLRT_MAX_RETX(n)	(n&0x0F)
/**  \brief ʱ���/��ͻ�������� */
#define AMHW_EMAC_CLRT_COLL(n)		((n&0x3F)<<8)
/**  \brief ʱ���/��ͻ����Ĭ��ֵ */
#define AMHW_EMAC_CLRT_DEF          ((AMHW_EMAC_CLRT_MAX_RETX(0x0F))|\
                                    (AMHW_EMAC_CLRT_COLL(0x37)))
/** @} */

/**
 * \name ���֡�Ĵ���λ����
 * @{
 */
/**  \brief ���֡�Ĵ���λ�궨�� */
#define AMHW_EMAC_MAXF_MAXFRMLEN(n)	(n&0xFFFF)
/** @} */

/**
 * \name PHY֧�ּĴ���λ����
 * @{
 */
#define AMHW_EMAC_SUPP_SPEED			0x00000100  	/**<  \brief ���ü򻯵�MII�߼������ڵ�ǰ�Ĳ������� */
#define AMHW_EMAC_SUPP_RES_RMII         0x00000800  	/**<  \brief �򻯵�MII�߼� */
/** @} */

/**
 * \name ���ԼĴ���λ����
 * @{
 */
#define AMHW_EMAC_TEST_SHCUT_PQUANTA  0x00000001  	/**<  \brief ��������ʱ�� */
#define AMHW_EMAC_TEST_TST_PAUSE      0x00000002  	/**<  \brief ������ͣ */
#define AMHW_EMAC_TEST_TST_BACKP      0x00000004  	/**<  \brief ������ѹ */
/** @} */

/**
 * \name MII Management���üĴ���λ����
 * @{
 */
#define AMHW_EMAC_MCFG_SCAN_INC       0x00000001  	/**<  \brief ������ȡPHY��ַ */
#define AMHW_EMAC_MCFG_SUPP_PREAM     0x00000002  	/**<  \brief ��ֹ���� */
#define AMHW_EMAC_MCFG_CLK_SEL(n)     ((n&0x0F)<<2)  /**<  \brief ʱ��ѡ���� */
#define AMHW_EMAC_MCFG_RES_MII        0x00008000  	/**<  \brief ��λMIIӲ�� */
#define AMHW_EMAC_MCFG_MII_MAXCLK	  2500000UL		/**<  \brief MII���ʱ�� */
/** @} */


/**
 * \name MII Management����Ĵ���λ����
 * @{
 */
#define AMHW_EMAC_MCMD_READ           0x00000001  	/**<  \brief MII�� */
#define AMHW_EMAC_MCMD_SCAN           0x00000002  	/**<  \brief MII������� */
#define AMHW_EMAC_MII_WR_TOUT         0x00050000  	/**<  \brief MIIд��ʱ */
#define AMHW_EMAC_MII_RD_TOUT         0x00050000  	/**<  \brief MII����ʱ */


/**
 * \name MII Management��ַ�Ĵ���λ����
 * @{
 */
#define AMHW_EMAC_MADR_REG_ADR(n)     (n&0x1F)  	/**<  \brief MII�Ĵ�����ַ�� */
#define AMHW_EMAC_MADR_PHY_ADR(n)     ((n&0x1F)<<8)  /**<  \brief PHY��ַ�� */
/** @} */

/**
 * \name MII����д���ݼĴ���λ����
 * @{
 */
/**  \brief MII����д���ݼĴ��� */
#define AMHW_EMAC_MWTD_DATA(n)		(n&0xFFFF)		
/** @} */

/**
 * \name MII��������ݼĴ���λ����
 * @{
 */
/**  \brief MII��������ݼĴ��� */
#define AMHW_EMAC_MRDD_DATA(n)		(n&0xFFFF)		
/** @} */

/**
 * \name MII����ָʾ�Ĵ���λ����
 * @{
 */
#define AMHW_EMAC_MIND_BUSY           0x00000001  	/**<  \brief MIIæ */
#define AMHW_EMAC_MIND_SCAN           0x00000002  	/**<  \brief MIIɨ�����ڽ��� */
#define AMHW_EMAC_MIND_NOT_VAL        0x00000004  	/**<  \brief MII��������Ч */
#define AMHW_EMAC_MIND_MII_LINK_FAIL  0x00000008  	/**<  \brief MII����ʧ�� */
/** @} */


/* ���ƼĴ����궨�� */
/**
 * \name ����Ĵ���λ����
 * @{
 */
#define AMHW_EMAC_CR_RX_EN            0x00000001  	/**<  \brief ����ʹ�� */
#define AMHW_EMAC_CR_TX_EN            0x00000002  	/**<  \brief ����ʹ�� */
#define AMHW_EMAC_CR_REG_RES          0x00000008  	/**<  \brief �Ĵ�����λ */
#define AMHW_EMAC_CR_TX_RES           0x00000010  	/**<  \brief ����ͨ����λ */
#define AMHW_EMAC_CR_RX_RES           0x00000020  	/**<  \brief ����ͨ����λ */
#define AMHW_EMAC_CR_PASS_RUNT_FRM    0x00000040  	/**<  \brief ��֡�˳� */
#define AMHW_EMAC_CR_PASS_RX_FILT     0x00000080  	/**<  \brief ���չ��� */
#define AMHW_EMAC_CR_TX_FLOW_CTRL     0x00000100  	/**<  \brief ���������� */
#define AMHW_EMAC_CR_RMII             0x00000200  	/**<  \brief ����MII�ӿ� */
#define AMHW_EMAC_CR_FULL_DUP         0x00000400  	/**<  \brief ȫ˫�� */
/** @} */

/**
 * \name ״̬�Ĵ���λ����
 * @{
 */
#define AMHW_EMAC_SR_RX_EN            0x00000001  	/**<  \brief ����ʹ��  */
#define AMHW_EMAC_SR_TX_EN            0x00000002  	/**<  \brief ����ʹ�� */
/** @} */

/**
 * \name ����״̬����0�Ĵ���λ�궨��
 * @{
 */
#define AMHW_EMAC_TSV0_CRC_ERR        0x00000001  /**<  \brief CRC���� */
#define AMHW_EMAC_TSV0_LEN_CHKERR     0x00000002  /**<  \brief ����У����� */
#define AMHW_EMAC_TSV0_LEN_OUTRNG     0x00000004  /**<  \brief �������� */
#define AMHW_EMAC_TSV0_DONE           0x00000008  /**<  \brief ������� */
#define AMHW_EMAC_TSV0_MCAST          0x00000010  /**<  \brief ����Ŀ���ַΪ�ಥ��ַ */
#define AMHW_EMAC_TSV0_BCAST          0x00000020  /**<  \brief ����Ŀ���ַΪ�㲥��ַ */
#define AMHW_EMAC_TSV0_PKT_DEFER      0x00000040  /**<  \brief ���ӳ� */
#define AMHW_EMAC_TSV0_EXC_DEFER      0x00000080  /**<  \brief ���ӳ�ʱ�䳬���涨ֵ */
#define AMHW_EMAC_TSV0_EXC_COLL       0x00000100  /**<  \brief �ӳٳ�ͻ */
#define AMHW_EMAC_TSV0_LATE_COLL      0x00000200  /**<  \brief �����ĳ�ͻ�����˳�ͻ���� */
#define AMHW_EMAC_TSV0_GIANT          0x00000400  /**<  \brief ��֡ */
#define AMHW_EMAC_TSV0_UNDERRUN       0x00000800  /**<  \brief ����������Ļ��������� */
#define AMHW_EMAC_TSV0_BYTES          0x0FFFF000  /**<  \brief ������ͻ����֡�ڵĴ����ֽ��� */
#define AMHW_EMAC_TSV0_CTRL_FRAME     0x10000000  /**<  \brief ����֡*/
#define AMHW_EMAC_TSV0_PAUSE          0x20000000  /**<  \brief ��ͣ֡ */
#define AMHW_EMAC_TSV0_BACK_PRESS     0x40000000  /**<  \brief ��ѹӦ�� */
#define AMHW_EMAC_TSV0_VLAN           0x80000000  /**<  \brief VLAN֡ */
/** @} */

/**
 * \name ����״̬�����Ĵ���1����
 * @{
 */
#define AMHW_EMAC_TSV1_BYTE_CNT       0x0000FFFF  /**<  \brief �����ֽ����� */
#define AMHW_EMAC_TSV1_COLL_CNT       0x000F0000  /**<  \brief ���ͳ�ͻ���� */
/** @} */

/**
 * \name ����״̬�����Ĵ���λ����
 * @{
 */
#define AMHW_EMAC_RSV_BYTE_CNT        0x0000FFFF  /**<  \brief ����֡��Ϣ���� */
#define AMHW_EMAC_RSV_PKT_IGNORED     0x00010000  /**<  \brief ����ǰһ���� */
#define AMHW_EMAC_RSV_RXDV_SEEN       0x00020000  /**<  \brief ǰһ�¼����Ȳ��������ܳ�Ϊ��Ч�� */
#define AMHW_EMAC_RSV_CARR_SEEN       0x00040000  /**<  \brief ǰһ����ͳ�ƺ󣬼�⵽�ز��¼� */
#define AMHW_EMAC_RSV_REC_CODEV       0x00080000  /**<  \brief ���մ�����Ч */
#define AMHW_EMAC_RSV_CRC_ERR         0x00100000  /**<  \brief CRC���� */
#define AMHW_EMAC_RSV_LEN_CHKERR      0x00200000  /**<  \brief ����У����� */
#define AMHW_EMAC_RSV_LEN_OUTRNG      0x00400000  /**<  \brief ���ȷ�Χ */
#define AMHW_EMAC_RSV_REC_OK          0x00800000  /**<  \brief ֡�������� */
#define AMHW_EMAC_RSV_MCAST           0x01000000  /**<  \brief ����Ŀ���ַΪ�ಥ��ַ */
#define AMHW_EMAC_RSV_BCAST           0x02000000  /**<  \brief ����Ŀ���ַΪ�㲥��ַ */
#define AMHW_EMAC_RSV_DRIB_NIBB       0x04000000  /**<  \brief ���յ���֮���ֽ��յ���һ��1-7λ������ */
#define AMHW_EMAC_RSV_CTRL_FRAME      0x08000000  /**<  \brief ����֡ */
#define AMHW_EMAC_RSV_PAUSE           0x10000000  /**<  \brief ��ͣ֡ */
#define AMHW_EMAC_RSV_UNSUPP_OPC      0x20000000  /**<  \brief δ֪������ */
#define AMHW_EMAC_RSV_VLAN            0x40000000  /**<  \brief VLAN֡ */
/** @} */

/**
 * \name �����Ƽ������Ĵ�������
 * @{
 */
#define AMHW_EMAC_FCC_MIRR_CNT(n)        	(n&0xFFFF)  		/**<  \brief ���·�����ͣ����֮֡ǰ�������� */
#define AMHW_EMAC_FCC_PAUSE_TIM(n)       	((n&0xFFFF)<<16)  	/**<  \brief ��ͣ��ʱ��ֵ */
/** @} */

/**
 * \name ������״̬�Ĵ�������
 * @{
 */
#define AMHW_EMAC_FCS_MIRR_CNT(n)        	(n&0xFFFF)  		/**<  \brief �����������ǰֵ */
/** @} */


/* ���չ��˼Ĵ������� */
/**
 * \name ���չ��������ƼĴ���λ����
 * @{
 */
#define AMHW_EMAC_RFC_UCAST_EN        0x00000001  /**<  \brief �������еĵ���֡ */
#define AMHW_EMAC_RFC_BCAST_EN        0x00000002  /**<  \brief �������й㲥֡ */
#define AMHW_EMAC_RFC_MCAST_EN        0x00000004  /**<  \brief ʹ�ܽ��նಥ֡ */
#define AMHW_EMAC_RFC_UCAST_HASH_EN   0x00000008  /**<  \brief ����ͨ������ȫhash�������ĵ���֡ */
#define AMHW_EMAC_RFC_MCAST_HASH_EN   0x00000010  /**<  \brief ����ͨ������ȫhash�������Ķಥ֡ */
#define AMHW_EMAC_RFC_PERFECT_EN      0x00000020  /**<  \brief ����Ŀ���ַ��վ��ַ��ͬ��֡ */
#define AMHW_EMAC_RFC_MAGP_WOL_EN     0x00001000  /**<  \brief ħ�����������ж�ʹ�� */
#define AMHW_EMAC_RFC_PFILT_WOL_EN    0x00002000  /**<  \brief ��ȫ��ַƥ��������벻��ȫhash�������Ľ��ƥ���ж�ʹ�� */
/** @} */

/**
 * \name ���չ�����LAN�ϻ���״̬�Ĵ���λ����
 * @{
 */
#define AMHW_EMAC_WOL_UCAST           0x00000001  /**<  \brief ����֡����WoL */
#define AMHW_EMAC_WOL_BCAST           0x00000002  /**<  \brief �㲥֡����WoL */
#define AMHW_EMAC_WOL_MCAST           0x00000004  /**<  \brief �ಥ֡����WoL */
#define AMHW_EMAC_WOL_UCAST_HASH      0x00000008  /**<  \brief һ��ͨ������ȫhash�������ĵ���֡����WoL */
#define AMHW_EMAC_WOL_MCAST_HASH      0x00000010  /**<  \brief һ��ͨ������ȫhash�������Ķಥ֡����WoL */
#define AMHW_EMAC_WOL_PERFECT         0x00000020  /**<  \brief ��ȫ��ַƥ�����������WoL */
#define AMHW_EMAC_WOL_RX_FILTER       0x00000080  /**<  \brief ���չ���������WoL */
#define AMHW_EMAC_WOL_MAG_PACKET      0x00000100  /**<  \brief ħ��������������WoL */
#define AMHW_EMAC_WOL_BITMASK		  0x01BF      /**<  \brief ���չ�����Wol״̬�Ĵ���λ���� */
/** @} */

/* ģ����ƼĴ��� */
/**
 * \name �ж�״̬ʹ�ܡ����㡢��λλ����
 * \anchor grp_amhw_enet_int
 * @{
 */
#define AMHW_EMAC_INT_RX_OVERRUN      0x00000001  /**<  \brief ���ն����������ʱ�ж���λ */
#define AMHW_EMAC_INT_RX_ERR          0x00000002  /**<  \brief ���մ��� */
#define AMHW_EMAC_INT_RX_FIN          0x00000004  /**<  \brief ���н����������Ѵ����� */
#define AMHW_EMAC_INT_RX_DONE         0x00000008  /**<  \brief ������� */
#define AMHW_EMAC_INT_TX_UNDERRUN     0x00000010  /**<  \brief ���Ͷ����������ʱ�ж���λ */
#define AMHW_EMAC_INT_TX_ERR          0x00000020  /**<  \brief ���ʹ��� */
#define AMHW_EMAC_INT_TX_FIN          0x00000040  /**<  \brief ���з����������Ѵ����� */
#define AMHW_EMAC_INT_TX_DONE         0x00000080  /**<  \brief ������� */
#define AMHW_EMAC_INT_SOFT_INT        0x00001000  /**<  \brief ��������ж� */
#define AMHW_EMAC_INT_WAKEUP          0x00002000  /**<  \brief �����¼��ж� */
/** @} */

/**
 * \name ����Ĵ�������
 * @{
 */
#define AMHW_EMAC_PD_POWER_DOWN       0x80000000  /**<  \brief ������PD�Ĵ����������AHB���� */
/** @} */


/* ��������״̬��ʽ */
/**
 * \name ���������������ֶ���
 * @{
 */
#define AMHW_EMAC_RCTRL_SIZE(n)       (n&0x7FF)  	/**<  \brief ���ݻ�������С */
#define AMHW_EMAC_RCTRL_INT           0x80000000  	/**<  \brief ������������ж� */
/** @} */

/**
 * \name ����״̬Hash CRC�ֶ���
 * @{
 */
#define EMAC_RHASH_SA            0x000001FF  	/**<  \brief ��Դ��ַ�м�����õ�Hash CRC */
#define EMAC_RHASH_DA            0x001FF000  	/**<  \brief ��Ŀ�ĵ�ַ�м�����õ�Hash CRC */
/** @} */

/**
 * \name ����״̬��Ϣ�ֶ���
 * \anchor grp_amhw_enet_rinfo
 * @{
 */
#define AMHW_EMAC_RINFO_SIZE          0x000007FF  /**<  \brief ʵ�����ݵ��ֽ��� */
#define AMHW_EMAC_RINFO_CTRL_FRAME    0x00040000  /**<  \brief ����֡ */
#define AMHW_EMAC_RINFO_VLAN          0x00080000  /**<  \brief VLAN֡ */
#define AMHW_EMAC_RINFO_FAIL_FILT     0x00100000  /**<  \brief ���չ������� */
#define AMHW_EMAC_RINFO_MCAST         0x00200000  /**<  \brief �ಥ֡ */
#define AMHW_EMAC_RINFO_BCAST         0x00400000  /**<  \brief �㲥֡ */
#define AMHW_EMAC_RINFO_CRC_ERR       0x00800000  /**<  \brief ���յ�֡��CRC���� */
#define AMHW_EMAC_RINFO_SYM_ERR       0x01000000  /**<  \brief PHY�ӿڱ�����һ������ */
#define AMHW_EMAC_RINFO_LEN_ERR       0x02000000  /**<  \brief ֡���ȴ��� */
#define AMHW_EMAC_RINFO_RANGE_ERR     0x04000000  /**<  \brief ����󳤶����� */
#define AMHW_EMAC_RINFO_ALIGN_ERR     0x08000000  /**<  \brief ������� */
#define AMHW_EMAC_RINFO_OVERRUN       0x10000000  /**<  \brief ������� */
#define AMHW_EMAC_RINFO_NO_DESCR      0x20000000  /**<  \brief û���µĽ������������� */
#define AMHW_EMAC_RINFO_LAST_FLAG     0x40000000  /**<  \brief ֡�����һ��Ƭ�� */
#define AMHW_EMAC_RINFO_ERR           0x80000000  /**<  \brief ֡���չ����г��ִ��� */

/**  \brief ֡���մ�������  */
#define AMHW_EMAC_RINFO_ERR_MASK     (AMHW_EMAC_RINFO_FAIL_FILT |\
                                      AMHW_EMAC_RINFO_CRC_ERR   |\
                                      AMHW_EMAC_RINFO_SYM_ERR   |\
                                      AMHW_EMAC_RINFO_LEN_ERR   |\
                                      AMHW_EMAC_RINFO_ALIGN_ERR |\
                                      AMHW_EMAC_RINFO_OVERRUN)
/** @} */

/**
 * \name �����������Ŀ�����λ����
 * @{
 */
#define AMHW_EMAC_TCTRL_SIZE          0x000007FF  /**<  \brief ���ݻ�������С  */
#define AMHW_EMAC_TCTRL_OVERRIDE      0x04000000  /**<  \brief ����ÿһ֡ */
#define AMHW_EMAC_TCTRL_HUGE          0x08000000  /**<  \brief ʹ�ܾ�֡ */
#define AMHW_EMAC_TCTRL_PAD           0x10000000  /**<  \brief ����֡��䵽64�ֽ� */
#define AMHW_EMAC_TCTRL_CRC           0x20000000  /**<  \brief ��һ��Ӳ��CRC��ӵ�֡�� */
#define AMHW_EMAC_TCTRL_LAST          0x40000000  /**<  \brief ����֡�����һ��Ƭ�ε������� */
#define AMHW_EMAC_TCTRL_INT           0x80000000  /**<  \brief ������������ж� */
/** @} */

/**
 * \name ����״̬����Ϣ��λ����
 * @{
 */
#define AMHW_EMAC_TINFO_COL_CNT       0x01E00000  /**<  \brief ��ͻ���� */
#define AMHW_EMAC_TINFO_DEFER         0x02000000  /**<  \brief ����ý�屻ռ�ݶ����ӳ� */
#define AMHW_EMAC_TINFO_EXCESS_DEF    0x04000000  /**<  \brief �ӳٳ����������ӳ����Ʋ�����ֹ */
#define AMHW_EMAC_TINFO_EXCESS_COL    0x08000000  /**<  \brief �����������ĳ�ͻ���Ʋ�����ֹ */
#define AMHW_EMAC_TINFO_LATE_COL      0x10000000  /**<  \brief ��ͻ���ڳ�����Χ�����·��Ͱ���ֹ */
#define AMHW_EMAC_TINFO_UNDERRUN      0x20000000  /**<  \brief û�����������ݶ����ַ������� */
#define AMHW_EMAC_TINFO_NO_DESCR      0x40000000  /**<  \brief �޿��õ������� */
#define AMHW_EMAC_TINFO_ERR           0x80000000  /**<  \brief ���͹����г��ֵĴ��� */
/** @} */


/**
 * @brief �������ݻ���ṹ��
 */
typedef struct amhw_mac_packet_type {
	uint32_t  data_length;      /**<  \brief ���ݳ���  */
	uint32_t *p_data_buf;		/**<  \brief ����ָ�� */
} amhw_mac_packet_type_t;



/**
 * @brief PHYģʽ/��ַ
 */
typedef struct amhw_phy_addr_mode {
    uint32_t            mode;          /**<  \brief
                                            - AMHW_EMAC_MODE_AUTO
                                            - AMHW_EMAC_MODE_10M_FULL
                                            - AMHW_EMAC_MODE_10M_HALF
                                            - AMHW_EMAC_MODE_100M_FULL
                                            - AMHW_EMAC_MODE_100M_HALF
                                            */
    uint32_t            phy_addr;    /**<  \brief PHY��ַ */
} amhw_phy_addr_mode_t;


/** \brief PHY��ʼ������ָ�� */
typedef int  (*pfn_amhw_phy_init) (amhw_enet_t             *p_hw_enet,
                                   amhw_phy_addr_mode_t    *p_phy_addr_mode);

/**
 * @brief enet���ýṹ��
 */
typedef struct amhw_enet_config {
	uint8_t               *p_mac_addr;    /**<  \brief MAC��ַ */
	amhw_phy_addr_mode_t   phy_addr_mode; /**<  \brief PHY��ַ */
	pfn_amhw_phy_init      pfn_phy_init;  /**<  \brief PHY��ʼ������ָ�� */
} amhw_enet_config_t;




/**
 * \brief  ����mac1ֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_mac1_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->mac1 = regvalue;
}

/**
 * \brief  ����mac1λֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_mac1_val_set_bit (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->mac1 |= regvalue;
}

/**
 * \brief  ����mac2ֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_mac2_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->mac2 = regvalue;
}
/**
 * \brief  ����mac2λ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_mac2_val_set_bit (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->mac2 |= regvalue;
}

/**
 * \brief  ����commandֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_command_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->command = regvalue;
}

/**
 * \brief  ����commandλֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_command_val_set_bit (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->command |= regvalue;
}


/**
 * \brief  ����suppֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_supp_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->supp = regvalue;
}


/**
 * \brief  ����ipgtֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_ipgt_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->ipgt = regvalue;
}


/**
 * \brief  ����rx_descriptorֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_rx_descriptor_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->rx_descriptor = regvalue;
}

/**
 * \brief  ����rx_statusֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_rx_status_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->rx_status = regvalue;
}

/**
 * \brief  ����rx_descriptor_numberֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_rx_descriptor_number_val_set (amhw_enet_t *p_hw_enet,
                                             uint32_t     regvalue)
{   
	p_hw_enet->rx_descriptor_number = regvalue;
}

/**
 * \brief  ����rx_consume_indexֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_rx_consume_index_val_set (amhw_enet_t *p_hw_enet,
                                         uint32_t     regvalue)
{   
	p_hw_enet->rx_consume_index = regvalue;
}


/**
 * \brief  ����tx_descriptorֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_tx_descriptor_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->tx_descriptor = regvalue;
}

/**
 * \brief  ����tx_statusֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_tx_status_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{   
	p_hw_enet->tx_status = regvalue;
}

/**
 * \brief  ����tx_descriptor_numberֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_tx_descriptor_number_val_set (amhw_enet_t *p_hw_enet,
                                             uint32_t     regvalue)
{   
	p_hw_enet->tx_descriptor_number = regvalue;
}

/**
 * \brief  ����tx_produce_indexֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_enet_tx_produce_index_val_set (amhw_enet_t *p_hw_enet,
                                         uint32_t     regvalue)
{   
	p_hw_enet->tx_produce_index = regvalue;
}

/**
 * \brief  ��ȡtx_produce_indexֵ
 *
 * \param[in] p_hw_enet ������ָ��
 *
 *  return   ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_enet_tx_produce_index_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->tx_produce_index;
}


/**
 * \brief  ����madrֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_madr_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->madr = regvalue;
}

/**
 * \brief  ����mwtdֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_mwtd_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->mwtd = regvalue;
}

/**
 * \brief  ��ȡmindֵ
 *
 * \param[in] p_hw_enet ������ָ��
 *
 *  return   ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_enet_mind_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->mind;
}

/**
 * \brief  ����mcmdֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_mcmd_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->mcmd = regvalue;
}

/**
 * \brief  ��ȡmrddֵ
 *
 * \param[in] p_hw_enet ������ָ��
 *
 * return   ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_enet_mrdd_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->mrdd;
}

/**
 * \brief  ����sa0ֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_sa0_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->sa0 = regvalue;
}

/**
 * \brief  ����sa1ֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_sa1_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->sa1 = regvalue;
}

/**
 * \brief  ����sa2ֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_sa2_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->sa2 = regvalue;
}

/**
 * \brief  ����maxfֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_maxf_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->maxf = regvalue;
}

/**
 * \brief  ����mcfgֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_mcfg_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->mcfg = regvalue;
}

/**
 * \brief  ����mcfgֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_mcfg_val_clr (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->mcfg &= regvalue;
}

/**
 * \brief  ����clrtֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_clrt_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->clrt = regvalue;
}

/**
 * \brief  ����ipgrֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_ipgr_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->ipgr = regvalue;
}

/**
 * \brief  ����rx_filter_ctrlֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_rx_filter_ctrl_val_set (amhw_enet_t *p_hw_enet,
                                       uint32_t     regvalue)
{
	p_hw_enet->rx_filter_ctrl = regvalue;
}

/**
 * \brief  ����int_enableֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_int_enable_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->int_enable = regvalue;
}

/**
 * \brief  ����int_enableֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_int_enable_val_or (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->int_enable |= regvalue;
}

/**
 * \brief  ����int_enableֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_int_enable_val_clr (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->int_enable &= regvalue;
}

/**
 * \brief  ����int_enableֵ
 *
 * \param[in] p_hw_enet ������ָ��
 *
 *  return   ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_enet_int_enable_val_get (amhw_enet_t *p_hw_enet)
{
	return  p_hw_enet->int_enable;
}


/**
 * \brief  ����int_clearֵ
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] regvalue  ���Ĵ���ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_enet_int_clear_val_set (amhw_enet_t *p_hw_enet, uint32_t regvalue)
{
	p_hw_enet->int_clear = regvalue;
}

/**
 * \brief  ��ȡrx_consume_indexֵ
 *
 * \param[in] p_hw_enet ������ָ��
 *
 * return   ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_enet_rx_consume_index_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->rx_consume_index;
}


/**
 * \brief  ��ȡint_statusֵ
 *
 * \param[in] p_hw_enet ������ָ��
 *
 * return   ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_enet_int_status_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->int_status;
}

/**
 * \brief  ��ȡtx_consume_indexֵ
 *
 * \param[in] p_hw_enet ������ָ��
 *
 * return   ��ǰ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_enet_tx_consume_index_val_get (amhw_enet_t *p_hw_enet)
{
	return p_hw_enet->tx_consume_index;
}




/**
 * \brief ��ʼ�������������ͽ���״̬����
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] p_config  �����ò���ָ��
 *
 * \return     ��
 */
void amhw_enet_rx_descr_init (amhw_enet_t        *p_hw_enet);

/**
 * \brief ��ʼ�������������ͷ���״̬����
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] p_config  �����ò���ָ��
 *
 * \return     ��
 */
void amhw_enet_tx_descr_init (amhw_enet_t        *p_hw_enet);

/**
 * \brief ��valueд��PHY�Ĵ�����
 *
 * \param[in]  p_hw_enet       ������ָ��
 * \param[in]  p_phy_addr_mode ��phyģʽ��ַָ��
 * \param[in]  phy_reg   ���Ĵ�����ַ 
 * \param[in]  value     ����ֵ
 *
 * \retval    -AM_EINVAL ������
 * \retval     AM_OK     ���ɹ�
 */
int amhw_enet_phy_write (amhw_enet_t             *p_hw_enet,
                         amhw_phy_addr_mode_t    *p_phy_addr_mode,
                         uint32_t                 phy_reg,
                         uint16_t                 value);

/**
 * \brief ��PHY�Ĵ���
 *
 * \param[in]  p_hw_enet       ������ָ��
 * \param[in]  p_phy_addr_mode ��phyģʽ��ַָ��
 * \param[in]  phy_reg         ���Ĵ�����ַ
 *
 * \retval    -AM_EINVAL ������
 * \retval     �Ĵ���ֵ
 */
int32_t amhw_enet_phy_read (amhw_enet_t             *p_hw_enet,
                            amhw_phy_addr_mode_t    *p_phy_addr_mode,
                            uint32_t                 phy_reg);

/**
 * \brief ����MAC��ַ
 *
 * \param[in]  p_hw_enet ������ָ��
 * \param[in]  mac_addr  ��MAC��ַ 
 *
 * \return     ��
 */
void amhw_enet_mac_addr_set (amhw_enet_t *p_hw_enet, uint8_t mac_addr[]);

/**
 * \brief ��ʼ����̫��ģ��
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] p_config  �����ò���ָ��
 *
 * \retval    -AM_EINVAL ������
 * \retval     AM_OK     ���ɹ�
 */
int amhw_enet_init (amhw_enet_t *p_hw_enet, amhw_enet_config_t *p_config);

/**
 * \brief д���ݵ����ͻ���
 *
 * \param[in] p_hw_enet     ������ָ��
 * \param[in] p_data_struct ����Ҫд������
 *
 * \retval    ��
 */
void amhw_enet_packet_buffer_write (amhw_enet_t            *p_hw_enet,
                                    amhw_mac_packet_type_t *p_data_struct);

/**
 * \brief �����ݵ����ջ���
 *
 * \param[in] p_hw_enet     ������ָ��
 * \param[in] p_data_struct ����Ҫд������
 *
 * \retval    ��
 */
void amhw_enet_packet_buffer_read (amhw_enet_t            *p_hw_enet,
                                   amhw_mac_packet_type_t *p_data_struct);

/**
 * \brief ʹ��/ʧ��ENET�ж�
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] int_type  :�ж����ͣ��μ�
 *                       \ref grp_amhw_enet_int
 * \param[in] state    :ʹ��TRUE/ʧ��FALSE
 *
 * \retval     ��
 */
void amhw_enet_int_cmd(amhw_enet_t *p_hw_enet, uint32_t int_type, bool_t state);

/**
 * \brief ��ȡ�ж�״̬
 * \param[in] p_hw_enet ������ָ��
 * \param[in] int_type  : �ж����ͣ��μ�
 *                       \ref grp_amhw_enet_int
 *
 * \retval     TRUE  ����Ч
 * \retval     FALSE ����Ч
 */
bool_t amhw_enet_int_status_get (amhw_enet_t *p_hw_enet, uint32_t int_type);

/**
 * \brief ���������������������Ƿ����
 *
 * \param[in] p_hw_enet ������ָ��
 *
 * \retval     TRUE  �����
 * \retval     FALSE ������
 */
bool_t amhw_enet_receive_index_check(amhw_enet_t *p_hw_enet);

/**
 * \brief ��ⷢ�������������������Ƿ����
 *
 * \param[in] p_hw_enet ������ָ��
 *
 * \retval     TRUE  �����
 * \retval     FALSE ������
 */
bool_t amhw_enet_transmit_index_check (amhw_enet_t *p_hw_enet);

/**
 * \brief ��ȡ��ǰ������Ϣ״̬
 *
 * \param[in] p_hw_enet             ������ָ��
 * \param[in] p_config              �����ò���ָ��
 * \param[in] amhw_enet_rx_stat_type��������Ϣ���ͣ��μ�
 *                                   \ref grp_amhw_enet_rinfo
 *
 * \retval     TRUE      ����Ч
 * \retval     FALSE     ����Ч
 */
bool_t amhw_enet_receive_data_status_check (amhw_enet_t        *p_hw_enet,
                                            amhw_enet_config_t *p_config,
                                            uint32_t            amhw_enet_rx_stat_type);

/**
 * \brief ��ȡ��ǰ�������ݵĴ�С
 *
 * \param[in] p_hw_enet ������ָ��
 * \param[in] p_config  �����ò���ָ��
 *
 * \return    �������ݳ���
 */
uint32_t amhw_enet_receive_data_size_get (amhw_enet_t        *p_hw_enet,
                                          amhw_enet_config_t *p_config);

/**
 * \brief ���½�����������
 *
 * \param[in] p_hw_enet ������ָ��
 *
 * \return    ��
 */
void amhw_enet_rx_consume_index_update(amhw_enet_t *p_hw_enet);

/**
 * \brief ���·��Ͳ�������
 *
 * \param[in] p_hw_enet ������ָ��
 *
 * \return    ��
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
    

