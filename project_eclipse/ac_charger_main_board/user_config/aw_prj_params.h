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
 * \brief AnyWhere ���̲��������ļ�
 */

#ifndef __AW_PRJ_PARAMS_H
#define __AW_PRJ_PARAMS_H

/**
 * \addtogroup grp_aw_plfm_params
 * @{
 */

/*******************************************************************************
  Ӳ������
*******************************************************************************/

/**
 * \addtogroup grp_aw_plfm_params_hwcfg   Ӳ������
 *
 * -# ע�͵�����궨�弴�ɽ��ܶ�Ӧ�����裬��֮����ʹ��;
 * -# ʹ��ĳ������󣬸��������������������ᱻ�Զ����ý�������������������
 *    �����������ġ�������á���
 * -# �жϿ�������GPIO������������裬Ĭ�ϱ�ʹ�ܡ�
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
  �������
*******************************************************************************/

/**
 * \addtogroup grp_aw_plfm_params_sftcfg   �������
 *
 * -# ע�͵�����궨�弴�ɽ��ܶ�Ӧ���������֮����ʹ��;
 * -# ʹ��ĳ������󣬸��������������������ᱻ�Զ����ý���;
 * -# ��ĳ��Ӳ������������������������Ӳ������ʹ��ʱ��������Щ�����������
 *    �Ƿ�ʹ�ܣ��������Զ����ý�����
 * -# ע���д���(����)�������ģ���ʾ��������뱻ʹ�ܣ�ע���д���(�Զ�����)��������
 *    ��ʾ������ǿ��Ա��Զ����õģ�ͨ������Щ������ֽ��ܾͺã�
 *    �������������Լ�����Ҫ�������Ҫ�õ���ʹ�ܣ�δʹ�þͿ��Խ��ܡ�
 * @{
 */

//#define AW_COM_AWBL_LED             /* LEDͨ�ÿ�(�Զ�����) */
//#define AW_DRV_AWBL_GPIO_LED        /* ����GPIO��LED���� (�Զ�����)*/

#define AW_COM_CONSOLE              /* ����̨��� */

#define AW_COM_AWBL_GPIO            /* GPIOͨ�ÿ�(����) */
#define AW_DEV_LPC17XX_GPIO         /* LPC17XX GPIO ����(����) */

#define AW_COM_AWBL_INTCTLR         /* �жϿ�����ͨ�ÿ�(����) */
#define AW_DEV_LPC17XX_NVIC         /* �жϿ���������(����)*/

//#define AW_COM_AWBL_PWM_BUZZER      /* PWM���������� */

/**
 * \name shell����
 * @{
 */
#define AW_SHELL_SERIAL             /**< \brief ʹ�ܴ���shell */
/** @} */

/**
 * \name ������ϵͳ�ü�����
 * @{
 */
//#define AW_COM_NETWORK			    /**< \brief ʹ������Э��ջ */
/** @} */

/**
 * \name C++֧��
 * @{
 */
//#define AW_USING_CPLUSPLUS
/** @} */

/** @} grp_aw_plfm_params_sftcfg */

/*******************************************************************************
  ϵͳ����
*******************************************************************************/

/**
 * \addtogroup  grp_aw_plfm_params_system  ϵͳ����
 * @{
 */
/** \brief ����PLL0����ʱ��Դ */
#define AW_CFG_PLL0_CLK_SRC          AMHW_CLOCK_PLL0_INSRC_OSC

/** \brief ����������Ƶ��(��ʹ���ڲ�RC�񵴣���������ã�Ĭ��12MHz) */
#define AW_CFG_CLOCK_OSC_FREQ        24000000

/** \brief �Ƿ�ʹ��PLL0�������ʹ�ܣ�PLL0���ʱ�Ӽ�ΪPLL0������ʱ��,1-ʹ�� 0-���� */
#define AW_CFG_PLL0_ENABLE           1

/** \brief ����PLL0�������Ƶ�ʣ�9.75MHz ~ 160MHz�� */
#define AW_CFG_PLL0_FCCO_FREQ        96000000

/** \brief ����CPUʱ�ӷ�Ƶ��CPU_CLK = PLL0�����Ƶ�� / DIV */
#define AW_CFG_CPU_CLK_DIV           1

/** \brief ��������ʱ�ӷ�Ƶ��PCLK = CPU_CLK/ DIV */
#define AW_CFG_PCLK_DIV              2

/** \brief ϵͳʱ�ӽ���Ƶ������ */
#define AW_CFG_TICKS_PER_SECOND             1000

/** \brief main�����ջ��С���Ƽ� >= 512 */
#define AW_CFG_MAIN_TASK_STACK_SIZE         (4096)

/** \brief main�������ȼ� */
#define AW_CFG_MAIN_TASK_PRIO               1

#define  AW_CFG_ISR_DEFER_TASK_PRIO         0
#define  AW_CFG_ISR_DEFER_TASK_STACK_SIZE   (2048)

/** @} grp_aw_plfm_params_system */

/*******************************************************************************
  AWBus-lite ����
*******************************************************************************/

/**
 * \addtogroup  grp_aw_plfm_params_awbus_lite AWBus-lite ����
 * @{
 */

/**
 * \brief  AWBus lite ֧�ֵ����������
 *
 * Ϊ�˱��ⲻ��Ҫ���ڴ����ģ��û����Խ��˲�������Ϊϵͳ��ʵ�ʻ�ʹ�õ�����������
 * ���磬���ֻ�õ����жϿ�������GPIO��������������Խ��˲�������Ϊ2��
 *
 * \attention ��Чֵ��ΧΪ 1 ~ 128
 */
#define AW_CFG_AWBUS_LITE_DRIVER_MAX   20

/**
 * \brief AWBus lite ֧�ֵ��������������
 *
 * Ϊ�˱��ⲻ��Ҫ���ڴ����ģ��û����Խ��˲�������Ϊϵͳ��ʵ�ʻ�ʹ�õ�������������
 * ���磬���ֻ�õ���CPU�������� (����ʹ��)��I2C�����������ͣ�����Խ��˲�������Ϊ2��
 *
 * \attention ��Чֵ��ΧΪ 1 ~ 128
 */
#define AW_CFG_AWBUS_LITE_BUSTYPE_MAX  8

/** @} grp_aw_plfm_params_system */


/*******************************************************************************
  ����̨����
*******************************************************************************/

/**
 * \addtogroup  grp_aw_plfm_vdebug_usrcfg
 * @{
 */

/** \brief ����̨����ʱ���Ƿ���ʾ��ӭ��ʶ��0-����ʾ 1-��ʾ */
#define AW_CFG_CONSOLE_SHOW_BANNER       1

/** \brief ����̨���ں� */
#define AW_CFG_CONSOLE_COMID             COM0

/** \brief ����̨������ */
#define AW_CFG_CONSOLE_BAUD_RATE         115200

/** @} grp_aw_plfm_vdebug_usrcfg */

/*******************************************************************************
  LPC17XX GPIO ����
*******************************************************************************/
/**
 * \addtogroup  grp_aw_plfm_LPC17XX_nvic_usrcfg
 * @{
 */

/**
 * \brief ����ISR�ж���Ϣ����
 *
 * ����LPC17XX��Դ���ޣ�Ϊ�˱��ⲻ��Ҫ���ڴ����ģ��û����Խ��˲�������Ϊʵ����Ҫ
 * ���Ӵ����������ŵĸ��������磬ֻ��3�����Żᱻ���Ӵ�����������Խ��˲�������Ϊ3��
 *
 * \attention LCP177x_8x ��40���жϣ���ˣ��˲��������ЧֵΪ40
 */
#define AW_CFG_ARMCM_NVIC_ISRINFO_COUNT    20

/** @} grp_aw_plfm_LPC17XX_nvic_usrcfg */

/*******************************************************************************
  ���ж˿�����
*******************************************************************************/

/**
 * \addtogroup grp_aw_plfm_serial_common_usrcfg
 * @{
 */

/**
 * \brief ϵͳ���ж˿ڸ���
 *
 * ��ǰ֧�ֵ����˿ڸ���Ϊ5����Ӧ�ø���ʵ�ʵ�Ӳ�������޸ġ�
 * ���õĶ˿ڸ�����Ӧ�ó���5����
 */
#define AW_CFG_NUM_COM      		5

/**
 * \name ���ж˿ڵ��շ������С����
 * \brief ���õĴ��ж˿ڣ���ų���AW_CFG_NUM_COM�������ò������á�
 * @{
 */

#define AW_CFG_COM0_TX_BUF_SIZE     128 /**< \brief COM0 ���ͻ����С */
#define AW_CFG_COM0_RX_BUF_SIZE     128 /**< \brief COM0 ���ջ����С */

#define AW_CFG_COM1_TX_BUF_SIZE     128 /**< \brief COM1 ���ͻ����С */
#define AW_CFG_COM1_RX_BUF_SIZE     128 /**< \brief COM1 ���ջ����С */

#define AW_CFG_COM2_TX_BUF_SIZE     128 /**< \brief COM2 ���ͻ����С */
#define AW_CFG_COM2_RX_BUF_SIZE     128 /**< \brief COM2 ���ջ����С */

#define AW_CFG_COM3_TX_BUF_SIZE     128 /**< \brief COM3 ���ͻ����С */
#define AW_CFG_COM3_RX_BUF_SIZE     128 /**< \brief COM3 ���ջ����С */

#define AW_CFG_COM4_TX_BUF_SIZE     128 /**< \brief COM4 ���ͻ����С */
#define AW_CFG_COM4_RX_BUF_SIZE     128 /**< \brief COM4 ���ջ����С */

#define AW_CFG_COM5_TX_BUF_SIZE     128 /**< \brief COM5 ���ͻ����С */
#define AW_CFG_COM5_RX_BUF_SIZE     128 /**< \brief COM5 ���ջ����С */

#define AW_CFG_COM6_TX_BUF_SIZE     128 /**< \brief COM6 ���ͻ����С */
#define AW_CFG_COM6_RX_BUF_SIZE     128 /**< \brief COM6 ���ջ����С */

#define AW_CFG_COM7_TX_BUF_SIZE     128 /**< \brief COM7 ���ͻ����С */
#define AW_CFG_COM7_RX_BUF_SIZE     128 /**< \brief COM7 ���ջ����С */

#define AW_CFG_COM8_TX_BUF_SIZE     128 /**< \brief COM8 ���ͻ����С */
#define AW_CFG_COM8_RX_BUF_SIZE     128 /**< \brief COM8 ���ջ����С */

#define AW_CFG_COM9_TX_BUF_SIZE     128 /**< \brief COM9 ���ͻ����С */
#define AW_CFG_COM9_RX_BUF_SIZE     128 /**< \brief COM9 ���ջ����С */

/** @} */

/** @} grp_aw_plfm_serial_common_usrcfg */

/*******************************************************************************
  ��ԴID
*******************************************************************************/

/* RTC ID ���� */
#define LPC17XX_RTC_ID 0

/* PWM ����ID���� */
#define LPC17XX_PWM_UNIT_ID            1
#define LPC17XX_PWM_CAP_UNIT_ID        1

#define LPC17XX_MCPWM_UNIT_ID          0
#define LPC17XX_MCPWM_CAP_UNIT_ID      0

/* ��ʱ�� ����ID���� */
#define LPC17XX_TIMER0_TIMING_UNIT_ID  0
#define LPC17XX_TIMER0_CAP_UNIT_ID     0

#define LPC17XX_TIMER1_TIMING_UNIT_ID  1
#define LPC17XX_TIMER1_CAP_UNIT_ID     1

#define LPC17XX_TIMER2_TIMING_UNIT_ID  2
#define LPC17XX_TIMER2_CAP_UNIT_ID     2

#define LPC17XX_TIMER3_TIMING_UNIT_ID  3
#define LPC17XX_TIMER3_CAP_UNIT_ID     3

#define LPC17XX_RIT_UNIT_ID            7

/* SPI ����ID���� */
#define LPC17XX_SSP0_BUSID             0
#define LPC17XX_SSP1_BUSID             1
#define LPC17XX_SSP2_BUSID             2
#define GPIO_SPI0_BUSID                3

/* I2C ����ID����  */
#define LPC17XX_I2C0_BUSID             0
#define LPC17XX_I2C1_BUSID             1
#define LPC17XX_I2C2_BUSID             2

/* ���� ID ���� */
#define LPC17XX_UART0_COMID            COM0
#define LPC17XX_UART1_COMID            COM1
#define LPC17XX_UART2_COMID            COM2
#define LPC17XX_UART3_COMID            COM3
#define LPC17XX_UART4_COMID            COM4

/* CAN ID ���� */
#define LPC17XX_CAN1_UNIT_ID           0
#define LPC17XX_CAN2_UNIT_ID           1

/* MII BUS ID ����  */
#define LPC17XX_MII0_BUSID             0

/** @} grp_aw_plfm_params_srcid */

/*******************************************************************************
  �Զ�����
*******************************************************************************/
/** \cond */

/* ����̨������� UARTx */
#ifdef AW_COM_CONSOLE
#if AW_CFG_CONSOLE_COMID == COM0
#define AW_DEV_LPC17XX_UART0        /* LPC17XX UART0 */
#endif
#endif  /* AW_COM_CONSOLE */

#ifdef AW_DEV_LED_GPIO
#define AW_COM_AWBL_LED
#define AW_DRV_AWBL_GPIO_LED
#endif

/* I2C0 ������ LPC17xx_I2C ���� */
#if defined(AW_DEV_LPC17XX_I2C_0) || \
	defined(AW_DEV_LPC17XX_I2C_1) || \
	defined(AW_DEV_LPC17XX_I2C_2)
#define AW_DRV_AWBL_LPC17XX_I2C     /* AWBus-lite LPC17XX I2C ���� */
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

/* LPC17XX_UART ������ UART ����*/
#if defined(AW_DEV_LPC17XX_UART0) || \
	defined(AW_DEV_LPC17XX_UART1) || \
	defined(AW_DEV_LPC17XX_UART2) || \
	defined(AW_DEV_LPC17XX_UART3) || \
	defined(AW_DEV_LPC17XX_UART4)
#define AW_DRV_AWBL_LPC17XX_UART     /* AWBus-lite  UART ���� */
#endif  /* AW_DEV_LPC17XX_UART */

/* TIMER ������ LPC17XX_TIMER ���� */
#if defined(AW_DEV_LPC17XX_TIMER0_TIMING) || \
    defined(AW_DEV_LPC17XX_TIMER1_TIMING) || \
    defined(AW_DEV_LPC17XX_TIMER2_TIMING) || \
    defined(AW_DEV_LPC17XX_TIMER3_TIMING)
#define AW_DRV_AWBL_LPC17XX_TIMER32 /* AWBus-lite LPC17XX ��ʱ������ */
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

/* LPC17xx_ADC ���������� ADC ͨ�ÿ� */
#ifdef AW_DEV_LPC17XX_ADC
#define AW_COM_AWBL_ADC       /* AWBus-lite ADC ͨ�ÿ� */
#endif  /* AW_DRV_AWBL_LPC17XX_ADC */

/* LPC17xx_DAC ���������� DAC ͨ�ÿ� */
#ifdef AW_DEV_LPC17XX_DAC
#define AW_COM_AWBL_DAC       /* AWBus-lite DAC ͨ�ÿ� */
#endif  /* AW_DRV_AWBL_LPC17XX_DAC */

/* LPC17xx_RTC ���������� RTC ͨ�ÿ� */
#ifdef AW_DEV_LPC17XX_RTC
#define AW_COM_AWBL_RTC    /* AWBus-lite RTC ���ߺ������ */
#endif  /* AW_DEV_LPC17XX_RTC */

/* LPC17xx_WDT ���������� WDT ͨ�ÿ� */
#if defined(AW_DEV_LPC17XX_WDT) || defined(AW_DEV_GPIO_WDT)
#define AW_COM_AWBL_WDT    /* AWBus-lite WDT ���ߺ������ */
#endif  /* AW_DEV_LPC17XX_WDT */

/* LPC17xx_I2C ���������� I2C ͨ�ÿ� */
#ifdef AW_DRV_AWBL_LPC17XX_I2C
#define AW_COM_AWBL_I2CBUS    /* AWBus-lite I2C ���ߺ������ */
#endif  /* AW_DRV_AWBL_LPC17XX_I2C */

/* LPC17xx_UART ���������� I2C ͨ�ÿ� */
#ifdef AW_DRV_AWBL_LPC17XX_UART
#define AW_COM_AWBL_SERIAL    /* AWBus-lite UART ���ߺ������ */
#endif  /* AW_DRV_AWBL_LPC17XX_UART */

/* LPC17xx_SPI ���������� SPI ͨ�ÿ� */
#ifdef AW_DRV_AWBL_LPC17XX_SPI
#define AW_COM_AWBL_SPIBUS    /* AWBus-lite SPI ���ߺ������ */
#endif  /* AW_DRV_AWBL_LPC17XX_SSP */

/* SDIO���������� LPC17XX_SDIO�豸 */
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
