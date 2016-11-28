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
 * \brief ������(touch screen)��׼�ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�:
 * \code
 * #include "aw_touch_screen.h"
 * \endcode
 *
 * \note
 *
 *  (1) �������豸�����Ĵ����������޹�, ��ΪGUI�ṩͨ�õĴ�������, ��ֱ���滻GUI�Ĵ���ϵͳ.
 *
 *      ����, ʹ��Apollo�������豸�滻emwin�Ĵ���ϵͳ
 *
 *      GUI_PID_STATE        th;                // emwinָ�������豸״̬�ṹ��
 *      struct aw_touch_state   ts_state;       // apollo����״̬�ṹ��
 *
 *      AW_FOREVER {
 *
 *          aw_touch_get_log_state(&ts_state);  // ��ȡ�������豸��ǰ�߼�����״̬
 *
 *          th.x = ts_state.x;
 *          th.y = ts_state.y;
 *          th.Pressed = ts_state.pressed;
 *
 *          GUI_TOUCH_StoreStateEx(&th);        // �ѽ���洢��emwin
 *
 *          aw_touch_exec()                     // ���ڶԴ����豸������ѯ
 *          aw_mdelay(10);
 *      }
 *
 *
 *  (2) ��ֱ��ʹ��GUI�Ĵ���ϵͳ, ����ó������豸�ײ�ԭʼ�����ӿ���GUIģ��ԽӼ���
 *
 *      void aw_touch_raw_active_x(void) �� ׼��Y���ѹֵ�Ĳ���
 *      void aw_touch_raw_active_y(void) �� ׼��X���ѹֵ�Ĳ���
 *
 *      void aw_touch_raw_measure_x(int *sample, int count);  - ����X������
 *      void aw_touch_raw_measure_y(int *sample, int count);  - ����Y������
 *
 *
 *  (3) ֱ�ӿ���Touch Screen Controller�ı�׼�ӿ�
 *      aw_touch_lock(bool_t lock)  �� ���������� (TRUE: ����, FALSE: ����)
 *
 *
 * \internal
 * \par modification history
 * - 1.01 14-09-22  chenshuyi, add the implementation of abstract touch device.
 * - 1.00 14-07-25  chenshuyi, first implementation.
 * \endinternal
 */
#ifndef AW_TOUCH_SCREEN_H_
#define AW_TOUCH_SCREEN_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_input_touch
 * \copydoc aw_touch_screen.h
 * @{
 */


#include "apollo.h"
#include "aw_ts_lib.h"


#define AW_TOUCH_SWAP_XY    (1 << 2)


/**
 * \brief ������״̬
 */
struct aw_touch_state {

	uint16_t x, y;        /* x,y ����ֵ */
	uint8_t pressed;      /* �Ƿ���, 1 : ����, 0 : δ���� */

};

typedef void calib_cb_func_t (void *calib_data);

/**
 * \brief ������У׼(ͼ��У׼)
 *
 * \param  algorithm    У׼�㷨
 *         pfunc        �ص�����(�ڴ˻ص�������, ʹ��GUI��ͼ��������У׼����)
 *
 */
int aw_touch_gui_calibrate(int algorithm, calib_cb_func_t *pfunc);

/**
 * \brief ������У׼(ԭʼ�ӿ�)
 *
 * \param  info        У׼����
 *         algorithm   У׼�㷨
 */
int aw_touch_raw_calibrate(void *info, int algorithm);

/**
 * \brief ��������ѯ
 *
 *        �ýӿ���Ҫ���ڵ���, �Դ�����������ѯ.
 */
void aw_touch_exec(void);

/**
 * \brief ���ô��������᷽��
 *
 *        ���������᷽��Ĭ��Ϊ������ʾ
 *
 * \param flags  ��ʾ���
 *
 *        AW_TS_LIB_SWAP_XY : ����������
 */
void aw_touch_set_orientation(int flags);

/**
 * \brief ��ȡ�������߼�״̬
 */
void aw_touch_get_log_state(struct aw_touch_state *pstate);

/**
 * \brief ����������߼�״̬
 */
void aw_touch_flush_log_state(void);

/**
 * \brief ��ȡ����������״̬
 */
void aw_touch_get_phy_state(struct aw_touch_state *pstate);

/**
 * \brief �������������״̬
 */
void aw_touch_flush_phy_state(void);

/**
 * \brief ��ȡ�˲���Ĵ�������ֵ
 *
 *        ���δ���, �Բ���������ݼ������˲�����,
 *        ��󷵻ؾ����˲��Ĳ���ֵ
 *
 * \param orientation : �����᷽��
 */
int aw_touch_get_phys(int orientation);

/**
 * \brief ����������
 *
 * \param lock  true : ����
 *              false: ����
 */
void aw_touch_lock (bool_t lock);

/***********************************************************************************
 *
 *    �������豸�ײ�ԭʼ�����ӿ�
 *
 ***********************************************************************************/

/**
 * \brief ׼��Y�����
 *
 *        (1) ��ͨX�Ĳ�����ѹ, ׼����Y����.
 *        (2) �ж�Y�ĵ�ѹ,���ö�X�Ĳ���.
 */
void aw_touch_raw_active_x (void);

/**
 * \brief ׼��X�����
 *
 *        (1) ��ͨY�Ĳ�����ѹ, ׼����X����.
 *        (2) �ж�X�ĵ�ѹ,���ö�Y�Ĳ���.
 */
void aw_touch_raw_active_y (void);

/**
 * \brief ����X������
 *
 * \param sample : �洢����ֵ
 *        count  : ��������
 */
void aw_touch_raw_measure_x(uint16_t *sample, int count);

/**
 * \brief ����Y������
 *
 * \param sample : �洢����ֵ
 *        count  : ��������
 */
void aw_touch_raw_measure_y(uint16_t *sample, int count);


#ifdef __cplusplus
}
#endif

#endif /* AW_TOUCH_SCREEN_H_ */

/* end of file */
