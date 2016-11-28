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
 * \brief �����㷨��׼�ӿ�
 *
 * ʹ�ñ��ӿ���Ҫ��������ͷ�ļ���
 * \code
 * #include "aw_ts_lib.h"
 * \endcode
 *
 *     ���ӿ���Դ�����ϵͳ�������Դ, Ϊ�������豸�ṩ���˲�������У׼���㷨��ʵ��
 *
 * \par ��ʾ��
 * \code
 *
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.01 14-10-14  ops, add five point calibration algorithm.
 * - 1.00 14-09-12  ops, first implementation
 * \endinternal
 */

#ifndef AW_TS_LIB_H_
#define AW_TS_LIB_H_

#include "apollo.h"
#include "aw_types.h"

#define AW_TS_LIB_TWO_POINT    0
#define AW_TS_LIB_FIVE_POINT   1

#define AW_TS_LIB_COORD_X    0
#define AW_TS_LIB_COORD_Y    1

typedef struct point {

	long x, y;

}aw_point_t;

typedef struct factor {

	long det;
	long det_x1, det_x2, det_x3;
	long det_y1, det_y2, det_y3;

}aw_factor_t;

typedef struct minmax {

	long min, max;

}aw_minmax_t;

struct two_point_data {

	uint16_t lcd_size;        /* �÷����lcd��Ļ���� */
	uint16_t log_a;           /* a���߼����� */
	uint16_t log_b;           /* b���߼����� */
	uint16_t phy_a;           /* a���������� */
	uint16_t phy_b;           /* b���������� */

};

struct aw_ts_lib_two_point_data {

	struct two_point_data   horizontal;
	struct two_point_data   vertical;

};

struct aw_ts_lib_five_point_data {

	aw_point_t  log[5], phy[5];   //�������߼�ֵ������ֵ
	uint16_t lcd_x_size, lcd_y_size;

};

/**********************************************************************
 *
 *   �˲��㷨
 *
 **********************************************************************/

/** \brief ����ֵ����ֵ�˲�
 *
 *  �㷨ԭ��
 *   (1) ��������NUM��, ����Сֵ��NUM�β�����������(ʹ��ð������, �γɽ�������).
 *   (2) ȡ�м���������, ���ֵ���ڷ�ֵ, ����. ��С�ڷ�ֵ, ��������������ľ�ֵ,
 *       ��Ϊ���β�������Чֵ.
 *
 *  \param   sample      ��������
 *           num         ��������
 *           threshold   ��ֵ
 *
 *  \return  �˲���Ĳ���ֵ
 *
 *  \error  -EDOM  �м����������Ĳ�ֵ���ڷ�ֵ
 */
int aw_ts_lib_filter_median(int *sample, int num, int threshold);


/** \brief �����ڵľ�ֵ�˲�
 *
 *  �㷨ԭ��
 *   (1) ��������NUM��, ����Сֵ��NUM�β�����������(ʹ��ð������, �γɽ�������).
 *   (2) ȡ���ڳߴ�WIN_SIZE������, ���о�ֵ����, ��Ϊ���β�������Чֵ.
 *       (���ڳߴ�ָ���������м�����ɸ�����.)
 *
 *  \param   sample    ��������
 *           num       ��������
 *           win_size  ���ڳߴ�
 *
 *  \return  �˲���Ĳ���ֵ
 *
 *  \error -EINVAL  ���ڳߴ������������, ���ڳߴ�С�ڵ�����
 */
int aw_ts_lib_filter_mean(uint16_t *sample, int num, int win_size);

/**********************************************************************
 *
 *   У׼�㷨
 *
 *   ʹ��Լ�� ���ȵ���У׼�ӿ�, ����ü���ӿ�
 *
 **********************************************************************/

/**
 * \brief ���㴥��У׼
 *
 * \param orientation     У׼����   X�� : AW_TS_LIB_COORD_X, Y�� : AW_TS_LIB_COORD_Y
 *        phy_minmax      �÷����ϵ�������С��A/Dת��ֵ
 *        lcd_size        �÷����ϵ�lcd�ߴ�
 *        log_a           A���ڸ÷����ϵ��߼�ֵ
 *        log_b           B���ڸ÷����ϵ��߼�ֵ
 *        phy_a           A���߼�ֵ��Ӧ��A/Dת��ֵ
 *        phy_b           B���߼�ֵ��Ӧ��A/Dת��ֵ
 *
 * \return AW_OK     У׼���
 *
 * \error  -EINVAL   �Ƿ���У׼����
 */
int aw_ts_lib_two_point_calibrate (int orientation, aw_minmax_t *phy_minmax, int lcd_size, int log_a, int log_b, int phy_a, int phy_b);

/**
 * \brief ����A/Dת��ֵ��������ֵ (���øýӿ�ǰ, ���ȵ�������У׼�ӿ�)
 *
 * \param orientation     У׼����   X�� : AW_TS_LIB_COORD_X, Y�� : AW_TS_LIB_COORD_Y
 *        phy             �ü�����A/Dת��ֵ
 *
 * \return  ���ظ�У׼�����ϵ�����ֵ
 *
 * \error  -EINVAL   �Ƿ���У׼����, û���ȵ��ö�ӦУ׼�ӿ�
 */
int aw_ts_lib_two_point_calculate_coord(int orientation, int phy);


/**
 * \brief ��㴥��У׼
 *
 * \param pdata       У׼����
 *        threshold   ��֤��ֵ
 *                    (���㷨������ɺ�, ������֤, ����ֵ��ԭֵ�Ĳ�ֵ��С����֤��ֵ, �㷨���ж�У׼�ɹ�.)
 *
 * \return AW_OK     У׼���
 *
 * \error  -EDOM     ����ֵ��ԭֵ�Ĳ�ֵ������֤��ֵ
 */
int aw_ts_lib_five_point_calibrate(struct aw_ts_lib_five_point_data *pdata, int threshold);

/**
 * \brief ����A/Dת��ֵ��������ֵ (���øýӿ�ǰ, ���ȵ������У׼�ӿ�)
 *
 * \param  phy_x   �ü������X���ϵ�A/Dת��ֵ
 *         phy_y   �ü������Y���ϵ�A/Dת��ֵ
 *
 * \return log   ���ظõ���߼�ֵ
 *
 * \error  log = (-1, -1)  û���ȵ��ö�ӦУ׼�ӿ�, �����м���, ����(-1, -1)
 */
aw_point_t aw_ts_lib_five_point_calculate_coord(int phy_x, int phy_y);


#endif /* AW_TS_LIB_H_ */
