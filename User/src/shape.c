/****************************************
* File Name: shape.c
* Date: 2017年9月2日 15点28分
* Author: muxiaozi
* Description: 俄罗斯方块形状实现文件
****************************************/
#include "shape.h"
#include "control.h"
#include "briupLCD.h"
#include <string.h>

//方块边长
#define SQUARE_WIDTH 20

//菜单条目打印起始横坐标
#define MENU_START_X 4

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
void printStr(u16 x, u16 y, const char *str, u8 size, u8 mode, u16 point_color, u16 back_color)
{
	while(*str != '\0')
	{
		briupLcdShowChar(x++ * size >> 1, y * size, *str++, size, mode, point_color, back_color);
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
void printNum(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode)
{
	briupLcdShowxNum(x * size >> 1, y * size, num, len, size, mode);
}

/**
 * 打印菜单界面
 * @param y 起始y坐标，因为x坐标会自动计算，所以不需要x坐标
 * @param items 菜单集合
 * @param count 菜单个数
 * @param selected 选中条目的索引
 */
void print_menu(u8 y, const char *items[], u8 count, u8 selected)
{
	u8 i, x;
	for(i = 0; i < count; i++)
	{
		//10 = 屏幕宽度320 / 字体宽度16 / 屏幕一半2
		//x = 屏幕一半字符数 - 条目的一半
		x = 10 - (strlen(items[i]) >> 1);
		if(i == selected)
		{
			printStr(x, y + (i << 1), items[i], 32, 1, BLUE, WHITE); 
			briupLcdFastDrawDirection(64, 256, (y + (i << 1)) * 32, (y + (i << 1) + 1) * 32, BLACK, 0);
		}else
		{
			printStr(x, y + (i << 1), items[i], 32, 0, BLACK, BLUE);
			briupLcdFastDrawDirection(64, 256, (y + (i << 1)) * 32, (y + (i << 1) + 1) * 32, WHITE, 0);
		}
	}
}

/**
 * 打印框架
 */
void print_frame(void)
{
	//下一个方块区域
	printStr(30, 1, "Next1:", 16, 0, BLACK, WHITE);
	briupLcdFastDrawLine(11 * SQUARE_WIDTH, 140, 320, 140, BLACK);
	
	//下下一个方块区域
	printStr(30, 9, "Next2:", 16, 0, BLACK, WHITE);
	briupLcdFastDrawLine(11 * SQUARE_WIDTH, 280, 320, 280, BLACK);
	
	printStr(30, 18, "Grade:", 16, 0, BLACK, WHITE);
	print_grade(0);
	
	//竖线
	briupLcdFastDrawLine(11 * SQUARE_WIDTH, 0, 11 * SQUARE_WIDTH, 480, BLACK);
}

/**
 * 打印得分
 * @param grade 得分
 */
void print_grade(u16 grade)
{
	printNum(15, 10, grade, 3, 32, 0);
}

/**
 * 打印游戏结束界面
 * @param grade 分数
 */
void print_gameover(u16 grade)
{
	printStr(5, 3, "Game Over", 32, 1, RED, WHITE);
	printStr(5, 5, "Grade:", 32, 0, BLACK, WHITE);
	printNum(11, 5, grade, 3, 32, 0);
}

/**
 * 打印最小正方形
 * @param x 方块左上角x坐标
 * @param y 方块左上角y坐标
 * @param c 方块颜色
 */
void print_square(u8 x, u8 y, u16 c)
{
	briupLcdFastDrawDirection(x * SQUARE_WIDTH + 1, (x + 1) * SQUARE_WIDTH - 1,
									y * SQUARE_WIDTH + 1, (y + 1) * SQUARE_WIDTH - 1, c, 1);
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
 * 打印提示方块
 * @param n 方块种类
 * @param m 方块旋转状态
 * @param x 方块左上角x坐标
 * @param y 方块左上角y坐标
 * @param c 方块颜色
 */
void print_hint_shape(u8 n, u8 m, u8 x, u8 y, u16 c)
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
									ty * SQUARE_WIDTH + 1, (ty + 1) * SQUARE_WIDTH - 1, c, 0);
		}
	}
}

