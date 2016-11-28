/**
 * \file aw_task2.h
 *
 * \brief aw_task2ÊµÏÖ£¬(OO)
 *
 * \internal
 * \par modification history:
 * - 151120, dcf, first implementation.
 * \endinternal
 */

#ifndef __aw_task2_H
#define __aw_task2_H

#include "apollo.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "aw_vdebug.h"
#include "aw_isr_defer.h"


/*
 * aw_task2
 */
struct aw_task2;
typedef struct aw_task2 *aw_task2_id_t;

/*
 * if pfunc valid call pfunc with arg.
 */
struct aw_task2_cleaner;
typedef struct aw_task2_cleaner *aw_task2_cleaner_id_t;

struct aw_task2_cleaner
{
    struct aw_task2_cleaner *next;

    uint32_t is_this_dynamic;/* if set, this obj will auto free */
    void (*pfunc)( void *arg );
    void *arg;
    void *reserved;
};

/*
 * static default.
 */
void aw_task2_cleaner_init( struct aw_task2_cleaner *p_cleaner );

#define aw_task2_cleaner_set_dynamic( p_cleaner, is_dynamic ) do{ p_cleaner->is_this_dynamic = is_dynamic;}while (0)

void aw_task2_cleaner_destroy( struct aw_task2_cleaner *p_cleaner );



aw_task2_id_t aw_task2_create(	const char *name,
										int stack_size, int priority,
										void *(*pfun)(void*),
										void *arg
										);

/*
 * don't use this function
 */
aw_task_id_t aw_task2_to_task_id( aw_task2_id_t task2id );
void aw_task2_startup( aw_task2_id_t p_this);


/*
 * add only one cleaner( next point force to NULL )
 */
void aw_task2_add_cleaner( aw_task2_id_t task2id, aw_task2_cleaner_id_t p_new_cleaner );


/*
 * set joinable true or false
 */
void aw_task2_joinable_set( aw_task2_id_t task2id, int joinable_true_or_false );

/*
 * get joinable true or false
 */
int aw_task2_joinable_get( aw_task2_id_t task2id );

/*
 * join aw_task2
 *
 * return value is void *, task return value.
 */
int aw_task2_join( aw_task2_id_t task2id, void **pp_ret );

/*
 * detach aw_task2
 *
 * return value is void *, task return value.
 */
int aw_task2_detach( aw_task2_id_t task2id );

/*
 * dynamic allocate cleanner
 */
aw_err_t aw_task2_add_clean_method( aw_task2_id_t task2id, void (*pfunc)(void*), void *arg );

struct aw_task2 * aw_task2_self( void );

aw_err_t aw_task2_exit( void *ret );

void *aw_task2_set_lts( aw_task2_id_t task2id, void *newlts );

void *aw_task2_get_lts( aw_task2_id_t task2id );


#endif /* #ifndef __aw_task2_H */

/* end of file */
