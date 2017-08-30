/****************************************
* File Name: main.c
* Date: 2017年8月24日 10点20分
* Author: muxiaozi
* Description: 主函数
****************************************/
#include <stm32f10x.h>
#include "briupBasePeriph.h"
#include "briupDelay.h"
#include "functions.h"
#include "briupNVIC.h"
#include "briupUsart.h"
#include <string.h>

int main()
{
	u8 process = 0;
	NVICGroupInit(2);
	usart1Init(57600);
	printf("USART1 完成...\t[%d]\n", process++);
	printf("BasePeriphInit Init...\t[%d]\n", process++);
	basePeriphInit();
	printf("BasePeriphInit Done...\t[%d]\n", process++);
	printf("Delay Init...\t[%d]\n", process++);
	delay_init(72);
	printf("Delay Done...\t[%d]\n", process++);
	printf("NVIC Init...\t[%d]\n", process++);
	NVIC_SetPriorityGrouping(2);
	printf("NVIC Done...\t[%d]\n", process++);
	
	while(1)
	{
		//printf("Hello!MyNameIs %10s\n", "muxiaozi");
		setLed(LED_B);
		delay_s(1);
		setLed(~LED_W);
		delay_s(1);
	}
}


