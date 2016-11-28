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
 * \brief Apollo linked-list and queue definitions
 *
 * 使用本模块需要包含以下头文件：
 * \code
 * #include "aw_list.h"
 * \endcode
 *
 * 本文件由 linux 中的 list.h 修改而来，相关用法请参阅linux链表的相关资料。
 *
 * // 更多内容待添加
 *
 * \internal
 * \par modification history:
 * - 1.00 12-10-23  zen, added
 * \endinternal
 */

#ifndef __AW_LIST_H
#define __AW_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_list
 * \copydoc aw_list.h
 * @{
 */


#include "aw_common.h"

/*
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#ifndef AW_LIST_POISON1
#define AW_LIST_POISON1  NULL
#endif

#ifndef AW_LIST_POISON2
#define AW_LIST_POISON2  NULL
#endif

struct aw_list_head {
    struct aw_list_head *next, *prev;
};

struct aw_hlist_head {
    struct aw_hlist_node *first;
};

struct aw_hlist_node {
    struct aw_hlist_node *next, **pprev;
};


/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

#if 0

#define AW_LIST_HEAD_INIT(name) { &(name), &(name) }

#define AW_LIST_HEAD(name) \
    struct aw_list_head name = AW_LIST_HEAD_INIT(name)

#endif

aw_local aw_inline void AW_INIT_LIST_HEAD(struct aw_list_head *list)
{
    list->next = list;
    list->prev = list;
}
#define aw_list_head_init(list) AW_INIT_LIST_HEAD(list)

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
aw_local aw_inline void __aw_list_add(struct aw_list_head *elm,
                                      struct aw_list_head *prev,
                                      struct aw_list_head *next)
{
    next->prev = elm;
    elm->next = next;
    elm->prev = prev;
    prev->next = elm;
}

/**
 * \brief add a new entry
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 *
 * \param elm   new entry to be added
 * \param head  list head to add it after
 */
aw_local aw_inline void aw_list_add(struct aw_list_head *elm,
                                    struct aw_list_head *head)
{
    __aw_list_add(elm, head, head->next);
}


/**
 * \brief add a new entry
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 *
 * \param elm   new entry to be added
 * \param head  list head to add it before
 */
aw_local aw_inline void aw_list_add_tail(struct aw_list_head *elm,
                                         struct aw_list_head *head)
{
    __aw_list_add(elm, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
aw_local aw_inline void __aw_list_del(struct aw_list_head *prev,
                                   struct aw_list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

/**
 * \brief deletes entry from list.
 *
 * \param entry     the element to delete from the list.
 *
 * \attention aw_list_empty() on entry does not return true after this, the entry
 * is in an undefined state.
 */
aw_local aw_inline void __aw_list_del_entry(struct aw_list_head *entry)
{
    __aw_list_del(entry->prev, entry->next);
}

aw_local aw_inline void aw_list_del(struct aw_list_head *entry)
{
    __aw_list_del(entry->prev, entry->next);

    entry->next = AW_LIST_POISON1;
    entry->prev = AW_LIST_POISON2;
}

/**
 * \brief replace old entry by new one
 *
 * If \a old was empty, it will be overwritten.
 *
 * \param old   the element to be replaced
 * \param elm   the new element to insert
 */
aw_local aw_inline void aw_list_replace(struct aw_list_head *old,
                                        struct aw_list_head *elm)
{
    elm->next = old->next;
    elm->next->prev = elm;
    elm->prev = old->prev;
    elm->prev->next = elm;
}

aw_local aw_inline void aw_list_replace_init(struct aw_list_head *old,
                                             struct aw_list_head *elm)
{
    aw_list_replace(old, elm);
    AW_INIT_LIST_HEAD(old);
}

/**
 * \brief deletes entry from list and reinitialize it.
 *
 * \param entry     the element to delete from the list.
 */
aw_local aw_inline void aw_list_del_init(struct aw_list_head *entry)
{
    __aw_list_del_entry(entry);
    AW_INIT_LIST_HEAD(entry);
}

/**
 * \brief delete from one list and add as another's head
 *
 * \param list  the entry to move
 * \param head  the head that will precede our entry
 */
aw_local aw_inline void aw_list_move(struct aw_list_head *list,
                                     struct aw_list_head *head)
{
    __aw_list_del_entry(list);
    aw_list_add(list, head);
}

/**
 * \brief delete from one list and add as another's tail
 *
 * \param list  the entry to move
 * \param head  the head that will follow our entry
 */
aw_local aw_inline void aw_list_move_tail(struct aw_list_head *list,
                                          struct aw_list_head *head)
{
    __aw_list_del_entry(list);
    aw_list_add_tail(list, head);
}

/**
 * \brief tests whether \a list is the last entry in list \a head
 *
 * \param list  the entry to test
 * \param head  the head of the list
 */
aw_local aw_inline int aw_list_is_last(const struct aw_list_head *list,
                                       const struct aw_list_head *head)
{
    return list->next == head;
}

/**
 * \brief tests whether a list is empty
 *
 * \param head  the list to test.
 */
aw_local aw_inline int aw_list_empty(const struct aw_list_head *head)
{
    return head->next == head;
}

/**
 * \brief tests whether a list is empty and not being modified
 *
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * \param head  the list to test
 *
 * \attention using aw_list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is aw_list_del_init(). Eg. it cannot be used
 * if another CPU could re-aw_list_add() it.
 */
aw_local aw_inline int aw_list_empty_careful(const struct aw_list_head *head)
{
    struct aw_list_head *next = head->next;
    return (next == head) && (next == head->prev);
}

/**
 * \brief rotate the list to the left
 *
 * \param head  the head of the list
 */
aw_local aw_inline void aw_list_rotate_left(struct aw_list_head *head)
{
    struct aw_list_head *first;

    if (!aw_list_empty(head)) {
        first = head->next;
        aw_list_move_tail(first, head);
    }
}

/**
 * \brief tests whether a list has just one entry.
 *
 * \param head  the list to test.
 */
aw_local aw_inline int aw_list_is_singular(const struct aw_list_head *head)
{
    return !aw_list_empty(head) && (head->next == head->prev);
}

aw_local aw_inline void __aw_list_cut_position(struct aw_list_head *list,
                                            struct aw_list_head *head,
                                            struct aw_list_head *entry)
{
    struct aw_list_head *elm_first = entry->next;
    list->next = head->next;
    list->next->prev = list;
    list->prev = entry;
    entry->next = list;
    head->next = elm_first;
    elm_first->prev = head;
}

/**
 * \brief cut a list into two
 *
 * This helper moves the initial part of \a head, up to and
 * including \a entry, from \a head to \a list. You should
 * pass on \a entry an element you know is on \a head. \a list
 * should be an empty list or a list you do not care about
 * losing its data.
 *
 * \param list   a new list to add all removed entries
 * \param head   a list with entries
 * \param entry  an entry within head, could be the head itself
 *               and if so we won't cut the list
 */
aw_local aw_inline void aw_list_cut_position(struct aw_list_head *list,
                                             struct aw_list_head *head,
                                             struct aw_list_head *entry)
{
    if (aw_list_empty(head))
        return;
    if (aw_list_is_singular(head) &&
        (head->next != entry && head != entry))
        return;
    if (entry == head)
        AW_INIT_LIST_HEAD(list);
    else
        __aw_list_cut_position(list, head, entry);
}

aw_local aw_inline void __aw_list_splice(const struct aw_list_head *list,
                                      struct aw_list_head       *prev,
                                      struct aw_list_head       *next)
{
    struct aw_list_head *first = list->next;
    struct aw_list_head *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

/**
 * \brief join two lists, this is designed for stacks
 *
 * \param list  the new list to add.
 * \param head  the place to add it in the first list.
 */
aw_local aw_inline void aw_list_splice(const struct aw_list_head *list,
                                       struct aw_list_head       *head)
{
    if (!aw_list_empty(list)) {
        __aw_list_splice(list, head, head->next);
    }
}

/**
 * \brief join two lists, each list being a queue
 *
 * \param list  the new list to add.
 * \param head  the place to add it in the first list.
 */
aw_local aw_inline void aw_list_splice_tail(struct aw_list_head *list,
                                            struct aw_list_head *head)
{
    if (!aw_list_empty(list))
        __aw_list_splice(list, head->prev, head);
}

/**
 * \brief join two lists and reinitialise the emptied list.
 *
 * The list at \a list is reinitialised
 *
 * \param list  the new list to add.
 * \param head  the place to add it in the first list.
 */
aw_local aw_inline void aw_list_splice_init(struct aw_list_head *list,
                                            struct aw_list_head *head)
{
    if (!aw_list_empty(list)) {
        __aw_list_splice(list, head, head->next);
        AW_INIT_LIST_HEAD(list);
    }
}

/**
 * \brief join two lists and reinitialise the emptied list
 *
 * Each of the lists is a queue.
 * The list at \a list is reinitialised
 *
 * \param list  the new list to add.
 * \param head  the place to add it in the first list.
 */
aw_local aw_inline void aw_list_splice_tail_init(struct aw_list_head *list,
                                                 struct aw_list_head *head)
{
    if (!aw_list_empty(list)) {
        __aw_list_splice(list, head->prev, head);
        AW_INIT_LIST_HEAD(list);
    }
}

/**
 * \brief get the struct for this entry
 *
 * \param ptr       the &struct aw_list_head pointer.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * \brief get the first element from a list
 *
 * \param ptr       the list head to take the element from.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 *
 * \attention  that list is expected to be not empty.
 */
#define aw_list_first_entry(ptr, type, member) \
    aw_list_entry((ptr)->next, type, member)

/**
 * \brief iterate over a list
 *
 * \param pos   the &struct aw_list_head to use as a loop cursor.
 * \param head  the head for your list.
 */
#define aw_list_for_each(pos, head) \
    for (pos = (head)->next; \
         prefetch(pos->next), pos != (head); \
         pos = pos->next)

/**
 * \brief iterate over a list
 *
 * This variant differs from aw_list_for_each() in that it's the
 * simplest possible list iteration code, no prefetching is done.
 * Use this for code that knows the list to be very short (empty
 * or 1 entry) most of the time.
 *
 * \param pos   the &struct aw_list_head to use as a loop cursor.
 * \param head  the head for your list.
 */
#define __aw_list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * \brief iterate over a list backwards
 *
 * \param pos   the &struct aw_list_head to use as a loop cursor.
 * \param head  the head for your list.
 */
#define aw_list_for_each_prev(pos, head) \
    for (pos = (head)->prev; prefetch(pos->prev), pos != (head); \
            pos = pos->prev)

/**
 * \brief iterate over a list safe against removal of list entry
 *
 * \param pos   the &struct aw_list_head to use as a loop cursor.
 * \param n     another &struct aw_list_head to use as temporary storage
 * \param head  the head for your list.
 */
#define aw_list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)

/**
 * \brief iterate over a list backwards safe against removal of list entry
 *
 * \param pos   the &struct aw_list_head to use as a loop cursor.
 * \param n     another &struct aw_list_head to use as temporary storage
 * \param head  the head for your list.
 */
#define aw_list_for_each_prev_safe(pos, n, head) \
    for (pos = (head)->prev, n = pos->prev; \
         prefetch(pos->prev), pos != (head); \
         pos = n, n = pos->prev)

/**
 * \brief iterate over list of given type
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry(pos, head, type, member) \
    for (pos = aw_list_entry((head)->next, type, member); \
         prefetch(pos->member.next), &pos->member != (head); \
         pos = aw_list_entry(pos->member.next, type, member))

/**
 * \brief iterate backwards over list of given type.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry_reverse(pos, head, type, member) \
    for (pos = aw_list_entry((head)->prev, type, member); \
         prefetch(pos->member.prev), &pos->member != (head); \
         pos = aw_list_entry(pos->member.prev, type, member))

/**
 * \brief prepare a pos entry for use in aw_list_for_each_entry_continue()
 *
 * Prepares a pos entry for use as a start point in aw_list_for_each_entry_continue().
 *
 * \param pos       the type * to use as a start point
 * \param head      the head of the list
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_prepare_entry(pos, head, type, member) \
    ((pos) ? : aw_list_entry(head, type, member))

/**
 * \brief continue iteration over list of given type
 *
 * Continue to iterate over list of given type, continuing after
 * the current position.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry_continue(pos, head, type, member) \
    for (pos = aw_list_entry(pos->member.next, type, member); \
         prefetch(pos->member.next), &pos->member != (head); \
         pos = aw_list_entry(pos->member.next, type, member))

/**
 * \brief iterate backwards from the given point
 *
 * Start to iterate over list of given type backwards, continuing after
 * the current position.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry_continue_reverse(pos, head, type, member) \
    for (pos = aw_list_entry(pos->member.prev, type, member); \
         prefetch(pos->member.prev), &pos->member != (head); \
         pos = aw_list_entry(pos->member.prev, type, member))

/**
 * \brief iterate over list of given type from the current point
 *
 * Iterate over list of given type, continuing from current position.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry_from(pos, head, type, member) \
    for (; prefetch(pos->member.next), &pos->member != (head); \
         pos = aw_list_entry(pos->member.next, type, member))

/**
 * \brief iterate over list of given type safe against removal of list entry
 *
 * \param pos       the type * to use as a loop cursor.
 * \param n         another type * to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry_safe(pos, n, head, type, member) \
    for (pos = aw_list_entry((head)->next, type, member), \
        n = aw_list_entry(pos->member.next, type, member); \
         &pos->member != (head); \
         pos = n, n = aw_list_entry(n->member.next, type, member))

/**
 * \brief continue list iteration safe against removal
 *
 * Iterate over list of given type, continuing after current point,
 * safe against removal of list entry.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param n         another type * to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry_safe_continue(pos, n, head, type, member) \
    for (pos = aw_list_entry(pos->member.next, type, member), \
        n = aw_list_entry(pos->member.next, type, member); \
         &pos->member != (head); \
         pos = n, n = aw_list_entry(n->member.next, type, member))

/**
 * \brief iterate over list from current point safe against removal
 *
 * Iterate over list of given type from current point, safe against
 * removal of list entry.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param n         another type * to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry_safe_from(pos, n, head, type, member) \
    for (n = aw_list_entry(pos->member.next, type, member); \
         &pos->member != (head); \
         pos = n, n = aw_list_entry(n->member.next, type, member))

/**
 * \brief iterate backwards over list safe against removal
 *
 * Iterate backwards over list of given type, safe against removal
 * of list entry.
 *
 * \param pos       the type * to use as a loop cursor.
 * \param n         another type * to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define aw_list_for_each_entry_safe_reverse(pos, n, head, type, member) \
    for (pos = aw_list_entry((head)->prev, type, member), \
        n = aw_list_entry(pos->member.prev, type, member); \
         &pos->member != (head); \
         pos = n, n = aw_list_entry(n->member.prev, type, member))

/**
 * \brief reset a stale aw_list_for_each_entry_safe loop
 *
 * list_safe_reset_next is not safe to use in general if the list may be
 * modified concurrently (eg. the lock is dropped in the loop body). An
 * exception to this is if the cursor element (pos) is pinned in the list,
 * and list_safe_reset_next is called after re-taking the lock and before
 * completing the current iteration of the loop body.
 *
 * \param pos       the loop cursor used in the aw_list_for_each_entry_safe loop
 * \param n         temporary storage used in aw_list_for_each_entry_safe
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the list_struct within the struct.
 */
#define list_safe_reset_next(pos, n, type, member) \
    n = aw_list_entry(pos->member.next, type, member)

/*
 * Double linked lists with a single pointer list head.
 * Mostly useful for hash tables where the two pointer list head is
 * too wasteful.
 * You lose the ability to access the tail in O(1).
 */

#if 0
#define AW_HLIST_HEAD_INIT { .first = NULL }
#define AW_HLIST_HEAD(name) struct aw_hlist_head name = {  .first = NULL }
#endif

#define AW_INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
aw_local aw_inline void AW_INIT_HLIST_NODE(struct aw_hlist_node *h)
{
    h->next = NULL;
    h->pprev = NULL;
}

aw_local aw_inline int aw_hlist_unhashed(const struct aw_hlist_node *h)
{
    return !h->pprev;
}

aw_local aw_inline int aw_hlist_empty(const struct aw_hlist_head *h)
{
    return !h->first;
}

aw_local aw_inline void __aw_hlist_del(struct aw_hlist_node *n)
{
    struct aw_hlist_node *next = n->next;
    struct aw_hlist_node **pprev = n->pprev;
    *pprev = next;
    if (next)
        next->pprev = pprev;
}

aw_local aw_inline void aw_hlist_del(struct aw_hlist_node *n)
{
    __aw_hlist_del(n);
    n->next = AW_LIST_POISON1;
    n->pprev = AW_LIST_POISON2;
}

aw_local aw_inline void aw_hlist_del_init(struct aw_hlist_node *n)
{
    if (!aw_hlist_unhashed(n)) {
        __aw_hlist_del(n);
        AW_INIT_HLIST_NODE(n);
    }
}

aw_local aw_inline void aw_hlist_add_head(struct aw_hlist_node *n,
                                          struct aw_hlist_head *h)
{
    struct aw_hlist_node *first = h->first;
    n->next = first;
    if (first)
        first->pprev = &n->next;
    h->first = n;
    n->pprev = &h->first;
}

/* next must be != NULL */
aw_local aw_inline void aw_hlist_add_before(struct aw_hlist_node *n,
                                            struct aw_hlist_node *next)
{
    n->pprev = next->pprev;
    n->next = next;
    next->pprev = &n->next;
    *(n->pprev) = n;
}

aw_local aw_inline void aw_hlist_add_after(struct aw_hlist_node *n,
                                           struct aw_hlist_node *next)
{
    next->next = n->next;
    n->next = next;
    next->pprev = &n->next;

    if(next->next)
        next->next->pprev  = &next->next;
}

/* after that we'll appear to be on some hlist and aw_hlist_del will work */
aw_local aw_inline void aw_aw_hlist_add_fake(struct aw_hlist_node *n)
{
    n->pprev = &n->next;
}

/*
 * Move a list from one list head to another. Fixup the pprev
 * reference of the first entry if it exists.
 */
aw_local aw_inline void aw_hlist_move_list(struct aw_hlist_head *old,
                                           struct aw_hlist_head *elm)
{
    elm->first = old->first;
    if (elm->first)
        elm->first->pprev = &elm->first;
    old->first = NULL;
}

#define aw_hlist_entry(ptr, type, member) container_of(ptr,type,member)

#define aw_hlist_for_each(pos, head) \
    for (pos = (head)->first; pos && ({ prefetch(pos->next); 1; }); \
         pos = pos->next)

#define aw_hlist_for_each_safe(pos, n, head) \
    for (pos = (head)->first; pos && ({ n = pos->next; 1; }); \
         pos = n)

/**
 * \brief iterate over list of given type
 *
 * \param tpos      the type * to use as a loop cursor.
 * \param pos       the &struct aw_hlist_node to use as a loop cursor.
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the hlist_node within the struct.
 */
#define aw_hlist_for_each_entry(tpos, pos, head, type, member) \
    for (pos = (head)->first; \
         pos && ({ prefetch(pos->next); 1;}) && \
        ({ tpos = aw_hlist_entry(pos, type), member); 1;}); \
         pos = pos->next)

/**
 * \brief iterate over a hlist continuing after current point
 *
 * \param tpos      the type * to use as a loop cursor.
 * \param pos       the &struct aw_hlist_node to use as a loop cursor.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the hlist_node within the struct.
 */
#define aw_hlist_for_each_entry_continue(tpos, pos, type, member) \
    for (pos = (pos)->next; \
         pos && ({ prefetch(pos->next); 1;}) && \
        ({ tpos = aw_hlist_entry(pos, type, member); 1;}); \
         pos = pos->next)

/**
 * \brief iterate over a hlist continuing from current point
 *
 * \param tpos      the type * to use as a loop cursor.
 * \param pos       the &struct aw_hlist_node to use as a loop cursor.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the hlist_node within the struct.
 */
#define aw_hlist_for_each_entry_from(tpos, pos, type, member) \
    for (; pos && ({ prefetch(pos->next); 1;}) && \
        ({ tpos = aw_hlist_entry(pos, type, member); 1;}); \
         pos = pos->next)

/**
 * \brief iterate over list of given type safe against removal of list entry
 *
 * \param tpos      the type * to use as a loop cursor.
 * \param pos       the &struct aw_hlist_node to use as a loop cursor.
 * \param n         another &struct aw_hlist_node to use as temporary storage
 * \param head      the head for your list.
 * \param type      the type of the struct this is embedded in.
 * \param member    the name of the hlist_node within the struct.
 */
#define aw_hlist_for_each_entry_safe(tpos, pos, n, head, type, member) \
    for (pos = (head)->first; \
         pos && ({ n = pos->next; 1; }) && \
        ({ tpos = aw_hlist_entry(pos, type, member); 1;}); \
         pos = n)

/** @}  grp_aw_if_list */

#ifdef __cplusplus
}
#endif

#endif /* __AW_LIST_H */

/* end of file */
