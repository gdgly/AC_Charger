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
 * \brief  DAC����������DAC��׼�ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-05-29  snk, first implementation.
 * \endinternal
 */

#ifndef __AMDR_DAC_H
#define __AMDR_DAC_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_dac.h"
#include "amhw_dac.h"
    
/** 
 * \addtogroup amdr_if_dac
 * \copydoc amdr_dac.h
 * @{
 */
    
/**
 * \brief DAC�豸��Ϣ�ṹ��
 */
typedef struct amdr_dac_devinfo {
    
    /** \brief ָ��DAC�Ĵ�����Ľṹ��ָ��    */
    amhw_dac_t  *p_hw_dac;

    /** \brief DAC�������� */
    uint8_t     bits;

    /** \brief  DAC�ο���ѹ    */
    uint32_t    vref;
   
} amdr_dac_devinfo_t;

/**
 * \brief DAC�豸�ṹ��
 */
typedef struct amdr_dac_dev {

    am_dac_serv_t              dac_serv;   /**< \brief DAC��׼����           */
    const amdr_dac_devinfo_t  *p_devinfo;  /**< \brief ָ��DAC�豸��Ϣ��ָ�� */
} amdr_dac_dev_t;

/**
 * \brief ��ʼ��DAC 
 *
 * \param[in] p_dev     : ָ��DAC�豸
 * \param[in] p_devinfo : ָ��DAC�豸��Ϣ
 *
 * \return  DAC ��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_dac_handle_t amdr_dac_init(amdr_dac_dev_t           *p_dev,
                              const amdr_dac_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ��DAC
 * \param[in] p_dev : ָ��DAC�豸
 * \return  ��
 */
void amdr_dac_deinit(amdr_dac_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_DAC_H */

/* end of file */
