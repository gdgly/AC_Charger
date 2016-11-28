/**
 * \file
 * \brief (交流桩)控制计费单元与集中控制器Modbus通讯协议实现
 *
 * \internal
 * \par modification history
 * - 1.00 2016-04-26 cod, first implementation
 * \endinternal
 */
#ifndef AC_MODBUS_REG_MAP_H_
#define AC_MODBUS_REG_MAP_H_
#include "apollo.h"
#include "aw_sem.h"
#include "aw_timer.h"

#define CHARGING_GUN_NUM           1  /**< \brief 充电枪数目          */

#define GUN1  1  /**< \brief 充电枪1          */
#define GUN2  2  /**< \brief 充电枪2          */

/** \brief 获取结构体的Modbus寄存器数          */
#define MB_REG_NUM_GET(structure)   (sizeof(structure) / sizeof(uint16_t))

/** \brief 获取寄存器结构体偏移个数          */
#define MB_REG_OFFSET_GET(structure, mem)  (AW_OFFSET(structure, mem) / sizeof(uint16_t))
/******************************************************************************
 * 遥信数据
 ******************************************************************************/
/** \brief 充电机状态1位状态 */
struct aw_charger_stat_bit {
    //todo 添加了预刷卡
    uint8_t key_store_ok           : 1;  /**< \brief 密钥保存成功 ，0没有保存成功，1密钥保存成功 每次刷卡时清零 */
    uint8_t card_swing_ok2         : 1;  /**< \brief 刷卡成功 ，0刷卡不成功，1刷卡成功 , 收到鉴权结果时置该标志位 */
    uint8_t charger_allow_stat     : 1;  /**< \brief 是否允许充电状态，0不允许充电，1允许充电*/
    uint8_t charger_stat           : 1;  /**< \brief 充电状态，0不充电，1充电*/
    uint8_t screen_lock_stat       : 1;  /**< \brief 锁屏状态，0锁屏。 1不锁屏*/
    uint8_t g4_comm_stat           : 1;  /**< \brief 4g通讯状态，0正常。 1故障*/
    uint8_t pile_order_stat        : 1;  /**< \brief 桩预约状态，0无预约，1预约*/
    uint8_t light_pro_alm          : 1;  /**< \brief 防雷器故障告警  */

    uint8_t charger_overtemp_alm   : 1;  /**< \brief 充电桩过温故障告警  */
    uint8_t flood_alm              : 1;  /**< \brief 水浸故障告警  */
    uint8_t contactor_fault_alm    : 1;  /**< \brief 接触器故障告警  */
    uint8_t door_switch_alm        : 1;  /**< \brief 门禁开关告警, 0关门，1开门 */
    uint8_t ammeter_alm            : 1;  /**< \brief 电表通讯告警  */
    uint8_t cardreader_alm         : 1;  /**< \brief 刷卡机通讯告警  */
    uint8_t ac_in_undervolt_alm    : 1;  /**< \brief 交流输入欠压告警  */
    uint8_t ac_in_overvolt_alm     : 1;  /**< \brief 交流输入过压告警  */
};



/**< \brief 充电机状态1 */
union aw_charger_stat1 {
    struct aw_charger_stat_bit stat1_bit;  /**< \brief 充电机状态1位状态 */
    uint16_t                   stat1;      /**< \brief 充电机状态1位状态 */
};
/******************************************************************************/
struct aw_charging_stop_cause_bit {
    uint8_t manual_stop              : 1;  /**< \brief 充电机人工终止充电 */
    uint8_t guide_test_fail          : 1;  /**< \brief 充电机引导测试不通过   */
    uint8_t batvolt_chk_unusal       : 1;  /**< \brief 充电机检测充电电压检测异常终止   */
    uint8_t door_switch_alm          : 1;  /**< \brief 充电机门禁检测异常终止   */
    uint8_t elect_lock_alm           : 1;  /**< \brief 电子锁异常终止   */
    uint8_t gun_contact_alm          : 1;  /**< \brief 枪接触终止 */
    uint8_t light_pro_unusal_stop    : 1;  /**< \brief 防雷异常终止  */
    uint8_t measure_per_unusal_stop  : 1;  /**< \brief 计量单元异常终止   */

    uint8_t pos_charge_unusal_stop   : 1;  /**< \brief 充电机刷卡外设异常终止   */
    uint8_t background_stop          : 1;  /**< \brief 充电机后台终止充电   */
    uint8_t banlance_notenough_stop  : 1;  /**< \brief 余额不足终止充电   */
    uint8_t ac_in_undervolt_stop     : 1;  /**< \brief 交流输入欠压终止  */
    uint8_t ac_in_overvolt_stop      : 1;  /**< \brief 交流输入过压终止  */
    uint8_t ac_in_overcurr_stop      : 1;  /**< \brief 交流输入过流终止  */
    uint8_t card_swing_ok1           : 1;  /**< \brief 预刷卡成功 ，检测到卡片置为成功 */
    uint8_t reserved                 : 1;  /**< \brief 保留  */
};

/**< \brief 充电停止原因  */
union aw_charging_stop_cause {
    struct aw_charging_stop_cause_bit cause_bit;  /**< \brief 充电停止原因位   */
    uint16_t                          cause;      /**< \brief 充电停止原因 */
};
/******************************************************************************/
/**< \brief 枪状态信息   */
struct aw_charging_gun_stat {
    union aw_charger_stat1       charger_stat1;       /**< \brief 充电机状态1   */
    union aw_charging_stop_cause charging_stop_cause; /**< \brief 充电停止原因   */
};

/**< \brief 遥信数据   */
struct aw_remote_signal_reg {
   struct aw_charging_gun_stat charger_stat[CHARGING_GUN_NUM];  /**< \brief 枪状态信息   */
};
/******************************************************************************/
#define RM_SIGNAL_REG_ADDR       1   /**< \brief 遥信地址          */

/** \brief 遥信寄存器个数          */
#define RM_SIGNAL_REG_NUM       MB_REG_NUM_GET(struct aw_remote_signal_reg)

#define RM_SIGNAL_REG_END_ADDR  (RM_SIGNAL_REG_ADDR + RM_SIGNAL_REG_NUM)
/******************************************************************************
 * 遥测数据
 ******************************************************************************/
/** \brief 整机数据      */
struct aw_charger_whole_data {
    uint16_t charger_interface;        /**< \brief 充电机接口方式（枪的数量）       */
    uint16_t charger_out_volt;         /**< \brief 充电机输出电压       */
    uint16_t charger_out_curr;         /**< \brief 充电机输出电流       */
    uint16_t charger_ambient_temp;     /**< \brief 充电机环境温度       */
    uint16_t now_charge_energy;        /**< \brief 本次充电电量      */
    uint16_t now_charge_amount;        /**< \brief 本次充电金额      */
    uint16_t now_charge_time;          /**< \brief 本次充电时间      */
    uint16_t auth_fail_reason;         /**< \brief 鉴权失败原因      */
    uint16_t meter_rtval_hi_word;      /**< \brief 电表实时读数高字节      */
    uint16_t meter_rtval_lo_word;      /**< \brief 电表实时读数低字节      */
};


/**< \brief 加密卡ID信息   */
struct aw_s50_card {
    uint16_t card_id[2];           /**< \brief 加密卡ID号高字节       */
    uint16_t card_dat[24];         /**< \brief 加密卡数据       */
//    uint16_t card_id_hi_word;  /**< \brief 加密卡ID号高字节       */
//    uint16_t card_id_lo_word;  /**< \brief 加密卡ID号低字节       */
//todo 4.22修改
//    uint16_t section0_1_1;     /**< \brief 扇区0-1-1       */
//    uint16_t section0_1_2;     /**< \brief 扇区0-1-2       */
//    uint16_t section0_1_3;     /**< \brief 扇区0-1-3       */
//    uint16_t section0_1_4;     /**< \brief 扇区0-1-4       */
//    uint16_t section0_1_5;     /**< \brief 扇区0-1-5       */
//    uint16_t section0_1_6;     /**< \brief 扇区0-1-6       */
//    uint16_t section0_1_7;     /**< \brief 扇区0-1-7       */
//    uint16_t section0_1_8;     /**< \brief 扇区0-1-8       */
//
//    uint16_t section0_2_1;     /**< \brief 扇区0-2-1       */
//    uint16_t section0_2_2;     /**< \brief 扇区0-2-2       */
//    uint16_t section0_2_3;     /**< \brief 扇区0-2-3       */
//    uint16_t section0_2_4;     /**< \brief 扇区0-2-4       */
//    uint16_t section0_2_5;     /**< \brief 扇区0-2-5       */
//    uint16_t section0_2_6;     /**< \brief 扇区0-2-6       */
//    uint16_t section0_2_7;     /**< \brief 扇区0-2-7       */
//    uint16_t section0_2_8;     /**< \brief 扇区0-2-8       */
//
//    uint16_t section0_3_1;     /**< \brief 扇区0-3-1       */
//    uint16_t section0_3_2;     /**< \brief 扇区0-3-2       */
//    uint16_t section0_3_3;     /**< \brief 扇区0-3-3       */
//    uint16_t section0_3_4;     /**< \brief 扇区0-3-4       */
//    uint16_t section0_3_5;     /**< \brief 扇区0-3-5       */
//    uint16_t section0_3_6;     /**< \brief 扇区0-3-6       */
//    uint16_t section0_3_7;     /**< \brief 扇区0-3-7       */
//    uint16_t section0_3_8;     /**< \brief 扇区0-3-8       */
};

/**< \brief 充电机对时时间  */
struct aw_charger_time {
    uint16_t  year;          /**< \brief 年 : 2010~2099  */
#define CUR_TIME_SET_YEAR_MAX  2099
#define CUR_TIME_SET_YEAR_MIN  2010
    uint16_t  month;         /**< \brief 月 : 1~12  */
    uint16_t  day;           /**< \brief 日 : 1~31  */
    uint16_t  hour;          /**< \brief 时 : 1~23 */
    uint16_t  minute;        /**< \brief 分 : 0~59 */
    uint16_t  second;        /**< \brief 秒 : 0~59  */
};

/**< \brief 用户信息   */
struct aw_charging_usr_info {
    /** \brief 用户ID所占大小  */
#define RM_ADJ_GUN_USER_ID_NUM   8   //交流桩用户ID未修改
    uint16_t user_id[RM_ADJ_GUN_USER_ID_NUM];    /**< \brief 用户ID  */
    uint16_t user_balance[2];        /**< \brief 用户ID余额高16位：0.01元 */

};

/**< \brief 充电机数据   */
struct aw_charger_data {
    struct aw_charger_time        local_time;           /**< brief RTC时间 */

#define RM_ADJ_TIME_INVL_NUM     24    /**< \brief 时间间隔段数 */
#define RM_ADJ_ELECT_MAX_PRICE   65535 /**< \brief 电量价格最大值    */
#define RM_ADJ_ELECT_MIN_PRICE   10000 /**< \brief 电量价格最小值    */
    /** \brief 时间段充电价格：最低位为0~1点， 单位为0.01元    */
    uint16_t                      time_invl_price[RM_ADJ_TIME_INVL_NUM];

#define RM_ADJ_CHARGER_PILE_ID_NUM   4     /**< \brief 充电桩编号 高位在地址值 大端方式   */
    uint16_t                      pile_id[RM_ADJ_CHARGER_PILE_ID_NUM];
};
/******************************************************************************/
/**< \brief 遥测寄存器   */
struct aw_remote_measure_reg {
    struct aw_charger_data        charger_data;          /**< \brief 充电机数据   */
    struct aw_charging_usr_info   usr_info;              /**< \brief 用户信息      */
    struct aw_charger_whole_data  charger_wdata;         /**< \brief 整机数据       */
    struct aw_s50_card            s50_card;              /**< \brief 加密卡ID信息   */
};
/******************************************************************************
 * 遥测寄存器地址、数目
 ******************************************************************************/
/** \brief 遥测---充电信息寄存器地址（只包含输出电压、电流、环境温度） */
#define RM_MEASURE_CHARGING_DAT_REG_ADDR   100
/** \brief 遥测---充电信息寄存器数（只包含输出电压、电流、环境温度） */
#define RM_MEASURE_CHARGING_DAT_REG_NUM    MB_REG_NUM_GET(struct aw_charger_data)

/** \brief 遥测---充电信息寄存器地址（只包含输出电压、电流、环境温度） */
#define RM_MEASURE_CHARGING_USR_REG_ADDR   180
/** \brief 遥测---充电信息寄存器数（只包含输出电压、电流、环境温度） */
#define RM_MEASURE_CHARGING_USR_REG_NUM    MB_REG_NUM_GET(struct aw_charging_usr_info)

/** \brief 遥测---充电信息寄存器地址（只包含输出电压、电流、环境温度） */
#define RM_MEASURE_CHARGING_WDAT_REG_ADDR   200
/** \brief 遥测---充电信息寄存器数（只包含输出电压、电流、环境温度） */
#define RM_MEASURE_CHARGING_WDAT_REG_NUM    MB_REG_NUM_GET(struct aw_charger_whole_data)

/** \brief 遥测---充电信息寄存器地址（只包含输出电压、电流、环境温度） */
#define RM_MEASURE_CHARGING_CARD_REG_ADDR   2000
/** \brief 遥测---充电信息寄存器数（只包含输出电压、电流、环境温度） */
#define RM_MEASURE_CHARGING_CARD_REG_NUM    MB_REG_NUM_GET(struct aw_s50_card)

/******************************************************************************
 * 遥调数据
 ******************************************************************************/
/** \brief 整桩数据   */
struct aw_remote_adjust_pile_data {
    /** \brief 时间段充电价格：最低位为0~1点， 单位为0.01元    */
    uint16_t                time_invl_price[RM_ADJ_TIME_INVL_NUM];

#define RM_ADJ_CHARGER_PILE_ID_NUM   4     /**< \brief 桩ID寄存器书数   */
    uint16_t                           pile_id[RM_ADJ_CHARGER_PILE_ID_NUM];
} ;
/**< \brief 遥调寄存器业务控制信息  */
struct aw_remote_adjust_usr_ctrl {
    uint16_t                           charger_interface;   /**< \brief 充电机接口方式（枪的数量）       */

    struct aw_charging_usr_info        usr_info;            /**< \brief 用户信息      */

    uint16_t                           now_charge_amount;   /**< \brief 本次充电金额      */
    uint16_t                           now_charge_energy;   /**< \brief 本次充电电量      */

#define RM_ADJ_GUN_CARD_SECRET_KEY_NUM   3
    /**< \brief 卡密钥，低位为高字节  */
    uint16_t                           card_secret_key[RM_ADJ_GUN_CARD_SECRET_KEY_NUM];
    uint16_t                           auth_fail_reason;      /**< \brief 鉴权失败原因   */
    uint16_t                           reserved[6];           /**< \brief 保留    */
};

/**< \brief 遥调寄存器   */
struct aw_remote_adjust_reg {
    /**< \brief 对时时间    */
    struct aw_charger_time             time;
    /** \brief 整桩数据   */
    struct aw_remote_adjust_pile_data  pile_data;
    /** \brief 用户控制信息   */
    struct aw_remote_adjust_usr_ctrl   usr_ctrl;
};
/******************************************************************************
 * 遥调---寄存器地址、数目
 ******************************************************************************/
#define RM_ADJ_TIME_REG_ADDR      1000    /**< \brief 遥调时间基地址   */
/** \brief 遥调时间寄存器数   */
#define RM_ADJ_TIME_REG_NUM       MB_REG_NUM_GET(struct aw_charger_time)

#define RM_ADJ_PILE_REG_ADDR      1006    /**< \brief 遥调整桩基地址   */
/** \brief 遥调整桩寄存器数   */
#define RM_ADJ_PILE_REG_NUM       MB_REG_NUM_GET(struct aw_remote_adjust_pile_data)

/** \brief 用户寄存器机制   */
#define RM_ADJ_USR_REG_ADDR       1100
/** \brief 遥调用户寄存器数   */
#define RM_ADJ_USR_REG_NUM        MB_REG_NUM_GET(struct aw_remote_adjust_usr_ctrl)

/** \brief 时间寄存器机制   */
#define RM_ADJ_ELECT_PRICE_INVL_REG_ADDR   (RM_ADJ_TIME_REG_ADDR + RM_ADJ_TIME_REG_NUM)
/** \brief 时间段充电价格寄存器数   */
#define RM_ADJ_ELECT_PRICE_INVL_REG_NUM    RM_ADJ_TIME_INVL_NUM    /**< \brief 遥调电量价格时段数   */

/* 时间寄存器偏移 */
#define RM_ADJ_TIME_YEAR_REG_OFFSET   0
#define RM_ADJ_TIME_MONTH_REG_OFFSET  1
#define RM_ADJ_TIME_DAY_REG_OFFSET    2
#define RM_ADJ_TIME_HOUR_REG_OFFSET   3
#define RM_ADJ_TIME_MINUTE_REG_OFFSET 4
#define RM_ADJ_TIME_SECOND_REG_OFFSET 5

#define RM_ADJ_USR_CHARGE_INTERFACE_ADDR  (RM_ADJ_USR_REG_ADDR)
#define RM_ADJ_USR_CHARGE_INTERFACE_NUM   (1)

#define RM_ADJ_USR_AUTH_FAIL_ADDR      (RM_ADJ_USR_REG_ADDR + 16)
#define RM_ADJ_USR_AUTH_FAIL_NUM       1

#define RM_ADJ_USR_CARD_KEY_ADDR      (RM_ADJ_USR_REG_ADDR + 13)
#define RM_ADJ_USR_CARD_KEY_NUM       3

#define RM_ADJ_USR_ID_ADDR          (RM_ADJ_USR_REG_ADDR + 1)
#define RM_ADJ_USR_ID_NUM           8

#define RM_ADJ_USR_BALANCE_ADDR    (RM_ADJ_USR_REG_ADDR + 9)
#define RM_ADJ_USR_BALANCE_NUM      2

#define RM_ADJ_USR_CHARGE_ENERGY_ADDR   (RM_ADJ_USR_REG_ADDR + 12)
#define RM_ADJ_USR_CHARGE_ENERGY_NUM    1

#define RM_ADJ_CHARGE_PRICE_ADDR    (RM_ADJ_PILE_REG_ADDR)
#define RM_ADJ_CHARGE_PRICE_NUM      24


#define RM_ADJ_PILE_ID_ADDR          (RM_ADJ_PILE_REG_ADDR + 24)
#define RM_ADJ_PILE_ID_NUM            4

/******************************************************************************
 * 遥控数据
 ******************************************************************************/
/**< \brief 枪控制数据  */
struct aw_charg_gun_ctrl_data {
    uint16_t allow_charging;        /**< \brief 允许充电，禁止充电：0x0055, 允许充电： 0x00AA   */
    uint16_t charging_startup;      /**< \brief 启动充电, 停止：0x0055, 启动： 0x00AA  */
    uint16_t unlock_screen;         /**< \brief 解锁屏幕， 锁屏： 0x0055, 解锁： 0x00AA   */
    uint16_t comm_4g_stat;          /**< \brief 4G通讯状态, 通讯异常： 0x0055, 通讯正常：0x00AA    */
    uint16_t order_charging;        /**< \brief 预约充电, 无预约： 0x0055, 有预约：0x00AA */
    uint16_t reserved[6];           /**< \brief 保留  */
};

/**< \brief 遥控信息   */
struct aw_remote_ctrl_reg {
    struct aw_charg_gun_ctrl_data gun_ctrl_data[CHARGING_GUN_NUM];  /**< \brief 枪控制信息    */
};
/******************************************************************************/
#define RM_CTRL_REG_ADDR        1500                    /**< \brief 遥控寄存器基地址   */
#define RM_CTRL_GUN1_REG_ADDR   RM_CTRL_REG_ADDR        /**< \brief 遥控寄存器枪1地址   */

#define RM_CTRL_GUN_REG_NUM     MB_REG_NUM_GET(struct aw_charg_gun_ctrl_data)

#define RM_CTRL_ALLOW_CHARGING_ADDR_OFFSET     0   /**< \brief 遥控--允许充电控制地址偏移   */
#define RM_CTRL_CHARGING_STARTUP_ADDR_OFFSET   1   /**< \brief 遥控--启动充电地址偏移   */
#define RM_CTRL_UNLOCK_SCREEN_ADDR_OFFSET      2   /**< \brief 遥控--解锁屏幕地址偏移   */
#define RM_CTRL_COMM_4G_STAT_ADDR_OFFSET       3   /**< \brief 遥控--4G通讯状态地址偏移   */
#define RM_CTRL_ORDER_CHARGING_ADDR_OFFSET     4   /**< \brief 遥控--预约充电地址偏移   */

#define RM_CTRL_DATA_VAL_SET     0x00AA  /**< \brief 遥控--设置值  */
#define RM_CTRL_DATA_VAL_RESET   0x0055  /**< \brief 遥控--复位值   */
/******************************************************************************
 * Modbus 寄存器表信息
 ******************************************************************************/
/** \brief modbus寄存器回调类型   */
enum mb_func_cb_type {
    TIME_SET_FUNC         = 0,  /**< \brief 时间设置回调，回调函数中写入类型为aw_charger_time   */
    ALLOW_CHARGING_FUNC   = 1,  /**< \brief 允许充电，写入为0x0055或0x00aa   */
    CHARGING_STARTUP_FUNC = 2,  /**< \brief 启动充电 ,写入为0x0055或0x00aa */
    UNLOCK_SCREEN_FUNC    = 3,  /**< \brief 解锁屏幕,写入为0x0055或0x00aa   */
    COMM_4G_STAT_FUNC     = 4,  /**< \brief 4G通讯异常 ，写入为0x0055或0x00aa  */
    ORDER_CHARGING_FUNC   = 5,  /**< \brief 预约充电  ，写入为0x0055或0x00aa  */
    CARD_KEY_LOAD_FUNC    = 6,  /**< \brief 卡key下发事件  */
    USR_ID_SAVE_FUNC      = 7,  /**< \brief 用户ID下发事件  */
    USR_ID_BALANCE_FUNC   = 8,  /**< \brief 用户余额下发事件  */
    CHARGE_INTERFACE_FUNC = 9,  /**< \brief 充电接口标志  */
    CHARGE_PRICE_FUNC     = 10, /**< \brief 电价遥调  */
    PILE_ID_FUNC          = 11, /**< \brief 桩ID  */
    CHARGE_ENERGY_FUNC    = 12, /**< \brief 充电电量接收  用户结算 */
    HUB4G_COMM_STATE      = 13, /**< \brief 集中器通信正常回调  */
    AUTH_FAILE_REASON     = 14, /**< \brief 鉴权失败原因回调 */
    MAX_FUNC_NUM          = 15  /**< \brief 无效类型，不应该设置该类型   */
};

/**
 * \brief Modbus寄存器表
 *
 * \param[in] *p_arg  : 用户自定义参数
 * \param[in] *p_reg  : 待操作寄存器,可为NULL，即不需要用户更新
 * \param[in] gun_num : 充电枪编号, 1为枪1,2为枪2
 * \param[in] *val    : 写入寄存器值
 *
 * \retval AW_OK    : 设置成功
 * \retval AW_ERROR : 设置失败
 */
typedef int (*mb_func_cb_t) (void *p_arg, void *p_reg, uint8_t gun_num, void *val);

/** \brief modbus寄存器更新回调   */
struct mb_func_cb_structure {
    enum mb_func_cb_type fun_type;
    mb_func_cb_t         mb_func_cb;
    void                 *p_arg;
};


/**
 * \brief 收到升级命令时发生的回调函数
 *
 * \param[in] *p_arg  : 用户自定义参数
 */
typedef int (*pfunc_upgrade_cb_t) (void *p_arg);

/** \brief 升级时回调   */
struct upgrade_cb_item {
    pfunc_upgrade_cb_t    pfunc_cb;
    void                 *p_arg;
};

/** \brief Modbus寄存器表    */
struct modbus_reg_map {
    struct aw_remote_signal_reg  rm_signal_reg;  /**< \brief 遥信寄存器    */
    struct aw_remote_measure_reg rm_measure_reg; /**< \brief 遥测寄存器    */
    struct aw_remote_adjust_reg  rm_adjust_reg;  /**< \brief 遥调寄存器    */
    struct aw_remote_ctrl_reg    rm_ctrl_reg;    /**< \brief 遥控寄存器   */

    struct mb_func_cb_structure  mb_func_cb[MAX_FUNC_NUM]; /**< \brief 回调函数表   */

    AW_MUTEX_DECL(lock);                         /**< \brief 读写寄存器保护锁  */

//todo Modbus主站访问监测，在一定时间内没访问则引起复位或其他操作.
//    aw_timer_t     monitor_timer;
//    aw_pfuncvoid_t monitor_func_cb;
//    void          *p_arg;
};


/** \brief 充电桩Modbus寄存器表初始化  */
aw_static_inline void modbus_reg_map_init(struct modbus_reg_map *p_this)
{
    uint8_t i = 0;
    AW_MUTEX_INIT(p_this->lock, AW_SEM_Q_PRIORITY);
    for (i = 0; i < MAX_FUNC_NUM; i++) {
        p_this->mb_func_cb[i].fun_type   = MAX_FUNC_NUM;
        p_this->mb_func_cb[i].mb_func_cb = NULL;
    }
}

/** \brief Modbus读写操作上锁  */
aw_static_inline void modbus_reg_map_lock(struct modbus_reg_map *p_this)
{
    AW_MUTEX_LOCK(p_this->lock, AW_SEM_WAIT_FOREVER);
}

/** \brief Modbus读写操作解锁  */
aw_static_inline void modbus_reg_map_unlock(struct modbus_reg_map *p_this)
{
    AW_MUTEX_UNLOCK(p_this->lock);
}

/** \brief 注册一个modbus寄存器设置回调 */
int modbus_func_cb_register (struct modbus_reg_map *p_this,
                             enum mb_func_cb_type   type,
                             mb_func_cb_t           func_cb,
                             void                  *p_arg);

/** \brief 获取一个modbus寄存器回调结构  */
struct mb_func_cb_structure *modbus_func_cb_get (struct modbus_reg_map *p_this,
                                                 enum mb_func_cb_type   type);

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
int modbus_slave_hdl_init (struct modbus_reg_map *p_mb_reg_map,
                           uint8_t                slave_addr,
                           uint8_t                com,
                           uint32_t               baudrate,
                           uint8_t                parity);

int ac_modbus_slave_hdl_init (struct modbus_reg_map *p_mb_reg_map,
                              uint8_t                   slave_addr,
                              uint8_t                   com,
                              uint32_t                  baudrate,
                              uint8_t                   parity);

/**
 * 设置从机地址
 */
aw_err_t ac_modbus_slave_set_addr (uint8_t addr);

void ac_modbus_upgrade_enable();

void ac_modbus_upgrade_disable();

void ac_modbus_upgrade_callback_set(pfunc_upgrade_cb_t pfunc_upgread_cb, void *p_arg);

/******************************************************************************/
#endif /* AC_MODBUS_REG_MAP_H_ */

