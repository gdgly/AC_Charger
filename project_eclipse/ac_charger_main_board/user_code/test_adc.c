/*
 *  Created on: 2015年8月18日
 *      Author: anu
 */

#include "apollo.h"
#include "ametal.h"
#include "aw_gpio.h"
#include "aw_adc.h"


#define N_SAMPLES    10        //定义采样次数为10次
#define CHANNEL      0         //转换通道为通道2

void adc_callback (void *p_arg, int state)
{
	 int num = (int)p_arg;

	 if (state != AW_OK ) {
		 //表征数据转换失败，后续序列会自动取消，如需再次转换，需重新启动
		 //这里属于中断级回调，处理时间应该尽可能短，再此可以使用信号量或消息邮箱
		 //处理转换失败的工作在任务中完成
	 } else {
		 //数据转换成功，接下来处理数据
		 //这里属于中断级回调，处理时间应该尽可能短，再此可以使用信号量或消息邮箱
		 //处理数据的工作在任务中完成
	 }
}


void test_adc(void)
{
#if 1 // 同步
	uint16_t  adc_val[N_SAMPLES]; // 假定采样位数为12位，则数据缓冲区类型为 uint16_t
	aw_err_t  ret;
	int       i;

	/* 设置IO口 */
	aw_gpio_pin_cfg(PIO0_23, PIO0_23_AD0_0 | AW_GPIO_FLOAT);

	while (1) {

		//同步读取，转换结束后返回
		ret = aw_adc_sync_read(CHANNEL, adc_val, N_SAMPLES, FALSE);

		if (ret != AW_OK) {
		   aw_kprintf("转换出错\r\n");
		} else {
		   aw_kprintf("转换完成\r\n");
		   //打印采样值
		   for (i = 0; i < N_SAMPLES; i++) {
		   aw_kprintf("%d ", adc_val[i]);
		   }
		}
	}
#else // 客户端读取

	uint16_t             adc_val1[100];
	uint16_t             adc_val2[100];
	aw_adc_buf_desc_t    desc[2];
	struct aw_adc_client client;

	//制作缓冲区描述符0，回调函数参数为0,0号缓冲区转换完成
	aw_adc_mkbufdesc(&desc[0],adc_val1,100,adc_callback,(void *)0);

	//制作缓冲区描述符1，回调函数参数为1,1号缓冲区转换完成
	aw_adc_mkbufdesc(&desc[1],adc_val2,100,adc_callback,(void *)1);

	aw_adc_client_init(&client, CHANNEL, FALSE);

	//启动客户端，2个缓冲区循环依次填充数据，0参数表示无限循环填充
	//函数立即返回，相应缓冲区数据填充满后调用相应的回调函数
	aw_adc_client_start(&client,desc,2,0);

	while(1) {
	}

#endif

}

