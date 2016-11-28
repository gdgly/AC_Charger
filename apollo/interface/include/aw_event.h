/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Event reporting framework.
 *
 * \internal
 * \par modification history:
 * - 1.01 15-01-05 orz, move event configuration to aw_event_cfg.c.
 * - 1.00 14-06-05 orz, first implementation.
 * \endinternal
 */

#ifndef __AW_EVENT_H /* { */
#define __AW_EVENT_H

/**
 * \addtogroup grp_aw_if_event
 * \copydoc aw_event.h
 * @{
 */

#include "aw_types.h"
#include "aw_compiler.h"
#include "aw_msgq.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/

/** \brief event handler flags. this flags are bit masks */
enum event_handler_flags {
    EVENT_HANDLER_FLAG_NONE       = 0, /**< \brief no options needed */
    EVENT_HANDLER_FLAG_AUTO_UNREG = 1  /**< \brief auto unregister after event*/
};

/** \brief event process flags. this flags are bit masks */
enum event_proc_flags {
    EVENT_PROC_FLAG_ASYNC    = 0, /**< \brief Asynchronous (delayed) process */
    EVENT_PROC_FLAG_SYNC     = 1, /**< \brief Synchronous (immediate) process */
    EVENT_PROC_FLAG_CAT_ONLY = 2  /**< \brief process category handlers only */
};

/******************************************************************************/
struct event_type;
struct event_category;

/******************************************************************************/
/**
 * \brief event handler prototype.
 * \param evt_type the event pointor.
 * \param evt_data event private data.
 * \param hdl_data event handler private data.
 */
typedef void event_function_t (struct event_type *evt_type,
                               void              *evt_data,
                               void              *hdl_data);

/******************************************************************************/

/** \brief event handler data */
struct event_handler {
    uint16_t              flags; /**< \brief \sa enum event_handler_flags */
    event_function_t     *func;  /**< \brief handler function */
    void                 *data;  /**< \brief user data pointer */
    struct event_handler *next;  /**< \brief next handler in list */
};

/** \brief event type */
struct event_type {
    struct event_handler  *handler; /**< \brief handler list of the event */
    struct event_category *category;/**< \brief category the event belongs to */
    struct event_type     *next;    /**< \brief next event type in list */
};

/** \brief event category. An event category includes one or more event types */
struct event_category {
    struct event_type    *event;    /**< \brief event type list */
    struct event_handler *handler;  /**< \brief handler of the event category */
};

/******************************************************************************/
/*
 * event message type for delayed event process
 * \note this is a internal structure.
 */
struct event_msg {
    struct event_type *event;
    void              *evt_data;

    /* if the event be processed by category handlers only */
    int                cat_only;
};

/******************************************************************************/

/**
 * \brief event task entry.
 * \note this task is used internal only.
 */
void aw_event_task (void *msgq_id);

/**
 * \brief initialize the event reporting framework lib configuration part.
 * \note this function is implemented in aw_event_cfg.c and was called by
 *       aw_event_lib_init(), so don't call it by yourself.
 */
void aw_event_cfg_init (void);

/** \brief arch function for queuing event message */
aw_err_t aw_event_cfg_msg_send (struct event_msg *msg);

/******************************************************************************/

/** \brief initialize the event reporting framework lib */
void aw_event_lib_init (void);

/******************************************************************************/

/** \brief initialize event category */
void aw_event_category_init (struct event_category *category);

/** \brief register an event handler to an event category */
void aw_event_category_handler_register (struct event_category *category,
                                         struct event_handler  *handler);

/** \brief register an event handler to an event category */
int aw_event_category_handler_unregister (struct event_category *category,
                                          struct event_handler  *handler);

/** \brief register an event type to an event category */
void aw_event_category_event_register (struct event_category *category,
                                       struct event_type     *event);

/******************************************************************************/
/** \brief initialize a handler struct */
aw_static_inline void aw_event_handler_init (struct event_handler *handler,
                                             event_function_t     *func,
                                             void                 *data,
                                             uint16_t              flags)
{
    handler->flags = flags;
    handler->func  = func;
    handler->data  = data;
    handler->next  = NULL;
}

/** \brief register an event handler to an event type */
void aw_event_handler_register (struct event_type     *event,
                                struct event_handler  *handler);

/** \brief unregister an event handler from an event type */
int aw_event_handler_unregister (struct event_type     *event,
                                 struct event_handler  *handler);

/******************************************************************************/

/** \brief initialize event type */
void aw_event_init (struct event_type *event);

/**
 * \brief raise an event.
 *
 * this function will directly call all the handlers that are registered for
 * this event category and this event type.
 *
 * @note this routine should not be called from exception or interrupt handler.
 *
 * @param event     event to raise.
 * @param evt_data  pointer to event data.
 * @param proc_type event process flags, \sa enum event_proc_flags.
 */
int aw_event_raise (struct event_type *event, void *evt_data, int proc_type);


#ifdef __cplusplus
}
#endif

/** @} grp_aw_if_event */

#endif /* } __AW_EVENT_H */

/* end of file */
