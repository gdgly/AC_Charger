/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
 DMA控制器配置信息
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_USBD

#include "driver/usb/awbl_lpc17xx_usbd.h"
#include "ametal.h"

#define __DEV_CLK_EN        (1 << 1)
#define __I2C_CLK_EN        (1 << 2)
#define __PORTSEL_CLK_EN    (1 << 3)
#define __OTG_CLK_EN        (1 << 3)
#define __AHB_CLK_EN        (1 << 4)

/* USBD相关寄存器  */
#ifdef AW_LPC177X_8X
/** \brief USBD设备基址  */
#define __USBD_REGADDR_BASE   (0x2008C200UL)

/** \brief USB端口选择寄存器  */
#define __USB_PORTSEL_REG    (*(volatile uint32_t *)(0x2008C110))

/** \brief USB时钟控制寄存器 */
#define __USB_CLK_CTRL_REG   (*(volatile uint32_t *)(0x2008CFF4))

/** \brief USB时钟状态寄存器 */
#define __USB_CLK_ST_REG     (*(volatile uint32_t *)(0x2008CFF8))

#else
#define __USBD_REGADDR_BASE   (0x5000C200UL)

/** \brief USB时钟控制寄存器 */
#define __USB_CLK_CTRL_REG   (*(volatile uint32_t *)(0x5000CFF4))

/** \brief USB时钟状态寄存器 */
#define __USB_CLK_ST_REG     (*(volatile uint32_t *)(0x5000CFF8))

#endif

/** \brief DMA描述符数目  */
#define __USBD_DMA_DESC_NUM  8

/** \brief 使用的物理端点个数  */
#define __USED_EP_NUM        10

/**
 * \brief USB Device平台初始化
 */
void amhw_plfm_usbd_init (void)
{
#ifdef AW_LPC177X_8X

    uint32_t clkctrl = __DEV_CLK_EN     | __I2C_CLK_EN | \
                       __PORTSEL_CLK_EN | __AHB_CLK_EN;

    /* 使用PLL1作为USB时钟, USB时钟不分频 */
    amhw_clock_usbclk_set(AMHW_CLOCK_USBSRC_PLL1, 1);

    /* PLL1输出48M时钟  */
    amhw_pll1_config(48000000);

    /* 跟SmartM31788硬件设计有关  */
    am_gpio_pin_cfg(PIO2_0, AM_GPIO_OUTPUT_INIT_LOW);

    amhw_power_periph_up(AMHW_POWER_USB);

    __USB_CLK_CTRL_REG = clkctrl;

    while ((__USB_CLK_ST_REG & clkctrl) != clkctrl);

    __USB_PORTSEL_REG &= ~0x03;   /* USB端口选择0 */

    __USB_CLK_CTRL_REG &= ~__PORTSEL_CLK_EN;

    am_gpio_pin_cfg(PIO0_29, PIO0_29_USB1_D_P);
    am_gpio_pin_cfg(PIO0_30, PIO0_30_USB1_D_N);

    am_gpio_pin_cfg(PIO1_18, PIO1_18_USB1_UP_LED);
    am_gpio_pin_cfg(PIO2_9,  PIO2_9_USB1_CONNECT);
    am_gpio_pin_cfg(PIO1_30, PIO1_30_VBUS);

    am_gpio_pin_cfg(PIO1_28, PIO1_28_USB1_SCL);
    am_gpio_pin_cfg(PIO1_29, PIO1_29_USB1_SDA);

#else

    uint32_t clkctrl = __DEV_CLK_EN | __AHB_CLK_EN;

    /* PLL时钟配置 48MHz */
    amhw_pll1_config();

    /* USB使能 */
    amhw_power_periph_up(AMHW_POWER_USB);

    /* 使能USB设备时钟 */
    __USB_CLK_CTRL_REG = clkctrl;
    while ((__USB_CLK_ST_REG & clkctrl) != clkctrl);

    am_gpio_pin_cfg(PIO0_29, PIO0_29_USB_D_P);
    am_gpio_pin_cfg(PIO0_30, PIO0_30_USB_D_N);
    am_gpio_pin_cfg(PIO1_18, PIO1_18_USB_UP_LED);
    am_gpio_pin_cfg(PIO1_30, PIO1_30_VBUS | PIO1_30_FLOAT);
    am_gpio_pin_cfg(PIO2_9,  PIO2_9_USB_CONNECT);
#endif
}

/**
 * \brief USB Device平台去初始化。
 */
void amhw_plfm_usbd_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_USB);
}

/* 开辟DMA RAM (必须128字节对齐)，存放在片上RAM  */
static uint32_t g_udca[32] __attribute__((aligned(128))) \
                           __attribute__((section(".ahb_bss")));

/* 定义DMA描述符，存放在片上RAM   */
struct awbl_lpc17xx_usbd_dma_desc g_usbd_dma_desc[__USBD_DMA_DESC_NUM] \
    __attribute__((aligned(4))) __attribute__((section(".ahb_bss")));

/* 设备信息 */
aw_local aw_const struct awbl_lpc17xx_usbd_info __g_lpc17xx_usbd_info = {
    {
        "/dev/usbd0",
        AWBL_USBD_CFG_SELF_POWERED
    },                                 /* USB设备信息               */
    __USBD_REGADDR_BASE,               /* USB设备寄存器基地址         */
    INUM_USB,                          /* USB中断编号         */
    (void *)&g_udca[0],                /* USB设备通信域       */
    __USED_EP_NUM,                     /* 使用的物理端点数       */
    g_usbd_dma_desc,                   /* DMA描述符         */
    __USBD_DMA_DESC_NUM,               /* DMA描述符数目         */
    amhw_plfm_usbd_init                /* USB设备 平台相关初始化函数 */
};

/* 设备实例内存静态分配 */
aw_local struct awbl_lpc17xx_usbd __g_lpc17xx_usbd_dev __attribute__((section(".ahb_bss")));

#define AWBL_HWCONF_LPC17XX_USBD                       \
    {                                                  \
        AWBL_LPC17XX_USBD_NAME,                        \
        0,                                             \
        AWBL_BUSID_PLB,                                \
        0,                                             \
        &__g_lpc17xx_usbd_dev.usbd.awdev,              \
        &__g_lpc17xx_usbd_info                         \
    },
#else

#define  AWBL_HWCONF_LPC17XX_USBD

#endif    /* AW_DEV_LPC17XX_DMA */

/* end of file */
