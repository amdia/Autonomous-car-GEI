/**
* @file us_sensor.c
* @brief Driver car layer for ultrasonic sensors
*/

#include "us_sensor.h"
#include <stm32f10x.h>
#include "gpio.h"
#include "time_systick.h"
#include "sensors_common.h"
#include "sensor_IT.h"
#include "NVIC_priorities.h"
    
/* Private function prototypes -----------------------------------------------*/
static void ultrasonic_config_echo_pin(Sensor_IT_TypeDef *ultrasonic_struct, uint16_t pin, GPIO_TypeDef* port);
static void ultrasonic_reset_echo_pin(Sensor_IT_TypeDef *ultrasonic_struct);
static void ultrasonic_reinit(Sensor_IT_TypeDef *ultrasonic_struct);
static void ultrasonic_trigger(void);
static void ultrasonic_untrigger(void);
static void ultrasonic_reset_all_echo_pins(void);
 
/* Private variables ---------------------------------------------------------*/

// Declaration of 6 ultrasonic echo pins
Sensor_IT_TypeDef ultrasonic_front_center;
Sensor_IT_TypeDef ultrasonic_front_left;
Sensor_IT_TypeDef ultrasonic_front_right;
Sensor_IT_TypeDef ultrasonic_rear_center;
Sensor_IT_TypeDef ultrasonic_rear_left;
Sensor_IT_TypeDef ultrasonic_rear_right;

/**
* @brief Stores the raised time of each echo signal
*/
float pulse_length[ULTRASONIC_NB] = {0};

/********************************/
/*       Public Functions       */
/********************************/

/**
* @brief  Overridable callback function for ultrasonic interruptions
* @param  pos ultrasonic sensor position
*/
__weak void ultrasonic_callback(Ultrasonic_Position pos) {}

/**
* @brief  Initialization of the 6 ultrasonic sensors : configuration of 6 echo pins as input with EXTI and 1 trig pin as output push-pull
*/
void ultrasonic_init(void) {
	// Configure 6 echo pins as input with EXTI
	ultrasonic_config_echo_pin(&ultrasonic_front_center, ULTRASONIC_FRONT_CENTER_ECHO_PIN, ULTRASONIC_FRONT_CENTER_ECHO_PORT);
	ultrasonic_config_echo_pin(&ultrasonic_front_left, ULTRASONIC_FRONT_LEFT_ECHO_PIN, ULTRASONIC_FRONT_LEFT_ECHO_PORT);
	ultrasonic_config_echo_pin(&ultrasonic_front_right, ULTRASONIC_FRONT_RIGHT_ECHO_PIN, ULTRASONIC_FRONT_RIGHT_ECHO_PORT);
	ultrasonic_config_echo_pin(&ultrasonic_rear_center, ULTRASONIC_REAR_CENTER_ECHO_PIN, ULTRASONIC_REAR_CENTER_ECHO_PORT);
	ultrasonic_config_echo_pin(&ultrasonic_rear_left, ULTRASONIC_REAR_LEFT_ECHO_PIN, ULTRASONIC_REAR_LEFT_ECHO_PORT);
	ultrasonic_config_echo_pin(&ultrasonic_rear_right, ULTRASONIC_REAR_RIGHT_ECHO_PIN, ULTRASONIC_REAR_RIGHT_ECHO_PORT);
	
	// Configure trig pin as output push-pull
	GPIO_init(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_Mode_Out_PP);
}

/**
* @brief Send the pulse which trig the ultrasonic sensors
*
* All ultrasonic sensors are connected to the same trigger
*/
void ultrasonic_trig_all(void) {
	// Reset all echo pins to set them to 0 if they are stuck to 1 because of the previous trig. (do not completly fix the bug)
	ultrasonic_reset_all_echo_pins();
	
	// Set the trig pin to 1 during ULTRASONIC_TRIGGER_DELAY time
	ultrasonic_trigger();
	delay_micros(ULTRASONIC_TRIGGER_DELAY);
	ultrasonic_untrigger();
}

/**
* @brief  Callback function for ultrasonic interruptions.
*
* This function is called everytime one of the echo pin goes high or goes low (every changes of state)
* @param  GPIO_Pin ultrasonic sensor echo pin
*/
void ultrasonic_exti_callback (uint16_t GPIO_Pin) {
	// Store the time to which the echo pin goes high
	static uint64_t time_tmp[ULTRASONIC_NB] = {0};
	// Store current state of the ultrasonic echo pin
	static FlagStatus state[ULTRASONIC_NB] = {RESET};
	// Store the echo pin which raised the current interruption
	Ultrasonic_Position position = get_ultrasonic_position(GPIO_Pin);
	
	// If the echo pin was previously RESET, update the current state to SET and save the time when it happened
	if(state[position] == RESET) {
		state[position] = SET;
		time_tmp[position] = micros();
	}
	// If the echo pin was previously SET, update the current state to RESET and calculate the time during which the pulse was high
	else{
		state[position] = RESET;
		pulse_length[position] = micros() - time_tmp[position];
		ultrasonic_callback(position);
	}
}

/********************************/
/*      Private Functions       */
/********************************/

/**
* @brief  Set the trig pin to 1
*/
void ultrasonic_trigger(void) {
	GPIO_set(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN);
}

/**
* @brief  Set the trig pin to 0
*/
void ultrasonic_untrigger(void) {
	GPIO_reset(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN);
}

/**
* @brief Reset all the echo pins
*/
void ultrasonic_reset_all_echo_pins(void) {
	// Set all echo pin to output then bring them to low state
	ultrasonic_reset_echo_pin(&ultrasonic_front_center);
	ultrasonic_reset_echo_pin(&ultrasonic_front_left);
	ultrasonic_reset_echo_pin(&ultrasonic_front_right);
	ultrasonic_reset_echo_pin(&ultrasonic_rear_center);
	ultrasonic_reset_echo_pin(&ultrasonic_rear_left);
	ultrasonic_reset_echo_pin(&ultrasonic_rear_right);

	// Delay for a short time, hopefully it will work
	delay_micros(ULTRASONIC_DELAY_RESET_ECHO_PIN);
	
	// Let's bring them back to input
	ultrasonic_reinit(&ultrasonic_front_center);
	ultrasonic_reinit(&ultrasonic_front_left);
	ultrasonic_reinit(&ultrasonic_front_right);
	ultrasonic_reinit(&ultrasonic_rear_center);
	ultrasonic_reinit(&ultrasonic_rear_left);
	ultrasonic_reinit(&ultrasonic_rear_right);
}

/**
* @brief Convert the pulse length of the echo pin into a distance
* @param pos #Ultrasonic_Position of the sensor
* @retval distance in centimeters
*/
int ultrasonic_get_distance(Ultrasonic_Position pos) {
	// Formula obtained from the sensors documentation. Can be retrieved with the wave speed.
	return (int)(pulse_length[pos] / ULTRASONIC_CONVERSION_CONSTANT);
}

/**
* @brief Return the #Ultrasonic_Position of the ultrasonic sensor for a given GPIO pin
* @param GPIO_Pin ultrasonic sensor GPIO echo pin
* @retval #Ultrasonic_Position of the ultrasonic sensor
*/
Ultrasonic_Position get_ultrasonic_position(uint16_t GPIO_Pin) {
		  if (GPIO_Pin == ULTRASONIC_FRONT_CENTER_ECHO_PIN) return ULTRASONIC_FRONT_CENTER;
	else if (GPIO_Pin == ULTRASONIC_FRONT_LEFT_ECHO_PIN) return ULTRASONIC_FRONT_LEFT;
	else if (GPIO_Pin == ULTRASONIC_FRONT_RIGHT_ECHO_PIN) return ULTRASONIC_FRONT_RIGHT;
	else if (GPIO_Pin == ULTRASONIC_REAR_CENTER_ECHO_PIN) return ULTRASONIC_REAR_CENTER;
	else if (GPIO_Pin == ULTRASONIC_REAR_LEFT_ECHO_PIN) return ULTRASONIC_REAR_LEFT;
	else if (GPIO_Pin == ULTRASONIC_REAR_RIGHT_ECHO_PIN) return ULTRASONIC_REAR_RIGHT;
	else return ULTRASONIC_POSITION_ERROR;
}

/**
* @brief Configure an echo pin with interruptions for an ultrasonic sensor
* @param ultrasonic_struct ultrasonic sensor structure to be initialized
* @param pin GPIO pin to which the ultrasonic sensor is connected
* @param port GPIO port to which the ultrasonic sensor is connected
*/
void ultrasonic_config_echo_pin(Sensor_IT_TypeDef *ultrasonic_struct, uint16_t pin, GPIO_TypeDef* port){
	ultrasonic_struct->pin = pin;  
	ultrasonic_struct->port = port;  
	ultrasonic_struct->gpioMode = GPIO_Mode_IPU;  
	ultrasonic_struct->triggerType = EXTI_Trigger_Rising_Falling; 
	ultrasonic_struct->priority = ULTRASONIC_PRIO; 
	Sensor_IT_Config(ultrasonic_struct);  
}

/**
* @brief Reset an echo pin
*
* Change the mode to output and write a 0
* @param ultrasonic_struct ultrasonic sensor structure to be modified
*/
void ultrasonic_reset_echo_pin(Sensor_IT_TypeDef *ultrasonic_struct){
	 ultrasonic_struct->gpioMode = GPIO_Mode_Out_OD;
    GPIO_Configuration(ultrasonic_struct); 
    GPIO_reset(ultrasonic_struct->port, ultrasonic_struct->pin);
}

/**
* @brief Reinitialize an echo pin
*
* Change the mode to input
* @param ultrasonic_struct ultrasonic sensor structure to be modified
*/
void ultrasonic_reinit(Sensor_IT_TypeDef *ultrasonic_struct){
    ultrasonic_struct->gpioMode = GPIO_Mode_IPU;
    GPIO_Configuration(ultrasonic_struct);
}
