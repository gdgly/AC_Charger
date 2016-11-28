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
 * \brief  CAN������ʵ��
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-06-02  anu, first implementation.
 * \endinternal
 */
 

#ifndef __AMDR_CAN_H
#define __AMDR_CAN_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "am_types.h"
#include "am_can.h"
#include "amhw_can.h"

/**
 * \addtogroup amdr_if_can
 * \copydoc amdr_can.h
 * @{
 */

/**
 * \name �����˲�����
 * \anchor grp_amdr_canaf_act
 * @{
 */

#define AMDR_CANAF_ACT_OPERATE   0x00         /**< \brief ���������˲�ģʽ */
#define AMDR_CANAF_ACT_BYPASS    0x01         /**< \brief ������·ģʽ */
#define AMDR_CANAF_ACT_ADD       0x02         /**< \brief �����˲���¼ */
#define AMDR_CANAF_ACT_DEL       0x03         /**< \brief ɾ�������˲���¼ */

/** @} */

/**
 * \name �����˲�������
 * \anchor grp_amdr_canaf_ram_type
 * @{
 */

typedef uint32_t amdr_canaf_rec_type_t;        /**< \brief �����˲������� */
#define AMDR_CANAF_REC_TYPE_SSF   0x00         /**< \brief ������׼֡�����˲���¼ */
#define AMDR_CANAF_REC_TYPE_GSF   0x01         /**< \brief ��׼֡�������˲���¼ */
#define AMDR_CANAF_REC_TYPE_SEF   0x02         /**< \brief ������չ֡�����˲���¼ */
#define AMDR_CANAF_REC_TYPE_GEF   0x03         /**< \brief ��չ֡�������˲���¼ */
#define AMDR_CANAF_REC_TYPE_NONE  0XFF         /**< \brief �����������˲����� */

/** @} */

/** \brief CAN���������жϷ���������Ϣ */
typedef struct amdr_can_comm_isr_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_isr;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;

} amdr_can_comm_isr_info_t;

/**
 * \brief CAN ���������豸��Ϣ
 */
typedef struct amdr_can_comm_devinfo {

    amhw_canaf_ram_t        *p_hw_canaf_ram;        /**< \brief CAN �˲���RAM ��ַ */
    amhw_canaf_t            *p_hw_canaf;            /**< \brief CAN �˲�����ַ     */
    amhw_cancr_t            *p_hw_cancr;            /**< \brief CAN ���Ŀ��ƼĴ�����ַ */

    /** \brief �жϺ� */
    int inum;

    /** \brief ISR ��Ϣ���� ��CAN�豸������ */
    int isrinfo_cnt;

    /** \brief ISR ��Ϣӳ���ڴ�(��С�� isrinfo_cnt һ��) */
    amdr_can_comm_isr_info_t *p_isrinfo;

} amdr_can_comm_devinfo_t;

/**
 * \brief CAN���������豸ʵ��
 */
typedef struct amdr_can_comm_dev {

    /** \brief ָ���ж��豸��Ϣ��ָ�� */
    const amdr_can_comm_devinfo_t *p_devinfo;

    /** \brief CAN �˲�����  */
    amdr_canaf_rec_type_t          filter_type;

} amdr_can_comm_dev_t;

/**
 * \brief �жϻص���Ϣ 
 */
typedef struct amdr_can_intcb_info {

    /** \brief �����ص�����   */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
	
} amdr_can_intcb_info_t;

/**
 * \brief CAN �豸��Ϣ 
 */
typedef struct amdr_can_devinfo {

    amhw_can_t              *p_hw_can;              /**< \brief CAN �Ĵ�����ַ        */
    amdr_can_intcb_info_t   *p_intcb_info;          /**< \brief CAN �жϻص� */	
    int                      can_id;              	/**< \brief CAN ��ID��(��0��ʼ)*/

} amdr_can_devinfo_t;


/**
 * \brief �豸
 */
typedef struct amdr_can_dev {

     /** \brief CAN ��׼���� */
    am_can_serv_t              handle;
    
    /** \brief CAN �豸��Ϣ  */
    const amdr_can_devinfo_t  *p_devinfo;

    /** \brief CAN ��¼��������  */
    uint8_t                    send_type;

    /** \brief CAN ��¼��������  */
    uint32_t                   send_cmd;

} amdr_can_dev_t;

/**
 * \brief  CAN�������ֳ�ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 * \param[in] p_devinfo : �豸��Ϣ
 *
 * \retval AM_OK      ���ɹ�
 * \retval -AM_EINVAL ����������
 * \retval -AM_EPERM  ��û�пյ��ڴ�ӳ��
 */
int amdr_can_comm_init (amdr_can_comm_dev_t           *p_dev,
                        const amdr_can_comm_devinfo_t *p_devinfo);

/**
 * \brief  CAN�������ֽ��ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 *
 * \retval AM_OK      ���ɹ�
 * \retval -AM_EINVAL �� ��������
 * \retval -AM_EPERM  �� ����������
 */
int amdr_can_comm_deinit (amdr_can_comm_dev_t *p_dev);

/**
 * \brief  CAN��ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 * \param[in] p_devinfo : �豸��Ϣ
 *
 * \return handle
 */
am_can_handle_t amdr_can_init (amdr_can_dev_t           *p_dev,
                               const amdr_can_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ��
 *
 * \param[in] p_dev     : �豸ʵ��
 *
 * \return ��
 */
void amdr_can_deinit (amdr_can_dev_t *p_dev);

/** 
 * @} amdr_if_can
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_CAN_H */

/*end of file */



