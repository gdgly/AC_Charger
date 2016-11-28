/*
 * awbl_gpio_spi.h
 *
 *  Created on: 2014年11月20日
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
 * \brief gpio spi 设备信息
 */
typedef struct awbl_gpio_spi_devinfo {

    /** \brief 继承自 AWBus SPI 控制器设备信息 */
    struct awbl_spi_master_devinfo spi_master_devinfo;

    int		sck;
    int		mosi;
    int		miso;
    uint8_t dummp_byte;

    aw_err_t (*hal_io_set) (int pin, int state);

    uint32_t trans_task_prio;

    /** 平台相关初始化：开启时钟、初始化引脚等操作 */
    void (*pfunc_plfm_init)(void);
} awbl_gpio_spi_devinfo_t;


/**
 * \brief gpio spi 设备结构
 */
typedef struct awbl_gpio_spi_dev {

    /** \brief 继承自 AWBus SPI 主机控制器 */
    struct awbl_spi_master  super;

    /** \brief 当前正在处理的 Message */
    struct aw_spi_message *p_cur_msg;

    /** \brief 当前正在处理的 Transfer */
    struct aw_spi_transfer *p_cur_trans;

    /** \brief 控制器忙标志 */
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
    AW_SEMB_DECL(gpio_spi_sem_sync); /**< /brief 用于同步传输任务的信号量 */

} awbl_gpio_spi_dev_t;


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_GPIO_SPI_H_ */
