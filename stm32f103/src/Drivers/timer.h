#ifndef _TIMER_H_
#define _TIMER_H_

#include <stm32f10x.h>

/** Timer on which is initialized the scheduler */
#define SCHEDULER_TIMER         	TIM2

void timer_init(TIM_TypeDef* timer, int counter_clock_frequency, int period_us);
void enable_timer_interrupt(TIM_TypeDef* timer, int priority);

#endif // _TIMER_H_
