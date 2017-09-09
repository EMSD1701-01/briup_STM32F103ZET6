/**
 * 游戏结束场景
 */
#include "ballGameover.h"
#include "ballCore.h"

#define MENU_RESTART 0
#define MENU_MENU 1

static u8 g_menu;

//菜单选项
const static char *ITEMS[] = 
{
	"Restart", "Menu"
};

/**
 * 进入场景时执行一次
 */
void onEnterGameover(void)
{
	g_menu = MENU_RESTART;
	briupLcdClear(WHITE);
	briupLcdShowStr(4, 4, "  Game Over  ", 32, 1, RED, WHITE);
	print_menu(7, ITEMS, 2, g_menu);
}

/**
 * 当有按键操作时执行
 * @param type 按键类型 JOY_S JOY_U JOY_D JOY_L JOY_R
 */
void onKeyDownGameover(u8 type)
{
	switch(type)
	{
		case JOY_L:
			g_menu = g_menu > 0 ? g_menu - 1 : 0;
			print_menu(7, ITEMS, 2, g_menu);
		break;
		case JOY_R:
			g_menu = g_menu < 1 ? g_menu + 1 : 1;
			print_menu(7, ITEMS, 2, g_menu);
		break;
		case JOY_S:
			if(g_menu == MENU_RESTART)
			{
				changeScene(SCENE_GAME);
			}else if(g_menu == MENU_MENU)
			{
				changeScene(SCENE_MENU);
			}
		break;
		default: break;
	}
}

/**
 * 每隔16ms以中断方式执行一次，帧率60FPS
 */
void onUpdateGameover(void)
{

}

/**
 * 传感器事件
 */
void onSensorGameover(short x, short y, short z)
{

}
