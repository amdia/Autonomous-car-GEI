#include "us_sensor.h"

#include "time_systick.h"
#include "sensor_IT.h"
#include "callback_functions.h"
#include "drivers_car_config.h"
#include <stm32f10x_gpio.h>

// macros, lazy way configure echo pins
#define ULTRASONIC_CONFIG_ECHO_PINS(name)  \
  do { \
    ultrasonic_##name.pin = ULTRASONIC_##name##_ECHO_PIN;  \
    ultrasonic_##name.port = ULTRASONIC_##name##_ECHO_PORT;  \
    ultrasonic_##name.gpioSpeed = GPIO_SPEED;  \
    ultrasonic_##name.gpioMode = GPIO_Mode_IPU;  \
    ultrasonic_##name.triggerType = EXTI_Trigger_Rising_Falling; \
    ultrasonic_##name.priority = ULTRASONIC_PRIO;  \
    Sensor_IT_Config(&ultrasonic_##name);  \
  } while(0) \

#define ULTRASONIC_SET_ECHO_PIN_TO_GROUND(name)   \
  do {  \
    ultrasonic_##name.gpioMode = GPIO_Mode_Out_OD; \
    GPIO_Configuration(&ultrasonic_##name);  \
    GPIO_WriteBit(ULTRASONIC_##name##_ECHO_PORT, ULTRASONIC_##name##_ECHO_PIN, Bit_RESET);  \
  } while(0)  \
  
#define ULTRASONIC_BRING_ECHO_PIN_BACK(name)    \
  do {  \
    ultrasonic_##name.gpioMode = GPIO_Mode_IPU;  \
    GPIO_Configuration(&ultrasonic_##name);  \
  } while(0)  \
  
  
// ---------------------------- //
// ----- Private section ------ //
// ---------------------------- //
  
// declaration of 6 ultrasonic echo pins
static Sensor_IT_TypeDef ultrasonic_AVC;
static Sensor_IT_TypeDef ultrasonic_AVG;
static Sensor_IT_TypeDef ultrasonic_AVD;
static Sensor_IT_TypeDef ultrasonic_ARC;
static Sensor_IT_TypeDef ultrasonic_ARG;
static Sensor_IT_TypeDef ultrasonic_ARD;

// private variable storing rise time of each echo signal
static float pulse_length[ULTRASONIC_NB] = {0};

// private functions which set and reset trig pin
static void ultrasonic_trigger(void);
static void ultrasonic_untrigger(void);
static void ultrasonic_reset_all_echo_pins(void);

// overloadable callback function, reserved for user
__weak void ultrasonic_callback(Ultrasonic_Position pos) {}

void init_ultrasonic_sensors(void) {
  // configure 6 echo pins as input with EXTI
	ULTRASONIC_CONFIG_ECHO_PINS(AVC);
  ULTRASONIC_CONFIG_ECHO_PINS(AVG);
  ULTRASONIC_CONFIG_ECHO_PINS(AVD);
  ULTRASONIC_CONFIG_ECHO_PINS(ARC);
  ULTRASONIC_CONFIG_ECHO_PINS(ARG);
  ULTRASONIC_CONFIG_ECHO_PINS(ARD);
  
  // configure trig pin as output push-pull
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = ULTRASONIC_TRIG_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED;
  GPIO_Init(ULTRASONIC_TRIG_PORT, &GPIO_InitStructure);
}

void ultrasonic_trig_all(void) {
	ultrasonic_reset_all_echo_pins();
	ultrasonic_trigger();
	delay_micros(ULTRASONIC_TRIGGER_DELAY);
	ultrasonic_untrigger();
}

void ultrasonic_trigger(void) {
	GPIO_WriteBit(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, Bit_SET);
}

void ultrasonic_untrigger(void) {
	GPIO_WriteBit(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, Bit_RESET);
}

void ultrasonic_reset_all_echo_pins(void) {
  // set all echo pin to output then bring them to low state
  ULTRASONIC_SET_ECHO_PIN_TO_GROUND(AVC);
  ULTRASONIC_SET_ECHO_PIN_TO_GROUND(AVG);
  ULTRASONIC_SET_ECHO_PIN_TO_GROUND(AVD);
  ULTRASONIC_SET_ECHO_PIN_TO_GROUND(ARC);
  ULTRASONIC_SET_ECHO_PIN_TO_GROUND(ARG);
  ULTRASONIC_SET_ECHO_PIN_TO_GROUND(ARD);
  // delay for a short time, hopefully it will work
  delay_micros(ULTRASONIC_DELAY_RESET_ECHO_PIN);
  // let's bring them back to input
  ULTRASONIC_BRING_ECHO_PIN_BACK(AVC);
  ULTRASONIC_BRING_ECHO_PIN_BACK(AVG);
  ULTRASONIC_BRING_ECHO_PIN_BACK(AVD);
  ULTRASONIC_BRING_ECHO_PIN_BACK(ARC);
  ULTRASONIC_BRING_ECHO_PIN_BACK(ARG);
  ULTRASONIC_BRING_ECHO_PIN_BACK(ARD);
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
