/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 外设内存映射地址宏定义和外设定义
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-09-02  cod, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC177X_8X_H
#define __AMHW_LPC177X_8X_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * =======================================================================================================
 * ---------- Interrupt Number Definition ----------------------------------------------------------------
 * =======================================================================================================
 */

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers *********************************************************/
    NonMaskableInt_IRQn      = -14,      /*!< 2 Non Maskable Interrupt                         */
    MemoryManagement_IRQn    = -12,      /*!< 4 Cortex-M3 Memory Management Interrupt          */
    BusFault_IRQn            = -11,      /*!< 5 Cortex-M3 Bus Fault Interrupt                  */
    UsageFault_IRQn          = -10,      /*!< 6 Cortex-M3 Usage Fault Interrupt                */
    SVCall_IRQn              = -5,       /*!< 11 Cortex-M3 SV Call Interrupt                   */
    DebugMonitor_IRQn        = -4,       /*!< 12 Cortex-M3 Debug Monitor Interrupt             */
    PendSV_IRQn              = -2,       /*!< 14 Cortex-M3 Pend SV Interrupt                   */
    SysTick_IRQn             = -1,       /*!< 15 Cortex-M3 System Tick Interrupt               */

/******  LPC177x_8x Specific Interrupt Numbers **********************************************************/
    WDT_IRQn                 = 0,        /*!< Watchdog Timer Interrupt                         */
    TIMER0_IRQn              = 1,        /*!< Timer0 Interrupt                                 */
    TIMER1_IRQn              = 2,        /*!< Timer1 Interrupt                                 */
    TIMER2_IRQn              = 3,        /*!< Timer2 Interrupt                                 */
    TIMER3_IRQn              = 4,        /*!< Timer3 Interrupt                                 */
    UART0_IRQn               = 5,        /*!< UART0 Interrupt                                  */
    UART1_IRQn               = 6,        /*!< UART1 Interrupt                                  */
    UART2_IRQn               = 7,        /*!< UART2 Interrupt                                  */
    UART3_IRQn               = 8,        /*!< UART3 Interrupt                                  */
    PWM1_IRQn                = 9,        /*!< PWM1 Interrupt                                   */
    I2C0_IRQn                = 10,       /*!< I2C0 Interrupt                                   */
    I2C1_IRQn                = 11,       /*!< I2C1 Interrupt                                   */
    I2C2_IRQn                = 12,       /*!< I2C2 Interrupt                                   */
    Reserved0_IRQn           = 13,       /*!< Reserved                                         */
    SSP0_IRQn                = 14,       /*!< SSP0 Interrupt                                   */
    SSP1_IRQn                = 15,       /*!< SSP1 Interrupt                                   */
    PLL0_IRQn                = 16,       /*!< PLL0 Lock (Main PLL) Interrupt                   */
    RTC_IRQn                 = 17,       /*!< Real Time Clock Interrupt                        */
    EINT0_IRQn               = 18,       /*!< External Interrupt 0 Interrupt                   */
    EINT1_IRQn               = 19,       /*!< External Interrupt 1 Interrupt                   */
    EINT2_IRQn               = 20,       /*!< External Interrupt 2 Interrupt                   */
    EINT3_IRQn               = 21,       /*!< External Interrupt 3 Interrupt                   */
    ADC_IRQn                 = 22,       /*!< A/D Converter Interrupt                          */
    BOD_IRQn                 = 23,       /*!< Brown-Out Detect Interrupt                       */
    USB_IRQn                 = 24,       /*!< USB Interrupt                                    */
    CAN_IRQn                 = 25,       /*!< CAN Interrupt                                    */
    DMA_IRQn                 = 26,       /*!< General Purpose DMA Interrupt                    */
    I2S_IRQn                 = 27,       /*!< I2S Interrupt                                    */
    ENET_IRQn                = 28,       /*!< Ethernet Interrupt                               */
    SDC_IRQn                 = 29,       /*!< SD/MMC card I/F Interrupt                        */
    MCPWM_IRQn               = 30,       /*!< Motor Control PWM Interrupt                      */
    QEI_IRQn                 = 31,       /*!< Quadrature Encoder Interface Interrupt           */
    PLL1_IRQn                = 32,       /*!< PLL1 Lock (USB PLL) Interrupt                    */
    USBActivity_IRQn         = 33,       /*!< USB Activity interrupt                             */
    CANActivity_IRQn         = 34,       /*!< CAN Activity interrupt                             */
    UART4_IRQn               = 35,       /*!< UART4 Interrupt                                  */
    SSP2_IRQn                = 36,       /*!< SSP2 Interrupt                                   */
    LCD_IRQn                 = 37,       /*!< LCD Interrupt                                    */
    GPIO_IRQn                = 38,       /*!< GPIO Interrupt                                   */
    PWM0_IRQn                = 39,       /*!< PWM0 Interrupt                                   */
    EEPROM_IRQn              = 40,       /*!< EEPROM Interrupt                                 */
} IRQn_Type;


/** 
 * \addtogroup amhw_if_lpc177x_8x
 * \copydoc amhw_lpc177x_8x.h
 * @{
 */

/**
 * \name Cortex-M3核处理器和外设配置
 * @{
 */
#define __MPU_PRESENT             1               /**< \brief 有MPU                          */
#define __NVIC_PRIO_BITS          5               /**< \brief 用于中断优先级的位数为5         */
#define __Vendor_SysTickConfig    0               /**< \brief 没有用到不同的Systick配置       */

#include "core_cm3.h"

/** @} */

/**
 * \name 基地址定义
 * @{
 */
 
#define AMHW_FLASH_BASE        (0x00000000UL)   /**< \brief FLASH的基地址           */
#define AMHW_RAM_BASE          (0x10000000UL)   /**< \brief RAM的基地址             */
#define AMHW_APB0_BASE         (0x40000000UL)   /**< \brief APB0的基地址            */
#define AMHW_APB1_BASE         (0x40080000UL)   /**< \brief APB1的基地址            */
#define AMHW_CM3_BASE          (0xE0000000UL)   /**< \brief CM3私有外设的基地址      */
#define AMHW_AHB_BASE          (0x20080000UL)   /**< \brief AHB的基地址             */

/** @} */

/**
 * \name FLASH的基地址定义
 * @{
 */

/** \brief EEPROM的基地址          */
#define AMHW_EEPROM_BASE  (AMHW_FLASH_BASE + 0x200080UL)

/** @} */

/**
 * \name CM3私有外设基地址定义
 * @{
 */
 
#define AMHW_NVIC_BASE     (0xE000E000UL + 0x100UL)  /**< \brief NVIC的基地址          */
#define AMHW_SYSTICK_BASE  (0xE000E000UL + 0x010UL)  /**< \brief SYSTICK的基地址   */

/** @} */


/**
 * \name APB0外设基地址定义
 * @{
 */

#define AMHW_WWDT_BASE       (AMHW_APB0_BASE + 0x00000)  /**< \brief WWDT的基地址            */
#define AMHW_TIM0_BASE       (AMHW_APB0_BASE + 0x04000)  /**< \brief TIM0的基地址           */
#define AMHW_TIM1_BASE       (AMHW_APB0_BASE + 0x08000)  /**< \brief TIM1的基地址           */
#define AMHW_UART0_BASE      (AMHW_APB0_BASE + 0x0C000)  /**< \brief UART0的基地址          */
#define AMHW_UART1_BASE      (AMHW_APB0_BASE + 0x10000)  /**< \brief UART1的基地址          */
#define AMHW_PWM1_BASE       (AMHW_APB0_BASE + 0x18000)  /**< \brief PWM1的基地址           */
#define AMHW_I2C0_BASE       (AMHW_APB0_BASE + 0x1C000)  /**< \brief I2C0的基地址           */
#define AMHW_RTC_BASE        (AMHW_APB0_BASE + 0x24000)  /**< \brief RTC的基地址            */
#define AMHW_GPIOINT_BASE    (AMHW_APB0_BASE + 0x28080)  /**< \brief GPIO INT的基地址       */
#define AMHW_PINCON_BASE     (AMHW_APB0_BASE + 0x2C000)  /**< \brief PIN Connect基地址      */
#define AMHW_SSP1_BASE       (AMHW_APB0_BASE + 0x30000)  /**< \brief SSP1基地址             */
#define AMHW_ADC_BASE        (AMHW_APB0_BASE + 0x34000)  /**< \brief ADC基地址              */
#define AMHW_CANAF_RAM_BASE  (AMHW_APB0_BASE + 0x38000)  /**< \brief CAN AF RAM 基地址      */
#define AMHW_CANAF_BASE      (AMHW_APB0_BASE + 0x3C000)  /**< \brief CAN AF基地址           */
#define AMHW_CANCR_BASE      (AMHW_APB0_BASE + 0x40000)  /**< \brief CAN Common 基地址      */
#define AMHW_CAN1_BASE       (AMHW_APB0_BASE + 0x44000)  /**< \brief CAN1 基地址            */
#define AMHW_CAN2_BASE       (AMHW_APB0_BASE + 0x48000)  /**< \brief CAN2 基地址            */
#define AMHW_I2C1_BASE       (AMHW_APB0_BASE + 0x5C000)  /**< \brief I2C1 基地址            */
#define AMHW_PWM0_BASE       (AMHW_APB0_BASE + 0x14000)  /**< \brief PWM0的基地址                 */

/** @} */


/**
 * \name APB1外设基地址定义
 * @{
 */
 
#define AMHW_SSP0_BASE     (AMHW_APB1_BASE + 0x08000)   /**< \brief SSP0 基地址            */
#define AMHW_DAC_BASE      (AMHW_APB1_BASE + 0x0C000)   /**< \brief DAC 基地址             */
#define AMHW_TIM2_BASE     (AMHW_APB1_BASE + 0x10000)   /**< \brief TIM2 基地址            */
#define AMHW_TIM3_BASE     (AMHW_APB1_BASE + 0x14000)   /**< \brief TIM3 基地址            */
#define AMHW_UART2_BASE    (AMHW_APB1_BASE + 0x18000)   /**< \brief UART2 基地址           */
#define AMHW_UART3_BASE    (AMHW_APB1_BASE + 0x1C000)   /**< \brief UART3 基地址           */
#define AMHW_I2C2_BASE     (AMHW_APB1_BASE + 0x20000)   /**< \brief I2C2 基地址            */
#define AMHW_I2S_BASE      (AMHW_APB1_BASE + 0x28000)   /**< \brief I2S 基地址             */
#define AMHW_MCPWM_BASE    (AMHW_APB1_BASE + 0x38000)   /**< \brief MCPWM 基地址           */
#define AMHW_QEI_BASE      (AMHW_APB1_BASE + 0x3C000)   /**< \brief QEI 基地址             */
#define AMHW_SYSCON_BASE   (AMHW_APB1_BASE + 0x7C000)   /**< \brief System Control 基地址  */
#define AMHW_UART4_BASE    (AMHW_APB1_BASE + 0x24000)   /**< \brief UART4 基地址           */
#define AMHW_SSP2_BASE     (AMHW_APB1_BASE + 0x2C000)   /**< \brief SSP2 基地址            */
#define AMHW_SDC_BASE      (AMHW_APB1_BASE + 0x40000)   /**< \brief SDC 基地址             */
/** @} */


/**
 * \name AHB外设基地址定义
 * @{
 */

#define AMHW_GPDMA_BASE  (AMHW_AHB_BASE  + 0x00000)   /**< \brief GPDMA 基地址              */
#define AMHW_EMAC_BASE   (AMHW_AHB_BASE  + 0x04000)   /**< \brief EMAC基地址       */
#define AMHW_LCD_BASE    (AMHW_AHB_BASE  + 0x08000)   /**< \brief LCD 基地址       */
#define AMHW_USB_BASE    (AMHW_AHB_BASE  + 0x0C000)   /**< \brief USB 基地址           */
#define AMHW_CRC_BASE    (AMHW_AHB_BASE  + 0x10000)   /**< \brief CRC 基地址           */
#define AMHW_GPIO_BASE   (AMHW_AHB_BASE  + 0x18000)   /**< \brief GPIO 基地址         */
#define AMHW_EMC_BASE    (AMHW_AHB_BASE  + 0x1C000)   /**< \brief EMC 基地址            */

/** @} */


/**
 * \name GPIO0 ~ 4 基地址定义
 * @{
 */
#define AMHW_GPIO0_BASE   (AMHW_GPIO_BASE + 0x18000)  /**< \brief GPIO0的基地址           */
#define AMHW_GPIO1_BASE   (AMHW_GPIO_BASE + 0x18020)  /**< \brief GPIO1的基地址           */
#define AMHW_GPIO2_BASE   (AMHW_GPIO_BASE + 0x18040)  /**< \brief GPIO2的基地址           */
#define AMHW_GPIO3_BASE   (AMHW_GPIO_BASE + 0x18060)  /**< \brief GPIO3的基地址           */
#define AMHW_GPIO4_BASE   (AMHW_GPIO_BASE + 0x18080)  /**< \brief GPIO4的基地址           */
#define AMHW_GPIO5_BASE   (AMHW_GPIO_BASE + 0x180A0)  /**< \brief GPIO5的基地址           */

/** @} */


/**
 * \name 外设定义
 * @{
 */
#define AMHW_INT       ((amhw_int_t       *)AMHW_NVIC_BASE)    /**< \brief  NVIC     */
#define AMHW_SYSTICK   ((amhw_systick_t   *)AMHW_SYSTICK_BASE) /**< \brief  SYSTICK  */
#define AMHW_SYSCON    ((amhw_syscon_t    *)AMHW_SYSCON_BASE)  /**< \brief SYSCON    */
#define AMHW_GPIO0     ((amhw_gpio_t      *)AMHW_GPIO0_BASE)   /**< \brief GPIO0     */
#define AMHW_GPIO1     ((amhw_gpio_t      *)AMHW_GPIO1_BASE)   /**< \brief GPIO1     */
#define AMHW_GPIO2     ((amhw_gpio_t      *)AMHW_GPIO2_BASE)   /**< \brief GPIO2     */
#define AMHW_GPIO3     ((amhw_gpio_t      *)AMHW_GPIO3_BASE)   /**< \brief GPIO3     */
#define AMHW_GPIO4     ((amhw_gpio_t      *)AMHW_GPIO4_BASE)   /**< \brief GPIO4     */
#define AMHW_GPIOINT   ((amhw_gpioint_t   *)AMHW_GPIOINT_BASE) /**< \brief GPIOINT   */
#define AMHW_PINCON    ((amhw_pincon_t    *)AMHW_PINCON_BASE)  /**< \brief IOCON     */
#define AMHW_WWDT      ((amhw_wwdt_t      *)AMHW_WWDT_BASE)    /**< \brief WWDT      */
#define AMHW_DAC       ((amhw_dac_t       *)AMHW_DAC_BASE)     /**< \brief DAC       */
#define AMHW_ADC       ((amhw_adc_t		  *)AMHW_ADC_BASE)     /**< \brief ADC       */
#define AMHW_I2C0      ((amhw_i2c_t		  *)AMHW_I2C0_BASE)    /**< \brief I2C0	   */
#define AMHW_I2C1      ((amhw_i2c_t		  *)AMHW_I2C1_BASE)    /**< \brief I2C1	   */
#define AMHW_I2C2      ((amhw_i2c_t		  *)AMHW_I2C2_BASE)    /**< \brief I2C2	   */
#define AMHW_MCPWM     ((amhw_mcpwm_t	  *)AMHW_MCPWM_BASE)   /**< \brief MCPWM	   */
#define AMHW_PWM1      ((amhw_pwm_t	      *)AMHW_PWM1_BASE)    /**< \brief PWM1	   */
#define AMHW_CANAF_RAM ((amhw_canaf_ram_t *)AMHW_CANAF_RAM_BASE) /**< \brief CANAF_RAM */
#define AMHW_CANAF     ((amhw_canaf_t     *)AMHW_CANAF_BASE) /**< \brief CANAF     */
#define AMHW_CANCR     ((amhw_cancr_t     *)AMHW_CANCR_BASE) /**< \brief CANCR	  */
#define AMHW_CAN1      ((amhw_can_t       *)AMHW_CAN1_BASE)  /**< \brief CAN1	  */
#define AMHW_CAN2      ((amhw_can_t       *)AMHW_CAN2_BASE)  /**< \brief CAN2	  */
#define AMHW_TIMER0    ((amhw_timer_t     *)AMHW_TIM0_BASE)  /**< \brief TIMER0    */
#define AMHW_TIMER1    ((amhw_timer_t     *)AMHW_TIM1_BASE)  /**< \brief TIMER1    */
#define AMHW_TIMER2    ((amhw_timer_t     *)AMHW_TIM2_BASE)  /**< \brief TIMER2    */
#define AMHW_TIMER3    ((amhw_timer_t     *)AMHW_TIM3_BASE)  /**< \brief TIMER3    */
#define AMHW_USART0    ((amhw_usart_t     *)AMHW_UART0_BASE) /**< \brief USART0 */
#define AMHW_USART1    ((amhw_usart_t     *)AMHW_UART1_BASE) /**< \brief USART1 */
#define AMHW_USART2    ((amhw_usart_t     *)AMHW_UART2_BASE) /**< \brief USART2 */
#define AMHW_USART3    ((amhw_usart_t     *)AMHW_UART3_BASE) /**< \brief USART3 */
#define AMHW_USART4    ((amhw_usart_t     *)AMHW_UART4_BASE) /**< \brief USART4 */
#define AMHW_RTC       ((amhw_rtc_t       *)AMHW_RTC_BASE)   /**< \brief RTC    */
#define AMHW_I2S       ((amhw_i2s_t       *)AMHW_I2S_BASE)   /**< \brief I2S	  */
#define AMHW_GPDMA     ((amhw_dma_t       *)AMHW_GPDMA_BASE) /**< \brief GPDMA  */
#define AMHW_SSP0      ((amhw_ssp_t       *)AMHW_SSP0_BASE)  /**< \brief SSP0	  */
#define AMHW_SSP1      ((amhw_ssp_t       *)AMHW_SSP1_BASE)  /**< \brief SSP1	  */
#define AMHW_SSP2      ((amhw_ssp_t       *)AMHW_SSP2_BASE)  /**< \brief SSP2    */
#define AMHW_PWM0      ((amhw_pwm_t       *)AMHW_PWM0_BASE)  /**< \brief PWM0       */
#define AMHW_EMC       ((amhw_emc_t       *)AMHW_EMC_BASE)   /**< \brief EMC    */
#define AMHW_CRC       ((amhw_crc_t       *)AMHW_CRC_BASE)   /**< \brief CRC    */
#define AMHW_EEPROM    ((amhw_eeprom_t    *)AMHW_EEPROM_BASE)/**< \brief EEPROM    */
#define AMHW_LCD       ((amhw_lcd_t       *)AMHW_LCD_BASE)   /**< \brief LCD    */
#define AMHW_EMAC      ((amhw_enet_t      *)AMHW_EMAC_BASE)  /**< \brief EMAC    */
#define AMHW_SDC       ((amhw_mci_t       *)AMHW_SDC_BASE)   /**< \brief SDC    */
#define AMHW_USBD      ((amhw_usbd_t      *)(AMHW_USB_BASE + 0x200))  /**< \brief USBD    */

#define AMHW_IAP_ENTRY_LOCATION   0x1FFF1FF1UL   /**< \brief ROM中IAP函数入口地址   */

/** @} */


/**
 * @} amhw_if_lpc177x_8x
 */

#ifdef __cplusplus
}
#endif


#endif  /* __AMHW_LPC177X_8X_H */

/* end of file */
