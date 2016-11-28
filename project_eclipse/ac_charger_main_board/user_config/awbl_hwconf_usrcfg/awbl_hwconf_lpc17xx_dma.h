/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
 DMA控制器配置信息
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_DMA

#include "driver/dma/awbl_lpc17xx_dma.h"
#include "ametal.h"

/** \brief DMA 设备信息 */
const amdr_dma_devinfo_t g_dma_devinfo = {

    AMHW_GPDMA,                    /**< \brief 指向DMA寄存器块的指针          */

	AMHW_SYSCON,				   /** \brief 指向系统控制寄存器块的指针		  */

	AMHW_DMA_LITTLE_ENDIAN,		   /**< \brief AHB主机字节顺序 小端模式       */

    INUM_GPDMA                     /**< \brief DMA中断号                      */
};

/** \brief DMA设备实例 */
amdr_dma_dev_t g_dma_dev;

/** 
 * \brief DMA 平台初始化。
 */
void amhw_plfm_dma_init (void)
{
    /* GPDMA上电 */
    amhw_power_periph_up(AMHW_POWER_GPDMA);

}

/** 
 * \brief DMA 平台去初始化。
 */
void amhw_plfm_dma_deinit (void)
{
	/* GPDMA断电 */
    amhw_power_periph_down(AMHW_POWER_GPDMA);
}

/* 设备信息 */
aw_local aw_const struct awbl_lpc17xx_dma_param __g_lpc17xx_dma_param = {
    &g_dma_dev,                           /* DMA 设备               */
    &g_dma_devinfo,                       /* DMA 设备信息时         */
    (pfunc_dma_init_t)amdr_dma_init,      /* DMA 初始化函数         */
    amhw_plfm_dma_init                    /* DMA 平台相关初始化函数 */
};

/* 设备实例内存静态分配 */
aw_local struct awbl_lpc17xx_dma_dev __g_lpc17xx_dma_dev;

#define AWBL_HWCONF_LPC17XX_DMA                     \
    {                                               \
        AWBL_LPC17XX_DMA_NAME,                      \
        0,                                          \
        AWBL_BUSID_PLB,                             \
        0,                                          \
        (struct awbl_dev *)&__g_lpc17xx_dma_dev,    \
        &__g_lpc17xx_dma_param                      \
    },

#else

#define  AWBL_HWCONF_LPC17XX_DMA

#endif    /* AW_DEV_LPC17XX_DMA */
    
/* end of file */
