#ifndef _SCHEDULER_TIMER_H_
#define _SCHEDULER_TIMER_H_

#define COUNTER_CLOCK_FREQ_100Hz  	1e4
#define PERIOD_US 						10

void scheduer_timer_init(void);
void scheduler_enable_timer_interrupt(void);

#endif // _SCHEDULER_TIMER_H_
