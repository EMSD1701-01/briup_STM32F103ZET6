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
#include "briupTIM2.h"
#include <string.h>
#include "briupNVIC.h"

u16 beepFreq[] = {
	17208, 15332, 13657, 12893, 11479, 10227, 9109
};

int main()
{
	int count = 0;
	usart1Init(57600);
	basePeriphInit();
	delay_init(72);
	
	NVICGroupInit(2);
	TIM2Init(4);
	
	while(1)
	{
		TIM2Start(beepFreq[count]);
		delay_ms(100);
		TIM2Stop();
		setBeep(0);
		delay_ms(100);
		count++;
		if(count >= 7)
		{
			count = 0;
		}
	}
}

