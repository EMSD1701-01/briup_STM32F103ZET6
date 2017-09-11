/**
 * 游戏结束场景
 */
#include "ballGameover.h"
#include "ballCore.h"
#include "ballGame.h"
#include "ballLevel.h"

static u8 g_menu;

//菜单选项
const static char *ITEMS_WIN[] = 
{
	"Next Level", "Menu", "Restart"
};

const static char *ITEMS_LOSE[] = 
{
	"Restart", "Menu"
};

/**
 * 进入场景时执行一次
 */
void onEnterGameover(void)
{
	briupLcdClear(WHITE);
	briupLcdFastDrawDirection(40, 320 - 40, 64, 64 + 100, BLACK, 1);
	
	//选择默认菜单
	g_menu = 0;
	if(getGameState() == GAMESTATE_WIN)
	{
		briupLcdShowStr(6, 3, "YOU  WIN", 32, 1, YELLOW, BLACK);
		print_menu(7, ITEMS_WIN, 3, g_menu);
	}else
	{
		briupLcdShowStr(6, 3, "YOU LOSE", 32, 1, RED, BLACK);
		print_menu(7, ITEMS_LOSE, 2, g_menu);
	}
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
			if(getGameState() == GAMESTATE_WIN)
			{
				g_menu = g_menu > 0 ? g_menu - 1 : 0;
				print_menu(7, ITEMS_WIN, 3, g_menu);
			}else
			{
				g_menu = g_menu > 0 ? g_menu - 1 : 0;
				print_menu(7, ITEMS_LOSE, 2, g_menu);
			}
		break;
		case JOY_R:
			if(getGameState() == GAMESTATE_WIN)
			{
				g_menu = g_menu < 2 ? g_menu + 1 : 2;
				print_menu(7, ITEMS_WIN, 3, g_menu);
			}else
			{
				g_menu = g_menu < 1 ? g_menu + 1 : 1;
				print_menu(7, ITEMS_LOSE, 2, g_menu);
			}
		break;
		case JOY_S:
			if(getGameState() == GAMESTATE_WIN)
			{
				if(g_menu == 0)
				{
					setLevel(getLevel() + 1, 0);
					changeScene(SCENE_GAME);
				}else if(g_menu == 1)
				{
					changeScene(SCENE_MENU);
				}else if(g_menu == 2)
				{
					changeScene(SCENE_GAME);
				}
			}else
			{
				if(g_menu == 0)
				{
					changeScene(SCENE_GAME);
				}else if(g_menu == 1)
				{
					changeScene(SCENE_MENU);
				}
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
