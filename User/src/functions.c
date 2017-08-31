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

//	//select
//	//调用GPIO映射接口
//	ExNVICInit(GPIO_G, 6, 0x3);
//	//设置外部中断线6的优先级和中断源
//	NVICPriorityConfig(3, 1, EXTI9_5_IRQn);
//	
//	//up
//	ExNVICInit(GPIO_G, 11, 0x3);
//	NVICPriorityConfig(1, 1, EXTI15_10_IRQn);

/**
 * select中断服务函数
 */
void EXTI9_5_IRQHandler()
{
	setLed(LED_C);
	delay_ms(1000);
	EXTI->PR |= 1 << 6;
}

/**
 * up中断服务函数
 */
void EXTI15_10_IRQHandler()
{
	setLed(~LED_W);
	delay_ms(1000);
	EXTI->PR |= 1 << 11;
}

