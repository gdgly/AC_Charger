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
 * \file  list.h
 * \brief the Real Time Kernel
 *
 * \internal
 * \par modification history:
 * - 1.00.14433 2014-11-19 Or2, support task_errno_set/get
 * \endinternal
 */

#ifndef __LIST_H__
#define __LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif
#define __inline__ __inline
#define inline     __inline
/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
struct list_head {
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name)                             \
    struct list_head name = LIST_HEAD_INIT(name)

#ifndef NO_INLINE_FUNCTION

static __inline__ void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static __inline__ void __list_add(struct list_head *elm,
                                  struct list_head *prev,
                                  struct list_head *next)
{
    next->prev = elm;
    elm->next = next;
    elm->prev = prev;
    prev->next = elm;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static __inline__ void list_add(struct list_head *elm, struct list_head *head)
{
    __list_add(elm, head, head->next);
}


/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static __inline__ void list_add_tail(struct list_head *elm, struct list_head *head)
{
    __list_add(elm, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static __inline__ void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static __inline__ void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}

/**
 *  list_del_init
 *  @brief the same as list_del
 */
static inline void list_del_init(struct list_head *entry)
{
	list_del(entry);
	entry->next = entry->prev = entry;
}


/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static __inline__ int list_is_last(const struct list_head *list,
                                   const struct list_head *head)
{
    return list->next == head;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static __inline__ int list_empty(const struct list_head *head)
{
    return head->next == head;
}

#else


#define INIT_LIST_HEAD(list) {\
        (list)->next = (list);                  \
        (list)->prev = (list);                  \
    }

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
void __list_add(struct list_head *new,
                struct list_head *prev,
                struct list_head *next);

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
void list_add(struct list_head *elm, struct list_head *head);


/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
void list_add_tail(struct list_head *elm, struct list_head *head);

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
void list_del(struct list_head *entry);


/**
 *  list_del_init
 *  @brief the same as list_del
 */
void list_del_init(struct list_head *entry);


/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
int list_is_last(const struct list_head *list,
                 const struct list_head *head);


/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
int list_empty(const struct list_head *head);


#endif

#define LIST_FIRST( head )      ((head)->next)
#define LIST_LAST( head )       ((head)->prev)

#define list_for_each(itervar, list)                                    \
	for (itervar = (list)->next; itervar != (list); itervar = itervar->next)

#define list_for_each_safe(itervar, save_var, list)                     \
	for (itervar = (list)->next, save_var = (list)->next->next;         \
         itervar != (list); itervar = save_var, save_var = save_var->next)


#ifndef container_of
#define container_of(p, t, m) \
    ((t *)((int)p - (int)(&(((t *)0)->m))))
#endif

/**
 * list_entry - get the struct for this entry
 * @ptr:    the &struct list_head pointer.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member)   container_of(ptr, type, member)

#ifdef __cplusplus
}
#endif

#endif

