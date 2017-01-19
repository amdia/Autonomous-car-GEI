/**
* @file hall_sensor.c
* @brief Driver car layer for the hall sensors
*/

#include "hall_sensor.h"
#include "sensor_IT.h"
#include "sensors_common.h"
#include "NVIC_priorities.h"

/********************************/
/*       Public Functions       */
/********************************/

/**
* @brief  Overridable callback function for hall sensor interruptions
* @param  pos hall sensor position
*/
__weak void hall_callback(Hall_Position pos){}

/**
* @brief  Initialization of the 4 hall sensors : 2 for the front stops and 2 for the rear wheels.
*/
void hall_init(void){
	Sensor_IT_TypeDef sensor_struct;
	
	// Common configuration to the 4 hall sensors
	// GPIO as input
	sensor_struct.gpioMode = GPIO_Mode_IPU;
	// Interruption happens on falling edge
	sensor_struct.triggerType = EXTI_Trigger_Falling;
	// Common priority to the 4 hall sensors
	sensor_struct.priority = HALL_PRIO;
	
	// Hall sensor for the left front stop
	sensor_struct.pin = HALL_FRONT_LEFT_PIN;
	sensor_struct.port = HALL_FRONT_LEFT_PORT;
	Sensor_IT_Config(&sensor_struct);
	
	// Hall sensor for the right front stop
	sensor_struct.pin = HALL_FRONT_RIGHT_PIN;
	sensor_struct.port = HALL_FRONT_RIGHT_PORT;
	Sensor_IT_Config(&sensor_struct);
	
	// Hall sensor for the left wheel
	sensor_struct.pin = HALL_REAR_LEFT_PIN;
	sensor_struct.port = HALL_REAR_LEFT_PORT;
	Sensor_IT_Config(&sensor_struct);

	// Hall sensor for the right wheel
	sensor_struct.pin = HALL_REAR_RIGHT_PIN;
	sensor_struct.port = HALL_REAR_RIGHT_PORT;
	Sensor_IT_Config(&sensor_struct);
}

/**
* @brief  Callback function for hall sensors interruptions.
*
* This function is called everytime one of the hall sensors stops to be in front of a magnet (falling edge)
* @param  GPIO_Pin hall sensor pin
*/
void hall_exti_callback (uint16_t GPIO_Pin){
	hall_callback(get_hall_position(GPIO_Pin));
}

/**
* @brief Return the #Hall_Position of the hall sensor for a given GPIO pin
* @param GPIO_Pin hall sensor GPIO pin
* @retval #Hall_Position of the hall sensor
*/
Hall_Position get_hall_position(uint16_t GPIO_Pin){
		  if (GPIO_Pin == HALL_FRONT_LEFT_PIN) return HALL_FRONT_LEFT;
	else if (GPIO_Pin == HALL_FRONT_RIGHT_PIN) return HALL_FRONT_RIGHT;
	else if (GPIO_Pin == HALL_REAR_LEFT_PIN) return HALL_REAR_LEFT;
	else if (GPIO_Pin == HALL_REAR_RIGHT_PIN) return HALL_REAR_RIGHT;
	else return HALL_POSITION_ERROR;
}
