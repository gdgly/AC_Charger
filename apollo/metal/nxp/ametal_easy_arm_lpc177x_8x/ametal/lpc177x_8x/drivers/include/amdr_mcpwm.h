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
 * \brief MCPWM����������MCPWM��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  snk, first implementation.
 * \endinternal
 */

#ifndef __AMDR_MCPWM_H
#define __AMDR_MCPWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "amhw_mcpwm.h"
#include "am_bitops.h"
    

/**
 * \addtogroup amdr_if_mcpwm
 * \copydoc amdr_mcpwm.h
 * @{
 */


/**
 * \brief mcpwm������ص�GPIO��Ϣ
 */
typedef struct amdr_mcpwm_ioinfo {
    uint32_t gpio;                          /**< \brief ��Ӧ��GPIO�ܽ�  */
    uint32_t func;                          /**< \brief ΪPWM����ʱ��GPIO��������  */
    uint32_t dfunc;                         /**< \brief ���ܹܽ�PWM����ʱ��Ĭ��GPIO�������� */
} amdr_mcpwm_ioinfo_t;

/**
 * \brief mcpwm������ص��豸��Ϣ
 */
typedef struct amdr_mcpwm_devinfo {
    amhw_mcpwm_t            *p_hw_mcpwm;    /**< \brief ָ��mcpwm�Ĵ������ָ�� */
    uint8_t                  inum;          /**< \brief mcpwm��Ӧ���жϺ� */
    amdr_mcpwm_ioinfo_t     *p_ioinfo;      /**< \brief ָ��PWM�ܽ���Ϣ�ṹ��   */
    uint8_t                  channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ4 */
} amdr_mcpwm_devinfo_t;
 
/**
 * \brief mcpwm�����豸�ṹ��
 */
typedef struct amdr_mcpwm_dev {
   
    /** \brief ��׼PWM����                         */
    am_pwm_serv_t                    pwm_serv; 
    
    /** \brief ָ��ʱ��PWM�����豸��Ϣ������ָ�� */
    const amdr_mcpwm_devinfo_t      *p_devinfo;

} amdr_mcpwm_dev_t;

/**
 * \brief ��ʼ��mcpwm�������
 *
 * \param[in] p_dev     : ָ��ʱ��PWM��������豸��ָ��
 * \param[in] p_devinfo : ָ��ʱ��PWM��������豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t amdr_mcpwm_init(amdr_mcpwm_dev_t           *p_dev,
                                const amdr_mcpwm_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��mcpwm�������ʱ�����ʼ����ʱ����PWM������ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��ʱ��PWM��������豸��ָ��
 * \return ��
 */
void amdr_mcpwm_deinit(amdr_mcpwm_dev_t *p_dev);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_MCPWM_H */

/* end of file */



