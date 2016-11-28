/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief USB descriptor define head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-04-04  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USB_CFG_H
#define __AWBL_USB_CFG_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/* common */
#if (AW_CPU_ENDIAN == AW_BIG_ENDIAN)
#define AWBL_USB_CPU_TO_LE32(x) \
            x = ((((x) & 0xff000000) >> 24) | \
             (((x) & 0x00ff0000) >> 8) | \
             (((x) & 0x0000ff00) << 8) | (((x) & 0x000000ff) << 24))

#define AWBL_USB_CPU_TO_LE16(x) \
            x =(uint16_t) ((((x) & 0xff00) >> 8) | (((x) & 0x00ff) << 8))
#else
#define AWBL_USB_CPU_TO_LE32(x) (x)
#define AWBL_USB_CPU_TO_LE16(x) (x)
#endif

#define AWBL_USB_LE_WRITE32(val, addr)    writel(AWBL_USB_CPU_TO_LE32(val), \
                                                (volatile void __iomem *)(addr))
#define AWBL_USB_LE_READ32(addr)          AWBL_USB_CPU_TO_LE32( \
                                            readl((volatile void __iomem *)(addr)))

#define AW_USB_CPU_CACHE_VALID          1


//#define AWBL_USB_USB_MEM_DEBUG

/* host */
#define AWBL_USBH_MAX_CHILDREN          (31)
#define AWBL_USBH_ROOT_HUB_ADDRESS      (1)
#define AWBL_USBH_MAX_EP_NUM            (32)
#define AWBL_USBH_MAX_CONFIG            (8)
#define AWBL_USBH_MAX_INTERFACES        (32)
#define AWBL_USBH_MAX_IADS              (AWBL_USBH_MAX_INTERFACES/2)
#define AWBL_USBH_MAX_ALTSETTING        128

//#define AWBL_USBH_HUB_DEBUG
#define AWBL_USBH_HUB_TASK_PRIO         6
#define AWBL_USBH_HUB_TASK_STACK_SIZE   4096
#define AWBL_USBH_HUB_MSG_MAX           20

//#define AWBL_USBH_EHCI_MEM_DEBUG
#define AWBL_USBH_EHCI_FRAME_LIST_SIZE  (1024)  /* 1024(4K), 512(2K), 256(1K) */
#define AWBL_USBH_EHCI_TASK_STACK_SIZE  (8192)
#define AWBL_USBH_EHCI_UFRAME_BANDWIDTH (100)   /* 一个微帧的带宽，125*80% us */
#define AWBL_USBH_EHCI_BANDWIDTH_SIZE   (80)    /* 存储微帧带宽的数量，同时也是最小的周期 */
#define AWBL_USBH_EHCI_TUNE_CERR        3       /* 0-3 qtd retries; 0 == don't stop */
#define AWBL_USBH_EHCI_TUNE_RL_HS       4       /* nak throttle; see 4.9 */
#define AWBL_USBH_EHCI_TUNE_RL_TT       0
#define AWBL_USBH_EHCI_TUNE_MULT_HS     1       /* 1-3 transactions/uframe; 4.10.3 */
#define AWBL_USBH_EHCI_TUNE_MULT_TT     1

//#define AWBL_USBH_OHCI_MEM_DEBUG

#define AWBL_USBH_OHCI_TASK_STACK_SIZE  (8192)

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_USB_CFG_H_ */
