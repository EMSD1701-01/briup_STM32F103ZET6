/****************************************
* File Name: briupNVIC.h
* Date: 2017年8月29日 16点48分
* Author: muxiaozi
* Description: 中断控制接口
****************************************/
#ifndef __NVIC_H__
#define __NVIC_H__

#include <stm32f10x.h>

typedef enum{
	GPIO_A,
	GPIO_B,
	GPIO_C,
	GPIO_D,
	GPIO_E,
	GPIO_F,
	GPIO_G,
}GPIO_x;

/**
 * NVIC中断分组初始化，只能设置一次
 * @param group 分组
 */
void NVICGroupInit(u8 group);

/**
 * NVIC外设优先级设置
 * @param preemptionPriority
 * @param subPriority
 * @param channel
 */
void NVICPriorityConfig(u8 preemptionPriority, u8 subPriority, u8 channel);

/**
 * GPIO外部中断引脚配置
 * @param GPIOx 端口
 * @param Bitx 位
 * @param TRIM 边沿
 */
void ExNVICInit(u8 GPIOx, u8 Bitx, u8 TRIM);

#endif //__NVIC_H__
