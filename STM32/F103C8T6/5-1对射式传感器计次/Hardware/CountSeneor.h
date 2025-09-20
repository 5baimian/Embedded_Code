#include "stm32f10x.h"                  // Device header

#ifndef __COUNTSENSOR_H
#define __COUNTSENSOR_H

void CountSensor_Init(void);
uint16_t CountSensor_Get(void);

#endif
