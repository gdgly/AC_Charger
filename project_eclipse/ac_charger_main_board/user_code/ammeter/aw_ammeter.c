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

#include "aw_ammeter.h"
#include "aw_serial.h"
#include "aw_ioctl.h"
#include "aw_delay.h"

#include "aw_vdebug.h"
#include "aw_task.h"                    /* ��������� */
#include <string.h>

#define __DL645_RX_BYTE_TIMEOUT_CFG    100   /* ���������յ��ֽڳ�ʱ���ã���λms */
#define __DL645_RX_FRAME_TIMEOUT_CFG   1000 /* ����������֡��ʱ��ʱ���ã���λms */


#define __DL645_GUIDE_CODE  (0xFEu)  /* DL645Э�������� */
#define __DL645_START_CODE  (0x68u)  /* DL645��ʼ��     */
#define __DL645_END_CODE    (0x16u)  /* DL645������     */
#define __DL645_ADDR_LEN    (6)      /* ��ַ���ȣ���λ�ֽ� */

#define __DL645_07_CTRL_CODE_DATGET    (0x11u)        /* ��ȡ���ݿ�����(07��汾) */
#define __DL645_07_DATAID_ENERGY       (0x00010000u)  /* ������ȡ��ʶ(07��汾) */
#define __DL645_07_DATAID_A_CURR       (0x02020100u)  /* A�������ʶ(07��汾) */
#define __DL645_07_DATAID_A_VOL        (0x02010100u)  /* A���ѹ��ʶ(07��汾) */
#define __DL645_07_DATAID_POWER        (0x02030000u)  /* ˲ʱ�й����ʱ�ʶ(07��汾) */

#define __DL645_97_CTRL_CODE_DATGET    (0x01u)        /* ��ȡ���ݿ�����(97��汾) */
#define __DL645_97_DATAID_ENERGY       (0x9010u)     /* ������ȡ��ʶ(97��汾) */
#define __DL645_97_DATAID_A_CURR       (0xB621u)     /* A�������ʶ(97��汾) */
#define __DL645_97_DATAID_A_VOL        (0xB611u)     /* A���ѹ��ʶ(97��汾) */
#define __DL645_97_DATAID_POWER        (0xB630u)     /* ˲ʱ�й����ʱ�ʶ(97��汾) */


#define __DL645_PROTOCOL_LENGTH 12    /**< \brief ͨѶ֡Э���ֽ��� */
#define __DL645_INFO_MAX_LENGTH 200   /**< \brief ͨѶ֡����ֽ��� */
/** \brief ͨѶ֡��Ϣ��С�ֽ�������֡��ʽ�� */
#define __DL645_PACKET_MIN_SIZE (__DL645_PROTOCOL_LENGTH)
/** \brief ͨѶ֡��Ϣ����ֽ�������֡��ʽ��*/
#define __DL645_PACKET_MAX_SIZE (__DL645_PROTOCOL_LENGTH + \
                                 __DL645_INFO_MAX_LENGTH)

/** \brief ����֧��DL645 07��Э��  */
#define __DL645_07_SUPPORT   1

/** \brief ����֧��DL645 97��Э��  */
#define __DL645_97_SUPPORT   0

/** \brief ����֧��modbusЭ��  */
#define __MODBUS_SUPPORT     0

#if __MODBUS_SUPPORT
#include "modbus/aw_mb_master.h"
#endif
/*******************************************************************************
  macro operate
*******************************************************************************/
/** \brief �ɵ����ָ��ת�ɵ�ֱ��������� */
#define __AMETER_DC_DECL(p_ammeter_dc, handle) \
                   aw_ammeter_dc_t *p_ammeter_dc = (aw_ammeter_dc_t *)((handle))

/** \brief ��ͨ���ุ��ָ��ת�ɵ�DL645ͨ������ */
#define __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle) \
                   aw_ammeter_transfer_dl645_t *p_ammeter_transfer_dl645 = \
                                      (aw_ammeter_transfer_dl645_t *)((handle))


/** \brief ��ͨ���ุ��ָ��ת�ɵ�modbus-rtuͨ������ */
#define __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, handle) \
                   aw_ammeter_transfer_mb_t *p_ammeter_transfer_mb = \
                                      (aw_ammeter_transfer_mb_t *)((handle))

/**
 * \brief ͨ��ʵ����ʼ��
 * \param[in]  handle  : ָ�����ָ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_transfer_inst_init (aw_ammeter_transfer_t* handle);

#if __DL645_07_SUPPORT || __DL645_97_SUPPORT
/** 
 * \brief ��DL645Э�鷢������
 * \param [in] handle  : ���ͨ�Ŵ����ʵ��
 * \param [in] p_txbuf : �������ݻ�����
 *                       p_txbuf[0] �̶����ڿ�����ʹ��
 * \param [in] nbytes  : �����ֽ���
 *                       nbytes �������0����Ϊ������һ�������룩
 *
 * \return AW_OK      : ͨ�ųɹ�
 * \return -AW_EINVAL : ��������
 * \return -AW_EIO    : Ӳ��ͨ��IO���ʹ���
 * 
 * \note DL/T 645Э�� ����ͨ�÷��ͽӿڣ������Զ����֡ͷ����ַ�Լ�У����Ϣ��
 *      �û�ֻ����Ĵ����͵Ŀ����룬�Լ����ݱ�ʶ�������򣩼���
 */
aw_local aw_err_t __dl645_send(struct aw_ammeter_transfer* handle,
                               const uint8_t              *p_txbuf,
                               uint32_t                    nbytes)
{
    __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle);
    uint8_t tx_data[50 + 12] = {__DL645_GUIDE_CODE, __DL645_GUIDE_CODE,
                                __DL645_GUIDE_CODE, __DL645_GUIDE_CODE,
                                __DL645_START_CODE};
    uint32_t i   = 0;
    uint8_t  sum = 0;  /* 8λУ��� */
    uint8_t  dat_num;  /* ȥ���������������� */
    
    aw_tick_t start_ticks, end_ticks;
    uint32_t  timeout_ms;



    if ((NULL == p_ammeter_transfer_dl645)     ||
        (NULL == handle->p_addr)               ||
        (__DL645_ADDR_LEN != handle->addr_len) || /* DL T645 ��֧��6�ֽڵĵ�ַ */
        (nbytes < 1) || (nbytes > 51)) {          /* д����ʱ�������������50���ֽ� */
        return -AW_EINVAL;
    }
   
    dat_num  = nbytes - 1;
    
    /* ����ַ */
    for (i = 0; i < __DL645_ADDR_LEN; i++) {
        tx_data[i + 5] = handle->p_addr[i];
    }
    tx_data[__DL645_ADDR_LEN + 5] = __DL645_START_CODE; /* �ڶ���֡��ʼ�� */
    tx_data[__DL645_ADDR_LEN + 6] = p_txbuf[0];         /* ������ */
    tx_data[__DL645_ADDR_LEN + 7] = dat_num;           /*  �����򳤶� */
    /*  �����򳤶� */
    for (i = 1; i < nbytes; i++) {
        tx_data[__DL645_ADDR_LEN + 7 + i] = p_txbuf[i] + 0x33u;
    }
    /* ����У��� */
    sum = 0;
    for (i = 4; i < nbytes + 13; i++) {
        sum += tx_data[i];
    }
    
    /* ������ */
    tx_data[__DL645_ADDR_LEN + 7 + nbytes]     = sum;
    /* ������ */
    tx_data[__DL645_ADDR_LEN + 7 + nbytes + 1] = __DL645_END_CODE;
    
    /* ��������֡ */
//    start_ticks = aw_sys_tick_get();

//    if ((nbytes + 15) != aw_serial_write(p_ammeter_transfer_dl645->uart_num,
//                                          (char *)tx_data,
//                                          nbytes + 15)) {
    if ((nbytes + 15) != aw_serial_poll_write(p_ammeter_transfer_dl645->uart_num,
                                              (char *)tx_data,
                                              nbytes + 15)) {
        return -AW_EIO;
    }
//    end_ticks = aw_sys_tick_get();
//    timeout_ms = aw_ticks_to_ms(end_ticks - start_ticks);
//    AW_INFOF(("Ticks: %d \r\n", timeout_ms));
    return AW_OK;
}


/**
 * \brief �Ӵ����ж�ȡ����
 * \param [in] handle    : ���ͨ�Ŵ����ʵ��
 * \param [out] p_rxbuf  : �洢���ݵ�ָ��
 * \param [in]  nbytes   : ���ո���
 * \param [in]  timeout  : �������ʱʱ�䣬��λms
 *
 * \return   >0          : ʵ�ʶ�ȡ���ֽ���
 * \return -AW_ETIMEDOUT : ��ʱ����
 * \return -AW_ENOMEM    : ���ջ�����p_rxbuf�ռ䲻��
 *
 * \note �����ճɹ���p_rxbuf[nbytes-1]Ϊ���յĿ�����
 */
aw_local int __dl645_recevie_timeout (struct aw_ammeter_transfer* handle,
                                      uint8_t  *p_rxbuf,
                                      uint8_t   nbytes,
                                      uint32_t  timeout)

{
#define __DL645_STATE_START_CODE_FIND   0  /* ����Э��ͷ */
#define __DL645_STATE_CTRL_CODE_GET     1  /* ��ȡ������  */
#define __DL645_STATE_DAT_GET           2  /* ��ȡ������ ��У����Լ������� */

    __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle);
    uint32_t uart_num;
    int      state = __DL645_STATE_START_CODE_FIND;
    int      cnt   = 0; /* ĿǰЭ�����ݵļ��� */
    uint8_t rx_data[__DL645_PACKET_MAX_SIZE], sum;
    aw_tick_t start_ticks, end_ticks;
    uint32_t  timeout_ms;
    uint8_t  *p_rbuf = &rx_data[0];
    uint8_t  rlen    = 1, rlen_tmp;

    uart_num = p_ammeter_transfer_dl645->uart_num;
    start_ticks = aw_sys_tick_get();

    while (1) {

        end_ticks  = aw_sys_tick_get();
        timeout_ms = aw_ticks_to_ms(end_ticks - start_ticks);
        if (timeout_ms > timeout) {
            return -AW_ETIMEDOUT;
        }

        /* ��ȡ֡��ʼ���͵�ַ��һ֡������12���ֽ� */
        if (0 >= (rlen_tmp = aw_serial_read(uart_num, (char *)p_rbuf, rlen))) {
            state  = __DL645_STATE_START_CODE_FIND;
            rlen   = 1;
            p_rbuf = &rx_data[0];
            aw_mdelay(5);
            continue;
        } else if (rlen != rlen_tmp){
            rlen  -= rlen_tmp;
            p_rbuf = p_rbuf + rlen_tmp;
            continue;
        }

        switch (state) {
        case __DL645_STATE_START_CODE_FIND:
             if (rx_data[0] == __DL645_START_CODE) {
                 rlen = 9;
                 p_rbuf = &rx_data[1];
                 state = __DL645_STATE_CTRL_CODE_GET;
             }
             break;

        case __DL645_STATE_CTRL_CODE_GET:

            if (rx_data[7] != __DL645_START_CODE) {
                p_rbuf = &rx_data[0];
                rlen   = 1;
                break;
            }
            /* �жϵ�ַ�Ƿ�һֱ */
            for (cnt = 0; cnt < __DL645_ADDR_LEN; cnt++) {
                if (rx_data[1+cnt] != handle->p_addr[cnt]) {
                    p_rbuf = &rx_data[0];
                    rlen   = 1;
                    break;
                }
            }
            if ((rx_data[9] <= __DL645_INFO_MAX_LENGTH) &&
                (rx_data[9] == (nbytes - 1))) { /* �ж����ݳ����Ƿ�Ϊ��Ч */
               p_rbuf = &rx_data[10];
               rlen   = rx_data[9]+2;
               state  = __DL645_STATE_DAT_GET;
            } else {
                p_rbuf = &rx_data[0];
                rlen   = 1;
                state  = __DL645_STATE_START_CODE_FIND;
            }
            break;

        case __DL645_STATE_DAT_GET:
            p_rbuf = &rx_data[0];
            rlen   = 1;
            state  = __DL645_STATE_START_CODE_FIND;
            if (rx_data[rx_data[9]+11] != __DL645_END_CODE) {
                break;
            }

            /* ����У��� */
            sum  = 0;
            for (cnt = 0; cnt < rx_data[9]+10; cnt++) {
                sum += rx_data[cnt];
            }

            if (sum == rx_data[rx_data[9]+10]) {
                if ((rx_data[9] + 1) < nbytes) {
                    return -AW_ENOMEM;
                }
                /* ���ݽ������ */
                p_rxbuf[rx_data[9]] = rx_data[8]; /* ��������� */
                for (cnt = 0; cnt < rx_data[9]; cnt++) {
                    p_rxbuf[cnt] = rx_data[cnt+10] - 0x33u;
                }
                return rx_data[9] + 1; /* ������+���� */
            }
            break;

        default:break;
        }
    }
    return AW_ERROR;
}
/** 
 * \brief ��DL645Э���������
 * \param [in] handle  : ���ͨ�Ŵ����ʵ��
 * \param [in] p_rxbuf : �������ݻ�����
 * \param [in] nbytes  : �����ֽ���
 *
 * \return   >0          : ʵ�ʶ�ȡ���ֽ���
 * \return -AW_EINVAL : ��������
 * \return -AW_ETIMEDOUT : ��ʱ����
 *
 * \note DL/T 645Э�� ����ͨ�ý��սӿڣ���������ʶ��֡ͷ����ַ�Լ�У����Ϣ��
 *      �û�ֻ����Ľ��յ��Ŀ����룬�Լ����ݣ��������ݱ�ʶ������.
 *    �����ճɹ���p_rxbuf[nbytes-1]Ϊ���յĿ�����
 *    �������ݸ�ʽ
 *    07�� �� ���ݱ�ʶ��4�ֽڣ� | ������ | �����루1�ֽڣ�
 *    97�� �� ���ݱ�ʶ��2�ֽڣ� | ������ | �����루1�ֽڣ�
 *
 */
aw_local int __dl645_receive(struct aw_ammeter_transfer* handle,
                             uint8_t                    *p_rxbuf,
                             uint32_t                    nbytes)
{
    __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle);

    if ((NULL == p_ammeter_transfer_dl645)     ||
        (NULL == handle->p_addr)               ||
        (__DL645_ADDR_LEN != handle->addr_len) || /* DL T645 ��֧��6�ֽڵĵ�ַ */
        (nbytes < 1) || (nbytes > 200)) {         /* ������ʱ�������������200���ֽ� */
        return -AW_EINVAL;
    }

    return __dl645_recevie_timeout(handle, p_rxbuf, nbytes, __DL645_RX_FRAME_TIMEOUT_CFG);
}

/**
 * \brief ��ȡ��ǰ��������λ0.01 KWh(DTL645 07��Э���ȡ)
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_energy : ָ���ŵ����ı���
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dl645_07_active_energy_get(struct aw_ammeter* handle,
                                               uint32_t          *p_energy)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[9] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_07_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_07_DATAID_ENERGY ;
    buf[2] = (uint8_t)(__DL645_07_DATAID_ENERGY >> 8);
    buf[3] = (uint8_t)(__DL645_07_DATAID_ENERGY >> 16);
    buf[4] = (uint8_t)(__DL645_07_DATAID_ENERGY >> 24);
    /* �������� */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    5)) {
        return  AW_ERROR;
    }
    /* ��ȡ���� */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (9 != len) {
        return AW_ERROR;
    }
    /* buf[0-3] �洢��4���ֽڵ����ݱ�־
     * buf[4-7] �洢��д�����ݵĵ������ݣ���ʽΪ XXXXXX.XX KWh (LSB��ʽ���) */
    p_ammeter_dc->super.energy = (AW_BCD_TO_HEX(buf[7]) * 1000000) +
                                (AW_BCD_TO_HEX(buf[6]) * 10000)   +
                                (AW_BCD_TO_HEX(buf[5]) * 100)     +
                                (AW_BCD_TO_HEX(buf[4]) );

    if (NULL != p_energy) {
        *p_energy = p_ammeter_dc->super.energy;
    }
    return AW_OK;
}
#if __DL645_97_SUPPORT
/**
 * \brief ��ȡ��ǰ��������λ0.01 KWh(DTL645 97��Э���ȡ)
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_energy : ָ���ŵ����ı���
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dl645_97_active_energy_get(struct aw_ammeter* handle,
                                               uint32_t          *p_energy)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[7] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          || 
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_97_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_97_DATAID_ENERGY ;
    buf[2] = (uint8_t)(__DL645_97_DATAID_ENERGY >> 8);
    /* �������� */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    3)) {
        return  AW_ERROR;                    
    }
    /* ��ȡ���� */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;                    
    }

    if (7 != len) {
        return AW_ERROR;
    }

    p_ammeter_dc->super.power = (AW_BCD_TO_HEX(buf[5]) * 1000000) +
                                (AW_BCD_TO_HEX(buf[4]) * 10000)   +
                                (AW_BCD_TO_HEX(buf[3]) * 100)     +
                                (AW_BCD_TO_HEX(buf[2]) );
                                
    if (NULL != p_energy) {
        *p_energy = p_ammeter_dc->super.power;
    }
    return AW_OK;
}
#endif

/**
 * \brief ��ȡA�������07��汾��
 * \param[in]  handle   : ָ�����ʵ��
 * \param[in]  phase    : ��ȡ���࣬0-A�࣬1-B�࣬2-C��
 * \param[out] p_curr   : ָ���ŵ����ı�������λ0.001A
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dl645_07_current_get(struct aw_ammeter* handle,
                                           uint8_t            phase,
                                           uint32_t          *p_curr)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[8] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_07_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_07_DATAID_A_CURR ;
    buf[2] = (uint8_t)(__DL645_07_DATAID_A_CURR >> 8) + phase;
    buf[3] = (uint8_t)(__DL645_07_DATAID_A_CURR >> 16);
    buf[4] = (uint8_t)(__DL645_07_DATAID_A_CURR >> 24);
    /* �������� */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    5)) {
        return  AW_ERROR;
    }
    /* ��ȡ���� */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_curr) {
        *p_curr = (AW_BCD_TO_HEX(buf[6]) * 10000) +
                  (AW_BCD_TO_HEX(buf[5]) * 100)     +
                  (AW_BCD_TO_HEX(buf[4]) );
    }
    return AW_OK;
}

/**
 * \brief ��ȡA���ѹ��07��汾��
 * \param[in]  handle   : ָ�����ʵ��
 * \param[in]  phase    : ��ȡ���࣬0-A�࣬1-B�࣬2-C��
 * \param[out] p_vol    : ָ����ѹ�ı�������λ0.1V
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dl645_07_vol_get(struct aw_ammeter* handle,
                                       uint8_t            phase,
                                       uint32_t          *p_vol)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[7] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_07_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_07_DATAID_A_VOL ;
    buf[2] = (uint8_t)(__DL645_07_DATAID_A_VOL >> 8) + phase;
    buf[3] = (uint8_t)(__DL645_07_DATAID_A_VOL >> 16);
    buf[4] = (uint8_t)(__DL645_07_DATAID_A_VOL >> 24);
    /* �������� */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    5)) {
        return  AW_ERROR;
    }
    /* ��ȡ���� */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_vol) {
        *p_vol =   (AW_BCD_TO_HEX(buf[5]) * 100)     +
                   (AW_BCD_TO_HEX(buf[4]) );
    }
    return AW_OK;
}

/**
 * \brief ��ȡ˲ʱ���ʣ�07��汾��
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_power  : ָ���Ź��ʵı�������λkW
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dl645_07_power_get(struct aw_ammeter* handle,
                                       uint32_t          *p_power)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[8] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_07_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_07_DATAID_POWER ;
    buf[2] = (uint8_t)(__DL645_07_DATAID_POWER >> 8);
    buf[3] = (uint8_t)(__DL645_07_DATAID_POWER >> 16);
    buf[4] = (uint8_t)(__DL645_07_DATAID_POWER >> 24);
    /* �������� */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    5)) {
        return  AW_ERROR;
    }
    /* ��ȡ���� */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_power) {
        *p_power = (AW_BCD_TO_HEX(buf[6]) * 10000) +
                   (AW_BCD_TO_HEX(buf[5]) * 100)     +
                   (AW_BCD_TO_HEX(buf[4]) );
    }
    return AW_OK;
}

#if __DL645_97_SUPPORT
/**
 * \brief ��ȡA�����(97��汾)
 * \param[in]  handle   : ָ�����ʵ��
 * \param[in]  phase    : ��ȡ���࣬0-A�࣬1-B�࣬2-C��
 * \param[out] p_curr   : ָ���ŵ����ı�������λ0.01A
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dl645_97_current_get(struct aw_ammeter* handle,
                                           uint8_t            phase,
                                           uint32_t          *p_curr)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[5] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_97_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_97_DATAID_A_CURR + phase;
    buf[2] = (uint8_t)(__DL645_97_DATAID_A_CURR >> 8);
    /* �������� */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    3)) {
        return  AW_ERROR;
    }
    /* ��ȡ���� */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_curr) {
        *p_curr = (AW_BCD_TO_HEX(buf[3]) * 100)     +
                  (AW_BCD_TO_HEX(buf[2]) );
    }
    return AW_OK;
}

/**
 * \brief ��ȡA���ѹ��97��汾��
 * \param[in]  handle   : ָ�����ʵ��
 * \param[in]  phase    : ��ȡ���࣬0-A�࣬1-B�࣬2-C��
 * \param[out] p_vol    : ָ����ѹ�ı�������λV
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dl645_97_vol_get(struct aw_ammeter* handle,
                                     uint8_t            phase,
                                     uint32_t          *p_vol)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[5] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t) __DL645_97_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_97_DATAID_A_VOL + phase;
    buf[2] = (uint8_t)(__DL645_97_DATAID_A_VOL >> 8);
    /* �������� */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    3)) {
        return  AW_ERROR;
    }
    /* �ȴ���Ӧ */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_vol) {
        *p_vol =   (AW_BCD_TO_HEX(buf[3]) * 100)     +
                   (AW_BCD_TO_HEX(buf[2]) );
    }
    return AW_OK;
}

/**
 * \brief ��ȡ˲ʱ���ʣ�97��汾��
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_power  : ָ���Ź��ʵı�������λkW
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dl645_97_power_get(struct aw_ammeter* handle,
                                       uint32_t          *p_power)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    uint8_t buf[6] = {0};
    int     len    = 0;

    if ((NULL == p_ammeter_dc)                          ||
        (NULL == p_ammeter_dc->p_transfer)              ||
        (NULL == p_ammeter_dc->p_transfer->pfn_send)    ||
        (NULL == p_ammeter_dc->p_transfer->pfn_receive) ) {
        return -AW_EINVAL;
    }
    buf[0] = (uint8_t)__DL645_97_CTRL_CODE_DATGET;
    buf[1] = (uint8_t)__DL645_97_DATAID_POWER ;
    buf[2] = (uint8_t)(__DL645_97_DATAID_POWER >> 8);
    /* �������� */
    if (AW_OK != p_ammeter_dc->p_transfer->pfn_send(p_ammeter_dc->p_transfer,
                                                    buf,
                                                    3)) {
        return  AW_ERROR;
    }
    /* ��ȡ���� */
    if (0 > (len = p_ammeter_dc->p_transfer->pfn_receive(p_ammeter_dc->p_transfer,
                                                         buf,
                                                         sizeof(buf)))) {
        return  AW_ERROR;
    }

    if (sizeof(buf) != len) {
        return AW_ERROR;
    }

    if (NULL != p_power) {
        *p_power = (AW_BCD_TO_HEX(buf[4]) * 10000) +
                   (AW_BCD_TO_HEX(buf[3]) * 100)     +
                   (AW_BCD_TO_HEX(buf[2]) );
    }
    return AW_OK;
}
#endif

/**
 * \brief DL645Э��ͨ��ʵ����ʼ��
 * \param[in]  handle  : ָ�����ʵ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_transfer_dl645_inst_init (aw_ammeter_transfer_t* handle)
{
    __AMETER_TRANSFER_DL645_DECL(p_ammeter_transfer_dl645, handle);
    uint32_t uart_num;
    
    if (NULL == p_ammeter_transfer_dl645) {
        return -AW_EINVAL;
    }
    uart_num = p_ammeter_transfer_dl645->uart_num;
    aw_ammeter_transfer_inst_init(&(p_ammeter_transfer_dl645->super));
    
    p_ammeter_transfer_dl645->super.pfn_send    = __dl645_send;
    p_ammeter_transfer_dl645->super.pfn_receive = __dl645_receive;
    
    /* ���ڳ�ʼ������, �粨���� 115200 */
    aw_serial_ioctl(uart_num,
                    SIO_BAUD_SET, 
                   (void *)(p_ammeter_transfer_dl645->uart_buad));
    /* ���ڲ��� �磺8 ������λ 1 ��ֹͣλ������żУ�� */
    aw_serial_ioctl(uart_num,
                    SIO_HW_OPTS_SET,
                    (void *)(p_ammeter_transfer_dl645->uart_format));

    /* ���ö�ȡ��ʱʱ�� */
    aw_serial_ioctl(uart_num, AW_TIOCRDTIMEOUT, (void *)__DL645_RX_BYTE_TIMEOUT_CFG);


    /* �����Ƿ�ʹ��RS485 */
    aw_serial_ioctl(uart_num, AM_UART_RS485_ENABLE_SET, (void *)(
            (p_ammeter_transfer_dl645->rs485_en ? RS485_ENABLE:RS485_DISABLE)));

    return AW_OK;
}

#endif

#if __MODBUS_SUPPORT

/**
 * \brief ��ȡ��ǰ�����й����ܣ���λ0.01 KWh (modbusЭ��ʵ�ֻ�ȡ)
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_energy : ָ���ŵ����ı���
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dc_md_active_energy_get(struct aw_ammeter* handle,
                                            uint32_t          *p_energy)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, p_ammeter_dc->p_transfer);
    aw_mb_err_t err     = AW_MB_ERR_NOERR;
    uint16_t    rbuf[2];

    /* �����ּĴ���---�ӵ�ַ1000��ʼ����ȡ20�����ּĴ�������ȡ���ݷ���rd_buf������ */
    err = aw_mb_holding_reg_read(p_ammeter_transfer_mb->master,
                                 p_ammeter_dc->p_transfer->p_addr[0],
                                 0x2000,
                                 2,
                                 rbuf);
    if (err != AW_MB_ERR_NOERR) {
        return AW_ERROR;
    }
//    p_ammeter_dc->super.power = (AW_BCD_TO_HEX((rbuf[1] & 0xFF00) >> 8) * 1000000) +
//                                (AW_BCD_TO_HEX( rbuf[1] & 0xFF) * 10000) +
//                                (AW_BCD_TO_HEX((rbuf[0] & 0xFF00) >> 8) * 100) +
//                                (AW_BCD_TO_HEX( rbuf[0] & 0xFF) );
    p_ammeter_dc->super.power = ((rbuf[0] & 0xFFFF) << 16) | (rbuf[1] & 0xFFFF);
    if (NULL != p_energy) {
        *p_energy = p_ammeter_dc->super.power;
    }
    return AW_OK;
}

/**
 * \brief ��ȡ��ǰ��ѹ����λ0.01V (modbusЭ��ʵ�ֻ�ȡ)
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_vol    : ָ���ŵ�ѹ�ı���
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dc_md_voltage_get(struct aw_ammeter* handle,
                                      int32_t           *p_vol)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, p_ammeter_dc->p_transfer);
    aw_mb_err_t err     = AW_MB_ERR_NOERR;
    uint16_t    rbuf[2];

    /* �����ּĴ���---�ӵ�ַ1000��ʼ����ȡ20�����ּĴ�������ȡ���ݷ���rd_buf������ */
    err = aw_mb_holding_reg_read(p_ammeter_transfer_mb->master,
                                 p_ammeter_dc->p_transfer->p_addr[0],
                                 0x1000,
                                 2,
                                 rbuf);
    if (err != AW_MB_ERR_NOERR) {
        return AW_ERROR;
    }

    if (NULL != p_vol) {
        *p_vol = ((rbuf[0] & 0xFFFF) << 16) | (rbuf[1] & 0xFFFF);
    }
    return AW_OK;
}

/**
 * \brief ��վ�����߳�
 */
aw_local void __aw_ammeter_task_modbus_poll (aw_mb_master_t master)
{
    aw_mb_err_t    err = AW_MB_ERR_NOERR;

    AW_INFOF(("[Ammeter] Modbus Master: Poll Task Startup!\n"));
    AW_FOREVER {
        err = aw_mb_master_poll(master);
        if (err != AW_MB_ERR_NOERR) {
            AW_ERRF(("Modbus Master Poll Failed, err: %d!\r\n", err));
        }
        aw_mdelay(1000);
    }
}

/**
 * \brief ���modbusЭ��ͨ��ʵ����ʼ��
 * \param[in]  handle  : ָ�����ʵ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 * \return  AW_ERROR   : ��ʼ��ʧ��
 */
aw_err_t aw_ammeter_transfer_mb_inst_init (aw_ammeter_transfer_t* handle)
{
    __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, handle);
    aw_mb_master_t  master;
    aw_mb_err_t     err = AW_MB_ERR_NOERR;
    aw_task_id_t    tid ;

    if ((NULL == p_ammeter_transfer_mb) ||
        (NULL == p_ammeter_transfer_mb->p_ser_params)) {
        return -AW_EINVAL;
    }
    aw_ammeter_transfer_inst_init(&(p_ammeter_transfer_mb->super));

    master = aw_mb_master_create();
    if (master == NULL) {
        AW_ERRF(("Modbus Master Create Failed\r\n"));
        return AW_ERROR;
    }
    /* ��վ����ΪRTUģʽ�����ô�����Ϣ */
    err = aw_mb_master_config(master, AW_MB_RTU, p_ammeter_transfer_mb->p_ser_params);
    if (err != AW_MB_ERR_NOERR) {
        AW_ERRF(("Modbus Master Config Failed, err: %d!\r\n", err));
        aw_mb_master_delete(master);  /* ����ʧ�ܣ�ɾ����վ */
        return AW_ERROR;
    }
    /* ������վ  */
    err = aw_mb_master_start(master);
    if (err != AW_MB_ERR_NOERR) {
        AW_ERRF(("Modbus Master Start Failed, err: %d\r\n", err));
        return AW_ERROR;
    }
    tid = aw_task_create("task_modbus_poll",              /* �������� */
                          26,                             /* �������ȼ� */
                          1024,                           /* �����ջ��С */
                          __aw_ammeter_task_modbus_poll,  /* ������ں��� */
                          (void *)master);                /* ������ڲ��� */

    p_ammeter_transfer_mb->master = master;
    p_ammeter_transfer_mb->tid    = tid;
    return aw_task_startup(tid);
}
#endif

/**
 * \brief ��ȡ��ǰ��������λ0.01 KWh
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_energy : ָ���ŵ����ı���
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dc_active_energy_get(struct aw_ammeter* handle,
                                         uint32_t          *p_energy)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);

    if ((NULL != p_ammeter_dc) &&
        (NULL != p_ammeter_dc->p_transfer)) {
        switch (p_ammeter_dc->p_transfer->protocol) {
#if __MODBUS_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU:
            return __dc_md_active_energy_get(handle, p_energy);
#endif

#if __DL645_07_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
            return __dl645_07_active_energy_get(handle, p_energy);
#endif

#if __DL645_97_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
            return __dl645_97_active_energy_get(handle, p_energy);
#endif

        default:
            break;
        }
    }
    return -AW_EINVAL;
}

/**
 * \brief ��ȡA�����
 * \param[in]  handle   : ָ�����ʵ��
 * \param[in]  phase    : ��ȡ���࣬0-A�࣬1-B�࣬2-C��
 * \param[out] p_curr   : ָ���ŵ����ı���
 *                        ����07��汾����λΪ0.001A
 *                        ����97��汾����λΪ0.01A
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dc_current_get(struct aw_ammeter* handle,
                                     uint8_t            phase,
                                     uint32_t          *p_curr)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);

    if ((NULL != p_ammeter_dc) &&
        (NULL != p_ammeter_dc->p_transfer)) {
        switch (p_ammeter_dc->p_transfer->protocol) {
#if __MODBUS_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU:
            break;
#endif

#if __DL645_07_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
            return __dl645_07_current_get(handle, phase, p_curr);
#endif

#if __DL645_97_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
            return __dl645_97_current_get(handle, p_curr);
#endif

        default:
            break;
        }
    }
    return -AW_EINVAL;
}

/**
 * \brief ��ȡA���ѹ��07��汾��
 * \param[in]  handle   : ָ�����ʵ��
 * \param[in]  phase    : ��ȡ���࣬0-A�࣬1-B�࣬2-C��
 * \param[out] p_vol    : ָ����ѹ�ı���
 * *                      ����07��汾����λΪ0.1V
 *                        ����97��汾����λΪV
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_local aw_err_t __dc_vol_get(struct aw_ammeter* handle,
                               uint8_t            phase,
                               uint32_t          *p_vol)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);

    if ((NULL != p_ammeter_dc) &&
        (NULL != p_ammeter_dc->p_transfer)) {
        switch (p_ammeter_dc->p_transfer->protocol) {
#if __MODBUS_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU:
            break;
#endif

#if __DL645_07_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
            return __dl645_07_vol_get(handle, phase, p_vol);
#endif

#if __DL645_97_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
            return __dl645_97_vol_get(handle, phase, p_vol);
            break;
#endif

        default:
            break;
        }
    }
    return -AW_EINVAL;
}


/**
 * \brief ͨ��ʵ����ʼ��
 * \param[in]  handle  : ָ�����ָ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_transfer_inst_init (aw_ammeter_transfer_t* handle)
{
    if (NULL == handle) {
        return -AW_EINVAL;
    }
    handle->pfn_send    = NULL;
    handle->pfn_receive = NULL;
    return AW_OK;
}


/**
 * \brief ����һ��ͨ�Ÿ�ʽ��ʼ����Ӧͨ�Ŷ���
 * \param[in]  handle  : ָ�����ʵ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 * \return -AW_ENOTSUP : Э�鲻֧��
 */
aw_local aw_err_t __ammeter_transfer_factory (aw_ammeter_transfer_t* handle)
{
    if (NULL == handle) {
        return -AW_EINVAL;
    }
    
    switch (handle->protocol) {
    
#if __DL645_07_SUPPORT || __DL645_97_SUPPORT
    case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
    case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
        return aw_ammeter_transfer_dl645_inst_init(handle);
#endif
        
#if __MODBUS_SUPPORT
    case AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU:
        return aw_ammeter_transfer_mb_inst_init(handle);
#endif
        
    default:break;
    }
    
    return -AW_ENOTSUP;
}

/**
 * \brief ����ʼ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_inst_init (aw_ammeter_t* handle)
{
    if (NULL == handle) {
        return -AW_EINVAL;
    }
    handle->energy                = 0;
    handle->pfn_active_energy_get = NULL;
    return AW_OK;
}

/**
 * \brief ֱ������ʼ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_dc_inst_init (aw_ammeter_t* handle)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    
    if (NULL == p_ammeter_dc) {
        return -AW_EINVAL;
    }
    aw_ammeter_inst_init(&(p_ammeter_dc->super));
    
    p_ammeter_dc->super.pfn_active_energy_get = __dc_active_energy_get;
    /* ��ʼ����Ӧ��ͨ��ʵ����Ϣ */
    return  __ammeter_transfer_factory(p_ammeter_dc->p_transfer);
}

/**
 * \brief ֱ�����ȥ��ʼ��
 * \return AW_OK       : ��ʼ���ɹ�
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_dc_inst_deinit (aw_ammeter_t* handle)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);
    __AMETER_TRANSFER_MB_DECL(p_ammeter_transfer_mb, NULL);

    if ((NULL == p_ammeter_dc) ||
        (NULL == p_ammeter_dc->p_transfer)) {
        return -AW_EINVAL;
    }
#if __MODBUS_SUPPORT
    /* ���ʹ��modbusЭ�飬ɾ���߳���Դ */
    if (p_ammeter_dc->p_transfer->protocol ==  AW_AMMETER_TRANSFER_PROTOCOL_MODBUS_RTU) {

        p_ammeter_transfer_mb = (aw_ammeter_transfer_mb_t *)(p_ammeter_dc->p_transfer);
        aw_task_terminate(p_ammeter_transfer_mb->tid);
    }
#endif
    /* ��ʼ����Ӧ��ͨ��ʵ����Ϣ */
    return  AW_OK;
}



/**
 * \brief ��ȡ��ǰ��������λ0.01 KWh
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_energy : ָ���ŵ����ı���
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 *
 * \note ���������ȡʧ�ܣ�����ͨ��ʧ������1s�ڷ��أ�����������3��.���Է��ֵ����ʱ�򲢲��ܼ�ʱ������Ӧ.
 */
aw_err_t aw_ammeter_active_energy_get(struct aw_ammeter* handle, uint32_t *p_energy)
{
    if ((NULL == handle) ||
        (NULL == handle->pfn_active_energy_get)) {
        return -AW_EINVAL;
    }
    return  handle->pfn_active_energy_get(handle, p_energy);
}


/**
 * \brief ��ȡ��ѹ����λ0.1V
 * \param[in]  handle  : ָ�����ʵ��
 * \param[in]  phase    : ��ȡ���࣬0-A�࣬1-B�࣬2-C��
 * \param[out] p_vol   : ָ���ŵ����ı���
 *
 * \return AW_OK       : ��ȡ�ɹ�
 * \return AW_ERROR    : ��ȡʧ��
 * \return -AW_EINVAL  : ��������
 */
aw_err_t aw_ammeter_voltage_get(struct aw_ammeter* handle,
                                uint8_t            phase,
                                int32_t           *p_vol)
{
    return  __dc_vol_get(handle, phase,  p_vol);
}


/**
 * \brief ��ȡA�����
 * \param[in]  handle  : ָ�����ʵ��
 * \param[in]  phase    : ��ȡ���࣬0-A�࣬1-B�࣬2-C��
 * \param[out] p_curr  : ָ���ŵ����ı���
 *                        ����07��汾����λΪ0.001A
 *                        ����97��汾����λΪ0.01A
 *
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_err_t aw_ammeter_current_get(struct aw_ammeter* handle,
                                uint8_t            phase,
                                uint32_t          *p_curr)
{
    return  __dc_current_get(handle, phase, p_curr);
}


/**
 * \brief ��ȡ����
 * \param[in]  handle   : ָ�����ʵ��
 * \param[out] p_power    : ָ����ѹ�ı�������λkW
 * \return AW_OK    : ��ȡ�ɹ�
 * \return AW_ERROR : ��ȡʧ��
 */
aw_err_t aw_ammeter_power_get(struct aw_ammeter* handle, uint32_t *p_power)
{
    __AMETER_DC_DECL(p_ammeter_dc, handle);

    if ((NULL != p_ammeter_dc) &&
        (NULL != p_ammeter_dc->p_transfer)) {
        switch (p_ammeter_dc->p_transfer->protocol) {

#if __DL645_07_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_07:
            return __dl645_07_power_get(handle, p_power);
#endif

#if __DL645_97_SUPPORT
        case AW_AMMETER_TRANSFER_PROTOCOL_DL645_97:
            return __dl645_97_power_get(handle, p_power);
            break;
#endif

        default:
            break;
        }
    }
    return -AW_EINVAL;
}
