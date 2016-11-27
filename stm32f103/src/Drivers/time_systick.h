#ifndef _TIME_SYSTICK_H_
#define _TIME_SYSTICK_H_

#include "stm32f10x.h"

#define SYSTICK_MICROS  1000000

static uint64_t timeMicros;

void systick_init(void);
uint64_t micros(void);
void delay_micros(uint64_t delay_time_micros);

#endif // _TIME_SYSTICK_H_
