/****************************************
* File Name: briupUsart.h
* Date: 2017年8月25日 16点56分
* Author: muxiaozi
* Description: 串口初始化接口、数据发送/接收申明
****************************************/
#ifndef __USART_H__
#define __USART_H__

#include <stdio.h>
#include <stm32f10x.h>

/**
 * 初始化基础外设函数接口
 * @param bound 需要设置的串口波特率
 */
void usart1Init(u32 bound);

/**
 * 通过串口向上位机发送一个字节
 * @param ch 发送的字节
 */
void usart1PutChar(char ch);

/**
 * 通过串口向上位机发送一个字符串
 * @param str 发送的字符串
 */
void usart1PutStr(char *str);

/**
 * 通过串口同步接收一字节数据，阻塞
 * @return 接收到的数据
 */
char usart1GetChar(void);

/**
 * 通过串口同步接收一个字符串，阻塞
 * @param buf 接收数据的缓存区
 * @return 接收到的字符串
 */
char *usart1GetStr(char *buf);

/**
 * 通过串口异步接收一字节数据，非阻塞
 * @return 接收到的数据
 */
char usart1GetCharAsyn(void);

/**
 * 通过串口异步接收一个字符串，非阻塞
 * @param buf 接收数据的缓存区
 * @return 接收到的字符串
 */
char *usart1GetStrAsyn(char *buf);



#endif //__USART_H__
