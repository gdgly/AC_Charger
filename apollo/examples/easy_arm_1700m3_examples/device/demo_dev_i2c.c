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
 * \brief 在I2C操作EEPROM演示例程，适用平台EasyARM-1700M3
 *
 * - I2C0 接口： |   管脚    |     I2C功能      |   
 *               ---------------------------------
 *               |  PIO0_27  |      SDA         |
 *               ---------------------------------
 *               |  PIO0_28  |      SCL         |
 * - 操作步骤:
 *   1. aw_prj_params.h中使能AW_DEV_LPC17XX_I2C0
 *   2. PIO0_0引脚连接PC串口的TXD；
 *   3. PIO0_1引脚连接PC串口的RXD；
 *   4. 将I2C接口和EEPROM对应的接口连接起来.
 *
 * - 实验现象:
 *   1. 从EEPROM中读取到的数据，通过串口打印出来.
 *   
 * \par 源代码
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
#include "apollo.h"                     /* 此头文件必须被首先包含 */


/* 本程序用到了以下服务 */
#include "aw_delay.h"                   /* 延时服务              */
#include "aw_i2c.h"                     /* I2C 相关服务          */
#include "aw_vdebug.h"
#include "aw_nvram.h"


#define EEPROM_ADDR         0xA0                     /* 从机地址  */
#define EEPROM_CAPACITY     256                      /* 256Byte    */
#define EEPROM_PAGE_SIZE    16                       /* 一页16 Byte       */ 
#define EEPROM_BUSID        0                        /* on i2c0 bus       */

/**
 *\brief eeprom_task program entry
 *\Notes:  [1].设置I2C 设备参数 ;
 *         [2].写数据到I2C设备中 起始地址0x00 ;
 *             若一次写入一页16byte 最后一次起始地址0xF0 写完一页之后地址0xFF
 *             CAT24C02 容量2kb--->256Byte
 *         [3].读取数据从I2C设备中;
 *         [4].进行数据校验，若校验不通过 系统进入死循环;
 *         [5].校验通过进入主循环 执行操作.
 */

void eeprom_task (void)
{
    uint8_t     data[EEPROM_PAGE_SIZE];  
    aw_i2c_device_t eeprom;
    int i;
   
    aw_kprintf("EEPROM_Test:\r\n");
    
    /** \brief 设置I2C设备结构体参数 */
    aw_i2c_mkdev(&eeprom,                                    /* 从机设备描述   */
                 EEPROM_BUSID,                               /* 从机I2C总线编号*/
                 EEPROM_ADDR,                                /* 从机设备地址   */
                 (AW_I2C_ADDR_7BIT | AW_I2C_SUBADDR_1BYTE)); /* 从机设备标志   */
    /* 准备数据 */
    for (i = 0; i < EEPROM_PAGE_SIZE; i++) {
        data[i] = i+0x6 ;
    }
    aw_mdelay(10);
    
    /* 写入数据  数据缓冲区data  要写入的数据个数--16*/
    aw_i2c_write(&eeprom, 0x40, &data[0], EEPROM_PAGE_SIZE);

    /* 清除data中的数据 */
    for (i =0; i < EEPROM_PAGE_SIZE; i++) {
        data[i] = 0;
    }

    /* 读取数据从E2PROM  存放到data中 长度为16byte */
    aw_mdelay(10);
    aw_i2c_read(&eeprom, 0x40, &data[0], EEPROM_PAGE_SIZE);
    
    
    for (i =0; i < EEPROM_PAGE_SIZE; i++) {
        aw_kprintf("EEPROM read %2dth data is %2x\r\n", i, data[i]);
        if(data[i] != (i+0x6)) {
            aw_kprintf("EEPROM读写失败\r\n");
            while(1);
        }
    }
}

/**
 * \brief 建立I2C任务
 * \return 无
 */
void demo_dev_i2c_entry (void)
{
    /* 定义任务实体，分配栈空间大小为512  */
    AW_TASK_DECL_STATIC(task0,1024);

    AW_TASK_INIT(task0,              /* 定义的任务实体   */
                 "task0",            /* 任务名          */
                   6,                /* 任务优先级      */
                  1024,              /* 任务栈大小       */
                  eeprom_task,       /* 任务的入口函数   */
                   0);               /* 传递给任务的参数 */
    
    AW_TASK_STARTUP(task0);          /* 启动任务        */
}

/** [src_dev_i2c] */

/* end of file */
