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
 * \brief ��I2C����EEPROM��ʾ���̣�����ƽ̨EasyARM-1700M3
 *
 * - I2C0 �ӿڣ� |   �ܽ�    |     I2C����      |   
 *               ---------------------------------
 *               |  PIO0_27  |      SDA         |
 *               ---------------------------------
 *               |  PIO0_28  |      SCL         |
 * - ��������:
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_I2C0
 *   2. PIO0_0��������PC���ڵ�TXD��
 *   3. PIO0_1��������PC���ڵ�RXD��
 *   4. ��I2C�ӿں�EEPROM��Ӧ�Ľӿ���������.
 *
 * - ʵ������:
 *   1. ��EEPROM�ж�ȡ�������ݣ�ͨ�����ڴ�ӡ����.
 *   
 * \par Դ����
 * \snippet demo_dev_i2c.c src_dev_i2c
 *
 * \internal
 * \par History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_dev_i2c
 * \copydoc demo_dev_i2c.c
 */
 
/** [src_dev_i2c] */
#include "apollo.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */


/* �������õ������·��� */
#include "aw_delay.h"                   /* ��ʱ����              */
#include "aw_i2c.h"                     /* I2C ��ط���          */
#include "aw_vdebug.h"
#include "aw_nvram.h"


#define EEPROM_ADDR         0xA0                     /* �ӻ���ַ  */
#define EEPROM_CAPACITY     256                      /* 256Byte    */
#define EEPROM_PAGE_SIZE    16                       /* һҳ16 Byte       */ 
#define EEPROM_BUSID        0                        /* on i2c0 bus       */

/**
 *\brief eeprom_task program entry
 *\Notes:  [1].����I2C �豸���� ;
 *         [2].д���ݵ�I2C�豸�� ��ʼ��ַ0x00 ;
 *             ��һ��д��һҳ16byte ���һ����ʼ��ַ0xF0 д��һҳ֮���ַ0xFF
 *             CAT24C02 ����2kb--->256Byte
 *         [3].��ȡ���ݴ�I2C�豸��;
 *         [4].��������У�飬��У�鲻ͨ�� ϵͳ������ѭ��;
 *         [5].У��ͨ��������ѭ�� ִ�в���.
 */

void eeprom_task (void)
{
    uint8_t     data[EEPROM_PAGE_SIZE];  
    aw_i2c_device_t eeprom;
    int i;
   
    aw_kprintf("EEPROM_Test:\r\n");
    
    /** \brief ����I2C�豸�ṹ����� */
    aw_i2c_mkdev(&eeprom,                                    /* �ӻ��豸����   */
                 EEPROM_BUSID,                               /* �ӻ�I2C���߱��*/
                 EEPROM_ADDR,                                /* �ӻ��豸��ַ   */
                 (AW_I2C_ADDR_7BIT | AW_I2C_SUBADDR_1BYTE)); /* �ӻ��豸��־   */
    /* ׼������ */
    for (i = 0; i < EEPROM_PAGE_SIZE; i++) {
        data[i] = i+0x6 ;
    }
    aw_mdelay(10);
    
    /* д������  ���ݻ�����data  Ҫд������ݸ���--16*/
    aw_i2c_write(&eeprom, 0x40, &data[0], EEPROM_PAGE_SIZE);

    /* ���data�е����� */
    for (i =0; i < EEPROM_PAGE_SIZE; i++) {
        data[i] = 0;
    }

    /* ��ȡ���ݴ�E2PROM  ��ŵ�data�� ����Ϊ16byte */
    aw_mdelay(10);
    aw_i2c_read(&eeprom, 0x40, &data[0], EEPROM_PAGE_SIZE);
    
    
    for (i =0; i < EEPROM_PAGE_SIZE; i++) {
        aw_kprintf("EEPROM read %2dth data is %2x\r\n", i, data[i]);
        if(data[i] != (i+0x6)) {
            aw_kprintf("EEPROM��дʧ��\r\n");
            while(1);
        }
    }
}

/**
 * \brief ����I2C����
 * \return ��
 */
void demo_dev_i2c_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ512  */
    AW_TASK_DECL_STATIC(task0,1024);

    AW_TASK_INIT(task0,              /* ���������ʵ��   */
                 "task0",            /* ������          */
                   6,                /* �������ȼ�      */
                  1024,              /* ����ջ��С       */
                  eeprom_task,       /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task0);          /* ��������        */
}

/** [src_dev_i2c] */

/* end of file */
