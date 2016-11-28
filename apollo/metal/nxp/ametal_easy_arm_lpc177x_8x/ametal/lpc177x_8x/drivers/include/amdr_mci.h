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
 * \brief MCI驱动，服务MCI标准接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-09-23  anu, first implementation.
 * \endinternal
 */

#ifndef __AMDR_MCI_H
#define __AMDR_MCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"  
#include "amhw_mci.h"
#include "amhw_dma.h"
    
/** 
 * \addtogroup amdr_if_mci
 * \copydoc amdr_mci.h
 * @{
 */

/**
 * \brief 引脚的触发信息 
 */
typedef struct amdr_mci_intcb_info {

    /** \brief 触发回调函数 */
    am_pfnvoid_t  pfn_callback;

    /** \brief 回调函数的参数 */
    void         *p_arg;

}amdr_mci_intcb_info_t;

/**
 * \brief MCI 设备信息
 */
typedef struct amdr_mci_devinfo {
    
    amhw_mci_t              *p_hw_mci;       /**< \brief MCI寄存器首地址  */
    amhw_syscon_t           *p_hw_syscon;    /**< \brief SYSCON寄存器首地址  */
    amdr_mci_intcb_info_t   *p_intcb_info;   /**< \brief MCI 回调信息 */
    uint16_t                 inum;           /**< \brief MCI 中断号  */
    int                      insert_pin;     /**< \brief MCI SD_INSERT引脚  */
    int                      wp_pin;         /**< \brief MCI SD_WP引脚  */

} amdr_mci_devinfo_t;

/**
 * \brief MCI 传输信息
 */
typedef struct amdr_mci_transfer {

    uint8_t   curtran;         /**< \brief 当前数据传输类型, 可为__MCI_CUR_RECV或__MCI_CUR_SEND */
    uint8_t   rxtxflag;        /**< \brief 数据接收/发送标志, 用于标识接收/发送执行结果 */

    uint8_t  *p_recvbuf;       /**< \brief 接收数据缓冲区指针 */
    uint8_t  *p_sendbuf;       /**< \brief 发送数据缓冲区指针 */
    uint32_t  recvcnt;         /**< \brief 接收数据计数器 */
    uint32_t  sendcnt;         /**< \brief 发送数据计数器 */

} amdr_mci_transfer_t;

/**
 * \brief SD卡信息结构体定义
 */
typedef struct amdr_mci_sd {
    uint32_t card_posnum;             /**< \brief 卡座号,多卡时使用 */
    uint8_t  card_type;               /**< \brief 卡型 */

    uint32_t block_num;               /**< \brief 卡中块的数量 */
    uint32_t block_len;               /**< \brief 卡的块长度(单位:字节) */
    uint32_t erase_unit;              /**< \brief 一次可擦除的块个数 */

    uint32_t timeout_read;            /**< \brief 读块超时时间(单位: 1 clock) */
    uint32_t timeout_write;           /**< \brief 写块超时时间(单位: 1 clock) */
    uint32_t timeout_erase;           /**< \brief 擦块超时时间(单位: 1 clock) */

    uint32_t rca;                     /**< \brief 卡的RCA地址 */
    uint32_t host_clkval;             /**< \brief 主机时钟值(Hz)  */
    uint32_t card_transpeed;          /**< \brief 卡数据最大传输速度(Hz) */

} amdr_mci_sd_t;

/**
 * \brief MCI设备
 */
typedef struct amdr_mci_dev {
    
    /** \brief 指向MCI设备信息的指针 */
    const amdr_mci_devinfo_t *p_devinfo;

    /** \brief 传输信息 */
    amdr_mci_transfer_t       trans;

    /** \brief 卡信息 */
    amdr_mci_sd_t             sd;

} amdr_mci_dev_t;

/**
 * \name MCI 期待的命令响应类型
 * \anchor grp_amdr_mci_expect_type
 * @{
 */

typedef uint32_t amdr_mci_expectresp_t;   /**< \brief MCI 期待的命令响应类型  */
#define AMDR_MCI_EXPECT_NO_RESP        0  /**< \brief 无响应 */
#define AMDR_MCI_EXPECT_SHORT_RESP     1  /**< \brief 短响应 */
#define AMDR_MCI_EXPECT_LONG_RESP      2  /**< \brief 长响应 */

/** @} */

/**
 * \name MCI SD卡命令的响应类型
 * \anchor grp_amdr_mci_resptype
 * @{
 */

typedef uint32_t amdr_mci_resptype_t;     /**< \brief MCI 命令的响应类型  */
#define AMDR_MCI_RESPTYPE_R0    0         /**< \brief 响应类型R0 */
#define AMDR_MCI_RESPTYPE_R1    1         /**< \brief 响应类型R1 */
#define AMDR_MCI_RESPTYPE_R1B   2         /**< \brief 响应类型R1B */
#define AMDR_MCI_RESPTYPE_R2    3         /**< \brief 响应类型R2 */
#define AMDR_MCI_RESPTYPE_R3    4         /**< \brief 响应类型R3 */
#define AMDR_MCI_RESPTYPE_R4    5         /**< \brief 响应类型R4 */
#define AMDR_MCI_RESPTYPE_R5    6         /**< \brief 响应类型R5 */
#define AMDR_MCI_RESPTYPE_R6    7         /**< \brief 响应类型R6 */
#define AMDR_MCI_RESPTYPE_R7    8         /**< \brief 响应类型R7 */

/** @} */

/**
 * \name MCI 等待函数的等待类型
 * \anchor grp_amdr_mci_busytype
 * @{
 */

typedef uint32_t amdr_mci_busytype_t;     /**< \brief 等待类型  */
#define AMDR_MCI_BUSY_TYPE_READ        0  /**< \brief 读等待  */
#define AMDR_MCI_BUSY_TYPE_RDY_DATA    1  /**< \brief 可接收数据等待  */
#define AMDR_MCI_BUSY_TYPE_PROG        2  /**< \brief 编程等待  */
#define AMDR_MCI_BUSY_TYPE_ERASE       3  /**< \brief 擦除等待  */

/** @} */

/**
 * \name MCI 等待函数的等待类型
 * \anchor grp_amdr_mci_cardtype
 * @{
 */

typedef uint32_t amdr_mci_cardtype_t;                      /**< \brief 卡类型  */
#define AMDR_MCI_CARDTYPE_UNKNOWN          0x00
#define AMDR_MCI_CARDTYPE_SD               0x01            /**< \brief 卡型为SD  卡  */
#define AMDR_MCI_CARDTYPE_MMC              0x02            /**< \brief 卡型为MMC 卡  */
#define AMDR_MCI_CARDTYPE_SDHC             0x03            /**< \brief 卡型为SDHC卡  */

/** @} */

/**
 * \name MCI 等待函数的等待类型
 * \anchor grp_amdr_mci_cardver
 * @{
 */

typedef uint32_t amdr_mci_cardver_t;     /**< \brief 卡版本  */
#define AMDR_MCI_SD_V1     0x00          /**< \brief version 1 */
#define AMDR_MCI_SD_V2     0x01          /**< \brief version 2 */
#define AMDR_MCI_SD_NA     0x02          /**< \brief unkown */

/** @} */

/**
 * \name MCI 总线宽度设置
 * \anchor grp_amdr_mci_width
 * @{
 */

typedef uint32_t amdr_mci_width_t;       /**< \brief 总线宽度  */
#define AMDR_MCI_WIDTH_1BIT     0x00     /**< \brief 1BIT的总线宽度 */
#define AMDR_MCI_WIDTH_4BIT     0x01     /**< \brief 4BIT的总线宽度 */

/** @} */

/**
 * \name MCI 命令的错误类型
 * \anchor grp_amdr_mci_err
 * @{
 */

typedef uint32_t amdr_mci_err_t;                  /**< \brief MCI 命令的错误类型  */

/** \brief 错误码  error code */
#define AMDR_MCI_ERR_NO_ERR             0x00      /**< \brief 函数执行成功 */
#define AMDR_MCI_ERR_NO_CARD            0x01      /**< \brief 卡没有完全插入到卡座中 */
#define AMDR_MCI_ERR_USER_PARAM         0x02      /**< \brief 用户使用API函数时，入口参数有错误 */
#define AMDR_MCI_ERR_CARD_PARAM         0x03      /**< \brief 卡中参数有错误（与本模块不兼容） */
#define AMDR_MCI_ERR_VOL_NOTSUSP        0x04      /**< \brief 卡不支持3.3V供电 */
#define AMDR_MCI_ERR_OVER_CARDRANGE     0x05      /**< \brief 操作超出卡容量范围 */
#define AMDR_MCI_ERR_UNKNOWN_CARD       0x06      /**< \brief 无法识别卡型 */

#define AMDR_MCI_ERR_CURRENT_STATE      0x07      /**< \brief 卡当前状态不正确(只适用于SD模式) */
#define AMDR_MCI_ERR_READY_FOR_DATA     0x08      /**< \brief 卡数据缓冲区未就绪 */

/** \brief 命令可能返回的错误码  */
#define AMDR_MCI_ERR_CMD_RESPTYPE       0x10      /**< \brief 命令类型错误  */
#define AMDR_MCI_ERR_CMD_TIMEOUT        0x11      /**< \brief 卡命令响应超时  */
#define AMDR_MCI_ERR_CMD_RESP           0x12      /**< \brief 卡命令响应错误  */
#define AMDR_MCI_ERR_CMD_NOTSUSP        0x13      /**< \brief 不支持该命令  */
#define AMDR_MCI_ERR_CMD_RESPCRC        0x14      /**< \brief 命令CRC响应错误  */

/** \brief 数据流错误码  */
#define AMDR_MCI_ERR_DATA_CRC16         0x20      /**< \brief 数据流CRC16校验不通过 */
#define AMDR_MCI_ERR_DATA_START_TOK     0x21      /**< \brief 读单块或多块时，数据开始令牌不正确 */
#define AMDR_MCI_ERR_DATA_RESP          0x22      /**< \brief 写单块或多块时，卡数据响应令牌不正确 */
#define AMDR_MCI_ERR_DATA_STARTBIT      0x23      /**< \brief 写单块或多块时, 数据起始位不正确 */

/** \brief 等待错误码 */
#define AMDR_MCI_ERR_TIMEOUT_WAIT       0x30      /**< \brief 写或擦操作时，发生超时错误 */
#define AMDR_MCI_ERR_TIMEOUT_READ       0x31      /**< \brief 读操作超时错误 */
#define AMDR_MCI_ERR_TIMEOUT_WRITE      0x32      /**< \brief 写操作超时错误 */
#define AMDR_MCI_ERR_TIMEOUT_ERASE      0x33      /**< \brief 擦除操作超时错误 */
#define AMDR_MCI_ERR_TIMEOUT_WAITIDLE   0x34      /**< \brief 初始化卡时，等待卡退出空闲状态超时错误 */

/** \brief 写操作可能返回的错误码 */
#define AMDR_MCI_ERR_WRITE_BLK          0x40      /**< \brief 写块数据错误 */
#define AMDR_MCI_ERR_WRITE_BLKNUMS      0x41      /**< \brief 写多块时，想要写入的块与正确写入的块数不一致 */
#define AMDR_MCI_ERR_WRITE_PROTECT      0x42      /**< \brief 卡外壳的写保护开关打在写保护位置 */

/** \brief 使用UCOS-II时可能出现的错误 */
#define AMDR_MCI_ERR_CREATE_SEMSD       0xA0      /**< \brief 创建SD/MMC卡访问信号量失败 */
#define AMDR_MCI_ERR_WAIT_WRSEM         0xA1      /**< \brief 等待读写信号量失败 */

/** \brief SD_STRUCT结构体可能出现的错误 */
#define AMDR_MCI_ERR_SD_STRUCT          0xB0      /**< \brief SD_STRUCT结构体成员值存在错误 */

/** \brief 其它可能的错误 */
#define AMDR_MCI_ERR_HARDWARE           0xE0      /**< \brief 硬件出错 */

/** @} */


/**
 * \brief MCI 设置 CMD 信号线的开漏状态
 *
 * \param[in] p_dev        : 指向MCI设备的指针
 * \param[in] bopendrain   : bopendrain> 0: CMD 信号线开漏;  = 0: CMD 信号线处于非开漏
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_opendraincmd (amdr_mci_dev_t *p_dev,
                                      uint8_t         bopendrain);

/**
 * \brief MCI 使能SD/MMC主控器是否使能宽总线
 *
 * \param[in] p_dev        : 指向MCI设备的指针
 * \param[in] bwidth       : 总线设置 配置参数 ，参见
 * 							 \ref grp_amdr_mci_width "MCI BUS WIDTH"
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_enablemcibuswidth (amdr_mci_dev_t   *p_dev,
										   amdr_mci_width_t  bwidth);

/**
 * \brief MCI 时钟设置
 *
 * \param[in] p_dev      : 指向MCI设备的指针
 * \param[in] clockrate  : 时钟速率
 *
 * \retval AMDR_MCI_ERR_NO_ERR     : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM : 无效参数
 */
amdr_mci_err_t amdr_mci_clock_set (amdr_mci_dev_t *p_dev,
                                   uint32_t        clockrate);

/**
 * \brief MCI 获取时钟速度
 *
 * \param[in] p_dev      : 指向MCI设备的指针
 *
 * \retval 时钟速度
 */
uint32_t amdr_mci_clock_get (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI 发送命令给卡, 但不获取响应
 *
 * \param[in] p_dev        : 指向MCI设备的指针
 * \param[in] cmdindex     : 命令索引
 * \param[in] argument     : 命令参数
 * \param[in] expectresp   : 期望响应类型   配置参数，参见
 *                           \ref grp_amdr_mci_resptype "MCI RESP TYPE"
 * \param[in] allowtimeout : 是否允许超时
 *
 * \retval AMDR_MCI_ERR_NO_ERR      : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM  : 无效参数
 */
amdr_mci_err_t amdr_mci_cmdsend (amdr_mci_dev_t        *p_dev,
                                 uint32_t               cmdindex,
                                 uint32_t               argument,
                                 amdr_mci_expectresp_t  expectresp,
                                 uint32_t               allowtimeout);

/**
 * \brief MCI 从卡获取响应, 该函数与MCI_SendCmd()成对使用
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] expectcmddata : 命令码
 * \param[in] expectresp    : 希望的响应 配置参数，参见
 *                            \ref grp_amdr_mci_expect_type "MCI EXPECT TYPE"
 * \param[in] resplen       : 响应长度
 * \param[out] p_cmdresp    : 响应内容
 *
 * \retval AMDR_MCI_ERR_NO_ERR      : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM  : 无效参数
 * \retval AMDR_MCI_ERR_CMD_TIMEOUT : 返回响应命令超时错误
 * \retval AMDR_MCI_ERR_CMD_RESPCRC : 返回响应命令CRC校验失败错误
 * \retval AMDR_MCI_ERR_CMD_RESP    : 返回响应错误
 */
amdr_mci_err_t amdr_mci_cmdresp_get (amdr_mci_dev_t        *p_dev,
                                     uint32_t               expectcmddata,
                                     amdr_mci_expectresp_t  expectresp,
                                     size_t                 resplen,
                                     uint32_t              *p_cmdresp);

/**
 * \brief MCI 发送一个命令并从卡获取响应
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] cmd           : 命令码
 * \param[in] argument      : 命令参数
 * \param[in] resptype      : 响应类型 配置参数，参见
 *                            \ref grp_amdr_mci_resptype "MCI RESP TYPE"
 * \param[in] resplen       : 响应长度
 * \param[out] p_resp       : 响应内容
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM   : 无效参数
 * \retval AMDR_MCI_ERR_CMD_RESPTYPE : 错误的响应类型
 * \retval AMDR_MCI_ERR_CMD_TIMEOUT  : 返回响应命令超时错误
 * \retval AMDR_MCI_ERR_CMD_RESPCRC  : 返回响应命令CRC校验失败错误
 * \retval AMDR_MCI_ERR_CMD_RESP     : 返回响应错误
 */
amdr_mci_err_t amdr_mci_cmdsend_respget (amdr_mci_dev_t      *p_dev,
                                         uint8_t              cmd,
                                         uint32_t             argument,
                                         amdr_mci_resptype_t  resptype,
                                         size_t               resplen,
                                         uint32_t            *p_resp);

/**
 * \brief MCI 检测卡是否完全插入卡座中
 *
 * \param[in] p_dev : 指向MCI设备的指针
 *
 * \retval 0 : 未插入
 * \retval 1 : 插入
 */
uint8_t amdr_mci_checkcard (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI 检测卡写保护
 *
 * \param[in] p_dev : 指向MCI设备的指针
 *
 * \retval 0 : 未写保护
 * \retval 1 : 写保护
 */
uint8_t amdr_mci_check_wp (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI 在发送读单块命令之前, 给硬件控制器做一些事情的机会
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM   : 无效参数
 */
amdr_mci_err_t amdr_mci_before_readblock (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI 在发送读单块命令之后, 由硬件控制器实现读取数据
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] p_recvbuf     : 接收缓冲区, 大小为512字节
 *
 * \retval 错误代码  参见 \ref grp_amdr_mci_err "MCI ERROR TYPE"
 */
amdr_mci_err_t amdr_mci_readblock (amdr_mci_dev_t *p_dev,
                                   uint8_t        *p_recvbuf);

/**
 * \brief MCI 在发送写单块命令之前, 给硬件控制器做一些事情的机会
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM   : 无效参数
 */
amdr_mci_err_t amdr_mci_before_writeblock (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI 在发送写单块命令之后, 由硬件控制器向卡发送数据
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] p_sendbuf     : 发送缓存 大小为512字节
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM   : 无效参数
 */
amdr_mci_err_t amdr_mci_writeblock (amdr_mci_dev_t *p_dev, uint8_t *p_sendbuf);

/**
 * \brief MCI 等待卡可接收数据(等待卡中有空的接收缓冲区), 即等待卡状态寄存器的 bit8 为1
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM   : 无效参数
 * \retval AMDR_MCI_ERR_NO_CARD      : 无卡插入
 */
amdr_mci_err_t amdr_mci_waitreadyfordata (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI 等待卡编程或擦除结束, 即等待卡状态由编程状态变为传输状态: prg --> tran
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] busytype      : 忙等待类型 配置参数，参见
 *                            \ref grp_amdr_mci_busytype "MCI BUSY TYPE"
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM   : 无效参数
 * \retval AMDR_MCI_ERR_NO_CARD      : 无卡插入
 */
amdr_mci_err_t amdr_mci_waitbusy (amdr_mci_dev_t      *p_dev,
                                  amdr_mci_busytype_t  busytype);

/**
 * \brief MCI CMD0, 复位所有卡, 使卡进入Idle状态
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM   : 无效参数
 * \retval AMDR_MCI_ERR_CMD_RESPTYPE : 错误的响应类型
 * \retval AMDR_MCI_ERR_CMD_TIMEOUT  : 返回响应命令超时错误
 * \retval AMDR_MCI_ERR_CMD_RESPCRC  : 返回响应命令CRC校验失败错误
 * \retval AMDR_MCI_ERR_CMD_RESP     : 返回响应错误
 */
amdr_mci_err_t amdr_mci_sdcmd_go_idle_state (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI CMD1(仅用于MMC卡), 使卡退出Idle状态, 进入Ready状态(通过判断MMC卡的OCR寄存器值)
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \retval AMDR_MCI_ERR_NO_ERR       : 设置成功
 * \retval AMDR_MCI_ERR_USER_PARAM   : 无效参数
 * \retval AMDR_MCI_ERR_CMD_RESPTYPE : 错误的响应类型
 * \retval AMDR_MCI_ERR_CMD_TIMEOUT  : 返回响应命令超时错误
 * \retval AMDR_MCI_ERR_CMD_RESPCRC  : 返回响应命令CRC校验失败错误
 * \retval AMDR_MCI_ERR_CMD_RESP     : 返回响应错误
 */
amdr_mci_err_t amdr_mci_sdcmd_send_op_cond (amdr_mci_dev_t *p_dev);

/**
 * \brief MCI CMD8 识别卡版本
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \retval  AMDR_MCI_SD_V1  : 卡版本号1
 * \retval  AMDR_MCI_SD_V2  : 卡版本号2
 * \retval  AMDR_MCI_SD_NA  : 卡版本号未知
 */
amdr_mci_cardver_t amdr_mci_sdcmd_checksdversion (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD55(仅用于SD卡), 在发送所有 ACMDxx 命令之前, 必须先发送本命令
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_send_acmd (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI ACMD41(仅用于SD卡), 使卡退出Idle状态, 并进入Ready状态(通过判断SD卡的OCR寄存器值)
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_sd_app_op_cond (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD2 获取所有卡的CID寄存器内容
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] cidlen        : CID 寄存器长度, 固定为16字节
 * \param[in] p_cidbuf      : CID 寄存器内容, 长度为16字节
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_all_send_cid (amdr_mci_dev_t      *p_dev,
                                            uint8_t              cidlen,
                                            uint8_t             *p_cidbuf);

/**
 * \brief MCI CMD3, 获取卡的RCA地址, 然后保存到sds结构体中
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_set_relative_addr (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD9, 获取卡的CSD寄存器值
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] csdlen        : CSD 寄存器长度
 * \param[out] p_csdbuf     : CSD寄存器内容, bit127 在csdbuf[0]
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_send_csd (amdr_mci_dev_t      *p_dev,
                                        uint8_t              csdlen,
                                        uint8_t             *p_csdbuf);

/**
 * \brief MCI CMD 7: 选择卡, 使卡在 Stand-by 与 Transfer 之间切换
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_select_card (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD 7: 取消选择卡, 使卡在 Stand-by 与 Transfer 之间切换
 *
 * \param[in] p_dev : 指向MCI设备的指针
 * \param[in] rca   : SD/MMC卡信息结构体
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_deselect_card (amdr_mci_dev_t *p_dev,
                                             uint32_t        rca);

/**
 * \brief MCI CMD12: 停止传输Stop Transmission
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_stop_transmission (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD13, 读取卡当前状态, 当卡进入数据传输模式后(即从识别模式进入该模式后), 就可以使用本函数
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[out] p_status     : 卡状态
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_send_status (amdr_mci_dev_t      *p_dev,
                                           uint32_t            *p_status);

/**
 * \brief MCI CMD15, 使卡进入非活动状态
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_go_inactive_state (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI CMD 16: 设置块长度, 必须发送CMD7后发送
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockLen      : 卡块的长度
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_set_blocklen (amdr_mci_dev_t      *p_dev,
                                            uint32_t             blockLen);

/**
 * \brief MCI ACMD6, 设置卡传输数据的总线宽度(对于SD卡, 可以为1bit, 也可以为4bits) 对于MMC卡, 本命令无效
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] bwidebus      : 宽总线 配置参数，参见\ref grp_amdr_mci_width "MCI WIDTH"
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_set_bus_width (amdr_mci_dev_t      *p_dev,
											 amdr_mci_width_t     bwidebus);

/**
 * \brief MCI CMD17, 发送读单块命令
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockadddr    : 块地址. 0 ~ 511字节取值为1. 512 ~ 1023字节取值为2
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_read_single_block (amdr_mci_dev_t *p_dev,
                                                 uint32_t        blockadddr);

/**
 * \brief MCI CMD18, 发送读多块命令
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockadddr    : 块地址
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_read_multiple_block (amdr_mci_dev_t *p_dev,
                                                   uint32_t        blockadddr);

/**
 * \brief MCI CMD24, 发送写单块命令
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockadddr    : 块地址
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_write_single_block (amdr_mci_dev_t *p_dev,
                                                  uint32_t        blockadddr);

/**
 * \brief MCI CMD25, 发送写多块命令
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockadddr    : 块地址
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_write_multiple_block (amdr_mci_dev_t *p_dev,
                                                    uint32_t        blockadddr);

/**
 * \brief MCI CMD32或CMD35: 设置擦卡起始地址
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockadddr    : 块地址
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_erase_wr_blk_start (amdr_mci_dev_t *p_dev,
                                                  uint32_t        blockadddr);

/**
 * \brief MCI CMD33或CMD36, 设置擦卡终止地址
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockadddr    : 块地址
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_erase_wr_blk_end (amdr_mci_dev_t      *p_dev,
                                                uint32_t             blockadddr);

/**
 * \brief MCI CMD38, 擦除所选择指定的块
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdcmd_erase (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI  从SD/MMC卡中读出一个数据块
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockaddr     : 以块为单位的块地址, 例如, 卡开始的0 ~ 511字节为块地址0, 512 ~ 1023字节的块地址为1
 * \param[out] p_recbuf     : 接收缓冲区,长度固定为 512 字节
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_readblock (amdr_mci_dev_t      *p_dev,
                                      uint32_t             blockaddr,
                                      uint8_t             *p_recbuf);

/**
 * \brief MCI 从SD/MMC卡中读出多个数据块
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockaddr     : 以块为单位的块地址
 * \param[in] blocknum      : 要读取的块的个数
 * \param[out] p_recbuf     : 接收缓冲区, 长度512 * blocknum 字节
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_readmultiblock (amdr_mci_dev_t      *p_dev,
                                           uint32_t             blockaddr,
                                           uint32_t             blocknum,
                                           uint8_t             *p_recbuf);

/**
 * \brief MCI 向SD/MMC卡中写入一个块
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockaddr     : 以块为单位的块地址, 例如, 卡开始的0 ~ 511字节为块地址0, 512 ~ 1023字节的块地址为1
 * \param[in] p_sendbuf     : 发送缓冲区,长度固定为 512 字节
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_writeblock (amdr_mci_dev_t      *p_dev,
                                       uint32_t             blockaddr,
                                       uint8_t             *p_sendbuf);

/**
 * \brief MCI 向SD/MMC卡中写入多个数据块
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] blockaddr     : 以块为单位的块地址, 例如, 卡开始的0 ~ 511字节为块地址0, 512 ~ 1023字节的块地址为1
 * \param[in] blocknum      : 要写入的块的个数
 * \param[in] p_sendbuf     : 发送缓冲区, 长度 512 * blocknum 字节
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_writemultiblock (amdr_mci_dev_t      *p_dev,
                                            uint32_t             blockaddr,
                                            uint32_t             blocknum,
                                            uint8_t             *p_sendbuf);

/**
 * \brief MCI 擦除SD/MMC卡中的块
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 * \param[in] startaddr     : 擦卡的起始地址, 地址为以块为单位的块地址
 * \param[in] blocknum      : 擦除的块数
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_eraseblock (amdr_mci_dev_t      *p_dev,
                                       uint32_t             startaddr,
                                       uint32_t             blocknum);

/**
 * \brief MCI SD2.00 SDHC card识别
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sd_ver2activeinit (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI 识别卡: SD, MMC, 或不可卡别卡
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdmmc_identifycard (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI 对卡的相关参数进行配置, 如卡总线宽度, 卡数据块大小
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdmmc_configcard (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI 获得SD/MMC卡的信息
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdmmc_getcardinfo (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI 计算读/写/擦超时时间
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_sdmmc_caltimeout (amdr_mci_dev_t      *p_dev);

/**
 * \brief MCI SD/MMC 卡初始化: 复位卡,识别卡,获取卡相关信息,使卡从识别模式进入数据传输模式
 *
 * \param[in] p_dev         : 指向MCI设备的指针
 *
 * \return 错误代码  参见  \ref grp_amdr_mci_err "MCI ERROR CODE"
 */
amdr_mci_err_t amdr_mci_card_init (amdr_mci_dev_t      *p_dev);

/**
 * \brief 注册中断回调函数
 *
 * \param[in] p_dev        : MCI设备
 * \param[in] inttype      : 中断类型 中断类型 配置参数，参见
 *                           \ref grp_amhw_mci_int_type "MCI INTERRUPT TYPE"
 * \param[in] pfn_callback : 要注册的回调函数
 * \param[in] p_arg        : 传进回调函数的参数
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 */
int amdr_mci_intcb_connect (amdr_mci_dev_t      *p_dev,
                            amhw_mci_int_type_t  inttype,
                            am_pfnvoid_t         pfn_callback,
                            void                *p_arg);

/**
 * \brief 删除某个类型的中断回调函数
 *
 * \param[in] p_dev        : MCI设备
 * \param[in] inttype      : 中断类型 配置参数，参见
 *                           \ref grp_amhw_mci_int_type "MCI INTERRUPT TYPE"
 *
 * \retval AM_OK        正常
 * \retval -AM_EINVAL   参数无效
 */
int amdr_mci_intcb_disconnect (amdr_mci_dev_t        *p_dev,
                               amhw_mci_int_type_t    inttype);

/**
 * \brief MCI初始化
 *
 * \param[in] p_dev     : 指向MCI设备的指针
 * \param[in] p_devinfo : 指向MCI设备信息的指针
 *
 * \retval AM_OK      : 操作成功
 * \retval -AM_EINVAL : 参数错误
 */
int amdr_mci_init (amdr_mci_dev_t           *p_dev,
                   const amdr_mci_devinfo_t *p_devinfo);

/**
 * \brief MCI解初始化
 *
 * \param[in] p_dev : 指向MCI设备的指针
 *
 * \return 无 
 */
void amdr_mci_deinit (amdr_mci_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_MCI_H */

/* end of file */
