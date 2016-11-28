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
 * \brief DGUS������Modbusͨ��Э�����ݼĴ�������
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

/** \brief DGUS�ɶ�������ʼ��ַ */
#define AW_MB_DGUS_READ_START_ADDR 0x1000

/** \brief DGUS�ɶ����������� */
#define AW_MB_DGUS_READ_MAX_NUM  50

/** \brief DGUS��д������ʼ��ַ */
#define AW_MB_DGUS_WRITE_START_ADDR 0x2000

/** \brief DGUS��д���������� */
#define AW_MB_DGUS_WRITE_MAX_NUM 11

/** \brief ����ص��ص����������� */
#define __MB_FUNC_CB_NUM_MAX     11

/**< \brief DGUS��ʾ����Ҫ�������� */
struct aw_mb_dgus_rd_reg {
    /* DGUS �������� */
    uint16_t card_stat;     /**< \brief ˢ��״̬ \ref grp_card_detect_stat */
    uint16_t card_cnt;      /**< \brief ˢ��������,���ڳ�磬����������Ӧ,��ͬ����1 */
    uint16_t card_id[4];    /**< \brief �û�ID0~3 LSB */
    uint16_t pile_stat;     /**< \brief ׮�쳣״̬ \ref grp_pile_stat */ 
    uint16_t pile_order;    /**< \brief ׮ԤԼ״̬ \ref grp_pile_order_stat */
    uint16_t balance_stat;  /**< \brief ����״̬ \ref grp_pile_balance_stat */
    uint16_t gun_stat;      /**< \brief ��ǹ״̬ \ref grp_gun_stat */
    uint16_t work_stat;     /**< \brief ��������״̬ \ref grp_work_stat */
    uint16_t used_time;     /**< \brief ���ʱ�� ��λ:���� */
    uint16_t charge_stat;   /**< \brief �������״̬ */
    uint16_t card_balance;  /**< \brief ����� ��λ    :0.1Ԫ */
    uint16_t used_amount;   /**< \brief ���ѽ�� ��λ:0.1Ԫ */
    uint16_t used_energy;   /**< \brief ������ ��λ:0.1�� */      
    uint16_t stop_reason;   /**< \brief ���ֹͣԭ��  \ref grp_charge_stop_reason */
    uint16_t usr_balance[2];   /**< \brief �û����, ��˴洢 */
    uint16_t usr_id[8];        /**< \brief �û�ID, ��˴洢 */
    uint16_t pile_err_reason;  /**< \brief �쳣ԭ�� */
    uint16_t upgrade_flag;     /**< \brief ׮������־ 0xAA: δ������ 0x55�������� */

    uint16_t admin_flag;       /**< \brief ����Ա��־ 0xAA: ��ͨģʽ�� 0x55������Աģʽ */
    uint16_t hub4g_addr;       /**< \brief ������ͨ�ŵ�ַ */
    int16_t  pile_temp;        /**< \brief ׮�¶� ��λ0.1�棬ƫ��-50�� */
    uint16_t input_vol;        /**< \brief �����ѹ ��λ0.1V */
    uint16_t input_curr;       /**< \brief ������� ��λ0.001A */
    uint16_t run_time;         /**< \brief ������ʱ�� ��λ���� */
    uint16_t err_cnt;          /**< \brief �쳣���� */
    uint16_t charge_cnt;       /**< \brief ������ */
    uint16_t bg_state;         /**< \brief ��̨ͨ�������0:������1:�쳣 */
    uint16_t ammeter_state;    /**< \brief ���ͨ�������0:������1:�쳣 */
    uint16_t cardreader_state; /**< \brief ������ͨ�������0:������1:�쳣 */
    uint16_t vol_state;        /**< \brief ��ѹ���������0:������1:�쳣 */
    uint16_t hvb_state;        /**< \brief ��ѹ��ͨ�������0:������1:�쳣 */

    uint8_t pile_id[16];       /**< \brief ׮ID���������ַ�����ʾ�� */
};

/**< \brief DGUS��ʾ����Ҫд������ */
struct aw_mb_dgus_wr_reg {
    /* DGUS д������ */
    uint16_t charge_ctrl;        /**< \brief ������ \ref grp_charge_ctrl */
    uint16_t charge_way;         /**< \brief ��緽ʽ \ref grp_charge_way  */
    uint16_t charge_amount;      /**< \brief ����� ��λ:0.1Ԫ                                       */
    uint16_t charge_energy;      /**< \brief ������ ��λ:0.1��                                       */
    uint16_t charge_time;        /**< \brief ���ʱ�� ��λ:����                                            */
    uint16_t card_state_clr;     /**< \brief �������״̬ */
    uint16_t amount_state_clr;   /**< \brief ��������״̬ */
    uint16_t accout_exit_cmd;    /**< \brief �˳��˻� */
    uint16_t admin_exit_cmd;     /**< \brief �˳�����Աģʽ */
    uint16_t hub4g_addr_set;     /**< \brief �����ڼ�����ͨ�ŵĵ�ַ */

};

/**
 * \brief Modbusд�Ĵ����ص���������
 */
typedef enum aw_mb_dugs_func_cb_type{
    FUNC_CHARGE_CTRL   = 0,
    FUNC_CHARGE_WAY    = 1,
    FUNC_CHARGE_AMOUNT = 2,
    FUNC_CHARGE_ENERGY = 3,
    FUNC_CHARGE_TIME   = 4,
    FUNC_CARD_STATE_CLR= 5,
    FUNC_AMOUNT_STATE_CLR= 6, /* ���״̬������� */
    FUNC_ACCOUT_EXIT_CMD = 7, /* �˻��˳����� */
    FUNC_ADMIN_EXIT_CMD  = 8, /* ����Աģʽ�˳����� */
    FUNC_HUB4G_ADDR_CMD  = 9, /* ��ַ�������� */
    FUNC_DUGS_COMM_STATE = 10, /* ������ͨ��״̬ */
} aw_mb_dugs_func_cb_type_t;

/**
 * \brief Modbusд�Ĵ����ص���������
 *
 * \param p_arg:�ص�����
 * \param val  :��Ӧ���ͼĴ���ֵ
 *
 * return 0:�ɹ� -1:ʧ��
 */
typedef int (*pfn_mb_dugs_cb_t) (void *p_arg, uint16_t val);


/**
 * \brief Modbusд�Ĵ����ص������ṹ
 */
struct aw_mb_dgus_func_cb_block {
    aw_mb_dugs_func_cb_type_t fun_type;
    pfn_mb_dugs_cb_t          pfn_mb_dgus_cb;
    void                     *p_arg;
};

/**< \brief DGUS��ʾ����Ҫ����д������   */
struct aw_mb_dgus_reg_map {
    struct aw_mb_dgus_rd_reg rd_reg;
    
    struct aw_mb_dgus_wr_reg wr_reg;
    
    /** \brief д���ݻص�������Ϣ */
    struct aw_mb_dgus_func_cb_block mb_dgus_funcs[__MB_FUNC_CB_NUM_MAX];
    
    AW_MUTEX_DECL(lock);    /**< \brief ��д�Ĵ���������  */
};


/**
 * \brief ����״̬
 * \anchor grp_card_detect_stat
 * @{
 */
#define AW_MB_DGUS_CARD_STAT_IDLE       0x00     /**< \brief û��ˢ�� */
#define AW_MB_DGUS_CARD_STAT_SUCCESS    0x55     /**< \brief ˢ���ɹ� */
#define AW_MB_DGUS_CARD_STAT_INVALID    0xAA     /**< \brief ��Ч�� */
#define AW_MB_DGUS_CARD_STAT_AUTH       0x05     /**< \brief ��Ȩ�� */
/** @} */

/**
 * \brief ���׮�쳣״̬
 * \anchor grp_pile_stat
 * @{
 */
#define AW_MB_DGUS_PILE_STAT_NORMAL    0xAA      /**< \brief ׮���� */
#define AW_MB_DGUS_PILE_STAT_ABNORMAL  0x55      /**< \brief ׮�쳣 */
/** @} */

/**
 * \brief ���׮׮ԤԼ״̬
 * \anchor grp_pile_order_stat
 * @{
 */
#define AW_MB_DGUS_PILE_IS_ORDERED      0x55     /**< \brief �ѱ�ԤԼ */
#define AW_MB_DGUS_PILE_IS_NOT_ORDERED  0xAA     /**< \brief δԤԼ */
/** @} */

/**
 * \brief ���״̬(����������û��趨�Ľ�������Աȵó�) 
 * \anchor grp_pile_balance_stat
 * @{
 * \note �������Ͱ������䷽ʽ����Ч
 */
#define AW_MB_DGUS_BALANCE_ENOUGH        0x55    /**< \brief ���� */
#define AW_MB_DGUS_BALANCE_NOT_ENOUGH    0xAA    /**< \brief ���� */
/** @} */

/**
 * \brief ���ǹ��״̬
 * \anchor grp_gun_stat
 * @{
 */
#define AW_MB_DGUS_GUN_IDLE      0               /**< \brief δ��ǹ(�Ѱγ�) */
#define AW_MB_DGUS_GUN_VALID     0x55            /**< \brief ��ǹ�ɹ� */
#define AW_MB_DGUS_GUN_ABNORMAL  0xAA            /**< \brief ǹ�쳣 */
/** @} */

/**
 * \brief ��繤��״̬
 * \anchor grp_work_stat
 * @{
 */
#define AW_MB_DGUS_WORK_STAT_IDLE     0          /**< \brief δ��� */
#define AW_MB_DGUS_WORK_STAT_BUSY     0x55       /**< \brief ����� */
#define AW_MB_DGUS_WORK_STAT_FINISH   0xAA       /**< \brief ������ */
/** @} */

/**
 * \brief �������״̬
 * \anchor grp_charge_stat
 * @{
 */
#define AW_MB_DGUS_CHARGE_STAT_NORMAL    0x55    /**< \brief ���� */
#define AW_MB_DGUS_CHARGE_STAT_ABNORMAL  0xAA    /**< \brief �쳣 */
/** @} */

/**
 * \brief ׮����״̬
 * \anchor grp_work_stat
 * @{
 */
#define AW_MB_DGUS_UPGRADE_BUSY     0x55       /**< \brief ׮������ */
#define AW_MB_DGUS_UPGRADE_IDLE     0xAA       /**< \brief ׮δ���� */
/** @} */

/**
 * \brief ������
 * \anchor grp_charge_ctrl
 * @{
 */ 
#define AW_MB_DGUS_CHARGE_CTRL_START    0x01      /**< \brief ��ʼ��� */
#define AW_MB_DGUS_CHARGE_CTRL_STOP     0x02      /**< \brief ��ͣ��� */
#define AW_MB_DGUS_CHARGE_CTRL_EXIT     0x03      /**< \brief �˳���� */
/** @} */                                         
                                                  
/**                                               
 * \brief ��緽ʽ                                
 * \anchor grp_charge_way                         
 * @{                                             
 */                                               
#define AW_MB_DGUS_CHARGE_WAY_AUTO      0x01      /**< \brief �Զ��� */
#define AW_MB_DGUS_CHARGE_WAY_AMOUNT    0x02      /**< \brief ������ */
#define AW_MB_DGUS_CHARGE_WAY_ENERGY    0x03      /**< \brief �������� */
#define AW_MB_DGUS_CHARGE_WAY_TIME      0x04      /**< \brief ��ʱ��� */
#define AW_MB_DGUS_CHARGE_WAY_APP       0x05      /**< \brief �ֻ�APP�� */
/** @} */

/**
 * \brief ���ֹͣԭ��
 * \anchor grp_charge_stop_reason
 * @{
 */
#define AW_MB_DGUS_CHARGE_NONE             0x00   /**< \brief δ���     */
#define AW_MB_DGUS_CHARGE_FULL             0x01   /**< \brief ������     */
#define AW_MB_DGUS_CHARGE_BALANCE_UNDER    0x02   /**< \brief ����   */
#define AW_MB_DGUS_CHARGE_MAN_EXIT         0x03   /**< \brief ��Ϊ�˳�   */
#define AW_MB_DGUS_CHARGE_AMOUNT_RUNOUT    0x04   /**< \brief ��������� */
#define AW_MB_DGUS_CHARGE_ENERGY_RUNOUT    0x05   /**< \brief ���������� */
#define AW_MB_DGUS_CHARGE_TIME_RUNOUT      0x06   /**< \brief ��ʱ������ */
#define AW_MB_DGUS_CHARGE_ERR_EXIT         0x07   /**< \brief �쳣�˳� */
#define AW_MB_DGUS_CHARGE_ERR_BILLING      0x08   /**< \brief �����쳣�˳� */
#define AW_MB_DGUS_CHARGE_BG_EXIT          0x09   /**< \brief ��̨�˳�   */
/* һ��Ϊ���ڵ��û��ʵ�ֵ��쳣��� ���ڵ���й���0x07�쳣���� */
#define AW_MB_DGUS_CHARGE_CARDREADER       0x0A   /**< \brief �������쳣   */
#define AW_MB_DGUS_CHARGE_AMETETER         0x0B   /**< \brief ���ͨ���쳣   */
#define AW_MB_DGUS_CHARGE_CURR             0x0C   /**< \brief �����쳣   */
#define AW_MB_DGUS_CHARGE_OVERVOL          0x0D   /**< \brief ��ѹ�쳣   */
#define AW_MB_DGUS_CHARGE_UNDERVOL         0x0E   /**< \brief Ƿѹ�쳣   */
#define AW_MB_DGUS_CHARGE_LIGHT            0x0F   /**< \brief �������쳣   */
#define AW_MB_DGUS_CHARGE_SCRAM            0x10   /**< \brief �������ض���   */
#define AW_MB_DGUS_CHARGE_TEMP             0x11   /**< \brief �¶��쳣   */
#define AW_MB_DGUS_CHARGE_AC               0x12   /**< \brief AC�Ӵ����쳣   */
/** @} */


/** \brief DGUS������Modbus�Ĵ������ʼ��  */
aw_static_inline void aw_mb_dgus_reg_map_init(struct aw_mb_dgus_reg_map *p_this)
{
    uint8_t i = 0;
    AW_MUTEX_INIT(p_this->lock, AW_SEM_Q_PRIORITY);
    
    /* ��ʼ���ص���������Ϣ*/
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

/** \brief Modbus��д��������  */
aw_static_inline void aw_mb_dugs_reg_map_lock(struct aw_mb_dgus_reg_map *p_this)
{
    AW_MUTEX_LOCK(p_this->lock, AW_SEM_WAIT_FOREVER);
}

/** \brief Modbus��д��������  */
aw_static_inline void aw_mb_dugs_reg_map_unlock(struct aw_mb_dgus_reg_map *p_this)
{
    AW_MUTEX_UNLOCK(p_this->lock);
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
                                 void                      *p_arg);

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
    aw_mb_dugs_func_cb_type_t  type);

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
