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
 * \brief �¼���־��
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_flag_grp.h
 *
 * \par ��ʾ��
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
 * // ������һ�������£����ö�Ӧ�ı��
 * aw_flag_post(&flag, AW_FLAG_1, AW_FLAG_SET);
 *
 * aw_flag_terminate(&flag);
 *
 * \endcode
 *
 * // �������ݴ���ӡ�����
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
 * \brief �����¼���ṹ��
 */
#define AW_FLAG_DECL(flag_grp)  struct aw_flag_grp flag_grp;

/**
 * \brief �����¼�������ڵ�
 */
#define AW_FLAG_NODE_DECL(flag_grp_node)  struct aw_flag_grp_node flag_grp_node;


/**
 * \brief ͬʱ�ȴ���Ӧ���
 */
#define AW_FLAG_WAIT_AND                1

/**
 * \brief ֻҪ1����ı��
 */
#define AW_FLAG_WAIT_OR                 2

/**
 * \brief ���ö�Ӧ���λ
 */
#define AW_FLAG_SET                     1

/**
 * \brief ��ն�Ӧ���λ
 */
#define AW_FLAG_CLR                     2

/**
 * \brief �����������б��еĽڵ�û��ʹ��
 */
#define AW_NODE_NOUSE                   0

/**
 * \brief �����������б��еĽڵ�����ʹ��
 */
#define AW_NODE_INUSE                   1


struct aw_flag_grp {

    uint32_t flags;                     /**< \brief ͳһ��־���� */

    struct aw_list_head wait_list_head; /**< \brief ���������׵�ַ */

    AW_MUTEX_DECL( mutex );             /**< \brief ���������� */
};

struct aw_flag_grp_node {

    struct aw_list_head list_node;      /**< \brief ���������еĽڵ� */

    uint32_t flags;                     /**< \brief ��ǰ�������ȴ��ı�־λ */

    int wait_type;                      /**< \brief �ȴ���ʽ */

    int state;                          /**< \brief ��ǵ�ǰ����ڵ�״̬�Ƿ�����ʹ�� */

    AW_SEMC_DECL( sem );                /**< \brief �ȴ��ź��� */
};

typedef struct aw_flag_grp aw_flag_grp_t;

typedef struct aw_flag_grp_node aw_flag_node_t;


/**
 * \brief ��ʼ���¼���־�����
 *
 * \param p_flag_grp    �¼���־�����
 * \param flags         ��ʼ�ı��
 *
 * \return ��ʼ�����״̬
 */

aw_err_t aw_flag_init(aw_flag_grp_t *p_flag_grp, uint32_t flags);

/**
 * \brief ��ʼ���¼�����ڵ�
 *
 * \param p_node        �¼���־�����
 * \param flags         ��ʼ�ı��
 * \param wait_type     �ȴ���ʽ��AW_FLAG_WAIT_AND, AW_FLAG_WAIT_OR
 *
 * \return ��ʼ������ڵ�״̬
 */

aw_err_t aw_flag_node_init(aw_flag_node_t *p_node, uint32_t flags, int wait_type);

/**
 * \brief �ȴ�����ڵ��¼�����
 *
 * \param p_flag_grp    �¼���־�����
 * \param p_node        ��Ҫ�ȴ��������
 * \param timeout       �ȴ���ʱʱ��
 *
 * \return ����0����ɹ������򷵻ش�����
 */

aw_err_t aw_flag_pend(aw_flag_grp_t *p_flag_grp, aw_flag_node_t *p_node, int timeout);

/**
 * \brief ���û�����¼����б��
 *
 * \param p_flag_grp    �¼���־�����
 * \param flags         ���õı��
 * \param option        ���÷�ʽ�� AW_FLAG_SET, AW_FLAG_CLR
 *
 * \return ����0����ɹ������򷵻ش�����
 */

aw_err_t aw_flag_post(aw_flag_grp_t *p_flag_grp, uint32_t flags, int option);

/**
 * \brief �����¼���־�����
 *
 * \param p_flag_grp        �¼���־�����
 *
 * \return ����0����ɹ������򷵻ش�����
 */

aw_err_t aw_flag_terminate(aw_flag_grp_t *p_flag_grp);

/**
 * \brief �����¼�����ڵ㣬����Ҫ�ֶ�����
 *
 * \param p_node            �¼�����ڵ�
 *
 * \return ����0����ɹ������򷵻ش�����
 */

aw_err_t aw_flag_node_terminate(aw_flag_node_t *p_node);


#ifdef __cplusplus
}
#endif


#endif /* AW_FLAG_GRP_H_ */
