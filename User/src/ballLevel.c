/**
 * 等级选择场景实现文件
 */
#include "ballLevel.h"
#include "ballCore.h"

#define MAX_LEVEL 8

//记录当前等级
static u8 g_level = 0;

/**
 * 进入场景时执行一次
 */
void onEnterLevel(void)
{
	briupLcdClear(WHITE);
	
	briupLcdFastDrawDirection(30, 320 - 30, 22, 22 + 50,  BLACK, 1);
	briupLcdShowStr(4, 1, "Select Level", 32, 1, WHITE, BLACK);
	
	briupLcdFastDrawDirection(15, 320 - 15, 104, 104 + 100,  BLACK, 0);
	briupLcdShowStr(4, 6, " Simple ", 16, 1, GREEN, WHITE);
	
	briupLcdFastDrawDirection(15, 320 - 15, 232, 232 + 100,  BLACK, 0);
	briupLcdShowStr(4, 14, " Normal ", 16, 1, BLUE, WHITE);
	
	briupLcdFastDrawDirection(15, 320 - 15, 360, 360 + 100,  BLACK, 0);
	briupLcdShowStr(5, 22, " Hard ", 16, 1, RED, WHITE);
	
	setLevel(g_level, 1);
}

/**
 * 当有按键操作时执行
 * @param type 按键类型 JOY_S JOY_U JOY_D JOY_L JOY_R
 */
void onKeyDownLevel(u8 type)
{
	switch(type)
	{
		case JOY_S:
			changeScene(SCENE_GAME);
		break;
		case JOY_L:
			setLevel(g_level - 3, 1);
		break;
		case JOY_R:
			setLevel(g_level + 3, 1);
		break;
		case JOY_D:
			setLevel(g_level - 1, 1);
		break;
		case JOY_U:
			setLevel(g_level + 1, 1);
		break;
		default: break;
	}
}

/**
 * 获取当前关卡等级
 * @return 当前关卡
 */
u8 getLevel(void)
{
	return g_level;
}

/**
 * 每隔16ms以中断方式执行一次，帧率60FPS
 */
void onUpdateLevel(void)
{
}

/**
 * 传感器事件
 */
void onSensorLevel(short x, short y, short z)
{
}

/**
 * 选择关卡
 * @param level 设置的关卡等级
 * @param needDraw 是否需要绘制
 */
void setLevel(u8 level, u8 needDraw)
{
	u8 c;
	if(level > MAX_LEVEL)
		return;
	
	for(c = 0; c < 3; c++)
	{
		if(level / 3 == 0 && level % 3 == c)
		{
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 114, 114 + 80,  WHITE, 1);
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 114, 114 + 80,  GREEN, 0);
			briupLcdShowChar(62 + c * 90, 140, c + 1 + '0', 32, 1, GREEN, WHITE);
		}else
		{
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 114, 114 + 80,  GREEN, 1);
			briupLcdShowChar(62 + c * 90, 140, c + 1 + '0', 32, 1, WHITE, GREEN);
		}
	}
	
	for(c = 0; c < 3; c++)
	{
		if(level / 3 == 1 && level % 3 == c)
		{
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 242, 242 + 80,  WHITE, 1);
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 242, 242 + 80,  BLUE, 0);
			briupLcdShowChar(62 + c * 90, 268, c + 4 + '0', 32, 1, BLUE, WHITE);
		}else
		{
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 242, 242 + 80,  BLUE, 1);
			briupLcdShowChar(62 + c * 90, 268, c + 4 + '0', 32, 1, WHITE, BLUE);
		}
	}
	
	for(c = 0; c < 3; c++)
	{
		if(level / 3 == 2 && level % 3 == c)
		{
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 370, 370 + 80,  WHITE, 1);
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 370, 370 + 80,  RED, 0);
			briupLcdShowChar(62 + c * 90, 396, c + 7 + '0', 32, 1, RED, WHITE);
		}else
		{
			briupLcdFastDrawDirection(30 + c * 90, 30 + c * 90 + 80, 370, 370 + 80,  RED, 1);
			briupLcdShowChar(62 + c * 90, 396, c + 7 + '0', 32, 1, WHITE, RED);
		}
	}
	g_level = level;
}
