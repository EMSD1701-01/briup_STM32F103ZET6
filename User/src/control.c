/****************************************
* File Name: control.c
* Date: 2017年9月2日 16点02分
* Author: muxiaozi
* Description: 俄罗斯方块控制实现文件
****************************************/
#include "control.h"
#include "briupDelay.h"
#include "briupBasePeriph.h"
#include "briupLCD.h"	//产生方块需要颜色的宏
#include "shape.h"

GameState_Type g_gameState = STATE_GAMEOVER;	//当前游戏状态
Menu_Type g_menu = MENU_PLAY;	//菜单选择状态
const u8 g_col = 16; //列数
const u8 g_row = 20; //行数
static u8 g_x[2];	//x坐标 0.当前，1.下一个
static u8 g_y[2];	//y坐标 0.当前，1.下一个
static u8 g_n[2];	//方块类型 0.当前，1.下一个
static u8 g_m[2];	//旋转状态 0.当前，1.下一个

u8 g_map[g_row][g_col * 2];	//全局地图

//事件表
void(*g_gameKeyDown[4])(u8 type) = 
{
	menuKeyDown,
	playKeyDown,
	stopKeyDown,
	gameoverKeyDown
};

//更新表
void(*g_gameUpdate[4])(void) = 
{
	menuUpdate,
	playUpdate,
	stopUpdate,
	gameoverUpdate
};

/**
 * 处理菜单事件
 * @param type 事件类型
 */
static void menuKeyDown(u8 type)
{
	if(type == JOY_L && g_menu != MENU_PLAY)
	{
		g_menu = MENU_PLAY;	
		print_menu();
	}else if(type == JOY_R && g_menu != MENU_AUTO)
	{
		g_menu = MENU_AUTO;
		print_menu();
	}else if(type == JOY_S)
	{
		changeGameState(STATE_PLAY);
	}
}

/**
 * 处理游戏事件
 * @param type 事件类型
 */
static void playKeyDown(u8 type)
{
	
}

/**
 * 处理暂停事件
 * @param type 事件类型
 */
static void stopKeyDown(u8 type)
{
	
}

/**
 * 处理游戏结束事件
 * @param type 事件类型
 */
static void gameoverKeyDown(u8 type)
{
	
}
/**
 * 菜单更新
 */
static void menuUpdate(void)
{
	u32 i;
	for(i = 0; i < 4; i++)
	{
		print_mode_shape(5, i, 2, 2, RED);
		print_mode_shape(3, i, 10, 18, GREEN);
		delay_ms(100);
		print_mode_shape(5, i, 2, 2, WHITE);
		print_mode_shape(3, i, 10, 18, WHITE);
	}
}
/**
 * 游戏更新
 */
static void playUpdate(void)
{
	
	
}
/**
 * 暂停更新
 */
static void stopUpdate(void)
{
	
}
/**
 * 游戏结束更新
 */
static void gameoverUpdate(void)
{
	
}

/**
 * 改变游戏状态
 * @param state 游戏状态
 */
void changeGameState(GameState_Type state)
{
	if(state != g_gameState)
	{
		switch(state)
		{
			case STATE_MENU:
				briupLcdClear(WHITE);
				setLed(LED_C);
				print_menu();
			break;
			case STATE_PLAY:
				print_frame();
				setLed(LED_G);
			break;
			case STATE_STOP:
				setLed(LED_Y);
			break;
			case STATE_GAMEOVER:
				print_gameover(123);
				setLed(LED_R);
			break;
			default: break;
		}
		g_gameState = state;
	}
}

/**
 * 改变形态
 */
void change_shape(void)
{
	
}

/**
 * 向左移动
 */
void move_shape_left(void)
{
	
}

/**
 * 向右移动
 */
void move_shape_right(void)
{
	
}

/**
 * 向下移动
 */
void move_shape_down(void)
{
	
}

/**
 * 快速下落
 */
void fall_down(void)
{
	
}

/**
 * 碰撞检测
 * @param n 方块种类
 * @param m 方块旋转状态
 * @param x 欲检测位置的x坐标
 * @param y 欲检测位置的y坐标
 * @return 如果产生碰撞，返回1，否则返回0
 */
u8 judge_shape(int n, int m, int x, int y)
{
	return 0;
}

/**
 * 产生新行
 */
void new_shape(void)
{
	
}

/**
 * 消行
 */
void destroy_line(void)
{
	
}

/**
 * 提示下落位置
 */
void show_hint_shape(void)
{
	
}

/**
 * 隐藏下落位置提示
 */
void hide_hint_shape(void)
{
	
}

