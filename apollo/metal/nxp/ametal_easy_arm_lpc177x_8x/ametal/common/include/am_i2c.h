/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief I2C��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AM_I2C_H
#define __AM_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * @addtogroup am_if_i2c
 * @copydoc am_i2c.h
 * @{
 */

/**
 * \name I2C ������Ʊ�ʶ
 * @{ 
 */

#define AM_I2C_M_MASK      0x00FFu    /**< \brief I2C���Ʊ�ʶ����  */
#define AM_I2C_M_7BIT      0x0000u    /**< \brief 7-bits �豸��ַ  */
#define AM_I2C_M_10BIT     0x0001u    /**< \brief 10-bits �豸��ַ */
#define AM_I2C_M_WR        0x0000u    /**< \brief д����           */
#define AM_I2C_M_RD        0x0002u    /**< \brief ������           */
#define AM_I2C_M_NOSTART   0x0010u    /**< \brief ������������     */
#define AM_I2C_M_STOP      0x0020u    /**< \brief I2Cֹͣ�ź�      */
/** @} */


/**
 * \name I2C �ӻ��豸��־
 * @{ 
 */
#define AM_I2C_ADDR_7BIT         AM_I2C_M_7BIT     /**< \brief 7-bits�ӻ���ַ           */
#define AM_I2C_ADDR_10BIT        AM_I2C_M_10BIT    /**< \brief 10-bits�ӻ���ַ          */
#define AM_I2C_SUBADDR_NONE      0x0000u           /**< \brief �ӻ��豸���ӵ�ַ          */
#define AM_I2C_SUBADDR_1BYTE     0x1000u           /**< \brief �ӻ��豸�ӵ�ַ���λ1�ֽ� */
#define AM_I2C_SUBADDR_2BYTE     0x2000u           /**< \brief �ӻ��豸�ӵ�ַ���λ2�ֽ� */

/** \brief �ӱ�־��������ȡ���ӵ�ַ��� */
#define AM_I2C_SUBADDR_LEN_GET(flags)  (((flags) & 0xF000) >> 12)

/** @} */


/**
 * \brief I2C�ӻ��豸�����Ϣ�ṹ��
 */
typedef struct am_i2c_device {
    uint16_t  dev_addr;                 /**< \brief I2C �ӻ��豸��ַ */ 
    uint16_t  dev_flags;                /**< \brief I2C �ӻ��豸���� */
} am_i2c_device_t;

/**
 * \brief I2C ����ṹ��
 */ 
typedef struct am_i2c_transfer {
    uint16_t   addr;                    /**< \brief I2C�豸��ַ          */ 
    uint16_t   flags;                   /**< \brief I2C �豸�����Լ�transfer��Ҫ�������ʶ */
    void      *p_buf;                   /**< \brief I2C �������ݻ���ָ�� */
    uint16_t   length;                  /**< \brief I2C ���ݻ��泤��     */
    int        (*pfn_callback)(void *,int); /**< \brief I2C ������ɻص����� */
    void      *p_arg;                   /**< \brief �ص�������ڲ��� */
} am_i2c_transfer_t;


/**
 * \brief I2C���������ṹ��
 */
struct am_i2c_drv_funcs {
    
    /** \brief ָ��I2C����/��ַ���亯�� */
    int (*pfunc_i2c_transfer) (void *p_drv, am_i2c_transfer_t *p_trans);
    
    /** \brief ָ��I2C�ж����Ӻ��� */
    int (*pfunc_i2c_connect) (void *p_drv);
    
};

/**
 * \brief I2C��׼����ṹ�� 
 */
typedef struct am_i2c_serv {
    struct am_i2c_drv_funcs   *p_drv_funcs;   /**< \brief I2C�������� */
    void                      *p_drv;         /**< \brief I2C����������ں��� */
} am_i2c_serv_t;

/** \brief I2C��׼�������������� */
typedef am_i2c_serv_t *am_i2c_handle_t;

/**
 * \brief I2C�ж����Ӻ���
 * \param[in] handle : I2C��׼����������
 * \retval  AM_OK    : ���ӳɹ�
 */
int am_i2c_connect(am_i2c_handle_t handle);


/**
 * \brief I2C�ӻ��豸�����Ϣ�ṹ���������
 *
 * \param[in] p_device     : ָ��ӻ��豸��Ϣ�Ľṹ���ָ��
 * \param[in] dev_addr     : �ӻ��豸��ַ
 * \param[in] dev_flags    : �ӻ��豸����
 *
 * \retval  AM_OK     : �豸��Ϣ�������
 */
int am_i2c_mkdevice(am_i2c_device_t *p_device, 
                    uint16_t         dev_addr,
                    uint16_t         dev_flags);

/**
 * \brief I2C����ṹ����Ϣ��������
 *
 * \param[in] p_trans : ָ����ṹ���ָ��
 * \param[in] addr    : �����Ĵӻ��豸��ַ
 * \param[in] flags   : ��������еĿ��Ʊ�ʶλ
 *                      AM_I2C_M_*�ĺ�ֵ���߶��AM_I2C_M_*��� ��OR��ֵ (#AM_I2C_M_RD) 
 * \param[in] p_buf   : ָ���ͻ��߽������ݻ���
 * \param[in] length  : ��ǰ���������/��ַ����
 * \param[in] pfn_callback   : ������ɻص�����
 * \param[in] p_callback_arg : �ص�������ڲ���
 *
 * \retval  AM_OK     : ����ṹ������������
 */
int am_i2c_mktrans (am_i2c_transfer_t *p_trans, 
                    uint16_t           addr,  
                    uint16_t           flags, 
                    void              *p_buf, 
                    uint16_t           length,
                    int                (*pfn_callback)(void *,int),
                    void              *p_callback_arg);

/**
 * \brief I2C��������/��ַ����
 *
 * \param[in] handle  : I2C��׼����������
 * \param[in] p_trans : ָ����ṹ���ָ��
 *
 * \retval  AM_OK     : ������������
 * \retval -AM_EINVAL : ����������� 
 *  ��������Լ����״̬���أ�ͨ������ص�״̬λ��ȡ
 *    \li  AW_OK  �������
 *    \li -AM_EIO ���ߴ�����������ٲô����
 */

int am_i2c_transfer(am_i2c_handle_t handle, am_i2c_transfer_t  *p_trans);


/**
 * \brief I2Cд����
 *
 * \param[in] handle   : I2C��׼����������
 * \param[in] p_device : ָ��ӻ��豸��Ϣ�Ľṹ���ָ��
 * \param[in] sub_addr : �ӻ��豸�ӵ�ַ
 * \param[in] p_buf    : ָ����/�������ݻ���
 * \param[in] nbytes   : ���ݻ��泤��
 *
 * \return  AM_OK : д�������
 */
int am_i2c_write(am_i2c_handle_t  handle,
                 am_i2c_device_t *p_device,
                 uint32_t         sub_addr,
                 uint8_t         *p_buf, 
                 uint32_t         nbytes);
/**
 * \brief I2C������
 *
 * \param[in] handle   : I2C��׼����������
 * \param[in] p_device : ָ��ӻ��豸��Ϣ�Ľṹ���ָ��
 * \param[in] sub_addr : �ӻ��豸�ӵ�ַ
 * \param[in] p_buf    : ָ����/�������ݻ���
 * \param[in] length   : ���ݻ��泤��
 *
 * \return  AM_OK : ��������� 
 */
int am_i2c_read (am_i2c_handle_t  handle,
                 am_i2c_device_t *p_device,
                 uint32_t         sub_addr,
                 void            *p_buf,
                 uint16_t         length);
/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2C_H */

/* end of file */
