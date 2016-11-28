/*******************************************************************************
*                                 apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.embedcontrol.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief DMA�ڴ浽�ڴ�����ݴ�������
 *
 * - �������裺
     1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_DMA
 *   2. PIO0_2��������PC���ڵ�TXD��
 *   3. PIO0_3��������PC���ڵ�RXD��
 *
 * - ʵ������
 *   1. DMA����ɹ���LED������
 *   2. DMA����ʧ�ܣ�LED��˸��
 *
 * \par Դ����
 * \snippet demo_dev_dma_m2m.c src_dev_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_dma_m2m
 * \copydoc demo_dev_dma_m2m.c
 */

/** [src_dev_dma_m2m] */
#include "apollo.h"
#include "main.h"

#include "aw_task.h" 
#include "aw_delay.h"
#include "aw_led.h"
#include "aw_vdebug.h"
#include "aw_lpc17xx_dma.h"

/**
 * \brief DMA�������
 *\param[in] p_arg : �������
 * \return ��
 */
static void task_entry (void *p_arg)
{
    /* DMAͨ�������� */
    aw_lpc17xx_dma_desc_t g_desc;

    /* ���ݻ����� */
    uint8_t src_buf[256];
    uint8_t dst_buf[256];

    uint32_t flags;
    int      i;


    aw_lpc17xx_dma_chan_setup(AW_DMA_CHAN_0,	             /* DMAͨ����                    */
    	                      AW_DMA_CONN_NONE,              /* �޴���Դ����                    */
    		    		      AW_DMA_CONN_NONE,              /* �޴���Ŀ������                    */
#if 1  /* ��ΪLPC177x_8x���˴��������� */
    		    		      AW_DMA_CCONFIG_SREQ_NONE    |  /* ����ԴΪ�洢�����ɺ���       */
                        	  AW_DMA_CCONFIG_DREQ_NONE	  |  /* ����Ŀ��Ϊ�洢�����ɺ���     */
#endif
                        	  AW_DMA_CCONFIG_TRANTYPE_M2M |  /* �洢�����洢��               */
                        	  AW_DMA_CCONFIG_IE_VALID 	  |  /* �������жϴ���             */
                        	  AW_DMA_CCONFIG_ITC_VALID    |  /* �������ն˼����ж�         */
                        	  AW_DMA_CCONFIG_TRANS_UNLOCK ); /* ����������                   */

    for (i = 0; i < 256; i++) {
        src_buf[i] = i;
        dst_buf[i] = 0;
    }

	/* DMA�������� */
	flags = AW_DMA_CCONTROL_SBSIZE_32     |   /* Դͻ������������ SIZE = 32      */
			AW_DMA_CCONTROL_DBSIZE_32     |   /* Ŀ��ͻ������������ SIZE = 32    */
			AW_DMA_CCONTROL_SWIDTH_32BIT  |   /* Դ�������ݿ�� 32Bits           */
			AW_DMA_CCONTROL_DWIDTH_32BIT  |   /* Ŀ�괫�����ݿ�� 32Bits    		*/
			AW_DMA_CCONTROL_SI_ENABLE     |   /* ָ��Դ��ַ�Զ�����           	*/
			AW_DMA_CCONTROL_DI_ENABLE     |   /* ָ��Ŀ���ַ�Զ�����         	*/
			AW_DMA_CCONTROL_ITC_ENABLE;	      /* ʹ���ն˼����ж�                */

	aw_lpc17xx_dma_desc_build(&g_desc,              /* ͨ��������                      */
							  (uint32_t)src_buf,    /* Դ�����ݵ�ַ                    */
							  (uint32_t)dst_buf,    /* Ŀ������ݵ�ַ                  */
							  256,                  /* ������ֽ���                    */
							  flags);               /* �������ò���                    */

    /* DMA ͬ������ */
    aw_lpc17xx_dma_tran_sync(AW_DMA_CHAN_0, &g_desc);

    /* ֹͣͨ������  */
    aw_lpc17xx_dma_tran_stop(AW_DMA_CHAN_0);

    for (i = 0; i < 256; i++) {
        if (src_buf[i] != dst_buf[i]) {
            while (1) {
                aw_led_toggle(0);
                aw_mdelay(100);
            }
        }
    }

    aw_led_on(0);
    
    while (1) {
        aw_mdelay(1);
   }
}

/**
 * \brief ����DMA����
 * \return ��
 */
void demo_dev_dma_m2m_entry (void)
{
    AW_TASK_DECL_STATIC(task, 1024);
    
    AW_TASK_INIT(task,               /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL ���� */
                "task",              /* ��������                                            */ 
                 6,                  /* �������ȼ�                                          */ 
                 1024,               /* �����ջ��С                                        */ 
                 task_entry,         /* ������ں���                                        */ 
                (void*)0);           /* ������ڲ���                                        */ 

    AW_TASK_STARTUP(task);
}

/** [src_dev_dma_m2m] */
 
/* end of file */
