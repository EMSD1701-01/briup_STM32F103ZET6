/****************************************
* File Name: briupUsart.c
* Date: 2017年8月25日 17点06分
* Author: muxiaozi
* Description: 串口初始化接口、数据发送/接收实现文件
****************************************/
#include "briupUsart.h"
#include "briupNVIC.h"

//开启或关闭printf输出重定向
#if 1

//使用半主机模式
#pragma import( __use_no_semihosting)

struct __FILE{
	int handle;
};

FILE __stdout;
_sys_exit(int x)
{
	x = x;
}

/**
 * fputc输出重定向
 * @param ch 要发送的字符
 * @param f 标准输出流
 */
int fputc(int ch, FILE *f)
{
	usart1PutChar(ch);
	return ch;
}

#endif

/**
 * 初始化基础外设函数接口
 * @param bound 需要设置的串口波特率
 */
void usart1Init(u32 bound)
{
	//计算波特率寄存器的值
	double temp = 72000000.0 / (16.0 * bound);
	u16 mantissa = (u16)temp;
	u16 fraction = (temp - mantissa) * 16;
	mantissa = (mantissa << 4) + fraction;
	
	//IO寄存器配置
	//使能GPIOCA/USART1时钟控制
	RCC->APB2ENR |= 0x1<<2 | 0x1<<14;
	
	//Tx-> GPIOA Pin.9	推挽复用输出
	//Rx-> GPIOA Pin.10	复用上拉输入
	GPIOA->CRH &= 0xfffff00f;
	GPIOA->CRH |= 0xb<<4;
	GPIOA->CRH |= 0x8<<8;
	GPIOA->ODR |= 0x1<<10;
	
	//USART1寄存器配置
	USART1->BRR = mantissa;
	USART1->CR1 |= 1<<13 | 1<<3 | 1<<2;
	
	//USART1中断配置
	//接收缓存区非空中断
	USART1->CR1 |= 1 << 5;
	
	//NVICPriorityConfig(3, 3, USART1_IRQn);
	NVIC_SetPriorityGrouping(5);
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(5, 1, 1));
	NVIC_EnableIRQ(USART1_IRQn);
}

/**
 * 通过串口向上位机发送一个字节
 * @param ch 发送的字节
 */
void usart1PutChar(char ch)
{
	//通过状态位检测前一次是否发送成功
	while(!(USART1->SR & (1<<6)));
	//将待发送数据放入数据寄存器
	USART1->DR = ch;
}

/**
 * 通过串口向上位机发送一个字符串
 * @param str 发送的字符串
 */
void usart1PutStr(char *str)
{
	while(*str != '\0' && *str != '\n')
	{
		usart1PutChar(*str++);
	}
	usart1PutChar('\n');
}

/**
 * 通过串口同步接收一字节数据，阻塞
 * @return 接收到的数据
 */
char usart1GetChar(void)
{
	//判断当前寄存器中是否有数据
	while(!(USART1->SR & 1<<5));
	//从数据寄存器得到数据
	return USART1->DR;
}

/**
 * 通过串口同步接收一个字符串，阻塞
 * @param buf 接收数据的缓存区
 * @return 接收到的字符串
 */
char *usart1GetStr(char *buf)
{
	u8 index = 0;
	do{
		buf[index++] = usart1GetChar();
	}while(buf[index - 1] != '\0' && buf[index - 1] != '\n');
	buf[index] = '\0';
	return buf;
}

/**
 * 通过串口异步接收一字节数据，非阻塞
 * @return 接收到的数据
 */
char usart1GetCharAsyn(void)
{
	return (USART1->SR & 1<<5) ? USART1->DR : '\0';
}

/**
 * 通过串口异步接收一个字符串，非阻塞
 * @param buf 接收数据的缓存区
 * @return 接收到的字符串
 */
char *usart1GetStrAsyn(char *buf)
{
	u8 index = 0;
	do{
		buf[index++] = usart1GetCharAsyn();
	}while(buf[index - 1] != '\0' && buf[index - 1] != '\n');
	buf[index] = '\0';
	return buf;
}

/**
 * 串口1中断服务函数
 */
void USART1_IRQHandler()
{
	//判断是否是接收寄存器非空引发的中断
	if(USART1->SR & 1<<5)
	{
		char buf[64];
		printf("From stm32: %s \n", usart1GetStr(buf));
	}
}
