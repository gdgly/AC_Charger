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
 * \brief USB EHCI memory
 *
 * \internal
 * \par modification history:
 * - 1.00 15-03-31  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USBH_EHCI_MEM_H
#define __AWBL_USBH_EHCI_MEM_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "host/controller/awbl_usbh_ehci.h"

/****************************************************************************/
aw_err_t awbl_usbh_ehci_mem_init (struct awbl_usbh_ehci *p_ehci);

/****************************************************************************/
struct awbl_usbh_ehci_qh *
awbl_usbh_ehci_qh_alloc (struct awbl_usbh_ehci *p_ehci);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_qh_free (
                struct awbl_usbh_ehci *p_ehci,
                struct awbl_usbh_ehci_qh *p_qh);

/****************************************************************************/
struct awbl_usbh_ehci_qtd *
awbl_usbh_ehci_qtd_alloc (struct awbl_usbh_ehci *p_ehci);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_qtd_free (
                struct awbl_usbh_ehci *p_ehci,
                struct awbl_usbh_ehci_qtd *p_qtd);

/****************************************************************************/
struct awbl_usbh_ehci_itd *
awbl_usbh_ehci_itd_alloc (struct awbl_usbh_ehci *p_ehci);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_itd_free (
                struct awbl_usbh_ehci *p_ehci,
                struct awbl_usbh_ehci_itd *p_itd);

/****************************************************************************/
struct awbl_usbh_ehci_sitd *
awbl_usbh_ehci_sitd_alloc (struct awbl_usbh_ehci *p_ehci);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_sitd_free (
                struct awbl_usbh_ehci *p_ehci,
                struct awbl_usbh_ehci_sitd *p_sitd);

/****************************************************************************/
void *awbl_usbh_ehci_periodic_addr (struct awbl_usbh_ehci *p_ehci);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_EHCI_MEM_H */
