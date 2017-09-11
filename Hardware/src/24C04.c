//24c04实现文件   IIc2

#include "IC24C04.h"

//IO的使能
void C04Init()
{

	//使能I2c2
	RCC->APB1ENR |= 1<<21;
	//使能GPIOB
	RCC->APB2ENR |= 1<<3;
	//设置GPIOB 6（SCL） 7（SCDA） 8 9通用开漏
	//GPIOB->CRL |= 0x00FFFFF;
	//GPIOB->CRL |= 0x77<<23;	
}
void I2C_delay(void)
{
	u8 i = 100;//速度的设置，最低速度为5
	while(i)
	{
		i--;
	}
}
/*************************************************/
bool I2C_Start(void)
{
	I2SDA_H;
	I2SCL_H;
	I2C_delay();
	if(!(GPIOB->IDR&(0<<7)))
		return FL; //SDA为低电平时退出
	I2SDA_L;
	I2C_delay();
	if((GPIOB->IDR|(1<<7)))
		return FL;//SDA为高电平总线忙，退出
	I2SDA_L;
	I2C_delay();
	return TU;
}
void I2C_Stop(void)
{
	I2SCL_L;
	I2C_delay();
	I2SDA_L;
	I2C_delay();
	I2SCL_H;
	I2C_delay();
	I2SDA_H;
	I2C_delay();
}
void I2C_Ack(void)
{
	I2SCL_L;
	I2C_delay();
	I2SDA_L;
	I2C_delay();
	I2SCL_H;
	I2C_delay();
	I2SCL_H;
	I2C_delay();	
}
void I2C_NoAck(void)
{
	I2SCL_L;
	I2C_delay();
	I2SDA_H;
	I2C_delay();
	I2SCL_H;
	I2C_delay();
	I2SCL_L;
	I2C_delay();
	
}
//返回为1时有ACK，0无ACK
bool I2C_WaitAck(void)
{
	I2SCL_L;
	I2C_delay();
	I2C_delay();
	I2SDA_H;
	I2C_delay();
	if((GPIOB->IDR|(1<<7)))
	{
		I2SCL_L;
		return FL;
	}
	I2SCL_L;
	return TU;
}
void I2C2_SendByte(u8 SendByte)
{
	u8 i = 8;
	while(i--)
	{
		I2SCL_L;
		I2C_delay();
		if(SendByte&0x80)
			{I2SDA_H;}
		else
			{
				I2SDA_L;
				SendByte<<=1;
				I2C_delay();
				I2SCL_H;
				I2C_delay();
			}			
		}
		I2SCL_L;	
}

u8 I2C_ReceiveByte(void)
{
	u8 i = 8;
	u8 ReceiveBYte = 0;
	I2SDA_H;
	while(i--)
	{
		ReceiveBYte <<= 1;
		I2SCL_L;
		I2C_delay();
		I2SCL_H;
		I2C_delay();
		if(GPIOB->IDR|(1<<7))
		{
			ReceiveBYte |= 0x01;
		}
	}
	I2SCL_L;
	return ReceiveBYte;
}
//IO的初始化
void C04Init(void);
//
bool I2C_WriteByte(u8 sendByte,u16 WriteAddress,u8 DeviceAddress)
{
	if(!I2C_Start())
		return FL;
	I2C2_SendByte((((WriteAddress&0x0700)>>7)| DeviceAddress) & 0xFFFE);
	if(!I2C_WaitAck())
	{
			I2C_Stop();
			return FL;
	}
	I2C2_SendByte((u8)(WriteAddress&0x00FF));
	I2C_WaitAck();
	I2C_Stop();
	delay_ms(10);
	return TU;
}
//
bool I2C_BufferWrite(u8* pBuffer,u8 length,u16 WriteAddress,u8 DeviceAddress)
{
	if(!I2C_Start())
		return FL;
	I2C2_SendByte((((WriteAddress&0x0700)>>7)| DeviceAddress) & 0xFFFE);
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return FL;
	}
	I2C2_SendByte((u8)(WriteAddress&0x00FF));
	I2C_WaitAck();
	
	while(length--)
	{
		I2C2_SendByte(*pBuffer);
		I2C_WaitAck();
		pBuffer++;
	}
	I2C_Stop();
	delay_ms(10);
	return TU;
}
//
void I2C_PageWrite(u8* pBuffer,u8 length,u16 WriteAddress,u8 DeviceAddress)
{
	u8 NumOfPage = 0,NumOfSingle = 0,Addr = 0,count = 0;
	Addr = WriteAddress % I2C2_PageSize;
	count  = I2C2_PageSize - Addr;
	NumOfPage = length/I2C2_PageSize;
	NumOfSingle = length%I2C2_PageSize;
	
	if(Addr == 0)
	{
		if(NumOfPage == 0)
		{
			I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);
		}
		else{
			while(NumOfPage)
			{
				I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);
				WriteAddress += I2C2_PageSize;
				pBuffer += I2C2_PageSize;
				NumOfPage--;
				delay_ms(10);
			}
			if(NumOfPage != 0)
			{
				I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);
				delay_ms(10);
			}
		}
	}
	else{
		if(NumOfPage == 0)
		{
			I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);
		}
		else{
			length -= count;
			NumOfPage  = length/I2C2_PageSize;
			NumOfSingle = length % I2C2_PageSize;
			if (count == 0)
			{
				I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);
				WriteAddress += count;
				pBuffer += count;
			}
			while(NumOfPage--)
			{
				I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);
				WriteAddress += I2C2_PageSize;
				pBuffer += I2C2_PageSize;
			}
			if(NumOfSingle != 0)
			{
				I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);
			}
		}
	}	
}
//
bool I2C_ReadByte(u8* pBuffer,u8 length,u16 ReadAddress,u8 DeviceAddress)
{
	if(!I2C_Start())
		return FL;
	I2C2_SendByte((((ReadAddress & 0x0700) >>7) | DeviceAddress)&0xFFFE);
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return FL;
	}
	I2C2_SendByte((u8)(ReadAddress&0x00FF));
	I2C_WaitAck();
	I2C_Start();
	I2C2_SendByte((((ReadAddress & 0x0700) >>7) | DeviceAddress)&0x0001);
	I2C_WaitAck();
	while(length)
	{
		*pBuffer = I2C_ReceiveByte();
		if(length == 1) I2C_NoAck();
		else I2C_Ack();
		pBuffer++;
		length--;
	}
	I2C_Stop();
	return TU;
}

//
bool I2C_SendStr(u8* pBuffer,u8 length,u16 WriteAddress,u8 DeviceAddress)
{
int i;
	for(i = 0;i < length;i++)
	{
		if(!I2C_Start())		
			return FL;
		I2C2_SendByte(DeviceAddress);
		if(!I2C_WaitAck())
		{
			I2C_Stop();
			return FL;
		}
		I2C2_SendByte(WriteAddress);
		I2C_WaitAck();
		I2C2_SendByte(*pBuffer);
		I2C_WaitAck();
		I2C_Stop();
		delay_ms(10);
		WriteAddress++;
		pBuffer++;
	}
	return TU;
}
//
bool I2C_ReadStr(u8* pBuffer,u8 length,u16 ReadAddress,u8 DeviceAddress)
{
	int i;
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return FL;
	}
	I2C2_SendByte(ReadAddress);
	if(!I2C_WaitAck())
	{
		I2C_Stop();
		return FL;
	}
	I2C_Start();
	I2C2_SendByte(DeviceAddress+1);
	I2C_WaitAck();
	
	for(i=0;i<length-1;i++)
	{
		*pBuffer = I2C_ReceiveByte();  
	  I2C_Ack();   
		pBuffer++;  
	}
	*pBuffer = I2C_ReceiveByte();
		I2C_Ack();
		I2C_Stop();
		return TU;
}

