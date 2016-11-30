#include "us_sensor.h"
#include <stm32f10x.h>
#include "gpio.h"
#include "time_systick.h"
#include "sensors_common.h"
#include "sensor_IT.h"
#include "NVIC_priorities.h"
    
// ---------------------------- //
// ----- Private section ------ //
// ---------------------------- //
static void ultrasonic_config_echo_pin(Sensor_IT_TypeDef ultrasonic_struct, uint16_t pin, GPIO_TypeDef* port);
static void ultrasonic_reset_echo_pin(Sensor_IT_TypeDef ultrasonic_struct);
static void ultrasonic_reinit(Sensor_IT_TypeDef ultrasonic_struct);
 
// declaration of 6 ultrasonic echo pins
Sensor_IT_TypeDef ultrasonic_front_center;
Sensor_IT_TypeDef ultrasonic_front_left;
Sensor_IT_TypeDef ultrasonic_front_right;
Sensor_IT_TypeDef ultrasonic_rear_center;
Sensor_IT_TypeDef ultrasonic_rear_left;
Sensor_IT_TypeDef ultrasonic_rear_right;

// private variable storing rise time of each echo signal
float pulse_length[ULTRASONIC_NB] = {0};

// private functions which set and reset trig pin
static void ultrasonic_trigger(void);
static void ultrasonic_untrigger(void);
static void ultrasonic_reset_all_echo_pins(void);

// overloadable callback function, reserved for user
__weak void ultrasonic_callback(Ultrasonic_Position pos) {}

void ultrasonic_init(void) {
  // configure 6 echo pins as input with EXTI
	ultrasonic_config_echo_pin(ultrasonic_front_center, ULTRASONIC_FRONT_CENTER_ECHO_PIN, ULTRASONIC_FRONT_CENTER_ECHO_PORT);
	ultrasonic_config_echo_pin(ultrasonic_front_left, ULTRASONIC_FRONT_LEFT_ECHO_PIN, ULTRASONIC_FRONT_LEFT_ECHO_PORT);
	ultrasonic_config_echo_pin(ultrasonic_front_right, ULTRASONIC_FRONT_RIGHT_ECHO_PIN, ULTRASONIC_FRONT_RIGHT_ECHO_PORT);
	ultrasonic_config_echo_pin(ultrasonic_rear_center, ULTRASONIC_REAR_CENTER_ECHO_PIN, ULTRASONIC_REAR_CENTER_ECHO_PORT);
	ultrasonic_config_echo_pin(ultrasonic_rear_left, ULTRASONIC_REAR_LEFT_ECHO_PIN, ULTRASONIC_REAR_LEFT_ECHO_PORT);
	ultrasonic_config_echo_pin(ultrasonic_rear_right, ULTRASONIC_REAR_RIGHT_ECHO_PIN, ULTRASONIC_REAR_RIGHT_ECHO_PORT);
  // configure trig pin as output push-pull
	GPIO_init(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, GPIO_Mode_Out_PP);
}

void ultrasonic_trig_all(void) {
	ultrasonic_reset_all_echo_pins();
	ultrasonic_trigger();
	delay_micros(ULTRASONIC_TRIGGER_DELAY);
	ultrasonic_untrigger();
}

void ultrasonic_trigger(void) {
	GPIO_set(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN);
}

void ultrasonic_untrigger(void) {
	GPIO_reset(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN);
}

void ultrasonic_reset_all_echo_pins(void) {
	// set all echo pin to output then bring them to low state
	ultrasonic_reset_echo_pin(ultrasonic_front_center);
	ultrasonic_reset_echo_pin(ultrasonic_front_left);
	ultrasonic_reset_echo_pin(ultrasonic_front_right);
	ultrasonic_reset_echo_pin(ultrasonic_rear_center);
	ultrasonic_reset_echo_pin(ultrasonic_rear_left);
	ultrasonic_reset_echo_pin(ultrasonic_rear_right);

	// delay for a short time, hopefully it will work
	delay_micros(ULTRASONIC_DELAY_RESET_ECHO_PIN);
	// let's bring them back to input
	ultrasonic_reinit(ultrasonic_front_center);
	ultrasonic_reinit(ultrasonic_front_left);
	ultrasonic_reinit(ultrasonic_front_right);
	ultrasonic_reinit(ultrasonic_rear_center);
	ultrasonic_reinit(ultrasonic_rear_left);
	ultrasonic_reinit(ultrasonic_rear_right);
}

void ultrasonic_exti_callback (uint16_t GPIO_Pin) {
  static uint64_t time_tmp[ULTRASONIC_NB] = {0};
  static Ultrasonic_State state[ULTRASONIC_NB] = {DOWN};
	Ultrasonic_Position position = get_ultrasonic_position(GPIO_Pin);
	if(state[position] == DOWN) {
		state[position] = UP;
		time_tmp[position] = micros();
	} else {
		state[position] = DOWN;
		pulse_length[position] = micros() - time_tmp[position];
		ultrasonic_callback(position);
	}
}

int ultrasonic_get_distance(Ultrasonic_Position pos) {
  return (int)(pulse_length[pos] / ULTRASONIC_CONVERSION_CONSTANT);
}

Ultrasonic_Position get_ultrasonic_position(uint16_t GPIO_Pin) {
		  if (GPIO_Pin == ULTRASONIC_FRONT_CENTER_ECHO_PIN) return ULTRASONIC_FRONT_CENTER;
	else if (GPIO_Pin == ULTRASONIC_FRONT_LEFT_ECHO_PIN) return ULTRASONIC_FRONT_LEFT;
	else if (GPIO_Pin == ULTRASONIC_FRONT_RIGHT_ECHO_PIN) return ULTRASONIC_FRONT_RIGHT;
	else if (GPIO_Pin == ULTRASONIC_REAR_CENTER_ECHO_PIN) return ULTRASONIC_REAR_CENTER;
	else if (GPIO_Pin == ULTRASONIC_REAR_LEFT_ECHO_PIN) return ULTRASONIC_REAR_LEFT;
	else if (GPIO_Pin == ULTRASONIC_REAR_RIGHT_ECHO_PIN) return ULTRASONIC_REAR_RIGHT;
	else return ULTRASONIC_POSITION_ERROR;
}

void ultrasonic_config_echo_pin(Sensor_IT_TypeDef ultrasonic_struct, uint16_t pin, GPIO_TypeDef* port){
	ultrasonic_struct.pin = pin;  
	ultrasonic_struct.port = port;  
	ultrasonic_struct.gpioMode = GPIO_Mode_IPU;  
	ultrasonic_struct.triggerType = EXTI_Trigger_Rising_Falling; 
	ultrasonic_struct.priority = ULTRASONIC_PRIO;  
	Sensor_IT_Config(&ultrasonic_struct);  
}

void ultrasonic_reset_echo_pin(Sensor_IT_TypeDef ultrasonic_struct){
	 ultrasonic_struct.gpioMode = GPIO_Mode_Out_OD;
    GPIO_Configuration(&ultrasonic_struct); 
    GPIO_reset(ultrasonic_struct.port, ultrasonic_struct.pin);
}

void ultrasonic_reinit(Sensor_IT_TypeDef ultrasonic_struct){
    ultrasonic_struct.gpioMode = GPIO_Mode_IPU;
    GPIO_Configuration(&ultrasonic_struct);
}
