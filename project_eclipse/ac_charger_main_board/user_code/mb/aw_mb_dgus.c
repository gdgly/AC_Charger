/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ��������DGUS������Modbusͨ��Э�����ݴ���
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-26  lnk, first implementation
 * \endinternal
 */
 
#include "apollo.h"
#include "modbus/aw_mb_slave.h"
#include "modbus/aw_mb_utils.h"
#include "modbus/aw_mb_comm.h"
#include "mb/aw_mb_dgus_regmap.h"
#include "aw_task.h"
#include "aw_vdebug.h"

/**
 * \brief ����Modbus ���� 
 * @{
 */
#define __MB_DGUS_SLAVE_ADDR      0x01            /**< \brief ModbusͨѶ������ַ   */
#define __MB_DGUS_SERIAL_COM      1               /**< \brief ModbusͨѶ����       */
#define __MB_DGUS_COM_BAUD_RATE   9600            /**< \brief ModbusͨѶ���ڲ����� */
#define __MB_DGUS_COM_PARITY      AW_MB_PAR_NONE  /**< \brief ModbusͨѶ����У�鷽ʽ  */

#define __MB_DGUS_POLL_TASK_PRI       2           /**< \brief ��ѯ�����������ȼ� */
#define __MB_DGUS_TASK_STACK_SIZE     4096        /**< \brief Modbus��վ����ջ��С  */
/** @}*/

/**< \brief ����modbus�Ĵ�����  */
aw_local struct aw_mb_dgus_reg_map  *gp_mb_reg_map;  

/*******************************************************************************
forward define 
*******************************************************************************/
/**
 * \brief д�Ĵ���
*/
aw_local aw_mb_exception_t __wr_reg_func_callback (aw_mb_slave_t slave,
                                                   uint8_t      *p_buf,
                                                   uint16_t      addr,
                                                   uint16_t      num);

/**
 * \brief ���Ĵ���
*/
aw_local aw_mb_exception_t __rd_reg_func_callback (aw_mb_slave_t slave,
                                                   uint8_t      *p_buf,
                                                   uint16_t      addr,
                                                   uint16_t      num);
/*******************************************************************************
implement 
*******************************************************************************/                                              
/**
 * \brief Modubs��վ���ݴ�������
*/
aw_local void __mb_dgus_hdl_poll (aw_mb_slave_t slave)
{
    aw_mb_err_t err;
    AW_FOREVER {
        /* �ӻ���ѯ����, ��ǰ����Ϊ�����ӿ�  */
        if ((err = aw_mb_slave_poll(slave)) != AW_MB_ERR_NOERR) {
            AW_INFOF(("Modbus Slave Poll Failed! mb_err = %d\r\n", err));
        }
    }
}

/**
 * \brief Modbus��վ�����ʼ��
*/
int aw_mb_dgus_slave_hdl_init (struct aw_mb_dgus_reg_map *p_mb_reg_map,
                               uint8_t                    slave_addr,
                               uint8_t                    com,
                               uint32_t                   baudrate,
                               uint8_t                    parity)
{
    AW_TASK_DECL_STATIC(modbus_dgus_task, __MB_DGUS_TASK_STACK_SIZE);
    aw_mb_slave_t             slave;
    
    /* �������� */
//    struct aw_mb_serial_param params = {MB_SLAVE_ADDR,
//                                        MB_COM_PARITY,
//                                        MB_SERIAL_COM,
//                                        MB_COM_BAUD_RATE};
    struct aw_mb_serial_param params;

    params.baud_rate  = baudrate;
    params.parity     = parity;
    params.port       = com;
    params.slave_addr = slave_addr;

    gp_mb_reg_map = p_mb_reg_map;  /* ����Modbus�Ĵ����б�  */

    aw_mb_err_t err;
    slave = aw_mb_slave_init(AW_MB_RTU, &params, &err);
    if (slave == NULL) {
        AW_INFOF(("Modbus Slave Init Failed!\r\n, err= %d\r\n", err));
        return AW_ERROR;
    }

    /* ���Ĵ����ص�  */
    (void)aw_mb_slave_register_callback(slave,
                                        AW_MB_FUNC_HOLDREGISTERS_CALLBACK,
                                        AW_MB_FUNC_CALLBACK_READ,
                                        __rd_reg_func_callback);

    /* д�Ĵ����ص�  */
    (void)aw_mb_slave_register_callback(slave,
                                        AW_MB_FUNC_HOLDREGISTERS_CALLBACK,
                                        AW_MB_FUNC_CALLBACK_WRITE,
                                        __wr_reg_func_callback);

    /* ��ʼ����*/
    if (aw_mb_slave_start(slave) != AW_MB_ERR_NOERR) {
        return AW_ERROR;
    }

    /* ��ʼ����ѯ���� */
    AW_TASK_INIT(modbus_dgus_task,
                 "modbus_dgus_task",
                 __MB_DGUS_POLL_TASK_PRI,
                 __MB_DGUS_TASK_STACK_SIZE,
                 __mb_dgus_hdl_poll,
                 (void *)slave);

    /* ������ѯ����  */
    AW_TASK_STARTUP(modbus_dgus_task);

    return AW_OK;
}

/**
 * \brief д�Ĵ���
*/
aw_local aw_mb_exception_t __wr_reg_func_callback (aw_mb_slave_t slave,
                                                   uint8_t      *p_buf,
                                                   uint16_t      addr,
                                                   uint16_t      num)
{
    aw_mb_exception_t exception = AW_MB_EXP_NONE;
    struct aw_mb_dgus_func_cb_block *pfunc_cb_block = NULL;
    struct aw_mb_dgus_wr_reg *p_wr_reg =
        (struct aw_mb_dgus_wr_reg *) (&gp_mb_reg_map->wr_reg);
    uint16_t             *p_regbuf     = (uint16_t *)p_wr_reg;
    uint16_t              index        = 0;
    int                   err          = 0;
    
    if ((addr >= AW_MB_DGUS_WRITE_START_ADDR) && 
        (addr < (AW_MB_DGUS_WRITE_START_ADDR + AW_MB_DGUS_WRITE_MAX_NUM))) {
            
        /* num �ж� */
        if (num != 1) {
            /* 0x06����*/
            return AW_MB_EXP_ILLEGAL_DATA_VALUE;
        }
        
        index = addr - AW_MB_DGUS_WRITE_START_ADDR;
        
        /* ִ�лص� */
        switch (index) {
        
        case FUNC_CHARGE_CTRL:  
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_CHARGE_CTRL);
            break;
            
        case FUNC_CHARGE_WAY:   
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_CHARGE_WAY);
            break;
            
        case FUNC_CHARGE_AMOUNT:
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_CHARGE_AMOUNT);
            break;
            
        case FUNC_CHARGE_ENERGY:
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_CHARGE_ENERGY);
            break;
            
        case FUNC_CHARGE_TIME:
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_CHARGE_TIME);
            break;
            
        case FUNC_CARD_STATE_CLR:
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_CARD_STATE_CLR);
            break;

        case FUNC_AMOUNT_STATE_CLR:
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_AMOUNT_STATE_CLR);
            break;

        case FUNC_ACCOUT_EXIT_CMD:
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_ACCOUT_EXIT_CMD);
            break;

        case FUNC_ADMIN_EXIT_CMD:
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_ADMIN_EXIT_CMD);
            break;

        case FUNC_HUB4G_ADDR_CMD:
            pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_HUB4G_ADDR_CMD);
            break;

        default:
            /* to do */
            break;
        }
        
        if (pfunc_cb_block->pfn_mb_dgus_cb) {
            err = pfunc_cb_block->pfn_mb_dgus_cb(pfunc_cb_block->p_arg,
                    (p_buf[0] << 8 | p_buf[1]));
        }
        
        if (err == 0) {
            aw_mb_dugs_reg_map_lock(gp_mb_reg_map); /* ��ȡ����  */
            aw_mb_regcpy(p_regbuf + index, p_buf, num); /* fix it ��ΪС�ˣ���memcpy */
            aw_mb_dugs_reg_map_unlock(gp_mb_reg_map); /* ��ȡ����  */
        }
    } else {
        return AW_MB_EXP_ILLEGAL_DATA_ADDRESS;
    }

    return exception;
}

/**
 * \brief ���Ĵ���
*/
aw_local aw_mb_exception_t __rd_reg_func_callback (aw_mb_slave_t slave,
                                                   uint8_t      *p_buf,
                                                   uint16_t      addr,
                                                   uint16_t      num)
{
    aw_mb_exception_t exception = AW_MB_EXP_NONE;
    struct aw_mb_dgus_rd_reg *p_rd_reg = &gp_mb_reg_map->rd_reg;
    uint16_t             *p_regbuf     = (uint16_t *)p_rd_reg;
    uint16_t              index        = 0;
    struct aw_mb_dgus_func_cb_block *pfunc_cb_block = NULL;

    pfunc_cb_block = aw_mb_dgus_func_cb_get(gp_mb_reg_map, FUNC_DUGS_COMM_STATE);
    
    /* addr �ж� */
    if ((addr >= AW_MB_DGUS_READ_START_ADDR) && 
        (addr < (AW_MB_DGUS_READ_START_ADDR + AW_MB_DGUS_READ_MAX_NUM))) {
        
        /* num �ж� */
        if ((num > AW_MB_DGUS_READ_MAX_NUM) || \
            ((addr + num) > (AW_MB_DGUS_READ_START_ADDR + AW_MB_DGUS_READ_MAX_NUM))) {
            return AW_MB_EXP_ILLEGAL_DATA_VALUE;
        }
        
        index = addr - AW_MB_DGUS_READ_START_ADDR;
        
        aw_mb_dugs_reg_map_lock(gp_mb_reg_map); /* ��ȡ����  */
        aw_mb_regcpy(p_buf, p_regbuf + index, num); /* fix it ��ΪС�ˣ���memcpy */
        aw_mb_dugs_reg_map_unlock(gp_mb_reg_map); /* ��ȡ����  */

        if (pfunc_cb_block->pfn_mb_dgus_cb) {
           /* ��ʱ����ͨ�������ص� */
           pfunc_cb_block->pfn_mb_dgus_cb(pfunc_cb_block->p_arg, p_buf);
       }

    } else {
        return AW_MB_EXP_ILLEGAL_DATA_ADDRESS;
    }

    return exception;
}


/**
 * \brief ע��һ��modbus�Ĵ������ûص�
 *
 * \param[in] p_this  ָ��Modusbus�Ĵ�����ָ��
 * \param[in] type    ע��ص���������������
 * \param[in] func_cb ָ������ָ��
 * \param[in] p_arg   �ص���������
 *
 * return 0-�ɹ�
 */
int aw_mb_dgus_func_cb_register (struct aw_mb_dgus_reg_map *p_this,
                                 aw_mb_dugs_func_cb_type_t  type,
                                 pfn_mb_dugs_cb_t           func_cb,
                                 void                      *p_arg)
{
    if (type >= __MB_FUNC_CB_NUM_MAX) {
        return AW_ERROR;
    }

    aw_mb_dugs_reg_map_lock(p_this);
    p_this->mb_dgus_funcs[type].fun_type       = type;
    p_this->mb_dgus_funcs[type].pfn_mb_dgus_cb = func_cb;
    p_this->mb_dgus_funcs[type].p_arg          = p_arg;
    aw_mb_dugs_reg_map_unlock(p_this);

    return AW_OK;
}

/**
 * \brief ��ȡһ��modbus�Ĵ����ص��ṹ
 *
 * \param[in] p_this ָ��Modusbus�Ĵ�����ָ��
 * \param[in] type   ע��ص���������������
 *
 * \return ����ص�������Ϣ��ָ��
 */
struct aw_mb_dgus_func_cb_block *aw_mb_dgus_func_cb_get (
    struct aw_mb_dgus_reg_map *p_this,
    aw_mb_dugs_func_cb_type_t  type)
{
    if (type >= __MB_FUNC_CB_NUM_MAX) {
        return NULL;
    }

    return &p_this->mb_dgus_funcs[type];
}


/* end of file */



