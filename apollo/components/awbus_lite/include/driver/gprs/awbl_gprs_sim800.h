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
 * \brief sim800 GPRS模块驱动
 *
 * \par 使用示例
 * \code
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.03 15-03-06  ops, add sms if for sim800.
 * - 1.02 15-01-23  ops, add signal strength if.
 * - 1.01 15-01-09  ops, redefine the architecture of sim800 driver.
 * - 1.00 14-12-15  afm, first implementation.
 * \endinternal
 */
#ifndef AW_GPRS_SIM800_H_
#define AW_GPRS_SIM800_H_

#include "aw_gprs.h"
#include "aw_sem.h"
#include "awbus_lite.h"
#include "aw_rngbuf.h"
#include "aw_mailbox.h"

#include "ppp/sio_mgn.h"
#include "ppp.h"

#define GPRS_INTERNAL_PROTOCOL					  /**< \brief 内部协议栈使能，注释后使用外部协议栈  */

#define GPRS_CMD_BUF_LEN      200                 /**< \brief 命令缓存长度    */
#ifdef GPRS_INTERNAL_PROTOCOL
#define GPRS_RSP_BUF_LEN      1500                /**< \brief 应答缓存长度    */
#else
#define GPRS_RSP_BUF_LEN      400                 /**< \brief 应答缓存长度    */
#endif

#define GPRS_IP_RCV_BUF_LEN	  2048				  /**< \brief GPRS内部协议栈接收环形队列缓存    */

#ifdef __cplusplus
extern "C" {
#endif

struct awbl_gprs_sim800_par {

	struct aw_gprs_par       gprs_par;

	int                      com;    	    /**< \brief com ID */
	uint32_t                 baud;    		/**< \brief baud rate */
	uint16_t                 pwren_gpio;	/**< \brief poweren gpio */
	uint16_t                 pwrkey_gpio;	/**< \brief power key gpio */
	uint16_t                 rst_gpio;		/**< \brief reset gpio */
	uint16_t                 ri_gpio;    	/**< \brief ri gpio  */

};

struct awbl_gprs_sim800_dev {

	struct awbl_dev              dev;

	struct aw_gprs_dev           gprs_dev;

	struct awbl_gprs_sim800_par  *p_sim_par;

	struct sio_mgn               serial_mgn;       /**< \brief sio管理 */

	int                          ppp_fd;           /**< \brief PPP句柄 */

	uint8_t                      ppp_state;        /**< \brief PPP连接状态 */

	AW_SEMC_DECL(sms_sem);                         /**< \brief 接收短信信号量  */

	AW_SEMC_DECL(event_sem);                       /**< \brief 事件信号量  */

	AW_SEMB_DECL(gprs_sem);						   /**< \brief GPRS操作互斥信号量  */

	struct ppp_addrs            *p_pppaddr;        /**< \brief PPP获取到的地址  */

	char at_cmd_buf[GPRS_CMD_BUF_LEN];			   /**< \brief AT命令缓存  */
	char at_rsp_buf[GPRS_RSP_BUF_LEN];			   /**< \brief AT应答缓存  */

	AW_MAILBOX_DECL(gprs_at_cmd_mailbox, 1);	   /**< \brief GPRS AT命令邮箱  */
	AW_MAILBOX_DECL(gprs_at_rsp_mailbox, 1);	   /**< \brief GPRS AT应答邮箱  */

#ifdef GPRS_INTERNAL_PROTOCOL
	uint8_t                      gprs_rcv_rngbuf_tmp[GPRS_IP_RCV_BUF_LEN];
	struct aw_rngbuf             gprs_rcv_rngbuf;  /**< \brief 内部协议栈接收环形队列 */

	AW_MAILBOX_DECL(gprs_snd_dat_mailbox, 1);	   /**< \brief GPRS发送数据邮箱  */
	AW_MAILBOX_DECL(gprs_snd_dat_rsp_mailbox, 1);  /**< \brief GPRS发送数据应答邮箱  */

	char                         gprs_rcv_dat_buf[GPRS_RSP_BUF_LEN];

	struct ppp_addrs             pppaddr;		  /**< \brief 内部协议栈的IP地址  */
#endif
};

/**
 * \brief sim800 GPRS模块构造函数
 *
 * \param p_sim_par  模块基本参数, 该参数不能为NULL, 否则构造失败
 */
struct aw_gprs_dev* awbl_gprs_sim800_ctor(struct awbl_gprs_sim800_dev  *p_sim,
	                                      struct awbl_gprs_sim800_par  *p_sim_par);

#ifdef __cplusplus
}
#endif


#endif /* AW_GPRS_SIM800_H_ */
