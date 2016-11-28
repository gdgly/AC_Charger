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
 * \brief  SSP����������SSP��׼�ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-28  ben, first implementation.
 * \endinternal
 */

#ifndef __AMDR_SSP_H
#define __AMDR_SSP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_spi.h"    
#include "am_types.h"
#include "amhw_int.h"
#include "amhw_power.h"
#include "amhw_ssp.h"

/**
 * \addtogroup amdr_if_ssp
 * \copydoc amdr_ssp.h
 * @{
 */


/**
 * \brief SSP �豸��Ϣ�ṹ��
 */
typedef struct amdr_ssp_devinfo {
    
	amhw_ssp_t   *p_hw_ssp;            /**< \brief ָ��SPI�Ĵ������ָ��  */
    uint16_t      inum;                /**< \brief SSP �жϱ��          */
    uint8_t       bits_per_word;       /**< \brief ����֡��λ��          */
    uint32_t      flags;               /**< \brief SPI ���ñ�ʶ          */
    uint32_t      speed;               /**< \brief ��ʼ������            */

} amdr_ssp_devinfo_t;

/** \brief SSP �豸��Ϣ�ض��� */
typedef amdr_ssp_devinfo_t am_ssp_devinfo_hw_t;


/**
 * \brief SSP �豸
 */
typedef struct amdr_ssp_dev {
    
     /** \brief SSP��׼���������� */
    am_spi_serv_t             spi_serve;  
    
    /** \brief ָ��SPI����ṹ���ָ�� */
    am_spi_transfer_t        *p_trans; 
    
    /** \brief ָ��SSP�豸��Ϣ��ָ�� */
    const amdr_ssp_devinfo_t *p_devinfo;
    
    uint8_t         state;          /**< \brief ��ǰ״̬   */
    
    uint32_t        cur_speed;      /**< \brief ��������ǰ�ٶ�   */
    uint8_t         cur_bpw;        /**< \brief ��������ǰ�ִ�С */
    uint8_t         cur_flags;      /**< \brief ��������ǰģʽ   */   
    uint32_t        nbytes_to_recv; /**< \brief �����յ��ֽ���   */    
    uint32_t        data_tx_ptr;    /**< \brief ���ݴ������     */
    uint32_t        data_rx_ptr;    /**< \brief ���ݴ������     */    
       
} amdr_ssp_dev_t;

/**
 * \brief SSP ��ʼ��
 *
 * \param[in] p_dev     : ָ��SSP�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SSP�豸��Ϣ�ṹ���ָ��
 *
 * \return  SPI��׼���������� 
 */
am_spi_handle_t amdr_ssp_init(amdr_ssp_dev_t           *p_dev,
                              const amdr_ssp_devinfo_t *p_devinfo);

/**
 * \brief ���SPI��ʼ��
 * \param[in] p_dev : ָ��SPI�豸�ṹ���ָ��
 * \return ��
 */
void amdr_ssp_deinit(amdr_ssp_dev_t *p_dev);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

/* end of file */

