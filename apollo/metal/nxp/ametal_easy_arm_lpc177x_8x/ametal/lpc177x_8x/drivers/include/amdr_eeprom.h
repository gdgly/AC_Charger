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
 * \brief EEPROM����������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-15  anu, first implementation.
 * \endinternal
 */

#ifndef __AMDR_EEPROM_H
#define __AMDR_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_eeprom.h"
    
/** 
 * \addtogroup amdr_if_eeprom
 * \copydoc amdr_eeprom.h
 * @{
 */

/**
 * \brief EEPROM �жϻص���Ϣ
 */
typedef struct amdr_eeprom_intcb_info {

    am_pfnvoid_t  pfn_callback;                /**< \brief �����ص����� */
    void         *p_arg;                       /**< \brief �ص������Ĳ��� */

} amdr_eeprom_intcb_info_t;

/**
 * \brief EEPROM �豸��Ϣ
 */
typedef struct amdr_eeprom_devinfo {
    
    amhw_eeprom_t              *p_hw_eeprom;    /**< \brief EEPROM �Ĵ����׵�ַ  */
    amdr_eeprom_intcb_info_t   *p_intcb_info;   /**< \brief EEPROM �ص���Ϣ */
    uint16_t                    inum;           /**< \brief EEPROM �жϺ�  */
    uint16_t                    int_count;      /**< \brief EEPROM �жϺ�  */
    
} amdr_eeprom_devinfo_t;

/**
 * \brief EEPROM �豸
 */
typedef struct amdr_eeprom_dev {
    
    /** \brief ָ��EEPROM�豸��Ϣ��ָ�� */
    const amdr_eeprom_devinfo_t *p_devinfo;

} amdr_eeprom_dev_t;

/**
 * \brief  EEPROM ����ģʽ
 */
typedef enum
{
    AMDR_EEPROM_MODE_8_BIT,
    AMDR_EEPROM_MODE_16_BIT,
    AMDR_EEPROM_MODE_32_BIT
}amdr_eeprom_mode_type_t;

/**
 * \name �жϴ�����λ����
 * \anchor grp_amdr_eeprom_int
 * @{
 */

typedef uint32_t amdr_eeprom_int_t;
#define AMDR_EEPROM_INT_NONE               0X00   /**< \brief ���ж�  */
#define AMDR_EEPROM_INT_RW_DONE            0X01   /**< \brief ��/д���������ж�ʹ��λ  */
#define AMDR_EEPROM_INT_PROG_DONE          0X02   /**< \brief ��̲���������ж�ʹ��λ   */

/** @} */

/**
 * \brief EEPROM �����ж�
 *
 * \param[in] p_dev        : EEPROM�豸ʵ��
 *
 * \retval  AM_OK     : �������
 * \retval -AM_EINVAL : �������Ϸ�
 */
int amdr_eeprom_int_connect (amdr_eeprom_dev_t *p_dev);

/**
 * \brief EEPROM ��װ�ص�����
 *
 * \param[in] p_dev          : EEPROM�豸ʵ��
 * \param[in] inttype        : �ж�����
 * \param[in] pfn_callback   : �ص�����
 * \param[in] p_arg          : ����
 *
 * \retval  AM_OK     : �������
 * \retval -AM_EINVAL : �������Ϸ�
 */
int amdr_eeprom_install_callback (amdr_eeprom_dev_t   *p_dev,
                                  amdr_eeprom_int_t    inttype,
                                  am_pfnvoid_t         pfn_callback,
                                  void                *p_arg);

/**
 * \brief EEPROM ɾ���ص�����
 *
 * \param[in] p_dev          : EEPROM�豸ʵ��
 * \param[in] inttype        : �ж�����
 *
 * \retval  AM_OK     : �������
 * \retval -AM_EINVAL : �������Ϸ�
 */
int amdr_eeprom_remove_callback (amdr_eeprom_dev_t   *p_dev,
                                 amdr_eeprom_int_t    inttype);
/**
 * \brief EEPROM д����
 *
 * \param[in] p_dev        : EEPROM�豸ʵ��
 * \param[in] page_offset  : ҳ���ݵ�ַ
 * \param[in] page_address : ҳ��ַ
 * \param[in] p_data       : Ҫд�������
 * \param[in] mode         : д���ģʽ
 * \param[in] count        : д������ݸ���
 *
 * \retval  AM_OK     : д�������
 * \retval -AM_EINVAL : �������Ϸ�
 * \retval -AM_EFAULT : ��ַ���� (�������)
 */
int amdr_eeprom_write (amdr_eeprom_dev_t       *p_dev,
                       uint16_t                 page_offset,
                       uint16_t                 page_address,
                       void                    *p_data,
                       amdr_eeprom_mode_type_t  mode,
                       uint32_t                 count);

/**
 * \brief EEPROM ������
 *
 * \param[in] p_dev        : EEPROM�豸ʵ��
 * \param[in] page_offset  : ҳ���ݵ�ַ
 * \param[in] page_address : ҳ��ַ
 * \param[in] p_data       : Ҫд�������
 * \param[in] mode         : д���ģʽ
 * \param[in] count        : д������ݸ���
 *
 * \retval  AM_OK     : д�������
 * \retval -AM_EINVAL : �������Ϸ�
 * \retval -AM_EFAULT : ��ַ���� (�������)
 */
int amdr_eeprom_read (amdr_eeprom_dev_t       *p_dev,
                      uint16_t                 page_offset,
                      uint16_t                 page_address,
                      void                    *p_data,
                      amdr_eeprom_mode_type_t  mode,
                      uint32_t                 count);

/**
 * \brief EEPROM ��ʼ��
 *
 * \param[in] p_dev     : EEPROM�豸ʵ��
 * \param[in] p_devinfo : EEPROM�豸��Ϣ
 *
 * \retval AM_OK : �����ɹ� 
 */
int amdr_eeprom_init(amdr_eeprom_dev_t           *p_dev,
                     const amdr_eeprom_devinfo_t *p_devinfo);

/**
 * \brief EEPROM ���ʼ��
 *
 * \param[in] p_dev : EEPROM�豸ʵ��
 *
 * \return �� 
 */
int amdr_eeprom_deinit (amdr_eeprom_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_EEPROM_H */

/* end of file */
