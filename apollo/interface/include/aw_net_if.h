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
 * \brief �����豸�����׼�ӿ�
 *
 *        ���ӿ�ΪApolloӦ�ó����ṩ��������ײ��豸������.
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�:
 * \code
 * #include "aw_net_if.h"
 * \endcode
 *
 * \par ʹ��ʾ��
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
 * \par ʹ��˵��
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
 * \brief  ��ȡָ�������豸��IP��ַ
 *
 * \param  p_ifname   �����豸��
 * \param  p_ipaddr   ���IP��ַ
 *
 * \return -EINVAL    p_ifnameΪ��
 *                    p_ipaddrΪ��
 *         -ENODEV    �豸������
 *         AW_OK      ��ȡ�ɹ�
 */
aw_err_t aw_netif_ipaddr_get(char *p_ifname, struct in_addr *p_ipaddr);

/**
 * \brief  ����ָ�������豸��IP��ַ
 *
 * \param  p_ifname   �����豸��
 * \param  p_ipaddr   IP��ַ�ַ���
 *
 * \return -EINVAL    p_ifnameΪ��
 *                    p_ipaddrΪ��
 *         -ENODEV    �豸������
 *         AW_OK      ���óɹ�
 */
aw_err_t aw_netif_ipaddr_set(char *p_ifname, aw_const char *p_ipaddr);

/**
 * \brief  ��ȡָ�������豸����������
 *
 * \param  p_ifname   �����豸��
 * \param  p_netmask  �����������
 *
 * \return -EINVAL    p_ifnameΪ��
 *                    p_netmaskΪ��
 *         -ENODEV    �豸������
 *         AW_OK      ��ȡ�ɹ�
 */
aw_err_t aw_netif_netmask_get(char *p_ifname, struct in_addr *p_netmask);

/**
 * \brief  ����ָ�������豸����������
 *
 * \param  p_ifname   �����豸��
 * \param  p_netmask  ���������ַ���
 *
 * \return -EINVAL    p_ifnameΪ��
 *                    p_netmaskΪ��
 *         -ENODEV    �豸������
 *         AW_OK      ���óɹ�
 */
aw_err_t aw_netif_netmask_set(char *p_ifname, aw_const char* p_netmask);

/**
 * \brief  ��ȡָ�������豸�����ص�ַ
 *
 * \param  p_ifname   �����豸��
 * \param  p_netmask  ������ص�ַ
 *
 * \return -EINVAL    p_ifnameΪ��
 *                    p_gwaddrΪ��
 *         -ENODEV    �豸������
 *         AW_OK      ��ȡ�ɹ�
 */
aw_err_t aw_netif_gateway_get(char *p_ifname, struct in_addr *p_gwaddr);

/**
 * \brief  ����ָ�������豸�����ص�ַ
 *
 * \param  p_ifname   �����豸��
 * \param  p_gwaddr   ���ص�ַ�ַ���
 *
 * \return -EINVAL    p_ifnameΪ��
 *                    p_gwaddrΪ��
 *         -ENODEV    �豸������
 *         AW_OK      ���óɹ�
 */
aw_err_t aw_netif_gateway_set(char *p_ifname, aw_const char* p_gwaddr);

/**
 * \brief  ��ȡָ�������豸��MAC��ַ
 *
 * \param  p_ifname   �����豸��
 * \param  p_netmask  ���MAC��ַ
 *
 * \return -EINVAL    p_ifnameΪ��
 *                    p_hwaddrΪ��
 *         -ENODEV    �豸������
 *         AW_OK      ��ȡ�ɹ�
 */
aw_err_t aw_netif_hwaddr_get(char *p_ifname, uint8_t *p_hwaddr);

#ifdef __cplusplus
}
#endif


#endif /* AW_NET_H_ */
