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
 * \file
 *
 * \brief 网络设备服务标准接口
 *
 *        本接口为Apollo应用程序提供访问网络底层设备的能力.
 *
 * 使用本服务需要包含以下头文件:
 * \code
 * #include "aw_net_if.h"
 * \endcode
 *
 * \par 使用示例
 *
 *  aw_const char ip_addr_set[] = "192.168.28.254";
 *  aw_const char mask_set[] = "255.255.255.0";
 *  aw_const char gateway_set[] = "192.168.28.1";
 *  uint8_t  hw_addr[6];
 *
 *  struct in_addr ip_addr_get, mask_get, gateway_get;
 *
 *  aw_netif_ipaddr_set("en0", ip_addr_set);
 *  aw_netif_ipaddr_get("en0", &ip_addr_get);
 *
 *  aw_netif_netmask_set("en0", mask_set);
 *  aw_netif_netmask_get("en0", &mask_get);
 *
 *  aw_netif_gateway_set("en0", gateway_set);
 *  aw_netif_gateway_get("en0", &gateway_get);
 *
 *  aw_netif_hwaddr_get("en0", hw_addr);
 *
 *  AW_INFOF(("\n"));
 *  AW_INFOF(("ip address is %s. \n", inet_ntoa(ip_addr_get)));
 *  AW_INFOF(("subnet mask is %s. \n", inet_ntoa(mask_get)));
 *  AW_INFOF(("gateway is %s. \n", inet_ntoa(gateway_get)));
 *  AW_INFOF(("mac addr is %02x-%02x-%02x-%02x-%02x-%02x. \n",
 *             hw_addr[0], hw_addr[1], hw_addr[2], hw_addr[3], hw_addr[4], hw_addr[5]));
 *  AW_INFOF(("\n"));
 *
 * \par 使用说明
 *
 * \internal
 * \par modification history
 * - 1.01 15-03-19  axn, add -ENODEV return value check, add aw_netif_hwaddr_get()
 * - 1.00 14-12-26  ops, first implementation
 * \endinternal
 */

#ifndef AW_NET_IF_H_
#define AW_NET_IF_H_

#include "apollo.h"
#include "netinet/in.h"
#include "arpa/inet.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief  获取指定网络设备的IP地址
 *
 * \param  p_ifname   网络设备名
 * \param  p_ipaddr   存放IP地址
 *
 * \return -EINVAL    p_ifname为空
 *                    p_ipaddr为空
 *         -ENODEV    设备不存在
 *         AW_OK      获取成功
 */
aw_err_t aw_netif_ipaddr_get(char *p_ifname, struct in_addr *p_ipaddr);

/**
 * \brief  设置指定网络设备的IP地址
 *
 * \param  p_ifname   网络设备名
 * \param  p_ipaddr   IP地址字符串
 *
 * \return -EINVAL    p_ifname为空
 *                    p_ipaddr为空
 *         -ENODEV    设备不存在
 *         AW_OK      设置成功
 */
aw_err_t aw_netif_ipaddr_set(char *p_ifname, aw_const char *p_ipaddr);

/**
 * \brief  获取指定网络设备的子网掩码
 *
 * \param  p_ifname   网络设备名
 * \param  p_netmask  存放子网掩码
 *
 * \return -EINVAL    p_ifname为空
 *                    p_netmask为空
 *         -ENODEV    设备不存在
 *         AW_OK      获取成功
 */
aw_err_t aw_netif_netmask_get(char *p_ifname, struct in_addr *p_netmask);

/**
 * \brief  设置指定网络设备的子网掩码
 *
 * \param  p_ifname   网络设备名
 * \param  p_netmask  子网掩码字符串
 *
 * \return -EINVAL    p_ifname为空
 *                    p_netmask为空
 *         -ENODEV    设备不存在
 *         AW_OK      设置成功
 */
aw_err_t aw_netif_netmask_set(char *p_ifname, aw_const char* p_netmask);

/**
 * \brief  获取指定网络设备的网关地址
 *
 * \param  p_ifname   网络设备名
 * \param  p_netmask  存放网关地址
 *
 * \return -EINVAL    p_ifname为空
 *                    p_gwaddr为空
 *         -ENODEV    设备不存在
 *         AW_OK      获取成功
 */
aw_err_t aw_netif_gateway_get(char *p_ifname, struct in_addr *p_gwaddr);

/**
 * \brief  设置指定网络设备的网关地址
 *
 * \param  p_ifname   网络设备名
 * \param  p_gwaddr   网关地址字符串
 *
 * \return -EINVAL    p_ifname为空
 *                    p_gwaddr为空
 *         -ENODEV    设备不存在
 *         AW_OK      设置成功
 */
aw_err_t aw_netif_gateway_set(char *p_ifname, aw_const char* p_gwaddr);

/**
 * \brief  获取指定网络设备的MAC地址
 *
 * \param  p_ifname   网络设备名
 * \param  p_netmask  存放MAC地址
 *
 * \return -EINVAL    p_ifname为空
 *                    p_hwaddr为空
 *         -ENODEV    设备不存在
 *         AW_OK      获取成功
 */
aw_err_t aw_netif_hwaddr_get(char *p_ifname, uint8_t *p_hwaddr);

#ifdef __cplusplus
}
#endif


#endif /* AW_NET_H_ */
