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
 * \brief  QEI������ʵ��
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  anu, first implementation.
 * \endinternal
 */
 

#ifndef __AMDR_QEI_H
#define __AMDR_QEI_H

#ifdef __cplusplus
extern "C" {
#endif
	
	
#include "am_types.h"
#include "amhw_qei.h"
#include "am_int.h"
    
    
/** 
 * \addtogroup amdr_if_qei
 * \copydoc amdr_qei.h
 * @{
 */
    

/**
 * \name QEI�����ģʽ����
 * \anchor grp_amdr_qei_capmode
 * @{
 */
    
typedef uint32_t amdr_qei_capmode_t; /**< \brief QEI�����ģʽ���� */
#define AMDR_QEI_CAPMODE_PHA    0    /**< \brief ����A���ر߽��в������ */
#define AMDR_QEI_CAPMODE_PHAB   1    /**< \brief ����A��B���ر߽��в������ */

/** @} */

/**
 * \name QEI�źŵ�ģʽ����
 * \anchor grp_amdr_qei_sigmode
 * @{
 */
    
typedef uint32_t amdr_qei_sigmode_t;       /**< \brief QEI�źŵ�ģʽ���� */
#define AMDR_QEI_SIGMODE_QUADRATURE    0   /**< \brief ��A����B��Ϊ��������������λ�ź� */
#define AMDR_QEI_SIGMODE_DIR_A_CLK_B   1   /**< \brief ��AΪ�����źţ���BΪʱ���ź� */

/** @} */

/**
 * \brief QEI������Ϣ
 */
typedef struct amdr_qei_cfg_info {
    uint32_t           maxpos;            /**< \brief λ�����ֵ  */
    uint32_t           cmpos0;            /**< \brief λ��0�Ƚ�ֵ  */
    uint32_t           cmpos1;            /**< \brief �Ƚ�λ��1ֵ  */
    uint32_t           cmpos2;            /**< \brief �Ƚ�λ��2ֵ  */
    uint32_t           cmpindex;          /**< \brief �����Ƚ�ֵ  */
    uint32_t           timeload;          /**< \brief ��ʱ��װ��ʱ��ֵ  */
    uint32_t           cmpvel;            /**< \brief �ٶȱȽ�ֵ  */
    uint32_t           filter;            /**< \brief ����ʱ��  */
    amdr_qei_capmode_t capmode;           /**< \brief �����ģʽ  */
    amdr_qei_sigmode_t sigmode;           /**< \brief �źŵ�ģʽ  */
} amdr_qei_cfg_info_t;

/**
 * \brief �жϻص���Ϣ 
 */
typedef struct amdr_qei_intcb_info {

    /** \brief �����ص�����   */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
	
} amdr_qei_intcb_info_t;

/**
 * \brief QEI �豸��Ϣ 
 */
typedef struct amdr_qei_devinfo {
    amhw_qei_t              *p_hw_qei;       /**< \brief QEI�Ĵ����׵�ַ  */
    amdr_qei_cfg_info_t     *p_cfg_info;     /**< \brief QEI ������Ϣ */
    amdr_qei_intcb_info_t   *p_intcb_info;   /**< \brief QEI �ص���Ϣ */
    uint16_t                 inum;           /**< \brief QEI �жϺ�  */
} amdr_qei_devinfo_t;

/**
 * \brief QEI �豸�ṹ��
 */
typedef struct amdr_qei_dev {
    const amdr_qei_devinfo_t  *p_devinfo;   /**< \brief ָ��QEI�豸��Ϣ */
} amdr_qei_dev_t;

/**
 * \brief ���ò����ģʽ 
 *
 * \param[in] p_dev : QEI�豸
 * \param[in] mode  : ����ģʽ ���ò������μ�
 *                    \ref grp_amdr_qei_capmode "capture mode"
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 *
 * \note AMDR_QEI_CAPMODE_PHA:edgesΪ2��AMDR_QEI_CAPMODE_PHAB:edgesΪ4
 */
int amdr_qei_capmode_set (amdr_qei_dev_t *p_dev, amdr_qei_capmode_t mode);

/**
 * \brief �����źŵ�ģʽ
 *
 * \param[in] p_dev : QEI�豸
 * \param[in] mode  : �ź�ģʽ ���ò������μ�
 *                    \ref grp_amdr_qei_sigmode "signal mode"
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 */
int amdr_qei_sigmode_set (amdr_qei_dev_t *p_dev, amdr_qei_sigmode_t mode);
    
/**
 * \brief ����QEI���ж�
 *
 * \param[in] p_dev : QEI�豸
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 * \retval -AM_EPERM    û�пյ��ڴ�ӳ��
 */
int amdr_qei_int_connect (amdr_qei_dev_t *p_dev);

/**
 * \brief ע���жϻص�����
 *
 * \param[in] p_dev        : QEI�豸
 * \param[in] inttype      : �ж����� �ж����� ���ò������μ�
 *                           \ref grp_amhw_qei_int "interrupt type"
 * \param[in] pfn_callback : Ҫע��Ļص�����
 * \param[in] p_arg        : �����ص������Ĳ���
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 */
int amdr_qei_intcb_connect (amdr_qei_dev_t      *p_dev,
                            amhw_qei_int_type_t  inttype,
                            am_pfnvoid_t         pfn_callback,
                            void                *p_arg);

/**
 * \brief ɾ��ĳ�����͵��жϻص�����
 *
 * \param[in] p_dev        : QEI�豸
 * \param[in] inttype      : �ж����� ���ò������μ�
 *                           \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 */
int amdr_qei_intcb_disconnect (amdr_qei_dev_t        *p_dev,
                               amhw_qei_int_type_t    inttype);
    
/**
 * \brief ��ʼ��QEI
 *
 * \param[in] p_dev     : QEI�豸
 * \param[in] p_devinfo : QEI�豸��Ϣ
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 */
int amdr_qei_init (amdr_qei_dev_t           *p_dev,
                   const amdr_qei_devinfo_t *p_devinfo);

/**
 * \brief ���ʼ��QEI
 * \param[in] p_dev   : QEI�豸
 *
 * \retval AM_OK        ����
 * \retval -AM_EINVAL   ������Ч
 */
int amdr_qei_deinit (amdr_qei_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_QEI_H */

/*end of file */



