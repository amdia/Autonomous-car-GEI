/**
* @file scheduler_timer_init.c
* @brief Service layer for the scheduler
*/
#include "scheduler_timer_init.h"
#include "timer.h"
#include "IT_functions.h"
#include "drivers_car_config.h"
#include "NVIC_priorities.h"

/********************************/
/*       Public Functions       */
/********************************/

/**
* @brief  Overridable callback function for scheduler interruptions
*/
__weak void scheduler_IT_callback(void){}

/**
* @brief Initialization of the scheduler. From there, interruptions happen every tick of the timer
*/	
void scheduler_timer_init(void){
	// Initialization of the timer dedicated to the scheduler
	timer_init(SCHEDULER_TIMER, COUNTER_CLOCK_FREQ_100Hz, PERIOD_US); 
	// Enable the interruptions of the timer - From there, interruptions happen every tick of the timer
	enable_timer_interrupt(SCHEDULER_TIMER, SCHEDULER_IT_PRIORITY);
}
