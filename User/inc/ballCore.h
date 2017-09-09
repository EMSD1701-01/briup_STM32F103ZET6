/**
 * 核心模块
 * 协调各种事件，负责场景转换
 */
#ifndef __BALLCORE_H__
#define __BALLCORE_H__
#include <stm32f10x.h>
#include "briupBasePeriph.h"	//基础外设
#include "briupLCD.h"			//LCD
#include "briupDelay.h"			//延时
#include <stdio.h>				//printf

typedef enum
{
	SCENE_START,	//初始化场景，注意：其它场景不能主动切换到此场景
	SCENE_MENU,		//菜单场景
	SCENE_GAME,		//游戏场景
	SCENE_GAMEOVER,	//游戏结束场景
	SCENE_LEVEL,	//选择关卡
	SCENE_HELP,		//帮助
	SCENE_RANK		//排行榜
}Scene;

/**
 * 切换场景
 * @param scene 下一个场景，如果目标场景是SCENE_START，则无效
 */
void changeScene(Scene scene);

/**
 * 运行平衡球
 */
void runBalanceBall(void);

/**
 * 打印菜单界面
 * @param y 起始y坐标，因为x坐标会自动计算，所以不需要x坐标
 * @param items 菜单集合
 * @param count 菜单个数
 * @param selected 选中条目的索引
 */
void print_menu(u8 y, const char *items[], u8 count, u8 selected);


#endif //__BALLCORE_H__
