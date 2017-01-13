/**
* @file gpio.c
* @brief driver layer for the gpio
*/
 
#include <stm32f10x_gpio.h>
#include "gpio.h"

/********************************/
/*       Public Functions       */
/********************************/

/**
* @brief GPIO initialization
* @param GPIOx GPIO number
* @param GPIO_Pin GPIO pin
* @param GPIO_Mode GPIO mode
* @retval None
*/
void GPIO_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode){
	 GPIO_InitTypeDef gpioStructure;
    gpioStructure.GPIO_Pin = GPIO_Pin;
    gpioStructure.GPIO_Mode = GPIO_Mode;
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &gpioStructure);
}

/**
* @brief set GPIO pin to 1
* @param GPIOx GPIO number
* @param GPIO_Pin GPIO pin
* @retval None
*/
void GPIO_set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_SET); 
}

/**
* @brief set GPIO pin to 0
* @param GPIOx GPIO number
* @param GPIO_Pin GPIO pin
* @retval None
*/
void GPIO_reset(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	GPIO_WriteBit(GPIOx, GPIO_Pin, Bit_RESET); 
}


