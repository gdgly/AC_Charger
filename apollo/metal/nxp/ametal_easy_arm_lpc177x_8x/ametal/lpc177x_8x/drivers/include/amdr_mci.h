/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief MCI����������MCI��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-23  anu, first implementation.
 * \endinternal
 */

#ifndef __AMDR_MCI_H
#define __AMDR_MCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"  
#include "amhw_mci.h"
#include "amhw_dma.h"
    
/** 
 * \addtogroup amdr_if_mci
 * \copydoc amdr_mci.h
 * @{
 */

/**
 * \brief ���ŵĴ�����Ϣ 
 */
typedef struct amdr_mci_intcb_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;

}amdr_mci_intcb_info_t;

/**
 * \brief MCI �豸��Ϣ
 */
typedef struct amdr_mci_devinfo {
    
    amhw_mci_t              *p_hw_mci;       /**< \brief MCI�Ĵ����׵�ַ  */
    amhw_syscon_t           *p_hw_syscon;    /**< \brief SYSCON�Ĵ����׵�ַ  */
    amdr_mci_intcb_info_t   *p_intcb_info;   /**< \brief MCI �ص���Ϣ */
    uint16_t                 inum;           /**< \brief MCI �жϺ�  */
    int                      insert_pin;     /**< \brief MCI SD_INSERT����  */
    int                      wp_pin;         /**< \brief MCI SD_WP����  */

} amdr_mci_devinfo_t;

/**
 * \brief MCI ������Ϣ
 */
typedef struct amdr_mci_transfer {

    uint8_t   curtran;         /**< \brief ��ǰ���ݴ�������, ��Ϊ__MCI_CUR_RECV��__MCI_CUR_SEND */
    uint8_t   rxtxflag;        /**< \brief ���ݽ���/���ͱ�־, ���ڱ�ʶ����/����ִ�н�� */

    uint8_t  *p_recvbuf;       /**< \brief �������ݻ�����ָ�� */
    uint8_t  *p_sendbuf;       /**< \brief �������ݻ�����ָ�� */
    uint32_t  recvcnt;         /**< \brief �������ݼ����� */
    uint32_t  sendcnt;         /**< \brief �������ݼ����� */

} amdr_mci_transfer_t;

/**
 * \brief SD����Ϣ�ṹ�嶨��
 */
typedef struct amdr_mci_sd {
    uint32_t card_posnum;             /**< \brief ������,�࿨ʱʹ�� */
    uint8_t  card_type;               /**< \brief ���� */

    uint32_t block_num;               /**< \brief ���п������ */
    uint32_t block_len;               /**< \brief ���Ŀ鳤��(��λ:�ֽ�) */
    uint32_t erase_unit;              /**< \brief һ�οɲ����Ŀ���� */

    uint32_t timeout_read;            /**< \brief ���鳬ʱʱ��(��λ: 1 clock) */
    uint32_t timeout_write;           /**< \brief д�鳬ʱʱ��(��λ: 1 clock) */
    uint32_t timeout_erase;           /**< \brief ���鳬ʱʱ��(��λ: 1 clock) */

    uint32_t rca;                     /**< \brief ����RCA��ַ */
    uint32_t host_clkval;             /**< \brief ����ʱ��ֵ(Hz)  */
    uint32_t card_transpeed;          /**< \brief ������������ٶ�(Hz) */

} amdr_mci_sd_t;

/**
 * \brief MCI�豸
 */
typedef struct amdr_mci_dev {
    
    /** \brief ָ��MCI�豸��Ϣ��ָ�� */
    const amdr_mci_devinfo_t *p_devinfo;

    /** \brief ������Ϣ */
    amdr_mci_transfer_t       trans;

    /** \brief ����Ϣ */
    amdr_mci_sd_t             sd;

} amdr_mci_dev_t;

/**
 * \name MCI �ڴ���������Ӧ����
 * \anchor grp_amdr_mci_expect_type
 * @{
 */

typedef uint32_t amdr_mci_expectresp_t;   /**< \brief MCI �ڴ���������Ӧ����  */
#define AMDR_MCI_EXPECT_NO_RESP        0  /**< \brief ����Ӧ */
#define AMDR_MCI_EXPECT_SHORT_RESP     1  /**< \brief ����Ӧ */
#define AMDR_MCI_EXPECT_LONG_RESP      2  /**< \brief ����Ӧ */

/** @} */

/**
 * \name MCI SD���������Ӧ����
 * \anchor grp_amdr_mci_resptype
 * @{
 */

typedef uint32_t amdr_mci_resptype_t;     /**< \brief MCI �������Ӧ����  */
#define AMDR_MCI_RESPTYPE_R0    0         /**< \brief ��Ӧ����R0 */
#define AMDR_MCI_RESPTYPE_R1    1         /**< \brief ��Ӧ����R1 */
#define AMDR_MCI_RESPTYPE_R1B   2         /**< \brief ��Ӧ����R1B */
#define AMDR_MCI_RESPTYPE_R2    3         /**< \brief ��Ӧ����R2 */
#define AMDR_MCI_RESPTYPE_R3    4         /**< \brief ��Ӧ����R3 */
#define AMDR_MCI_RESPTYPE_R4    5         /**< \brief ��Ӧ����R4 */
#define AMDR_MCI_RESPTYPE_R5    6         /**< \brief ��Ӧ����R5 */
#define AMDR_MCI_RESPTYPE_R6    7         /**< \brief ��Ӧ����R6 */
#define AMDR_MCI_RESPTYPE_R7    8         /**< \brief ��Ӧ����R7 */

/** @} */

/**
 * \name MCI �ȴ������ĵȴ�����
 * \anchor grp_amdr_mci_busytype
 * @{
 */

typedef uint32_t amdr_mci_busytype_t;     /**< \brief �ȴ�����  */
#define AMDR_MCI_BUSY_TYPE_READ        0  /**< \brief ���ȴ�  */
#define AMDR_MCI_BUSY_TYPE_RDY_DATA    1  /**< \brief �ɽ������ݵȴ�  */
#define AMDR_MCI_BUSY_TYPE_PROG        2  /**< \brief ��̵ȴ�  */
#define AMDR_MCI_BUSY_TYPE_ERASE       3  /**< \brief �����ȴ�  */

/** @} */

/**
 * \name MCI �ȴ������ĵȴ�����
 * \anchor grp_amdr_mci_cardtype
 * @{
 */

typedef uint32_t amdr_mci_cardtype_t;                      /**< \brief ������  */
#define AMDR_MCI_CARDTYPE_UNKNOWN          0x00
#define AMDR_MCI_CARDTYPE_SD               0x01            /**< \brief ����ΪSD  ��  */
#define AMDR_MCI_CARDTYPE_MMC              0x02            /**< \brief ����ΪMMC ��  */
#define AMDR_MCI_CARDTYPE_SDHC             0x03            /**< \brief ����ΪSDHC��  */

/** @} */

/**
 * \name MCI �ȴ������ĵȴ�����
 * \anchor grp_amdr_mci_cardver
 * @{
 */

typedef uint32_t amdr_mci_cardver_t;     /**< \brief ���汾  */
#define AMDR_MCI_SD_V1     0x00          /**< \brief version 1 */
#define AMDR_MCI_SD_V2     0x01          /**< \brief version 2 */
#define AMDR_MCI_SD_NA     0x02          /**< \brief unkown */

/** @} */

/**
 * \name MCI ���߿������
 * \anchor grp_amdr_mci_width
 * @{
 */

typedef uint32_t amdr_mci_width_t;       /**< \brief ���߿��  */
#define AMDR_MCI_WIDTH_1BIT     0x00     /**< \brief 1BIT�����߿�� */
#define AMDR_MCI_WIDTH_4BIT     0x01     /**< \brief 4BIT�����߿�� */

/** @} */

/**
 * \name MCI ����Ĵ�������
 * \anchor grp_amdr_mci_err
 * @{
 */

typedef uint32_t amdr_mci_err_t;                  /**< \brief MCI ����Ĵ�������  */

/** \brief ������  error code */
#define AMDR_MCI_ERR_NO_ERR             0x00      /**< \brief ����ִ�гɹ� */
#define AMDR_MCI_ERR_NO_CARD            0x01      /**< \brief ��û����ȫ���뵽������ */
#define AMDR_MCI_ERR_USER_PARAM         0x02      /**< \brief �û�ʹ��API����ʱ����ڲ����д��� */
#define AMDR_MCI_ERR_CARD_PARAM         0x03      /**< \brief ���в����д����뱾ģ�鲻���ݣ� */
#define AMDR_MCI_ERR_VOL_NOTSUSP        0x04      /**< \brief ����֧��3.3V���� */
#define AMDR_MCI_ERR_OVER_CARDRANGE     0x05      /**< \brief ����������������Χ */
#define AMDR_MCI_ERR_UNKNOWN_CARD       0x06      /**< \brief �޷�ʶ���� */

#define AMDR_MCI_ERR_CURRENT_STATE      0x07      /**< \brief ����ǰ״̬����ȷ(ֻ������SDģʽ) */
#define AMDR_MCI_ERR_READY_FOR_DATA     0x08      /**< \brief �����ݻ�����δ���� */

/** \brief ������ܷ��صĴ�����  */
#define AMDR_MCI_ERR_CMD_RESPTYPE       0x10      /**< \brief �������ʹ���  */
#define AMDR_MCI_ERR_CMD_TIMEOUT        0x11      /**< \brief ��������Ӧ��ʱ  */
#define AMDR_MCI_ERR_CMD_RESP           0x12      /**< \brief ��������Ӧ����  */
#define AMDR_MCI_ERR_CMD_NOTSUSP        0x13      /**< \brief ��֧�ָ�����  */
#define AMDR_MCI_ERR_CMD_RESPCRC        0x14      /**< \brief ����CRC��Ӧ����  */

/** \brief ������������  */
#define AMDR_MCI_ERR_DATA_CRC16         0x20      /**< \brief ������CRC16У�鲻ͨ�� */
#define AMDR_MCI_ERR_DATA_START_TOK     0x21      /**< \brief ���������ʱ�����ݿ�ʼ���Ʋ���ȷ */
#define AMDR_MCI_ERR_DATA_RESP          0x22      /**< \brief д�������ʱ����������Ӧ���Ʋ���ȷ */
#define AMDR_MCI_ERR_DATA_STARTBIT      0x23      /**< \brief д�������ʱ, ������ʼλ����ȷ */

/** \brief �ȴ������� */
#define AMDR_MCI_ERR_TIMEOUT_WAIT       0x30      /**< \brief д�������ʱ��������ʱ���� */
#define AMDR_MCI_ERR_TIMEOUT_READ       0x31      /**< \brief ��������ʱ���� */
#define AMDR_MCI_ERR_TIMEOUT_WRITE      0x32      /**< \brief д������ʱ���� */
#define AMDR_MCI_ERR_TIMEOUT_ERASE      0x33      /**< \brief ����������ʱ���� */
#define AMDR_MCI_ERR_TIMEOUT_WAITIDLE   0x34      /**< \brief ��ʼ����ʱ���ȴ����˳�����״̬��ʱ���� */

/** \brief д�������ܷ��صĴ����� */
#define AMDR_MCI_ERR_WRITE_BLK          0x40      /**< \brief д�����ݴ��� */
#define AMDR_MCI_ERR_WRITE_BLKNUMS      0x41      /**< \brief д���ʱ����Ҫд��Ŀ�����ȷд��Ŀ�����һ�� */
#define AMDR_MCI_ERR_WRITE_PROTECT      0x42      /**< \brief ����ǵ�д�������ش���д����λ�� */

/** \brief ʹ��UCOS-IIʱ���ܳ��ֵĴ��� */
#define AMDR_MCI_ERR_CREATE_SEMSD       0xA0      /**< \brief ����SD/MMC�������ź���ʧ�� */
#define AMDR_MCI_ERR_WAIT_WRSEM         0xA1      /**< \brief �ȴ���д�ź���ʧ�� */

/** \brief SD_STRUCT�ṹ����ܳ��ֵĴ��� */
#define AMDR_MCI_ERR_SD_STRUCT          0xB0      /**< \brief SD_STRUCT�ṹ���Աֵ���ڴ��� */

/** \brief �������ܵĴ��� */
#define AMDR_MCI_ERR_HARDWARE           0xE0      /**< \brief Ӳ������ */

/** @} */


/**
 * \brief MCI ���� CMD �ź��ߵĿ�©״̬
 *
 * \param[in] p_dev        : ָ��MCI�豸��ָ��
 * \param[in] bopendrain   : bopendrain> 0: CMD �ź��߿�©;  = 0: CMD �ź��ߴ��ڷǿ�©
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_opendraincmd (amdr_mci_dev_t *p_dev,
                                      uint8_t         bopendrain);

/**
 * \brief MCI ʹ��SD/MMC�������Ƿ�ʹ�ܿ�����
 *
 * \param[in] p_dev        : ָ��MCI�豸��ָ��
 * \param[in] bwidth       : �������� ���ò��� ���μ�
 * 							 \ref grp_amdr_mci_width "MCI BUS WIDTH"
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_enablemcibuswidth (amdr_mci_dev_t   *p_dev,
										   amdr_mci_width_t  bwidth);

/**
 * \brief MCI ʱ������
 *
 * \param[in] p_dev      : ָ��MCI�豸��ָ��
 * \param[in] clockrate  : ʱ������
 *
 * \retval AMDR_MCI_ERR_NO_ERR     : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM : ��Ч����
 */
amdr_mci_err_t amdr_mci_clock_set (amdr_mci_dev_t *p_dev,
                                   uint32_t        clockrate);

/**
 * \brief MCI ��ȡʱ���ٶ�
 *
 * \param[in] p_dev      : ָ��MCI�豸��ָ��
 *
 * \retval ʱ���ٶ�
 */
uint32_t amdr_mci_clock_get (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI �����������, ������ȡ��Ӧ
 *
 * \param[in] p_dev        : ָ��MCI�豸��ָ��
 * \param[in] cmdindex     : ��������
 * \param[in] argument     : �������
 * \param[in] expectresp   : ������Ӧ����   ���ò������μ�
 *                           \ref grp_amdr_mci_resptype "MCI RESP TYPE"
 * \param[in] allowtimeout : �Ƿ�����ʱ
 *
 * \retval AMDR_MCI_ERR_NO_ERR      : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM  : ��Ч����
 */
amdr_mci_err_t amdr_mci_cmdsend (amdr_mci_dev_t        *p_dev,
                                 uint32_t               cmdindex,
                                 uint32_t               argument,
                                 amdr_mci_expectresp_t  expectresp,
                                 uint32_t               allowtimeout);

/**
 * \brief MCI �ӿ���ȡ��Ӧ, �ú�����MCI_SendCmd()�ɶ�ʹ��
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] expectcmddata : ������
 * \param[in] expectresp    : ϣ������Ӧ ���ò������μ�
 *                            \ref grp_amdr_mci_expect_type "MCI EXPECT TYPE"
 * \param[in] resplen       : ��Ӧ����
 * \param[out] p_cmdresp    : ��Ӧ����
 *
 * \retval AMDR_MCI_ERR_NO_ERR      : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM  : ��Ч����
 * \retval AMDR_MCI_ERR_CMD_TIMEOUT : ������Ӧ���ʱ����
 * \retval AMDR_MCI_ERR_CMD_RESPCRC : ������Ӧ����CRCУ��ʧ�ܴ���
 * \retval AMDR_MCI_ERR_CMD_RESP    : ������Ӧ����
 */
amdr_mci_err_t amdr_mci_cmdresp_get (amdr_mci_dev_t        *p_dev,
                                     uint32_t               expectcmddata,
                                     amdr_mci_expectresp_t  expectresp,
                                     size_t                 resplen,
                                     uint32_t              *p_cmdresp);

/**
 * \brief MCI ����һ������ӿ���ȡ��Ӧ
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] cmd           : ������
 * \param[in] argument      : �������
 * \param[in] resptype      : ��Ӧ���� ���ò������μ�
 *                            \ref grp_amdr_mci_resptype "MCI RESP TYPE"
 * \param[in] resplen       : ��Ӧ����
 * \param[out] p_resp       : ��Ӧ����
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM   : ��Ч����
 * \retval AMDR_MCI_ERR_CMD_RESPTYPE : �������Ӧ����
 * \retval AMDR_MCI_ERR_CMD_TIMEOUT  : ������Ӧ���ʱ����
 * \retval AMDR_MCI_ERR_CMD_RESPCRC  : ������Ӧ����CRCУ��ʧ�ܴ���
 * \retval AMDR_MCI_ERR_CMD_RESP     : ������Ӧ����
 */
amdr_mci_err_t amdr_mci_cmdsend_respget (amdr_mci_dev_t      *p_dev,
                                         uint8_t              cmd,
                                         uint32_t             argument,
                                         amdr_mci_resptype_t  resptype,
                                         size_t               resplen,
                                         uint32_t            *p_resp);

/**
 * \brief MCI ��⿨�Ƿ���ȫ���뿨����
 *
 * \param[in] p_dev : ָ��MCI�豸��ָ��
 *
 * \retval 0 : δ����
 * \retval 1 : ����
 */
uint8_t amdr_mci_checkcard (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI ��⿨д����
 *
 * \param[in] p_dev : ָ��MCI�豸��ָ��
 *
 * \retval 0 : δд����
 * \retval 1 : д����
 */
uint8_t amdr_mci_check_wp (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI �ڷ��Ͷ���������֮ǰ, ��Ӳ����������һЩ����Ļ���
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM   : ��Ч����
 */
amdr_mci_err_t amdr_mci_before_readblock (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI �ڷ��Ͷ���������֮��, ��Ӳ��������ʵ�ֶ�ȡ����
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] p_recvbuf     : ���ջ�����, ��СΪ512�ֽ�
 *
 * \retval �������  �μ� \ref grp_amdr_mci_err "MCI ERROR TYPE"
 */
amdr_mci_err_t amdr_mci_readblock (amdr_mci_dev_t *p_dev,
                                   uint8_t        *p_recvbuf);

/**
 * \brief MCI �ڷ���д��������֮ǰ, ��Ӳ����������һЩ����Ļ���
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM   : ��Ч����
 */
amdr_mci_err_t amdr_mci_before_writeblock (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI �ڷ���д��������֮��, ��Ӳ���������򿨷�������
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] p_sendbuf     : ���ͻ��� ��СΪ512�ֽ�
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM   : ��Ч����
 */
amdr_mci_err_t amdr_mci_writeblock (amdr_mci_dev_t *p_dev, uint8_t *p_sendbuf);

/**
 * \brief MCI �ȴ����ɽ�������(�ȴ������пյĽ��ջ�����), ���ȴ���״̬�Ĵ����� bit8 Ϊ1
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM   : ��Ч����
 * \retval AMDR_MCI_ERR_NO_CARD      : �޿�����
 */
amdr_mci_err_t amdr_mci_waitreadyfordata (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI �ȴ�����̻��������, ���ȴ���״̬�ɱ��״̬��Ϊ����״̬: prg --> tran
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] busytype      : æ�ȴ����� ���ò������μ�
 *                            \ref grp_amdr_mci_busytype "MCI BUSY TYPE"
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM   : ��Ч����
 * \retval AMDR_MCI_ERR_NO_CARD      : �޿�����
 */
amdr_mci_err_t amdr_mci_waitbusy (amdr_mci_dev_t      *p_dev,
                                  amdr_mci_busytype_t  busytype);

/**
 * \brief MCI CMD0, ��λ���п�, ʹ������Idle״̬
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM   : ��Ч����
 * \retval AMDR_MCI_ERR_CMD_RESPTYPE : �������Ӧ����
 * \retval AMDR_MCI_ERR_CMD_TIMEOUT  : ������Ӧ���ʱ����
 * \retval AMDR_MCI_ERR_CMD_RESPCRC  : ������Ӧ����CRCУ��ʧ�ܴ���
 * \retval AMDR_MCI_ERR_CMD_RESP     : ������Ӧ����
 */
amdr_mci_err_t amdr_mci_sdcmd_go_idle_state (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI CMD1(������MMC��), ʹ���˳�Idle״̬, ����Ready״̬(ͨ���ж�MMC����OCR�Ĵ���ֵ)
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : ���óɹ�
 * \retval AMDR_MCI_ERR_USER_PARAM   : ��Ч����
 * \retval AMDR_MCI_ERR_CMD_RESPTYPE : �������Ӧ����
 * \retval AMDR_MCI_ERR_CMD_TIMEOUT  : ������Ӧ���ʱ����
 * \retval AMDR_MCI_ERR_CMD_RESPCRC  : ������Ӧ����CRCУ��ʧ�ܴ���
 * \retval AMDR_MCI_ERR_CMD_RESP     : ������Ӧ����
 */
amdr_mci_err_t amdr_mci_sdcmd_send_op_cond (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI CMD8 ʶ�𿨰汾
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \retval  AMDR_MCI_SD_V1  : ���汾��1
 * \retval  AMDR_MCI_SD_V2  : ���汾��2
 * \retval  AMDR_MCI_SD_NA  : ���汾��δ֪
 */
amdr_mci_cardver_t amdr_mci_sdcmd_checksdversion (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD55(������SD��), �ڷ������� ACMDxx ����֮ǰ, �����ȷ��ͱ�����
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_send_acmd (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI ACMD41(������SD��), ʹ���˳�Idle״̬, ������Ready״̬(ͨ���ж�SD����OCR�Ĵ���ֵ)
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_sd_app_op_cond (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD2 ��ȡ���п���CID�Ĵ�������
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] cidlen        : CID �Ĵ�������, �̶�Ϊ16�ֽ�
 * \param[in] p_cidbuf      : CID �Ĵ�������, ����Ϊ16�ֽ�
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_all_send_cid (amdr_mci_dev_t      *p_dev,
                                            uint8_t              cidlen,
                                            uint8_t             *p_cidbuf);

/**
 * \brief MCI CMD3, ��ȡ����RCA��ַ, Ȼ�󱣴浽sds�ṹ����
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_set_relative_addr (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD9, ��ȡ����CSD�Ĵ���ֵ
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] csdlen        : CSD �Ĵ�������
 * \param[out] p_csdbuf     : CSD�Ĵ�������, bit127 ��csdbuf[0]
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_send_csd (amdr_mci_dev_t      *p_dev,
                                        uint8_t              csdlen,
                                        uint8_t             *p_csdbuf);

/**
 * \brief MCI CMD 7: ѡ��, ʹ���� Stand-by �� Transfer ֮���л�
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_select_card (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD 7: ȡ��ѡ��, ʹ���� Stand-by �� Transfer ֮���л�
 *
 * \param[in] p_dev : ָ��MCI�豸��ָ��
 * \param[in] rca   : SD/MMC����Ϣ�ṹ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_deselect_card (amdr_mci_dev_t *p_dev,
                                             uint32_t        rca);

/**
 * \brief MCI CMD12: ֹͣ����Stop Transmission
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_stop_transmission (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD13, ��ȡ����ǰ״̬, �����������ݴ���ģʽ��(����ʶ��ģʽ�����ģʽ��), �Ϳ���ʹ�ñ�����
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[out] p_status     : ��״̬
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_send_status (amdr_mci_dev_t      *p_dev,
                                           uint32_t            *p_status);

/**
 * \brief MCI CMD15, ʹ������ǻ״̬
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_go_inactive_state (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD 16: ���ÿ鳤��, ���뷢��CMD7����
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockLen      : ����ĳ���
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_set_blocklen (amdr_mci_dev_t      *p_dev,
                                            uint32_t             blockLen);

/**
 * \brief MCI ACMD6, ���ÿ��������ݵ����߿��(����SD��, ����Ϊ1bit, Ҳ����Ϊ4bits) ����MMC��, ��������Ч
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] bwidebus      : ������ ���ò������μ�\ref grp_amdr_mci_width "MCI WIDTH"
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_set_bus_width (amdr_mci_dev_t      *p_dev,
											 amdr_mci_width_t     bwidebus);

/**
 * \brief MCI CMD17, ���Ͷ���������
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockadddr    : ���ַ. 0 ~ 511�ֽ�ȡֵΪ1. 512 ~ 1023�ֽ�ȡֵΪ2
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_read_single_block (amdr_mci_dev_t *p_dev,
                                                 uint32_t        blockadddr);

/**
 * \brief MCI CMD18, ���Ͷ��������
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockadddr    : ���ַ
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_read_multiple_block (amdr_mci_dev_t *p_dev,
                                                   uint32_t        blockadddr);

/**
 * \brief MCI CMD24, ����д��������
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockadddr    : ���ַ
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_write_single_block (amdr_mci_dev_t *p_dev,
                                                  uint32_t        blockadddr);

/**
 * \brief MCI CMD25, ����д�������
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockadddr    : ���ַ
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_write_multiple_block (amdr_mci_dev_t *p_dev,
                                                    uint32_t        blockadddr);

/**
 * \brief MCI CMD32��CMD35: ���ò�����ʼ��ַ
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockadddr    : ���ַ
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_erase_wr_blk_start (amdr_mci_dev_t *p_dev,
                                                  uint32_t        blockadddr);

/**
 * \brief MCI CMD33��CMD36, ���ò�����ֹ��ַ
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockadddr    : ���ַ
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_erase_wr_blk_end (amdr_mci_dev_t      *p_dev,
                                                uint32_t             blockadddr);

/**
 * \brief MCI CMD38, ������ѡ��ָ���Ŀ�
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_erase (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI  ��SD/MMC���ж���һ�����ݿ�
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockaddr     : �Կ�Ϊ��λ�Ŀ��ַ, ����, ����ʼ��0 ~ 511�ֽ�Ϊ���ַ0, 512 ~ 1023�ֽڵĿ��ַΪ1
 * \param[out] p_recbuf     : ���ջ�����,���ȹ̶�Ϊ 512 �ֽ�
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_readblock (amdr_mci_dev_t      *p_dev,
                                      uint32_t             blockaddr,
                                      uint8_t             *p_recbuf);

/**
 * \brief MCI ��SD/MMC���ж���������ݿ�
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockaddr     : �Կ�Ϊ��λ�Ŀ��ַ
 * \param[in] blocknum      : Ҫ��ȡ�Ŀ�ĸ���
 * \param[out] p_recbuf     : ���ջ�����, ����512 * blocknum �ֽ�
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_readmultiblock (amdr_mci_dev_t      *p_dev,
                                           uint32_t             blockaddr,
                                           uint32_t             blocknum,
                                           uint8_t             *p_recbuf);

/**
 * \brief MCI ��SD/MMC����д��һ����
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockaddr     : �Կ�Ϊ��λ�Ŀ��ַ, ����, ����ʼ��0 ~ 511�ֽ�Ϊ���ַ0, 512 ~ 1023�ֽڵĿ��ַΪ1
 * \param[in] p_sendbuf     : ���ͻ�����,���ȹ̶�Ϊ 512 �ֽ�
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_writeblock (amdr_mci_dev_t      *p_dev,
                                       uint32_t             blockaddr,
                                       uint8_t             *p_sendbuf);

/**
 * \brief MCI ��SD/MMC����д�������ݿ�
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] blockaddr     : �Կ�Ϊ��λ�Ŀ��ַ, ����, ����ʼ��0 ~ 511�ֽ�Ϊ���ַ0, 512 ~ 1023�ֽڵĿ��ַΪ1
 * \param[in] blocknum      : Ҫд��Ŀ�ĸ���
 * \param[in] p_sendbuf     : ���ͻ�����, ���� 512 * blocknum �ֽ�
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_writemultiblock (amdr_mci_dev_t      *p_dev,
                                            uint32_t             blockaddr,
                                            uint32_t             blocknum,
                                            uint8_t             *p_sendbuf);

/**
 * \brief MCI ����SD/MMC���еĿ�
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 * \param[in] startaddr     : ��������ʼ��ַ, ��ַΪ�Կ�Ϊ��λ�Ŀ��ַ
 * \param[in] blocknum      : �����Ŀ���
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_eraseblock (amdr_mci_dev_t      *p_dev,
                                       uint32_t             startaddr,
                                       uint32_t             blocknum);

/**
 * \brief MCI SD2.00 SDHC cardʶ��
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_ver2activeinit (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI ʶ��: SD, MMC, �򲻿ɿ���
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdmmc_identifycard (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI �Կ�����ز�����������, �翨���߿��, �����ݿ��С
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdmmc_configcard (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI ���SD/MMC������Ϣ
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdmmc_getcardinfo (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI �����/д/����ʱʱ��
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdmmc_caltimeout (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI SD/MMC ����ʼ��: ��λ��,ʶ��,��ȡ�������Ϣ,ʹ����ʶ��ģʽ�������ݴ���ģʽ
 *
 * \param[in] p_dev         : ָ��MCI�豸��ָ��
 *
 * \return �������  �μ�  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_card_init (amdr_mci_dev_t      *p_dev);

/**
 * \brief ע���жϻص�����
 *
 * \param[in] p_dev        : MCI�豸
 * \param[in] inttype      : �ж����� �ж����� ���ò������μ�
 *                           \ref grp_amhw_mci_int_type "MCI INTERRUPT TYPE"
 * \param[in] pfn_callback : Ҫע��Ļص�����
 * \param[in] p_arg        : �����ص������Ĳ���
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 */
int amdr_mci_intcb_connect (amdr_mci_dev_t      *p_dev,
                            amhw_mci_int_type_t  inttype,
                            am_pfnvoid_t         pfn_callback,
                            void                *p_arg);

/**
 * \brief ɾ��ĳ�����͵��жϻص�����
 *
 * \param[in] p_dev        : MCI�豸
 * \param[in] inttype      : �ж����� ���ò������μ�
 *                           \ref grp_amhw_mci_int_type "MCI INTERRUPT TYPE"
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 */
int amdr_mci_intcb_disconnect (amdr_mci_dev_t        *p_dev,
                               amhw_mci_int_type_t    inttype);

/**
 * \brief MCI��ʼ��
 *
 * \param[in] p_dev     : ָ��MCI�豸��ָ��
 * \param[in] p_devinfo : ָ��MCI�豸��Ϣ��ָ��
 *
 * \retval AM_OK      : �����ɹ�
 * \retval -AM_EINVAL : ��������
 */
int amdr_mci_init (amdr_mci_dev_t           *p_dev,
                   const amdr_mci_devinfo_t *p_devinfo);

/**
 * \brief MCI���ʼ��
 *
 * \param[in] p_dev : ָ��MCI�豸��ָ��
 *
 * \return �� 
 */
void amdr_mci_deinit (amdr_mci_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_MCI_H */

/* end of file */
