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
 * \brief USART ����ʵ��
 * 
 * \internal
 * \par Modification history
 * - 1.02 15-11-18  cod, add uart tx/rx FIFO function.
 * - 1.01 15-06-10  sam, first implementation.
 * 
 * \endinternal
 */
 
#include "amdr_usart.h"
#include "amhw_clock.h"
#include "amhw_int.h"

/*******************************************************************************
* ���ܺ�������
*******************************************************************************/

static int __usart_mode_set (amdr_usart_dev_t *p_dev, uint32_t new_mode);

static int __usart_opt_set (amdr_usart_dev_t *p_dev, uint32_t opts);

static int __usart_flowctrl_set (amdr_usart_dev_t *p_dev, uint8_t mode);

static int __usart_ioctl(void *p_drv, int, void *);

static int __usart_tx_startup(void *p_drv);

static int __usart_callback_set (void  *p_drv,
	                             int    callback_type,
							   	 int   (*pfn_callback)(void *),
                                 void   *callback_arg);
																 
static int __usart_connect(void *p_drv);
																 
																 
static int __usart_poll_getchar (void *p_drv, char *p_char);
																 
static int __usart_poll_putchar (void *p_drv, char outchar);

/** \brief ������������ */																 
static const struct am_uart_drv_funcs __g_uart_drv_funcs = {
    __usart_ioctl,
	__usart_tx_startup,
    __usart_callback_set,
	__usart_poll_getchar,
	__usart_poll_putchar,
	__usart_connect,
};

/**
 * \brief ����IO���ƺ���
 *
 * ͨ������ķ�ʽ���û��ȡ������,�жϻ���ѯģʽ, ����֡��ʽ��
 *
 * \return AM_OK �ɹ�, -AM_EIO ���豸ʧ��,
 *         -AM_ENOTSUP ���������
 */
static int __usart_ioctl (void *p_drv, int request, void *p_arg)     
{
    amdr_usart_dev_t  *p_dev      = (amdr_usart_dev_t *)p_drv;
	int                status     = AM_OK;
	amhw_usart_t      *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
	 
	switch (request) {
	case AM_UART_BAUD_SET:

	    while ((amhw_usart_stat_get(p_hw_usart) & AMHW_USART_LSR_TEMT) == 0);
	    
	    status = amhw_usart_baudrate_set(p_dev->p_devinfo->p_hw_usart,
	                                     g_pclk_freq,
	                                     (uint32_t)p_arg);
	    
	    if (status > 0) {
			p_dev->baud_rate = status;
			status = AM_OK;					 
		} else {
			status = -AM_EIO;
		}
	    break;
		
	case AM_UART_BAUD_GET:
        *(int *)p_arg = p_dev->baud_rate;
	    break;
	
	case AM_UART_MODE_SET:
		status = (__usart_mode_set(p_dev, (int)p_arg) == AM_OK) ? AM_OK : -AM_EIO;
	    break;
	
	case AM_UART_MODE_GET:
	    *(int *)p_arg = p_dev->channel_mode;		
	    break;
	
	case AM_UART_OPTS_SET:
        status = (__usart_opt_set(p_dev, (int)p_arg) == AM_OK) ? AM_OK : -AM_EIO;
        break;

    case AM_UART_OPTS_GET:
        *(int *)p_arg = p_dev->options;
        break;

    case AM_UART_FLOWMODE_SET:
    	status = __usart_flowctrl_set(p_dev, (int)p_arg);
    	break;

    case AM_UART_FLOWSTAT_RX_SET:
    case AM_UART_FLOWSTAT_TX_GET:
    	status = -AM_ENOTSUP;
    	break;

    case AM_UART_RS485_ENABLE_SET:
    	if ((int)p_arg) {
    		p_dev->rs485_enable = 1;
    		amhw_usart_rs485_ctrl_set(p_hw_usart, p_dev->p_devinfo->rs485_ctrl);
			amhw_usart_rs485_dly_set(p_hw_usart, p_dev->p_devinfo->rs485_dly);
    	} else {
    		p_dev->rs485_enable = 0;
        	amhw_usart_rs485_ctrl_set(p_hw_usart, 0);
        	amhw_usart_rs485_dly_set(p_hw_usart, 0);
    	}
    	break;
    case AM_UART_RS485STAT_GET:
    	*(int *)p_arg = (int)p_dev->rs485_enable;
    	break;
    default:
        status = -AM_EIO;
        break;
		
	}
   
    return (status);
}

/** 
 * \brief USART ���俪ʼ(ֻ�������ж�ģʽ)
 */
int __usart_tx_startup (void *p_drv)              
{
	char              data       = 0;
    amdr_usart_dev_t *p_dev      = (amdr_usart_dev_t *)p_drv;
	amhw_usart_t     *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
	uint8_t           fifo_size  = p_dev->p_devinfo->fifo_size;

	/* FIFO�ǿգ� ����δ��� */
	if (!(amhw_usart_stat_get(p_hw_usart) & AMHW_USART_LSR_THRE)) {
		return -AM_EFULL;
	}

	if ((p_dev->rs485_enable) &&
	    (!p_dev->rs485_txing) &&
	    !(p_dev->p_devinfo->rs485_ctrl & AMHW_USART_RS485_DCTRL_ENABLE)) {
	    p_dev->rs485_txing = 1;
	    p_dev->p_devinfo->pfunc_rs485_gpio_dir_set( \
	        (p_dev->p_devinfo->rs485_ctrl & AMHW_USART_RS485_OINV1) ? 1 : 0);
	}
		    
	/* �رշ����ж� */
	amhw_usart_int_disable(p_hw_usart, AMHW_USART_IER_THREINT);	
	
	while (fifo_size--) {

        if (p_dev->pfn_txchar_get(p_dev->txget_arg, &data) == AM_OK) {
            p_hw_usart->thr = data;
            while (!(amhw_usart_stat_get(p_hw_usart) & AMHW_USART_LSR_THRE));
        } else if ((p_dev->rs485_enable) &&
                   (fifo_size == (p_dev->p_devinfo->fifo_size - 1))) {

            p_dev->rs485_txing = 0;

            p_dev->p_devinfo->pfunc_rs485_gpio_dir_set( \
                (p_dev->p_devinfo->rs485_ctrl & AMHW_USART_RS485_OINV1) ? \
                        0 : 1);
            break;
        } else {
            break;
        }
	}

	/* ʹ�ܷ����ж� */
	amhw_usart_int_enable(p_hw_usart, AMHW_USART_IER_THREINT);

	return AM_OK;
}

/**
 * \brief �����жϻص�����
 *
 * \param p_drv             ��ָ��
 * \param callback_type     �ص�����(���ͻ��߽���)
 * \param pfn_callback      �ص�����ָ��
 * \param callback_arg      �ص���������ָ��
 *
 * \return AM_OK �����óɹ�, ENOSYS ��ʾ��֧�ֻص���������
 */
static int __usart_callback_set (void  *p_drv,                
	                             int    callback_type,
								 int  (*pfn_callback)(void *),
	                             void  *callback_arg)
{
    amdr_usart_dev_t  *p_dev = (amdr_usart_dev_t *)p_drv;
	
	switch (callback_type) {
	case AM_UART_CALLBACK_GET_TX_CHAR:
	    p_dev->pfn_txchar_get = (pfn_uart_txchar_get_t)pfn_callback;
	    p_dev->txget_arg      = callback_arg;
	    return (AM_OK);

    case AM_UART_CALLBACK_PUT_RCV_CHAR:
        p_dev->pfn_rxchar_put = (pfn_uart_rxchar_put_t)pfn_callback;
        p_dev->rxput_arg      = callback_arg;
	    return (AM_OK);
	
	case AM_UART_CALLBACK_ERROR:
		p_dev->pfn_err = (pfn_uart_err_t)pfn_callback;
	    p_dev->err_arg = callback_arg;
	    return (AM_OK);
	
	default:
		  return (-AM_ENOTSUP);		  
	}

}

/**
 * \brief ��ѯģʽ�����һ���ֽ�
 *
 * \return AM_OK ��ʾ���һ���ֽڳɹ�, -EAGAIN ��ʾ���һ���ֽ�ʧ��
 */
static int __usart_poll_putchar (void *p_drv, char outchar)            
{
    amdr_usart_dev_t *p_dev   =  (amdr_usart_dev_t *)p_drv;
	   
	amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;

	/* add by xjc */
//	extern dir_clr_work_restart();

	if ((p_dev->rs485_enable) &&
        !(p_dev->p_devinfo->rs485_ctrl & AMHW_USART_RS485_DCTRL_ENABLE)) {
	    p_dev->p_devinfo->pfunc_rs485_gpio_dir_set( \
	                   (p_dev->p_devinfo->rs485_ctrl & AMHW_USART_RS485_OINV1) ? \
	                           1 : 0);
        p_dev->p_devinfo->pfunc_rs485_gpio_dir_set(2);
    }
//	dir_clr_work_restart();
	/* end */

	if (amhw_usart_stat_get(p_hw_usart) & AMHW_USART_LSR_TEMT) {
		/* ����һ���ֽ� */
      	p_hw_usart->thr = outchar;
	} else {		
		return (-AM_EAGAIN);	
	}

    return (AM_OK);
}

/**
 * \brief ��ѯģʽ�½���һ���ֽ�
 *
 * \return AM_OK ��ʾ���ճɹ�, -EAGAIN ��ʾ���ջ�����Ϊ�գ���û�н��յ�����
 */
static int __usart_poll_getchar (void *p_drv, char *p_char)              
{
    amdr_usart_dev_t *p_dev = (amdr_usart_dev_t *)p_drv;
  	
	uint8_t       *p_inchar = (uint8_t *)p_char;  

	amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;

	if ((amhw_usart_stat_get(p_hw_usart) & AMHW_USART_LSR_RDR) ==0)	{
		return (-AM_EAGAIN); 		    				
	} else {
			
        /* ����һ���ֽ� */
	    *p_inchar = p_hw_usart->rbr;
	}
		
	return (AM_OK);
}

/**
 * \brief ����ģʽ����(�жϻ���ѯ) 
 *
 * \return AM_OK ��ʾ���ճɹ�, AM_ERROR��ʾʧ��
 */
int __usart_mode_set (amdr_usart_dev_t *p_dev, uint32_t new_mode)   
{
	amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
	  
	/* ֻ֧���жϺ���ѯģʽ */
    if ((new_mode != AM_UART_MODE_POLL) && (new_mode != AM_UART_MODE_INT)) {
		return (AM_ERROR);
	} 
			
	if (new_mode == AM_UART_MODE_INT) {

	    /* ���ý���FIFOˮƽ  */
	    amhw_usart_fifo_set(p_hw_usart, p_dev->p_devinfo->fifo_level |
                                        AMHW_USART_RXFIFO_RESET      |
                                        AMHW_USART_TXFIFO_RESET      |
                                        AMHW_USART_FCR_FIFO);
							  
	    /* ʹ�����н����ж�  */
	    amhw_usart_int_enable(p_hw_usart, AMHW_USART_IER_RBRINT);			  		 
    } else {
		   
		/* �ر���������ж� */
		amhw_usart_int_disable(p_hw_usart, AMHW_USART_IER_INTALL);   
	}				

    p_dev->channel_mode = new_mode;
    
	return (AM_OK);
}

/**
 * \brief ����֡��ʽѡ������
 *
 * \return AM_OK ��ʾ���ճɹ�
 */
int __usart_opt_set (amdr_usart_dev_t *p_dev, uint32_t options)    
{
    amhw_usart_t *p_hw_usart;
	uint32_t      cfg_flags;
	  
	if (p_dev == NULL) {
		return (AM_ERROR);		
	}
    
	p_hw_usart = p_dev->p_devinfo->p_hw_usart;
	cfg_flags  = p_hw_usart->lcr;
		
	switch (options & AM_UART_CSIZE) {
	case AM_UART_CS5: 
		cfg_flags &= ~0x03;
	    cfg_flags |= AMHW_USART_LCR_5BIT;
	    break;
	
	case AM_UART_CS6:
		cfg_flags &= ~0x03;
        cfg_flags |= AMHW_USART_LCR_6BIT;
        break;	
				
	case AM_UART_CS7: 
		cfg_flags &= ~0x03;
	    cfg_flags |= AMHW_USART_LCR_7BIT;
	    break;
	
	case AM_UART_CS8:
        cfg_flags &= ~0x03;
        cfg_flags |= AMHW_USART_LCR_8BIT;
        break;
	
	default:
		  break;		
		}
  
	if (options & AM_UART_STOPB) {
        cfg_flags &= ~(0x01 << 2);
        cfg_flags |= AMHW_USART_LCR_STOP_2;
    } else {
        cfg_flags &= ~(0x01 << 2);
        cfg_flags |= AMHW_USART_LCR_STOP_1;
    }
		
	if (options & AM_UART_PARENB) {			
		/* ʹ��У�� */    
	    cfg_flags |= AMHW_USART_LCR_PARITY;
			   
		cfg_flags &= ~(0x03 << 4);
		    
	    if (options & AM_UART_PARODD) {
			cfg_flags |= AMHW_USART_PARITY_ODD;
		} else {
			cfg_flags |= AMHW_USART_PARITY_EVEN;
		}
	} else {
			
		/* �ر�У�� */
		cfg_flags &= ~AMHW_USART_LCR_PARITY;   
	}
		
	/*  �������ò��� */
	while ((amhw_usart_stat_get(p_hw_usart) & AMHW_USART_LSR_TEMT) == 0);
			
	p_hw_usart->lcr = cfg_flags;
		
	p_dev->options = options;
		
	return (AM_OK);
}

/**
 * \brief Ӳ������������
 *
 * \return AM_OK ��ʾ���óɹ�
 * \retrun -AM_ENOTSUP��ʾ��֧��
 */
int __usart_flowctrl_set (amdr_usart_dev_t *p_dev, uint8_t mode)
{
	amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
	uint8_t       flowctrl   = p_dev->p_devinfo->flowctrl_flags;

	if (flowctrl == 0) {
		return -AM_ENOTSUP;
	}

	/* only support hardware flow-control */
	if (mode == AM_UART_FLOWCTL_HW) {

		amhw_usart_mcr_set(p_hw_usart, flowctrl);

	} else if (mode == AM_UART_FLOWCTL_NO) {

		amhw_usart_mcr_set(p_hw_usart, 0);

	} else {
		return -AM_ENOTSUP;
	}

	return AM_OK;

}

/*******************************************************************************
  USART �ж���������
*******************************************************************************/
/** 
 * \brief USART �жϴ�����
 * \param[in] p_arg : am_int_connect()���ò���.
 * \return None
 */
void __usart_irq_handler (void *p_arg)           
{
    amdr_usart_dev_t     *p_dev      = (amdr_usart_dev_t *)p_arg;   
    amhw_usart_t         *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
	uint32_t              intld;

	intld = amhw_usart_intstat_get(p_hw_usart, AMHW_USART_INTID_MASK);
  
	/* check the interrupt ID*/
    if ((intld & AMHW_USART_IIR_INTSTATUS) == 0) {
			
        switch (intld) {

        case AMHW_USART_THRE_INTID:   /* �����ж�            */
        	__usart_tx_startup((void *)p_dev);
            break;

        case AMHW_USART_RDA_INTID:     /* �����ж�            */
        case AMHW_USART_CTI_INTID:     /* ��ʱ����           */

            /* ��ȡFIFO��ʣ������ */
            while ((amhw_usart_stat_get(p_hw_usart) & AMHW_USART_LSR_RDR) == 1) {
                p_dev->pfn_rxchar_put(p_dev->rxput_arg, (char)p_hw_usart->rbr);
            }
            break;

        default:
            break;
        }
	}
}	


int __usart_connect (void *p_drv)            
{
    amdr_usart_dev_t *p_dev = (amdr_usart_dev_t *)p_drv;
	
	am_int_connect(p_dev->p_devinfo->inum, __usart_irq_handler, (void *)p_dev);
	am_int_enable(p_dev->p_devinfo->inum);
	
	amhw_usart_int_enable(p_dev->p_devinfo->p_hw_usart, p_dev->other_int_enable);

	return AM_OK;
}

/**
 * \brief ����ص�����
 *
 * \returns AM_EINVAL
 */
static int __usart_dummy_callback (void *p_outchar)
{
    return (AM_ERROR);
}

/**
 * \brief  USART ��ʼ��
 *
 * \param[in] p_dev     : ָ��USART�豸��ָ��
 * \param[in] p_devinfo : ָ��USART�豸��Ϣ��ָ�� 
 *
 * \return ��׼I2S�ӿڷ���.��ΪNULL�����ʼ��ʧ��
 */
am_uart_handle_t amdr_usart_init (amdr_usart_dev_t           *p_dev,
                                  const amdr_usart_devinfo_t *p_devinfo)
{
    amhw_usart_t           *p_hw_usart;
	uint32_t                tmp;
	
	if (p_devinfo == NULL || p_devinfo->p_hw_usart == NULL) {
	    return NULL;					
	}

	p_hw_usart               = p_devinfo->p_hw_usart;
	p_dev->p_devinfo         = p_devinfo;
    
	p_dev->uart_serv.p_funcs = (struct am_uart_drv_funcs *)&__g_uart_drv_funcs;		
	p_dev->uart_serv.p_drv   = p_dev;
	p_dev->baud_rate         = p_devinfo->baud_rate;
		
	p_dev->options           = 0;
	p_dev->pfn_txchar_get    = (int (*) (void *, char*))__usart_dummy_callback;
    p_dev->txget_arg         = NULL;
    
	p_dev->pfn_rxchar_put    = (int (*) (void *, char ))__usart_dummy_callback;
    p_dev->rxput_arg         = NULL;
    p_dev->pfn_err           = (int (*) (void *, int, void*, int))__usart_dummy_callback;
    p_dev->err_arg           = NULL;
	
	p_dev->other_int_enable  = p_devinfo->other_int_enable & \
                               ~(AMHW_USART_IER_RBRINT  | \
                                 AMHW_USART_IER_THREINT | \
                                 AMHW_USART_IER_RXLSINT);
	  		
    tmp  = p_devinfo->cfg_flags;
    tmp &= 0x03;
    
    switch (tmp) {
	case 0:
		p_dev->options |= AM_UART_CS5;
		break;
    
	case 1:
		p_dev->options |= AM_UART_CS6;
		break;
	
	case 2:
		p_dev->options |= AM_UART_CS7;
		break;
    
	case 3:
		p_dev->options |= AM_UART_CS8;
	    break;  
	
	default:
		p_dev->options |= AM_UART_CS8;
		break;
    }
		
	tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 3) & 0x07;
    
    if (tmp == 1) {
        p_dev->options |= (AM_UART_PARENB |AM_UART_PARODD);
    } else if (tmp == 3) {
        p_dev->options |= AM_UART_PARENB;
    }
    
	tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 1) & 0x01;
		
    if (p_devinfo->cfg_flags & AMHW_USART_LCR_STOP_2) {
        p_dev->options |= AM_UART_STOPB;
    }
    
	/* ���ô��ڴ���֡��ʽ */
    amhw_usart_config(p_hw_usart, p_devinfo->cfg_flags);
		
    /* ���ô��� FIFO */
    amhw_usart_fifo_set(p_hw_usart, p_devinfo->fifo_level   |
                                    AMHW_USART_RXFIFO_RESET |
                                    AMHW_USART_TXFIFO_RESET |
                                    AMHW_USART_FCR_FIFO);
	      
    p_dev->baud_rate = amhw_usart_baudrate_set(p_dev->p_devinfo->p_hw_usart,
                                               g_pclk_freq,
                                               p_devinfo->baud_rate);
    
    p_dev->rs485_enable = 0;

	/* ��ʼ��Ϊ��ѯģʽ */
    __usart_mode_set(p_dev, AM_UART_MODE_POLL);   
		
    return &(p_dev->uart_serv);
				
}

/**
 * \brief  USART ���ʼ��
 * \param[in] p_dev : ָ��USART�豸��ָ��
 * \return ��
 */
void amdr_usart_deinit (amdr_usart_dev_t *p_dev)
{  	  	
	p_dev->uart_serv.p_funcs = NULL;	  
	p_dev->uart_serv.p_drv   = NULL;
   
	if (p_dev->channel_mode == AM_UART_MODE_INT) {
		__usart_mode_set(p_dev, AM_UART_MODE_POLL);
	}
		
	/* �رմ����ж� */
	am_int_disable(p_dev->p_devinfo->inum);
}

/* end of file */

