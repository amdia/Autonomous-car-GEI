#include <stm32f10x_gpio.h>
#include "gpio.h"

void GPIO_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode){
	 GPIO_InitTypeDef gpioStructure;
    gpioStructure.GPIO_Pin = GPIO_Pin;
    gpioStructure.GPIO_Mode = GPIO_Mode;
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &gpioStructure);
}

void GPIO_set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET); 
}

void GPIO_reset(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET); 
}


