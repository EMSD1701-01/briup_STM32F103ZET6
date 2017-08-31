/****************************************
* File Name: briupTIM2.h
* Date: 2017年8月31日 16点43分
* Author: muxiaozi
* Description: 定时器2接口文件
****************************************/
#ifndef __TIM2_H__
#define __TIM2_H__

#include <stm32f10x.h>

/**
 * 定时器2的初始化接口
 * @param psc 预分频系数
 */
void TIM2Init(u16 psc);

/**
 * 开始定时器
 * @param arr 
 */
void TIM2Start(u16 arr);

/**
 * 关闭定时器
 */
void TIM2Stop(void);


#endif //__TIM2_H__
