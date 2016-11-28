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
 * \brief PWM����������CAP��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-20  snk, first implementation.
 * \endinternal
 */

#ifndef __AMDR_PWM_CAP_H
#define __AMDR_PWM_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "amhw_pwm.h"

/**
 * \addtogroup amdr_if_pwm_cap
 * \copydoc amdr_pwm_cap.h
 * @{
 */

/**
 * \brief CAP������ص�GPIO��Ϣ
 */
typedef struct amdr_pwm_cap_ioinfo {
    uint32_t gpio;                          /**< \brief ��Ӧ��GPIO�ܽ�  */
    uint32_t func;                          /**< \brief ΪPWM����ʱ��GPIO��������   */
    uint32_t dfunc;                         /**< \brief ���ܹܽ�PWM����ʱ��Ĭ��GPIO�������� */
} amdr_pwm_cap_ioinfo_t;



/**
 * \brief pwm��������ص��豸��Ϣ
 */
typedef struct amdr_pwm_cap_devinfo {
    amhw_pwm_t                *p_hw_pwm;   /**< \brief ָ��pwm�Ĵ������ָ�� */
    uint8_t                    inum;       /**< \brief  �жϺ�          */
    amdr_pwm_cap_ioinfo_t     *p_ioinfo;      /**< \brief ָ��PWM�ܽ���Ϣ�ṹ��            */
    uint8_t                    channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ4 */
} amdr_pwm_cap_devinfo_t;
 
/**
 * \brief pwm�������豸�ṹ��
 */
typedef struct amdr_pwm_cap_dev {
    am_cap_serv_t           cap_serv;       /**< \brief ��׼CAP����  */
    
    struct {   
        am_cap_callback_t   callback_func;  /**< \brief �ص����� */
        void               *p_arg;          /**< \brief �ص��������û�����   */
    }callback_info[2];                      /**< \brief �洢���2ͨ���Ļص�������Ϣ */
    
    /** \brief ָ��pwm�������豸��Ϣ������ָ�� */
    const amdr_pwm_cap_devinfo_t  *p_devinfo; 

} amdr_pwm_cap_dev_t;

/**
 * \brief ��ʼ��pwmΪ������
 *
 * \param[in] p_dev     : ָ��pwm�������豸��ָ��
 * \param[in] p_devinfo : ָ��pwm�������豸��Ϣ������ָ��
 *
 * \return CAP��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_cap_handle_t amdr_pwm_cap_init(amdr_pwm_cap_dev_t           *p_dev,
                                  const amdr_pwm_cap_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��mcpwm������ʱ�����ʼ��mcpwm�����ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��mcpwm�������豸��ָ��
 * \return ��
 */
void amdr_pwm_cap_deinit(amdr_pwm_cap_dev_t *p_dev);


/** 
 * @} 
 */

 
#ifdef __cplusplus
}
#endif

#endif /* __AMDR_PWM_CAP_H */

/* end of file */
