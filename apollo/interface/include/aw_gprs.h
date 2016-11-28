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
 * \brief 通用GPRS定义
 *
 * \par 使用示例
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

/** \brief GPRS模块操作结果  */
#define	AW_GPRS_OK       		(0)   	/**< \brief 操作成功   */
#define	AW_GPRS_FAIL			(-1)	/**< \brief 操作失败   */
#define	AW_GPRS_NO_SIM			(-2)	/**< \brief 找不到SIM卡  */
#define	AW_GPRS_CSQ_LOW			(-3)	/**< \brief 信号强度弱  */
#define	AW_GPRS_REG_FAIL		(-4)	/**< \brief 注册失败  */
#define	AW_GPRS_NO_RSP			(-5)	/**< \brief 模块无响应  */
#define	AW_GPRS_RSP_ERR			(-6)	/**< \brief 模块应答错误  */
#define	AW_GPRS_PARA_ERR		(-7)	/**< \brief 模块参数设置错误  */

/** \brief 接收的短信编码类型  */
#define AW_SMS_CODE_GB			(0)		/**< \brief GB编码短信   */
#define AW_SMS_CODE_HEX			(1)		/**< \brief HEX编码短信  */

/** \brief GPRS连接模式  */
#define AW_GPRS_TCP_MODE		(0)		/**< \brief TCP连接模式   */
#define AW_GPRS_UDP_MODE		(1)		/**< \brief UDP连接模式   */

/** \brief GPRS模块操作参数  */
struct aw_gprs_par
{
	char *p_dial_num;					/**< \brief 数据业务拨号号码   */
	char *p_apn;						/**< \brief APN名称   */
	char *p_user;						/**< \brief APN用户名   */
	char *p_password;					/**< \brief APN密码   */
	char *p_center_num;					/**< \brief 短信息中心号码   */

	void (*pfn_sms_int_cb)(void);       /**< \brief 短信接收中断回调函数, 该函数用于通知用户接收到短信息 */
};

/** \brief GPRS模块接收短信结构  */
struct aw_gprs_sms_data
{
	char     *p_sms_buff;				/**< \brief 短信内容缓存   */
	uint16_t  sms_buff_len;				/**< \brief 短信内容缓存长度   */

	char     *p_num_buff;				/**< \brief 手机号码内容缓存   */
	uint16_t  num_buff_len;				/**< \brief 手机号码内容缓存长度   */

	char     *p_time_buff;				/**< \brief 时间内容缓存   */
	uint16_t  time_buff_len;			/**< \brief 时间内容缓存长度   */

	uint8_t   sms_code;				 	/**< \brief 短信编码   */
};


struct aw_gprs_dev {

	struct aw_gprs_par       *p_gprs_par;

	struct aw_gprs_sms_data  *p_sms_par;

	/**
	 * \brief 是否拨号在线
	 */
	uint8_t              online;

	/**
	 * \brief 是否处于命令状态
	 */
	uint8_t              cmd_state;

	/**
	 * \brief GPRS模块开机接口
	 */
	void (*pfn_gprs_power_on)(struct aw_gprs_dev *p_this);

	/**
	 * \brief GPRS模块关机接口
	 */
	void (*pfn_gprs_power_off)(struct aw_gprs_dev *p_this);

	/**
	 * \brief GPRS模块初始化接口
	 */
	aw_err_t (*pfn_gprs_init)(struct aw_gprs_dev *p_this);

	/**
	 * \brief GPRS模块信号强度获取接口
	 */
	aw_err_t (*pfn_gprs_csq_get)(struct aw_gprs_dev *p_this, uint8_t *p_csq);

	/**
	 * \brief 获取GPRS模块CCID接口
	 */
	aw_err_t (*pfn_gprs_ccid_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief PPP拨号接口
	 */
	aw_err_t (*pfn_gprs_ppp_open)(struct aw_gprs_dev *p_this);

	/**
	 * \brief PPP拨号关闭接口
	 */
	aw_err_t (*pfn_gprs_ppp_close)(struct aw_gprs_dev *p_this);

	/**
	 * \brief PPP拨号的IP地址获取接口
	 */
	aw_err_t (*pfn_gprs_pppif_ip_get)(struct aw_gprs_dev *p_this,
			                          struct in_addr     *p_ipaddr);

	/**
	 * \brief 短信发送接口
	 */
	aw_err_t (*pfn_gprs_sms_send)(struct aw_gprs_dev *p_this,
			                      char               *p_sms,
			                      char               *p_num);

	/**
	 * \brief HEX短信发送接口
	 */
	aw_err_t (*pfn_gprs_sms_hex_send)(struct aw_gprs_dev *p_this,
							          uint8_t            *p_sms,
							          uint8_t             len,
							          char               *p_num);

	/**
	 * \brief 短信接收接口
	 */
	aw_err_t (*pfn_gprs_sms_recv)(struct aw_gprs_dev      *p_this,
			                      struct aw_gprs_sms_data *p_sms,
			                      uint32_t                 timeout);

	/**
	 * \brief 删除全部短信
	 */
	aw_err_t (*pfn_gprs_all_sms_del)(struct aw_gprs_dev *p_this);

	/**
	 * \brief 获取GPRS模块的版本号
	 */
	aw_err_t (*pfn_gprs_module_revision_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief 获取GPRS模块的IMEI号
	 */
	aw_err_t (*pfn_gprs_module_imei_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief 获取GPRS模块的IMSI号
	 */
	aw_err_t (*pfn_gprs_module_imsi_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief 获取GPRS模块的短信息中心号码
	 */
	aw_err_t (*pfn_gprs_module_sca_get)(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes);

	/**
	 * \brief 建立GPRS连接
	 */
    aw_err_t (*pfn_gprs_ip_start)(struct aw_gprs_dev *p_this, uint8_t mode, char *p_ip, uint16_t port, uint32_t timeout);

	/**
	 * \brief 关闭GPRS连接
	 */
    aw_err_t (*pfn_gprs_ip_close)(struct aw_gprs_dev *p_this);

	/**
	 * \brief 发送GPRS数据
	 */
    ssize_t (*pfn_gprs_ip_send)(struct aw_gprs_dev *p_this, void *p_data, size_t len, uint32_t timeout);

	/**
	 * \brief 接收GPRS数据
	 */
    ssize_t (*pfn_gprs_ip_receive)(struct aw_gprs_dev *p_this, void *p_buf, size_t len);

	/**
	 * \brief 获取GPRS连接状态
	 */
    aw_err_t (*pfn_gprs_ip_get_status)(struct aw_gprs_dev *p_this);
};

/**
 * \brief GPRS模块开机
 *
 * 打开GPRS模块电源，并开机
 *
 * \param  p_this  当前模块
 *
 * \retval 无
 */
aw_local aw_inline void aw_gprs_power_on (struct aw_gprs_dev *p_this)
{
	p_this->pfn_gprs_power_on(p_this);
}

/**
 * \brief GPRS模块关机
 *
 * GPRS模块关机并关掉模块电源
 *
 * \param  p_this  当前模块
 *
 * \retval 无
 *
 */
aw_local aw_inline void aw_gprs_power_off(struct aw_gprs_dev *p_this)
{
	p_this->pfn_gprs_power_off(p_this);
}

/**
 * \brief 初始化GPRS模块
 *
 * 本函数初始化GPRS模块，执行时间比较长，执行时间跟网络信号有关
 *
 * \param  p_this  当前模块
 *
 * \retval AW_OK   成功
 *
 */
aw_local aw_inline aw_err_t aw_gprs_init(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_init(p_this);
}

/**
 * \brief 获取GPRS模块的信号强度
 *
 *  获取到的信号强度范围为0~31, 或99.
 *  0~31能检测到信号强度, 0为最弱, 31为最强. 99不能检测到信号强度
 *
 *  在线状态下获取信号强度, 有可能会导致网络断开
 *
 * \param   p_this  当前模块
 * \param   p_csq   获取的信号强度
 *
 * \retval  AW_OK   成功
 *
 */
aw_local aw_inline aw_err_t aw_gprs_csq_get(struct aw_gprs_dev *p_this, uint8_t *p_csq)
{
	return p_this->pfn_gprs_csq_get(p_this, p_csq);
}

/**
 * \brief 获取GPRS模块的CCID
 *
 * 在线状态下获取CCID，有可能会导致网络断开
 *
 * \param   p_this   当前模块
 * \param   p_buf    存放获取到CCID的缓存
 * \param   nbytes   缓存大小
 *
 * \retval  AW_OK    成功
 *
 */
aw_local aw_inline aw_err_t aw_gprs_ccid_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_ccid_get(p_this, p_buf, nbytes);
}

/**
 * \brief PPP拨号接口（外部协议栈）
 *
 * 执行PPP拨号，拨号超时为30s
 *
 * \param  p_this  当前模块
 *
 * \retval AW_OK   成功
 *
 */
aw_local aw_inline aw_err_t aw_gprs_ppp_open(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_ppp_open(p_this);
}

/**
 * \brief PPP拨号关闭（外部协议栈）
 *
 * 本函数执行PPP拨号关闭
 *
 * \param  p_this  当前模块
 *
 * \retval AW_OK   成功
 *
 */
aw_local aw_inline aw_err_t aw_gprs_ppp_close(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_ppp_close(p_this);
}

/**
 * \brief 获取PPP拨号的IP地址
 *
 * \param  p_this   当前模块
 * \param  p_ipaddr 存放IP地址
 *
 * \retval -EINVAL  p_gprs为空
 *                  p_ipaddr为空
 *         AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_pppif_ip_get(struct aw_gprs_dev *p_this,
			                                     struct in_addr     *p_ipaddr)
{
	return p_this->pfn_gprs_pppif_ip_get(p_this, p_ipaddr);
}

/**
 * \brief 短信发送
 *
 * \param  p_this   当前模块
 * \param  p_sms    短信内容
 * \param  p_num    手机号码
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_sms_send(struct aw_gprs_dev *p_this,
		                                     char               *p_sms,
		                                     char               *p_num)
{
	return p_this->pfn_gprs_sms_send(p_this, p_sms, p_num);
}

/**
 * \brief HEX短信发送
 *
 * \param  p_this   当前模块
 * \param  p_sms    短信内容
 * \param  len		短信内容长度
 * \param  p_num    手机号码
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_sms_hex_send(struct aw_gprs_dev *p_this,
		                                         uint8_t            *p_sms,
		                                         uint8_t			 len,
		                                         char               *p_num)
{
	return p_this->pfn_gprs_sms_hex_send(p_this, p_sms, len, p_num);
}

/**
 * \brief 短信接收
 *
 * \param  p_this   当前模块
 * \param  p_sms    短信内容
 * \param  p_num    手机号码
 * \param  p_time   接收到短信的时刻
 *
 * \retval > 0     还有剩余短信可以继续接收
 *         = 0     短信接收完成
 *         = -1    短信接收失败
 */
aw_local aw_inline aw_err_t aw_gprs_sms_recv(struct aw_gprs_dev      *p_this,
		                                     struct aw_gprs_sms_data *p_sms,
		                                     uint32_t                 timeout)
{
	return p_this->pfn_gprs_sms_recv(p_this, p_sms, timeout);
}

/**
 * \brief 删除全部短信
 *
 * \param  p_this   当前模块
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_all_sms_del(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_all_sms_del(p_this);
}

/**
 * \brief 获取GPRS模块的版本号
 *
 * \param  p_this   当前模块
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_module_revision_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_module_revision_get(p_this, p_buf, nbytes);
}

/**
 * \brief 获取GPRS模块的IMEI号
 *
 * \param  p_this   当前模块
 * \param  p_buf    存放获取到IMEI的缓存
 * \param  p_buf    缓存大小
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_module_imei_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_module_imei_get(p_this, p_buf, nbytes);
}

/**
 * \brief 获取GPRS模块的IMSI号
 *
 * \param  p_this   当前模块
 * \param  p_buf    存放获取到IMSI的缓存
 * \param  p_buf    缓存大小
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_module_imsi_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_module_imsi_get(p_this, p_buf, nbytes);
}

/**
 * \brief 获取GPRS模块的短信息中心号码
 *
 * \param  p_this   当前模块
 * \param  p_buf    存放获取到短信息中心号码的缓存
 * \param  p_buf    缓存大小
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_module_sca_get(struct aw_gprs_dev *p_this, char *p_buf, uint8_t nbytes)
{
	return p_this->pfn_gprs_module_sca_get(p_this, p_buf, nbytes);
}

/**
 * \brief 建立GPRS连接（内部协议栈）
 *
 * \param  p_this   当前模块
 * \param  mode     模式TCP或UDP
 * \param  p_ip     连接服务器的IP地址或域名
 * \param  p_port   连接服务器的端口号
 * \param  timeout  超时时间，单位为秒
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_ip_start(struct aw_gprs_dev *p_this, uint8_t mode, char *p_ip, uint16_t port, uint32_t timeout)
{
	return p_this->pfn_gprs_ip_start(p_this, mode, p_ip, port, timeout);
}

/**
 * \brief 关闭GPRS连接（内部协议栈）
 *
 * \param  p_this   当前模块
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_ip_close(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_ip_close(p_this);
}

/**
 * \brief 发送GPRS数据（内部协议栈）
 *
 * \param  p_this   当前模块
 * \param  p_data   发送的数据
 * \param  len      发送数据长度
 * \param  timeout  超时时间，单位为秒
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline ssize_t aw_gprs_ip_send(struct aw_gprs_dev *p_this, void *p_data, size_t len, uint32_t timeout)
{
	return p_this->pfn_gprs_ip_send(p_this, p_data, len, timeout);
}

/**
 * \brief 接收GPRS数据（内部协议栈）
 *
 * \param  p_this   当前模块
 * \param  p_buf    接收数据缓存
 * \param  len      接收数据缓存大小
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline ssize_t aw_gprs_ip_receive(struct aw_gprs_dev *p_this, void *p_buf, size_t len)
{
	return p_this->pfn_gprs_ip_receive(p_this, p_buf, len);
}

/**
 * \brief 获取GPRS连接状态（内部协议栈）
 *
 * \param  p_this   当前模块
 *
 * \retval AW_OK    成功
 */
aw_local aw_inline aw_err_t aw_gprs_ip_get_status(struct aw_gprs_dev *p_this)
{
	return p_this->pfn_gprs_ip_get_status(p_this);
}
#ifdef __cplusplus
}
#endif


#endif /* AW_GPRS_H_ */
