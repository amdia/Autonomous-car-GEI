/**
* @file sensor_IT.c
* @brief Driver layer for the GPIO sensors based on interruptions
*/

#include "sensor_IT.h"
#include "gpio.h"
#include "IT_functions.h"

/* Private macro -------------------------------------------------------------*/

 /**
* @brief check on which pin is connected the sensor, for exti line 0 to 4 and then do the needed configurations 
*
* 	A macro is a copy-paste
* "##x" allow to concatenate the param to the end of a string
* "##x##" allow to concatenante the param inside a string
* @param n number of the GPIO pin
 */

#define IF_DEFINE_NUM(n) \
	if (initStructSensor->pin == GPIO_Pin_##n) { \
		GPIO_PinSource_Sensor = GPIO_PinSource##n;\
		EXTI_Line_Sensor = EXTI_Line##n;\
		EXTI_IRQn_Sensor = EXTI##n##_IRQn;\
	}\

/**
* @brief check on which pin is connected the sensor, for exti line 5 to 15 and then do the needed configurations
*
* 	A macro is a copy-paste
* "##x" allow to concatenate the param to the end of a string
* "##x##" allow to concatenante the param inside a string
* @param n number of the GPIO pin
* @param n1 first interval number for the exti IRQn
* @param n2 second interval number for the exti IRQn
 */
	
#define IF_DEFINE_NUM_2(n,n1,n2) \
	if (initStructSensor->pin == GPIO_Pin_##n) { \
		GPIO_PinSource_Sensor = GPIO_PinSource##n;\
		EXTI_Line_Sensor = EXTI_Line##n;\
		EXTI_IRQn_Sensor = EXTI##n1##_##n2##_IRQn;\
	}\

/* Private function prototypes -----------------------------------------------*/
static void EXTI_Config(Sensor_IT_TypeDef* initStructSensor);

/********************************/
/*      Public Functions        */
/********************************/
	
/**
* @brief  Do the configuration for a given sensor based on interruption. Configures the GPIO and the EXTI
* @param  initStructSensor sensor structure contains the information necessary to the configuration and is read by this function
*/
void Sensor_IT_Config(Sensor_IT_TypeDef* initStructSensor) {
	// Configure the GPIO port
	GPIO_Configuration(initStructSensor);

	//Configure external interruption
	EXTI_Config(initStructSensor);
}

/**
* @brief  return the value from the sensor
* @param  structSensor sensor structure is read by this function
* @retval value read from the sensor
*/
unsigned int Sensor_IT_Read(Sensor_IT_TypeDef* structSensor) {
	return GPIO_ReadInputDataBit(structSensor->port, structSensor->pin);
}

/**
* @brief  gpio configuration (pin, port, mode)
* @param  initStructSensor sensor structure contains the information necessary to the configuration and is read by this function
*/
void GPIO_Configuration(Sensor_IT_TypeDef* initStructSensor) {
	GPIO_init(initStructSensor->port, initStructSensor->pin, initStructSensor->gpioMode);
}

/********************************/
/*      Private Functions       */
/********************************/

/**
* @brief  exti configuration (line, port, priority, trigger type)
* @param  initStructSensor sensor structure contains the information necessary to the configuration and is read by this function
*/
void EXTI_Config(Sensor_IT_TypeDef* initStructSensor) {
	EXTI_InitTypeDef 		EXTI_InitStructure;
	NVIC_InitTypeDef  	NVIC_InitStructure;
	uint8_t 					GPIO_PortSource_Sensor;
	uint8_t 					GPIO_PinSource_Sensor;
	uint32_t 				EXTI_Line_Sensor;
	uint8_t 					EXTI_IRQn_Sensor;

	//GPIO_EXTILineConfig function need to receive a GPIO port parameter 
	//but its value is different from the one used for GPIO configuration
	//so it is necessary to find the parameter corresponding to exti configuration
	if (initStructSensor->port == GPIOA) {
			GPIO_PortSource_Sensor = GPIO_PortSourceGPIOA;
	} else if (initStructSensor->port == GPIOB) {
			GPIO_PortSource_Sensor = GPIO_PortSourceGPIOB;
	} else if (initStructSensor->port == GPIOC) {
			GPIO_PortSource_Sensor = GPIO_PortSourceGPIOC;
	} else if(initStructSensor->port == GPIOD) {
			GPIO_PortSource_Sensor = GPIO_PortSourceGPIOD;
	} else if(initStructSensor->port == GPIOE) {
			GPIO_PortSource_Sensor = GPIO_PortSourceGPIOE;
	} else if(initStructSensor->port == GPIOF) {
			GPIO_PortSource_Sensor = GPIO_PortSourceGPIOF;
	} else if(initStructSensor->port == GPIOG) {
			GPIO_PortSource_Sensor = GPIO_PortSourceGPIOG;
	}

	//GPIO_EXTILineConfig function need to receive a GPIO pin parameter 
	//but its value is different from the one used for GPIO configuration
	//so it is necessary to find the parameter corresponding to exti configuration
	
	//find the right pin source, the exti line and the exti IRQn according to the GPIO pin number
  IF_DEFINE_NUM(0)
	else IF_DEFINE_NUM(1)
	else IF_DEFINE_NUM(2)
	else IF_DEFINE_NUM(3)
	else IF_DEFINE_NUM(4)
	else IF_DEFINE_NUM_2(5,9,5)
	else IF_DEFINE_NUM_2(6,9,5)
	else IF_DEFINE_NUM_2(7,9,5)
	else IF_DEFINE_NUM_2(8,9,5)
	else IF_DEFINE_NUM_2(9,9,5)
	else IF_DEFINE_NUM_2(10,15,10)
	else IF_DEFINE_NUM_2(11,15,10)
	else IF_DEFINE_NUM_2(12,15,10)
	else IF_DEFINE_NUM_2(13,15,10)
	else IF_DEFINE_NUM_2(14,15,10)
	else IF_DEFINE_NUM_2(15,15,10)
		
	//configure the port and the pin source
	GPIO_EXTILineConfig(GPIO_PortSource_Sensor,  GPIO_PinSource_Sensor);

	//Give the right parameters to the exti structure
	EXTI_InitStructure.EXTI_Line = EXTI_Line_Sensor;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = initStructSensor->triggerType;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	//initialization of the exti structure
	EXTI_Init(&EXTI_InitStructure);

	//Give the right parameters to the nvic structure
	NVIC_InitStructure.NVIC_IRQChannel = EXTI_IRQn_Sensor;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = initStructSensor->priority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //we do not use sub priority in the whole project
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//initialization of the nvic structure
	NVIC_Init(&NVIC_InitStructure);
}
