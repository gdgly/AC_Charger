/*******************************************************************************
*                                 AWORKS
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      aworks.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief user interface of modbus master protocol.
 *
 * \internal
 * \par modification history
 * - 1.00 2016-01-11  cod, first implementation
 * \endinternal
 */
#ifndef __AW_MB_MASTER_H  /* { */
#define __AW_MB_MASTER_H

/**
 * \addtogroup grp_aw_mb_master_if
 * \copydoc aw_mb_master.h
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "modbus/aw_mb_config.h"
#include "modbus/aw_mb_err.h"
#include "modbus/aw_mb_compiler.h"
#include "modbus/aw_mb_comm.h"

/** Modbus��վ������� */
typedef void *aw_mb_master_t;

/**
 * \brief ����Modbus��վ����
 *
 * @note �ڵ���������վ����֮ǰ�������ȵ��øú���.
 * @note TCPģʽ�£�����ͬһ��վ�����в�����ͬһ���߳���.�û���ʹ�øýӿڽ����������.
 *
 * @return Modbus��վ���������������󷵻�NULL
 */
aw_mb_master_t aw_mb_master_create (void);

/**
 * \brief �رա�ɾ����վ
 * @note  �˳�ϵͳ���߲���Ҫ��ʹ����վʱ����
 *
 * @param[in] master : Modbus��վ���
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR
 */
aw_mb_err_t aw_mb_master_delete (aw_mb_master_t master);

/**
 * \brief ����Modbus��վ
 *
 * @note �ýӿڱ�������վֹͣ��δ�����µ���.
 *
 * @param[in] master           : Modbus��վ���
 * @param[in] mode             �� ��վģʽ.
 * @param[in] p_params         : ���ò�����
 *                               ����AW_MB_RTU/AW_MB_ASCIIģʽ��
 *                               ʹ��aw_mb_master_serial_param_t��Ϊ����;
 *                               ����AW_MB_TCPģʽ,
 *                               ʹ��aw_mb_tcp_client_param_t��Ϊ����.
 *                               ���û������������ò������ò����ɴ���NULL����.
 * @retval: AW_MB_ERR_NOERR    : ��վֹͣ�ɹ�.
 * @retval: AW_MB_ERR_EINVAL   : ��������.
 * @retval: AW_MB_ERR_EILLSTATE: Э��ջ�Ƿ�״̬.
 * @retval: AW_MB_ERR_EIO      : �������ó���.
 */
aw_mb_err_t aw_mb_master_config (aw_mb_master_t  master,
                                 enum aw_mb_mode mode,
                                 const void     *p_params);

/**
 * \brief ����Modbus��վ
 *
 * @note Modbus TCPģʽ��, ���øýӿڽ������˽�������.
 *
 * @param[in] master           : Modbus��վ���
 * @retval: AW_MB_ERR_NOERR    : ��վ�����ɹ�
 * @retval: AW_MB_ERR_EINVAL   : ��������
 * @retval: AW_MB_ERR_EILLSTATE: Э��ջ�Ƿ�״̬
 * @retval: AW_MB_ERR_EIO      : TCPģʽ�£����ӽ���ʧ��.
 */
aw_mb_err_t aw_mb_master_start (aw_mb_master_t master);

/**
 * \brief ֹͣModbus��վ
 *
 * @note ���øýӿڽ�������ֱ��Modbus�����������.
 * @note Modbus TCPģʽ�£� ���øýӿڽ��Ͽ�TCP����.
 *
 * @param[in] master           : Modbus��վ���
 * @retval: AW_MB_ERR_NOERR    : ��վֹͣ�ɹ�
 * @retval: AW_MB_ERR_EINVAL   : ��������
 * @retval: AW_MB_ERR_EILLSTATE: Э��ջ�Ƿ�״̬
 * @retval: AW_MB_ERR_EIO      : IO����
 */
aw_mb_err_t aw_mb_master_stop (aw_mb_master_t master);

/**
 * \brief Modbus��վ���ݴ���ӿ�.
 * @note  �ýӿڷ��͡���������֡���������ݡ��ýӿ�Ϊ�����ӿڣ��ұ��뱻�����Ե���.
 * @note  ���ж����վ�����Modbus���磩���贴������߳������øýӿ�.
 * @note  Modbus TCPģʽ�²���Ҫ���øýӿ�,�����÷����޴���AW_MB_ERR_NOERR.
 *
 * @param[in] master           : Modbus��վ���;
 * @retval: AW_MB_ERR_NOERR    : �ӿ�����
 * @retval: AW_MB_ERR_EINVAL   : ��������;
 * @retval: AW_MB_ERR_EILLSTATE: Э��ջ�Ƿ�״̬;
 * @retval: AW_MB_ERR_EIO      : IO����.
 */
aw_mb_err_t aw_mb_master_poll (aw_mb_master_t master);

/** \brief ��վ��д���� */
typedef struct aw_mb_master_rw_param {
     uint16_t  rd_addr;     /**< \brief ����ʼ��ַ  */
     uint16_t  rd_num;      /**< \brief ����Ŀ            */
     uint16_t *p_rd_buf;    /**< \brief ������            */
     uint16_t  wr_addr;     /**< \brief д��ʼ��ַ  */
     uint16_t  wr_num;      /**< \brief д��Ŀ            */
     uint16_t *p_wr_buf;    /**< \brief д����            */
} aw_mb_master_rw_param_t;

/**
 * \brief ��վ����
 * @note  �ýӿ�����վ������������ɵ���.
 * @note  �ýӿ�Ϊͬ�������ӿ�.
 * @note  TCPģʽ�£�������ͬһ�������ڶ��߳��²���.
 * @note  ��վ����ʱʱ�䣬ͨ���ӿ� aw_mb_master_ack_timeout_set ����
 *
 * @note
 * @param[in] master       : Modbus��վ���
 * @param[in] slave_addr   : �����Ŀ��ӻ���ַ
 * @param[in] funcode      : ������
 * @param[in][out] p_param : ��д����;
 *                           ��ΪЭ��ջ֧�ֹ����룬
 *                           �ò���Ϊaw_mb_master_rw_param_t����;
 *                           ��Ϊ�û��Զ��幦���룬�ò������û��Զ��塣
 *
 * @return ���û�д��󷵻�AW_MB_ERR_NOERR��������ʧ�ܣ��ɲ鿴����������͡�
 *
 */
aw_mb_err_t aw_mb_master_request (aw_mb_master_t master,
                                  uint8_t        slave_addr,
                                  uint8_t        funcode,
                                  void          *p_params);

/**
 * \brief ����PDU���ݴ���ӿ�
 * @note  �û�ע���Զ��幦����ʱ���趨������ͽӿ�ע�ᡣ
 * @note  �û�ʹ�øýӿڽ�p_params����ת��Ϊp_pdudata���ݣ������������룩,������PDU
 *        ���ݳ���(p_pdudata_len)���Դ˸�֪Э��ջ������PDU���ݼ����ͳ��ȡ�
 *
 * @param[in]           p_params : �û��Զ������;
 *                                 �ò���Ϊaw_mb_master_request�ӿڵ�p_param����.
 * @param[in][out]     p_pdudata : PDU�������ݻ��������û�������ת�����������С�
 * @param[in][out] p_pdudata_len : PDU�������ݻ��������ȣ��ò�������ʱ����֪�û�
 *                                 PDU���ݻ���������󳤶ȡ�
 * @return ������PDU���ݴ���ʧ�ܣ��򷵻���Ӧ�������ͣ���֮����AW_MB_ERR_NOERR��
 */
typedef aw_mb_err_t (*aw_mb_snd_funcode_handler_t) (void    *p_params,
                                                    uint8_t *p_pdudata,
                                                    uint8_t *p_pdudata_len);

/**
 * \brief ����PDU���ݴ���ӿ�
 * @note  �û�ע���Զ��幦����ʱ���趨������ͽӿ�ע�ᡣ
 * @note  �û�ʹ�øýӿڽ�PDU����������ת��Ϊp_params.
 *
 * @param[in][out]  p_params : �û��Զ������,
 *                             �ò���Ϊaw_mb_master_request�ӿڵ�p_param����.
 * @param[in]      p_pdudata : PDU���ݻ�����(������������).
 * @param[in]    pdudata_len : PDU���ݻ���������.
 * @return ��PDU���ݴ���ʧ�ܣ��򷵻���Ӧ�������ͣ���֮����AW_MB_ERR_NOERR��
 */
typedef aw_mb_err_t (*aw_mb_rcv_funcode_handler_t) (void    *p_params,
                                                    uint8_t *p_pdudata,
                                                    uint8_t  pdudata_len);
/**
 * \brief ע���Զ��幦���봦��ӿڵ�ָ����վ.
 * @note  ���� ��վ�󣬿�ע���û��Զ��幦���봦��ӿڡ�
 * @note  �ýӿڽ������봦��ӿ�ע��ɹ��󣬿�ʹ��aw_mb_master_request�ӿ�������
 * @note  �û������¶���Э��ջĬ�Ϲ����봦��ӿڡ����û����ע��ͬһ�����봦��ӿڣ�
 *        ��ʹ�����ע��Ĺ����봦��ӿڡ�
 * @note  ����ע��Ĺ����봦����������aw_mb_config.h��
 *        AW_MB_MASTER_FUNCODE_HANDLER_MAX���壬�����ø������޷���ע�ᡣ
 *
 * @param[in] master      : ��վ���
 * @param[in] funcode     : �������
 * @param[in] snd_handler : ���ʹ�����
 * @param[in] rcv_handler : ���մ���������Ϊд�������û����账�����PDU���ݣ�
 *                          �ɽ��˽ӿ���NULL��
 * @return ע��ɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������.
 *
 * \code
 * #include "aw_mb_master.h"
 *
 * #define MB_MASK_WRITE_REG_FUNCODE  22
 * struct wr_mask_param {
 *     uint16_t addr;
 *     uint16_t and_mask;
 *     uint16_t or_mask;
 * } my_mask_param;
 *
 * aw_mb_err_t __mb_snd_mask_handler (void    *p_params,
 *                                    uint8_t *p_pdudata,
 *                                    uint8_t *pdudata_len)
 * {
 *     struct wr_mask_param *p_mask_param = (struct wr_mask_param *)p_params;
 *
 *     p_pdudata[0] = (uint8_t)(p_mask_param->addr >> 8);
 *     p_pdudata[1] = (uint8_t)(p_mask_param->addr);
 *     p_pdudata[2] = (uint8_t)(p_mask_param->and_mask >> 8);
 *     p_pdudata[3] = (uint8_t)(p_mask_param->and_mask);
 *     p_pdudata[4] = (uint8_t)(p_mask_param->or_mask >> 8);
 *     p_pdudata[5] = (uint8_t)(p_mask_param->or_mask);
 *
 *     *pdudata_len = 6;
 *
 *     return AW_MB_ERR_NOERR;
 * }
 *     //ע��д�Ĵ������빦���봦����
 *     aw_mb_master_funcode_register(master,
 *                                   MB_MASK_WRITE_REG_FUNCODE,
 *                                   __mb_snd_mask_handler,
 *                                   NULL);
 *     //д�Ĵ�������
 *     my_mask_param.addr     = 1000;
 *     my_mask_param.and_mask = 0x01;
 *     my_mask_param.or_mask  = 0;
 *     aw_mb_master_request(master,
 *                          SLAVE_ADDR,
 *                          MB_MASK_WRITE_REG_FUNCODE,
 *                          &my_mask_param);
 * \endcode
 */
aw_mb_err_t aw_mb_master_funcode_register ( \
                                    aw_mb_master_t              master,
                                    uint8_t                     funcode,
                                    aw_mb_snd_funcode_handler_t snd_handler,
                                    aw_mb_rcv_funcode_handler_t rcv_handler);

/**
 * \brief ��������Ӧ��ʱʱ��
 *
 * @param[in]      master      : ��վ���
 * @param[in]      timeout     : Ӧ��ʱʱ�䣨���룩, ȡֵ��Χ50 ~ 100000ms
 * @param[in][out] p_rw_param  : ��д����
 *
 * @retval AW_MB_ERR_EINVAL    : ��������
 * @retval AW_MB_ERR_EILLSTATE : �Ƿ�״̬��δ������վ
 */
aw_mb_err_t aw_mb_master_ack_timeout_set (aw_mb_master_t master,
                                          uint32_t       timeout);

/**
 * \brief ��ȡ����Ӧ��ʱʱ��
 *
 * @param[in]      master      : ��վ���
 *
 * @return Ӧ��ʱʱ���ȡ�� ����0Ϊ�����������
 */
uint32_t aw_mb_master_ack_timeout_get (aw_mb_master_t master);
/*****************************************************************************
 * Common Function's Code Interface
 *****************************************************************************/
/**
 * \brief ����Ȧ����
 *
 * @param[in] master        : ��վ���
 * @param[in] slave_addr    : Ŀ��ӻ���ַ
 * @param[in] start_addr    : ��Ȧ��ʼ��ַ
 * @param[in] quantity      : ��Ȧ��, ȡֵ��Χ1~2000
 * @param[in][out] p_rd_val : ��ȡ��Ȧֵ
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_coils_read (aw_mb_master_t master,
                              uint8_t        slave_addr,
                              uint16_t       start_addr,
                              uint16_t       quantity,
                              uint8_t       *p_rd_val);

/**
 * \brief ����ɢ������
 *
 * @param[in] master        : ��վ���
 * @param[in] slave_addr    : Ŀ��ӻ���ַ
 * @param[in] start_addr    : ��ɢ��������ʼ��ַ
 * @param[in] quantity      : ��ɢ����ȡ����, ȡֵ��Χ1~2000
 * @param[in][out] p_rd_val : ��ȡ��ɢ��ֵ
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_discrete_inputs_read (aw_mb_master_t master,
                                        uint8_t        slave_addr,
                                        uint16_t       start_addr,
                                        uint16_t       quantity,
                                        uint8_t       *p_rd_val);

/**
 * \brief �����ּĴ�������
 *
 * @param[in] master        : ��վ���
 * @param[in] slave_addr    : Ŀ��ӻ���ַ
 * @param[in] start_addr    : ��ʼ��ַ
 * @param[in] quantity      : ��ȡ���ּĴ���������ȡֵ��Χ1~125
 * @param[in][out] p_rd_val : ��ȡ���ּĴ���ֵ
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_holding_reg_read (aw_mb_master_t master,
                                    uint8_t        slave_addr,
                                    uint16_t       start_addr,
                                    uint16_t       quantity,
                                    uint16_t      *p_rd_val);

/**
 * \brief ������Ĵ�������
 *
 * @param[in] master        : ��վ���
 * @param[in] slave_addr    : Ŀ��ӻ���ַ
 * @param[in] start_addr    : ��ʼ��ַ
 * @param[in] quantity      : ��ȡ����Ĵ���������ȡֵ��Χ1~125
 * @param[in][out] p_rd_val : ��ȡ����Ĵ���ֵ
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_input_reg_read (aw_mb_master_t master,
                                  uint8_t        slave_addr,
                                  uint16_t       start_addr,
                                  uint16_t       quantity,
                                  uint16_t      *p_rd_val);

/**
 * \brief д������Ȧ����
 *
 * @param[in] master     : ��վ���
 * @param[in] slave_addr : Ŀ��ӻ���ַ
 * @param[in] coil_addr  : д��Ȧ��ַ
 * @param[in] coil_val   : д��Ȧֵ��ֵΪ0x0000(COIL OFF)�� 0xFF00(COIL ON).
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_single_coil_write (aw_mb_master_t master,
                                     uint8_t        slave_addr,
                                     uint16_t       coil_addr,
                                     uint16_t       coil_val);

/**
 * \brief д�����Ĵ�������
 *
 * @param[in] master     : ��վ���
 * @param[in] slave_addr : Ŀ��ӻ���ַ
 * @param[in] reg_addr   : д�Ĵ�����ַ
 * @param[in] reg_val    : д��Ĵ���ֵ
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_single_reg_write (aw_mb_master_t master,
                                    uint8_t        slave_addr,
                                    uint16_t       reg_addr,
                                    uint16_t       reg_val);

/**
 * \brief д�����Ȧ����
 *
 * @param[in] master     : ��վ���
 * @param[in] slave_addr : Ŀ��ӻ���ַ
 * @param[in] start_addr : д��Ȧ��ʼ��ַ
 * @param[in] quantity   : д��Ȧ������0x01~0x7b0��
 * @param[in] p_wr_buf   : д��Ȧֵ(������)
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_multiple_coils_write (aw_mb_master_t master,
                                        uint8_t        slave_addr,
                                        uint16_t       start_addr,
                                        uint16_t       quantity,
                                        uint8_t       *p_wr_buf);

/**
 * \brief д����Ĵ�������
 *
 * @param[in] master     : ��վ���
 * @param[in] slave_addr : Ŀ��ӻ���ַ
 * @param[in] start_addr : д�Ĵ�����ʼ��ַ
 * @param[in] quantity   : д�Ĵ�������
 * @param[in] p_wr_buf   : д�Ĵ���ֵ(������)
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_multiple_regs_write (aw_mb_master_t master,
                                       uint8_t        slave_addr,
                                       uint16_t       start_addr,
                                       uint16_t       quantity,
                                       uint16_t      *p_wr_buf);

/**
 * \brief ��д����Ĵ�������
 *
 * @param[in]      master     : ��վ���
 * @param[in]      slave_addr : Ŀ��ӻ���ַ
 * @param[in][out] p_rw_param : ��д����
 *
 * @return ִ�гɹ�����AW_MB_ERR_NOERR;ʧ�ܷ�����Ӧ��������
 */
aw_mb_err_t aw_mb_multiple_regs_read_write ( \
                                        aw_mb_master_t           master,
                                        uint8_t                  slave_addr,
                                        aw_mb_master_rw_param_t *p_rw_param);
/*****************************************************************************/


#ifdef __cplusplus
}
#endif

/** @} grp_aw_mb_master_if */

#endif /* } __AW_MB_MASTER_H */

/* end of file */

