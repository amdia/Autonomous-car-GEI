#ifndef _SCHEDULER_TIMER_INIT_H_
#define _SCHEDULER_TIMER_INIT_H_

#define COUNTER_CLOCK_FREQ_100Hz  	1e4
#define PERIOD_US 						10

void scheduler_timer_init(void);
void scheduler_IT_callback(void);

#endif // _SCHEDULER_TIMER_INIT_H_
