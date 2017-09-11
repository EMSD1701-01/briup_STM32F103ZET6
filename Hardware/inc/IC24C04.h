//24c04部分初始化函数 IIc2
#ifndef _IC24C04_H_
#define _IC24C04_H_

#ifndef _cplusplus
typedef enum {FL = 0,TU = !FL }bool;
#endif

#include <stm32f10x.h>
#include "briupDelay.h"

#define I2SCL_H GPIOB->IDR |= 1<<6;
#define I2SCL_L GPIOB->IDR |= 0<<6;
#define I2SDA_H GPIOB->IDR |= 1<<7;
#define I2SDA_L GPIOB->IDR |= 0<<7;

#define I2CSCL_read  (GPIOB->IDR & ~(0<<6));
#define I2CSDA_read  (GPIOB->IDR & ~(0<<7));

#define I2C2_PageSize 8 //24c02每页8字节 

//IO的初始化
void C04Init(void);
//
bool I2C_WriteByte(u8 sendByte,u16 WriteAddress,u8 DeviceAddress);
//
bool I2C_BufferWrite(u8* pBuffer,u8 length,u16 WriteAddress,u8 DeviceAddress);
//
void I2C_PageWrite(u8* pBuffer,u8 length,u16 WriteAddress,u8 DeviceAddress);
//
bool I2C_ReadByte(u8* pBuffer,u8 length,u16 ReadAddress,u8 DeviceAddress);
//
bool I2C_SendStr(u8* pBuffer,u8 length,u16 WriteAddress,u8 DeviceAddress);//0xae
//
bool I2C_ReadStr(u8* pBuffer,u8 length,u16 ReadAddress,u8 DeviceAddress);


#endif

