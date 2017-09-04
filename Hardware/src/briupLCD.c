#include "briupLCD.h"
#include "briupLCDFont.h"
#include "briupDelay.h"
#include "briupUsart.h"
#include "briupFsmc.h"

//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 

//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;
	
		   
//写寄存器函数
//regval:寄存器值
void LCD_WR_REG(u16 regval)
{ 
	LCD->LCD_REG=regval;//写入要写的寄存器序号	 
}
//写LCD数据
//data:要写入的值
void LCD_WR_DATA(u16 data)
{										    	   
	LCD->LCD_RAM=data;		 
}
//读LCD数据
//返回值:读到的值
u16 LCD_RD_DATA(void)
{										    	   
	return LCD->LCD_RAM;		 
}					   
//写寄存器
//LCD_Reg:寄存器地址
//LCD_RegValue:要写入的数据
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;		//写入要写的寄存器序号	 
	LCD->LCD_RAM = LCD_RegValue;//写入数据	    		 
}	   
//读寄存器
//LCD_Reg:寄存器地址
//返回值:读到的数据
u16 LCD_ReadReg(u8 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		//写入要读的寄存器序号
	delay_us(3);
	return LCD_RD_DATA();		//返回读到的值
}   


void  briupLcdInit(void)
{
	FSMCInit();
	lcddev.id = 0;
	
	LCD_WR_REG( 0x00b0);
	LCD_WR_DATA( 0x00);
	
	LCD_WR_REG( 0x00d3);
	LCD_RD_DATA();
	LCD_RD_DATA();
	lcddev.id=LCD_RD_DATA();
	lcddev.id<<=8;
	lcddev.id|=LCD_RD_DATA();
	printf("%x\r\n", lcddev.id);
	
	LCD_WR_REG(0xC0);  		//电源控制
	LCD_WR_DATA(0x0a);     //1e  contrast
	LCD_WR_DATA(0x0a);     //1e  contrast
	
	LCD_WR_REG(0xC1);				//	电源控制
	LCD_WR_DATA(0x44);    //41
	
	LCD_WR_REG(0XC5);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x09);  //vcom  10
	
	LCD_WR_REG(0xB1);				//帧速率控制
	LCD_WR_DATA(0x90);			//56HZ
	LCD_WR_DATA(0x11);			//25 clocks
	
	LCD_WR_REG(0xB4);			//	显示反转控制
	LCD_WR_DATA(0x02);
	
	LCD_WR_REG(0xB7);			//输入模式设置！！！！！！！
	LCD_WR_DATA(0xC6);
	
	LCD_WR_REG(0xB6);		//	显示功能控制
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x22);//0 GS SS SM ISC[3:0];??GS SS??????,????R36
	LCD_WR_DATA(0x3B);

	LCD_WR_REG(0xE0);			//图像灰度控制
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x3F);
	LCD_WR_DATA(0xAC);
	LCD_WR_DATA(0x4F);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x24);
	LCD_WR_DATA(0x0F);
	
	LCD_WR_REG(0XE1);			//消除伽马矫正
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x1B);
	LCD_WR_DATA(0x1E);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x30);
	LCD_WR_DATA(0xff);
	LCD_WR_DATA(0x40);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x3B);
	LCD_WR_DATA(0x0F);
	
	LCD_WR_REG(0XF2);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0xA3);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0xB2);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x00);
	
	LCD_WR_REG(0XF7);
	LCD_WR_DATA(0xA9);
	LCD_WR_DATA(0x91);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x4F);
	
	LCD_WR_REG(0XFB);
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x04);
	
	LCD_WR_REG(0x36);				//设置扫描方式
	LCD_WR_DATA(0x00);		 //88 48   68   ??????
	
	LCD_WR_REG(0x3A);			//	接口像素格式。选择16位的接口模式
	LCD_WR_DATA(0x55);
	
	LCD_WR_REG(0xF9);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x08);  
	
	LCD_WR_REG(0xF4);  
	LCD_WR_DATA(0x00);  
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x08);  
	LCD_WR_DATA(0x91); 
	LCD_WR_DATA(0x04);
	LCD_WR_REG(0x11);
	
	delay_ms(120);
	LCD_WR_REG(0x29);
	
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1	//使用横屏	  
	lcddev.dir=1;//横屏
	lcddev.width=480;
	lcddev.height=320;			
	LCD_WriteReg(0x36,0x31);
#else//竖屏
	lcddev.dir=0;//竖屏				 	 		
	lcddev.width=320;
	lcddev.height=480;	
	LCD_WriteReg(0x36,0x08); //0x08
#endif
	
	LCD_LED_ON();
	briupLcdClear( 0xeed3);
}

//LCD_DisplayOn
void briupLcdDisplayOn(void)
{
	 LCD_WriteReg(0x0029,0);
}
//LCD_Displayoff
void briupLcdDisplayOff(void)
{
	LCD_WriteReg(0x0028,0);
}

void briupLcdClear(u16 Color)
{
	BACK_COLOR = Color;
	briupLcdFastDrawDirection( 0, lcddev.width-1, 0,lcddev.height-1, Color, 1);
}

//快速画点
void briupLcdFastDrawPoint(u16 x, u16 y, u16 color)
{
	LCD->LCD_REG = 0x2a;	//命令！
	LCD->LCD_RAM = x >> 8;
	LCD->LCD_RAM = x;
	LCD->LCD_RAM = x >> 8;
	LCD->LCD_RAM = x;
	LCD->LCD_REG = 0x2b;
	LCD->LCD_RAM = y >> 8;
	LCD->LCD_RAM = y;
	LCD->LCD_RAM = y >> 8;
	LCD->LCD_RAM = y;
	
	LCD->LCD_REG= 0x2c;
	LCD->LCD_RAM=color;
}

//快速画线
void briupLcdFastDrawLine(u16 x1, u16 y1,u16 x2, u16 y2, u16 color)
{
	int dx = x2-x1;
	int dy = y2-y1;
	int y = y1;
	int eps = 0, i;
	
	LCD->LCD_REG = 0x2a;	//命令！
	LCD->LCD_RAM = x1 >> 8;
	LCD->LCD_RAM = x1;
	LCD->LCD_RAM = x2 >> 8;
	LCD->LCD_RAM = x2;
	LCD->LCD_REG = 0x2b;
	LCD->LCD_RAM = y1 >> 8;
	LCD->LCD_RAM = y1;
	LCD->LCD_RAM = y2 >> 8;
	LCD->LCD_RAM = y2;
	
	LCD->LCD_REG= 0x2c;
	if(dx == 0)
		for( i = y1; i <= y2; i++)
			LCD->LCD_RAM = color;
	else if( dy == 0)
		for( i = x1; i <= x2; i++)
			LCD->LCD_RAM = color;
	else
		for( i = x1; i <= x2; i++)
		{
			LCD->LCD_RAM = color;
			eps+= dy;
			if( (eps << 1) >= dx)
			{
				y++;
				eps -= dx;
			}
		}
}


//快速画矩形
void briupLcdFastDrawDirection(u16 x1, u16 x2, u16 y1,u16 y2,u16 color, u8 full)
{
	u16 i,j;
	
	if( full == 1)
	{
		LCD->LCD_REG = 0x2a;
		LCD->LCD_RAM = x1 >> 8;
		LCD->LCD_RAM = x1;
		LCD->LCD_RAM = x2 >> 8;
		LCD->LCD_RAM = x2;
		LCD->LCD_REG = 0x2b;
		LCD->LCD_RAM = y1 >> 8;
		LCD->LCD_RAM = y1;
		LCD->LCD_RAM = y2 >> 8;
		LCD->LCD_RAM = y2;
		
		LCD->LCD_REG= 0x2c;
		for(i = x1;i <= x2;i++)
			for(j = y1; j <= y2; j++)
				LCD->LCD_RAM=color;
	}else
	{
		//先画横线
		LCD->LCD_REG = 0x2a;
		LCD->LCD_RAM = x1 >> 8;
		LCD->LCD_RAM = x1;
		LCD->LCD_RAM = x2 >> 8;
		LCD->LCD_RAM = x2;
		LCD->LCD_REG = 0x2b;
		LCD->LCD_RAM = y1 >> 8;
		LCD->LCD_RAM = y1;
		LCD->LCD_RAM = y1 >> 8;
		LCD->LCD_RAM = y1;
		
		LCD->LCD_REG= 0x2c;
		for(i = x1; i <= x2; i++)
			LCD->LCD_RAM=color;
		
		LCD->LCD_REG = 0x2b;
		LCD->LCD_RAM = y2 >> 8;
		LCD->LCD_RAM = y2;
		LCD->LCD_RAM = y2 >> 8;
		LCD->LCD_RAM = y2;
		
		LCD->LCD_REG= 0x2c;
		for(i = x1; i <= x2; i++)
			LCD->LCD_RAM=color;
		
		//再画竖线
		LCD->LCD_REG = 0x2b;
		LCD->LCD_RAM = y1 >> 8;
		LCD->LCD_RAM = y1;
		LCD->LCD_RAM = y2 >> 8;
		LCD->LCD_RAM = y2;
		LCD->LCD_REG = 0x2a;
		LCD->LCD_RAM = x1 >> 8;
		LCD->LCD_RAM = x1;
		LCD->LCD_RAM = x1 >> 8;
		LCD->LCD_RAM = x1;
		
		LCD->LCD_REG= 0x2c;
		for(i = y1; i <= y2; i++)
			LCD->LCD_RAM=color;
		
		LCD->LCD_REG = 0x2a;
		LCD->LCD_RAM = x2 >> 8;
		LCD->LCD_RAM = x2;
		LCD->LCD_RAM = x2 >> 8;
		LCD->LCD_RAM = x2;
		
		LCD->LCD_REG= 0x2c;
		for(i = y1; i <= y2; i++)
			LCD->LCD_RAM=color;
	}
}

void briupLcdFastDrawCircle( u16 xc, u16 yc, u16 r, u16 color, u8 full)
{
	int x = 0, y = r, yi, d;

	d = 3 - 2 * r;

	if (full) 
	{
		// 如果填充（画实心圆）
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
			{
				briupLcdFastDrawPoint(xc + x, yc + y, color);
				briupLcdFastDrawPoint(xc - x, yc + y, color);
				briupLcdFastDrawPoint(xc + x, yc - y, color);
				briupLcdFastDrawPoint(xc - x, yc - y, color);
				briupLcdFastDrawPoint(xc + y, yc + x, color);
				briupLcdFastDrawPoint(xc - y, yc + x, color);
				briupLcdFastDrawPoint(xc + y, yc - x, color);
				briupLcdFastDrawPoint(xc - y, yc - x, color);
			}

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		// 如果不填充（画空心圆）
		while (x <= y) {
			briupLcdFastDrawPoint(xc + x, yc + y, color);
			briupLcdFastDrawPoint(xc - x, yc + y, color);
			briupLcdFastDrawPoint(xc + x, yc - y, color);
			briupLcdFastDrawPoint(xc - x, yc - y, color);
			briupLcdFastDrawPoint(xc + y, yc + x, color);
			briupLcdFastDrawPoint(xc - y, yc + x, color);
			briupLcdFastDrawPoint(xc + y, yc - x, color);
			briupLcdFastDrawPoint(xc - y, yc - x, color);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

//=======================================================================================
//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16
//mode:叠加方式(1)还是非叠加方式(0)
void briupLcdShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode,u16 point_colar,u16 back_colar)
{
	u8 temp=0,t1,t,size_x=0;
	u16 Supplementary_data_x = 0;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	if(!mode) //非叠加方式
	{
				if(size == 12)size_x = 12;  //调用1206字体
				if(size == 16)size_x = 16;	//调用1608字体 	                          
				if(size == 32){size_x = 64;Supplementary_data_x=960;}	//调用3210字体 
		for(t=0;t<size_x;t++)
	    {   
				if(size == 12)temp=asc2_1206[num][t];  //调用1206字体
				if(size == 16)temp=asc2_1608[num][t];	 //调用1608字体 	                          
				if(size == 32)temp=asc2_3210[num][t];	 //调用3210字体
				for(t1=0;t1<8;t1++)
				{			    
					if(temp&0x80)POINT_COLOR=colortemp;
					else POINT_COLOR=BACK_COLOR;
					briupLcdFastDrawPoint( x, y, POINT_COLOR);	
					temp<<=1;
					y++;
					if(x>=lcddev.width+Supplementary_data_x){POINT_COLOR=colortemp;return;}//超区域了
					if((y-y0)==size)
					{
						y=y0;
						x++;
						if(x>=lcddev.width+Supplementary_data_x){POINT_COLOR=colortemp;return;}//超区域了
						break;
					}
				}  	 
	    }    
	}else//叠加方式
	{
			if(size == 12)size_x = 12;  //调用1206字体
			if(size == 16)size_x = 16;	//调用1608字体 	                          
			if(size == 32){size_x = 64;Supplementary_data_x=960;}	//调用3210字体 
	    for(t=0;t<size_x;t++)
	    {   
				if(size == 12)temp=asc2_1206[num][t];  //调用1206字体
				if(size == 16)temp=asc2_1608[num][t];	 //调用1608字体 	                          
				if(size == 32)temp=asc2_3210[num][t];	 //调用3210字体                          
				for(t1=0;t1<8;t1++)
				{			    
					if(temp&0x80)briupLcdFastDrawPoint( x, y, point_colar);
					else briupLcdFastDrawPoint( x, y, back_colar);
					temp<<=1;
					y++;
					if(x>=lcddev.height+Supplementary_data_x){POINT_COLOR=colortemp;return;}//超区域了
					if((y-y0)==size)
					{
						y=y0;
						x++;
						if(x>=lcddev.width+Supplementary_data_x){POINT_COLOR=colortemp;return;}//超区域了
						break;
					}
				}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   

//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);
//len:长度(即要显示的位数)
//size:字体大小 12 / 16
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void briupLcdShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)briupLcdShowChar(x+(size/2)*t,y,'0',size,mode&0X01,POINT_COLOR,0xffff);  
				else briupLcdShowChar(x+(size/2)*t,y,' ',size,mode&0X01,POINT_COLOR,0xffff);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	briupLcdShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01,POINT_COLOR,0xffff); 
	}
}

/**
 * LCD显示图片
 * @param img 图片结构体
 * @param imgW 图片宽度
 * @param imgH图片高度
 * @param localX 横坐标
 * @param localY 纵坐标
 * @param imgArr 图片数据
 */
void briupLcdImageInit(Image_TypeDef * img, u16 imgW, u16 imgH, u16 localX, u16 localY, \
						unsigned char* imgArr)
{
	img->imgH = imgH;
	img->imgW = imgW;
	img->localX = localX;
	img->localY = localY;
	img->imgArr = imgArr;
}

/**
 * 图片显示设置
 */
void briupLcdImageDraw(Image_TypeDef *img, u8 mode)
{
	u16 imgColor;
	u32 i, j;
	
	//设置横向显示区域（列宽）
	LCD->LCD_REG = 0x2a;
	//设置起始列
	LCD->LCD_RAM = img->localX >> 8;
	LCD->LCD_RAM = img->localX & 0xff;
	//设置结束列
	LCD->LCD_RAM = (img->localX + img->imgW - 1) >> 8;
	LCD->LCD_RAM = (img->localX + img->imgW - 1) & 0xff;
	
	//设置纵向显示区域（行高）
	LCD->LCD_REG = 0x2b;
	//设置起始列
	LCD->LCD_RAM = img->localY >> 8;
	LCD->LCD_RAM = img->localY & 0xff;
	//设置结束列
	LCD->LCD_RAM = (img->localY + img->imgH) >> 8;
	LCD->LCD_RAM = (img->localY + img->imgH) & 0xff;
	
	//发送图片数据
	LCD->LCD_REG = 0x2c;
	//顺序将图像数据组合后发送
	for(i = 0; i < img->imgH * img->imgW; i++)
	{
		LCD->LCD_RAM = ((u16*)img->imgArr)[i];
	}
	
//	for(i = 0; i < img->imgH; i++)
//	{
//		for(j = 0; j < img->imgW; j++)
//		{
//			imgColor = img->imgArr[((j + i * img->imgW) << 1) + 1] << 8;
//			imgColor |= img->imgArr[(j + i * img->imgW) << 1];
//			LCD->LCD_RAM = imgColor;
//		}
//	}
}

