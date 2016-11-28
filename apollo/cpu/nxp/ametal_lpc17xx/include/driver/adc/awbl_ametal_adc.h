/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AWBus-lite ametal ADC
 *
 * \internal
 * \par modification history:
 * - 1.00 2015-12-25 cod, first implementation
 * \endinternal
 */

#ifndef __AWBL_AMETAL_ADC_H
#define __AWBL_AMETAL_ADC_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#include "awbl_adc.h"
#include "aw_spinlock.h"
#include "aw_isr_defer.h"
#include "am_adc.h"
#include "amdr_adc.h"

/** \brief ADC ������ */
#define AWBL_AMETAL_ADC_NAME   "ametal_adc"
/*******************************************************************************
    defines
*******************************************************************************/
/**
 * \brief ametal ADC �豸��Ϣ
 */
typedef struct awbl_ametal_adc_param {
    
    /** \brief Ӳ������豸��Ϣ */
    void *p_hw_devinfo;

    /** \brief ADC ���������Ϣ */
    struct awbl_adc_servinfo adc_servinfo;

    /** \brief BSP function to pre initialize the device */
    void (*pfunc_plfm_init) (void);
    
} awbl_ametal_adc_param_t;


/**
 * \brief ametal ADC �豸ʵ��
 */
typedef struct awbl_ametal_adc_dev {

    /** \brief �̳��� AWBus �豸 */
    struct awbl_dev         super;

    /** \brief ADC ���� */
    struct awbl_adc_service adc_serv;

    /** \brief �豸��ǰת����ͨ��*/
	aw_adc_channel_t        channel;

    /** \brief ADC ���ݻ����������� */
    aw_adc_buf_desc_t      *p_bufdesc;

    /** \brief ADC ���ݻ���������������  */
    uint32_t                desc_num;

    /** \brief ��ǰʹ�õĻ�������������  */
    uint32_t                cur_desc_cnt;

    /** \brief ��ǰ���������� */
    uint32_t                cur_buf_cnt;

    /** \brief ʣ��ת�����д���   */
    uint32_t                remain_cnt;

    /** \brief ������ɻص�����     */
    pfn_adc_complete_t      pfn_seq_complete;

    /** \brief ������ɻص��������� */
    void                   *p_arg;

    /** \brief ����������  */
    aw_spinlock_isr_t       lock;

    /** \brief ADC����״̬  */
    uint8_t                 stat;
#define __ADC_STAT_INIT      0   /** \brief ��ʼ���׶�      */
#define __ADC_STAT_START     1   /** \brief ADC����ת��   */
#define __ADC_STAT_COMPLETE  2   /** \brief ADCת�����   */
#define __ADC_STAT_STOP      3   /** \brief ADCת��ֹͣ   */
    
} awbl_ametal_adc_dev_t;

/**
 * \brief ametal driver register
 */
void awbl_ametal_adc_drv_register(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_AMETAL_ADC_H */

/* end of file */
