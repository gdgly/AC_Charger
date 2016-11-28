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
 * \brief SD����MCI�� Ӳ�������ӿ�
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
 * \name fifo �ĸ���
 * \anchor grp_amhw_fifo_cnt
 * @{
 */

#define AMHW_FIFO_CNT     16    /**< \brief FIFO �ĸ���  */

/** @} */

/**
 * \brief MCI �Ĵ�����ṹ��
 */
typedef struct amhw_mci {
    __IO uint32_t power;        		/**< \brief ��Դ���ƼĴ���        */
    __IO uint32_t clock;       	 		/**< \brief ʱ�ӿ��ƼĴ���        */
    __IO uint32_t argument;     		/**< \brief �����Ĵ���                  */
    __IO uint32_t command;      		/**< \brief ����Ĵ���                  */
    __I  uint32_t resp_cmd;     		/**< \brief ��Ӧ����Ĵ���        */
    __I  uint32_t resp0;        		/**< \brief ��Ӧ�Ĵ���                  */
    __I  uint32_t resp1;        		/**< \brief ��Ӧ�Ĵ���                  */
    __I  uint32_t resp2;        		/**< \brief ��Ӧ�Ĵ���                  */
    __I  uint32_t resp3;        		/**< \brief ��Ӧ�Ĵ���                   */
    __IO uint32_t datatmr;      		/**< \brief ���ݶ�ʱ��                   */
    __IO uint32_t datalen;      		/**< \brief ���ݳ��ȼĴ���         */
    __IO uint32_t datactrl;     		/**< \brief ���ݿ��ƼĴ���         */
    __I  uint32_t datacnt;      		/**< \brief ���ݼ�����                   */
    __I  uint32_t status;       		/**< \brief ״̬�Ĵ���                   */
    __O  uint32_t clear;        		/**< \brief ����Ĵ���                   */
    __IO uint32_t mask0;        		/**< \brief �ж� 0 ���μĴ���   */
         uint32_t reserved0[2]; 		/**< \brief ����                                   */
    __I  uint32_t fifocnt;      		/**< \brief FIFO ������                 */
         uint32_t reserved1[13];		/**< \brief ����                                   */
    __IO uint32_t fifo[AMHW_FIFO_CNT];	/**< \brief ���� FIFO �Ĵ���      */
} amhw_mci_t;

/**
 * \name ϵͳ���ƺ�״̬�Ĵ���λ����
 * \anchor grp_amhw_syscon_mcipwr
 * @{
 */

#define AMHW_SYSCON_MCI_PWR    (0x1UL << 3)         /**< \brief SD_PWR �ߵ�ƽ��Ч  */

/** @} */

/**
 * \brief ����SD_PWR���Ÿߵ�ƽ��Ч
 *
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƿ�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_mci_pwr_level_high_set (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs |= AMHW_SYSCON_MCI_PWR;
}

/**
 * \brief ����SD_PWR���ŵ͵�ƽ��Ч
 *
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƿ�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_mci_pwr_level_low_set (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs &= ~AMHW_SYSCON_MCI_PWR;
}

/**
 * \name MCI ��Դ���ƼĴ���λ����
 * \anchor grp_amhw_mci_pwr
 * @{
 */

typedef int amhw_mci_pwr_ctrl_t;                       /**< \brief ��Դ���ƶ���  */
#define AMHW_MCI_PWR_CTRL_OFF    (0x00UL << 0)         /**< \brief ��Դ�ر�  */
#define AMHW_MCI_PWR_CTRL_RSV    (0x01UL << 0)         /**< \brief ��Դ����  */
#define AMHW_MCI_PWR_CTRL_ON     (0x02UL << 0)         /**< \brief ��Դ�ϵ�  */
#define AMHW_MCI_PWR_CTRL_START  (0x03UL << 0)         /**< \brief ��Դ����  */
#define AMHW_MCI_PWR_OD          (1UL << 6)            /**< \brief SD_CMD ������� */
#define AMHW_MCI_PWR_ROD         (1UL << 7)            /**< \brief ���ư� */

/** @} */

/**
 * \brief ���õ�Դ�����е�ĳһλ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 * \param[in] pwr_ctrl : ��Դ����  ���ò������μ�
 *                       \ref grp_amhw_mci_pwr "MCI PWR"
 *
 * \return ��
 */
am_static_inline 
void amhw_mci_pwr_set (amhw_mci_t *p_hw_mci, amhw_mci_pwr_ctrl_t pwr_ctrl)
{
    p_hw_mci->power |= pwr_ctrl;
}

/**
 * \brief �����Դ�����е�ĳһλ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 * \param[in] pwr_ctrl : ��Դ����  ���ò������μ�
 *                       \ref grp_amhw_mci_pwr "MCI PWR"
 *
 * \return ��
 */
am_static_inline
void amhw_mci_pwr_clr (amhw_mci_t *p_hw_mci, amhw_mci_pwr_ctrl_t pwr_ctrl)
{
    p_hw_mci->power &= ~pwr_ctrl;
}

/**
 * \brief ��ȡ��Դ���Ƶ�����
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��Դ���Ƶ�����  �μ� \ref grp_amhw_mci_pwr "MCI PWR"
 */
am_static_inline
amhw_mci_pwr_ctrl_t amhw_mci_pwr_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->power;
}

/**
 * \name MCI ʱ�ӿ��ƼĴ���λ����
 * \anchor grp_amhw_mci_clock
 * @{
 */

typedef uint32_t amhw_mci_clk_en_t;                /**< \brief ʱ�ӿ���ʹ�ܶ��� */
#define AMHW_MCI_CLK_EN         (1UL << 8)         /**< \brief ʹ��SD������ʱ�� */
#define AMHW_MCI_CLK_PWRSAVE    (1UL << 9)         /**< \brief ���߿���ʱ,��ֹ SD_CLK ���  */
#define AMHW_MCI_CLK_BYPASS     (1UL << 10)        /**< \brief ʹ��ʱ�ӷ�Ƶ�߼���·  */
#define AMHW_MCI_CLK_WIDEBUS    (1UL << 11)        /**< \brief ʹ�ܿ�����ģʽ */

/** @} */

/**
 * \brief ����ʹ�ܿ�����ģʽ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_mci_widebus_set (amhw_mci_t *p_hw_mci)
{
    p_hw_mci->clock |= AMHW_MCI_CLK_WIDEBUS;
}

/**
 * \brief ������ܿ�����ģʽ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_mci_widebus_clr (amhw_mci_t *p_hw_mci)
{
    p_hw_mci->clock &= ~AMHW_MCI_CLK_WIDEBUS;
}

/**
 * \brief ���������߿���ʱʱ�ӿ�ʼ���
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_mci_clking_set (amhw_mci_t *p_hw_mci)
{
    p_hw_mci->clock &= ~AMHW_MCI_CLK_PWRSAVE;
}

/**
 * \brief ��������߿���ʱʱ�����
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_mci_clking_clr (amhw_mci_t *p_hw_mci)
{
    p_hw_mci->clock |= AMHW_MCI_CLK_PWRSAVE;
}

/**
 * \brief ����ʱ��
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 * \param[in] div      : ����ʱ�ӷ�Ƶ
 * \param[in] clk_en   : ��Ҫʹ�ܵ�ʱ��  ���ò������μ�
 *                       \ref grp_amhw_mci_clock "MCI CLOCK ENABLE"
 *
 * \return ��
 */
am_static_inline
void amhw_mci_clk_set (amhw_mci_t        *p_hw_mci,
                       uint8_t            div,
                       amhw_mci_clk_en_t  clk_en)
{
    p_hw_mci->clock = (div | clk_en);
}

/**
 * \brief ��ȡʱ�ӷ�Ƶ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ʱ�ӷ�Ƶ
 */
am_static_inline
uint8_t amhw_mci_clk_div_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->clock & 0xff);
}

/**
 * \brief ��ȡʱ�ӵ�ʹ��״̬
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ʱ�ӵ�ʹ��״̬  �μ� \ref grp_amhw_mci_clock "MCI CLOCK ENABLE"
 */
am_static_inline
amhw_mci_clk_en_t amhw_mci_clk_en_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->clock & (~0xff));
}

/**
 * \brief ���ò���
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 * \param[in] arg      : ����
 *
 * \return ��
 */
am_static_inline
void amhw_mci_arg_set (amhw_mci_t *p_hw_mci, uint32_t arg)
{
    p_hw_mci->argument = arg;
}

/**
 * \brief ��ȡ����ֵ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ����ֵ
 */
am_static_inline
uint32_t amhw_mci_arg_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->argument;
}

/**
 * \name MCI ����Ĵ���λ����
 * \anchor grp_amhw_mci_cmd
 * @{
 */

typedef uint32_t amhw_mci_cmd_ctrl_t;           /**< \brief ������ƶ��� */
#define AMHW_MCI_CMD_RESPONSE       (1UL << 6)  /**< \brief CPSM �ȴ���Ӧ */
#define AMHW_MCI_CMD_LONGRSP        (1UL << 7)  /**< \brief CPSM ����һ�� 136 λ����Ӧ  */
#define AMHW_MCI_CMD_INTERRUPT      (1UL << 8)  /**< \brief CPSM �������ʱ�����ȴ��ж�����  */
#define AMHW_MCI_CMD_PENDING        (1UL << 9)  /**< \brief CPSM �ڿ�ʼ��������ǰ�ȴ� CmdPend */
#define AMHW_MCI_CMD_ENABLE         (1UL << 10) /**< \brief CPSM ��ʹ�� */

/** @} */

/**
 * \brief ����ʱ��
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 * \param[in] cmdindex : ��������
 * \param[in] cmdctrl  : ��Ҫ���Ƶ���������   ���ò������μ�
 *                       \ref grp_amhw_mci_cmd "MCI CMD CTRL"
 *
 * \return ��
 */
am_static_inline
void amhw_mci_cmd_set (amhw_mci_t          *p_hw_mci,
                       uint8_t              cmdindex,
                       amhw_mci_cmd_ctrl_t  cmdctrl)
{
    p_hw_mci->command = ((cmdindex & 0x3f) | cmdctrl);
}

/**
 * \brief ��ȡ��������
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��������
 */
am_static_inline
uint8_t amhw_mci_cmd_index_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->command & 0x3f);
}

/**
 * \brief ��ȡ�����������
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ����ʹ������,�μ�  \ref grp_amhw_mci_cmd "MCI CMD CTRL"
 */
am_static_inline
amhw_mci_cmd_ctrl_t amhw_mci_cmd_en_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->command & (~0x3f));
}

/**
 * \brief ��ȡ������Ӧ����
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ������Ӧ����
 */
am_static_inline
uint8_t amhw_mci_resp_cmd_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->command & 0x3f);
}

/**
 * \brief ��ȡ��״̬����Ӧ���� ������Ӧ ��״̬[31:0] ����Ӧ ��״̬[127:96]��
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��״̬
 */
am_static_inline
uint32_t amhw_mci_resp0_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->resp0;
}

/**
 * \brief ��ȡ��״̬����Ӧ���� ������Ӧ δʹ��   ����Ӧ ��״̬[95:64]��
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��״̬
 */
am_static_inline
uint32_t amhw_mci_resp1_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->resp1;
}

/**
 * \brief ��ȡ��״̬����Ӧ���� ������Ӧ δʹ��   ����Ӧ ��״̬[63:32]��
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��״̬
 */
am_static_inline
uint32_t amhw_mci_resp2_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->resp2;
}

/**
 * \brief ��ȡ��״̬����Ӧ���� ������Ӧ δʹ��   ����Ӧ ��״̬[31:1] [0]ʼ��Ϊ0��
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ��״̬
 */
am_static_inline
uint32_t amhw_mci_resp3_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->resp3;
}

/**
 * \brief �������ݶ�ʱ���Ĵ���
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 * \param[in] datatime : ���ݳ�ʱ����
 *
 * \return ��
 */
am_static_inline
void amhw_mci_datatmr_set (amhw_mci_t *p_hw_mci, uint32_t datatime)
{
    p_hw_mci->datatmr = datatime;
}

/**
 * \brief ��ȡ���ݶ�ʱ����ֵ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ���ݶ�ʱ����ֵ
 */
am_static_inline
uint32_t amhw_mci_datatmr_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->datatmr;
}

/**
 * \brief �������ݳ��ȼĴ���
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 * \param[in] datalen  : ���ݳ���
 *
 * \return ��
 */
am_static_inline
void amhw_mci_datalen_set (amhw_mci_t *p_hw_mci, uint16_t datalen)
{
    p_hw_mci->datalen = datalen;
}

/**
 * \brief ��ȡ���ݳ��ȵ�ֵ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ���ݳ��ȵ�ֵ
 */
am_static_inline
uint16_t amhw_mci_datalen_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->datalen;
}

/**
 * \name MCI ���ݿ��ƼĴ���λ����
 * \anchor grp_amhw_mci_datactrl
 * @{
 */

#define AMHW_MCI_DATA_CTRL_EN       (1UL << 0)  /**< \brief ���ݴ���ʹ�� */
#define AMHW_MCI_DATA_CTRL_DIR      (1UL << 1)  /**< \brief ���ݴ��䷽�� */
#define AMHW_MCI_DATA_CTRL_MOD      (1UL << 2)  /**< \brief ���ݴ���ģʽ */
#define AMHW_MCI_DATA_CTRL_DMA_EN   (1UL << 3)  /**< \brief ʹ��DMA     */
#define AMHW_MCI_DATA_CTRL_BLKSIZE  (1UL << 4)  /**< \brief ���ݿ鳤��      */

/** @} */

/**
 * \name MCI ���ݴ��䷽����
 * \anchor grp_amhw_mci_datadir
 * @{
 */

typedef int amhw_mci_data_dir_t;                /**< \brief ���ݴ��䷽���� */
#define AMHW_MCI_DATA_DIR_M2C       (0UL << 1)  /**< \brief �ӿ��������� */
#define AMHW_MCI_DATA_DIR_C2M       (1UL << 1)  /**< \brief �ӿ��������� */

/** @} */

/**
 * \name MCI ����ģʽ����
 * \anchor grp_amhw_mci_datamode
 * @{
 */

typedef int amhw_mci_data_mod_t;                 /**< \brief ����ģʽ���� */
#define AMHW_MCI_DATA_MOD_BLK_TRAN   (0UL << 2)  /**< \brief �����ݴ��� */
#define AMHW_MCI_DATA_DIR_STR_TRAN   (1UL << 2)  /**< \brief �����ݴ��� */

/** @} */

/**
 * \name MCI ���ݴ��䷽����
 * \anchor grp_amhw_mci_datactrl_en
 * @{
 */

typedef int amhw_mci_datactrl_en_t;            /**< \brief ���ݴ���ʹ�ܶ��� */
#define AMHW_MCI_DATACTRL_EN       (1UL << 0)  /**< \brief ���ݴ���ʹ�� */
#define AMHW_MCI_DATACTRL_DIS      (0UL << 0)  /**< \brief ���ݴ������ */
#define AMHW_MCI_DATACTRL_DMA_EN   (1UL << 3)  /**< \brief ����DMA����ʹ�� */
#define AMHW_MCI_DATACTRL_DMA_DIS  (0UL << 3)  /**< \brief ����DMA������� */

/** @} */

/**
 * \brief �������ݿ�����
 *
 * \param[in] p_hw_mci    : ָ��MCI�Ĵ������ָ��
 * \param[in] dir         : ���ݷ��� ���ò������μ�
 *                          \ref grp_amhw_mci_datadir "MCI DATA DIRECTION"
 * \param[in] mod         : ���ݷ���ģʽ   ���ò������μ�
 *                          \ref grp_amhw_mci_datamode "MCI DATA MODE"
 * \param[in] blocksize   : ���ݿ鳤�� ��2��blocksize�η��ֽڣ�
 * \param[in] datactrl_en : ���ݴ���ʹ��   ���ò������μ�
 *                          \ref grp_amhw_mci_datactrl_en "MCI DATA TRANS ENABLE"
 *
 * \return ��
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
 * \brief ��ȡ���ݴ��䷽��
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ���ݵķ���
 */
am_static_inline
amhw_mci_data_dir_t amhw_mci_data_dir_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->datactrl & AMHW_MCI_DATA_CTRL_DIR);
}

/**
 * \brief ��ȡ���ݴ���ģʽ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ���ݵ�ģʽ
 */
am_static_inline
amhw_mci_data_mod_t amhw_mci_data_mod_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->datactrl & AMHW_MCI_DATA_CTRL_MOD);
}

/**
 * \brief ��ȡ���ݴ���ʹ�ܵ�״̬λ
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return �����ʹ��״̬λ
 */
am_static_inline
amhw_mci_datactrl_en_t amhw_mci_datactrl_enable_get (amhw_mci_t *p_hw_mci)
{
    return (p_hw_mci->datactrl    &
           (AMHW_MCI_DATA_CTRL_EN |
            AMHW_MCI_DATA_CTRL_DMA_EN));
}

/**
 * \brief ��ȡ���ݿ鳤��
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ���ݿ鳤��
 */
am_static_inline
size_t amhw_mci_data_blksize_get (amhw_mci_t *p_hw_mci)
{
    return ((p_hw_mci->datactrl & 0xf0) >> 4);
}

/**
 * \brief ��ȡ���ݼ�����
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return ����ʣ�������
 */
am_static_inline
uint16_t amhw_mci_datacnt_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->datacnt;
}

/**
 * \name MCI �ж����͸���
 * \anchor grp_amhw_mci_int_type_count
 * @{
 */

#define AMHW_MCI_INT_TYPE_COUNT          22       /**< \brief �ж����͵ĸ���  */

/** @} */

/**
 * \name MCI �ж����Ͷ���
 * \anchor grp_amhw_mci_int_type
 * @{
 */

typedef uint32_t amhw_mci_int_type_t;             /**< \brief �ж����Ͷ��� */
#define AMHW_MCI_INT_NONE             (0X0UL)     /**< \brief ���ж�  */
#define AMHW_MCI_INT_CMDCRCFAIL       (1UL << 0)  /**< \brief ������Ӧ���գ�δͨ�� CRC У�飩 */
#define AMHW_MCI_INT_DATACRCFAIL      (1UL << 1)  /**< \brief ���ݿ鷢��/���գ�δͨ�� CRC У�飩 */
#define AMHW_MCI_INT_CMDTIMEOUT       (1UL << 2)  /**< \brief ������Ӧ��ʱ */
#define AMHW_MCI_INT_DATATIMEOUT      (1UL << 3)  /**< \brief ���ݳ�ʱ */
#define AMHW_MCI_INT_TXUNDERRUN       (1UL << 4)  /**< \brief ���� FIFO ������� */
#define AMHW_MCI_INT_RXOVERRUN        (1UL << 5)  /**< \brief ���� FIFO ������� */
#define AMHW_MCI_INT_CMDRESPEND       (1UL << 6)  /**< \brief ������Ӧ���գ�ͨ�� CRC У�飩 */
#define AMHW_MCI_INT_CMDSENT          (1UL << 7)  /**< \brief ����ͣ�������Ӧ�� */
#define AMHW_MCI_INT_DATAEND          (1UL << 8)  /**< \brief ������ֹ�����ݼ�����Ϊ 0�� */
#define AMHW_MCI_INT_STARTBITERR      (1UL << 9)  /**< \brief �ڿ�����ģʽ�£����������ź���δ��⵽��ʼλ */
#define AMHW_MCI_INT_DATABLKEND       (1UL << 10) /**< \brief ���ݿ鷢��/���գ�ͨ�� CRC У�飩 */
#define AMHW_MCI_INT_CMDACTIVE        (1UL << 11) /**< \brief ��������ڽ����� */
#define AMHW_MCI_INT_TXACTIVE         (1UL << 12) /**< \brief ���ݷ������ڽ����� */
#define AMHW_MCI_INT_RXACTIVE         (1UL << 13) /**< \brief ���ݽ������ڽ����� */
#define AMHW_MCI_INT_TXFIFOHEMPTY     (1UL << 14) /**< \brief ���� FIFO Ϊ��� */
#define AMHW_MCI_INT_RXFIFOHFULL      (1UL << 15) /**< \brief ���� FIFO Ϊ���� */
#define AMHW_MCI_INT_TXFIFOFULL       (1UL << 16) /**< \brief ���� FIFO Ϊ�� */
#define AMHW_MCI_INT_RXFIFOFULL       (1UL << 17) /**< \brief ���� FIFO Ϊ�� */
#define AMHW_MCI_INT_TXFIFOEMPTY      (1UL << 18) /**< \brief ���� FIFO Ϊ�� */
#define AMHW_MCI_INT_RXFIFOEMPTY      (1UL << 19) /**< \brief ���� FIFO Ϊ�� */
#define AMHW_MCI_INT_TXDATAAVIBL      (1UL << 20) /**< \brief ���� FIFO �д��ڿ������� */
#define AMHW_MCI_INT_RXDATAAVIBL      (1UL << 21) /**< \brief ���� FIFO �д��ڿ������� */
#define AMHW_MCI_INT_ALL              (0X3FFFFFUL)/**< \brief ���������ж�  */

/** @} */

/**
 * \brief ��ȡ״̬�Ĵ���
 *
 * \param[in] p_hw_mci : ָ��MCI�Ĵ������ָ��
 *
 * \return �μ� \ref grp_amhw_mci_int_type "MCI STATUS"
 *
 * \note   ��̬[10:0]�� ��Щ��־�ᱣ��Ϊ��Ч�� ֱ��ͨ��д������Ĵ������������
 *         ��̬[21:1 1]����Щ����״̬ȡ���ڵײ��߼���״̬�����磬��д�� FIFO ʱ
 *                       FIFO ���Ϳձ�־����Ϊ���ݱ���Ϊ��Ч����Ч�� ��
 */
am_static_inline
amhw_mci_int_type_t amhw_mci_status_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->status;
}

/**
 * \brief ��������Ĵ���   ������Ӧ�ľ�̬״̬��־
 *
 * \param[in] p_hw_mci   : ָ��MCI�Ĵ������ָ��
 * \param[in] status_clr : ��Ҫ�����״̬λ     ���ò������μ�
 *                         \ref grp_amhw_mci_int_type "MCI STATUS"
 *                         ֻ��ǰ11λ[0:10]�ɽ�������  ����Ϊ����λ
 *
 * \return ��
 */
am_static_inline
void amhw_mci_status_clr (amhw_mci_t          *p_hw_mci,
                          amhw_mci_int_type_t  status_clr)
{
    p_hw_mci->clear = status_clr & 0x7ff;
}

/**
 * \brief �����ж����μĴ���  ʹ����Ӧ���ж�λ
 *
 * \param[in] p_hw_mci   : ָ��MCI�Ĵ������ָ��
 * \param[in] int_mask   : ��Ҫ���ε��ж�λ     ���ò������μ�
 *                         \ref grp_amhw_mci_int_type "MCI INT MASK"
 *
 * \return ��
 */
am_static_inline
void amhw_mci_int_enable_set (amhw_mci_t          *p_hw_mci,
                              amhw_mci_int_type_t  int_mask)
{
    p_hw_mci->mask0 |= int_mask;
}

/**
 * \brief ����ж����μĴ���  ������Ӧ���ж�λ
 *
 * \param[in] p_hw_mci   : ָ��MCI�Ĵ������ָ��
 * \param[in] int_mask   : ��Ҫ���ε��ж�λ     ���ò������μ�
 *                         \ref grp_amhw_mci_int_type "MCI INT MASK"
 *
 * \return ��
 */
am_static_inline
void amhw_mci_int_enable_clr (amhw_mci_t          *p_hw_mci,
                              amhw_mci_int_type_t  int_mask)
{
    p_hw_mci->mask0 &= ~int_mask;
}

/**
 * \brief ��ȡ�ж����μĴ���
 *
 * \param[in] p_hw_mci   : ָ��MCI�Ĵ������ָ��
 *
 * \return ʹ�ܵ��ж�λ���μ� \ref grp_amhw_mci_int_type "MCI INT MASK"
 */
am_static_inline
amhw_mci_int_type_t amhw_mci_int_mask_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->mask0;
}

/**
 * \brief ��ȡFIFO������
 *
 * \param[in] p_hw_mci   : ָ��MCI�Ĵ������ָ��
 *
 * \return FIFO����ֵ
 */
am_static_inline
uint16_t amhw_mci_fifocnt_get (amhw_mci_t *p_hw_mci)
{
    return p_hw_mci->fifocnt;
}

/**
 * \brief ����FIFO����
 *
 * \param[in] p_hw_mci   : ָ��MCI�Ĵ������ָ��
 * \param[in] chn        : ͨ��
 * \param[in] data       : Ҫд�������
 *
 * \return ��
 */
am_static_inline
void amhw_mci_fifodata_set (amhw_mci_t *p_hw_mci, uint32_t chn, uint32_t data)
{
    p_hw_mci->fifo[chn] = data;
}

/**
 * \brief ��ȡFIFO����
 *
 * \param[in] p_hw_mci   : ָ��MCI�Ĵ������ָ��
 * \param[in] chn        : ͨ��
 *
 * \return FIFO����
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
