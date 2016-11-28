/**
 * \file
 * \brief (����׮)���ƼƷѵ�Ԫ�뼯�п�����ModbusͨѶЭ��ʵ��
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

#define CHARGING_GUN_NUM           1  /**< \brief ���ǹ��Ŀ          */

#define GUN1  1  /**< \brief ���ǹ1          */
#define GUN2  2  /**< \brief ���ǹ2          */

/** \brief ��ȡ�ṹ���Modbus�Ĵ�����          */
#define MB_REG_NUM_GET(structure)   (sizeof(structure) / sizeof(uint16_t))

/** \brief ��ȡ�Ĵ����ṹ��ƫ�Ƹ���          */
#define MB_REG_OFFSET_GET(structure, mem)  (AW_OFFSET(structure, mem) / sizeof(uint16_t))
/******************************************************************************
 * ң������
 ******************************************************************************/
/** \brief ����״̬1λ״̬ */
struct aw_charger_stat_bit {
    //todo �����Ԥˢ��
    uint8_t key_store_ok           : 1;  /**< \brief ��Կ����ɹ� ��0û�б���ɹ���1��Կ����ɹ� ÿ��ˢ��ʱ���� */
    uint8_t card_swing_ok2         : 1;  /**< \brief ˢ���ɹ� ��0ˢ�����ɹ���1ˢ���ɹ� , �յ���Ȩ���ʱ�øñ�־λ */
    uint8_t charger_allow_stat     : 1;  /**< \brief �Ƿ�������״̬��0�������磬1������*/
    uint8_t charger_stat           : 1;  /**< \brief ���״̬��0����磬1���*/
    uint8_t screen_lock_stat       : 1;  /**< \brief ����״̬��0������ 1������*/
    uint8_t g4_comm_stat           : 1;  /**< \brief 4gͨѶ״̬��0������ 1����*/
    uint8_t pile_order_stat        : 1;  /**< \brief ׮ԤԼ״̬��0��ԤԼ��1ԤԼ*/
    uint8_t light_pro_alm          : 1;  /**< \brief ���������ϸ澯  */

    uint8_t charger_overtemp_alm   : 1;  /**< \brief ���׮���¹��ϸ澯  */
    uint8_t flood_alm              : 1;  /**< \brief ˮ�����ϸ澯  */
    uint8_t contactor_fault_alm    : 1;  /**< \brief �Ӵ������ϸ澯  */
    uint8_t door_switch_alm        : 1;  /**< \brief �Ž����ظ澯, 0���ţ�1���� */
    uint8_t ammeter_alm            : 1;  /**< \brief ���ͨѶ�澯  */
    uint8_t cardreader_alm         : 1;  /**< \brief ˢ����ͨѶ�澯  */
    uint8_t ac_in_undervolt_alm    : 1;  /**< \brief ��������Ƿѹ�澯  */
    uint8_t ac_in_overvolt_alm     : 1;  /**< \brief ���������ѹ�澯  */
};



/**< \brief ����״̬1 */
union aw_charger_stat1 {
    struct aw_charger_stat_bit stat1_bit;  /**< \brief ����״̬1λ״̬ */
    uint16_t                   stat1;      /**< \brief ����״̬1λ״̬ */
};
/******************************************************************************/
struct aw_charging_stop_cause_bit {
    uint8_t manual_stop              : 1;  /**< \brief �����˹���ֹ��� */
    uint8_t guide_test_fail          : 1;  /**< \brief �����������Բ�ͨ��   */
    uint8_t batvolt_chk_unusal       : 1;  /**< \brief ����������ѹ����쳣��ֹ   */
    uint8_t door_switch_alm          : 1;  /**< \brief �����Ž�����쳣��ֹ   */
    uint8_t elect_lock_alm           : 1;  /**< \brief �������쳣��ֹ   */
    uint8_t gun_contact_alm          : 1;  /**< \brief ǹ�Ӵ���ֹ */
    uint8_t light_pro_unusal_stop    : 1;  /**< \brief �����쳣��ֹ  */
    uint8_t measure_per_unusal_stop  : 1;  /**< \brief ������Ԫ�쳣��ֹ   */

    uint8_t pos_charge_unusal_stop   : 1;  /**< \brief ����ˢ�������쳣��ֹ   */
    uint8_t background_stop          : 1;  /**< \brief ������̨��ֹ���   */
    uint8_t banlance_notenough_stop  : 1;  /**< \brief ������ֹ���   */
    uint8_t ac_in_undervolt_stop     : 1;  /**< \brief ��������Ƿѹ��ֹ  */
    uint8_t ac_in_overvolt_stop      : 1;  /**< \brief ���������ѹ��ֹ  */
    uint8_t ac_in_overcurr_stop      : 1;  /**< \brief �������������ֹ  */
    uint8_t card_swing_ok1           : 1;  /**< \brief Ԥˢ���ɹ� ����⵽��Ƭ��Ϊ�ɹ� */
    uint8_t reserved                 : 1;  /**< \brief ����  */
};

/**< \brief ���ֹͣԭ��  */
union aw_charging_stop_cause {
    struct aw_charging_stop_cause_bit cause_bit;  /**< \brief ���ֹͣԭ��λ   */
    uint16_t                          cause;      /**< \brief ���ֹͣԭ�� */
};
/******************************************************************************/
/**< \brief ǹ״̬��Ϣ   */
struct aw_charging_gun_stat {
    union aw_charger_stat1       charger_stat1;       /**< \brief ����״̬1   */
    union aw_charging_stop_cause charging_stop_cause; /**< \brief ���ֹͣԭ��   */
};

/**< \brief ң������   */
struct aw_remote_signal_reg {
   struct aw_charging_gun_stat charger_stat[CHARGING_GUN_NUM];  /**< \brief ǹ״̬��Ϣ   */
};
/******************************************************************************/
#define RM_SIGNAL_REG_ADDR       1   /**< \brief ң�ŵ�ַ          */

/** \brief ң�żĴ�������          */
#define RM_SIGNAL_REG_NUM       MB_REG_NUM_GET(struct aw_remote_signal_reg)

#define RM_SIGNAL_REG_END_ADDR  (RM_SIGNAL_REG_ADDR + RM_SIGNAL_REG_NUM)
/******************************************************************************
 * ң������
 ******************************************************************************/
/** \brief ��������      */
struct aw_charger_whole_data {
    uint16_t charger_interface;        /**< \brief �����ӿڷ�ʽ��ǹ��������       */
    uint16_t charger_out_volt;         /**< \brief ���������ѹ       */
    uint16_t charger_out_curr;         /**< \brief �����������       */
    uint16_t charger_ambient_temp;     /**< \brief ���������¶�       */
    uint16_t now_charge_energy;        /**< \brief ���γ�����      */
    uint16_t now_charge_amount;        /**< \brief ���γ����      */
    uint16_t now_charge_time;          /**< \brief ���γ��ʱ��      */
    uint16_t auth_fail_reason;         /**< \brief ��Ȩʧ��ԭ��      */
    uint16_t meter_rtval_hi_word;      /**< \brief ���ʵʱ�������ֽ�      */
    uint16_t meter_rtval_lo_word;      /**< \brief ���ʵʱ�������ֽ�      */
};


/**< \brief ���ܿ�ID��Ϣ   */
struct aw_s50_card {
    uint16_t card_id[2];           /**< \brief ���ܿ�ID�Ÿ��ֽ�       */
    uint16_t card_dat[24];         /**< \brief ���ܿ�����       */
//    uint16_t card_id_hi_word;  /**< \brief ���ܿ�ID�Ÿ��ֽ�       */
//    uint16_t card_id_lo_word;  /**< \brief ���ܿ�ID�ŵ��ֽ�       */
//todo 4.22�޸�
//    uint16_t section0_1_1;     /**< \brief ����0-1-1       */
//    uint16_t section0_1_2;     /**< \brief ����0-1-2       */
//    uint16_t section0_1_3;     /**< \brief ����0-1-3       */
//    uint16_t section0_1_4;     /**< \brief ����0-1-4       */
//    uint16_t section0_1_5;     /**< \brief ����0-1-5       */
//    uint16_t section0_1_6;     /**< \brief ����0-1-6       */
//    uint16_t section0_1_7;     /**< \brief ����0-1-7       */
//    uint16_t section0_1_8;     /**< \brief ����0-1-8       */
//
//    uint16_t section0_2_1;     /**< \brief ����0-2-1       */
//    uint16_t section0_2_2;     /**< \brief ����0-2-2       */
//    uint16_t section0_2_3;     /**< \brief ����0-2-3       */
//    uint16_t section0_2_4;     /**< \brief ����0-2-4       */
//    uint16_t section0_2_5;     /**< \brief ����0-2-5       */
//    uint16_t section0_2_6;     /**< \brief ����0-2-6       */
//    uint16_t section0_2_7;     /**< \brief ����0-2-7       */
//    uint16_t section0_2_8;     /**< \brief ����0-2-8       */
//
//    uint16_t section0_3_1;     /**< \brief ����0-3-1       */
//    uint16_t section0_3_2;     /**< \brief ����0-3-2       */
//    uint16_t section0_3_3;     /**< \brief ����0-3-3       */
//    uint16_t section0_3_4;     /**< \brief ����0-3-4       */
//    uint16_t section0_3_5;     /**< \brief ����0-3-5       */
//    uint16_t section0_3_6;     /**< \brief ����0-3-6       */
//    uint16_t section0_3_7;     /**< \brief ����0-3-7       */
//    uint16_t section0_3_8;     /**< \brief ����0-3-8       */
};

/**< \brief ������ʱʱ��  */
struct aw_charger_time {
    uint16_t  year;          /**< \brief �� : 2010~2099  */
#define CUR_TIME_SET_YEAR_MAX  2099
#define CUR_TIME_SET_YEAR_MIN  2010
    uint16_t  month;         /**< \brief �� : 1~12  */
    uint16_t  day;           /**< \brief �� : 1~31  */
    uint16_t  hour;          /**< \brief ʱ : 1~23 */
    uint16_t  minute;        /**< \brief �� : 0~59 */
    uint16_t  second;        /**< \brief �� : 0~59  */
};

/**< \brief �û���Ϣ   */
struct aw_charging_usr_info {
    /** \brief �û�ID��ռ��С  */
#define RM_ADJ_GUN_USER_ID_NUM   8   //����׮�û�IDδ�޸�
    uint16_t user_id[RM_ADJ_GUN_USER_ID_NUM];    /**< \brief �û�ID  */
    uint16_t user_balance[2];        /**< \brief �û�ID����16λ��0.01Ԫ */

};

/**< \brief ��������   */
struct aw_charger_data {
    struct aw_charger_time        local_time;           /**< brief RTCʱ�� */

#define RM_ADJ_TIME_INVL_NUM     24    /**< \brief ʱ�������� */
#define RM_ADJ_ELECT_MAX_PRICE   65535 /**< \brief �����۸����ֵ    */
#define RM_ADJ_ELECT_MIN_PRICE   10000 /**< \brief �����۸���Сֵ    */
    /** \brief ʱ��γ��۸����λΪ0~1�㣬 ��λΪ0.01Ԫ    */
    uint16_t                      time_invl_price[RM_ADJ_TIME_INVL_NUM];

#define RM_ADJ_CHARGER_PILE_ID_NUM   4     /**< \brief ���׮��� ��λ�ڵ�ֵַ ��˷�ʽ   */
    uint16_t                      pile_id[RM_ADJ_CHARGER_PILE_ID_NUM];
};
/******************************************************************************/
/**< \brief ң��Ĵ���   */
struct aw_remote_measure_reg {
    struct aw_charger_data        charger_data;          /**< \brief ��������   */
    struct aw_charging_usr_info   usr_info;              /**< \brief �û���Ϣ      */
    struct aw_charger_whole_data  charger_wdata;         /**< \brief ��������       */
    struct aw_s50_card            s50_card;              /**< \brief ���ܿ�ID��Ϣ   */
};
/******************************************************************************
 * ң��Ĵ�����ַ����Ŀ
 ******************************************************************************/
/** \brief ң��---�����Ϣ�Ĵ�����ַ��ֻ���������ѹ�������������¶ȣ� */
#define RM_MEASURE_CHARGING_DAT_REG_ADDR   100
/** \brief ң��---�����Ϣ�Ĵ�������ֻ���������ѹ�������������¶ȣ� */
#define RM_MEASURE_CHARGING_DAT_REG_NUM    MB_REG_NUM_GET(struct aw_charger_data)

/** \brief ң��---�����Ϣ�Ĵ�����ַ��ֻ���������ѹ�������������¶ȣ� */
#define RM_MEASURE_CHARGING_USR_REG_ADDR   180
/** \brief ң��---�����Ϣ�Ĵ�������ֻ���������ѹ�������������¶ȣ� */
#define RM_MEASURE_CHARGING_USR_REG_NUM    MB_REG_NUM_GET(struct aw_charging_usr_info)

/** \brief ң��---�����Ϣ�Ĵ�����ַ��ֻ���������ѹ�������������¶ȣ� */
#define RM_MEASURE_CHARGING_WDAT_REG_ADDR   200
/** \brief ң��---�����Ϣ�Ĵ�������ֻ���������ѹ�������������¶ȣ� */
#define RM_MEASURE_CHARGING_WDAT_REG_NUM    MB_REG_NUM_GET(struct aw_charger_whole_data)

/** \brief ң��---�����Ϣ�Ĵ�����ַ��ֻ���������ѹ�������������¶ȣ� */
#define RM_MEASURE_CHARGING_CARD_REG_ADDR   2000
/** \brief ң��---�����Ϣ�Ĵ�������ֻ���������ѹ�������������¶ȣ� */
#define RM_MEASURE_CHARGING_CARD_REG_NUM    MB_REG_NUM_GET(struct aw_s50_card)

/******************************************************************************
 * ң������
 ******************************************************************************/
/** \brief ��׮����   */
struct aw_remote_adjust_pile_data {
    /** \brief ʱ��γ��۸����λΪ0~1�㣬 ��λΪ0.01Ԫ    */
    uint16_t                time_invl_price[RM_ADJ_TIME_INVL_NUM];

#define RM_ADJ_CHARGER_PILE_ID_NUM   4     /**< \brief ׮ID�Ĵ�������   */
    uint16_t                           pile_id[RM_ADJ_CHARGER_PILE_ID_NUM];
} ;
/**< \brief ң���Ĵ���ҵ�������Ϣ  */
struct aw_remote_adjust_usr_ctrl {
    uint16_t                           charger_interface;   /**< \brief �����ӿڷ�ʽ��ǹ��������       */

    struct aw_charging_usr_info        usr_info;            /**< \brief �û���Ϣ      */

    uint16_t                           now_charge_amount;   /**< \brief ���γ����      */
    uint16_t                           now_charge_energy;   /**< \brief ���γ�����      */

#define RM_ADJ_GUN_CARD_SECRET_KEY_NUM   3
    /**< \brief ����Կ����λΪ���ֽ�  */
    uint16_t                           card_secret_key[RM_ADJ_GUN_CARD_SECRET_KEY_NUM];
    uint16_t                           auth_fail_reason;      /**< \brief ��Ȩʧ��ԭ��   */
    uint16_t                           reserved[6];           /**< \brief ����    */
};

/**< \brief ң���Ĵ���   */
struct aw_remote_adjust_reg {
    /**< \brief ��ʱʱ��    */
    struct aw_charger_time             time;
    /** \brief ��׮����   */
    struct aw_remote_adjust_pile_data  pile_data;
    /** \brief �û�������Ϣ   */
    struct aw_remote_adjust_usr_ctrl   usr_ctrl;
};
/******************************************************************************
 * ң��---�Ĵ�����ַ����Ŀ
 ******************************************************************************/
#define RM_ADJ_TIME_REG_ADDR      1000    /**< \brief ң��ʱ�����ַ   */
/** \brief ң��ʱ��Ĵ�����   */
#define RM_ADJ_TIME_REG_NUM       MB_REG_NUM_GET(struct aw_charger_time)

#define RM_ADJ_PILE_REG_ADDR      1006    /**< \brief ң����׮����ַ   */
/** \brief ң����׮�Ĵ�����   */
#define RM_ADJ_PILE_REG_NUM       MB_REG_NUM_GET(struct aw_remote_adjust_pile_data)

/** \brief �û��Ĵ�������   */
#define RM_ADJ_USR_REG_ADDR       1100
/** \brief ң���û��Ĵ�����   */
#define RM_ADJ_USR_REG_NUM        MB_REG_NUM_GET(struct aw_remote_adjust_usr_ctrl)

/** \brief ʱ��Ĵ�������   */
#define RM_ADJ_ELECT_PRICE_INVL_REG_ADDR   (RM_ADJ_TIME_REG_ADDR + RM_ADJ_TIME_REG_NUM)
/** \brief ʱ��γ��۸�Ĵ�����   */
#define RM_ADJ_ELECT_PRICE_INVL_REG_NUM    RM_ADJ_TIME_INVL_NUM    /**< \brief ң�������۸�ʱ����   */

/* ʱ��Ĵ���ƫ�� */
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
 * ң������
 ******************************************************************************/
/**< \brief ǹ��������  */
struct aw_charg_gun_ctrl_data {
    uint16_t allow_charging;        /**< \brief �����磬��ֹ��磺0x0055, �����磺 0x00AA   */
    uint16_t charging_startup;      /**< \brief �������, ֹͣ��0x0055, ������ 0x00AA  */
    uint16_t unlock_screen;         /**< \brief ������Ļ�� ������ 0x0055, ������ 0x00AA   */
    uint16_t comm_4g_stat;          /**< \brief 4GͨѶ״̬, ͨѶ�쳣�� 0x0055, ͨѶ������0x00AA    */
    uint16_t order_charging;        /**< \brief ԤԼ���, ��ԤԼ�� 0x0055, ��ԤԼ��0x00AA */
    uint16_t reserved[6];           /**< \brief ����  */
};

/**< \brief ң����Ϣ   */
struct aw_remote_ctrl_reg {
    struct aw_charg_gun_ctrl_data gun_ctrl_data[CHARGING_GUN_NUM];  /**< \brief ǹ������Ϣ    */
};
/******************************************************************************/
#define RM_CTRL_REG_ADDR        1500                    /**< \brief ң�ؼĴ�������ַ   */
#define RM_CTRL_GUN1_REG_ADDR   RM_CTRL_REG_ADDR        /**< \brief ң�ؼĴ���ǹ1��ַ   */

#define RM_CTRL_GUN_REG_NUM     MB_REG_NUM_GET(struct aw_charg_gun_ctrl_data)

#define RM_CTRL_ALLOW_CHARGING_ADDR_OFFSET     0   /**< \brief ң��--��������Ƶ�ַƫ��   */
#define RM_CTRL_CHARGING_STARTUP_ADDR_OFFSET   1   /**< \brief ң��--��������ַƫ��   */
#define RM_CTRL_UNLOCK_SCREEN_ADDR_OFFSET      2   /**< \brief ң��--������Ļ��ַƫ��   */
#define RM_CTRL_COMM_4G_STAT_ADDR_OFFSET       3   /**< \brief ң��--4GͨѶ״̬��ַƫ��   */
#define RM_CTRL_ORDER_CHARGING_ADDR_OFFSET     4   /**< \brief ң��--ԤԼ����ַƫ��   */

#define RM_CTRL_DATA_VAL_SET     0x00AA  /**< \brief ң��--����ֵ  */
#define RM_CTRL_DATA_VAL_RESET   0x0055  /**< \brief ң��--��λֵ   */
/******************************************************************************
 * Modbus �Ĵ�������Ϣ
 ******************************************************************************/
/** \brief modbus�Ĵ����ص�����   */
enum mb_func_cb_type {
    TIME_SET_FUNC         = 0,  /**< \brief ʱ�����ûص����ص�������д������Ϊaw_charger_time   */
    ALLOW_CHARGING_FUNC   = 1,  /**< \brief �����磬д��Ϊ0x0055��0x00aa   */
    CHARGING_STARTUP_FUNC = 2,  /**< \brief ������� ,д��Ϊ0x0055��0x00aa */
    UNLOCK_SCREEN_FUNC    = 3,  /**< \brief ������Ļ,д��Ϊ0x0055��0x00aa   */
    COMM_4G_STAT_FUNC     = 4,  /**< \brief 4GͨѶ�쳣 ��д��Ϊ0x0055��0x00aa  */
    ORDER_CHARGING_FUNC   = 5,  /**< \brief ԤԼ���  ��д��Ϊ0x0055��0x00aa  */
    CARD_KEY_LOAD_FUNC    = 6,  /**< \brief ��key�·��¼�  */
    USR_ID_SAVE_FUNC      = 7,  /**< \brief �û�ID�·��¼�  */
    USR_ID_BALANCE_FUNC   = 8,  /**< \brief �û�����·��¼�  */
    CHARGE_INTERFACE_FUNC = 9,  /**< \brief ���ӿڱ�־  */
    CHARGE_PRICE_FUNC     = 10, /**< \brief ���ң��  */
    PILE_ID_FUNC          = 11, /**< \brief ׮ID  */
    CHARGE_ENERGY_FUNC    = 12, /**< \brief ����������  �û����� */
    HUB4G_COMM_STATE      = 13, /**< \brief ������ͨ�������ص�  */
    AUTH_FAILE_REASON     = 14, /**< \brief ��Ȩʧ��ԭ��ص� */
    MAX_FUNC_NUM          = 15  /**< \brief ��Ч���ͣ���Ӧ�����ø�����   */
};

/**
 * \brief Modbus�Ĵ�����
 *
 * \param[in] *p_arg  : �û��Զ������
 * \param[in] *p_reg  : �������Ĵ���,��ΪNULL��������Ҫ�û�����
 * \param[in] gun_num : ���ǹ���, 1Ϊǹ1,2Ϊǹ2
 * \param[in] *val    : д��Ĵ���ֵ
 *
 * \retval AW_OK    : ���óɹ�
 * \retval AW_ERROR : ����ʧ��
 */
typedef int (*mb_func_cb_t) (void *p_arg, void *p_reg, uint8_t gun_num, void *val);

/** \brief modbus�Ĵ������»ص�   */
struct mb_func_cb_structure {
    enum mb_func_cb_type fun_type;
    mb_func_cb_t         mb_func_cb;
    void                 *p_arg;
};


/**
 * \brief �յ���������ʱ�����Ļص�����
 *
 * \param[in] *p_arg  : �û��Զ������
 */
typedef int (*pfunc_upgrade_cb_t) (void *p_arg);

/** \brief ����ʱ�ص�   */
struct upgrade_cb_item {
    pfunc_upgrade_cb_t    pfunc_cb;
    void                 *p_arg;
};

/** \brief Modbus�Ĵ�����    */
struct modbus_reg_map {
    struct aw_remote_signal_reg  rm_signal_reg;  /**< \brief ң�żĴ���    */
    struct aw_remote_measure_reg rm_measure_reg; /**< \brief ң��Ĵ���    */
    struct aw_remote_adjust_reg  rm_adjust_reg;  /**< \brief ң���Ĵ���    */
    struct aw_remote_ctrl_reg    rm_ctrl_reg;    /**< \brief ң�ؼĴ���   */

    struct mb_func_cb_structure  mb_func_cb[MAX_FUNC_NUM]; /**< \brief �ص�������   */

    AW_MUTEX_DECL(lock);                         /**< \brief ��д�Ĵ���������  */

//todo Modbus��վ���ʼ�⣬��һ��ʱ����û����������λ����������.
//    aw_timer_t     monitor_timer;
//    aw_pfuncvoid_t monitor_func_cb;
//    void          *p_arg;
};


/** \brief ���׮Modbus�Ĵ������ʼ��  */
aw_static_inline void modbus_reg_map_init(struct modbus_reg_map *p_this)
{
    uint8_t i = 0;
    AW_MUTEX_INIT(p_this->lock, AW_SEM_Q_PRIORITY);
    for (i = 0; i < MAX_FUNC_NUM; i++) {
        p_this->mb_func_cb[i].fun_type   = MAX_FUNC_NUM;
        p_this->mb_func_cb[i].mb_func_cb = NULL;
    }
}

/** \brief Modbus��д��������  */
aw_static_inline void modbus_reg_map_lock(struct modbus_reg_map *p_this)
{
    AW_MUTEX_LOCK(p_this->lock, AW_SEM_WAIT_FOREVER);
}

/** \brief Modbus��д��������  */
aw_static_inline void modbus_reg_map_unlock(struct modbus_reg_map *p_this)
{
    AW_MUTEX_UNLOCK(p_this->lock);
}

/** \brief ע��һ��modbus�Ĵ������ûص� */
int modbus_func_cb_register (struct modbus_reg_map *p_this,
                             enum mb_func_cb_type   type,
                             mb_func_cb_t           func_cb,
                             void                  *p_arg);

/** \brief ��ȡһ��modbus�Ĵ����ص��ṹ  */
struct mb_func_cb_structure *modbus_func_cb_get (struct modbus_reg_map *p_this,
                                                 enum mb_func_cb_type   type);

/**
 *  \brief Modbus ��վ�����ʼ���ӿ�
 *
 *  \param[in] p_mb_reg_map : Modbus�Ĵ�����ָ��
 *  \param[in] com          : Modbusʹ�ô��ں�
 *  \param[in] baudrate     : ������
 *  \param[in] parity       : У�飺 0��У�飬 1��У�飬 2żУ��
 *
 *  \retval AW_OK    : ��ʼ���ɹ�
 *  \retval AW_ERROR : ʧ��
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
 * ���ôӻ���ַ
 */
aw_err_t ac_modbus_slave_set_addr (uint8_t addr);

void ac_modbus_upgrade_enable();

void ac_modbus_upgrade_disable();

void ac_modbus_upgrade_callback_set(pfunc_upgrade_cb_t pfunc_upgread_cb, void *p_arg);

/******************************************************************************/
#endif /* AC_MODBUS_REG_MAP_H_ */

