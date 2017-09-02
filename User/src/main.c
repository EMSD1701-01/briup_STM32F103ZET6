/****************************************
* File Name: main.c
* Date: 2017年8月24日 10点20分
* Author: muxiaozi
* Description: 主函数
****************************************/
#include <stm32f10x.h>
#include "briupBasePeriph.h"
#include "briupDelay.h"
#include "briupUsart.h"
#include "briupTIM2.h"
#include "briupNVIC.h"
#include "briupLCD.h"
#include "shape.h"
#include "control.h"

void JoyHandler(u8 type);

int main()
{
	usart1Init(57600);
	basePeriphInit();
	delay_init(72);
	NVICGroupInit(2);
	//TIM2Init(4);
	setJoyInterrupt(JoyHandler);
	briupLcdInit();
	
	changeGameState(STATE_MENU);
	while(1)
	{
		g_gameUpdate[g_gameState]();
	}
}

void JoyHandler(u8 type)
{
	//printf("input %d\n", type);
	g_gameKeyDown[g_gameState](type);
	while(getJoy());
}

