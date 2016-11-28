/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * @file
 * @brief Network initializing interface.
 *
 * @internal
 * @par History
 * - 13-04-02, orz, first implementation.
 * @endinternal
 */

#ifndef __IRON_NET_H /* { */
#define __IRON_NET_H

void net_init (void);
void net_shell_init (void);

void ethernet_if_lib_init (void *err);

#endif /* } __IRON_NET_H */

/* end of file */
