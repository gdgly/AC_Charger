/**
 * \file
 * \brief 交流桩控制计费单元与集中控制器Modbus通讯协议数据处理
 *
 * \internal
 * \par modification history
 * - 1.00 2016-04-26 cod, first implementation
 * \endinternal
 */
#include "ac_modbus_reg_map.h"
#include "modbus/aw_mb_slave.h"
#include "modbus/aw_mb_utils.h"
#include "modbus/aw_mb_comm.h"
#include "aw_task.h"
#include "aw_vdebug.h"
#include "aw_int.h"
#include "aw_ioctl.h"
#include "acp1000/ac_charge_prj_cfg.h"
/******************************************************************************/
#define MB_SLAVE_ADDR      0x01            /**< \brief Modbus通讯本机地址   */
#define MB_SERIAL_COM      1               /**< \brief Modbus通讯串口          */
#define MB_COM_BAUD_RATE   19200            /**< \brief Modbus通讯串口波特率          */
#define MB_COM_PARITY      AW_MB_PAR_NONE  /**< \brief Modbus通讯串口校验方式          */

#define MB_POLL_TASK_PRI       5           /**< \brief 轮询函数任务优先级         */
#define MB_TASK_STACK_SIZE     4096        /**< \brief Modbus从站任务栈大小         */

/******************************************************************************/
aw_local struct modbus_reg_map  *gp_mb_reg_map;  /**< \brief 保存modbus寄存器表  */
/******************************************************************************/

/* 遥信---读寄存器  */
aw_local aw_mb_exception_t remote_signal_reg_read (uint8_t  *p_buf,
                                                   uint16_t  addr,
                                                   uint16_t  num)
{
    struct aw_remote_signal_reg *p_rm_sig_reg = &gp_mb_reg_map->rm_signal_reg;
    uint16_t                    *p_regbuf     = (uint16_t *)p_rm_sig_reg;
    uint16_t                     index        = addr - RM_SIGNAL_REG_ADDR;

#if 1
    if ((addr + num) >
        (RM_SIGNAL_REG_ADDR + RM_SIGNAL_REG_NUM)) {
        return AW_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
    aw_mb_regcpy(p_buf, p_regbuf + index, num);
    modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */
#endif

    return AW_MB_EXP_NONE;
}

/* 遥信---读寄存器  */
aw_local
aw_mb_exception_t remote_measure_charge_dat_reg_read (uint8_t  *p_buf,
                                                      uint16_t  addr,
                                                      uint16_t  num)
{
    struct aw_charger_data *p_charge_reg = &gp_mb_reg_map->rm_measure_reg.charger_data;
    uint16_t               *p_regbuf     = (uint16_t *)p_charge_reg;
    uint16_t                index        = addr - RM_MEASURE_CHARGING_DAT_REG_ADDR;

    if ((addr + num) >
    (RM_MEASURE_CHARGING_DAT_REG_ADDR + RM_MEASURE_CHARGING_DAT_REG_NUM)) {
    return AW_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
    aw_mb_regcpy(p_buf, p_regbuf + index, num);
    modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */

    return AW_MB_EXP_NONE;
}

/* 遥信---读寄存器  */
aw_local
aw_mb_exception_t remote_measure_charge_usr_reg_read (uint8_t  *p_buf,
                                                      uint16_t  addr,
                                                      uint16_t  num)
{
    struct aw_charger_data *p_charge_reg = &gp_mb_reg_map->rm_measure_reg.usr_info;
    uint16_t               *p_regbuf     = (uint16_t *)p_charge_reg;
    uint16_t                index        = addr - RM_MEASURE_CHARGING_USR_REG_ADDR;

    if ((addr + num) >
        (RM_MEASURE_CHARGING_USR_REG_ADDR +
         RM_MEASURE_CHARGING_USR_REG_NUM)) {
        return AW_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
    aw_mb_regcpy(p_buf, p_regbuf + index, num);
    modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */

    return AW_MB_EXP_NONE;
}

/* 遥信---整机数据  */
aw_local
aw_mb_exception_t remote_measure_charge_pile_reg_read (uint8_t  *p_buf,
                                                      uint16_t  addr,
                                                      uint16_t  num)
{
    struct aw_charger_data *p_charge_reg = &gp_mb_reg_map->rm_measure_reg.charger_wdata;
    uint16_t               *p_regbuf     = (uint16_t *)p_charge_reg;
    uint16_t                index        = addr - RM_MEASURE_CHARGING_WDAT_REG_ADDR;

    if ((addr + num) >
        (RM_MEASURE_CHARGING_WDAT_REG_ADDR +
         RM_MEASURE_CHARGING_WDAT_REG_NUM )) {
        return AW_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
    aw_mb_regcpy(p_buf, p_regbuf + index, num);
    modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */

    return AW_MB_EXP_NONE;
}


/* 遥信---卡寄存器  */
aw_local
aw_mb_exception_t remote_measure_charge_card_reg_read (uint8_t  *p_buf,
                                                       uint16_t  addr,
                                                       uint16_t  num)
{
    struct aw_s50_card *p_s50_card = &gp_mb_reg_map->rm_measure_reg.s50_card;
    uint16_t           *p_regbuf   = (uint16_t *)p_s50_card;
    uint16_t           index       = addr - RM_MEASURE_CHARGING_CARD_REG_ADDR;

    if ((addr + num) >
        (RM_MEASURE_CHARGING_CARD_REG_ADDR + RM_MEASURE_CHARGING_CARD_REG_NUM)) {
        return AW_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
    aw_mb_regcpy(p_buf, p_regbuf + index, num);
    modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */

    return AW_MB_EXP_NONE;
}


/******************************************************************************/
/* 遥调---时间设置判断 */
aw_local int remote_adj_time_judge (const uint8_t *p_buf, uint16_t num)
{
    uint8_t   i;
    uint16_t  reg;

    for (i = 0; i < num; i++) {

        reg = (uint16_t)((p_buf[i << 1]) << 8) | p_buf[(i << 1) + 1];

        switch (i) {

        case RM_ADJ_TIME_YEAR_REG_OFFSET:
            if ((reg < CUR_TIME_SET_YEAR_MIN) || \
                (reg > CUR_TIME_SET_YEAR_MAX)) {
                goto __exit;
            }
            break;

        case RM_ADJ_TIME_MONTH_REG_OFFSET:
            if ((reg < 1) || (reg > 12)) {
                goto __exit;
            }
            break;

        case RM_ADJ_TIME_DAY_REG_OFFSET:
            if ((reg < 1) || (reg > 31)) {
                goto __exit;
            }
            break;

        case RM_ADJ_TIME_HOUR_REG_OFFSET:
            if (reg > 23) {
                goto __exit;
            }
            break;

        case RM_ADJ_TIME_MINUTE_REG_OFFSET:
        case RM_ADJ_TIME_SECOND_REG_OFFSET:
            if (reg > 59) {
                goto __exit;
            }
            break;

        default:
            aw_assert(0);
            break;

        }
    }

__exit:
    if (i != num) {
        return AW_ERROR;
    } else {
        return AW_OK;
    }
}

/* 遥调---对时数据设置  */
aw_local aw_mb_exception_t remote_adj_time_reg_write (uint8_t  *p_buf,
                                                      uint16_t  addr,
                                                      uint16_t  num)
{
    aw_mb_exception_t                  exception   = AW_MB_EXP_NONE;
    struct aw_charger_time *p_time_data = \
                                      &gp_mb_reg_map->rm_adjust_reg.time;
    uint16_t                          *p_regbuf    = (uint16_t *)p_time_data;
    uint16_t                           index       = 0;
    uint8_t                            i           = 0;

    /* 设置时间  */
    struct aw_charger_time time;
    struct mb_func_cb_structure *p_func_cb = \
                    modbus_func_cb_get(gp_mb_reg_map, TIME_SET_FUNC);

    if (num < RM_ADJ_TIME_REG_NUM ) {
        return AW_MB_EXP_ILLEGAL_DATA_VALUE;
    }
    num = num > RM_ADJ_TIME_REG_NUM ? RM_ADJ_TIME_REG_NUM : num;

    aw_mb_regcpy((uint16_t *)&time, p_buf,  num);

    if (remote_adj_time_judge(p_buf, RM_ADJ_TIME_REG_NUM) != AW_OK) {
        return AW_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    if (p_func_cb->mb_func_cb != NULL) {
        if (p_func_cb->mb_func_cb(p_func_cb->p_arg, NULL, 0, &time) != AW_OK) {
            return AW_MB_EXP_SLAVE_DEVICE_FAILURE;
        }
    }

    modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
    aw_mb_regcpy(p_regbuf + index, p_buf, num);
    aw_mb_regcpy(&gp_mb_reg_map->rm_measure_reg.charger_data.local_time, p_buf, 6);

    modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */

    return exception;

}
/* 遥调---整桩数据设置  */
aw_local aw_mb_exception_t remote_adj_pile_reg_write (uint8_t  *p_buf,
                                                      uint16_t  addr,
                                                      uint16_t  num)
{
    aw_mb_exception_t                  exception   = AW_MB_EXP_NONE;
    struct aw_remote_adjust_pile_data *p_pile_data = \
                                        &gp_mb_reg_map->rm_adjust_reg.pile_data;
    uint16_t                          *p_regbuf    = (uint16_t *)p_pile_data;
    uint16_t                           index       = addr - RM_ADJ_PILE_REG_ADDR;

    num = num > RM_ADJ_PILE_REG_NUM ? RM_ADJ_PILE_REG_NUM : num;

    modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
    aw_mb_regcpy(p_regbuf + index, p_buf, num);
    modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */

    /* 电价遥调 */
    if (addr <= (RM_ADJ_CHARGE_PRICE_ADDR) &&
        (addr + num) >= (RM_ADJ_CHARGE_PRICE_ADDR + RM_ADJ_CHARGE_PRICE_NUM)) {

        struct mb_func_cb_structure *p_func_cb = \
                        modbus_func_cb_get(gp_mb_reg_map, CHARGE_PRICE_FUNC);
        if ((NULL != p_func_cb) && (p_func_cb->mb_func_cb)) {
            index = (RM_ADJ_CHARGE_PRICE_ADDR - addr) << 1;
            p_func_cb->mb_func_cb( p_func_cb->p_arg,
                                   NULL,
                                   0,
                                   (void *)&p_buf[index]);
        }
    }

    /* 桩ID */
    if (addr <= (RM_ADJ_PILE_ID_ADDR) &&
        (addr + num) >= (RM_ADJ_PILE_ID_ADDR + RM_ADJ_PILE_ID_NUM)) {

        struct mb_func_cb_structure *p_func_cb = \
                        modbus_func_cb_get(gp_mb_reg_map, PILE_ID_FUNC);
        if ((NULL != p_func_cb) && (p_func_cb->mb_func_cb)) {
            index = (RM_ADJ_PILE_ID_ADDR - addr) << 1;
            p_func_cb->mb_func_cb( p_func_cb->p_arg,
                                   NULL,
                                   0,
                                   (void *)&p_buf[index]);
        }
    }

    return exception;
}

/* 遥调---整桩数据设置  */
aw_local aw_mb_exception_t remote_adj_usr_reg_write (uint8_t  *p_buf,
                                                     uint16_t  addr,
                                                     uint16_t  num)
{
    aw_mb_exception_t                  exception   = AW_MB_EXP_NONE;
    struct aw_remote_adjust_usr_ctrl  *p_usr_data     = \
                                        &gp_mb_reg_map->rm_adjust_reg.usr_ctrl;
    uint16_t                          *p_regbuf    = (uint16_t *)p_usr_data;
    int index                                      = addr - RM_ADJ_USR_REG_ADDR;

    num = num > RM_ADJ_USR_REG_NUM ? RM_ADJ_USR_REG_NUM : num;

    modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
    aw_mb_regcpy(p_regbuf + index, p_buf, num);
    modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */

    /* 充电接口标志 */
    if (addr <= (RM_ADJ_USR_CHARGE_INTERFACE_ADDR) &&
        (addr + num) >= (RM_ADJ_USR_CHARGE_INTERFACE_ADDR + RM_ADJ_USR_CHARGE_INTERFACE_NUM)) {

        struct mb_func_cb_structure *p_func_cb = \
                        modbus_func_cb_get(gp_mb_reg_map, CHARGE_INTERFACE_FUNC);
        if ((NULL != p_func_cb) && (p_func_cb->mb_func_cb)) {
            index = (RM_ADJ_USR_CHARGE_INTERFACE_ADDR - addr) << 1;
            p_func_cb->mb_func_cb( p_func_cb->p_arg,
                                   NULL,
                                   0,
                                   (void *)&p_buf[index]);
        }
    }

    /* */
    if (addr <= (RM_ADJ_USR_CARD_KEY_ADDR) &&
        (addr + num) >= (RM_ADJ_USR_CARD_KEY_ADDR + RM_ADJ_USR_CARD_KEY_NUM)) {

        struct mb_func_cb_structure *p_func_cb = \
                        modbus_func_cb_get(gp_mb_reg_map, CARD_KEY_LOAD_FUNC);
        if ((NULL != p_func_cb) && (p_func_cb->mb_func_cb)) {
            index = (RM_ADJ_USR_CARD_KEY_ADDR - addr) << 1;
            p_func_cb->mb_func_cb( p_func_cb->p_arg,
                                   NULL,
                                   0,
                                   (void *)&p_buf[index]);
        }
    }

    if (addr <= (RM_ADJ_USR_ID_ADDR) &&
       (addr + num) >= (RM_ADJ_USR_ID_ADDR + RM_ADJ_USR_ID_NUM)) {

       struct mb_func_cb_structure *p_func_cb = \
                       modbus_func_cb_get(gp_mb_reg_map, USR_ID_SAVE_FUNC);
       if ((NULL != p_func_cb) && (p_func_cb->mb_func_cb)) {
           index = (RM_ADJ_USR_ID_ADDR - addr) << 1;
           p_func_cb->mb_func_cb( p_func_cb->p_arg,
                                  NULL,
                                  0,
                                  (void *)&p_buf[index]);
       }
    }

    if (addr <= (RM_ADJ_USR_BALANCE_ADDR) &&
        (addr + num) >= (RM_ADJ_USR_BALANCE_ADDR + RM_ADJ_USR_BALANCE_NUM)) {

        struct mb_func_cb_structure *p_func_cb = \
                      modbus_func_cb_get(gp_mb_reg_map, USR_ID_BALANCE_FUNC);
        if ((NULL != p_func_cb) && (p_func_cb->mb_func_cb)) {
            index = (RM_ADJ_USR_BALANCE_ADDR - addr) << 1;
            p_func_cb->mb_func_cb( p_func_cb->p_arg,
                                 NULL,
                                 0,
                                 (void *)&p_buf[index]);
        }
    }

    if (addr <= (RM_ADJ_USR_CHARGE_ENERGY_ADDR) &&
        (addr + num) >= (RM_ADJ_USR_CHARGE_ENERGY_ADDR + RM_ADJ_USR_CHARGE_ENERGY_NUM)) {

        struct mb_func_cb_structure *p_func_cb = \
                      modbus_func_cb_get(gp_mb_reg_map, CHARGE_ENERGY_FUNC);
        if ((NULL != p_func_cb) && (p_func_cb->mb_func_cb)) {
            index = (RM_ADJ_USR_CHARGE_ENERGY_ADDR - addr) << 1;
            p_func_cb->mb_func_cb( p_func_cb->p_arg,
                                 NULL,
                                 0,
                                 (void *)&p_buf[index]);
        }
    }

    if (addr <= (RM_ADJ_USR_AUTH_FAIL_ADDR) &&
        (addr + num) >= (RM_ADJ_USR_AUTH_FAIL_ADDR + RM_ADJ_USR_AUTH_FAIL_NUM)) {

        struct mb_func_cb_structure *p_func_cb = \
                      modbus_func_cb_get(gp_mb_reg_map, AUTH_FAILE_REASON);
        if ((NULL != p_func_cb) && (p_func_cb->mb_func_cb)) {
            index = (RM_ADJ_USR_AUTH_FAIL_ADDR - addr) << 1;
            p_func_cb->mb_func_cb( p_func_cb->p_arg,
                                 NULL,
                                 0,
                                 (void *)&p_buf[index]);
        }
    }

    return exception;
}

/******************************************************************************/

/******************************************************************************/
/* 遥控---枪控制  */
aw_local aw_mb_exception_t remote_ctrl_gun_reg_write (uint8_t  *p_buf,
                                                      uint16_t  addr,
                                                      uint16_t  num,
                                                      uint16_t  gun_num)
{
    aw_mb_exception_t                 exception  = AW_MB_EXP_NONE;
    struct aw_charg_gun_ctrl_data    *p_gun_info = \
                        &gp_mb_reg_map->rm_ctrl_reg.gun_ctrl_data[0];
    struct mb_func_cb_structure      *p_mb_func  = NULL;
    uint16_t                         *p_regbuf   = (uint16_t *)p_gun_info;
    int                               err        = 0;
    uint16_t                          index;

    /* 获取枪信息寄存器基地址  */
    index     = addr - RM_CTRL_REG_ADDR;

//todo 目前设置为写单个寄存器，此处无需判断
//    /* 访问地址范围判断 */
//    if ((num > RM_CTRL_GUN_REG_NUM) ||
//        ((addr + num) > (base_addr + RM_CTRL_GUN_REG_NUM))) {
//        return AW_MB_EXP_ILLEGAL_DATA_VALUE;
//    }

    /* 值判断  */
    if ((p_buf[1] != RM_CTRL_DATA_VAL_RESET) && \
        (p_buf[1] != RM_CTRL_DATA_VAL_SET)) {
        return AW_MB_EXP_ILLEGAL_DATA_VALUE;
    }

    switch (index) {

    /** 遥控--允许充电控制   */
    case RM_CTRL_ALLOW_CHARGING_ADDR_OFFSET:
        p_mb_func = modbus_func_cb_get(gp_mb_reg_map, ALLOW_CHARGING_FUNC);
        break;

    /** 遥控--启动充电   */
    case RM_CTRL_CHARGING_STARTUP_ADDR_OFFSET:
        p_mb_func = modbus_func_cb_get(gp_mb_reg_map, CHARGING_STARTUP_FUNC);
        break;

    /** 遥控--解锁屏幕  */
    case RM_CTRL_UNLOCK_SCREEN_ADDR_OFFSET:
        p_mb_func = modbus_func_cb_get(gp_mb_reg_map, UNLOCK_SCREEN_FUNC);
        break;

    /** 遥控--4G通讯状态  */
    case RM_CTRL_COMM_4G_STAT_ADDR_OFFSET:
        p_mb_func = modbus_func_cb_get(gp_mb_reg_map, COMM_4G_STAT_FUNC);
        break;

    /** 遥控--预约充电  */
    case RM_CTRL_ORDER_CHARGING_ADDR_OFFSET:
        p_mb_func = modbus_func_cb_get(gp_mb_reg_map, ORDER_CHARGING_FUNC);
        break;

    default:
//        aw_assert(0);  //todo 保留区不操作
        break;
    }

    if (p_mb_func->mb_func_cb) {
        err = p_mb_func->mb_func_cb(p_mb_func->p_arg,
                                    NULL,
                                    gun_num,
                                    (void *)p_buf[1]);
    }

    if (err != AW_OK) {
        exception = AW_MB_EXP_SLAVE_DEVICE_FAILURE;
    } else {
        modbus_reg_map_lock(gp_mb_reg_map); /* 读取保护  */
        aw_mb_regcpy(p_regbuf + index, p_buf, num);
        modbus_reg_map_unlock(gp_mb_reg_map); /* 读取保护  */
    }

    return exception;
}

/******************************************************************************/
/**
 * \brief 写寄存器
*/
aw_local aw_mb_exception_t wr_reg_func_callback (aw_mb_slave_t slave,
                                                 uint8_t      *p_buf,
                                                 uint16_t      addr,
                                                 uint16_t      num)
{
    aw_mb_exception_t exception = AW_MB_EXP_NONE;
    uint16_t          cur_addr  = addr;
    uint16_t          index     = num;

    while (cur_addr < (addr + index)) {

        /* 对时 */
        if (cur_addr == RM_ADJ_TIME_REG_ADDR) {
            exception = remote_adj_time_reg_write(p_buf, cur_addr, num);
            cur_addr += RM_ADJ_TIME_REG_NUM;
            num      -= RM_ADJ_TIME_REG_NUM;

        /* 电价与桩编号 */
        } else if ((cur_addr >= RM_ADJ_PILE_REG_ADDR) &&
                 ((cur_addr + num) <= (RM_ADJ_PILE_REG_ADDR + RM_ADJ_PILE_REG_NUM)) ) {
            exception = remote_adj_pile_reg_write(p_buf, cur_addr, num);
            cur_addr += RM_ADJ_PILE_REG_NUM;
            num      -= RM_ADJ_PILE_REG_NUM;

        /* 用户ID 用户余额， 充电电量等 */
        } else if ((cur_addr >= RM_ADJ_USR_REG_ADDR) &&
                  ((cur_addr + num) <= (RM_ADJ_USR_REG_ADDR + RM_ADJ_USR_REG_NUM)) ) {
            exception = remote_adj_usr_reg_write(p_buf, cur_addr, num);
            cur_addr += RM_ADJ_USR_REG_NUM;
            num      -= RM_ADJ_USR_REG_NUM;

        /* 摇控 */
        } else if ((cur_addr >= RM_CTRL_REG_ADDR) &&
                ((cur_addr + num) <= (RM_CTRL_REG_ADDR + RM_CTRL_GUN_REG_NUM)) ) {
            exception = remote_ctrl_gun_reg_write(p_buf, cur_addr, num, 1);
            cur_addr += RM_CTRL_GUN_REG_NUM;
            num      -= RM_CTRL_GUN_REG_NUM;

        } else {
            exception = AW_MB_EXP_ILLEGAL_DATA_ADDRESS;
        }
    }
    return exception;
}

/**
 * \brief 读寄存器
*/
aw_local aw_mb_exception_t rd_reg_func_callback (aw_mb_slave_t slave,
                                                 uint8_t      *p_buf,
                                                 uint16_t      addr,
                                                 uint16_t      num)
{
    aw_mb_exception_t exception = AW_MB_EXP_NONE;
    uint16_t          cur_addr  = addr;
    uint16_t          index     = num;
    uint8_t          *p_cur_buf = p_buf;
    struct mb_func_cb_structure      *p_mb_func  = NULL;

    while (cur_addr < (addr + index)) {
       /* 对时 */
       if ((cur_addr >= RM_SIGNAL_REG_ADDR) &&
           ((cur_addr + num) <= (RM_SIGNAL_REG_ADDR + RM_SIGNAL_REG_NUM))) {
           exception = remote_signal_reg_read(p_cur_buf, cur_addr, num);
           cur_addr  += RM_ADJ_TIME_REG_NUM;
           num       -= RM_ADJ_TIME_REG_NUM;
           p_cur_buf += (RM_ADJ_TIME_REG_NUM << 1);


       }  else if ((cur_addr >= RM_MEASURE_CHARGING_DAT_REG_ADDR) &&
               ((cur_addr + num) <=
       (RM_MEASURE_CHARGING_DAT_REG_ADDR + RM_MEASURE_CHARGING_DAT_REG_NUM))) {

           exception = remote_measure_charge_dat_reg_read(p_cur_buf, cur_addr, num);
           cur_addr  += RM_MEASURE_CHARGING_DAT_REG_NUM;
           num       -= RM_MEASURE_CHARGING_DAT_REG_NUM;
           p_cur_buf += (RM_MEASURE_CHARGING_DAT_REG_NUM << 1);

       }  else if ((cur_addr >= RM_MEASURE_CHARGING_USR_REG_ADDR) &&
               ((cur_addr + num) <= (RM_MEASURE_CHARGING_USR_REG_ADDR +
                                    RM_MEASURE_CHARGING_USR_REG_NUM))) {

           exception = remote_measure_charge_usr_reg_read(p_cur_buf, cur_addr, num);
           cur_addr  += RM_MEASURE_CHARGING_USR_REG_NUM;
           num       -= RM_MEASURE_CHARGING_USR_REG_NUM;
           p_cur_buf += ((RM_MEASURE_CHARGING_USR_REG_NUM) << 1);

       } else if ((cur_addr >= RM_MEASURE_CHARGING_WDAT_REG_ADDR) &&
               ((cur_addr + num) <= (RM_MEASURE_CHARGING_WDAT_REG_ADDR +
                                    RM_MEASURE_CHARGING_WDAT_REG_NUM))) {

           exception = remote_measure_charge_pile_reg_read(p_cur_buf, cur_addr, num);
           cur_addr  += RM_MEASURE_CHARGING_WDAT_REG_NUM;
           num       -= RM_MEASURE_CHARGING_WDAT_REG_NUM;
           p_cur_buf += ((RM_MEASURE_CHARGING_WDAT_REG_NUM) << 1);

       } else if ((cur_addr >= RM_MEASURE_CHARGING_CARD_REG_ADDR) &&
               ((cur_addr + num) <=
      (RM_MEASURE_CHARGING_CARD_REG_ADDR + RM_MEASURE_CHARGING_CARD_REG_NUM))) {

           exception = remote_measure_charge_card_reg_read(p_cur_buf, cur_addr, num);
           cur_addr  += RM_MEASURE_CHARGING_CARD_REG_NUM;
           num       -= RM_MEASURE_CHARGING_CARD_REG_NUM;
           p_cur_buf += (RM_MEASURE_CHARGING_CARD_REG_NUM << 1);


       } else {
           exception = AW_MB_EXP_ILLEGAL_DATA_ADDRESS;
       }
    }
    if (AW_MB_EXP_NONE == exception) {
        p_mb_func = modbus_func_cb_get(gp_mb_reg_map, HUB4G_COMM_STATE);
        p_mb_func->mb_func_cb(p_mb_func->p_arg, NULL, 0, NULL);
    }

    return exception;
}
/******************************************************************************/
/**
 * \brief Modubs从站数据处理任务
*/
aw_local void __mb_hdl_poll (aw_mb_slave_t slave)
{
    aw_mb_err_t err;
    AW_FOREVER {
        /* 从机轮询操作, 当前设置为阻塞接口  */
        if ((err = aw_mb_slave_poll(slave)) != AW_MB_ERR_NOERR) {
            AW_INFOF(("Modbus Slave Poll Failed! mb_err = %d\r\n", err));
        }
    }
}

AW_TASK_DECL_STATIC(modbus_task, MB_TASK_STACK_SIZE);
static aw_mb_slave_t      gp_slave = NULL;

aw_err_t ac_modbus_slave_set_addr (uint8_t addr)
{
    if (NULL != gp_slave) {
        aw_mb_slave_set_addr(gp_slave, addr);
        return AW_OK;
    } else {
        return AW_ERROR;
    }

}
#include "boot/boot_cfg.h"
#include "boot/valid_flag/nvram_valid_flag.h"

#define IMG_UPDATE_FUNC_CODE  0x60 /* 升级时使用的功能码 */
#define IMG_VERSION_FUNC_CODE 0x61 /* 后期版本号时使用的功能码 */

aw_err_t  app_into_boot(void)
{
    aw_err_t  ret = AW_OK;

    struct nvram_valid_flag nvram_valid;

    struct valid_flag  *p_valid = nvram_valid_flag_ctor(&nvram_valid,
                                                        INTO_UPDATE_FLAG,
                                                        NVRAM_VALID_SIZE_256);
    if (NULL == p_valid) {
        return  -AW_EPERM;
    }

    ret = valid_flag_set(p_valid, TRUE);
    if (ret != AW_OK) {
        return  ret;
    }

    NVIC_SystemReset();

    return  ret;
}

/**
 * 升级时回调参数
 */
static struct upgrade_cb_item g_upgrade_cb_item;

//todo
aw_mb_exception_t ac_modbus_update_dat_handle (aw_mb_slave_t slave,
                                               uint8_t      *p_pdubuf,
                                               uint16_t     *p_pdulen)
{
    uint32_t    len         = *p_pdulen;
    uint16_t    curr_addr   = 0;

    aw_mb_exception_t  mb_exp = AW_MB_EXP_NONE;

    if (len < 6) {
        /* p_pdubuf[0]: func code                               */
        /* p_p_pdubuf[1-2]: reg addr ( (buf[2] << 16) ! buf[3]) */
        /* p_p_pdubuf[3-4]: reg nums ( (buf[4] << 16) ! buf[5]) */
        /* p_p_pdubuf[5]  : data bytes */
        /* p_p_pdubuf[n]  : data... */
        return AW_ERROR;
    }

    /* 判断数据量是否合法 */
    if (*p_pdulen < 8) {
        mb_exp =  AW_MB_EXP_ILLEGAL_DATA_VALUE;
        AW_ERRF(("MODBUS_SLAVE_FRAME_LEN err: %d\n", *p_pdulen));
        goto  __boot_modbus_call_end;
    }

    /* 获取功能码（当前帧的第0个字节 ） */
    if (p_pdubuf[0] != IMG_UPDATE_FUNC_CODE) {
        mb_exp =  AW_MB_EXP_ILLEGAL_DATA_VALUE;
        AW_ERRF(("MODBUS_FUN_CODE err: %02x\n", p_pdubuf[0]));
        goto  __boot_modbus_call_end;
    }

    /* 获取当前固件数据包地址（当前帧的第1,2两个字节 ）大端模式 */
    curr_addr = ((p_pdubuf[1]<<8) | p_pdubuf[2]);
    if (curr_addr != 1024) {
        mb_exp =  AW_MB_EXP_ILLEGAL_DATA_ADDRESS;
        AW_ERRF(("MODBUS_FUN_CODE err: %02x\n", p_pdubuf[0]));
        goto  __boot_modbus_call_end;
    }

    if (g_upgrade_cb_item.pfunc_cb) {
        g_upgrade_cb_item.pfunc_cb(g_upgrade_cb_item.p_arg);
    }
    app_into_boot();

__boot_modbus_call_end:
    *p_pdulen = 5;

    return mb_exp;
}


aw_mb_exception_t ac_modbus_version_dat_handle (aw_mb_slave_t slave,
                                               uint8_t      *p_pdubuf,
                                               uint16_t     *p_pdulen)
{
    uint32_t    len         = *p_pdulen;
    uint16_t    curr_addr   = 0;
    const uint8_t version1[20] = ACP1000_VERSION_STRING;
//    const uint8_t version2[20] = "LPC1765 : V6.66";
//    const uint8_t version3[20] = "LPC17xx : V2.22";

    aw_mb_exception_t  mb_exp = AW_MB_EXP_NONE;

    //61 00 01 00 14 ED CD
    if (len < 5) {
       /* p_pdubuf[0]: func code                               */
       /* p_p_pdubuf[1-2]: reg addr ( (buf[2] << 16) ! buf[3]) */
       /* p_p_pdubuf[3-4]: reg nums ( (buf[4] << 16) ! buf[5]) */
       return AW_ERROR;
    }
    len = 20;
    p_pdubuf[1] = len; /* packet len */
    aw_mb_regcpy(&p_pdubuf[2], version1, 10);
    *p_pdulen = len + 2;

//    len = sizeof(version1) + sizeof(version2) + sizeof(version3) + 2;
//
//    p_pdubuf[1] = len; /* packet len */
//    p_pdubuf[2] = 3; /* version total numbers */
//    p_pdubuf[3] = 0; /* version total numbers */
//    aw_mb_regcpy(&p_pdubuf[4], version1, 10);
//    aw_mb_regcpy(&p_pdubuf[4+20], version2, 10);
//    aw_mb_regcpy(&p_pdubuf[4+20+20], version3, 10);
//    *p_pdulen = len + 2;

    return mb_exp;
}
/**
 * \brief Modbus从站处理初始化
*/
int ac_modbus_slave_hdl_init (struct modbus_reg_map *p_mb_reg_map,
                              uint8_t                   slave_addr,
                              uint8_t                   com,
                              uint32_t                  baudrate,
                              uint8_t                   parity)
{
    struct aw_mb_serial_param params;

    params.baud_rate  = baudrate;
    params.parity     = parity;
    params.port       = com;
    params.slave_addr = slave_addr;

    gp_mb_reg_map = p_mb_reg_map;  /* 保存Modbus寄存器列表  */

    gp_slave = aw_mb_slave_init(AW_MB_RTU, &params, NULL);
    if (gp_slave == NULL) {
        AW_INFOF(("Modbus Slave Init Failed!\r\n"));
        return AW_ERROR;
    }
    /* 设置是否使能RS485 */
//    aw_serial_ioctl(com, AM_UART_RS485_ENABLE_SET, (void *)(1));
    aw_serial_ioctl(com, AM_UART_RS485_ENABLE_SET, RS485_ENABLE);

    /* 读寄存器回调  */
    (void)aw_mb_slave_register_callback(gp_slave,
                                        AW_MB_FUNC_HOLDREGISTERS_CALLBACK,
                                        AW_MB_FUNC_CALLBACK_READ,
                                        rd_reg_func_callback);

    /* 写寄存器回调  */
    (void)aw_mb_slave_register_callback(gp_slave,
                                        AW_MB_FUNC_HOLDREGISTERS_CALLBACK,
                                        AW_MB_FUNC_CALLBACK_WRITE,
                                        wr_reg_func_callback);

    /* 注册固件升级命令 */
     aw_mb_slave_register_handler(gp_slave, IMG_UPDATE_FUNC_CODE, ac_modbus_update_dat_handle);
     aw_mb_slave_register_handler(gp_slave, IMG_VERSION_FUNC_CODE, ac_modbus_version_dat_handle);

    /* 开始运行*/
    if (aw_mb_slave_start(gp_slave) != AW_MB_ERR_NOERR) {
        return AW_ERROR;
    }

    /* 初始化轮询任务 */
    AW_TASK_INIT(modbus_task,
                 "modbbus_task",
                 3,
                 MB_TASK_STACK_SIZE,
                 __mb_hdl_poll,
                 (void *)gp_slave);

    /* 启动轮询任务  */
    AW_TASK_STARTUP(modbus_task);

    return AW_OK;
}

void ac_modbus_upgrade_enable()
{
    aw_mb_slave_register_handler(gp_slave, IMG_UPDATE_FUNC_CODE, ac_modbus_update_dat_handle);
}

void ac_modbus_upgrade_disable()
{
    aw_mb_slave_register_handler(gp_slave, IMG_UPDATE_FUNC_CODE, NULL);
}

void ac_modbus_upgrade_callback_set(pfunc_upgrade_cb_t pfunc_upgread_cb, void *p_arg)
{
    g_upgrade_cb_item.p_arg = p_arg;
    g_upgrade_cb_item.pfunc_cb = pfunc_upgread_cb;
}

int modbus_func_cb_register (struct modbus_reg_map    *p_this,
                             enum mb_func_cb_type      type,
                             mb_func_cb_t              func_cb,
                             void                      *p_arg)
{
    if (type >= MAX_FUNC_NUM) {
        return AW_ERROR;
    }

    modbus_reg_map_lock(p_this);
    p_this->mb_func_cb[type].fun_type   = type;
    p_this->mb_func_cb[type].mb_func_cb = func_cb;
    p_this->mb_func_cb[type].p_arg      = p_arg;
    modbus_reg_map_unlock(p_this);

    return AW_OK;
}

struct mb_func_cb_structure *modbus_func_cb_get (struct modbus_reg_map *p_this,
                                                 enum mb_func_cb_type      type)
{
    if (type >= MAX_FUNC_NUM) {
        return NULL;
    }

    return &p_this->mb_func_cb[type];
}
