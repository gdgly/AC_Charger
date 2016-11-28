/******************************************************************************
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
 * \brief imx28 lradc driver head file
 *
 * \internal
 * \par Modification History
 * - 1.10 15-10-13  tee, modified according to new standard interface.
 * - 1.00 12-06-11  ehf, first implementation.
 * \endinternal
 */

#ifndef __AWBL_IMX28_LRADC_H
#define __AWBL_IMX28_LRADC_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_clk.h"
#include "awbl_adc.h"
#include "aw_spinlock.h"
#include "aw_isr_defer.h"
#include "awbus_lite.h"

/**
 * \name 寄存器相关宏定义
 *
 * 这些宏暂不能存放于.c文件中，由于文件：
 * apollo/components/awbus_lite/source/driver/input/touchscreen/awbl_imx28_ts.c
 * 中也有使用。
 *
 * @{
 */
#define __SETREG_ADDR           (4)
#define __CLRREG_ADDR           (8)
#define __TOGREG_ADDR           (12)

#define __LRADC_CYCLE_TIME_6MHZ_166NS   (0 << 8)
#define __LRADC_CYCLE_TIME_4MHZ_250NS   (1 << 8)
#define __LRADC_CYCLE_TIME_3MHZ_333NS   (2 << 8)
#define __LRADC_CYCLE_TIME_2MHZ_500NS   (3 << 8)

#define __LRADC_HIGH_TIME_42NS          (0 << 4)
#define __LRADC_HIGH_TIME_83NS          (1 << 4)
#define __LRADC_HIGH_TIME_125NS         (2 << 4)
#define __LRADC_HIGH_TIME_250NS         (3 << 4)



/* write register */
#define __IMX_LRADC_REG_WRITE(regbase, offset, data) \
    AW_REG_WRITE32( (regbase) + (offset), (data))

/* read register */
#define __IMX_LRADC_REG_READ(regbase, offset) \
    AW_REG_READ32( (regbase) + (offset))

/* set bits*/
#define __IMX_LRADC_REG_SET(regbase, offset, data) \
    AW_REG_WRITE32( (regbase) + (offset) +__SETREG_ADDR, data)

/* clear bits*/
#define __IMX_LRADC_REG_CLR(regbase, offset, data) \
    AW_REG_WRITE32( (regbase) + (offset) +__CLRREG_ADDR, data)

/* toggle bits*/
#define __IMX_LRADC_REG_TOG(regbase, offset, data) \
    AW_REG_WRITE32( (regbase) + (offset) +__TOGREG_ADDR, data)

/* clear interrupt flag */
#define __IMX_LRADC_CLR_INTFLAG(regbase,chmask) \
    __IMX_LRADC_REG_CLR(regbase, __IMX_LRADC_CTRL1, (chmask&__CTRL1_IRQ_ALL))

/* enable channel interrupt */
#define __IMX_LRADC_INT_EN(regbase, chmask) \
    __IMX_LRADC_REG_SET(regbase,__IMX_LRADC_CTRL1, (chmask&__CTRL1_IRQ_EN_ALL))

/* disable channel interrupt */
#define __IMX_LRADC_INT_DIS(regbase, chmask) \
    __IMX_LRADC_REG_CLR(regbase,__IMX_LRADC_CTRL1, (chmask&__CTRL1_IRQ_EN_ALL))

/* read adc channel value */
#define __IMX_LRADC_VAL_READ(regbase, ch) \
   __IMX_LRADC_REG_READ(regbase, (__IMX_LRADC_CH0+ch*16) )

#define __IMX_LRADC_IS_DONE(regbase, ch) \
    (__IMX_LRADC_REG_READ(regbase, __IMX_LRADC_STATUS)&((1<<16)<<ch) )

#define __DEV_GET_LRADC_INFO(p_dev) \
              ((struct awbl_imx28_lradc_devinfo *)AWBL_DEVINFO_GET(p_dev))

#define __DEV_GET_LRADC_DEV(p_dev) \
            ((struct awbl_imx28_lradc_dev *)p_dev)



#define __IMX_LRADC_CTRL0       (0x0000u)
#define __IMX_LRADC_CTRL1       (0x0010u)
#define __IMX_LRADC_CTRL2       (0x0020u)
#define __IMX_LRADC_CTRL3       (0x0030u)
#define __IMX_LRADC_STATUS      (0x0040u)
#define __IMX_LRADC_CH0         (0x0050u)
#define __IMX_LRADC_CH1         (0x0060u)
#define __IMX_LRADC_CH2         (0x0070u)
#define __IMX_LRADC_CH3         (0x0080u)
#define __IMX_LRADC_CH4         (0x0090u)
#define __IMX_LRADC_CH5         (0x00a0u)
#define __IMX_LRADC_CH6         (0x00b0u)
#define __IMX_LRADC_CH7         (0x00c0u)
#define __IMX_LRADC_DELAY0      (0x00d0u)
#define __IMX_LRADC_DELAY1      (0x00e0u)
#define __IMX_LRADC_DELAY2      (0x00f0u)
#define __IMX_LRADC_DELAY3      (0x0100u)
#define __IMX_LRADC_DEBUG0      (0x0110u)
#define __IMX_LRADC_DEBUG1      (0x0120u)
#define __IMX_LRADC_CONVERSION  (0x0130u)
#define __IMX_LRADC_CTRL4       (0x0140u)
#define __IMX_LRADC_THRESHOLD0  (0x0150u)
#define __IMX_LRADC_THRESHOLD1  (0x0160u)
#define __IMX_LRADC_VERSION     (0x0170u)

#define __CTRL0_SFTRST                  AW_BIT(31)
#define __CTRL0_CLKGATE                 AW_BIT(30)
#define __CTRL0_ONCHIP_GROUNDREF        AW_BIT(26)
#define __CTRL0_BUTTON1_DETECT_ENABLE   AW_BIT(25)
#define __CTRL0_BUTTON0_DETECT_ENABLE   AW_BIT(24)
#define __CTRL0_TOUCH_DETECT_ENABLE     AW_BIT(23)
#define __CTRL0_TOUCH_SCREEN_TYPE       AW_BIT(22)
#define __CTRL0_YNLRSW                  AW_BIT(21)
#define __CTRL0_YPLLSW(val)             AW_SBF(val,19)
#define __CTRL0_XNURSW(val)             AW_SBF(val,17)
#define __CTRL0_XPULSW                  AW_BIT(16)
#define __CTRL0_SCHEDULE(ch)            AW_BIT(ch)

#define __CTRL1_IRQ_EN_ALL                  (0x1fff0000)
#define __CTRL1_BUTTON1_DETECT_IRQ_EN       AW_BIT(28)
#define __CTRL1_BUTTON0_DETECT_IRQ_EN       AW_BIT(27)
#define __CTRL1_THRESHOLD1_DETECT_IRQ_EN    AW_BIT(26)
#define __CTRL1_THRESHOLD0_DETECT_IRQ_EN    AW_BIT(25)
#define __CTRL1_TOUCH_DETECT_IRQ_EN         AW_BIT(24)
#define __CTRL1_LRADC7_IRQ_EN               AW_BIT(23)
#define __CTRL1_LRADC6_IRQ_EN               AW_BIT(22)
#define __CTRL1_LRADC5_IRQ_EN               AW_BIT(21)
#define __CTRL1_LRADC4_IRQ_EN               AW_BIT(20)
#define __CTRL1_LRADC3_IRQ_EN               AW_BIT(19)
#define __CTRL1_LRADC2_IRQ_EN               AW_BIT(18)
#define __CTRL1_LRADC1_IRQ_EN               AW_BIT(17)
#define __CTRL1_LRADC0_IRQ_EN               AW_BIT(16)

#define __CTRL1_IRQ_ALL                 (0x1fff)
#define __CTRL1_BUTTON1_DETECT_IRQ      AW_BIT(12)
#define __CTRL1_BUTTON0_DETECT_IRQ      AW_BIT(11)
#define __CTRL1_THRESHOLD1_DETECT_IRQ   AW_BIT(10)
#define __CTRL1_THRESHOLD0_DETECT_IRQ   AW_BIT(9)
#define __CTRL1_TOUCH_DETECT_IRQ        AW_BIT(8)
#define __CTRL1_LRADC7_IRQ              AW_BIT(7)
#define __CTRL1_LRADC6_IRQ              AW_BIT(6)
#define __CTRL1_LRADC5_IRQ              AW_BIT(5)
#define __CTRL1_LRADC4_IRQ              AW_BIT(4)
#define __CTRL1_LRADC3_IRQ              AW_BIT(3)
#define __CTRL1_LRADC2_IRQ              AW_BIT(2)
#define __CTRL1_LRADC1_IRQ              AW_BIT(1)
#define __CTRL1_LRADC0_IRQ              AW_BIT(0)

#define __CTRL2_DIVIDE_BY_TWO(val)      AW_SBF(val,24)
#define __CTRL2_TEMPSENSE_PWD           AW_BIT(15)
#define __CTRL2_VTHSENSE(val)           AW_SBF(val,13)
#define __CTRL2_DISABLE_MUXAMP_BYPASS   AW_BIT(12)
#define __CTRL2_TEMP_SENSOR_IENABLE1    AW_BIT(9)
#define __CTRL2_TEMP_SENSOR_IENABLE0    AW_BIT(8)
#define __CTRL2_TEMP_ISRC1(val)         AW_SBF(val,4)
#define __CTRL2_TEMP_ISRC0(val)         AW_SBF(val,0)

#define __CTRL3_DISCARD(val)            AW_SBF(val,24)
#define __CTRL3_FORCE_ANALOG_PWUP       AW_BIT(23)
#define __CTRL3_FORCE_ANALOG_PWDN       AW_BIT(22)
#define __CTRL3_CYCLE_TIME(val)         AW_SBF(val,8)
#define __CTRL3_HIGH_TIME(val)          AW_SBF(val,4)
#define __CTRL3_DELAY_CLOCK(val)        AW_BIT(1)
#define __CTRL3_INVERT_CLOCK(val)       AW_BIT(0)

#define __STATUS_BUTTON1_PRESENT        AW_BIT(28)
#define __STATUS_BUTTON0_PRESENT        AW_BIT(27)
#define __STATUS_TEMP1_PRESENT          AW_BIT(26)
#define __STATUS_TEMP0_PRESENT          AW_BIT(25)
#define __STATUS_TOUCH_PANEL_PRESENT    AW_BIT(24)
#define __STATUS_CHANNEL7_PRESENT       AW_BIT(23)
#define __STATUS_CHANNEL6_PRESENT       AW_BIT(22)
#define __STATUS_CHANNEL5_PRESENT       AW_BIT(21)
#define __STATUS_CHANNEL4_PRESENT       AW_BIT(20)
#define __STATUS_CHANNEL3_PRESENT       AW_BIT(19)
#define __STATUS_CHANNEL2_PRESENT       AW_BIT(18)
#define __STATUS_CHANNEL1_PRESENT       AW_BIT(17)
#define __STATUS_CHANNEL0_PRESENT       AW_BIT(16)
#define __STATUS_BUTTON1_DETECT_RAW     AW_BIT(2)
#define __STATUS_BUTTON0_DETECT_RAW     AW_BIT(1)
#define __STATUS_TOUCH_DETECT_RAW       AW_BIT(0)

#define __RESULT_TOGGLE                 AW_BIT(31)
#define __BATRES_TESTMODE_TOGGLE        AW_BIT(30)
#define __RESULT_ACCUMULATE             AW_BIT(29)
#define __RESULT_NUM_SMAPLES(val)       AW_SBF(val,24)
#define __RESULT_VALUE(val)             AW_SBF(val,0)

#define __CTRL4_LRADC7SELECT(val)       AW_SBF(val,28)
#define __CTRL4_LRADC6SELECT(val)       AW_SBF(val,24)
#define __CTRL4_LRADC5SELECT(val)       AW_SBF(val,20)
#define __CTRL4_LRADC4SELECT(val)       AW_SBF(val,16)
#define __CTRL4_LRADC3SELECT(val)       AW_SBF(val,12)
#define __CTRL4_LRADC2SELECT(val)       AW_SBF(val,8)
#define __CTRL4_LRADC1SELECT(val)       AW_SBF(val,4)
#define __CTRL4_LRADC0SELECT(val)       AW_SBF(val,0)

#define __LRADC_DELAYn(n)           (__IMX_LRADC_DELAY0 + (n) * 0x10)
#define __LRADC_DELYAn_SET(n)       (__LRADC_DELAY(n) + 0x0004)
#define __LRADC_DELAYn_CLR(n)       (__LRADC_DELAY(n) + 0x0008)

#define __LRADC_DELAYn_TRIGGER_LRADCS_BIT   24
#define __LRADC_DELAYn_TRIGGER_LRADCS_MAP   0xFF000000
#define __LRADC_DELAYn_TRIGGER_LRADCS(v)    \
                        (((v) << 24 ) & __LRADC_DELAYn_TRIGGER_LRADCS_MAP)

#define __LRADC_DELAYn_KICK          0x00100000

#define __LRADC_DELAYn_TRIGGER_DELAY_BITs   16
#define __LRADC_DELAYn_TRIGGER_DELAY_MAP    0x000F0000
#define __LRADC_DELAYn_TRIGGER_DELAYS(v)    \
                       (((v) << 16 ) & __LRADC_DELAYn_TRIGGER_DELAY_MAP)

#define __LRADC_DELAYn_LOOP_COUNT_BITs   11
#define __LRADC_DELAYn_LOOP_COUNT_MAP    0x0000F800
#define __LRADC_DELAYn_LOOP_COUNT(v)    \
                       (((v) << 11 ) & __LRADC_DELAYn_LOOP_COUNT_MAP)

#define __LRADC_DELAYn_DELAY_BITs   0
#define __LRADC_DELAYn_DELAY_MAP    0x000007FF
#define __LRADC_DELAYn_DELAY(v)    \
                       (((v) << 0 ) & __LRADC_DELAYn_DELAY_MAP)

#define __LRADC_CHn(n)                   (__IMX_LRADC_CH0 + (n) * 0x10)
#define __LRADC_CHn_SET(n)               (__LRADC_CHn(n) + 0x0004)
#define __LRADC_CHn_CLR(n)               (__LRADC_CHn(n) + 0x0008)

#define __LRADC_CHn_TOGGLE                0x80000000
#define __LRADC_CHn_ACCUMULATE            0x20000000

#define __LRADC_CHn_NUM_SAMPLES_BIT       24
#define __LRADC_CHn_NUM_SAMPLES_MAP       0x1F000000
#define __LRADC_CHn_NUM_SAMPLES(v)  \
                      (((v) << 24 ) & __LRADC_CHn_NUM_SAMPLES_MAP)

#define __LRADC_CHn_VALUE_BIT             0
#define __LRADC_CHn_VALUE_MAP             0x0003FFFF
#define __LRADC_CHn_VALUE(v)        \
                      (((v) << 0 ) & __LRADC_CHn_VALUE_MAP)

/** @} */

#define AWBL_IMX28_LRADC_NAME            "imx28_lradc"

/**
 * \brief imx28 LRADC 设备信息
 */
typedef struct awbl_imx28_lradc_devinfo {

    struct awbl_adc_servinfo adc_servinfo;     /**< \brief ADC 服务相关信息   */
    uint32_t    regbase;                       /**< \brief ADC 寄存器基地址   */
    uint8_t    *p_intnums;                     /**< \brief 通道中断号数组     */
    uint8_t     intcnts;                       /**< \brief 通道中断号个数     */
    uint8_t     bits;                          /**< \brief ADC 位数           */
    uint32_t    refmv;                         /**< \brief ADC 参考电压 mV    */
    aw_clk_id_t clk_id;                        /**< \brief ADC 采样时钟的ID   */
    void (*pfn_plfm_init) (void);              /**< \brief 平台初始化函数     */

} awbl_imx28_lradc_devinfo_t;

/**
 * \brief imx28 LRADC 设备实例
 */
typedef struct awbl_imx28_lradc_dev {

    struct awbl_dev         super;             /**< \brief 继承自 AWBus 设备  */
    struct awbl_adc_service adc_serv;          /**< \brief ADC 服务           */

    aw_adc_channel_t        phy_chan;          /**< \brief 设备当前转换的通道 */

    aw_adc_buf_desc_t      *p_bufdesc;         /**< \brief 指向各个缓冲区描述 */
    uint32_t                bufdesc_num;       /**< \brief 缓冲区个数         */
    uint32_t                cur_bufdesc_id;    /**< \brief 正在处理的缓冲区ID */

    uint32_t                samples;           /**< \brief 缓冲区已完成的次数 */
    uint32_t                remain_count;      /**< \brief 剩余的序列转换次数 */
    bool_t                  is_stopped;        /**< \brief 标志是否被强制停止 */

    pfn_adc_complete_t      pfn_seq_complete;  /**< \brief 序列完成回调函数   */
    void                   *p_arg;             /**< \brief 回调函数参数       */

} awbl_imx28_lradc_dev_t;


/**
 * \brief imx28 driver register
 */
void awbl_imx28_lradc_drv_register (void);

/**
 * \brief auto measure batt volt
 */
aw_err_t  awbl_imx283_batt_volt_auto_measure_init (void);

/**
 * \brief read batt volt
 */
aw_err_t  awbl_imx283_batt_volt_get (uint32_t  *pbatt_volt);

#endif
