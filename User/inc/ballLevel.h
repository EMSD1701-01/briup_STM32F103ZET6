/**
 * 等级选择场景接口文件
 */
#ifndef __BALLLEVEL_H__
#define __BALLLEVEL_H__

#include <stm32f10x.h>

/**
 * 进入场景时执行一次
 */
void onEnterLevel(void);

/**
 * 当有按键操作时执行
 * @param type 按键类型 JOY_S JOY_U JOY_D JOY_L JOY_R
 */
void onKeyDownLevel(u8 type);

/**
 * 每隔16ms以中断方式执行一次，帧率60FPS
 */
void onUpdateLevel(void);

/**
 * 传感器事件
 */
void onSensorLevel(short x, short y, short z);

/**
 * 获取当前关卡等级
 * @return 当前关卡等级
 */
u8 getLevel(void);

/**
 * 选择关卡
 * @param level 设置的关卡等级
 * @param needDraw 是否需要绘制
 */
void setLevel(u8 level, u8 needDraw);

#endif //__BALLLEVEL_H__
