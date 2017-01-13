/**
* @file time_systick.c
* @brief driver layer for handling time (delay, system timer interruption)
*/
#include "time_systick.h"
#include <stdint.h>
#include "NVIC_priorities.h"

/********************************/
/*      Public Functions        */
/********************************/

/**
* @brief  systick initialization. The systick priority has to be the highest one
* but nothing else than the counter has to be in the interrupt handler so it takes very few time
* and does not block the rest by doing long interrupt all the time
* @param  None
* @retval None
*/
void systick_init(void) {
  timeMicros = 0;
  while (SysTick_Config(SystemCoreClock / SYSTICK_MICROS) != 0);
  NVIC_SetPriority(SysTick_IRQn, SYSTICK_PRIORITY);
}

/**
 * @brief  return the time in microseconds since the sistick has been init
 * @param  None
 * @retval time in microseconds
 */
uint64_t micros(void) {
  return timeMicros;
}

/**
 * @brief  Generate a sleep. To use carefully because it is a blocking function because of the while
 * @param  None
 * @retval None
 */
void delay_micros(uint64_t delay_time_micros) {
  uint64_t time_tmp = micros();
  while (micros() - time_tmp < delay_time_micros);
}

/********************************/
/*      Private Functions       */
/********************************/
/**
* @brief  This function handles SysTick_Handler interrupt request.
* @param  None
* @retval None
*/
void SysTick_Handler(void) {
  timeMicros++;
}
