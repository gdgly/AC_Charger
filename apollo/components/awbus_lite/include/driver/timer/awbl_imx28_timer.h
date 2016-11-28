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
 * \brief IMX28 ϵ�ж�ʱ������
 *
 * ������ֻʵ���˶�ʱ���������жϹ��ܣ����ṩ������ƥ�䡢������ת�����PWM���ܡ�
 *
 * \par 1.������Ϣ
 *
 *  - ������:  "lpc11xx_timer32"(32-bit timer) ; "lpc11xx_timer16"(16-bit timer)
 *  - ��������: AWBL_BUSID_PLB
 *  - �豸��Ϣ: struct awbl_lpc11xx_timer_param
 *
 * \par 2.�����豸
 *
 *  - NXP LPC11XX ϵ��MCU
 *  - NXP LPC13XX ϵ��MCU
 *  - ������LPC11XX TIMER ���ݵ��豸
 *
 * \par 3.�豸����/����
 *
 *  - \ref grp_awbl_drv_lpc11xx_16_32timer_hwconf
 *
 * \par 4.�û��ӿ�
 *
 *  - \ref grp_aw_serv_hwtimer
 *
 * \internal
 * \par modification history
 * - 1.00 12-11-15  orz, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX28_TIMER_H
#define __AWBL_IMX28_TIMER_H /* { */

#include "awbl_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_awbl_drv_imx28_timer
 * \copydetails awbl_imx28_timer.h
 * @{
 */

/**
 * \defgroup  grp_awbl_drv_lpc11xx_16_32timer_hwconf �豸����/����
 *
 * LPC11XX TIMER Ӳ���豸�Ķ���������Ĵ�����ʾ���û��ڶ���Ŀ��ϵͳ��Ӳ����Դʱ,
 * ����ֱ�ӽ���δ���Ƕ�뵽 awbus_lite_hwconf_usrcfg.c �ж�Ӧ��λ�ã�Ȼ����豸
 * ��Ϣ���б�Ҫ������(�����õ���Ŀ�á�x����ʶ)��
 *
 * \note �ж��ٸ�TIMER���ͽ�����Ĵ���Ƕ����ٴΣ�ע�⽫�����޸�Ϊ��ͬ�����֡�
 *
 * \include  hwconf_usrcfg_hwtimer_lpc11xx.c
 * \note �����������д����û����á���ʶ�ģ���ʾ�û��ڿ���Ӧ��ʱ�������ô˲�����
 *
 * - ��1��ƽ̨��س�ʼ������ \n
 * ��ƽ̨��ʼ�����������ʹ��ʱ�ӵ���ƽ̨��صĲ�����
 *
 * - ��2����ʱ���ɴﵽ����СƵ�� \n
 * ������ֲ��ж�ʱ���Ŀ��÷�Ƶ������ȷ���ò���
 *
 * - ��3����ʱ���ɴﵽ�����Ƶ�� \n
 * ������ֲ��ж�ʱ���Ŀ��÷�Ƶ������ȷ���ò���
 *
 * - ��4����ʱ��������ʱ��Ƶ�� \n
 * ������ֲἰϵͳʱ��������ȷ���ò���
 *
 * - ��5����ʱ���������ת���� \n
 *
 * - ��6����ʱ���Ĵ�����ʼ��ַ \n
 * ������ֲ�ȷ���ò���
 *
 * - ��8���豸���� \n
 * 16λ��ʱ�����lpc11xx_timer16����32λ��ʱ������д��lpc11xx_timer32��
 *
 * - ��9����ʱ���豸�ĵ�Ԫ�� \n
 * ��������ͬ���豸����16λ��ʱ��0��16λ��ʱ��1
 */

/** @} */

/******************************************************************************/
struct imx28_reg {
    uint32_t dat; /**< \brief data value (both read and write) register */
    uint32_t set; /**< \brief data bits field set register */
    uint32_t clr; /**< \brief data bits field clear register */
    uint32_t tog; /**< \brief data bits field toggle register */
};

/** \brief IMX28 timer registers */
struct imx28_timer_reg {
    struct imx28_reg tim_ctrl;      /**< \brief [00] Control and status */
    struct imx28_reg running_count; /**< \brief [10] Running Count */
    struct imx28_reg fixed_count;   /**< \brief [20] Fixed Count */
    struct imx28_reg match_count;   /**< \brief [30] Match Count */
};

/******************************************************************************/

/** \brief timer fixed parameter */
struct awbl_imx28_timer_param {
    uint32_t	clk_frequency;	        /**< \brief clock frequency              */
    uint32_t     alloc_byname;          /**< \brief the bit with 1 means the chan the timer can any be alloc by name   */
    uint32_t         reg_addr;          /**< \brief register base address   */
    int                  inum;          /**< \brief interrupt number        */
    void (*pfunc_plfm_init) (void);     /**< \brief platform initializing   */ 
};

/** \brief convert AWBus timer device info to imx28 timer parameter */
#define awbldev_get_imx28_timer_param(p_dev) \
    ((struct awbl_imx28_timer_param *)AWBL_DEVINFO_GET(p_dev))
 
/******************************************************************************/

/** \brief imx28 Timer type for AWBus */
struct awbl_imx28_timer {
    /* always go first */   
    awbl_dev_t  dev;                 /** \brief AWBus device data */
    
    struct awbl_timer        tmr;    /**< \brief AWBL timer instance */
    struct imx28_timer_reg  *reg;    /**< \brief register base */
    
    uint32_t                 count;  /**< \brief current max counts */
    uint32_t          rollover_period;  /**< \brief rollover_period */
    
    struct awbl_timer_param  param;     /**< \brief the timer's param */
    
    void (*pfunc_isr) (void *p_arg);    /**< \brief ISR */
    void  *p_arg;                       /**< \brief ISR argument */
};

/** \brief Convert a awbl_timer pointer to a awbl_imx28_timer pointer */
#define awbl_timer_to_imx28_timer(p_timer) \
    ((struct awbl_imx28_timer *)(p_timer))

/** \brief convert a awbl_dev pointer to awbl_imx28_timer pointer */
#define awbldev_to_imx28_timer(p_dev) \
          ((struct awbl_imx28_timer *)(p_dev))

/** \brief get IMX28 timer parameter */
#define imx28_timer_get_param(p_imxtimer)  ((struct awbl_imx28_timer_param *) \
    AWBL_DEVINFO_GET(&((p_imxtimer)->tmr.dev)))

/******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* } __AWBL_IMX28_TIMER_H */

/* end of file */
