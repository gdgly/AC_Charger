/*
 * awbl_hwconf_lpc17xx_can.h
 *
 *  Created on: 2015-09-01
 *      Author: anu
 */

#ifndef __AWBL_HWCONF_LPC17XX_CAN_H
#define __AWBL_HWCONF_LPC17XX_CAN_H

#include "ametal.h"

#define __CAN_DEV_CNT  2             /**< \brief CAN�豸�ĸ��� */
#define __CAN_ISR_CNT  __CAN_DEV_CNT /**< \brief CAN�жϷ�����Ϣ�ĸ��� */

/** \brief CAN�����жϷ���ص���Ϣ */
static amdr_can_comm_isr_info_t __g_can_comm_isr_infos[__CAN_ISR_CNT];

/** \brief CAN�����豸��Ϣ */
const  amdr_can_comm_devinfo_t  g_can_comm_devinfo = {
    AMHW_CANAF_RAM,                         /**< \brief CANAF_RAM ��ַ                   */
    AMHW_CANAF,                             /**< \brief CANAF ��ַ                              */
    AMHW_CANCR,                             /**< \brief CANCR ��ַ                              */
    INUM_CAN,                               /**< \brief CAN  �жϺ�                            */
    __CAN_ISR_CNT,                          /**< \brief CAN �жϷ�����Ϣ�ĸ��� */
    __g_can_comm_isr_infos                  /**< \brief CAN  �ص���Ϣ                        */
};

/** \brief CAN �����豸ʵ�� */
amdr_can_comm_dev_t g_can_comm_dev;

#endif /* __AWBL_HWCONF_LPC17XX_CAN_H */
/* end of file */

