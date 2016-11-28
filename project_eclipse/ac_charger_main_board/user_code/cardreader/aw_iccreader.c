/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief  ������ʵ��
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-12  xjc, first implementation
 * \endinternal
 */

#include "aw_iccreader.h"
#include "aw_serial.h"
#include "aw_ioctl.h"
#include "aw_delay.h"

#include "aw_vdebug.h"
#include "aw_task.h"                    /* ��������� */
#include <string.h>

#define __ICC_RX_BYTE_TIMEOUT_CFG    5    /* ���������յ��ֽڳ�ʱ���ã���λms */
#define __ICC_RX_FRAME_TIMEOUT_CFG   1000 /* ����������֡��ʱ��ʱ���ã���λms */


#define __ICC_START_CODE  (0x02u)  /* Э����ʼ��     */
#define __ICC_END_CODE    (0x03u)  /* Э�������     */


#define __ICC_PROTOCOL_LENGTH 5     /**< \brief ͨѶ֡Э������ֽ��� */
#define __ICC_INFO_MAX_LENGTH 265   /**< \brief ͨѶ֡���ݵ�Ԫ����ֽ���(��������δ�����������APDU���ֽ�Ҫ��) */
/** \brief ͨѶ֡��Ϣ��С�ֽ�������֡��ʽ�� */
#define __ICC_PACKET_MIN_SIZE (__ICC_PROTOCOL_LENGTH)
/** \brief ͨѶ֡��Ϣ����ֽ�������֡��ʽ��*/
#define __ICC_PACKET_MAX_SIZE (__ICC_PROTOCOL_LENGTH + __ICC_INFO_MAX_LENGTH)

#define __ICC_CMD_EXE_STATE(rbuf, rlen) \
                            ((rbuf[rlen - 2] == 0) && \
                             (rbuf[rlen - 1] == 0))

#define __CMD_S50S70_KEY_AUTH   0x0246 /* ֱ����Կ��֤ */
#define __CMD_S50S70_BLK_READ   0x0247 /* ��� */
#define __CMD_S50S70_BLK_WRITE  0x0248 /* ��д */
#define __CMD_S50S70_VAL_OPT    0x024A /* ֵ���� */
#define __CMD_S50S70_VAL_SET    0x0250 /* ֵ���� */
#define __CMD_S50S70_VAL_GET    0x0251 /* ֵ��ȡ */

#define __CMD_CTRL_BAUD_SET     0x3001 /* ���������� */
#define __CMD_CTRL_INFO_GET     0x3111 /* ��Ϣ��ȡ */
#define __CMD_CTRL_BUZZER_SET   0x3113 /* ���������� */
#define __CMD_CTRL_LED_SET      0x3114 /* LED���� */
#define __CMD_CTRL_RF_OPEN      0x3190 /* ����Ƶ */
#define __CMD_CTRL_RF_CLOSE     0x3191 /* �ر���Ƶ */

#define __CMD_CARD_POWER_ON     0x3222 /* �Ӵ����ϵ� */
#define __CMD_CARD_POWER_OFF    0x3223 /* �Ӵ������� */
#define __CMD_CARD_ACTIVE       0x3224 /* ����ǽӴ��� */
#define __CMD_CARD_APDU         0x3226 /* APDU����� */


/** 
 * \brief ͨ�����ڷ�������
 * \param [in] handle  : ������ʵ��
 * \param [in] p_txbuf : �������ݻ�����
 *                       p_txbuf[0] �̶����ڿ�����ʹ��
 * \param [in] nbytes  : �����ֽ���
 *                       nbytes �������0����Ϊ������һ�������룩
 *
 * \return AW_OK      : ͨ�ųɹ�
 * \return -AW_EINVAL : ��������
 * \return -AW_EIO    : Ӳ��ͨ��IO���ʹ���
 * 
 * \note Э������ͨ�÷��ͽӿڣ������Զ����֡ͷ����ַ�Լ�У����Ϣ��
 *      �û�ֻ����Ĵ����͵Ŀ����룬�Լ����ݱ�ʶ�������򣩼���
 */
aw_local aw_err_t __serial_send(struct aw_iccreader* handle,
                                const uint8_t       *p_txbuf,
                                uint32_t             nbytes)
{
    uint8_t tx_data[__ICC_PACKET_MAX_SIZE];
    uint32_t i   = 0;
    uint8_t  sum = 0;  /* 8λУ��� */
    
    if ((NULL == handle)||
        (NULL == handle->p_transfer) ||
        ((nbytes-2) > __ICC_INFO_MAX_LENGTH)) {
        return -AW_EINVAL;
    }
   
    tx_data[0] = __ICC_START_CODE;
    tx_data[1] = (nbytes >> 8);
    tx_data[2] = (nbytes >> 0);
    tx_data[3] = p_txbuf[0];
    tx_data[4] = p_txbuf[1];
    memcpy(&tx_data[5], &p_txbuf[2], (nbytes-2));
    sum  = tx_data[3];
    sum ^= tx_data[4];
    for (i = 0; i < (nbytes-2); i++) {
        sum ^= tx_data[5+i];
    }
    tx_data[5 + (nbytes-2)] = sum;
    tx_data[5 + (nbytes-2) + 1] = __ICC_END_CODE;
    
    /* ��������֡ */
    if ((nbytes + 5) != aw_serial_poll_write(handle->p_transfer->uart_num,
                                              (char *)tx_data,
                                              nbytes + 5)) {
        return -AW_EIO;
    }
    return AW_OK;
}


/**
 * \brief �Ӵ����ж�ȡ����
 * \param [in] handle    : ������ʵ��
 * \param [out] p_rxbuf  : �洢���ݵ�ָ��
 * \param [in]  nbytes   : ���ո���
 * \param [in]  timeout  : �������ʱʱ�䣬��λms
 *
 * \return   >0          : ʵ�ʶ�ȡ���ֽ���
 * \return -AW_ETIMEDOUT : ��ʱ����
 * \return -AW_ENOMEM    : ���ջ�����p_rxbuf�ռ䲻��
 *
 * \note �����ճɹ���p_rxbuf[nbytes-1],p_rxbuf[nbytes-2]Ϊ���յ�״̬��
 */
aw_local int __recevie_timeout (struct aw_iccreader* handle,
                                 uint8_t  *p_rxbuf,
                                 uint8_t   nbytes,
                                 uint32_t  timeout)

{
#define __ICC_STATE_START_CODE_FIND   0  /* ����Э��ͷ */
#define __ICC_STATE_CTRL_CODE_GET     1  /* ��ȡ������  */
#define __ICC_STATE_DAT_GET           2  /* ��ȡ������ ��У����Լ������� */

    uint32_t uart_num;
    int      state = __ICC_STATE_START_CODE_FIND;
    int      cnt   = 0; /* ĿǰЭ�����ݵļ��� */
    uint8_t rx_data[__ICC_PACKET_MAX_SIZE], sum;
    aw_tick_t start_ticks, end_ticks;
    uint32_t  timeout_ms;
    uint8_t  *p_rbuf = &rx_data[0];
    uint16_t  rlen = 1, rlen_tmp;

    uart_num = handle->p_transfer->uart_num;
    start_ticks = aw_sys_tick_get();

    while (1) {

        if (__ICC_STATE_START_CODE_FIND == state) {
            /* ֡��ʼʱ��Ҫ����Ӧ��ʱ*/
            end_ticks  = aw_sys_tick_get();
            timeout_ms = aw_ticks_to_ms(end_ticks - start_ticks);
            if (timeout_ms > timeout) {
                return -AW_ETIMEDOUT;
            }
        }

        /* ��ȡ֡��ʼ���͵�ַ��һ֡������12���ֽ� */
        if (0 >= (rlen_tmp = aw_serial_read(uart_num, (char *)p_rbuf, rlen))) {
            if (__ICC_STATE_START_CODE_FIND != state) {
                /* ֡��ʼ��Ҫ����ֽڳ�ʱ*/
                return -AW_ETIMEDOUT;
            }
            continue;
        } else if (rlen != rlen_tmp){
            rlen  -= rlen_tmp;
            p_rbuf = p_rbuf + rlen_tmp;
            continue;
        }

        switch (state) {
        case __ICC_STATE_START_CODE_FIND:
             if (rx_data[0] == __ICC_START_CODE) {
                 rlen = 4;
                 p_rbuf = &rx_data[1];
                 state = __ICC_STATE_CTRL_CODE_GET;
             }
             break;

        case __ICC_STATE_CTRL_CODE_GET:
            rlen = (rx_data[1] << 8) | (rx_data[2]);
            if ((rlen > __ICC_INFO_MAX_LENGTH) || (rlen < 2)) {
                return -AW_ENOMEM;
            }
            p_rbuf = &rx_data[5];
            state  = __ICC_STATE_DAT_GET;
            break;

        case __ICC_STATE_DAT_GET:
            rlen = (rx_data[1] << 8) | (rx_data[2]);
            if (__ICC_END_CODE != rx_data[rlen + 4]) {
                return AW_ERROR; /* ֡��ʽ���� */
            }

//            if (rlen != nbytes) {
//                return AW_ERROR; /* ֡��ʽ���� */
//            }

            /* ����У��� */
            sum  = rx_data[3];
            for (cnt = 1; cnt < rlen; cnt++) {
                sum ^= rx_data[3 + cnt];
            }

            if (sum != rx_data[rlen + 3]) {
                return AW_ERROR;  /* ֡��ʽ���� */
            }

            memcpy(p_rxbuf, &rx_data[5], rlen-2);
            p_rxbuf[rlen - 2] = rx_data[3];
            p_rxbuf[rlen - 1] = rx_data[4];
            return rlen;
            break;

        default:break;
        }
    }
    return AW_ERROR;
}
/** 
 * \brief ��������
 * \param [in] handle  : ������ʵ��
 * \param [in] p_rxbuf : �������ݻ�����
 * \param [in] nbytes  : �����ֽ���
 *
 * \return   >0          : ʵ�ʶ�ȡ���ֽ���
 * \return -AW_EINVAL : ��������
 * \return -AW_ETIMEDOUT : ��ʱ����
 *
 * \note ����ͨ�ý��սӿڣ���������ʶ��֡ͷ����ַ�Լ�У����Ϣ��
 *      �û�ֻ����Ľ��յ��Ŀ����룬�Լ����ݣ��������ݱ�ʶ������.
 *    �����ճɹ���p_rxbuf[nbytes-2], p_rxbuf[nbytes-1]Ϊ���յ�״̬��
 *    �������ݸ�ʽ
 *     ������ | ״̬�֣�2�ֽڣ�
 *
 */
aw_local int __serial_receive(struct aw_iccreader* handle,
                              uint8_t             *p_rxbuf,
                              uint32_t             nbytes)
{

    if ((NULL == handle)                     ||
        (NULL == handle->p_transfer)         ||
        (nbytes < 2) || (nbytes > __ICC_INFO_MAX_LENGTH)) {
        return -AW_EINVAL;
    }

    return __recevie_timeout(handle, p_rxbuf, nbytes, __ICC_RX_FRAME_TIMEOUT_CFG);
}


/**
 * \brief ��������
 * \param[in]  handle   : ָ���������ʵ��
 * \param[in]  cmd      : ��������
 * \param[in]  p_txbuf  : ���ͻ�����
 * \param[in]  tlen     : ���ͻ���������
 * \param[out] p_rxbuf  : ���ջ�����
 * \param[in]  rlen     : ���ջ���������
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_transfer(struct aw_iccreader* handle,
                               uint32_t  cmd,
                               void     *p_txbuf,
                               uint16_t  tlen,
                               void     *p_rxbuf,
                               uint16_t  rlen)
{
    uint8_t  buf[__ICC_PACKET_MAX_SIZE] = {0};
    int      len      = 0;

    if ((NULL == handle)              ||
        (NULL == handle->p_transfer)  ||
        (NULL == handle->pfn_send)    ||
        (NULL == handle->pfn_receive) ) {
        return -AW_EINVAL;
    }

    if (((tlen + 2) > __ICC_PACKET_MAX_SIZE) ||
        ((rlen + 2) > __ICC_PACKET_MAX_SIZE)) {
        return -AW_EINVAL;
    }

    buf[0] = (uint8_t)(cmd >> 8);
    buf[1] = (uint8_t)(cmd >> 0);
    memcpy(&buf[2], p_txbuf, tlen);
    /* �������� */
    if (AW_OK != handle->pfn_send(handle, buf, 2+tlen)) {
        return  AW_ERROR;
    }
    /* ��ȡ���� */
    if (0 > (len = handle->pfn_receive(handle, buf, 2+rlen))) {
        return  AW_ERROR;
    }

    if (!__ICC_CMD_EXE_STATE(buf, len)) {
        /* �쳣��Ӧ֡ */
        //memcpy(p_rxbuf, &buf[len-2], 2);
        return -AW_EPERM;
    }
    memcpy(p_rxbuf, buf, rlen);
    return AW_OK;
}

/**
 * \brief ���ö�����ģ��ͨ�Ų�����
 * \param[in]  handle    : ָ���������ʵ��
 * \param[in]  baud_code : �����ʴ���
 *                         0x00 : 9600
 *                         0x01 : 19200
 *                         0x02 : 38400
 *                         0x03 : 57600
 *                         0x04 : 115200
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_baud_set (struct aw_iccreader* handle, uint8_t baud_code)
{
    return aw_iccreader_transfer(handle, __CMD_CTRL_BAUD_SET, &baud_code, 1, NULL, 0);
}

/**
 * \brief ��ȡ�������汾��Ϣ
 * \param[in]  handle    : ָ���������ʵ��
 * \param[in]  p_rxbuf   : ��Ű汾��Ϣ�Ļ�����
 * \param[in]  rlen      : ��ȡ�汾��Ϣ���ֽ���
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_info_get (struct aw_iccreader* handle, void *p_rxbuf, uint32_t rlen)
{
    return aw_iccreader_transfer(handle, __CMD_CTRL_INFO_GET, NULL, 0, p_rxbuf, rlen);
}

/**
 * \brief ��ȡ�������汾��Ϣ
 * \param[in]  handle    : ָ���������ʵ��
 * \param[in]  dlytime   : ����������ʱ��
 * \param[in]  times     : �������������
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_buzzer_set (struct aw_iccreader* handle, uint16_t dlytime, uint8_t times)
{
    uint8_t buf[3] = {dlytime>>8, dlytime, times};

    return aw_iccreader_transfer(handle, __CMD_CTRL_BUZZER_SET, buf, 3, NULL, 0);
}

/**
 * \brief ����LED״̬
 * \param[in]  handle    : ָ���������ʵ��
 * \param[in]  led1_en   :LED1���ƣ�TRUE-���ƣ�FALSE-���
 * \param[in]  led2_en   :LED2���ƣ�TRUE-���ƣ�FALSE-���
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_led_set (struct aw_iccreader* handle, bool_t led1_en, bool_t led2_en)
{
    uint8_t state = (led1_en ? (1 << 7) : 0) | (led2_en ? (1 << 6) : 0);

    return aw_iccreader_transfer(handle, __CMD_CTRL_LED_SET, &state, 1, NULL, 0);
}

/**
 * \brief ����Ƶ
 * \param[in]  handle    : ָ���������ʵ��
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_rf_open (struct aw_iccreader* handle)
{
    return aw_iccreader_transfer(handle, __CMD_CTRL_RF_OPEN, NULL, 0, NULL, 0);
}


/**
 * \brief �ر���Ƶ
 * \param[in]  handle    : ָ���������ʵ��
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_rf_close (struct aw_iccreader* handle)
{
    return aw_iccreader_transfer(handle, __CMD_CTRL_RF_CLOSE, NULL, 0, NULL, 0);
}

/**
 * \brief ��ֱ����Կ��֤
 * \param [in] handle   : ָ���������ʵ��
 * \param [in] key_type : ��Կ���ͣ� ��ԿA #AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYA
 *                                 ��ԿB #AW_ICCREADER_KEY_AUTH_KEYTYPE_KEYB
 * \param [in] p_uid    : ����UID������
 * \param [in] uid_len  : ����UID�ĳ���( ֻ����4���ֽ�)
 * \param [in] p_uid    : ��Կ
 * \param [in] uid_len  : ��Կ�ĳ���( ֻ����6��16���ֽ�)
 * \param [in] block    : ��֤��
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_key_auth (struct aw_iccreader* handle,
                                uint8_t              key_type,
                                uint8_t             *p_uid,
                                uint8_t              uid_len,
                                uint8_t             *p_key,
                                uint8_t              key_len,
                                uint8_t              block)
{
    uint8_t buf[22] = {0};

    buf[0] = key_type;
    memcpy(&buf[1], p_uid, 4);
    memcpy(&buf[1+4], p_key, key_len);
    buf[1+4+key_len] = block;

    return aw_iccreader_transfer(handle, __CMD_S50S70_KEY_AUTH, buf, 2+4+key_len, NULL, 0);
}

/**
 * \brief ��ȡĳ�������
 * \param [in] handle   : IC����������ʵ��
 * \param [in] block    : ��֤��
 * \param [out] p_buf   : �������������ǿ�ĳ��ȣ�16�ֽڣ�
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_block_read (struct aw_iccreader *handle,
                                  uint8_t             *p_buf,
                                  uint8_t              block)
{
    return aw_iccreader_transfer(handle, __CMD_S50S70_BLK_READ, &block, 1, p_buf, 16);
}

/**
 * \brief дĳ�������
 * \param [in] handle   : IC����������ʵ��
 * \param [in] block    : ��֤��
 * \param [out] p_buf   : �������������ǿ�ĳ��ȣ�16�ֽڣ�
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_block_write (struct aw_iccreader *handle,
                                   uint8_t             *p_buf,
                                   uint8_t              block)
{
    uint8_t buf[17] = {0};

    buf[0] = block;
    memcpy(&buf[1], p_buf, 16);
    return aw_iccreader_transfer(handle, __CMD_S50S70_BLK_WRITE, buf, 17, NULL, 0);
}

/**
 * \brief ����s50s70��
 * \param [in] handle   : IC����������ʵ��
 * \param [in] aw_iccreader_s50s70_ci_t    : �������Ϣ
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_s50s70_active (struct aw_iccreader      *handle,
                                     aw_iccreader_s50s70_ci_t *p_card)
{
    uint8_t buf[2] = {0};
    return aw_iccreader_transfer(handle, __CMD_CARD_ACTIVE, buf, 2, p_card, 6);
}


/**
 * \brief S50S70������
 * \param[in]  handle  : ָ��IC����ʵ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_iccreader_halt(struct aw_iccreader *handle)
{

    return AW_OK;
}

/**
 * \brief ���Ӵ����ϵ�
 * \param [in] handle   : IC����������ʵ��
 * \param [in] card_no  : �����ţ��û����� 00H~0FH�� PSAM ����10H~1FH��
 * \param [in] dly_time : �ȴ��忨ʱ��(ms)��0 ����ȴ����޿�ֱ�ӷ��أ�
 * \param [in] dly_time : �ȴ��忨ʱ��(ms)��0 ����ȴ����޿�ֱ�ӷ��أ�
 * \param [in] p_info   : ����Ϣ
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_samc_power_on(struct aw_iccreader *handle,
                                    uint8_t card_no,
                                    uint16_t dly_time,
                                    aw_iccreader_samc_info_t *p_info)
{
    uint8_t buf[3] = {0};

    buf[0] = (uint8_t)(dly_time >> 8);
    buf[1] = (uint8_t)(dly_time >> 0);
    buf[2] = card_no;
    return aw_iccreader_transfer(handle, __CMD_CARD_POWER_ON, buf, 3, p_info, 50);
}

/**
 * \brief ���Ӵ����µ�
 * \param [in] handle   : IC����������ʵ��
 * \param [in] card_no  : �����ţ��û����� 00H~0FH�� PSAM ����10H~1FH��
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 * \return -AW_EPERM   : �����������豸��Ӧ���쳣֡��
 */
aw_err_t aw_iccreader_samc_power_off(struct aw_iccreader *handle,
                                    uint8_t               card_no)
{
    return aw_iccreader_transfer(handle, __CMD_CARD_POWER_OFF, &card_no, 1, NULL, 0);
}

/**
 * \brief ��������ʼ��
 * \param[in]  handle  : ָ��IC����ʵ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
 aw_err_t aw_iccreader_inst_init (struct aw_iccreader           *handle,
                                  const aw_iccreader_transfer_t *p_transfer)
{
    uint32_t uart_num;

    if ((NULL == handle) ||
        (NULL == p_transfer)) {
        return -AW_EINVAL;
    }
    uart_num = p_transfer->uart_num;

    handle->pfn_send    = __serial_send;
    handle->pfn_receive = __serial_receive;
    handle->p_transfer  = p_transfer;

    /* ���ڳ�ʼ������, �粨���� 115200 */
    aw_serial_ioctl(uart_num,
                    SIO_BAUD_SET,
                   (void *)(p_transfer->uart_buad));
    /* ���ڲ��� �磺8 ������λ 1 ��ֹͣλ������żУ�� */
    aw_serial_ioctl(uart_num,
                    SIO_HW_OPTS_SET,
                    (void *)(p_transfer->uart_format));
    /* ���ö�ȡ��ʱʱ�� */
    aw_serial_ioctl(uart_num, AW_TIOCRDTIMEOUT, (void *)__ICC_RX_BYTE_TIMEOUT_CFG);

    return AW_OK;
}



