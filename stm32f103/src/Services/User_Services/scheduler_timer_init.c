#include "scheduler_timer_init.h"
#include "timer.h"
#include "IT_functions.h"
#include "drivers_car_config.h"
#include "NVIC_priorities.h"

__weak void scheduler_IT_callback(void){}

void scheduler_timer_init(void){
	timer_init(SCHEDULER_TIMER, COUNTER_CLOCK_FREQ_100Hz, PERIOD_US);
	enable_timer_interrupt(SCHEDULER_TIMER, SCHEDULER_IT_PRIORITY);
}
