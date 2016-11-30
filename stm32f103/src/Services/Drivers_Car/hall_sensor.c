#include "hall_sensor.h"
#include "sensor_IT.h"
#include "sensors_common.h"
#include "NVIC_priorities.h"

void hall_init(void){
	Sensor_IT_TypeDef sensor_struct;
	
	sensor_struct.gpioMode = GPIO_Mode_IPU;
	sensor_struct.triggerType = EXTI_Trigger_Falling;
	sensor_struct.priority = HALL_PRIO;
	
	sensor_struct.pin = HALL_FRONT_LEFT_PIN;
	sensor_struct.port = HALL_FRONT_LEFT_PORT;
	Sensor_IT_Config(&sensor_struct);
	
	sensor_struct.pin = HALL_FRONT_RIGHT_PIN;
	sensor_struct.port = HALL_FRONT_RIGHT_PORT;
	Sensor_IT_Config(&sensor_struct);
	
	sensor_struct.pin = HALL_REAR_LEFT_PIN;
	sensor_struct.port = HALL_REAR_LEFT_PORT;
	Sensor_IT_Config(&sensor_struct);
	
	sensor_struct.pin = HALL_REAR_RIGHT_PIN;
	sensor_struct.port = HALL_REAR_RIGHT_PORT;
	Sensor_IT_Config(&sensor_struct);
}

__weak void hall_callback(Hall_Position pos){}

void hall_exti_callback (uint16_t GPIO_Pin){
	hall_callback(get_hall_position(GPIO_Pin));
}

Hall_Position get_hall_position(uint16_t GPIO_Pin){
		  if (GPIO_Pin == HALL_FRONT_LEFT_PIN) return HALL_FRONT_LEFT;
	else if (GPIO_Pin == HALL_FRONT_RIGHT_PIN) return HALL_FRONT_RIGHT;
	else if (GPIO_Pin == HALL_REAR_LEFT_PIN) return HALL_REAR_LEFT;
	else if (GPIO_Pin == HALL_REAR_RIGHT_PIN) return HALL_REAR_RIGHT;
	else return HALL_POSITION_ERROR;
}
