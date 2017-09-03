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
	STATE_GAMEOVER	//游戏结束
}GameState_Type;

//菜单
typedef enum Menu
{
	MENU_PLAY,	//手动模式
	MENU_AUTO,	//自动模式
	
	MENU_RESTART,	//重新开始
	MENU_MENU,		//进入主菜单
}Menu_Type;


//全局按键处理
extern void(*g_gameKeyDown[3])(u8 type);
//全局事件更新
extern void(*g_gameUpdate[3])(void);
//进入场景
extern void(*g_gameEnter[3])(void);

//全局游戏状态
extern GameState_Type g_gameState;
//行数
extern const u8 g_row;
//列数
extern const u8 g_col;
//伪时间种子
extern u32 g_seed;

/**
 * 处理按键
 * @param type 按键类型
 */
static void onMenuKeyDown(u8 type);		//菜单
static void onPlayKeyDown(u8 type);		//游戏中
static void onGameoverKeyDown(u8 type);	//游戏结束

/**
 * 更新事件
 */
static void onMenuUpdate(void);		//菜单
static void onPlayUpdate(void);		//游戏中
static void onGameoverUpdate(void);	//游戏结束

/**
 * 进入场景
 */
static void onEnterMenu(void);		//菜单
static void onEnterPlay(void);		//游戏中
static void onEnterGameover(void);	//游戏结束

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
 * @return 如果产生碰撞，返回1，否则返回0
 */
u8 judge_shape(int n, int m, int x, int y);

/**
 * 产生新方块
 * @param begin 是否开始游戏的第一次产生方块
 */
void new_shape(u8 begin);

/**
 * 判断某行是否已满
 * @param row 待判断行
 * @return 如果已满返回1，否则返回0
 */
u8 is_full_line(u8 row);

/**
 * 判断某行是否为空行
 * @param row 待判断行
 * @return 如果为空行返回1，否则返回0
 */
u8 is_empty_line(u8 row);

/**
 * 消行
 */
void destroy_line(void);

/**
 * 存储当前方块到地图中
 */
void store_shape(void);

/**
 * 根据地图数据打印界面
 */
void draw_matrix(void);

/**
 * 提示下落位置
 */
void show_hint_shape(void);

/**
 * 隐藏下落位置提示
 */
void hide_hint_shape(void);


#endif //__CONTROL_H__
