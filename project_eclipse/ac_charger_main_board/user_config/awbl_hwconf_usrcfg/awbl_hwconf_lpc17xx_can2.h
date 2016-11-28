/*
 * awbl_hwconf_lpc17xx_can.h
 *
 *  Created on: 2015-09-01
 *      Author: anu
 */

#include "aw_int.h"
#include "aw_gpio.h"
#include "aw_rngbuf.h"
#include "ametal.h"
#include "driver/can/awbl_ametal_can.h"

#ifdef  AW_DEV_LPC17XX_CAN2

extern const  amdr_can_comm_devinfo_t  g_can_comm_devinfo;
extern amdr_can_comm_dev_t             g_can_comm_dev;

#define AW_CFG_CAN2_CTLR_HS         AW_CAN_CTLR_HS       /**< \brief ����CAN */
#define AW_CFG_CAN2_RX_BUF_SIZE     128			         /**< \brief CAN�����С */
#define AW_CFG_CAN2_ID              1                    /**< \brief CAN��ID�� */

/** \brief CAN2 �жϻص���Ϣ */
static amdr_can_intcb_info_t __g_can2_intcb_infos[AMHW_CAN_INT_TYPE_COUNT];

/** \brief CAN2 �豸��Ϣ */
const  amdr_can_devinfo_t  g_can2_devinfo = {
    AMHW_CAN2,                              /**< \brief CAN2 ��ַ           */
    __g_can2_intcb_infos,                   /**< \brief CAN  �ص���Ϣ */
    AW_CFG_CAN2_ID                          /**< \brief CAN  �жϺ�      */
};

/** \brief CAN2 �豸 */
amdr_can_dev_t g_can2_dev;

/** \brief CAN2 ���ų�ʼ�� */
void amhw_plfm_can2_init (void)
{
	am_gpio_pin_cfg(PIO0_5, PIO0_5_TD2);
	am_gpio_pin_cfg(PIO0_4, PIO0_4_RD2);

    amhw_power_periph_up(AMHW_POWER_CAN2);

    amdr_can_comm_init(&g_can_comm_dev, &g_can_comm_devinfo);
}

/** \brief CAN2 ���Ž��ʼ�� */
void amhw_plfm_can2_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_CAN2);
}

struct aw_rngbuf  can2_rd_buf_ctr;      /**< \brief CAN���ձ��Ļ��λ��� */

struct aw_can_std_msg can2_rx_msg_buff[AW_CFG_CAN2_RX_BUF_SIZE];

/* can �豸��Ϣ */
aw_local aw_const struct awbl_ametal_can_param __g_ametal_can2_info = {

	{
		AW_CFG_CAN2_ID,						/**< \brief ��ǰͨ���ţ�1*/
		AW_CFG_CAN2_CTLR_HS,			    /**< \brief ����������*/
		sizeof(struct aw_can_std_msg),      /**< \brief һ֡���ĳ���*/
		AW_CFG_CAN2_RX_BUF_SIZE,			/**< \brief ���ջ�������С*/
		can2_rx_msg_buff,					/**< \brief ���ջ������׵�ַ*/
		&can2_rd_buf_ctr                    /**< \brief ����rngbuf������*/
	},

    &g_can2_dev,						/* The hardware device              */
    &g_can2_devinfo,                    /* The hardware device information  */
    (pfn_can_init_t)amdr_can_init,      /* The hardware init function       */
    amhw_plfm_can2_init                 /* pfn_plfm_init                    */
};

/* can�豸ʵ���ڴ澲̬���� */
aw_local struct awbl_ametal_can_dev __g_ametal_can2_dev;

#define AWBL_HWCONF_LPC17XX_CAN2   \
    {                         	   \
		AWBL_AMETAL_CAN_NAME,      \
		LPC17XX_CAN2_UNIT_ID,      \
        AWBL_BUSID_PLB,       	   \
        0,                     	   \
        &(__g_ametal_can2_dev.dev),\
        &(__g_ametal_can2_info)    \
    },
#else

#define AWBL_HWCONF_LPC17XX_CAN2

#endif /* AW_DEV_LPC17XX_CAN2 */
/* end of file */

