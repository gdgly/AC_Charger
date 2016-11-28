/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief  USB�豸Ӳ�������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-11-03  cod, first implementation.
 * - 1.00 15-08-04  sam, first implementation.
 * \endinternal
 */

#ifndef __AMHW_USBD_H
#define __AMHW_USBD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_usbd
 * \copydoc amhw_usbd.h
 * @{
 */

/**
 * \brief USBD�Ĵ�����ṹ��
 */
typedef struct amhw_usbd {

    __I  uint32_t devintst;          /**< \brief �豸�ж�״̬�Ĵ���           */
    __IO uint32_t devinten;          /**< \brief �豸�ж�ʹ�ܼĴ���          */
    __O  uint32_t devintclr;         /**< \brief �豸�ж�����Ĵ���           */
    __O  uint32_t devintset;         /**< \brief �豸�ж�״̬�Ĵ���           */

    __O  uint32_t cmdcode;           /**< \brief �������Ĵ���           */
    __I  uint32_t cmddata;           /**< \brief �������ݼĴ���          */

    __I  uint32_t rxdata;            /**< \brief �������ݼĴ���           */
    __O  uint32_t txdata;            /**< \brief �������ݼĴ���          */
    __I  uint32_t rxplen;            /**< \brief ���հ����ȼĴ���           */
    __O  uint32_t txplen;            /**< \brief ���Ͱ����ȼĴ���           */
    __IO uint32_t ctrl;              /**< \brief ���ƼĴ���           */

    __O  uint32_t devintpri;         /**< \brief �豸�ж����ȼ��Ĵ���           */

    __I  uint32_t epintst;           /**< \brief �˵��ж�״̬�Ĵ���           */
    __IO uint32_t epinten;           /**< \brief �˵��ж�ʹ�ܼĴ���          */
    __O  uint32_t epintclr;          /**< \brief �˵��ж�����Ĵ���           */
    __O  uint32_t epintset;          /**< \brief �˵��ж����üĴ���          */
    __O  uint32_t epintpri;          /**< \brief �˵��ж����ȼ� �Ĵ���          */

    __IO uint32_t reep;              /**< \brief ʹ�ö˵�Ĵ���           */
    __O  uint32_t epind;             /**< \brief �˵������Ĵ���           */
    __IO uint32_t maxpsize;          /**< \brief �������ȼĴ���           */

    __I  uint32_t dmarst;            /**< \brief DMA����״̬�Ĵ���          */
    __O  uint32_t dmarclr;           /**< \brief DMA��������Ĵ���          */
    __O  uint32_t dmarset;           /**< \brief DMA�������üĴ���           */
         uint32_t reserved0[9];      /**< \brief ����         */
    __IO uint32_t udcah;             /**< \brief  UDCA Head�Ĵ���     */
    __I  uint32_t epdmast;           /**< \brief �˵�DMA״̬�Ĵ���          */
    __O  uint32_t epdmaen;           /**< \brief �˵�DMAʹ�ܼĴ���         */
    __O  uint32_t epdmadis;          /**< \brief �˵�DMA���ܼĴ���          */
    __I  uint32_t dmaintst;          /**< \brief DMA�ж�״̬�Ĵ���          */
    __IO uint32_t dmainten;          /**< \brief DMA�ж�ʹ�ܼĴ���          */
         uint32_t reserved1[2];      /**< \brief ����λ          */
    __I  uint32_t eotintst;          /**< \brief ��������ж�״̬�Ĵ���          */
    __O  uint32_t eotintclr;         /**< \brief ��������ж�����Ĵ���          */
    __O  uint32_t eotintset;         /**< \brief ��������ж����üĴ���          */
    __I  uint32_t nddrintst;         /**< \brief ��DD�����ж�״̬�Ĵ���          */
    __O  uint32_t nddrintclr;        /**< \brief ��DD�����ж�����Ĵ���          */
    __O  uint32_t nddrintset;        /**< \brief ��DD�����ж����üĴ���          */
    __I  uint32_t syserrintst;       /**< \brief ϵͳ�����ж�״̬�Ĵ���          */
    __O  uint32_t syserrintclr;      /**< \brief ϵͳ�����ж�����Ĵ���          */
    __O  uint32_t syserrintset;      /**< \brief ϵͳ�����ж����üĴ���          */
         uint32_t reserved2[844];    /**< \brief ����   */

    __IO uint32_t usbclkctrl;        /**< \brief  USB ʱ�ӿ��ƼĴ���           */
    __I  uint32_t usbclkst;          /**< \brief  USB ʱ��״̬�Ĵ���           */

} amhw_usbd_t;


/**
 * \name USB�˵�λ��־
 * \anchor grp_amhw_usbd_ep_bit
 * @{
 */

#define AMHW_USBD_BIT_EP(x)     (1 << x)   /**< \brief  �˵�λ          */

/** @} */

/**
 * \name USBʱ�ӿ���λ����
 * \anchor grp_amhw_usbd_clock_bit
 * @{
 */
#define AMHW_USBD_DEV_CLK      (1 << 1)  /**< \brief  �豸ʱ��          */
#define AMHW_USBD_PORTSEL_CLK  (1 << 3)  /**< \brief  �˿�ѡ��Ĵ���ʱ�ӣ�ֻ����LPC177x_8x�� */
#define AMHW_USBD_AHB_CLK      (1 << 4)  /**< \brief  AHBʱ��           */

/** @} */

/**
 * \name ����  USB�豸�ж�λ����
 * \anchor grp_amhw_usbd_interrupt_flag
 * @{
 */

#define AMHW_USBD_INT_FRAME        (1 << 0)  /**< \brief  ÿ��1ms����һ��֡�ж�           */
#define AMHW_USBD_INT_EP_FAST      (1 << 1)  /**< \brief  �˵�Ŀ����ж�           */
#define AMHW_USBD_INT_EP_SLOW      (1 << 2)  /**< \brief  �˵�������ж�           */
#define AMHW_USBD_INT_DEV_STAT     (1 << 3)  /**< \brief  USB���߸�λ��USB����ı�����Ӹı�ʱ��λ           */
#define AMHW_USBD_INT_CCEMPTY      (1 << 4)  /**< \brief  �������Ĵ�����USBCmdCode��Ϊ�գ���д���µ����          */
#define AMHW_USBD_INT_CDFULL       (1 << 5)  /**< \brief  �������ݼĴ�����USBCmdData�����������ڿ��Զ�ȡ���ݣ�           */
#define AMHW_USBD_INT_RXENDPKT     (1 << 6)  /**< \brief  �ڶ˵㻺�����еĵ�ǰ���ݰ��Ѵ��͸�CPU           */
#define AMHW_USBD_INT_TXENDPKT     (1 << 7)  /**< \brief  ���䵽�˵㻺�����������ֽ�����TxPacket���ȼĴ�����USBTxPLen���б���趨���ֽ������           */
#define AMHW_USBD_INT_EP_RLZED     (1 << 8)  /**< \brief  �˵㱻ʹ��          */
#define AMHW_USBD_INT_ERR          (1 << 9)  /**< \brief  �����ж�          */

/** @} */

/**
 * \name ����  USB�豸�ж����ȼ��Ĵ���
 * @{
 */

#define AMHW_USBD_FRAME_ENTER_HP   (1 << 0)  /**< \brief  FRAME�жϽ�����USB_INT_REQ_HP           */
#define AMHW_USBD_EPFAST_ENTER_HP  (1 << 1)  /**< \brief  EP_FAST�жϽ�����USB_INT_REQ_HP           */

/** @} */

/**
 * \name USB���ƼĴ���λ����
 * @{
 */

#define AMHW_USBD_RD_EN       (1 << 0)           /**< \brief  ��ģʽʹ��           */
#define AMHW_USBD_WR_EN       (1 << 1)           /**< \brief  дģʽʹ��           */

#define AMHW_USBD_LOG_EP(x)   (((x) >> 1) << 2)  /**< \brief �߼��˵����ã�xΪ����˵�       */

/** @} */

/**
 * \name USB���հ����ȼĴ���λ����
 * @{
 */

#define AMHW_USBD_RX_PKTLEN_MASK    0x3FF      /**< \brief  �˵�������ݳ�������           */
#define AMHW_USBD_RX_BIT_DV        (1 << 10)   /**< \brief  ������Чλ����          */
#define AMHW_USBD_RX_BIT_PKT_RDY   (1 << 11)   /**< \brief  ���ݰ�׼��λ����          */

/** @} */

/**
 * \name USB DMA�����ж�����
 * \anchor grp_amhw_usbd_dmaint_flag
 * @{
 */

#define AMHW_USBD_DMAINT_EOT      (1 << 0)  /**< \brief  DMA��������ж�          */
#define AMHW_USBD_DMAINT_NDDR     (1 << 1)  /**< \brief  �µ�DMA���������ж�    */
#define AMHW_USBD_DMAINT_SYSERR   (1 << 2)  /**< \brief  ϵͳ�����ж�           */

/** @} */

/**
 * \brief USBʱ��ʹ��
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] clk_flag    : ʱ��ʹ��λ,�μ�\ref grp_amhw_usbd_clock_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_clk_enable (amhw_usbd_t *p_hw_usbd, uint32_t clk_flag)
{
    p_hw_usbd->usbclkctrl = clk_flag;
}

/**
 * \brief USBʱ��ʧ��
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] clk_flag  : ʱ��ʹ��λ,�μ�\ref grp_amhw_usbd_clock_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_clk_disable (amhw_usbd_t *p_hw_usbd, uint32_t clk_flag)
{
    p_hw_usbd->usbclkctrl &= ~clk_flag;
}

/**
 * \brief USBʱ��״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return ʱ��״̬,�μ�\ref grp_amhw_usbd_clock_bit
 */
am_static_inline
uint32_t amhw_usbd_clkstat_get (amhw_usbd_t *p_hw_usbd)
{
    return p_hw_usbd->usbclkst;
}

/**
 * \brief USB�豸�ж�״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
uint32_t amhw_usbd_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->devintst;
}

/**
 * \brief USB�豸�ж�ʹ��
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag    : �ж�ʹ��λ,�μ�\ref grp_amhw_usbd_interrupt_flag
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_int_enable (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->devinten |= int_flag;
}

/**
 * \brief ��ȡʹ���豸�ж�
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return ʹ���ж�λ,�μ�\ref grp_amhw_usbd_interrupt_flag
 */
am_static_inline
uint32_t amhw_usbd_int_enable_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->devinten;
}

/**
 * \brief USB�豸�ж����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag    : �ж����λ,�μ�\ref grp_amhw_usbd_interrupt_flag
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_int_clr (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->devintclr = int_flag;
}

/**
 * \brief USB�豸�ж�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag    : �ж�����λ,�μ�\ref grp_amhw_usbd_interrupt_flag
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_int_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->devintset = int_flag;
}

/**
 * \brief USB�豸�ж����ȼ�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag    : �ж����ȼ�����λ,ֵΪ#AMHW_USBD_FRAME_ENTER_HP ��
 *                          #AMHW_USBD_EPFAST_ENTER_HP,�����λд0
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_intpri_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->devintpri |= int_flag;
}

/**
 * \brief USB�˵��ж�״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return �˵��ж�״̬
 */
am_static_inline
uint32_t amhw_usbd_ep_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->epintst;
}

/**
 * \brief USB�˵��ж�ʹ��
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] flag        : �˵�λ��־���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_ep_int_enable (amhw_usbd_t *p_hw_usbd, uint32_t flag)
{
    p_hw_usbd->epinten |= flag;
}

/**
 * \brief ʧ�ܶ˵��ģʽ�ж�
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] flag        : ʧ�ܱ�־���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_ep_int_disable (amhw_usbd_t *p_hw_usbd, uint32_t flag)
{
    p_hw_usbd->epinten &= ~flag;
}

/**
 * \brief USB�˵��ж����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag    : �˵��ж����λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_ep_int_clr (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->epintclr = int_flag;
}

/**
 * \brief USB�˵��ж�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag    : �˵��ж�����λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_ep_int_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->epintset = int_flag;
}

/**
 * \brief ָ���˵�˵��ж����ȼ�����λEP_FAST
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag    : �˵��ж����ȼ�����λ,���μ�\ref grp_amhw_usbd_ep_bit
 * \return ��
 */
am_static_inline
void amhw_usbd_intpri_epfast_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->epintpri = int_flag;
}

/**
 * \brief ָ���˵��ж����ȼ�����ΪEP_SLOW
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag  : �˵��ж����ȼ�����λ,���μ�\ref grp_amhw_usbd_ep_bit
 * \return ��
 */
am_static_inline
void amhw_usbd_intpri_epslow_set (amhw_usbd_t *p_hw_usbd, uint32_t int_flag)
{
    p_hw_usbd->epintpri &= ~int_flag;
}

/**
 * \brief USBʹ�ö˵�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_flag     : ʹ�ö˵�����λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_ep_use_set (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    p_hw_usbd->reep |= ep_flag;
}

/**
 * \brief ���ò���ʹ��ָ���˵�
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_flag     : ��ʹ�ö˵�����λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_ep_no_use_set (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    p_hw_usbd->reep &= ~ep_flag;
}


/**
 * \brief �˵���������
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep          : ����˵�ţ�ֵΪ0~31
 * \param[in] size        : ������С��ֵΪ0~1024���������ʵ�ʶ˵������
 *
 * \return ��
 */
void amhw_usbd_ep_maxpacksize_set (amhw_usbd_t *p_hw_usbd,
                                   uint8_t      ep,
                                   uint16_t     size);

/**
 * \brief �˵�DMA������������״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] dma_ep      : �˵�DMA����״̬λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ����״̬
 */
am_static_inline
uint32_t amhw_usbd_dmarst_stat_get (amhw_usbd_t *p_hw_usbd, uint32_t dma_ep)
{
    return (uint32_t)(p_hw_usbd->dmarst & dma_ep);
}


/**
 * \brief USB�˵�DMA�����������
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] dma_ep      : �˵�DMA���λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_dmarst_clr (amhw_usbd_t *p_hw_usbd, uint32_t dma_ep)
{
    p_hw_usbd->dmarclr = dma_ep;
}

/**
 * \brief USB�˵�DMA������������
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] int_flag    : �ж�����λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_dmarst_set (amhw_usbd_t *p_hw_usbd, uint32_t dma_ep)
{
    p_hw_usbd->dmarset = dma_ep;
}

/**
 * \brief USB UDCA Head ����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] udca_addr   : UDCA ��ַ
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_udcah_set (amhw_usbd_t *p_hw_usbd, uint32_t udca_addr)
{
    p_hw_usbd->udcah = udca_addr;
}

/**
 * \brief USB�˵�DMA״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_flag     : �˵�DMA״̬λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return �˵�DMA״̬���μ�\ref grp_amhw_usbd_ep_bit
 */
am_static_inline
uint32_t amhw_usbd_ep_dmastat_get (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    return (uint32_t)(p_hw_usbd->epdmast & ep_flag);
}

/**
 * \brief �˵�DMA����ʹ��
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_flag     : DMAʹ�ܶ˵��־���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_ep_dma_enable (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    p_hw_usbd->epdmaen = ep_flag;
}

/**
 * \brief �˵�DMA����ʧ��
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_flag     : �˵��ж����λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_ep_dma_disable (amhw_usbd_t *p_hw_usbd, uint32_t ep_flag)
{
    p_hw_usbd->epdmadis = ep_flag;
}

/**
 * \brief USB DMA  �ж�״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return DMA�ж�״̬���μ�\ref grp_amhw_usbd_dmaint_flag
 */
am_static_inline
uint32_t amhw_usbd_dmaint_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->dmaintst;
}

/**
 * \brief USB DMA �ж�ʹ��
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] dma_int     : DMA�ж�ʹ��λ���μ�\ref grp_amhw_usbd_dmaint_flag
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_dma_int_enable (amhw_usbd_t *p_hw_usbd, uint32_t dma_int)
{
    p_hw_usbd->dmainten |= dma_int;
}

/**
 * \brief USB ��������ж�״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return ��������ж�״̬
 */
am_static_inline
uint32_t amhw_usbd_eot_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->eotintst;
}


/**
 * \brief USB ��������ж�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] eot_ep      : ��������ж�����λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_eot_intstat_clr (amhw_usbd_t *p_hw_usbd, uint32_t eot_ep)
{
    p_hw_usbd->eotintclr = eot_ep;
}

/**
 * \brief USB��������ж���λ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] eot_ep      : ��������ж���λλ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_eot_intstat_set (amhw_usbd_t *p_hw_usbd, uint32_t eot_ep)
{
    p_hw_usbd->eotintset = eot_ep;
}

/**
 * \brief USB ��DD�����ж�״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] dd_ep       : USB ��DD�����ж�״̬λ
 *
 * \return USB ��DD�����ж�״̬
 */
am_static_inline
uint32_t amhw_usbd_nddr_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->nddrintst;
}


/**
 * \brief USB ��DD�����ж�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] dd_ep       : ��DD�����ж�����λ,�μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_nddr_intstat_clr (amhw_usbd_t *p_hw_usbd, uint32_t dd_ep)
{
    p_hw_usbd->nddrintclr = dd_ep;
}

/**
 * \brief USB��DD�����ж���λ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] dd_ep       : ��DD�����ж���λλ,�μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_nddr_intstat_set (amhw_usbd_t *p_hw_usbd, uint32_t dd_ep)
{
    p_hw_usbd->nddrintset = dd_ep;
}

/**
 * \brief USB ϵͳ�����ж�״̬��ȡ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return �˵�DMA����ϵͳ�����ж�״̬
 */
am_static_inline
uint32_t amhw_usbd_syserr_intstat_get (amhw_usbd_t *p_hw_usbd)
{
    return (uint32_t)p_hw_usbd->syserrintst;
}


/**
 * \brief USB ϵͳ�����ж�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] err_ep      : ϵͳ�����ж�����λ���μ�\ref grp_amhw_usbd_ep_bit
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_syserr_intstat_clr (amhw_usbd_t *p_hw_usbd, uint32_t err_ep)
{
    p_hw_usbd->syserrintclr = err_ep;
}

/**
 * \brief USBϵͳ�����ж���λ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] err_ep      : ϵͳ�����ж���λλ
 *
 * \return ��
 */
am_static_inline
void amhw_usbd_syserr_intstat_set (amhw_usbd_t *p_hw_usbd, uint32_t err_ep)
{
    p_hw_usbd->syserrintset = err_ep;
}

/*****************************************************************************
 *   SIE�������
 *****************************************************************************/
/**
 * \name SIE����
 * \anchor grp_amhw_sie_cmd
 * @{
 */

#define AMHW_CMD_SET_ADDR          0x00D00500                 /**< \brief ���õ�ַ          */
#define AMHW_CMD_CFG_DEV           0x00D80500                 /**< \brief �����豸          */
#define AMHW_CMD_SET_MODE          0x00F30500                 /**< \brief ����ģʽ          */
#define AMHW_CMD_RD_FRAME          0x00F50500                 /**< \brief ����ǰ֡��ţ���� */
#define AMHW_DAT_RD_FRAME          0x00F50200                 /**< \brief ����ǰ֡��ţ����ݣ� */
#define AMHW_CMD_RD_TEST           0x00FD0500                 /**< \brief �����ԼĴ�������� */
#define AMHW_DAT_RD_TEST           0x00FD0200                 /**< \brief �����ԼĴ��������ݣ�  */
#define AMHW_CMD_SET_DEV_STAT      0x00FE0500                 /**< \brief �����豸״̬�����  */
#define AMHW_CMD_GET_DEV_STAT      0x00FE0500                 /**< \brief ��ȡ�豸״̬�����  */
#define AMHW_DAT_GET_DEV_STAT      0x00FE0200                 /**< \brief �����豸״̬�����ݣ�  */
#define AMHW_CMD_GET_ERR_CODE      0x00FF0500                 /**< \brief ��ȡ������루���  */
#define AMHW_DAT_GET_ERR_CODE      0x00FF0200                 /**< \brief ��ȡ������루���ݣ�  */
#define AMHW_CMD_RD_ERR_STAT       0x00FB0500                 /**< \brief ������״̬�����  */
#define AMHW_DAT_RD_ERR_STAT       0x00FB0200                 /**< \brief �����״̬�����ݣ�  */
#define AMHW_DAT_WR_BYTE(x)       (0x00000100 | ((x) << 16))  /**< \brief ��/д����  */
#define AMHW_CMD_SEL_EP(x)        (0x00000500 | ((x) << 16))  /**< \brief ѡ��˵㣨���  */
#define AMHW_DAT_SEL_EP(x)        (0x00000200 | ((x) << 16))  /**< \brief ѡ��˵㣨���ݣ�  */
#define AMHW_CMD_SEL_EP_CLRI(x)   (0x00400500 | ((x) << 16))  /**< \brief ѡ��˵�/����жϣ����  */
#define AMHW_DAT_SEL_EP_CLRI(x)   (0x00400200 | ((x) << 16))  /**< \brief ѡ��˵�/����жϣ����ݣ�  */
#define AMHW_CMD_SET_EP_STAT(x)   (0x00400500 | ((x) << 16))  /**< \brief ���ö˵�״̬  */
#define AMHW_CMD_CLR_BUF           0x00F20500                 /**< \brief ��ջ����������  */
#define AMHW_DAT_CLR_BUF           0x00F20200                 /**< \brief ��ջ����������ݣ�  */
#define AMHW_CMD_VALID_BUF         0x00FA0500                 /**< \brief ȷ�ϻ�����  */

/** @} */

/**
 * \brief SIE��ȡһ�ֽ�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] cmd       : SIE����μ�\ref grp_amhw_sie_cmd
 *
 * \return ��
 */
uint8_t amhw_usbd_sie_data_get (amhw_usbd_t *p_hw_usbd, uint32_t cmd);

/**
 * \brief SIE��ȡһ�ֽ�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] cmd       : SIE����μ�\ref grp_amhw_sie_cmd
 * \param[in] data      : SIE���ݣ���������0
 *
 * \return ��
 */
void amhw_usbd_sie_cmd_send (amhw_usbd_t *p_hw_usbd, uint32_t cmd, uint32_t data);

/**
 * \brief ����USB�豸��ַ��ʹ���豸
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] addr      : �豸��ַ
 * \param[in] enable    : ʹ���豸λ
 *
 * \return ��
 */
void amhw_usbd_set_address_enable (amhw_usbd_t *p_hw_usbd,
                                   uint8_t      addr,
                                   bool_t       enable);

/**
 * \brief �����豸������ʹ�ܵ����ö˵��������Ӧ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] cfg       : �����豸
 *
 * \return ��
 */
void amhw_usbd_cfg_device_set (amhw_usbd_t *p_hw_usbd, bool_t cfg);

/**
 * \brief �����豸ģʽ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] mode      : �豸ģʽֵ
 *
 * \return ��
 */
void amhw_usbd_mode_set (amhw_usbd_t *p_hw_usbd, uint8_t mode);

/**
 * \brief ��ȡ��ǰ֡���
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return ��ǰ֡���
 */
uint16_t amhw_usbd_curframe_num_read (amhw_usbd_t *p_hw_usbd);

/**
 * \brief �����ԼĴ���
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return ��ȡ����ֵ����USBʱ�����У��򷵻�ֵΪ0xA50F
 */
uint16_t amhw_usbd_test_register_read (amhw_usbd_t *p_hw_usbd);

/**
 * \name USB�豸״̬λ����
 * @{
 */
#define AMHW_DEV_CON          (1 << 0)     /**< \brief ����λ��ʾ��ǰ�豸����״̬  */
#define AMHW_DEV_CON_CH       (1 << 1)     /**< \brief ���ӷ����ı�λ  */
#define AMHW_DEV_SUS          (1 << 2)     /**< \brief ����״̬λ  */
#define AMHW_DEV_SUS_CH       (1 << 3)     /**< \brief ����״̬�ı�λ  */
#define AMHW_DEV_RST          (1 << 4)     /**< \brief ���߸�λλ  */
/** @} */

/**
 * \brief �����豸״̬
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] status    �� �豸״̬��ֵΪAMHW_DEV_*��(#AMHW_DEV_CON)
 *
 * \return ��
 */
void amhw_usbd_device_status_set (amhw_usbd_t *p_hw_usbd, uint8_t status);

/**
 * \brief ��ȡ�豸״̬
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return �豸״̬��ֵΪAMHW_DEV_*��(#AMHW_DEV_CON)
 */
uint8_t amhw_usbd_device_status_get (amhw_usbd_t *p_hw_usbd);

/**
 * \brief ��ȡ�������
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return �������
 */
uint8_t amhw_usbd_err_code_get (amhw_usbd_t *p_hw_usbd);

/**
 * \name USB�豸״̬λ����
 * @{
 */
#define AMHW_ERR_PID_ERR     (1 << 0)     /**< \brief PID�������δ֪��PID��δ֪������CRC  */
#define AMHW_ERR_UEPKT       (1 << 1)     /**< \brief �������Ϣ�����κ�Υ���淶����Ϣ������ */
#define AMHW_ERR_DCRC        (1 << 2)     /**< \brief ����CRC����  */
#define AMHW_ERR_TIMEOUT     (1 << 3)     /**< \brief ��ʱ����  */
#define AMHW_ERR_EOP         (1 << 4)     /**< \brief ��Ϣ����������  */
#define AMHW_ERR_B_OVRN      (1 << 5)     /**< \brief ���������  */
#define AMHW_ERR_BTSTF       (1 << 6)     /**< \brief λ������  */
#define AMHW_ERR_TGL_ERR     (1 << 7)     /**< \brief ����PID�еĴ���תλ��toggle bit����������Ч  */
/** @} */

/**
 * \brief ��ȡ����״̬
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return ����״̬,ֵΪAMHW_ERR_*��(#AMHW_ERR_PID_ERR)
 */
uint8_t amhw_usbd_err_status_get (amhw_usbd_t *p_hw_usbd);


/**
 * \name USBѡ��˵�λ����
 * @{
 */
#define AMHW_EP_SEL_FE         (1 << 0)    /**< \brief �˵���/��λ  */
#define AMHW_EP_SEL_ST         (1 << 1)    /**< \brief ��ͣ�˵�ָʾλ  */
#define AMHW_EP_SEL_STP        (1 << 2)    /**< \brief SETUPλ */
#define AMHW_EP_SEL_PO         (1 << 3)    /**< \brief ������λ */
#define AMHW_EP_SEL_EPN        (1 << 4)    /**< \brief EP NAKλ */
#define AMHW_EP_SEL_B_1_FULL   (1 << 5)    /**< \brief ������1״̬λ */
#define AMHW_EP_SEL_B_2_FULL   (1 << 6)    /**< \brief ������2״̬λ */

/** @} */

/**
 * \brief ѡ��˵�
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_index  : ����˵��ţ�ֵΪ0~31
 *
 * \return �˵�״̬��Ϣ��ֵΪAMHW_EP_SEL_*��(#AMHW_EP_SEL)
 */
uint8_t amhw_usbd_endpoint_select (amhw_usbd_t *p_hw_usbd, uint8_t ep_index);

/**
 * \brief ѡ��˵�����жϲ����ض˵���Ϣ
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_index  : ����˵��ţ�ֵΪ0~31
 *
 * \return �˵�״̬��Ϣ��ֵΪAMHW_EP_SEL_*��(#AMHW_EP_SEL)
 */
uint8_t amhw_usbd_endpoint_select_int_clr (amhw_usbd_t *p_hw_usbd, uint8_t ep_index);


/**
 * \name USB�˵�״̬λ����
 * @{
 */
#define AMHW_EP_STAT_ST        (1 << 0)   /**< \brief ��ͣ�Ķ˵�λ  */
#define AMHW_EP_STAT_DA        (1 << 5)   /**< \brief ���ܶ˵�λ  */
#define AMHW_EP_STAT_RF_MO     (1 << 6)   /**< \brief ���ʷ���ģʽλ  */
#define AMHW_EP_STAT_CND_ST    (1 << 7)   /**< \brief ������ͣλ  */

/** @} */

/**
 * \brief ���ö˵�״̬
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_index  : ����˵��ţ�ֵΪ0~31
 * \param[in] status    : �˵�״̬,ֵΪAMHW_EP_STAT_*��(#AMHW_EP_STAT_ST)
 *
 * \return ��
 */
void amhw_usbd_endpoint_status_set (amhw_usbd_t *p_hw_usbd,
                                    uint8_t      ep_index,
                                    uint8_t      status);

/**
 * \brief ���OUT�˵㻺����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \retval           1  : ֮ǰ���յ�����Ϣ���������SETUP������
 * \retval           0  : ֮ǰ���յ�����Ϣ���������
 */
uint8_t amhw_usbd_buffer_clr (amhw_usbd_t *p_hw_usbd);

/**
 * \brief ȷ�ϻ�����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 *
 * \return ��
 */
void amhw_usbd_vaild_buffer (amhw_usbd_t *p_hw_usbd);

/*****************************************************************************
 * ��д�˵����
 *****************************************************************************/
/**
 * \brief ��ָ������˵�д������
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_index  : ����˵���
 * \param[in] p_buf     : ���ͻ�����ָ��
 * \param[in] len       : �������ݳ���
 *
 * \return ʵ�ʷ������ݳ���
 */
uint16_t amhw_usbd_endpoint_write (amhw_usbd_t    *p_hw_usbd,
                                   uint8_t         ep_index,
                                   const uint8_t  *p_buf,
                                   uint16_t        len);

/**
 * \brief ��ָ������˵��ȡ����
 *
 * \param[in] p_hw_usbd : ָ��USB�Ĵ������ָ��
 * \param[in] ep_index  : ����˵���
 * \param[in] p_buf     : ���ջ�����ָ��
 * \param[in] len       : �������ݳ���
 *
 * \return ʵ�ʽ������ݳ���
 */
uint16_t amhw_usbd_endpoint_read (amhw_usbd_t *p_hw_usbd,
                                  uint8_t      ep_index,
                                  uint8_t     *p_buf,
                                  uint16_t     len);

/*****************************************************************************
 * DMA������ز���
 *****************************************************************************/
/**
 * \brief DMA��������DD���ṹ�嶨��
 */
typedef struct amhw_usbd_dd {

    uint32_t    next;           /**< \brief �¸�DMA��������ʼ��ַ  */

    uint32_t    control;        /**< \brief DD(DMA������)������Ϣ */

    uint32_t    buf;            /**< \brief DMA��������ʼ��ַ  */

    uint32_t    status;         /**< \brief ״̬��Ϣ */

    uint32_t    iso_buf;        /**< \brief ͬ���˵�֡��ŵĻ�������ַ��ͬ���˵�ʹ�ã�  */

} amhw_usbd_dd_t;


/**
 * \name DD������Ϣ��ض���
 * @{
 */

#define AMHW_DD_MODE_NORMAL     (0 << 0)   /**< \brief  ����ģʽ            */
#define AMHW_DD_MODE_ATLE       (1 << 0)   /**< \brief  ATLEģʽ            */

#define AMHW_DD_NEXT_DD_VALID   (1 << 2)   /**< \brief �¸�DD��Ч            */

#define AMHW_DD_ISO_EP          (1 << 4)   /**< \brief ͬ���˵�λ            */

/** \brief �����Ϣ����С�����ã�            */
#define AMHW_DD_MAXPKT_SIZE(x)  (((x) & 0x7FF) << 5)

/** \brief DMA�����ֽ���/���������ã�  */
#define AMHW_DD_BUF_LEN(x)      (((x) & 0xFFFF) << 16)

/** @} */

/**
 * \name DD״̬��Ϣλ����
 * @{
 */

#define AMHW_DD_RETIRED              0x01  /**< \brief DDʹ�����־            */

#define AMHW_DD_STATUS_MASK          0x1F  /**< \brief ״̬����(��Retiredλ) */

#define AMHW_DD_STATUS_NOT_SERV      0x00  /**< \brief ָʾû�а�û����            */
#define AMHW_DD_STATUS_BEING_SERV    0x01  /**< \brief ָʾ������һ����������      */
#define AMHW_DD_STATUS_UNDER_RUN     0x03  /**< \brief ָʾ�յ��̰�����ֹ          */
#define AMHW_DD_STATUS_SYS_ERR       0x09  /**< \brief ָʾϵͳ���ߴ���            */
#define AMHW_DD_STATUS_OVER_RUN      0x11  /**< \brief ָʾ����������ĩβ����      */
#define AMHW_DD_STATUS_NORMAL_COMP   0x05  /**< \brief ָʾDMA������������         */

#define AMHW_DD_PACKET_VALID      (1 << 5) /**< \brief ����Ч������ͬ���˵㣩        */

/** \brief LS_byte_extracted,ATLEģʽ   */
#define AMHW_DD_LS_BYTE_EXTRACTED (1 << 6)

/** \brief MS_byte_extracted,ATLEģʽ   */
#define AMHW_DD_MS_BYTE_EXTRACTED (1 << 7)

/**< \brief Ƕ�뵽�������ݰ��е���Ϣ����λ�õ�ƫ����   */
#define AMHW_DD_MESS_LEN_POS(x)   (((x) & 0x3F) << 8)

/** \brief ��ǰDMA���䳤��        */
#define AMHW_DD_PRESENT_CNT(x)  (((x) >> 16) & 0x7FF)

/** @} */


/**
 *@}
 */

#ifdef __cplusplus
}
#endif

#endif /* AMHW_USBD_H_ */
