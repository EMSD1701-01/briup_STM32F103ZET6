#ifndef __MCU6050_H__
#define __MCU6050_H__

#include <stm32f10x.h>
#include <math.h>
#include "briupDelay.h"
#include "briupUsart.h"
#include "inv_mpu.h"
#include "briupMPUDriver.h"

#define q30  1073741824.0f

void briupMPU6050Init(void);

void getMPU6050Data(short * x, short * y);

#endif


