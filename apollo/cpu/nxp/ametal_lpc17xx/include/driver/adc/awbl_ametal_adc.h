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

/** \brief ADC 驱动名 */
#define AWBL_AMETAL_ADC_NAME   "ametal_adc"
/*******************************************************************************
    defines
*******************************************************************************/
/**
 * \brief ametal ADC 设备信息
 */
typedef struct awbl_ametal_adc_param {
    
    /** \brief 硬件相关设备信息 */
    void *p_hw_devinfo;

    /** \brief ADC 服务相关信息 */
    struct awbl_adc_servinfo adc_servinfo;

    /** \brief BSP function to pre initialize the device */
    void (*pfunc_plfm_init) (void);
    
} awbl_ametal_adc_param_t;


/**
 * \brief ametal ADC 设备实例
 */
typedef struct awbl_ametal_adc_dev {

    /** \brief 继承自 AWBus 设备 */
    struct awbl_dev         super;

    /** \brief ADC 服务 */
    struct awbl_adc_service adc_serv;

    /** \brief 设备当前转换的通道*/
	aw_adc_channel_t        channel;

    /** \brief ADC 数据缓冲区描述符 */
    aw_adc_buf_desc_t      *p_bufdesc;

    /** \brief ADC 数据缓冲区描述符个数  */
    uint32_t                desc_num;

    /** \brief 当前使用的缓冲区描述符号  */
    uint32_t                cur_desc_cnt;

    /** \brief 当前缓冲区计数 */
    uint32_t                cur_buf_cnt;

    /** \brief 剩余转换序列次数   */
    uint32_t                remain_cnt;

    /** \brief 序列完成回调函数     */
    pfn_adc_complete_t      pfn_seq_complete;

    /** \brief 序列完成回调函数参数 */
    void                   *p_arg;

    /** \brief 自旋锁保护  */
    aw_spinlock_isr_t       lock;

    /** \brief ADC运行状态  */
    uint8_t                 stat;
#define __ADC_STAT_INIT      0   /** \brief 初始化阶段      */
#define __ADC_STAT_START     1   /** \brief ADC启动转换   */
#define __ADC_STAT_COMPLETE  2   /** \brief ADC转换完成   */
#define __ADC_STAT_STOP      3   /** \brief ADC转换停止   */
    
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
