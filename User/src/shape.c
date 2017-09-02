/****************************************
* File Name: shape.c
* Date: 2017年9月2日 15点28分
* Author: muxiaozi
* Description: 俄罗斯方块形状实现文件
****************************************/
#include "shape.h"
#include "control.h"
#include "briupLCD.h"
#include "briupUSART.h"

//方块边长
#define SQUARE_WIDTH 20

//形状集合
u32 g_shape[7][4] = {
	{33737728,33737728,33737728,33737728},
	{50366600,258048,50366600,258048},
	{16928256,33655936,16966656,33639488},
	{16958976,33639552,16958976,33639552},
	{16935936,33655872,16935936,33655872},
	{16920064,33654976,16967680,33670208},
	{16944640,33671296,16966144,33637568}
};

/**
 * 指定位置打印字符串
 * @param x x坐标
 * @param y y坐标
 * @param str 打印的字符串
 * @param size 字号 12/16/32可选
 * @param mode 是否应用前景色/背景色
 * @param point_color 字体颜色
 * @param back_color 背景颜色
 */
static void printStr(u16 x,u16 y,char *str,u8 size,u8 mode,u16 point_color,u16 back_color)
{
	while(*str != '\0')
	{
		briupLcdShowChar(x++ * size / 2, y * size, *str++, size, mode, point_color, back_color);
	}
}

/**
 * 指定位置打印数字
 * @param x x坐标
 * @param y y坐标
 * @param num 打印的数字
 * @param len 长度
 * @param size 字号 12/16/32可选
 * @param mode 是否显示背景色
 */
static void printNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{
	briupLcdShowxNum(x * size / 2, y * size, num, len, size, mode);
}

/**
 * 打印菜单界面
 */
void print_menu(void)
{
	if(g_menu == MENU_AUTO)
	{
		printStr(6, 6, "  Play  ", 32, 0, BLACK, WHITE);
		printStr(6, 8, "  Auto  ", 32, 1, WHITE, BLUE);
	}else
	{
		printStr(6, 6, "  Play  ", 32, 1, WHITE, BLUE);
		printStr(6, 8, "  Auto  ", 32, 0, BLACK, WHITE);
	}
}

/**
 * 打印框架
 */
void print_frame(void)
{
	briupLcdClear(GREEN);
	printStr(10, 10, "Grade:", 16, 0, BLACK, WHITE);
}

/**
 * 打印游戏结束界面
 * @param grade 分数
 */
void print_gameover(u16 grade)
{
	printStr(5, 6, "Game Over", 32, 1, RED, WHITE);
	printStr(5, 8, "Grade:", 32, 0, BLACK, WHITE);
	printNum(11, 8, grade, 3, 32, 1);
}

/**
 * 打印方块
 * @param n 方块种类
 * @param m 方块旋转状态
 * @param x 方块左上角x坐标
 * @param y 方块左上角y坐标
 * @param c 方块颜色
 */
void print_mode_shape(u8 n, u8 m, u8 x, u8 y, u16 c)
{
	s8 i;
	u16 tx, ty;
	for(i = 15; i >= 0; i--)
	{
		if(g_shape[n][m] & 1<<i)
		{
			ty = 3 - (i >> 2) + y;
			tx = 3 - i % 4 + x;
			briupLcdFastDrawDirection(tx * SQUARE_WIDTH + 1, (tx + 1) * SQUARE_WIDTH - 1,
									ty * SQUARE_WIDTH + 1, (ty + 1) * SQUARE_WIDTH - 1, c, 1);
		}
	}
}

/**
 * 打印地图方块
 */
void print_matrix(void)
{
	
}
