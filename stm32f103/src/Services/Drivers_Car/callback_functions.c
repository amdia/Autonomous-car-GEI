/**
* @file callback_functions.c
* @brief Driver car layer for the ultrasonic and hall sensors callback functions
*
* Is one level above the @ref IT_functions.c file and one level below the @ref hall_sensor.c and @ref us_sensor.c files
*/

#include <stdint.h>
#include "callback_functions.h"
#include "IT_functions.h"
#include "hall_sensor.h"
#include "us_sensor.h"

/********************************/
/*       Public Functions       */
/********************************/

/**
* Overridable callback function for the GPIO interrupts related to the ultrasonic sensors
* @param  GPIO_Pin GPIO pin
*/
__weak void ultrasonic_exti_callback (uint16_t GPIO_Pin){}
	
/**
* Overridable callback function for the GPIO interrupts related to the hall sensors
* @param  GPIO_Pin GPIO pin
*/
__weak void hall_exti_callback (uint16_t GPIO_Pin){}

/**
* @brief Called every GPIO interruptions. Call a different function if the interruption comes from a hall or an ultrasonic sensor.
* @param  GPIO_Pin GPIO pin
*/
void GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (get_hall_position(GPIO_Pin) != HALL_POSITION_ERROR)
		hall_exti_callback(GPIO_Pin);
	else if (get_ultrasonic_position(GPIO_Pin) != ULTRASONIC_POSITION_ERROR)
		ultrasonic_exti_callback(GPIO_Pin);
	else
		{}
}




