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
 * \brief  QEIӲ����ʵ��
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  anu, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_QEI_H
#define __AMHW_QEI_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "am_types.h"

/** 
 * \addtogroup amhw_if_qei
 * \copydoc amhw_qei.h
 * @{
 */
    
/** 
 * \brief  QEI�Ĵ��������б�
 */
typedef struct amhw_qei{
    __O  uint32_t qeicon;       /**< \brief ���ƼĴ��� */
    __I  uint32_t qeistat;      /**< \brief ����״̬�Ĵ��� */
    __IO uint32_t qeiconf;      /**< \brief ���üĴ��� */
    __I  uint32_t qeipos;       /**< \brief λ�üĴ��� */
    __IO uint32_t qeimaxpos;    /**< \brief ���λ�üĴ��� */
    __IO uint32_t cmpos0;       /**< \brief λ�ñȽϼĴ���0 */
    __IO uint32_t cmpos1;       /**< \brief λ�ñȽϼĴ���1 */
    __IO uint32_t cmpos2;       /**< \brief λ�ñȽϼĴ���2 */
    __I  uint32_t inxcnt;       /**< \brief ���������Ĵ��� */
    __IO uint32_t inxcmp;       /**< \brief �����ȽϼĴ��� */
    __IO uint32_t qeiload;      /**< \brief �ٶȶ�ʱ�����ؼĴ��� */
    __I  uint32_t qeitime;      /**< \brief �ٶȶ�ʱ���Ĵ��� */
    __I  uint32_t qeivel;       /**< \brief �ٶȼ������Ĵ��� */
    __I  uint32_t qeicap;       /**< \brief �ٶȲ���Ĵ��� */
    __IO uint32_t velcomp;      /**< \brief �ٶȱȽϼĴ��� */
    __IO uint32_t filter;       /**< \brief �����˲��Ĵ��� */
         uint32_t reserved[998];/**< \brief ������ */
    __O  uint32_t qeiiec;       /**< \brief �ж�ʹ������Ĵ��� */
    __O  uint32_t qeiies;       /**< \brief �ж�ʹ����λ�Ĵ��� */
    __I  uint32_t qeiintstat;   /**< \brief �ж�״̬�Ĵ��� */
    __I  uint32_t qeiie;        /**< \brief �ж�ʹ�ܼĴ��� */
    __O  uint32_t qeiclr;       /**< \brief �ж�״̬����Ĵ��� */
    __O  uint32_t qeiset;       /**< \brief �ж�״̬���üĴ��� */
} amhw_qei_t;

/**
 * \name QEI���ƼĴ���λ����
 * \anchor grp_amhw_qei_con
 * @{
 */

#define AMHW_QEI_CON_RESP    (1UL << 0) /**< \brief ��λλ�ü����� */
#define AMHW_QEI_CON_RESPI   (1UL << 1) /**< \brief �����������ʱ��λλ�ü����� */
#define AMHW_QEI_CON_RESV    (1UL << 2) /**< \brief ��λ�ٶ� */
#define AMHW_QEI_CON_RESI    (1UL << 3) /**< \brief ��λ���������� */

/** @} */

/**
 * \brief ��λλ�ü�����
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_pos_rst (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeicon = AMHW_QEI_CON_RESP;
}

/**
 * \brief ����������������ʱ��λλ�ü�����
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_indexpos_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeicon = AMHW_QEI_CON_RESPI;
}

/**
 * \brief ��λ�ٶ�
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_velocity_rst (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeicon = AMHW_QEI_CON_RESV;
}

/**
 * \brief ��λ����������
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_index_rst (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeicon = AMHW_QEI_CON_RESI;
}

/**
 * \name QEI���üĴ���λ����
 * \anchor grp_amhw_qei_conf
 * @{
 */

#define AMHW_QEI_CONF_DIRINV     (1UL << 0) /**< \brief ������ */
#define AMHW_QEI_CONF_SIGMODE    (1UL << 1) /**< \brief �ź�ģʽ */
#define AMHW_QEI_CONF_CAPMODE    (1UL << 2) /**< \brief ����ģʽ */
#define AMHW_QEI_CONF_INVINX     (1UL << 3) /**< \brief �������巴�� */

/** @} */

/**
 * \brief ���÷����� ��DIR����
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_dirinv_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf |= AMHW_QEI_CONF_DIRINV;
}

/**
 * \brief ���������
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_dirinv_clr (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf &= ~AMHW_QEI_CONF_DIRINV;
}

/**
 * \brief �����ź�ģʽ AΪ�����ź� BΪʱ���ź�
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_sigmode_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf |= AMHW_QEI_CONF_SIGMODE;
}

/**
 * \brief ����ź�ģʽ AB��Ϊ������λ�ź�
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_sigmode_clr (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf &= ~AMHW_QEI_CONF_SIGMODE;
}

/**
 * \brief ���ò���ģʽ ͬʱ��AB����м���4X
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_capmode_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf |= AMHW_QEI_CONF_CAPMODE;
}

/**
 * \brief �������ģʽ ֻ��A����м���2X
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_capmode_clr (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf &= ~AMHW_QEI_CONF_CAPMODE;
}

/**
 * \brief ���������������巴��
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_invinx_set (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf |= AMHW_QEI_CONF_INVINX;
}

/**
 * \brief ��������������巴��
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_invinx_clr (amhw_qei_t *p_hw_qei)
{
    p_hw_qei->qeiconf &= ~AMHW_QEI_CONF_INVINX;
}

/**
 * \name QEI״̬�Ĵ���λ����
 * \anchor grp_amhw_qei_stat
 * @{
 */

#define AMHW_QEI_STAT_DIR     (1UL << 0)     /**< \brief ����λ */

/** @} */

/**
 * \brief ��ȡ����λ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval 0Ϊ����
 * \retval 1Ϊ����
 */
am_static_inline 
uint32_t amhw_qei_dir_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeistat & AMHW_QEI_STAT_DIR)? 1 : 0;
}

/**
 * \brief ��ȡ��ǰ��λ��ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval λ��ֵ
 */
am_static_inline 
uint32_t amhw_qei_pos_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeipos);
}

/**
 * \brief ��������λ��ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] maxpos   : λ��ֵ
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_maxpos_set (amhw_qei_t *p_hw_qei, uint32_t maxpos)
{
    p_hw_qei->qeimaxpos = maxpos;
}

/**
 * \brief ��ȡ����λ��ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ����λ��ֵ
 */
am_static_inline 
uint32_t amhw_qei_maxpos_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeimaxpos);
}

/**
 * \brief ����λ�ñȽ���0
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] pos      : λ��ֵ
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_cmpos0_set (amhw_qei_t *p_hw_qei, uint32_t pos)
{
    p_hw_qei->cmpos0 = pos;
}

/**
 * \brief ��ȡλ�ñȽ���0��ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval λ��ֵ
 */
am_static_inline 
uint32_t amhw_qei_cmpos0_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->cmpos0);
}

/**
 * \brief ����λ�ñȽ���1
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] pos      : λ��ֵ
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_cmpos1_set (amhw_qei_t *p_hw_qei, uint32_t pos)
{
    p_hw_qei->cmpos1 = pos;
}

/**
 * \brief ��ȡλ�ñȽ���1��ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval λ��ֵ
 */
am_static_inline 
uint32_t amhw_qei_cmpos1_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->cmpos1);
}

/**
 * \brief ����λ�ñȽ���2
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] pos      : λ��ֵ
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_cmpos2_set (amhw_qei_t *p_hw_qei, uint32_t pos)
{
    p_hw_qei->cmpos2 = pos;
}

/**
 * \brief ��ȡλ�ñȽ���2��ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval λ��ֵ
 */
am_static_inline 
uint32_t amhw_qei_cmpos2_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->cmpos2);
}

/**
 * \brief ��ȡ���������Ĵ���
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval λ��ֵ
 */
am_static_inline 
uint32_t amhw_qei_inxcnt_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->inxcnt);
}

/**
 * \brief ���������Ƚ���
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] index    : λ��ֵ
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_inxcmp_set (amhw_qei_t *p_hw_qei, uint32_t index)
{
    p_hw_qei->inxcmp = index;
}

/**
 * \brief ��ȡ�����Ƚ�����ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ����ֵ
 */
am_static_inline 
uint32_t amhw_qei_inxcmp_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->inxcmp);
}

/**
 * \brief ���ö�ʱ��װ��
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] time     : װ��ʱ����
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_timeload_set (amhw_qei_t *p_hw_qei, uint32_t time)
{
    p_hw_qei->qeiload = time;
}

/**
 * \brief ��ȡ��ʱ��װ�ص�ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ��ʱ����װ��ʱ��
 */
am_static_inline 
uint32_t amhw_qei_timeload_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeiload);
}

/**
 * \brief ��ȡ��ǰ�ٶȶ�ʱ����ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval �ٶȶ�ʱ����ֵ
 */
am_static_inline 
uint32_t amhw_qei_timevel_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeivel);
}

/**
 * \brief ��ȡ��ǰ�ٶ�����ļ���
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval �ٶ��������ֵ
 */
am_static_inline 
uint32_t amhw_qei_time_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeitime);
}

/**
 * \brief ��ȡ��ǰ�ٶȲ������
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval �ٶ��������ֵ
 */
am_static_inline 
uint32_t amhw_qei_capture_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeicap);
}

/**
 * \brief �����ٶȱȽϵ�ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] vel      : �ٶȵıȽ�ֵ
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_velocitycmp_set (amhw_qei_t *p_hw_qei, uint32_t vel)
{
    p_hw_qei->velcomp = vel;
}

/**
 * \brief ��ȡ�ٶȱȽϵ�ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval �ٶȱȽϵ�ֵ
 */
am_static_inline 
uint32_t amhw_qei_velocitycmp_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->velcomp);
}

/**
 * \brief ���������˲���������ʱ �����������Ϊ0���˲�����·
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] time     : 0����· 1~4,294,967,295������ʱ��
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_filter_set (amhw_qei_t *p_hw_qei, uint32_t time)
{
    p_hw_qei->filter = time;
}

/**
 * \brief ��ȡ�ٶȱȽϵ�ֵ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval ������ʱ��ֵ
 */
am_static_inline 
uint32_t amhw_qei_filter_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->filter);
}

/**
 * \brief QEI �ж�����
 */
typedef uint32_t amhw_qei_int_type_t;

#define AMHW_QEI_INT_TYPE_COUNT    13  /**< \brief �ж����͵����� */


/**
 * \name QEI�жϼĴ���λ����
 * \anchor grp_amhw_qei_int
 * @{
 */

#define AMHW_QEI_INT_INX         (1UL << 0)  /**< \brief ��⵽һ���������� */
#define AMHW_QEI_INT_TIM         (1UL << 1)  /**< \brief ��⵽�ٶȶ�ʱ����� */
#define AMHW_QEI_INT_VELC        (1UL << 2)  /**< \brief ��⵽�����ٶ�С�ڱȽ��ٶ� */
#define AMHW_QEI_INT_DIR         (1UL << 3)  /**< \brief ��⵽����ı� */
#define AMHW_QEI_INT_ERR         (1UL << 4)  /**< \brief ��⵽��������λ���� */
#define AMHW_QEI_INT_ENCLK       (1UL << 5)  /**< \brief ��������ʱ������ */
#define AMHW_QEI_INT_POS0        (1UL << 6)  /**< \brief ��⵽λ��0�Ƚ�ֵ�뵱ǰλ����� */
#define AMHW_QEI_INT_POS1        (1UL << 7)  /**< \brief ��⵽λ��1�Ƚ�ֵ�뵱ǰλ����� */
#define AMHW_QEI_INT_POS2        (1UL << 8)  /**< \brief ��⵽λ��2�Ƚ�ֵ�뵱ǰλ����� */
#define AMHW_QEI_INT_REV         (1UL << 9)  /**< \brief ��⵽�����Ƚ�ֵ���ڵ�ǰ���� */
#define AMHW_QEI_INT_POS0REV     (1UL << 10) /**< \brief ��⵽λ��0����ת�����ж���� */
#define AMHW_QEI_INT_POS1REV     (1UL << 11) /**< \brief ��⵽λ��1����ת�����ж���� */
#define AMHW_QEI_INT_POS2REV     (1UL << 12) /**< \brief ��⵽λ��2����ת�����ж���� */
#define AMHW_QEI_INT_ALL         (0XFFFFFFFF)/**< \brief ���������ж� */

/** @} */

/**
 * \brief ��ȡ�ж�״̬
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval �жϵ����ͣ��μ� \ref grp_amhw_qei_int "interrupt type"
 */
am_static_inline 
amhw_qei_int_type_t amhw_qei_intstat_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeiintstat);
}

/**
 * \brief �ж�����״̬
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] inttype  : �ж����� ���ò������μ�
 *                       \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_intstat_set (amhw_qei_t *p_hw_qei, amhw_qei_int_type_t inttype)
{
	p_hw_qei->qeiset = inttype;
}


/**
 * \brief �ж����״̬
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] inttype  : �ж����� ���ò������μ�
 *                       \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_intstat_clr (amhw_qei_t *p_hw_qei, amhw_qei_int_type_t inttype)
{
	p_hw_qei->qeiclr = inttype;
}

/**
 * \brief �ж�ʹ��
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 *
 * \retval �ж����ͣ��μ� \ref grp_amhw_qei_int "interrupt type"
 */
am_static_inline 
amhw_qei_int_type_t amhw_qei_int_get (amhw_qei_t *p_hw_qei)
{
	return (p_hw_qei->qeiie);
}

/**
 * \brief �ж�ʹ����λ
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] inttype  : �ж����� ���ò������μ�
 *                       \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_int_set (amhw_qei_t *p_hw_qei, amhw_qei_int_type_t inttype)
{
	p_hw_qei->qeiies = inttype;
}

/**
 * \brief �ж�ʹ�����
 *
 * \param[in] p_hw_qei : ָ��QEI�Ĵ������ָ��
 * \param[in] inttype  : �ж����� ���ò������μ�
 *                       \ref grp_amhw_qei_int "interrupt type"
 *
 * \retval ��
 */
am_static_inline 
void amhw_qei_int_clr (amhw_qei_t *p_hw_qei, amhw_qei_int_type_t inttype)
{
	p_hw_qei->qeiiec = inttype;
}

/** 
 * @} amhw_if_qei
 */

#ifdef __cplusplus
}
#endif


#endif  /* __AMDR_QEI_H */

/*end of file */

