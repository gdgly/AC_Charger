/*******************************************************************************
*                                 AnyWhere
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
  LPC5410x GPIO ������Ϣ  
*******************************************************************************/

#ifdef AW_DEV_LPC17XX_GPIO

#include "apollo.h"
#include "awbl_gpio.h"
#include "lpc177x_8x_pin.h"

#include "driver/gpio/awbl_ametal_gpio.h"
#include "amdr_gpio.h"
#include "am_gpio.h"
#include "ametal.h"

/**
 * \brief ����100�ŵķ�װ��PIO0 + PIO2 = 28 + 14 = 42,�����ܽ��ж���ĿΪ42��
 * ����80�ŵķ�װ��PIO0 + PIO2 = 19 + 11 = 30,�����ܽ��ж���ĿΪ30��Ϊ��ʡ
 * �ռ䣬���Խ���ֵ����Ϊʵ���õ��Ĺܽ��ж���Ŀ����10�����Ҳ�Ҫ��������ֵ��
 */
#define GPIO_INT_COUNT    64

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct amdr_gpio_trigger_info g_gpio_triginfos[GPIO_INT_COUNT];

/** \brief GPIO�豸��Ϣ */
const amdr_gpio_devinfo_t g_gpio_devinfo = {

    AMHW_GPIO_BASE,    /**< \brief GPIO�Ļ���ַ                  */
    AMHW_PINCON,       /**< \brief ָ��Pin connect�Ĵ������ָ��  */
    AMHW_GPIOINT,      /**< \brief ָ�������жϼĴ������ָ��     */

    INUM_GPIO,        /**< \brief GPIO�жϺ�             */

    GPIO_INT_COUNT,    /**< \brief ʹ�õ��Ĺܽ��ж���Ŀ          */
    
    g_gpio_triginfos   /**< \brief ���Ŵ�����Ϣ�ڴ�              */
};

/** \brief GPIO�豸ʵ�� */
amdr_gpio_dev_t g_gpio_dev;

/** \brief GPIOƽ̨��ʼ�� */
void amhw_plfm_gpio_init (void)
{
    /* GPIO�ϵ� */
    amhw_power_periph_up(AMHW_POWER_GPIO);
}

/** \brief GPIOƽ̨ȥ��ʼ�� */
void amhw_plfm_gpio_deinit (void)
{
    /* GPIO�رյ�Դ */
    amhw_power_periph_down(AMHW_POWER_GPIO);
}

/** \brief GPIO �豸��Ϣ */
aw_local struct awbl_ametal_gpio_param __g_lpc17xx_gpio_param = {
    &g_gpio_dev,
    &g_gpio_devinfo,
    
    {
        PIO0_0,            /**< \brief ֧�ֵ���С���ű��     */
        PIO5_4,           /**< \brief ֧�ֵ�������ű��     */
    },
    
    {
        INUM_PIO0_0,       /**< \brief ֧�ֵ���С�����жϱ�� */
        INUM_PIO5_4       /**< \brief ֧�ֵ���С�����жϱ�� */
    },
    
    (pfunc_gpio_init_t)(&amdr_gpio_init),
    &amhw_plfm_gpio_init
};

/** \brief GPIO �豸ʵ���ڴ澲̬���� */
awbl_ametal_gpio_dev_t __g_ametal_gpio_dev;


#define AWBL_HWCONF_LPC17XX_GPIO    \
    {                               \
        AWBL_AMETAL_GPIO_NAME,      \
        0,                          \
        AWBL_BUSID_PLB,             \
        0,                          \
        (struct awbl_dev *)&__g_ametal_gpio_dev,   \
        &__g_lpc17xx_gpio_param    \
    },

#else

#define  AWBL_HWCONF_LPC17XX_GPIO
 
#endif  /* AW_DRV_AWBL_LPC17XX_GPIO */

/* end of file */

