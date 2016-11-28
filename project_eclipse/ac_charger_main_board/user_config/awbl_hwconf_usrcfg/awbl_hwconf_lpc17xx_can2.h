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

#define AW_CFG_CAN2_CTLR_HS         AW_CAN_CTLR_HS       /**< \brief 高速CAN */
#define AW_CFG_CAN2_RX_BUF_SIZE     128			         /**< \brief CAN缓存大小 */
#define AW_CFG_CAN2_ID              1                    /**< \brief CAN的ID号 */

/** \brief CAN2 中断回调信息 */
static amdr_can_intcb_info_t __g_can2_intcb_infos[AMHW_CAN_INT_TYPE_COUNT];

/** \brief CAN2 设备信息 */
const  amdr_can_devinfo_t  g_can2_devinfo = {
    AMHW_CAN2,                              /**< \brief CAN2 基址           */
    __g_can2_intcb_infos,                   /**< \brief CAN  回调信息 */
    AW_CFG_CAN2_ID                          /**< \brief CAN  中断号      */
};

/** \brief CAN2 设备 */
amdr_can_dev_t g_can2_dev;

/** \brief CAN2 引脚初始化 */
void amhw_plfm_can2_init (void)
{
	am_gpio_pin_cfg(PIO0_5, PIO0_5_TD2);
	am_gpio_pin_cfg(PIO0_4, PIO0_4_RD2);

    amhw_power_periph_up(AMHW_POWER_CAN2);

    amdr_can_comm_init(&g_can_comm_dev, &g_can_comm_devinfo);
}

/** \brief CAN2 引脚解初始化 */
void amhw_plfm_can2_deinit (void)
{
    amhw_power_periph_down(AMHW_POWER_CAN2);
}

struct aw_rngbuf  can2_rd_buf_ctr;      /**< \brief CAN接收报文环形缓冲 */

struct aw_can_std_msg can2_rx_msg_buff[AW_CFG_CAN2_RX_BUF_SIZE];

/* can 设备信息 */
aw_local aw_const struct awbl_ametal_can_param __g_ametal_can2_info = {

	{
		AW_CFG_CAN2_ID,						/**< \brief 当前通道号：1*/
		AW_CFG_CAN2_CTLR_HS,			    /**< \brief 控制器类型*/
		sizeof(struct aw_can_std_msg),      /**< \brief 一帧报文长度*/
		AW_CFG_CAN2_RX_BUF_SIZE,			/**< \brief 接收缓冲区大小*/
		can2_rx_msg_buff,					/**< \brief 接收缓冲区首地址*/
		&can2_rd_buf_ctr                    /**< \brief 接收rngbuf控制字*/
	},

    &g_can2_dev,						/* The hardware device              */
    &g_can2_devinfo,                    /* The hardware device information  */
    (pfn_can_init_t)amdr_can_init,      /* The hardware init function       */
    amhw_plfm_can2_init                 /* pfn_plfm_init                    */
};

/* can设备实例内存静态分配 */
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

