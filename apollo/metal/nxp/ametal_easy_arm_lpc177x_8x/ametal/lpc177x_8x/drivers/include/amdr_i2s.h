
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
 * \brief I2S����������I2S��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 15-07-14  sam, first implementation.
 * \endinternal
 */

#ifndef __AMDR_I2S_H
#define __AMDR_I2S_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2s.h"	
#include "amhw_i2s.h"		

/**
 * \addtogroup amdr_if_i2s
 * \copydoc amdr_i2s.h
 * @{
 */	
	

/**
 * \brief LPC17XX I2S  �豸��Ϣ
 */	

typedef struct amdr_i2s_devinfo {
	uint8_t          ms_mode;          /**< \brief ����ģʽѡ��*/
	
	uint8_t          clk_select;       /**< \brief  ʱ��ѡ�� */  

	uint8_t          irq_depth;        /**< \brief  �ж����ѡ�� */
	
    uint8_t          wordwidth_set;    /**< \brief �����ֵĿ��  */
	
    uint8_t          sound_mode;       /**< \brief ����ģʽ  ����/������	*/      
   
    uint32_t         sample_speed;     /**< \brief I2S��ʼ�������ٶ�,am_i2s_speed_set() ��׼�ӿڿ��Ըı����� */
 
    amhw_i2s_t      *p_hw_i2s;         /**< \brief ָ��I2S�Ĵ������ָ��  */
	
    uint16_t         inum;             /**< \brief I2S ���������жϺ�     */
} amdr_i2s_devinfo_t;

/**
 * \brief I2S�豸
 */
typedef struct amdr_i2s_dev {

    am_i2s_serv_t  i2s_serv;                    /**< \brief I2S ��׼����        */
   
    int (*pfn_txdata_get)(void *, uint32_t *);  /**< \brief ���ͺ���ָ��        */
    int (*pfn_rxdata_put)(void *, uint32_t);    /**< \brief ���պ���ָ��        */
    int (*pfn_err)(void *, int, void *, int);   /**< \brief ������ָ��        */

    void     *txget_arg;                        /**< \brief ���ͺ�������ָ��    */
    void     *rxput_arg;                        /**< \brief ���պ�������ָ��    */
    void     *err_arg;                          /**< \brief ����������ָ��    */
	
    /** \brief ָ���豸��Ϣָ�� */
    const amdr_i2s_devinfo_t *p_devinfo;
	
} amdr_i2s_dev_t;


/**
 * \brief  I2S ��ʼ��
 *
 * \param[in] p_dev     : ָ��I2S�豸��ָ��
 * \param[in] p_devinfo : ָ��I2S�豸��Ϣ��ָ�� 
 *
 * \return ��׼I2S�ӿڷ���.��ΪNULL�����ʼ��ʧ��
 */
am_i2s_handle_t amdr_i2s_init(amdr_i2s_dev_t           *p_dev,
                              const amdr_i2s_devinfo_t *p_devinfo);

/**
 * \brief  I2S ���ʼ��
 * \param[in] p_dev : ָ��I2S�豸��ָ��
 * \return ��
 */
void amdr_i2s_deinit(amdr_i2s_dev_t *p_dev);

/** 
 * @} 
 */
#ifdef __cplusplus
}
#endif

#endif    /* __AMDR_I2S_H */

/* end of file */


