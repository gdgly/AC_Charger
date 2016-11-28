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
 * \brief DGUS串口屏Modbus通信协议数据寄存器定义
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-26  lnk, first implementation
 * \endinternal
 */
#ifndef __ACP1000_DGUS_REG_MAP_H 
#define __ACP1000_DGUS_REG_MAP_H

#include "apollo.h"
#include "aw_sem.h"
#include "aw_timer.h"
#include "aw_spinlock.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/** \brief DGUS可读变量开始地址 */
#define AW_MB_DGUS_READ_START_ADDR 0x1000

/** \brief DGUS可读变量最大个数 */
#define AW_MB_DGUS_READ_MAX_NUM  50

/** \brief DGUS可写变量开始地址 */
#define AW_MB_DGUS_WRITE_START_ADDR 0x2000

/** \brief DGUS可写变量最大个数 */
#define AW_MB_DGUS_WRITE_MAX_NUM 11

/** \brief 保存回调回调函数最大个数 */
#define __MB_FUNC_CB_NUM_MAX     11

/**< \brief DGUS显示屏需要读的数据 */
struct aw_mb_dgus_rd_reg {
    /* DGUS 读的数据 */
    uint16_t card_stat;     /**< \brief 刷卡状态 \ref grp_card_detect_stat */
    uint16_t card_cnt;      /**< \brief 刷卡计数器,正在充电，其他卡不响应,相同卡加1 */
    uint16_t card_id[4];    /**< \brief 用户ID0~3 LSB */
    uint16_t pile_stat;     /**< \brief 桩异常状态 \ref grp_pile_stat */ 
    uint16_t pile_order;    /**< \brief 桩预约状态 \ref grp_pile_order_stat */
    uint16_t balance_stat;  /**< \brief 余额不足状态 \ref grp_pile_balance_stat */
    uint16_t gun_stat;      /**< \brief 插枪状态 \ref grp_gun_stat */
    uint16_t work_stat;     /**< \brief 充电机工作状态 \ref grp_work_stat */
    uint16_t used_time;     /**< \brief 充电时间 单位:分钟 */
    uint16_t charge_stat;   /**< \brief 充电运行状态 */
    uint16_t card_balance;  /**< \brief 卡余额 单位    :0.1元 */
    uint16_t used_amount;   /**< \brief 消费金额 单位:0.1元 */
    uint16_t used_energy;   /**< \brief 充电电量 单位:0.1度 */      
    uint16_t stop_reason;   /**< \brief 充电停止原因  \ref grp_charge_stop_reason */
    uint16_t usr_balance[2];   /**< \brief 用户余额, 大端存储 */
    uint16_t usr_id[8];        /**< \brief 用户ID, 大端存储 */
    uint16_t pile_err_reason;  /**< \brief 异常原因 */
    uint16_t upgrade_flag;     /**< \brief 桩升级标志 0xAA: 未升级； 0x55：升级中 */

    uint16_t admin_flag;       /**< \brief 管理员标志 0xAA: 普通模式； 0x55：管理员模式 */
    uint16_t hub4g_addr;       /**< \brief 集中器通信地址 */
    int16_t  pile_temp;        /**< \brief 桩温度 单位0.1℃，偏移-50度 */
    uint16_t input_vol;        /**< \brief 输入电压 单位0.1V */
    uint16_t input_curr;       /**< \brief 输入电流 单位0.001A */
    uint16_t run_time;         /**< \brief 总运行时间 单位分钟 */
    uint16_t err_cnt;          /**< \brief 异常次数 */
    uint16_t charge_cnt;       /**< \brief 充电次数 */
    uint16_t bg_state;         /**< \brief 后台通信情况，0:正常，1:异常 */
    uint16_t ammeter_state;    /**< \brief 电表通信情况，0:正常，1:异常 */
    uint16_t cardreader_state; /**< \brief 读卡器通信情况，0:正常，1:异常 */
    uint16_t vol_state;        /**< \brief 电压健康情况，0:正常，1:异常 */
    uint16_t hvb_state;        /**< \brief 高压板通信情况，0:正常，1:异常 */

    uint8_t pile_id[16];       /**< \brief 桩ID缓冲区（字符串显示） */
};

/**< \brief DGUS显示屏需要写的数据 */
struct aw_mb_dgus_wr_reg {
    /* DGUS 写的数据 */
    uint16_t charge_ctrl;        /**< \brief 充电控制 \ref grp_charge_ctrl */
    uint16_t charge_way;         /**< \brief 充电方式 \ref grp_charge_way  */
    uint16_t charge_amount;      /**< \brief 充电金额 单位:0.1元                                       */
    uint16_t charge_energy;      /**< \brief 充电电量 单位:0.1度                                       */
    uint16_t charge_time;        /**< \brief 充电时间 单位:分钟                                            */
    uint16_t card_state_clr;     /**< \brief 清除卡的状态 */
    uint16_t amount_state_clr;   /**< \brief 清除余额不足的状态 */
    uint16_t accout_exit_cmd;    /**< \brief 退出账户 */
    uint16_t admin_exit_cmd;     /**< \brief 退出管理员模式 */
    uint16_t hub4g_addr_set;     /**< \brief 设置于集中器通信的地址 */

};

/**
 * \brief Modbus写寄存器回调函数索引
 */
typedef enum aw_mb_dugs_func_cb_type{
    FUNC_CHARGE_CTRL   = 0,
    FUNC_CHARGE_WAY    = 1,
    FUNC_CHARGE_AMOUNT = 2,
    FUNC_CHARGE_ENERGY = 3,
    FUNC_CHARGE_TIME   = 4,
    FUNC_CARD_STATE_CLR= 5,
    FUNC_AMOUNT_STATE_CLR= 6, /* 余额状态清除命令 */
    FUNC_ACCOUT_EXIT_CMD = 7, /* 账户退出命令 */
    FUNC_ADMIN_EXIT_CMD  = 8, /* 管理员模式退出命令 */
    FUNC_HUB4G_ADDR_CMD  = 9, /* 地址设置命令 */
    FUNC_DUGS_COMM_STATE = 10, /* 串口屏通信状态 */
} aw_mb_dugs_func_cb_type_t;

/**
 * \brief Modbus写寄存器回调函数类型
 *
 * \param p_arg:回调参数
 * \param val  :对应类型寄存器值
 *
 * return 0:成功 -1:失败
 */
typedef int (*pfn_mb_dugs_cb_t) (void *p_arg, uint16_t val);


/**
 * \brief Modbus写寄存器回调函数结构
 */
struct aw_mb_dgus_func_cb_block {
    aw_mb_dugs_func_cb_type_t fun_type;
    pfn_mb_dugs_cb_t          pfn_mb_dgus_cb;
    void                     *p_arg;
};

/**< \brief DGUS显示屏需要读、写的数据   */
struct aw_mb_dgus_reg_map {
    struct aw_mb_dgus_rd_reg rd_reg;
    
    struct aw_mb_dgus_wr_reg wr_reg;
    
    /** \brief 写数据回调函数信息 */
    struct aw_mb_dgus_func_cb_block mb_dgus_funcs[__MB_FUNC_CB_NUM_MAX];
    
    AW_MUTEX_DECL(lock);    /**< \brief 读写寄存器保护锁  */
};


/**
 * \brief 读卡状态
 * \anchor grp_card_detect_stat
 * @{
 */
#define AW_MB_DGUS_CARD_STAT_IDLE       0x00     /**< \brief 没有刷卡 */
#define AW_MB_DGUS_CARD_STAT_SUCCESS    0x55     /**< \brief 刷卡成功 */
#define AW_MB_DGUS_CARD_STAT_INVALID    0xAA     /**< \brief 无效卡 */
#define AW_MB_DGUS_CARD_STAT_AUTH       0x05     /**< \brief 鉴权中 */
/** @} */

/**
 * \brief 充电桩异常状态
 * \anchor grp_pile_stat
 * @{
 */
#define AW_MB_DGUS_PILE_STAT_NORMAL    0xAA      /**< \brief 桩正常 */
#define AW_MB_DGUS_PILE_STAT_ABNORMAL  0x55      /**< \brief 桩异常 */
/** @} */

/**
 * \brief 充电桩桩预约状态
 * \anchor grp_pile_order_stat
 * @{
 */
#define AW_MB_DGUS_PILE_IS_ORDERED      0x55     /**< \brief 已被预约 */
#define AW_MB_DGUS_PILE_IS_NOT_ORDERED  0xAA     /**< \brief 未预约 */
/** @} */

/**
 * \brief 余额状态(将卡余额与用户设定的金额或电量对比得出) 
 * \anchor grp_pile_balance_stat
 * @{
 * \note 仅按金额和按电量充方式下有效
 */
#define AW_MB_DGUS_BALANCE_ENOUGH        0x55    /**< \brief 充足 */
#define AW_MB_DGUS_BALANCE_NOT_ENOUGH    0xAA    /**< \brief 不足 */
/** @} */

/**
 * \brief 充电枪插状态
 * \anchor grp_gun_stat
 * @{
 */
#define AW_MB_DGUS_GUN_IDLE      0               /**< \brief 未插枪(已拔出) */
#define AW_MB_DGUS_GUN_VALID     0x55            /**< \brief 插枪成功 */
#define AW_MB_DGUS_GUN_ABNORMAL  0xAA            /**< \brief 枪异常 */
/** @} */

/**
 * \brief 充电工作状态
 * \anchor grp_work_stat
 * @{
 */
#define AW_MB_DGUS_WORK_STAT_IDLE     0          /**< \brief 未充电 */
#define AW_MB_DGUS_WORK_STAT_BUSY     0x55       /**< \brief 充电中 */
#define AW_MB_DGUS_WORK_STAT_FINISH   0xAA       /**< \brief 充电完成 */
/** @} */

/**
 * \brief 充电运行状态
 * \anchor grp_charge_stat
 * @{
 */
#define AW_MB_DGUS_CHARGE_STAT_NORMAL    0x55    /**< \brief 正常 */
#define AW_MB_DGUS_CHARGE_STAT_ABNORMAL  0xAA    /**< \brief 异常 */
/** @} */

/**
 * \brief 桩升级状态
 * \anchor grp_work_stat
 * @{
 */
#define AW_MB_DGUS_UPGRADE_BUSY     0x55       /**< \brief 桩升级中 */
#define AW_MB_DGUS_UPGRADE_IDLE     0xAA       /**< \brief 桩未升级 */
/** @} */

/**
 * \brief 充电控制
 * \anchor grp_charge_ctrl
 * @{
 */ 
#define AW_MB_DGUS_CHARGE_CTRL_START    0x01      /**< \brief 开始充电 */
#define AW_MB_DGUS_CHARGE_CTRL_STOP     0x02      /**< \brief 暂停充电 */
#define AW_MB_DGUS_CHARGE_CTRL_EXIT     0x03      /**< \brief 退出充电 */
/** @} */                                         
                                                  
/**                                               
 * \brief 充电方式                                
 * \anchor grp_charge_way                         
 * @{                                             
 */                                               
#define AW_MB_DGUS_CHARGE_WAY_AUTO      0x01      /**< \brief 自动充 */
#define AW_MB_DGUS_CHARGE_WAY_AMOUNT    0x02      /**< \brief 按金额充 */
#define AW_MB_DGUS_CHARGE_WAY_ENERGY    0x03      /**< \brief 按电量充 */
#define AW_MB_DGUS_CHARGE_WAY_TIME      0x04      /**< \brief 按时间充 */
#define AW_MB_DGUS_CHARGE_WAY_APP       0x05      /**< \brief 手机APP充 */
/** @} */

/**
 * \brief 充电停止原因
 * \anchor grp_charge_stop_reason
 * @{
 */
#define AW_MB_DGUS_CHARGE_NONE             0x00   /**< \brief 未充电     */
#define AW_MB_DGUS_CHARGE_FULL             0x01   /**< \brief 车充满     */
#define AW_MB_DGUS_CHARGE_BALANCE_UNDER    0x02   /**< \brief 余额不足   */
#define AW_MB_DGUS_CHARGE_MAN_EXIT         0x03   /**< \brief 人为退出   */
#define AW_MB_DGUS_CHARGE_AMOUNT_RUNOUT    0x04   /**< \brief 定金额用完 */
#define AW_MB_DGUS_CHARGE_ENERGY_RUNOUT    0x05   /**< \brief 定电量用完 */
#define AW_MB_DGUS_CHARGE_TIME_RUNOUT      0x06   /**< \brief 定时间用完 */
#define AW_MB_DGUS_CHARGE_ERR_EXIT         0x07   /**< \brief 异常退出 */
#define AW_MB_DGUS_CHARGE_ERR_BILLING      0x08   /**< \brief 结算异常退出 */
#define AW_MB_DGUS_CHARGE_BG_EXIT          0x09   /**< \brief 后台退出   */
/* 一下为串口电表没有实现的异常情况 串口点表中归于0x07异常代码 */
#define AW_MB_DGUS_CHARGE_CARDREADER       0x0A   /**< \brief 读卡器异常   */
#define AW_MB_DGUS_CHARGE_AMETETER         0x0B   /**< \brief 电表通信异常   */
#define AW_MB_DGUS_CHARGE_CURR             0x0C   /**< \brief 电流异常   */
#define AW_MB_DGUS_CHARGE_OVERVOL          0x0D   /**< \brief 过压异常   */
#define AW_MB_DGUS_CHARGE_UNDERVOL         0x0E   /**< \brief 欠压异常   */
#define AW_MB_DGUS_CHARGE_LIGHT            0x0F   /**< \brief 防雷器异常   */
#define AW_MB_DGUS_CHARGE_SCRAM            0x10   /**< \brief 紧急开关动作   */
#define AW_MB_DGUS_CHARGE_TEMP             0x11   /**< \brief 温度异常   */
#define AW_MB_DGUS_CHARGE_AC               0x12   /**< \brief AC接触器异常   */
/** @} */


/** \brief DGUS串口屏Modbus寄存器表初始化  */
aw_static_inline void aw_mb_dgus_reg_map_init(struct aw_mb_dgus_reg_map *p_this)
{
    uint8_t i = 0;
    AW_MUTEX_INIT(p_this->lock, AW_SEM_Q_PRIORITY);
    
    /* 初始化回调函数块信息*/
    for (i = 0; i < __MB_FUNC_CB_NUM_MAX; i++) {
        p_this->mb_dgus_funcs[i].fun_type   = __MB_FUNC_CB_NUM_MAX;
        p_this->mb_dgus_funcs[i].pfn_mb_dgus_cb = NULL;
    }
    
    p_this->rd_reg.work_stat = AW_MB_DGUS_WORK_STAT_IDLE;
    p_this->rd_reg.card_stat = AW_MB_DGUS_CARD_STAT_IDLE;

    p_this->rd_reg.pile_stat    = AW_MB_DGUS_PILE_STAT_NORMAL;
    p_this->rd_reg.pile_order   = AW_MB_DGUS_PILE_IS_NOT_ORDERED;
    p_this->rd_reg.balance_stat = AW_MB_DGUS_BALANCE_ENOUGH;
    p_this->rd_reg.gun_stat     = AW_MB_DGUS_GUN_IDLE;
    p_this->rd_reg.work_stat    = AW_MB_DGUS_WORK_STAT_IDLE;
    p_this->rd_reg.charge_stat  = AW_MB_DGUS_CHARGE_STAT_NORMAL;
    p_this->rd_reg.card_balance = 0;
    p_this->rd_reg.used_amount  = 0;
    p_this->rd_reg.used_energy  = 0;
    p_this->rd_reg.used_time    = 0;
    p_this->rd_reg.stop_reason  = 0;

    p_this->wr_reg.charge_ctrl   = AW_MB_DGUS_CHARGE_CTRL_EXIT;
    p_this->wr_reg.charge_way    = AW_MB_DGUS_CHARGE_WAY_AUTO;
    p_this->wr_reg.charge_amount = 0;
    p_this->wr_reg.charge_energy = 0;
    p_this->wr_reg.charge_time   = 0;
}

/** \brief Modbus读写操作上锁  */
aw_static_inline void aw_mb_dugs_reg_map_lock(struct aw_mb_dgus_reg_map *p_this)
{
    AW_MUTEX_LOCK(p_this->lock, AW_SEM_WAIT_FOREVER);
}

/** \brief Modbus读写操作解锁  */
aw_static_inline void aw_mb_dugs_reg_map_unlock(struct aw_mb_dgus_reg_map *p_this)
{
    AW_MUTEX_UNLOCK(p_this->lock);
}


/** 
 * \brief 注册一个modbus寄存器设置回调 
 *
 * \param[in] p_this  指向Modusbus寄存器的指针
 * \param[in] type    注册回调函数关联的索引
 * \param[in] func_cb 指向函数的指针
 * \param[in] p_arg   回调函数参数
 * 
 * return 0-成功
 */
int aw_mb_dgus_func_cb_register (struct aw_mb_dgus_reg_map *p_this,
                                 aw_mb_dugs_func_cb_type_t  type,
                                 pfn_mb_dugs_cb_t           func_cb,
                                 void                      *p_arg);

/**
 * \brief 获取一个modbus寄存器回调结构 
 * 
 * \param[in] p_this 指向Modusbus寄存器的指针
 * \param[in] type   注册回调函数关联的索引
 * 
 * \return 保存回调函数信息的指针
 */
struct aw_mb_dgus_func_cb_block *aw_mb_dgus_func_cb_get (
    struct aw_mb_dgus_reg_map *p_this,
    aw_mb_dugs_func_cb_type_t  type);

/**
 *  \brief Modbus 从站处理初始化接口
 *
 *  \param[in] p_mb_reg_map : Modbus寄存器表指针
 *  \param[in] com          : Modbus使用串口号
 *  \param[in] baudrate     : 波特率
 *  \param[in] parity       : 校验： 0无校验， 1奇校验， 2偶校验
 *
 *  \retval AW_OK    : 初始化成功
 *  \retval AW_ERROR : 失败
 *
 **/
int aw_mb_dgus_slave_hdl_init (struct aw_mb_dgus_reg_map *p_mb_reg_map,
                               uint8_t                    slave_addr,
                               uint8_t                    com,
                               uint32_t                   baudrate,
                               uint8_t                    parity);
                                                          

#ifdef __cplusplus
extern }
#endif  /* __cplusplus  */

#endif /* __ACP1000_DGUS_REG_MAP_H */
 
/* end of file */ 
