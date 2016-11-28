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
 * \brief GPIO����������GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-5-08  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_GPIO_H
#define __AMDR_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"  
#include "am_bitops.h"
#include "lpc177x_8x_pin.h"

#include "amhw_gpio.h"
#include "amhw_pincon.h"
#include "amhw_gpioint.h"
    
/** 
 * \addtogroup amdr_if_gpio
 * \copydoc amdr_gpio.h
 * @{
 */

/**
 * \brief ���ŵĴ�����Ϣ 
 */
struct amdr_gpio_trigger_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
};

/**
 * \brief GPIO �豸��Ϣ
 */
typedef struct amdr_gpio_devinfo {
    
    /** \brief ָ��GPIO�Ĵ�����Ļ���ַ */
    uint32_t       gpio_regbase;
    
    /** \brief ָ��IOCON�Ĵ������ָ�� */
    amhw_pincon_t  *p_hw_pincon;

    /** \brief ָ�������жϼĴ������ָ�� */
    amhw_gpioint_t *p_hw_gpioint;

    /** \brief GPIO�����жϺţ���EXTINT3�����жϺ� */
    int8_t         gpioint_inum;

    /** 
     * \brief GPIO�����жϺ�����,��PORT0��PORT2֧���жϣ���ֵ���Ϊ64
     *        �����ʵ���õ��ж��������ø�ֵ��
     */
    size_t         gpioint_count;

    /** \brief ָ�����Ŵ�����Ϣ��ָ��,��СӦ����pint_countһ�� */
    struct amdr_gpio_trigger_info *p_triginfo;
    
} amdr_gpio_devinfo_t;

/**
 * \brief GPIO�豸
 */
typedef struct amdr_gpio_dev {
    
    /** \brief ָ��GPIO�豸��Ϣ��ָ�� */
    const amdr_gpio_devinfo_t *p_devinfo;

    /** \brief ������Ϣӳ�� */
    uint8_t                    infomap[AWBL_GPIOPIN_COUNT_MAX];
    
    /** \brief ����״̬���� */
    uint8_t                    trig_state[AWBL_GPIOPIN_COUNT_MAX];
    
} amdr_gpio_dev_t;

/**
 * \brief GPIO��ʼ�� 
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ�� 
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ�� 
 *
 * \retval AM_OK : �����ɹ� 
 */
int amdr_gpio_init(amdr_gpio_dev_t           *p_dev, 
                   const amdr_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIO���ʼ��
 *
 * \param[in] p_dev : ָ��GPIO�豸��ָ�� 
 *
 * \return �� 
 */
void amdr_gpio_deinit(amdr_gpio_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_GPIO_H */

/* end of file */
