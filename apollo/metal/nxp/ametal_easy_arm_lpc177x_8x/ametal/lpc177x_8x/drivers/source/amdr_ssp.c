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
 * \brief SPI drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.01 15-08-25  cod, fix code style and comments,a little improve.
 * - 1.00 15-07-21  ben, first implementation.
 * \endinternal
 */

#include "amhw_clock.h"
#include "amdr_ssp.h"
#include "amdr_dma.h"
/*
 * SSP Controller State
 */

#define __SSP_ST_M_FINI             0       /* finished present task */
#define __SSP_ST_M_NEXT             1       /* wait for next farame*/
#define __SSP_ST_M_SEND_DATA        2       /* master send data */
#define __SSP_ST_M_RECV_DATA        3       /* master receive data */
#define __SSP_ST_M_IDLE             4       /* idle state */

/*******************************************************************************
* Functions declaration
*******************************************************************************/

/* SSP drive function implementation */
static int __ssp_config(void *p_drv, am_spi_cfg_info_t *p_cfg_info);

static int __ssp_transfer(void *p_drv, am_spi_transfer_t *p_trans);

static int __ssp_connect(void *p_drv);

/* SPI interrupt related functions */
static int __ssp_hard_init(amdr_ssp_dev_t *p_dev);
static void __ssp_irq_handler(void *p_arg);
static int __ssp_send_data(amdr_ssp_dev_t *p_dev);
static int __ssp_recv_data(amdr_ssp_dev_t *p_dev);
static int __ssp_rx_tx_data(amdr_ssp_dev_t *p_dev);
static int __ssp_sm_send_event(amdr_ssp_dev_t *p_dev, uint32_t event);
/**
 * \brief SSP driver functions definition
 */
static am_const struct am_spi_drv_funcs __g_ssp_drv_funcs = {
    __ssp_config,
    __ssp_transfer,
    __ssp_connect
};



static int __ssp_config(void *p_arg,am_spi_cfg_info_t *p_info)
{
    amdr_ssp_dev_t   *p_dev     = (amdr_ssp_dev_t *)p_arg;
    amhw_ssp_t       *p_hw_ssp  =  p_dev->p_devinfo->p_hw_ssp;
    int               error     =  AM_OK;
    uint32_t  		  ssp_pclk_freq, ssp_max_speed ,ssp_min_speed;

    if (p_hw_ssp == NULL) {
        return -AM_EINVAL;
    }

    ssp_pclk_freq = amhw_clock_freq_pclk_get();
    /*todo max_speed min_speed 简单处理了*/
    ssp_max_speed = ssp_pclk_freq / (2 * (0 + 1));
    ssp_min_speed = ssp_pclk_freq / (254 * (255 + 1));

    if(p_info->speed > ssp_max_speed) p_info->speed = ssp_max_speed;
    if(p_info->speed < ssp_min_speed) p_info->speed = ssp_min_speed;

    if(p_dev->cur_speed != p_info->speed)
    {
        p_info->speed     = amhw_ssp_set_clock(p_hw_ssp,p_info->speed,ssp_pclk_freq);
        p_dev->cur_speed  = p_info->speed;
    }

    if ( p_info->cfg_flags != p_dev->cur_flags
         || p_info->bpw != p_dev->cur_bpw ) {

        uint32_t  cfg_flg = p_hw_ssp->cr0;

        if (p_info->cfg_flags & AM_SPI_CFG_CPHA) {
            cfg_flg |= (1 << 7);
        } else {
            cfg_flg &= ~(1 << 7);
        }

        if (p_info->cfg_flags & AM_SPI_CFG_CPOL) {
            cfg_flg |= (1 << 6);
        } else {
            cfg_flg &= ~(1 << 6);
        }
        /* 选择ssp功能中的spi功能 */
        cfg_flg |= 0 << 4;

        /* 设置与当前设置不匹配时才进行配置 */
        if (p_info->bpw != p_dev->cur_bpw) {

            if (p_info->bpw > 16) {
                /* 不支持的位宽或模式      */
                error =  -AM_ENOTSUP;
                p_info->bpw = p_dev->cur_bpw = 16;

            } else if (p_info->bpw > 8) {

                p_dev->cur_bpw = p_info->bpw;

            } else if (p_info->bpw > 3 && p_info->bpw <=8) {
                /* 保存位宽，发送数据时设置 */
                p_dev->cur_bpw = p_info->bpw;

            } else {

                p_dev->cur_bpw = p_info->bpw = 4;
                error = -AM_ENOTSUP;
            }
        }

        cfg_flg |= ((p_dev->cur_bpw - 1) << 0);
        /* nbytes data to receive */
        p_dev->nbytes_to_recv = p_dev->cur_bpw < 9 ? 0 : 1;
        p_dev->cur_flags = p_info->cfg_flags;
        /* SSP Configuration */
        p_hw_ssp->cr0 = cfg_flg;
        /* 禁止 SSP */
        p_hw_ssp->cr1 = 0;
    }

    return error;
}



static int __ssp_connect (void *p_drv)
{
    amdr_ssp_dev_t *p_dev = (amdr_ssp_dev_t *)p_drv;
    am_int_connect(p_dev->p_devinfo->inum, __ssp_irq_handler, (void *)p_drv);
    am_int_enable(p_dev->p_devinfo->inum);
    return AM_OK;
}

static void __ssp_error_entry(amdr_ssp_dev_t *p_dev)
{
    amhw_ssp_t *p_hw_ssp  = p_dev->p_devinfo->p_hw_ssp;
    amhw_ssp_clear_roric(p_hw_ssp);
    amhw_ssp_clear_rtic(p_hw_ssp);
    /* 调用回调函数，声明出现错误 */
    if (p_dev->p_trans->pfn_callback) {
        p_dev->p_trans->pfn_callback(p_dev->p_trans->p_arg,AM_ERROR);
    }
}
/**
 * \brief SSP 中断处理函数
 */
static void __ssp_irq_handler(void *p_arg)
{
    amdr_ssp_dev_t  	*p_dev      = (amdr_ssp_dev_t *)p_arg;
    amhw_ssp_t      	*p_hw_ssp   =  p_dev->p_devinfo->p_hw_ssp;
    uint8_t              status     =  amhw_ssp_int_status_read(p_hw_ssp);

   amhw_ssp_int_clear(p_hw_ssp, AMHW_SSP_IM_ROR
                               |AMHW_SSP_IM_RT
                               |AMHW_SSP_IM_RX
                               |AMHW_SSP_IM_TX);

    if (status & AMHW_SSP_MIS_ROR) {
        __ssp_error_entry(p_dev);
        p_dev->state = __SSP_ST_M_IDLE;
        return;
    }

    if (status & AMHW_SSP_MIS_RT) {
        amhw_ssp_clear_rtic(p_hw_ssp);
        __ssp_recv_data(p_dev);
    }

    if (status & AMHW_SSP_MIS_TX) {
        if (p_dev->state == __SSP_ST_M_IDLE || p_dev->state == __SSP_ST_M_NEXT) {
            p_dev->state = __SSP_ST_M_SEND_DATA;
        }
    } else if (status & AMHW_SSP_MIS_RX) {
        if (p_dev->state == __SSP_ST_M_IDLE || p_dev->state == __SSP_ST_M_NEXT) {
            p_dev->state = __SSP_ST_M_RECV_DATA;
        }
    }
     __ssp_sm_send_event(p_dev,p_dev->state);
}


#define ssp_tx_ptr      ((uint32_t )p_dev->p_trans->p_txbuf + p_dev->data_tx_ptr)
#define ssp_rx_ptr      ((uint32_t )p_dev->p_trans->p_rxbuf + p_dev->data_rx_ptr)
#define ssp_rx_tx_len   (p_dev->p_trans->nbytes)

static int __ssp_transfer(void *p_drv, am_spi_transfer_t *p_trans)
{
    amdr_ssp_dev_t  *p_dev    = (amdr_ssp_dev_t *)p_drv;
    amhw_ssp_t      *p_hw_ssp =  p_dev->p_devinfo->p_hw_ssp;
    uint8_t          intflags = (p_dev->cur_flags & AM_SPI_CFG_INT);

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_dev->nbytes_to_recv = p_dev->cur_bpw < 9 ? 0 : 1;
    p_dev->data_rx_ptr    = 0;
    p_dev->data_tx_ptr    = 0;
    p_dev->p_trans        = p_trans;

    if (intflags) {
		/** \brief 中断处理时存在一个状态机，未处理完数据需要等待 */
		while ( p_dev->state != __SSP_ST_M_IDLE);

		p_dev->state          = __SSP_ST_M_SEND_DATA;
		amhw_ssp_int_set(p_hw_ssp, AMHW_SSP_IM_ROR
								  |AMHW_SSP_IM_RT
								  |AMHW_SSP_IM_RX
								  |AMHW_SSP_IM_TX);
		amhw_ssp_enable(p_hw_ssp);
		am_int_enable(p_dev->p_devinfo->inum);

    } else {

		amhw_ssp_enable(p_hw_ssp);
		while (p_dev->data_tx_ptr < ssp_rx_tx_len &&
			   p_dev->data_rx_ptr < ssp_rx_tx_len) {
//			__ssp_send_data(p_dev);
//			__ssp_recv_data(p_dev);
		    __ssp_rx_tx_data(p_dev);
		}
		if (p_dev->p_trans->pfn_callback) {
			p_dev->p_trans->pfn_callback(p_dev->p_trans->p_arg,AM_OK);
		}
		return AM_OK;
    }
    return __ssp_sm_send_event(p_dev, p_dev->state);
}


static int __ssp_rx_tx_data(amdr_ssp_dev_t *p_dev)
{
    uint8_t           bytes     = p_dev->nbytes_to_recv;
    amhw_ssp_t       *p_hw_ssp  = p_dev->p_devinfo->p_hw_ssp;

    while((amhw_ssp_read_status(p_hw_ssp) & AMHW_SSP_ST_TF_NOT_FULL)
           && (p_dev->data_tx_ptr < ssp_rx_tx_len)) {
        if (p_dev->p_trans->p_txbuf == NULL) {
            if (bytes == 0) {
                amhw_ssp_send_data(p_hw_ssp,0xff);
            } else {
                amhw_ssp_send_data(p_hw_ssp,0xffff);
            }
        } else {
            if (bytes == 0) {
                amhw_ssp_send_data(p_hw_ssp,*(uint8_t*)ssp_tx_ptr);
            } else {
                amhw_ssp_send_data(p_hw_ssp,*(uint16_t*)ssp_tx_ptr);
            }
        }

        if (p_dev->p_trans->p_rxbuf == NULL) {

            if (bytes == 0) {
                (void)amhw_ssp_read_8bit_data(p_hw_ssp);
            } else {
                (void)amhw_ssp_read_16bit_data(p_hw_ssp);
            }
        } else {

            if (bytes == 0) {
                *(uint8_t *)ssp_rx_ptr = amhw_ssp_read_8bit_data(p_hw_ssp);
            } else {
                *(uint16_t *)ssp_rx_ptr = amhw_ssp_read_16bit_data(p_hw_ssp);
            }
        }

        p_dev->data_tx_ptr += (bytes + 1);
        p_dev->data_rx_ptr += (bytes + 1);
    }

    return p_dev->data_tx_ptr;
}



static int __ssp_send_data(amdr_ssp_dev_t *p_dev)
{
    uint8_t           bytes     = p_dev->nbytes_to_recv;
    amhw_ssp_t       *p_hw_ssp  = p_dev->p_devinfo->p_hw_ssp;

    while((amhw_ssp_read_status(p_hw_ssp) & AMHW_SSP_ST_TF_NOT_FULL)
           && (p_dev->data_tx_ptr < ssp_rx_tx_len)) {
        if (p_dev->p_trans->p_txbuf == NULL) {
            if (bytes == 0) {
                amhw_ssp_send_data(p_hw_ssp,0xff);
            } else {
                amhw_ssp_send_data(p_hw_ssp,0xffff);
            }
        } else {
            if (bytes == 0) {
                amhw_ssp_send_data(p_hw_ssp,*(uint8_t*)ssp_tx_ptr);
            } else {
                amhw_ssp_send_data(p_hw_ssp,*(uint16_t*)ssp_tx_ptr);
            }
        }
        p_dev->data_tx_ptr += (bytes + 1);
    }

    return p_dev->data_tx_ptr;
}

static int __ssp_recv_data(amdr_ssp_dev_t *p_dev)
{
    uint8_t           bytes     =  p_dev->nbytes_to_recv;
    amhw_ssp_t       *p_hw_ssp  =  p_dev->p_devinfo->p_hw_ssp;

    while((amhw_ssp_read_status(p_hw_ssp) & AMHW_SSP_ST_RF_NOT_EMPTY)
           && (p_dev->data_rx_ptr < ssp_rx_tx_len))
    {
        if (p_dev->p_trans->p_rxbuf == NULL) {

            if (bytes == 0) {
                (void)amhw_ssp_read_8bit_data(p_hw_ssp);
            } else {
                (void)amhw_ssp_read_16bit_data(p_hw_ssp);
            }
        } else {

            if (bytes == 0) {
                *(uint8_t *)ssp_rx_ptr = amhw_ssp_read_8bit_data(p_hw_ssp);
            } else {
                *(uint16_t *)ssp_rx_ptr = amhw_ssp_read_16bit_data(p_hw_ssp);
            }
        }
        p_dev->data_rx_ptr += (bytes + 1);

    }
    return p_dev->data_rx_ptr;
}


static int __ssp_sm_send_event(amdr_ssp_dev_t *p_dev, uint32_t event)
{
   amhw_ssp_t       *p_hw_ssp  =  p_dev->p_devinfo->p_hw_ssp;
   uint8_t           loop_cnt  =  0;
   uint32_t          len ;

   amhw_ssp_int_clear(p_hw_ssp, AMHW_SSP_IM_ROR
                               |AMHW_SSP_IM_RT
                               |AMHW_SSP_IM_RX
                               |AMHW_SSP_IM_TX);
   while(1) {
       switch(event) {

       case __SSP_ST_M_SEND_DATA:

           len = __ssp_send_data(p_dev);

           if (len >= ssp_rx_tx_len && p_dev->data_rx_ptr >= ssp_rx_tx_len) {

               event = __SSP_ST_M_FINI;

           } else if (p_dev->data_rx_ptr < ssp_rx_tx_len) { /**< \brief 接收数据 */

               event = __SSP_ST_M_RECV_DATA;

           } else {

               event = __SSP_ST_M_NEXT ;/**< \brief 使能中断推出循环*/
           }
           break;


       case __SSP_ST_M_RECV_DATA:

           len = __ssp_recv_data(p_dev);

           if (len >= ssp_rx_tx_len &&  p_dev->data_tx_ptr >= ssp_rx_tx_len) {

               event = __SSP_ST_M_FINI;

           } else if ( p_dev->data_tx_ptr < ssp_rx_tx_len) {

               event = __SSP_ST_M_SEND_DATA;

           } else {

               event = __SSP_ST_M_NEXT;
           }
		   break;

       case __SSP_ST_M_NEXT:

           amhw_ssp_int_set(p_hw_ssp, AMHW_SSP_IM_ROR
                                     |AMHW_SSP_IM_RT
                                     |AMHW_SSP_IM_RX
                                     |AMHW_SSP_IM_TX);
           amhw_ssp_enable(p_hw_ssp);

           return AM_OK;

       case __SSP_ST_M_FINI:

           amhw_ssp_int_clear(p_hw_ssp, AMHW_SSP_IM_ROR
                                       |AMHW_SSP_IM_RT
                                       |AMHW_SSP_IM_RX
                                       |AMHW_SSP_IM_TX);

           am_int_disable(p_dev->p_devinfo->inum);
           p_dev->state = __SSP_ST_M_IDLE;

           if (p_dev->p_trans->pfn_callback) {
               p_dev->p_trans->pfn_callback(p_dev->p_trans->p_arg,AM_OK);
           }

           return AM_OK;

       default:
           p_dev->state = __SSP_ST_M_IDLE;
           return -AM_EINVAL;
       }

       /** \brief 处理接发发送FIFO各一帧数据后退出循环 */
       if(loop_cnt++ > 1) {
          if (event != __SSP_ST_M_NEXT || event != __SSP_ST_M_FINI) {
              event = __SSP_ST_M_NEXT;
          }
       }
    }
    return AM_OK;
}

int __ssp_hard_init (amdr_ssp_dev_t *p_dev)
{
    const amdr_ssp_devinfo_t *p_devinfo = p_dev->p_devinfo;
    amhw_ssp_t               *p_hw_ssp  = p_devinfo->p_hw_ssp;
    am_spi_cfg_info_t         cfg_info;

    if (p_hw_ssp == NULL) {
        return -AM_EINVAL;
    }

    p_dev->state      = __SSP_ST_M_IDLE;

    cfg_info.bpw       = p_devinfo->bits_per_word ;
    cfg_info.cfg_flags = p_devinfo->flags;
    cfg_info.speed     = p_devinfo->speed;

	/* close SPI controller,configure SPI master parameter */
    __ssp_config(p_dev,&cfg_info);

    return AM_OK;
}

/**
 * \brief SPI initialize
 */
am_spi_handle_t amdr_ssp_init (amdr_ssp_dev_t           *p_dev ,
                               const amdr_ssp_devinfo_t *p_devinfo)
{
    amhw_ssp_t        *p_hw_ssp  = p_devinfo->p_hw_ssp;
    p_dev->spi_serve.p_drv_funcs = (struct am_spi_drv_funcs *)&__g_ssp_drv_funcs;
    p_dev->spi_serve.p_drv       =  p_dev;
    p_dev->p_devinfo             =  p_devinfo;

    __ssp_hard_init(p_dev);
    p_dev->data_tx_ptr        = 0;
    p_dev->data_rx_ptr        = 0;
    p_dev->nbytes_to_recv     = 0;

    amhw_ssp_enable(p_hw_ssp);

    return &(p_dev->spi_serve);
}

/**
 * \brief SSP De_initialize
 */
void amdr_ssp_deinit(amdr_ssp_dev_t *p_dev)
{
    amhw_ssp_t *p_hw_ssp  = p_dev->p_devinfo->p_hw_ssp;

    p_dev->spi_serve.p_drv_funcs = NULL;
    p_dev->spi_serve.p_drv       = NULL;

    amhw_ssp_disable(p_hw_ssp);
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum, __ssp_irq_handler, (void *)p_dev);
}

/*end of file */
