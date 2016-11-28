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
 * \brief EEPROM Ӳ�������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-15  anu, first implementation.
 * \endinternal
 */

#ifndef __AMHW_EEPROM_H
#define __AMHW_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 

/** 
 * \addtogroup amhw_if_eeprom
 * \copydoc amhw_eeprom.h
 * @{
 */


/**
 * \brief eeprom �Ĵ�����ṹ��
 */
typedef struct amhw_eeprom {
	__IO uint32_t cmd;			    /**< \brief ����Ĵ���   */
	__IO uint32_t addr;				/**< \brief ��ַ�Ĵ���  */
	__O  uint32_t wdata;			/**< \brief д���ݼĴ���  */
	__I  uint32_t rdata;			/**< \brief �����ݼĴ���  */
	__IO uint32_t wstate;			/**< \brief �ȴ�״̬�Ĵ���  */
	__IO uint32_t clkdiv;			/**< \brief ʱ�ӷ�Ƶ���Ĵ���  */
	__IO uint32_t pwrdwn;		    /**< \brief ����Ĵ��� */
	     uint32_t reserved0[975];   /**< \brief ����  */
	__O  uint32_t int_clr_enable;	/**< \brief �ж�ʹ������ */
	__O  uint32_t int_set_enable;   /**< \brief �ж�ʹ����λ  */
	__I  uint32_t int_status;		/**< \brief �ж�״̬ */
	__I  uint32_t int_enable;       /**< \brief �ж�ʹ�� */
	__O  uint32_t int_clr_status;   /**< \brief �ж�״̬����  */
	__O  uint32_t int_set_status;   /**< \brief �ж�״̬��λ  */
} amhw_eeprom_t;

/**
 * \name ����Ĵ���������Ķ���
 * \anchor grp_amhw_eeprom_cmd
 * @{
 */

typedef uint32_t amhw_eeprom_cmd_t;
#define AMHW_EEPROM_CMD_8BR             0X00   /**< \brief 8 λ��ȡ  */
#define AMHW_EEPROM_CMD_16BR            0X01   /**< \brief 16 λ��ȡ  */
#define AMHW_EEPROM_CMD_32BR            0X02   /**< \brief 32 λ��ȡ  */
#define AMHW_EEPROM_CMD_8BW             0X03   /**< \brief 8 λд��  */
#define AMHW_EEPROM_CMD_16BW            0X04   /**< \brief 16 λд��  */
#define AMHW_EEPROM_CMD_32BW            0X05   /**< \brief 32 λд��  */
#define AMHW_EEPROM_CMD_PROG            0X06   /**< \brief ����/���ҳ  */
#define AMHW_EEPROM_CMD_RSV             0X07   /**< \brief ����  */
#define AMHW_EEPROM_CMD_RDPREFETCH      0x08   /**< \brief ��ȡ����Ԥȡλ   */

/** @} */

/**
 * \brief ����EEPROM������
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] cmd         : ��������
 *
 * \return    ��
 */
am_static_inline 
void amhw_eeprom_cmd_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_cmd_t cmd)
{
    p_hw_eeprom->cmd = cmd;
}

/**
 * \brief ��ȡEEPROM������
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    ��������
 */
am_static_inline
amhw_eeprom_cmd_t amhw_eeprom_cmd_get (amhw_eeprom_t *p_hw_eeprom)
{
    return (p_hw_eeprom->cmd & 0x0f);
}


/**
 * \brief ����EEPROM�ĵ�ַ
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] addr        : ��ַ 12λ��ַ
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_addr_set (amhw_eeprom_t *p_hw_eeprom, int addr)
{
    p_hw_eeprom->addr = (addr & 0x0FFF);
}

/**
 * \brief ����EEPROM�ĵ�ַ
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    12λ��ַ
 */
am_static_inline
amhw_eeprom_cmd_t amhw_eeprom_addr_get (amhw_eeprom_t *p_hw_eeprom)
{
    return (p_hw_eeprom->addr & 0x0FFF);
}

/**
 * \brief ����EEPROM��д����
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] data        : ����
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_wdata_set (amhw_eeprom_t *p_hw_eeprom, uint32_t data)
{
    p_hw_eeprom->wdata = data;
}

/**
 * \brief ��ȡEEPROM�Ķ�����
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
uint32_t amhw_eeprom_rdata_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->rdata;
}

/**
 * \name �ȴ�״̬�Ĵ�����λ����
 * \anchor grp_amhw_eeprom_phase
 * @{
 */

typedef uint32_t amhw_eeprom_phase_t;
#define AMHW_EEPROM_PHASE3          (0XFFUL << 0)   /**< \brief �ȴ�״̬ 3 Ҫ���ṩ���� 15ns ��ʱ��   */
#define AMHW_EEPROM_PHASE2          (0XFFUL << 8)   /**< \brief �ȴ�״̬ 2 Ҫ���ṩ���� 55ns ��ʱ��   */
#define AMHW_EEPROM_PHASE1          (0XFFUL << 16)  /**< \brief �ȴ�״̬ 1 Ҫ���ṩ���� 35ns ��ʱ��   */

/** @} */

/**
 * \brief ����EEPROM�ĵȴ�״̬
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] kind        : �ȴ�״̬����
 * \param[in] val         : �ȴ�ʱ��
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_phase_set (amhw_eeprom_t       *p_hw_eeprom,
                            amhw_eeprom_phase_t  kind,
                            uint32_t             val)
{
    p_hw_eeprom->wstate &= ~kind;
    p_hw_eeprom->wstate |= (val & kind);
}

/**
 * \brief ��ȡEEPROM�ĵȴ�״̬
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    �ȴ�״̬
 */
am_static_inline
uint32_t amhw_eeprom_phase_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->wstate;
}

/**
 * \brief ����EEPROM�ķ�Ƶֵ
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] div         : ��Ƶ��
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_clkdiv_set (amhw_eeprom_t       *p_hw_eeprom,
                             uint16_t             div)
{
    p_hw_eeprom->clkdiv &= ~0xffff;
    p_hw_eeprom->clkdiv |= div;
}

/**
 * \brief ��ȡEEPROM�ķ�Ƶֵ
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    ��Ƶֵ
 */
am_static_inline
uint16_t amhw_eeprom_clkdiv_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->clkdiv;
}

/**
 * \brief ����EEPROM�ĵ���λ  Ϊ����ģʽ
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_pwrdwn_set (amhw_eeprom_t *p_hw_eeprom)
{
    p_hw_eeprom->pwrdwn |= 0x01;
}

/**
 * \brief ���EEPROM��Ϊ����λ Ϊ�ǵ���ģʽ
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_pwrdwn_clr (amhw_eeprom_t *p_hw_eeprom)
{
    p_hw_eeprom->pwrdwn = 0;
}

/**
 * \brief ��ȡEEPROM�ĵ���ģʽ״̬
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \retval    0 ��Ϊ�ǵ���ģʽ
 * \retval    1 : Ϊ����ģʽ
 */
am_static_inline
uint32_t amhw_eeprom_pwrdwn_get (amhw_eeprom_t *p_hw_eeprom)
{
    return (p_hw_eeprom->pwrdwn & 0x01);
}

/**
 * \name �жϴ�����λ����
 * \anchor grp_amhw_eeprom_int
 * @{
 */

typedef uint32_t amhw_eeprom_int_t;
#define AMHW_EEPROM_INT_NONE               0             /**< \brief ���ж�  */
#define AMHW_EEPROM_INT_RW_DONE            (1UL << 26)   /**< \brief ��/д���������ж�ʹ��λ  */
#define AMHW_EEPROM_INT_PROG_DONE          (1UL << 28)   /**< \brief ��̲���������ж�ʹ��λ   */

/** @} */

/**
 * \brief ����EEPROM���ж�ʹ��
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] type        : �ж�����
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_inten_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_int_t type)
{
    p_hw_eeprom->int_set_enable = type;
}

/**
 * \brief ����EEPROM���ж�ʧ��
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] type        : �ж�����
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_intdis_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_int_t type)
{
    p_hw_eeprom->int_clr_enable = type;
}

/**
 * \brief ��ȡEEPROM���ж�ʹ��
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
amhw_eeprom_int_t amhw_eeprom_int_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->int_enable;
}

/**
 * \brief ����EEPROM���ж�״̬ʹ��
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] type        : �ж�����
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_staten_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_int_t type)
{
    p_hw_eeprom->int_set_status = type;
}

/**
 * \brief ����EEPROM���ж�״̬ʧ��
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 * \param[in] type        : �ж�����
 *
 * \return    ��
 */
am_static_inline
void amhw_eeprom_statdis_set (amhw_eeprom_t *p_hw_eeprom, amhw_eeprom_int_t type)
{
    p_hw_eeprom->int_clr_status = type;
}

/**
 * \brief ��ȡEEPROM���ж�״̬
 *
 * \param[in] p_hw_eeprom : ָ��EEPROM�Ĵ������ָ��
 *
 * \return    ��
 */
am_static_inline
amhw_eeprom_int_t amhw_eeprom_stat_get (amhw_eeprom_t *p_hw_eeprom)
{
    return p_hw_eeprom->int_status;
}

/**
 * @} amhw_if_eeprom
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_EEPROM_H */

/* end of file */
