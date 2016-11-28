/*
 *  Created on: 2015��8��18��
 *      Author: anu
 */

#include "apollo.h"
#include "ametal.h"
#include "aw_gpio.h"
#include "aw_adc.h"


#define N_SAMPLES    10        //�����������Ϊ10��
#define CHANNEL      0         //ת��ͨ��Ϊͨ��2

void adc_callback (void *p_arg, int state)
{
	 int num = (int)p_arg;

	 if (state != AW_OK ) {
		 //��������ת��ʧ�ܣ��������л��Զ�ȡ���������ٴ�ת��������������
		 //���������жϼ��ص�������ʱ��Ӧ�þ����̣ܶ��ٴ˿���ʹ���ź�������Ϣ����
		 //����ת��ʧ�ܵĹ��������������
	 } else {
		 //����ת���ɹ�����������������
		 //���������жϼ��ص�������ʱ��Ӧ�þ����̣ܶ��ٴ˿���ʹ���ź�������Ϣ����
		 //�������ݵĹ��������������
	 }
}


void test_adc(void)
{
#if 1 // ͬ��
	uint16_t  adc_val[N_SAMPLES]; // �ٶ�����λ��Ϊ12λ�������ݻ���������Ϊ uint16_t
	aw_err_t  ret;
	int       i;

	/* ����IO�� */
	aw_gpio_pin_cfg(PIO0_23, PIO0_23_AD0_0 | AW_GPIO_FLOAT);

	while (1) {

		//ͬ����ȡ��ת�������󷵻�
		ret = aw_adc_sync_read(CHANNEL, adc_val, N_SAMPLES, FALSE);

		if (ret != AW_OK) {
		   aw_kprintf("ת������\r\n");
		} else {
		   aw_kprintf("ת�����\r\n");
		   //��ӡ����ֵ
		   for (i = 0; i < N_SAMPLES; i++) {
		   aw_kprintf("%d ", adc_val[i]);
		   }
		}
	}
#else // �ͻ��˶�ȡ

	uint16_t             adc_val1[100];
	uint16_t             adc_val2[100];
	aw_adc_buf_desc_t    desc[2];
	struct aw_adc_client client;

	//����������������0���ص���������Ϊ0,0�Ż�����ת�����
	aw_adc_mkbufdesc(&desc[0],adc_val1,100,adc_callback,(void *)0);

	//����������������1���ص���������Ϊ1,1�Ż�����ת�����
	aw_adc_mkbufdesc(&desc[1],adc_val2,100,adc_callback,(void *)1);

	aw_adc_client_init(&client, CHANNEL, FALSE);

	//�����ͻ��ˣ�2��������ѭ������������ݣ�0������ʾ����ѭ�����
	//�����������أ���Ӧ����������������������Ӧ�Ļص�����
	aw_adc_client_start(&client,desc,2,0);

	while(1) {
	}

#endif

}

