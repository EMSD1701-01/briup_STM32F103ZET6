/**
 * 游戏场景
 */
#ifndef __BALLGAME_H__
#define __BALLGAME_H__

#include <stm32f10x.h>

/**
 * 进入场景时执行一次
 */
void onEnterGame(void);

/**
 * 当有按键操作时执行
 * @param type 按键类型 JOY_S JOY_U JOY_D JOY_L JOY_R
 */
void onKeyDownGame(u8 type);

/**
 * 每隔16ms以中断方式执行一次，帧率60FPS
 */
void onUpdateGame(void);

/**
 * 传感器事件
 */
void onSensorGame(short x, short y, short z);


#endif //__BALLGAME_H__
