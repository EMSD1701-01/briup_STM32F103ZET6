/****************************************
* File Name: shape.h
* Date: 2017年9月2日 15点26分
* Author: muxiaozi
* Description: 俄罗斯方块形状接口文件
****************************************/
#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <stm32f10x.h>

//位置
typedef struct Point
{
	u16 x;
	u16 y;
}Point_Type;

//形状集合
extern u32 g_shape[7][4];

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
static void printStr(u16 x,u16 y,char *str,u8 size,u8 mode,u16 point_color,u16 back_color);

/**
 * 指定位置打印数字
 * @param x x坐标
 * @param y y坐标
 * @param num 打印的数字
 * @param len 长度
 * @param size 字号 12/16/32可选
 * @param mode 是否显示背景色
 */
static void printNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);

/**
 * 打印菜单界面
 */
void print_menu(void);

/**
 * 打印框架
 */
void print_frame(void);

/**
 * 打印游戏结束界面
 * @param grade 分数
 */
void print_gameover(u16 grade);

/**
 * 打印方块
 * @param n 方块种类
 * @param m 方块旋转状态
 * @param x 方块左上角x坐标
 * @param y 方块左上角y坐标
 * @param c 方块颜色
 */
void print_mode_shape(u8 n, u8 m, u8 x, u8 y, u16 c);

/**
 * 打印地图方块
 */
void print_matrix(void);



#endif //__SHAPE_H__

