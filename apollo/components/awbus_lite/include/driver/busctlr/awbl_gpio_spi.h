/*
 * awbl_gpio_spi.h
 *
 *  Created on: 2014��11��20��
 *      Author: Administrator
 */

#ifndef AWBL_GPIO_SPI_H_
#define AWBL_GPIO_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_spinlock.h"
#include "awbl_spibus.h"
#include "aw_hwtimer.h"

#define AWBL_GPIO_SPI_NAME "awbl_gpio_spi"

#define __GPIO_SPI_TASK_STACK_SIZE        1024

/**
 * \brief gpio spi �豸��Ϣ
 */
typedef struct awbl_gpio_spi_devinfo {

    /** \brief �̳��� AWBus SPI �������豸��Ϣ */
    struct awbl_spi_master_devinfo spi_master_devinfo;

    int		sck;
    int		mosi;
    int		miso;
    uint8_t dummp_byte;

    aw_err_t (*hal_io_set) (int pin, int state);

    uint32_t trans_task_prio;

    /** ƽ̨��س�ʼ��������ʱ�ӡ���ʼ�����ŵȲ��� */
    void (*pfunc_plfm_init)(void);
} awbl_gpio_spi_devinfo_t;


/**
 * \brief gpio spi �豸�ṹ
 */
typedef struct awbl_gpio_spi_dev {

    /** \brief �̳��� AWBus SPI ���������� */
    struct awbl_spi_master  super;

    /** \brief ��ǰ���ڴ���� Message */
    struct aw_spi_message *p_cur_msg;

    /** \brief ��ǰ���ڴ���� Transfer */
    struct aw_spi_transfer *p_cur_trans;

    /** \brief ������æ��־ */
    bool_t  busy;

    uint8_t mode;
    uint8_t bpw;
    uint32_t speed;
    uint32_t dly;

    uint8_t *p_dat;
    uint32_t len;
    uint8_t sck_state;

    aw_err_t (*io_set) (int pin, int state);

    AW_TASK_DECL(gpio_spi_trans_task, __GPIO_SPI_TASK_STACK_SIZE);
    AW_SEMB_DECL(gpio_spi_sem_sync); /**< /brief ����ͬ������������ź��� */

} awbl_gpio_spi_dev_t;


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_GPIO_SPI_H_ */
