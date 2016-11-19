 #include <misc.h>
 #include <stm32f10x.h>
 #include <stm32f10x_tim.h>
 #include "scheduler_timer.h"
 #include "services_config.h"
 
#define IF_DEFINE_IT_FUNCTION(n) \
	if (SCHEDULER_TIMER == TIM##n) \
		Scheduler_TIM_IRQn = TIM##n##_IRQn;\

void scheduer_timer_init(void){
	TIM_TimeBaseInitTypeDef timeBaseInit;
	uint16_t prescalerVal = 0;

	prescalerVal = (uint16_t)(SystemCoreClock / COUNTER_CLOCK_FREQ_100Hz ) - 1; 
	timeBaseInit.TIM_Period = PERIOD_US - 1;
	timeBaseInit.TIM_Prescaler = prescalerVal;
	timeBaseInit.TIM_ClockDivision = TIM_CKD_DIV1;
	timeBaseInit.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(SCHEDULER_TIMER, &timeBaseInit);
	TIM_Cmd(SCHEDULER_TIMER, ENABLE);
	TIM_ITConfig(SCHEDULER_TIMER, TIM_IT_Update, ENABLE);
}


void scheduler_enable_timer_interrupt(void){
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
}

