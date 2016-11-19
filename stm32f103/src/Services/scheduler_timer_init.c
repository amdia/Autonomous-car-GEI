#include "scheduler_timer.h"
#include "scheduler_timer_init.h"

__weak void scheduler_IT_callback(void){}

void scheduler_timer_init(void){
	scheduer_timer_init();
	scheduler_enable_timer_interrupt();
}
