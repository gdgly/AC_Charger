/*******************************************************************************
 *                                 Apollo
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
 * \brief ������ʾ���̣������ж�ģʽ����ѯģʽ
 *
 * - �������裺
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_UART0
 *   2. PIO0_2��������PC���ڵ�TXD��
 *   3. PIO0_3��������PC���ڵ�RXD��
 *
 * - ʵ������
 *   1. ���Ƚ���UART0 ��ѯģʽ ��λ������10���ַ� ���շ��͵������� (10��)��
 *   2. ���Ž����ж�ģʽ      ��λ������10���ַ� ���շ��͵������� (10��)�� 
 *
 * \par Դ����
 * \snippet demo_dev_serial.c src_dev_serial
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dev_serial
 * \copydoc demo_dev_serial.c
 */

/** [src_dev_serial] */
#include "apollo.h"

#include "aw_delay.h"
#include "aw_serial.h"                  /* �����豸���� */
#include "aw_gpio.h"


/**
*\brief serial_task program entry 
*\details [1].�Ƚ��г�ʼ�����ù���(���ڲ�������)
*         [2].���ò�ѯģʽ �����ַ��� ��λ������10���ַ� ���շ��͵������� (10��)
*         [3].�����ж�ģʽ �����ַ��� ��λ������10���ַ� ���շ��͵������� (10��)
*     
*\param[in] void *p_arg 
*\note    ��λ�������ַ�ʱ����Ҫѡ�񡾷������С�ѡ��
*/
void serial_task (void)
{

    static char buf[32];
    int len=0; 
    int i = 0; 
    /* ���ڳ�ʼ������ ������115200 */
    aw_serial_ioctl(COM0, SIO_BAUD_SET, (void *)115200);

    /* ���ڲ��� ��8������λ 1��ֹͣλ������żУ�� */
    aw_serial_ioctl(COM0, SIO_HW_OPTS_SET, (void *)(CS8 | CLOCAL));
    
    /* ����ģʽ ����ѯģʽ �����ַ��� */
    aw_serial_ioctl(COM0, SIO_MODE_SET, (void *)SIO_MODE_POLL);
    aw_serial_poll_write(COM0, "Hello,Enter Serial Poll Mode:\r\n", 32);
    
    for(i = 0; i < 10; i++) {
        len = aw_serial_poll_read(COM0, buf, 10);
            if (len > 0) {
                aw_serial_poll_write(COM0, buf, len);            
            }
        aw_serial_poll_write(COM0, "\r\n", len);
    }
    
    /* �ٴ����ô���ģʽ ���ж�ģʽ */
    aw_serial_ioctl(COM0, SIO_MODE_SET, (void *)SIO_MODE_INT);
    aw_serial_write(COM0, "Hello,Enter Serial INT  Mode:\r\n", 32);
    for(i = 0; i < 10; i++) {
        len = aw_serial_read(COM0, buf, 10);
            if (len > 0) {
                aw_serial_write(COM0, buf, len);            
            }
        aw_serial_write(COM0, "\r\n", len);
    }
    
}


/**
 * \brief ����SERIAL����
 * \return ��
 */
void demo_dev_serial_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0,512);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������          */
                   2,                /* �������ȼ�      */
                  512,               /* ����ջ��С       */
                  serial_task,       /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task0);          /* ��������        */
}
/** [src_dev_serial] */

/* end of file */
