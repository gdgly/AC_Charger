
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
 * \brief I2S驱动，服务I2S标准接口
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
 * \brief LPC17XX I2S  设备信息
 */	

typedef struct amdr_i2s_devinfo {
	uint8_t          ms_mode;          /**< \brief 主从模式选择*/
	
	uint8_t          clk_select;       /**< \brief  时钟选择 */  

	uint8_t          irq_depth;        /**< \brief  中断深度选择 */
	
    uint8_t          wordwidth_set;    /**< \brief 传输字的宽度  */
	
    uint8_t          sound_mode;       /**< \brief 声道模式  立体/单声道	*/      
   
    uint32_t         sample_speed;     /**< \brief I2S初始化总线速度,am_i2s_speed_set() 标准接口可以改变速率 */
 
    amhw_i2s_t      *p_hw_i2s;         /**< \brief 指向I2S寄存器块的指针  */
	
    uint16_t         inum;             /**< \brief I2S 控制器的中断号     */
} amdr_i2s_devinfo_t;

/**
 * \brief I2S设备
 */
typedef struct amdr_i2s_dev {

    am_i2s_serv_t  i2s_serv;                    /**< \brief I2S 标准服务        */
   
    int (*pfn_txdata_get)(void *, uint32_t *);  /**< \brief 发送函数指针        */
    int (*pfn_rxdata_put)(void *, uint32_t);    /**< \brief 接收函数指针        */
    int (*pfn_err)(void *, int, void *, int);   /**< \brief 错误函数指针        */

    void     *txget_arg;                        /**< \brief 发送函数参数指针    */
    void     *rxput_arg;                        /**< \brief 接收函数参数指针    */
    void     *err_arg;                          /**< \brief 错误函数参数指针    */
	
    /** \brief 指向设备信息指针 */
    const amdr_i2s_devinfo_t *p_devinfo;
	
} amdr_i2s_dev_t;


/**
 * \brief  I2S 初始化
 *
 * \param[in] p_dev     : 指向I2S设备的指针
 * \param[in] p_devinfo : 指向I2S设备信息的指针 
 *
 * \return 标准I2S接口服务.如为NULL，则初始化失败
 */
am_i2s_handle_t amdr_i2s_init(amdr_i2s_dev_t           *p_dev,
                              const amdr_i2s_devinfo_t *p_devinfo);

/**
 * \brief  I2S 解初始化
 * \param[in] p_dev : 指向I2S设备的指针
 * \return 无
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


