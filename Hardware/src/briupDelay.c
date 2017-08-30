/****************************************
* File Name: briupDelay.c
* Date: 2017年8月24日 10点44分
* Author: muxiaozi
* Description: 延时实现文件
****************************************/
#include "briupDelay.h"

//微秒、毫秒计数频率
//每微秒数多少次
static u32 fac_us, fac_ms;

/**
 * 初始化系统时钟的定时器
 *
 * @param SYSCLK 系统时钟频率（MHZ）
 */
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL = 0x0;
	fac_us = SYSCLK / 8;
	fac_ms = fac_us * 1000;
}

/**
 * 按微秒延时
 *
 * @param us 延时时间
 */
void delay_us(u32 us)
{
	u32 temp;	//检测倒计时是否结束
	SysTick->LOAD = fac_us * us;
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x01; //开启定时器
	do{
		temp = SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1<<16)));
	SysTick->CTRL &= ~0x01; //关闭定时器
}

/**
 * 按毫秒延时
 *
 * @param ms 延时时间，不可超过1864ms
 */
void delay_ms(u32 ms)
{
	u32 temp;	//检测倒计时是否结束
	SysTick->LOAD = fac_ms * ms;
	SysTick->VAL = 0;
	SysTick->CTRL |= 0x01; //开启定时器
	do{
		temp = SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1<<16)));
	SysTick->CTRL &= ~0x01; //关闭定时器
}

/**
 * 按秒延时
 *
 * @param s 延时时间
 */
void delay_s(double s)
{
	u32 ms = (u32)(s * 1000);
	do{
		if(ms > 1000)
		{
			delay_ms(1000);
			ms -= 1000;
		}else
		{
			delay_ms(ms);
			ms = 0;
		}
	}while(ms);
}
