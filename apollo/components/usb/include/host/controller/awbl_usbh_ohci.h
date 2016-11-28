/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief USB OHCI controller support head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-09-16  deo, first implementation
 * \endinternal
 */


#ifndef __AWBL_USBH_OHCI_H
#define __AWBL_USBH_OHCI_H

#include "apollo.h"
#include "aw_timer.h"
#include "aw_sem.h"
#include "aw_task.h"
#include "aw_list.h"
#include "aw_spinlock.h"
#include "aw_job_queue.h"
#include "host/awbl_usbhbus.h"

#define AWBL_USBH_TO_OHCI_INFO(p_hc) \
    ((struct awbl_usbh_ohci_info *)AWBL_DEVINFO_GET(&((p_hc)->super.super)))

#define AWBL_USBH_OHCI_DECL(p_ohci, p_hc) \
    struct awbl_usbh_ohci *p_ohci = \
        (struct awbl_usbh_ohci *)AW_CONTAINER_OF(p_hc, struct awbl_usbh_ohci, hc)

#define AWBL_USBH_OHCI_INFO_DECL(p_info, p_hc) \
    struct awbl_usbh_ohci_info *p_info = AWBL_USBH_TO_OHCI_INFO(p_hc)

//#define _TD_MODE_0_


struct awbl_usbh_ohci_otrp {
    struct awbl_usbh_trp *p_trp;
    int                  td_cnt;
};

/* transfer descriptor,
 * must be aligned to a 16-byte boundary. */
struct awbl_usbh_ohci_td {
    uint32_t                    hwinfo;
#define __OHCI_TD_CC            0xf0000000              /* condition code */
    #define __OHCI_TD_CC_NOERROR      0x00
    #define __OHCI_TD_CC_CRC          0x01
    #define __OHCI_TD_CC_BITSTUFFING  0x02
    #define __OHCI_TD_CC_DATATOGGLEM  0x03
    #define __OHCI_TD_CC_STALL        0x04
    #define __OHCI_TD_DEVNOTRESP      0x05
    #define __OHCI_TD_PIDCHECKFAIL    0x06
    #define __OHCI_TD_UNEXPECTEDPID   0x07
    #define __OHCI_TD_DATAOVERRUN     0x08
    #define __OHCI_TD_DATAUNDERRUN    0x09
    #define __OHCI_TD_BUFFEROVERRUN   0x0C
    #define __OHCI_TD_BUFFERUNDERRUN  0x0D
    #define __OHCI_TD_NOTACCESSED     0x0F
#define __OHCI_TD_CC_GET(info)  ((info >>28) & 0x0f)
#define __OHCI_TD_EC            0x0C000000              /* error count */
#define __OHCI_TD_T             0x03000000              /* data toggle state */
    #define __OHCI_TD_T_DATA0   0x02000000              /* DATA0 */
    #define __OHCI_TD_T_DATA1   0x03000000              /* DATA1 */
    #define __OHCI_TD_T_TOGGLE  0x00000000              /* uses ED_C */
#define __OHCI_TD_DI            0x00E00000              /* frames before interrupt */
#define __OHCI_TD_DI_SET(x)     (((x) & 0x07)<< 21)
#define __OHCI_TD_DP            0x00180000              /* direction/pid */
#define __OHCI_TD_DP_SETUP      0x00000000              /* SETUP pid */
#define __OHCI_TD_DP_IN         0x00100000              /* IN pid */
#define __OHCI_TD_DP_OUT        0x00080000              /* OUT pid */
#define __OHCI_TD_R             0x00040000              /* round: short packets OK? */
    uint32_t                    hwcbp;
    uint32_t                    hwnexttd;
    uint32_t                    hwbe;
    void                        *addr_dma;
    struct awbl_usbh_ohci_otrp  *p_otrp;
    size_t                      len;
    struct aw_list_head         node;

#ifdef _TD_MODE_0_
    bool_t                      in_done_list;
#endif
}__attribute__ ((aligned (16)));

/* EndPoint descriptor,
 * must be aligned to a 16-byte boundary. */
struct awbl_usbh_ohci_ed {
    uint32_t                    hwinfo;
    /* info bits defined by the hardware */
#define __OHCI_ED_ISO      (1u << 15)
#define __OHCI_ED_SKIP     (1u << 14)
#define __OHCI_ED_LOWSPEED (1u << 13)
#define __OHCI_ED_OUT      (0x01u << 11)
#define __OHCI_ED_IN       (0x02u << 11)
    uint32_t                    hwtailp;
    uint32_t                    hwheadp;
#define __OHCI_ED_C        (0x02)          /* toggle carry */
#define __OHCI_ED_H        (0x01)          /* halted */
    uint32_t                    hwnexted;

    void                        *addr_dma;
    struct aw_list_head         node;
    struct aw_list_head         td_list;  /* TD list */
    struct awbl_usbh_ohci       *p_ohci;
    struct awbl_usbh_endpoint   *p_ep;
    struct awbl_usbh_ohci_td    *dummy_td;
    uint16_t                    frame_no;

    uint8_t                     phase;
    uint16_t                    interval;

    uint8_t                     state;
#define __OHCI_ED_ST_IDLE            0
#define __OHCI_ED_ST_LINKED          1
#define __OHCI_ED_ST_UNLINKING       2

    aw_semb_id_t                unlink_sem;
}__attribute__ ((aligned (16)));



/*
 * The HCCA (Host Controller Communications Area)
 * is a 256 byte structure, must be 256-byte aligned.
 */
struct awbl_usbh_ohci_hcca {
#define __MAX_INT_NUM 32
    uint32_t  int_table [__MAX_INT_NUM];   /* periodic schedule */
    uint16_t  frame_no;                     /* current frame number */
    uint16_t  pad;
    uint32_t  done_head;                    /* info returned for an interrupt */
    uint8_t   reserved[116];
    uint8_t   aligned[4];                   /* spec only identifies 252 bytes :) */
}__attribute__ ((aligned (256)));


/* USB host controller OHCI */
struct awbl_usbh_ohci {
    struct awbl_usbh            hc;
    aw_spinlock_isr_t           lock;
    AW_MUTEX_DECL(mutex);

    uint8_t                     nposts;
    struct awbl_usbh_ohci_hcca  *hcca;
    uint32_t                    reg_base;

    /* root hub */
    struct awbl_usbh_hub_desc   root_hub_desc;
    uint16_t                    cbitmap;            /* root hub发回上层中断传输的数据 */
    struct awbl_usbh_trp        *p_rh_int_trp;      /* 等待root hub中断传输的TRP */

    /* 处理OHCI日常事务 */
    struct aw_job_queue         *p_qjob;
    AW_TASK_DECL(ohci_task, AWBL_USBH_OHCI_TASK_STACK_SIZE);
    aw_timer_t                  guarder;
    aw_qjob_t                   guarder_job;
    aw_qjob_t                   irq_job;

    /* ED list */
    struct aw_list_head         ctrl_list;
    struct aw_list_head         bulk_list;
    struct aw_list_head         remove_list;

    /* periodic bandwidth */
    int                         bandwidth[__MAX_INT_NUM];
    int                         periodic_req;
};

/* OHCI controller information */
struct awbl_usbh_ohci_info {
    struct awbl_usbh_info   hc_info;
    uint32_t                task_prio;
};


aw_err_t awbl_usbh_ohci_init (struct awbl_usbh   *p_hc,
                              uint32_t           reg_base);

void awbl_usbh_ohci_irq (void *p_arg);

aw_err_t  awbl_usbh_ohci_reset (struct awbl_usbh *p_hc);

aw_err_t awbl_usbh_ohci_ep_enable (struct awbl_usbh          *p_hc,
                                   struct awbl_usbh_endpoint *p_ep);

aw_err_t awbl_usbh_ohci_ep_disable (struct awbl_usbh          *p_hc,
                                    struct awbl_usbh_endpoint *p_ep);

aw_err_t awbl_usbh_ohci_ep_reset (struct awbl_usbh          *p_hc,
                                  struct awbl_usbh_endpoint *p_ep);

aw_err_t awbl_usbh_ohci_transfer_request (struct awbl_usbh     *p_hc,
                                          struct awbl_usbh_trp *p_trp);

aw_err_t awbl_usbh_ohci_transfer_cancel (struct awbl_usbh     *p_hc,
                                         struct awbl_usbh_trp *p_trp);

aw_err_t awbl_usbh_ohci_rh_req(struct awbl_usbh     *p_hc,
                               struct awbl_usbh_trp *p_trp);

aw_err_t awbl_usbh_ohci_rh_cancel(struct awbl_usbh     *p_hc,
                                  struct awbl_usbh_trp *p_trp);

#endif /* __AWBL_USBH_OHCI_H */
