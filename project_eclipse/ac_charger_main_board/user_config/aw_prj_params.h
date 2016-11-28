/*******************************************************************************

*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AnyWhere 工程参数配置文件
 */

#ifndef __AW_PRJ_PARAMS_H
#define __AW_PRJ_PARAMS_H

/**
 * \addtogroup grp_aw_plfm_params
 * @{
 */

/*******************************************************************************
  硬件剪裁
*******************************************************************************/

/**
 * \addtogroup grp_aw_plfm_params_hwcfg   硬件剪裁
 *
 * -# 注释掉外设宏定义即可禁能对应的外设，反之，则使能;
 * -# 使能某个外设后，该外设所依赖的软件组件会被自动配置进来，如无特殊需求，则
 *    无需进行下面的“组件剪裁”；
 * -# 中断控制器和GPIO是最基础的外设，默认被使能。
 * @{
 */

#define AW_DEV_LED_GPIO
#define AW_DEV_LPC17XX_ADC
//#define AW_DEV_LPC17XX_DAC
//#define AW_DEV_LPC17XX_DMA
#define AW_DEV_LPC17XX_I2C_0
//#define AW_DEV_LPC17XX_I2C_1
//#define AW_DEV_LPC17XX_I2C_2
//#define AW_DEV_LPC17XX_RIT
#define AW_DEV_LPC17XX_RTC
//#define AW_DEV_LPC17XX_CRC
//#define AW_DEV_LPC17XX_SSP_0
//#define AW_DEV_LPC17XX_SSP_1
//#define AW_DEV_LPC17XX_SSP_2
//#define AW_DEV_LPC17XX_PWM0
#define AW_DEV_LPC17XX_PWM1
//#define AW_DEV_LPC17XX_PWM_CAP
//#define AW_DEV_LPC17XX_MCPWM_CAP
//#define AW_DEV_LPC17XX_MCPWM
//#define AW_DEV_LPC17XX_TIMER0_CAP
#define AW_DEV_LPC17XX_TIMER0_TIMING
//#define AW_DEV_LPC17XX_TIMER1_CAP
#define AW_DEV_LPC17XX_TIMER1_TIMING
//#define AW_DEV_LPC17XX_TIMER2_CAP
#define AW_DEV_LPC17XX_TIMER2_TIMING
//#define AW_DEV_LPC17XX_TIMER3_CAP
#define AW_DEV_LPC17XX_TIMER3_TIMING
#define AW_DEV_LPC17XX_UART0
#define AW_DEV_LPC17XX_UART1
#define AW_DEV_LPC17XX_UART2
#define AW_DEV_LPC17XX_UART3
#define AW_DEV_LPC17XX_UART4
//#define AW_DEV_LPC17XX_WDT
//#define AW_DEV_LPC17XX_CAN1
//#define AW_DEV_LPC17XX_CAN2
#define AW_DEV_LPC17XX_EEPROM
//#define AW_DEV_LPC17XX_SDIO
#define AW_DEV_GPIO_WDT

//#define  AW_DEV_NOR_FLASH
//#define AW_DEV_EXTEND_PCF8563_0
#define AW_DRV_AWBL_PCF85063
#define AW_DRV_AWBL_GPIO_WDT

#define AW_DEV_GPIO_SPI_0
#define AW_DEV_NOR_FLASH
//#define AW_DEV_PWM_BUZZER
/** @} grp_aw_plfm_params_hwcfg */

/*******************************************************************************
  组件剪裁
*******************************************************************************/

/**
 * \addtogroup grp_aw_plfm_params_sftcfg   组件剪裁
 *
 * -# 注释掉组件宏定义即可禁能对应的组件，反之，则使能;
 * -# 使能某个组件后，该外设所依赖的软件组件会被自动配置进来;
 * -# 若某个硬件外设依赖这里的组件，当该硬件外设使能时，无论这些被依赖的组件
 *    是否被使能，都将被自动配置进来。
 * -# 注释中带“(必须)”字样的，表示该组件必须被使能；注释中带“(自动配置)”字样的
 *    表示该组件是可以被自动剪裁的，通常，这些组件保持禁能就好；
 *    其它组件则根据自己的需要，如果需要用到就使能，未使用就可以禁能。
 * @{
 */

//#define AW_COM_AWBL_LED             /* LED通用库(自动配置) */
//#define AW_DRV_AWBL_GPIO_LED        /* 基于GPIO的LED驱动 (自动配置)*/

#define AW_COM_CONSOLE              /* 控制台组件 */

#define AW_COM_AWBL_GPIO            /* GPIO通用库(必须) */
#define AW_DEV_LPC17XX_GPIO         /* LPC17XX GPIO 驱动(必须) */

#define AW_COM_AWBL_INTCTLR         /* 中断控制器通用库(必须) */
#define AW_DEV_LPC17XX_NVIC         /* 中断控制器驱动(必须)*/

//#define AW_COM_AWBL_PWM_BUZZER      /* PWM驱动蜂鸣器 */

/**
 * \name shell配置
 * @{
 */
#define AW_SHELL_SERIAL             /**< \brief 使能串口shell */
/** @} */

/**
 * \name 网络子系统裁剪配置
 * @{
 */
//#define AW_COM_NETWORK			    /**< \brief 使能网络协议栈 */
/** @} */

/**
 * \name C++支持
 * @{
 */
//#define AW_USING_CPLUSPLUS
/** @} */

/** @} grp_aw_plfm_params_sftcfg */

/*******************************************************************************
  系统配置
*******************************************************************************/

/**
 * \addtogroup  grp_aw_plfm_params_system  系统配置
 * @{
 */
/** \brief 配置PLL0输入时钟源 */
#define AW_CFG_PLL0_CLK_SRC          AMHW_CLOCK_PLL0_INSRC_OSC

/** \brief 配置主振荡器频率(若使用内部RC振荡，无需该配置，默认12MHz) */
#define AW_CFG_CLOCK_OSC_FREQ        24000000

/** \brief 是否使能PLL0，如果不使能，PLL0输出时钟即为PLL0的输入时钟,1-使能 0-禁能 */
#define AW_CFG_PLL0_ENABLE           1

/** \brief 配置PLL0期望输出频率（9.75MHz ~ 160MHz） */
#define AW_CFG_PLL0_FCCO_FREQ        96000000

/** \brief 配置CPU时钟分频，CPU_CLK = PLL0的输出频率 / DIV */
#define AW_CFG_CPU_CLK_DIV           1

/** \brief 配置外设时钟分频，PCLK = CPU_CLK/ DIV */
#define AW_CFG_PCLK_DIV              2

/** \brief 系统时钟节拍频率配置 */
#define AW_CFG_TICKS_PER_SECOND             1000

/** \brief main任务堆栈大小，推荐 >= 512 */
#define AW_CFG_MAIN_TASK_STACK_SIZE         (4096)

/** \brief main任务优先级 */
#define AW_CFG_MAIN_TASK_PRIO               1

#define  AW_CFG_ISR_DEFER_TASK_PRIO         0
#define  AW_CFG_ISR_DEFER_TASK_STACK_SIZE   (2048)

/** @} grp_aw_plfm_params_system */

/*******************************************************************************
  AWBus-lite 配置
*******************************************************************************/

/**
 * \addtogroup  grp_aw_plfm_params_awbus_lite AWBus-lite 配置
 * @{
 */

/**
 * \brief  AWBus lite 支持的最大驱动数
 *
 * 为了避免不必要的内存消耗，用户可以将此参数设置为系统中实际会使用的驱动个数。
 * 例如，如果只用到了中断控制器、GPIO两个驱动，则可以将此参数设置为2。
 *
 * \attention 有效值范围为 1 ~ 128
 */
#define AW_CFG_AWBUS_LITE_DRIVER_MAX   20

/**
 * \brief AWBus lite 支持的最大总线类型数
 *
 * 为了避免不必要的内存消耗，用户可以将此参数设置为系统中实际会使用的总线类型数。
 * 例如，如果只用到了CPU本地总线 (必须使用)、I2C两种总线类型，则可以将此参数设置为2。
 *
 * \attention 有效值范围为 1 ~ 128
 */
#define AW_CFG_AWBUS_LITE_BUSTYPE_MAX  8

/** @} grp_aw_plfm_params_system */


/*******************************************************************************
  控制台配置
*******************************************************************************/

/**
 * \addtogroup  grp_aw_plfm_vdebug_usrcfg
 * @{
 */

/** \brief 控制台启动时，是否显示欢迎标识：0-不显示 1-显示 */
#define AW_CFG_CONSOLE_SHOW_BANNER       1

/** \brief 控制台串口号 */
#define AW_CFG_CONSOLE_COMID             COM0

/** \brief 控制台波特率 */
#define AW_CFG_CONSOLE_BAUD_RATE         115200

/** @} grp_aw_plfm_vdebug_usrcfg */

/*******************************************************************************
  LPC17XX GPIO 配置
*******************************************************************************/
/**
 * \addtogroup  grp_aw_plfm_LPC17XX_nvic_usrcfg
 * @{
 */

/**
 * \brief 配置ISR中断信息条数
 *
 * 由于LPC17XX资源有限，为了避免不必要的内存消耗，用户可以将此参数设置为实际需要
 * 连接触发器的引脚的个数。例如，只有3个引脚会被连接触发器，则可以将此参数设置为3。
 *
 * \attention LCP177x_8x 有40个中断，因此，此参数最大有效值为40
 */
#define AW_CFG_ARMCM_NVIC_ISRINFO_COUNT    20

/** @} grp_aw_plfm_LPC17XX_nvic_usrcfg */

/*******************************************************************************
  串行端口配置
*******************************************************************************/

/**
 * \addtogroup grp_aw_plfm_serial_common_usrcfg
 * @{
 */

/**
 * \brief 系统串行端口个数
 *
 * 当前支持的最大端口个数为5个，应该根据实际的硬件配置修改。
 * 配置的端口个数不应该超过5个。
 */
#define AW_CFG_NUM_COM      		5

/**
 * \name 串行端口的收发缓冲大小配置
 * \brief 不用的串行端口（编号超过AW_CFG_NUM_COM）的配置不起作用。
 * @{
 */

#define AW_CFG_COM0_TX_BUF_SIZE     128 /**< \brief COM0 发送缓冲大小 */
#define AW_CFG_COM0_RX_BUF_SIZE     128 /**< \brief COM0 接收缓冲大小 */

#define AW_CFG_COM1_TX_BUF_SIZE     128 /**< \brief COM1 发送缓冲大小 */
#define AW_CFG_COM1_RX_BUF_SIZE     128 /**< \brief COM1 接收缓冲大小 */

#define AW_CFG_COM2_TX_BUF_SIZE     128 /**< \brief COM2 发送缓冲大小 */
#define AW_CFG_COM2_RX_BUF_SIZE     128 /**< \brief COM2 接收缓冲大小 */

#define AW_CFG_COM3_TX_BUF_SIZE     128 /**< \brief COM3 发送缓冲大小 */
#define AW_CFG_COM3_RX_BUF_SIZE     128 /**< \brief COM3 接收缓冲大小 */

#define AW_CFG_COM4_TX_BUF_SIZE     128 /**< \brief COM4 发送缓冲大小 */
#define AW_CFG_COM4_RX_BUF_SIZE     128 /**< \brief COM4 接收缓冲大小 */

#define AW_CFG_COM5_TX_BUF_SIZE     128 /**< \brief COM5 发送缓冲大小 */
#define AW_CFG_COM5_RX_BUF_SIZE     128 /**< \brief COM5 接收缓冲大小 */

#define AW_CFG_COM6_TX_BUF_SIZE     128 /**< \brief COM6 发送缓冲大小 */
#define AW_CFG_COM6_RX_BUF_SIZE     128 /**< \brief COM6 接收缓冲大小 */

#define AW_CFG_COM7_TX_BUF_SIZE     128 /**< \brief COM7 发送缓冲大小 */
#define AW_CFG_COM7_RX_BUF_SIZE     128 /**< \brief COM7 接收缓冲大小 */

#define AW_CFG_COM8_TX_BUF_SIZE     128 /**< \brief COM8 发送缓冲大小 */
#define AW_CFG_COM8_RX_BUF_SIZE     128 /**< \brief COM8 接收缓冲大小 */

#define AW_CFG_COM9_TX_BUF_SIZE     128 /**< \brief COM9 发送缓冲大小 */
#define AW_CFG_COM9_RX_BUF_SIZE     128 /**< \brief COM9 接收缓冲大小 */

/** @} */

/** @} grp_aw_plfm_serial_common_usrcfg */

/*******************************************************************************
  资源ID
*******************************************************************************/

/* RTC ID 分配 */
#define LPC17XX_RTC_ID 0

/* PWM 总线ID分配 */
#define LPC17XX_PWM_UNIT_ID            1
#define LPC17XX_PWM_CAP_UNIT_ID        1

#define LPC17XX_MCPWM_UNIT_ID          0
#define LPC17XX_MCPWM_CAP_UNIT_ID      0

/* 定时器 总线ID分配 */
#define LPC17XX_TIMER0_TIMING_UNIT_ID  0
#define LPC17XX_TIMER0_CAP_UNIT_ID     0

#define LPC17XX_TIMER1_TIMING_UNIT_ID  1
#define LPC17XX_TIMER1_CAP_UNIT_ID     1

#define LPC17XX_TIMER2_TIMING_UNIT_ID  2
#define LPC17XX_TIMER2_CAP_UNIT_ID     2

#define LPC17XX_TIMER3_TIMING_UNIT_ID  3
#define LPC17XX_TIMER3_CAP_UNIT_ID     3

#define LPC17XX_RIT_UNIT_ID            7

/* SPI 总线ID分配 */
#define LPC17XX_SSP0_BUSID             0
#define LPC17XX_SSP1_BUSID             1
#define LPC17XX_SSP2_BUSID             2
#define GPIO_SPI0_BUSID                3

/* I2C 总线ID分配  */
#define LPC17XX_I2C0_BUSID             0
#define LPC17XX_I2C1_BUSID             1
#define LPC17XX_I2C2_BUSID             2

/* 串口 ID 分配 */
#define LPC17XX_UART0_COMID            COM0
#define LPC17XX_UART1_COMID            COM1
#define LPC17XX_UART2_COMID            COM2
#define LPC17XX_UART3_COMID            COM3
#define LPC17XX_UART4_COMID            COM4

/* CAN ID 分配 */
#define LPC17XX_CAN1_UNIT_ID           0
#define LPC17XX_CAN2_UNIT_ID           1

/* MII BUS ID 分配  */
#define LPC17XX_MII0_BUSID             0

/** @} grp_aw_plfm_params_srcid */

/*******************************************************************************
  自动配置
*******************************************************************************/
/** \cond */

/* 控制台组件依赖 UARTx */
#ifdef AW_COM_CONSOLE
#if AW_CFG_CONSOLE_COMID == COM0
#define AW_DEV_LPC17XX_UART0        /* LPC17XX UART0 */
#endif
#endif  /* AW_COM_CONSOLE */

#ifdef AW_DEV_LED_GPIO
#define AW_COM_AWBL_LED
#define AW_DRV_AWBL_GPIO_LED
#endif

/* I2C0 依赖于 LPC17xx_I2C 驱动 */
#if defined(AW_DEV_LPC17XX_I2C_0) || \
	defined(AW_DEV_LPC17XX_I2C_1) || \
	defined(AW_DEV_LPC17XX_I2C_2)
#define AW_DRV_AWBL_LPC17XX_I2C     /* AWBus-lite LPC17XX I2C 驱动 */
#endif  /* AW_DEV_LPC17XX_I2C_0 */

/* PWM */
#if defined(AW_DEV_LPC17XX_PWM0) || defined(AW_DEV_LPC17XX_PWM1) || defined(AW_DEV_LPC17XX_MCPWM)
#define AW_DRV_AWBL_LPC17XX_PWM
#endif  /* AW_DEV_LPC17XX_PWM */

/* CAP */
#if defined(AW_DEV_LPC17XX_PWM_CAP)    || \
	defined(AW_DEV_LPC17XX_MCPWM_CAP)  || \
	defined(AW_DEV_LPC17XX_TIMER0_CAP) || \
	defined(AW_DEV_LPC17XX_TIMER1_CAP) || \
	defined(AW_DEV_LPC17XX_TIMER2_CAP) || \
    defined(AW_DEV_LPC17XX_TIMER3_CAP)
#define AW_DRV_AWBL_LPC17XX_CAP
#endif  /* AW_DEV_LPC17XX_PWM_CAP */

/* SPI SSP */
#if defined(AW_DEV_LPC17XX_SPI_0) || \
	defined(AW_DEV_LPC17XX_SPI_1) || \
	defined(AW_DEV_LPC17XX_SSP_0) || \
	defined(AW_DEV_LPC17XX_SSP_1) || \
	defined(AW_DEV_LPC17XX_SSP_2)
#define AW_DRV_AWBL_LPC17XX_SPI
#endif  /* AW_DEV_LPC17XX_SPI */

/* TIMER */
#if defined(AW_DEV_LPC17XX_TIMER0_TIMING) || \
	defined(AW_DEV_LPC17XX_TIMER1_TIMING) || \
	defined(AW_DEV_LPC17XX_TIMER2_TIMING) || \
	defined(AW_DEV_LPC17XX_TIMER3_TIMING)
#define AW_DRV_AWBL_LPC17XX_TIMER
#endif  /* AW_DEV_LPC17XX_TIMER_TIMING */

/* EMAC */
#if defined(AW_DEV_LPC17XX_EMAC)
#define AW_DRV_AWBL_LPC17XX_EMAC
#endif  /* AW_DEV_LPC17XX_EMAC */

/* LPC17XX_UART 依赖于 UART 驱动*/
#if defined(AW_DEV_LPC17XX_UART0) || \
	defined(AW_DEV_LPC17XX_UART1) || \
	defined(AW_DEV_LPC17XX_UART2) || \
	defined(AW_DEV_LPC17XX_UART3) || \
	defined(AW_DEV_LPC17XX_UART4)
#define AW_DRV_AWBL_LPC17XX_UART     /* AWBus-lite  UART 驱动 */
#endif  /* AW_DEV_LPC17XX_UART */

/* TIMER 依赖于 LPC17XX_TIMER 驱动 */
#if defined(AW_DEV_LPC17XX_TIMER0_TIMING) || \
    defined(AW_DEV_LPC17XX_TIMER1_TIMING) || \
    defined(AW_DEV_LPC17XX_TIMER2_TIMING) || \
    defined(AW_DEV_LPC17XX_TIMER3_TIMING)
#define AW_DRV_AWBL_LPC17XX_TIMER32 /* AWBus-lite LPC17XX 定时器驱动 */
#endif  /* AW_DEV_LPC17XX_TIMER32_0 */

/* CAN */
#if defined(AW_DEV_LPC17XX_CAN0) || defined(AW_DEV_LPC17XX_CAN1)
#define AW_DRV_AWBL_LPC17XX_CAN
#endif  /* AW_DEV_LPC17XX_CAN */

#if defined(AW_DEV_LPC17XX_EEPROM)
#define AW_DRV_AWBL_LPC17XX_EEPROM
#endif

/* CAP */
#if defined(AW_DRV_AWBL_LPC17XX_CAP)
#define AW_COM_AWBL_CAP
#endif  /* AW_DRV_AWBL_LPC17XX_CAP */

/* LPC17xx_ADC 驱动依赖于 ADC 通用库 */
#ifdef AW_DEV_LPC17XX_ADC
#define AW_COM_AWBL_ADC       /* AWBus-lite ADC 通用库 */
#endif  /* AW_DRV_AWBL_LPC17XX_ADC */

/* LPC17xx_DAC 驱动依赖于 DAC 通用库 */
#ifdef AW_DEV_LPC17XX_DAC
#define AW_COM_AWBL_DAC       /* AWBus-lite DAC 通用库 */
#endif  /* AW_DRV_AWBL_LPC17XX_DAC */

/* LPC17xx_RTC 驱动依赖于 RTC 通用库 */
#ifdef AW_DEV_LPC17XX_RTC
#define AW_COM_AWBL_RTC    /* AWBus-lite RTC 总线核心组件 */
#endif  /* AW_DEV_LPC17XX_RTC */

/* LPC17xx_WDT 驱动依赖于 WDT 通用库 */
#if defined(AW_DEV_LPC17XX_WDT) || defined(AW_DEV_GPIO_WDT)
#define AW_COM_AWBL_WDT    /* AWBus-lite WDT 总线核心组件 */
#endif  /* AW_DEV_LPC17XX_WDT */

/* LPC17xx_I2C 驱动依赖于 I2C 通用库 */
#ifdef AW_DRV_AWBL_LPC17XX_I2C
#define AW_COM_AWBL_I2CBUS    /* AWBus-lite I2C 总线核心组件 */
#endif  /* AW_DRV_AWBL_LPC17XX_I2C */

/* LPC17xx_UART 驱动依赖于 I2C 通用库 */
#ifdef AW_DRV_AWBL_LPC17XX_UART
#define AW_COM_AWBL_SERIAL    /* AWBus-lite UART 总线核心组件 */
#endif  /* AW_DRV_AWBL_LPC17XX_UART */

/* LPC17xx_SPI 驱动依赖于 SPI 通用库 */
#ifdef AW_DRV_AWBL_LPC17XX_SPI
#define AW_COM_AWBL_SPIBUS    /* AWBus-lite SPI 总线核心组件 */
#endif  /* AW_DRV_AWBL_LPC17XX_SSP */

/* SDIO驱动依赖于 LPC17XX_SDIO设备 */
#ifdef AW_DEV_LPC17XX_SDIO
#define AW_COM_AWBL_SDIOBUS
#define AW_DEV_AWBL_SDCARD
#endif  /* AW_DEV_LPC17XX_SDIO */


#if defined(AW_DEV_GPIO_SPI_0)
#define AW_DRV_AWBL_GPIO_SPI
#endif

#ifdef AW_DRV_AWBL_GPIO_SPI
#define AW_COM_AWBL_SPIBUS
#endif

#ifdef AW_DEV_NOR_FLASH
#ifndef AW_COM_AWBL_SPIBUS
#error "AW_DEV_NOR_FLASH depends on SPI device!"
#endif
#define AW_DRV_AWBL_NOR_FLASH
//#define AW_DRV_BLOCK_DEV
//#define AW_DRV_MTD_DEV
#define AW_COM_EVENT
#endif

/** \endcond */

/** @} grp_aw_prj_param */

#endif  /* __AW_PRJ_PARAMS_H */

/* end of file */
