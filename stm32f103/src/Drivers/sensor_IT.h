#ifndef __SENSOR_IT_H
#define __SENSOR_IT_H

#include <stm32f10x.h>

/**
* @brief Structure that contains about a sensor using GPIO interruptions
*/
typedef struct {
	/** Pin to which the sensor is connected */
	uint16_t pin;
	/** Port to which the sensor is connected */
	GPIO_TypeDef* port;
	/** GPIO mode */
	GPIOMode_TypeDef gpioMode;
	/** Type of trigger that makes the interruption happens */
	EXTITrigger_TypeDef triggerType;
	/** Priority of the interruption */
	uint8_t priority;
} Sensor_IT_TypeDef;


void Sensor_IT_Config(Sensor_IT_TypeDef* initStructSensor);
void GPIO_Configuration(Sensor_IT_TypeDef* initStructSensor);

unsigned int Sensor_IT_Read(Sensor_IT_TypeDef* structSensor);

#endif // __SENSOR_IT_H
