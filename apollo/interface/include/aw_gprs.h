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
 * \brief ͨ��GPRS����
 *
 * \par ʹ��ʾ��
 * \code
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.03 15-03-06  ops, add sms if and aw_gprs_sms_data.
 * - 1.02 15-01-23  ops, add signal strength if.
 * - 1.01 15-01-09  ops, create the gprs abstract class, and redefine the std if.
 * - 1.00 14-12-15  afm, first implementation.
 * \endinternal
 */

#ifndef AW_GPRS_H_
#define AW_GPRS_H_

#include "apollo.h"
#include "aw_types.h"

#include "arpa/inet.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief GPRSģ��������  */
#define	AW_GPRS_OK       		(0)   	/**< \brief �����ɹ�   */
#define	AW_GPRS_FAIL			(-1)	/**< \brief ����ʧ��   */
#define	AW_GPRS_NO_SIM			(-2)	/**< \brief �Ҳ���SIM��  */
#define	AW_GPRS_CSQ_LOW			(-3)	/**< \brief �ź�ǿ����  */
#define	AW_GPRS_REG_FAIL		(-4)	/**< \brief ע��ʧ��  */
#define	AW_GPRS_NO_RSP			(-5)	/**< \brief ģ������Ӧ  */
#define	AW_GPRS_RSP_ERR			(-6)	/**< \brief ģ��Ӧ�����  */
#define	AW_GPRS_PARA_ERR		(-7)	/**< \brief ģ��������ô���  */

/** \brief ���յĶ��ű�������  */
#define AW_SMS_CODE_GB			(0)		/**< \brief GB�������   */
#define AW_SMS_CODE_HEX			(1)		/**< \brief HEX�������  */

/** \brief GPRS����ģʽ  */
#define AW_GPRS_TCP_MODE		(0)		/**< \brief TCP����ģʽ   */
#define AW_GPRS_UDP_MODE		(1)		/**< \brief UDP����ģʽ   */

/** \brief GPRSģ���������  */
struct aw_gprs_par
{
	char *p_dial_num;					/**< \brief ����ҵ�񲦺ź���   */
	char *p_apn;						/**< \brief APN����   */
	char *p_user;						/**< \brief APN�û���   */
	char *p_password;					/**< \brief APN����   */
	char *p_center_num;					/**< \brief ����Ϣ���ĺ���   */

	void (*pfn_sms_int_cb)(void);       /**< \brief ���Ž����жϻص�����, �ú�������֪ͨ�û����յ�����Ϣ */
};

/** \brief GPRSģ����ն��Žṹ  */
struct aw_gprs_sms_data
{
	char     *p_sms_buff;				/**< \brief �������ݻ���   */
	uint16_t  sms_buff_len;				/**< \brief �������ݻ��泤��   */

	char     *p_num_buff;				/**< \brief �ֻ��������ݻ���   */
	uint16_t  num_buff_len;				/**< \brief �ֻ��������ݻ��泤��   */

	char     *p_time_buff;				/**< \brief ʱ�����ݻ���   */
	uint16_t  time_buff_len;			/**< \brief ʱ�����ݻ��泤��   */

	uint8_t   sms_code;				 	/**< \brief ���ű���   */
};


struct aw_gprs_dev {

	struct aw_gprs_par       *p_gprs_par;

	struct aw_gprs_sms_data  *p_sms_par;

	/**
	 * \brief �Ƿ񲦺�����
	 */
	uint8_t              online;

	/**
	 * \brief �Ƿ�������״̬
	 */
	uint8_t              cmd_state;

	/**
	 * \brief GPRSģ�鿪���ӿ�
	 */
	void (*pfn_gprs_power_on)(struct aw_gprs_dev *p_this);

	/**
	 * \brief GPRSģ��ػ��ӿ�
	 */
	void (*pfn_gprs_power_off)(struct aw_gprs_dev *p_this);

	/**
	 * \brief GPRSģ���ʼ���ӿ�
	 */
	aw_err_t (*pfn_gprs_init)(struct aw_gprs_dev *p_this);

	/**
	 * \brief GPRSģ���ź�ǿ�Ȼ�ȡ�ӿ�
	 */
	aw_err_t (*pfn_gprs_csq_get)(struct aw_gprs_dev *p_this, uint8_t *p_csq);

	/**
	 * \brief ��ȡGPRSģ��CCID�ӿ�
	 */
	aw_err_t (*pfn_gprs_ccid_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief PPP���Žӿ�
	 */
	aw_err_t (*pfn_gprs_ppp_open)(struct aw_gprs_dev *p_this);

	/**
	 * \brief PPP���Źرսӿ�
	 */
	aw_err_t (*pfn_gprs_ppp_close)(struct aw_gprs_dev *p_this);

	/**
	 * \brief PPP���ŵ�IP��ַ��ȡ�ӿ�
	 */
	aw_err_t (*pfn_gprs_pppif_ip_get)(struct aw_gprs_dev *p_this,
			                          struct in_addr     *p_ipaddr);

	/**
	 * \brief ���ŷ��ͽӿ�
	 */
	aw_err_t (*pfn_gprs_sms_send)(struct aw_gprs_dev *p_this,
			                      char               *p_sms,
			                      char               *p_num);

	/**
	 * \brief HEX���ŷ��ͽӿ�
	 */
	aw_err_t (*pfn_gprs_sms_hex_send)(struct aw_gprs_dev *p_this,
							          uint8_t            *p_sms,
							          uint8_t             len,
							          char               *p_num);

	/**
	 * \brief ���Ž��սӿ�
	 */
	aw_err_t (*pfn_gprs_sms_recv)(struct aw_gprs_dev      *p_this,
			                      struct aw_gprs_sms_data *p_sms,
			                      uint32_t                 timeout);

	/**
	 * \brief ɾ��ȫ������
	 */
	aw_err_t (*pfn_gprs_all_sms_del)(struct aw_gprs_dev *p_this);

	/**
	 * \brief ��ȡGPRSģ��İ汾��
	 */
	aw_err_t (*pfn_gprs_module_revision_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief ��ȡGPRSģ���IMEI��
	 */
	aw_err_t (*pfn_gprs_module_imei_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief ��ȡGPRSģ���IMSI��
	 */
	aw_err_t (*pfn_gprs_module_imsi_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief ��ȡGPRSģ��Ķ���Ϣ���ĺ���
	 */
	aw_err_t (*pfn_gprs_module_sca_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief ����GPRS����
	 */
    aw_err_t (*pfn_gprs_ip_start)(struct aw_gprs_dev *p_this, uint8_t mode, char *p_ip, uint16_t port, uint32_t timeout);

	/**
	 * \brief �ر�GPRS����
	 */
    aw_err_t (*pfn_gprs_ip_close)(struct aw_gprs_dev *p_this);

	/**
	 * \brief ����GPRS����
	 */
    ssize_t (*pfn_gprs_ip_send)(struct aw_gprs_dev *p_this, void *p_data, size_t len, uint32_t timeout);

	/**
	 * \brief ����GPRS����
	 */
    ssize_t (*pfn_gprs_ip_receive)(struct aw_gprs_dev *p_this, void *p_buf, size_t len);

	/**
	 * \brief ��ȡGPRS����״̬
	 */
    aw_err_t (*pfn_gprs_ip_get_status)(struct aw_gprs_dev *p_this);
};

/**
 * \brief GPRSģ�鿪��
 *
 * ��GPRSģ���Դ��������
 *
 * \param  p_this  ��ǰģ��
 *
 * \retval ��
 */
aw_local aw_inline void aw_gprs_power_on (struct aw_gprs_dev *p_this)
{
	p_this->pfn_gprs_power_on(p_this);
}

/**
 * \brief GPRSģ��ػ�
 *
 * GPRSģ��ػ����ص�ģ���Դ
 *
 * \param  p_this  ��ǰģ��
 *
 * \retval ��
 *
 */
aw_local aw_inline void aw_gprs_power_off(struct aw_gprs_dev *p_this)
{
	p_this->pfn_gprs_power_off(p_this);
}

/**
 * \brief ��ʼ��GPRSģ��
 *
 * ��������ʼ��GPRSģ�飬ִ��ʱ��Ƚϳ���ִ��ʱ��������ź��й�
 *
 * \param  p_this  ��ǰģ��
 *
 * \retval AW_OK   �ɹ�
 *
 */
aw_local aw_inline aw_err_t aw_gprs_init(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_init(p_this);
}

/**
 * \brief ��ȡGPRSģ����ź�ǿ��
 *
 *  ��ȡ�����ź�ǿ�ȷ�ΧΪ0~31, ��99.
 *  0~31�ܼ�⵽�ź�ǿ��, 0Ϊ����, 31Ϊ��ǿ. 99���ܼ�⵽�ź�ǿ��
 *
 *  ����״̬�»�ȡ�ź�ǿ��, �п��ܻᵼ������Ͽ�
 *
 * \param   p_this  ��ǰģ��
 * \param   p_csq   ��ȡ���ź�ǿ��
 *
 * \retval  AW_OK   �ɹ�
 *
 */
aw_local aw_inline aw_err_t aw_gprs_csq_get(struct aw_gprs_dev *p_this, uint8_t *p_csq)
{
	return p_this->pfn_gprs_csq_get(p_this, p_csq);
}

/**
 * \brief ��ȡGPRSģ���CCID
 *
 * ����״̬�»�ȡCCID���п��ܻᵼ������Ͽ�
 *
 * \param   p_this   ��ǰģ��
 * \param   p_buf    ��Ż�ȡ��CCID�Ļ���
 * \param   nbytes   �����С
 *
 * \retval  AW_OK    �ɹ�
 *
 */
aw_local aw_inline aw_err_t aw_gprs_ccid_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_ccid_get(p_this, p_buf, nbytes);
}

/**
 * \brief PPP���Žӿڣ��ⲿЭ��ջ��
 *
 * ִ��PPP���ţ����ų�ʱΪ30s
 *
 * \param  p_this  ��ǰģ��
 *
 * \retval AW_OK   �ɹ�
 *
 */
aw_local aw_inline aw_err_t aw_gprs_ppp_open(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_ppp_open(p_this);
}

/**
 * \brief PPP���Źرգ��ⲿЭ��ջ��
 *
 * ������ִ��PPP���Źر�
 *
 * \param  p_this  ��ǰģ��
 *
 * \retval AW_OK   �ɹ�
 *
 */
aw_local aw_inline aw_err_t aw_gprs_ppp_close(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_ppp_close(p_this);
}

/**
 * \brief ��ȡPPP���ŵ�IP��ַ
 *
 * \param  p_this   ��ǰģ��
 * \param  p_ipaddr ���IP��ַ
 *
 * \retval -EINVAL  p_gprsΪ��
 *                  p_ipaddrΪ��
 *         AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_pppif_ip_get(struct aw_gprs_dev *p_this,
			                                     struct in_addr     *p_ipaddr)
{
	return p_this->pfn_gprs_pppif_ip_get(p_this, p_ipaddr);
}

/**
 * \brief ���ŷ���
 *
 * \param  p_this   ��ǰģ��
 * \param  p_sms    ��������
 * \param  p_num    �ֻ�����
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_sms_send(struct aw_gprs_dev *p_this,
		                                     char               *p_sms,
		                                     char               *p_num)
{
	return p_this->pfn_gprs_sms_send(p_this, p_sms, p_num);
}

/**
 * \brief HEX���ŷ���
 *
 * \param  p_this   ��ǰģ��
 * \param  p_sms    ��������
 * \param  len		�������ݳ���
 * \param  p_num    �ֻ�����
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_sms_hex_send(struct aw_gprs_dev *p_this,
		                                         uint8_t            *p_sms,
		                                         uint8_t			 len,
		                                         char               *p_num)
{
	return p_this->pfn_gprs_sms_hex_send(p_this, p_sms, len, p_num);
}

/**
 * \brief ���Ž���
 *
 * \param  p_this   ��ǰģ��
 * \param  p_sms    ��������
 * \param  p_num    �ֻ�����
 * \param  p_time   ���յ����ŵ�ʱ��
 *
 * \retval > 0     ����ʣ����ſ��Լ�������
 *         = 0     ���Ž������
 *         = -1    ���Ž���ʧ��
 */
aw_local aw_inline aw_err_t aw_gprs_sms_recv(struct aw_gprs_dev      *p_this,
		                                     struct aw_gprs_sms_data *p_sms,
		                                     uint32_t                 timeout)
{
	return p_this->pfn_gprs_sms_recv(p_this, p_sms, timeout);
}

/**
 * \brief ɾ��ȫ������
 *
 * \param  p_this   ��ǰģ��
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_all_sms_del(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_all_sms_del(p_this);
}

/**
 * \brief ��ȡGPRSģ��İ汾��
 *
 * \param  p_this   ��ǰģ��
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_module_revision_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_module_revision_get(p_this, p_buf, nbytes);
}

/**
 * \brief ��ȡGPRSģ���IMEI��
 *
 * \param  p_this   ��ǰģ��
 * \param  p_buf    ��Ż�ȡ��IMEI�Ļ���
 * \param  p_buf    �����С
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_module_imei_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_module_imei_get(p_this, p_buf, nbytes);
}

/**
 * \brief ��ȡGPRSģ���IMSI��
 *
 * \param  p_this   ��ǰģ��
 * \param  p_buf    ��Ż�ȡ��IMSI�Ļ���
 * \param  p_buf    �����С
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_module_imsi_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_module_imsi_get(p_this, p_buf, nbytes);
}

/**
 * \brief ��ȡGPRSģ��Ķ���Ϣ���ĺ���
 *
 * \param  p_this   ��ǰģ��
 * \param  p_buf    ��Ż�ȡ������Ϣ���ĺ���Ļ���
 * \param  p_buf    �����С
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_module_sca_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_module_sca_get(p_this, p_buf, nbytes);
}

/**
 * \brief ����GPRS���ӣ��ڲ�Э��ջ��
 *
 * \param  p_this   ��ǰģ��
 * \param  mode     ģʽTCP��UDP
 * \param  p_ip     ���ӷ�������IP��ַ������
 * \param  p_port   ���ӷ������Ķ˿ں�
 * \param  timeout  ��ʱʱ�䣬��λΪ��
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_ip_start(struct aw_gprs_dev *p_this, uint8_t mode, char *p_ip, uint16_t port, uint32_t timeout)
{
	return p_this->pfn_gprs_ip_start(p_this, mode, p_ip, port, timeout);
}

/**
 * \brief �ر�GPRS���ӣ��ڲ�Э��ջ��
 *
 * \param  p_this   ��ǰģ��
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_ip_close(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_ip_close(p_this);
}

/**
 * \brief ����GPRS���ݣ��ڲ�Э��ջ��
 *
 * \param  p_this   ��ǰģ��
 * \param  p_data   ���͵�����
 * \param  len      �������ݳ���
 * \param  timeout  ��ʱʱ�䣬��λΪ��
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline ssize_t aw_gprs_ip_send(struct aw_gprs_dev *p_this, void *p_data, size_t len, uint32_t timeout)
{
	return p_this->pfn_gprs_ip_send(p_this, p_data, len, timeout);
}

/**
 * \brief ����GPRS���ݣ��ڲ�Э��ջ��
 *
 * \param  p_this   ��ǰģ��
 * \param  p_buf    �������ݻ���
 * \param  len      �������ݻ����С
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline ssize_t aw_gprs_ip_receive(struct aw_gprs_dev *p_this, void *p_buf, size_t len)
{
	return p_this->pfn_gprs_ip_receive(p_this, p_buf, len);
}

/**
 * \brief ��ȡGPRS����״̬���ڲ�Э��ջ��
 *
 * \param  p_this   ��ǰģ��
 *
 * \retval AW_OK    �ɹ�
 */
aw_local aw_inline aw_err_t aw_gprs_ip_get_status(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_ip_get_status(p_this);
}
#ifdef __cplusplus
}
#endif


#endif /* AW_GPRS_H_ */
