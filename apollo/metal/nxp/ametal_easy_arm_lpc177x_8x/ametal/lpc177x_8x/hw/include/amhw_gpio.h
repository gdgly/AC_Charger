/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief GPIO Ӳ�������ӿ�
 * 
 * 1. GPIO �����ܹ�ͨ���������Ϊ���������
 * 2. ����GPIO ����Ĭ��Ϊ�������룬�ڸ�λʱ�жϽ��ܣ�
 * 3. ���żĴ����������ŵ������û���ͬʱ���á�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-04-23  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_GPIO_H
#define __AMHW_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 

/** 
 * \addtogroup amhw_if_gpio 
 * \copydoc amhw_gpio.h
 * @{
 */

/** 
 * \name GPIO �˿ڱ��
 * @{
 */

#define AMHW_GPIO_PORT_0        0        /**< \brief �˿� 0  */ 
#define AMHW_GPIO_PORT_1        1        /**< \brief �˿� 1  */
#define AMHW_GPIO_PORT_2        2        /**< \brief �˿� 2  */ 
#define AMHW_GPIO_PORT_3        3        /**< \brief �˿� 3  */
#define AMHW_GPIO_PORT_4        4        /**< \brief �˿� 4  */ 

/** @} */

/**
 * \name GPIO ���ŵ�ƽ
 * @{
 */
 
#define AMHW_GPIO_LEVEL_LOW     0        /**< \brief �͵�ƽ */
#define AMHW_GPIO_LEVEL_HIGH    1        /**< \brief �ߵ�ƽ */

/** @} */

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \brief GPIO �Ĵ�����ṹ��
 */
typedef struct amhw_gpio {
  union {
    __IO uint32_t fiodir;     /**< \brief ����GPIO�˿ڷ�����ƼĴ���                   */
    struct {
      __IO uint16_t fiodirl;  /**< \brief ����GPIO�˿�x������ƵͰ��ּĴ���  */
      __IO uint16_t fiodirh;  /**< \brief ����GPIO�˿�x������Ƹ߰��ּĴ���  */
    };
    struct {
      __IO uint8_t  fiodir0;  /**< \brief ����GPIO�˿�x������ƼĴ���0     */
      __IO uint8_t  fiodir1;  /**< \brief ����GPIO�˿�x������ƼĴ���1     */
      __IO uint8_t  fiodir2;  /**< \brief ����GPIO�˿�x������ƼĴ���2     */
      __IO uint8_t  fiodir3;  /**< \brief ����GPIO�˿�x������ƼĴ���3     */
    };
  };
  uint32_t reserved0[3];      /**< \brief ����                                                                           */
  union {
    __IO uint32_t fiomask;    /**< \brief ���ٶ˿����μĴ���                                         */
    struct {
      __IO uint16_t fiomaskl; /**< \brief ����GPIO�˿�x���εͰ��ּĴ���              */
      __IO uint16_t fiomaskh; /**< \brief ����GPIO�˿�x���θ߰��ּĴ���              */
    };
    struct {
      __IO uint8_t  fiomask0; /**< \brief ����GPIO�˿�x���μĴ���0          */
      __IO uint8_t  fiomask1; /**< \brief ����GPIO�˿�x���μĴ���1          */
      __IO uint8_t  fiomask2; /**< \brief ����GPIO�˿�x���μĴ���2          */
      __IO uint8_t  fiomask3; /**< \brief ����GPIO�˿�x���μĴ���3          */
    };
  };
  union {
    __IO uint32_t fiopin;    /**< \brief ���ٶ˿�����ֵ�Ĵ���  */
    struct {
      __IO uint16_t fiopinl; /**< \brief ����GPIO�˿�x����ֵ�Ͱ��ּĴ���     */
      __IO uint16_t fiopinh; /**< \brief ����GPIO�˿�x����ֵ�߰��ּĴ���     */
    };
    struct {
      __IO uint8_t  fiopin0; /**< \brief ����GPIO�˿�x����ֵ�Ĵ���0       */
      __IO uint8_t  fiopin1; /**< \brief ����GPIO�˿�x����ֵ�Ĵ���1       */
      __IO uint8_t  fiopin2; /**< \brief ����GPIO�˿�x����ֵ�Ĵ���2       */
      __IO uint8_t  fiopin3; /**< \brief ����GPIO�˿�x����ֵ�Ĵ���3       */
    };
  };
  union {
    __IO uint32_t fioset;    /**< \brief ���ٶ˿������λ�Ĵ���                             */
    struct {
      __IO uint16_t fiosetl; /**< \brief ����GPIO�˿�x������õͰ��ּĴ���  */
      __IO uint16_t fioseth; /**< \brief ����GPIO�˿�x������ø߰��ּĴ���  */
    };
    struct {
      __IO uint8_t  fioset0; /**< \brief ����GPIO�˿�x������üĴ���0     */
      __IO uint8_t  fioset1; /**< \brief ����GPIO�˿�x������üĴ���1     */
      __IO uint8_t  fioset2; /**< \brief ����GPIO�˿�x������üĴ���2     */
      __IO uint8_t  fioset3; /**< \brief ����GPIO�˿�x������üĴ���3     */
    };
  };
  union {
    __O  uint32_t fioclr;    /**< \brief ���ٶ˿��������Ĵ���                              */
    struct {
      __O  uint16_t fioclrl; /**< \brief ����GPIO�˿�x�������Ͱ��ּĴ���  */
      __O  uint16_t fioclrh; /**< \brief ����GPIO�˿�x�������߰��ּĴ���  */
    };
    struct {
      __O  uint8_t  fioclr0; /**< \brief ����GPIO�˿�x�������Ĵ���0     */
      __O  uint8_t  fioclr1; /**< \brief ����GPIO�˿�x�������Ĵ���1     */
      __O  uint8_t  fioclr2; /**< \brief ����GPIO�˿�x�������Ĵ���2     */
      __O  uint8_t  fioclr3; /**< \brief ����GPIO�˿�x�������Ĵ���3     */
    };
  };
} amhw_gpio_t;

/**
 * \brief ����GPIO���ŷ���Ϊ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_num   : �˿ڵ����ű�ţ�0 ~ 31
 *
 * \return    ��
 */
am_static_inline 
void amhw_gpio_pin_dir_output (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    p_hw_gpio->fiodir |= (1UL << (pin_num & 0x1F));
}

/**
 * \brief ����GPIO���ŷ���Ϊ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_num   : �˿ڵ����ű�ţ�0 ~ 31
 *
 * \return    ��
 */
am_static_inline 
void amhw_gpio_pin_dir_input (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    p_hw_gpio->fiodir  &= ~(1UL << (pin_num & 0x1F));
}

/**
 * \brief ��ȡָ�����ŵķ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_num   : �˿ڵ����ű�ţ�0 ~ 31
 *
 * \retval  0  : ����
 * \retval  1  : ���
 */
am_static_inline
int amhw_gpio_pin_dir_get (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    return (((p_hw_gpio->fiodir & 
             (1UL << (pin_num & 0x1F))) != 0) ? 1 : 0);
}

/**
 * \brief ����GPIO�˿ڵ�����ֵ�����ڶ˿ڵĶ���д
 *
 *  ��ֵӰ��Զ˿ڵĶ���д(��λ������).д0ʱ��ʹ�ܶ���д��д1ʱ��д���λ��ֵ�����ԣ���ʱʼ��Ϊ0.
 *
 * \param[in] p_hw_gpio  : ָ��GPIO�Ĵ������ָ��
 * \param[in] mask_value : ����ֵ�������ڶ���д
 * 
 * \return    ��
 */
am_static_inline 
void amhw_gpio_mask_set (amhw_gpio_t *p_hw_gpio, 
                         uint32_t     mask_value)
{
    p_hw_gpio->fiomask = mask_value;
}

/**
 * \brief ��ȡGPIOָ���˿ڵ�����ֵ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port      : �˿ڱ�ţ�ֵΪ AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 *
 * \return    �˿ڵ�����ֵ
 */
am_static_inline 
uint32_t amhw_gpio_mask_get (amhw_gpio_t *p_hw_gpio, int port)
{
    return p_hw_gpio->fiomask;
}

/**
 * \brief ��ȡ���ŵĵ�ƽ״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_num   : �˿ڵ����ű�ţ�0 ~ 31
 *
 * \retval  0  : �͵�ƽ
 * \retval  1  : �ߵ�ƽ
 */
am_static_inline 
int amhw_gpio_pin_get (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    return (((p_hw_gpio->fiopin & 
             (1UL << (pin_num & 0x1F))) != 0) ? 1 : 0);
}

/**
 * \brief ����ָ���˿ڵ�����GPIO���ŵ�״̬���������йأ�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] value     : �����ڸö˿ڵ�valueֵ
 *
 * \return ��
 */
am_static_inline 
void amhw_gpio_port_set (amhw_gpio_t *p_hw_gpio, uint32_t value)
{
    p_hw_gpio->fiopin = value;
}

/**
 * \brief ��ȡָ���˿ڵ�����GPIO���ŵ�״̬���������йأ�
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \return �˿ڵ�����״̬
 */
am_static_inline 
uint32_t amhw_gpio_port_get (amhw_gpio_t *p_hw_gpio)
{
    return p_hw_gpio->fiopin;
}

/**
 * \brief ����GPIO��������ߵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_num   : �˿ڵ����ű�ţ�0 ~ 31
 *
 * \return ��
 *
 * \note �ù��ܽ�����������Ϊ���������
 */
am_static_inline 
void amhw_gpio_pin_out_high (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    p_hw_gpio->fioset = (1UL << (pin_num & 0x1F));
}

/**
 * \brief ����GPIO��������͵�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_num   : �˿ڵ����ű�ţ�0 ~ 31
 *
 * \return    ��
 *
 * \note �ù��ܽ�����������Ϊ���������
 */
am_static_inline 
void amhw_gpio_pin_out_low (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    p_hw_gpio->fioclr = (1UL << (pin_num & 0x1F));
}

/**
 * \brief ��תGPIO������ŵĵ�ƽ״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin_num   : �˿ڵ����ű�ţ�0 ~ 31
 *
 * \return ��
 *
 * \note �ù��ܽ�����������Ϊ���������
 */
am_static_inline 
void amhw_gpio_pin_toggle (amhw_gpio_t *p_hw_gpio, int pin_num)
{
    if (amhw_gpio_pin_get(p_hw_gpio,pin_num) == 0) {
        amhw_gpio_pin_out_high(p_hw_gpio,pin_num);
    } else {
        amhw_gpio_pin_out_low(p_hw_gpio,pin_num);
    }
}

/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/**
 * @} amhw_if_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_GPIO_H */

/* end of file */
