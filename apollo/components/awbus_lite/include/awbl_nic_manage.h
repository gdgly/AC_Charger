/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief NIC(net interface card) MANAGE
 *
 * \internal
 * \par modification history
 * - 1.00 15-07-28  axn, first implementation
 * \endinternal
 */
#ifndef __AWBL_NIC_MANAGE_H
#define __AWBL_NIC_MANAGE_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "apollo.h"
#include "awbus_lite.h"
#include "aw_types.h"

typedef enum {

	AWBL_ETHERNET_NIC = 1,
	AWBL_WIRELESS_NIC_STA,
	AWBL_WIRELESS_NIC_AP,
	AWBL_WIRELESS_NIC_P2P,

} awbl_nic_type_t;

typedef struct awbl_nic {

	awbl_dev_t      *p_nic_dev;
	char            *p_nic_name; /* Íø¿¨Ãû×Ö           */
	char            *p_nic_info; /* Íø¿¨ÃèÊöÐÅÏ¢ */
	awbl_nic_type_t  nic_type;   /* Íø¿¨ÀàÐÍ */
	struct awbl_nic *p_next;

} awbl_nic_t;

aw_err_t    awbl_nic_add(awbl_nic_t *p_nic);
aw_err_t    awbl_nic_remove(awbl_nic_t *p_nic);
aw_err_t    awbl_nic_remove_by_name(char *p_nic_name);
awbl_nic_t *awbl_find_nic_by_name(char *p_nic_name);
int         awbl_get_nic_num(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AWBL_NIC_MANAGE_H */


/* end of file */


