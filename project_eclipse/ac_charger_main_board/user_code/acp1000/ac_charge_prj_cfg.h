/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief ACP1000 工程全局配置
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-23  xjc, first implementation
 * \endinternal
 */
#ifndef __AC_CHARGE_PRJ_CFG_H
#define __AC_CHARGE_PRJ_CFG_H

#include "aw_serial.h"

/******************************************************************************
 *  软件版本定义
 ******************************************************************************/
#define ACP1000_VERSION_MAJOR  0  /* 主版本号 */
#define ACP1000_VERSION_MINOR  9  /* 次版本号 */
#define ACP1000_VERSION_STRING "LPC1778 : V0.90" /* 版本号字符串（必须少于20个字节）*/
/******************************************************************************
 *  EEPROM存储定义(真正定义在“awbl_hwconf_lpc17xx_eeprom.h”)
 ******************************************************************************/
#define ACP1000_EEPROM_NAME   "lpc17_eeprom"  /* 存储器名称 */
#define ACP1000_EEPROM_PILE_ID            0   /* 桩ID偏移 */
#define ACP1000_EEPROM_HUB4G_ADDR         8   /* 集中器地址偏移 */
#define ACP1000_EEPROM_PRICE              9   /* 电价地址偏移 */
#define ACP1000_EEPROM_CHARGE_TOTAL       62  /* 充电总条目 */
#define ACP1000_EEPROM_CHARGE_LAST        63  /* 最近一次充电总条目偏移 */
#define ACP1000_EEPROM_CHARGE_DAT_START   64  /* 充电数据条目起始偏移 */
#define ACP1000_EEPROM_CHARGE_MAX_NUMS    90  /* 最大允许存储的充电条目数 */
#define ACP1000_EEPROM_CHARGE_SIZE        44  /* 每条充电条目字节数 */
#define ACP1000_EEPROM_CARD_KEY           8   /* 保存卡密钥字节 */

#define ACP1000_EEPROM_PILE_ID_SET        1   /* 开启桩ID设置 */
#define ACP1000_EEPROM_PILE_ID_GET        1   /* 开启桩ID获取 */
#define ACP1000_EEPROM_PRICE_SET          1   /* 价格设置 */
#define ACP1000_EEPROM_PRICE_GET          1   /* 价格获取 */
#define ACP1000_EEPROM_HUB4G_ADDR_SET     1   /* 开启集中器地址设置 */
#define ACP1000_EEPROM_HUB4G_ADDR_GET     1   /* 开启集中器地址获取 */
#define ACP1000_EEPROM_CHARGE_DAT_SET     1   /* 开启充电数据设置 */
#define ACP1000_EEPROM_CHARGE_DAT_GET     1   /* 开启充电数据获取 */
/******************************************************************************
 *  超时时间定义
 ******************************************************************************/
#define ACP1000_WAIT_KEY_TIMEOUT 10000   /* 最大等待集中器下发key的时间， 超时不做其他处理，并将预刷卡标志清零（单位ms） */
#define ACP1000_AUTH_TIMEOUT     10000   /* 最大鉴权时间， 超时认为鉴权失败 （单位ms） */
#define ACP1000_BILLING_TIMEOUT  10000   /* 最大结算余额下发时间， 若超时- */
#define ACP1000_SCARM_TIMEOUT    30000   /* 紧急开关异常延时时间  */
#define ACP1000_DUGS_ERR_TIMEOUT 10000   /* 最大串口屏通信超时时间  */
#define ACP1000_HUB4G_ERR_TIMEOUT 10000   /* 最大集中器通信超时时间  */
/******************************************************************************
 *  串口资源分配
 ******************************************************************************/
#define ACP1000_CARDREADER_COM   COM3 /* 读卡器串口 */
#define ACP1000_DBUGS_COM        COM2 /* 串口屏串口 */
#define ACP1000_AMMETER_COM      COM1 /* 电表串口 */
#define ACP1000_HUB4G_COM        COM4 /* 集中器串口 */
#define ACP1000_RTC_NUM          1     /* 计时的RTC编号 */
#define ACP1000_PILE_MAX_CURR    35000 /* 桩输出的最大电流 单位0.001A*/
/******************************************************************************
 *  测试调试宏
 ******************************************************************************/
#define ACP1000_CARD_VALID_DETECT     0  /* 是否检测卡是否有效： 使能  0： 禁能(非调试时置1)*/
#define ACP1000_CARD_AMOUNT_ADD       0  /* 是否新的一张时，自动初始化余额 （调试用）*/
#define ACP1000_ENERGY_AUTO_ADD       0  /* 充电时使用电量是否自动增加（调试用）*/
#define ACP1000_ERR_INFO_PRINT        0  /* 是否打印异常信息 */
/******************************************************************************
 *  异常检测 （对应模块禁能时，模块对充电业务流程没有影响）
 ******************************************************************************/

#define ACP1000_AMMETER_ERR_DETECT    1  /* 是否使能电表模块异常检测, 1： 使能  0： 禁能 */
#define ACP1000_CURR_ERR_DETECT       1  /* 是否使能电流模块异常检测, 1： 使能  0： 禁能 */
#define ACP1000_VOL_ERR_DETECT        1  /* 是否使能电压模块异常检测, 1： 使能  0： 禁能 */
#define ACP1000_CARD_ERR_DETECT       0  /* 是否使能读卡模块异常检测, 1： 使能  0： 禁能 */
#define ACP1000_AC1_ERR_DETECT        1  /* 是否使能交流母排检测  1： 使能  0： 禁能*/
#define ACP1000_LIGHT_ERR_DETECT      1  /* 是否使能防雷器异常检测  1： 使能  0： 禁能*/
#define ACP1000_TEMP_ERR_DETECT       1  /* 是否使能温度异常检测  1： 使能  0： 禁能*/
#define ACP1000_DUGS_ERR_DETECT       0  /* 是否使能串口屏通信异常检测  1： 使能  0： 禁能*/
#define ACP1000_HUB4G_ERR_DETECT      0  /* 是否使能集中器通信异常检测  1： 使能  0： 禁能*/

#define ACP1000_HUB4G_AUTH            0  /* 是否开启集中器鉴权 1： 使能  0： 禁能*/
#define ACP1000_HUB4G_BILLING         0  /* 是否按集中器结算 1： 使能  0： 禁能*/
#define ACP1000_OVERTIME_DETECT       0  /* 是否鉴权后无操作检测  1： 使能  0： 禁能*/
#define ACP1000_SCRAM_DETECT          1  /* 是否紧急开关检测  1： 使能  0： 禁能*/
#define ACP1000_VTP1_DETECT           1  /* 是否VTP1电压检测  1： 使能  0： 禁能*/
#define ACP1000_CARD_DETECT           0  /* 是否使能卡片检测 1： 使能  0： 禁能*/
#define ACP1000_BILING_MONITOR        0  /* 计费单元是否限制充电  1： 使能  0： 禁能  */
#define ACP1000_SKIP_AUTH             1  /* 充电逻辑是否忽略鉴权，实现插枪即充  1： 使能  0： 禁能  */
/******************************************************************************
 *  任务控制
 ******************************************************************************/
#define ACP1000_VOL_TASK                 1  /* 是否使能电压异常检测  1： 使能  0： 禁能（必须）*/
#define ACP1000_INLOCK_TASK              0  /* 是否使能枪在位检测  1： 使能  0： 禁能（可选）*/
#define ACP1000_LEDLOCK_TASK             1  /* 是否启动LED和锁检测任务  （可选）*/
#define ACP1000_HUB4G_TASK               1  /* 是否启动集中器任务 （升级必须）*/
#define ACP1000_DUGS_TASK                0  /* 是否启动串口屏任务（充电业务可选） */
#define ACP1000_CARD_DETECT_TASK         0  /* 是否卡片检测任务 （充电业务可选）*/
#define ACP1000_VTP1_DETECT_TASK         1  /* 是否VTP1电压检测任务（必须） */
#define ACP1000_CURR_DETECT_TASK         1  /* 是否启动电流检测任务（防护可选） */
#define ACP1000_PILE_ERR_DETECT_TASK     1  /* 是否启动桩异常检测任务（防护必须） */
#define ACP1000_BUZZER_TASK              1  /* 是否启动蜂鸣器任务 （可选）*/
#define ACP1000_PILE_TEMP_TASK           1  /* 是否启动桩温度检测任务 （防护可选）*/
#define ACP1000_AMMETER_DETECT_TASK      1  /* 是否电表读取任务（计费必须） */
#define ACP1000_BILING_DETECT_TASK       0  /* 是否启动计费任务（充电业务必须） */
#define ACP1000_CHARGE_TASK              1  /* 是否启动充电任务  （必须）*/
#define ACP1000_DUBUG_SHELL_TASK         1  /* 是否使能测试壳  （调试可选）*/
#endif
