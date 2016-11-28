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
 DMA������������Ϣ
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_DMA

#include "driver/dma/awbl_lpc17xx_dma.h"
#include "ametal.h"

/** \brief DMA �豸��Ϣ */
const amdr_dma_devinfo_t g_dma_devinfo = {

    AMHW_GPDMA,                    /**< \brief ָ��DMA�Ĵ������ָ��          */

	AMHW_SYSCON,				   /** \brief ָ��ϵͳ���ƼĴ������ָ��		  */

	AMHW_DMA_LITTLE_ENDIAN,		   /**< \brief AHB�����ֽ�˳�� С��ģʽ       */

    INUM_GPDMA                     /**< \brief DMA�жϺ�                      */
};

/** \brief DMA�豸ʵ�� */
amdr_dma_dev_t g_dma_dev;

/** 
 * \brief DMA ƽ̨��ʼ����
 */
void amhw_plfm_dma_init (void)
{
    /* GPDMA�ϵ� */
    amhw_power_periph_up(AMHW_POWER_GPDMA);

}

/** 
 * \brief DMA ƽ̨ȥ��ʼ����
 */
void amhw_plfm_dma_deinit (void)
{
	/* GPDMA�ϵ� */
    amhw_power_periph_down(AMHW_POWER_GPDMA);
}

/* �豸��Ϣ */
aw_local aw_const struct awbl_lpc17xx_dma_param __g_lpc17xx_dma_param = {
    &g_dma_dev,                           /* DMA �豸               */
    &g_dma_devinfo,                       /* DMA �豸��Ϣʱ         */
    (pfunc_dma_init_t)amdr_dma_init,      /* DMA ��ʼ������         */
    amhw_plfm_dma_init                    /* DMA ƽ̨��س�ʼ������ */
};

/* �豸ʵ���ڴ澲̬���� */
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
