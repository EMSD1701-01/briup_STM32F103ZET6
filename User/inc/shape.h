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
void printStr(u16 x, u16 y, const char *str, u8 size, u8 mode, u16 point_color, u16 back_color);

/**
 * 指定位置打印数字
 * @param x x坐标
 * @param y y坐标
 * @param num 打印的数字
 * @param len 长度
 * @param size 字号 12/16/32可选
 * @param mode 是否显示背景色
 */
void printNum(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode);

/**
 * 打印菜单界面
 * @param y 起始y坐标，因为x坐标会自动计算，所以不需要x坐标
 * @param items 菜单集合
 * @param count 菜单个数
 * @param selected 选中条目的索引
 */
void print_menu(u8 y, const char *items[], u8 count, u8 selected);

/**
 * 打印框架
 */
void print_frame(void);

/**
 * 打印得分
 * @param grade 得分
 */
void print_grade(u16 grade);

/**
 * 打印游戏结束界面
 * @param grade 分数
 */
void print_gameover(u16 grade);

/**
 * 打印最小正方形
 * @param x 方块左上角x坐标
 * @param y 方块左上角y坐标
 * @param c 方块颜色
 */
void print_square(u8 x, u8 y, u16 c);

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
 * 打印提示方块
 * @param n 方块种类
 * @param m 方块旋转状态
 * @param x 方块左上角x坐标
 * @param y 方块左上角y坐标
 * @param c 方块颜色
 */
void print_hint_shape(u8 n, u8 m, u8 x, u8 y, u16 c);


#endif //__SHAPE_H__
