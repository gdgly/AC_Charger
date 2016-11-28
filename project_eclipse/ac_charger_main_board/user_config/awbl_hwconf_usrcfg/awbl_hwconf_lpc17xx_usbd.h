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
 DMA������������Ϣ
*******************************************************************************/
#ifdef AW_DEV_LPC17XX_USBD

#include "driver/usb/awbl_lpc17xx_usbd.h"
#include "ametal.h"

#define __DEV_CLK_EN        (1 << 1)
#define __I2C_CLK_EN        (1 << 2)
#define __PORTSEL_CLK_EN    (1 << 3)
#define __OTG_CLK_EN        (1 << 3)
#define __AHB_CLK_EN        (1 << 4)

/* USBD��ؼĴ���  */
#ifdef AW_LPC177X_8X
/** \brief USBD�豸��ַ  */
#define __USBD_REGADDR_BASE   (0x2008C200UL)

/** \brief USB�˿�ѡ��Ĵ���  */
#define __USB_PORTSEL_REG    (*(volatile uint32_t *)(0x2008C110))

/** \brief USBʱ�ӿ��ƼĴ��� */
#define __USB_CLK_CTRL_REG   (*(volatile uint32_t *)(0x2008CFF4))

/** \brief USBʱ��״̬�Ĵ��� */
#define __USB_CLK_ST_REG     (*(volatile uint32_t *)(0x2008CFF8))

#else
#define __USBD_REGADDR_BASE   (0x5000C200UL)

/** \brief USBʱ�ӿ��ƼĴ��� */
#define __USB_CLK_CTRL_REG   (*(volatile uint32_t *)(0x5000CFF4))

/** \brief USBʱ��״̬�Ĵ��� */
#define __USB_CLK_ST_REG     (*(volatile uint32_t *)(0x5000CFF8))

#endif

/** \brief DMA��������Ŀ  */
#define __USBD_DMA_DESC_NUM  8

/** \brief ʹ�õ�����˵����  */
#define __USED_EP_NUM        10

/**
 * \brief USB Deviceƽ̨��ʼ��
 */
void amhw_plfm_usbd_init (void)
{
#ifdef AW_LPC177X_8X

    uint32_t clkctrl = __DEV_CLK_EN     | __I2C_CLK_EN | \
                       __PORTSEL_CLK_EN | __AHB_CLK_EN;

    /* ʹ��PLL1��ΪUSBʱ��, USBʱ�Ӳ���Ƶ */
    amhw_clock_usbclk_set(AMHW_CLOCK_USBSRC_PLL1, 1);

    /* PLL1���48Mʱ��  */
    amhw_pll1_config(48000000);

    /* ��SmartM31788Ӳ������й�  */
    am_gpio_pin_cfg(PIO2_0, AM_GPIO_OUTPUT_INIT_LOW);

    amhw_power_periph_up(AMHW_POWER_USB);

    __USB_CLK_CTRL_REG = clkctrl;

    while ((__USB_CLK_ST_REG & clkctrl) != clkctrl);

    __USB_PORTSEL_REG &= ~0x03;   /* USB�˿�ѡ��0 */

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

    /* PLLʱ������ 48MHz */
    amhw_pll1_config();

    /* USBʹ�� */
    amhw_power_periph_up(AMHW_POWER_USB);

    /* ʹ��USB�豸ʱ�� */
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
 * \brief USB Deviceƽ̨ȥ��ʼ����
 */
void amhw_plfm_usbd_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_USB);
}

/* ����DMA RAM (����128�ֽڶ���)�������Ƭ��RAM  */
static uint32_t g_udca[32] __attribute__((aligned(128))) \
                           __attribute__((section(".ahb_bss")));

/* ����DMA�������������Ƭ��RAM   */
struct awbl_lpc17xx_usbd_dma_desc g_usbd_dma_desc[__USBD_DMA_DESC_NUM] \
    __attribute__((aligned(4))) __attribute__((section(".ahb_bss")));

/* �豸��Ϣ */
aw_local aw_const struct awbl_lpc17xx_usbd_info __g_lpc17xx_usbd_info = {
    {
        "/dev/usbd0",
        AWBL_USBD_CFG_SELF_POWERED
    },                                 /* USB�豸��Ϣ               */
    __USBD_REGADDR_BASE,               /* USB�豸�Ĵ�������ַ         */
    INUM_USB,                          /* USB�жϱ��         */
    (void *)&g_udca[0],                /* USB�豸ͨ����       */
    __USED_EP_NUM,                     /* ʹ�õ�����˵���       */
    g_usbd_dma_desc,                   /* DMA������         */
    __USBD_DMA_DESC_NUM,               /* DMA��������Ŀ         */
    amhw_plfm_usbd_init                /* USB�豸 ƽ̨��س�ʼ������ */
};

/* �豸ʵ���ڴ澲̬���� */
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
