/*
 * awbl_imx283_rtc.h
 *
 *  Created on: 2014-6-3
 *      Author: may
 */

#ifndef AWBL_IMX283_RTC_H_
#define AWBL_IMX283_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/**
 * \addtogroup grp_awbl_drv_imx283_rtc
 * \copydetails awbl_imx283_rtc.h
 * @{
 */

/**
 * \defgroup  grp_awbl_drv_imx283_rtc ʵ�����
 * \todo
 *
 */

/**
 * \defgroup  grp_awbl_imx283_rtc_hwconf �豸����/����
 * \todo
 */

/** @} grp_awbl_drv_imx283_rtc */

#include "apollo.h"
#include "awbus_lite.h"
#include "awbl_rtc.h"
#include "aw_sem.h"

/* ���ƼĴ���  */
#define  IMX283_RTC_CTRL  			0x0000
#define  IMX283_RTC_CTRL_SET        0x0004
#define  IMX283_RTC_CTRL_CLR        0x0008
#define  __IMX283_RTC_CTRL_CLKGA    AW_BIT(30)
#define  __IMX283_RTC_CTRL_SFTRST   AW_BIT(31)
#define  __IMX283_RTC_CTRL_WATCHDOG	AW_BIT(4)

/* ״̬�Ĵ���   */
#define  IMX283_RTC_STAT            0x0010
#define  IMX283_RTC_STAT_START_BIT  8
#define  IMX283_RTC_STAT_BIT_LEN    8
#define  _READ_IMX283_RTC_STAT(regbase)  (AW_REG_BITS_GET32((regbase) + IMX283_RTC_STAT, \
	IMX283_RTC_STAT_START_BIT, IMX283_RTC_STAT_BIT_LEN))

/* �������  */
#define  IMX283_RTC_S_COUNTER                 0x0030
#define  _READ_IMX283_RTC_S_COUNTER(regbase)  AW_REG_READ32( (regbase) + IMX283_RTC_S_COUNTER)
#define  _CLR_IMX283_RTC_S_COUNTER(regbase)   AW_REG_WRITE32( (regbase) + IMX283_RTC_S_COUNTER, (0))

/* �����Ĵ���   */
#define  IMX283_RTC_ALARM                          0x0040
#define  _CLR_IMX283_RTC_ALARM(regbase)            AW_REG_WRITE32( (regbase) + IMX283_RTC_ALARM, (0))
#define  _WRITE_IMX283_RTC_ALARM(regbase, value)   AW_REG_WRITE32( (regbase) + IMX283_RTC_ALARM, (value))

/* ���Ź��Ĵ���  */
#define  IMX283_RTC_WATCHDOG		0x0050
#define  _WRITE_IMX283_RTC_WATCHDOG(regbase, value)	AW_REG_WRITE32( (regbase) + IMX283_RTC_WATCHDOG, (value))

/* ��λָ��λ��   */
#define  __IMX283_RTC_SET(reg_base, offset, bits)  \
	AW_REG_WRITE32( (reg_base) + (offset) + IMX283_RTC_CTRL_SET, bits)

/* ��λָ��λ��   */
#define  __IMX283_RTC_CLR(reg_base, offset, bits)  \
	AW_REG_WRITE32( (reg_base) + (offset) + IMX283_RTC_CTRL_CLR, bits)

/* REGISTER0�Ĵ���  */
#define  IMX283_RTC_REGISTER_0      0x0060
#define  IMX283_RTC_REGISTER_0_SET  0x0064
#define  IMX283_RTC_REGISTER_0_CLR  0x0068
#define  __IMX283_RTC_REGISTER_0_EXTERNAL_RESET   AW_BIT(21)
#define  __IMX283_RTC_REGISTER_0_THERMAL_RESET    AW_BIT(20)
#define  __IMX283_RTC_REGISTER_0_ENABLE_LRADC_PWRUP AW_BIT(18)
#define  __IMX283_RTC_REGISTER_0_AUTO_RESTART     AW_BIT(17)
#define  __IMX283_RTC_REGISTER_0_ALARM_WAKE       AW_BIT(7)
#define  __IMX283_RTC_REGISTER_0_XTAL32_FREQ      AW_BIT(6)
#define  __IMX283_RTC_REGISTER_0_XTAL32KHZ_PWRUP  AW_BIT(5)
#define  __IMX283_RTC_REGISTER_0_XTAL24MHZ_PWRUP  AW_BIT(4)
#define  __IMX283_RTC_REGISTER_0_WAKE_EN          AW_BIT(2)
#define  __IMX283_RTC_REGISTER_0_ALARM_WAKE_EN    AW_BIT(1)
#define  __IMX283_RTC_REGISTER_0_CLOCKSOURCE      AW_BIT(0)

/* ���ڴ洢�趨ʱ�������  */
#define  IMX283_RTC_REGISTER_2      0x0080
#define  _READ_IMX283_RTC_START_TIME(regbase)  AW_REG_READ32( (regbase) + IMX283_RTC_REGISTER_2)
#define  _WRITE_IMX283_RTC_START_TIME(regbase, value) AW_REG_WRITE32( (regbase) + IMX283_RTC_REGISTER_2, (value))


/** \brief imx283 rtc ������ */
#define AWBL_IMX283_RTC_NAME   "imx283RTC"

/**
 * \brief imx283RTC �豸��Ϣ
 */
// �����ϲ�������ײ�Ӳ����ƥ�䣬�����ϲ�ֻ��Ҫ�����豸�žͿ��Բ�����Ӧ���豸��
typedef struct awbl_imx283_rtc_devinfo {

    /** \brief RTC ����������Ϣ */
    struct awbl_rtc_servinfo  rtc_servinfo;

    /** \brief RTC �Ĵ����Ļ���ַ */
    uint32_t  base_addr;

} awbl_imx283_rtc_devinfo_t;

/**
 * \brief imx283RTC �豸ʵ��
 */
typedef struct awbl_imx283_rtc_dev {

    /** \brief �����豸 */
    struct awbl_dev super;   // ����Ҫ�ĳ�Ա

    /** \brief RTC ���� */
    struct awbl_rtc_service rtc_serv;

    /** \brief �豸�� */
    AW_MUTEX_DECL(devlock);
} awbl_imx283_rtc_dev_t;

/**
 * \brief imx283RTC driver register
 */
void awbl_imx283_rtc_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_IMX283_RTC_H_ */
