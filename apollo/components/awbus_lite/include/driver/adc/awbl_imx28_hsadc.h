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
 * \brief im28 HSADC �豸��Ϣ
 */
typedef struct awbl_imx28_hsadc_devinfo {

    /** \brief ADC ���������Ϣ */
    struct awbl_adc_servinfo adc_servinfo;

    /** \brief ADC �Ĵ�������ַ */
    uint32_t    regbase;

    /** \brief ADC �жϱ�� */
    uint8_t    intnum;

    /** \brief ADC λ������֧��8λ��10λ��12λ */
    uint8_t    bits;

    /** \brief ADC �ο���ѹ mV */
    uint32_t   refmv;

    /** \brief ADC ʱ�� */
    aw_clk_id_t clk_id;
    
    /** \brief DMAͨ����     */
    uint32_t    dma_channel;
    
    /** \brief DMA�Ĵ�����ַ,APBH or APBX */
    uint32_t    dma_regbase;
    
    /** \brief DMA�жϺ�     */
    int         dma_inum;

    /** \brief BSP function to get apb clock */
    uint32_t (*pfunc_plfm_apbclk_get) (void);

    /** \brief BSP function to pre initialize the device */
    void (*pfunc_plfm_init) (void);
} awbl_imx28_hsadc_devinfo_t;


/** \brief ���ݴ���ӿڣ�������һ��HSADC DMA���ݴ���������Ϣ */
struct awbl_imx28_hsadc_data_trans {

    /** \brief ָ�����飬����3��dma������ָ�� */
    awbl_imx28_dma_desc_t   *dma_desc[3];
    uint8_t                 *dma_buf[3];
    
    uint32_t                 desc_num;   /** \brief ������ʹ�õ����������� */
    uint32_t                 start_addr; /** \brief �����为�����ʼ��ַ   */
    uint32_t                 len;        /** \brief �����䴫��ĳ���       */
    
    /* ���������Ҫ�������ݿ��� */
    struct data_copy {
        uint32_t src_addr;         /** \brief Դ��ַ               */
        uint32_t dst_addr;         /** \brief Ŀ���ַ             */
        uint32_t data_len;         /** \brief ����                 */
        bool_t   flag;             /** \brief TRUE if need copy   */
    } copy[3];                     /** \brief ������3�����ݿ����� */
    
};

/**
 * \brief imx28 ADC �豸ʵ��
 */
typedef struct awbl_imx28_hsadc_dev {

    /** \brief �̳��� AWBus �豸 */
    struct awbl_dev                  super;

    /** \brief ADC ���� */
    struct awbl_adc_service          adc_serv;

    /** \brief �����������ݴ���(ÿ������������3��DMA����)���������������� */
    struct awbl_imx28_hsadc_data_trans  trans[2];
    
    /** \brief ��ǰ���ڴ����transfer��ID */
    uint8_t                          cur_trans_id;
    
    /** \brief �Ƿ���Ҫ��һ������         */
    bool_t                           is_need_next_trans; 
    
    /** \brief �Ƿ�Ϊ�������ϵ�ת��       */
    bool_t                           convert_forever;
    
    /** \brief �����������ʱ�����豸��Ϊȡ��״̬�������ٴ���DMA��������е��� */
    bool_t                           is_cancelled;       
    
    uint8_t                          bytes_per_samp;     /* ÿ�β���ֵ��Ӧ���ֽ���     */
    
    uint32_t                         addr;
    uint32_t                         remain_len;
    uint32_t                         remain_count;       /* ʣ�������ת������        */
    uint32_t                         samples;
    
    /** \brief �豸��ǰת����ͨ��*/
    aw_adc_channel_t                 channel;
    
    aw_adc_buf_desc_t               *p_bufdesc;
    uint32_t                         bufdesc_num;
    uint32_t                         cur_bufdesc_id;     /* ��ǰ���ڴ���Ļ�����ID    */
    uint32_t                         pro_bufdesc_id;     /* DMA������ӵ��Ļ�����ID���У����ܻ�û��ʼ���䣩*/
    
    awbl_imx28_dma_chan_dev          dma_chan_dev;
    
    pfn_adc_complete_t               pfn_seq_complete;  /** \brief ������ɻص�����     */
    void                            *p_arg;             /** \brief ������ɻص��������� */
    
} awbl_imx28_hsadc_dev_t;


/**
 * \brief imx28 driver register
 */

void awbl_imx28_hsadc_drv_register (void);

#endif
