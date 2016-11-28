/*******************************************************************************
*                                 AWORKS
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
 * \brief modbus�ӻ�Э��ջ�û��ӿ�ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.03 2016-04-27  cod, support muti-instance.
 * - 1.02 2015-05-22  cod, fix code style and comments, a little improve.
 * - 1.01 2013-03-29  liuweiyun, fix code style and comments, a little improve.
 * - 1.00 2012-05-03  ygy, first implementation
 * \endinternal
 */

#ifndef __AW_MB_SLAVE_H /* { */
#define __AW_MB_SLAVE_H

/**
 * \addtogroup grp_aw_if_mbslave_if
 * \copydoc mbslave.h
 * @{
 */

#include "modbus/aw_mb_config.h"
#include "modbus/aw_mb_err.h"
#include "modbus/aw_mb_comm.h"
#include "modbus/aw_mb_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/** ������ص��������� */
enum aw_mb_func_cb_type {
	AW_MB_FUNC_COILS_CALLBACK,                /**< \brief ��д��Ȧ�����ص� */
	AW_MB_FUNC_DISCRETEINPUTS_CALLBACK,       /**< \brief ����ɢ�������ص� */
	AW_MB_FUNC_HOLDREGISTERS_CALLBACK,        /**< \brief ��д����Ĵ����ص� */
	AW_MB_FUNC_INPUTREGISTERS_CALLBACK,       /**< \brief ������Ĵ����ص� */
};

/** ������ص������������� */
enum aw_mb_func_cb_op {
	AW_MB_FUNC_CALLBACK_READ,   /**< \brief ������ */
	AW_MB_FUNC_CALLBACK_WRITE,  /**< \brief д���� */
};

/** Modbus��ջ������� */
typedef void *aw_mb_slave_t;

/******************************************************************************/

/**
 * \file
 *
 * callback function
 *
 * Read the ON/OFF status of discrete outputs(DO)in the slave. The coils status
 * is packed as per bit of data field. Status is indicated as: 1=ON, 0=OFF.
 * The LSB of the first data byte contains the coil addressed in the query.
 * If the coil quantity is not a multiple of eight, the remaining bits in the
 * final data byte will be padded with zeros.
 *
 * For example. addr = 0x0013  num = 10,
 * status of coils 20 ~ 27 is ON-ON-OFF-OFF-ON-OFF-ON-OFF 28~29 ON-ON,
 * so the buf[0] = 01010011(0x53)  buf[1] = 00000011
 *
 * buf[0]:
 * 7  |6  |5  |4  |3  |2  |1  |0
 * ---|---|---|---|---|---|---|---
 * 27 |26 |25 |24 |23 |22 |21 |20
 * OFF|ON |OFF|ON |OFF|OFF|ON |ON
 * 0  |1  |0  |1  |0  |0  |1  |1
 *
 * buf[1]:
 * 7  |6  |5  |4  |3  |2  |1  |0
 * ---|---|---|---|---|---|---|----
 * -  |-  |-  |-  |-  |-  |29 |28
 * 0  |0  |0  |0  |0  |0  |ON |ON
 * 0  |0  |0  |0  |0  |0  |1  |1
 */

/**
 * \brief ��д��Ȧ������ɢ������д����Ĵ�����������Ĵ����ص�����ԭ��
 * @note  ��ʹ�ñ����ṩ�Ķ�д��Ȧ������ɢ������д����Ĵ�����
 * 		     ������Ĵ����ȹ����봦����ʱ����Ҫע��
 * @code
 * aw_mb_exception_t my_coils_callback(aw_mb_slave_t slave,
 *                                     uint8_t   *buf,
 *                                     uint16_t   addr,
 *                                     uint16_t   num)
 * {
 *     //����Ȧ����
 * }
 *
 * //������slave֮ǰ�������²�����
 * aw_mb_slave_register_callback(slave,
 *                            	 AW_MB_FUNC_COILS_CALLBACK,
 *                            	 AW_MB_FUNC_CALLBACK_READ,
 *                            	 my_coils_callback);
 * @endcode
 *
 * @param[in] slave �ӻ����
 * @param[in,out] buf  ��д����������
 * @param[in] addr ��д������ʼ��ַ
 * @param[in] num  ��д��������
 * @return ���û���쳣������AW_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 * @see aw_mb_slave_register_callback
 */
typedef aw_mb_exception_t (*aw_mb_slave_fn_code_callback_t)(
	aw_mb_slave_t slave,
	uint8_t      *p_buf,
    uint16_t   	  addr,
    uint16_t      num);

/**
 * \brief ע���д��Ȧ������ɢ������д����Ĵ�����������Ĵ����ص�����.
 * @note  ��ʹ�ñ����ṩ�Ķ�д��Ȧ������ɢ������д����Ĵ�����������Ĵ���������
 * 		     ������ʱ, ����ʹ�øú������лص�����ע�ᣬ�����������÷Ƿ��������쳣
 *
 * @param[in] slave �ӻ����
 * @param[in] type ������ص���������
 * @param[in] op ������ص�������������
 * @param[in] callback �ص�����
 * @return ���û�д��󷵻�MB_ERR_NOERR,���򷵻ض�Ӧ�Ĵ����
 */
aw_mb_err_t aw_mb_slave_register_callback (
	aw_mb_slave_t                  slave,
	enum aw_mb_func_cb_type        type,
	enum aw_mb_func_cb_op          op,
	aw_mb_slave_fn_code_callback_t callback);

/**
 * \brief �����봦����ԭ��.
 * @note  ���ӻ��յ�һ֡�����Ժ󣬽����ݹ�������ö�Ӧ�Ĵ�������
 * 		     ���������û�ͨ��\a aw_mb_slave_register_handler ��ע�ᡣ
 *		     ͬʱ�Ѿ���������Ķ�д��Ȧ������ɢ������д����Ĵ�����������Ĵ���
 * 		     �ȴ�����������ο�\a mbslavefun.h
 *
 * @param[in] slave Modbus��ջ���
 * @param[in,out] p_pdubuf PDU����(����������)
 *         - [in]  ����PDU����
 *         - [out] Ӧ��PDU����
 * @param[in,out] p_pdulen PDU���ݳ���
 *         - [in]  ����PDU���ݳ���
 *         - [out] Ӧ��PDU���ݳ���
 * @return ���û���쳣������AW_MB_EXP_NONE�����򷵻ض�Ӧ���쳣��
 */
typedef aw_mb_exception_t (*aw_mb_fn_code_handler_t) (aw_mb_slave_t slave,
                                                  	  uint8_t      *p_pdubuf,
                                                  	  uint16_t     *p_pdulen);

/******************************************************************************/

/**
 * \brief ��������ʼ��һ��Modbus��վ
 * @note  �ڵ������дӻ�����֮ǰ�������ȵ��øú���
 * @note  ����ͬ���紴�������վ
 *
 * @param[in] mode    : ͨ��ģʽ
 * @param[in] p_param : ��ʼ������������MB_RTU/MB_ASCIIģʽʹ��
 *                      struct aw_mb_serial_param��Ϊ����
 *                      ����AW_MB_TCPģʽ��param��Ϊ�˿ںŲ���ʹ��,ֱ�Ӵ����β�
 * @param[out] p_err  : �����. ����Դ���Ų�����Ȥ���Դ���AW_MB_NULL������
 *                      ���û�д�����ֵΪAW_MB_ERR_NOERR
 * @return Modbus��ջ���������������󷵻�NULL
 */
aw_mb_slave_t aw_mb_slave_init (enum aw_mb_mode mode,
							    void     	   *p_param,
								aw_mb_err_t    *p_err);

/**
 * \brief �ر�Modbus��վ.
 * @note  �˳�ϵͳ���߲���Ҫ��ʹ�ôӻ�ʱ����
 *
 * @param[in] slave : Modbus��ջ���
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_close (aw_mb_slave_t slave);

/**
 * \brief ����Modbus��ջ.
 * @note  �ú��������ڵ���aw_mb_slave_init��������ߵ���aw_mb_slave_stop�����󱻵���
 *
 * @param[in] slave : Modbus��ջ���
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_start (aw_mb_slave_t slave);

/**
 * \brief ֹͣModbus��ջ.
 *
 * @param[in] slave : Modbus��ջ���
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_stop (aw_mb_slave_t slave);

/**
 * \brief ע�Ṧ���봦����.
 * @note  ��ʼ��Modbus��վ�Ժ󣬿��Ե��øú�����ע���Ӧ�Ĺ����봦������������չ������
 *
 * @note ����ע��Ĺ����봦����������aw_mb_config.h��AW_MB_FUNC_CODE_HANDLER_MAX���塣
 *       �����ø������޷���ע�ᡣͬһ��������ֻ����һ�������������ע������ͬ
 *       һ�������봦��������ֻʹ�����ע��Ĵ�������
 * @param[in] slave    : Modbus��ջ���
 * @param[in] funcode  : �������
 * @param[in] handler  : �����봦����
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR;
 *  ����������󷵻�AW_MB_ERR_EINVAL;
 *  ����޷���ע�Ṧ���뷵��AW_MB_ERR_ENORES.
 */
aw_mb_err_t aw_mb_slave_register_handler (aw_mb_slave_t            slave,
                                    	  uint8_t                  funcode,
                                    	  aw_mb_fn_code_handler_t  handler);

/**
 * \brief Modbus��ջ��ѯ����.
 * @note  ��������֡�����������֡����ΪModbus��ջЭ��ĺ��ġ��ú������뱻�����Եĵ��á�
 *        ��ʱ������������Ӧ�ú���ջҪ���ʱ������
 *
 * @param[in] slave : Modbus��վ���
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR����֮������Ӧ�Ĵ�������.
 */
aw_mb_err_t aw_mb_slave_poll (aw_mb_slave_t slave);

/**
 * \brief ����Modbus��ջ��Ϣ.
 * ��������Modbus��ջ����˵������ǰ״̬������һЩ������Ϣ��
 * @note ��ʵ�ֶ�����Modbus��ջ��Ϣ��󳤶�Ϊ32���ֽڣ����У�
 *    - ջ����˵��ռһ���ֽ�
 *    - ��ǰ״̬ռһ���ֽ�
 *    - ������Ϣ����<= 30����Ϣ\n
 *  ��ʹ����Ҫ�ر�ע��.
 *
 * @param[in] slave        : Modbus��ջ���
 * @param[in] slave_id     : ����˵��
 * @param[in] is_running   : ��ǰ״̬
 * @param[in] p_additional : ����һЩ������Ϣ
 * @param[in] alen         : ����һЩ������Ϣ����
 *
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_set_id (aw_mb_slave_t     slave,
                                uint8_t           slave_id,
                                uint8_t           is_running,
                                const uint8_t    *p_additional,
                                uint16_t          alen);

/**
 * \brief ����Modbus��ջ��ַ.
 * @note  Ĭ��������ڵ���aw_mb_slave_init���г�ʼ��ʱ����ʼ�����������Ѿ������ô�ջ��ַ��
 * 		     ���������Ҫ������ʱ�޸Ĵ�ջ��ַ������ʹ�øú�����
 *
 * @param[in] slave : Modbus��ջ���
 * @param[in] addr  : �µ�Modbus��ջ��ַ
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_slave_set_addr (aw_mb_slave_t slave, uint8_t addr);

#ifdef __cplusplus
}
#endif

/** @} grp_aw_if_mbslave_if */

#endif /* } __AW_MB_SLAVE_H */

/* end of file */
