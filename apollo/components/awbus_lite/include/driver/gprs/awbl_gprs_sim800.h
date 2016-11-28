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
 * \brief sim800 GPRSģ������
 *
 * \par ʹ��ʾ��
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

#define GPRS_INTERNAL_PROTOCOL					  /**< \brief �ڲ�Э��ջʹ�ܣ�ע�ͺ�ʹ���ⲿЭ��ջ  */

#define GPRS_CMD_BUF_LEN      200                 /**< \brief ����泤��    */
#ifdef GPRS_INTERNAL_PROTOCOL
#define GPRS_RSP_BUF_LEN      1500                /**< \brief Ӧ�𻺴泤��    */
#else
#define GPRS_RSP_BUF_LEN      400                 /**< \brief Ӧ�𻺴泤��    */
#endif

#define GPRS_IP_RCV_BUF_LEN	  2048				  /**< \brief GPRS�ڲ�Э��ջ���ջ��ζ��л���    */

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

	struct sio_mgn               serial_mgn;       /**< \brief sio���� */

	int                          ppp_fd;           /**< \brief PPP��� */

	uint8_t                      ppp_state;        /**< \brief PPP����״̬ */

	AW_SEMC_DECL(sms_sem);                         /**< \brief ���ն����ź���  */

	AW_SEMC_DECL(event_sem);                       /**< \brief �¼��ź���  */

	AW_SEMB_DECL(gprs_sem);						   /**< \brief GPRS���������ź���  */

	struct ppp_addrs            *p_pppaddr;        /**< \brief PPP��ȡ���ĵ�ַ  */

	char at_cmd_buf[GPRS_CMD_BUF_LEN];			   /**< \brief AT�����  */
	char at_rsp_buf[GPRS_RSP_BUF_LEN];			   /**< \brief ATӦ�𻺴�  */

	AW_MAILBOX_DECL(gprs_at_cmd_mailbox, 1);	   /**< \brief GPRS AT��������  */
	AW_MAILBOX_DECL(gprs_at_rsp_mailbox, 1);	   /**< \brief GPRS ATӦ������  */

#ifdef GPRS_INTERNAL_PROTOCOL
	uint8_t                      gprs_rcv_rngbuf_tmp[GPRS_IP_RCV_BUF_LEN];
	struct aw_rngbuf             gprs_rcv_rngbuf;  /**< \brief �ڲ�Э��ջ���ջ��ζ��� */

	AW_MAILBOX_DECL(gprs_snd_dat_mailbox, 1);	   /**< \brief GPRS������������  */
	AW_MAILBOX_DECL(gprs_snd_dat_rsp_mailbox, 1);  /**< \brief GPRS��������Ӧ������  */

	char                         gprs_rcv_dat_buf[GPRS_RSP_BUF_LEN];

	struct ppp_addrs             pppaddr;		  /**< \brief �ڲ�Э��ջ��IP��ַ  */
#endif
};

/**
 * \brief sim800 GPRSģ�鹹�캯��
 *
 * \param p_sim_par  ģ���������, �ò�������ΪNULL, ������ʧ��
 */
struct aw_gprs_dev* awbl_gprs_sim800_ctor(struct awbl_gprs_sim800_dev  *p_sim,
	                                      struct awbl_gprs_sim800_par  *p_sim_par);

#ifdef __cplusplus
}
#endif


#endif /* AW_GPRS_SIM800_H_ */
