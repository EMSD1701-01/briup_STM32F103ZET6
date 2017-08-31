/****************************************
* File Name: functions.h
* Date: 2017年8月24日 14点29分
* Author: muxiaozi
* Description: 功能合集实现文件
****************************************/
#include "functions.h"
#include "briupDelay.h"
#include "briupBasePeriph.h"
#include "briupUsart.h"

/**
 * 呼吸灯
 */
void breathLed(void)
{
	u8 pwm = 0, led = 1;
	u32 cnt = 0;
	
	while(1){
		led = led < 7 ? led + 1 : 1;
		while(pwm < 199)
		{
			if(cnt++ % 10 == 0) pwm++;
			setLed(led);
			delay_us(pwm);
			
			setLed(~LED_W);
			delay_us(200 - pwm);
		}
		
		while(pwm > 1)
		{
			if(cnt++ % 30 == 0) pwm--;
			setLed(led);
			delay_us(pwm);
			
			setLed(~LED_W);
			delay_us(200 - pwm);
		}
	}
}

/**
 * 测试基础外设
 * @param block 是否阻塞
 */
void testBasePeriph(u8 block)
{
	do{
		switch(getJoy())
		{
			case JOY_S:
				setRelay(RELAY_ALL);
				setLed(LED_W);
			break;
			
			case JOY_D:
				setRelay(RELAY_1);
				setLed(LED_R);
			break;
			
			case JOY_L:
				setBeep(1);
				setLed(LED_G);
			break;
			
			case JOY_U:
				setRelay(RELAY_2);
				setLed(LED_B);
			break;
			
			case JOY_R:
				setBeep(1);
				setLed(LED_P);
			break;
			
			case JOY_S | JOY_D:
				setLed(LED_Y);
			break;
			
			default:
				setBeep(0);
				setRelay(0);
				setLed(0);
			break;
		}
	}while(block);
}
