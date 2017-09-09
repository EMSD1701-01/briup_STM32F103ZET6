/**
 * 初始化场景
 * 主要用于各种外设的初始化，以及把它们的初始化过程打印到LCD屏幕上
 */
#ifndef __BALLSTART_H__
#define __BALLSTART_H__

#include <stm32f10x.h>

/**
 * 进入场景时执行一次
 */
void onEnterStart(void);

/**
 * 当有按键操作时执行
 * @param type 按键类型 JOY_S JOY_U JOY_D JOY_L JOY_R
 */
void onKeyDownStart(u8 type);

/**
 * 每隔16ms以中断方式执行一次，帧率60FPS
 */
void onUpdateStart(void);

/**
 * 传感器事件
 */
void onSensorStart(short x, short y, short z);


#endif //__BALLSTART_H__
