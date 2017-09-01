/****************************************
* File Name: briupFSMC.c
* Date: 2017年9月1日 17点03分
* Author: muxiaozi
* Description: FSMC实现文件
****************************************/
#include "briupFSMC.h"

#include "briupNVIC.h"
#include "briupDelay.h"
#include "briupUsart.h"

/**
 * FSMC初始化
 */
void FSMCInit(void)
{
	//使能FSMC
	RCC->AHBENR |= 1<<8;
	
	//使能GPIO时钟
	RCC->APB2ENR |= 1<<3 | 1<<5 | 1<<6 | 1<<8;
	
	//GPIOB PB.0
	GPIOB->CRL &= ~0x0f;
	GPIOB->CRL |= 0x03;
	
	//GPIOD PD.4.5.8.9.10.14.15
	GPIOD->CRL &= 0xff00ff00;
	GPIOD->CRL |= 0x00bb00bb;
	GPIOD->CRH &= 0x00fff000;
	GPIOD->CRH |= 0xbb000bbb;
	
	//GPIOG PG.7~15
	GPIOE->CRL &= 0x0fffffff;
	GPIOE->CRL |= 0xb0000000;
	GPIOE->CRH = 0xbbbbbbbb;
	
	//GPIOG PG.0/12
	GPIOG->CRL &= ~0xf;
	GPIOG->CRL |= 0x0b;
	GPIOG->CRH &= 0xfff0ffff;
	GPIOG->CRH |= 0x000b0000;
	
	//FSMC寄存器配置
	FSMC_Bank1->BTCR[6] = 0;	//FSMC_BCR4
	FSMC_Bank1->BTCR[7] = 0;	//FSMC_BTR4
	FSMC_Bank1E->BWTR[6] = 0;	//FSMC_BWTR4
	
	FSMC_Bank1->BTCR[6] = 1<<14 | 1<<12 | 1<<4;
	FSMC_Bank1->BTCR[7] = 0x0f<<8 | 0x01;
	
	FSMC_Bank1E->BWTR[6] = 0x03<<8;
	
	FSMC_Bank1->BTCR[6] |= 0x01;
	delay_ms(50);
}

