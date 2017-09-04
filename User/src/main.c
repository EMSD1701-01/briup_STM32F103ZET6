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

//#include "love.h"	//狗粮
//#include "ning.h" //李宁
#include "panda.h"	//熊猫 150 123

void JoyHandler(u8 type);

int main()
{
	u8 y;
	Image_TypeDef imgTest;
	
	usart1Init(57600);
	basePeriphInit();
	delay_init(72);
	
	NVICGroupInit(2);
	TIM2Init(4);
	
	briupLcdInit();
	setJoyInterrupt(JoyHandler);
	
	while(1)
	{
		briupLcdFastDrawLine(0, y-1, 150, y-1, WHITE);
		briupLcdImageInit(&imgTest, 150, 123, 1, y++, (unsigned char *)gImage);
		briupLcdImageDraw(&imgTest, 0);
		//delay_ms(10);
		//breathLed();
	}
}

void JoyHandler(u8 type)
{
	printf("input %d\n", type);
	switch(type)
	{
		case JOY_S:
			setLed(LED_R);
		break;
		
		case JOY_D:
			setLed(LED_G);
		break;
		
		case JOY_L:
			setLed(LED_B);
		break;
		
		case JOY_U:
			setLed(LED_P);
		break;
		
		case JOY_R:
			setLed(LED_C);
		break;
		
		default:
			setLed(LED_W);
		break;
	}
	
	while(getJoy());
}

