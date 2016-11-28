/*
 * awbl_lpc17xx_sdio.h
 *
 *  Created on: 2014-9-15
 *      Author: wengyedong
 */

#ifndef AWBL_IMX28_SDIO_H_
#define AWBL_IMX28_SDIO_H_


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#ifdef AW_LPC177X_8X

#include "awbl_sdiobus.h"
#include "driver/dma/awbl_lpc17xx_dma.h"
#include "amdr_mci.h"

#define AWBL_LPC17XX_SDIO_NAME            "lpc17xx_sdio"

#define __SDIO_SPI_TRANS_TASK_STACK_SIZE        2048


/** \brief LPC17x MCI ��ʼ���������� */
typedef int (*pfunc_mci_init_t) (void *, const void *);

/**
 * \brief lpc17xx sdio �豸ʵ��
 */
typedef struct awbl_lpc17xx_sdio_dev {
    /** \brief �̳��� AWBus SDIO ���������� */
	awbl_sdio_host_t  host;

	uint32_t		speed;

	AW_SEMB_DECL(dma_complete_sem);

	AW_TASK_DECL(trans_task, __SDIO_SPI_TRANS_TASK_STACK_SIZE);
    AW_SEMB_DECL(sem_sync);                 /**< /brief ����ͬ������������ź��� */

}awbl_lpc17xx_sdio_dev_t;

/* sdio host �豸��Ϣ  */
typedef struct awbl_lpc17xx_sdio_dev_info {
	awbl_sdio_host_info_t host_info;

    uint8_t		dma_en;
    uint32_t    dma_channel;  	/**< DMAͨ���� */
    uint32_t    fifo_regaddr;   /**< SDIO FIFO�ĵ�ַ */
    uint32_t    task_trans_prio;/**< �����������ȼ� */


    /**< \brief �豸 */
    void        *p_hw_dev;

    /**< \breif �豸��Ϣ */
    const void  *p_hw_devinfo;

    /**< \brief �ӿڳ�ʼ�� */
    pfunc_mci_init_t  pfunc_mci_init;

    /**< \brief ƽ̨��س�ʼ��������ʱ�ӡ���ʼ�����ŵȲ��� */
    void (*pfunc_plfm_init)(void);

}awbl_lpc17xx_sdio_dev_info_t;

void awbl_lpc17xx_sdio_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AW_LPC177X_8X */

#endif /* AWBL_IMX28_SDIO_H_ */
