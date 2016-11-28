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
 * \brief 在SPI操作SPI接口数码管演示例程，适用平台EasyARM-1700M3
 *
 * - 操作步骤:
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_SPI或AW_DEV_LPC17XX_SSP_0
 *   2. USART0接口和PC串口连接起来；
 *   3. 将SPI0接口和SPI数码管对应的接口连接起来：
 *      （1） 短接核心板J5的I2S_WS与P0.8管脚。
 *      （2）将基础扩展板的J7A与J7B中丝印为3.21与J7A连接。
 *      （3）将基础扩展板SPI_2与COM接上跳线帽。
 *   4. 将程序下载到demo板，重新上电或者复位。
 *
 * - 实验现象:
 *   1. 4位数码管显示数字"1024".
 *   2. 若SPI配置失败，串口打印"Setup SPI device Failed".
 *   
 * \par 源代码
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
#include "apollo.h"                     /* 此头文件必须被首先包含 */

/* 本程序用到了以下服务 */
#include "aw_delay.h"                   /* 延时服务              */
#include "aw_spi.h"                     /* SPI 服务              */
#include "aw_led.h"                     /* LED 服务              */
#include "aw_gpio.h"
#include "aw_vdebug.h"
#include "aw_sem.h"

#define  SEG_NUM                4
#define  SET_SEG_RCK_LOW()      do{aw_gpio_set(PIO0_8,0);}while(0)
#define  SET_SEG_RCK_HIGH()     do{aw_gpio_set(PIO0_8,1);}while(0)

/*
 * 数码管位选定义
 */
static const uint8_t g_seg_tube[SEG_NUM] = { 0x01, 0x02, 0x04, 0x08 };

/*
 * 8位段码数据结构
 */
struct seg8_ascii_code {
    char    ascii_char; /* ASCII码 */
    uint8_t seg_data;   /* ASCII对应数码管段码 */
};


/*
 * 数码管段码ASCII码编码
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

/* 将ASCII转换为数码管编码 */
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

        SET_SEG_RCK_LOW();   /*RCK拉低*/
        seg_data = digitron_seg8_ascii_decode(show_str[i]);
        data[1]  = seg_data;       /* 数码管段码数据 */
        data[0]  = g_seg_tube[i];  /* 数码管位选数据 */

        /* 写入SPI数码管接口数据 */
        aw_spi_write_then_write(p_spi_device,
                                &data[0],
                                2,
                                NULL,
                                0);
	}

}

/**
 * \brief 测试demo
 **/
void spi_digital_task (void)
{
	int16_t         count = 0;
	aw_spi_device_t spi_digital;

	/* 生成 SPI设备 */
	aw_spi_mkdev(&spi_digital,
				 0,                 /* 位于SPI总线上 SPI0 */
				 16,                /* 字大小 */
				 AW_SPI_MODE_0,     /* SPI 模式 */
				 2000000,           /* 支持的最大速度 */
				 PIO0_10,           /* 片选引脚 */
				 NULL);             /* 无自定义的片选控制函数 */

	/* 设置 SPI设备 */
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
 * \brief 建立SPI任务
 * \return 无
 */
void demo_dev_spi_entry (void)
{
    /* 定义任务实体，分配栈空间大小为1024  */
    AW_TASK_DECL_STATIC(task0, 1024);

    AW_TASK_INIT( task0,             /* 定义的任务实体   */
                 "task0",            /* 任务名          */
                   2,                /* 任务优先级      */
                  1024,              /* 任务栈大小       */
                  spi_digital_task,  /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task0);          /* 启动任务        */
}
/** [src_dev_spi] */

/* end of file */
