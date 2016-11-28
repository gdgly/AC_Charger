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
 * \brief USB OHCI controller memory manage file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-09-19  deo, first implementation
 * \endinternal
 */


#ifndef __AWBL_USBH_OHCI_MEM_H
#define __AWBL_USBH_OHCI_MEM_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "host/controller/awbl_usbh_ohci.h"

aw_err_t awbl_usbh_ohci_mem_init (struct awbl_usbh_ohci *p_ohci);

void awbl_usbh_ohci_mem_uninit (struct awbl_usbh_ohci *p_ohci);

struct awbl_usbh_ohci_ed *
awbl_usbh_ohci_ed_alloc (struct awbl_usbh_ohci *p_ohci);

aw_err_t awbl_usbh_ohci_ed_free (struct awbl_usbh_ohci    *p_ohci,
                                 struct awbl_usbh_ohci_ed *p_ed);

struct awbl_usbh_ohci_td *
awbl_usbh_ohci_td_alloc (struct awbl_usbh_ohci *p_ohci);

aw_err_t awbl_usbh_ohci_td_free (struct awbl_usbh_ohci    *p_ohci,
                                 struct awbl_usbh_ohci_td *p_td);

struct awbl_usbh_ohci_otrp *
awbl_usbh_ohci_otrp_alloc (struct awbl_usbh_ohci *p_ohci);

aw_err_t awbl_usbh_ohci_otrp_free (struct awbl_usbh_ohci      *p_ohci,
                                   struct awbl_usbh_ohci_otrp *p_otrp);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_OHCI_MEM_H */
