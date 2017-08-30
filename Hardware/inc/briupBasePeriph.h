/****************************************
* File Name: briupBasePeriph.h
* Date: 2017年8月24日 09点42分
* Author: muxiaozi
* Description: 基础外设接口
****************************************/
#ifndef __BASEPERIPH_H__
#define __BASEPERIPH_H__

#include <stm32f10x.h>

//颜色
#define LED_R	0x4	//PC2
#define LED_G	0x2	//PC1
#define LED_B	0x1	//PC0
#define LED_Y	(LED_R | LED_G)
#define LED_P	(LED_R | LED_B)
#define LED_C	(LED_B | LED_G)
#define LED_W	(LED_R | LED_G | LED_B)

//按键
#define JOY_S 0x01 //PG6
#define JOY_U 0x02 //PG11
#define JOY_D 0x04 //PG7
#define JOY_L 0x08 //PG9
#define JOY_R 0x10 //PC4

//继电器
#define RELAY_1	0x1	//继电器1
#define RELAY_2 0x2 //继电器2
#define RELAY_ALL (RELAY_1 | RELAY_2) //两个继电器

/** 
 * 初始化外设
 */
void basePeriphInit(void);

/** 
 * LED配置
 *
 * @param led 只使用低3位，分别控制R G B
 */
void setLed(u8 led);

/** 
 * 蜂鸣器配置 
 *
 * @param open 是否打开蜂鸣器
 */
void setBeep(u8 open);

/** 
 * 继电器配置
 *
 * @param relay 低2位代表2个继电器，1打开，0关闭 
 * @ref RELAY_1 RELAY_2 RELAY_ALL
 */
void setRelay(u8 relay);

/**
 * 获取五项按键输入
 *
 * @return 低5位代表5个按键, 
 * @ref JOY_S JOY_U JOY_D JOY_L JOY_R
 * 		也可以组合,比如JOY_S|JOY_U代表中键和上键同时按
 * 		建议使用switch语句对按键进行判断
 */
u8 getJoy(void);



#endif  //__BASEPERIPH_H__



