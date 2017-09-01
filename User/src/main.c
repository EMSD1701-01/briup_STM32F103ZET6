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
#include "briupLCD.h"

void JoyHandler(u8 type);

u16 beepFreq[] = {
	17208, 15332, 13657, 12893, 11479, 10227, 9109
};

int main()
{
	usart1Init(57600);
	basePeriphInit();
	delay_init(72);
	
	NVICGroupInit(2);
	TIM2Init(4);
	
	briupLcdDisplayOn();
	briupLcdInit();
	briupLcdFastDrawCircle(240, 240, 10, 2, 0);
	setJoyInterrupt(JoyHandler);
	
	while(1)
	{
		breathLed();
	}
}

void JoyHandler(u8 type)
{
	printf("input %d\n", type);
	switch(type)
	{
		case JOY_S:
			TIM2Start(beepFreq[0]);
			setLed(LED_R);
		break;
		
		case JOY_D:
			TIM2Start(beepFreq[1]);
			setLed(LED_G);
		break;
		
		case JOY_L:
			TIM2Start(beepFreq[2]);
			setLed(LED_B);
		break;
		
		case JOY_U:
			TIM2Start(beepFreq[3]);
			setLed(LED_P);
		break;
		
		case JOY_R:
			TIM2Start(beepFreq[4]);
			setLed(LED_C);
		break;
		
		default:
			setLed(LED_W);
		break;
	}
	
	while(getJoy());
	TIM2Stop();
	setBeep(0);
}

