/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
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
 * \brief ÊÂ¼þÊµÀý
 *
 * \internal
 * \par modification history:
 * - 1.00 16-05-24  xjc, first implementation
 * \endinternal
 */
#include <string.h>
#include "event_node.h"

static void event_manager_foreach( struct event_manager *p_this,
                                   event_t               event,
                                   void                 *p_arg);


void event_node_init( struct event_node *p_this )
{
    memset( p_this, 0x00, sizeof(*p_this));
    AW_MUTEX_INIT(p_this->lock, AW_SEM_Q_PRIORITY );
}


void event_node_lock( struct event_node *p_this )
{
    AW_MUTEX_LOCK(p_this->lock, AW_SEM_WAIT_FOREVER );
}
void event_node_unlock( struct event_node *p_this )
{
    AW_MUTEX_UNLOCK(p_this->lock );
}
void event_node_tell( struct event_node *p_this, event_t event, void *p_arg)
{
    if (p_this->pfunc_event){
        AW_MUTEX_LOCK(p_this->lock, AW_SEM_WAIT_FOREVER );
        p_this->pfunc_event(p_this, event, p_arg);
        AW_MUTEX_UNLOCK(p_this->lock );
    }
}

void event_node_tell_all( struct event_node *p_this, event_t event, void *p_arg)
{
    event_manager_foreach(p_this->parent, event , p_arg);
}


void event_node_destroy( struct event_node *p_this )
{

}

void event_manager_init( struct event_manager *p_this)
{
    p_this->p_event_nodes = 0;
    AW_MUTEX_INIT(p_this->lock, AW_SEM_Q_PRIORITY);
}

void event_manager_add( struct event_manager *p_this, struct event_node *p_newone)
{
    AW_MUTEX_LOCK(p_this->lock, AW_SEM_WAIT_FOREVER);
    p_newone->parent = p_this;
    p_newone->next = p_this->p_event_nodes;
    p_this->p_event_nodes = p_newone;
    AW_MUTEX_UNLOCK(p_this->lock);
}

static void event_manager_foreach( struct event_manager *p_this,
                                   event_t               event,
                                   void                 *p_arg)
{
    struct event_node *p;
    if (!p_this){
        return ;
    }
    p = p_this->p_event_nodes;
    AW_MUTEX_LOCK(p_this->lock, AW_SEM_WAIT_FOREVER);
    while (p) {
        p->pfunc_event(p, event, p_arg);
        p = p->next;
    }
    AW_MUTEX_UNLOCK(p_this->lock);
}


void event_manager_tell_all( struct event_manager *p_this, event_t event, void *p_arg)
{

    event_manager_foreach(p_this, event, p_arg);
}

void event_manager_destroy( struct event_manager *p_this)
{
    AW_MUTEX_TERMINATE(p_this->lock);
    (void)p_this;
}

