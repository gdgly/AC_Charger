
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
 * \brief Apollo CAN �ӿ�ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.01 15-12-02  cae, first implementation
 * \endinternal
 */

#ifndef __AW_CAN_H
#define __AW_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_types.h"

/** \brief can controller type */
#define AW_CAN_CTLR_HS                  0x00    /**< \brief ����CAN */
#define AW_CAN_CTLR_FD                  0x01    /**< \brief CANFD */

/** \brief can work mode */
#define AW_CAN_WORK_MODE_NORMAL         0x00    /**< \brief ��������ģʽ */
#define AW_CAN_WORK_MODE_LISTEN_ONLY    0x01    /**< \brief ֻ������ģʽ */

/** \brief can bus error type */
#define AW_CAN_BUS_ERR_NONE             0x00    /**< \brief �޴��� */
#define AW_CAN_BUS_ERR_BIT              0x01    /**< \brief λ���� */
#define AW_CAN_BUS_ERR_ACK              0x02    /**< \brief Ӧ����� */
#define AW_CAN_BUS_ERR_CRC              0x04    /**< \brief CRC���� */
#define AW_CAN_BUS_ERR_FORM             0x08    /**< \brief ��ʽ���� */
#define AW_CAN_BUS_ERR_STUFF            0x10    /**< \brief ������ */
#define AW_CAN_BUS_ERR_DATAOVER         0x20    /**< \brief ���ش��� */
#define AW_CAN_BUS_ERR_RCVBUFF_FULL     0x40    /**< \brief ���ջ������� */
#define AW_CAN_BUS_ERR_TXDBUFF_FULL     0x80    /**< \brief ���ͻ������� */
typedef uint32_t aw_can_bus_err_t;

/** \brief status code returned by */
#define AW_CAN_BUS_STATUS_OK            0x00    /**< \brief �������� */
#define AW_CAN_BUS_STATUS_ERROR         0xE1    /**< \brief ���ߴ��� */
#define AW_CAN_BUS_STATUS_WARN          0xE2    /**< \brief ���߾��� */
#define AW_CAN_BUS_STATUS_PASSIVE       0xE3    /**< \brief �������� */
#define AW_CAN_BUS_STATUS_OFF           0xE4    /**< \brief ���߹ر� */
#define AW_CAN_BUS_STATUS_DATAOVER      0xE5    /**< \brief ���߳��� */
#define AW_CAN_BUS_STATUS_WAKE          0xE6    /**< \brief ���߻��� */
typedef uint32_t aw_can_bus_status_t;

/** \brief Macro definitions to be used with filtering*/
#define AW_CAN_COMPARE_ALL_STD_IDS      0x7FF
#define AW_CAN_COMPARE_ALL_EXT_IDS      0x1FFFFFFF
#define AW_CAN_ACCEPT_ALL_IDS           0

/** \brief STATUS error codes returned by CAN interface functions */
#define AW_CAN_ERR_NONE                         0
#define AW_CAN_ERR_BASE                         0
#define AW_CAN_ERR_BUSY                        (AW_CAN_ERR_BASE + 80)
#define AW_CAN_ERR_NOT_INITIALIZED             (AW_CAN_ERR_BASE + 81)
#define AW_CAN_ERR_NONE_DRIVER_FUNC            (AW_CAN_ERR_BASE + 82)
#define AW_CAN_ERR_ILLEGAL_CHANNEL_NO          (AW_CAN_ERR_BASE + 83)
#define AW_CAN_ERR_ILLEGAL_CHANNEL_MODE        (AW_CAN_ERR_BASE + 84)
#define AW_CAN_ERR_ILLEGAL_CTRL_TYPE           (AW_CAN_ERR_BASE + 85)
#define AW_CAN_ERR_INCOMPATIBLE_CTRL_TYPE      (AW_CAN_ERR_BASE + 86)
#define AW_CAN_ERR_CTRL_NOT_START              (AW_CAN_ERR_BASE + 87)
#define AW_CAN_ERR_NO_OP                       (AW_CAN_ERR_BASE + 88)
#define AW_CAN_ERR_ILLEGAL_DATA_LENGTH         (AW_CAN_ERR_BASE + 89)
#define AW_CAN_ERR_ILLEGAL_MASK_VALUE          (AW_CAN_ERR_BASE + 90)
#define AW_CAN_ERR_INVALID_PARAMETER           (AW_CAN_ERR_BASE + 91)
#define AW_CAN_ERR_ILLEGAL_OFFSET              (AW_CAN_ERR_BASE + 92)
#define AW_CAN_ERR_SLEEP_IN_RESET_MODE         (AW_CAN_ERR_BASE + 93)
#define AW_CAN_ERR_CANNOT_SET_WAKEUPINT        (AW_CAN_ERR_BASE + 94)
#define AW_CAN_ERR_CANNOT_SET_BOFFINT          (AW_CAN_ERR_BASE + 95)
#define AW_CAN_ERR_CANNOT_SET_ERRINT           (AW_CAN_ERR_BASE + 96)
#define AW_CAN_ERR_BAUDRATE_ERROR              (AW_CAN_ERR_BASE + 97)
#define AW_CAN_ERR_ABORT_TRANSMITTED           (AW_CAN_ERR_BASE + 98)
#define AW_CAN_ERR_TRANSMITTED_TIMEOUT         (AW_CAN_ERR_BASE + 99)
#define AW_CAN_ERR_BUS_FAULT                   (AW_CAN_ERR_BASE + 100)
#define AW_CAN_ERR_RXD_BUFF_UNUSED             (AW_CAN_ERR_BASE + 101)
#define AW_CAN_ERR_NONE_RCV_FUNC               (AW_CAN_ERR_BASE + 102)



#define AW_CAN_ERR_UNKNOWN_ERROR               (AW_CAN_ERR_BASE + 255)

typedef int32_t aw_can_err_t;

/** \brief message  timeout*/
#define AW_CAN_WAIT_FOREVER                  AW_WAIT_FOREVER
#define AW_CAN_NO_WAIT                       AW_NO_WAIT

/** \brief message send type*/
#define AW_CAN_MSG_SEND_NORMAL               0   /**< \brief ��������*/
#define AW_CAN_MSG_SEND_ONCE                 1   /**< \brief ���η���*/
#define AW_CAN_MSG_SEND_SELF                 2   /**< \brief �Է�����*/
#define AW_CAN_MSG_SEND_SELFONCE             3   /**< \brief �����Է�����*/

/** \brief error information save or not*/
#define AW_CAN_ERR_INFO_UNREC                0   /**< \brief ����¼CAN������Ϣ*/
#define AW_CAN_ERR_INFO_REC                  1   /**< \brief ��¼CAN������Ϣ */

/** \brief error information save or not*/
#define AW_CAN_RXD_BUFF_UNUSED               0   /**< \brief ��ʹ��RXD_BUFF*/
#define AW_CAN_RXD_BUFF_USED                 1   /**< \brief ʹ��RXD_BUFF */

/** \brief message flag bit define*/
#define AW_CAN_MSG_FLAG_REMOTE              0x0020
#define AW_CAN_MSG_FLAG_EXTERND             0x0040
#define AW_CAN_MSG_FLAG_ERROR               0x0080
#define AW_CAN_MSG_FLAG_FD_CTRL             0x0100
#define AW_CAN_MSG_FLAG_CTLR_CHCK           0x0300


/*******************************************************************************
                       CAN�����ʡ����ġ������ṹ��
*******************************************************************************/
/** \brief define CAN message type */
typedef struct aw_can_msg {
    uint32_t      timestamp; /**< \brief timestamp  ʱ��� */
    uint32_t      id; /**< \brief id ֡ID */

    /** \brief flags ������Ϣ�ı�־
     * -----------------------------------------------------------
     * | 15:10                             | 9:8 controller type |
     * -----------------------------------------------------------
     * -----------------------------------------------------------
     * | 7:iserrmsg |6:SEF | 5:SDF | 4:reseverd | 0:3 sendtype |
     * -----------------------------------------------------------
     * bit7:iserrmsg �Ƿ�Ϊ������Ϣ (1:err������Ϣ 0:normal��������)
     * bit6:SEF ֡��ʽ (1:extended��չ֡ 0:std ��׼֡)
     * bit5:SDF ֡���� (1:remoteԶ��֡   0:data����֡)
     * bit4:reseverd ����
     * bit0~3:��������  (sendtype:���궨��)
     */
    uint16_t      flags; /**< \brief msginfo ������Ϣ */
    uint8_t       chn; /**< \brief chn ��������ͨ���� */
    uint8_t       length; /**< \brief msglen ���ĳ��� */
}aw_can_msg_t;

/** \brief define CAN stander message type */
typedef struct aw_can_std_msg {
    aw_can_msg_t      can_msg;
    uint8_t           msgbuff[8];
}aw_can_std_msg_t;

/** \brief define CAN fd message type */
typedef struct aw_can_fd_msg {
    aw_can_msg_t      can_msg;
    uint8_t           msgbuff[64];
}aw_can_fd_msg_t;

/** \brief CAN����� */
typedef struct aw_can_transfer {
    aw_can_msg_t     *p_msgs;         /**< \brief ������CAN���Ļ������׵�ַ*/
    uint16_t          msgs_num;       /**< \brief �����䱨�ĸ��� */
    uint16_t          done_num;       /**< \brief �ɹ�����Ĵ��䱨�ĸ��� */
    aw_pfuncvoid_t    pfunc_complete; /**< \brief ������ɻص�����,�첽������Ч*/
    void             *p_arg;          /**< \brief ���ݸ� pfunc_complete �Ĳ��� */
    int               status;         /**< \brief ��ǰ������״̬����: */
                                      /**< \brief -ENOTCONN:δ�Ŷ�*/
                                      /**< \brief -EISCONN:�Ŷ�*/
                                      /**< \brief -EINPROGRESS:����*/
                                      /**< \brief -ETIME:��ʱ*/
                                      /**< \brief -ENETDOWN:���߹رգ��豸ֹͣ*/
                                      /**< \brief AW_OK:���*/
    void             *ctlrdata[2];    /**< \brief ������ʹ�� */
} aw_can_transfer_t;

/** \brief can baud rate parameters
* ----------------------------------------------------------
* | sync |        tseg1      |   tseg2                     |
* |                     sample point                       |
* ----------------------------------------------------------
* f(tq)= fpclk(can����ʱ��) /brp����Ƶֵ����ͨ��CAN������Ĭ�Ϸ�Ƶֵ+1
*
* baudrate = ftq / (sync + tseg1 + tseg2),
*
* sync: ͬ���Σ�Ĭ��Ϊ1
*
* tseg1:��λ�����1: tseg1��������Ĭ��+1����Tseg1����ϸ�ο�CAN����������
*
* tseg2:��λ�����2: tseg2��������Ĭ��+1����tseg2 >= sjw
*
* smp: ��������: �������������ߴ�����ͨ������Ϊ���β���
*
*/
typedef struct aw_can_baud_param {
    uint8_t     tseg1;          /**< \brief tseg1 ��λ��1 */
    uint8_t     tseg2;          /**< \brief tseg2 ��λ��2 */
    uint8_t     sjw;            /**< \brief sjw ͬ����ת��� */
    uint16_t    brp;            /**< \brief brp ��Ƶֵ */
    uint8_t     smp;            /**< \brief smp ����ģʽ0:���� 1:���� */
}aw_can_baud_param_t;

/** \brief ���������*/
typedef struct aw_can_err_cnt{
    uint8_t rx_err_cnt;         /**< \brief rx_error_cnt  ���մ�������� */
    uint8_t tx_err_cnt;         /**< \brief tx_error_cnt  ���ʹ�������� */
}aw_can_err_cnt_t;

/*******************************************************************************
                                                      �û�APP�����ص�������Ϣ�ṹ��
*******************************************************************************/
typedef uint32_t (*aw_can_timestamp_get_callback_t)(void);
typedef uint32_t (*aw_can_proto_rx_callback_t)     (int chn, aw_can_msg_t* p_msg);
typedef uint32_t (*aw_can_proto_tx_callback_t)     (int chn);
typedef uint32_t (*aw_can_bus_err_sta_callback_t)  (int chn,
                                                    aw_can_bus_err_t    err,
                                                    aw_can_bus_status_t sta);

typedef uint32_t (*aw_can_dev_wakeup_callback_t)   (int chn);

typedef struct aw_can_app_callbacks {
    /**< \brief  ��ȡϵͳʱ���   �ص�������ַ  */
    aw_can_timestamp_get_callback_t  timestamp_get_cb;

    /**< \brief  ���߽���һ֡ ����      �ص�������ַ
     *   ��������ֵ�������յ��ı����Ƿ����rngbuf��
     *   TRUE:�����棬FALSE:����
     */
    aw_can_proto_rx_callback_t       proto_rx_cb;

    /**< \brief  ���߷������        �ص�������ַ  */
    aw_can_proto_tx_callback_t       proto_tx_cb;

    /**< \brief  Ӧ�ò��������״̬����   �ص�������ַ
     * ��������ֵ����������Ϣ�Ƿ����rngbuf��
     * TRUE:�����棬FALSE:����
     */
    aw_can_bus_err_sta_callback_t    bus_err_sta_cb;

    /**< \brief  ���߻���               �ص�������ַ  */
    aw_can_dev_wakeup_callback_t     dev_wakeup_cb;

}aw_can_app_callbacks_t;

/*******************************************************************************
                           CAN �ӿں���
*******************************************************************************/
/**
 * \brief CAN��ʼ����������ʼ��ͨ����ģʽ�������ʣ��ص������Ȳ���
 *
 * \param[in] chn:       ѡ��ͨ����chn: 0~AW_CFG_NUM_CAN��
 *
 * \param[in] work_mode: ���� ����ģʽ��
 *                       AW_WORK_MODE_NROMAL(����ģʽ)��
 *                       AW_WORK_MODE_LISTEN_ONLY��ֻ��ģʽ����
 *
 * \param[in] p_baud:    ���ò����ʣ������ʲ����ο��ṹ��˵����
 *
 * \param[in] p_app_cb:  �û��ص���������Ӧ���¼����ص��û�APP��������ΪNULL��
 *
 * \retval aw_can_err_t: ���������ش����롣
 *
 * \code
 */
aw_can_err_t aw_can_init (int                     chn,
                          uint8_t                 work_mode,
                          aw_can_baud_param_t    *p_baud,
                          aw_can_app_callbacks_t *p_app_cb);

/**
 * \brief  start can
 *  ����CAN��ʹCAN��������������ģʽ�����Խ���ͨ�š�
 *
 * \param[in] chn:          ͨ���š�
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_start (int chn);

/**
 * \brief stop/reset can device
 * ��λCAN��������ʹCAN���������븴λģʽ��CAN����������������ͨ�š�
 *
 * \param[in] chn:          ͨ���š�
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_reset (int chn);

/**
 * \brief put into sleep mode
 * ��CAN����������˯��ģʽ
 *
 * \param[in] chn:          ͨ���š�
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_sleep (int chn);

/**
 * \brief force the CAN controller out of sleep mode
 *  ����CAN������
 *
 * \param[in] chn:          ͨ���š�
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_wakeup (int chn);

/**
 * \brief set the bit timing parameters of the controller
 * ����CAN������
 *
 * \param[in] chn:          ͨ���š�
 *
 * \param[in] p_baud:       �����ʲ�����
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_baudrate_set (int chn, aw_can_baud_param_t *p_baud);

/**
 * \brief set the bit timing parameters of the controller
 * ��ȡCAN������
 *
 * \param[in] chn:          ͨ���š�
 *
 * \param[in] p_baud:       �����ʲ�����
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_baudrate_get (int chn, aw_can_baud_param_t *p_baud);

/**
 * \brief clear send and receive error count of the controller
 *  ������ͺͽ��ܴ������
 *
 * \param[in] chn:          ͨ���š�
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_err_cnt_clr (int chn);

/**
 * \brief get send and receive error count
 * ��ȡ���ͺͽ��մ��������
 *
 * \param[in] chn:          ͨ���š�
 *
 * \param[in] p_can_err_reg:����Ĵ���ֵָ�롣
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_err_cnt_get (int chn, aw_can_err_cnt_t *p_err_cnt);


/** \brief �����˲���غ��� */
/**
 * \brief aw_can_set_filter_table
 * *
 *  ����CAN�˲����˽ӿں���Ϊͨ�ø�ʽ������ֻ�б��׵�ַ�ͱ��ȣ��ֽڸ�������
 *  ��ͬ�Ŀ������˲���ͬ����ʽҲ��ͬ����� �˲����ʽ���û��Լ����塣
 *
 * \param[in] chn:          ͨ���š�
 *
 * \param[in] p_filter_buff:�˲����׵�ַ��
 *
 * \param[in] length:       �˲����ȣ��ֽڸ�������
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_filter_table_set (int      chn,
                                      uint8_t *p_filter_buff,
                                      size_t   length);
/**
 * \brief aw_can_get_filter_table
 * *
 *  ��ȡCAN�˲����˽ӿں���Ϊͨ�ø�ʽ������ֻ�б��׵�ַ�ͱ��ȣ��ֽڸ�������
 *  ��ͬ�Ŀ������˲���ͬ����ʽҲ��ͬ����� �˲����ʽ���û��Լ����塣
 *
 * \param[in] chn:          ͨ���š�
 *
 * \param[in] p_filter_buff:�˲����׵�ַ��
 *
 * \param[in] p_length:     �����˲����ȣ��ֽڸ�������
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_filter_table_get (int       chn,
                                      uint8_t  *p_filter_buff,
                                      size_t   *p_length);

/**
 * \brief ����CAN����ṹ�����
 *
 * \param p_transfer        CAN���Ĵ���������ָ��
 * \param p_msgs            ��ɴ����ı���
 * \param trans_num         ���ĵĸ���
 * \param pfunc_complete    ������ɻص�����
 *                          (������ aw_can_msgs_send_async() ʱ�˲�����Ч,
 *                          ���� aw_can_msgs_send_sync()ʱ��������Ч)
 * \param p_arg             ���ݸ��ص������Ĳ���
 *
 * \par ����
 * \code
 * #include "aw_can.h"
 *
 * aw_can_transfer_t transfer;  // ����������ṹ��
 * aw_can_std_msg_t  msgs[2];   // ��ɴ����ı��Ļ�����
 *
 * // ���ô��������ṹ��
 * aw_i2c_mktrans(&transfer,    // ����������ṹ
 *                msgs,         // ��ɴ����ı��Ļ������׵�ַ
 *                2��                             // �������
 *                my_callback,  // ������ɻص�����
 *                my_arg);      // ������ɻص������Ĳ���
 *
 *  ����ʵ�֣�
 *  p_transfer->p_msgs         = (aw_can_msg_t*)p_msgs;
 *  p_transfer->msgs_num       = msgs_num;
 *  p_transfer->done_num       = 0;
 *  p_transfer->pfunc_complete = pfunc_complete;
 *  p_transfer->p_arg          = p_arg;
 *  p_transfer->status         = -ENOTCONN;
 *
 *
 * \endcode
 */
 void aw_can_mkmsg (aw_can_transfer_t  *p_transfer,
                    aw_can_std_msg_t   *p_msgs,
                    uint16_t            msgs_num,
                    aw_pfuncvoid_t      pfunc_complete,
                    void               *p_arg);

/**
 * \brief aw_can_msgs_send_async
 * ����һ��CAN���ĵ��첽���䣬�ӿڲ���ʹ�ô���飬
 * �����ǰ�д�������ڴ�������´������ӵ������б�
 * �û��Ĵ�����������Ч����飬δ�������֮ǰ�����ͷŸô���飬������ʧ�ܡ�
 * ��������������ο�����aw_can_mkmsg���ݣ�
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] p_transfer:   �����p_transfer�ĵ�ַ��
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_msgs_send_async (int                chn,
                                     aw_can_transfer_t *p_transfer);

/**
 * \brief synchronous can transfer ͬ������
 * ����һ��ͬ�����䣬����һ��CAN���ģ����ĸ������û�����
 * �û��Ĵ�����������Ч����飬δ�������֮ǰ�����ͷŸô���飬������ʧ�ܡ�
 *
 * \param[in] p_serv:       CAN�����ַ��
 *
 * \param[in] p_transfer:   ������ַ��
 *
 * \param[in] timeout:      ���䳬ʱ�䡣
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_msgs_send_sync (int                chn,
                                    aw_can_transfer_t *p_transfer,
                                    uint32_t           timeout);

/**
 * \brief saw_can_fd_msgs_send
 * CANFD�ı��ķ��ͺ�����CANFD������ʱ��ʹ�ã�
 * ���ĸ�ʽ����CANFD���ĸ�ʽ����ο���aw_can_fd_msg_t
 * �û��Ĵ�����������Ч����飬δ�������֮ǰ�����ͷŸĴ���飬������ʧ�ܡ�
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] p_msgs:       FD���Ļ�������ַ��
 *
 * \param[in] msgs_num:     ���������ĸ�����
 *
 * \param[in] p_done_num:   ʵ�ʷ��ͳɹ�������ַ��
 *
 * \param[in] timeout:      ���ͳ�ʱʱ�䣬�����0��
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_fd_msgs_send (int              chn,
                                  aw_can_fd_msg_t *p_msgs,
                                  uint32_t         msgs_num,
                                  uint32_t        *p_done_num,
                                  uint32_t         timeout);

/**
 * \brief saw_can_std_msgs_send
 * ��׼��CAN���ķ��ͺ���������CAN������ʱ��ʹ�ã�
 * ���ĸ�ʽ���ñ�׼CAN���ĸ�ʽ����ο���aw_can_std_msg_t
 * �û��Ĵ�����������Ч����飬δ�������֮ǰ�����ͷŸĴ���飬������ʧ�ܡ�
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] p_msgs:       ��׼���Ļ�������ַ��
 *
 * \param[in] msgs_num:     ���������ĸ�����
 *
 * \param[in] p_done_num:   ʵ�ʷ��ͳɹ�������ַ��
 *
 * \param[in] timeout:      ���ͳ�ʱʱ�䣬�����0��
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_std_msgs_send (int               chn,
                                   aw_can_std_msg_t *p_msgs,
                                   uint32_t          msgs_num,
                                   uint32_t         *p_done_num,
                                   uint32_t          timeout);

/**
 * \brief aw_can_msgs_stop_send
 * ֹͣ���ͺ�����
 * ע�⣬�����첽����ֹͣ���ͣ��û����ô˽ӿ�aw_can_msgs_send_async��ʹ�á�
 * ʹ��ͬ�����䣬������ʱ�¼���ϵͳ���Զ�����ֹͣ���䣬�û�������á�
 * �û���ֹͣ��ǰ���ķ��ͣ������������б�
 * �û��ӿں�����
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_msgs_stop_send (int chn);


/** \brief ������غ��� */
/**
 * \brief aw_can_rcv_msgs_num
 * ��ȡ���ջ������Ѿ�����can���ĵĸ�����
 *
 * \param[in] chn:      CANͨ���š�
 *
 * \retval frame count: ���������ĸ�����
 *
 */
uint32_t aw_can_rcv_msgs_num (int chn);

/**
 * \brief aw_can_rcv_fifo_size
 * ������ֻ��С��
 *
 * \param[in] chn:     CANͨ���š���
 *
 * \retval fifo size:  ������ʵ�ʴ�С�����ĸ�������
 *
 */
uint32_t aw_can_rcv_fifo_size (int chn);

/**
 * \brief aw_can_msgs_rcv
 * ����CAN���ģ�������ֻҪ�����ݾͻ�ɹ����أ�
 * ʵ�ʸ���ֵ��aw_can_transfer_t��Ԫ��done_num�У�
 * ֻ�л�����û�����ݵ�ʱ�򣬳�ʱʱ����Ч��
 * Ϊ�˱�֤��������ʵʱ�ԣ��ڳ�ʱ�ȴ�ʱ�򣬵����յ���Ч���ݣ����̷��ء�
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] p_transfer:   ������ַ��
 *
 * \param[in] timeout:      ���ջ��������ޱ��ĵĳ�ʱʱ�䡣
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_msgs_rcv (int                chn,
                              aw_can_transfer_t *p_transfer,
                              uint32_t           timeout);

/**
 * \brief aw_can_std_msgs_rcv
 * ���ա���׼CAN���ġ���������ֻҪ�����ݾͻ�ɹ����أ�
 * ʵ�ʸ���ֵ�ڴ����p_done_num�У�
 * ֻ�л�����û�����ݵ�ʱ�򣬳�ʱʱ����Ч��
 * Ϊ�˱�֤��������ʵʱ�ԣ��ڳ�ʱ�ȴ�ʱ�򣬵����յ���Ч���ݣ����̷��ء�
 * �û��ӿں�����
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] p_msgs:       ���ձ��Ļ�������ַ��
 *
 * \param[in] msgs_num:     ���������ĸ�����
 *
 * \param[in] p_done_num:   ʵ�ʶ�ȡ������ַ��
 *
 * \param[in] timeout:      ���ջ��������ޱ��ĵĳ�ʱʱ�䡣
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_std_msgs_rcv (int               chn,
                                  aw_can_std_msg_t *p_msgs,
                                  uint32_t          msgs_num,
                                  uint32_t         *p_done_num,
                                  uint32_t          timeout);

/**
 * \brief aw_can_std_msgs_rcv
 * ���ձ�׼CAN���ģ�������ֻҪ�����ݾͻ�ɹ����أ�
 * ʵ�ʸ���ֵ�ڴ����p_done_num�У�
 * ֻ�л�����û�����ݵ�ʱ�򣬳�ʱʱ����Ч��
 * Ϊ�˱�֤��������ʵʱ�ԣ��ڳ�ʱ�ȴ�ʱ�򣬵����յ���Ч���ݣ����̷��ء�
 * �û��ӿں�����
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] p_msgs:       ����FD���Ļ�������ַ��
 *
 * \param[in] msgs_num:     ���������ĸ�����
 *
 * \param[in] p_done_num:   ʵ�ʶ�ȡ������ַ��
 *
 * \param[in] timeout:      �ޱ��ĳ�ʱʱ�䡣
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_fd_msgs_rcv (int              chn,
                                 aw_can_fd_msg_t *p_msgs,
                                 uint32_t         msgs_num,
                                 uint32_t        *p_done_num,
                                 uint32_t         timeout);
/**
 * \brief дCAN�Ĵ���
 * дCAN�Ĵ�����������CAN������ܲ������ģ������CAN����
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] offset:       �Ĵ�����ַ
 *
 * \param[in] p_data:       ���ݡ�
 *
 * \param[in] length:       ���ȡ�
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_reg_write (int      chn,
                               uint32_t offset,
                               uint8_t *p_data,
                               size_t   length);

/**
 * \brief ��ȡCAN�Ĵ���
 * ��ȡCAN�Ĵ�����������CAN������ܲ������ģ������CAN����
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] offset:       �Ĵ�����ַ
 *
 * \param[in] p_data:       ��ȡ���ݡ�
 *
 * \param[in] length:       ��ȡ���ȡ�
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_reg_read (int      chn,
                              uint32_t offset,
                              uint8_t *p_data,
                              size_t   length);
/**
 * \brief ��CAN�Ĵ���д���ģ�
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] p_msg:        ����ָ��
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_reg_msg_write (int                 chn,
                                   aw_can_msg_t       *p_msg);

/**
 * \brief ��ȡCAN���ģ�
 * ��CAN�Ĵ����ж�ȡ����
 *
 * \param[in] chn:          CANͨ���š�
 *
 * \param[in] p_msg:        ����ָ��
 *
 * \retval aw_can_err_t:    ���������ش����롣
 *
 */
aw_can_err_t aw_can_reg_msg_read  (int                 chn,
                                   aw_can_msg_t       *p_msg);

#ifdef __cplusplus
}
#endif

#endif /* __AW_CAN_H */
