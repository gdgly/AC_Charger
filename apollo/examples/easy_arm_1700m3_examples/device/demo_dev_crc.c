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
 * \brief CRC��ʾ����
 *
 * - ��������:
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_CRC
 *   2. USART0�ӿں�PC��������������
 *
 * - ʵ������
 *   1. ���ڴ�ӡCRCУ������
 * 
 * - ��ע��
 *   ��MCUΪLPC175X_6X��ʹ�����CRC��
 *   ��MCUΪLPC177X_8X��ʹ��Ӳ��CRC��
 *
 * \par Դ����
 * \snippet demo_dev_crc.c src_dev_crc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-16  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_crc
 * \copydoc demo_dev_crc.c
 */

/** [src_dev_crc] */
#include "apollo.h"
#include "main.h"
#include "aw_led.h"
#include "aw_delay.h"
#include "aw_crc.h"
#include "aw_vdebug.h"

/**
 * \brief LED�������
 *\param[in] p_arg : �������
 * \return ��
 */
static void task_entry (void *p_arg)
{
    uint8_t  ret;
    uint8_t  ndata[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    uint32_t crc;

    /* ������һ��ģ�ͣ���ģ�;��ǳ��õ�CRC-16ģ�ͣ���WinRAR�о���ʹ�õĸ�ģ�� */
    AW_CRC_DECL(crc16,         /* crcģ�� crc16 */
                16,            /* crc��� 16 */
                0x8005,        /* ���ɶ���ʽ */
                0x0000,        /* ��ʼֵ */
                TRUE,          /* refin */
                TRUE,          /* refout */
                0x0000);       /* xorout */


     ret =  AW_CRC_INIT(crc16,               /* crcģ�ͣ���AW_CRC_DECL()����� */
                        crctable16_1021_ref, /* crc��ϵͳ�ģ�����Ҫ���� */
                        AW_CRC_FLAG_AUTO);   /* �Զ�ģʽ���Զ�ѡ��Ӳ�������ʵ�� */
    if (ret != AW_OK) {
        /* ��ʼ��ʧ�� */
    	aw_kprintf("���� error\n");
    } else {
        AW_CRC_CAL(crc16,                /* crcģ�ͣ���AW_CRC_DECL()����� */
                   ndata,                /* ������CRC��������� */
                   sizeof(ndata));       /* �˴μ�������� */

        /* �м���Լ������� */
        /* ... */


        /* ��������ȡ�����ս��    ������ӦΪ��0xbb3d  */
        crc = AW_CRC_FINAL(crc16);  /* crcģ�ͣ���AW_CRC_DECL()����� */

        aw_kprintf("������Ϊ:%x\n",crc);

        /* �������������㣬����Ҫ���µ���AW_CRC_INIT()��ʼ�����ټ��� */
    }

    while (1) {
    	aw_mdelay(5);
    }
}

/**
 * \brief ����CRC����
 * \return ��
 */
void demo_dev_crc_entry (void)
{
    AW_TASK_DECL_STATIC(task, 256);

    AW_TASK_INIT(task,               /* ����ʵ��:AW_TASK_DECL_STATIC ���� AW_TASK_DECL ���� */
                "task",              /* ��������                                            */
                 6,                  /* �������ȼ�                                          */
                 256,                /* �����ջ��С                                        */
                 task_entry,         /* ������ں���                                        */
                (void*)0);           /* ������ڲ���                                        */

    AW_TASK_STARTUP(task);
}

/** [src_dev_crc] */

/* end of file */
