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
 * \brief MCPWM����������CAP��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-07  snk, first implementation.
 * \endinternal
 */

#ifndef __AMDR_MCPWM_CAP_H
#define __AMDR_MCPWM_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "amhw_mcpwm.h"

/**
 * \addtogroup amdr_if_mcpwm_cap
 * \copydoc amdr_mcpwm_cap.h
 * @{
 */


/**
 * \brief CAP������ص�GPIO��Ϣ
 */
typedef struct amdr_mcpwm_cap_ioinfo {
    uint32_t gpio;                          /**< \brief ��Ӧ��GPIO�ܽ� */
    uint32_t func;                          /**< \brief ΪPWM����ʱ��GPIO�������� */
    uint32_t dfunc;                         /**< \brief ���ܹܽ�PWM����ʱ��Ĭ��GPIO��������  */
} amdr_mcpwm_cap_ioinfo_t;

/**
 * \brief mcpwm��������ص��豸��Ϣ
 */
typedef struct amdr_mcpwm_cap_devinfo {
    amhw_mcpwm_t            *p_hw_mcpwm;    /**< \brief ָ��mcpwm�Ĵ������ָ�� */
    uint8_t                  inum;          /**< \brief ��ʱ���жϺ� */
    amdr_mcpwm_cap_ioinfo_t *p_ioinfo;      /**< \brief ָ��PWM�ܽ���Ϣ�ṹ�� */
    uint8_t                  channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ4 */
} amdr_mcpwm_cap_devinfo_t;
 
/**
 * \brief mcpwm�������豸�ṹ��
 */
typedef struct amdr_mcpwm_cap_dev {
    am_cap_serv_t           cap_serv;       /**< \brief ��׼CAP����           */
    
    struct {   
        am_cap_callback_t   callback_func;  /**< \brief �ص�����              */
        void               *p_arg;          /**< \brief �ص��������û�����    */
    }callback_info[3];                      /**< \brief �洢���3ͨ���Ļص�������Ϣ */
    
    /** \brief ָ��mcpwm�������豸��Ϣ������ָ�� */
    const amdr_mcpwm_cap_devinfo_t  *p_devinfo; 

} amdr_mcpwm_cap_dev_t;

/**
 * \brief ��ʼ��mcpwmΪ������
 *
 * \param[in] p_dev     : ָ��mcpwm�������豸��ָ��
 * \param[in] p_devinfo : ָ��mcpwm�������豸��Ϣ������ָ��
 *
 * \return CAP��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_cap_handle_t amdr_mcpwm_cap_init(amdr_mcpwm_cap_dev_t           *p_dev,
                                    const amdr_mcpwm_cap_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��mcpwm������ʱ�����ʼ��mcpwm�����ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��mcpwm�������豸��ָ��
 * \return ��
 */
void amdr_mcpwm_cap_deinit(amdr_mcpwm_cap_dev_t *p_dev);


/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_MCPWM_CAP_H */

/* end of file */
