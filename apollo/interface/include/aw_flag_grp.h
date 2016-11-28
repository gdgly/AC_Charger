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
 * \brief 事件标志组
 *
 * 使用本服务需要包含头文件 aw_flag_grp.h
 *
 * \par 简单示例
 * \code
 *
 * #include "apollo.h"
 * #include "aw_flag_grp.h"
 *

 * #define AW_FLAG_1 0x01
 * #define AW_FLAG_2 0x02
 * #define AW_FLAG_3 0x04
 *
 * AW_FLAG_DECL(flag);
 *
 * AW_FLAG_NODE_DECL(flag_node_1);
 *
 * aw_flag_init(&flag, 0x00);
 *
 * aw_flag_node_init(&flag_node_1, AW_FLAG_1, AW_FLAG_WAIT_AND);
 *
 * aw_flag_pend(&flag, &flag_node_1, AW_SEM_WAIT_FOREVER);
 *
 * // 在另外一个任务下，设置对应的标记
 * aw_flag_post(&flag, AW_FLAG_1, AW_FLAG_SET);
 *
 * aw_flag_terminate(&flag);
 *
 * \endcode
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history
 * - 1.00 15-06-02  dav, create file
 * @endinternal
 */

#ifndef AW_FLAG_GRP_H_
#define AW_FLAG_GRP_H_

#include "aw_common.h"
#include "aw_sem.h"
#include "aw_int.h"
#include "aw_list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief 定义事件组结构体
 */
#define AW_FLAG_DECL(flag_grp)  struct aw_flag_grp flag_grp;

/**
 * \brief 定义事件组任务节点
 */
#define AW_FLAG_NODE_DECL(flag_grp_node)  struct aw_flag_grp_node flag_grp_node;


/**
 * \brief 同时等待对应标记
 */
#define AW_FLAG_WAIT_AND                1

/**
 * \brief 只要1个或的标记
 */
#define AW_FLAG_WAIT_OR                 2

/**
 * \brief 设置对应标记位
 */
#define AW_FLAG_SET                     1

/**
 * \brief 清空对应标记位
 */
#define AW_FLAG_CLR                     2

/**
 * \brief 保存在任务列表中的节点没有使用
 */
#define AW_NODE_NOUSE                   0

/**
 * \brief 保存在任务列表中的节点正在使用
 */
#define AW_NODE_INUSE                   1


struct aw_flag_grp {

    uint32_t flags;                     /**< \brief 统一标志组标记 */

    struct aw_list_head wait_list_head; /**< \brief 任务链表首地址 */

    AW_MUTEX_DECL( mutex );             /**< \brief 操作互斥量 */
};

struct aw_flag_grp_node {

    struct aw_list_head list_node;      /**< \brief 任务链表中的节点 */

    uint32_t flags;                     /**< \brief 当前任务正等待的标志位 */

    int wait_type;                      /**< \brief 等待方式 */

    int state;                          /**< \brief 标记当前任务节点状态是否正在使用 */

    AW_SEMC_DECL( sem );                /**< \brief 等待信号量 */
};

typedef struct aw_flag_grp aw_flag_grp_t;

typedef struct aw_flag_grp_node aw_flag_node_t;


/**
 * \brief 初始化事件标志组对象
 *
 * \param p_flag_grp    事件标志组对象
 * \param flags         初始的标记
 *
 * \return 初始化结果状态
 */

aw_err_t aw_flag_init(aw_flag_grp_t *p_flag_grp, uint32_t flags);

/**
 * \brief 初始化事件任务节点
 *
 * \param p_node        事件标志组对象
 * \param flags         初始的标记
 * \param wait_type     等待方式：AW_FLAG_WAIT_AND, AW_FLAG_WAIT_OR
 *
 * \return 初始化任务节点状态
 */

aw_err_t aw_flag_node_init(aw_flag_node_t *p_node, uint32_t flags, int wait_type);

/**
 * \brief 等待任务节点事件触发
 *
 * \param p_flag_grp    事件标志组对象
 * \param p_node        需要等待任务对象
 * \param timeout       等待超时时间
 *
 * \return 返回0代表成功，否则返回错误码
 */

aw_err_t aw_flag_pend(aw_flag_grp_t *p_flag_grp, aw_flag_node_t *p_node, int timeout);

/**
 * \brief 设置或清空事件组中标记
 *
 * \param p_flag_grp    事件标志组对象
 * \param flags         设置的标记
 * \param option        设置方式： AW_FLAG_SET, AW_FLAG_CLR
 *
 * \return 返回0代表成功，否则返回错误码
 */

aw_err_t aw_flag_post(aw_flag_grp_t *p_flag_grp, uint32_t flags, int option);

/**
 * \brief 销毁事件标志组对象
 *
 * \param p_flag_grp        事件标志组对象
 *
 * \return 返回0代表成功，否则返回错误码
 */

aw_err_t aw_flag_terminate(aw_flag_grp_t *p_flag_grp);

/**
 * \brief 销毁事件任务节点，不需要手动调用
 *
 * \param p_node            事件任务节点
 *
 * \return 返回0代表成功，否则返回错误码
 */

aw_err_t aw_flag_node_terminate(aw_flag_node_t *p_node);


#ifdef __cplusplus
}
#endif


#endif /* AW_FLAG_GRP_H_ */
