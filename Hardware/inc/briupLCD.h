#ifndef __BALLANCE_LCD_H__
#define __BALLANCE_LCD_H__

#include <stm32f10x.h>

//是否使用横屏
#define USE_HORIZONTAL 0

//屏幕参数结构体定义
typedef struct
{
	u16 width;	//屏幕宽度 320
	u16 height; //屏幕高度 480
	u16 id;		//屏幕标识符
	u8 dir;		//屏幕方向
	u8 wramcmd; //写RAM命令
	u8 setxcmd; //设置横坐标命令
	u8 setycmd; //设置纵坐标命令
}_lcd_dev;

extern _lcd_dev lcddev;
extern u16 POINT_COLOR;
extern u16 BACK_COLOR;

#define LCD_LED_ON()	GPIOB->ODR |= 0x01;
#define LCD_LED_OFF()	GPIOB->ODR &= ~0x01;
#define LCD_WIDTH_MAX	320
#define LCD_HIGH_MAX	480

//LCD地址结构体
typedef struct
{
	u16 LCD_REG;	//Register
	u16 LCD_RAM;	//随机访问存储器
} LCD_TypeDef;
//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 111110=0X3E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

#define	LCD_RST_SET  GPIOC->BSRR=1<<5    //复位			PC5
#define	LCD_RST_CLR  GPIOC->BRR=1<<5    //复位			PC5


//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0xF800 
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0x001F
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0X457 
#define BRRED 			0XFC07 
#define GRAY  			0X8430 
//GUI

#define DARKBLUE      	 0X01CF	
#define LIGHTBLUE      	 0X7D7C	
#define GRAYBLUE       	 0X5458 

#define LIGHTGREEN     	0X841F 
//#define LIGHTGRAY     0XEF5B 
#define LGRAY 			 		0XC618 

#define LGRAYBLUE      	0XA651 
#define LBBLUE          0X2B12 

void briupLcdInit(void);	//液晶屏初始化函数
void briupLcdDisplayOn(void);	//打开显示模式								//开显示
void briupLcdDisplayOff(void);  //关显示
void briupLcdClear(u16 Color);	 												//清屏

//快速画矩形
void briupLcdFastDrawDirection(u16 x1, u16 x2, u16 y1,u16 y2,u16 color, u8 full);
//快速画点
void briupLcdFastDrawPoint(u16 x, u16 y, u16 color);
//快速画线
void briupLcdFastDrawLine(u16 x1, u16 y1,u16 x2, u16 y2, u16 color);
//快速画圆
void briupLcdFastDrawCircle( u16 x, u16 y, u16 r, u16 color, u8 full);

//向LCD中写入数据
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
//读取LCD指定寄存器的数据
u16 LCD_ReadReg(u8 LCD_Reg);

//显示字符串
void briupLcdShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 point_colar,u16 back_colar);
//显示数字
void briupLcdShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);

#endif
