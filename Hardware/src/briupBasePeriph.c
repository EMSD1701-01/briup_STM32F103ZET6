/****************************************
* File Name: briupBasePeriph.c
* Date: 2017年8月24日 10点00分
* Author: muxiaozi
* Description: 对基础外设接口的实现文件
****************************************/
#include "briupBasePeriph.h"
#include "briupNVIC.h"
#include "briupDelay.h"

/** 
 * 初始化外设
 */
void basePeriphInit(void)
{
	//配置LED
	RCC->APB2ENR |= 0x1<<4; //PC Pin.0/1/2
	GPIOC->CRL &= ~0xfff;	//重置控制位
	GPIOC->CRL |= 0x333;	//推挽输出
	setLed(~LED_W);
	
	//配置JOY
	RCC->APB2ENR |= 0x1<<4 | 0x1<<8;
	GPIOG->CRL &= ~((u32)0xff<<24);	//PG Pin.6/7
	GPIOG->CRL |= (u32)0x88<<24;
	GPIOG->CRH &= ~((u32)0xf0f<<4);	//PG Pin.9/11
	GPIOG->CRH |= 0x808<<4;
	GPIOG->ODR |= 0x0ac0;		//GPIOG对应端口上拉
	GPIOC->CRL &= ~(0xf<<16);	//PC Pin.4
	GPIOC->CRL |= 0x8<<16;
	GPIOC->ODR |= 0x1<<4;		//GPIOC对应端口上拉
	
	//select
	//调用GPIO映射接口
	ExNVICInit(GPIO_G, 6, 0x3);
	//设置外部中断线6的优先级和中断源
	NVICPriorityConfig(3, 1, EXTI9_5_IRQn);
	
	//up
	ExNVICInit(GPIO_G, 11, 0x3);
	NVICPriorityConfig(1, 1, EXTI15_10_IRQn);
	
	//配置Beep
	RCC->APB2ENR |= 0x1<<8; //GPIOG
	GPIOG->CRH &= ~(0xf<<24); //PG Pin.14
	GPIOG->CRH |= 0x3<<24;
	
	//配置Relay
	RCC->APB2ENR |= 0x1<<4 | 0x1<<8; //GPIOC GPIOG
	GPIOG->CRH &= ~(0xf<<20); //PG Pin.13
	GPIOG->CRH |= 0x3<<20;
	GPIOC->CRL &= ~(0xf<<12); //PC Pin.3
	GPIOC->CRL |= 0x3<<12;
}

/** 
 * LED配置
 *
 * @param led 只使用低3位，分别控制R G B
 */
void setLed(u8 led)
{
	GPIOC->ODR |= 0x7;
	GPIOC->ODR &= ~led;
}

/** 
 * 蜂鸣器配置 
 * 
 * @param open 是否打开蜂鸣器
 */
void setBeep(u8 open)
{
	//PG Pin.14
	if(open) GPIOG->ODR |= 0x1<<14;	
	else GPIOG->ODR &= ~(0x1<<14);
}

/** 
 * 继电器配置
 *
 * @param relay 低2位代表2个继电器，1打开，0关闭 
 * @ref RELAY_1 RELAY_2 RELAY_ALL
 */
void setRelay(u8 relay)
{
	if(relay & 0x01) GPIOG->ODR |= 1<<13;
	else GPIOG->ODR &= ~(1<<13);
	if(relay & 0x02) GPIOC->ODR |= 1<<3;
	else GPIOC->ODR &= ~(1<<3);
}

/**
 * 获取五项按键输入
 *
 * @return 低5位代表5个按键, 
 * @ref JOY_S JOY_U JOY_D JOY_L JOY_R
 * 		也可以组合,比如JOY_S|JOY_U代表中键和上键同时按
 * 		建议使用switch语句对按键进行判断
 */
u8 getJoy(void)
{
	u8 temp = 0x00;
	if(!(GPIOG->IDR & (1<<6))) temp |= 0x1<<0;
	if(!(GPIOG->IDR & (1<<11))) temp |= 0x1<<1;
	if(!(GPIOG->IDR & (1<<7))) temp |= 0x1<<2;
	if(!(GPIOG->IDR & (1<<9))) temp |= 0x1<<3;
	if(!(GPIOC->IDR & (1<<4))) temp |= 0x1<<4;
	return temp;
}

//select中断服务函数
void EXTI9_5_IRQHandler()
{
	setLed(LED_C);
	delay_ms(1000);
	EXTI->PR |= 1 << 6;
}

//up中断服务函数
void EXTI15_10_IRQHandler()
{
	setLed(~LED_W);
	delay_ms(1000);
	EXTI->PR |= 1 << 11;
}
