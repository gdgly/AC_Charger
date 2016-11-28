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
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AWBus iMX283 SSP ����ͷ�ļ�
 *
 * LPC11XX SSP Ϊ LPC11XX ϵ��MCU��Ƭ��SSP��������ֻʵ����SPI�������ܡ�
 *
 * \par 1.������Ϣ
 *
 *  - ������:   "lpc11xx_ssp"
 *  - ��������: AWBL_BUSID_PLB
 *  - �豸��Ϣ: struct awbl_lpc11xx_ssp_devinfo
 *
 * \par 2.�����豸
 *
 *  - NXP LPC11XX ϵ��MCU
 *  - NXP LPC13XX ϵ��MCU
 *  - ������LPC11XX SSP ���ݵ��豸
 *
 * \par 3.�豸����/����
 *
 *  - \ref grp_awbl_imx28_ssp_hwconf
 *
 * \par 4.�û��ӿ�
 *
 *  - \ref grp_aw_serv_spi
 *
 * \internal
 * \par modification history:
 * - 1.00 12-11-20  zen, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX28_SPI_H
#define __AWBL_IMX28_SPI_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/**
 * \addtogroup grp_awbl_drv_lpc11xx_ssp
 * \copydetails awbl_imx28_ssp.h
 * @{
 */

/**
 * \defgroup  grp_awbl_imx28_ssp_hwconf �豸����/����
 *
 * LPC11XX I2C Ӳ���豸�Ķ���������Ĵ�����ʾ���û��ڶ���Ŀ��ϵͳ��Ӳ����Դʱ��
 * ����ֱ�ӽ���δ���Ƕ�뵽 awbus_lite_hwconf_usrcfg.c �ж�Ӧ��λ�ã�Ȼ����豸
 * ��Ϣ���б�Ҫ������(�����õ���Ŀ�á�x����ʶ)��
 *
 * \note �ж��ٸ�I2C���ͽ�����Ĵ���Ƕ����ٴΣ�ע�⽫�����޸�Ϊ��ͬ�����֡�

 * \include  hwconf_usrcfg_lpc11xx_ssp.c
 * \note �����������д����û����á���ʶ�ģ���ʾ�û��ڿ���Ӧ��ʱ�������ô˲�����
 *
 * - ��1�� ƽ̨��س�ʼ�� \n
 * ��ƽ̨��ʼ�����������ʹ��SSP�豸ʱ�ӵ���ƽ̨��صĳ�ʼ��������
 *
 * - ��2�� SPI���߱�� \n
 * �����SSP�����������߱�š�����ϵͳ�е�SPI���߱�ŷ��䲻�����ص���
 * ʹ�� Apollo��׼SPI�ӿ�ʱ��ʹ�ô����߱�ţ�����Զ�λ�����ﶨ���
 * LPC11XX SSP�豸��
 *
 * - ��3�� �Ĵ�������ַ \n
 * ��ο�MCU���û��ֲ���д�˲���
 *
 * - ��4�� �жϺ� \n
 * ��ο�ϵͳ���жϺŷ�����д�˲������� \ref grp_aw_plfm_inums

 * - ��5�� ����ʱ��Ƶ�� \n
 * �����ϵͳ��������д��ֵ��
 *
 * - ��6�� imx28 SSP ��Ԫ�� \n
 * Ϊÿ��imx28 SSP ���䲻ͬ�ĵ�Ԫ��
 */

/** @} grp_awbl_drv_imx28_ssp */

#include "aw_spinlock.h"
#include "awbl_spibus.h"
#include "aw_task.h"                    /* ��������� */

#include "driver/dma/awbl_imx28_dma.h"

#define AWBL_IMX28_SSP_NAME   "imx28_ssp"
#define __SSP_TASK_STACK_SIZE        4096

/**
 * \brief imx28 SSP �豸��Ϣ
 */
struct awbl_imx28_ssp_devinfo {

    /** \brief �̳��� AWBus SPI �������豸��Ϣ */
    struct awbl_spi_master_devinfo spi_master_devinfo;

    uint32_t regbase;               /**< �Ĵ�������ַ */
    int      inum;                  /**< �жϺ� */
    uint32_t clkfreq;               /**< ����ʱ��Ƶ�� */
    uint32_t clk_id;                /**< ����ʱ��ID��ȡֵCLK_SSP0~CLK_SSP3 */

    uint32_t dma_channel;  			/**< DMAͨ���� */
    uint32_t dma_regbase;			/**< DMA�Ĵ�����ַ */
    int      dma_inum;              /**< DMA�жϺ� */
    uint32_t task_trans_prio;       /**< �����������ȼ� */

    /*
     * 283��SPI�ǵ�˫������һЩ����SD��Ӧ����SPI�ڶ�ȡ����ʱ��ҪMOSI����Ϊ�ߵ�ƽ��
     * ��283Ĭ��MOSI������SPI��ȡ����ʱΪ�͵�ƽ����һ����Ϊ����������֧��MOSI���ſ�����
     */
    void (*pfunc_gpio)(void); /* ��MOSI��������ΪGPIO���ܣ�������ߵ�ƽ */
    void (*pfunc_mosi)(void); /* ��MOSI��������ΪMOSI���� */

    /** ƽ̨��س�ʼ��������ʱ�ӡ���ʼ�����ŵȲ��� */
    void (*pfunc_plfm_init)(void);
};

/**
 * \brief imx28 SSP �豸ʵ��
 */
struct awbl_imx28_ssp_dev {

    /** \brief �̳��� AWBus SPI ���������� */
    struct awbl_spi_master  super;

    /** \brief ��ǰ���ڴ���� Message */
    struct aw_spi_message *p_cur_msg;

    /** \brief ��ǰ���ڴ���� Transfer */
    struct aw_spi_transfer *p_cur_trans;

    /** \brief �������ݼ��� */
    size_t      data_ptr;

    /** \brief ������æ��־ */
    bool_t        busy;

    /** \brief ������״̬��״̬  */
    int         state;

    uint32_t    cur_speed;      /**< /brief ��������ǰ�ٶ� */
    uint8_t     cur_bpw;        /**< /brief ��������ǰ֡��С */
    uint8_t     cur_mode;       /**< /brief ��������ǰģʽ */

    uint32_t    nbytes_to_recv; /**< /brief �����յ��ֽ��� */
    uint8_t     cs_toggle;      /**< /brief Ƭѡ������־ */
    aw_spi_device_t *p_tgl_dev; /**< /brief ��ǰ������SPI�豸 */

	awbl_imx28_ssp_dma_desc *dma_desc[3]; /* DMA������ */
	uint8_t 	 	        *dma_buff[2]; /* ���ݻ�����������cacheӰ�� */

    AW_TASK_DECL(ssp_trans_task_decl, __SSP_TASK_STACK_SIZE);
    AW_SEMB_DECL(ssp_sem_sync); /**< /brief ����ͬ������������ź��� */

    awbl_imx28_dma_chan_dev dma_chan_dev;/**< DMAͨ�� */

};

/**
 * \brief imx28 SSP master driver register
 */
void awbl_imx28_ssp_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_LPC11XX_SPI_H */

/* end of file */
