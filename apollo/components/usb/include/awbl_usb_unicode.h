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
 * \brief USB unicode support head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-05-11  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USB_UNICODE_H
#define __AWBL_USB_UNICODE_H


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

int awbl_usb_unicode_utf16s_to_utf8s (const uint16_t  *pwcs,
                                      int             inlen,
                                      uint8_t         *s,
                                      int             maxout);

int awbl_usb_unicode_utf8s_to_utf16s(const uint8_t   *s,
                                     int             len,
                                     uint16_t        *pwcs);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_USB_UNICODE_H_ */
