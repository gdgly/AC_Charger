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
 * \brief USB EHCI controller support head file
 *
 * \internal
 * \par modification history:
 * - 1.00 15-04-04  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_USBH_EHCI_H
#define __AWBL_USBH_EHCI_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "apollo.h"
#include "aw_timer.h"
#include "aw_pool.h"
#include "aw_sem.h"
#include "aw_task.h"
#include "aw_msgq.h"
#include "aw_list.h"
#include "aw_job_queue.h"
#include "host/awbl_usbhbus.h"


/** \brief EHCI controller capability register */
struct __ehci_cap_regs {
    uint32_t    caplength_hciver;
    uint32_t    hcsparams;
#define HCS_PI(p)           ((p)&(1 << 16))
#define HCS_PPC(p)          ((p)&(1 << 4))      /* true: port power control */
#define HCS_N_PORTS(p)      (((p)>>0)&0xf)      /* bits 3:0, ports on HC */
    uint32_t    hccparams;
/* EHCI 1.1 addendum */
#define HCC_32FRAME_PERIODIC_LIST(p)    ((p)&(1 << 19))
#define HCC_PER_PORT_CHANGE_EVENT(p)    ((p)&(1 << 18))
#define HCC_LPM(p)                      ((p)&(1 << 17))
#define HCC_HW_PREFETCH(p)              ((p)&(1 << 16))

#define HCC_EXT_CAPS(p)             (((p)>>8)&0xff) /* for pci extended caps */
#define HCC_ISOC_CACHE(p)           ((p)&(1 << 7))  /* true: can cache isoc frame */
#define HCC_ISOC_THRES(p)           (((p)>>4)&0x7)  /* bits 6:4, uframes cached */
#define HCC_CANPARK(p)              ((p)&(1 << 2))  /* true: can park on async qh */
#define HCC_PGM_FRAME_LIST_FLAG(p)  ((p)&(1 << 1))  /* true: periodic_size changes*/
#define HCC_64BIT_ADDR(p)           ((p)&(1))       /* true: can use 64-bit addr */

    uint32_t    hcsp_portroute;
};

/** \brief EHCI operational capability register */
struct __ehci_host_regs {
    uint32_t    usbcmd;                     /* Command register */
#define CMD_PPCEE       (1<<15)             /* per port change event enable */
#define CMD_PARK        (1<<11)             /* enable "park" on async qh */
#define CMD_PARK_CNT(c) (((c)>>8)&3)        /* how many transfers to park for */
#define CMD_LRESET      (1<<7)              /* partial reset (no ports, etc) */
#define CMD_IAAD        (1<<6)              /* "doorbell" interrupt async advance */
#define CMD_ASE         (1<<5)              /* async schedule enable */
#define CMD_PSE         (1<<4)              /* periodic schedule enable */
    #define CMD_FLS_1024    (0x00000000)    /* 000 */
    #define CMD_FLS_512     (0x00000004)    /* 001 */
    #define CMD_FLS_256     (0x00000008)    /* 010 */
    #define CMD_FLS_128     (0x0000000C)    /* 011 */
    #define CMD_FLS_64      (0x00008000)    /* 100 */
    #define CMD_FLS_32      (0x00008004)    /* 101 */
    #define CMD_FLS_16      (0x00008008)    /* 110 */
    #define CMD_FLS_8       (0x0000800C)    /* 111 */
#define CMD_RESET       (1<<1)              /* reset HC not bus */
#define CMD_RUN         (1<<0)              /* start/stop HC */
    uint32_t    usbsts;                     /* Status register */
#define STS_ASS     (1<<15)                 /* Async Schedule Status */
#define STS_PSS     (1<<14)                 /* Periodic Schedule Status */
#define STS_RECL    (1<<13)                 /* Reclamation */
#define STS_HALT    (1<<12)                 /* Not running (any reason) */
#define STS_IAA     (1<<5)                  /* Interrupted on async advance */
#define STS_FATAL   (1<<4)                  /* such as some PCI access errors */
#define STS_FLR     (1<<3)                  /* frame list rolled over */
#define STS_PCD     (1<<2)                  /* port change detect */
#define STS_ERR     (1<<1)                  /* "error" completion (overflow, ...) */
#define STS_INT     (1<<0)                  /* "normal" completion (short, ...) */
    uint32_t    usbintr;                    /* Interrupt enable */
    uint32_t    frindex;                    /* Frame index */
    uint32_t    ctrldssegment;              /* 4G segment selector */
    uint32_t    periodiclistbase;           /* Periodic schedule list */
    uint32_t    asynclistaddr;              /* Current Asynch schedule list */
    uint32_t    asyncttsts;                 /* Async buffer in embedded TT control */
    uint32_t    reserved[8];
    uint32_t    configflag;                 /* Configured Flag register */
    uint32_t    portsc[9];                  /* Port Status/Control x, x = 1..8 */
#define PORT_OWNER      (1<<13)     /* true: companion hc owns this port */
#define PORT_POWER      (1<<12)     /* true: has power (see PPC) */
#define PORT_LS         (3<<10)
#define PORT_USB11(x)   (((x) & (3 << 10)) == (1 << 10))    /* USB 1.1 device */
#define PORT_RESET      (1<<8)      /* reset port */
#define PORT_SUSPEND    (1<<7)      /* suspend port */
#define PORT_RESUME     (1<<6)      /* resume it */
#define PORT_OCC        (1<<5)      /* Over-current Change */
#define PORT_OC         (1<<4)      /* Over-current */
#define PORT_PEC        (1<<3)      /* port enable change */
#define PORT_PE         (1<<2)      /* port enable */
#define PORT_CSC        (1<<1)      /* connect status change */
#define PORT_CONNECT    (1<<0)      /* device connected */
    uint32_t    usbmode;
#define USBMODE_SDIS    (1<<3)      /* Stream disable */
#define USBMODE_BE      (1<<2)      /* BE/LE endianness select */
#define USBMODE_CM_HC   (3<<0)      /* host controller mode */
#define USBMODE_CM_IDLE (0<<0)      /* idle state */
};

/** \brief EHCI controller */
struct awbl_usbh_ehci {
    struct awbl_usbh          hc;
    aw_spinlock_isr_t         lock;

    struct __ehci_cap_regs    *cap_regs;
    struct __ehci_host_regs   *opt_regs;

    uint16_t                  vesion;
    uint32_t                  hcs_params;
    /* port change detect bits support by EHCI V1.1 */
    bool_t                    ppcd_support;
    uint32_t                  int_dis_cnt;

    /* periodic */
    uint32_t            *periodic_addr;
    uint32_t            frame_list_size;
    uint8_t             bandwidth[AWBL_USBH_EHCI_BANDWIDTH_SIZE];
    int                 random_frame;
    struct aw_list_head intr_qh_list;


    /* asynchronous */
    struct awbl_usbh_ehci_qh    *async;

    /* root hub */
    struct awbl_usbh_hub_desc   root_hub_desc;
    uint32_t                    root_hub_status;
    /* store port status,
     * 30,31bit are soft virtual,
     * for reset and suspend */
    uint32_t                    port_status[15];
    /* store root hub data for interrupt TRP */
    uint16_t                    cbitmap;
    /* interrupt TRP */
    struct awbl_usbh_trp        *p_rh_int_trp;

    struct aw_job_queue         *p_qjob;
    AW_TASK_DECL(ehci_task, AWBL_USBH_EHCI_TASK_STACK_SIZE);
    aw_timer_t                  guarder;
    aw_qjob_t                   guarder_job;
    aw_qjob_t                   irq_job;

#define __EHCI_IRQ_JOB_PRIO      3
#define __EHCI_GUARD_JOB_PRIO    2
#define __EHCI_USER_JOB_PRIO     1

#define __EHCI_USER_EN_EP        0x01
#define __EHCI_USER_DIS_EP       0x02
#define __EHCI_USER_REQ_TRP      0x04
#define __EHCI_USER_CANCEL_TRP   0x08

};

/** \brief EHCI controller information */
struct awbl_usbh_ehci_info {
    struct awbl_usbh_info hc_info;
    uint32_t              ehci_task_prio;
};

/* element common defines */
#define Q_TYPE_ITD  (0 << 1)
#define Q_TYPE_QH   (1 << 1)
#define Q_TYPE_SITD (2 << 1)
#define Q_TYPE_FSTN (3 << 1)

/** \brief EHCI QTD */
struct awbl_usbh_ehci_qtd {
    /* for HC */
    uint32_t                hw_next;
    uint32_t                hw_alt_next;
    uint32_t                hw_token;
#define QTD_TOGGLE      (1u << 31)  /* data toggle */
#define QTD_LENGTH(tok) (((tok)>>16) & 0x7fffu)
#define QTD_IOC         (1u << 15)  /* interrupt on complete */
#define QTD_CERR(tok)   (((tok)>>10) & 0x3u)
#define QTD_PID(tok)    (((tok)>>8) & 0x3u)
#define QTD_STS_ACTIVE  (1u << 7)   /* HC may execute this */
#define QTD_STS_HALT    (1u << 6)   /* halted on error */
#define QTD_STS_DBE     (1u << 5)   /* data buffer error (in HC) */
#define QTD_STS_BABBLE  (1u << 4)   /* device was babbling (qtd halted) */
#define QTD_STS_XACT    (1u << 3)   /* device gave illegal response */
#define QTD_STS_MMF     (1u << 2)   /* incomplete split transaction */
#define QTD_STS_STS     (1u << 1)   /* split transaction state */
#define QTD_STS_PING    (1u << 0)   /* issue PING? */

#define QTD_PID_OUT     0
#define QTD_PID_IN      1
#define QTD_PID_SETUP   2

#define ACTIVE_BIT(ehci)        cpu_to_hc32(ehci, QTD_STS_ACTIVE)
#define HALT_BIT(ehci)          cpu_to_hc32(ehci, QTD_STS_HALT)
#define STATUS_BIT(ehci)        cpu_to_hc32(ehci, QTD_STS_STS)
#define IS_SHORT_READ(token)    (QTD_LENGTH(token) != 0 && QTD_PID(token) == QTD_PID_IN)

    uint32_t                hw_buf [5];
    uint32_t                hw_buf_hi [5];

    /* for HCD */
    void                    *addr_dma;      /* DMA address of this QTD */
    struct aw_list_head     node;           /* next QTD */
    struct awbl_usbh_trp    *p_trp;         /* TRP */
    size_t                  len;            /* data length */
} __attribute__ ((aligned (32)));


union __ehci_ptr {
    struct awbl_usbh_ehci_qh    *qh;        /* Q_TYPE_QH */
    struct awbl_usbh_ehci_itd   *itd;       /* Q_TYPE_ITD */
    struct awbl_usbh_ehci_sitd  *sitd;      /* Q_TYPE_SITD */
    struct awbl_usbh_ehci_fstn  *fstn;      /* Q_TYPE_FSTN */
    void                        *ptr;
};

/** \brief EHCI QH */
struct awbl_usbh_ehci_qh {
    /* for HC */
    uint32_t                    hw_next;
    uint32_t                    hw_info1;
#define QH_CONTROL_EP   (1 << 27)   /* FS/LS control endpoint */
#define QH_HEAD         (1 << 15)   /* Head of async reclamation list */
#define QH_TOGGLE_CTL   (1 << 14)   /* Data toggle control */
#define QH_HIGH_SPEED   (2 << 12)   /* Endpoint speed */
#define QH_LOW_SPEED    (1 << 12)
#define QH_FULL_SPEED   (0 << 12)
#define QH_INACTIVATE   (1 << 7)    /* Inactivate on next transaction */
    uint32_t                    hw_info2;
#define QH_SMASK    0x000000ff
#define QH_CMASK    0x0000ff00
#define QH_HUBADDR  0x007f0000
#define QH_HUBPORT  0x3f800000
#define QH_MULT     0xc0000000
    uint32_t                    hw_cur_qtd;
    uint32_t                    hw_next_qtd;
    uint32_t                    hw_alt_next_qtd;
    uint32_t                    hw_token;
    uint32_t                    hw_buf [5];
    uint32_t                    hw_buf_hi [5];

    /* for HCD */
    void                        *addr_dma;      /* DMA address of this QH */
    union __ehci_ptr            p_next;         /* next QH or others*/
    struct aw_list_head         qtd_list;       /* QTDs on this QH */
    struct awbl_usbh_ehci_qtd   *dummy_qtd;     /* dummy */
    struct awbl_usbh_ehci       *p_ehci;        /* controller */
    uint8_t                     state;          /* state */
#define QH_ST_IDLE              0
#define QH_ST_LINKED            1
#define QH_ST_UNLINKED          2
    uint8_t                     retry;          /* XactErr retry count */
#define QH_RETRY_MAX        32                  /* XactErr max retry */
    bool_t                      need_unlink;
    /* for interrupt transfer */
    uint16_t                    f_phase;        /* frame index */
    uint8_t                     u_phase;        /* uframe index */
    uint16_t                    f_period;       /* frame period */
    struct aw_list_head         intr_node;
    struct awbl_usbh_endpoint   *p_ep;

} __attribute__ ((aligned(32)));

/** \brief EHCI ITD */
struct awbl_usbh_ehci_itd {
    /* first part defined by EHCI spec */
    uint32_t            hw_next;                /* see EHCI 3.3.1 */
    uint32_t            hw_transaction [8];     /* see EHCI 3.3.2 */
#define EHCI_ISOC_ACTIVE        (1<<31)        /* activate transfer this slot */
#define EHCI_ISOC_BUF_ERR       (1<<30)        /* Data buffer error */
#define EHCI_ISOC_BABBLE        (1<<29)        /* babble detected */
#define EHCI_ISOC_XACTERR       (1<<28)        /* XactErr - transaction error */
#define EHCI_ITD_LENGTH(tok)    (((tok)>>16) & 0x0fff)
#define EHCI_ITD_IOC        (1 << 15)   /* interrupt on complete */

#define ITD_ACTIVE(ehci)    cpu_to_hc32(ehci, EHCI_ISOC_ACTIVE)

    uint32_t            hw_bufp [7];    /* see EHCI 3.3.3 */
    uint32_t            hw_bufp_hi [7]; /* Appendix B */

    /* the rest is HCD-private */
    void*               addr_dma;       /* for this itd */
    union __ehci_ptr    p_next;         /* ptr to periodic q entry */

    struct aw_list_head itd_list;       /* list of stream's itds */

} __attribute__ ((aligned (32)));

/** \brief EHCI SITD */
struct awbl_usbh_ehci_sitd {
    /* first part defined by EHCI spec */
    uint32_t            hw_next;
/* uses bit field macros above - see EHCI 0.95 Table 3-8 */
    uint32_t            hw_fullspeed_ep;    /* EHCI table 3-9 */
    uint32_t            hw_uframe;      /* EHCI table 3-10 */
    uint32_t            hw_results;     /* EHCI table 3-11 */
#define SITD_IOC    (1 << 31)   /* interrupt on completion */
#define SITD_PAGE   (1 << 30)   /* buffer 0/1 */
#define SITD_LENGTH(x)  (0x3ff & ((x)>>16))
#define SITD_STS_ACTIVE (1 << 7)    /* HC may execute this */
#define SITD_STS_ERR    (1 << 6)    /* error from TT */
#define SITD_STS_DBE    (1 << 5)    /* data buffer error (in HC) */
#define SITD_STS_BABBLE (1 << 4)    /* device was babbling */
#define SITD_STS_XACT   (1 << 3)    /* illegal IN response */
#define SITD_STS_MMF    (1 << 2)    /* incomplete split transaction */
#define SITD_STS_STS    (1 << 1)    /* split transaction state */

#define SITD_ACTIVE(ehci)   cpu_to_hc32(ehci, SITD_STS_ACTIVE)

    uint32_t            hw_buf [2];         /* EHCI table 3-12 */
    uint32_t            hw_backpointer;     /* EHCI table 3-13 */
    uint32_t            hw_buf_hi [2];      /* Appendix B */

    /* the rest is HCD-private */
    void*               addr_dma;
    union __ehci_ptr    p_next;     /* ptr to periodic q entry */
    struct aw_list_head sitd_list;  /* list of stream's sitds */

} __attribute__ ((aligned (32)));

/** \brief EHCI FSTN */
struct awbl_usbh_ehci_fstn {
    uint32_t            hw_next;
    union __ehci_ptr    p_next;
};

/****************************************************************************/
aw_err_t awbl_usbh_ehci_init(struct awbl_usbh *p_hc,
                             uint32_t         reg_base);

/****************************************************************************/
void awbl_usbh_ehci_irq (void *p_arg);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_ep_enable (struct awbl_usbh          *p_hc,
                                   struct awbl_usbh_endpoint *p_ep);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_ep_disable (struct awbl_usbh          *p_hc,
                                    struct awbl_usbh_endpoint *p_ep);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_ep_reset (struct awbl_usbh          *p_hc,
                                  struct awbl_usbh_endpoint *p_ep);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_transfer_request (struct awbl_usbh     *p_hc,
                                          struct awbl_usbh_trp *p_trp);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_transfer_cancel (struct awbl_usbh     *p_hc,
                                         struct awbl_usbh_trp *p_trp);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_rh_req(struct awbl_usbh     *p_hc,
                               struct awbl_usbh_trp *p_trp);

/****************************************************************************/
aw_err_t awbl_usbh_ehci_rh_cancel(struct awbl_usbh     *p_hc,
                                  struct awbl_usbh_trp *p_trp);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */


#endif /* __AWBL_USBH_EHCI_H */
