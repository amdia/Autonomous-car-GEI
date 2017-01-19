#include <stdint.h>
#include "callback_functions.h"
#include "IT_functions.h"
#include "hall_sensor.h"
#include "us_sensor.h"

__weak void ultrasonic_exti_callback (uint16_t GPIO_Pin){}
__weak void hall_exti_callback (uint16_t GPIO_Pin){}
	
void GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (get_hall_position(GPIO_Pin) != HALL_POSITION_ERROR)
		hall_exti_callback(GPIO_Pin);
	else if (get_ultrasonic_position(GPIO_Pin) != ULTRASONIC_POSITION_ERROR)
		ultrasonic_exti_callback(GPIO_Pin);
	else
		{}
}




