/**
 * \file
 * \brief imx28 hsadc driver head file
 *
 * - 1.00 12-06-11  ehf, first implementation
 *
 */
#ifndef __AWBL_IMX28_HSADC_H
#define __AWBL_IMX28_HSADC_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_clk.h"
#include "awbl_adc.h"
#include "aw_spinlock.h"
#include "aw_isr_defer.h"
#include "driver/dma/awbl_imx28_dma.h"

#define __SETREG_ADDR        (4)
#define __CLRREG_ADDR        (8)
#define __TOGREG_ADDR       (12)

#define __IMX_ADC_CTRL0		    (0x0000u)

/* write register */
#define __IMX_ADC_REG_WRITE(regbase, offset, data)   AW_REG_WRITE32( (regbase) + (offset), (data))

/* read register */
#define __IMX_ADC_REG_READ(regbase, offset)          AW_REG_READ32( (regbase) + (offset))

/* set bits*/
#define __IMX_ADC_REG_SET(regbase, offset, data)     AW_REG_WRITE32( (regbase) + (offset) +__SETREG_ADDR, data)

/* clear bits*/
#define __IMX_ADC_REG_CLR(regbase, offset, data)     AW_REG_WRITE32( (regbase) + (offset) +__CLRREG_ADDR, data)

/* toggle bits*/
#define __IMX_ADC_REG_TOG(regbase, offset, data)     AW_REG_WRITE32( (regbase) + (offset) +__TOGREG_ADDR, data)

/***************************   HSADC REGISTERS  **********************************/
#define __IMX_HSADC_CTRL0               (0x0000u)
#define __IMX_HSADC_CTRL1               (0x0010u)
#define __IMX_HSADC_CTRL2               (0x0020u)
#define __IMX_HSADC_SEQ_SAM_NUM         (0x0030u)
#define __IMX_HSADC_SEQ_NUM             (0x0040u)
#define __IMX_HSADC_FIFO_DATA           (0x0050u)
#define __IMX_HSADC_DBG_INFO0           (0x0060u)
#define __IMX_HSADC_DBG_INFO1           (0x0070u)
#define __IMX_HSADC_DBG_INFO2           (0x0080u)
#define __IMX_HSADC_VERSION             (0x00b0u)

#define __HCTRL0_SFTRST                 (1ul<<31)
#define __HCTRL0_CLKGATE                (1ul<<30)
#define __CTRL0_TRIG_SOUCE(val)         (val<<28)
#define __CTRL0_SFT_TRIG                (1ul<<27)
#define __CTRL0_DISCARD(val)            (val<<19)
#define __CTRL0_PRECISION(val)          (val<<17)
#define __CTRL0_ADC_PRESENT             (1ul<<6)
#define __CTRL0_TRIG_DLY_CLE(val)       (val<<1)
#define __CTRL0_RUN                     (1)

#define __CTRL1_INT_ONE_SEQ_EN          (1ul<<31)
#define __CTRL1_INT_DONE_EN             (1ul<<30)
#define __CTRL1_FIFO_OVER_EN            (1ul<<29)
#define __CTRL1_TIMEOUT_EN              (1ul<<28)
#define __CTRL1_INT_CLR                 (1ul<<27)
#define __CTRL1_INT_ALL_CLR             (1ul<<26)

#define __CTRL1_FIFO_RD_EMPTY           (1<<5)
#define __CTRL1_INT_ONE_SEQ_STAT        (1<<4)
#define __CTRL1_INT_DONE_STAT           (1<<3)
#define __CTRL1_FIFO_OVER_STAT          (1<<2)
#define __CTRL1_TIMEOUT_STAT            (1<<1)
#define __CTRL1_INTERRUPT               (1)

#define __CTRL2_POW_DOWN                (1<<13)
#define __CTRL2_CH_SEL(val)             (val<<1)
#define __CTRL2_PRECHARGE               (1)

#define AWBL_IMX28_HSADC_NAME            "imx28_hsadc"

/**
 * \brief im28 HSADC 设备信息
 */
typedef struct awbl_imx28_hsadc_devinfo {

    /** \brief ADC 服务相关信息 */
    struct awbl_adc_servinfo adc_servinfo;

    /** \brief ADC 寄存器基地址 */
    uint32_t    regbase;

    /** \brief ADC 中断编号 */
    uint8_t    intnum;

    /** \brief ADC 位数，仅支持8位，10位，12位 */
    uint8_t    bits;

    /** \brief ADC 参考电压 mV */
    uint32_t   refmv;

    /** \brief ADC 时钟 */
    aw_clk_id_t clk_id;
    
    /** \brief DMA通道号     */
    uint32_t    dma_channel;
    
    /** \brief DMA寄存器基址,APBH or APBX */
    uint32_t    dma_regbase;
    
    /** \brief DMA中断号     */
    int         dma_inum;

    /** \brief BSP function to get apb clock */
    uint32_t (*pfunc_plfm_apbclk_get) (void);

    /** \brief BSP function to pre initialize the device */
    void (*pfunc_plfm_init) (void);
} awbl_imx28_hsadc_devinfo_t;


/** \brief 数据传输接口，包含了一次HSADC DMA数据传输的相关信息 */
struct awbl_imx28_hsadc_data_trans {

    /** \brief 指针数组，包含3个dma描述符指针 */
    awbl_imx28_dma_desc_t   *dma_desc[3];
    uint8_t                 *dma_buf[3];
    
    uint32_t                 desc_num;   /** \brief 本传输使用的描述符个数 */
    uint32_t                 start_addr; /** \brief 本传输负责的起始地址   */
    uint32_t                 len;        /** \brief 本传输传输的长度       */
    
    /* 传输完成需要做的数据拷贝 */
    struct data_copy {
        uint32_t src_addr;         /** \brief 源地址               */
        uint32_t dst_addr;         /** \brief 目标地址             */
        uint32_t data_len;         /** \brief 长度                 */
        bool_t   flag;             /** \brief TRUE if need copy   */
    } copy[3];                     /** \brief 最多包含3个数据拷贝段 */
    
};

/**
 * \brief imx28 ADC 设备实例
 */
typedef struct awbl_imx28_hsadc_dev {

    /** \brief 继承自 AWBus 设备 */
    struct awbl_dev                  super;

    /** \brief ADC 服务 */
    struct awbl_adc_service          adc_serv;

    /** \brief 包含两个数据传输(每个传输最多包含3个DMA描述)，以轮流传输数据 */
    struct awbl_imx28_hsadc_data_trans  trans[2];
    
    /** \brief 当前正在传输的transfer的ID */
    uint8_t                          cur_trans_id;
    
    /** \brief 是否需要下一个传输         */
    bool_t                           is_need_next_trans; 
    
    /** \brief 是否为持续不断的转换       */
    bool_t                           convert_forever;
    
    /** \brief 当缓冲区溢出时，将设备置为取消状态，避免再次在DMA传输完成中调用 */
    bool_t                           is_cancelled;       
    
    uint8_t                          bytes_per_samp;     /* 每次采样值对应的字节数     */
    
    uint32_t                         addr;
    uint32_t                         remain_len;
    uint32_t                         remain_count;       /* 剩余的序列转换次数        */
    uint32_t                         samples;
    
    /** \brief 设备当前转换的通道*/
    aw_adc_channel_t                 channel;
    
    aw_adc_buf_desc_t               *p_bufdesc;
    uint32_t                         bufdesc_num;
    uint32_t                         cur_bufdesc_id;     /* 当前正在处理的缓冲区ID    */
    uint32_t                         pro_bufdesc_id;     /* DMA描述添加到的缓冲区ID序列（可能还没开始传输）*/
    
    awbl_imx28_dma_chan_dev          dma_chan_dev;
    
    pfn_adc_complete_t               pfn_seq_complete;  /** \brief 序列完成回调函数     */
    void                            *p_arg;             /** \brief 序列完成回调函数参数 */
    
} awbl_imx28_hsadc_dev_t;


/**
 * \brief imx28 driver register
 */

void awbl_imx28_hsadc_drv_register (void);

#endif
