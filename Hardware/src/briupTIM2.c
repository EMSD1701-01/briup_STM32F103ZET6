/****************************************
* File Name: briupTIM2.c
* Date: 2017年8月31日 16点45分
* Author: muxiaozi
* Description: 定时器2实现文件
****************************************/
#include "briupTIM2.h"

#include "briupUsart.h"
#include "briupBasePeriph.h"
#include "briupDelay.h"
#include "briupNVIC.h"

/**
 * 定时器2的初始化接口
 * @param psc 预分频系数
 */
void TIM2Init(u16 psc)
{
	//使能TIM2
	RCC->APB1ENR |= 0x01;
	
	//设置预分频系数
	TIM2->PSC = psc - 1;
	
	//向下计数
	TIM2->CR1 |= 0x01<<4;
	
	//允许更新中断
	TIM2->DIER |= 0x01;
	
	//注册定时器2中断向量
	NVICPriorityConfig(1, 1, TIM2_IRQn);
}

/**
 * 开始定时器
 * @param arr 
 */
void TIM2Start(u16 arr)
{
	TIM2->ARR = arr;
	TIM2->CR1 |= 0x01;
}

/**
 * 关闭定时器
 */
void TIM2Stop(void)
{
	TIM2->CR1 &= ~0x01;
}

/**
 * 定时器中断服务程序
 */
static __IO u8 BeepFlag = 1;
void TIM2_IRQHandler()
{
	setBeep(BeepFlag);
	BeepFlag = !BeepFlag;
	TIM2->SR &= ~0x01;
}
