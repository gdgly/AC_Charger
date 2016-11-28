/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief EMCӲ�������ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-12  cod, first implementation.
 * \endinternal
 */

#ifndef __AMHW_EMC_H
#define __AMHW_EMC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"

/**
 * \addtogroup amhw_if_emc
 * \copydoc amhw_emc.h
 * @{
 */

/**
 * \name EMCƬ��洢����ַ
 * @{
 */

/** \brief ��̬�洢��Ƭѡ0��ַ����Χ0x80000000��0x83FFFFFF,ʹ�ܴ洢ת��ģʽ�������ɴ�256MB */
#define AMHW_EMC_STATICMEM_ADDR0  0x80000000UL

/** \brief ��̬�洢��Ƭѡ1��ַ����Χ0x90000000��0x93FFFFFF,ʹ�ܴ洢ת��ģʽ�������ɴ�128MB */
#define AMHW_EMC_STATICMEM_ADDR1  0x90000000UL

/** \brief ��̬�洢��Ƭѡ2��ַ����Χ0x9800 0000��0x9BFF FFFF    */
#define AMHW_EMC_STATICMEM_ADDR2  0x98000000UL

/** \brief ��̬�洢��Ƭѡ3��ַ����Χ0x9C00 0000��0x9FFF FFFF    */
#define AMHW_EMC_STATICMEM_ADDR3  0x9C000000UL

/** \brief ��̬�洢��Ƭѡ0��ַ����Χ0xA000 0000��0xAFFF FFFF    */
#define AMHW_EMC_DYNAMICMEM_ADDR0  0xA0000000UL

/** \brief ��̬�洢��Ƭѡ1��ַ����Χ0xB000 0000��0xBFFF FFFF    */
#define AMHW_EMC_DYNAMICMEM_ADDR1  0xB0000000UL

/** \brief ��̬�洢��Ƭѡ2��ַ����Χ0xC000 0000��0xBFFF FFFF    */
#define AMHW_EMC_DYNAMICMEM_ADDR2  0xC0000000UL

/** \brief ��̬�洢��Ƭѡ3��ַ����Χ0xD000 0000��0xDFFF FFFF    */
#define AMHW_EMC_DYNAMICMEM_ADDR3  0xD0000000UL
/** @} */

/**
 * \name EMC ��С��ģʽ
 * @{
 */
#define AMHW_EMC_LITTLE_ENDIAN   0    /**< \brief EMCС��ģʽ                         */
#define AMHW_EMC_BIG_ENDIAN      1    /**< \brief EMC���ģʽ                          */
/** @} */

/**
 * \brief EMC��̬�洢�����üĴ�����RAS & CAS��ʱ�Ĵ�����
 */
typedef struct amhw_emc_dynamics {
    __IO uint32_t config;          /**< \brief ��̬�洢�����üĴ���                           */
    __IO uint32_t rascas;          /**< \brief ��̬�洢��RAS & CAS��ʱ�Ĵ���   */
         uint32_t reserved[6];     /**< \brief ����                                                                   */
} amhw_emc_dynamics_t;

/**
 * \brief EMC��̬�洢���Ĵ�����
 */
typedef struct amhw_emc_statics {
    __IO uint32_t config;       /**< \brief ��̬�洢�����üĴ���                                */
    __IO uint32_t waitwen;      /**< \brief ��̬�洢��дʹ���ӳټĴ���                 */
    __IO uint32_t waitoen;      /**< \brief ��̬�洢�����ʹ���ӳټĴ���             */
    __IO uint32_t waitrd;       /**< \brief ��̬�洢����ȡ�ӳټĴ���                       */
    __IO uint32_t waitpage;     /**< \brief ��̬�洢��ҳ��ģʽ��ȡ�ӳټĴ���  */
    __IO uint32_t waitwr;       /**< \brief ��̬�洢��д���ӳټĴ���                        */
    __IO uint32_t waitturn;     /**< \brief ��̬�洢����ת�ӳټĴ���                        */
         uint32_t reserved;     /**< \brief ����                                                                           */
} amhw_emc_statics_t;

/**
 * \brief EMC�������Ĵ�����ṹ��
 */
typedef struct amhw_emc {
    __IO uint32_t control;             /**< \brief ���ƼĴ���              */
    __I  uint32_t status;              /**< \brief ״̬�Ĵ���              */
    __IO uint32_t config;              /**< \brief ���üĴ���              */
         uint32_t reserved0[5];        /**< \brief ����                             */
    __IO uint32_t dynamiccontrol;      /**< \brief ��̬�洢�����ƼĴ���                                              */
    __IO uint32_t dynamicrefresh;      /**< \brief ��̬�洢��ˢ�¶�ʱ���Ĵ���                               */
    __IO uint32_t dynamicreadconfig;   /**< \brief ��̬�洢����ȡ���üĴ���                                    */
         uint32_t reserved1;           /**< \brief ����                                                                                      */
    __IO uint32_t dynamictrp;          /**< \brief ��̬�洢��Ԥ����������ڼĴ���                     */
    __IO uint32_t dynamictras;         /**< \brief ��̬�洢����Ч��Ԥ����������ڼĴ���      */
    __IO uint32_t dynamictsrex;        /**< \brief ��̬�洢����ˢ���˳�ʱ��Ĵ���                     */
    __IO uint32_t dynamictapr;         /**< \brief ��̬�洢����������������Чʱ��Ĵ���                  */
    __IO uint32_t dynamictdal;         /**< \brief ��̬�洢��������������Ч����ʱ��Ĵ���                  */
    __IO uint32_t dynamictwr;          /**< \brief ��̬�洢��д��ָ�ʱ��Ĵ���                                           */
    __IO uint32_t dynamictrc;          /**< \brief ��̬�洢����Ч����Ч�������ڼĴ���                            */
    __IO uint32_t dynamictrfc;         /**< \brief ��̬�洢���Զ�ˢ�����ڼĴ���                                           */
    __IO uint32_t dynamictxsr;         /**< \brief ��̬�洢���˳���ˢ�¼Ĵ���                                                */
    __IO uint32_t dynamictrrd;         /**< \brief ��̬�洢����Ч��A����Ч��B��ʱ��Ĵ���                  */
    __IO uint32_t dynamictmrd;         /**< \brief ��̬�洢��װ��ģʽ�Ĵ�������Ч����ʱ��Ĵ���    */
         uint32_t reserved2[9];        /**< \brief ����                                                                        */
    __IO uint32_t staticextendedwait;  /**< \brief ��̬�洢���ӳ��ȴ��Ĵ���                      */
         uint32_t reserved3[31];       /**< \brief ����                                                                        */

    amhw_emc_dynamics_t dynamic_mem[4]; /**< \brief EMC��̬�洢�����üĴ�����RAS & CAS��ʱ�Ĵ���0~3 */

    uint32_t reserved7[32];             /**< \brief ����                                                                        */

    amhw_emc_statics_t  static_mem[4];  /**< \brief ��̬�洢���Ĵ�����0~3                 */

} amhw_emc_t;

/**
 * \brief ʹ��EMC������
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \return    ��
 * \note      ��λ�Զ�ʹ��
 */
am_static_inline
void amhw_emc_enable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control |= (1 << 0);
}

/**
 * \brief ����EMC������
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_emc_disable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control &= ~(1 << 0);
}

/**
 * \name EMC��λ�洢��ӳ��
 * @{
 */
#define AMHW_EMC_MIRROR_ENABLE  (1 << 1)  /**< \brief ��λ�洢��ӳ��ʹ��   */
#define AMHW_EMC_MIRROR_DISABLE (0)       /**< \brief ��λ�洢��ӳ��ʧ��   */
/** @} */

/**
 * \brief ʹ��EMC��λ�洢��ӳ��(��λĬ��״̬)
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \return    ��
 * \note      ��λ�Զ�ʹ��
 */
am_static_inline
void amhw_emc_mirror_enable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control |= (1 << 1);
}

/**
 * \brief ����EMC��λ�洢��ӳ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_emc_mirror_disable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control &= ~(1 << 1);
}

/**
 * \brief ʹ�ܵ͹���ģʽ
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_emc_lowpower_mode_enable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control |= (1 << 2);
}

/**
 * \brief ���ܵ͹���ģʽ(����ģʽ)
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \return    ��
 * \note      ��λ�����ģʽ
 */
am_static_inline
void amhw_emc_lowpower_mode_disable (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->control |= (1 << 2);
}

/**
 * \name EMC״̬�Ĵ���״̬λ����
 * @{
 */
#define AMHW_EMC_STAT_BUSY   AM_BIT(0)  /**< \brief EMC BUSYλ        */
#define AMHW_EMC_STAT_S      AM_BIT(1)  /**< \brief д����λ               */
#define AMHW_EMC_STAT_SA     AM_BIT(2)  /**< \brief EMC����ģʽλ   */
#define AMHW_EMC_STAT_MASK   (0x07)     /**< \brief EMC״̬λ����   */
/** @} */

/**
 * \brief ָ��״̬λ�Ƿ���λ
 *
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] flag     : ָ��״̬λ, ֵΪAMHW_EMC_STAT_*(��#AMHW_EMC_STAT_BUSY)
 * \retval    TURE     : ָ��λ��λ
 * \retval    FALSE    : ָ��λΪ0
 */
am_static_inline
bool_t amhw_emc_status_get (amhw_emc_t *p_hw_emc, uint8_t flag)
{
    return (bool_t)(p_hw_emc->status & (flag & 0x7));
}

/**
 * \brief EMC����ΪС��ģʽ
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \return    ��
 * \note ����ԸüĴ������޸�Ӧ��ϵͳ��ʼ���ڼ䣬���ڲ����ڵ�����δ�������ʱ����
 */
am_static_inline
void amhw_emc_endian_little (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->config &= ~(1 << 0);
}

/**
 * \brief EMC����Ϊ���ģʽ
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \return    ��
 * \note ����ԸüĴ������޸�Ӧ��ϵͳ��ʼ���ڼ䣬���ڲ����ڵ�����δ�������ʱ����
 */
am_static_inline
void amhw_emc_endian_big (amhw_emc_t *p_hw_emc)
{
    p_hw_emc->config = (1 << 0);
}

/**
 * \name EMC ��̬�洢��������Ϣ
 * \anchor grp_amhw_emc_dynamic_ctrl_flag
 * @{
 */
/** \brief �����豸��ʱ��ʹ�ܱ���ֹ(�ϵ縴λֵ)  */
#define AMHW_EMC_DYNCTRL_CE_SAVEPWR     (0UL)
/** \brief ����ʱ��ʹ�ܳ����ܵ��ߵ�ƽ������        */
#define AMHW_EMC_DYNCTRL_CE_ALLCLK_HI   (1 << 0)

/** \brief CLKOUTֹͣ                                               */
#define AMHW_EMC_DYNCTRL_CS_CLKOUT_STOP (0UL)
/** \brief CLKOUT�������У��ϵ縴λֵ��  */
#define AMHW_EMC_DYNCTRL_CS_CLKOUT_CONN (1 << 1)

#define AMHW_EMC_DYNCTRL_SR_NORMALMODE  (0UL)     /**< \brief ����ģʽ       */
#define AMHW_EMC_DYNCTRL_SR_SELFREFRESH (1 << 2)  /**< \brief ��ˢ��ģʽ���ϵ縴λֵ�� */

#define AMHW_EMC_DYNCTRL_MMC_CLKOUT_ENABLE   (0UL)     /**< \brief CLKOUTʹ��    */
#define AMHW_EMC_DYNCTRL_MMC_CLKOUT_DISABLE  (1 << 5)  /**< \brief CLKOUT����    */

#define AMHW_EMC_DYNCTRL_SDRAM_NORMAL (0 << 7) /**< \brief SDRAM NORMAL��������ϵ縴λֵ��*/
#define AMHW_EMC_DYNCTRL_SDRAM_MODE   (1 << 7) /**< \brief SDRAM MODE��������   */
#define AMHW_EMC_DYNCTRL_SDRAM_PALL   (2 << 7) /**< \brief SDRAM PALL��������   */
#define AMHW_EMC_DYNCTRL_SDRAM_NOP    (3 << 7) /**< \brief SDRAM NOP��������   */

#define AMHW_EMC_DYNCTRL_DP_NORMAL      (0UL)      /**< \brief �����������ϵ縴λֵ�� */
#define AMHW_EMC_DYNCTRL_DP_DEEPSLEEP   (1 << 13)  /**< \brief �������˯��ģʽ                 */

/** @} */

/**
 * \brief  EMC��̬�洢��ʱ�ӿ���
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ�ӿ���ֵ��ֵΪ
 *                       #AMHW_EMC_DYNCTRL_CE_SAVEPWR  �������豸��ʱ��ʹ�ܱ���ֹ, ��
 *                       #AMHW_EMC_DYNCTRL_CE_ALLCLK_HI:����ʱ��ʹ�ܳ����ܵ��ߵ�ƽ������
 *
 * \return    ��
 */
am_static_inline
void amhw_emc_dynctrl_ce_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 0);
    p_hw_emc->dynamiccontrol |= val & 0x01;
}

/**
 * \brief  EMC��̬�洢��ʱ��CLKOUT����
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ����ֵ��ֵΪ
 *                       #AMHW_EMC_DYNCTRL_CS_CLKOUT_STOP: CLKOUTֹͣ, ��
 *                       #AMHW_EMC_DYNCTRL_CS_CLKOUT_CONN: CLKOUT��������
 *
 * \return    ��
 */
am_static_inline
void amhw_emc_dynctrl_cs_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 1);
    p_hw_emc->dynamiccontrol |= val & (0x01 << 1);
}

/**
 * \brief  EMC��̬�洢����ˢ��ģʽ����
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ��ˢ������ֵ��ֵΪ
 *                       #AMHW_EMC_DYNCTRL_SR_NORMALMODE: ����ģʽ, ��
 *                       #AMHW_EMC_DYNCTRL_SR_SELFREFRESH: ��ˢ��ģʽ
 *
 * \return    ��
 */
am_static_inline
void amhw_emc_dynctrl_sr_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 2);
    p_hw_emc->dynamiccontrol |= val & (0x01 << 2);
}

/**
 * \brief  ����EMC��̬�洢��CLKOUT ʹ�ܻ�ʧ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʹ��/ʧ�ܣ�ֵΪ��
 *                       (#AMHW_EMC_DYNCTRL_MMC_CLKOUT_ENABLE)ʹ�ܻ�
 *                       (#AMHW_EMC_DYNCTRL_MMC_CLKOUT_DISABLE)ʧ��
 *
 * \return    ��
 */
am_static_inline
void amhw_emc_dynctrl_mmc_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 5);
    p_hw_emc->dynamiccontrol |= val & (0x01 << 5);
}

/**
 * \brief ����EMC SDRAM����
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] cmd      : SDRAM���ֵΪAMHW_EMC_DYNCTRL_SDRAM_*
 *                       ��(#AMHW_EMC_DYNCTRL_SDRAM_NORMAL)
 * \return    ��
 */
am_static_inline
void amhw_emc_dynctrl_sdram_init (amhw_emc_t *p_hw_emc, uint32_t cmd)
{
    p_hw_emc->dynamiccontrol &= ~(0x03 << 7);
    p_hw_emc->dynamiccontrol |= (cmd & (0x03 << 7));
}

/**
 * \brief ��̬�洢�����˯��ģʽ����
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ����ģʽ�����˯��ģʽ��ֵΪ
 *                       #AMHW_EMC_DYNCTRL_DP_NORMAL:����ģʽ
 *                       #AMHW_EMC_DYNCTRL_DP_DEEPSLEEP:���˯��
 * \return    ��
 */
am_static_inline
void amhw_emc_dynctrl_dp_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamiccontrol &= ~(0x01 << 13);
    p_hw_emc->dynamiccontrol |= (val & (0x01 << 13));
}

/**
 * \brief ����EMC SDRAMˢ������֮��16��CCLK�ı���
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : 16��CCLK�ı���ֵ��ֵΪ0~0x3FF.ֵΪ0ʱˢ�½���
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_refresh_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamicrefresh = val & 0x3FF;
}

/**
 * \name EMC ��̬�洢����ʱ����
 * @{
 */
/** \brief ʱ�������ʱ���ԣ�ʹ��CLKOUT������δ��ʱ��ʱ�������ʱ��,�ϵ縴λֵ       */
#define AMHW_EMC_DYNAMIC_RD_0  (0UL)
/** \brief ������ʱ���ԣ�ʹ��EMCCLKDELAY��������ʱ��ʱ�����δ��ʱ  */
#define AMHW_EMC_DYNAMIC_RD_1  (1UL)
/** \brief ������ʱ������һ��ʱ�����ڣ�ʹ��EMCCLKDELAY��������ʱ��ʱ�����δ��ʱ��  */
#define AMHW_EMC_DYNAMIC_RD_2  (2UL)
/** \brief ������ʱ���������ʱ�����ڣ�ʹ��EMCCLKDELAY��������ʱ��ʱ�����δ��ʱ��  */
#define AMHW_EMC_DYNAMIC_RD_3  (3UL)
/** @} */

/**
 * \brief  ����EMC��̬�洢���Ķ�ȡ����
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ��ȡ���ԣ�ֵΪ0~3,���õ��ú���(#AMHW_EMC_DYNAMIC_RD_0)
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_rd_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamicreadconfig = val & 0x03;
}

/**
 * \brief ����EMC��̬�洢��Ԥ�����������
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~15. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_trp_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictrp = val & 0x0F;
}

/**
 * \brief ����EMC��̬�洢����Ч��Ԥ�����������
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~15. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_tras_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictras = val & 0x0F;
}

/**
 * \brief ����EMC��̬�洢����ˢ���˳�ʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~15. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_tsrex_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictsrex = val & 0x0F;
}

/**
 * \brief ����EMC��̬�洢����������������Чʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~15. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_tapr_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictapr = val & 0x0F;
}

/**
 * \brief ����EMC��̬�洢��������������Ч����ʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~15. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_tdal_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictdal = val & 0x0F;
}

/**
 * \brief ����EMC��̬�洢��д��ָ�ʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~15. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_twr_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictwr = val & 0x0F;
}

/**
 * \brief ����EMC��̬�洢����Ч����Ч��������
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~31. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_trc_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictrc = val & 0x1F;
}

/**
 * \brief ����EMC��̬�洢����ˢ������
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~31. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_trfc_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictrfc = val & 0x1F;
}

/**
 * \brief ����EMC��̬�洢���˳���ˢ������Ч����ʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~31. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_txsr_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictxsr = val & 0x1F;
}

/**
 * \brief ����EMC��̬�洢����Ч��A����Ч��B��ʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~15. ʵ��ʱ������Ϊval+1
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_trrd_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictrrd = val & 0x0F;
}

/**
 * \brief ����EMC��̬�洢��װ��ģʽ�Ĵ�������Ч����ʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~15. val+1��ʱ������
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_tmrd_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->dynamictmrd = val & 0x0F;
}

/**
 * \brief ����EMC��̬�洢���ӳ��ȴ�ʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] val      : ʱ����������ֵΪ0~0x3FF. ʵ��ʱ������Ϊ(val+1)*16��
 * \return    ��
 */
am_static_inline
void amhw_emc_externdedwait_set (amhw_emc_t *p_hw_emc, uint32_t val)
{
    p_hw_emc->staticextendedwait = val & 0x3FF;
}

/**
 * \name EMC ��̬�洢��������Ϣ
 * \anchor grp_amhw_emc_dynamic_cfg_flag
 * @{
 */

#define AMHW_EMC_DYNCFG_MD_SDRAM          (0 << 3)  /**< \brief SDRAM���ϵ縴λֵ��  */
#define AMHW_EMC_DYNCFG_MD_LOWPWR_SDRAM   (1 << 3)  /**< \brief �͹���SDRAM        */

/** \brief ��ַӳ������,����λ��[11:7]  */
#define AMHW_EMC_DYNCFG_ADDRMAP_P1(val)   (((val) & 0x1F) << 7)
/** \brief ��ַӳ������,����λ��[12],��ַӳ�䷽ʽ (������)��(������) */
#define AMHW_EMC_DYNCFG_ADDRMAP_P2(val)   (((val) & 0x01) << 12)
/** \brief ��ַӳ������,����λ��[14],16bits�ⲿ����valΪ0,32bitsʱvalΪ1  */
#define AMHW_EMC_DYNCFG_ADDRMAP_P3(val)   (((val) & 0x01) << 14)

#define AMHW_EMC_DYNCFG_BUFFER_ENABLE     (1 << 19) /**< \brief ����ʹ��    */
#define AMHW_EMC_DYNCFG_BUFFER_DISABLE    (0 << 19) /**< \brief �������    */

#define AMHW_EMC_DYNCFG_WR_PROTECTED      (1 << 20) /**< \brief д����         */
#define AMHW_EMC_DYNCFG_WR_UNPROTECTED    (0 << 20) /**< \brief дδ����    */

/** @} */

/**
 * \brief ����EMC��̬�洢���ڴ��豸����
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] num      : ���üĴ������,ֵΪ0~3
 * \param[in] val      : �ڴ��豸,ֵΪ(#AMHW_EMC_DYNCFG_MD_SDRAM)��
 *                                   (#AMHW_EMC_DYNCFG_MD_LOWPWR_SDRAM)
 *
 * \return    ��
 */
am_static_inline
void amhw_emc_dynconfig_md_set (amhw_emc_t *p_hw_emc,
                                uint8_t     num,
                                uint32_t    val)
{
    p_hw_emc->dynamic_mem[num].config &= ~(1 << 3);
    p_hw_emc->dynamic_mem[num].config |= val;
}

/**
 * \name EMC ��̬�洢����ַӳ��������Ϣ
 * @{
 */
#define AMHW_EMC_ADDRWIDTH_16   (16)    /**< \brief ��ַ���߿��16bits    */
#define AMHW_EMC_ADDRWIDTH_32   (32)    /**< \brief ��ַ���߿��32bits    */

#define AMHW_EMC_DATAWIDTH_8    (8)     /**< \brief �������߿��8bits     */
#define AMHW_EMC_DATAWIDTH_16   (16)    /**< \brief �������߿��16bits    */
#define AMHW_EMC_DATAWIDTH_32   (32)    /**< \brief �������߿��32bits    */

#define AMHW_EMC_AM_ROW_BANK_COL   (0)  /**< \brief ��ַӳ�䣺��-��-��   */
#define AMHW_EMC_AM_BANK_ROW_COL   (1)  /**< \brief ��ַӳ�䣺��-��-��   */

#define AMHW_EMC_DYNCHIP_SIZE_16MB   (16)  /**< \brief ��̬�洢����С16MB    */
#define AMHW_EMC_DYNCHIP_SIZE_64MB   (64)  /**< \brief ��̬�洢����С64MB    */
#define AMHW_EMC_DYNCHIP_SIZE_128MB  (128) /**< \brief ��̬�洢����С128MB   */
#define AMHW_EMC_DYNCHIP_SIZE_256MB  (256) /**< \brief ��̬�洢����С256MB   */
#define AMHW_EMC_DYNCHIP_SIZE_512MB  (512) /**< \brief ��̬�洢����С512MB   */

/** @} */

/**
 * \brief ����EMC��̬�洢����ַӳ������
 * \param[in] p_hw_emc   : ָ��EMC�������Ĵ������ָ��
 * \param[in] index      : Ƭѡ��,ֵΪ0~3
 * \param[in] addr_width : �ⲿ���ߵ�ַ���,ֵΪ16/32,
 *                         ������Ϊ(#AMHW_EMC_ADDRWIDTH_16)��
 *                                 (#AMHW_EMC_ADDRWIDTH_32)
 * \param[in] data_width : �ⲿ�������߿��,ֵΪ8/16/32,
 *                         ������Ϊ(#AMHW_EMC_DATAWIDTH_8)��
 *                                 (#AMHW_EMC_DATAWIDTH_16)��
 *                                 (#AMHW_EMC_DATAWIDTH_32)
 * \param[in] addrmap    : ��ַӳ�䷽ʽ,ֵΪ(#AMHW_EMC_AM_ROW_BANK_COL)��
 *                                         (#AMHW_EMC_AM_BANK_ROW_COL)
 * \param[in] chipsize   : ��̬�洢���洢��С(MB),ֵΪ 16/64/128/256/512,
 *                         ������ֵΪAMHW_EMC_DYNCHIP_SIZE_*(��#AMHW_EMC_DYNCHIP_SIZE_16MB)
 *
 * \return    ��
 */
void amhw_emc_dynconfig_am_set(amhw_emc_t *p_hw_emc,
                               uint8_t     index,
                               uint8_t     addr_width,
                               uint8_t     data_width,
                               uint8_t     addrmap,
                               uint8_t     chipsize);

/**
 * \brief ����EMC��̬�洢�� ����ʹ/����
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] index    : Ƭѡ��,ֵΪ0~3
 * \param[in] val      : ʹ��#AMHW_EMC_DYNCFG_BUFFER_ENABLE ��
 *                       ����#AMHW_EMC_DYNCFG_BUFFER_DISABLE
 * \return    ��
 */
am_static_inline
void amhw_emc_dynconfig_buffer_set (amhw_emc_t *p_hw_emc,
                                    uint8_t     index,
                                    uint32_t    val)
{
    p_hw_emc->dynamic_mem[index].config &= ~AMHW_EMC_DYNCFG_BUFFER_ENABLE;
    p_hw_emc->dynamic_mem[index].config |= val;
}

/**
 * \brief ����EMC��̬�洢�� д����ʹ/����
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] index    : Ƭѡ��,ֵΪ0~3
 * \param[in] val      : д����,ֵΪ#AMHW_EMC_DYNCFG_WR_PROTECTED ��
 *                       δд����, ֵΪ#AMHW_EMC_DYNCFG_WR_UNPROTECTED
 * \return    ��
 */
am_static_inline
void amhw_emc_dynconfig_protect_set (amhw_emc_t *p_hw_emc,
                                     uint8_t     index,
                                     uint32_t    val)
{
    p_hw_emc->dynamic_mem[index].config &= ~AMHW_EMC_DYNCFG_WR_UNPROTECTED;
    p_hw_emc->dynamic_mem[index].config |= val;
}

/**
 * \brief ����EMC��̬�洢��RAS��CAS��ʱ
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] num      : ���üĴ������,ֵΪ0~3
 * \param[in] ras      : RAS��CCLK��������ֵΪ1~3.���ϵ縴λΪ3��CCLK���ڣ�
 * \param[in] cas      : CAS��CCLK��������ֵΪ1~3.���ϵ縴λΪ3��CCLK���ڣ�
 * \return    ��
 */
am_static_inline
void amhw_emc_dynamic_rascas_set (amhw_emc_t *p_hw_emc,
                                  uint8_t     num,
                                  uint32_t    ras,
                                  uint32_t    cas)
{
    p_hw_emc->dynamic_mem[num].rascas = (ras & 0x03) | ((cas & 0x03) << 8);
}

/**
 * \name EMC ��̬�洢��������Ϣ
 * \anchor grp_amhw_emc_static_cfg_flag
 * @{
 */
#define AMHW_EMC_STATICCFG_MW_8BITS   AM_SBF(0, 0)  /**< \brief �洢�����8λ  */
#define AMHW_EMC_STATICCFG_MW_16BITS  AM_SBF(1, 0)  /**< \brief �洢�����16λ  */
#define AMHW_EMC_STATICCFG_MW_32BITS  AM_SBF(2, 0)  /**< \brief �洢�����32λ  */

#define AMHW_EMC_STATICCFG_PM_ENABLE  AM_SBF(1, 3)  /**< \brief �첽ҳ��ģʽʹ��  */
#define AMHW_EMC_STATICCFG_PM_DISABLE AM_SBF(0, 3)  /**< \brief ���ܣ��ϵ縴λֵ�� */

#define AMHW_EMC_STATICCFG_PC_ACTIVE_LO  AM_SBF(0, 6) /**< \brief �͵�ƽƬѡ��Ч  */
#define AMHW_EMC_STATICCFG_PC_ACTIVE_HI  AM_SBF(1, 6) /**< \brief �ߵ�ƽƬѡ��Ч  */

#define AMHW_EMC_STATICCFG_PB_RDHI  AM_SBF(0, 7) /**< \brief ��ȡBLS[3:0]�е�����λΪ�ߵ�ƽ  */
#define AMHW_EMC_STATICCFG_PB_RDLO  AM_SBF(1, 7) /**< \brief ��ȡBLS[3:0]�е�����λΪ�͵�ƽ  */

#define AMHW_EMC_STATICCFG_EW_DISABLE  AM_SBF(0, 8)  /**< \brief �ӳ��ȴ�����  */
#define AMHW_EMC_STATICCFG_EW_ENABLE   AM_SBF(1, 8)  /**< \brief �ӳ��ȴ�ʹ��  */

#define AMHW_EMC_STATICCFG_BUFFER_DISABLE  AM_SBF(0, 19)  /**< \brief д�������  */
#define AMHW_EMC_STATICCFG_BUFFER_ENABLE   AM_SBF(1, 19)  /**< \brief д�����ʹ��  */

#define AMHW_EMC_STATICCFG_WR_UNPROTECTED  AM_SBF(0, 20)  /**< \brief δд����  */
#define AMHW_EMC_STATICCFG_WR_PROTECTED    AM_SBF(1, 20)  /**< \brief д����       */

/** @} */

/**
 * \brief ����EMC��̬�洢��������Ϣ
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] index    : Ƭѡ��,ֵΪ0~3
 * \param[in] flag     : ������Ϣ,�μ�
 *                       \ref grp_amhw_emc_static_cfg_flag "Static Configuration Flag"
 * \return    ��
 */
am_static_inline
void amhw_emc_static_config_set (amhw_emc_t *p_hw_emc,
                                 uint8_t     index,
                                 uint32_t    flag)
{
    p_hw_emc->static_mem[index].config = flag;
}

/**
 * \brief ����EMC��̬�洢��дʹ����ʱʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] num      : ���üĴ������,ֵΪ0~3
 * \param[in] val      : ��ʱ��������ֵΪ0~15.��ʱ����Ϊ(val+1)��CCLK
 * \return    ��
 */
am_static_inline
void amhw_emc_static_waitwen_set (amhw_emc_t *p_hw_emc,
                                  uint8_t     num,
                                  uint32_t    val)
{
    p_hw_emc->static_mem[num].waitwen = val & 0xF;
}

/**
 * \brief ����EMC��̬�洢�����ʹ���ӳ�
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] num      : ���üĴ������,ֵΪ0~3
 * \param[in] val      : ��ʱ��������ֵΪ0~15,Ϊ0���ӳ�,����0,�ӳ�Ϊval*cclk.
 * \return    ��
 */
am_static_inline
void amhw_emc_static_waitoen_set (amhw_emc_t *p_hw_emc,
                                  uint8_t     num,
                                  uint32_t    val)
{
    p_hw_emc->static_mem[num].waitoen = val & 0xF;
}

/**
 * \brief ����EMC��̬�洢����Ƭѡ����ȡ���ӳ�
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] num      : ���üĴ������,ֵΪ0~3
 * \param[in] val      : ��ʱ��������ֵΪ0~0x1F
 * \return    ��
 * \note      valֵΪ0x1Fʱ��32����ȡCCLK���ڣ��ϵ縴λֵ��
 *            valֵΪ0~0x1Eʱ���ȴ�״̬ʱ��Ϊ(val+1)*cclk.
 */
am_static_inline
void amhw_emc_static_waitrd_set (amhw_emc_t *p_hw_emc,
                                 uint8_t     num,
                                 uint32_t    val)
{
    p_hw_emc->static_mem[num].waitrd = val & 0x1F;
}

/**
 * \brief ����EMC��̬�洢��ҳ��ģʽ��ȡ�ӳ�
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] num      : ���üĴ������,ֵΪ0~3
 * \param[in] val      : ��ʱ��������ֵΪ0~0x1F
 * \return    ��
 * \note      valֵΪ0x1Fʱ��32����ȡCCLK���ڣ��ϵ縴λֵ��
 *            valֵΪ0~0x1Eʱ���ȴ�״̬ʱ��Ϊ(val+1)*cclk.
 */
am_static_inline
void amhw_emc_static_waitpage_set (amhw_emc_t *p_hw_emc,
                                   uint8_t     num,
                                   uint32_t    val)
{
    p_hw_emc->static_mem[num].waitpage = val & 0x1F;
}

/**
 * \brief ����EMC��̬�洢��д���ӳ�
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] num      : ���üĴ������,ֵΪ0~3
 * \param[in] val      : ��ʱ��������ֵΪ0~0x1F
 * \return    ��
 * \note      valֵΪ0x1Fʱ��33����ȡCCLK���ڣ��ϵ縴λֵ��
 *            valֵΪ0~0x1Eʱ���ȴ�״̬ʱ��Ϊ(val+2)*cclk.
 */
am_static_inline
void amhw_emc_static_waitwr_set (amhw_emc_t *p_hw_emc,
                                 uint8_t     num,
                                 uint32_t    val)
{
    p_hw_emc->static_mem[num].waitwr = val & 0x1F;
}

/**
 * \brief ����EMC��̬�洢����ת�ӳ�ʱ��
 * \param[in] p_hw_emc : ָ��EMC�������Ĵ������ָ��
 * \param[in] num      : ���üĴ������,ֵΪ0~3
 * \param[in] val      : ��ʱ��������ֵΪ1~15.��ת�ӳ�Ϊ(val+1)*cclk.
 * \return    ��
 */
am_static_inline
void amhw_emc_static_waitturn_set (amhw_emc_t *p_hw_emc,
                                   uint8_t     num,
                                   uint32_t    val)
{
    p_hw_emc->static_mem[num].waitturn = val & 0xF;
}

/**
 * \brief ��̬�洢��ʱ����Ϣ
 */
typedef struct amdr_emc_dynamic_timeinfo {
    uint16_t refreshtime;   /**< \brief SDRAMˢ������֮��16��CCLK�ı���  */
    uint8_t  trp;           /**< \brief ��̬�洢��Ԥ�����������   */
    uint8_t  tras;          /**< \brief ��̬�洢����Ч��Ԥ�����������   */
    uint8_t  tsrex;         /**< \brief ��̬�洢����ˢ���˳�ʱ��  */
    uint8_t  tapr;          /**< \brief ��̬�洢����������������Чʱ��   */
    uint8_t  tdal;          /**< \brief ��̬�洢��������������Ч����ʱ�� */
    uint8_t  twr;           /**< \brief ��̬�洢��д��ָ�ʱ��   */
    uint8_t  trc;           /**< \brief ��̬�洢����Ч����Ч��������   */
    uint8_t  trfc;          /**< \brief ��̬�洢���Զ�ˢ������   */
    uint8_t  txsr;          /**< \brief ��̬�洢���˳���ˢ������Ч����ʱ��   */
    uint8_t  trrd;          /**< \brief ��̬�洢����Ч��A����Ч��B����ʱ   */
    uint8_t  tmrd;          /**< \brief ��̬�洢��װ��ģʽ�Ĵ�������Ч����ʱ��   */
} amhw_emc_dynamic_timeinfo_t;

/**
 * \brief ����EMC��̬�洢��ʱ����Ϣ
 * \param[in] p_hw_emc   : ָ��EMC�Ĵ������ָ��
 * \param[in] p_info     : ʱ����Ϣ��
 *                         �μ��ṹ��amhw_emc_dynamic_timeinfo_t
 *
 * \return    ��
 */
void amhw_emc_dynamic_time_set (amhw_emc_t                  *p_hw_emc,
                                amhw_emc_dynamic_timeinfo_t *p_info);

/**
 * \brief ��̬�洢���ӳ�ʱ����Ϣ
 */
typedef struct amdr_emc_static_timeinfo {
    uint8_t waitwen;       /**< \brief ��̬�洢��дʹ����ʱʱ��  */
    uint8_t waitoen;       /**< \brief ��̬�洢�����ʹ���ӳ�ʱ��  */
    uint8_t waitrd;        /**< \brief ��̬�洢����Ƭѡ����ȡ���ӳ�ʱ��  */
    uint8_t waitpage;      /**< \brief ��̬�洢��ҳ��ģʽ��ȡ�ӳ�ʱ��  */
    uint8_t waitwr;        /**< \brief ��̬�洢��д���ӳ�ʱ��  */
    uint8_t waitturn;      /**< \brief ��̬�洢����ת�ӳ�ʱ��  */
} amhw_emc_static_timeinfo_t;

/**
 * \brief EMC��̬�洢���ӳ�ʱ������
 * \param[in] p_hw_emc   : ָ��EMC�Ĵ������ָ��
 * \param[in] index      : Ƭѡ�ţ�ֵΪ0/1/2/3
 * \param[in] p_info     : �ӳ�ʱ����Ϣ��
 *                         �μ��ṹ��amhw_emc_static_timeinfo_t
 *
 * \return    ��
 */
void amhw_emc_static_time_set (amhw_emc_t                 *p_hw_emc,
                               uint8_t                     index,
                               amhw_emc_static_timeinfo_t *p_info);
/**
 * \name EMC�ӳٿ�����Ϣ
 * \anchor grp_amhw_emc_dlyctl_flag
 * @{
 */

/** \brief �����ӳ�ģʽ��EMC ����Ŀɱ���ӳ�ֵ,�ӳ�ʱ��ԼΪ(n+1)*250ps  */
#define AMHW_EMC_DLYCTL_CMDDLY(n)        ((uint32_t)(n&0x1F))
/** \brief �����������ݲ����ķ���ʱ�ӵĿɱ���ӳ�ֵ,�ӳ�ʱ��ԼΪ(n+1)*250ps  */
#define AMHW_EMC_DLYCTL_FBCLKDLY(n)      ((uint32_t)((n&0x1F)<<8))
/** \brief CLKOUT0 ����Ŀɱ���ӳ�ֵ,�ӳ�ʱ��ԼΪ(n+1)*250ps  */
#define AMHW_EMC_DLYCTL_CLKOUT0DLY(n)    ((uint32_t)((n&0x1F)<<16))
/** \brief CLKOUT1 ����Ŀɱ���ӳ�ֵ,�ӳ�ʱ��ԼΪ(n+1)*250ps  */
#define AMHW_EMC_DLYCTL_CLKOUT1DLY(n)    ((uint32_t)((n&0x1F)<<24))
/** @} */

/**
 * \brief ����EMC��̬�洢�����ʹ���ӳ�
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \param[in] flag        : �ӳٿ�����Ϣ���μ�
 *                          \ref grp_amhw_emc_dlyctl_flag "EMC Dlyctl Flag"
 * \return    ��
 */
am_static_inline
void amhw_emc_dlyctl_set (amhw_syscon_t *p_hw_syscon,
                          uint32_t       flag)
{
    p_hw_syscon->emcdlyctl = flag;
}

/**
 * \name EMCУ׼λ����
 * @{
 */
/** \brief ����Լ50MHz ���������ļ���  */
#define AMHW_EMC_CAL_CALVALUE(n) ((uint32_t)(n&0xFF))
/** \brief EMC У׼�������Ŀ�ʼ����λ��  */
#define AMHW_EMC_CAL_START       ((uint32_t)(1<<14))
/** \brief ������ɱ�־  */
#define AMHW_EMC_CAL_DONE        ((uint32_t)(1<<15))
/** @} */


/**
 * \brief ��ȡEMC��������������У׼ֵ
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \return   Լ50MHz ���������ļ���
 */
uint8_t amhw_emc_calvalue_get(amhw_syscon_t *p_hw_syscon);

/**
 * \brief ��̬�洢����ַͨ��ת����ƥ���������߿��
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \return    ��
 * \note ���øýӿڣ���ʹ�洢�������256MB
 */
am_static_inline
void amhw_emc_sc_enable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs &= ~(1 << 0);
}

/**
 * \brief ��̬�洢����ַת��ʧ��
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \return    ��
 * \note  �ϵ�Ĭ��ֵ
 */
am_static_inline
void amhw_emc_sc_disable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs |= (1 << 0);
}

/**
 * \brief EMC��λȥʹ��
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \return    ��
 * \note ���øýӿڣ���ʹ�洢�������256MB
 */
am_static_inline
void amhw_emc_reset_disable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs |= (1 << 1);
}

/**
 * \brief ����EMC��λ����Ч
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_emc_reset_assert (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs &= ~(1 << 1);
}

/**
 * \brief EMCͻ��ʹ��(�ϵ�Ĭ��ֵ)
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_emc_burst_enable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs &= ~(1 << 2);
}

/**
 * \brief EMCͻ������
 * \param[in] p_hw_syscon : ָ��ϵͳ���ƼĴ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_emc_burst_disable (amhw_syscon_t *p_hw_syscon)
{
    p_hw_syscon->scs |= (1 << 2);
}

/**
 * @} amhw_if_emc
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_EMC_H */

/* end of file */
