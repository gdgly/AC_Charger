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
 * @brief net interface none volatile information.
 *
 * @internal
 * @par History
 * - 15-01-08, axn, add dns and dhcp interface
 * - 13-04-23, orz, first implementation.
 * @endinternal
 */

#ifndef __IDRV_NETIF_NVINFO_H /* { */
#define __IDRV_NETIF_NVINFO_H

#include "aw_types.h"
#include "lwip/ip_addr.h"

/**
 * @name Net interface hard address and IP address management
 *  The hard address and IP address are stored in NVRAM
 * @{
 */

#define NETIF_IPADDR_STR        "ipaddr"
#define NETIF_NETMASK_STR       "netmask"
#define NETIF_GATEWAY_STR       "gateway"
#define NETIF_DNS0_STR          "dns0"
#define NETIF_DNS1_STR          "dns1"
#define NETIF_DHCP_STR          "dhcp"

int netif_hwaddr_get(const char *p_name, uint_t if_unit, uint8_t       *hwaddr, uint_t hwaddr_len);
int netif_hwaddr_set(const char *p_name, uint_t if_unit, const uint8_t *hwaddr, uint_t hwaddr_len);

int netif_ipaddr_get(uint_t if_unit, ip_addr_t       *ipaddr);
int netif_ipaddr_set(uint_t if_unit, const ip_addr_t *ipaddr);

int netif_netmask_get(uint_t if_unit, ip_addr_t       *ipaddr);
int netif_netmask_set(uint_t if_unit, const ip_addr_t *ipaddr);

int netif_gateway_get(uint_t if_unit, ip_addr_t       *ipaddr);
int netif_gateway_set(uint_t if_unit, const ip_addr_t *ipaddr);

int netif_dns0_get(uint_t if_unit, ip_addr_t       *ipaddr);
int netif_dns0_set(uint_t if_unit, const ip_addr_t *ipaddr);
int netif_dns1_get(uint_t if_unit, ip_addr_t       *ipaddr);
int netif_dns1_set(uint_t if_unit, const ip_addr_t *ipaddr);

int netif_dhcp_get(uint_t if_unit, uint8_t *en);
int netif_dhcp_set(uint_t if_unit, uint8_t en);

/** @} */

#endif /* } __IDRV_NETIF_NVINFO_H */

/* end of file */
