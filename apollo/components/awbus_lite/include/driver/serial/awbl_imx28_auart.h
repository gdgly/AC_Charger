/*
 * awbl_imx28_auart.h
 *
 *  Created on: 2014-6-9
 *      Author: wengyedong
 */

#ifndef AWBL_IMX28_AUART_H_
#define AWBL_IMX28_AUART_H_


#define AWBL_IMX28_AUART_NAME "imx28_auart"
#include "aw_hwtimer.h"
#include "aw_sem.h"

/*******************************************************************************
    types
*******************************************************************************/
/** \brief imx28 auart device channel structure for awbus lite */
struct awbl_imx28_auart_chan {
    /** \brief driver functions, always goes first */
    aw_const struct aw_sio_drv_funcs *p_drv_funcs;

	/**< \brief device */
	struct awbl_dev          dev;

    /** \brief pointer to xmitr func */
    int  (*pfunc_txchar_get)(void *, char *);

    /** \brief pointer to rcvr func */
    int  (*pfunc_rxchar_put)(void *, char);

    void  *txget_arg;   /**< \brief argument for xmitr func */
    void  *rxput_arg;   /**< \brief argument for rcvr func */

    uint8_t  channel_mode;  /**< \brief such as INT, POLL modes */
    uint8_t  channel_no;    /**< \brief channel number */
    uint16_t options;       /**< \brief hardware setup options */
    uint32_t baud_rate;     /**< \brief baud rate */
    uint8_t	 rs485_en;
    uint8_t  rs485_detect_en;

    aw_spinlock_isr_t spinlock_isr; /**< \brief ISR-callable spinlock */

    /**
     * \brief next auart for imx28
     */
    struct awbl_imx28_auart_chan *p_next;

};


/** \brief imx28 auart initialization structure for plb based AWBus devices */
struct awbl_imx28_auart_chan_param {
    int      vector;    /**< \brief Actual architectural vector */
    uint32_t base_addr; /**< \brief Virt address of register set */
    uint32_t clk_id;    /**< \brief UART clock id */
    uint32_t freq_irq_rs485;	/* 提供一个定时中断频率用于查询485模式下数据发送完成标志 */
    void     (*pfunc_rs485_dir)(uint8_t dir);

    /** \brief BSP function to pre initialize the device */
    void      (*pfunc_plfm_init)(void);
};


struct awbl_imx28_auart_485_detect {
	aw_hwtimer_handle_t tm;
	uint32_t	max_baud_rate;
	uint8_t		cnt_485_en;
	uint8_t		cnt_485_detect;
};




#endif /* AWBL_IMX28_AUART_H_ */
