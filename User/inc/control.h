/****************************************
* File Name: control.h
* Date: 2017年9月2日 16点01分
* Author: muxiaozi
* Description: 俄罗斯方块控制接口
****************************************/
#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <stm32f10x.h>

//游戏状态
typedef enum GameState
{
	STATE_MENU,		//菜单状态
	STATE_PLAY,		//游戏状态
	STATE_STOP,		//暂停状态
	STATE_GAMEOVER	//游戏结束
}GameState_Type;

//菜单
typedef enum Menu
{
	MENU_PLAY,	//手动模式
	MENU_AUTO	//自动模式
}Menu_Type;

//全局游戏状态
extern GameState_Type g_gameState;
//全局菜单状态
extern Menu_Type g_menu;
//全局游戏按键处理
extern void(*g_gameKeyDown[4])(u8 type);
//全局游戏事件更新
extern void(*g_gameUpdate[4])(void);
//行数
extern const u8 g_row;
//列数
extern const u8 g_col;

/**
 * 处理按键
 * @param type 按键类型
 */
static void menuKeyDown(u8 type);		//菜单
static void playKeyDown(u8 type);		//游戏中
static void stopKeyDown(u8 type);		//暂停
static void gameoverKeyDown(u8 type);	//游戏结束

/**
 * 更新事件
 */
static void menuUpdate(void);		//菜单
static void playUpdate(void);		//游戏中
static void stopUpdate(void);		//暂停
static void gameoverUpdate(void);	//游戏结束

/**
 * 改变游戏状态
 * @param state 游戏状态
 */
void changeGameState(GameState_Type state);

/**
 * 改变形态
 */
void change_shape(void);

/**
 * 向左移动
 */
void move_shape_left(void);

/**
 * 向右移动
 */
void move_shape_right(void);

/**
 * 向下移动
 */
void move_shape_down(void);

/**
 * 快速下落
 */
void fall_down(void);

/**
 * 碰撞检测
 * @param n 方块种类
 * @param m 方块旋转状态
 * @param x 欲检测位置的x坐标
 * @param y 欲检测位置的y坐标
 */
u8 judge_shape(int n, int m, int x, int y);

/**
 * 产生新行
 */
void new_shape(void);

/**
 * 消行
 */
void destroy_line(void);

/**
 * 提示下落位置
 */
void show_hint_shape(void);

/**
 * 隐藏下落位置提示
 */
void hide_hint_shape(void);


#endif //__CONTROL_H__
