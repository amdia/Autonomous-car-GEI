 /**
* @file timer.c
* @brief Driver layer for the timers
*/
 
 #include <misc.h>
 #include <stm32f10x.h>
 #include "timer.h"
 #include "NVIC_priorities.h"
	
/********************************/
/*       Public Functions       */
/********************************/
	
/**
 * @brief  timer initialization
 * @param  timer Timer number
 * @param  counter_clock_frequency Counter clock frequency
 * @param  period_us Timer period in micro-seconds
 */

void timer_init(TIM_TypeDef* timer, int counter_clock_frequency, int period_us){
	TIM_TimeBaseInitTypeDef timeBaseInit;
	uint16_t prescalerVal = 0;

	prescalerVal = (uint16_t)(SystemCoreClock / counter_clock_frequency ) - 1; 
	timeBaseInit.TIM_Period = period_us - 1;
	timeBaseInit.TIM_Prescaler = prescalerVal;
	timeBaseInit.TIM_ClockDivision = TIM_CKD_DIV1;
	timeBaseInit.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(timer, &timeBaseInit);
	TIM_ARRPreloadConfig(timer, ENABLE);
	TIM_Cmd(timer, ENABLE);
}

/**
* @brief enable timer interruption for a given timer
* @param timer Timer number
* @param priority Interrupt priority
*/

void enable_timer_interrupt(TIM_TypeDef* timer, int priority){
	NVIC_InitTypeDef  NVIC_InitStructure;
	uint8_t TIM_IRQn;
	
	if (timer == TIM1) 
		TIM_IRQn = TIM1_UP_IRQn;
	else if(timer == TIM2)
		TIM_IRQn = TIM2_IRQn;
	else if(timer == TIM3)
		TIM_IRQn = TIM3_IRQn;
	else if(timer == TIM4)
		TIM_IRQn = TIM4_IRQn;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = priority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(timer, TIM_IT_Update, ENABLE);
}

