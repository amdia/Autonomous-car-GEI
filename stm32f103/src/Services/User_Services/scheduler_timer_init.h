#ifndef _SCHEDULER_TIMER_INIT_H_
#define _SCHEDULER_TIMER_INIT_H_

/** Counter clock frequency of the scheduler */
#define COUNTER_CLOCK_FREQ_10kHz  	1e4
/** Period in microseconds of the scheduler */
#define PERIOD_US 						10

void scheduler_timer_init(void);
void scheduler_IT_callback(void);

#endif // _SCHEDULER_TIMER_INIT_H_
