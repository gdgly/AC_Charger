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
 * \brief ACP1000 ����ȫ������
 *
 * \internal
 * \par modification history:
 * - 1.00 16-04-23  xjc, first implementation
 * \endinternal
 */
#ifndef __AC_CHARGE_PRJ_CFG_H
#define __AC_CHARGE_PRJ_CFG_H

#include "aw_serial.h"

/******************************************************************************
 *  ����汾����
 ******************************************************************************/
#define ACP1000_VERSION_MAJOR  0  /* ���汾�� */
#define ACP1000_VERSION_MINOR  9  /* �ΰ汾�� */
#define ACP1000_VERSION_STRING "LPC1778 : V0.90" /* �汾���ַ�������������20���ֽڣ�*/
/******************************************************************************
 *  EEPROM�洢����(���������ڡ�awbl_hwconf_lpc17xx_eeprom.h��)
 ******************************************************************************/
#define ACP1000_EEPROM_NAME   "lpc17_eeprom"  /* �洢������ */
#define ACP1000_EEPROM_PILE_ID            0   /* ׮IDƫ�� */
#define ACP1000_EEPROM_HUB4G_ADDR         8   /* ��������ַƫ�� */
#define ACP1000_EEPROM_PRICE              9   /* ��۵�ַƫ�� */
#define ACP1000_EEPROM_CHARGE_TOTAL       62  /* �������Ŀ */
#define ACP1000_EEPROM_CHARGE_LAST        63  /* ���һ�γ������Ŀƫ�� */
#define ACP1000_EEPROM_CHARGE_DAT_START   64  /* ���������Ŀ��ʼƫ�� */
#define ACP1000_EEPROM_CHARGE_MAX_NUMS    90  /* �������洢�ĳ����Ŀ�� */
#define ACP1000_EEPROM_CHARGE_SIZE        44  /* ÿ�������Ŀ�ֽ��� */
#define ACP1000_EEPROM_CARD_KEY           8   /* ���濨��Կ�ֽ� */

#define ACP1000_EEPROM_PILE_ID_SET        1   /* ����׮ID���� */
#define ACP1000_EEPROM_PILE_ID_GET        1   /* ����׮ID��ȡ */
#define ACP1000_EEPROM_PRICE_SET          1   /* �۸����� */
#define ACP1000_EEPROM_PRICE_GET          1   /* �۸��ȡ */
#define ACP1000_EEPROM_HUB4G_ADDR_SET     1   /* ������������ַ���� */
#define ACP1000_EEPROM_HUB4G_ADDR_GET     1   /* ������������ַ��ȡ */
#define ACP1000_EEPROM_CHARGE_DAT_SET     1   /* ��������������� */
#define ACP1000_EEPROM_CHARGE_DAT_GET     1   /* ����������ݻ�ȡ */
/******************************************************************************
 *  ��ʱʱ�䶨��
 ******************************************************************************/
#define ACP1000_WAIT_KEY_TIMEOUT 10000   /* ���ȴ��������·�key��ʱ�䣬 ��ʱ����������������Ԥˢ����־���㣨��λms�� */
#define ACP1000_AUTH_TIMEOUT     10000   /* ����Ȩʱ�䣬 ��ʱ��Ϊ��Ȩʧ�� ����λms�� */
#define ACP1000_BILLING_TIMEOUT  10000   /* ����������·�ʱ�䣬 ����ʱ- */
#define ACP1000_SCARM_TIMEOUT    30000   /* ���������쳣��ʱʱ��  */
#define ACP1000_DUGS_ERR_TIMEOUT 10000   /* ��󴮿���ͨ�ų�ʱʱ��  */
#define ACP1000_HUB4G_ERR_TIMEOUT 10000   /* �������ͨ�ų�ʱʱ��  */
/******************************************************************************
 *  ������Դ����
 ******************************************************************************/
#define ACP1000_CARDREADER_COM   COM3 /* ���������� */
#define ACP1000_DBUGS_COM        COM2 /* ���������� */
#define ACP1000_AMMETER_COM      COM1 /* ����� */
#define ACP1000_HUB4G_COM        COM4 /* ���������� */
#define ACP1000_RTC_NUM          1     /* ��ʱ��RTC��� */
#define ACP1000_PILE_MAX_CURR    35000 /* ׮����������� ��λ0.001A*/
/******************************************************************************
 *  ���Ե��Ժ�
 ******************************************************************************/
#define ACP1000_CARD_VALID_DETECT     0  /* �Ƿ��⿨�Ƿ���Ч�� ʹ��  0�� ����(�ǵ���ʱ��1)*/
#define ACP1000_CARD_AMOUNT_ADD       0  /* �Ƿ��µ�һ��ʱ���Զ���ʼ����� �������ã�*/
#define ACP1000_ENERGY_AUTO_ADD       0  /* ���ʱʹ�õ����Ƿ��Զ����ӣ������ã�*/
#define ACP1000_ERR_INFO_PRINT        0  /* �Ƿ��ӡ�쳣��Ϣ */
/******************************************************************************
 *  �쳣��� ����Ӧģ�����ʱ��ģ��Գ��ҵ������û��Ӱ�죩
 ******************************************************************************/

#define ACP1000_AMMETER_ERR_DETECT    1  /* �Ƿ�ʹ�ܵ��ģ���쳣���, 1�� ʹ��  0�� ���� */
#define ACP1000_CURR_ERR_DETECT       1  /* �Ƿ�ʹ�ܵ���ģ���쳣���, 1�� ʹ��  0�� ���� */
#define ACP1000_VOL_ERR_DETECT        1  /* �Ƿ�ʹ�ܵ�ѹģ���쳣���, 1�� ʹ��  0�� ���� */
#define ACP1000_CARD_ERR_DETECT       0  /* �Ƿ�ʹ�ܶ���ģ���쳣���, 1�� ʹ��  0�� ���� */
#define ACP1000_AC1_ERR_DETECT        1  /* �Ƿ�ʹ�ܽ���ĸ�ż��  1�� ʹ��  0�� ����*/
#define ACP1000_LIGHT_ERR_DETECT      1  /* �Ƿ�ʹ�ܷ������쳣���  1�� ʹ��  0�� ����*/
#define ACP1000_TEMP_ERR_DETECT       1  /* �Ƿ�ʹ���¶��쳣���  1�� ʹ��  0�� ����*/
#define ACP1000_DUGS_ERR_DETECT       0  /* �Ƿ�ʹ�ܴ�����ͨ���쳣���  1�� ʹ��  0�� ����*/
#define ACP1000_HUB4G_ERR_DETECT      0  /* �Ƿ�ʹ�ܼ�����ͨ���쳣���  1�� ʹ��  0�� ����*/

#define ACP1000_HUB4G_AUTH            0  /* �Ƿ�����������Ȩ 1�� ʹ��  0�� ����*/
#define ACP1000_HUB4G_BILLING         0  /* �Ƿ񰴼��������� 1�� ʹ��  0�� ����*/
#define ACP1000_OVERTIME_DETECT       0  /* �Ƿ��Ȩ���޲������  1�� ʹ��  0�� ����*/
#define ACP1000_SCRAM_DETECT          1  /* �Ƿ�������ؼ��  1�� ʹ��  0�� ����*/
#define ACP1000_VTP1_DETECT           1  /* �Ƿ�VTP1��ѹ���  1�� ʹ��  0�� ����*/
#define ACP1000_CARD_DETECT           0  /* �Ƿ�ʹ�ܿ�Ƭ��� 1�� ʹ��  0�� ����*/
#define ACP1000_BILING_MONITOR        0  /* �Ʒѵ�Ԫ�Ƿ����Ƴ��  1�� ʹ��  0�� ����  */
#define ACP1000_SKIP_AUTH             1  /* ����߼��Ƿ���Լ�Ȩ��ʵ�ֲ�ǹ����  1�� ʹ��  0�� ����  */
/******************************************************************************
 *  �������
 ******************************************************************************/
#define ACP1000_VOL_TASK                 1  /* �Ƿ�ʹ�ܵ�ѹ�쳣���  1�� ʹ��  0�� ���ܣ����룩*/
#define ACP1000_INLOCK_TASK              0  /* �Ƿ�ʹ��ǹ��λ���  1�� ʹ��  0�� ���ܣ���ѡ��*/
#define ACP1000_LEDLOCK_TASK             1  /* �Ƿ�����LED�����������  ����ѡ��*/
#define ACP1000_HUB4G_TASK               1  /* �Ƿ��������������� ���������룩*/
#define ACP1000_DUGS_TASK                0  /* �Ƿ��������������񣨳��ҵ���ѡ�� */
#define ACP1000_CARD_DETECT_TASK         0  /* �Ƿ�Ƭ������� �����ҵ���ѡ��*/
#define ACP1000_VTP1_DETECT_TASK         1  /* �Ƿ�VTP1��ѹ������񣨱��룩 */
#define ACP1000_CURR_DETECT_TASK         1  /* �Ƿ���������������񣨷�����ѡ�� */
#define ACP1000_PILE_ERR_DETECT_TASK     1  /* �Ƿ�����׮�쳣������񣨷������룩 */
#define ACP1000_BUZZER_TASK              1  /* �Ƿ��������������� ����ѡ��*/
#define ACP1000_PILE_TEMP_TASK           1  /* �Ƿ�����׮�¶ȼ������ ��������ѡ��*/
#define ACP1000_AMMETER_DETECT_TASK      1  /* �Ƿ����ȡ���񣨼Ʒѱ��룩 */
#define ACP1000_BILING_DETECT_TASK       0  /* �Ƿ������Ʒ����񣨳��ҵ����룩 */
#define ACP1000_CHARGE_TASK              1  /* �Ƿ������������  �����룩*/
#define ACP1000_DUBUG_SHELL_TASK         1  /* �Ƿ�ʹ�ܲ��Կ�  �����Կ�ѡ��*/
#endif
