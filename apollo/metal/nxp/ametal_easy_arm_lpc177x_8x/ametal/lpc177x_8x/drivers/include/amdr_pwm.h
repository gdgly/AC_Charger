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
 * \brief PWM����������PWM��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-16  snk, first implementation.
 * \endinternal
 */

#ifndef __AMDR_PWM_H
#define __AMDR_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "amhw_pwm.h"
#include "am_bitops.h"
    

/**
 * \addtogroup amdr_if_pwm
 * \copydoc amdr_pwm.h
 * @{
 */

/**
 * \brief PWM������ص�GPIO��Ϣ
 */
typedef struct amdr_pwm_ioinfo {
    uint32_t gpio;                          /**< \brief ��Ӧ��GPIO�ܽ�  */
    uint32_t func;                          /**< \brief ΪPWM����ʱ��GPIO��������  */
    uint32_t dfunc;                         /**< \brief ���ܹܽ�PWM����ʱ��Ĭ��GPIO�������� */
} amdr_pwm_ioinfo_t;


/**
 * \brief pwm������ص��豸��Ϣ
 */
typedef struct amdr_pwm_devinfo {
    amhw_pwm_t            *p_hw_pwm;      /**< \brief ָ��pwm�Ĵ������ָ��  */
    uint8_t                inum;          /**< \brief pwm��Ӧ���жϺ�  */
    amdr_pwm_ioinfo_t     *p_ioinfo;      /**< \brief ָ��PWM�ܽ���Ϣ�ṹ�� */
    uint8_t                channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ4 */
} amdr_pwm_devinfo_t;
 
/**
 * \brief pwm�����豸�ṹ��
 */
typedef struct amdr_pwm_dev {
   
    /** \brief ��׼PWM����                         */
    am_pwm_serv_t                    pwm_serv; 
    
    /** \brief ָ��ʱ��PWM�����豸��Ϣ������ָ�� */
    const amdr_pwm_devinfo_t        *p_devinfo;

} amdr_pwm_dev_t;

/**
 * \brief ��ʼ��pwm�������
 *
 * \param[in] p_dev     : ָ��ʱ��PWM��������豸��ָ��
 * \param[in] p_devinfo : ָ��ʱ��PWM��������豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t amdr_pwm_init(amdr_pwm_dev_t             *p_dev,
                                const amdr_pwm_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��pwm�������ʱ�����ʼ����ʱ����PWM������ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��ʱ��PWM��������豸��ָ��
 * \return ��
 */
void amdr_pwm_deinit(amdr_pwm_dev_t *p_dev);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_PWM_H */

/* end of file */



