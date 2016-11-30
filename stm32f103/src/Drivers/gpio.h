#ifndef __GPIO_H
#define __GPIO_H
#include <stm32f10x.h>

void GPIO_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode);

void GPIO_set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

void GPIO_reset(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif //__GPIO_H

