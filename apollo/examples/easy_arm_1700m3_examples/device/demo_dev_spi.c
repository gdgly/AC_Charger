/*******************************************************************************
 *                                 Apollo
 *                       ---------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.embedcontrol.com/
 * e-mail:      apollo.support@zlg.cn
 *******************************************************************************/
/**
 * \file
 * \brief ��SPI����SPI�ӿ��������ʾ���̣�����ƽ̨EasyARM-1700M3
 *
 * - ��������:
 *   1. aw_prj_params.h��ʹ��AW_DEV_LPC17XX_SPI��AW_DEV_LPC17XX_SSP_0
 *   2. USART0�ӿں�PC��������������
 *   3. ��SPI0�ӿں�SPI����ܶ�Ӧ�Ľӿ�����������
 *      ��1�� �̽Ӻ��İ�J5��I2S_WS��P0.8�ܽš�
 *      ��2����������չ���J7A��J7B��˿ӡΪ3.21��J7A���ӡ�
 *      ��3����������չ��SPI_2��COM��������ñ��
 *   4. ���������ص�demo�壬�����ϵ���߸�λ��
 *
 * - ʵ������:
 *   1. 4λ�������ʾ����"1024".
 *   2. ��SPI����ʧ�ܣ����ڴ�ӡ"Setup SPI device Failed".
 *   
 * \par Դ����
 * \snippet demo_dev_spi.c src_dev_spi
 *
 * \internal
 * \par History
 * - 1.00 15-10-12  cod, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_dev_spi
 * \copydoc demo_dev_spi.c
 */
 
/** [src_dev_spi] */
#include "apollo.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */

/* �������õ������·��� */
#include "aw_delay.h"                   /* ��ʱ����              */
#include "aw_spi.h"                     /* SPI ����              */
#include "aw_led.h"                     /* LED ����              */
#include "aw_gpio.h"
#include "aw_vdebug.h"
#include "aw_sem.h"

#define  SEG_NUM                4
#define  SET_SEG_RCK_LOW()      do{aw_gpio_set(PIO0_8,0);}while(0)
#define  SET_SEG_RCK_HIGH()     do{aw_gpio_set(PIO0_8,1);}while(0)

/*
 * �����λѡ����
 */
static const uint8_t g_seg_tube[SEG_NUM] = { 0x01, 0x02, 0x04, 0x08 };

/*
 * 8λ�������ݽṹ
 */
struct seg8_ascii_code {
    char    ascii_char; /* ASCII�� */
    uint8_t seg_data;   /* ASCII��Ӧ����ܶ��� */
};


/*
 * ����ܶ���ASCII�����
 */
static const struct seg8_ascii_code g_seg8_ascii_code[] = {
    {' ', 0xFF},

    {'0', 0xC0}, {'1', 0xF9}, {'2', 0xA4}, {'3', 0xB0}, {'4', 0x99},
    {'5', 0x92}, {'6', 0x82}, {'7', 0xF8}, {'8', 0x80}, {'9', 0x90},

    {'A', 0x88}, {'b', 0x83}, {'C', 0xC6}, {'d', 0xA1}, {'E', 0x86},
    {'F', 0x8E}, {'H', 0x89}, {'L', 0xC7}, {'P', 0x8C},

    {'.', 0x7F}, {'-', 0xBF}
};

static const char show_str[SEG_NUM] = "1024";

/* ��ASCIIת��Ϊ����ܱ��� */
uint8_t digitron_seg8_ascii_decode (uint16_t ascii_char)
{
    int i;
    int num;

    num = sizeof(g_seg8_ascii_code) / sizeof(g_seg8_ascii_code[0]);
    for (i = 0; i < num; i++) {
        if (g_seg8_ascii_code[i].ascii_char == ascii_char) {
            return g_seg8_ascii_code[i].seg_data;
        }
    }
    return g_seg8_ascii_code[0].seg_data;
}


void spi_digital_tube_demo (aw_spi_device_t *p_spi_device)
{
    uint32_t i;
	uint8_t  seg_data;
    uint8_t  data[2];

    for(i = 0; i < SEG_NUM; i++){

        SET_SEG_RCK_LOW();   /*RCK����*/
        seg_data = digitron_seg8_ascii_decode(show_str[i]);
        data[1]  = seg_data;       /* ����ܶ������� */
        data[0]  = g_seg_tube[i];  /* �����λѡ���� */

        /* д��SPI����ܽӿ����� */
        aw_spi_write_then_write(p_spi_device,
                                &data[0],
                                2,
                                NULL,
                                0);
	}

}

/**
 * \brief ����demo
 **/
void spi_digital_task (void)
{
	int16_t         count = 0;
	aw_spi_device_t spi_digital;

	/* ���� SPI�豸 */
	aw_spi_mkdev(&spi_digital,
				 0,                 /* λ��SPI������ SPI0 */
				 16,                /* �ִ�С */
				 AW_SPI_MODE_0,     /* SPI ģʽ */
				 2000000,           /* ֧�ֵ�����ٶ� */
				 PIO0_10,           /* Ƭѡ���� */
				 NULL);             /* ���Զ����Ƭѡ���ƺ��� */

	/* ���� SPI�豸 */
	if (aw_spi_setup(&spi_digital) != AW_OK) {
        aw_kprintf("Setup SPI device Failed!\r\n");
	    while (1);
	}

	while (1) {
		spi_digital_tube_demo(&spi_digital);
		count++;
		if (count == 1000) {
			count = 0;
			aw_mdelay(2);
		}
	}

}


/**
 * \brief ����SPI����
 * \return ��
 */
void demo_dev_spi_entry (void)
{
    /* ��������ʵ�壬����ջ�ռ��СΪ1024  */
    AW_TASK_DECL_STATIC(task0, 1024);

    AW_TASK_INIT( task0,             /* ���������ʵ��   */
                 "task0",            /* ������          */
                   2,                /* �������ȼ�      */
                  1024,              /* ����ջ��С       */
                  spi_digital_task,  /* �������ں���   */
                   0);               /* ���ݸ�����Ĳ��� */
    
    AW_TASK_STARTUP(task0);          /* ��������        */
}
/** [src_dev_spi] */

/* end of file */
