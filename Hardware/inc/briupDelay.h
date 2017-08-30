/****************************************
* File Name: briupDelay.h
* Date: 2017年8月24日 10点37分
* Author: muxiaozi
* Description: 申明延时的初始化接口
			   及按us/ms/s进行延时的接口
****************************************/
#ifndef __DELAY_H__
#define __DELAY_H__

#include <stm32f10x.h>

/**
 * 初始化系统时钟的定时器
 *
 * @param SYSCLK 系统时钟频率（MHZ）
 */
void delay_init(u8 SYSCLK);

/**
 * 按微秒延时
 *
 * @param us 延时时间
 */
void delay_us(u32 us);

/**
 * 按毫秒延时
 *
 * @param ms 延时时间
 */
void delay_ms(u32 ms);

/**
 * 按秒延时
 *
 * @param s 延时时间
 */
void delay_s(double s);



#endif //__DELAY_H__
