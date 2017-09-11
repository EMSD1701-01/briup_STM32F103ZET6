/**
 * 初始化场景
 * 主要用于各种外设的初始化，以及把它们的初始化过程打印到LCD屏幕上
 */
#include "ballStart.h"
#include "ballCore.h"

#include "briupTIM2.h"
#include "briupNVIC.h"
#include "briupMPU6050.h"
#include "briupUsart.h"
#include "IC24C04.h"

/**
 * 进入场景时执行一次
 */
void onEnterStart(void)
{
	NVICGroupInit(2);
	usart1Init(57600);
	basePeriphInit();
	delay_init(72);
	briupLcdInit();
	TIM2Init(72);
	C04Init();
	briupMPU6050Init();
	
	changeScene(SCENE_MENU);
}

/**
 * 当有按键操作时执行
 * @param type 按键类型 JOY_S JOY_U JOY_D JOY_L JOY_R
 */
void onKeyDownStart(u8 type)
{
}

/**
 * 每隔16ms以中断方式执行一次，帧率60FPS
 */
void onUpdateStart(void)
{
}

/**
 * 传感器事件
 */
void onSensorStart(short x, short y, short z)
{
}
