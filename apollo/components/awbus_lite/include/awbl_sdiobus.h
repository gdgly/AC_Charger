/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AWBus SDIO bus type implementation (lite)
 *
 * \internal
 * \par modification history:
 * - 1.00 14-08-08  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_SDIOBUS_H_
#define __AWBL_SDIOBUS_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */
#include "aw_task.h"
#include "aw_list.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "awbus_lite.h"
#include "string.h"

#define AWBL_SDIO_SLOT_DETECT_STACK_SIZE       4096

/* SDIO command */
#define AWBL_SDIO_CMD0      0
#define AWBL_SDIO_CMD1      1
#define AWBL_SDIO_CMD2      2
#define AWBL_SDIO_CMD3      3
#define AWBL_SDIO_CMD4      4
#define AWBL_SDIO_CMD5      5
#define AWBL_SDIO_CMD6      6
#define AWBL_SDIO_CMD7      7
#define AWBL_SDIO_CMD8      8
#define AWBL_SDIO_CMD9      9
#define AWBL_SDIO_CMD10     10
#define AWBL_SDIO_CMD11     11
#define AWBL_SDIO_CMD12     12
#define AWBL_SDIO_CMD13     13
#define AWBL_SDIO_CMD14     14
#define AWBL_SDIO_CMD15     15
#define AWBL_SDIO_CMD16     16
#define AWBL_SDIO_CMD17     17
#define AWBL_SDIO_CMD18     18
#define AWBL_SDIO_CMD19     19
#define AWBL_SDIO_CMD20     20
#define AWBL_SDIO_CMD21     21
#define AWBL_SDIO_CMD22     22
#define AWBL_SDIO_CMD23     23
#define AWBL_SDIO_CMD24     24
#define AWBL_SDIO_CMD25     25
#define AWBL_SDIO_CMD26     26
#define AWBL_SDIO_CMD27     27
#define AWBL_SDIO_CMD28     28
#define AWBL_SDIO_CMD29     29
#define AWBL_SDIO_CMD31     31
#define AWBL_SDIO_CMD32     32
#define AWBL_SDIO_CMD33     33
#define AWBL_SDIO_CMD34     34
#define AWBL_SDIO_CMD35     35
#define AWBL_SDIO_CMD36     36
#define AWBL_SDIO_CMD37     37
#define AWBL_SDIO_CMD38     38
#define AWBL_SDIO_CMD39     39
#define AWBL_SDIO_CMD40     40
#define AWBL_SDIO_CMD41     41
#define AWBL_SDIO_CMD42     42
#define AWBL_SDIO_CMD43     43
#define AWBL_SDIO_CMD44     44
#define AWBL_SDIO_CMD45     45
#define AWBL_SDIO_CMD46     46
#define AWBL_SDIO_CMD47     47
#define AWBL_SDIO_CMD48     48
#define AWBL_SDIO_CMD49     49
#define AWBL_SDIO_CMD50     50
#define AWBL_SDIO_CMD51     51
#define AWBL_SDIO_CMD52     52
#define AWBL_SDIO_CMD53     53
#define AWBL_SDIO_CMD54     54
#define AWBL_SDIO_CMD55     55
#define AWBL_SDIO_CMD56     56
#define AWBL_SDIO_CMD57     57
#define AWBL_SDIO_CMD57     57
#define AWBL_SDIO_CMD58     58
#define AWBL_SDIO_CMD59     59

#define AWBL_SDIO_ACMD6     6
#define AWBL_SDIO_ACMD13    13
#define AWBL_SDIO_ACMD14    14
#define AWBL_SDIO_ACMD15    15
#define AWBL_SDIO_ACMD16    16
#define AWBL_SDIO_ACMD22    22
#define AWBL_SDIO_ACMD23    23
#define AWBL_SDIO_ACMD28    28
#define AWBL_SDIO_ACMD41    41
#define AWBL_SDIO_ACMD42    42
#define AWBL_SDIO_ACMD51    51


/* response of R1 on SD mode  */
#define AWBL_SD_R1_OUT_OF_RANGE          (1 << 31)           /* 命令参数段超出范围 */
#define AWBL_SD_R1_ADDRESS_ERROR         (1 << 30)           /* 地址错误 */
#define AWBL_SD_R1_BLOCK_LEN_ERROR       (1 << 29)           /* 卡不支持指定的块长度或是传输的字节数与块长度不匹配 */
#define AWBL_SD_R1_ERASE_SEQ_ERROR       (1 << 28)           /* 当前擦除命令序列有错误 */
#define AWBL_SD_R1_ERASE_PARAM           (1 << 27)           /* 当前指定写入或擦除的块无效 */
#define AWBL_SD_R1_WP_VIOLATION          (1 << 26)           /* 当前指定写入的块为写保护块 */
#define AWBL_SD_R1_CARD_IS_LOCKED        (1 << 25)           /* 指示当前卡是否被锁定 */
#define AWBL_SD_R1_LOCK_UNLOCK_FAILED    (1 << 24)           /* 指示在lock/unlock命令下，密码序列校验错误 */
#define AWBL_SD_R1_COM_CRC_ERROR         (1 << 23)           /* CRC校验失败 */
#define AWBL_SD_R1_ILLEGAL_COMMAND       (1 << 22)           /* 非法命令，对于当前卡状态  */
#define AWBL_SD_R1_CARD_ECC_FAILED       (1 << 21)           /* ECC失败 */
#define AWBL_SD_R1_CC_ERROR              (1 << 20)           /* 卡内部控制器错误 */
#define AWBL_SD_R1_ERROR                 (1 << 19)           /* 未知错误 */
#define AWBL_SD_R1_UNDERRUN              (1 << 18)
#define AWBL_SD_R1_OVERRUN               (1 << 17)
#define AWBL_SD_R1_CID_CSD_OVERWRITE     (1 << 16)           /* CID/CSD overwrite */
#define AWBL_SD_R1_WP_ERASE_SKIP         (1 << 15)           /* 跳过写保护区域 */
#define AWBL_SD_R1_CARD_ECC_DISABLED     (1 << 14)           /* 指示内部ECC是否被禁用 */
#define AWBL_SD_R1_ERASE_RESET           (1 << 13)
#define AWBL_SD_R1_STATUS(x)            (x & 0xFFFFE000)
#define AWBL_SD_R1_CURRENT_STATE(x)  ((x & 0x00001E00) >> 9) /* 当前状态 */
#define AWBL_SD_R1_READY_FOR_DATA        (1 << 8)            /* 总线可进行数据传输 */
#define AWBL_SD_R1_SWITCH_ERROR          (1 << 7)
#define AWBL_SD_R1_EXCEPTION_EVENT       (1 << 6)
#define AWBL_SD_R1_APP_CMD               (1 << 5)            /* 指示当前卡是否进入了APP CMD模式 */
#define AWBL_SD_R1_ALL_ERROR             0xF9F90000

/*  card status of R1 on SD mode  */
#define AWBL_SD_R1_STATE_IDLE   0
#define AWBL_SD_R1_STATE_READY  1
#define AWBL_SD_R1_STATE_IDENT  2
#define AWBL_SD_R1_STATE_STBY   3
#define AWBL_SD_R1_STATE_TRAN   4
#define AWBL_SD_R1_STATE_DATA   5
#define AWBL_SD_R1_STATE_RCV    6
#define AWBL_SD_R1_STATE_PRG    7
#define AWBL_SD_R1_STATE_DIS    8

/*  card status of R1 on SPI mode  */
#define AWBL_SD_SPI_R1_IN_IDLE_STATE        0x01    /* 指示卡是否处于空闲状态 */
#define AWBL_SD_SPI_R1_ERASE_RESET          0x02    /* 操作被复位 */
#define AWBL_SD_SPI_R1_ILLEGAL_CMD          0x04    /* 对于当前卡状态为非法命令  */
#define AWBL_SD_SPI_R1_COM_CRC_ERROR        0x08    /* CRC校验失败 */
#define AWBL_SD_SPI_R1_ERASE_SEQ_ERROR      0x10    /* 擦除错误 */
#define AWBL_SD_SPI_R1_ADDRESS_ERROR        0x20    /* 地址错误，非对齐或是与数据长度不匹配 */
#define AWBL_SD_SPI_R1_PARA_ERROR           0x40    /* 参数错误，命令参数段不合法  */
#define AWBL_SD_SPI_R1_ALL_ERROR            0x7E
#define AWBL_SD_SPI_R1_MASK                 0x7F

/*  card status of R2 on SPI mode  */
#define AWBL_SD_SPI_R2_CARD_LOCKED          0x01    /* 卡被锁定 */
#define AWBL_SD_SPI_R2_WP_ERASE_SKIP        0x02    /* 忽略写保护,擦除 */
#define AWBL_SD_SPI_R2_LOCK_UNLOCK_FAIL     0x02    /* LOCK、UNLOCK命令失败 */
#define AWBL_SD_SPI_R2_ERROR                0x04    /* 为止错误 */
#define AWBL_SD_SPI_R2_CC_ERROR             0x08    /* 卡内部控制器错误 */
#define AWBL_SD_SPI_R2_CARD_ECC_ERROR       0x10    /* ECC错误 */
#define AWBL_SD_SPI_R2_WP_VIOLATION         0x20    /* 对写保护区域进行了写操作 */
#define AWBL_SD_SPI_R2_ERASE_PARAM          0x40    /* 擦除参数无效，对无效区域擦除 */
#define AWBL_SD_SPI_R2_OUT_OF_RANGE         0x80    /*  */
#define AWBL_SD_SPI_R2_CSD_OVERWRITE        0x80

/*  OCR register  */
#define AWBL_SD_OCR_VDD_165_195     0x00000080  /* VDD voltage 1.65 - 1.95 */
#define AWBL_SD_OCR_VDD_20_21       0x00000100  /* VDD voltage 2.0 ~ 2.1 */
#define AWBL_SD_OCR_VDD_21_22       0x00000200  /* VDD voltage 2.1 ~ 2.2 */
#define AWBL_SD_OCR_VDD_22_23       0x00000400  /* VDD voltage 2.2 ~ 2.3 */
#define AWBL_SD_OCR_VDD_23_24       0x00000800  /* VDD voltage 2.3 ~ 2.4 */
#define AWBL_SD_OCR_VDD_24_25       0x00001000  /* VDD voltage 2.4 ~ 2.5 */
#define AWBL_SD_OCR_VDD_25_26       0x00002000  /* VDD voltage 2.5 ~ 2.6 */
#define AWBL_SD_OCR_VDD_26_27       0x00004000  /* VDD voltage 2.6 ~ 2.7 */
#define AWBL_SD_OCR_VDD_27_28       0x00008000  /* VDD voltage 2.7 ~ 2.8 */
#define AWBL_SD_OCR_VDD_28_29       0x00010000  /* VDD voltage 2.8 ~ 2.9 */
#define AWBL_SD_OCR_VDD_29_30       0x00020000  /* VDD voltage 2.9 ~ 3.0 */
#define AWBL_SD_OCR_VDD_30_31       0x00040000  /* VDD voltage 3.0 ~ 3.1 */
#define AWBL_SD_OCR_VDD_31_32       0x00080000  /* VDD voltage 3.1 ~ 3.2 */
#define AWBL_SD_OCR_VDD_32_33       0x00100000  /* VDD voltage 3.2 ~ 3.3 */
#define AWBL_SD_OCR_VDD_33_34       0x00200000  /* VDD voltage 3.3 ~ 3.4 */
#define AWBL_SD_OCR_VDD_34_35       0x00400000  /* VDD voltage 3.4 ~ 3.5 */
#define AWBL_SD_OCR_VDD_35_36       0x00800000  /* VDD voltage 3.5 ~ 3.6 */
#define AWBL_SD_OCR_S18R            0x01000000  /* 1.8V switching request */
#define AWBL_SD_OCR_XPC             0x10000000  /* SDXC power control */
#define AWBL_SD_OCR_CCS             0x40000000  /* Card Capacity Status (CCS)1 */



#define AWBL_SDIO_CARD_TO_HOST_INFO_DECL(p_info, p_card) \
        awbl_sdio_host_info_t *p_info = \
            (awbl_sdio_host_info_t *)AWBL_DEVINFO_GET( \
                &(((awbl_sdio_card_t *)p_card)->slot->host->super.super))

#define AWBL_SDIO_CARD_TO_HOST_DECL(p_host, p_card) \
            awbl_sdio_host_t *p_host = ((awbl_sdio_card_t *)p_card)->slot->host;

#define AWBL_SDIO_CARD_TO_SLOT_DECL(p_slot, p_card) \
            awbl_sdio_slot_t *p_slot = ((awbl_sdio_card_t *)p_card)->slot;

#define AWBL_DEV_TO_CARD_DECL(p_card, p_awdev) \
            awbl_sdio_card_t *p_card = \
                (awbl_sdio_card_t *)AW_CONTAINER_OF( \
                    p_awdev, awbl_sdio_card_t, super);


typedef struct awbl_sdio_cmd        awbl_sdio_cmd_t;
typedef struct awbl_sdio_slot       awbl_sdio_slot_t;
typedef struct awbl_sdio_cid        awbl_sdio_cid_t;
typedef struct awbl_sdio_msg        awbl_sdio_msg_t;

typedef struct awbl_sdio_host       awbl_sdio_host_t;
typedef struct awbl_sdio_card       awbl_sdio_card_t;
typedef struct awbl_sdio_host_info  awbl_sdio_host_info_t;
typedef struct awbl_sdio_card_info  awbl_sdio_card_info_t;


typedef enum _sdio_host_mode{
    SDIO_SPI_M,
    SDIO_SD_1B_M,
    SDIO_SD_4B_M
}sdio_host_mode_t;

enum {
    SDIO_BUS_WIDTH_1B,
    SDIO_BUS_WIDTH_4B
};

enum {
    SDIO_TYPE_ILLEGAL,
    SDIO_TYPE_MEM,              /* 存储卡，SD卡、MMC卡 */
    SDIO_TYPE_SDIO,             /* SDIO 卡，单纯IO卡  */
    SDIO_TYPE_COMBO             /* SD combo (IO+mem) 卡 */
};

enum {
    SDIO_SPI_CRC_ENABLE,
    SDIO_SPI_CRC_DISABLE
};

/* SDIO host information  */
struct awbl_sdio_host_info {
    uint8_t             bus_index;
    sdio_host_mode_t    mode;
    uint32_t            ocr_valid;
#define SDIO_VDD_165_195    0x00000001  /* VDD voltage 1.65 - 1.95 */
#define SDIO_VDD_20_21      0x00000002  /* VDD voltage 2.0 ~ 2.1 */
#define SDIO_VDD_21_22      0x00000004  /* VDD voltage 2.1 ~ 2.2 */
#define SDIO_VDD_22_23      0x00000008  /* VDD voltage 2.2 ~ 2.3 */
#define SDIO_VDD_23_24      0x00000010  /* VDD voltage 2.3 ~ 2.4 */
#define SDIO_VDD_24_25      0x00000020  /* VDD voltage 2.4 ~ 2.5 */
#define SDIO_VDD_25_26      0x00000040  /* VDD voltage 2.5 ~ 2.6 */
#define SDIO_VDD_26_27      0x00000080  /* VDD voltage 2.6 ~ 2.7 */
#define SDIO_VDD_27_28      0x00000100  /* VDD voltage 2.7 ~ 2.8 */
#define SDIO_VDD_28_29      0x00000200  /* VDD voltage 2.8 ~ 2.9 */
#define SDIO_VDD_29_30      0x00000400  /* VDD voltage 2.9 ~ 3.0 */
#define SDIO_VDD_30_31      0x00000800  /* VDD voltage 3.0 ~ 3.1 */
#define SDIO_VDD_31_32      0x00001000  /* VDD voltage 3.1 ~ 3.2 */
#define SDIO_VDD_32_33      0x00002000  /* VDD voltage 3.2 ~ 3.3 */
#define SDIO_VDD_33_34      0x00004000  /* VDD voltage 3.3 ~ 3.4 */
#define SDIO_VDD_34_35      0x00008000  /* VDD voltage 3.4 ~ 3.5 */
#define SDIO_VDD_35_36      0x00010000  /* VDD voltage 3.5 ~ 3.6 */
    uint8_t             crc_en;
};


/* SDIO card driver information  */
struct awbl_sdio_card_info {
    struct awbl_drvinfo super;
};


/* SDIO host controller  */
struct awbl_sdio_host {
    struct awbl_busctlr     super;
    awbl_sdio_slot_t       *slot_list;

    aw_spinlock_isr_t       dev_lock;
    AW_MUTEX_DECL(dev_mux);

    bool_t                  lock;

    struct aw_list_head     msg_list;

    /* startup transfer */
    aw_err_t (*xfer) (awbl_sdio_host_t *p_host);

    void (*cancel) (awbl_sdio_host_t *p_host,
                    awbl_sdio_msg_t  *p_msg);

    /* set bus speed */
    uint32_t (*set_speed) (awbl_sdio_host_t *p_host, uint32_t speed);

    /* set bus width */
    aw_err_t (*set_bus_width) (awbl_sdio_host_t *p_host, uint32_t width);

    /* output n clocks */
    aw_err_t (*dummy_clks) (awbl_sdio_host_t *p_host, uint8_t nclks);

    /* reset controller */
    void (*host_reset) (awbl_sdio_host_t *p_host);
};

/* SDIO card  */
struct awbl_sdio_card {
    struct awbl_dev     super;
    awbl_sdio_slot_t    *slot;
    uint8_t             type;
    uint8_t             state;
#define SDIO_CARD_DRIVER        (1<<0)
#define SDIO_CARD_READ_ONLY     (1<<1)
};



/* SDIO response type  */
enum  {
    RSP_NONE,
    RSP_R1,
    RSP_R1B,
    RSP_R2,
    RSP_R3,
    RSP_R4,
    RSP_R5,
    RSP_R6,
    RSP_R7,
};

/* command option */
enum {
    NO_DATA,
    RD_DATA,
    WR_DATA
};

/* command */
struct awbl_sdio_cmd{
    struct aw_list_head cmd_node;
    uint32_t        cmd;            /* SDIO command*/
    uint32_t        arg;            /* parameter */
    uint8_t         opt;            /* option */
    void            *pdata;         /* data */
    uint32_t        blk_size;       /* block size */
    uint32_t        nblock;         /* block count */
    uint8_t         rsp_type;       /* response type */
    uint32_t        *p_rsp;         /* response data */
    uint8_t         retries;
};

/* message */
struct awbl_sdio_msg {
    struct aw_list_head msg_node;
    struct aw_list_head cmd_list;
    int                 status;         /* message complete status  */
    void                *p_arg;         /* complete call back */
    void (*complete) (void *p_arg);     /* for complete*/
};


/* slot state */
enum {
    SDIO_CD_PLUG,   /* card insert */
    SDIO_CD_STUBBS  /* card remove */
};

enum {
    SDIO_READ_ONLY, /* read only */
    SDIO_WRITE_EN   /* write enable */
};

/* SDIO slot */
struct awbl_sdio_slot {
    awbl_sdio_slot_t    *next;
    awbl_sdio_host_t    *host;

    uint8_t             ro_state;           /* storage RO pin state */
    uint8_t             cd_state;           /* storage CD pin state */

    bool_t            (*_detect) (awbl_sdio_slot_t *p_slot);
    AW_TASK_DECL(       detect_task,
                        AWBL_SDIO_SLOT_DETECT_STACK_SIZE);

    struct awbl_devhcf  card_devhcf;        /* device information for card */
    char                card_name[12];      /* card name */
    awbl_sdio_card_t   *p_card;            /* memory for card */
    uint32_t            card_buf_size;      /* memory size*/
};

/* method for SDIO bus */
AWBL_METHOD_IMPORT(awbl_sdio_match_type);
AWBL_METHOD_IMPORT(awbl_sdio_del_card);

/**
 * \brief post a message to controller
 */
aw_local aw_inline void awbl_sdio_msg_in (awbl_sdio_host_t *p_host,
                                          awbl_sdio_msg_t  *p_msg)
{
    aw_spinlock_isr_take(&(p_host->dev_lock));
    aw_list_add_tail(&(p_msg->msg_node),
                     &(p_host->msg_list));
    p_msg->status = -EISCONN;
    aw_spinlock_isr_give(&(p_host->dev_lock));
}

/**
 * \brief get a message from controller
 */
aw_local aw_inline awbl_sdio_msg_t *
    awbl_sdio_msg_out (awbl_sdio_host_t *p_host)
{
    awbl_sdio_msg_t *p_msg = NULL;

    aw_spinlock_isr_take(&(p_host->dev_lock));
    if (!aw_list_empty(&(p_host->msg_list))) {

        p_msg = (awbl_sdio_msg_t*)
                    aw_list_first_entry(
                        &p_host->msg_list,
                        awbl_sdio_msg_t,
                        msg_node);
        aw_list_del(&p_msg->msg_node);
    }
    aw_spinlock_isr_give(&(p_host->dev_lock));
    return p_msg;
}

/**
 * \brief check if message empty
 */
aw_local aw_inline int awbl_sdio_msg_empty (awbl_sdio_host_t *p_host)
{
    return aw_list_empty_careful(&p_host->msg_list);
}

/**
 * \brief config command
 */
aw_local aw_inline void aw_sdio_config_cmd (awbl_sdio_cmd_t *p_cmd,
                                            uint8_t         cmd,
                                            uint32_t        arg,
                                            uint8_t         opt,
                                            void            *p_data,
                                            uint32_t        blk_size,
                                            uint32_t        nblk,
                                            uint8_t         rsp_type,
                                            void            *p_rsp,
                                            uint8_t         retries)
{
    p_cmd->cmd      = cmd;
    p_cmd->arg      = arg;
    p_cmd->opt      = opt;
    p_cmd->pdata    = p_data;
    p_cmd->blk_size = blk_size;
    p_cmd->nblock   = nblk;
    p_cmd->rsp_type = rsp_type;
    p_cmd->p_rsp    = p_rsp;
    p_cmd->retries  = retries;
}

/**
 * \brief initialize message
 */
aw_local aw_inline void aw_sdio_msg_init (awbl_sdio_msg_t  *p_msg)
{
    memset(p_msg, 0, sizeof(awbl_sdio_msg_t));

    AW_INIT_LIST_HEAD(&(p_msg->cmd_list));

    p_msg->status = -ENOTCONN;
}

/**
 * \brief add command
 */
aw_local aw_inline void aw_sdio_cmd_add_tail (awbl_sdio_msg_t *p_msg,
                                              awbl_sdio_cmd_t *p_cmd)
{
    aw_list_add_tail(&p_cmd->cmd_node, &p_msg->cmd_list);
}

/**
 * \brief delete command
 */
aw_local aw_inline void aw_sdio_cmd_del (awbl_sdio_cmd_t *p_cmd)
{
    aw_list_del(&p_cmd->cmd_node);
}


aw_err_t awbl_sdio_host_create (awbl_sdio_host_t *p_host);

void awbl_sdio_slot_change (awbl_sdio_slot_t *slot,
                            uint8_t          cd_state,
                            uint8_t          ro_state);

void awbl_sdio_link_slot (awbl_sdio_host_t  *p_host,
                          awbl_sdio_slot_t  *p_slot,
                          bool_t (*_detect)(awbl_sdio_slot_t *p_slot),
                          uint8_t           *card_buf,
                          uint32_t          buf_size,
                          uint8_t           slot_id);

aw_err_t awbl_sdio_host_reset (awbl_sdio_host_t *p_host);

aw_err_t awbl_sdio_host_dummy_clks (awbl_sdio_host_t *p_host,
                                    uint8_t          clks);

aw_err_t awbl_sdio_host_set_speed (awbl_sdio_host_t *p_host,
                                   uint32_t         speed);

aw_err_t awbl_sdio_host_set_bus_width (awbl_sdio_host_t *p_host,
                                       uint32_t         width);

aw_err_t aw_sdio_app_cmd(awbl_sdio_card_t *p_card,
                         uint32_t         rca);

aw_err_t aw_sdio_go_idle_state (awbl_sdio_card_t *p_card);

aw_err_t aw_sdio_send_if_cond (awbl_sdio_card_t *p_card,
                               uint32_t         ocr);

aw_err_t aw_sdio_send_app_op_cond (awbl_sdio_card_t *p_card,
                                   uint32_t         rca,
                                   uint32_t         ocr,
                                   uint32_t         *rocr);

aw_err_t aw_sdio_spi_read_ocr (awbl_sdio_card_t *p_card,
                               uint8_t          highcap,
                               uint32_t         *ocrp);

aw_err_t aw_sdio_send_cid (awbl_sdio_card_t *p_card,
                           uint32_t         rca,
                           uint32_t         *cid);

aw_err_t aw_sdio_all_send_cid (awbl_sdio_card_t *p_card,
                               uint32_t         *cid);

aw_err_t aw_sdio_send_relative_addr (awbl_sdio_card_t *p_card,
                                     uint32_t         *rca);

aw_err_t aw_sdio_mmc_set_relative_addr (awbl_sdio_card_t *p_card,
                                        uint32_t         rca);

aw_err_t aw_sdio_mmc_send_ext_csd (awbl_sdio_card_t *p_card,
                                   uint32_t         *ext_csd);

aw_err_t aw_sdio_send_csd (awbl_sdio_card_t *p_card,
                           uint32_t         rca,
                           uint32_t         *csd);

aw_err_t aw_sdio_select_card (awbl_sdio_card_t *p_card,
                              uint32_t         rca,
                              uint8_t          select);

aw_err_t aw_sdio_app_send_scr (awbl_sdio_card_t *p_card,
                               uint32_t         rca,
                               uint32_t         *scr);

aw_err_t aw_sdio_app_sd_status (awbl_sdio_card_t *p_card,
                                uint32_t         rca,
                                uint32_t         *ssr);

aw_err_t aw_sdio_sd_switch (awbl_sdio_card_t *p_card,
                            int              mode,
                            int              group,
                            uint8_t          value,
                            uint8_t          *resp);

aw_err_t aw_sdio_spi_set_crc(awbl_sdio_card_t *p_card,
                             uint8_t          crc_en);

aw_err_t aw_sdio_app_set_bus_width (awbl_sdio_card_t *p_card,
                                    uint32_t         rca,
                                    uint8_t          width);

aw_err_t aw_sdio_voltage_witch (awbl_sdio_card_t *p_card);

aw_err_t aw_sdio_send_op_cond (awbl_sdio_card_t *p_card,
                               uint32_t         ocr,
                               uint32_t         *rocr);

aw_err_t aw_sdio_set_blocklen (awbl_sdio_card_t *p_card,
                               uint32_t         blk_len);

aw_err_t aw_sdio_read_single_block (awbl_sdio_card_t *p_card,
                                    uint32_t         sector,
                                    uint8_t          *p_buf,
                                    uint16_t         sector_size);

aw_err_t aw_sdio_write_single_block (awbl_sdio_card_t *p_card,
                                     uint32_t         sector,
                                     uint8_t          *p_buf,
                                     uint16_t         sector_size);

aw_err_t aw_sdio_stop_transmission (awbl_sdio_card_t *p_card);

aw_err_t aw_sdio_send_status (awbl_sdio_card_t *p_card,
                              uint32_t         rca,
                              uint32_t         *status);


aw_err_t aw_sdio_read_multiple_block (awbl_sdio_card_t *p_card,
                                      uint32_t         sector,
                                      uint8_t          *p_buf,
                                      uint32_t         sector_cnt,
                                      uint16_t         sector_size,
                                      uint8_t          stop_en);

aw_err_t aw_sdio_write_multiple_block (awbl_sdio_card_t *p_card,
                                       uint32_t         sector,
                                       uint8_t          *p_buf,
                                       uint32_t         sector_cnt,
                                       uint16_t         sector_size,
                                       uint8_t          stop_en);

aw_err_t aw_sdio_read_single_block_async (awbl_sdio_card_t *p_card,
                                          uint32_t         sector,
                                          uint8_t          *p_buf,
                                          uint16_t         sector_size,
                                          uint32_t         *p_rsp,
                                          void             *p_arg,
                                          void (*complete) (void *p_arg));

aw_err_t aw_sdio_write_single_block_async (awbl_sdio_card_t *p_card,
                                           uint32_t         sector,
                                           uint8_t          *p_buf,
                                           uint16_t         sector_size,
                                           uint32_t         *p_rsp,
                                           void             *p_arg,
                                           void (*complete) (void *p_arg));
#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_SDIOBUS_H_ */
