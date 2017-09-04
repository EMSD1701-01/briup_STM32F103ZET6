/****************************************
* File Name: control.c
* Date: 2017年9月2日 16点02分
* Author: muxiaozi
* Description: 俄罗斯方块控制实现文件
****************************************/
#include "control.h"
#include "briupBasePeriph.h"
#include "briupLCD.h"	//颜色
#include "shape.h"
#include <stdlib.h>	//srand(u32) rand()

GameState_Type g_gameState = STATE_GAMEOVER;	//当前游戏状态
Menu_Type g_menu = MENU_AUTO;	//菜单选项
const u8 g_col = 11; //列数
const u8 g_row = 24; //行数
static u8 g_x[3];	//x坐标 0.当前，1.下一个
static u8 g_y[3];	//y坐标 0.当前，1.下一个
static u8 g_n[3];	//方块类型 0.当前，1.下一个
static u8 g_m[3];	//旋转状态 0.当前，1.下一个
static u16 g_c[3];	//颜色	0.当前，1.下一个
static u8 g_pause = 0;	//暂停
static u16 g_grade = 0;	//分数
static u16 g_record = 0;//最高纪录
u32 g_seed;	//伪时间种子
u16 g_map[g_row][g_col * 2];	//全局地图

const static u16 COLORS[] = //颜色库
{
	BLUE,BRED,GRED,GBLUE,RED,MAGENTA,GREEN,BROWN,BRRED,GRAY,DARKBLUE,GRAYBLUE
};
const static char* START_MENU[] = //开始菜单
{
	"Play", "Auto"
};
const static char* GAMEOVER_MENU[] = //游戏结束菜单
{
	"Restart", "Menu"
};

//全局按键处理
void(*g_gameKeyDown[3])(u8 type) = 
{
	onMenuKeyDown,
	onPlayKeyDown,
	onGameoverKeyDown
};

//全局事件更新
void(*g_gameUpdate[3])(void) = 
{
	onMenuUpdate,
	onPlayUpdate,
	onGameoverUpdate
};

//进入场景
void(*g_gameEnter[3])(void) =
{
	onEnterMenu,
	onEnterPlay,
	onEnterGameover
};

/**
 * 处理菜单事件
 * @param type 事件类型
 */
static void onMenuKeyDown(u8 type)
{
	if(type == JOY_L && g_menu != MENU_PLAY)
	{
		g_menu = MENU_PLAY;	
		print_menu(6, START_MENU, 2, 0);
	}else if(type == JOY_R && g_menu != MENU_AUTO)
	{
		g_menu = MENU_AUTO;
		print_menu(6, START_MENU, 2, 1);
	}else if(type == JOY_S)
	{
		if(g_menu == MENU_PLAY)
		{
			changeGameState(STATE_PLAY);
		}else
		{
			//TODO AI功能
		}
	}
}

/**
 * 处理游戏事件
 * @param type 事件类型
 */
static void onPlayKeyDown(u8 type)
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
static void onGameoverKeyDown(u8 type)
{
	if(type == JOY_L && g_menu != MENU_RESTART)
	{
		g_menu = MENU_RESTART;	
		print_menu(8, GAMEOVER_MENU, 2, 0);
	}else if(type == JOY_R && g_menu != MENU_MENU)
	{
		g_menu = MENU_MENU;
		print_menu(8, GAMEOVER_MENU, 2, 1);
	}else if(type == JOY_S)
	{
		if(g_menu == MENU_RESTART)
		{
			changeGameState(STATE_PLAY);
		}else if(g_menu == MENU_MENU)
		{
			changeGameState(STATE_MENU);
		}
	}
}

/**
 * 菜单更新
 */
static void onMenuUpdate(void)
{
	static u8 i = 0;
	if(g_seed % 0x4ffff == 0)
	{
		i++;
		print_mode_shape(5, (i - 1) % 4, 2, 2, WHITE);
		print_mode_shape(3, (i - 1) % 4, 10, 18, WHITE);
		print_mode_shape(5, i % 4, 2, 2, RED);
		print_mode_shape(3, i % 4, 10, 18, GREEN);
	}
}

/**
 * 游戏更新
 */
static void onPlayUpdate(void)
{
	if(!g_pause)
	{
		if(g_seed % 0xfffff == 0)
		{
			move_shape_down();
		}
	}
}

/**
 * 游戏结束更新
 */
static void onGameoverUpdate(void)
{
	
}

/**
 * 进入菜单场景
 */
static void onEnterMenu(void)
{
	setLed(LED_Y);
	g_menu = MENU_PLAY;
	briupLcdClear(WHITE);
	print_menu(6, START_MENU, 2, 0);
}

/**
 * 进入游戏场景
 */
static void onEnterPlay(void)
{
	u8 x, y;
	for(x = 0; x < g_col * 2; x++)
	{
		for(y = 0; y < g_row; y++)
		{
			g_map[y][x] = 0;
		}
	}
	g_grade = 0;
	g_pause = 0;
	g_x[1] = 12;
	g_y[1] = 2;
	g_x[2] = 12;
	g_y[2] = 9;
	
	setLed(LED_G);
	briupLcdClear(WHITE);
	print_frame();
	new_shape(1);
	print_grade(g_grade, g_record);
}

/**
 * 进入游戏结束场景
 */
static void onEnterGameover(void)
{
	g_menu = MENU_RESTART;
	briupLcdClear(WHITE);
	print_menu(8, GAMEOVER_MENU, 2, 0);
	print_gameover(g_grade, g_record);
	if(g_grade > g_record) 
		g_record = g_grade;
	setLed(LED_R);
}

/**
 * 改变游戏状态
 * @param state 游戏状态
 */
void changeGameState(GameState_Type state)
{
	if(state != g_gameState)
	{
		//调用相应的转场回调
		g_gameEnter[state]();
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
		hide_hint_shape();
		print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], WHITE);
		g_m[0] = tm;
		show_hint_shape();
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
		hide_hint_shape();
		print_mode_shape(g_n[0], g_m[0], g_x[0]--, g_y[0], WHITE);
		show_hint_shape();
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
		hide_hint_shape();
		print_mode_shape(g_n[0], g_m[0], g_x[0]++, g_y[0], WHITE);
		show_hint_shape();
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
		store_shape();
		destroy_line();
		if(g_y[0] <= 0) //游戏结束
		{
			changeGameState(STATE_GAMEOVER);
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
	while(!judge_shape(g_n[0], g_m[0], g_x[0], g_y[0] + step)) 
		step++;
	print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], WHITE);
	g_y[0] += step - 1;
	print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], g_c[0]);
	//等待下一次下落刷新
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
	
	if(x < 0 || x > g_col - (4 - right_space)) 
		return 1;
	if(y < 0 || y > g_row - (4 - bottom_space)) 
		return 1;

	for(i = 15; i >= 0; i--)
	{
		ty = 3 - (i >> 2);
		if(ty >= 4 - bottom_space) 
			continue;
		tx = 3 - i % 4;
		if(tx >= 4 - right_space) 
			continue;
		if(g_shape[n][m] & 1<<i)
		{
			if(g_map[ty+y][(tx+x)<<1]) 
				return 1;
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
	srand(g_seed);
	if(begin)
	{
		//随机
		g_m[0] = rand() % 4;
		g_n[0] = rand() % 7;
		g_c[0] = COLORS[rand() % (sizeof(COLORS) / sizeof(u16))];
		
		//Next1
		g_m[1] = rand() % 4;
		g_n[1] = rand() % 7;
		g_c[1] = COLORS[rand() % (sizeof(COLORS) / sizeof(u16))];
		print_mode_shape(g_n[1], g_m[1], g_x[1], g_y[1], g_c[1]);
	}else
	{
		g_m[0] = g_m[1];
		g_n[0] = g_n[1];
		g_c[0] = g_c[1];
		
		//Next1
		print_mode_shape(g_n[1], g_m[1], g_x[1], g_y[1], WHITE);
		g_m[1] = g_m[2];
		g_n[1] = g_n[2];
		g_c[1] = g_c[2];
		print_mode_shape(g_n[1], g_m[1], g_x[1], g_y[1], g_c[1]);
	}
	
	//Next2
	print_mode_shape(g_n[2], g_m[2], g_x[2], g_y[2], WHITE);
	g_m[2] = rand() % 4;
	g_n[2] = rand() % 7;
	g_c[2] = COLORS[rand() % (sizeof(COLORS) / sizeof(u16))];
	print_mode_shape(g_n[2], g_m[2], g_x[2], g_y[2], g_c[2]);
	
	g_x[0] = 6;
	g_y[0] = 0;
	
	show_hint_shape();
	print_mode_shape(g_n[0], g_m[0], g_x[0], g_y[0], g_c[0]);
}

/**
 * 判断某行是否已满
 * @param row 待判断行
 * @return 如果已满返回1，否则返回0
 */
u8 is_full_line(u8 row)
{
	u8 x;
	for(x = 0; x < g_col; x++)
	{
		if(!g_map[row][x<<1])
			return 0;
	}
	return 1;
}

/**
 * 判断某行是否为空行
 * @param row 待判断行
 * @return 如果为空行返回1，否则返回0
 */
u8 is_empty_line(u8 row)
{
	u8 x;
	for(x = 0; x < g_col; x++)
	{
		if(g_map[row][x<<1]) 
			return 0;
	}
	return 1;
}

/**
 * 消行
 */
void destroy_line(void)
{
	//消行数
	u8 line_cnt = 0;
	//当前检测位置
	u8 x, y, ty;
	//被检测形状的高度
	u8 shape_height = 4 - (g_shape[g_n[0]][g_m[0]] >> 16 & 0x00ff);
	
	//处理方块所在的几行
	for(y = g_y[0]; y < g_y[0] + shape_height; y++)
	{
		if(is_full_line(y))
		{
			ty = y;
			line_cnt++;
			while(!is_empty_line(ty) && ty > 0)
			{
				for(x = 0; x < g_col * 2; x++)
				{
					g_map[ty][x] = g_map[ty - 1][x];
				}
				ty--;
			}
		}	
	}
	
	if(line_cnt != 0)
	{
		draw_matrix();
		g_grade += line_cnt * 8;
		print_grade(g_grade, g_record);
	}
}

/**
 * 存储当前方块到地图中
 */
void store_shape(void)
{
	s8 i;
	u16 tx, ty;
	for(i = 15; i >= 0; i--)
	{
		if(g_shape[g_n[0]][g_m[0]] & 1<<i)
		{
			ty = 3 - (i >> 2) + g_y[0];
			tx = 3 - i % 4 + g_x[0];
			g_map[ty][tx<<1] = 1;	//方块存在标志
			g_map[ty][(tx<<1)+1] = g_c[0]; //方块颜色
		}
	}
}

/**
 * 根据地图数据打印界面
 */
void draw_matrix(void)
{
	u8 x, y;
	for(x = 0; x < g_col; x++)
	{
		for(y = 0; y < g_row; y++)
		{
			if(g_map[y][x<<1]) //此处有方块
			{
				print_square(x, y, g_map[y][(x<<1) + 1]);
			}else
			{
				print_square(x, y, WHITE);
			}
		}
	}
}

/**
 * 提示下落位置
 */
void show_hint_shape(void)
{
	u8 step = 1;
	while(!judge_shape(g_n[0], g_m[0], g_x[0], g_y[0] + step))
		step++;
	print_hint_shape(g_n[0], g_m[0], g_x[0], g_y[0] + step - 1, BLACK);
}

/**
 * 隐藏下落位置提示
 */
void hide_hint_shape(void)
{
	u8 step = 1;
	while(!judge_shape(g_n[0], g_m[0], g_x[0], g_y[0] + step))
		step++;
	print_hint_shape(g_n[0], g_m[0], g_x[0], g_y[0] + step - 1, WHITE);
}

