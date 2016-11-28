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
 * \brief ������ϵͳͨ�ñ�׼�ӿ�
 *
 *    ͨ������ӿڰ�����ꡢ���̡�ҡ�ˡ������豸��
 *
 *    �����豸ͨ���ᷢ�����������¼�, ����, ��귢����������¼��������¼�, ���̷��������¼�,
 *    �������������������¼�. ��������ϵͳ���������¼����ĸ�������豸����, ��������Ͷ���¼�.
 *
 *    ������ϵͳ��ʹ������ѭ"˭����˭����"��ԭ��, �û�ע��ص�������ϵͳ, �ڻص�������, ����
 *    ��ǿ��ת��Ϊ�����ĵ��������ͼ���.
 *
 * \par ʹ��˵��
 * \code
 *
 * (1) ʹ���ϱ��¼���׼�ӿ�ǰ, ����ȷ��������������ϵͳ(aw_prj_params.h)
 *
 * ......
 *
 * #define AW_COM_AWBL_INPUT_EV             // Input Service�¼�����
 * #define AW_COM_AWBL_INPUT_EV_KEY         // Input Service�����¼�
 * #define AW_COM_AWBL_INPUT_EV_ABS         // Input Service�����¼�
 *
 * ......
 *
 * (2) ��ʼ���¼���, �Լ���Apolloƽ̨ע��������ϵͳ(aw_prj_config.c)
 * static void aw_prj_task_level_init( void )
 * {
 * ......
 *
 *   aw_event_lib_init();           // event lib initialization
 *
 * #ifdef AW_COM_AWBL_INPUT_EV
 *   awbl_input_ev_mgr_register();
 * #endif
 *
 * ......
 * }
 *
 * (3) �����⴦ʹ��������ϵͳ��׼�ӿ�ǰ�����Ȱ���aw_input.hͷ�ļ�
 *
 * \endcode
 *
 * \par ��ʾ��
 * \code
 *
 * #include "aw_input.h"
 *
 * (1) �������⴦�����ϱ��ӿ�, �ϱ�����
 *
 * aw_input_report_key(EV_KEY, KEY_1, 1);
 *
 * (2) ʹ�ûص������ϱ�����
 *
 * void key_proc0_cb (void *p_input_data, void *p_usr_data)
 * {
 *     struct aw_input_event *p_input_ev = (struct aw_input_event *)p_input_data;
 *
 *	   if (p_input_ev->ev_type != EV_KEY) {
 *
 *	       return;
 *	   }
 *
 *	   struct aw_input_key_data *key_data = (struct aw_input_key_data *)p_input_data;
 *
 *	   switch (key_data->key_code) {
 *
 *	   case KEY_1 : if (key_data->key_state) {
 *
 *	                    AW_INFOF(("key_proc0_cb : KEY1 is down : %d. \n", key_data->key_state));
 *                  }
 *                  else {
 *
 *               	    AW_INFOF(("key_proc0_cb : KEY1 is up : %d. \n", key_data->key_state));
 *                  }
 *  	            break;
 *     }
 * }
 *
 * void my_func (void *p_arg)
 * {
 *     aw_local struct aw_input_handler input_hdlr;
 *
 *	   aw_input_handler_register(&input_hdlr, key_proc0_cb, NULL);
 * }
 *
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.01 15-01-07  ops, encapsulate aw_input_handler and redefine how to register/unregister.
 * - 1.00 14-07-18  ops, first implementation.
 * \endinternal
 */

#ifndef __AW_INPUT_H
#define __AW_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_input
 * \copydoc aw_input.h
 * @{
 */

#include "aw_input_code.h"
#include "aw_types.h"
#include "aw_event.h"

struct aw_input_pos {

	int x, y, z;
};

struct aw_input_event {

	int ev_type;                        /* �¼������� */
};

/** \brief �������� */
struct aw_input_key_data {

	struct aw_input_event input_ev;     /* �¼����� */
	int                   key_code;     /* ���������� */
	int                   key_state;    /* ����״̬, DOWN : 0, UP : ��0*/
};

/** \brief ָ�������豸���� */
struct aw_input_ptr_data {

	struct aw_input_event input_ev;     /* �¼����� */
	int                   ptr_code;     /* ָ�������豸������ */
	struct aw_input_pos   pos;          /* ����ֵ */
};

union aw_input_data {

	struct aw_input_key_data key_data;
	struct aw_input_ptr_data ptr_data;

};

/**
 * \brief ������ϵͳ���ݽ��ջص���������.
 *
 * \param p_input_data   ��������.
 * \param p_usr_data     �û�����.
 */
typedef void input_cb_func_t (void *p_input_data, void *p_usr_data);

/**
 * \brief ������ϵͳ���.
 */
struct aw_input_handler {

	struct event_handler ev_handler;
	input_cb_func_t      *p_cb_func;
	void                 *p_usr_data;
};

/***********************************************************************************
 *
 *    ������ϵͳ     -  �����ϱ��ӿ�
 *
 ***********************************************************************************/

/**
 * \brief �ϱ�һ�������¼���������ϵͳ
 *
 * \param ev_type     �¼�������
 * \param code        ������
 * \param is_pressed  ����״̬
 *
 * \return  AW_OK   �ϱ��ɹ�
 *        -ENODEV   δע����¼�
 */
int aw_input_report_key (int ev_type, int code, int is_pressed);

/**
 * \brief �ϱ�һ�������¼���������ϵͳ
 *
 * \param ev_type     �¼�������
 * \param code        ������  (ABS_COORD : ��������, REL_COORD : �������)
 * \param coord_x     X����
 * \param coord_y     Y����
 * \param coord_z     Z����
 *
 * \return  AW_OK   �ϱ��ɹ�
 *        -ENODEV   δע����¼�
 */
int aw_input_report_coord (int ev_type, int code, int coord_x, int coord_y, int coord_z);


/***********************************************************************************
 *
 *     ������ϵͳ     -  ע��/ע���ӿ�
 *
 ***********************************************************************************/

/**
 * \brief ע��һ����������������ϵͳ
 *
 * \param p_input_handler    ��ע���������ϵͳ���.
 * \param p_cb_func          ���ݽ��ջص�����.
 * \param p_usr_data         �û��Զ�������, ����, ��ΪNULL.
 *
 * \return  AW_OK      �ɹ�ע��.
 *          -EINVAL    ��p_input_handler��p_cb_funcΪNULLʱ, ע��ʧ��.
 */
aw_err_t aw_input_handler_register (struct aw_input_handler  *p_input_handler,
		                            input_cb_func_t          *p_cb_func,
		                            void                     *p_usr_data);

/**
 * \brief ��������ϵͳ��ע��ָ����������
 *
 * \param p_input_handler    ��ע����������ϵͳ���.
 *
 * \return  AW_OK      �ɹ�ע��.
 *          -EINVAL    ��p_input_handlerΪNULLʱ, ע��ʧ��.
 */
aw_err_t aw_input_handler_unregister (struct aw_input_handler *p_input_handler);


/** @} grp_aw_if_input */

#ifdef __cplusplus
}
#endif

#endif /* __AW_INPUT_H */

/* end of file */
