/****************************************
* File Name: briupNVIC.c
* Date: 2017年8月29日 16点57分
* Author: muxiaozi
* Description: 中断控制实现文件
****************************************/
#include "briupNVIC.h"

static __IO u8 NVIC_Group; //分组号

/**
 * NVIC中断分组初始化，只能设置一次
 * @param group STM32中断分组
 */
void NVICGroupInit(u8 group)
{
	//SCB->AIRCR
	//System Control Block 系统控制块/区
	u32 temp = group;
	NVIC_Group = group;
	
	//通过STM32组号获取CM3内核中断分组号
	group = ~group & 0x07;
	
	temp = SCB->AIRCR;
	temp &= 0x0000f8ff; 
	temp |= group << 8;
	temp |= 0x05fa0000;
	
	SCB->AIRCR = temp;
}

/**
 * NVIC外设优先级设置
 * @param preemptionPriority 抢占优先级
 * @param subPriority 次优先级
 * @param channel 中断源
 */
void NVICPriorityConfig(u8 preemptionPriority, u8 subPriority, u8 channel)
{
	//NVIC->IP 寄存器组
	//根据中断分组指定4位有效位的抢占优先级
	u8 temp;
	//有效位数
	u8 tempPtr, tempSub;
	
	tempPtr = 0x04 - NVIC_Group;
	tempSub = 0x0f >> NVIC_Group;
	
	temp = preemptionPriority << tempPtr;
	temp |= subPriority & tempSub;
	temp <<= 4;
	NVIC->IP[channel] = temp;
	NVIC->ISER[channel >> 0x05] |= 1 << (channel & 0x1f);
}

/**
 * GPIO外部中断引脚配置
 * @param GPIOx 端口
 * @param Bitx 位
 * @param TRIM 边沿
 */
void ExNVICInit(u8 GPIOx, u8 Bitx, u8 TRIM)
{
	//计算AFIO->EXTICR寄存器组的位置
	u8 exAddr, exOffset;
	exAddr = Bitx / 4;
	exOffset = (Bitx % 4) * 4;
	
	//开启AFIO时钟
	RCC->APB2ENR |= 0x01;
	//将传入的IO引脚映射到对应EXTI线
	AFIO->EXTICR[exAddr] |= GPIOx <<exOffset;
	
	//开放IO引脚对应外部中断线上的中断屏蔽位
	EXTI->IMR |= 1 << Bitx;
	EXTI->EMR |= 1 << Bitx;
	
	if(TRIM & 0x01)
		EXTI->RTSR |= 1<<Bitx;
	
	if(TRIM & 0x02)
		EXTI->FTSR |= 1<<Bitx;
	
	
}
