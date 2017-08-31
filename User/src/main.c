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
#include "briupUsart.h"
#include <string.h>

int main()
{
	//usart1Init(57600);

	basePeriphInit();

	//delay_init(72);

	NVIC_EnableIRQ(SysTick_IRQn);
	
	while(1)
	{
		setLed(LED_W);
	}
}

void SysTick_Handler(void)
{

	setLed(LED_R);
}


