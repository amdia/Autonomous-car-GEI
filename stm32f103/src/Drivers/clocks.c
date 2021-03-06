/**
* @file clocks.c
* @brief Driver layer for the peripherals clocks
*/

#include "clocks.h"
#include <stm32f10x.h>

/**
* @brief Enable all the peripherals clocks
*/
void clocks_init(void){
	// Enable the SPI2 periph
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	// Enable all GPIO ports
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	// Enable all timers
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	// Enable alternate functions
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
}
