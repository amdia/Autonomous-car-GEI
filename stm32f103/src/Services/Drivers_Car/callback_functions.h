#ifndef __CALLBACK_FUNCTIONS_H
#define __CALLBACK_FUNCTIONS_H

#include <stdint.h>

void ultrasonic_exti_callback (uint16_t GPIO_Pin);
void hall_exti_callback (uint16_t GPIO_Pin);

#endif // __CALLBACK_FUNCTIONS_H
