/****************************************
* File Name: functions.h
* Date: 2017年8月24日 14点27分
* Author: muxiaozi
* Description: 功能合集
****************************************/
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stm32f10x.h>

/**
 * 呼吸灯
 */
void breathLed(void);

/**
 * 测试基础外设
 * @param block 是否阻塞
 */
void testBasePeriph(u8 block);


#endif //__FUNCTIONS_H__
