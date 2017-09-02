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
const u8 g_row = 24; //行数
static u8 g_x[2];	//x坐标 0.当前，1.下一个
static u8 g_y[2];	//y坐标 0.当前，1.下一个
static u8 g_n[2];	//方块类型 0.当前，1.下一个
static u8 g_m[2];	//旋转状态 0.当前，1.下一个
static u16 g_c[2];	//颜色	0.当前，1.下一个
static u8 g_pause = 0;	//暂停
static u16 g_grade = 0;	//分数

u8 g_map[g_row][g_col * 2];	//全局地图

//事件表
void(*g_gameKeyDown[3])(u8 type) = 
{
	menuKeyDown,
	playKeyDown,
	gameoverKeyDown
};

//更新表
void(*g_gameUpdate[3])(void) = 
{
	menuUpdate,
	playUpdate,
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
	switch(type)
	{
		case JOY_L: //上
			if(!g_pause) change_shape();
		break;
		case JOY_R: //下
			if(!g_pause) fall_down();
		break;
		case JOY_D: //左
			if(!g_pause) move_shape_left();
		break;
		case JOY_U: //右
			if(!g_pause) move_shape_right();
		break;
		case JOY_S: //中
			g_pause = !g_pause;
		break;
		default: break;
	}
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
	if(!g_pause)
	{
		static u32 cnt = 0;
		if(cnt++ == 0xfffff)
		{
			cnt = 0;
			move_shape_down();
			//TODO 判断游戏结束
			//changeGameState(STATE_GAMEOVER);
		}
		
	}
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
				print_menu();
				setLed(LED_C);
			break;
			case STATE_PLAY:
				print_frame();
				new_shape(1);
				setLed(LED_G);
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
	u8 tm = g_m[0] < 3 ? g_m[0] + 1 : 0;
	if(!judge_shape(g_n[0], tm, g_x[0], g_y[0]))
	{
		print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], WHITE);
		g_m[0] = tm;
		print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], g_c[0]);
	}
}

/**
 * 向左移动
 */
void move_shape_left(void)
{
	if(!judge_shape(g_n[0], g_m[0], g_x[0] - 1, g_y[0]))
	{
		print_mode_shape(g_n[0], g_m[0], g_x[0]--, g_y[0], WHITE);
		print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], g_c[0]);
	}
}

/**
 * 向右移动
 */
void move_shape_right(void)
{
	if(!judge_shape(g_n[0], g_m[0], g_x[0] + 1, g_y[0]))
	{
		print_mode_shape(g_n[0], g_m[0], g_x[0]++, g_y[0], WHITE);
		print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], g_c[0]);
	}
}

/**
 * 向下移动
 */
void move_shape_down(void)
{
	if(!judge_shape(g_n[0], g_m[0], g_x[0], g_y[0]+1))
	{
		print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0]++, WHITE);
		print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], g_c[0]);
	}else
	{
		destroy_line();
		//游戏结束
		if(g_y[0] <= 0) 
		{
			
			return;
		}
		new_shape(0);
	}
}

/**
 * 快速下落
 */
void fall_down(void)
{
	u8 step = 1;
	while(!judge_shape(g_n[0], g_m[0], g_x[0], g_y[0] + step)) step++;
	print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], WHITE);
	g_y[0] += step - 1;
	print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], g_c[0]);

	destroy_line();
	//游戏结束
	if(g_y[0] <= 0) 
	{
		
		return;
	}
	new_shape(0);
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
	s8 i;
	u8 tx, ty;
	u8 right_space = g_shape[n][m]>>24;
	u8 bottom_space = g_shape[n][m]>>16 & 0x00ff;
	
	if(x < 0 || x > g_col - (4 - right_space)) return 1;
	if(y < 0 || y > g_row - (4 - bottom_space)) return 1;

	for(i = 15; i >= 0; i--)
	{
		ty = 3 - (i >> 2);
		if(ty >= 4 - bottom_space) continue;
		tx = 3 - i % 4;
		if(tx >= 4 - right_space) continue;
		if(g_shape[n][m] & 1<<i)
		{
			if(g_map[ty+y][(tx+x)<<1]) return 1;
		}
	}
	return 0;
}

/**
 * 产生新方块
 * @param begin 是否开始游戏的第一次产生方块
 */
void new_shape(u8 begin)
{
	if(begin)
	{
		//随机
		g_m[0] = 2;
		g_n[0] = 2;
		g_c[0] = RED;
	}else
	{
		g_m[0] = g_m[1];
		g_n[0] = g_n[1];
		g_c[0] = g_c[1];
	}
	
	//随机
	g_m[1] = 2;
	g_n[1] = 4;
	g_c[1] = YELLOW;
	
	g_x[0] = 0;
	g_y[0] = 0;
	g_x[1] = 1;
	g_x[1] = 1;
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

