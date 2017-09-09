/**
 * 帮助场景接口文件
 */
#ifndef __BALLHELP_H__
#define __BALLHELP_H__

#include <stm32f10x.h>

/**
 * 进入场景时执行一次
 */
void onEnterHelp(void);

/**
 * 当有按键操作时执行
 * @param type 按键类型 JOY_S JOY_U JOY_D JOY_L JOY_R
 */
void onKeyDownHelp(u8 type);

/**
 * 每隔16ms以中断方式执行一次，帧率60FPS
 */
void onUpdateHelp(void);

/**
 * 传感器事件
 */
void onSensorHelp(short x, short y, short z);

#endif //__BALLHELP_H__
