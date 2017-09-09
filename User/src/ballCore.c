/**
 * 核心模块
 * 协调各种事件，负责场景转换
 */
#include "ballCore.h"
#include "ballStart.h"
#include "ballMenu.h"
#include "ballGame.h"
#include "ballGameover.h"
#include "ballLevel.h"
#include "ballRank.h"
#include "ballHelp.h"
#include "briupTIM2.h"
#include "briupMPU6050.h"
#include <string.h>

//当前场景
static Scene g_scene = SCENE_START;

//更新向量表
static void(*const g_onUpdate[])(void) = 
{
	onUpdateStart,
	onUpdateMenu,
	onUpdateGame,
	onUpdateGameover,
	onUpdateLevel,
	onUpdateHelp,
	onUpdateRank
};
//按键向量表
static void(*const g_onKeyDown[])(u8 type) = 
{
	onKeyDownStart,
	onKeyDownMenu,
	onKeyDownGame,
	onKeyDownGameover,
	onKeyDownLevel,
	onKeyDownHelp,
	onKeyDownRank
};
//MPU6050传感器向量表
static void(*const g_onSensor[])(short x, short y, short z) = 
{
	onSensorStart,
	onSensorMenu,
	onSensorGame,
	onSensorGameover,
	onSensorLevel,
	onSensorHelp,
	onSensorRank
};
//进入场景向量表
static void(*const g_onEnter[])(void) = 
{
	onEnterStart,
	onEnterMenu,
	onEnterGame,
	onEnterGameover,
	onEnterLevel,
	onEnterHelp,
	onEnterRank
};

/**
 * 按键回调
 */
static void JoyHandler(u8 type)
{
	static u16 jcnt = 0; //按键延时计数器
	g_onKeyDown[g_scene](type);
	delay_ms(200); //防止按键按下很短时间内再次响应按键
	while(getJoy())
	{
		if(jcnt++ == 0xffff)
		{
			g_onKeyDown[g_scene](type);
		}
	}
}

/**
 * 定时器2更新回调
 * @note 更新时间 16ms
 */
static void TIM2Handler()
{
	g_onUpdate[g_scene]();
}

/**
 * 切换场景
 * @param scene 下一个场景，如果目标场景是SCENE_START，则无效
 */
void changeScene(Scene scene)
{
	//禁止进入初始化场景，因为初始化场景最多执行一次
	if(scene == SCENE_START)
		return;
	if(scene != g_scene)
	{
		g_onEnter[scene]();
		g_scene = scene;
	}
}

/**
 * 运行平衡球
 */
void runBalanceBall(void)
{
	short x, y, z;
	
	//进入初始化场景
	g_scene = SCENE_START;
	g_onEnter[g_scene]();
	
	//监听按键回调
	setJoyInterrupt(JoyHandler);
	
	//更新函数 16ms
	//暂时不需要定时刷新函数，有重力感应驱动就够了
	//TIM2Start(16000, TIM2Handler);
	
	while(1)
	{
		getMPU6050Data(&x, &y, &z);
		g_onSensor[g_scene](x, y, z);
	}
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
			briupLcdShowStr(x, y + (i << 1), items[i], 32, 1, BLUE, WHITE); 
			briupLcdFastDrawDirection(64, 256, (y + (i << 1)) * 32, (y + (i << 1) + 1) * 32, BLACK, 0);
		}else
		{
			briupLcdShowStr(x, y + (i << 1), items[i], 32, 0, BLACK, BLUE);
			briupLcdFastDrawDirection(64, 256, (y + (i << 1)) * 32, (y + (i << 1) + 1) * 32, WHITE, 0);
		}
	}
}

