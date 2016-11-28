/*
 * awbl_hwconf_lpc17xx_can.h
 *
 *  Created on: 2015-09-01
 *      Author: anu
 */

#ifndef __AWBL_HWCONF_LPC17XX_CAN_H
#define __AWBL_HWCONF_LPC17XX_CAN_H

#include "ametal.h"

#define __CAN_DEV_CNT  2             /**< \brief CAN设备的个数 */
#define __CAN_ISR_CNT  __CAN_DEV_CNT /**< \brief CAN中断服务信息的个数 */

/** \brief CAN公共中断服务回调信息 */
static amdr_can_comm_isr_info_t __g_can_comm_isr_infos[__CAN_ISR_CNT];

/** \brief CAN公共设备信息 */
const  amdr_can_comm_devinfo_t  g_can_comm_devinfo = {
    AMHW_CANAF_RAM,                         /**< \brief CANAF_RAM 基址                   */
    AMHW_CANAF,                             /**< \brief CANAF 基址                              */
    AMHW_CANCR,                             /**< \brief CANCR 基址                              */
    INUM_CAN,                               /**< \brief CAN  中断号                            */
    __CAN_ISR_CNT,                          /**< \brief CAN 中断服务信息的个数 */
    __g_can_comm_isr_infos                  /**< \brief CAN  回调信息                        */
};

/** \brief CAN 公共设备实例 */
amdr_can_comm_dev_t g_can_comm_dev;

#endif /* __AWBL_HWCONF_LPC17XX_CAN_H */
/* end of file */

