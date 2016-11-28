#include <stdint.h>
#include "time_systick.h"

void systick_init(void) {
  timeMicros = 0;
  while (SysTick_Config(SystemCoreClock / SYSTICK_MICROS) != 0);
  NVIC_SetPriority(SysTick_IRQn, 0);
}

uint64_t micros(void) {
  return timeMicros;
}

void delay_micros(uint64_t delay_time_micros) {
  uint64_t time_tmp = micros();
  while (micros() - time_tmp < delay_time_micros);
}

// Systick's interruption, add things here if you feel like to
void SysTick_Handler(void) {
  timeMicros++;
}
