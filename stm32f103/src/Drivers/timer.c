 #include <misc.h>
 #include <stm32f10x.h>
 #include "timer.h"
 #include "NVIC_priorities.h"
 
#define IF_DEFINE_IT_FUNCTION(n) \
	if (SCHEDULER_TIMER == TIM##n) \
		Scheduler_TIM_IRQn = TIM##n##_IRQn;\

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


void enable_timer_interrupt(TIM_TypeDef* timer){
	NVIC_InitTypeDef  NVIC_InitStructure;
	uint8_t Scheduler_TIM_IRQn;
	
	if (SCHEDULER_TIMER == TIM1) 
		Scheduler_TIM_IRQn = TIM1_UP_IRQn;
	else{
		IF_DEFINE_IT_FUNCTION(2);
		IF_DEFINE_IT_FUNCTION(3);
		IF_DEFINE_IT_FUNCTION(4);
	}
	
	NVIC_InitStructure.NVIC_IRQChannel = Scheduler_TIM_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = SCHEDULER_IT_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(timer, TIM_IT_Update, ENABLE);
}

