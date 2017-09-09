/**
 * 菜单场景
 * 主要用于显示菜单界面，菜单包括以下条目，使用五项按键进行切换，注意屏幕方向
 * 1.开始游戏
 * 2.选择关卡
 * 3.帮助
 * 4.排行榜
 */
#include "ballMenu.h"
#include "ballCore.h"
#include <string.h>

#define MENU_PLAY 0
#define MENU_LEVEL 1
#define MENU_HELP 2
#define MENU_RANKING 3

static u8 g_menu;

//菜单选项
const static char *ITEMS[] = 
{
	"Play", "Level", "Help", "Rank"
};

/**
 * 进入场景时执行一次
 */
void onEnterMenu(void)
{
	g_menu = MENU_PLAY;
	briupLcdClear(WHITE);
	briupLcdShowStr(2, 1, "                ", 32, 1, GREEN, BLACK);
	briupLcdShowStr(2, 2, "  Balance Ball  ", 32, 1, GREEN, BLACK);
	briupLcdShowStr(2, 3, "                ", 32, 1, GREEN, BLACK);
	print_menu(5, ITEMS, 4, g_menu);
}

/**
 * 当有按键操作时执行
 * @param type 按键类型 JOY_S JOY_U JOY_D JOY_L JOY_R
 */
void onKeyDownMenu(u8 type)
{
	switch(type)
	{
		case JOY_L:
			g_menu = g_menu > 0 ? g_menu - 1 : 0;
			print_menu(5, ITEMS, 4, g_menu);
		break;
		case JOY_R:
			g_menu = g_menu < 3 ? g_menu + 1 : 3;
			print_menu(5, ITEMS, 4, g_menu);
		break;
		case JOY_S:
			switch(g_menu)
			{
				case MENU_PLAY:
					changeScene(SCENE_GAME);
				break;
				case MENU_LEVEL:
					changeScene(SCENE_LEVEL);
				break;
				case MENU_HELP:
					changeScene(SCENE_HELP);
				break;
				case MENU_RANKING:
					changeScene(SCENE_RANK);
				break;
			}
		break;
		default: break;
	}
}

/**
 * 每隔16ms以中断方式执行一次，帧率60FPS
 */
void onUpdateMenu(void)
{

}

/**
 * 传感器事件
 */
void onSensorMenu(short x, short y, short z)
{
	
}
